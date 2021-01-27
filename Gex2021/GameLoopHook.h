#pragma once

#include "Globals.h"

/// <MOD>
/// Hook Main Render Loop
/// </MOD>
/// <description>
/// Replace the main render loop with our own and render a text overlay menu.
/// </description>
/// <variables>
/// 
/// </variables>
/// <functions>
/// 0x40a010 | MAIN_GAME_LOOP
/// </functions>



/*
typedef LRESULT(__cdecl* FUN_0040ef40_SomethingGameObjectsProcessingUnk_Def)(GexPlayerStruct* param_1);
FUN_0040ef40_SomethingGameObjectsProcessingUnk_Def FUN_0040ef40_SomethingGameObjectsProcessingUnk = (FUN_0040ef40_SomethingGameObjectsProcessingUnk_Def)0x40ef40;

typedef LRESULT(__cdecl* FUN_0040efa0_GraphicFunctions_Def)(GexPlayerStruct* param_1);
FUN_0040efa0_GraphicFunctions_Def FUN_0040efa0_GraphicFunctions = (FUN_0040efa0_GraphicFunctions_Def)0x40efa0;
*/

bool customDebug = false;

void PrintDebugTextOnScreen(int x, int y, const char* string)
{
	FUN_0043fa70_DrawText(0x80000 + (0x80000 * x), 0xC0000 + (0x80000 * y), (char*)string);
}

void PrintDebugTextOnScreenF(int x, int y, const char* format, ...)
{
	char bufferInternal[500];
	va_list args;
	va_start(args, format);
	vsprintf_s(bufferInternal, format, args);
	va_end(args);
	FUN_0043fa70_DrawText(0x80000 + (0x80000 * x), 0xC0000 + (0x80000 * y), (char*)bufferInternal);
}



undefined4 __cdecl FUN_0040f7a0_MainGameInput(int param_1, undefined4 param_2, uint* CurrentInputPTR)

