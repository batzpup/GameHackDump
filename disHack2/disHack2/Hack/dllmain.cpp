// dllmain.cpp : Defines the entry point for the DLL application.
#include <cstdio>
#include <iostream>
#include "Proc.h"
#include "Data.cpp"
#include "Hook.h"
#include "mem.h"
#include <d3d9.h>
#include "dllmain.h"


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


//Function hook defintions
typedef void(__thiscall* tTakeDamage)(void* thisPtr, int damage, int* otherEntity, float xPos, float yPos, float zPos, float arg7, float arg8, float arg9, float arg10,int arg11, int arg12, int arg13, int arg14, int arg15, int arg16, int arg17, int arg18);
tTakeDamage oTakeDamage;

typedef void(__thiscall* tCheckForUpgradesTick) (void* thisPtr, int powerId, int zero, UINT powerLevel, int zer0);
tCheckForUpgradesTick oCheckForUpgradesTick;

typedef void(__cdecl* tSetPos)(Vector3* pos, uintptr_t entity);
tSetPos oSetPos;

typedef float*(__fastcall* tUpdatePos)(EnemyEnt*);
tUpdatePos oUpdatePos;

typedef float(__stdcall* tEndScene)(IDirect3DDevice9* pDevice);
tEndScene oEndScene;

typedef void(__thiscall* tSetCameraPos)(void* thisPtr,  Vector3* pos, Vector3* param_3);
tSetCameraPos oSetCameraPos;



//Global Variables
Player* player;
bool isRunning = true,godMode = false, infiniteMana = false, 
infiniteAmmo = false, oneShotKill = false, flyToCamera = false,
freezeEnemyMovement = false;
int currentLevelId, oldLevelId;
std::vector<EnemyEnt*> enemyEntityList{};
std::vector<EnemyEnt*> allEntityList{};
uintptr_t baseModule;
PowerList* powerList;
EnhancementList enchantmentList;
Vector3 cameraPos;
Vector3 viewMatrixBullshit;
float flySpeed = 10;


//Hook Function Implementation

void __fastcall HkSetCameraPos(void* thisPtr, void* edx, Vector3* pos,Vector3* param_3)
{

    
    oSetCameraPos(thisPtr, pos, param_3);
    //pos->y = (float)pos->y - 500;
    //pos->z = (float)pos->z + 300;
    cameraPos.x = player->position.x;
    cameraPos.y = player->position.y;
    cameraPos.z = player->position.z;
}

float* __fastcall HkUpdatePos(EnemyEnt* ent)
{
    if (ent != NULL && ent != (EnemyEnt*)player)
    {
        if (find(allEntityList.begin(), allEntityList.end(), ent) == allEntityList.end())
            {
                allEntityList.push_back(ent);

            }
        if ((int)ent->vTable == 0x1136758 && ent->currentHealth > 0 && ent->currentHealth < 100)
        {
            if (find(enemyEntityList.begin(), enemyEntityList.end(), ent) == enemyEntityList.end())
            {
                enemyEntityList.push_back(ent);
                //printf("Added entity:%p \n" "Health:%d \n", (void*)ent, ent->currentHealth);
            }
        }
    }
    return oUpdatePos(ent);
}

void __cdecl HkSetPos(Vector3* pos, uintptr_t entity)
{
    EnemyEnt* ent = (EnemyEnt*)entity;
    if (entity == NULL || entity == (uintptr_t)player)
    {
        return oSetPos(pos, entity);
    }
    if (find(enemyEntityList.begin(), enemyEntityList.end(), ent) == enemyEntityList.end())
    {
        enemyEntityList.push_back(ent);
        //printf("Added entity:%p \n" ,(void*)entity);
    }

    oSetPos(pos, entity);
}

