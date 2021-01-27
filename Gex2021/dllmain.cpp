// dllmain.cpp : Defines the entry point for the DLL application.
//////////////////////////////////////////////////////////////////////////////
//
//  Gex Function Detours
//
//  This DLL will detour the function in Gex we want to overwrite to understand more.
//  
//  To use, find the address of the function you want to overwrite in IDA.
//  Match the calling struction when making the pointer to the function.
//  Create a new function to replace the old function, matching the calling structure.
//  Add DetourAttach(&(PVOID&)pointer_to_old_function, new_function); after DetourUpdateThread.
//
#include "pch.h"
#include <stdio.h>
#include <Windows.h>
#include <Xinput.h>
#pragma comment(lib, "xinput.lib")
#include <string>
#include "detours.h"
#pragma comment(lib, "detours.lib")

#include "loguru.hpp"

#include <ddraw.h>
#include <sstream>
#include <vector>
#include <list>
#include <time.h>
#include <iostream>


// HOOK MACROS
#include "Globals.h"

// GAME LOOP HOOKS
#include "GameLoopHook.h"

GexVar::GexVar(const char* name, DWORD addr, DWORD sizeInBytes, bool isPointerType, bool isConstData)
{
}


bool LoggingStarted = false;


HANDLE currentprocessHandle;

// Write Process Memory Example
//BYTE dataOut[] = { 0x21 };
//DWORD dataOutSize = sizeof(dataOut);
//WriteProcessMemory(currentprocessHandle, (LPVOID)0x405143, dataOut, dataOutSize, NULL);

void PatchByteSingle(unsigned long addr, BYTE byte)
{
	//unsigned int len = length;

	unsigned long dwOldProt = 0;
	VirtualProtect((LPVOID)addr, 1, PAGE_EXECUTE_READWRITE, &dwOldProt);

	for (unsigned int i = 0; i < 1; i++)
		*(unsigned char*)(addr + i) = byte;
}

void PatchByteRepeat(unsigned long addr, unsigned int len, BYTE byte)
{
	//unsigned int len = length;

	unsigned long dwOldProt = 0;
	VirtualProtect((LPVOID)addr, len, PAGE_EXECUTE_READWRITE, &dwOldProt);

	for (unsigned int i = 0; i < len; i++)
		*(unsigned char*)(addr + i) = byte;
}

// Hook empty function with OutputDebugString output, must be captured via another program.
void WINAPI Console_Write(const char* format, ...)
{
	char bufferInternal[500];
	va_list args;
	va_start(args, format);
	vsprintf_s(bufferInternal, format, args);
	va_end(args);
	//std::string outputBuffer(bufferInternal);
	//DebugString += "\n";
	//OutputDebugStringA(bufferInternal);+
	strtok(bufferInternal, "\n");
	LOG_F(INFO, "%s", bufferInternal);
	AllocConsole();
	freopen("CONOUT$", "w", stdout);
	std::cout << bufferInternal << ".\n";
}

