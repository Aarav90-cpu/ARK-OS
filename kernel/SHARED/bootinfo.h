#pragma once
#include <stdint.h>

typedef struct {
    uint32_t *BaseAddress;
    uint32_t BufferSize;
    uint32_t Width;
    uint32_t Height;
    uint32_t PixelsPerScanLine;
} FramebufferInfo;

typedef struct {
    FramebufferInfo Framebuffer;
    void* RSDP; // Pointer to ACPI RSDP table
    void* MemoryMap;
    uint64_t MemoryMapSize;
    uint64_t MemoryMapDescriptorSize;
} BootInfo;
