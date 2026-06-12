#include "acpi.h"
#include "../SHARED/klog.h"
#include <stddef.h>

uint32_t gLocalApicAddress = 0;
uint32_t gIoApicAddress = 0;

// Helper to compare 4-byte signatures
static int CompareSignature(const char* sig1, const char* sig2) {
    for (int i = 0; i < 4; i++) {
        if (sig1[i] != sig2[i]) return 0;
    }
    return 1;
}

// Function to find the MADT in the XSDT
static MADT* FindMADT(XSDT *xsdt) {
    int entries = (xsdt->Header.Length - sizeof(SDTHeader)) / 8;
    for (int i = 0; i < entries; i++) {
        SDTHeader *header = (SDTHeader*)xsdt->PointerToOtherSDT[i];
        if (CompareSignature(header->Signature, "APIC")) return (MADT*)header;
    }
    return NULL;
}

static FADT* FindFADT(XSDT *xsdt) {
    int entries = (xsdt->Header.Length - sizeof(SDTHeader)) / 8;
    for (int i = 0; i < entries; i++) {
        SDTHeader *header = (SDTHeader*)xsdt->PointerToOtherSDT[i];
        if (CompareSignature(header->Signature, "FACP")) return (FADT*)header;
    }
    return NULL;
}

static MCFG* FindMCFG(XSDT *xsdt) {
    int entries = (xsdt->Header.Length - sizeof(SDTHeader)) / 8;
    for (int i = 0; i < entries; i++) {
        SDTHeader *header = (SDTHeader*)xsdt->PointerToOtherSDT[i];
        if (CompareSignature(header->Signature, "MCFG")) return (MCFG*)header;
    }
    return NULL;
}

void ACPI_Init(void* rsdp_addr) {
    SystemLog("IN PROGRESS", "Parsing ACPI Tables & Finding CPU Cores...");

    if (!rsdp_addr) {
        SystemLog("FAIL", "RSDP pointer is NULL! ACPI not supported.");
        return;
    }

    RSDPDescriptor20 *rsdp = (RSDPDescriptor20*)rsdp_addr;

    // Verify signature "RSD PTR "
    const char *sig = "RSD PTR ";
    for (int i = 0; i < 8; i++) {
        if (rsdp->Signature[i] != sig[i]) {
            SystemLog("FAIL", "Invalid RSDP Signature!");
            return;
        }
    }

    SystemLog("PASS", "ACPI RSDP Validated.");

    if (rsdp->Revision < 2) {
        SystemLog("FAIL", "ACPI 1.0 is not supported (Requires ACPI 2.0+ XSDT).");
        return;
    }

    XSDT *xsdt = (XSDT*)rsdp->XsdtAddress;
    if (!CompareSignature(xsdt->Header.Signature, "XSDT")) {
        SystemLog("FAIL", "Invalid XSDT Signature!");
        return;
    }

    SystemLog("PASS", "ACPI XSDT Parsed.");

    MADT *madt = FindMADT(xsdt);
    if (!madt) {
        SystemLog("FAIL", "MADT (Multiple APIC Description Table) not found!");
        return;
    }

    SystemLog("PASS", "Found MADT.");
    gLocalApicAddress = madt->LocalAPICAddress;
    printf("[INFO] Local APIC Address: 0x%X\n", gLocalApicAddress);

    // Parse MADT to enumerate CPU Cores
    uint8_t *ptr = (uint8_t*)madt + sizeof(MADT);
    uint8_t *end = (uint8_t*)madt + madt->Header.Length;

    int cpu_count = 0;

    while (ptr < end) {
        MADT_RecordHeader *header = (MADT_RecordHeader*)ptr;
        
        // Type 0 is Processor Local APIC
        if (header->Type == 0) {
            MADT_LocalAPIC *lapic = (MADT_LocalAPIC*)ptr;
            if (lapic->Flags & 1) { // If Processor Enabled
                printf("[INFO] Found CPU Core - APIC ID: %d\n", lapic->APICID);
                cpu_count++;
            }
        } else if (header->Type == 1) {
            MADT_IOAPIC *ioapic = (MADT_IOAPIC*)ptr;
            gIoApicAddress = ioapic->IOAPICAddress;
            printf("[INFO] Found IO APIC - ID: %d, Address: 0x%X\n", ioapic->IOAPICID, gIoApicAddress);
        }
        
        ptr += header->Length;
    }

    SystemLog("PASS", "Enumerated CPU Cores from ACPI MADT.");
    printf("[INFO] Total CPU Cores found: %d\n", cpu_count);

    FADT *fadt = FindFADT(xsdt);
    if (fadt) {
        SystemLog("PASS", "Found FADT.");
        printf("[INFO] SMI Command Port: 0x%X\n", fadt->SMI_CommandPort);
        printf("[INFO] PM1a Control Block: 0x%X\n", fadt->PM1aControlBlock);
    } else {
        SystemLog("FAIL", "FADT not found!");
    }

    MCFG *mcfg = FindMCFG(xsdt);
    if (mcfg) {
        SystemLog("PASS", "Found MCFG.");
        MCFG_Allocation *alloc = (MCFG_Allocation*)((uint8_t*)mcfg + sizeof(MCFG));
        printf("[INFO] PCI Express Base Address: 0x%llX\n", alloc->BaseAddress);
    } else {
        SystemLog("FAIL", "MCFG not found! Cannot enumerate PCIe devices.");
    }
}
