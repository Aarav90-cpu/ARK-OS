#include "../../SHARED/klog.h"
#include "../../SHARED/subsystems.h"
#include "idt.h"

struct GDTEntry {
    uint16_t LimitLow;
    uint16_t BaseLow;
    uint8_t BaseMiddle;
    uint8_t AccessByte;
    uint8_t Granularity;
    uint8_t BaseHigh;
} __attribute__((packed));

struct GDTDescriptor {
    uint16_t Size;
    uint64_t Offset;
} __attribute__((packed));

struct GDTEntry gdt[3];
struct GDTDescriptor gdtr;

static void CPUID_Vendor(char *vendorStr) {
    uint32_t eax, ebx, ecx, edx;
    eax = 0;
    __asm__ volatile("cpuid" : "=a"(eax), "=b"(ebx), "=c"(ecx), "=d"(edx) : "0"(eax));
    ((uint32_t *)vendorStr)[0] = ebx;
    ((uint32_t *)vendorStr)[1] = edx;
    ((uint32_t *)vendorStr)[2] = ecx;
    vendorStr[12] = '\0';
}

static void CPUID_Brand(char *brandStr) {
    uint32_t eax, ebx, ecx, edx;
    
    // Check if extended CPUID leaves are supported
    __asm__ volatile("cpuid" : "=a"(eax), "=b"(ebx), "=c"(ecx), "=d"(edx) : "0"(0x80000000));
    if (eax < 0x80000004) {
        brandStr[0] = '\0';
        return;
    }

    uint32_t *ptr = (uint32_t *)brandStr;
    for (uint32_t i = 0; i < 3; i++) {
        __asm__ volatile("cpuid" : "=a"(eax), "=b"(ebx), "=c"(ecx), "=d"(edx) : "0"(0x80000002 + i));
        *ptr++ = eax;
        *ptr++ = ebx;
        *ptr++ = ecx;
        *ptr++ = edx;
    }
    brandStr[48] = '\0';
}

void CPU_Identify() {
    char vendor[13];
    CPUID_Vendor(vendor);
    SystemLog("PASS", vendor);

    char brand[49];
    CPUID_Brand(brand);
    if (brand[0] != '\0') {
        printf("[INFO] CPU Model: %s\n", brand);
    }

    uint32_t eax, ebx, ecx, edx;
    // Check for Hybrid Architecture (Leaf 7, Subleaf 0)
    __asm__ volatile("cpuid" : "=a"(eax), "=b"(ebx), "=c"(ecx), "=d"(edx) : "a"(7), "c"(0));
    int is_hybrid = (edx & (1 << 15)) != 0;
    
    if (is_hybrid) {
        printf("[INFO] Intel Hybrid Architecture Detected (Thread Director Supported)\n");
        // Check Core Type (Leaf 0x1A, Subleaf 0)
        __asm__ volatile("cpuid" : "=a"(eax), "=b"(ebx), "=c"(ecx), "=d"(edx) : "a"(0x1A), "c"(0));
        uint8_t core_type = (eax >> 24) & 0xFF;
        if (core_type == 0x20) {
            printf("[INFO] Current Bootstrap Core: E-Core (Gracemont/Efficient)\n");
        } else if (core_type == 0x40) {
            printf("[INFO] Current Bootstrap Core: P-Core (Raptor Cove/Performance)\n");
        } else {
            printf("[INFO] Current Bootstrap Core: Unknown Hybrid Type (0x%X)\n", core_type);
        }
    } else {
        printf("[INFO] Symmetric Architecture (No Hybrid Topology)\n");
    }
}

void CPU_Init(BootInfo *binfo) {
    (void)binfo;
    SystemLog("IN PROGRESS", "Initializing CPU Cores & GDT...");

    gdt[0].LimitLow = 0; gdt[0].BaseLow = 0; gdt[0].BaseMiddle = 0;
    gdt[0].AccessByte = 0; gdt[0].Granularity = 0; gdt[0].BaseHigh = 0;

    gdt[1].LimitLow = 0xFFFF; gdt[1].BaseLow = 0; gdt[1].BaseMiddle = 0;
    gdt[1].AccessByte = 0x9A; gdt[1].Granularity = 0xAF; gdt[1].BaseHigh = 0;

    gdt[2].LimitLow = 0xFFFF; gdt[2].BaseLow = 0; gdt[2].BaseMiddle = 0;
    gdt[2].AccessByte = 0x92; gdt[2].Granularity = 0xAF; gdt[2].BaseHigh = 0;

    gdtr.Size = sizeof(gdt) - 1;
    gdtr.Offset = (uint64_t)&gdt[0];

    __asm__ volatile(
        "lgdt %0\n"
        "mov $0x10, %%ax\n"
        "mov %%ax, %%ds\n"
        "mov %%ax, %%es\n"
        "mov %%ax, %%fs\n"
        "mov %%ax, %%gs\n"
        "mov %%ax, %%ss\n"
        "pushq $0x08\n"
        "leaq 1f(%%rip), %%rax\n"
        "pushq %%rax\n"
        "lretq\n"
        "1:\n"
        : : "m"(gdtr) : "rax", "memory"
    );

    SystemLog("PASS", "GDT Loaded & Segments Reloaded. Ring 0 Executable.");
    
    // Initialize the IDT
    IDT_Init();

    CPU_Identify();
}
