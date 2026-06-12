#include "f2.h"
#include "../../../../efi.h"
#include "../../../../OUTPUT/DISPLAY/display.h"

void HandleF2(void) {
    Print(u"F2\r\n      Rebooting System...\r\n");
    gBS->Stall(1000000);
    gRT->ResetSystem(EfiResetCold, EFI_SUCCESS, 0, NULL);
}

