#include "SHARED/bootinfo.h"
#include "SHARED/klog.h"
#include "SHARED/subsystems.h"
#include "STORAGE/RAM/paging.h"

void kernel_main(BootInfo *bootInfo) {
    __asm__ volatile("cli");
    if (!bootInfo) while(1);

    // Clear screen directly to black
    uint32_t *fbBase = bootInfo->Framebuffer.BaseAddress;
    uint32_t width = bootInfo->Framebuffer.Width;
    uint32_t height = bootInfo->Framebuffer.Height;
    uint32_t ppl = bootInfo->Framebuffer.PixelsPerScanLine;

    for (uint32_t y = 0; y < height; y++) {
        for (uint32_t x = 0; x < width; x++) {
            fbBase[y * ppl + x] = 0x00000000;
        }
    }

    KLog_Init(bootInfo);
    
    printf("========================================\n");
    printf("         ARK OS Kernel Loaded           \n");
    printf("========================================\n\n");
    
    printf("[INFO] Framebuffer initialized at %p\n", fbBase);
    printf("[INFO] Resolution: %dx%d\n", width, height);

    UEFI_Init(bootInfo);
    RAM_Init(bootInfo);
    Paging_Init(bootInfo);
    CPU_Init(bootInfo);
    Timers_Init(bootInfo);
    Motherboard_Init(bootInfo);
    Cooling_Init(bootInfo);
    Storage_Init(bootInfo);

    printf("\n[SUCCESS] Initialization complete. Handing over to user space...\n");

    while (1) {
        __asm__ volatile("hlt");
    }
}

