#include "../SHARED/subsystems.h"
#include "acpi.h"

void Motherboard_Init(BootInfo *binfo) {
    ACPI_Init(binfo->RSDP);
}
