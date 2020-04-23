#pragma once
#include <string>
using namespace std;

#include "types.h"
#include "DSReg.h"

class RegSect_display9
{
public:
    /// <summary>
    /// LCD Control 2 R/W
    /// </summary>
    DSReg A_DISPCNT;
    /// <summary>
    /// BG Mode (0-5=Video Mode 0-6, 7=Prohibited)
    /// </summary>
    DSReg A_DISPCNT_BG_Mode;
    /// <summary>
    /// A only BG0 2D/3D Selection (instead CGB Mode) (0=2D, 1=3D)
    /// </summary>
    DSReg A_DISPCNT_BG0_2D_3D;
    /// <summary>
    /// Tile OBJ Mapping (0=2D; max 32KB, 1=1D; max 32KB..256KB)
    /// </summary>
    DSReg A_DISPCNT_Tile_OBJ_Mapping;
    /// <summary>
    /// Bitmap OBJ 2D-Dimension (0=128x512 dots, 1=256x256 dots)
    /// </summary>
    DSReg A_DISPCNT_Bitmap_OBJ_2D_Dim;
    /// <summary>
    /// Bitmap OBJ Mapping (0=2D; max 128KB, 1=1D; max 128KB..256KB)
    /// </summary>
    DSReg A_DISPCNT_Bitmap_OBJ_Mapping;
    /// <summary>
    /// Forced Blank (1=Allow FAST access to VRAM,Palette,OAM)
    /// </summary>
    DSReg A_DISPCNT_Forced_Blank;
    /// <summary>
    /// Screen Display BG0 (0=Off, 1=On)
    /// </summary>
    DSReg A_DISPCNT_Screen_Display_BG0;
    /// <summary>
    /// Screen Display BG1 (0=Off, 1=On)
    /// </summary>
    DSReg A_DISPCNT_Screen_Display_BG1;
    /// <summary>
    /// Screen Display BG2 (0=Off, 1=On)
    /// </summary>
    DSReg A_DISPCNT_Screen_Display_BG2;
    /// <summary>
    /// Screen Display BG3 (0=Off, 1=On)
    /// </summary>
    DSReg A_DISPCNT_Screen_Display_BG3;
    /// <summary>
    /// Screen Display OBJ (0=Off, 1=On)
    /// </summary>
    DSReg A_DISPCNT_Screen_Display_OBJ;
    /// <summary>
    /// Window 0 Display Flag (0=Off, 1=On)
    /// </summary>
    DSReg A_DISPCNT_Window_0_Display_Flag;
    /// <summary>
    /// Window 1 Display Flag (0=Off, 1=On)
    /// </summary>
    DSReg A_DISPCNT_Window_1_Display_Flag;
    /// <summary>
    /// OBJ Window Display Flag (0=Off, 1=On)
    /// </summary>
    DSReg A_DISPCNT_OBJ_Wnd_Display_Flag;
    /// <summary>
    /// 16-17 A+B Display Mode (Engine A: 0..3, Engine B: 0..1, GBA: Green Swap)
    /// </summary>
    DSReg A_DISPCNT_Display_Mode;
    /// <summary>
    /// 18-19 A VRAM block (0..3=VRAM A..D) (For Capture & above Display Mode=2)
    /// </summary>
    DSReg A_DISPCNT_VRAM_block;
    /// <summary>
    /// 20-21 A+B Tile OBJ 1D-Boundary (see Bit4)
    /// </summary>
    DSReg A_DISPCNT_Tile_OBJ_1D_Boundary;
    /// <summary>
    /// 22 A Bitmap OBJ 1D-Boundary (see Bit5-6)
    /// </summary>
    DSReg A_DISPCNT_Bitmap_OBJ_1D_Boundary;
    /// <summary>
    /// 23 A+B OBJ Processing during H-Blank (was located in Bit5 on GBA)
    /// </summary>
    DSReg A_DISPCNT_OBJ_Process_H_Blank;
    /// <summary>
    /// 24-26 A Character Base (in 64K steps) (merged with 16K step in BGxCNT)
    /// </summary>
    DSReg A_DISPCNT_Character_Base;
    /// <summary>
    /// 27-29 A Screen Base (in 64K steps) (merged with 2K step in BGxCNT)
    /// </summary>
    DSReg A_DISPCNT_Screen_Base;
    /// <summary>
    /// 30 A+B BG Extended Palettes (0=Disable, 1=Enable)
    /// </summary>
    DSReg A_DISPCNT_BG_Extended_Palettes;
    /// <summary>
    /// 31 A+B OBJ Extended Palettes (0=Disable, 1=Enable
    /// </summary>
    DSReg A_DISPCNT_OBJ_Extended_Palettes;
    /// <summary>
    /// General LCD Status (STAT,LYC) 2 R/W
    /// </summary>
    DSReg DISPSTAT;
    /// <summary>
    /// V-Blank flag (Read only) (1=VBlank) (set in line 160..226; not 227)
    /// </summary>
    DSReg DISPSTAT_V_Blank_flag;
    /// <summary>
    /// H-Blank flag (Read only) (1=HBlank) (toggled in all lines, 0..227)
    /// </summary>
    DSReg DISPSTAT_H_Blank_flag;
    /// <summary>
    /// V-Counter flag (Read only) (1=Match) (set in selected line) (R)
    /// </summary>
    DSReg DISPSTAT_V_Counter_flag;
    /// <summary>
    /// V-Blank IRQ Enable (1=Enable) (R/W)
    /// </summary>
    DSReg DISPSTAT_V_Blank_IRQ_Enable;
    /// <summary>
    /// H-Blank IRQ Enable (1=Enable) (R/W)
    /// </summary>
    DSReg DISPSTAT_H_Blank_IRQ_Enable;
    /// <summary>
    /// V-Counter IRQ Enable (1=Enable) (R/W)
    /// </summary>
    DSReg DISPSTAT_V_Counter_IRQ_Enable;
    /// <summary>
    /// NDS: MSB of V-Vcount Setting (LYC.Bit8) (0..262)(R/W)
    /// </summary>
    DSReg DISPSTAT_V_Count_Setting8;
    /// <summary>
    /// V-Count Setting (LYC) (0..227) (R/W)
    /// </summary>
    DSReg DISPSTAT_V_Count_Setting;
    /// <summary>
    /// Vertical Counter (LY) 2 R
    /// </summary>
    DSReg VCOUNT;
    /// <summary>
    /// BG0 Control 2 R/W
    /// </summary>
    DSReg A_BG0CNT;
    /// <summary>
    /// BG Priority (0-3, 0=Highest)
    /// </summary>
    DSReg A_BG0CNT_BG_Priority;
    /// <summary>
    /// Character Base Block (0-15, in units of 16 KBytes) (=BG Tile Data)
    /// </summary>
    DSReg A_BG0CNT_Character_Base_Block;
    /// <summary>
    /// Mosaic (0=Disable, 1=Enable)
    /// </summary>
    DSReg A_BG0CNT_Mosaic;
    /// <summary>
    /// Colors/Palettes (0=16/16, 1=256/1)
    /// </summary>
    DSReg A_BG0CNT_Colors_Palettes;
    /// <summary>
    /// Screen Base Block (0-31, in units of 2 KBytes) (=BG Map Data)
    /// </summary>
    DSReg A_BG0CNT_Screen_Base_Block;
    /// <summary>
    /// Ext Palette Slot for BG0/BG1
    /// </summary>
    DSReg A_BG0CNT_Ext_Palette_Slot;
    /// <summary>
    /// Screen Size (0-3)
    /// </summary>
    DSReg A_BG0CNT_Screen_Size;
    /// <summary>
    /// BG1 Control 2 R/W
    /// </summary>
    DSReg A_BG1CNT;
    /// <summary>
    /// BG Priority (0-3, 0=Highest)
    /// </summary>
    DSReg A_BG1CNT_BG_Priority;
    /// <summary>
    /// Character Base Block (0-15, in units of 16 KBytes) (=BG Tile Data)
    /// </summary>
    DSReg A_BG1CNT_Character_Base_Block;
    /// <summary>
    /// Mosaic (0=Disable, 1=Enable)
    /// </summary>
    DSReg A_BG1CNT_Mosaic;
    /// <summary>
    /// Colors/Palettes (0=16/16, 1=256/1)
    /// </summary>
    DSReg A_BG1CNT_Colors_Palettes;
    /// <summary>
    /// Screen Base Block (0-31, in units of 2 KBytes) (=BG Map Data)
    /// </summary>
    DSReg A_BG1CNT_Screen_Base_Block;
    /// <summary>
    /// Ext Palette Slot for BG0/BG1
    /// </summary>
    DSReg A_BG1CNT_Ext_Palette_Slot;
    /// <summary>
    /// Screen Size (0-3)
    /// </summary>
    DSReg A_BG1CNT_Screen_Size;
    /// <summary>
    /// BG2 Control 2 R/W
    /// </summary>
    DSReg A_BG2CNT;
    /// <summary>
    /// BG Priority (0-3, 0=Highest)
    /// </summary>
    DSReg A_BG2CNT_BG_Priority;
    /// <summary>
    /// Character Base Block (0-15, in units of 16 KBytes) (=BG Tile Data)
    /// </summary>
    DSReg A_BG2CNT_Character_Base_Block;
    /// <summary>
    /// Mosaic (0=Disable, 1=Enable)
    /// </summary>
    DSReg A_BG2CNT_Mosaic;
    /// <summary>
    /// Colors/Palettes (0=16/16, 1=256/1)
    /// </summary>
    DSReg A_BG2CNT_Colors_Palettes;
    /// <summary>
    /// Screen Base Block (0-31, in units of 2 KBytes) (=BG Map Data)
    /// </summary>
    DSReg A_BG2CNT_Screen_Base_Block;
    /// <summary>
    /// Display Area Overflow (0=Transparent, 1=Wraparound; BG2CNT/BG3CNT only)
    /// </summary>
    DSReg A_BG2CNT_Display_Area_Overflow;
    /// <summary>
    /// Screen Size (0-3)
    /// </summary>
    DSReg A_BG2CNT_Screen_Size;
    /// <summary>
    /// BG3 Control 2 R/W
    /// </summary>
    DSReg A_BG3CNT;
    /// <summary>
    /// BG Priority (0-3, 0=Highest)
    /// </summary>
    DSReg A_BG3CNT_BG_Priority;
    /// <summary>
    /// Character Base Block (0-15, in units of 16 KBytes) (=BG Tile Data)
    /// </summary>
    DSReg A_BG3CNT_Character_Base_Block;
    /// <summary>
    /// Mosaic (0=Disable, 1=Enable)
    /// </summary>
    DSReg A_BG3CNT_Mosaic;
    /// <summary>
    /// Colors/Palettes (0=16/16, 1=256/1)
    /// </summary>
    DSReg A_BG3CNT_Colors_Palettes;
    /// <summary>
    /// Screen Base Block (0-31, in units of 2 KBytes) (=BG Map Data)
    /// </summary>
    DSReg A_BG3CNT_Screen_Base_Block;
    /// <summary>
    /// Display Area Overflow (0=Transparent, 1=Wraparound; BG2CNT/BG3CNT only)
    /// </summary>
    DSReg A_BG3CNT_Display_Area_Overflow;
    /// <summary>
    /// Screen Size (0-3)
    /// </summary>
    DSReg A_BG3CNT_Screen_Size;
    /// <summary>
    /// BG0 X-Offset 2 W
    /// </summary>
    DSReg A_BG0HOFS;
    /// <summary>
    /// BG0 Y-Offset 2 W
    /// </summary>
    DSReg A_BG0VOFS;
    /// <summary>
    /// BG1 X-Offset 2 W
    /// </summary>
    DSReg A_BG1HOFS;
    /// <summary>
    /// BG1 Y-Offset 2 W
    /// </summary>
    DSReg A_BG1VOFS;
    /// <summary>
    /// BG2 X-Offset 2 W
    /// </summary>
    DSReg A_BG2HOFS;
    /// <summary>
    /// BG2 Y-Offset 2 W
    /// </summary>
    DSReg A_BG2VOFS;
    /// <summary>
    /// BG3 X-Offset 2 W
    /// </summary>
    DSReg A_BG3HOFS;
    /// <summary>
    /// BG3 Y-Offset 2 W
    /// </summary>
    DSReg A_BG3VOFS;
    /// <summary>
    /// BG2 Rotation/Scaling Parameter A (dx) 2 W
    /// </summary>
    DSReg A_BG2RotScaleParDX;
    /// <summary>
    /// BG2 Rotation/Scaling Parameter B (dmx) 2 W
    /// </summary>
    DSReg A_BG2RotScaleParDMX;
    /// <summary>
    /// BG2 Rotation/Scaling Parameter C (dy) 2 W
    /// </summary>
    DSReg A_BG2RotScaleParDY;
    /// <summary>
    /// BG2 Rotation/Scaling Parameter D (dmy) 2 W
    /// </summary>
    DSReg A_BG2RotScaleParDMY;
    /// <summary>
    /// BG2 Reference Point X-Coordinate 4 W
    /// </summary>
    DSReg A_BG2RefX;
    /// <summary>
    /// BG2 Reference Point Y-Coordinate 4 W
    /// </summary>
    DSReg A_BG2RefY;
    /// <summary>
    /// BG3 Rotation/Scaling Parameter A (dx) 2 W
    /// </summary>
    DSReg A_BG3RotScaleParDX;
    /// <summary>
    /// BG3 Rotation/Scaling Parameter B (dmx) 2 W
    /// </summary>
    DSReg A_BG3RotScaleParDMX;
    /// <summary>
    /// BG3 Rotation/Scaling Parameter C (dy) 2 W
    /// </summary>
    DSReg A_BG3RotScaleParDY;
    /// <summary>
    /// BG3 Rotation/Scaling Parameter D (dmy) 2 W
    /// </summary>
    DSReg A_BG3RotScaleParDMY;
    /// <summary>
    /// BG3 Reference Point X-Coordinate 4 W
    /// </summary>
    DSReg A_BG3RefX;
    /// <summary>
    /// BG3 Reference Point Y-Coordinate 4 W
    /// </summary>
    DSReg A_BG3RefY;
    /// <summary>
    /// Window 0 Horizontal Dimensions 2 W
    /// </summary>
    DSReg A_WIN0H;
    /// <summary>
    /// Window 0 Horizontal Dimensions 2 W
    /// </summary>
    DSReg A_WIN0H_X2;
    /// <summary>
    /// Window 0 Horizontal Dimensions 2 W
    /// </summary>
    DSReg A_WIN0H_X1;
    /// <summary>
    /// Window 1 Horizontal Dimensions 2 W
    /// </summary>
    DSReg A_WIN1H;
    /// <summary>
    /// Window 1 Horizontal Dimensions 2 W
    /// </summary>
    DSReg A_WIN1H_X2;
    /// <summary>
    /// Window 1 Horizontal Dimensions 2 W
    /// </summary>
    DSReg A_WIN1H_X1;
    /// <summary>
    /// Window 0 Vertical Dimensions 2 W
    /// </summary>
    DSReg A_WIN0V;
    /// <summary>
    /// Window 0 Vertical Dimensions 2 W
    /// </summary>
    DSReg A_WIN0V_Y2;
    /// <summary>
    /// Window 0 Vertical Dimensions 2 W
    /// </summary>
    DSReg A_WIN0V_Y1;
    /// <summary>
    /// Window 1 Vertical Dimensions 2 W
    /// </summary>
    DSReg A_WIN1V;
    /// <summary>
    /// Window 1 Vertical Dimensions 2 W
    /// </summary>
    DSReg A_WIN1V_Y2;
    /// <summary>
    /// Window 1 Vertical Dimensions 2 W
    /// </summary>
    DSReg A_WIN1V_Y1;
    /// <summary>
    /// Inside of Window 0 and 1 2 R/W
    /// </summary>
    DSReg A_WININ;
    /// <summary>
    /// 0-3 Window_0_BG0_BG3_Enable (0=No Display, 1=Display)
    /// </summary>
    DSReg A_WININ_Window_0_BG0_Enable;
    /// <summary>
    /// 0-3 Window_0_BG0_BG3_Enable (0=No Display, 1=Display)
    /// </summary>
    DSReg A_WININ_Window_0_BG1_Enable;
    /// <summary>
    /// 0-3 Window_0_BG0_BG3_Enable (0=No Display, 1=Display)
    /// </summary>
    DSReg A_WININ_Window_0_BG2_Enable;
    /// <summary>
    /// 0-3 Window_0_BG0_BG3_Enable (0=No Display, 1=Display)
    /// </summary>
    DSReg A_WININ_Window_0_BG3_Enable;
    /// <summary>
    /// 4 Window_0_OBJ_Enable (0=No Display, 1=Display)
    /// </summary>
    DSReg A_WININ_Window_0_OBJ_Enable;
    /// <summary>
    /// 5 Window_0_Special_Effect (0=Disable, 1=Enable)
    /// </summary>
    DSReg A_WININ_Window_0_Special_Effect;
    /// <summary>
    /// 8-11 Window_1_BG0_BG3_Enable (0=No Display, 1=Display)
    /// </summary>
    DSReg A_WININ_Window_1_BG0_Enable;
    /// <summary>
    /// 8-11 Window_1_BG0_BG3_Enable (0=No Display, 1=Display)
    /// </summary>
    DSReg A_WININ_Window_1_BG1_Enable;
    /// <summary>
    /// 8-11 Window_1_BG0_BG3_Enable (0=No Display, 1=Display)
    /// </summary>
    DSReg A_WININ_Window_1_BG2_Enable;
    /// <summary>
    /// 8-11 Window_1_BG0_BG3_Enable (0=No Display, 1=Display)
    /// </summary>
    DSReg A_WININ_Window_1_BG3_Enable;
    /// <summary>
    /// 12 Window_1_OBJ_Enable (0=No Display, 1=Display)
    /// </summary>
    DSReg A_WININ_Window_1_OBJ_Enable;
    /// <summary>
    /// 13 Window_1_Special_Effect (0=Disable, 1=Enable)
    /// </summary>
    DSReg A_WININ_Window_1_Special_Effect;
    /// <summary>
    /// Inside of OBJ Window & Outside of Windows 2 R/W
    /// </summary>
    DSReg A_WINOUT;
    /// <summary>
    /// 0-3 Outside_BG0_BG3_Enable (0=No Display, 1=Display)
    /// </summary>
    DSReg A_WINOUT_Outside_BG0_Enable;
    /// <summary>
    /// 0-3 Outside_BG0_BG3_Enable (0=No Display, 1=Display)
    /// </summary>
    DSReg A_WINOUT_Outside_BG1_Enable;
    /// <summary>
    /// 0-3 Outside_BG0_BG3_Enable (0=No Display, 1=Display)
    /// </summary>
    DSReg A_WINOUT_Outside_BG2_Enable;
    /// <summary>
    /// 0-3 Outside_BG0_BG3_Enable (0=No Display, 1=Display)
    /// </summary>
    DSReg A_WINOUT_Outside_BG3_Enable;
    /// <summary>
    /// 4 Outside_OBJ_Enable (0=No Display, 1=Display)
    /// </summary>
    DSReg A_WINOUT_Outside_OBJ_Enable;
    /// <summary>
    /// 5 Outside_Special_Effect (0=Disable, 1=Enable)
    /// </summary>
    DSReg A_WINOUT_Outside_Special_Effect;
    /// <summary>
    /// 8-11 object window_BG0_BG3_Enable (0=No Display, 1=Display)
    /// </summary>
    DSReg A_WINOUT_Objwnd_BG0_Enable;
    /// <summary>
    /// 8-11 object window_BG0_BG3_Enable (0=No Display, 1=Display)
    /// </summary>
    DSReg A_WINOUT_Objwnd_BG1_Enable;
    /// <summary>
    /// 8-11 object window_BG0_BG3_Enable (0=No Display, 1=Display)
    /// </summary>
    DSReg A_WINOUT_Objwnd_BG2_Enable;
    /// <summary>
    /// 8-11 object window_BG0_BG3_Enable (0=No Display, 1=Display)
    /// </summary>
    DSReg A_WINOUT_Objwnd_BG3_Enable;
    /// <summary>
    /// 12 object window_OBJ_Enable (0=No Display, 1=Display)
    /// </summary>
    DSReg A_WINOUT_Objwnd_OBJ_Enable;
    /// <summary>
    /// 13 object window_Special_Effect (0=Disable, 1=Enable)
    /// </summary>
    DSReg A_WINOUT_Objwnd_Special_Effect;
    /// <summary>
    /// Mosaic Size 2 W
    /// </summary>
    DSReg A_MOSAIC;
    /// <summary>
    ///  0-3 BG_Mosaic_H_Size (minus 1)
    /// </summary>
    DSReg A_MOSAIC_BG_Mosaic_H_Size;
    /// <summary>
    ///  4-7 BG_Mosaic_V_Size (minus 1)
    /// </summary>
    DSReg A_MOSAIC_BG_Mosaic_V_Size;
    /// <summary>
    ///  8-11 OBJ_Mosaic_H_Size (minus 1)
    /// </summary>
    DSReg A_MOSAIC_OBJ_Mosaic_H_Size;
    /// <summary>
    ///  12-15 OBJ_Mosaic_V_Size (minus 1)
    /// </summary>
    DSReg A_MOSAIC_OBJ_Mosaic_V_Size;
    /// <summary>
    /// Color Special Effects Selection 2 R/W
    /// </summary>
    DSReg A_BLDCNT;
    /// <summary>
    /// 0 (Background 0)
    /// </summary>
    DSReg A_BLDCNT_BG0_1st_Target_Pixel;
    /// <summary>
    /// 1 (Background 1)
    /// </summary>
    DSReg A_BLDCNT_BG1_1st_Target_Pixel;
    /// <summary>
    /// 2 (Background 2)
    /// </summary>
    DSReg A_BLDCNT_BG2_1st_Target_Pixel;
    /// <summary>
    /// 3 (Background 3)
    /// </summary>
    DSReg A_BLDCNT_BG3_1st_Target_Pixel;
    /// <summary>
    /// 4 (Top-most OBJ pixel)
    /// </summary>
    DSReg A_BLDCNT_OBJ_1st_Target_Pixel;
    /// <summary>
    /// 5 (Backdrop)
    /// </summary>
    DSReg A_BLDCNT_BD_1st_Target_Pixel;
    /// <summary>
    /// 6-7 (0-3, see below) 0 = None (Special effects disabled), 1 = Alpha Blending (1st+2nd Target mixed), 2 = Brightness Increase (1st Target becomes whiter), 3 = Brightness Decrease (1st Target becomes blacker)
    /// </summary>
    DSReg A_BLDCNT_Color_Special_Effect;
    /// <summary>
    /// 8 (Background 0)
    /// </summary>
    DSReg A_BLDCNT_BG0_2nd_Target_Pixel;
    /// <summary>
    /// 9 (Background 1)
    /// </summary>
    DSReg A_BLDCNT_BG1_2nd_Target_Pixel;
    /// <summary>
    /// 10 (Background 2)
    /// </summary>
    DSReg A_BLDCNT_BG2_2nd_Target_Pixel;
    /// <summary>
    /// 11 (Background 3)
    /// </summary>
    DSReg A_BLDCNT_BG3_2nd_Target_Pixel;
    /// <summary>
    /// 12 (Top-most OBJ pixel)
    /// </summary>
    DSReg A_BLDCNT_OBJ_2nd_Target_Pixel;
    /// <summary>
    /// 13 (Backdrop)
    /// </summary>
    DSReg A_BLDCNT_BD_2nd_Target_Pixel;
    /// <summary>
    /// Alpha Blending Coefficients 2 W
    /// </summary>
    DSReg A_BLDALPHA;
    /// <summary>
    /// 0-4 (1st Target) (0..16 = 0/16..16/16, 17..31=16/16)
    /// </summary>
    DSReg A_BLDALPHA_EVA_Coefficient;
    /// <summary>
    /// 8-12 (2nd Target) (0..16 = 0/16..16/16, 17..31=16/16)
    /// </summary>
    DSReg A_BLDALPHA_EVB_Coefficient;
    /// <summary>
    /// Brightness (Fade-In/Out) Coefficient 0-4 EVY Coefficient (Brightness) (0..16 = 0/16..16/16, 17..31=16/16
    /// </summary>
    DSReg A_BLDY;
    /// <summary>
    /// 3D Display Control Register (R/W)
    /// </summary>
    DSReg DISP3DCNT;
    /// <summary>
    /// 0 Texture Mapping (0=Disable, 1=Enable)
    /// </summary>
    DSReg DISP3DCNT_Texture_Mapping;
    /// <summary>
    /// 1 PolygonAttr Shading (0=Toon Shading, 1=Highlight Shading)
    /// </summary>
    DSReg DISP3DCNT_PolygonAttr_Shading;
    /// <summary>
    /// 2 Alpha-Test (0=Disable, 1=Enable) (see ALPHA_TEST_REF)
    /// </summary>
    DSReg DISP3DCNT_Alpha_Test;
    /// <summary>
    /// 3 Alpha-Blending (0=Disable, 1=Enable) (see various Alpha values)
    /// </summary>
    DSReg DISP3DCNT_Alpha_Blending;
    /// <summary>
    /// 4 Anti-Aliasing (0=Disable, 1=Enable)
    /// </summary>
    DSReg DISP3DCNT_Anti_Aliasing;
    /// <summary>
    /// 5 Edge-Marking (0=Disable, 1=Enable) (see EDGE_COLOR)
    /// </summary>
    DSReg DISP3DCNT_Edge_Marking;
    /// <summary>
    /// 6 Fog Color/Alpha Mode (0=Alpha and Color, 1=Only Alpha) (see FOG_COLOR)
    /// </summary>
    DSReg DISP3DCNT_Fog_Color_Alpha;
    /// <summary>
    /// 7 Fog Master Enable (0=Disable, 1=Enable)
    /// </summary>
    DSReg DISP3DCNT_Fog_Master_Enable;
    /// <summary>
    /// 8-11 Fog Depth Shift (FOG_STEP=400h shr FOG_SHIFT) (see FOG_OFFSET)
    /// </summary>
    DSReg DISP3DCNT_Fog_Depth_Shift;
    /// <summary>
    /// 12 Color Buffer RDLINES Underflow (0=None, 1=Underflow/Acknowledge)
    /// </summary>
    DSReg DISP3DCNT_RDLINES_Underflow;
    /// <summary>
    /// 13 Polygon/Vertex RAM Overflow (0=None, 1=Overflow/Acknowledge)
    /// </summary>
    DSReg DISP3DCNT_RAM_Overflow;
    /// <summary>
    /// 14 Rear-Plane Mode (0=Blank, 1=Bitmap)
    /// </summary>
    DSReg DISP3DCNT_Rear_Plane_Mode;
    /// <summary>
    /// Alpha Blending Coefficients 2 W
    /// </summary>
    DSReg DISPCAPCNT;
    /// <summary>
    /// 0-4 EVA (0..16 = Blending Factor for Source A)
    /// </summary>
    DSReg DISPCAPCNT_EVA;
    /// <summary>
    /// 8-12 EVB (0..16 = Blending Factor for Source B)
    /// </summary>
    DSReg DISPCAPCNT_EVB;
    /// <summary>
    /// 16-17 VRAM Write Block (0..3 = VRAM A..D) (VRAM must be allocated to LCDC)
    /// </summary>
    DSReg DISPCAPCNT_VRAM_Write_Block;
    /// <summary>
    /// 18-19 VRAM Write Offset (0=00000h, 0=08000h, 0=10000h, 0=18000h)
    /// </summary>
    DSReg DISPCAPCNT_VRAM_Write_Offset;
    /// <summary>
    /// 20-21 Capture Size (0=128x128, 1=256x64, 2=256x128, 3=256x192 dots)
    /// </summary>
    DSReg DISPCAPCNT_Capture_Size;
    /// <summary>
    /// 24 Source A (0=Graphics Screen BG+3D+OBJ, 1=3D Screen)
    /// </summary>
    DSReg DISPCAPCNT_Source_A;
    /// <summary>
    /// 25 Source B (0=VRAM, 1=Main Memory Display FIFO)
    /// </summary>
    DSReg DISPCAPCNT_Source_B;
    /// <summary>
    /// 26-27 VRAM Read Offset (0=00000h, 0=08000h, 0=10000h, 0=18000h)
    /// </summary>
    DSReg DISPCAPCNT_VRAM_Read_Offset;
    /// <summary>
    /// 29-30 Capture Source (0=Source A, 1=Source B, 2/3=Sources A+B blended)
    /// </summary>
    DSReg DISPCAPCNT_Capture_Source;
    /// <summary>
    /// 31 Capture Enable (0=Disable/Ready, 1=Enable/Busy)
    /// </summary>
    DSReg DISPCAPCNT_Capture_Enable;
    /// <summary>
    /// Main Memory Display FIFO (R?/W)
    /// </summary>
    DSReg DISP_MMEM_FIFO;
    /// <summary>
    /// Alpha Blending Coefficients 2 W
    /// </summary>
    DSReg A_MASTER_BRIGHT;
    /// <summary>
    /// Factor used for 6bit R,G,B Intensities (0-16, values >16 same as 16)
    /// </summary>
    DSReg A_MASTER_BRIGHT_Factor;
    /// <summary>
    /// Mode (0=Disable, 1=Up, 2=Down, 3=Reserved)
    /// </summary>
    DSReg A_MASTER_BRIGHT_Mode;
    /// <summary>
    /// LCD Control 2 R/W
    /// </summary>
    DSReg B_DISPCNT;
    /// <summary>
    /// BG Mode (0-5=Video Mode 0-6, 7=Prohibited)
    /// </summary>
    DSReg B_DISPCNT_BG_Mode;
    /// <summary>
    /// A only BG0 2D/3D Selection (instead CGB Mode) (0=2D, 1=3D)
    /// </summary>
    DSReg B_DISPCNT_BG0_2D_3D;
    /// <summary>
    /// Tile OBJ Mapping (0=2D; max 32KB, 1=1D; max 32KB..256KB)
    /// </summary>
    DSReg B_DISPCNT_Tile_OBJ_Mapping;
    /// <summary>
    /// Bitmap OBJ 2D-Dimension (0=128x512 dots, 1=256x256 dots)
    /// </summary>
    DSReg B_DISPCNT_Bitmap_OBJ_2D_Dim;
    /// <summary>
    /// Bitmap OBJ Mapping (0=2D; max 128KB, 1=1D; max 128KB..256KB)
    /// </summary>
    DSReg B_DISPCNT_Bitmap_OBJ_Mapping;
    /// <summary>
    /// Forced Blank (1=Allow FAST access to VRAM,Palette,OAM)
    /// </summary>
    DSReg B_DISPCNT_Forced_Blank;
    /// <summary>
    /// Screen Display BG0 (0=Off, 1=On)
    /// </summary>
    DSReg B_DISPCNT_Screen_Display_BG0;
    /// <summary>
    /// Screen Display BG1 (0=Off, 1=On)
    /// </summary>
    DSReg B_DISPCNT_Screen_Display_BG1;
    /// <summary>
    /// Screen Display BG2 (0=Off, 1=On)
    /// </summary>
    DSReg B_DISPCNT_Screen_Display_BG2;
    /// <summary>
    /// Screen Display BG3 (0=Off, 1=On)
    /// </summary>
    DSReg B_DISPCNT_Screen_Display_BG3;
    /// <summary>
    /// Screen Display OBJ (0=Off, 1=On)
    /// </summary>
    DSReg B_DISPCNT_Screen_Display_OBJ;
    /// <summary>
    /// Window 0 Display Flag (0=Off, 1=On)
    /// </summary>
    DSReg B_DISPCNT_Window_0_Display_Flag;
    /// <summary>
    /// Window 1 Display Flag (0=Off, 1=On)
    /// </summary>
    DSReg B_DISPCNT_Window_1_Display_Flag;
    /// <summary>
    /// OBJ Window Display Flag (0=Off, 1=On)
    /// </summary>
    DSReg B_DISPCNT_OBJ_Wnd_Display_Flag;
    /// <summary>
    /// 16-17 A+B Display Mode (Engine A: 0..3, Engine B: 0..1, GBA: Green Swap)
    /// </summary>
    DSReg B_DISPCNT_Display_Mode;
    /// <summary>
    /// 18-19 A VRAM block (0..3=VRAM A..D) (For Capture & above Display Mode=2)
    /// </summary>
    DSReg B_DISPCNT_VRAM_block;
    /// <summary>
    /// 20-21 A+B Tile OBJ 1D-Boundary (see Bit4)
    /// </summary>
    DSReg B_DISPCNT_Tile_OBJ_1D_Boundary;
    /// <summary>
    /// 22 A Bitmap OBJ 1D-Boundary (see Bit5-6)
    /// </summary>
    DSReg B_DISPCNT_Bitmap_OBJ_1D_Boundary;
    /// <summary>
    /// 23 A+B OBJ Processing during H-Blank (was located in Bit5 on GBA)
    /// </summary>
    DSReg B_DISPCNT_OBJ_Process_H_Blank;
    /// <summary>
    /// 24-26 A Character Base (in 64K steps) (merged with 16K step in BGxCNT)
    /// </summary>
    DSReg B_DISPCNT_Character_Base;
    /// <summary>
    /// 27-29 A Screen Base (in 64K steps) (merged with 2K step in BGxCNT)
    /// </summary>
    DSReg B_DISPCNT_Screen_Base;
    /// <summary>
    /// 30 A+B BG Extended Palettes (0=Disable, 1=Enable)
    /// </summary>
    DSReg B_DISPCNT_BG_Extended_Palettes;
    /// <summary>
    /// 31 A+B OBJ Extended Palettes (0=Disable, 1=Enable
    /// </summary>
    DSReg B_DISPCNT_OBJ_Extended_Palettes;
    /// <summary>
    /// BG0 Control 2 R/W
    /// </summary>
    DSReg B_BG0CNT;
    /// <summary>
    /// BG Priority (0-3, 0=Highest)
    /// </summary>
    DSReg B_BG0CNT_BG_Priority;
    /// <summary>
    /// Character Base Block (0-15, in units of 16 KBytes) (=BG Tile Data)
    /// </summary>
    DSReg B_BG0CNT_Character_Base_Block;
    /// <summary>
    /// Mosaic (0=Disable, 1=Enable)
    /// </summary>
    DSReg B_BG0CNT_Mosaic;
    /// <summary>
    /// Colors/Palettes (0=16/16, 1=256/1)
    /// </summary>
    DSReg B_BG0CNT_Colors_Palettes;
    /// <summary>
    /// Screen Base Block (0-31, in units of 2 KBytes) (=BG Map Data)
    /// </summary>
    DSReg B_BG0CNT_Screen_Base_Block;
    /// <summary>
    /// Ext Palette Slot for BG0/BG1
    /// </summary>
    DSReg B_BG0CNT_Ext_Palette_Slot;
    /// <summary>
    /// Screen Size (0-3)
    /// </summary>
    DSReg B_BG0CNT_Screen_Size;
    /// <summary>
    /// BG1 Control 2 R/W
    /// </summary>
    DSReg B_BG1CNT;
    /// <summary>
    /// BG Priority (0-3, 0=Highest)
    /// </summary>
    DSReg B_BG1CNT_BG_Priority;
    /// <summary>
    /// Character Base Block (0-15, in units of 16 KBytes) (=BG Tile Data)
    /// </summary>
    DSReg B_BG1CNT_Character_Base_Block;
    /// <summary>
    /// Mosaic (0=Disable, 1=Enable)
    /// </summary>
    DSReg B_BG1CNT_Mosaic;
    /// <summary>
    /// Colors/Palettes (0=16/16, 1=256/1)
    /// </summary>
    DSReg B_BG1CNT_Colors_Palettes;
    /// <summary>
    /// Screen Base Block (0-31, in units of 2 KBytes) (=BG Map Data)
    /// </summary>
    DSReg B_BG1CNT_Screen_Base_Block;
    /// <summary>
    /// Ext Palette Slot for BG0/BG1
    /// </summary>
    DSReg B_BG1CNT_Ext_Palette_Slot;
    /// <summary>
    /// Screen Size (0-3)
    /// </summary>
    DSReg B_BG1CNT_Screen_Size;
    /// <summary>
    /// BG2 Control 2 R/W
    /// </summary>
    DSReg B_BG2CNT;
    /// <summary>
    /// BG Priority (0-3, 0=Highest)
    /// </summary>
    DSReg B_BG2CNT_BG_Priority;
    /// <summary>
    /// Character Base Block (0-15, in units of 16 KBytes) (=BG Tile Data)
    /// </summary>
    DSReg B_BG2CNT_Character_Base_Block;
    /// <summary>
    /// Mosaic (0=Disable, 1=Enable)
    /// </summary>
    DSReg B_BG2CNT_Mosaic;
    /// <summary>
    /// Colors/Palettes (0=16/16, 1=256/1)
    /// </summary>
    DSReg B_BG2CNT_Colors_Palettes;
    /// <summary>
    /// Screen Base Block (0-31, in units of 2 KBytes) (=BG Map Data)
    /// </summary>
    DSReg B_BG2CNT_Screen_Base_Block;
    /// <summary>
    /// Display Area Overflow (0=Transparent, 1=Wraparound; BG2CNT/BG3CNT only)
    /// </summary>
    DSReg B_BG2CNT_Display_Area_Overflow;
    /// <summary>
    /// Screen Size (0-3)
    /// </summary>
    DSReg B_BG2CNT_Screen_Size;
    /// <summary>
    /// BG3 Control 2 R/W
    /// </summary>
    DSReg B_BG3CNT;
    /// <summary>
    /// BG Priority (0-3, 0=Highest)
    /// </summary>
    DSReg B_BG3CNT_BG_Priority;
    /// <summary>
    /// Character Base Block (0-15, in units of 16 KBytes) (=BG Tile Data)
    /// </summary>
    DSReg B_BG3CNT_Character_Base_Block;
    /// <summary>
    /// Mosaic (0=Disable, 1=Enable)
    /// </summary>
    DSReg B_BG3CNT_Mosaic;
    /// <summary>
    /// Colors/Palettes (0=16/16, 1=256/1)
    /// </summary>
    DSReg B_BG3CNT_Colors_Palettes;
    /// <summary>
    /// Screen Base Block (0-31, in units of 2 KBytes) (=BG Map Data)
    /// </summary>
    DSReg B_BG3CNT_Screen_Base_Block;
    /// <summary>
    /// Display Area Overflow (0=Transparent, 1=Wraparound; BG2CNT/BG3CNT only)
    /// </summary>
    DSReg B_BG3CNT_Display_Area_Overflow;
    /// <summary>
    /// Screen Size (0-3)
    /// </summary>
    DSReg B_BG3CNT_Screen_Size;
    /// <summary>
    /// BG0 X-Offset 2 W
    /// </summary>
    DSReg B_BG0HOFS;
    /// <summary>
    /// BG0 Y-Offset 2 W
    /// </summary>
    DSReg B_BG0VOFS;
    /// <summary>
    /// BG1 X-Offset 2 W
    /// </summary>
    DSReg B_BG1HOFS;
    /// <summary>
    /// BG1 Y-Offset 2 W
    /// </summary>
    DSReg B_BG1VOFS;
    /// <summary>
    /// BG2 X-Offset 2 W
    /// </summary>
    DSReg B_BG2HOFS;
    /// <summary>
    /// BG2 Y-Offset 2 W
    /// </summary>
    DSReg B_BG2VOFS;
    /// <summary>
    /// BG3 X-Offset 2 W
    /// </summary>
    DSReg B_BG3HOFS;
    /// <summary>
    /// BG3 Y-Offset 2 W
    /// </summary>
    DSReg B_BG3VOFS;
    /// <summary>
    /// BG2 Rotation/Scaling Parameter A (dx) 2 W
    /// </summary>
    DSReg B_BG2RotScaleParDX;
    /// <summary>
    /// BG2 Rotation/Scaling Parameter B (dmx) 2 W
    /// </summary>
    DSReg B_BG2RotScaleParDMX;
    /// <summary>
    /// BG2 Rotation/Scaling Parameter C (dy) 2 W
    /// </summary>
    DSReg B_BG2RotScaleParDY;
    /// <summary>
    /// BG2 Rotation/Scaling Parameter D (dmy) 2 W
    /// </summary>
    DSReg B_BG2RotScaleParDMY;
    /// <summary>
    /// BG2 Reference Point X-Coordinate 4 W
    /// </summary>
    DSReg B_BG2RefX;
    /// <summary>
    /// BG2 Reference Point Y-Coordinate 4 W
    /// </summary>
    DSReg B_BG2RefY;
    /// <summary>
    /// BG3 Rotation/Scaling Parameter A (dx) 2 W
    /// </summary>
    DSReg B_BG3RotScaleParDX;
    /// <summary>
    /// BG3 Rotation/Scaling Parameter B (dmx) 2 W
    /// </summary>
    DSReg B_BG3RotScaleParDMX;
    /// <summary>
    /// BG3 Rotation/Scaling Parameter C (dy) 2 W
    /// </summary>
    DSReg B_BG3RotScaleParDY;
    /// <summary>
    /// BG3 Rotation/Scaling Parameter D (dmy) 2 W
    /// </summary>
    DSReg B_BG3RotScaleParDMY;
    /// <summary>
    /// BG3 Reference Point X-Coordinate 4 W
    /// </summary>
    DSReg B_BG3RefX;
    /// <summary>
    /// BG3 Reference Point Y-Coordinate 4 W
    /// </summary>
    DSReg B_BG3RefY;
    /// <summary>
    /// Window 0 Horizontal Dimensions 2 W
    /// </summary>
    DSReg B_WIN0H;
    /// <summary>
    /// Window 0 Horizontal Dimensions 2 W
    /// </summary>
    DSReg B_WIN0H_X2;
    /// <summary>
    /// Window 0 Horizontal Dimensions 2 W
    /// </summary>
    DSReg B_WIN0H_X1;
    /// <summary>
    /// Window 1 Horizontal Dimensions 2 W
    /// </summary>
    DSReg B_WIN1H;
    /// <summary>
    /// Window 1 Horizontal Dimensions 2 W
    /// </summary>
    DSReg B_WIN1H_X2;
    /// <summary>
    /// Window 1 Horizontal Dimensions 2 W
    /// </summary>
    DSReg B_WIN1H_X1;
    /// <summary>
    /// Window 0 Vertical Dimensions 2 W
    /// </summary>
    DSReg B_WIN0V;
    /// <summary>
    /// Window 0 Vertical Dimensions 2 W
    /// </summary>
    DSReg B_WIN0V_Y2;
    /// <summary>
    /// Window 0 Vertical Dimensions 2 W
    /// </summary>
    DSReg B_WIN0V_Y1;
    /// <summary>
    /// Window 1 Vertical Dimensions 2 W
    /// </summary>
    DSReg B_WIN1V;
    /// <summary>
    /// Window 1 Vertical Dimensions 2 W
    /// </summary>
    DSReg B_WIN1V_Y2;
    /// <summary>
    /// Window 1 Vertical Dimensions 2 W
    /// </summary>
    DSReg B_WIN1V_Y1;
    /// <summary>
    /// Inside of Window 0 and 1 2 R/W
    /// </summary>
    DSReg B_WININ;
    /// <summary>
    /// 0-3 Window_0_BG0_BG3_Enable (0=No Display, 1=Display)
    /// </summary>
    DSReg B_WININ_Window_0_BG0_Enable;
    /// <summary>
    /// 0-3 Window_0_BG0_BG3_Enable (0=No Display, 1=Display)
    /// </summary>
    DSReg B_WININ_Window_0_BG1_Enable;
    /// <summary>
    /// 0-3 Window_0_BG0_BG3_Enable (0=No Display, 1=Display)
    /// </summary>
    DSReg B_WININ_Window_0_BG2_Enable;
    /// <summary>
    /// 0-3 Window_0_BG0_BG3_Enable (0=No Display, 1=Display)
    /// </summary>
    DSReg B_WININ_Window_0_BG3_Enable;
    /// <summary>
    /// 4 Window_0_OBJ_Enable (0=No Display, 1=Display)
    /// </summary>
    DSReg B_WININ_Window_0_OBJ_Enable;
    /// <summary>
    /// 5 Window_0_Special_Effect (0=Disable, 1=Enable)
    /// </summary>
    DSReg B_WININ_Window_0_Special_Effect;
    /// <summary>
    /// 8-11 Window_1_BG0_BG3_Enable (0=No Display, 1=Display)
    /// </summary>
    DSReg B_WININ_Window_1_BG0_Enable;
    /// <summary>
    /// 8-11 Window_1_BG0_BG3_Enable (0=No Display, 1=Display)
    /// </summary>
    DSReg B_WININ_Window_1_BG1_Enable;
    /// <summary>
    /// 8-11 Window_1_BG0_BG3_Enable (0=No Display, 1=Display)
    /// </summary>
    DSReg B_WININ_Window_1_BG2_Enable;
    /// <summary>
    /// 8-11 Window_1_BG0_BG3_Enable (0=No Display, 1=Display)
    /// </summary>
    DSReg B_WININ_Window_1_BG3_Enable;
    /// <summary>
    /// 12 Window_1_OBJ_Enable (0=No Display, 1=Display)
    /// </summary>
    DSReg B_WININ_Window_1_OBJ_Enable;
    /// <summary>
    /// 13 Window_1_Special_Effect (0=Disable, 1=Enable)
    /// </summary>
    DSReg B_WININ_Window_1_Special_Effect;
    /// <summary>
    /// Inside of OBJ Window & Outside of Windows 2 R/W
    /// </summary>
    DSReg B_WINOUT;
    /// <summary>
    /// 0-3 Outside_BG0_BG3_Enable (0=No Display, 1=Display)
    /// </summary>
    DSReg B_WINOUT_Outside_BG0_Enable;
    /// <summary>
    /// 0-3 Outside_BG0_BG3_Enable (0=No Display, 1=Display)
    /// </summary>
    DSReg B_WINOUT_Outside_BG1_Enable;
    /// <summary>
    /// 0-3 Outside_BG0_BG3_Enable (0=No Display, 1=Display)
    /// </summary>
    DSReg B_WINOUT_Outside_BG2_Enable;
    /// <summary>
    /// 0-3 Outside_BG0_BG3_Enable (0=No Display, 1=Display)
    /// </summary>
    DSReg B_WINOUT_Outside_BG3_Enable;
    /// <summary>
    /// 4 Outside_OBJ_Enable (0=No Display, 1=Display)
    /// </summary>
    DSReg B_WINOUT_Outside_OBJ_Enable;
    /// <summary>
    /// 5 Outside_Special_Effect (0=Disable, 1=Enable)
    /// </summary>
    DSReg B_WINOUT_Outside_Special_Effect;
    /// <summary>
    /// 8-11 object window_BG0_BG3_Enable (0=No Display, 1=Display)
    /// </summary>
    DSReg B_WINOUT_Objwnd_BG0_Enable;
    /// <summary>
    /// 8-11 object window_BG0_BG3_Enable (0=No Display, 1=Display)
    /// </summary>
    DSReg B_WINOUT_Objwnd_BG1_Enable;
    /// <summary>
    /// 8-11 object window_BG0_BG3_Enable (0=No Display, 1=Display)
    /// </summary>
    DSReg B_WINOUT_Objwnd_BG2_Enable;
    /// <summary>
    /// 8-11 object window_BG0_BG3_Enable (0=No Display, 1=Display)
    /// </summary>
    DSReg B_WINOUT_Objwnd_BG3_Enable;
    /// <summary>
    /// 12 object window_OBJ_Enable (0=No Display, 1=Display)
    /// </summary>
    DSReg B_WINOUT_Objwnd_OBJ_Enable;
    /// <summary>
    /// 13 object window_Special_Effect (0=Disable, 1=Enable)
    /// </summary>
    DSReg B_WINOUT_Objwnd_Special_Effect;
    /// <summary>
    /// Mosaic Size 2 W
    /// </summary>
    DSReg B_MOSAIC;
    /// <summary>
    ///  0-3 BG_Mosaic_H_Size (minus 1)
    /// </summary>
    DSReg B_MOSAIC_BG_Mosaic_H_Size;
    /// <summary>
    ///  4-7 BG_Mosaic_V_Size (minus 1)
    /// </summary>
    DSReg B_MOSAIC_BG_Mosaic_V_Size;
    /// <summary>
    ///  8-11 OBJ_Mosaic_H_Size (minus 1)
    /// </summary>
    DSReg B_MOSAIC_OBJ_Mosaic_H_Size;
    /// <summary>
    ///  12-15 OBJ_Mosaic_V_Size (minus 1)
    /// </summary>
    DSReg B_MOSAIC_OBJ_Mosaic_V_Size;
    /// <summary>
    /// Color Special Effects Selection 2 R/W
    /// </summary>
    DSReg B_BLDCNT;
    /// <summary>
    /// 0 (Background 0)
    /// </summary>
    DSReg B_BLDCNT_BG0_1st_Target_Pixel;
    /// <summary>
    /// 1 (Background 1)
    /// </summary>
    DSReg B_BLDCNT_BG1_1st_Target_Pixel;
    /// <summary>
    /// 2 (Background 2)
    /// </summary>
    DSReg B_BLDCNT_BG2_1st_Target_Pixel;
    /// <summary>
    /// 3 (Background 3)
    /// </summary>
    DSReg B_BLDCNT_BG3_1st_Target_Pixel;
    /// <summary>
    /// 4 (Top-most OBJ pixel)
    /// </summary>
    DSReg B_BLDCNT_OBJ_1st_Target_Pixel;
    /// <summary>
    /// 5 (Backdrop)
    /// </summary>
    DSReg B_BLDCNT_BD_1st_Target_Pixel;
    /// <summary>
    /// 6-7 (0-3, see below) 0 = None (Special effects disabled), 1 = Alpha Blending (1st+2nd Target mixed), 2 = Brightness Increase (1st Target becomes whiter), 3 = Brightness Decrease (1st Target becomes blacker)
    /// </summary>
    DSReg B_BLDCNT_Color_Special_Effect;
    /// <summary>
    /// 8 (Background 0)
    /// </summary>
    DSReg B_BLDCNT_BG0_2nd_Target_Pixel;
    /// <summary>
    /// 9 (Background 1)
    /// </summary>
    DSReg B_BLDCNT_BG1_2nd_Target_Pixel;
    /// <summary>
    /// 10 (Background 2)
    /// </summary>
    DSReg B_BLDCNT_BG2_2nd_Target_Pixel;
    /// <summary>
    /// 11 (Background 3)
    /// </summary>
    DSReg B_BLDCNT_BG3_2nd_Target_Pixel;
    /// <summary>
    /// 12 (Top-most OBJ pixel)
    /// </summary>
    DSReg B_BLDCNT_OBJ_2nd_Target_Pixel;
    /// <summary>
    /// 13 (Backdrop)
    /// </summary>
    DSReg B_BLDCNT_BD_2nd_Target_Pixel;
    /// <summary>
    /// Alpha Blending Coefficients 2 W
    /// </summary>
    DSReg B_BLDALPHA;
    /// <summary>
    /// 0-4 (1st Target) (0..16 = 0/16..16/16, 17..31=16/16)
    /// </summary>
    DSReg B_BLDALPHA_EVA_Coefficient;
    /// <summary>
    /// 8-12 (2nd Target) (0..16 = 0/16..16/16, 17..31=16/16)
    /// </summary>
    DSReg B_BLDALPHA_EVB_Coefficient;
    /// <summary>
    /// Brightness (Fade-In/Out) Coefficient 0-4 EVY Coefficient (Brightness) (0..16 = 0/16..16/16, 17..31=16/16
    /// </summary>
    DSReg B_BLDY;
    /// <summary>
    /// Alpha Blending Coefficients 2 W
    /// </summary>
    DSReg B_MASTER_BRIGHT;
    /// <summary>
    /// Factor used for 6bit R,G,B Intensities (0-16, values >16 same as 16)
    /// </summary>
    DSReg B_MASTER_BRIGHT_Factor;
    /// <summary>
    /// Mode (0=Disable, 1=Up, 2=Down, 3=Reserved)
    /// </summary>
    DSReg B_MASTER_BRIGHT_Mode;

