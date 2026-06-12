#pragma once
#include "efi.h"

EFI_STATUS InitDisplay(void);

void Print(const uint16_t* str);

void ClearScreen(uint8_t bgColor);

EFI_STATUS DrawBmpCentered(void* bmpBuffer, UINTN bufferSize);

extern EFI_GRAPHICS_OUTPUT_PROTOCOL *gGOP;

