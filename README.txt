DLL Injection Program
Platform: Visual Studio
Game: Pwn Adventure 3

The Pwn3.dll(x86) file is in the Debug directory, and it can be used for DLL injection.

1. The testing is conducted in Offline Play, and the dll file should be injected after the player
enters the game world.

2. All the hacking modes have been listed in the console window after injection, and just press
the corresponding key to turn on/off the hacking mode.

3. If the injection wants to be closed, all the hacking modes listed in the console should
be turned off first to restore the original bytes before pressing 'F7' key to end the injection. 

4. The bear hack needs to be activated in advance before teleporting to the bear chest to avoid crashing the game

The main structure of the code is divided into the following sections:

dllmain.cpp  ------  The main file that includes the dll entry function and thread function
		containing the loop to detect all hacking modes

hackFunc.cpp  ------  Definitions of all the functions that implement our hacking based
	                   on the hook technique and memory operations

originalFunc.cpp  ------  Original variables and functions related to the source code 

mem.cpp  ------  Functions related to the hook technique and memory operations