    RegSect_display9();
};

class RegSect_dma9
{
public:
    /// <summary>
    /// Source Address 4 W
    /// </summary>
    DSReg DMA0SAD;
    /// <summary>
    /// Destination Address 4 W
    /// </summary>
    DSReg DMA0DAD;
    /// <summary>
    /// Word Count 2 W
    /// </summary>
    DSReg DMA0CNT_L;
    /// <summary>
    /// Control 2 R/W
    /// </summary>
    DSReg DMA0CNT_H;
    /// <summary>
    /// 5-6 Dest Addr Control (0=Increment,1=Decrement,2=Fixed,3=Increment/Reload)
    /// </summary>
    DSReg DMA0CNT_H_Dest_Addr_Control;
    /// <summary>
    /// 7-8 Source Adr Control (0=Increment,1=Decrement,2=Fixed,3=Prohibited)
    /// </summary>
    DSReg DMA0CNT_H_Source_Adr_Control;
    /// <summary>
    /// 9 DMA Repeat (0=Off, 1=On) (Must be zero if Bit 11 set)
    /// </summary>
    DSReg DMA0CNT_H_DMA_Repeat;
    /// <summary>
    /// 10 DMA Transfer Type (0=16bit, 1=32bit)
    /// </summary>
    DSReg DMA0CNT_H_DMA_Transfer_Type;
    /// <summary>
    /// 11-13 Transfer mode 0 Start Immediately, 1 Start at V-Blank, 2 Start at H-Blank (paused during V-Blank), 3 Synchronize to start of display , 4 Main memory display, 5 DS Cartridge Slot ,6 GBA Cartridge Slot ,7 Geometry Command FIFO
    /// </summary>
    DSReg DMA0CNT_H_DMA_Start_Timing;
    /// <summary>
    /// 14 IRQ upon end of Word Count (0=Disable, 1=Enable)
    /// </summary>
    DSReg DMA0CNT_H_IRQ_on;
    /// <summary>
    /// 15 DMA Enable (0=Off, 1=On)
    /// </summary>
    DSReg DMA0CNT_H_DMA_Enable;
    /// <summary>
    /// Source Address 4 W
    /// </summary>
    DSReg DMA1SAD;
    /// <summary>
    /// Destination Address 4 W
    /// </summary>
    DSReg DMA1DAD;
    /// <summary>
    /// Word Count 2 W
    /// </summary>
    DSReg DMA1CNT_L;
    /// <summary>
    /// Control 2 R/W
    /// </summary>
    DSReg DMA1CNT_H;
    /// <summary>
    /// 5-6 Dest Addr Control (0=Increment,1=Decrement,2=Fixed,3=Increment/Reload)
    /// </summary>
    DSReg DMA1CNT_H_Dest_Addr_Control;
    /// <summary>
    /// 7-8 Source Adr Control (0=Increment,1=Decrement,2=Fixed,3=Prohibited)
    /// </summary>
    DSReg DMA1CNT_H_Source_Adr_Control;
    /// <summary>
    /// 9 DMA Repeat (0=Off, 1=On) (Must be zero if Bit 11 set)
    /// </summary>
    DSReg DMA1CNT_H_DMA_Repeat;
    /// <summary>
    /// 10 DMA Transfer Type (0=16bit, 1=32bit)
    /// </summary>
    DSReg DMA1CNT_H_DMA_Transfer_Type;
    /// <summary>
    /// 11-13 Transfer mode 0 Start Immediately, 1 Start at V-Blank, 2 Start at H-Blank (paused during V-Blank), 3 Synchronize to start of display , 4 Main memory display, 5 DS Cartridge Slot ,6 GBA Cartridge Slot ,7 Geometry Command FIFO
    /// </summary>
    DSReg DMA1CNT_H_DMA_Start_Timing;
    /// <summary>
    /// 14 IRQ upon end of Word Count (0=Disable, 1=Enable)
    /// </summary>
    DSReg DMA1CNT_H_IRQ_on;
    /// <summary>
    /// 15 DMA Enable (0=Off, 1=On)
    /// </summary>
    DSReg DMA1CNT_H_DMA_Enable;
    /// <summary>
    /// Source Address 4 W
    /// </summary>
    DSReg DMA2SAD;
    /// <summary>
    /// Destination Address 4 W
    /// </summary>
    DSReg DMA2DAD;
    /// <summary>
    /// Word Count 2 W
    /// </summary>
    DSReg DMA2CNT_L;
    /// <summary>
    /// Control 2 R/W
    /// </summary>
    DSReg DMA2CNT_H;
    /// <summary>
    /// 5-6 Dest Addr Control (0=Increment,1=Decrement,2=Fixed,3=Increment/Reload)
    /// </summary>
    DSReg DMA2CNT_H_Dest_Addr_Control;
    /// <summary>
    /// 7-8 Source Adr Control (0=Increment,1=Decrement,2=Fixed,3=Prohibited)
    /// </summary>
    DSReg DMA2CNT_H_Source_Adr_Control;
    /// <summary>
    /// 9 DMA Repeat (0=Off, 1=On) (Must be zero if Bit 11 set)
    /// </summary>
    DSReg DMA2CNT_H_DMA_Repeat;
    /// <summary>
    /// 10 DMA Transfer Type (0=16bit, 1=32bit)
    /// </summary>
    DSReg DMA2CNT_H_DMA_Transfer_Type;
    /// <summary>
    /// 11-13 Transfer mode 0 Start Immediately, 1 Start at V-Blank, 2 Start at H-Blank (paused during V-Blank), 3 Synchronize to start of display , 4 Main memory display, 5 DS Cartridge Slot ,6 GBA Cartridge Slot ,7 Geometry Command FIFO
    /// </summary>
    DSReg DMA2CNT_H_DMA_Start_Timing;
    /// <summary>
    /// 14 IRQ upon end of Word Count (0=Disable, 1=Enable)
    /// </summary>
    DSReg DMA2CNT_H_IRQ_on;
    /// <summary>
    /// 15 DMA Enable (0=Off, 1=On)
    /// </summary>
    DSReg DMA2CNT_H_DMA_Enable;
    /// <summary>
    /// Source Address 4 W
    /// </summary>
    DSReg DMA3SAD;
    /// <summary>
    /// Destination Address 4 W
    /// </summary>
    DSReg DMA3DAD;
    /// <summary>
    /// Word Count 2 W
    /// </summary>
    DSReg DMA3CNT_L;
    /// <summary>
    /// Control 2 R/W
    /// </summary>
    DSReg DMA3CNT_H;
    /// <summary>
    /// 5-6 Dest Addr Control (0=Increment,1=Decrement,2=Fixed,3=Increment/Reload)
    /// </summary>
    DSReg DMA3CNT_H_Dest_Addr_Control;
    /// <summary>
    /// 7-8 Source Adr Control (0=Increment,1=Decrement,2=Fixed,3=Prohibited)
    /// </summary>
    DSReg DMA3CNT_H_Source_Adr_Control;
    /// <summary>
    /// 9 DMA Repeat (0=Off, 1=On) (Must be zero if Bit 11 set)
    /// </summary>
    DSReg DMA3CNT_H_DMA_Repeat;
    /// <summary>
    /// 10 DMA Transfer Type (0=16bit, 1=32bit)
    /// </summary>
    DSReg DMA3CNT_H_DMA_Transfer_Type;
    /// <summary>
    /// 11 Game Pak DRQ - DMA3 only - (0=Normal, 1=DRQ <from> Game Pak, DMA3)
    /// </summary>
    DSReg DMA3CNT_H_Game_Pak_DRQ;
    /// <summary>
    /// 11-13 Transfer mode 0 Start Immediately, 1 Start at V-Blank, 2 Start at H-Blank (paused during V-Blank), 3 Synchronize to start of display , 4 Main memory display, 5 DS Cartridge Slot ,6 GBA Cartridge Slot ,7 Geometry Command FIFO
    /// </summary>
    DSReg DMA3CNT_H_DMA_Start_Timing;
    /// <summary>
    /// 14 IRQ upon end of Word Count (0=Disable, 1=Enable)
    /// </summary>
    DSReg DMA3CNT_H_IRQ_on;
    /// <summary>
    /// 15 DMA Enable (0=Off, 1=On)
    /// </summary>
    DSReg DMA3CNT_H_DMA_Enable;
    /// <summary>
    /// DMA0FILL - DMA 0 Filldata (R/W)
    /// </summary>
    DSReg DMA0FILL;
    /// <summary>
    /// DMA1FILL - DMA 1 Filldata (R/W)
    /// </summary>
    DSReg DMA1FILL;
    /// <summary>
    /// DMA2FILL - DMA 2 Filldata (R/W)
    /// </summary>
    DSReg DMA2FILL;
    /// <summary>
    /// DMA3FILL - DMA 3 Filldata (R/W)
    /// </summary>
    DSReg DMA3FILL;

