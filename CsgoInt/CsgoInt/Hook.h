#pragma once

#include <Windows.h>

void Hook(BYTE* hkLoc, BYTE* funcLoc, uintptr_t len);
