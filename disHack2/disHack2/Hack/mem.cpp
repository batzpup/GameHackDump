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


void mem::Patch(BYTE* patchAddr, BYTE* patchedCode, unsigned int size)
{
	DWORD oldProtectionRight;
	VirtualProtect(patchAddr, size, PAGE_EXECUTE_READWRITE, &oldProtectionRight);
	memcpy(patchAddr, patchedCode, size);
	VirtualProtect(patchAddr, size, oldProtectionRight, &oldProtectionRight);
}
void  mem::PatchVal(BYTE* dstAddr, int val, unsigned int size)
{
	DWORD oldProtectionRight;
	VirtualProtect(dstAddr, size, PAGE_EXECUTE_READWRITE, &oldProtectionRight);
	memcpy(dstAddr, (BYTE*)&val, size);
	VirtualProtect(dstAddr, size, oldProtectionRight, &oldProtectionRight);
}

void mem::Nop(BYTE* nopAddr, unsigned int size)
{
	DWORD oldProtectionRight;
	VirtualProtect(nopAddr, size, PAGE_EXECUTE_READWRITE, &oldProtectionRight);
	memset(nopAddr, 0x90, size);
	VirtualProtect(nopAddr, size, oldProtectionRight, &oldProtectionRight);

}

