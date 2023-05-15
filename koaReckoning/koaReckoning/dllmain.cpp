// dllmain.cpp : Defines the entry point for the DLL application.
#include "mem.h"
#include "Hook.h"
#include <cstdio>
#include <iostream>
#include "Data.cpp"
#include <d3d9.h>



//direct x bullshit
void* d3d9Device[119];
LPDIRECT3DDEVICE9 pD3DDevice = nullptr;
bool bInit = false;
static HWND window;

BOOL CALLBACK EnumWindowsCallback(HWND handle, LPARAM lParam)
{
    DWORD wndProcId;
    GetWindowThreadProcessId(handle, &wndProcId);

    if (GetCurrentProcessId() != wndProcId)
        return TRUE; // skip to next window

    window = handle;
    return FALSE; // window found abort search
}

HWND GetProcessWindow()
{
    window = NULL;
    EnumWindows(EnumWindowsCallback, NULL);
    return window;
}

bool GetD3D9Device(void** pTable, size_t Size)
{
    if (!pTable)
        return false;

    IDirect3D9* pD3D = Direct3DCreate9(D3D_SDK_VERSION);

    if (!pD3D)
        return false;

    IDirect3DDevice9* pDummyDevice = NULL;

    // options to create dummy device
    D3DPRESENT_PARAMETERS d3dpp = {};
    d3dpp.Windowed = false;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.hDeviceWindow = GetProcessWindow();

    HRESULT dummyDeviceCreated = pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, d3dpp.hDeviceWindow, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &pDummyDevice);

    if (dummyDeviceCreated != S_OK)
    {
        // may fail in windowed fullscreen mode, trying again with windowed mode
        d3dpp.Windowed = !d3dpp.Windowed;

        dummyDeviceCreated = pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, d3dpp.hDeviceWindow, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &pDummyDevice);

        if (dummyDeviceCreated != S_OK)
        {
            pD3D->Release();
            return false;
        }
    }

    memcpy(pTable, *reinterpret_cast<void***>(pDummyDevice), Size);

    pDummyDevice->Release();
    pD3D->Release();
    return true;
}

void DrawFilledRect(int x, int y, int w, int h, D3DCOLOR color, IDirect3DDevice9* dev)
{
    D3DRECT BarRect = { x, y, x + w, y + h };
    dev->Clear(1, &BarRect, D3DCLEAR_TARGET | D3DCLEAR_TARGET, color, 0, 0);
}

uintptr_t baseModule;
uintptr_t playerBase;
World* world;

typedef float(__stdcall* tEndScene)(IDirect3DDevice9* pDevice);
tEndScene oEndScene;



typedef void(__thiscall* tMovementRelated)(void* thisPtr, float posToMoveTo[2]);
tMovementRelated oMovementRelated;
void __fastcall HkMovementRelated(void* thisPtr, void* edx, float posToMoveTo[2])
{
    return oMovementRelated(thisPtr, posToMoveTo);
    if (thisPtr == world->player->locationPart->mainLocationPart->posHolder)
    {
        std::cout << "ThisPtr: " << thisPtr << " Edx: " << edx << std::dec << " posX: " << posToMoveTo[0] << " posY: " << posToMoveTo[1] << std::endl;

        float overridePos[2] = { world->cameraRelated->cameraRelated1->cameraRelated2->cameraRelated3->camera->CameraPos.x,world->cameraRelated->cameraRelated1->cameraRelated2->cameraRelated3->camera->CameraPos.y };
        return oMovementRelated(thisPtr, overridePos);
    }
    else
    {
        return oMovementRelated(thisPtr, posToMoveTo);
    }
    
}


void MainLoop()
{
      world = (World*)(baseModule + 0x007F90d4);
      
}
HRESULT __stdcall hkEndScene(IDirect3DDevice9* pDevice) {

    if (bInit == false)
    {
        pD3DDevice = pDevice;
        bInit = true;
    }

    //draw stuff here like so:
    //DrawFilledRect(200, 200, 200, 200, D3DCOLOR_ARGB(255, 255, 0, 0), pDevice);
    MainLoop();
    return oEndScene(pDevice);
}


DWORD WINAPI HackThread(HMODULE hModule)
{
    //Create console
    AllocConsole();
    FILE* f;
    freopen_s(&f, "CONOUT$", "w", stdout);
    std::cout << "Im in\n";

    // get module base
    baseModule = (uintptr_t)GetModuleHandle(L"Reckoning.exe");
    if (!baseModule)
    {
        std::cout << "base module not found" << std::endl;
        return 0;
    }
  
    oMovementRelated = (tMovementRelated)(baseModule + 0x4cade0);
    oMovementRelated = (tMovementRelated)TrampHook32((BYTE*)oMovementRelated, (BYTE*)HkMovementRelated, 6);
    
    
    BYTE endSceneBytes[7]{ 0 };
    if (GetD3D9Device(d3d9Device, sizeof(d3d9Device)))
    {
        memcpy(endSceneBytes, (char*)d3d9Device[42], 7);
        oEndScene = (tEndScene)TrampHook32((BYTE*)d3d9Device[42], (BYTE*)hkEndScene, 7);
    }
    //hack loop
    while (!GetAsyncKeyState(VK_END) &1)
    {
        Sleep(5);
    }

    UnHookTramp32((BYTE*)oMovementRelated, (BYTE*)(baseModule + 0x4cade0), 6);
    mem::Patch((BYTE*)d3d9Device[42], (BYTE*)endSceneBytes, 7);
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

