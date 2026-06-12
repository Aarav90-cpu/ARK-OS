#include "../../SHARED/klog.h"
#include "../../SHARED/subsystems.h"
#include <stdbool.h>
#include <stddef.h>

typedef struct {
    uint32_t Type;
    uint32_t Pad;
    uint64_t PhysicalStart;
    uint64_t VirtualStart;
    uint64_t NumberOfPages;
    uint64_t Attribute;
} EFI_MEMORY_DESCRIPTOR;

#define EFI_CONVENTIONAL_MEMORY 7

uint8_t* gMemoryBitmap = 0;
uint64_t gTotalPages = 0;
uint64_t gFreePages = 0;
uint64_t gBitmapSize = 0;

static void BitmapSet(uint64_t index) {
    gMemoryBitmap[index / 8] |= (1 << (index % 8));
}

static void BitmapClear(uint64_t index) {
    gMemoryBitmap[index / 8] &= ~(1 << (index % 8));
}

static bool BitmapTest(uint64_t index) {
    return gMemoryBitmap[index / 8] & (1 << (index % 8));
}

void* PMM_AllocPage() {
    for (uint64_t i = 0; i < gTotalPages; i++) {
        if (!BitmapTest(i)) {
            BitmapSet(i);
            gFreePages--;
            return (void*)(i * 4096);
        }
    }
    return NULL;
}

void PMM_FreePage(void* ptr) {
    uint64_t index = (uint64_t)ptr / 4096;
    if (BitmapTest(index)) {
        BitmapClear(index);
        gFreePages++;
    }
}

void RAM_Init(BootInfo *binfo) {
    SystemLog("IN PROGRESS", "Initializing Physical Memory Manager (Bitmap)...");

    if (!binfo->MemoryMap || binfo->MemoryMapDescriptorSize == 0) {
        SystemLog("FAIL", "Invalid Memory Map provided by UEFI!");
        return;
    }

    uint64_t mapEntries = binfo->MemoryMapSize / binfo->MemoryMapDescriptorSize;
    uint64_t maxAddress = 0;

    for (uint64_t i = 0; i < mapEntries; i++) {
        EFI_MEMORY_DESCRIPTOR* desc = (EFI_MEMORY_DESCRIPTOR*)((uint8_t*)binfo->MemoryMap + (i * binfo->MemoryMapDescriptorSize));
        uint64_t top = desc->PhysicalStart + (desc->NumberOfPages * 4096);
        if (top > maxAddress) maxAddress = top;
    }

    gTotalPages = maxAddress / 4096;
    gBitmapSize = gTotalPages / 8;
    if (gBitmapSize == 0) gBitmapSize = 1;

    for (uint64_t i = 0; i < mapEntries; i++) {
        EFI_MEMORY_DESCRIPTOR* desc = (EFI_MEMORY_DESCRIPTOR*)((uint8_t*)binfo->MemoryMap + (i * binfo->MemoryMapDescriptorSize));
        if (desc->Type == EFI_CONVENTIONAL_MEMORY && (desc->NumberOfPages * 4096) >= gBitmapSize) {
            gMemoryBitmap = (uint8_t*)desc->PhysicalStart;
            break;
        }
    }

    if (!gMemoryBitmap) {
        SystemLog("FAIL", "Not enough contiguous RAM to store PMM Bitmap!");
        return;
    }

    for (uint64_t i = 0; i < gBitmapSize; i++) gMemoryBitmap[i] = 0xFF;

    for (uint64_t i = 0; i < mapEntries; i++) {
        EFI_MEMORY_DESCRIPTOR* desc = (EFI_MEMORY_DESCRIPTOR*)((uint8_t*)binfo->MemoryMap + (i * binfo->MemoryMapDescriptorSize));
        if (desc->Type == EFI_CONVENTIONAL_MEMORY) {
            for (uint64_t p = 0; p < desc->NumberOfPages; p++) {
                uint64_t pageIndex = (desc->PhysicalStart / 4096) + p;
                BitmapClear(pageIndex);
                gFreePages++;
            }
        }
    }

    uint64_t bitmapPageCount = (gBitmapSize + 4095) / 4096;
    uint64_t bitmapStartIndex = (uint64_t)gMemoryBitmap / 4096;
    for (uint64_t i = 0; i < bitmapPageCount; i++) {
        BitmapSet(bitmapStartIndex + i);
        gFreePages--;
    }

    SystemLog("PASS", "PMM Initialized. Ready for Page Allocations.");
}

