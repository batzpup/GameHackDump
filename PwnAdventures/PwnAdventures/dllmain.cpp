// dllmain.cpp : Defines the entry point for the DLL application.
#include "mem.h"
#include "Hook.h"
#include <cstdio>
#include <iostream>
#include "GameLogic.h"
#include <format>
#include <string>

auto RegenPacket = "\x17\x03\x01\x00\x20\xf0\xd4\xa8\xb4\xd0\x8b\x8d\x38\x23\x39\x3f\x68\x99\xd4\x79\xf5\x6d\x8f\xb2\x57\xa2\xdf\x96\xc5\x40\x04\x83\x30\x21\xce\x47\x66\x17\x03\x01\x00\x20\xa2\xab\x30\xe9\x45\x53\x36\x27\x9a\xf7\x80\x8e\xcb\xac\x50\x11\x65\x24\xba\xb4\x50\x8e\xb2\xf6\x9b\xd0\x6a\xd7\xf4\x44\x33\x05";

struct offsets
{
    std::vector<unsigned int> playerPos = { 0x164,0x290,0x4c,0x240,0x244,0x280,0x90};
}offset;


uintptr_t playerPosptr;
uintptr_t baseModule;
ClientWorld* clientWorldPtr;
Player* activePlayer;
Vector3 playerPos;


bool displayPacketInfo = false;
bool speedHack = false;

std::string oldText;

typedef void(__thiscall* tCompleteQuest) (void* player, IQuest* quest);
tCompleteQuest oCompleteQuest;

typedef void(__thiscall* tPlayerChat) (void* player,const char* text);
tPlayerChat oPlayerChat;

typedef int (__stdcall* tWs2_32Send) (SOCKET s, const char* buffer, int len, int flags);
tWs2_32Send oSend;

typedef void(__thiscall* tVTPlayerTick) (void* thisptr,float delta);
tVTPlayerTick oVTPlayerTick;

typedef int(__stdcall* tWs32Recv)(SOCKET s, const char* buffer, int len, int flags);
tWs32Recv oWs32Recv;

int __stdcall HkWs32Recv(SOCKET socket, const char* buffer, int len, int flags)
{
    BYTE bytes[100];
    memcpy(bytes, buffer, len);
    std::string text(buffer, buffer + len);

    if (oldText != text && text.substr(0, 2) != "mv")
    {
        std::cout << "Text Recieved: " << text << "\n";
        printf("Bytes Recieved: ");
        for (auto val : bytes)
        {
            if (val != 0xcc)
            {
                printf("%.2x ", val);
            }

        }
        printf("\n");
        oldText = text;
    }
    return oWs32Recv(socket, buffer, len, flags);
}


int __stdcall HkWs32Send(SOCKET s, const char* buffer, int len, int flags)
{
    if (!displayPacketInfo)
    {

        BYTE bytes[100];
        memcpy(bytes, buffer, len);
        std::string text(buffer, buffer + len);
        
        if (oldText != text && text.substr(0,2) != "mv")
        {
            std::cout << "Text Sent: " << text << "\n";
            printf("Bytes Sent: ");
            for (auto val : bytes)
            {
                if (val != 0xcc)
                {
                    printf("%.2x ", val);
                }

            }
            printf("\n");
            oldText = text;
        }
    }
    return oSend(s,buffer,len,flags);
}

//TO DO WORK OUT MID FUNCTION HOOK
DWORD jumpBackAddy;
void __declspec(naked) MidWs32SendHook()
{
    __asm
    {
        jmp[jumpBackAddy]
    }
}

void __fastcall HkPlayerChat(void* pThis,void* notUsed, const char* text)
{

    if (strncmp("/tp ", text, 4) == 0)
    {
        Vector3 pos = Vector3(0, 0, 0);
        if (sscanf_s(text+4, "%f %f %f", &pos.x, &pos.y, &pos.z) == 3)
        {
            std::string teleportLocationText = std::format("{}, {}, {}", pos.x,pos.y,pos.z);
            std::cout << "teleporting to " << teleportLocationText << std::endl;
            (*((float*)(playerPosptr))) = pos.x;
            (*((float*)(playerPosptr+4))) = pos.y;
            (*((float*)(playerPosptr+8))) = pos.z;
        };
        

    }
    else if (strncmp("/tpa ", text, 4) == 0)
    {
        Vector3 pos = Vector3(0, 0, 0);
        if (sscanf_s(text + 4, "%f %f %f", &pos.x, &pos.y, &pos.z) == 3)
        {
            std::string teleportLocationText = std::format("{}, {}, {}", pos.x, pos.y, pos.z);
            (*((float*)(playerPosptr))) += pos.x;
            (*((float*)(playerPosptr + 4))) += pos.y;
            (*((float*)(playerPosptr + 8))) += pos.z;
        };
    }
    else if (strncmp("/tpz ", text, 4) == 0)
    {
        Vector3 pos = Vector3(0, 0, 0);
        if (sscanf_s(text + 4, "%f", &pos.z) == 1)
        {
            (*((float*)(playerPosptr + 8))) += pos.z;
        };
    }
    oPlayerChat(pThis, text);
}




