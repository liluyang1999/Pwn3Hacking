#include "pch.h"
#include "hackFunc.h"
// original
extern uintptr_t baseAddr;

DWORD  speedHookJumpBack;
float  walkSpeed = 1500;
void  speedHackFunc(uintptr_t  baseAddr, bool flag) {
	DWORD speedHook = baseAddr + 0x4ff90;
	// length 6, overwrites initial bytes
	int speedHookLen = 6;
	// jump back to the original function.
	speedHookJumpBack = speedHook + speedHookLen;
	// true
	if (flag) {
		hook((void*)speedHook, speedHackOnFunc, speedHookLen);
	}
	// false, patch original bytes
	else {
		patch((BYTE*)(speedHook), (BYTE*)"\xd9\x81\x20\x01\x00\x00", speedHookLen);
		*(float*)findMemoryAddress(baseAddr + 0x97d7c, { 0x1c, 0x6c, 0x120 }) = 200;
	}
}
// inject assembly to the orignal function
// pushing declared walk speed (1500) into register
// move walk speed into the pointer address with an offset of 120, overwriting the initial walkspeed
// pop
// after assigning the new walking speed, we follow the orignal logic, jumping back to the orignal function.
void  __declspec(naked)  speedHackOnFunc() {
	__asm {
		push eax
		mov eax, walkSpeed
		mov dword ptr[ecx + 0x120], eax
		pop eax
		fld dword ptr[ecx + 0x120]
		jmp[speedHookJumpBack]
	}
}


void  immuneDamageHackFunc(uintptr_t baseAddr, bool flag) {
	if (flag) {
		patch((BYTE*)(baseAddr + 0x51176), (BYTE*)"\x0F\x84\x9C\x00\x00\x00", 6);
	}
	else {
		patch((BYTE*)(baseAddr + 0x51176), (BYTE*)"\x0F\x85\x9C\x00\x00\x00", 6);
	}
}


DWORD  manaHookJumpBack;
void  manaHackFunc(uintptr_t baseAddr, bool flag) {
	// Dword hook shows the actual address of the mana in the game, 525c5 = the location where the use mana value is stored
	DWORD manaHook = baseAddr + 0x525c5;
	// we overwrite 8 bytes, we use these 8 bytes to tell the program to jump our function, instead of the game function. (we replace the game function with our own) 
	int manaHookLen = 8;
	// After we overwrite the mana value, we jump back to the orignal function
	manaHookJumpBack = manaHook + manaHookLen;
	if (flag) {
		hook((void*)manaHook, manaHackOnFunc, manaHookLen);
	}
	else {
		patch((BYTE*)(manaHook), (BYTE*)"\x2b\xc2\x89\x86\xbc\x00\x00\x00", manaHookLen);
		*(int*)findMemoryAddress(baseAddr + 0x97d7c, { 0x1c, 0x6c, 0xbc }) = 100;
	}
}
// the function we are using to overwrite
void  __declspec(naked)  manaHackOnFunc() {
	__asm {
		// same assembly that the game uses, but we do not include the subtract mana part of the assembly (sub     eax, edx).
		// we are removing the mana subtraction part of the useMana assembly function, and executing the rest of the function. 
		mov[esi + 0xBC], eax
		// execute the rest of the assembly from 525CD (0x525CD = 0x525C5 + 8 bytes) onwards
		jmp[manaHookJumpBack]
	}
}


DWORD  greatDamageJumpBack;
void  greatDamageHackFunc(uintptr_t baseAddr, bool flag) {
	uintptr_t  greatDamageHook = baseAddr + 0x20C2;
	int greatDamageLen = 6;
	greatDamageJumpBack = greatDamageHook + greatDamageLen;
	if (flag) {
		hook((void*)greatDamageHook, greatDamageHackOnFunc, greatDamageLen);
	}
	else {
		patch((BYTE*)greatDamageHook, (BYTE*)"\x8b\x45\x10\x29\x47\x30", 6);
	}
}
void  _declspec(naked)  greatDamageHackOnFunc() {
	_asm {
		mov  eax, 0x2000
		sub[edi + 0x30], eax
		jmp[greatDamageJumpBack]
	}
}


DWORD  bearHookJumpBack;
char bearName[] = "Friendly Bear";
DWORD bearNameJumpBack;
BYTE*  prepareAttackBytes = (BYTE*)malloc(432);
BYTE*  defendBytes = (BYTE*)malloc(692);
void  bearHackFunc(uintptr_t baseAddr, bool flag) {
	DWORD bearHook = baseAddr + 0x5190;
	DWORD bearNameHook = baseAddr + 0x51C0;
	int bearHookLen = 6;
	int bearNameHookLen = 5;
	bearHookJumpBack = bearHook + bearHookLen;
	bearNameJumpBack = bearNameHook + bearNameHookLen;
	if (flag) {
		hook((void*)bearHook, bearRadiusHackOnFunc, bearHookLen);   //Stop bear's active aggression
		hook((void*)bearNameHook, bearNameHackOnFunc, bearNameHookLen);
		patch(prepareAttackBytes, (BYTE*)(baseAddr + 0x66c9),  432);
		patch(defendBytes, (BYTE*)(baseAddr + 0x5216), 692);
		nop((BYTE*)(baseAddr + 0x66c9), 432);   //Let bear attack itself
		nop((BYTE*)(baseAddr + 0x5216), 692);   //Stop bear defend for chest
	}
	else {
		patch((BYTE*)(bearHook), (BYTE*)"\xd9\x05\xa0\x8b\x07\x10", bearHookLen);
		patch((BYTE*)(bearNameHook), (BYTE*)"\xb8\xe4\xf9\x06\x10", bearNameHookLen);
		patch((BYTE*)(baseAddr + 0x66c9),  prepareAttackBytes, 432);
		patch((BYTE*)(baseAddr + 0x5216),  defendBytes, 692);
	}
}
void  __declspec(naked)  bearRadiusHackOnFunc() {
	_asm {
		mov eax, 0
		jmp[bearHookJumpBack]
	}
}
void  __declspec(naked)  bearNameHackOnFunc() {
	_asm {
		mov eax, offset bearName
		jmp[bearNameJumpBack]
	}
}



