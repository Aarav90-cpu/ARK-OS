#include "SHARED/bootinfo.h"

// Tiny 8x8 font for just the characters we need (H, I, A, M, L, V, E, space)
const uint8_t tiny_font[128][8] = {
    [' '] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    ['H'] = {0x66, 0x66, 0x66, 0x7E, 0x66, 0x66, 0x66, 0x00},
    ['I'] = {0x3C, 0x18, 0x18, 0x18, 0x18, 0x18, 0x3C, 0x00},
    ['A'] = {0x18, 0x3C, 0x66, 0x66, 0x7E, 0x66, 0x66, 0x00},
    ['M'] = {0x63, 0x77, 0x7F, 0x6B, 0x63, 0x63, 0x63, 0x00},
    ['L'] = {0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x3E, 0x00},
    ['V'] = {0x66, 0x66, 0x66, 0x66, 0x66, 0x3C, 0x18, 0x00},
    ['E'] = {0x7E, 0x60, 0x60, 0x78, 0x60, 0x60, 0x7E, 0x00}};

void DrawChar(BootInfo *bootInfo, char c, uint32_t cx, uint32_t cy, uint32_t color) {
    // Draw to BackBuffer instead of BaseAddress
    uint32_t *fb = (uint32_t *)bootInfo->Framebuffer.BackBuffer;
    uint32_t ppl = bootInfo->Framebuffer.PixelsPerScanLine;
    const uint8_t *glyph = tiny_font[(uint8_t)c];
    
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            if (glyph[y] & (1 << (7 - x))) {
                // Scale the 8x8 font up by 4x so it's readable!
                for(int dy=0; dy<4; dy++) {
                    for(int dx=0; dx<4; dx++) {
                        fb[(cy + y*4 + dy) * ppl + (cx + x*4 + dx)] = color;
                    }
                }
            }
        }
    }
}

void PrintString(BootInfo *bootInfo, const char *str, uint32_t x, uint32_t y,
                 uint32_t color) {
  while (*str) {
    DrawChar(bootInfo, *str, x, y, color);
    x += 32; // 8 pixels * 4 scale
    str++;
  }
}

void kernel_main(BootInfo *bootInfo) {
    __asm__ volatile("cli");
    if (!bootInfo) while(1);

    uint32_t *fbBase = bootInfo->Framebuffer.BaseAddress;
    uint32_t *backBuffer = bootInfo->Framebuffer.BackBuffer;
    uint32_t width = bootInfo->Framebuffer.Width;
    uint32_t height = bootInfo->Framebuffer.Height;
    uint32_t ppl = bootInfo->Framebuffer.PixelsPerScanLine;
    uint32_t bufferSize = bootInfo->Framebuffer.BufferSize;

    int y_pos = 50;
    while (1) {
        // 1. Draw Everything to the Back Buffer (Invisible)
        // Clear back buffer to bright white
        for (uint32_t y = 0; y < height; y++) {
            for (uint32_t x = 0; x < width; x++) {
                backBuffer[y * ppl + x] = 0x00FFFFFF;
            }
        }

        // Print it scrolling down!
        PrintString(bootInfo, "HI I AM ALIVE", 50, y_pos, 0x00FF0000); // Red text
        y_pos += 40;
        if (y_pos > (int)height - 40) y_pos = 50;
        
        // 2. Blast Back Buffer to Front Buffer (Visible)
        // A simple memory copy (uint64_t for speed)
        uint64_t *dst = (uint64_t *)fbBase;
        uint64_t *src = (uint64_t *)backBuffer;
        for (uint32_t i = 0; i < bufferSize / 8; i++) {
            dst[i] = src[i];
        }
        
        // Artificial delay
        for (volatile int i = 0; i < 50000000; i++) {
            __asm__ __volatile__("nop");
        }
    }
}