{
	//return f_FUN_0040f7a0_MainGameInput(param_1, param_2, CurrentInputPTR);
	uint KeyInput;

	KeyInput = FUN_00404ba0_ReturnKeyPressInput_TRUEINPUT();

	ZeroMemory(&state, sizeof(XINPUT_STATE));
	if (XInputGetState(0, &state) == ERROR_SUCCESS)
	{
		ControllerConnected = true;
	}
		/*
		PrintDebugTextOnScreen(0, y++, "Controller connected on port 0.");
		PrintDebugTextOnScreenF(0, y++, "A: %d", ((state.Gamepad.wButtons & XINPUT_GAMEPAD_A) != 0));
		PrintDebugTextOnScreenF(0, y++, "B: %d", ((state.Gamepad.wButtons & XINPUT_GAMEPAD_B) != 0));
		PrintDebugTextOnScreenF(0, y++, "X: %d", ((state.Gamepad.wButtons & XINPUT_GAMEPAD_X) != 0));
		PrintDebugTextOnScreenF(0, y++, "Y: %d", ((state.Gamepad.wButtons & XINPUT_GAMEPAD_Y) != 0));
		PrintDebugTextOnScreenF(0, y++, "LB: %d", ((state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) != 0));
		PrintDebugTextOnScreenF(0, y++, "LT: %f", (float)state.Gamepad.bLeftTrigger / 255);
		PrintDebugTextOnScreenF(0, y++, "RB: %d", ((state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) != 0));
		PrintDebugTextOnScreenF(0, y++, "RT: %f", (float)state.Gamepad.bRightTrigger / 255);
		PrintDebugTextOnScreenF(0, y++, "U: %d", ((state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP) != 0));
		PrintDebugTextOnScreenF(0, y++, "D: %d", ((state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN) != 0));
		PrintDebugTextOnScreenF(0, y++, "L: %d", ((state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT) != 0));
		PrintDebugTextOnScreenF(0, y++, "R: %d", ((state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) != 0));

		PrintDebugTextOnScreenF(0, y++, "Tail Whip: %d", ((DAT_004a27e0_CurrentKey >> 1) & 0x1));
		PrintDebugTextOnScreenF(0, y++, "Jump: %d", ((DAT_004a27e0_CurrentKey >> 2) & 0x1));
		PrintDebugTextOnScreenF(0, y++, "Tongue: %d", ((DAT_004a27e0_CurrentKey >> 3) & 0x1));
		PrintDebugTextOnScreenF(0, y++, "Left: %d", ((DAT_004a27e0_CurrentKey >> 4) & 0x1));
		PrintDebugTextOnScreenF(0, y++, "Right: %d", ((DAT_004a27e0_CurrentKey >> 5) & 0x1));
		PrintDebugTextOnScreenF(0, y++, "Up: %d", ((DAT_004a27e0_CurrentKey >> 6) & 0x1));
		PrintDebugTextOnScreenF(0, y++, "Down: %d", ((DAT_004a27e0_CurrentKey >> 7) & 0x1));
		PrintDebugTextOnScreenF(0, y++, "Run: %d", ((DAT_004a27e0_CurrentKey_ >> 5) & 0x1));
		*/



	DAT_004a27e0_MainGame_NextKeyInput = 0;
	// Start Directional Input
	// UP
	if (((KeyInput & 0x1000) != 0) || ((state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP))) {
		DAT_004a27e0_MainGame_NextKeyInput = 0x40000000;
	}
	// DOWN
	if ((KeyInput & 0x4000) != 0 || ((state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN))) {
		DAT_004a27e0_MainGame_NextKeyInput = DAT_004a27e0_MainGame_NextKeyInput | 0x80000000;
	}
	// LEFT
	if ((KeyInput & 0x8000) != 0 || ((state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT))) {
		DAT_004a27e0_MainGame_NextKeyInput = DAT_004a27e0_MainGame_NextKeyInput | 0x10000000;
	}
	// RIGHT
	if ((KeyInput & 0x2000) != 0 || ((state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT))) {
		DAT_004a27e0_MainGame_NextKeyInput = DAT_004a27e0_MainGame_NextKeyInput | 0x20000000;
	}
	// End Directional Input
	// TONGUE
	if ((KeyInput & 0x80) != 0 || ((state.Gamepad.wButtons & XINPUT_GAMEPAD_X))) {
		DAT_004a27e0_MainGame_NextKeyInput = DAT_004a27e0_MainGame_NextKeyInput | 0x8000000;
	}
	// JUMP
	if ((KeyInput & 0x40) != 0 || ((state.Gamepad.wButtons & XINPUT_GAMEPAD_A))) {
		DAT_004a27e0_MainGame_NextKeyInput = DAT_004a27e0_MainGame_NextKeyInput | 0x4000000;
	}
	// UNKNOWN
	if ((KeyInput & 0x10) != 0) {
		DAT_004a27e0_MainGame_NextKeyInput = DAT_004a27e0_MainGame_NextKeyInput | 0x100000;
	}
	// TAILWHIP
	if ((KeyInput & 0x20) != 0 || ((state.Gamepad.wButtons & XINPUT_GAMEPAD_B))) {
		DAT_004a27e0_MainGame_NextKeyInput = DAT_004a27e0_MainGame_NextKeyInput | 0x2000000;
	}
	// UNKNOWN
	if ((KeyInput & 0x800) != 0) {
		DAT_004a27e0_MainGame_NextKeyInput = DAT_004a27e0_MainGame_NextKeyInput | 0x1000000;
	}
	// UNKNOWN
	if ((KeyInput & 0x100) != 0) {
		DAT_004a27e0_MainGame_NextKeyInput = DAT_004a27e0_MainGame_NextKeyInput | 0x800000;
	}
	// UNKNOWN
	if ((KeyInput & 8) != 0) {
		DAT_004a27e0_MainGame_NextKeyInput = DAT_004a27e0_MainGame_NextKeyInput | 0x400000;
	}
	// RUN
	if ((KeyInput & 4) != 0 || ((state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER)) || ((state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER))) {
		DAT_004a27e0_MainGame_NextKeyInput = DAT_004a27e0_MainGame_NextKeyInput | 0x200000;
	}
	// UNKNOWN
	if ((KeyInput & 2) != 0) {
		DAT_004a27e0_MainGame_NextKeyInput = DAT_004a27e0_MainGame_NextKeyInput | 0x80000;
	}
	// UNKNOWN
	if ((KeyInput & 1) != 0) {
		DAT_004a27e0_MainGame_NextKeyInput = DAT_004a27e0_MainGame_NextKeyInput | 0x40000;
	}
	DAT_004a27d8_MainGame_KeyInput = DAT_004a27d8_MainGame_KeyInput | DAT_004a27e0_MainGame_NextKeyInput;
	if (1 < param_1) {
		*CurrentInputPTR = 0;
		return 1;
	}
	*CurrentInputPTR = DAT_004a27e0_MainGame_NextKeyInput;
	return 1;
}



