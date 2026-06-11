#pragma once
#include "efi.h"

// Initialize Graphics Output Protocol
EFI_STATUS InitDisplay(void);

// Print a string to the screen
void Print(const uint16_t* str);

// Clear the screen with a specific background color
void ClearScreen(uint8_t bgColor);

// Load and display a 24-bit uncompressed BMP image centered on the screen
// Assumes the image is loaded into memory at 'bmpBuffer'
EFI_STATUS DrawBmpCentered(void* bmpBuffer, UINTN bufferSize);

extern EFI_GRAPHICS_OUTPUT_PROTOCOL *gGOP;