    RegSect_dma9();
};

class RegSect_timer9
{
public:
    /// <summary>
    /// Timer 0 Counter/Reload 2 R/W
    /// </summary>
    DSReg TM0CNT_L;
    /// <summary>
    /// Timer 0 Control 2 R/W
    /// </summary>
    DSReg TM0CNT_H;
    /// <summary>
    /// Prescaler Selection (0=F/1, 1=F/64, 2=F/256, 3=F/1024)
    /// </summary>
    DSReg TM0CNT_H_Prescaler;
    /// <summary>
    /// Count-up Timing (0=Normal, 1=See below)
    /// </summary>
    DSReg TM0CNT_H_Count_up;
    /// <summary>
    /// Timer IRQ Enable (0=Disable, 1=IRQ on Timer overflow)
    /// </summary>
    DSReg TM0CNT_H_Timer_IRQ_Enable;
    /// <summary>
    /// Timer Start/Stop (0=Stop, 1=Operate)
    /// </summary>
    DSReg TM0CNT_H_Timer_Start_Stop;
    /// <summary>
    /// Timer 1 Counter/Reload 2 R/W
    /// </summary>
    DSReg TM1CNT_L;
    /// <summary>
    /// Timer 1 Control 2 R/W
    /// </summary>
    DSReg TM1CNT_H;
    /// <summary>
    /// Prescaler Selection (0=F/1, 1=F/64, 2=F/256, 3=F/1024)
    /// </summary>
    DSReg TM1CNT_H_Prescaler;
    /// <summary>
    /// Count-up Timing (0=Normal, 1=See below)
    /// </summary>
    DSReg TM1CNT_H_Count_up;
    /// <summary>
    /// Timer IRQ Enable (0=Disable, 1=IRQ on Timer overflow)
    /// </summary>
    DSReg TM1CNT_H_Timer_IRQ_Enable;
    /// <summary>
    /// Timer Start/Stop (0=Stop, 1=Operate)
    /// </summary>
    DSReg TM1CNT_H_Timer_Start_Stop;
    /// <summary>
    /// Timer 2 Counter/Reload 2 R/W
    /// </summary>
    DSReg TM2CNT_L;
    /// <summary>
    /// Timer 2 Control 2 R/W
    /// </summary>
    DSReg TM2CNT_H;
    /// <summary>
    /// Prescaler Selection (0=F/1, 1=F/64, 2=F/256, 3=F/1024)
    /// </summary>
    DSReg TM2CNT_H_Prescaler;
    /// <summary>
    /// Count-up Timing (0=Normal, 1=See below)
    /// </summary>
    DSReg TM2CNT_H_Count_up;
    /// <summary>
    /// Timer IRQ Enable (0=Disable, 1=IRQ on Timer overflow)
    /// </summary>
    DSReg TM2CNT_H_Timer_IRQ_Enable;
    /// <summary>
    /// Timer Start/Stop (0=Stop, 1=Operate)
    /// </summary>
    DSReg TM2CNT_H_Timer_Start_Stop;
    /// <summary>
    /// Timer 3 Counter/Reload 2 R/W
    /// </summary>
    DSReg TM3CNT_L;
    /// <summary>
    /// Timer 3 Control 2 R/W
    /// </summary>
    DSReg TM3CNT_H;
    /// <summary>
    /// Prescaler Selection (0=F/1, 1=F/64, 2=F/256, 3=F/1024)
    /// </summary>
    DSReg TM3CNT_H_Prescaler;
    /// <summary>
    /// Count-up Timing (0=Normal, 1=See below)
    /// </summary>
    DSReg TM3CNT_H_Count_up;
    /// <summary>
    /// Timer IRQ Enable (0=Disable, 1=IRQ on Timer overflow)
    /// </summary>
    DSReg TM3CNT_H_Timer_IRQ_Enable;
    /// <summary>
    /// Timer Start/Stop (0=Stop, 1=Operate)
    /// </summary>
    DSReg TM3CNT_H_Timer_Start_Stop;

