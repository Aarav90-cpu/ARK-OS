#include "klog.h"
#include "font.h"

static BootInfo *gBootInfo = 0;
static int gCursorY = 0;
static int gCursorX = 0;
static uint32_t gColor = 0x00FFFFFF; // Default white

void KLog_Init(BootInfo *binfo) {
    gBootInfo = binfo;
    gCursorX = 0;
    gCursorY = 0;
}

static void PutPixel(int x, int y, uint32_t color) {
    if (!gBootInfo) return;
    uint32_t *fb = (uint32_t *)gBootInfo->Framebuffer.BaseAddress;
    uint32_t width = gBootInfo->Framebuffer.Width;
    uint32_t height = gBootInfo->Framebuffer.Height;
    uint32_t ppl = gBootInfo->Framebuffer.PixelsPerScanLine;

    if (x >= 0 && x < (int)width && y >= 0 && y < (int)height) {
        fb[y * ppl + x] = color;
    }
}

void scroll_screen(void) {
    if (!gBootInfo) return;
    uint32_t *fb = (uint32_t *)gBootInfo->Framebuffer.BaseAddress;
    uint32_t width = gBootInfo->Framebuffer.Width;
    uint32_t height = gBootInfo->Framebuffer.Height;
    uint32_t ppl = gBootInfo->Framebuffer.PixelsPerScanLine;
    
    // Scroll up by 16 pixels
    for (uint32_t y = 16; y < height; y++) {
        for (uint32_t x = 0; x < width; x++) {
            fb[(y - 16) * ppl + x] = fb[y * ppl + x];
        }
    }
    
    // Clear the bottom 16 pixels
    for (uint32_t y = height - 16; y < height; y++) {
        for (uint32_t x = 0; x < width; x++) {
            fb[y * ppl + x] = 0x00000000;
        }
    }
    
    gCursorY -= 16;
}

void putchar(char c) {
    if (!gBootInfo) return;
    
    if (c == '\n') {
        gCursorX = 0;
        gCursorY += 16;
    } else if (c == '\r') {
        gCursorX = 0;
    } else {
        uint8_t *glyph = (uint8_t *)font8x8_basic[(uint8_t)c];
        for (int y = 0; y < 8; y++) {
            for (int x = 0; x < 8; x++) {
                if (glyph[y] & (1 << x)) {
                    // Scale 8x8 font by 2x for better readability
                    PutPixel(gCursorX + x*2, gCursorY + y*2, gColor);
                    PutPixel(gCursorX + x*2 + 1, gCursorY + y*2, gColor);
                    PutPixel(gCursorX + x*2, gCursorY + y*2 + 1, gColor);
                    PutPixel(gCursorX + x*2 + 1, gCursorY + y*2 + 1, gColor);
                }
            }
        }
        gCursorX += 16;
    }

    uint32_t width = gBootInfo->Framebuffer.Width;
    if (gCursorX >= (int)width) {
        gCursorX = 0;
        gCursorY += 16;
    }
    
    uint32_t height = gBootInfo->Framebuffer.Height;
    if (gCursorY + 16 > (int)height) {
        scroll_screen();
    }
}

static void print_string(const char *str) {
    while (*str) {
        putchar(*str++);
    }
}

static void print_hex(uint64_t num) {
    char buf[20];
    int idx = 19;
    buf[idx--] = 0;
    if (num == 0) {
        buf[idx--] = '0';
    } else {
        const char *hex_chars = "0123456789ABCDEF";
        while (num > 0 && idx >= 0) {
            buf[idx--] = hex_chars[num & 0xF];
            num >>= 4;
        }
    }
    buf[idx--] = 'x';
    buf[idx] = '0';
    print_string(&buf[idx]);
}

static void print_dec(int64_t num) {
    char buf[24];
    int idx = 23;
    buf[idx--] = 0;
    
    int is_negative = 0;
    if (num < 0) {
        is_negative = 1;
        num = -num;
    }
    
    if (num == 0) {
        buf[idx--] = '0';
    } else {
        while (num > 0 && idx >= 0) {
            buf[idx--] = '0' + (num % 10);
            num /= 10;
        }
    }
    
    if (is_negative && idx >= 0) {
        buf[idx--] = '-';
    }
    
    print_string(&buf[idx + 1]);
}

void printf(const char *format, ...) {
    va_list args;
    va_start(args, format);

    while (*format) {
        if (*format == '%') {
            format++;
            switch (*format) {
                case 's': {
                    const char *str = va_arg(args, const char *);
                    if (!str) str = "(null)";
                    print_string(str);
                    break;
                }
                case 'c': {
                    char c = (char)va_arg(args, int);
                    putchar(c);
                    break;
                }
                case 'd': {
                    int num = va_arg(args, int);
                    print_dec(num);
                    break;
                }
                case 'x': {
                    uint32_t num = va_arg(args, uint32_t);
                    print_hex(num);
                    break;
                }
                case 'p':
                case 'X': {
                    uint64_t num = va_arg(args, uint64_t);
                    print_hex(num);
                    break;
                }
                case '%': {
                    putchar('%');
                    break;
                }
                default:
                    putchar('%');
                    putchar(*format);
                    break;
            }
        } else {
            putchar(*format);
        }
        format++;
    }

    va_end(args);
}

void SystemLog(const char *status, const char *job) {
    if (!gBootInfo) return;

    // Use default color unless it's a specific status
    uint32_t oldColor = gColor;
    if (status[0] == 'P') gColor = 0x0000FF00;
    if (status[0] == 'F') gColor = 0x00FF0000;
    if (status[0] == 'I') gColor = 0x00FFFF00;

    printf("[%s] %s\n", status, job);

    gColor = oldColor;
}