DWORD WINAPI NewHotkeysThread(LPVOID lpParameter)
{
	for (;;)
	{
		// If High bit is set, key is down
		/*if (GetAsyncKeyState(VK_F11) & (1 << 15))
		{
			DebugMenuBool = true;
		}*/
		/*else if ((GetAsyncKeyState(VK_F11) & (1 << 15)) == 0)
		{
			DebugMenuBool = false;
		}*/
		/*if (GetAsyncKeyState(VK_F11) & 0x0001)
		{
			// low bit is set.  Key just transitioned from released to pressed.
			DebugMenuBool = !DebugMenuBool;
		}*/

		// Debug String Vars
		// DAT_00455c54_DebugVar = 0;
		// DAT_004593c4_DebugVarUnk = 0;
		// DAT_00464278_ScriptDebugVar = 1;

		//DAT_00487bc0_VramWindowBool = 1;

		/// <MOD>
		/// Level Select
		/// </MOD>
		/// <description>
		/// Open Level Select when pressing '`'
		/// </description>
		/// <bytes>
		/// 0x455c3c | 0x0
		/// 0x45acc4 | 0x1
		/// 0x4a2a7c | 0x1
		/// </bytes>
		/// <length>
		/// 1
		/// 1
		/// 1
		/// </length>
		if (GetAsyncKeyState(VK_OEM_3)) {
			PatchByteSingle(0x455c3c, 0x0);
			PatchByteSingle(0x45acc4, 0x1);
			PatchByteSingle(0x4a2a7c, 0x1);
		}


		/// <MOD>
		/// Speed Modifier
		/// </MOD>
		/// <description>
		/// Speed up the game by holding '+'
		/// </description>
		/// <bytes>
		/// 0x405143 | 0x02 (High Speed)
		/// 0x405143 | 0x21 (Regular Speed)
		/// </bytes>
		/// <length>
		/// 1
		/// </length>
		if (GetAsyncKeyState(VK_ADD))
		{
			/*BYTE dataOut[] = { 0x02 };
			DWORD dataOutSize = sizeof(dataOut);

			WriteProcessMemory(currentprocessHandle, (LPVOID)0x405143, dataOut, dataOutSize, NULL);*/
			PatchByteSingle(0x405143, 0x2);
		}
		else
		{
			PatchByteSingle(0x405143, 0x21);
			/*BYTE dataOut[] = { 0x21 };
			DWORD dataOutSize = sizeof(dataOut);

			WriteProcessMemory(currentprocessHandle, (LPVOID)0x405143, dataOut, dataOutSize, NULL);*/
		}

	}
	return 0;
}

DWORD WINAPI XInputThread(LPVOID lpParameter)
{
	for (;;)
	{
		ZeroMemory(&state, sizeof(XINPUT_STATE));

		if (XInputGetState(0, &state) == ERROR_SUCCESS)
		{
			ControllerConnected = true;
		}
		else
		{
			ControllerConnected = false;
		}
	}
	return 0;
}


