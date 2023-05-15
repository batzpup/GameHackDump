
#include "proc.h"


//Templates 
template <typename T>
void EditSingleValue(const HANDLE& process_handle, const uintptr_t& dynamicBaseAddress, 
               std::vector<unsigned int> valueOffsets,T newValue,std::string valueName)
{
    uintptr_t currentAmmoPtr = FindDMAAddy(process_handle, dynamicBaseAddress, valueOffsets);

    int oldValue = 0;
    ReadProcessMemory(process_handle, (void*)currentAmmoPtr, &oldValue, sizeof(oldValue), NULL);
    WriteProcessMemory(process_handle, (void*)currentAmmoPtr, &newValue, sizeof(newValue), NULL);

    ReadProcessMemory(process_handle, (void*)currentAmmoPtr, &oldValue, sizeof(oldValue), NULL);
    std::cout << "Current " << valueName << ": " << std::dec << newValue << std::endl;
}


template <typename T>
void EditVector3Value(const HANDLE& process_handle, const uintptr_t& dynamicBaseAddress,
    std::vector<std::vector<unsigned int>> valueOffsets, std::vector<T> newValues, std::vector<std::string> valueNames)
{
    uintptr_t currentXPtr = FindDMAAddy(process_handle, dynamicBaseAddress, valueOffsets[0]);
    uintptr_t currentYPtr = FindDMAAddy(process_handle, dynamicBaseAddress, valueOffsets[1]);
    uintptr_t currentZPtr = FindDMAAddy(process_handle, dynamicBaseAddress, valueOffsets[2]);

    float oldXValue = 0;
    float oldYValue = 0;
    float oldZValue = 0;
    ReadProcessMemory(process_handle, (void*)currentXPtr, &oldXValue, sizeof(oldXValue), NULL);
    ReadProcessMemory(process_handle, (void*)currentYPtr, &oldYValue, sizeof(oldYValue), NULL);
    ReadProcessMemory(process_handle, (void*)currentZPtr, &oldZValue, sizeof(oldZValue), NULL);

    float newXValue = newValues[0];
    float newYValue = newValues[1];
    float newZValue = newValues[2];
    WriteProcessMemory(process_handle, (void*)currentXPtr, &newXValue, sizeof(newXValue), NULL);
    WriteProcessMemory(process_handle, (void*)currentYPtr, &newYValue, sizeof(newYValue), NULL);
    WriteProcessMemory(process_handle, (void*)currentZPtr, &newZValue, sizeof(newZValue), NULL);

    ReadProcessMemory(process_handle, (void*)currentXPtr, &oldXValue, sizeof(oldXValue), NULL);
    ReadProcessMemory(process_handle, (void*)currentYPtr, &oldYValue, sizeof(oldYValue), NULL);
    ReadProcessMemory(process_handle, (void*)currentZPtr, &oldZValue, sizeof(oldZValue), NULL);
    std::cout << "Current " << valueNames[0] << ": " << std::dec << newXValue << std::endl;
    std::cout << "Current " << valueNames[1] << ": " << std::dec << newYValue << std::endl;
    std::cout << "Current " << valueNames[2] << ": " << std::dec << newZValue << std::endl;
}

int main()
{   
    //Setup
    // Change to games window Title
    const wchar_t* windowTitle = L"AssaultCube";
    // Change to games module Name
    const wchar_t* moduleName = L"ac_client.exe";

    DWORD process_id = GetProcId(windowTitle);
    if (!process_id)
    {
        std::cout << "process or window not found" << std::endl;
        std::cin.get();
        return 1;
    }

    uintptr_t moduleBase = GetModuleBaseAddress(process_id, moduleName);

    if (moduleBase == 0)
    {
        std::cout << "Module not found" << std::endl;
        std::cin.get();
           return 1;
    }
    uintptr_t dynamicPlayerBaseAddrSp = moduleBase + 0x109B74;
    uintptr_t dynamicPlayerBaseAddrMp = moduleBase + 0x10F4F4;

    HANDLE process_handle = 0;
    process_handle = OpenProcess(PROCESS_ALL_ACCESS, NULL, process_id);

    //Remember to use hex
    std::vector<unsigned int> AmmoOffsets = { 0x374 ,0x14,0x0 };
    std::vector<unsigned int> HealthOffsets = {0xF8};

    std::vector<unsigned int> xOffsets = { 0x34 };
    std::vector<unsigned int> yOffsets = { 0x38 };
    std::vector<unsigned int> zOffsets = { 0x3c};
    
    std::vector<std::vector<unsigned int>> posOffsets = { xOffsets ,yOffsets,zOffsets };
    std::vector<float> posValues = { 360.0f,330.0f,0.0f};
    std::vector<std::string> valueNames = { "xPos","yPos","zPos"};

    bool bRunning = true;
    bool bInfiniteAmmo = true;
    bool bGodMode = true;

    //Main loop
    while (bRunning)
    {
 
        if (bInfiniteAmmo)
        {
            EditSingleValue(process_handle, dynamicPlayerBaseAddrSp, AmmoOffsets, 6969,"Ammo");
        }
        if (bGodMode)
        {
            EditSingleValue(process_handle, dynamicPlayerBaseAddrMp, HealthOffsets,1337,"Health");
        }

        //EditVector3Value(process_handle, dynamicPlayerBaseAddrSp, posOffsets, posValues, valueNames);
        
        
        system("cls");
    }


  
    

   

}



