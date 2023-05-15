// dllmain.cpp : Defines the entry point for the DLL application.
#include "mem.h"
#include <cstdio>
#include <iostream>
#include "ent.h"
#include "Hook.h"
/// <summary>
/// Damage is Server Side
/// Health is Server Side
/// </summary>

typedef Ent* (__cdecl* tGetEntAtCrossHair)();

//Patch and hook Address
uintptr_t recoilHkAddress = 0x00462021;
uintptr_t freezeHkAddress = 0X0045bd40;

// call address
uintptr_t PrintToKillFeedAddress = 0x004090f0;
uintptr_t PrintSomewhereAddress = 0x0046b060;

//Call Functions
typedef void(__cdecl* _PrintSomething)(char* string);
_PrintSomething PrintToKillFeed = (_PrintSomething)PrintToKillFeedAddress;
_PrintSomething PrintSomewhere = (_PrintSomething)PrintSomewhereAddress;


Ent* localPlayerPtr{ nullptr };
bool healthHack = false;
bool ammoHack = false;
bool triggerBotHack = false;
bool flyHack = false;
bool gunHack = false;
bool freezePlayer = false;

UINT16 oldReloadSpeed;
UINT16 oldTimeBetweenShots;
UINT16 oldDamage;
UINT16 oldSpreadArea;
UINT16 oldKnockBack;
UINT16 oldInitialRecoil;
UINT16 oldRecoil;
UINT16 oldDragDownForce;
UINT16 oldIsAuto;

typedef BOOL(__stdcall* twglSwapBuffers) (HDC hDc);
twglSwapBuffers owglSwapBuffers;

uintptr_t baseModule = (uintptr_t)GetModuleHandle(L"ac_client.exe");
tGetEntAtCrossHair GetEntAtCrossHair = (tGetEntAtCrossHair)(baseModule + 0x607c0);





void __declspec(naked) StopRecoil()
{
    __asm {

        pop ebp
        ret 0x0008
        nop
    }
}



BOOL __stdcall hkwglSwapBuffers(HDC hDc)
{
   
    localPlayerPtr = *(Ent**)(baseModule + 0x10F4F4);

    if (GetAsyncKeyState(VK_NUMPAD7) & 1)
    {
        healthHack = !healthHack;
    }
    if (GetAsyncKeyState(VK_NUMPAD8) & 1)
    {
        ammoHack = !ammoHack;
    }
    if (GetAsyncKeyState(VK_NUMPAD9) & 1)
    {
        
        triggerBotHack = !triggerBotHack;
        std::cout << "Trigger Bot Enabled: " << triggerBotHack << std::endl;
    }
    if (GetAsyncKeyState(VK_NUMPAD1) & 1)
    {
        flyHack = !flyHack;
    }
    if (GetAsyncKeyState(VK_NUMPAD2) & 1)
    {
        gunHack = !gunHack;
        if (gunHack)
        {
            mem::Patch((BYTE*)recoilHkAddress, (BYTE*)StopRecoil, 5);
        }
        else
        {
            mem::Patch((BYTE*)recoilHkAddress, (BYTE*)"\x8b\xec\x83\xe4\xf8", 5);
        }
    }
    if (GetAsyncKeyState(VK_NUMPAD3) & 1)
    {
        freezePlayer = !freezePlayer;
        PrintToKillFeed((char*)"Hello Gamers");
       
    }
   
    if (localPlayerPtr)
    {
        if (healthHack)
        {
            localPlayerPtr->health = 1000;
        }
        if (ammoHack)
        {
            localPlayerPtr->currentWeapon->ammoPointer->currentAmmo = 6969;
        }

        if (flyHack)
        {
            localPlayerPtr->canFly5 = 5;
        }
        else
        {
            localPlayerPtr->canFly5 = 0;
        }
       
       

        if (triggerBotHack)
        {
            
            Ent* crossHairEnt = GetEntAtCrossHair();
            if (crossHairEnt)
            {
                if (localPlayerPtr->teamId != crossHairEnt->teamId)
                {
                    localPlayerPtr->isFiring = true;
                }
                else
                {
                    localPlayerPtr->isFiring = false;
                }
            }
  
        }
    }
    return owglSwapBuffers(hDc);
}





DWORD WINAPI HackThread(HMODULE hModule)
{
    //Create console
    AllocConsole();
    FILE* f;
    freopen_s(&f, "CONOUT$", "w", stdout);
    std::cout << "Im in\n";
 

    std::cout << std::hex << "stop recoil func Loc: " << StopRecoil << std::endl;
   

 
    // Hook
    owglSwapBuffers = (twglSwapBuffers)GetProcAddress(GetModuleHandle(L"opengl32.dll"), "wglSwapBuffers");
    owglSwapBuffers = (twglSwapBuffers)TrampHook32((BYTE*)owglSwapBuffers, (BYTE*)hkwglSwapBuffers, 5);
    //
   
    while (!GetAsyncKeyState(VK_END) & 1)
    {
        
       

    }


    //cleanup and eject
    if (f)
    {
        fclose(f);
    }
    FreeConsole();
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
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