    RegSect_timer9();
};

class RegSect_keypad9
{
public:
    /// <summary>
    /// Key Status 2 R
    /// </summary>
    DSReg KEYINPUT;
    /// <summary>
    /// Key Interrupt Control 2 R/W
    /// </summary>
    DSReg KEYCNT;

    RegSect_keypad9();
};

class RegSect_system9
{
public:
    /// <summary>
    /// IPC Synchronize Register (R/W)
    /// </summary>
    DSReg IPCSYNC;
    /// <summary>
    /// 0-3 R Data input from IPCSYNC Bit8-11 of remote CPU (00h..0Fh)
    /// </summary>
    DSReg IPCSYNC_Data_from_IPCSYNC;
    /// <summary>
    /// 8-11 R/W Data output to IPCSYNC Bit0-3 of remote CPU (00h..0Fh)
    /// </summary>
    DSReg IPCSYNC_Data_to_IPCSYNC;
    /// <summary>
    /// 13 W Send IRQ to remote CPU (0=None, 1=Send IRQ)
    /// </summary>
    DSReg IPCSYNC_IRQ_to_remote_CPU;
    /// <summary>
    /// 14 R/W Enable IRQ from remote CPU (0=Disable, 1=Enable)
    /// </summary>
    DSReg IPCSYNC_Ena_IRQ_from_remote_CPU;
    /// <summary>
    /// IPC Fifo Control Register (R/W)
    /// </summary>
    DSReg IPCFIFOCNT;
    /// <summary>
    /// 0 R Send Fifo Empty Status (0=Not Empty, 1=Empty)
    /// </summary>
    DSReg IPCFIFOCNT_Send_Fifo_Empty_Status;
    /// <summary>
    /// 1 R Send Fifo Full Status (0=Not Full, 1=Full)
    /// </summary>
    DSReg IPCFIFOCNT_Send_Fifo_Full_Status;
    /// <summary>
    /// 2 R/W Send Fifo Empty IRQ (0=Disable, 1=Enable)
    /// </summary>
    DSReg IPCFIFOCNT_Send_Fifo_Empty_IRQ;
    /// <summary>
    /// 3 W Send Fifo Clear (0=Nothing, 1=Flush Send Fifo)
    /// </summary>
    DSReg IPCFIFOCNT_Send_Fifo_Clear;
    /// <summary>
    /// 8 R Receive Fifo Empty (0=Not Empty, 1=Empty)
    /// </summary>
    DSReg IPCFIFOCNT_Receive_Fifo_Empty;
    /// <summary>
    /// 9 R Receive Fifo Full (0=Not Full, 1=Full)
    /// </summary>
    DSReg IPCFIFOCNT_Receive_Fifo_Full;
    /// <summary>
    /// 10 R/W Receive Fifo Not Empty IRQ (0=Disable, 1=Enable)
    /// </summary>
    DSReg IPCFIFOCNT_Receive_Fifo_Not_Empty_IRQ;
    /// <summary>
    /// 14 R/W Error, Read Empty/Send Full (0=No Error, 1=Error/Acknowledge)
    /// </summary>
    DSReg IPCFIFOCNT_Error_Read_Empty_Send_Full;
    /// <summary>
    /// 15 R/W Enable Send/Receive Fifo (0=Disable, 1=Enable)
    /// </summary>
    DSReg IPCFIFOCNT_Enable_Send_Receive_Fifo;
    /// <summary>
    /// IPC Send Fifo (W)
    /// </summary>
    DSReg IPCFIFOSEND;
    /// <summary>
    /// IPC Receive Fifo (R)
    /// </summary>
    DSReg IPCFIFORECV;
    /// <summary>
    /// Gamecard ROM and SPI Control
    /// </summary>
    DSReg AUXSPICNT;
    /// <summary>
    /// 0-1 SPI Baudrate (0=4MHz/Default, 1=2MHz, 2=1MHz, 3=512KHz)
    /// </summary>
    DSReg AUXSPICNT_SPI_Baudrate;
    /// <summary>
    /// 6 SPI Hold Chipselect (0=Deselect after transfer, 1=Keep selected)
    /// </summary>
    DSReg AUXSPICNT_SPI_Hold_Chipselect;
    /// <summary>
    /// 7 SPI Busy (0=Ready, 1=Busy) (presumably Read-only)
    /// </summary>
    DSReg AUXSPICNT_SPI_Busy;
    /// <summary>
    /// 13 NDS Slot Mode (0=Parallel/ROM, 1=Serial/SPI-Backup)
    /// </summary>
    DSReg AUXSPICNT_NDS_Slot_Mode;
    /// <summary>
    /// 14 Transfer Ready IRQ (0=Disable, 1=Enable) (for ROM, not for AUXSPI)
    /// </summary>
    DSReg AUXSPICNT_Transfer_Ready_IRQ;
    /// <summary>
    /// 15 NDS Slot Enable (0=Disable, 1=Enable) (for both ROM and AUXSPI)
    /// </summary>
    DSReg AUXSPICNT_NDS_Slot_Enable;
    /// <summary>
    /// Gamecard SPI Bus Data/Strobe (R/W)
    /// </summary>
    DSReg AUXSPIDATA;
    /// <summary>
    /// Gamecard Bus ROMCTRL (R/W)
    /// </summary>
    DSReg ROMCTRL;
    /// <summary>
    ///  0-12 KEY1 gap1 length (0-1FFFh) (forced min 08F8h by BIOS) (leading gap)
    /// </summary>
    DSReg ROMCTRL_KEY1_gap1_length;
    /// <summary>
    ///  13 KEY2 encrypt data (0=Disable, 1=Enable KEY2 Encryption for Data)
    /// </summary>
    DSReg ROMCTRL_KEY2_encrypt_data;
    /// <summary>
    ///  14 SE Unknown? (usually same as Bit13) (does NOT affect timing?)
    /// </summary>
    DSReg ROMCTRL_SE;
    /// <summary>
    ///  15 KEY2 Apply Seed (0=No change, 1=Apply Encryption Seed) (Write only)
    /// </summary>
    DSReg ROMCTRL_KEY2_Apply_Seed;
    /// <summary>
    ///  16-21 KEY1 gap2 length (0-3Fh) (forced min 18h by BIOS) (200h-byte gap)
    /// </summary>
    DSReg ROMCTRL_KEY1_gap2_length;
    /// <summary>
    ///  22 KEY2 encrypt cmd (0=Disable, 1=Enable KEY2 Encryption for Commands)
    /// </summary>
    DSReg ROMCTRL_KEY2_encrypt_cmd;
    /// <summary>
    ///  23 Data-Word Status (0=Busy, 1=Ready/DRQ) (Read-only)
    /// </summary>
    DSReg ROMCTRL_Data_Word_Status;
    /// <summary>
    ///  24-26 Data Block size (0=None, 1..6=100h SHL (1..6) bytes, 7=4 bytes)
    /// </summary>
    DSReg ROMCTRL_Data_Block_size;
    /// <summary>
    ///  27 Transfer CLK rate (0=6.7MHz=33.51MHz/5, 1=4.2MHz=33.51MHz/8)
    /// </summary>
    DSReg ROMCTRL_Transfer_CLK_rate;
    /// <summary>
    ///  28 KEY1 Gap CLKs (0=Hold CLK High during gaps, 1=Output Dummy CLK Pulses)
    /// </summary>
    DSReg ROMCTRL_KEY1_Gap_CLKs;
    /// <summary>
    ///  29 RESB Release Reset (0=Reset, 1=Release) (cannot be cleared once set)
    /// </summary>
    DSReg ROMCTRL_RESB_Release_Reset;
    /// <summary>
    ///  30 WR Unknown, maybe data-write? (usually 0) (read/write-able)
    /// </summary>
    DSReg ROMCTRL_WR;
    /// <summary>
    ///  31 Block Start/Status (0=Ready, 1=Start/Busy) (IRQ See 40001A0h/Bit14)
    /// </summary>
    DSReg ROMCTRL_Block_Start_Status;
    /// <summary>
    /// Gamecard bus 8-byte Command Out
    /// </summary>
    DSReg Gamecard_bus_Command_1;
    /// <summary>
    /// Gamecard bus 8-byte Command Out
    /// </summary>
    DSReg Gamecard_bus_Command_2;
    /// <summary>
    /// Gamecard bus 4-byte Data In (R)
    /// </summary>
    DSReg Gamecard_bus_DataIn;
    /// <summary>
    /// Encryption Seed 0 Lower 32bit (W)
    /// </summary>
    DSReg Encryption_Seed_0_Lower;
    /// <summary>
    /// Encryption Seed 1 Lower 32bit (W)
    /// </summary>
    DSReg Encryption_Seed_1_Lower;
    /// <summary>
    /// Encryption Seed 0 Upper 7bit (bit7-15 unused)
    /// </summary>
    DSReg Encryption_Seed_0_Upper;
    /// <summary>
    /// Encryption Seed 1 Upper 7bit (bit7-15 unused)
    /// </summary>
    DSReg Encryption_Seed_1_Upper;
    /// <summary>
    /// External Memory Control (R/W)
    /// </summary>
    DSReg EXMEMCNT;
    /// <summary>
    /// 0-1 32-pin GBA Slot SRAM Access Time (0-3 = 10, 8, 6, 18 cycles)
    /// </summary>
    DSReg EXMEMCNT_GBASlot_SRAM_Access_Time;
    /// <summary>
    /// 2-3 32-pin GBA Slot ROM 1st Access Time (0-3 = 10, 8, 6, 18 cycles)
    /// </summary>
    DSReg EXMEMCNT_GBASlot_ROM_1st_Access_Time;
    /// <summary>
    /// 4 32-pin GBA Slot ROM 2nd Access Time (0-1 = 6, 4 cycles)
    /// </summary>
    DSReg EXMEMCNT_GBASlot_ROM_2nd_Access_Time;
    /// <summary>
    /// 5-6 32-pin GBA Slot PHI-pin out (0-3 = Low, 4.19MHz, 8.38MHz, 16.76MHz)
    /// </summary>
    DSReg EXMEMCNT_GBASlot_PHI_pin_out;
    /// <summary>
    /// 7 32-pin GBA Slot Access Rights (0=ARM9, 1=ARM7)
    /// </summary>
    DSReg EXMEMCNT_GBASlot_Access_Rights;
    /// <summary>
    /// 11 17-pin NDS Slot Access Rights (0=ARM9, 1=ARM7)
    /// </summary>
    DSReg EXMEMCNT_NDSSlot_Access_Rights;
    /// <summary>
    /// 13 NDS:Always set? ;set/tested by DSi bootcode: Main RAM enable, CE2 pin?
    /// </summary>
    DSReg EXMEMCNT_SET;
    /// <summary>
    /// 14 Main Memory Interface Mode Switch (0=Async/GBA/Reserved, 1=Synchronous)
    /// </summary>
    DSReg EXMEMCNT_MainMem_Interface_Mode;
    /// <summary>
    /// 15 Main Memory Access Priority (0=ARM9 Priority, 1=ARM7 Priority)
    /// </summary>
    DSReg EXMEMCNT_MainMem_Access_Priority;
    /// <summary>
    /// Interrupt Master Enable Register
    /// </summary>
    DSReg IME;
    /// <summary>
    /// Interrupt Enable
    /// </summary>
    DSReg IE;
    /// <summary>
    /// 0 LCD V-Blank
    /// </summary>
    DSReg IE_LCD_V_Blank;
    /// <summary>
    /// 1 LCD H-Blank
    /// </summary>
    DSReg IE_LCD_H_Blank;
    /// <summary>
    /// 2 LCD V-Counter Match
    /// </summary>
    DSReg IE_LCD_V_Counter_Match;
    /// <summary>
    /// 3 Timer 0 Overflow
    /// </summary>
    DSReg IE_Timer_0;
    /// <summary>
    /// 4 Timer 1 Overflow
    /// </summary>
    DSReg IE_Timer_1;
    /// <summary>
    /// 5 Timer 2 Overflow
    /// </summary>
    DSReg IE_Timer_2;
    /// <summary>
    /// 6 Timer 3 Overflow
    /// </summary>
    DSReg IE_Timer_3;
    /// <summary>
    /// 8 DMA 0
    /// </summary>
    DSReg IE_DMA_0;
    /// <summary>
    /// 9 DMA 1
    /// </summary>
    DSReg IE_DMA_1;
    /// <summary>
    /// 10 DMA 2
    /// </summary>
    DSReg IE_DMA_2;
    /// <summary>
    /// 11 DMA 3
    /// </summary>
    DSReg IE_DMA_3;
    /// <summary>
    /// 12 Keypad
    /// </summary>
    DSReg IE_Keypad;
    /// <summary>
    /// 13 GBA-Slot (external IRQ source)
    /// </summary>
    DSReg IE_GBA_Slot_external_IRQ;
    /// <summary>
    /// 16 IPC Sync
    /// </summary>
    DSReg IE_IPC_Sync;
    /// <summary>
    /// 17 IPC Send FIFO Empty
    /// </summary>
    DSReg IE_IPC_Send_FIFO_Empty;
    /// <summary>
    /// 18 IPC Recv FIFO Not Empty
    /// </summary>
    DSReg IE_IPC_Recv_FIFO_Not_Empty;
    /// <summary>
    /// 19 NDS-Slot Game Card Data Transfer Completion
    /// </summary>
    DSReg IE_NDS_Slot_Transfer_Complete;
    /// <summary>
    /// 20 NDS-Slot Game Card IREQ_MC
    /// </summary>
    DSReg IE_NDS_Slot_IREQ_MC;
    /// <summary>
    /// 21 NDS9 only: Geometry Command FIFO
    /// </summary>
    DSReg IE_Geometry_Command_FIFO;
    /// <summary>
    /// 22-31 unused
    /// </summary>
    DSReg IE_unused;
    /// <summary>
    /// Interrupt Request Flags / IRQ Acknowledge
    /// </summary>
    DSReg IF;
    /// <summary>
    /// 0 LCD V-Blank
    /// </summary>
    DSReg IF_LCD_V_Blank;
    /// <summary>
    /// 1 LCD H-Blank
    /// </summary>
    DSReg IF_LCD_H_Blank;
    /// <summary>
    /// 2 LCD V-Counter Match
    /// </summary>
    DSReg IF_LCD_V_Counter_Match;
    /// <summary>
    /// 3 Timer 0 Overflow
    /// </summary>
    DSReg IF_Timer_0;
    /// <summary>
    /// 4 Timer 1 Overflow
    /// </summary>
    DSReg IF_Timer_1;
    /// <summary>
    /// 5 Timer 2 Overflow
    /// </summary>
    DSReg IF_Timer_2;
    /// <summary>
    /// 6 Timer 3 Overflow
    /// </summary>
    DSReg IF_Timer_3;
    /// <summary>
    /// 8 DMA 0
    /// </summary>
    DSReg IF_DMA_0;
    /// <summary>
    /// 9 DMA 1
    /// </summary>
    DSReg IF_DMA_1;
    /// <summary>
    /// 10 DMA 2
    /// </summary>
    DSReg IF_DMA_2;
    /// <summary>
    /// 11 DMA 3
    /// </summary>
    DSReg IF_DMA_3;
    /// <summary>
    /// 12 Keypad
    /// </summary>
    DSReg IF_Keypad;
    /// <summary>
    /// 13 GBA-Slot (external IRQ source)
    /// </summary>
    DSReg IF_GBA_Slot_external_IRQ;
    /// <summary>
    /// 16 IPC Sync
    /// </summary>
    DSReg IF_IPC_Sync;
    /// <summary>
    /// 17 IPC Send FIFO Empty
    /// </summary>
    DSReg IF_IPC_Send_FIFO_Empty;
    /// <summary>
    /// 18 IPC Recv FIFO Not Empty
    /// </summary>
    DSReg IF_IPC_Recv_FIFO_Not_Empty;
    /// <summary>
    /// 19 NDS-Slot Game Card Data Transfer Completion
    /// </summary>
    DSReg IF_NDS_Slot_Transfer_Complete;
    /// <summary>
    /// 20 NDS-Slot Game Card IREQ_MC
    /// </summary>
    DSReg IF_NDS_Slot_IREQ_MC;
    /// <summary>
    /// 21 NDS9 only: Geometry Command FIFO
    /// </summary>
    DSReg IF_Geometry_Command_FIFO;
    /// <summary>
    /// 
    /// </summary>
    DSReg MemControl1;
    /// <summary>
    /// Bit2 not used by VRAM-A,B,H,I
    /// </summary>
    DSReg MemControl1_VRAM_A_MST;
    /// <summary>
    /// Offset not used by VRAM-E,H,I
    /// </summary>
    DSReg MemControl1_VRAM_A_Offset;
    /// <summary>
    /// (0=Disable, 1=Enable)
    /// </summary>
    DSReg MemControl1_VRAM_A_Enable;
    /// <summary>
    /// 
    /// </summary>
    DSReg MemControl1_VRAM_B_MST;
    /// <summary>
    /// 
    /// </summary>
    DSReg MemControl1_VRAM_B_Offset;
    /// <summary>
    /// 
    /// </summary>
    DSReg MemControl1_VRAM_B_Enable;
    /// <summary>
    /// 
    /// </summary>
    DSReg MemControl1_VRAM_C_MST;
    /// <summary>
    /// 
    /// </summary>
    DSReg MemControl1_VRAM_C_Offset;
    /// <summary>
    /// 
    /// </summary>
    DSReg MemControl1_VRAM_C_Enable;
    /// <summary>
    /// 
    /// </summary>
    DSReg MemControl1_VRAM_D_MST;
    /// <summary>
    /// 
    /// </summary>
    DSReg MemControl1_VRAM_D_Offset;
    /// <summary>
    /// 
    /// </summary>
    DSReg MemControl1_VRAM_D_Enable;
    /// <summary>
    /// 
    /// </summary>
    DSReg MemControl2;
    /// <summary>
    /// Bit2 not used by VRAM-A,B,H,I
    /// </summary>
    DSReg MemControl2_VRAM_E_MST;
    /// <summary>
    /// Offset not used by VRAM-E,H,I
    /// </summary>
    DSReg MemControl2_VRAM_E_Offset;
    /// <summary>
    /// (0=Disable, 1=Enable)
    /// </summary>
    DSReg MemControl2_VRAM_E_Enable;
    /// <summary>
    /// 
    /// </summary>
    DSReg MemControl2_VRAM_F_MST;
    /// <summary>
    /// 
    /// </summary>
    DSReg MemControl2_VRAM_F_Offset;
    /// <summary>
    /// 
    /// </summary>
    DSReg MemControl2_VRAM_F_Enable;
    /// <summary>
    /// 
    /// </summary>
    DSReg MemControl2_VRAM_G_MST;
    /// <summary>
    /// 
    /// </summary>
    DSReg MemControl2_VRAM_G_Offset;
    /// <summary>
    /// 
    /// </summary>
    DSReg MemControl2_VRAM_G_Enable;
    /// <summary>
    /// (0-3 = 32K/0K, 2nd 16K/1st 16K, 1st 16K/2nd 16K, 0K/32K)
    /// </summary>
    DSReg MemControl2_WRAM;
    /// <summary>
    /// 
    /// </summary>
    DSReg MemControl3;
    /// <summary>
    /// Bit2 not used by VRAM-A,B,H,I
    /// </summary>
    DSReg MemControl3_VRAM_H_MST;
    /// <summary>
    /// Offset not used by VRAM-E,H,I
    /// </summary>
    DSReg MemControl3_VRAM_H_Offset;
    /// <summary>
    /// (0=Disable, 1=Enable)
    /// </summary>
    DSReg MemControl3_VRAM_H_Enable;
    /// <summary>
    /// 
    /// </summary>
    DSReg MemControl3_VRAM_I_MST;
    /// <summary>
    /// 
    /// </summary>
    DSReg MemControl3_VRAM_I_Offset;
    /// <summary>
    /// 
    /// </summary>
    DSReg MemControl3_VRAM_I_Enable;
    /// <summary>
    /// Division Control (R/W)
    /// </summary>
    DSReg DIVCNT;
    /// <summary>
    /// 0-1 Division Mode (0-2=See below) (3=Reserved; same as Mode 1)
    /// </summary>
    DSReg DIVCNT_Division_Mode;
    /// <summary>
    /// 14 Division by zero (0=Okay, 1=Division by zero error; 64bit Denom=0)
    /// </summary>
    DSReg DIVCNT_Division_by_zero;
    /// <summary>
    /// 15 Busy (0=Ready, 1=Busy) (Execution time see below)
    /// </summary>
    DSReg DIVCNT_Busy;
    /// <summary>
    /// 64bit Division Numerator (R/W)
    /// </summary>
    DSReg DIV_NUMER_Low;
    /// <summary>
    /// 64bit Division Numerator (R/W)
    /// </summary>
    DSReg DIV_NUMER_High;
    /// <summary>
    /// 64bit Division Denominator (R/W)
    /// </summary>
    DSReg DIV_DENOM_Low;
    /// <summary>
    /// 64bit Division Denominator (R/W)
    /// </summary>
    DSReg DIV_DENOM_High;
    /// <summary>
    /// 64bit Division Quotient (=Numer/Denom) (R)
    /// </summary>
    DSReg DIV_RESULT_Low;
    /// <summary>
    /// 64bit Division Quotient (=Numer/Denom) (R)
    /// </summary>
    DSReg DIV_RESULT_High;
    /// <summary>
    /// 64bit Remainder (=Numer MOD Denom) (R)
    /// </summary>
    DSReg DIVREM_RESULT_Low;
    /// <summary>
    /// 64bit Remainder (=Numer MOD Denom) (R)
    /// </summary>
    DSReg DIVREM_RESULT_High;
    /// <summary>
    /// Square Root Control (R/W)
    /// </summary>
    DSReg SQRTCN;
    /// <summary>
    /// 0 Mode (0=32bit input, 1=64bit input)
    /// </summary>
    DSReg SQRTCN_Mode;
    /// <summary>
    /// 15 Busy (0=Ready, 1=Busy) (Execution time is 13 clks, in either Mode)
    /// </summary>
    DSReg SQRTCN_Busy;
    /// <summary>
    /// Square Root Result (R)
    /// </summary>
    DSReg SQRT_RESULT;
    /// <summary>
    /// Square Root Parameter Input (R/W)
    /// </summary>
    DSReg SQRT_PARAM_Low;
    /// <summary>
    /// Square Root Parameter Input (R/W)
    /// </summary>
    DSReg SQRT_PARAM_High;
    /// <summary>
    /// Post Boot Flag (R/W)
    /// </summary>
    DSReg POSTFLG;
    /// <summary>
    /// Post Boot Flag (0=Boot in progress, 1=Boot completed)
    /// </summary>
    DSReg POSTFLG_Flag;
    /// <summary>
    /// Bit1 is read-writeable
    /// </summary>
    DSReg POSTFLG_RW;
    /// <summary>
    /// Graphics Power Control Register (R/W) - default all available bits set
    /// </summary>
    DSReg POWCNT1;
    /// <summary>
    /// 0 Enable Flag for both LCDs (0=Disable) (Prohibited, see notes)
    /// </summary>
    DSReg POWCNT1_Enable_Flag_for_both_LCDs;
    /// <summary>
    /// 1 2D Graphics Engine A (0=Disable) (Ports 008h-05Fh, Pal 5000000h)
    /// </summary>
    DSReg POWCNT1_2D_Graphics_Engine_A;
    /// <summary>
    /// 2 3D Rendering Engine (0=Disable) (Ports 320h-3FFh)
    /// </summary>
    DSReg POWCNT1_3D_Rendering_Engine;
    /// <summary>
    /// 3 3D Geometry Engine (0=Disable) (Ports 400h-6FFh)
    /// </summary>
    DSReg POWCNT1_3D_Geometry_Engine;
    /// <summary>
    /// 9 2D Graphics Engine B (0=Disable) (Ports 1008h-105Fh, Pal 5000400h)
    /// </summary>
    DSReg POWCNT1_2D_Graphics_Engine_B;
    /// <summary>
    /// 15 Display Swap (0=Send Display A to Lower Screen, 1=To Upper Screen)
    /// </summary>
    DSReg POWCNT1_Display_Swap;

