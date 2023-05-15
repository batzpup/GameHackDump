#include "Hook.h"
void Hook(BYTE* hkLoc, BYTE* funcLoc, uintptr_t len)
{
	if (len < 5)
		return;

	DWORD oldProc = 0;
	VirtualProtect(hkLoc, len, PAGE_EXECUTE_READWRITE, &oldProc);
	memset(hkLoc, 0x90, len);
	DWORD relativeAddr = (funcLoc - hkLoc) - len;



	 *hkLoc = 0xE9; // set jmp to that location
	 *(hkLoc + 1) = relativeAddr; // next byte set the jump location your our relative addr

	DWORD temp;
	VirtualProtect(hkLoc, len, oldProc, &temp);
}




