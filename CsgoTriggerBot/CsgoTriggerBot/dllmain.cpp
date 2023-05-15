// dllmain.cpp : Defines the entry point for the DLL application.
#include "mem.h"
#include "Hook.h"
#include <cstdio>
#include <iostream>


struct offsets
{
    uintptr_t localPlayer = 0xDBF4CC;
    uintptr_t forceLMB = 0x320BE10;
    uintptr_t entityList = 0x4DDB92C;
    uintptr_t crosshair = 0x11838;
    uintptr_t team = 0xF4;
    uintptr_t health = 0x100;
} offset;

struct variables
{
    uintptr_t localPlayer;
    uintptr_t gameModule;
    uintptr_t myTeam;
    uintptr_t entityList;
} val;


bool canTbot = false;

void Shoot()
{
    *(uintptr_t*)(val.gameModule + offset.forceLMB) = 5;
    Sleep(20);
    *(uintptr_t*)(val.gameModule + offset.forceLMB) = 4;
}
bool CheckTBot()
{

    uintptr_t crosshair = *(uintptr_t*) (val.localPlayer + offset.crosshair);
    if (crosshair != 0 && crosshair < 64)
    {
        uintptr_t entity = *(uintptr_t*)( val.entityList + ((crosshair - 1) * 0x10)); 
        uintptr_t entTeam = *(uintptr_t*)(entity + offset.team);
        uintptr_t entHealth = *(uintptr_t*)(entity + offset.health);
        
        
        if (entTeam == val.myTeam || entHealth <= 0)
        {
            return false;
        }
     
        return true;
    
    }
    return false;
    
    
}

void HandleTBot()
{
    if (CheckTBot())
    {
        Shoot();
    }
}

DWORD WINAPI HackThread(HMODULE hModule)
{


    //Create console
    AllocConsole();
    FILE* f;
    freopen_s(&f, "CONOUT$", "w", stdout);
    std::cout << "Im in\n";

 
    val.gameModule = (uintptr_t)GetModuleHandle(L"client.dll");
    val.localPlayer = *(uintptr_t*) (val.gameModule + offset.localPlayer);

    if (!val.localPlayer)
    {
        while (!val.localPlayer)
        {
            val.localPlayer = *(uintptr_t*)(val.gameModule + offset.localPlayer);
        }
    }



    //hack loop
    while (!GetAsyncKeyState(VK_END) &1)
    {
        val.entityList = (val.gameModule + offset.entityList);
      

        if (GetAsyncKeyState(VK_F2) & 1)
        {
            val.myTeam = *(uintptr_t*) (val.localPlayer + offset.team);
            canTbot = !canTbot;
            std::cout << "Trigger bot enabled: " << canTbot << std::endl;
        }

        if (canTbot)
        {
            HandleTBot();
        }
        
        Sleep(1);
    }

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

