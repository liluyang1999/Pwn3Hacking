#include  "pch.h"
#include  "mem.h"
#include  "hackFunc.h"
#include  "originalFunc.h"
// Basic Code Template for Dll injection used^
// https://guidedhacking.com/threads/how-to-hack-any-game-tutorial-c-trainer-3-first-internal.12142/
// Hooks learned and used from
// https://liveoverflow.com/why-speedrunners-are-hackers-and-cheaters/
// https://guidedhacking.com/threads/how-to-hook-functions-code-detouring-guide.14185/
// Fly hack built off of
// https://youtu.be/8Z1D64qfrxM
DWORD WINAPI MyThread(HMODULE hModule)
{
	AllocConsole();
	FILE* f = new FILE;
	freopen_s(&f, "CONOUT$", "w", stdout);
	cout << "**********************************************************************" << endl;
	cout << "DLL Injection Hacking\n";
	cout << "Process ID: " << GetCurrentProcessId() << endl;
	cout << "**********************************************************************" << endl;
	cout << "Please choose the mode by pressing the corresponding key\n" << endl;
	cout << "F1:  Accelerating walking speed" << endl;
	cout << "F2:  Increase jump speed and hold time" << endl;
	cout << "F3:  Immune to damage" << endl;
	cout << "F4:  Unlimited mana" << endl;
	cout << "F5:  Great damage to enemy" << endl;
	cout << "F6:  Stop bears' attack and defend for chest" << endl;
	cout << "F:   Flying mode" << endl;
	cout << "G:   Teleport to designated places" << endl;
	cout << "H:   Get weapons and ammunition" << endl;
	cout << "**********************************************************************" << endl;
	cout << "G+1: Bear Chest    G+2: Gun Shop    G+3: Fireball    G+4: Pirate Bay" << endl;
	cout << "G+5: Magma Boss     G+6: Cow King     G+7: Fort Blox" << endl;
	cout << "**********************************************************************" << endl;
	cout << "Press 'F7' to close the injection" << endl;
	cout << "**********************************************************************" << endl;

 	uintptr_t  pwnAventAddr = (uintptr_t)GetModuleHandle(L"PwnAdventure3-Win32-Shipping.exe");
	uintptr_t  gameLogicAddr = (uintptr_t)GetModuleHandle(L"GameLogic.dll");

	Vector3* playerPos = (Vector3*)(findMemoryAddress(pwnAventAddr + 0x18FCD60, { 0x20, 0x238, 0x280, 0x90 }));
	Vector3* cameraPos = (Vector3*)(findMemoryAddress(pwnAventAddr + 0x18FCD60, { 0X20, 0x238, 0x400, 0x90 }));
	Vector4* qua = (Vector4*)(findMemoryAddress(pwnAventAddr + 0x18FCD60, { 0x20, 0x238, 0x400, 0x80 }));

	int* health = (int*)(findMemoryAddress(gameLogicAddr + 0x97D7C, { 0x1C, 0x6C, -0x40 }));
	int* mana = (int*)(findMemoryAddress(gameLogicAddr + 0x97D7C, { 0x1C, 0x6C, 0xBC }));
	float* jumpSpeed = (float*)(findMemoryAddress(gameLogicAddr + 0x97D7C, { 0x1C, 0x6C, 0x124 }));
	float* jumpHoldTime = (float*)(findMemoryAddress(gameLogicAddr + 0x97D7C, { 0x1C, 0x6C, 0x128 }));

	// declaring a false flag, hack disabled
	bool speedFlag = false;
	bool jumpFlag = false;
	bool manaFlag = false;
	bool imDamageFlag = false;
	bool grDamageFlag = false;
	bool flyFlag = false;
	bool bearFlag = false;

	vector<int>  playerVftableAddressOffset = { 0x1c, 0x6c, 0x0 };
	void* playerVftable = (void*)findMemoryAddress(gameLogicAddr + 0x97D7C, playerVftableAddressOffset);
	_Chat Chat = (_Chat)(gameLogicAddr + 0x551A0);

	//Flying hack parameters
	BYTE  originalCode[7] = { 0 };
	float speed = 110.0f;
	int i = 0;
	Vector3  temp;

	while (true) {

		//Accelerating walk speed
		if (GetAsyncKeyState(VK_F1) & 1) {
			speedFlag = !speedFlag;
			if (speedFlag) {
				cout << "Start accelerating......" << endl;
				Chat(playerVftable, "Start accelerating");
				speedHackFunc(gameLogicAddr, true);
			}
			else {
				cout << "Stop accelerating......" << endl;
				Chat(playerVftable, "Stop accelerating");
				speedHackFunc(gameLogicAddr, false);
			}
		}

		//Increase jump speed and hold time
		if (GetAsyncKeyState(VK_F2) & 1) {
			jumpFlag = !jumpFlag;
			if (jumpFlag) {
				cout << "Increase jump speed and hold time......" << endl;
				Chat(playerVftable, "Increase jump speed and hold time");
				*jumpSpeed = 800;
				*jumpHoldTime = 10;
			}
			else {
				cout << "Restore jump speed and hold time......" << endl;
				Chat(playerVftable, "Restore jump speed and hold time");
				*jumpSpeed = 420;
				*jumpHoldTime = 0.2;
			}
		}

		//Immune to any damage
		if (GetAsyncKeyState(VK_F3) & 1) {
			imDamageFlag = !imDamageFlag;
			if (imDamageFlag) {
				cout << "Start immunity to damage......." << endl;
				Chat(playerVftable, "Start immunity to damage");
				immuneDamageHackFunc(gameLogicAddr, imDamageFlag);
			}
			else {
				cout << "Stop immunity to damage......." << endl;
				Chat(playerVftable, "Stop immunity to damage");
				immuneDamageHackFunc(gameLogicAddr, imDamageFlag);
			}
		}

		//Unlimited mana
		if (GetAsyncKeyState(VK_F4) & 1) {
			// when we press the key, we toggle the flag to true, enabling the hack
			manaFlag = !manaFlag;
		
			if (manaFlag) {
				// print to console (black box)
				cout << "Start unlimited mana......" << endl;
				// use chat function to show hack has started in the chat (in game)
				Chat(playerVftable, "Start unlimited mana");
				// send game logic address, and the true flag to the function
				manaHackFunc(gameLogicAddr, true);
			}
			else {
				cout << "Stop unlimited mana......" << endl;
				Chat(playerVftable, "Stop unlimited mana");
				manaHackFunc(gameLogicAddr, false);
			}
		}

		//Great damage to enemy
		if (GetAsyncKeyState(VK_F5) & 1) {
			grDamageFlag = !grDamageFlag;
			if (grDamageFlag) {
				cout << "Start great damage......." << endl;
				Chat(playerVftable, "Start great damage");
				greatDamageHackFunc(gameLogicAddr, grDamageFlag);
			}
			else {
				cout << "Stop great damage......." << endl;
				Chat(playerVftable, "Stop great damage");
				greatDamageHackFunc(gameLogicAddr, grDamageFlag);
			}
		}

		//Stop bear's attack and defend for chest
		if (GetAsyncKeyState(VK_F6) & 1) {
			bearFlag = !bearFlag;
			if (bearFlag) {
				cout << "Start hack bear......" << endl;
				Chat(playerVftable, "Start hack bear");
				bearHackFunc(gameLogicAddr, bearFlag);
			}
			else {
				cout << "Stop hack bear......" << endl;
				Chat(playerVftable, "Stop hack bear");
				bearHackFunc(gameLogicAddr, bearFlag);
			}
		}

		//Flying hack
		if (GetAsyncKeyState('F') & 1) {
			flyFlag = !flyFlag;
			if (flyFlag) {
				cout << "Turn on the flying mode......" << endl;
				Chat(playerVftable, "Trun on the flying mode");
				patch(originalCode, (BYTE*)(pwnAventAddr + 0x8DB2D8), 7);
				nop((BYTE*)(pwnAventAddr + 0x8DB2D8), 7);
			}
			else {
				cout << "Turn off the flying mode......" << endl;
				Chat(playerVftable, "Turn off the flying mode");
				//Restore the original assembly code
				patch((BYTE*)(pwnAventAddr + 0x8DB2D8), originalCode, 7);
			}
		}
		if (flyFlag) {
			//Use the 'W' key to control the direction
			if (GetAsyncKeyState('W') & 1) {
				temp.x = (1 - 2 * (qua->y * qua->y + qua->z * qua->z));
				temp.y = (2 * (qua->x * qua->y + qua->w * qua->z));
				temp.z = (2 * (qua->x * qua->z - qua->w * qua->y));
				cameraPos->x += temp.x * speed;
				cameraPos->y += temp.y * speed;
				cameraPos->z += temp.z * speed;
			}
			if ((i % 50) == 0) {
				playerPos->x = cameraPos->x;
				playerPos->y = cameraPos->y;
				playerPos->z = cameraPos->z - 64.0f;
				i = 0;
			}  else  i++;
		}

		//Change position to designated place using key combination
		if (GetAsyncKeyState('G') & GetAsyncKeyState('1') & 0x8000) {
			Chat(playerVftable, "Teleport to Bear Chest !!!");
			teleport(-8034.0f,  64193.0f,  2642.0f);
		}
		if (GetAsyncKeyState('G') & GetAsyncKeyState('2') & 0x8000) {
			Chat(playerVftable, "Teleport to Gun Shop !!!");
			teleport(-37496.0f, -18540.0f, 2514.0f);
		}
		if (GetAsyncKeyState('G') & GetAsyncKeyState('3') & 0x8000) {
			Chat(playerVftable, "Teleport to Fireball !!!");
			teleport(-43644.0f, -56041.0f, 309.0f);
		}
		if (GetAsyncKeyState('G') & GetAsyncKeyState('4') & 0x8000) {
			Chat(playerVftable, "Teleport to Pirate Bay !!!");
			teleport(45796.0f, 58723.0f, 529.0f);
		}
		if (GetAsyncKeyState('G') & GetAsyncKeyState('5') & 0x8000) {
			Chat(playerVftable, "Teleport to Magma Boss !!!");
			teleport(54827.0f, -8199.0f, 1548.0f);
		}
		if (GetAsyncKeyState('G') & GetAsyncKeyState('6') & 0x8000) {
			Chat(playerVftable, "Teleport to Cow King !!!");
			teleport(260063.0f,  -249116.0f, 1495.0f);
		}
		if (GetAsyncKeyState('G') & GetAsyncKeyState('7') & 0x8000) {
			Chat(playerVftable, "Teleport to Fort Blox !!!");
			teleport(-2077.0f, 23190.0f, 2268.0f);
		}

		//Get weapons and ammunition
		if (GetAsyncKeyState('H') & 1) {
			cout << "Get weapons and ammunition" << endl;
			Chat(playerVftable, "Get weapons and ammunition");
			// uses games original getItemByName and addItem function, addresses for these functions found using IDA.
			getItems();
		}

		//Close the hacking
		if (GetAsyncKeyState(VK_F7) & 1)  break;
	}

	fclose(f);
	FreeConsole();
	FreeLibraryAndExitThread(hModule, 0);
	return 0;
}


BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	{
		CloseHandle(CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)MyThread, hModule, 0, nullptr));
	}
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:  break;
	}
	return TRUE;
}


