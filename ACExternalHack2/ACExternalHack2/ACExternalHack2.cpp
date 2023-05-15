
#include "proc.h"
#include "mem.h"

int main()
{

    const wchar_t* windowTitle = L"AssaultCube";
    const wchar_t* moduleName = L"ac_client.exe";



    DWORD process_id = GetProcId(windowTitle);
    if (!process_id)
    {
        std::cout << "process or window not found" << std::endl;
        std::cin.get();
        return 0;
    }

    uintptr_t moduleBase = GetModuleBaseAddress(process_id, moduleName);
    if (moduleBase == 0)
    {
        std::cout << "Module not found" << std::endl;
        std::cin.get();
        return 0;
    }
    uintptr_t dynamicPlayerBaseAddrMp = moduleBase + 0x10F4F4;

    HANDLE hProcess = 0;
    hProcess = OpenProcess(PROCESS_ALL_ACCESS, NULL, process_id);


    uintptr_t healthAddr = 0, ammoAddr = 0, hasAkimboAddr = 0;
    healthAddr = FindDMAAddy(hProcess, dynamicPlayerBaseAddrMp, { 0xf8 });
    
    hasAkimboAddr = FindDMAAddy(hProcess, dynamicPlayerBaseAddrMp, { 0x10c });


    DWORD shouldExit;

    const int healthValue = 1337;
    const int ammoValue = 6969;
    const bool Akimbo = true;

    bool godmode = false, infiniteAmmo = false, hasAkimbo = false;
    while(GetExitCodeProcess(hProcess,&shouldExit) && shouldExit == STILL_ACTIVE )
    {
        ammoAddr = FindDMAAddy(hProcess, dynamicPlayerBaseAddrMp, { 0x374,0x14,0x0 });
        if (GetAsyncKeyState(VK_HOME) & 1)
        {
            godmode = !godmode;
            
           
        }
        if (GetAsyncKeyState(VK_INSERT) & 1)
        {
            infiniteAmmo = !infiniteAmmo;
        }
        if (GetAsyncKeyState(VK_NUMPAD7) & 1)
        {
            hasAkimbo = !hasAkimbo;
        }
        if (godmode)
        {
            std::cout << "God Mode Activated\n";
            mem::PatchEx((BYTE*)healthAddr, (BYTE*)&healthValue, sizeof(healthValue), hProcess);
        }
        if (infiniteAmmo)
        {
            std::cout << "Infinite Activated\n";
            mem::PatchExVal((BYTE*)ammoAddr, 1549, sizeof(ammoValue), hProcess);
        }
        if (hasAkimbo)
        {
            
            mem::PatchEx((BYTE*)hasAkimboAddr, (BYTE*)&Akimbo, sizeof(Akimbo), hProcess);
        }

        Sleep(10);
        system("cls");
    }
}

