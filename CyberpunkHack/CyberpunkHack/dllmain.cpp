// dllmain.cpp : Defines the entry point for the DLL application.
#include "mem.h"
#include "Hook.h"
#include <cstdio>
#include <iostream>

typedef void(__stdcall* tConsumeAmmo)(long long param_1, short param_2);
tConsumeAmmo oAmmoRelated;
void __stdcall HkAmmoRelated(long long param_1, short param_2)
{
    printf("Consume Ammo Call\n");
    oAmmoRelated(param_1, 0);
}

// CRASHING
typedef void(__fastcall* tConsumeItem)(long long* itemId, int amountConsumed);
tConsumeItem oConsumeItem;
void __fastcall  HkConsumeItem(long long* itemId, int amountConsumed)
{
    printf("Consume Item Call\n");
    return oConsumeItem(itemId, 0);
}


typedef void(__stdcall* tUpdateStat)(INT64 characterId, float staminaPercentage, long long param_3, INT64 param_4,
    char param_5, char param_6);
tUpdateStat oUpdateStat;
void __stdcall HkUpdateStat(INT64 characterId,  float statValue,  long long param_3, INT64 param_4, char param_5,  char param_6)
{
    printf("Update Stat Call\n");
    std::cout << std::hex << "param 1: " << characterId << " Param 2: " << statValue << " Param 3: " << param_3 << " Param 4 :" << param_4 << std::endl;
    oUpdateStat(characterId, statValue,  param_3,  param_4, param_5,  param_6);
}

DWORD WINAPI HackThread(HMODULE hModule)
{
    //Create console
    AllocConsole();
    FILE* f;
    freopen_s(&f, "CONOUT$", "w", stdout);
    std::cout << "Im in\n";

    // get module base
    uintptr_t baseModule = (uintptr_t)GetModuleHandle(L"Cyberpunk2077.exe");
    if (!baseModule)
    {
        std::cout << "base module not found" << std::endl;
        return 0;
    }
    //oSetHealth = (tSetHealth)(baseModule + 0x242150);
    //oSetHealth = (tSetHealth)TrampHook64((BYTE*)oSetHealth, (BYTE*)HkSetHealth, 20);

    oAmmoRelated = (tConsumeAmmo)(baseModule + 0x1b08d10);
    oAmmoRelated = (tConsumeAmmo)TrampHook64((BYTE*)oAmmoRelated, (BYTE*)HkAmmoRelated, 16);
    
    oConsumeItem = (tConsumeItem)(baseModule + 0x182eb80);
    oConsumeItem = (tConsumeItem)TrampHook64((BYTE*)oConsumeItem, (BYTE*)HkConsumeItem, 15);
    
   //oUpdateStat = (tUpdateStat)(baseModule + 0x19bd100);
   //oUpdateStat = (tUpdateStat)TrampHook64((BYTE*)oUpdateStat, (BYTE*)HkUpdateStat, 14);
    
    //oConsume  basemodule + 0x182deb0
    //hack loop
    while (!GetAsyncKeyState(VK_END) &1)
    {
        //DO stuff
        
    }
   // UnHookTramp32((BYTE*)oSetHealth, (BYTE*)(baseModule + 0x242150), 20);
    UnHookTramp((BYTE*)oAmmoRelated, (BYTE*)(baseModule + 0x1b08d10), 16);
    UnHookTramp((BYTE*)oConsumeItem, (BYTE*)(baseModule + 0x182eb80), 15);
   // UnHookTramp((BYTE*)oUpdateStat, (BYTE*)(baseModule + 0x19bd100), 14);
    //cleanup and eject
    if (f)
    {
        fclose(f);
    }
    FreeConsole();
    //Disable if hooking into another thread as main thread
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
        HANDLE handle = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)HackThread, hModule, 0, 0);
            if (handle)
            {
                CloseHandle(handle);
            }
      
    }
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

