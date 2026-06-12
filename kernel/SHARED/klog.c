#include "klog.h"

extern void DrawChar(BootInfo *bootInfo, char c, int cx, int cy, uint32_t color);
extern void PrintString(BootInfo *bootInfo, const char *str, int x, int y, uint32_t color);

static BootInfo *gBootInfo = 0;
static int gCursorY = 0;
static int gCursorX = -380;
static char failBuffer[4096];
static int failLen = 0;

void KLog_Init(BootInfo *binfo) {
    gBootInfo = binfo;
    gCursorY = 30;
    gCursorX = 20;
}

static uint8_t GetUpdateInProgressFlag() {
    outb(0x70, 0x0A);
    return (inb(0x71) & 0x80);
}

static uint8_t GetRTCRegister(int reg) {
    outb(0x70, reg);
    return inb(0x71);
}

static void IntToStr(int num, char *str, int *idx, int padZeroes) {
    int digits = 0;
    int temp = num;
    do { digits++; temp /= 10; } while(temp);

    if (padZeroes && digits < 2) {
        str[(*idx)++] = '0';
    }

    int start = *idx;
    (*idx) += digits;
    str[*idx] = 0;

    for (int i = *idx - 1; i >= start; i--) {
        str[i] = '0' + (num % 10);
        num /= 10;
    }
}

static void AppendString(char *dest, int *idx, const char *src) {
    while (*src) {
        dest[(*idx)++] = *src++;
    }
    dest[*idx] = '\0';
}

void SystemLog(const char *status, const char *job) {
    if (!gBootInfo) return;

    uint8_t second = GetRTCRegister(0x00);
    uint8_t minute = GetRTCRegister(0x02);
    uint8_t hour   = GetRTCRegister(0x04);
    uint8_t day    = GetRTCRegister(0x07);
    uint8_t month  = GetRTCRegister(0x08);
    uint8_t year   = GetRTCRegister(0x09);

    second = (second & 0x0F) + ((second / 16) * 10);
    minute = (minute & 0x0F) + ((minute / 16) * 10);
    hour = ( (hour & 0x0F) + (((hour & 0x70) / 16) * 10) ) | (hour & 0x80);
    day = (day & 0x0F) + ((day / 16) * 10);
    month = (month & 0x0F) + ((month / 16) * 10);
    year = (year & 0x0F) + ((year / 16) * 10);

    char logStr[128];
    int idx = 0;

    AppendString(logStr, &idx, "20");
    IntToStr(year, logStr, &idx, 1);
    AppendString(logStr, &idx, "/");
    IntToStr(month, logStr, &idx, 1);
    AppendString(logStr, &idx, "/");
    IntToStr(day, logStr, &idx, 1);
    AppendString(logStr, &idx, " ");
    IntToStr(hour, logStr, &idx, 1);
    AppendString(logStr, &idx, ":");
    IntToStr(minute, logStr, &idx, 1);
    AppendString(logStr, &idx, ":");
    IntToStr(second, logStr, &idx, 1);

    AppendString(logStr, &idx, " [");
    AppendString(logStr, &idx, status);
    AppendString(logStr, &idx, "] ");
    AppendString(logStr, &idx, job);

    uint32_t color = 0x00FFFFFF;
    if (status[0] == 'P') color = 0x0000FF00;
    if (status[0] == 'F') color = 0x00FF0000;
    if (status[0] == 'I') color = 0x00FFFF00;

    PrintString(gBootInfo, logStr, gCursorX, gCursorY, color);

    uint64_t *dst = (uint64_t *)gBootInfo->Framebuffer.BaseAddress;
    uint64_t *src = (uint64_t *)gBootInfo->Framebuffer.BackBuffer;
    for (uint32_t i = 0; i < gBootInfo->Framebuffer.BufferSize / 8; i++) {
        dst[i] = src[i];
    }

    gCursorY += 40;

    if (status[0] == 'F') {
        AppendString(failBuffer, &failLen, logStr);
        AppendString(failBuffer, &failLen, "\n");
    }
}

