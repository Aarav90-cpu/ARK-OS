#pragma once
#include "efi.h"

// Draws the recovery menu and handles user input (F1-F7).
// Returns when the user presses F7 (Continue) or triggers a system reset/shutdown.
void ShowRecoveryMenu(void);
