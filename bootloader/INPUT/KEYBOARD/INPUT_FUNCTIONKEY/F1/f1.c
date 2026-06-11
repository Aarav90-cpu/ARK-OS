#include "f1.h"
#include "../../../../efi.h"
#include "../../../../OUTPUT/DISPLAY/display.h"

void HandleF1(void) {
    Print(u"F1\r\n      Rebooting to Firmware Setup...\r\n");
    gBS->Stall(1000000);
    gRT->ResetSystem(EfiResetCold, EFI_SUCCESS, 0, NULL);
}
