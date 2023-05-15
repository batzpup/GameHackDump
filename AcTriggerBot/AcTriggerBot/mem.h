#pragma once
#include <Windows.h>
#include <vector>
namespace mem
{
	void PatchEx(BYTE* dstAddr, BYTE* srcAddr, unsigned int size, HANDLE hProcess);
	void PatchExVal(BYTE* dstAddr, int val, unsigned int size, HANDLE hProcess);
	void NopEx(BYTE* dst, unsigned int size, HANDLE hProcess);

	void Patch(BYTE* dstAddr, BYTE* srcAddr, unsigned int size);

	void PatchVal(BYTE* dstAddr, int val, unsigned int size);
	void Nop(BYTE* dst, unsigned int size);

	uintptr_t FindDMAAddy(uintptr_t ptr, std::vector<unsigned int> offsets);
}
