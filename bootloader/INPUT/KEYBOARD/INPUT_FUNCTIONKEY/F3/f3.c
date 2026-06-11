#include "f3.h"
#include "../../../../efi.h"
#include "../../../../OUTPUT/DISPLAY/display.h"

void HandleF3(void) {
    Print(u"F3\r\n      Shutting down...\r\n");
    gBS->Stall(1000000);
    gRT->ResetSystem(EfiResetShutdown, EFI_SUCCESS, 0, NULL);
}
