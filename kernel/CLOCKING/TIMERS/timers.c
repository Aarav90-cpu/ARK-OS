#include "../../SHARED/klog.h"
#include "../../SHARED/subsystems.h"

#include "../../MOTHERBOARD/acpi.h"
#include "../../SHARED/io.h"

// Local APIC Registers
#define LAPIC_ID         0x0020
#define LAPIC_VER        0x0030
#define LAPIC_TPR        0x0080
#define LAPIC_EOI        0x00B0
#define LAPIC_SVR        0x00F0
#define LAPIC_TIMER      0x0320
#define LAPIC_THERMAL    0x0330
#define LAPIC_PERF       0x0340
#define LAPIC_LINT0      0x0350
#define LAPIC_LINT1      0x0360
#define LAPIC_ERROR      0x0370
#define LAPIC_TICR       0x0380
#define LAPIC_TCCR       0x0390
#define LAPIC_TDCR       0x03E0

static inline void apic_write(uint32_t reg, uint32_t val) {
    volatile uint32_t *apic = (volatile uint32_t *)(uint64_t)gLocalApicAddress;
    apic[reg / 4] = val;
}

static inline uint32_t apic_read(uint32_t reg) {
    volatile uint32_t *apic = (volatile uint32_t *)(uint64_t)gLocalApicAddress;
    return apic[reg / 4];
}

void Timers_Init(BootInfo *binfo) {
    (void)binfo;
    SystemLog("IN PROGRESS", "Configuring System Clocks & Interrupts...");

    // 1. Disable the Legacy 8259 PIC
    // We mask all interrupts on the master (0x21) and slave (0xA1) PICs.
    outb(0x21, 0xFF);
    outb(0xA1, 0xFF);
    SystemLog("PASS", "Legacy 8259 PIC Disabled.");

    // 2. Enable Local APIC
    if (gLocalApicAddress) {
        // Set Spurious Interrupt Vector Register to 0x1FF (Vector 255, and Bit 8 sets APIC Enable)
        apic_write(LAPIC_SVR, 0x1FF);
        SystemLog("PASS", "Local APIC Software-Enabled.");
    } else {
        SystemLog("FAIL", "Local APIC Address not found! Cannot enable APIC.");
    }
}

