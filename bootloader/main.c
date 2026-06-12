#include "efi.h"
#include "OUTPUT/DISPLAY/display.h"
#include "INPUT/KEYBOARD/INPUT_ESC/esc.h"
#include "UI/DRAW/RECOVERYUI/menu.h"
#include "LOADKERNEL/loadkernel.h"
#include "UI/DRAW/LOGO/logo.h"

EFI_SYSTEM_TABLE *gST = NULL;
EFI_BOOT_SERVICES *gBS = NULL;
EFI_RUNTIME_SERVICES *gRT = NULL;
EFI_HANDLE gImageHandle = NULL;

EFI_STATUS efi_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable) {
    gST = SystemTable;
    gBS = SystemTable->BootServices;
    gRT = SystemTable->RuntimeServices;
    gImageHandle = ImageHandle;

    gST->ConOut->Reset(gST->ConOut, false);
    gST->ConOut->SetAttribute(gST->ConOut, EFI_WHITE | EFI_BACKGROUND_BLACK);
    gST->ConOut->ClearScreen(gST->ConOut);

    InitDisplay();

    DrawBmpCentered((void*)logo_bmp, logo_bmp_len);

    if (WaitForEscape()) {
        ShowRecoveryMenu();
    }

    ClearScreen(EFI_BACKGROUND_BLACK);

    LoadKernel();

    Print(u"Halted.\r\n");
    while(1) {
        gBS->Stall(1000000);
    }

    return EFI_SUCCESS;
}