BOOL WINAPI DllMain(HINSTANCE hinst, DWORD dwReason, LPVOID reserved)
{
	//MessageBox(HWND_DESKTOP, L"Success!", L"Dll Injection", MB_OK);
	/////////////////////
	// Logging
	/////////////////////

	if (!LoggingStarted)
	{

		// Put every log message in "everything.log":
		loguru::add_file("debug.log", loguru::Append, loguru::Verbosity_MAX);
		// Only show most relevant things on stderr:
		loguru::g_stderr_verbosity = 9;


		// current date/time based on current system
		time_t now = time(0);

		// convert now to string form
		char* dt = ctime(&now);

		LOG_F(INFO, "Gex - %s", dt);

		LoggingStarted = true;

	}


	LONG error;
	(void)hinst;
	(void)reserved;

	if (DetourIsHelperProcess()) {
		return TRUE;
	}

	if (dwReason == DLL_PROCESS_ATTACH) {
		DetourRestoreAfterWith();
		DetourTransactionBegin();
		DetourUpdateThread(GetCurrentThread());

		currentprocessHandle = GetCurrentProcess();


		/// <MOD>
		/// Skip LOADER.EXE check.
		/// </MOD>
		/// <description>
		/// Patches out the check for LOADER.EXE
		/// </description>
		/// <bytes>
		/// 0x405EC0 | 0xEB
		/// </bytes>
		/// <length>
		/// 1
		/// </length>
		PatchByteSingle(0x405EC0, 0xEB);

		/// <MOD>
		/// Remove Help Menu
		/// </MOD>
		/// <description>
		/// Patches out F1 opening the help menu.
		/// </description>
		/// <bytes>
		/// 0x403CC6 | 0x90 (NOP) * 42
		/// </bytes>
		/// <length>
		/// 42
		/// </length>
		PatchByteRepeat(0x403CC6, 42, 0x90);

		/// <MOD>
		/// Remove Full Screen Toggle
		/// </MOD>
		/// <description>
		/// Patches out F4 toggling full screen.
		/// </description>
		/// <bytes>
		/// 0x403D91 | 0x90 (NOP) * 3
		/// 0x403D94 | 0xe9,0xa4,0x00,0x00,0x00,0x90
		/// </bytes>
		/// <length>
		/// 3
		/// 6
		/// </length>
		PatchByteRepeat(0x403D91, 3, 0x90);
		BYTE SKIP_F4[] = { 0xE9,0xA4,0x00,0x00,0x00,0x90 };
		WriteProcessMemory(currentprocessHandle, (LPVOID)0x403D94, SKIP_F4, sizeof(SKIP_F4), NULL);

		// F5 - Set Width and Height to 0x140,0xe0, rep with 0x280,0x1c0
		BYTE PATCH_F5[] = { 0xc0,0x01 };
		WriteProcessMemory(currentprocessHandle, (LPVOID)0x403e43, PATCH_F5, sizeof(PATCH_F5), NULL);
		BYTE PATCH_F5_2[] = { 0x80,0x02 };
		WriteProcessMemory(currentprocessHandle, (LPVOID)0x403e48, PATCH_F5_2, sizeof(PATCH_F5_2), NULL);

		// F6 - Set Width and Height to 0x280,0x1c0, rep with 0x500,0x380
		BYTE PATCH_F6[] = { 0x80,0x03 };
		WriteProcessMemory(currentprocessHandle, (LPVOID)0x403e65, PATCH_F6, sizeof(PATCH_F6), NULL);
		BYTE PATCH_F6_2[] = { 0x00,0x05 };
		WriteProcessMemory(currentprocessHandle, (LPVOID)0x403e6a, PATCH_F6_2, sizeof(PATCH_F6_2), NULL);

		unsigned int lpParameterHotKeys = 0;
		CreateThread(NULL, 0, NewHotkeysThread, &lpParameterHotKeys, 0, NULL);

		/// <MOD>
		/// Skip Intro Video
		/// </MOD>
		/// <description>
		/// Sets Variables to skip the Intro Video
		/// </description>
		/// <bytes>
		/// 0x4a2970 | 0x2
		/// 0x4a2a80 | 0x1
		/// </bytes>
		/// <length>
		/// 1
		/// 1
		/// </length>
		PatchByteSingle(0x4a2970, 0x2);
		PatchByteSingle(0x4a2a80, 0x1);
		//DAT_004a2970_IntroSwitchCase = 2;
		//DAT_004a2a80_ResetGame = 1;

		//GEX_ATTACH(MAIN_GAME_LOOP);
		GEX_ATTACH(FUN_0040f7a0_MainGameInput);


		// XInput

		/*XINPUT_STATE state;
		ZeroMemory(&state, sizeof(XINPUT_STATE));

		if (XInputGetState(0, &state) == ERROR_SUCCESS)
		{
			// controller is connected on port 0
			Console_Write("Controller connected on port 0.");*/
		unsigned int lpParameterXInput = 0;
		//CreateThread(NULL, 0, XInputThread, &lpParameterXInput, 0, NULL);
		/*}
		else
		{
			Console_Write("Controller Not Found.");
		}*/


		error = DetourTransactionCommit();

		if (error == NO_ERROR) {
			//MessageBox(HWND_DESKTOP, L"Success!", L"Dll Injection", MB_OK);
		}
		else {
			//MessageBox(HWND_DESKTOP, L"Error detouring!", L"Dll Injection", MB_OK);
		}
	}
	else if (dwReason == DLL_PROCESS_DETACH) {
		DetourTransactionBegin();
		DetourUpdateThread(GetCurrentThread());


		error = DetourTransactionCommit();
	}
	return TRUE;
}