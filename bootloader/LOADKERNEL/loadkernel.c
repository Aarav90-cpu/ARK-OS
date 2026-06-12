#include "loadkernel.h"
#include "../OUTPUT/DISPLAY/display.h"
#include "efi.h"
#include "../../kernel/UEFI/elf.h"
#include "../../kernel/SHARED/bootinfo.h"

static bool gVerbose = false;

bool GetVerboseMode(void) {
    return gVerbose;
}

void ToggleVerboseMode(void) {
    gVerbose = !gVerbose;
}

int memcmpEfi(const void *s1, const void *s2, UINTN n) {
    const uint8_t *p1 = s1, *p2 = s2;
    while(n--) {
        if(*p1 != *p2) return *p1 - *p2;
        p1++; p2++;
    }
    return 0;
}

void PrintHex(uint64_t val) {
    uint16_t buf[19];
    buf[0] = u'0'; buf[1] = u'x'; buf[18] = 0;
    for (int i = 17; i >= 2; i--) {
        int nibble = val & 0xF;
        if (nibble < 10) buf[i] = u'0' + nibble;
        else buf[i] = u'A' + (nibble - 10);
        val >>= 4;
    }
    Print(buf);
}

void LoadKernel(void) {
    ClearScreen(EFI_BACKGROUND_BLACK);
    if (gVerbose) Print(u"Locating Simple File System...\r\n");

    EFI_GUID sfsGuid = EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID;
    EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *sfs;
    EFI_STATUS status = gBS->LocateProtocol(&sfsGuid, NULL, (void**)&sfs);
    if (EFI_ERROR(status)) { Print(u"Failed to locate file system.\r\n"); while(1); }

    EFI_FILE_PROTOCOL *root;
    status = sfs->OpenVolume(sfs, &root);
    if (EFI_ERROR(status)) { Print(u"Failed to open root volume.\r\n"); while(1); }

    EFI_FILE_PROTOCOL *kernelFile;
    status = root->Open(root, &kernelFile, u"kernel.elf", EFI_FILE_MODE_READ, 0);
    if (EFI_ERROR(status)) { Print(u"Failed to open kernel.elf.\r\n"); while(1); }

    Elf64_Ehdr header;
    UINTN headerSize = sizeof(Elf64_Ehdr);
    status = kernelFile->Read(kernelFile, &headerSize, &header);

    if (memcmpEfi(header.e_ident, "\x7f""ELF", 4) != 0) {
        Print(u"Not a valid ELF file.\r\n"); while(1);
    }

    if (gVerbose) Print(u"Loading kernel segments...\r\n");

    Elf64_Phdr *phdrs;
    UINTN phdrsSize = header.e_phnum * header.e_phentsize;
    gBS->AllocatePool(2, phdrsSize, (void**)&phdrs);

    kernelFile->SetPosition(kernelFile, header.e_phoff);
    kernelFile->Read(kernelFile, &phdrsSize, phdrs);

    uint64_t minAddr = ~0ULL;
    uint64_t maxAddr = 0;
    for (int i = 0; i < header.e_phnum; i++) {
        if (phdrs[i].p_type == PT_LOAD) {
            if (phdrs[i].p_vaddr < minAddr) minAddr = phdrs[i].p_vaddr;
            if (phdrs[i].p_vaddr + phdrs[i].p_memsz > maxAddr) maxAddr = phdrs[i].p_vaddr + phdrs[i].p_memsz;
        }
    }

    UINTN totalPages = (maxAddr - minAddr + 0xFFF) / 0x1000;
    uint64_t baseAddr = 0;
    status = gBS->AllocatePages(0, 1, totalPages, &baseAddr);
    if (EFI_ERROR(status)) {
        Print(u"Failed to allocate memory for kernel!\r\n");
        while(1);
    }

    for (int i = 0; i < header.e_phnum; i++) {
        if (phdrs[i].p_type == PT_LOAD) {
            status = kernelFile->SetPosition(kernelFile, phdrs[i].p_offset);
            if (EFI_ERROR(status)) { Print(u"SetPosition Failed!\r\n"); while(1); }
            UINTN size = phdrs[i].p_filesz;
            uint64_t dest = baseAddr + (phdrs[i].p_vaddr - minAddr);
            status = kernelFile->Read(kernelFile, &size, (void*)dest);
            if (EFI_ERROR(status)) { Print(u"Read Failed!\r\n"); while(1); }

            uint8_t *bss = (uint8_t*)(dest + size);
            for (UINTN j = 0; j < phdrs[i].p_memsz - size; j++) bss[j] = 0;
        }
    }

    uint64_t kernelEntry = baseAddr + (header.e_entry - minAddr);

    if (gVerbose) Print(u"Building BootInfo...\r\n");

    BootInfo *bootInfo;
    status = gBS->AllocatePool(2, sizeof(BootInfo), (void**)&bootInfo);
    if (EFI_ERROR(status)) { Print(u"AllocatePool Failed!\r\n"); while(1); }

    uint8_t* binfoPtr = (uint8_t*)bootInfo;
    for (UINTN i = 0; i < sizeof(BootInfo); i++) binfoPtr[i] = 0;

    if (gGOP && gGOP->Mode) {
        bootInfo->Framebuffer.BaseAddress = (uint32_t*)gGOP->Mode->FrameBufferBase;
        bootInfo->Framebuffer.BufferSize = gGOP->Mode->FrameBufferSize;
        bootInfo->Framebuffer.Width = gGOP->Mode->Info->HorizontalResolution;
        bootInfo->Framebuffer.Height = gGOP->Mode->Info->VerticalResolution;
        bootInfo->Framebuffer.PixelsPerScanLine = gGOP->Mode->Info->PixelsPerScanLine;

        status = gBS->AllocatePool(2, bootInfo->Framebuffer.BufferSize, (void**)&bootInfo->Framebuffer.BackBuffer);
        if (EFI_ERROR(status)) { Print(u"BackBuffer Allocation Failed!\r\n"); while(1); }
    }

    bootInfo->RSDP = NULL;
    EFI_GUID acpi20 = { 0x8868e871, 0xe4f1, 0x11d3, { 0xbc, 0x22, 0x00, 0x80, 0xc7, 0x3c, 0x88, 0x81 } };
    for (UINTN i = 0; i < gST->NumberOfTableEntries; i++) {
        if (memcmpEfi(&gST->ConfigurationTable[i].VendorGuid, &acpi20, sizeof(EFI_GUID)) == 0) {
            bootInfo->RSDP = gST->ConfigurationTable[i].VendorTable;
            break;
        }
    }

    if (gVerbose) {
        Print(u"Kernel Entry: ");
        PrintHex(kernelEntry);
        Print(u"  |  Framebuffer Base: ");
        PrintHex((uint64_t)bootInfo->Framebuffer.BaseAddress);
        Print(u"\r\nExiting Boot Services...\r\n");
        gBS->Stall(5000000);
    }

    UINTN mapSize = 0, mapKey, descSize;
    uint32_t descVersion;
    void *mmap = NULL;
    gBS->GetMemoryMap(&mapSize, NULL, &mapKey, &descSize, &descVersion);
    mapSize += 4096; // Safe padding instead of relying on descSize
    status = gBS->AllocatePool(2, mapSize, &mmap);
    if (EFI_ERROR(status)) { Print(u"MemMap Alloc Fail!\r\n"); while(1); }
    gBS->GetMemoryMap(&mapSize, mmap, &mapKey, &descSize, &descVersion);

    status = gBS->ExitBootServices(gImageHandle, mapKey);
    if (EFI_ERROR(status)) {
        gBS->GetMemoryMap(&mapSize, mmap, &mapKey, &descSize, &descVersion);
        status = gBS->ExitBootServices(gImageHandle, mapKey);
    }

    bootInfo->MemoryMap = mmap;
    bootInfo->MemoryMapSize = mapSize;
    bootInfo->MemoryMapDescriptorSize = descSize;

    uint32_t *fb = (uint32_t *)bootInfo->Framebuffer.BaseAddress;
    for (int i = 0; i < 50000; i++) fb[i] = 0x000000FF;

    void __attribute__((sysv_abi)) (*kernel_main)(BootInfo*) = (void __attribute__((sysv_abi)) (*)(BootInfo*))kernelEntry;
    kernel_main(bootInfo);

    while(1);
}