int __cdecl MAIN_GAME_LOOP(GexTileStruct param_1)
{

	/*if (!SDLInitialised)
	{
		graphics = Graphics();
		graphics.SDL_Initialise(640, 240);
		SDLInitialised = true;

	}
	if (SDLInitialised)
	{
		graphics.SDL_Test();
	}*/


	/*if (GetAsyncKeyState(0x51) & 0x0001) // Q
	{
			// sofakingdom - Turn on all TVs in current map
		while (SelectTV1 = pointer_FUN_00429c60_RemoteTVSelect_Unk(0xdc), SelectTV1 != (GexPlayerStruct*)0x0) {
			if (-1 < SelectTV1->field_0x9c_gob_work1) {
				pbVar1 = (byte*)((int)&DAT_004a2540_RemoteUnk2 + SelectTV1->field_0x9c_gob_work1);
				*pbVar1 = *pbVar1 | 1;
			}
			SelectTV1->field_0x8_objectype = -1;
		}
		while (SelectTV2 = pointer_FUN_00429c60_RemoteTVSelect_Unk(-1), SelectTV2 != (GexPlayerStruct*)0x0) {
			SelectTV2->field_0x8_objectype = 0xdc;
		}
	}*/



	astruct_MainObjects** ppaVar1;
	int yPos;
	int tempInt;
	GexTileStruct* pGVar2;


	DAT_004a2990_BlockAnims = param_1.handle_0x0_BlockAnims;
	if ((DAT_004626f4_InitialiseLevel != 0) && (DAT_004626f4_InitialiseLevel = 0, DAT_004a2948 != 1)) {
		FUN_0043f490_GameInitUnk(8, 0, 0xff, 0, 0xff, 0, 0xff);
	}
	if (DAT_004a2a8c_ResetGame != NULL) {
		if ((DAT_004a2958_ToggleVoicesInMainGame == 0) && ((DAT_004a2964_LEV_Value_Start < 63 || (69 < DAT_004a2964_LEV_Value_Start)))) {
			DAT_004a2964_LEV_Value_Start = 0x3f;
			DAT_004a2a7c_Process_Level_Change = 1;
		}
		else {
			DAT_004a2a8c_ResetGame = NULL;
		}
	}

	FUN_0041fc40_KeyInput_Outer();
	if (DAT_004a2958_ToggleVoicesInMainGame == 0) {
		FUN_0041faf0_VoiceRelated();
	}

	/*if (ToggleCamera)
	{
		DAT_004a2a38_CameraX_TrueCam = xOffset;
		DAT_004a2a1c_CameraY_TrueCam = yOffset;
		if (GetAsyncKeyState(VK_NUMPAD8)) yOffset -= 0x100000; // Up
		if (GetAsyncKeyState(VK_NUMPAD2)) yOffset += 0x100000; // Down
		if (GetAsyncKeyState(VK_NUMPAD4)) xOffset -= 0x100000; // Left
		if (GetAsyncKeyState(VK_NUMPAD6)) xOffset += 0x100000; // Right
	}

	if (GetAsyncKeyState(VK_DIVIDE) & 0x0001)
	{
		ToggleCamera = !ToggleCamera;
		if (ToggleCamera)
		{
			xOffset = DAT_004a2a38_CameraX_TrueCam;
			yOffset = DAT_004a2a1c_CameraY_TrueCam;
		}
	}

	if (GetAsyncKeyState(VK_SUBTRACT) & 0x0001)
	{
		pointer_FUN_0041a360_Sound(0x40 + soundCount, 0xFF);
		soundCount++;
	}*/

	// missing
	tempInt = 0;

	if (((DAT_00455c4c_Pause_Game_On_Collision == 0) && (DAT_004a2ad0_Objects == 0)) && (0 < DAT_004626fc_Objects)) {
		yPos = 0;
		do {


			ppaVar1 = (astruct_MainObjects**)(DAT_004a2a78_ObjectsInner + yPos);
			yPos = yPos + 4;
			tempInt = tempInt + 1;
			FUN_0040f910_SpawnObjects(*ppaVar1, DAT_004a2a38_CameraX_TrueCam, DAT_004a2a1c_CameraY_TrueCam, 0);

		} while (tempInt < DAT_004626fc_Objects);
	}



	if (DAT_004a288c_ProcessBlockAnimations == 0) {
		// ProcessBlockAnims
		//FUN_00405390_EmptyStringDebugFunction(s_ProcessBlockAnims_00455e14);
		FUN_0041f710_ProcessBlockAnims(DAT_004a2990_BlockAnims);
		// ProcessTileAnims
		//FUN_00405390_EmptyStringDebugFunction(s_ProcessTileAnims_00455e00);
		FUN_0041f7a0_ProcessTileAnims();
	}

	//FUN_00405390_EmptyStringDebugFunction(s_Process_Objects_00455dec);
	FUN_00409f00_ProcessCheatWords();

	void(__cdecl * v4)(GexPlayerStruct*) = 0; // esi
	void(__cdecl * v13)(unsigned int*);

	if (DAT_00455c4c_Pause_Game_On_Collision == 0) {

		/*if (!GetAsyncKeyState(0x31))*/ (*PTR_FUN_00458ed4_GameObjectProcess_Unk)(DAT_004a28a0_GameObjectUnkDrawBackground);
		/*if (!GetAsyncKeyState(0x32))*/ (*PTR_FUN_00458ed4_GameObjectProcess_Unk)(DAT_004a28ac_GameObjectUnkDrawBackgroundObjects);
		/*if (!GetAsyncKeyState(0x33))*/ (*PTR_FUN_00458ed4_GameObjectProcess_Unk)(DAT_004a28b8_GameObjectUnk3_StaticBehindGex);
		/*if (!GetAsyncKeyState(0x34))*/ (*PTR_FUN_00458ed4_GameObjectProcess_Unk)(DAT_004a28c4_GameObjectUnk4_DrawGexAndTitle);
		/*if (!GetAsyncKeyState(0x35))*/ (*PTR_FUN_00458ed4_GameObjectProcess_Unk)(DAT_004a28d0_GameObjectUnk5_DrawTitleStartText); // Stop gex moving
		/*if (!GetAsyncKeyState(0x36))*/ (*PTR_FUN_00458ed4_GameObjectProcess_Unk)(DAT_004a28dc_GameObjectUnk6_Enemies);
		/*if (!GetAsyncKeyState(0x37))*/ (*PTR_FUN_00458ed4_GameObjectProcess_Unk)(DAT_004a28e8_GameObjectUnk7_Obstacles);
		/*if (!GetAsyncKeyState(0x38))*/ (*PTR_FUN_00458ed4_GameObjectProcess_Unk)(DAT_004a28f4_GameObjectUnk8);
		/*if (!GetAsyncKeyState(0x39))*/ (*PTR_FUN_00458ed4_GameObjectProcess_Unk)(DAT_004a2900_GameObjectUnk9);
		// Process Collisions
		FUN_0041e5c0_ProcessCollisions();
		// Set Scroll Position
		FUN_00410280_SetScrollPosition_ScrollScreen();
		/*if (!GetAsyncKeyState(0x30))*/ (*PTR_FUN_00458ed4_GameObjectProcess_Unk)(DAT_004a290c_GameObjectUnk10);
		FUN_00410c60_CameraFollowGex();
	}





	int v5;
	int v6;

	DAT_004a2a96_CameraX = HIWORD(DAT_004a2974_CameraX_TrueCam2);
	DAT_004a2a94_CameraY = HIWORD(DAT_004a2988_CameraY_TrueCam2);
	DAT_004a2974_CameraX_TrueCam2 = DAT_004a2a38_CameraX_TrueCam & 0xFFFF0000;
	DAT_004a2988_CameraY_TrueCam2 = DAT_004a2a1c_CameraY_TrueCam & 0xFFFF0000;
	if ((DAT_004a2a38_CameraX_TrueCam & 0xFFFF0000 & 0x80000000) != 0)
		DAT_004a2974_CameraX_TrueCam2 = 0;
	if ((int)DAT_004a2974_CameraX_TrueCam2 < 0) {
		DAT_004a2974_CameraX_TrueCam2 = 0;
	}
	if ((int)DAT_004a2988_CameraY_TrueCam2 < 0) {
		DAT_004a2988_CameraY_TrueCam2 = 0x0;
	}
	pGVar2 = DAT_004a2990_BlockAnims->f_0x4_CurrentTileMaybe->f_0x4_CurrentTileMaybe;
	if ((int)&pGVar2[-0x8e38f].field_0x1c_ptr <= (int)DAT_004a2974_CameraX_TrueCam2) {
		DAT_004a2974_CameraX_TrueCam2 = (uint)&pGVar2[-0x8eaab].f_0xc;
	}
	pGVar2 = DAT_004a2990_BlockAnims->f_0x4_CurrentTileMaybe->f_0x8_NextTileMaybe;
	if ((int)&pGVar2[-0x6aaab].f_0xc <= (int)DAT_004a2988_CameraY_TrueCam2) {
		DAT_004a2988_CameraY_TrueCam2 = pGVar2[-0x6b1c8].field_0x20_gTiles;
	}
	DAT_004a2a96_CameraX = ((DAT_004a2974_CameraX_TrueCam2 >> 16) - DAT_004a2a96_CameraX) / 2;
	DAT_004a2a94_CameraY = ((DAT_004a2988_CameraY_TrueCam2 >> 16) - DAT_004a2a94_CameraY) / 2;

	if (DAT_004a2abc_EnableParallaxBackground != 0) {
		// nopping if misaligns background
		// nopping first assignment stops parallax background
		DAT_004a293c_CameraX = DAT_004a2974_CameraX_TrueCam2;
		DAT_004a2978_CameraY = DAT_004a2988_CameraY_TrueCam2;
	}


	if ((DAT_004a2a24_DrawGraphics != 0) && (DAT_004a288c_ProcessBlockAnimations == 0)) {
		(*_PTR_FUN_DrawObjects_00458ed8)(DAT_004a28a0_GameObjectUnkDrawBackground);
		(*_PTR_FUN_DrawObjects_00458ed8)(DAT_004a28ac_GameObjectUnkDrawBackgroundObjects);
	}
	__DAT_004a2ae8_TileData = DAT_004a2990_BlockAnims->field_0x14_TileData;
	//FUN_00405390_EmptyStringDebugFunction(s_Draw_Tiles_00455db4);
	// Draw Tiles
	if ((DAT_004a2a20_ObjectsLeftToGetReady == 0) && (DAT_004a288c_ProcessBlockAnimations == 0)) {
		// Nopping crashes
		FUN_0043fb40_DrawObjectsMidOuter_TrueDraw
		((TilePTRStruct*)DAT_004a2990_BlockAnims->f_0x4_CurrentTileMaybe, (GexTileStruct*)DAT_004a2990_BlockAnims->field_0x20_gTiles,
			DAT_004a2974_CameraX_TrueCam2, (uint)DAT_004a2988_CameraY_TrueCam2);
		FUN_00440510_DrawObjectsMid();
	}
	//FUN_00405390_EmptyStringDebugFunction(s_Draw_Objects_Mid_00455da0);
	// Draw Objects Mid
	if ((DAT_004a2a24_DrawGraphics != 0) && (DAT_004a288c_ProcessBlockAnimations == 0)) {
		//Message("0x%x", &DAT_004a28b8_GameObjectUnk3_StaticBehindGex[24]);
		(*_PTR_FUN_DrawObjects_00458ed8)(DAT_004a28b8_GameObjectUnk3_StaticBehindGex);
		(*_PTR_FUN_DrawObjects_00458ed8)(DAT_004a28c4_GameObjectUnk4_DrawGexAndTitle);
		(*_PTR_FUN_DrawObjects_00458ed8)(DAT_004a28d0_GameObjectUnk5_DrawTitleStartText);
		(*_PTR_FUN_DrawObjects_00458ed8)(DAT_004a28dc_GameObjectUnk6_Enemies);
		(*_PTR_FUN_DrawObjects_00458ed8)(DAT_004a28e8_GameObjectUnk7_Obstacles);
		(*_PTR_FUN_DrawObjects_00458ed8)(DAT_004a28f4_GameObjectUnk8);
	}
	if ((DAT_004a2a20_ObjectsLeftToGetReady == 0) && (DAT_004a288c_ProcessBlockAnimations == 0)) {
		FUN_00440560_DrawObjectsHigh_InFrontOfGex();
	}

	/*char TitleScreenText[100];
	sprintf(TitleScreenText, "Level: %d", DAT_004a2964_LEV_Value_Start);
	FUN_0043fa70_DrawText(0x80000, 0xF0000, (char*)TitleScreenText);*/

	/*char CallText[100];
	sprintf(CallText, "CallList: %d", callList.size());
	FUN_0043fa70_DrawText(0x80000, 0xC0000, (char*)CallText);*/

	/*int i = 0;
	if (!(std::count(callList.begin(), callList.end(), CallText)))
	{
		FUN_0043fa70_DrawText(0x80000, 0xC0000+(0x2000*i), (char*)CallText);
		i++;
	}*/
	/*int count = 0;
	if (GetAsyncKeyState(0x57)) // W
	{
		// sofakingdom - Turn on all TVs in current map


		while (SelectTV1 = pointer_FUN_00429c60_RemoteTVSelect_Unk(0xdc), SelectTV1 != (GexPlayerStruct*)0x0) {
			if (-1 < SelectTV1->field_0x9c_gob_work1) {
				pbVar1 = (byte*)((int)&DAT_004a2540_RemoteUnk2 + SelectTV1->field_0x9c_gob_work1);
				char buffer[100];
				sprintf_s(buffer, "TV:%x count:%d", *pbVar1, count);
				FUN_0043fa70_DrawText(0x80000, 0xC0000 + (0x80000 * count), (char*)buffer);
				count++;

			}
			SelectTV1->field_0x8_objectype = -1;
		}
		while (SelectTV2 = pointer_FUN_00429c60_RemoteTVSelect_Unk(-1), SelectTV2 != (GexPlayerStruct*)0x0) {
			SelectTV2->field_0x8_objectype = 0xdc;
		}

	}*/


	/*if (customDebug)
	{
		DebugMenuOverlay();
	}*/

	if (GetAsyncKeyState(VK_F1) & 0x0001)
	{
		customDebug = !customDebug;
	}


	/*char CameraPos[100];
	sprintf(CameraPos, "Camera: [%x,%x]: %d", DAT_004a2a38_CameraX_TrueCam, DAT_004a2a1c_CameraY_TrueCam, ToggleCamera);
	FUN_0043fa70_DrawText(0x80000, 0x120000, (char*)CameraPos);*/



	//FUN_00405390_EmptyStringDebugFunction(s_Draw_Objects_Hi_00455d8c);
	// Draw Objects High
	if ((DAT_004a2a24_DrawGraphics != 0) && (DAT_004a288c_ProcessBlockAnimations == 0)) {
		(*_PTR_FUN_DrawObjects_00458ed8)(DAT_004a2900_GameObjectUnk9);
		(*_PTR_FUN_DrawObjects_00458ed8)(DAT_004a290c_GameObjectUnk10);
	}
	// nopping does nothing
	FUN_00410250_Camera_unk();
	if ((DAT_004a27fc_GexPlayerObject != (GexPlayerStruct*)0x0) && (DAT_004a2960_PausedUnk == 0)) {
		FUN_00417d90_COLLISIONS();
	}
	if (((DAT_00455c4c_Pause_Game_On_Collision != 0) && (DAT_004a2960_PausedUnk == 0)) &&
		(DAT_004a288c_ProcessBlockAnimations != 0)) {
		// nopping function makes word pause disappear
		FUN_0041bfc0_MakesWordPauseAppear_ProcessCheats(DAT_004a27fc_GexPlayerObject);
	}

	/*if (DAT_004a02fc_gTiles_start)
	{

		for (int i = 0; i < 20; i++)
		{
			char CallText[100];
			sprintf(CallText, "%08x", *(&DAT_004a02fc_gTiles_start + (i * 3)));
			FUN_0043fa70_DrawText(0x80000, 0xC0000 + (0x80000 * i), (char*)CallText);
		}
	}*/

	/// Controller Debug Output
	//if(ControllerConnected)
	//{
		/*char ControllerMessage[100];
		sprintf(ControllerMessage, "Controller connected on port 0.");
		FUN_0043fa70_DrawText(0x80000, 0xC0000 + (0x80000), (char*)ControllerMessage);

		bool A_button_pressed = ((state.Gamepad.wButtons & XINPUT_GAMEPAD_A) != 0);

		*/
		/*int y = 0;
		ZeroMemory(&state, sizeof(XINPUT_STATE));
		if (XInputGetState(0, &state) == ERROR_SUCCESS)
		{
			ControllerConnected = true;

			PrintDebugTextOnScreen(0, y++, "Controller connected on port 0.");
			PrintDebugTextOnScreenF(0, y++, "A: %d", ((state.Gamepad.wButtons & XINPUT_GAMEPAD_A) != 0));
			PrintDebugTextOnScreenF(0, y++, "B: %d", ((state.Gamepad.wButtons & XINPUT_GAMEPAD_B) != 0));
			PrintDebugTextOnScreenF(0, y++, "X: %d", ((state.Gamepad.wButtons & XINPUT_GAMEPAD_X) != 0));
			PrintDebugTextOnScreenF(0, y++, "Y: %d", ((state.Gamepad.wButtons & XINPUT_GAMEPAD_Y) != 0));
			PrintDebugTextOnScreenF(0, y++, "LB: %d", ((state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) != 0));
			PrintDebugTextOnScreenF(0, y++, "LT: %f", (float)state.Gamepad.bLeftTrigger / 255);
			PrintDebugTextOnScreenF(0, y++, "RB: %d", ((state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) != 0));
			PrintDebugTextOnScreenF(0, y++, "RT: %f", (float)state.Gamepad.bRightTrigger / 255);
			PrintDebugTextOnScreenF(0, y++, "U: %d", ((state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP) != 0));
			PrintDebugTextOnScreenF(0, y++, "D: %d", ((state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN) != 0));
			PrintDebugTextOnScreenF(0, y++, "L: %d", ((state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT) != 0));
			PrintDebugTextOnScreenF(0, y++, "R: %d", ((state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) != 0));

			PrintDebugTextOnScreenF(0, y++, "Tail Whip: %d", ((DAT_004a27e0_CurrentKey >> 1) & 0x1));
			PrintDebugTextOnScreenF(0, y++, "Jump: %d", ((DAT_004a27e0_CurrentKey >> 2) & 0x1));
			PrintDebugTextOnScreenF(0, y++, "Tongue: %d", ((DAT_004a27e0_CurrentKey >> 3) & 0x1));
			PrintDebugTextOnScreenF(0, y++, "Left: %d", ((DAT_004a27e0_CurrentKey >> 4) & 0x1));
			PrintDebugTextOnScreenF(0, y++, "Right: %d", ((DAT_004a27e0_CurrentKey >> 5) & 0x1));
			PrintDebugTextOnScreenF(0, y++, "Up: %d", ((DAT_004a27e0_CurrentKey >> 6) & 0x1));
			PrintDebugTextOnScreenF(0, y++, "Down: %d", ((DAT_004a27e0_CurrentKey >> 7) & 0x1));
			PrintDebugTextOnScreenF(0, y++, "Run: %d", ((DAT_004a27e0_CurrentKey_ >> 5) & 0x1));

			// IF (A) PRESSED

			if (((state.Gamepad.wButtons & XINPUT_GAMEPAD_A) != 0))
			{
				DAT_004a27e0_CurrentKey = 0x04;
			}

			//PatchByteSingle(0x4a0280, 0x01);

		}
		else
		{
			ControllerConnected = false;
		}*/
		

	//}

	//int count = 0;
	/*for (auto itr : callList)
	{
		char CallText[100];
		sprintf(CallText, "Call: %x", itr);
		FUN_0043fa70_DrawText(0x80000, 0xC0000 + (0x80000 * count), (char*)CallText);
		count++;
	}*/
	/*for (auto itr : callList2)
	{
		char CallText2[100];
		sprintf(CallText2, "Call2: %x", itr);
		FUN_0043fa70_DrawText(0x80000, 0xC0000 + (0x80000 * count), (char*)CallText2);
		count++;
	}

	FUN_0043fa70_DrawText(0x180000, 0x120000, (char*)DrawText1);
	*/
	_DAT_004626ec = FUN_00402fa0_ret_timeSetEventUnk2();

	FUN_0043f310_InitVarsRelatedUnk();
	uint gameRunning = FUN_00405120_WaitTicks();
	gameRunning = gameRunning | DAT_004a294c_FreezeGame;
	// nopping stops graphics
	FUN_0043db70_DEBUGTHISGRAPHICS(gameRunning);
	// Paused
	if (DAT_004a294c_FreezeGame == 1) {
		FUN_004053a0_SaveScreenshotAndPauseGame();
		DAT_004a294c_FreezeGame = DAT_004a294c_FreezeGame + 1;
	}
	// nopping stops unpausing game
	FUN_0043f2d0_CheckF3ForUnpauseGameDrawWindow(gameRunning);
	FUN_0040b2d0_InputProcessing();
	if (DAT_00455c48 == 0) {
		FUN_0043db50();
	}
	if (DAT_00455c4c_Pause_Game_On_Collision == 0) {
		// Increment Frame
		DAT_004a2ac8_FrameCount = DAT_004a2ac8_FrameCount + 1;
	}
	FUN_00409970_BetweenLevelsTVFuzz();
	if (((DAT_004a2958_ToggleVoicesInMainGame == 0) && (DAT_004a2a0c_DemoMode != 0)) &&
		((tempInt = FUN_0040f400_CallKeyInputFunction_ProcessKeyInput(0), tempInt != 0 ||
			(*(int*)(DAT_004a27dc_KeyInput + 0xc) == 0)))) {
		DAT_004a2964_LEV_Value_Start = 0x3f;
		DAT_004a2a7c_Process_Level_Change = 1;
	}

	if (((DAT_004a2a3c != 0)
		|| (DAT_004a2a98_LEV_Related_End == DAT_004a2964_LEV_Value_Start))
		&& (DAT_00455c3c_GameTypeSwitchCase == DAT_004626f0_GameTypeSwitchCase))
	{
		//callList.clear();
		return 1;
	}
	return 0;

}
