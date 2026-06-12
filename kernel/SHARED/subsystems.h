#ifndef SUBSYSTEMS_H
#define SUBSYSTEMS_H

#include "bootinfo.h"

void UEFI_Init(BootInfo *binfo);
void RAM_Init(BootInfo *binfo);
void CPU_Init(BootInfo *binfo);
void Timers_Init(BootInfo *binfo);
void Motherboard_Init(BootInfo *binfo);
void Cooling_Init(BootInfo *binfo);
void Storage_Init(BootInfo *binfo);

#endif

