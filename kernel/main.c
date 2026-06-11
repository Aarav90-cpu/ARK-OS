#include "SHARED/bootinfo.h"

void kernel_main(BootInfo *bootInfo) {
    if (!bootInfo) while(1);

    volatile uint32_t *fbBase = (volatile uint32_t *)bootInfo->Framebuffer.BaseAddress;
    uint32_t width = bootInfo->Framebuffer.Width;
    uint32_t height = bootInfo->Framebuffer.Height;
    uint32_t ppl = bootInfo->Framebuffer.PixelsPerScanLine;

    for (uint32_t y = 0; y < height; y++) {
        for (uint32_t x = 0; x < width; x++) {
            fbBase[y * ppl + x] = 0x0000FF00;
        }
    }

    while (1) {
        __asm__ __volatile__("cli; hlt");
    }
}
