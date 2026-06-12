#include "paging.h"
#include "../../SHARED/klog.h"

extern void* PMM_AllocPage(void);

PageTable *kernel_pml4;

// Flush CR3 to load the new PML4
static inline void LoadPML4(PageTable *pml4) {
    __asm__ volatile("mov %0, %%cr3" : : "r"((uint64_t)pml4));
}

// Simple memset for 4KB pages
static void ZeroPage(void *page) {
    uint64_t *p = (uint64_t*)page;
    for (int i = 0; i < 512; i++) {
        p[i] = 0;
    }
}

void Paging_Init(BootInfo *binfo) {
    (void)binfo; // Used for KLog, but we can access it via global
    SystemLog("IN PROGRESS", "Initializing Virtual Memory Manager (Paging)...");

    kernel_pml4 = (PageTable*)PMM_AllocPage();
    if (!kernel_pml4) {
        SystemLog("FAIL", "Could not allocate PML4!");
        return;
    }
    ZeroPage(kernel_pml4);

    PageTable *pdpt = (PageTable*)PMM_AllocPage();
    if (!pdpt) {
        SystemLog("FAIL", "Could not allocate PDPT!");
        return;
    }
    ZeroPage(pdpt);

    // Map the first 64GB of memory using 2MB Huge Pages.
    // 64GB requires 64 Page Directories (PD).
    // 1 PDPT can hold 512 PDs, so 64 easily fits in the first PDPT.

    // 1. Link PML4 entry 0 to our PDPT
    kernel_pml4->entries[0] = ((uint64_t)pdpt) | PT_FLAG_PRESENT | PT_FLAG_READ_WRITE;

    uint64_t phys_addr = 0;

    // 2. Allocate 64 PDs and link them to the PDPT
    for (int i = 0; i < 64; i++) {
        PageTable *pd = (PageTable*)PMM_AllocPage();
        ZeroPage(pd);

        pdpt->entries[i] = ((uint64_t)pd) | PT_FLAG_PRESENT | PT_FLAG_READ_WRITE;

        // 3. Fill the PD with 512 entries of 2MB each
        for (int j = 0; j < 512; j++) {
            pd->entries[j] = phys_addr | PT_FLAG_PRESENT | PT_FLAG_READ_WRITE | PT_FLAG_HUGE_PAGE;
            phys_addr += (2 * 1024 * 1024); // Increment by 2MB
        }
    }

    SystemLog("PASS", "Mapped first 64GB of RAM (Identity Map, 2MB Pages).");
    SystemLog("IN PROGRESS", "Swapping CR3 to new PML4...");

    LoadPML4(kernel_pml4);

    SystemLog("PASS", "CR3 Swapped Successfully! We are running on custom Page Tables.");
}
