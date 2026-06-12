#ifndef KLOG_H
#define KLOG_H

#include "bootinfo.h"
#include <stdint.h>
#include <stdarg.h>

void KLog_Init(BootInfo *binfo);
void putchar(char c);
void printf(const char *format, ...);
void scroll_screen(void);
void SystemLog(const char *status, const char *job);

#endif
