#include "f6.h"
#include "../../../../efi.h"
#include "../../../../OUTPUT/DISPLAY/display.h"
#include "../../../../LOADKERNEL/loadkernel.h"

void HandleF6(void) {
    ToggleVerboseMode();
}
