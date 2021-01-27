#pragma once

typedef unsigned char   undefined;
typedef unsigned int    ImageBaseOffset32;
typedef unsigned char    byte;
typedef unsigned int    dword;
typedef unsigned char    uchar;
typedef unsigned int    uint;
typedef unsigned long    ulong;
typedef unsigned long long    ulonglong;
typedef unsigned char    undefined1;
typedef unsigned short    undefined2;
typedef unsigned int    undefined4;
typedef unsigned long long    undefined6;
typedef unsigned long long    undefined8;
typedef unsigned short    ushort;
typedef unsigned short    word;

struct TVarInfo
{
    DWORD mAddr;
    DWORD mSize;
    bool mIsPointerType;
    bool mIsConstData;
    const char* mName;
};

bool RunningAsInjectedDll()
{
    return true;
}


class GexVar
{
public:
    GexVar(const char* name, DWORD addr, DWORD sizeInBytes, bool isDynamicallyAllocated, bool isConstData);
};

#define GEX_VAR_EXTERN(TypeName, VarName)\
extern TypeName LocalVar_##VarName;\
extern TypeName& VarName;

#define GEX_VAR(Redirect, Addr, TypeName, VarName, Value)\
TypeName LocalVar_##VarName = Value;\
GexVar Var_##VarName(#VarName, Addr, sizeof(LocalVar_##VarName), std::is_pointer<TypeName>::value, std::is_const<TypeName>::value);\
TypeName& VarName = (Redirect && RunningAsInjectedDll()) ? *reinterpret_cast<TypeName*>(Addr) : LocalVar_##VarName;


