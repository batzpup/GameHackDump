// dllmain.cpp : Defines the entry point for the DLL application.
#include "mem.h"
#include "Hook.h"
#include <cstdio>
#include <iostream>
#include <Psapi.h>

MODULEINFO GetModuleInfo(char* module)
{
    MODULEINFO modInfo = { 0 };
    HMODULE hModule = GetModuleHandle((LPCWSTR)module);
    if (hModule == 0)
    {
        return modInfo;
    }
    GetModuleInformation(GetCurrentProcess(), hModule, &modInfo, sizeof(MODULEINFO));
    return modInfo;
}


DWORD FindPattern(char *module, char *pattern, char *mask)
{
	//Get all module related information
	MODULEINFO mInfo = GetModuleInfo(module);

	//Assign our base and module size
	DWORD base = (DWORD)mInfo.lpBaseOfDll;
	DWORD size = (DWORD)mInfo.SizeOfImage;

	//Get length for our mask, this will allow us to loop through our array
	DWORD patternLength = (DWORD)strlen(mask);

	for (DWORD i = 0; i < size - patternLength; i++)
	{
		bool found = true;
		for (DWORD j = 0; j < patternLength; j++)
		{
			//if we have a ? in our mask then we have true by default,
			//or if the bytes match then we keep searching until finding it or not
			found &= mask[j] == '?' || pattern[j] == *(char*)(base + i + j);
		}

		//found = true, our entire pattern was found
		if (found)
		{
			return base + i;
		}
	}
	return NULL;
}






DWORD WINAPI HackThread(HMODULE hModule)
{
    //Create console
    AllocConsole();
    FILE* f;
    freopen_s(&f, "CONOUT$", "w", stdout);
    std::cout << "Im in\n";
    MODULEINFO modInfo = GetModuleInfo((char*)"Terraria.exe");
    DWORD PlayerHurt = FindPattern((char*)"Terraria.exe", (char*)"\x0C\x55\x8B\xEC\x57\x56\x53\x81\xEC\x70", (char*) "xxxxxxxxxx");

    std::cout << PlayerHurt;
    // get module base
    /*
    uintptr_t baseModule = (uintptr_t)GetModuleHandle(L"");
    if (!baseModule)
    {
        std::cout << "base module not found" << std::endl;
        return 0;
    }
    */
    //hack loop
    while (!GetAsyncKeyState(VK_END) &1)
    {
        //DO stuff
        
    }

    //cleanup and eject

    fclose(f);
    FreeConsole();
    FreeLibraryAndExitThread(hModule, 0);
   
    return 0;
}



BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    {
        DisableThreadLibraryCalls(hModule);
        CloseHandle(CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)HackThread, hModule, 0, nullptr));
      
    }
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