void __fastcall HkCheckForUpgradesTick(void* thisPtr, void* edx, int powerId, int param_3, UINT powerLevel, int param_5)
{
    printf("This: %p\npowerId: %d\nParam3: %d\nPowerLevel: %d\nParam5: %d\n",thisPtr, powerId,param_3,powerLevel,param_5);
    oCheckForUpgradesTick(thisPtr, powerId, param_3, powerLevel, param_5);
}
// entity taking damage, damage type, damage amount, entity at weird offset, xpos,ypos,zpos , arg 7-11 always 0, arg12 is an addresss, arg 13 and 14 can be 0 or -1   arg 15 &16 are unknown ints  arg 17 is an unknown entity, arg 18 is the damage source
void __fastcall HkTakeDamage(void* thisPtr,void* edx, int damage, int* otherEntity, float xPos, float yPos, float zPos, float arg7, float arg8, float arg9, float arg10, int arg11, int arg12, int arg13, int arg14, int arg15, int arg16, int arg17, int arg18)
{
    /*
    printf("edx:%p\n", edx);
    printf("Entity: %p Damage: %d \n", thisPtr, damage);
    printf("arg3: %p xPos: %f yPos: %f zPos: %f \n", otherEntity, xPos, yPos, zPos);
    printf("arg7: %f arg8: %f arg9: %f arg10: %f \n", arg7, arg8, arg9, arg10);
    printf("arg11:%d arg12:%p arg13:%d arg14:%d arg15:%d arg16:%d arg17:%p arg18:%p \n", arg11, arg12, arg13, arg14, arg15, arg16, arg17, arg18);
    std::cout << "--------------------------------------------------------------------------------------------------------- \n";
    */
    if (godMode && thisPtr == player)
    {
        return;
    }
    if (oneShotKill && thisPtr != player)
    {
        damage = 1000;
    }
    
    oTakeDamage(thisPtr, damage, otherEntity, xPos, yPos, zPos, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg15, arg16, arg17, arg17, arg18);
}


void FlyLogic()
{
    // 3x3 Matrix
    // row 1: x
    // row 2: z
    // row 3: y

     // Update Camera Position
    if (GetAsyncKeyState(0x57) & 0x8000)
    {
        cameraPos.x += (viewMatrixBullshit.x * flySpeed * -1);
        cameraPos.y += (viewMatrixBullshit.z * flySpeed);
        cameraPos.z += (viewMatrixBullshit.y * flySpeed);

    }
    if (GetAsyncKeyState(0x41) & 0x8000)
    {

   
        cameraPos.x += (viewMatrixBullshit.z * flySpeed);
        cameraPos.y += (viewMatrixBullshit.x * flySpeed);
    }

     if (GetAsyncKeyState(0x53) & 0x8000)
    {
       
        cameraPos.x += (viewMatrixBullshit.x * flySpeed);
        cameraPos.y += (viewMatrixBullshit.z * flySpeed*-1);
        cameraPos.z += (viewMatrixBullshit.y * flySpeed*-1);
    }
     if (GetAsyncKeyState(0x44) & 0x8000)
    {

        cameraPos.x += (viewMatrixBullshit.z * flySpeed * -1);
        cameraPos.y += (viewMatrixBullshit.x * flySpeed * -1);
    }
     if (GetAsyncKeyState(0x51) & 0x8000)
    {
       
        cameraPos.z += flySpeed;
    }
    if (GetAsyncKeyState(0x45) & 0x8000)
    {
       
        cameraPos.z -= flySpeed;
    }
    
    //Move Player To Camera Position
    player->position.x = cameraPos.x;
    player->position.y = cameraPos.y;
    player->position.z = cameraPos.z;
}

