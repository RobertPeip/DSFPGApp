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
    DSReg DISPCNT;
    /// <summary>
    /// BG Mode (0-5=Video Mode 0-5, 6-7=Prohibited)
    /// </summary>
    DSReg DISPCNT_BG_Mode;
    /// <summary>
    /// Reserved / CGB Mode (0=GBA, 1=CGB; can be set only by BIOS opcodes)
    /// </summary>
    DSReg DISPCNT_Reserved_CGB_Mode;
    /// <summary>
    /// Display Frame Select (0-1=Frame 0-1) (for BG Modes 4,5 only)
    /// </summary>
    DSReg DISPCNT_Display_Frame_Select;
    /// <summary>
    /// H-Blank Interval Free (1=Allow access to OAM during H-Blank)
    /// </summary>
    DSReg DISPCNT_H_Blank_IntervalFree;
    /// <summary>
    /// OBJ Character VRAM Mapping (0=Two dimensional, 1=One dimensional)
    /// </summary>
    DSReg DISPCNT_OBJ_Char_VRAM_Map;
    /// <summary>
    /// Forced Blank (1=Allow FAST access to VRAM,Palette,OAM)
    /// </summary>
    DSReg DISPCNT_Forced_Blank;
    /// <summary>
    /// Screen Display BG0 (0=Off, 1=On)
    /// </summary>
    DSReg DISPCNT_Screen_Display_BG0;
    /// <summary>
    /// Screen Display BG1 (0=Off, 1=On)
    /// </summary>
    DSReg DISPCNT_Screen_Display_BG1;
    /// <summary>
    /// Screen Display BG2 (0=Off, 1=On)
    /// </summary>
    DSReg DISPCNT_Screen_Display_BG2;
    /// <summary>
    /// Screen Display BG3 (0=Off, 1=On)
    /// </summary>
    DSReg DISPCNT_Screen_Display_BG3;
    /// <summary>
    /// Screen Display OBJ (0=Off, 1=On)
    /// </summary>
    DSReg DISPCNT_Screen_Display_OBJ;
    /// <summary>
    /// Window 0 Display Flag (0=Off, 1=On)
    /// </summary>
    DSReg DISPCNT_Window_0_Display_Flag;
    /// <summary>
    /// Window 1 Display Flag (0=Off, 1=On)
    /// </summary>
    DSReg DISPCNT_Window_1_Display_Flag;
    /// <summary>
    /// OBJ Window Display Flag (0=Off, 1=On)
    /// </summary>
    DSReg DISPCNT_OBJ_Wnd_Display_Flag;
    /// <summary>
    /// Undocumented - Green Swap 2 R/W
    /// </summary>
    DSReg GREENSWAP;
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
    DSReg BG0CNT;
    /// <summary>
    /// BG Priority (0-3, 0=Highest)
    /// </summary>
    DSReg BG0CNT_BG_Priority;
    /// <summary>
    /// Character Base Block (0-3, in units of 16 KBytes) (=BG Tile Data)
    /// </summary>
    DSReg BG0CNT_Character_Base_Block;
    /// <summary>
    /// 4-5 Not used (must be zero)
    /// </summary>
    DSReg BG0CNT_UNUSED_4_5;
    /// <summary>
    /// Mosaic (0=Disable, 1=Enable)
    /// </summary>
    DSReg BG0CNT_Mosaic;
    /// <summary>
    /// Colors/Palettes (0=16/16, 1=256/1)
    /// </summary>
    DSReg BG0CNT_Colors_Palettes;
    /// <summary>
    /// Screen Base Block (0-31, in units of 2 KBytes) (=BG Map Data)
    /// </summary>
    DSReg BG0CNT_Screen_Base_Block;
    /// <summary>
    /// Screen Size (0-3)
    /// </summary>
    DSReg BG0CNT_Screen_Size;
    /// <summary>
    /// BG1 Control 2 R/W
    /// </summary>
    DSReg BG1CNT;
    /// <summary>
    /// BG Priority (0-3, 0=Highest)
    /// </summary>
    DSReg BG1CNT_BG_Priority;
    /// <summary>
    /// Character Base Block (0-3, in units of 16 KBytes) (=BG Tile Data)
    /// </summary>
    DSReg BG1CNT_Character_Base_Block;
    /// <summary>
    /// 4-5 Not used (must be zero)
    /// </summary>
    DSReg BG1CNT_UNUSED_4_5;
    /// <summary>
    /// Mosaic (0=Disable, 1=Enable)
    /// </summary>
    DSReg BG1CNT_Mosaic;
    /// <summary>
    /// Colors/Palettes (0=16/16, 1=256/1)
    /// </summary>
    DSReg BG1CNT_Colors_Palettes;
    /// <summary>
    /// Screen Base Block (0-31, in units of 2 KBytes) (=BG Map Data)
    /// </summary>
    DSReg BG1CNT_Screen_Base_Block;
    /// <summary>
    /// Screen Size (0-3)
    /// </summary>
    DSReg BG1CNT_Screen_Size;
    /// <summary>
    /// BG2 Control 2 R/W
    /// </summary>
    DSReg BG2CNT;
    /// <summary>
    /// BG Priority (0-3, 0=Highest)
    /// </summary>
    DSReg BG2CNT_BG_Priority;
    /// <summary>
    /// Character Base Block (0-3, in units of 16 KBytes) (=BG Tile Data)
    /// </summary>
    DSReg BG2CNT_Character_Base_Block;
    /// <summary>
    /// Mosaic (0=Disable, 1=Enable)
    /// </summary>
    DSReg BG2CNT_Mosaic;
    /// <summary>
    /// Colors/Palettes (0=16/16, 1=256/1)
    /// </summary>
    DSReg BG2CNT_Colors_Palettes;
    /// <summary>
    /// Screen Base Block (0-31, in units of 2 KBytes) (=BG Map Data)
    /// </summary>
    DSReg BG2CNT_Screen_Base_Block;
    /// <summary>
    /// Display Area Overflow (0=Transparent, 1=Wraparound; BG2CNT/BG3CNT only)
    /// </summary>
    DSReg BG2CNT_Display_Area_Overflow;
    /// <summary>
    /// Screen Size (0-3)
    /// </summary>
    DSReg BG2CNT_Screen_Size;
    /// <summary>
    /// BG3 Control 2 R/W
    /// </summary>
    DSReg BG3CNT;
    /// <summary>
    /// BG Priority (0-3, 0=Highest)
    /// </summary>
    DSReg BG3CNT_BG_Priority;
    /// <summary>
    /// Character Base Block (0-3, in units of 16 KBytes) (=BG Tile Data)
    /// </summary>
    DSReg BG3CNT_Character_Base_Block;
    /// <summary>
    /// Mosaic (0=Disable, 1=Enable)
    /// </summary>
    DSReg BG3CNT_Mosaic;
    /// <summary>
    /// Colors/Palettes (0=16/16, 1=256/1)
    /// </summary>
    DSReg BG3CNT_Colors_Palettes;
    /// <summary>
    /// Screen Base Block (0-31, in units of 2 KBytes) (=BG Map Data)
    /// </summary>
    DSReg BG3CNT_Screen_Base_Block;
    /// <summary>
    /// Display Area Overflow (0=Transparent, 1=Wraparound; BG2CNT/BG3CNT only)
    /// </summary>
    DSReg BG3CNT_Display_Area_Overflow;
    /// <summary>
    /// Screen Size (0-3)
    /// </summary>
    DSReg BG3CNT_Screen_Size;
    /// <summary>
    /// BG0 X-Offset 2 W
    /// </summary>
    DSReg BG0HOFS;
    /// <summary>
    /// BG0 Y-Offset 2 W
    /// </summary>
    DSReg BG0VOFS;
    /// <summary>
    /// BG1 X-Offset 2 W
    /// </summary>
    DSReg BG1HOFS;
    /// <summary>
    /// BG1 Y-Offset 2 W
    /// </summary>
    DSReg BG1VOFS;
    /// <summary>
    /// BG2 X-Offset 2 W
    /// </summary>
    DSReg BG2HOFS;
    /// <summary>
    /// BG2 Y-Offset 2 W
    /// </summary>
    DSReg BG2VOFS;
    /// <summary>
    /// BG3 X-Offset 2 W
    /// </summary>
    DSReg BG3HOFS;
    /// <summary>
    /// BG3 Y-Offset 2 W
    /// </summary>
    DSReg BG3VOFS;
    /// <summary>
    /// BG2 Rotation/Scaling Parameter A (dx) 2 W
    /// </summary>
    DSReg BG2RotScaleParDX;
    /// <summary>
    /// BG2 Rotation/Scaling Parameter B (dmx) 2 W
    /// </summary>
    DSReg BG2RotScaleParDMX;
    /// <summary>
    /// BG2 Rotation/Scaling Parameter C (dy) 2 W
    /// </summary>
    DSReg BG2RotScaleParDY;
    /// <summary>
    /// BG2 Rotation/Scaling Parameter D (dmy) 2 W
    /// </summary>
    DSReg BG2RotScaleParDMY;
    /// <summary>
    /// BG2 Reference Point X-Coordinate 4 W
    /// </summary>
    DSReg BG2RefX;
    /// <summary>
    /// BG2 Reference Point Y-Coordinate 4 W
    /// </summary>
    DSReg BG2RefY;
    /// <summary>
    /// BG3 Rotation/Scaling Parameter A (dx) 2 W
    /// </summary>
    DSReg BG3RotScaleParDX;
    /// <summary>
    /// BG3 Rotation/Scaling Parameter B (dmx) 2 W
    /// </summary>
    DSReg BG3RotScaleParDMX;
    /// <summary>
    /// BG3 Rotation/Scaling Parameter C (dy) 2 W
    /// </summary>
    DSReg BG3RotScaleParDY;
    /// <summary>
    /// BG3 Rotation/Scaling Parameter D (dmy) 2 W
    /// </summary>
    DSReg BG3RotScaleParDMY;
    /// <summary>
    /// BG3 Reference Point X-Coordinate 4 W
    /// </summary>
    DSReg BG3RefX;
    /// <summary>
    /// BG3 Reference Point Y-Coordinate 4 W
    /// </summary>
    DSReg BG3RefY;
    /// <summary>
    /// Window 0 Horizontal Dimensions 2 W
    /// </summary>
    DSReg WIN0H;
    /// <summary>
    /// Window 0 Horizontal Dimensions 2 W
    /// </summary>
    DSReg WIN0H_X2;
    /// <summary>
    /// Window 0 Horizontal Dimensions 2 W
    /// </summary>
    DSReg WIN0H_X1;
    /// <summary>
    /// Window 1 Horizontal Dimensions 2 W
    /// </summary>
    DSReg WIN1H;
    /// <summary>
    /// Window 1 Horizontal Dimensions 2 W
    /// </summary>
    DSReg WIN1H_X2;
    /// <summary>
    /// Window 1 Horizontal Dimensions 2 W
    /// </summary>
    DSReg WIN1H_X1;
    /// <summary>
    /// Window 0 Vertical Dimensions 2 W
    /// </summary>
    DSReg WIN0V;
    /// <summary>
    /// Window 0 Vertical Dimensions 2 W
    /// </summary>
    DSReg WIN0V_Y2;
    /// <summary>
    /// Window 0 Vertical Dimensions 2 W
    /// </summary>
    DSReg WIN0V_Y1;
    /// <summary>
    /// Window 1 Vertical Dimensions 2 W
    /// </summary>
    DSReg WIN1V;
    /// <summary>
    /// Window 1 Vertical Dimensions 2 W
    /// </summary>
    DSReg WIN1V_Y2;
    /// <summary>
    /// Window 1 Vertical Dimensions 2 W
    /// </summary>
    DSReg WIN1V_Y1;
    /// <summary>
    /// Inside of Window 0 and 1 2 R/W
    /// </summary>
    DSReg WININ;
    /// <summary>
    /// 0-3 Window_0_BG0_BG3_Enable (0=No Display, 1=Display)
    /// </summary>
    DSReg WININ_Window_0_BG0_Enable;
    /// <summary>
    /// 0-3 Window_0_BG0_BG3_Enable (0=No Display, 1=Display)
    /// </summary>
    DSReg WININ_Window_0_BG1_Enable;
    /// <summary>
    /// 0-3 Window_0_BG0_BG3_Enable (0=No Display, 1=Display)
    /// </summary>
    DSReg WININ_Window_0_BG2_Enable;
    /// <summary>
    /// 0-3 Window_0_BG0_BG3_Enable (0=No Display, 1=Display)
    /// </summary>
    DSReg WININ_Window_0_BG3_Enable;
    /// <summary>
    /// 4 Window_0_OBJ_Enable (0=No Display, 1=Display)
    /// </summary>
    DSReg WININ_Window_0_OBJ_Enable;
    /// <summary>
    /// 5 Window_0_Special_Effect (0=Disable, 1=Enable)
    /// </summary>
    DSReg WININ_Window_0_Special_Effect;
    /// <summary>
    /// 8-11 Window_1_BG0_BG3_Enable (0=No Display, 1=Display)
    /// </summary>
    DSReg WININ_Window_1_BG0_Enable;
    /// <summary>
    /// 8-11 Window_1_BG0_BG3_Enable (0=No Display, 1=Display)
    /// </summary>
    DSReg WININ_Window_1_BG1_Enable;
    /// <summary>
    /// 8-11 Window_1_BG0_BG3_Enable (0=No Display, 1=Display)
    /// </summary>
    DSReg WININ_Window_1_BG2_Enable;
    /// <summary>
    /// 8-11 Window_1_BG0_BG3_Enable (0=No Display, 1=Display)
    /// </summary>
    DSReg WININ_Window_1_BG3_Enable;
    /// <summary>
    /// 12 Window_1_OBJ_Enable (0=No Display, 1=Display)
    /// </summary>
    DSReg WININ_Window_1_OBJ_Enable;
    /// <summary>
    /// 13 Window_1_Special_Effect (0=Disable, 1=Enable)
    /// </summary>
    DSReg WININ_Window_1_Special_Effect;
    /// <summary>
    /// Inside of OBJ Window & Outside of Windows 2 R/W
    /// </summary>
    DSReg WINOUT;
    /// <summary>
    /// 0-3 Outside_BG0_BG3_Enable (0=No Display, 1=Display)
    /// </summary>
    DSReg WINOUT_Outside_BG0_Enable;
    /// <summary>
    /// 0-3 Outside_BG0_BG3_Enable (0=No Display, 1=Display)
    /// </summary>
    DSReg WINOUT_Outside_BG1_Enable;
    /// <summary>
    /// 0-3 Outside_BG0_BG3_Enable (0=No Display, 1=Display)
    /// </summary>
    DSReg WINOUT_Outside_BG2_Enable;
    /// <summary>
    /// 0-3 Outside_BG0_BG3_Enable (0=No Display, 1=Display)
    /// </summary>
    DSReg WINOUT_Outside_BG3_Enable;
    /// <summary>
    /// 4 Outside_OBJ_Enable (0=No Display, 1=Display)
    /// </summary>
    DSReg WINOUT_Outside_OBJ_Enable;
    /// <summary>
    /// 5 Outside_Special_Effect (0=Disable, 1=Enable)
    /// </summary>
    DSReg WINOUT_Outside_Special_Effect;
    /// <summary>
    /// 8-11 object window_BG0_BG3_Enable (0=No Display, 1=Display)
    /// </summary>
    DSReg WINOUT_Objwnd_BG0_Enable;
    /// <summary>
    /// 8-11 object window_BG0_BG3_Enable (0=No Display, 1=Display)
    /// </summary>
    DSReg WINOUT_Objwnd_BG1_Enable;
    /// <summary>
    /// 8-11 object window_BG0_BG3_Enable (0=No Display, 1=Display)
    /// </summary>
    DSReg WINOUT_Objwnd_BG2_Enable;
    /// <summary>
    /// 8-11 object window_BG0_BG3_Enable (0=No Display, 1=Display)
    /// </summary>
    DSReg WINOUT_Objwnd_BG3_Enable;
    /// <summary>
    /// 12 object window_OBJ_Enable (0=No Display, 1=Display)
    /// </summary>
    DSReg WINOUT_Objwnd_OBJ_Enable;
    /// <summary>
    /// 13 object window_Special_Effect (0=Disable, 1=Enable)
    /// </summary>
    DSReg WINOUT_Objwnd_Special_Effect;
    /// <summary>
    /// Mosaic Size 2 W
    /// </summary>
    DSReg MOSAIC;
    /// <summary>
    ///  0-3 BG_Mosaic_H_Size (minus 1)
    /// </summary>
    DSReg MOSAIC_BG_Mosaic_H_Size;
    /// <summary>
    ///  4-7 BG_Mosaic_V_Size (minus 1)
    /// </summary>
    DSReg MOSAIC_BG_Mosaic_V_Size;
    /// <summary>
    ///  8-11 OBJ_Mosaic_H_Size (minus 1)
    /// </summary>
    DSReg MOSAIC_OBJ_Mosaic_H_Size;
    /// <summary>
    ///  12-15 OBJ_Mosaic_V_Size (minus 1)
    /// </summary>
    DSReg MOSAIC_OBJ_Mosaic_V_Size;
    /// <summary>
    /// Color Special Effects Selection 2 R/W
    /// </summary>
    DSReg BLDCNT;
    /// <summary>
    /// 0 (Background 0)
    /// </summary>
    DSReg BLDCNT_BG0_1st_Target_Pixel;
    /// <summary>
    /// 1 (Background 1)
    /// </summary>
    DSReg BLDCNT_BG1_1st_Target_Pixel;
    /// <summary>
    /// 2 (Background 2)
    /// </summary>
    DSReg BLDCNT_BG2_1st_Target_Pixel;
    /// <summary>
    /// 3 (Background 3)
    /// </summary>
    DSReg BLDCNT_BG3_1st_Target_Pixel;
    /// <summary>
    /// 4 (Top-most OBJ pixel)
    /// </summary>
    DSReg BLDCNT_OBJ_1st_Target_Pixel;
    /// <summary>
    /// 5 (Backdrop)
    /// </summary>
    DSReg BLDCNT_BD_1st_Target_Pixel;
    /// <summary>
    /// 6-7 (0-3, see below) 0 = None (Special effects disabled), 1 = Alpha Blending (1st+2nd Target mixed), 2 = Brightness Increase (1st Target becomes whiter), 3 = Brightness Decrease (1st Target becomes blacker)
    /// </summary>
    DSReg BLDCNT_Color_Special_Effect;
    /// <summary>
    /// 8 (Background 0)
    /// </summary>
    DSReg BLDCNT_BG0_2nd_Target_Pixel;
    /// <summary>
    /// 9 (Background 1)
    /// </summary>
    DSReg BLDCNT_BG1_2nd_Target_Pixel;
    /// <summary>
    /// 10 (Background 2)
    /// </summary>
    DSReg BLDCNT_BG2_2nd_Target_Pixel;
    /// <summary>
    /// 11 (Background 3)
    /// </summary>
    DSReg BLDCNT_BG3_2nd_Target_Pixel;
    /// <summary>
    /// 12 (Top-most OBJ pixel)
    /// </summary>
    DSReg BLDCNT_OBJ_2nd_Target_Pixel;
    /// <summary>
    /// 13 (Backdrop)
    /// </summary>
    DSReg BLDCNT_BD_2nd_Target_Pixel;
    /// <summary>
    /// Alpha Blending Coefficients 2 W
    /// </summary>
    DSReg BLDALPHA;
    /// <summary>
    /// 0-4 (1st Target) (0..16 = 0/16..16/16, 17..31=16/16)
    /// </summary>
    DSReg BLDALPHA_EVA_Coefficient;
    /// <summary>
    /// 8-12 (2nd Target) (0..16 = 0/16..16/16, 17..31=16/16)
    /// </summary>
    DSReg BLDALPHA_EVB_Coefficient;
    /// <summary>
    /// Brightness (Fade-In/Out) Coefficient 0-4 EVY Coefficient (Brightness) (0..16 = 0/16..16/16, 17..31=16/16
    /// </summary>
    DSReg BLDY;
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
    DSReg MASTER_BRIGHT;
    /// <summary>
    /// Factor used for 6bit R,G,B Intensities (0-16, values >16 same as 16)
    /// </summary>
    DSReg MASTER_BRIGHT_Factor;
    /// <summary>
    /// Mode (0=Disable, 1=Up, 2=Down, 3=Reserved)
    /// </summary>
    DSReg MASTER_BRIGHT_Mode;

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
    DSReg IPCSYNC_IRQ;
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
    DSReg IPCFIFOCNT_Send_Fifo_Empty;
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
    DSReg DIV_NUMER_High;
    /// <summary>
    /// 64bit Division Numerator (R/W)
    /// </summary>
    DSReg DIV_NUMER_Low;
    /// <summary>
    /// 64bit Division Denominator (R/W)
    /// </summary>
    DSReg DIV_DENOM_High;
    /// <summary>
    /// 64bit Division Denominator (R/W)
    /// </summary>
    DSReg DIV_DENOM_Low;
    /// <summary>
    /// 64bit Division Quotient (=Numer/Denom) (R)
    /// </summary>
    DSReg DIV_RESULT_High;
    /// <summary>
    /// 64bit Division Quotient (=Numer/Denom) (R)
    /// </summary>
    DSReg DIV_RESULT_Low;
    /// <summary>
    /// 64bit Remainder (=Numer MOD Denom) (R)
    /// </summary>
    DSReg DIVREM_RESULT_High;
    /// <summary>
    /// 64bit Remainder (=Numer MOD Denom) (R)
    /// </summary>
    DSReg DIVREM_RESULT_Low;
    /// <summary>
    /// Square Root Control (R/W)
    /// </summary>
    DSReg SQRTCN;
    /// <summary>
    /// 0 Mode (0=32bit input, 1=64bit input)
    /// </summary>
    DSReg SQRTCN_Division_Mode;
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
    DSReg SQRT_PARAM_High;
    /// <summary>
    /// Square Root Parameter Input (R/W)
    /// </summary>
    DSReg SQRT_PARAM_Low;

    RegSect_system9();
};

class REGS_Arm9
{
public:
    RegSect_display9 Sect_display9;
    RegSect_dma9 Sect_dma9;
    RegSect_timer9 Sect_timer9;
    RegSect_keypad9 Sect_keypad9;
    RegSect_system9 Sect_system9;

    byte data[4208];
    byte rwmask[4208];

    void reset();
};
extern REGS_Arm9 Regs_Arm9;
