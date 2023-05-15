// dllmain.cpp : Defines the entry point for the DLL application.
#include "mem.h"
#include <cstdio>
#include <iostream>
#include <bitset>

#define FL_ONGROUND 1  
std::bitset<32> newForceJump;

struct gameOffsets
{
    uintptr_t localClient = 0x4DDB92C;
    uintptr_t localPlayer = 0xDBF4CC;
    uintptr_t forceJump = 0x52858A8;
    uintptr_t flags = 0x104;
    uintptr_t bSpotted = 0x93D;
    uintptr_t entityList = 0x4DDB91C;
    uintptr_t flashDuration = 0x10470;
}offsets;



struct values
{
    uintptr_t localClient;
    uintptr_t localPlayer;
    uintptr_t forceJump;
    uintptr_t flags;
    uintptr_t entityList;
    uintptr_t flashDuration;
}values;


DWORD WINAPI HackThread(HMODULE hModule)
{
    //Create console
    AllocConsole();
    FILE* f;
    freopen_s(&f, "CONOUT$", "w", stdout);
    
    // get module base
    
    uintptr_t baseModule = (uintptr_t)GetModuleHandle(L"client.dll");
 
    values.localPlayer = *(uintptr_t*)(baseModule + offsets.localPlayer);
   
    if (!values.localPlayer)
    {
       
        std::cout << "Waiting for Game"  << "\n";
    }
    if (!values.localPlayer)
    {
        while (!values.localPlayer)
        {
            values.localPlayer = *(uintptr_t*)(baseModule + offsets.localPlayer);
        }
    }

    //hack loop
    while (!GetAsyncKeyState(VK_END) & 1)
    {
        
        
    
        values.localPlayer = *(uintptr_t*)(baseModule + offsets.localPlayer);
        values.entityList = (baseModule + offsets.entityList);
        values.flashDuration = *(uintptr_t*)(values.localPlayer + offsets.flashDuration);
        if (values.flashDuration > 0)
        {
            *(uintptr_t*)(values.localPlayer + offsets.flashDuration) = 0;
        }

        for (int i = 1; i <= 10; i++)
        {
            if (!*(uintptr_t*)(values.entityList + i * 0x10))
            {
                break;
            }
            *(uintptr_t*)(*(uintptr_t*)(values.entityList + i*0x10) + offsets.bSpotted) = 1;
        }       

        if (GetAsyncKeyState(VK_SPACE) )
        {
            values.flags = *(BYTE*)(values.localPlayer + offsets.flags);
            values.forceJump = *(uintptr_t*)(baseModule + offsets.forceJump);
            newForceJump = values.forceJump;

            if (values.flags == FL_ONGROUND)
            {
                newForceJump.set(0);
                *(uintptr_t*)(baseModule + offsets.forceJump) = newForceJump.to_ulong();
            }
            else
            {
                newForceJump.reset(0);
                *(uintptr_t*)(baseModule + offsets.forceJump) = newForceJump.to_ulong();
            }
            
        }

        Sleep(1);
        system("cls");
    }

    //cleanup and eject
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
        DisableThreadLibraryCalls(hModule);
        HANDLE handle = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)HackThread, hModule, 0, 0);
            if (handle)
            {
                CloseHandle(handle);
            }
      
    }
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