void MainLoop()
{
    
    player = *(Player**)(baseModule + 0x1052DE8);
    currentLevelId = mem::FindDMAAddy((baseModule + 0x103D878), { 0x2c0, 0x314, 0, 0x38 });
    viewMatrixBullshit = *(Vector3*)(baseModule + 0x1066670);

    if (currentLevelId != oldLevelId)
    {
        Sleep(1000);
        oldLevelId = currentLevelId;
        return;
    }

    // key inputs
    if (GetAsyncKeyState(VK_END) & 1)
    {
        isRunning = false;
        return;
    }

    if (GetAsyncKeyState(VK_NUMPAD2) & 1)
    {
        godMode = !godMode;
        if (godMode)
        {
            player->currentHealth = player->maxHealth;
        }
    }
    if (GetAsyncKeyState(VK_NUMPAD3) & 1)
    {
        infiniteMana = !infiniteMana;
    }
    if (GetAsyncKeyState(VK_NUMPAD4) & 1)
    {
        oneShotKill = !oneShotKill;
    }
    if (GetAsyncKeyState(VK_NUMPAD5) & 1)
    {
        infiniteAmmo = !infiniteAmmo;
        if (infiniteAmmo)
        {
            mem::Nop((BYTE*)(baseModule + 0x804f19), 2);
            for (size_t i = 0; i < 18; i++)
            {
              *((int*)player->inventoryPtr->ammoInventory + i) = 20;
            }
        }
        else
        {
            mem::Patch((BYTE*)(baseModule + 0x804f19), (BYTE*)"\x2b\xc1", 2);
        }
    }
    //Sometimes crashes
    if (GetAsyncKeyState(VK_NUMPAD6) & 1)
    {
        for (auto i : enemyEntityList)
        {
            if (i == NULL)
            {
                continue;
            }
            else
            {
                HkTakeDamage((void*)i, (void*)0x0132D2B0, 9999, (int*)(baseModule + 0x1052DD4), i->position.x, i->position.y, i->position.z, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, (int)player);
            }

        }
        enemyEntityList.clear();
    }
    if (GetAsyncKeyState(VK_NUMPAD7) & 1)
    {
        flyToCamera = !flyToCamera;
        if (flyToCamera)
        {
            //Disable Player Movement
            mem::Nop((BYTE*)(baseModule + 0x24dd21), 8);//freeze x
            mem::Nop((BYTE*)(baseModule + 0x24dd36), 8);// freeze y
            mem::Nop((BYTE*)(baseModule + 0x24dd4b), 8);// freeze z
           
        }
        else
        {
            //Enable PlayerMovement
            mem::Patch((BYTE*)(baseModule + 0x24dd21), (BYTE*)"\xF3\x0F\x11\x86\xC4\x00\x00\x00", 8);//x
            mem::Patch((BYTE*)(baseModule + 0x24dd36), (BYTE*)"\xF3\x0F\x11\x86\xC8\x00\x00\x00", 8); //y 
            mem::Patch((BYTE*)(baseModule + 0x24dd4b), (BYTE*)"\xF3\x0F\x11\x86\xCC\x00\x00\x00", 8); // z
        }
    }
    if (GetAsyncKeyState(VK_NUMPAD8) & 1)
    {
        for (EnemyEnt* entity : allEntityList)
        {
            entity->position.x = player->position.x;
            entity->position.y = player->position.y;
            entity->position.z = player->position.z;
        }
        allEntityList.clear();
    }
   
    if(GetAsyncKeyState(VK_F2) & 1)
    {
        freezeEnemyMovement = !freezeEnemyMovement;
        if (freezeEnemyMovement)
        {
            mem::Patch((BYTE*)(baseModule + 0x7BB090), (BYTE*)"\xc3", 1);
        }
        else
        {
            mem::Patch((BYTE*)(baseModule + 0x7BB090), (BYTE*)"\x55", 1);
        }
    }
    if (infiniteMana)
    {
        player->currentMana = player->maxMana;
    }
    if (flyToCamera)
    {
       
        FlyLogic();
    }

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

void UnlockAllAbiltities(const uintptr_t& upgradeThisPtr)
{
    for (size_t i = 0; i < 4; i++)
    {
        oCheckForUpgradesTick((void*)upgradeThisPtr, enchantmentList.EnhancementArray[i].id, 0, 2, 0);
    }
    oCheckForUpgradesTick((void*)upgradeThisPtr, powerList->blink->powerId, 0, 2, 0);
    oCheckForUpgradesTick((void*)upgradeThisPtr, powerList->bendTime->powerId, 0, 2, 0);
    oCheckForUpgradesTick((void*)upgradeThisPtr, powerList->windBlast->powerId, 0, 2, 0);
    oCheckForUpgradesTick((void*)upgradeThisPtr, powerList->possession->powerId, 0, 2, 0);
    oCheckForUpgradesTick((void*)upgradeThisPtr, powerList->darkSense->powerId, 0, 2, 0);
    oCheckForUpgradesTick((void*)upgradeThisPtr, powerList->devouringSwarm->powerId, 0, 2, 0);
}



DWORD WINAPI HackThread(HMODULE hModule)
{
    AllocConsole();
    FILE* f;
    freopen_s(&f, "CONOUT$", "w", stdout);
    std::cout << "Im in\n";

    baseModule = (uintptr_t)GetModuleHandle(L"Dishonored.exe");

    if (!baseModule)
    {
        std::cout << "base module not found" << std::endl;
        return 0;
    }

    //do stuff here
    currentLevelId = mem::FindDMAAddy((baseModule + 0x103D878), { 0x2c0, 0x314, 0, 0x38 });

    player = *(Player**)(baseModule + 0x1052DE8);
    uintptr_t upgradeThisPtr = (uintptr_t)player->powerList->powerThisPtr;
    enchantmentList = *(EnhancementList*)mem::FindDMAAddy((baseModule + 0x1065184), { 0x1f4,0x54,0x0 });
    powerList = player->powerList;

  

    oldLevelId = currentLevelId;

    oTakeDamage = (tTakeDamage)(baseModule + 0x183da0);
    oTakeDamage = (tTakeDamage)TrampHook32((BYTE*)oTakeDamage, (BYTE*)HkTakeDamage, 6);

    oCheckForUpgradesTick = (tCheckForUpgradesTick)(baseModule + 0x6cdc90);
    oCheckForUpgradesTick = (tCheckForUpgradesTick)TrampHook32((BYTE*)oCheckForUpgradesTick, (BYTE*)HkCheckForUpgradesTick, 6);
    //oSetPos = (tSetPos)(baseModule + 0x7bb090);
    //oSetPos = (tSetPos)TrampHook32((BYTE*)oSetPos, (BYTE*)HkSetPos, 6);

    oUpdatePos = (tUpdatePos)(baseModule + 0x16df20);
    oUpdatePos = (tUpdatePos)TrampHook32((BYTE*)oUpdatePos, (BYTE*)HkUpdatePos, 6);

    oSetCameraPos = (tSetCameraPos)(baseModule + 0x1e2380);
    oSetCameraPos = (tSetCameraPos)TrampHook32((BYTE*)oSetCameraPos, (BYTE*)HkSetCameraPos, 6);

    BYTE endSceneBytes[7]{0};
    if (GetD3D9Device(d3d9Device, sizeof(d3d9Device)))
    {
        memcpy(endSceneBytes, (char*)d3d9Device[42],7);
        oEndScene = (tEndScene)TrampHook32((BYTE*)d3d9Device[42], (BYTE*)hkEndScene, 7);
    }
    
 
  
    UnlockAllAbiltities(upgradeThisPtr);
    
    
    while (isRunning)
    {
        
    }


    //UnHookTramp32((BYTE*)oSetPos, (byte*)baseModule + 0x7bb090, 6);
    UnHookTramp32((BYTE*)oCheckForUpgradesTick,(BYTE*)(baseModule + 0x6cdc90),6);
    //UnHookTramp32((BYTE*)oEndScene, (BYTE*)d3d9Device[42], 6);
    UnHookTramp32((BYTE*)oUpdatePos, (BYTE*)(baseModule + 0x16df20), 6);
    UnHookTramp32((BYTE*)oTakeDamage, (byte*)baseModule + 0x183da0, 6);
    UnHookTramp32((BYTE*)oSetCameraPos, (BYTE*)(baseModule + 0x1e2380), 6);
    mem::Patch((BYTE*)d3d9Device[42], (BYTE*)endSceneBytes,7);
    if (f)
    {
        fclose(f);
    }
    FreeConsole();
    FreeLibraryAndExitThread(hModule, 0);
    return 0;
}



BOOL APIENTRY DllMain(HMODULE hModule,
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

