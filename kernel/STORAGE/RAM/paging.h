#ifndef PAGING_H
#define PAGING_H

#include <stdint.h>
#include <stddef.h>
#include "../../SHARED/bootinfo.h"

#define PAGE_SIZE 4096

// Page Table Entry Flags
#define PT_FLAG_PRESENT      (1 << 0)
#define PT_FLAG_READ_WRITE   (1 << 1)
#define PT_FLAG_USER_SUPER   (1 << 2)
#define PT_FLAG_WRITE_THROUGH (1 << 3)
#define PT_FLAG_CACHE_DISABLE (1 << 4)
#define PT_FLAG_ACCESSED     (1 << 5)
#define PT_FLAG_DIRTY        (1 << 6)
#define PT_FLAG_HUGE_PAGE    (1 << 7)
#define PT_FLAG_GLOBAL       (1 << 8)

typedef uint64_t PT_Entry;

// A Page Table contains 512 entries
typedef struct {
    PT_Entry entries[512];
} __attribute__((aligned(PAGE_SIZE))) PageTable;

// Function declarations
void Paging_Init(BootInfo *binfo);
void MapPage(void* physicalMemory, void* virtualMemory, uint64_t flags);

#endif