    RegSect_system9();
};

class RegSect_3D9
{
public:
    /// <summary>
    /// Clear Color Attribute Register (W)
    /// </summary>
    DSReg CLEAR_COLOR;
    /// <summary>
    /// 0-4 Clear Color, Red
    /// </summary>
    DSReg CLEAR_COLOR_Red;
    /// <summary>
    /// 5-9 Clear Color, Green
    /// </summary>
    DSReg CLEAR_COLOR_Green;
    /// <summary>
    /// 10-14 Clear Color, Blue
    /// </summary>
    DSReg CLEAR_COLOR_Blue;
    /// <summary>
    /// 15 Fog (enables Fog to the rear-plane) (doesn't affect Fog of polygons)
    /// </summary>
    DSReg CLEAR_COLOR_Fog;
    /// <summary>
    /// 16-20 Alpha
    /// </summary>
    DSReg CLEAR_COLOR_Alpha;
    /// <summary>
    /// 24-29 Clear Polygon ID (affects edge-marking, at the screen-edges?)
    /// </summary>
    DSReg CLEAR_COLOR_Clear_Polygon_ID;
    /// <summary>
    /// Clear Depth Register (W)
    /// </summary>
    DSReg CLEAR_DEPTH;
    /// <summary>
    /// 0-14 Clear Depth (0..7FFFh) (usually 7FFFh = most distant)
    /// </summary>
    DSReg CLEAR_DEPTH_DEPTH;
    /// <summary>
    /// Bit16-23 X-Offset (0..255; 0=upper row of bitmap)
    /// </summary>
    DSReg CLEAR_DEPTH_X_Offset;
    /// <summary>
    /// Bit24-30 Y-Offset (0..255; 0=left column of bitmap)
    /// </summary>
    DSReg CLEAR_DEPTH_Y_Offset;
    /// <summary>
    /// Geometry Command FIFO (mirrored up to 400043Fh?)
    /// </summary>
    DSReg GXFIFO;
    /// <summary>
    /// Geometry Engine Status Register (R and R/W)
    /// </summary>
    DSReg GXSTAT;
    /// <summary>
    /// 0 BoxTest,PositionTest,VectorTest Busy (0=Ready, 1=Busy)
    /// </summary>
    DSReg GXSTAT_TestBusy;
    /// <summary>
    /// 1 BoxTest Result (0=All Outside View, 1=Parts or Fully Inside View)
    /// </summary>
    DSReg GXSTAT_BoxTest_Result;
    /// <summary>
    /// 8-12 Position & Vector Matrix Stack Level (0..31) (lower 5bit of 6bit value)
    /// </summary>
    DSReg GXSTAT_PosVect_Matrix_Stack_Level;
    /// <summary>
    /// 13 Projection Matrix Stack Level (0..1)
    /// </summary>
    DSReg GXSTAT_Proj_Matrix_Stack_Level;
    /// <summary>
    /// 14 Matrix Stack Busy (0=No, 1=Yes; Currently executing a Push/Pop command)
    /// </summary>
    DSReg GXSTAT_Matrix_Stack_Busy;
    /// <summary>
    /// 15 Matrix Stack Overflow/Underflow Error (0=No, 1=Error/Acknowledge/Reset)
    /// </summary>
    DSReg GXSTAT_Matrix_Stack_Error;
    /// <summary>
    /// 16-24 Number of 40bit-entries in Command FIFO (0..256) (24) Command FIFO Full (MSB of above) (0=No, 1=Yes; Full)
    /// </summary>
    DSReg GXSTAT_Command_FIFO_Entries;
    /// <summary>
    /// 25 Command FIFO Less Than Half Full (0=No, 1=Yes; Less than Half-full)
    /// </summary>
    DSReg GXSTAT_Command_FIFO_Less_Half;
    /// <summary>
    /// 26 Command FIFO Empty (0=No, 1=Yes; Empty)
    /// </summary>
    DSReg GXSTAT_Command_FIFO_Empty;
    /// <summary>
    /// 27 Geometry Engine Busy (0=No, 1=Yes; Busy; Commands are executing)
    /// </summary>
    DSReg GXSTAT_Geometry_Engine_Busy;
    /// <summary>
    /// 30-31 Command FIFO IRQ (0=Never, 1=Less than half full, 2=Empty, 3=Reserved)
    /// </summary>
    DSReg GXSTAT_Command_FIFO_IRQ;

    RegSect_3D9();
};

class REGS_Arm9
{
public:
    RegSect_display9 Sect_display9;
    RegSect_dma9 Sect_dma9;
    RegSect_timer9 Sect_timer9;
    RegSect_keypad9 Sect_keypad9;
    RegSect_system9 Sect_system9;
    RegSect_3D9 Sect_3D9;

    byte data[4208];
    byte rwmask[4208];
    const int allregcount = 571;
    DSReg allregs[571];

    void reset();
};
extern REGS_Arm9 Regs_Arm9;
