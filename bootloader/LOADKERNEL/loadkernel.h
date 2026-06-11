#pragma once
#include <stdbool.h>

// Gets the current verbose mode state
bool GetVerboseMode(void);

// Toggles the verbose mode state
void ToggleVerboseMode(void);

// Attempts to load the kernel into memory
void LoadKernel(void);
