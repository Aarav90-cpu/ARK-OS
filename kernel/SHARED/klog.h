#ifndef KLOG_H
#define KLOG_H

#include <stdint.h>
#include "bootinfo.h"

void KLog_Init(BootInfo *binfo);

void SystemLog(const char *status, const char *job);

static inline void outb(uint16_t port, uint8_t val) {
    __asm__ volatile ( "outb %0, %1" : : "a"(val), "Nd"(port) );
}

static inline uint8_t inb(uint16_t port) {
    uint8_t ret;
    __asm__ volatile ( "inb %1, %0" : "=a"(ret) : "Nd"(port) );
    return ret;
}

#endif

