#include "../../SHARED/klog.h"
#include "../../SHARED/subsystems.h"

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

void CPU_Identify() {
    char vendor[13];
    CPUID_Vendor(vendor);
    SystemLog("PASS", vendor);
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
        "mov $0x08, %%rcx\n"
        "pushq %%rcx\n"
        "leaq 1f(%%rip), %%rax\n"
        "pushq %%rax\n"
        "lretq\n"
        "1:\n"
        "mov $0x10, %%ax\n"
        "mov %%ax, %%ds\n"
        "mov %%ax, %%es\n"
        "mov %%ax, %%fs\n"
        "mov %%ax, %%gs\n"
        "mov %%ax, %%ss\n"
        : : "m"(gdtr) : "rax", "rcx", "memory"
    );

    SystemLog("PASS", "GDT Loaded & Segments Reloaded. Ring 0 Executable.");
    CPU_Identify();
}