void __fastcall hkVirtualPlayerTick(void* thisptr, int edx, float delta)
{
    if (GetAsyncKeyState(VK_NUMPAD3) & 1)
    {
        speedHack = !speedHack;
        std::cout << "[] Speed hack on: " << speedHack << std::endl;
    }
    if (GetAsyncKeyState(VK_NUMPAD2) & 1)
    {

        displayPacketInfo = !displayPacketInfo;
        std::cout << "[] Paused : " << displayPacketInfo << std::endl;

    }
    if (GetAsyncKeyState(VK_NUMPAD4) & 1)
    {
        oCompleteQuest(activePlayer, activePlayer->currentQuest);
        
    }
    activePlayer->walkingSpeed = speedHack ? 4000 : 200;
    activePlayer->jumpForce = speedHack ? 1000 : 420;
    activePlayer->jumpHoldTime = speedHack ? 50.0f : 0.2f;
    oVTPlayerTick(thisptr, delta);
}

DWORD WINAPI HackThread(HMODULE hModule)
{
    //Create console
    AllocConsole();
    FILE* f;
    freopen_s(&f, "CONOUT$", "w", stdout);
    std::cout << "Im in\n";

    // get module base
    baseModule = (uintptr_t)GetModuleHandle(L"GameLogic.dll");
    clientWorldPtr = *(ClientWorld**)(baseModule + 0x97d7c);
    while (clientWorldPtr == nullptr)
    {
        clientWorldPtr = *(ClientWorld**)(baseModule + 0x97d7c);
    }
    activePlayer = clientWorldPtr->activePlayer;
    playerPosptr = mem::FindDMAAddy((baseModule + 0x00097D80), offset.playerPos);
    
    //Functions to call
    //oCompleteQuest = (tCompleteQuest)(baseModule + 0x0053710);

    //Hooks
    
    //Actor Tick VTABLEHOOK
    oVTPlayerTick = (tVTPlayerTick)((uintptr_t)(activePlayer)-0x70);
    oVTPlayerTick = (tVTPlayerTick)HookVTableFunction(oVTPlayerTick, hkVirtualPlayerTick, 15);


    //Chat Hook
    oPlayerChat =  (tPlayerChat)(baseModule + 0x000551a0);
    oPlayerChat = (tPlayerChat)TrampHook32((BYTE*)oPlayerChat, (BYTE*)HkPlayerChat, 6);

    //Ws2_32.send hook
    oSend = (tWs2_32Send)GetProcAddress(GetModuleHandle(L"ws2_32.dll"), "send");
    oSend = (tWs2_32Send)TrampHook32((BYTE*)oSend, (BYTE*)HkWs32Send, 5);

    oWs32Recv = (tWs32Recv)GetProcAddress(GetModuleHandle(L"ws2_32.dll"), "recv");
    oWs32Recv = (tWs32Recv)TrampHook32((BYTE*)oWs32Recv, (BYTE*)HkWs32Recv, 5);

    /* Attempt mid function hook later
    std::cout << "w32Send Address " << oSend << std::endl;
    jumpBackAddy = (uintptr_t)oSend + 5;
    std::cout << "jumpBackAddy Address " << jumpBackAddy << std::endl;
    Detour32((BYTE*)((uintptr_t)oSend + 0x22), (BYTE*)MidWs32SendHook, 5);
    */

    //hack loop
    while (!(GetAsyncKeyState(VK_END) & 1))
    {
        
    }

    //UnHook
    UnHookTramp32((BYTE*)oSend, (BYTE*)GetProcAddress(GetModuleHandle(L"ws2_32.dll"), "send"), 5);
    UnHookTramp32((BYTE*)oPlayerChat,(BYTE*) (baseModule + 0x000551a0), 6);
    UnHookTramp32((BYTE*)oWs32Recv, (BYTE*)GetProcAddress(GetModuleHandle(L"ws2_32.dll"), "recv"), 5);
    oVTPlayerTick = (tVTPlayerTick)HookVTableFunction((tVTPlayerTick)((uintptr_t)(activePlayer)-0x70), oVTPlayerTick, 15);

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

