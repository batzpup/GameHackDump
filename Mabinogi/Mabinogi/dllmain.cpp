// dllmain.cpp : Defines the entry point for the DLL application.
#include "mem.h"
#include "Hook.h"
#include <cstdio>
#include <iostream>



typedef int(__stdcall* tWs2_32Send) (SOCKET s, const char* buffer, int len, int flags);
tWs2_32Send oSend;

typedef int(__cdecl*_mabiWs2_SendWrapper) (SOCKET s, const char* buffer, int len, int flags);
_mabiWs2_SendWrapper mabiWS2_SendWrapper;

bool isConsolePaused = false;


int __cdecl HkMabiWs2SendWrapper(SOCKET s, const char* buffer, int len, int flags)
{
    BYTE bytes[100];
    memcpy(bytes, buffer, len);
    for (auto val : bytes)
        printf("%.2x ", val);
    printf("\n");
    return mabiWS2_SendWrapper(s, buffer, len, flags);
}

int __stdcall HkWs32Send(SOCKET s, const char* buffer, int len, int flags)
{
    if (!isConsolePaused)
    {
        
        BYTE bytes[0x500];
        memcpy(bytes, buffer, len);
        for (auto val : bytes)
        {
            if (val != 0xcc && val != 0x00)
            {
                printf("%.2x ", val);
            }
        }
        printf("\n \n");
    }
    return oSend(s,buffer,len,flags);
}


DWORD WINAPI NexonSecurity(HMODULE hModule)
{
    //Create console
    AllocConsole();
    FILE* f;
    freopen_s(&f, "CONOUT$", "w", stdout);
    std::cout << "Im in\n";

    // get module base
    uintptr_t baseModule = (uintptr_t)GetModuleHandle(L"Client.exe");


   


    //hack loop
    while (!GetAsyncKeyState(VK_END) & 1)
    {


        if (GetAsyncKeyState(VK_HOME) & 1)
        {
            printf("Hooked\n");
            
            // oSend = (tWs2_32Send)GetProcAddress(GetModuleHandle(L"ws2_32.dll"), "send");
            // oSend = (tWs2_32Send)TrampHook32((BYTE*)oSend, (BYTE*)HkWs32Send, 5);
            //mabiWS2_SendWrapper = (_mabiWs2_SendWrapper)(baseModule + 0x269AF60);
            //mabiWS2_SendWrapper = (_mabiWs2_SendWrapper) ((uintptr_t)mabiWS2_SendWrapper +0x06);

            //mabiWS2_SendWrapper = (_mabiWs2_SendWrapper)TrampHook32((BYTE*)oSend, (BYTE*)HkWs32Send, 5);
        }
        if (GetAsyncKeyState(VK_NUMPAD3) & 1)
        {
            printf("Unhooked\n");
            //UnHookTramp32((BYTE*)oSend, (BYTE*)GetProcAddress(GetModuleHandle(L"ws2_32.dll"), "send"), 5);
            
        }
        if (GetAsyncKeyState(VK_NUMPAD1) & 1)
        {
            isConsolePaused = !isConsolePaused;
            std::cout << "[] Paused : " << isConsolePaused << std::endl;
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
        HANDLE handle = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)NexonSecurity, hModule, 0, 0);
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

