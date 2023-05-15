#pragma once

#include <Windows.h>
#include <TlHelp32.h>
#include <iostream>
#include <vector>



uintptr_t GetModuleBaseAddress(DWORD procId, const wchar_t* modName);
DWORD GetProcId(const wchar_t* windowTitle);
uintptr_t FindDMAAddy(HANDLE hProc, uintptr_t ptr, std::vector<unsigned int> offsets);