#include "pch.h"
#include "mem.h"

uintptr_t  findMemoryAddress(uintptr_t ptr, vector<int> offsets) {
	uintptr_t addr = ptr;
	for (unsigned int i = 0; i < offsets.size(); i++) {
		addr = *(uintptr_t*)addr;
		addr = addr + offsets[i];
	}
	return addr;
}

void  patch(BYTE* destination, BYTE* source, unsigned int size) {
	DWORD oldProtect;
	VirtualProtect(destination,  size,  PAGE_EXECUTE_READWRITE,  &oldProtect);
	memcpy(destination, source, size);
	VirtualProtect(destination, size, oldProtect,  &oldProtect);
}

void  nop(BYTE* destination, unsigned int size) {
	DWORD  oldProtect;
	VirtualProtect(destination,  size,   PAGE_EXECUTE_READWRITE,  &oldProtect);
	memset(destination, 0x90, size);
	VirtualProtect(destination,  size,  oldProtect,  &oldProtect);
}

bool hook(void* target, void* myFunc, int size) {
	if (size < 5)  return false;      //(jmp instruction + new function's address) need at least 5 bytes

	DWORD curProtect;
	VirtualProtect(target, size, PAGE_EXECUTE_READWRITE, &curProtect);

	memset(target, 0x90, size);
	DWORD relativeAddress = ((DWORD)myFunc - (DWORD)target) - 5;
	*(BYTE*)target = 0xE9;
	*(DWORD*)((DWORD)target + 1) = relativeAddress;

	DWORD temp;
	VirtualProtect(target, size, curProtect, &temp);
	return true;
}
