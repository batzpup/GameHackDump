#include "mem.h"


uintptr_t mem::FindDMAAddy(uintptr_t ptr, std::vector<unsigned int> offsets)
{
	uintptr_t addr = ptr;
	for (unsigned int i = 0; i < offsets.size(); ++i)
	{
		addr = *(uintptr_t*)addr;
		addr += offsets[i];
	}
	return addr;
}

void mem::PatchEx(BYTE* dstAddr, BYTE* srcAddr, unsigned int size, HANDLE hProcess)
{
	DWORD oldProtectionRight;
	VirtualProtectEx(hProcess, dstAddr, size, PAGE_EXECUTE_READWRITE, &oldProtectionRight);
	WriteProcessMemory(hProcess, dstAddr, srcAddr, size, nullptr);
	VirtualProtectEx(hProcess, dstAddr, size, oldProtectionRight, &oldProtectionRight);
}
void mem::PatchExVal(BYTE* dstAddr, int val, unsigned int size, HANDLE hProcess)
{
	DWORD oldProtectionRight;
	VirtualProtectEx(hProcess, dstAddr, size, PAGE_EXECUTE_READWRITE, &oldProtectionRight);
	WriteProcessMemory(hProcess, dstAddr, (BYTE*)&val, size, nullptr);
	VirtualProtectEx(hProcess, dstAddr, size, oldProtectionRight, &oldProtectionRight);
}

void mem::NopEx(BYTE* dst, unsigned int size, HANDLE hProcess)
{
	BYTE* nopArray = new BYTE[size];
	memset(nopArray, 0x90, size);
	PatchEx(dst, nopArray, size, hProcess);
	delete[] nopArray;
}


void mem::Patch(BYTE* dstAddr, BYTE* srcAddr, unsigned int size)
{
	DWORD oldProtectionRight;
	VirtualProtect(dstAddr, size, PAGE_EXECUTE_READWRITE, &oldProtectionRight);
	memcpy(dstAddr, srcAddr, size);
	VirtualProtect(dstAddr, size, oldProtectionRight, &oldProtectionRight);
}
void  mem::PatchVal(BYTE* dstAddr, int val, unsigned int size)
{
	DWORD oldProtectionRight;
	VirtualProtect(dstAddr, size, PAGE_EXECUTE_READWRITE, &oldProtectionRight);
	memcpy(dstAddr, (BYTE*)&val, size);
	VirtualProtect(dstAddr, size, oldProtectionRight, &oldProtectionRight);
}

void mem::Nop(BYTE* dst, unsigned int size)
{
	DWORD oldProtectionRight;
	VirtualProtect(dst, size, PAGE_EXECUTE_READWRITE, &oldProtectionRight);

	memset(dst, 0x90, size);
	VirtualProtect(dst, size, oldProtectionRight, &oldProtectionRight);

}

