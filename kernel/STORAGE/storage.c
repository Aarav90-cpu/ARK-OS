#include "../SHARED/klog.h"
#include "../SHARED/subsystems.h"

void Storage_Init(BootInfo *binfo) {
    (void)binfo;
    SystemLog("IN PROGRESS", "Scanning for HDD/SSD/NVMe Controllers...");

    SystemLog("FAIL", "No valid boot drive filesystem found!");
}

