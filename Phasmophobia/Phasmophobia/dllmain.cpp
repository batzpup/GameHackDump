// dllmain.cpp : Defines the entry point for the DLL application.
#include "mem.h"
#include "Hook.h"
#include <cstdio>
#include <iostream>
#include <tlhelp32.h>
#include<Psapi.h>

struct Vector3
{
    float x;
    float y;
    float z;
};


/*
Address of signature = GameAssembly.dll + 0x0203C110
"\x48\x89\x00\x00\x00\x48\x89\x00\x00\x00\x57\x48\x83\xEC\x00\x80\x3D\xAD\xC8\x9F\x01", "xx???xx???xxxx?xxxxxx"
"48 89 ? ? ? 48 89 ? ? ? 57 48 83 EC ? 80 3D AD C8 9F 01"
*/


typedef void(__stdcall* tTeleport)(Vector3 pos);
tTeleport oTeleport;

void __stdcall HkTeleport(Vector3 pos)
{
    printf("[x] Teleporting to x:%f y:%f z:%f", pos.x, pos.y, pos.z);
    return oTeleport(pos);
}

DWORD WINAPI HackThread(HMODULE hModule)
{
    //Create console
    AllocConsole();
    FILE* f;
    freopen_s(&f, "CONOUT$", "w", stdout);
    std::cout << "Im in\n";

    // get module base
    uintptr_t baseModule = (uintptr_t)GetModuleHandle(L"GameAssembly.dll");




 
    oTeleport = (tTeleport)(baseModule + 0x203C110);
    oTeleport = (tTeleport)TrampHook64((BYTE*)oTeleport, (BYTE*)HkTeleport, 14);

    //hack loop
    while (!GetAsyncKeyState(VK_END) &1)
    {
       if(GetAsyncKeyState(VK_NUMPAD9) & 1)
       {
           Vector3 pos = Vector3(0, 0, 0);
           HkTeleport(pos);
       }
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

