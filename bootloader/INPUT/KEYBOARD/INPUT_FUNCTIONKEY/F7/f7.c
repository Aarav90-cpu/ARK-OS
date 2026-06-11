#include "f7.h"
#include "../../../../efi.h"
#include "../../../../OUTPUT/DISPLAY/display.h"

bool HandleF7(void) {
    Print(u"F7\r\n      Continuing boot...\r\n");
    gBS->Stall(1000000);
    return false; // Tells the menu to exit
}
