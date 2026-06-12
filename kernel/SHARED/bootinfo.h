#pragma once
#include <stdint.h>

typedef struct {
    uint32_t *BaseAddress;
    uint32_t *BackBuffer;
    uint32_t BufferSize;
    uint32_t Width;
    uint32_t Height;
    uint32_t PixelsPerScanLine;
} FramebufferInfo;

typedef struct {
    FramebufferInfo Framebuffer;
    void* RSDP;
    void* MemoryMap;
    uint64_t MemoryMapSize;
    uint64_t MemoryMapDescriptorSize;
} BootInfo;

