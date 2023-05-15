// dllmain.cpp : Defines the entry point for the DLL application.
#include <cstdio>
#include <iostream>
#include "Basics/Proc.h"
#include "Data.cpp"
#include "Basics/Hook.h"


typedef void(__thiscall* tTakeDamage)(void* thisPtr, void* arg2, float arg3, float arg4, float arg5, float arg6, float arg7, float arg8, int32_t arg9, int32_t arg10);
tTakeDamage oTakeDamage;

void __fastcall HkTakeDamage(void* thisPtr, void* edx, void* arg2, int arg3, float arg4, float arg5, float arg6, float arg7, float arg8, float arg9, float arg10)
{
    printf("Entity: %p Entity2: %d ",thisPtr,arg2);
    printf("arg3: %d xPos: %f yPos: %f zPos: %f  ", arg3, arg4,arg5,arg6);
    printf("arg7: %f arg8: %f arg9: %f arg10: %f  ", arg7, arg8, arg9, arg10);
    return oTakeDamage(thisPtr,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9,arg10);
}

DWORD WINAPI HackThread(HMODULE hModule)
{
    AllocConsole();
    FILE* f;
    freopen_s(&f, "CONOUT$", "w", stdout);
    std::cout << "Im in\n";
    uintptr_t baseModule = (uintptr_t)GetModuleHandle(L"Dishonored.exe");

    if (!baseModule)
    {
        std::cout << "base module not found" << std::endl;
        return 0;
    }
    //do stuff here
    Player* player;
    oTakeDamage = (tTakeDamage)(baseModule + 0x183da0);
    oTakeDamage = (tTakeDamage)TrampHook32((BYTE*)oTakeDamage,(BYTE*)HkTakeDamage,6);

    
    bool godMode = false, infiniteMana = false, infiniteCrossBow = false;
    while (true)
    {
        player = *(Player**)(baseModule + 0x1052DE8);
        
        // key inputs
        if (GetAsyncKeyState(VK_END) & 1)
        {
            break;
        }
        
        if (GetAsyncKeyState(VK_NUMPAD2) & 1)
        {
            godMode = !godMode;
            printf("GodMode: %d", godMode);
        }
        if (GetAsyncKeyState(VK_NUMPAD3) & 1)
        {   
            infiniteCrossBow = !infiniteCrossBow;
        }
        if (godMode)
        {
            player->curentHealth = player->maxHealth;
            player->currentMana = player->maxMana;
        }
       

          
        Sleep(1);
      
    }

  
    UnHookTramp32((BYTE*)oTakeDamage, (byte*)baseModule + 0x183da0,6);
    if (f)
    {
        fclose(f);
    }
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

