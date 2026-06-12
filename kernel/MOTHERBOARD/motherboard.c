#include "../SHARED/klog.h"
#include "../SHARED/subsystems.h"
#include <stdbool.h>
#include <stddef.h>

typedef struct {
    char Signature[8];
    uint8_t Checksum;
    char OEMID[6];
    uint8_t Revision;
    uint32_t RsdtAddress;
} __attribute__((packed)) RSDPDescriptor;

typedef struct {
    RSDPDescriptor firstPart;
    uint32_t Length;
    uint64_t XsdtAddress;
    uint8_t ExtendedChecksum;
    uint8_t reserved[3];
} __attribute__((packed)) RSDPDescriptor20;

typedef struct {
    char Signature[4];
    uint32_t Length;
    uint8_t Revision;
    uint8_t Checksum;
    char OEMID[6];
    char OEMTableID[8];
    uint32_t OEMRevision;
    uint32_t CreatorID;
    uint32_t CreatorRevision;
} __attribute__((packed)) ACPISDTHeader;

void Motherboard_Init(BootInfo *binfo) {
    SystemLog("IN PROGRESS", "Parsing ACPI Tables & Finding PCI Bus...");
    if (!binfo->RSDP) {
        SystemLog("FAIL", "No ACPI RSDP found from UEFI!");
        return;
    }

    RSDPDescriptor* rsdp = (RSDPDescriptor*)binfo->RSDP;

    char* sig = rsdp->Signature;
    if (!(sig[0]=='R' && sig[1]=='S' && sig[2]=='D' && sig[3]==' ' &&
          sig[4]=='P' && sig[5]=='T' && sig[6]=='R' && sig[7]==' ')) {
        SystemLog("FAIL", "Invalid ACPI RSDP Signature!");
        return;
    }

    if (rsdp->Revision < 2) {
        SystemLog("FAIL", "ACPI 1.0 (RSDT) is not supported. Use ACPI 2.0+ (XSDT).");
        return;
    }

    RSDPDescriptor20* rsdp20 = (RSDPDescriptor20*)rsdp;
    ACPISDTHeader* xsdt = (ACPISDTHeader*)rsdp20->XsdtAddress;

    if (!xsdt) {
        SystemLog("FAIL", "XSDT Address is NULL!");
        return;
    }

    if (xsdt->Signature[0] != 'X' || xsdt->Signature[1] != 'S' || xsdt->Signature[2] != 'D' || xsdt->Signature[3] != 'T') {
        SystemLog("FAIL", "Invalid XSDT Signature!");
        return;
    }

    int entries = (xsdt->Length - sizeof(ACPISDTHeader)) / 8;
    uint64_t* otherTables = (uint64_t*)((uint8_t*)xsdt + sizeof(ACPISDTHeader));

    bool foundMCFG = false;
    for (int i = 0; i < entries; i++) {
        ACPISDTHeader* h = (ACPISDTHeader*)otherTables[i];
        if (h->Signature[0] == 'M' && h->Signature[1] == 'C' && h->Signature[2] == 'F' && h->Signature[3] == 'G') {
            foundMCFG = true;
            break;
        }
    }

    if (foundMCFG) {
        SystemLog("PASS", "ACPI XSDT Parsed. PCI Express (MCFG) Found!");
    } else {
        SystemLog("PASS", "ACPI XSDT Parsed, but no MCFG found.");
    }
}

