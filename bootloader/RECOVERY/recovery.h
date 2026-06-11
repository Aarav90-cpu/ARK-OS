#pragma once
#include "efi.h"

// Prompts the user "Press ESC for Options" and waits for a few seconds.
// Returns true if ESC was pressed, false otherwise.
bool WaitForEscape(void);
