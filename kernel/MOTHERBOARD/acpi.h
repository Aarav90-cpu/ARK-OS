#ifndef ACPI_H
#define ACPI_H

#include <stdint.h>
#include "../SHARED/bootinfo.h"

// All ACPI structures must be packed
#pragma pack(push, 1)

typedef struct {
    char Signature[8];
    uint8_t Checksum;
    char OEMID[6];
    uint8_t Revision;
    uint32_t RsdtAddress; // For ACPI 1.0 (32-bit)
    // The following fields are ACPI 2.0+ only
    uint32_t Length;
    uint64_t XsdtAddress; // For ACPI 2.0+ (64-bit)
    uint8_t ExtendedChecksum;
    uint8_t reserved[3];
} RSDPDescriptor20;

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
} SDTHeader;

typedef struct {
    SDTHeader Header;
    uint64_t PointerToOtherSDT[]; // Variable length array
} XSDT;

typedef struct {
    SDTHeader Header;
    uint32_t LocalAPICAddress;
    uint32_t Flags;
    // Followed by variable length records
} MADT;

typedef struct {
    uint8_t Type;
    uint8_t Length;
} MADT_RecordHeader;

// Type 0: Processor Local APIC
typedef struct {
    MADT_RecordHeader Header;
    uint8_t ACPIProcessorID;
    uint8_t APICID;
    uint32_t Flags; // Bit 0 = Processor Enabled
} MADT_LocalAPIC;

// Type 1: IO APIC
typedef struct {
    MADT_RecordHeader Header;
    uint8_t IOAPICID;
    uint8_t reserved;
    uint32_t IOAPICAddress;
    uint32_t GlobalSystemInterruptBase;
} MADT_IOAPIC;

typedef struct {
    SDTHeader Header;
    uint32_t FirmwareCtrl;
    uint32_t Dsdt;
    uint8_t  Reserved;
    uint8_t  PreferredPowerManagementProfile;
    uint16_t SCI_Interrupt;
    uint32_t SMI_CommandPort;
    uint8_t  AcpiEnable;
    uint8_t  AcpiDisable;
    uint8_t  S4BIOS_REQ;
    uint8_t  PSTATE_Control;
    uint32_t PM1aEventBlock;
    uint32_t PM1bEventBlock;
    uint32_t PM1aControlBlock;
    uint32_t PM1bControlBlock;
    // ... ignoring the rest of the FADT for now since we only need basic ports
} FADT;

typedef struct {
    uint64_t BaseAddress;
    uint16_t PCISegmentGroup;
    uint8_t StartBusNumber;
    uint8_t EndBusNumber;
    uint32_t Reserved;
} MCFG_Allocation;

typedef struct {
    SDTHeader Header;
    uint64_t Reserved;
    // Followed by variable length array of allocations
} MCFG;

#pragma pack(pop)

extern uint32_t gLocalApicAddress;
extern uint32_t gIoApicAddress;

void ACPI_Init(void* rsdp_addr);

#endif // ACPI_H
