#include "recovery.h"
#include "../OUTPUT/DISPLAY/display.h"

bool WaitForEscape(void) {
    if (!gST || !gBS || !gST->ConIn) return false;

    // Flush any pending keys
    gST->ConIn->Reset(gST->ConIn, false);

    Print(u"\r\n  Press ESC for Options... (3)\r\n");

    // Wait loop (approx 3 seconds)
    for (int seconds = 3; seconds > 0; seconds--) {
        UINTN index;
        void* waitList[1] = { gST->ConIn->WaitForKey };

        // Wait for 1 second or key press
        EFI_STATUS status = gBS->WaitForEvent(1, waitList, &index);
        if (!EFI_ERROR(status)) {
            EFI_INPUT_KEY key;
            status = gST->ConIn->ReadKeyStroke(gST->ConIn, &key);
            if (!EFI_ERROR(status)) {
                if (key.ScanCode == SCAN_ESC) {
                    return true;
                }
            }
        } else {
            // WaitForEvent might not timeout properly if we only use WaitForKey.
            // So we poll instead using Stall for simplicity and robustness.
        }
        
        // Manual 1-second poll loop (1000 * 1000us)
        for(int m = 0; m < 100; m++) {
            EFI_INPUT_KEY key;
            status = gST->ConIn->ReadKeyStroke(gST->ConIn, &key);
            if (!EFI_ERROR(status) && key.ScanCode == SCAN_ESC) {
                return true;
            }
            gBS->Stall(10000); // 10ms
        }
        
        if (seconds > 1) {
            // A bit hacky to redraw the line, but standard UEFI ConOut supports \r
            Print(u"\r  Press ESC for Options... (2)  ");
            if (seconds == 2) Print(u"\r  Press ESC for Options... (1)  ");
        }
    }
    
    Print(u"\r\n");
    return false;
}