#define GEX_FUNC_HOOK(ReturnValue, CallType, FunctionName, Address, ...)\
typedef ReturnValue(CallType* original_##FunctionName)(__VA_ARGS__);\
original_##FunctionName f_##FunctionName = (original_##FunctionName)Address;

#define GEX_FUNC_EXTERN(ReturnValue, CallType, FunctionName, Address, ...)\
typedef ReturnValue(CallType* ext_##FunctionName)(__VA_ARGS__);\
ext_##FunctionName (##FunctionName) = (ext_##FunctionName)Address;



//GEX_FUNC_EXTERN(LRESULT, __cdecl, FUN_0040f4c0_CallAndProcessKeyInput, 0x40f4c0, int param_1);


/*
typedef LRESULT(__stdcall* FUN_00404a20_MoveWindow_Def)();
FUN_00404a20_MoveWindow_Def FUN_00404a20_MoveWindow = (FUN_00404a20_MoveWindow_Def)0x404a20;
*/
#define GEX_ATTACH(FunctionName)\
DetourAttach(&(PVOID&)f_##FunctionName, FunctionName);

#define GEX_DETACH(FunctionName)\
DetourDetach(&(PVOID&)f_##FunctionName, FunctionName);


// STRUCTS

struct astruct_MainObjects {
    int field_0x0;
    int field_0x4;
    int field_0x8;
    byte field_0xc;
    byte field_0xd;
    byte field_0xe;
    byte field_0xf;
    byte field_0x10;
    byte field_0x11;
    byte field_0x12;
    byte field_0x13;
    int field_0x14;
    int field_0x18;
    int field_0x1c;
    int field_0x20;
    int field_0x24;
    int field_0x28;
    int field_0x2c;
    int field_0x30;
    int field_0x34;
};


struct GexTileStruct {
    struct GexTileStruct* handle_0x0_BlockAnims;
    struct GexTileStruct* f_0x4_CurrentTileMaybe;
    struct GexTileStruct* f_0x8_NextTileMaybe;
    int f_0xc;
    int field_0x10;
    int field_0x14_TileData; /* Created by retype action */
    short field_0x18_TileX; /* Created by retype action */
    short field_0x1a_TileY; /* Created by retype action */
    struct GexTileStruct* field_0x1c_ptr;
    int field_0x20_gTiles;
};

struct GexPlayerStruct {
    GexPlayerStruct* field_0x0;
    int field_0x4;
    int field_0x8_objectype; /* Created by retype action */
    unsigned int** field_0xc_gOb_unk;
    int field_0x10_objectscript; /* Created by retype action */
    byte field_0x14;
    byte field_0x15;
    byte field_0x16;
    byte field_0x17;
    byte field_0x18;
    byte field_0x19;
    byte field_0x1a;
    byte field_0x1b;
    byte field_0x1c;
    byte field_0x1d;
    byte field_0x1e;
    byte field_0x1f;
    byte field_0x20;
    byte field_0x21;
    byte field_0x22;
    byte field_0x23;
    byte field_0x24;
    byte field_0x25;
    byte field_0x26;
    byte field_0x27;
    byte field_0x28;
    byte field_0x29;
    byte field_0x2a;
    byte field_0x2b;
    byte field_0x2c;
    byte field_0x2d;
    byte field_0x2e;
    byte field_0x2f;
    byte field_0x30;
    byte field_0x31;
    byte field_0x32;
    byte field_0x33;
    byte field_0x34;
    byte field_0x35;
    byte field_0x36;
    byte field_0x37;
    byte field_0x38;
    byte field_0x39;
    byte field_0x3a;
    byte field_0x3b;
    byte field_0x3c;
    byte field_0x3d;
    byte field_0x3e;
    byte field_0x3f;
    byte field_0x40;
    byte field_0x41;
    byte field_0x42;
    byte field_0x43;
    byte field_0x44;
    byte field_0x45;
    byte field_0x46;
    byte field_0x47;
    byte field_0x48;
    byte field_0x49;
    byte field_0x4a;
    byte field_0x4b;
    byte field_0x4c;
    byte field_0x4d;
    byte field_0x4e;
    byte field_0x4f;
    int field_0x50_spriteIndex_CurrentFrameGroup; /* Created by retype action */
    int field_0x54_animationframe_CurrentFrameIndex; /* Created by retype action */
    byte field_0x58_callFunction; /* Created by retype action */
    byte field_0x59;
    byte field_0x5a;
    byte field_0x5b;
    int* callFunction_pos_update_player; /* Created by retype action */
    struct GexPlayerStruct* field_0x60_GexFunctions;
    byte field_0x64_functionpointer; /* Created by retype action */
    byte field_0x65;
    byte field_0x66;
    byte field_0x67;
    int* field_0x68;
    int* field_0x6c_GameFunctions_or_ObjectsMaybe;
    int field_0x70_animation_state_string_enum; /* Created by retype action */
    int field_0x74;
    int field_0x78_xPos;
    int field_0x7c_yPos;
    int field_0x80_x_velocity;
    int field_0x84_MaxVelocityX;
    int field_0x88_x_velocity_2;
    int field_0x8c_y_velocity;
    int field_0x90_MaxVelocityY;
    int field_0x94_jumping_related;
    int field_0x98_frameCount;
    int field_0x9c_gob_work1;
    int field_0xa0_BackgroundUnk;
    int field_0xa4_Loading_and_Running;
    int field_0xa8_standingTime;
    int field_0xac_yPos2;
    int field_0xb0_possible_idle_animation;
    int field_0xb4_doorID;
    int field_0xb8_Collision;
    int field_0xbc;
    int field_0xc0;
    int field_0xc4_MovementSpeed;
    int field_0xc8_MaxVelocityX2;
    int field_0xcc_MaxVelocityY2;
    int field_0xd0;
    int field_0xd4_xPos2;
    int field_0xd8_yPos2;
    int field_0xdc;
    int field_0xe0;
    int field_0xe4;
    int field_0xe8;
    int field_0xec;
    int field_0xf0;
    int field_0xf4_spriteIndex2;
    int field_0xf8_animationFrame2;
    int* field_0xfc_GameFunctions2;
    int field_0x100;
    int field_0x104;
    int field_0x108;
    int field_0x10c;
    int field_0x110;
    int field_0x114;
    int field_0x118;
    int field_0x11c;
    int field_0x120;
    int field_0x124;
    int field_0x128;
    int field_0x12c;
    int field_0x130;
    int field_0x134;
    int field_0x138;
    int field_0x13c;
    int field_0x140;
    int field_0x144;
    int field_0x148;
    int field_0x14c;
    int field_0x150;
    int field_0x154;
    int field_0x158;
    int field_0x15c;
    int field_0x160;
    int field_0x164;
    int field_0x168;
    int field_0x16c;
    int field_0x170;
    int field_0x174;
    struct GexPlayerStruct* field_0x178_GexPlayerObject;
    int field_0x17c;
    int field_0x180;
    int field_0x184_xPosFinal;
    int field_0x188_yPosFinal;
    int field_0x18c;
    int field_0x190;
    int field_0x194;
    int field_0x198;
    int field_0x19c;
    int field_0x1a0;
    int field_0x1a4;
    int field_0x1a8;
    int field_0x1ac;
    int field_0x1b0;
    int field_0x1b4;
    int field_0x1b8;
    int field_0x1bc;
    int field_0x1c0;
    int field_0x1c4;
    int field_0x1c8;
    int field_0x1cc;
    int field_0x1d0;
    int field_0x1d4;
    int field_0x1d8;
    int field_0x1dc;
    int field_0x1e0;
    int field_0x1e4;
    int field_0x1e8;
    int field_0x1ec;
    int field_0x1f0;
    int frameCount;
    int field_0x1f8_xPos;
    int field_0x1fc_yPos;
};

struct TilePTRStruct {
    struct TilePTRStruct* field_0x0_TilePTR;
    int* field_0x4;
    short field_0x8_TopRightXPosition;
    short field_0xa_TopRightYPosition;
    short field_0xc;
    short field_0xe;
    ushort field_0x10_TopLeftXPosition;
    short field_0x12_TopLeftYPosition;
    short field_0x14;
    short field_0x16;
    short field_0x18_BottomRightXPosition;
    short field_0x1a_BottomRightYPosition;
    byte field_0x1c;
    char field_0x1d;
    byte field_0x1e;
    byte field_0x1f;
    ushort field_0x20_BottomLeftXPosition;
    short field_0x22_BottomLeftYPosition;
    byte field_0x24;
    char field_0x25;
    byte field_0x26;
    byte field_0x27;
    struct TilePTRStruct* field_0x28_NextTile;
    int* field_0x2c;
    short field_0x30;
    short field_0x32;
    ushort field_0x34;
    short field_0x36;
    ushort field_0x38;
    int* field_0x3a;
    byte field_0x3e;
    byte field_0x3f;
    short field_0x40;
    byte field_0x42;
    byte field_0x43;
    short field_0x44;
    short field_0x46;
    short field_0x48;
    short field_0x4a;
    byte field_0x4c;
    byte field_0x4d;
    byte field_0x4e;
    byte field_0x4f;
    int* field_0x50;
    byte field_0x54;
    byte field_0x55;
    byte field_0x56;
    byte field_0x57;
    byte field_0x58;
    byte field_0x59;
    byte field_0x5a;
    byte field_0x5b;
    byte field_0x5c;
    byte field_0x5d;
    byte field_0x5e;
    byte field_0x5f;
    byte field_0x60;
    byte field_0x61;
    byte field_0x62;
    byte field_0x63;
    byte field_0x64;
    byte field_0x65;
    byte field_0x66;
    byte field_0x67;
    byte field_0x68;
    byte field_0x69;
    byte field_0x6a;
    byte field_0x6b;
    byte field_0x6c;
    byte field_0x6d;
    byte field_0x6e;
    byte field_0x6f;
    byte field_0x70;
    byte field_0x71;
    byte field_0x72;
    byte field_0x73;
    byte field_0x74;
    byte field_0x75;
    byte field_0x76;
    byte field_0x77;
    int* field_0x78;
    byte field_0x7c;
    byte field_0x7d;
    byte field_0x7e;
    byte field_0x7f;
    byte field_0x80;
    byte field_0x81;
    byte field_0x82;
    byte field_0x83;
    byte field_0x84;
    byte field_0x85;
    byte field_0x86;
    byte field_0x87;
    byte field_0x88;
    byte field_0x89;
    byte field_0x8a;
    byte field_0x8b;
};



/// VARS

GEX_FUNC_HOOK(void, __cdecl, FUN_0040ef40_SomethingGameObjectsProcessingUnk, 0x40ef40, GexPlayerStruct* param_1);
GEX_FUNC_HOOK(void, __cdecl, FUN_0040efa0_GraphicFunctions, 0x40efa0, GexPlayerStruct* GameStruct);

GEX_VAR(1, 0x458ed4, original_FUN_0040ef40_SomethingGameObjectsProcessingUnk, PTR_FUN_00458ed4_GameObjectProcess_Unk, nullptr);
GEX_VAR(1, 0x458ed8, original_FUN_0040efa0_GraphicFunctions, _PTR_FUN_DrawObjects_00458ed8, nullptr);


GEX_VAR(1, 0x4a2a20, unsigned int*, DAT_004a2a20_ObjectsLeftToGetReady, 0);


GEX_VAR(1, 0x4a2990, GexTileStruct*, DAT_004a2990_BlockAnims, 0);
GEX_VAR(1, 0x4626f4, unsigned int, DAT_004626f4_InitialiseLevel, 0);
GEX_VAR(1, 0x4a2948, unsigned int, DAT_004a2948, 0);
GEX_VAR(1, 0x4a2a8c, unsigned int*, DAT_004a2a8c_ResetGame, 0);
GEX_VAR(1, 0x4a2958, unsigned int*, DAT_004a2958_ToggleVoicesInMainGame, 0);
GEX_VAR(1, 0x4a2964, unsigned int, DAT_004a2964_LEV_Value_Start, 0);
GEX_VAR(1, 0x4a2a7c, unsigned int, DAT_004a2a7c_Process_Level_Change, 0);
GEX_VAR(1, 0x455e28, LPSTR, s_Intro_Objects_00455e28, 0);
GEX_VAR(1, 0x455c4c, unsigned int, DAT_00455c4c_Pause_Game_On_Collision, 0);
GEX_VAR(1, 0x4a2ad0, unsigned int, DAT_004a2ad0_Objects, 0);
GEX_VAR(1, 0x4626fc, unsigned int, DAT_004626fc_Objects, 0);
GEX_VAR(1, 0x4a2a78, unsigned int, DAT_004a2a78_ObjectsInner, 0);
GEX_VAR(1, 0x4a288c, unsigned int, DAT_004a288c_ProcessBlockAnimations, 0);
GEX_VAR(1, 0x455e14, LPSTR, s_ProcessBlockAnims_00455e14, 0);
GEX_VAR(1, 0x455e00, LPSTR, s_ProcessTileAnims_00455e00, 0);
GEX_VAR(1, 0x455dec, LPSTR, s_Process_Objects_00455dec, 0);
GEX_VAR(1, 0x4a27fc, GexPlayerStruct*, DAT_004a27fc_GexPlayerObject, 0);
GEX_VAR(1, 0x4a28a0, GexPlayerStruct*, DAT_004a28a0_GameObjectUnkDrawBackground, 0);
GEX_VAR(1, 0x4a28ac, GexPlayerStruct*, DAT_004a28ac_GameObjectUnkDrawBackgroundObjects, 0);
GEX_VAR(1, 0x4a28b8, GexPlayerStruct*, DAT_004a28b8_GameObjectUnk3_StaticBehindGex, 0);
GEX_VAR(1, 0x4a28c4, GexPlayerStruct*, DAT_004a28c4_GameObjectUnk4_DrawGexAndTitle, 0);
GEX_VAR(1, 0x4a28d0, GexPlayerStruct*, DAT_004a28d0_GameObjectUnk5_DrawTitleStartText, 0);
GEX_VAR(1, 0x4a28dc, GexPlayerStruct*, DAT_004a28dc_GameObjectUnk6_Enemies, 0);
GEX_VAR(1, 0x4a28e8, GexPlayerStruct*, DAT_004a28e8_GameObjectUnk7_Obstacles, 0);
GEX_VAR(1, 0x4a28f4, GexPlayerStruct*, DAT_004a28f4_GameObjectUnk8, 0);
GEX_VAR(1, 0x4a2900, GexPlayerStruct*, DAT_004a2900_GameObjectUnk9, 0);
GEX_VAR(1, 0x455dd8, LPSTR, s_Process_Collisions_00455dd8, 0);
GEX_VAR(1, 0x455dc0, LPSTR, s_Set_Scroll_Position_00455dc0, 0);
GEX_VAR(1, 0x4a290c, GexPlayerStruct*, DAT_004a290c_GameObjectUnk10, 0);
GEX_VAR(1, 0x4a2a96, short, DAT_004a2a96_CameraX, 0);
GEX_VAR(1, 0x4a2a94, short, DAT_004a2a94_CameraY, 0);
GEX_VAR(1, 0x4a293c, int, DAT_004a293c_CameraX, 0);
GEX_VAR(1, 0x4a2978, int, DAT_004a2978_CameraY, 0);
GEX_VAR(1, 0x4a2a24, unsigned int*, DAT_004a2a24_DrawGraphics, 0);
GEX_VAR(1, 0x4a2ae8, unsigned int, __DAT_004a2ae8_TileData, 0);
GEX_VAR(1, 0x455db4, LPSTR, s_Draw_Tiles_00455db4, 0);
GEX_VAR(1, 0x455da0, LPSTR, s_Draw_Objects_Mid_00455da0, 0);
GEX_VAR(1, 0x455d8c, LPSTR, s_Draw_Objects_Hi_00455d8c, 0);
GEX_VAR(1, 0x4a2960, unsigned int, DAT_004a2960_PausedUnk, 0);
GEX_VAR(1, 0x4626ec, unsigned int, _DAT_004626ec, 0);
GEX_VAR(1, 0x4a2a0c, unsigned int, DAT_004a2a0c_DemoMode, 0);
GEX_VAR(1, 0x4a2ac8, unsigned int, DAT_004a2ac8_FrameCount, 0);
GEX_VAR(1, 0x4a2a98, unsigned int, DAT_004a2a98_LEV_Related_End, 0);
GEX_VAR(1, 0x4626f0, unsigned int, DAT_004626f0_GameTypeSwitchCase, 0);
GEX_VAR(1, 0x455c3c, unsigned int, DAT_00455c3c_GameTypeSwitchCase, 0);
GEX_VAR(1, 0x4a2a3c, unsigned int, DAT_004a2a3c, 0);

GEX_VAR(1, 0x4a2a38, int, DAT_004a2a38_CameraX_TrueCam, 0);
GEX_VAR(1, 0x4a2a1c, int, DAT_004a2a1c_CameraY_TrueCam, 0);
GEX_VAR(1, 0x4a2974, int, DAT_004a2974_CameraX_TrueCam2, 0);
GEX_VAR(1, 0x4a2988, int, DAT_004a2988_CameraY_TrueCam2, 0);

GEX_VAR(1, 0x4a27dc, unsigned int, DAT_004a27dc_KeyInput, 0);
GEX_VAR(1, 0x455c48, unsigned int, DAT_00455c48, 0);

GEX_VAR(1, 0x4a2540, int, DAT_004a2540_RemoteUnk2, 0);
GEX_VAR(1, 0x4a2abc, uint, DAT_004a2abc_EnableParallaxBackground, 0);

GEX_VAR(1, 0x4a28a0, GexPlayerStruct*, DAT_004a28a0_LevelObjectsListStart, 0);
GEX_VAR(1, 0x4a2918, GexPlayerStruct*, DAT_004a2918_LevelObjectsListEnd, 0);

GEX_VAR(1, 0x46a588, int*, DAT_0046a588_GFXInit1, 0);
GEX_VAR(1, 0x46a5e4, int*, DAT_0046a5e4_GFXInit2, 0);

GEX_VAR(1, 0x46a59e, unsigned int, DAT_0046a59e_GFXInit3, 0);
GEX_VAR(1, 0x46a59f, unsigned int, DAT_0046a59f_GFXInit4, 0);
GEX_VAR(1, 0x46a5a0, unsigned int, DAT_0046a5a0_GFXInit5, 0);
GEX_VAR(1, 0x46a5fa, unsigned int, DAT_0046a5fa_GFXInit6, 0);
GEX_VAR(1, 0x46a5fb, unsigned int, DAT_0046a5fb_GFXInit7, 0);
GEX_VAR(1, 0x46a5fc, unsigned int, DAT_0046a5fc_GFXInit8, 0);
GEX_VAR(1, 0x4a2b08, unsigned int, DAT_004a2b08_GFXInit9, 0);

GEX_VAR(1, 0x4a23c0, unsigned int*, DAT_004a23c0_gTilesMax, 0);
GEX_VAR(1, 0x4a02f0, unsigned int*, DAT_004a02f0_gTiles, 0);
GEX_VAR(1, 0x4a02fc, unsigned int*, DAT_004a02fc_gTiles_start, 0);

GEX_VAR(1, 0x48294c, unsigned int, DAT_004a294c_FreezeGame, 0);

GEX_VAR(1, 0x4a27e0, unsigned int, DAT_004a27e0_MainGame_NextKeyInput, 0);
GEX_VAR(1, 0x4a27d8, unsigned int, DAT_004a27d8_MainGame_KeyInput, 0);

/// FUNCTIONS

GEX_FUNC_EXTERN(void, __cdecl, FUN_0043f490_GameInitUnk, 0x43f490, int param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int param_7);
GEX_FUNC_EXTERN(void, __stdcall, FUN_0041faf0_VoiceRelated, 0x41faf0);
GEX_FUNC_EXTERN(int, __cdecl, FUN_0040f910_SpawnObjects, 0x40f910, astruct_MainObjects* param_1, uint CameraX, uint CameraY, int param_4);

GEX_FUNC_EXTERN(void, __cdecl, FUN_0041f710_ProcessBlockAnims, 0x41f710, GexTileStruct* param_1);
GEX_FUNC_EXTERN(void, __stdcall, FUN_0041f7a0_ProcessTileAnims, 0x41f7a0);
GEX_FUNC_EXTERN(void, __stdcall, FUN_00409f00_ProcessCheatWords, 0x409f00);
GEX_FUNC_EXTERN(void, __stdcall, FUN_0041e5c0_ProcessCollisions, 0x41e5c0);
GEX_FUNC_EXTERN(void, __stdcall, FUN_00410280_SetScrollPosition_ScrollScreen, 0x410280);
GEX_FUNC_EXTERN(void, __stdcall, FUN_00410c60_CameraFollowGex, 0x410c60);
GEX_FUNC_EXTERN(void, __cdecl, FUN_0043fb40_DrawObjectsMidOuter_TrueDraw, 0x43fb40, TilePTRStruct* CurrentTileMaybe, GexTileStruct* GTiles, uint CameraXParam, uint CameraYParam);
GEX_FUNC_EXTERN(void, __stdcall, FUN_00440510_DrawObjectsMid, 0x440510);
GEX_FUNC_EXTERN(void, __stdcall, FUN_00440560_DrawObjectsHigh_InFrontOfGex, 0x440560);
GEX_FUNC_EXTERN(void, __stdcall, FUN_00410250_Camera_unk, 0x410250);
GEX_FUNC_EXTERN(void, __stdcall, FUN_00417d90_COLLISIONS, 0x417d90);
GEX_FUNC_EXTERN(void, __cdecl, FUN_0041bfc0_MakesWordPauseAppear_ProcessCheats, 0x41bfc0, GexPlayerStruct* param_1);
GEX_FUNC_EXTERN(int, __stdcall, FUN_00402fa0_ret_timeSetEventUnk2, 0x402fa0);
GEX_FUNC_EXTERN(void, __stdcall, FUN_0043f310_InitVarsRelatedUnk, 0x43f310);
GEX_FUNC_EXTERN(uint, __stdcall, FUN_00405120_WaitTicks, 0x405120);
GEX_FUNC_EXTERN(void, __stdcall, FUN_004053a0_SaveScreenshotAndPauseGame, 0x4053a0);
GEX_FUNC_EXTERN(void, __cdecl, FUN_0043f2d0_CheckF3ForUnpauseGameDrawWindow, 0x43f2d0, int param_1);
GEX_FUNC_EXTERN(void, __stdcall, FUN_0040b2d0_InputProcessing, 0x40b2d0);
GEX_FUNC_EXTERN(void, __cdecl, FUN_0043db70_DEBUGTHISGRAPHICS, 0x43db70, int param_1);
GEX_FUNC_EXTERN(void, __stdcall, FUN_0043db50, 0x43db50);
GEX_FUNC_EXTERN(void, __stdcall, FUN_00409970_BetweenLevelsTVFuzz, 0x409970);
GEX_FUNC_EXTERN(int, __cdecl, FUN_0040f400_CallKeyInputFunction_ProcessKeyInput, 0x40f400, int param_1);
GEX_FUNC_EXTERN(LRESULT, __cdecl, FUN_0043fa70_DrawText, 0x43fa70, int xpos, int ypos, char* text);

GEX_FUNC_EXTERN(int, __stdcall, FUN_00404ba0_ReturnKeyPressInput_TRUEINPUT, 0x404ba0);



GEX_FUNC_EXTERN(void, __stdcall, FUN_0041fc40_KeyInput_Outer, 0x41fc40);
GEX_FUNC_HOOK(undefined4, __cdecl, FUN_0040f7a0_MainGameInput, 0x40f7a0, int param_1, undefined4 param_2, uint* CurrentInputPTR);
GEX_FUNC_HOOK(int, __stdcall, FUN_00404ba0_ReturnKeyPressInput_TRUEINPUT, 0x404ba0);
GEX_FUNC_HOOK(int, __cdecl, MAIN_GAME_LOOP, 0x40a010, GexTileStruct param_1);


// HELPER FUNCTION HEADERS

XINPUT_STATE state;

bool ControllerConnected = false;

void WINAPI Console_Write(const char* format, ...);

void PatchByteSingle(unsigned long addr, BYTE byte);
void PatchByteRepeat(unsigned long addr, unsigned int len, BYTE byte);

const char* PRINT_BINARY_STRING(int x)
{
    static char b[sizeof(int) * 8 + 1] = { 0 };
    int y;
    long long z;

    for (z = 1LL << sizeof(int) * 8 - 1, y = 0; z > 0; z >>= 1, y++) {
        b[y] = (((x & z) == z) ? '1' : '0');
    }
    b[y] = 0;

    return b;
}