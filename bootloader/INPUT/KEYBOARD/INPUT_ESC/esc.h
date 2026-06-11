#pragma once
#include <stdbool.h>

// Prompts the user to press ESC at the bottom right corner.
// Uses a proper UEFI timer event to wait.
bool WaitForEscape(void);
