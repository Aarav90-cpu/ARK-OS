#include "menu.h"
#include "../../../OUTPUT/DISPLAY/display.h"
#include "../../../LOADKERNEL/loadkernel.h"
#include "../../../INPUT/KEYBOARD/INPUT_FUNCTIONKEY/F1/f1.h"
#include "../../../INPUT/KEYBOARD/INPUT_FUNCTIONKEY/F2/f2.h"
#include "../../../INPUT/KEYBOARD/INPUT_FUNCTIONKEY/F3/f3.h"
#include "../../../INPUT/KEYBOARD/INPUT_FUNCTIONKEY/F4/f4.h"
#include "../../../INPUT/KEYBOARD/INPUT_FUNCTIONKEY/F5/f5.h"
#include "../../../INPUT/KEYBOARD/INPUT_FUNCTIONKEY/F6/f6.h"
#include "../../../INPUT/KEYBOARD/INPUT_FUNCTIONKEY/F7/f7.h"

void DrawMenuBox(void) {
    ClearScreen(EFI_BACKGROUND_BLUE >> 4); // Clear screen to blue

    gST->ConOut->SetAttribute(gST->ConOut, EFI_WHITE | EFI_BACKGROUND_BLUE);
    
    Print(u"\r\n\r\n");
    Print(u"      =======================================================\r\n");
    Print(u"      ||               ARK OS RECOVERY MENU                ||\r\n");
    Print(u"      =======================================================\r\n");
    Print(u"      ||                                                   ||\r\n");
    Print(u"      ||  [F1 / 1] Firmware Setup                          ||\r\n");
    Print(u"      ||  [F2 / 2] Reboot System                           ||\r\n");
    Print(u"      ||  [F3 / 3] ShutDown                                ||\r\n");
    Print(u"      ||  [F4 / 4] BOOTMENU                                ||\r\n");
    Print(u"      ||  [F5 / 5] CONSOLE                                 ||\r\n");
    Print(u"      ||  [F6 / 6] Toggle VERBOSE (Current: ");
    if (GetVerboseMode()) Print(u"ON )           ||\r\n");
    else Print(u"OFF)           ||\r\n");
    Print(u"      ||  [F7 / 7] Continue Booting                        ||\r\n");
    Print(u"      ||                                                   ||\r\n");
    Print(u"      =======================================================\r\n");
    Print(u"\r\n      Select an option (F1-F7 or 1-7): ");
}

void ShowRecoveryMenu(void) {
    bool menuActive = true;

    while (menuActive) {
        DrawMenuBox();

        // Wait for key
        EFI_INPUT_KEY key;
        while (true) {
            EFI_STATUS status = gST->ConIn->ReadKeyStroke(gST->ConIn, &key);
            if (!EFI_ERROR(status)) {
                break;
            }
            gBS->Stall(10000); // 10ms
        }

        if (key.ScanCode == SCAN_F1 || key.UnicodeChar == '1') HandleF1();
        else if (key.ScanCode == SCAN_F2 || key.UnicodeChar == '2') HandleF2();
        else if (key.ScanCode == SCAN_F3 || key.UnicodeChar == '3') HandleF3();
        else if (key.ScanCode == SCAN_F4 || key.UnicodeChar == '4') HandleF4();
        else if (key.ScanCode == SCAN_F5 || key.UnicodeChar == '5') HandleF5();
        else if (key.ScanCode == SCAN_F6 || key.UnicodeChar == '6') HandleF6();
        else if (key.ScanCode == SCAN_F7 || key.UnicodeChar == '7') menuActive = HandleF7();
    }
    
    // Reset to black background
    ClearScreen(EFI_BACKGROUND_BLACK);
}
