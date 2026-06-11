#include "esc.h"
#include "../../../efi.h"
#include "../../../OUTPUT/DISPLAY/display.h"

bool WaitForEscape(void) {
    if (!gST || !gBS || !gST->ConIn || !gST->ConOut) return false;

    // Flush any pending keys
    gST->ConIn->Reset(gST->ConIn, false);
    
    // Create a 1-second timer event
    void* timerEvent;
    gBS->CreateEvent(EVT_TIMER, TPL_CALLBACK, NULL, NULL, &timerEvent);

    bool escPressed = false;

    for (int seconds = 3; seconds > 0; seconds--) {
        // Set timer for 1 second (10,000,000 * 100ns = 1 second)
        gBS->SetTimer(timerEvent, TimerRelative, 10000000);

        void* waitList[2] = { gST->ConIn->WaitForKey, timerEvent };
        UINTN index;
        EFI_STATUS status = gBS->WaitForEvent(2, waitList, &index);

        if (!EFI_ERROR(status)) {
            if (index == 0) {
                // Key pressed
                EFI_INPUT_KEY key;
                status = gST->ConIn->ReadKeyStroke(gST->ConIn, &key);
                if (!EFI_ERROR(status) && key.ScanCode == SCAN_ESC) {
                    escPressed = true;
                    break;
                }
            } else if (index == 1) {
                // Timer expired (1 second passed)
                continue;
            }
        }
    }

    gBS->CloseEvent(timerEvent);
    return escPressed;
}
