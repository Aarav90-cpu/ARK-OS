#include "f5.h"
#include "../../../../efi.h"
#include "../../../../OUTPUT/DISPLAY/display.h"

bool StrCmpEfi(const uint16_t* a, const uint16_t* b) {
    while (*a && *b) {
        if (*a != *b) return false;
        a++; b++;
    }
    return (*a == *b);
}

void HandleF5(void) {
    ClearScreen(EFI_BACKGROUND_BLACK);
    Print(u"ARK OS Console\r\nType 'help' for commands. 'exit' to return.\r\n> ");

    uint16_t buffer[256];
    UINTN index = 0;

    EFI_INPUT_KEY key;
    while (true) {
        EFI_STATUS status = gST->ConIn->ReadKeyStroke(gST->ConIn, &key);
        if (!EFI_ERROR(status)) {
            if (key.UnicodeChar == '\r' || key.UnicodeChar == '\n') {
                buffer[index] = 0;
                Print(u"\r\n");

                if (index > 0) {
                    if (StrCmpEfi(buffer, u"exit")) {
                        break;
                    } else if (StrCmpEfi(buffer, u"help")) {
                        Print(u"Available commands:\r\n  help   - Show this message\r\n  clear  - Clear screen\r\n  reboot - Restart system\r\n  exit   - Return to menu\r\n");
                    } else if (StrCmpEfi(buffer, u"clear")) {
                        ClearScreen(EFI_BACKGROUND_BLACK);
                    } else if (StrCmpEfi(buffer, u"reboot")) {
                        gRT->ResetSystem(EfiResetWarm, EFI_SUCCESS, 0, NULL);
                    } else {
                        Print(u"Unknown command: ");
                        Print(buffer);
                        Print(u"\r\n");
                    }
                }

                index = 0;
                Print(u"> ");
            } else if (key.UnicodeChar == '\b') {
                if (index > 0) {
                    index--;
                    Print(u"\b \b");
                }
            } else if (key.UnicodeChar >= ' ' && key.UnicodeChar <= '~') {
                if (index < 255) {
                    buffer[index++] = key.UnicodeChar;
                    uint16_t str[2] = { key.UnicodeChar, 0 };
                    Print(str);
                }
            } else if (key.ScanCode == SCAN_ESC) {
                break;
            }
        }
        gBS->Stall(10000);
    }
}

