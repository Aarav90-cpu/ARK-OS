#include "f4.h"
#include "../../../../efi.h"
#include "../../../../OUTPUT/DISPLAY/display.h"

void UInt16ToBootVarName(uint16_t val, uint16_t *str) {
    const uint16_t hex[] = { '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F' };
    str[0] = 'B';
    str[1] = 'o';
    str[2] = 'o';
    str[3] = 't';
    str[4] = hex[(val >> 12) & 0xF];
    str[5] = hex[(val >> 8) & 0xF];
    str[6] = hex[(val >> 4) & 0xF];
    str[7] = hex[val & 0xF];
    str[8] = 0;
}

void HandleF4(void) {
    ClearScreen(EFI_BACKGROUND_BLACK);
    Print(u"\r\n  ARK OS BOOT MENU\r\n  ================\r\n\r\n");

    EFI_GUID globalGuid = EFI_GLOBAL_VARIABLE;
    UINTN size = 0;
    EFI_STATUS status = gRT->GetVariable(u"BootOrder", &globalGuid, NULL, &size, NULL);
    
    if (status != EFI_BUFFER_TOO_SMALL || size == 0) {
        Print(u"  No BootOrder variable found in NVRAM!\r\n");
        Print(u"\r\n  Press any key to return...");
        EFI_INPUT_KEY key;
        while (gST->ConIn->ReadKeyStroke(gST->ConIn, &key) == EFI_NOT_READY) gBS->Stall(10000);
        return;
    }

    uint16_t *bootOrder = NULL;
    gBS->AllocatePool(2, size, (void**)&bootOrder);
    gRT->GetVariable(u"BootOrder", &globalGuid, NULL, &size, bootOrder);

    UINTN numOptions = size / sizeof(uint16_t);
    if (numOptions > 9) numOptions = 9; // Limit to 0-9 for easy keyboard selection

    for (UINTN i = 0; i < numOptions; i++) {
        uint16_t varName[9];
        UInt16ToBootVarName(bootOrder[i], varName);

        UINTN optSize = 0;
        status = gRT->GetVariable(varName, &globalGuid, NULL, &optSize, NULL);
        if (status == EFI_BUFFER_TOO_SMALL) {
            uint8_t *optData = NULL;
            gBS->AllocatePool(2, optSize, (void**)&optData);
            gRT->GetVariable(varName, &globalGuid, NULL, &optSize, optData);
            
            uint16_t *desc = (uint16_t*)(optData + sizeof(EFI_LOAD_OPTION));
            
            uint16_t prefix[7] = { ' ', ' ', '[', '0' + i, ']', ' ', 0 };
            Print(prefix);
            Print(desc);
            Print(u"\r\n");
            
            gBS->FreePool(optData);
        }
    }

    gBS->FreePool(bootOrder);

    Print(u"\r\n  Press 0-");
    uint16_t maxIdx[2] = { '0' + (numOptions - 1), 0 };
    Print(maxIdx);
    Print(u" to boot, or ESC to cancel: ");

    EFI_INPUT_KEY key;
    while (true) {
        status = gST->ConIn->ReadKeyStroke(gST->ConIn, &key);
        if (!EFI_ERROR(status)) {
            if (key.UnicodeChar >= '0' && key.UnicodeChar < '0' + numOptions) {
                int selected = key.UnicodeChar - '0';
                uint16_t bootNext = bootOrder[selected];
                
                Print(u"\r\n  Setting BootNext and rebooting...\r\n");
                
                uint32_t attr = EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS;
                gRT->SetVariable(u"BootNext", &globalGuid, attr, sizeof(uint16_t), &bootNext);
                
                gRT->ResetSystem(EfiResetWarm, EFI_SUCCESS, 0, NULL);
            } else if (key.ScanCode == SCAN_ESC) {
                break;
            }
        }
        gBS->Stall(10000);
    }
}
