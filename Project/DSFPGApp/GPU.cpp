#include <algorithm>

using namespace std;

#include "GPU.h"
#include "regs_arm9.h"
#include "regs_arm7.h"
#include "GPU_Timing.h"
#include "Memory.h"

Gpu GPU_A;
Gpu GPU_B;

void Pixel::update(Byte color_red, Byte color_green, Byte color_blue)
{
	this->color_red = color_red;
	this->color_green = color_green;
	this->color_blue = color_blue;
}

void Pixel::copy(Pixel source)
{
	this->color_red = source.color_red;
	this->color_green = source.color_green;
	this->color_blue = source.color_blue;
	this->transparent = source.transparent;
	this->undrawn = source.undrawn;
	this->prio = source.prio;
	this->objwnd = source.objwnd;
	this->alpha = source.alpha;
}

void Pixel::copycolor(Pixel source)
{
	this->color_red = source.color_red;
	this->color_green = source.color_green;
	this->color_blue = source.color_blue;
}

void Pixel::mixcolor(Pixel source, Pixel secondpixel)
{
	color_red = (byte)(min(255, (source.color_red + secondpixel.color_red) >> 1));
	color_green = (byte)(min(255, (source.color_green + secondpixel.color_green) >> 1));
	color_blue = (byte)(min(255, (source.color_blue + secondpixel.color_blue) >> 1));
}

void Pixel::calcalpha(Pixel secondpixel, byte eva, byte evb)
{
	color_red = (byte)(min(255, (color_red * eva + secondpixel.color_red * evb) >> 4));
	color_green = (byte)(min(255, (color_green * eva + secondpixel.color_green * evb) >> 4));
	color_blue = (byte)(min(255, (color_blue * eva + secondpixel.color_blue * evb) >> 4));
}

void Pixel::whiter(byte change)
{
	color_red = (byte)min(255, color_red + (((255 - color_red) * change) >> 4));
	color_green = (byte)min(255, color_green + (((255 - color_green) * change) >> 4));
	color_blue = (byte)min(255, color_blue + (((255 - color_blue) * change) >> 4));
}

void Pixel::blacker(byte change)
{
	color_red = (byte)max(0, color_red - ((color_red * change) >> 4));
	color_green = (byte)max(0, color_green - ((color_green * change) >> 4));
	color_blue = (byte)max(0, color_blue - ((color_blue * change) >> 4));
}

void Gpu::reset(bool isGPUA)
{
	this->isGPUA = isGPUA;
	swap = !isGPUA;

#if DEBUG
	lockSpeed = false;
#endif
	forcedblank = false;

	//drawlock = new object();

	intern_frames = 0;

	pixelbackdrop.transparent = false;
	pixelbackdrop.prio = 4;

	while (!mainmemfifo.empty()) mainmemfifo.pop();

	videomode = 0;
	displaymode = 0;
	is3D = false;
	screenbase = 0;
	charbase = 0;

	ext_palette_bg = false;
	ext_palette_obj = false;

	frametimeleft = FRAMETIME;
	//stopwatch_frame.Start();

	layerenable = 0x1F;

	if (isGPUA)
	{
		DISPCNT_BG_Mode = Regs_Arm9.Sect_display9.A_DISPCNT_BG_Mode;
		DISPCNT_BG0_2D_3D = Regs_Arm9.Sect_display9.A_DISPCNT_BG0_2D_3D;
		DISPCNT_Tile_OBJ_Mapping = Regs_Arm9.Sect_display9.A_DISPCNT_Tile_OBJ_Mapping;
		DISPCNT_Bitmap_OBJ_2D_Dim = Regs_Arm9.Sect_display9.A_DISPCNT_Bitmap_OBJ_2D_Dim;
		DISPCNT_Bitmap_OBJ_Mapping = Regs_Arm9.Sect_display9.A_DISPCNT_Bitmap_OBJ_Mapping;
		DISPCNT_Forced_Blank = Regs_Arm9.Sect_display9.A_DISPCNT_Forced_Blank;
		DISPCNT_Screen_Display_BG0 = Regs_Arm9.Sect_display9.A_DISPCNT_Screen_Display_BG0;
		DISPCNT_Screen_Display_BG1 = Regs_Arm9.Sect_display9.A_DISPCNT_Screen_Display_BG1;
		DISPCNT_Screen_Display_BG2 = Regs_Arm9.Sect_display9.A_DISPCNT_Screen_Display_BG2;
		DISPCNT_Screen_Display_BG3 = Regs_Arm9.Sect_display9.A_DISPCNT_Screen_Display_BG3;
		DISPCNT_Screen_Display_OBJ = Regs_Arm9.Sect_display9.A_DISPCNT_Screen_Display_OBJ;
		DISPCNT_Window_0_Display_Flag = Regs_Arm9.Sect_display9.A_DISPCNT_Window_0_Display_Flag;
		DISPCNT_Window_1_Display_Flag = Regs_Arm9.Sect_display9.A_DISPCNT_Window_1_Display_Flag;
		DISPCNT_OBJ_Wnd_Display_Flag = Regs_Arm9.Sect_display9.A_DISPCNT_OBJ_Wnd_Display_Flag;
		DISPCNT_Display_Mode = Regs_Arm9.Sect_display9.A_DISPCNT_Display_Mode;
		DISPCNT_VRAM_block = Regs_Arm9.Sect_display9.A_DISPCNT_VRAM_block;
		DISPCNT_Tile_OBJ_1D_Boundary = Regs_Arm9.Sect_display9.A_DISPCNT_Tile_OBJ_1D_Boundary;
		DISPCNT_Bitmap_OBJ_1D_Boundary = Regs_Arm9.Sect_display9.A_DISPCNT_Bitmap_OBJ_1D_Boundary;
		DISPCNT_OBJ_Process_H_Blank = Regs_Arm9.Sect_display9.A_DISPCNT_OBJ_Process_H_Blank;
		DISPCNT_Character_Base = Regs_Arm9.Sect_display9.A_DISPCNT_Character_Base;
		DISPCNT_Screen_Base = Regs_Arm9.Sect_display9.A_DISPCNT_Screen_Base;
		DISPCNT_BG_Extended_Palettes = Regs_Arm9.Sect_display9.A_DISPCNT_BG_Extended_Palettes;
		DISPCNT_OBJ_Extended_Palettes = Regs_Arm9.Sect_display9.A_DISPCNT_OBJ_Extended_Palettes;
		BG0CNT_BG_Priority = Regs_Arm9.Sect_display9.A_BG0CNT_BG_Priority;
		BG0CNT_Character_Base_Block = Regs_Arm9.Sect_display9.A_BG0CNT_Character_Base_Block;
		BG0CNT_Mosaic = Regs_Arm9.Sect_display9.A_BG0CNT_Mosaic;
		BG0CNT_Colors_Palettes = Regs_Arm9.Sect_display9.A_BG0CNT_Colors_Palettes;
		BG0CNT_Screen_Base_Block = Regs_Arm9.Sect_display9.A_BG0CNT_Screen_Base_Block;
		BG0CNT_Ext_Palette_Slot = Regs_Arm9.Sect_display9.A_BG0CNT_Ext_Palette_Slot;
		BG0CNT_Screen_Size = Regs_Arm9.Sect_display9.A_BG0CNT_Screen_Size;
		BG1CNT_BG_Priority = Regs_Arm9.Sect_display9.A_BG1CNT_BG_Priority;
		BG1CNT_Character_Base_Block = Regs_Arm9.Sect_display9.A_BG1CNT_Character_Base_Block;
		BG1CNT_Mosaic = Regs_Arm9.Sect_display9.A_BG1CNT_Mosaic;
		BG1CNT_Colors_Palettes = Regs_Arm9.Sect_display9.A_BG1CNT_Colors_Palettes;
		BG1CNT_Screen_Base_Block = Regs_Arm9.Sect_display9.A_BG1CNT_Screen_Base_Block;
		BG1CNT_Ext_Palette_Slot = Regs_Arm9.Sect_display9.A_BG1CNT_Ext_Palette_Slot;
		BG1CNT_Screen_Size = Regs_Arm9.Sect_display9.A_BG1CNT_Screen_Size;
		BG2CNT_BG_Priority = Regs_Arm9.Sect_display9.A_BG2CNT_BG_Priority;
		BG2CNT_Character_Base_Block = Regs_Arm9.Sect_display9.A_BG2CNT_Character_Base_Block;
		BG2CNT_Mosaic = Regs_Arm9.Sect_display9.A_BG2CNT_Mosaic;
		BG2CNT_Colors_Palettes = Regs_Arm9.Sect_display9.A_BG2CNT_Colors_Palettes;
		BG2CNT_Screen_Base_Block = Regs_Arm9.Sect_display9.A_BG2CNT_Screen_Base_Block;
		BG2CNT_Display_Area_Overflow = Regs_Arm9.Sect_display9.A_BG2CNT_Display_Area_Overflow;
		BG2CNT_Screen_Size = Regs_Arm9.Sect_display9.A_BG2CNT_Screen_Size;
		BG3CNT_BG_Priority = Regs_Arm9.Sect_display9.A_BG3CNT_BG_Priority;
		BG3CNT_Character_Base_Block = Regs_Arm9.Sect_display9.A_BG3CNT_Character_Base_Block;
		BG3CNT_Mosaic = Regs_Arm9.Sect_display9.A_BG3CNT_Mosaic;
		BG3CNT_Colors_Palettes = Regs_Arm9.Sect_display9.A_BG3CNT_Colors_Palettes;
		BG3CNT_Screen_Base_Block = Regs_Arm9.Sect_display9.A_BG3CNT_Screen_Base_Block;
		BG3CNT_Display_Area_Overflow = Regs_Arm9.Sect_display9.A_BG3CNT_Display_Area_Overflow;
		BG3CNT_Screen_Size = Regs_Arm9.Sect_display9.A_BG3CNT_Screen_Size;
		BG0HOFS = Regs_Arm9.Sect_display9.A_BG0HOFS;
		BG0VOFS = Regs_Arm9.Sect_display9.A_BG0VOFS;
		BG1HOFS = Regs_Arm9.Sect_display9.A_BG1HOFS;
		BG1VOFS = Regs_Arm9.Sect_display9.A_BG1VOFS;
		BG2HOFS = Regs_Arm9.Sect_display9.A_BG2HOFS;
		BG2VOFS = Regs_Arm9.Sect_display9.A_BG2VOFS;
		BG3HOFS = Regs_Arm9.Sect_display9.A_BG3HOFS;
		BG3VOFS = Regs_Arm9.Sect_display9.A_BG3VOFS;
		BG2RotScaleParDX = Regs_Arm9.Sect_display9.A_BG2RotScaleParDX;
		BG2RotScaleParDMX = Regs_Arm9.Sect_display9.A_BG2RotScaleParDMX;
		BG2RotScaleParDY = Regs_Arm9.Sect_display9.A_BG2RotScaleParDY;
		BG2RotScaleParDMY = Regs_Arm9.Sect_display9.A_BG2RotScaleParDMY;
		BG2RefX = Regs_Arm9.Sect_display9.A_BG2RefX;
		BG2RefY = Regs_Arm9.Sect_display9.A_BG2RefY;
		BG3RotScaleParDX = Regs_Arm9.Sect_display9.A_BG3RotScaleParDX;
		BG3RotScaleParDMX = Regs_Arm9.Sect_display9.A_BG3RotScaleParDMX;
		BG3RotScaleParDY = Regs_Arm9.Sect_display9.A_BG3RotScaleParDY;
		BG3RotScaleParDMY = Regs_Arm9.Sect_display9.A_BG3RotScaleParDMY;
		BG3RefX = Regs_Arm9.Sect_display9.A_BG3RefX;
		BG3RefY = Regs_Arm9.Sect_display9.A_BG3RefY;
		WIN0H_X2 = Regs_Arm9.Sect_display9.A_WIN0H_X2;
		WIN0H_X1 = Regs_Arm9.Sect_display9.A_WIN0H_X1;
		WIN1H_X2 = Regs_Arm9.Sect_display9.A_WIN1H_X2;
		WIN1H_X1 = Regs_Arm9.Sect_display9.A_WIN1H_X1;
		WIN0V_Y2 = Regs_Arm9.Sect_display9.A_WIN0V_Y2;
		WIN0V_Y1 = Regs_Arm9.Sect_display9.A_WIN0V_Y1;
		WIN1V_Y2 = Regs_Arm9.Sect_display9.A_WIN1V_Y2;
		WIN1V_Y1 = Regs_Arm9.Sect_display9.A_WIN1V_Y1;
		WININ = Regs_Arm9.Sect_display9.A_WININ;
		WININ_Window_0_BG0_Enable = Regs_Arm9.Sect_display9.A_WININ_Window_0_BG0_Enable;
		WININ_Window_0_BG1_Enable = Regs_Arm9.Sect_display9.A_WININ_Window_0_BG1_Enable;
		WININ_Window_0_BG2_Enable = Regs_Arm9.Sect_display9.A_WININ_Window_0_BG2_Enable;
		WININ_Window_0_BG3_Enable = Regs_Arm9.Sect_display9.A_WININ_Window_0_BG3_Enable;
		WININ_Window_0_OBJ_Enable = Regs_Arm9.Sect_display9.A_WININ_Window_0_OBJ_Enable;
		WININ_Window_0_Special_Effect = Regs_Arm9.Sect_display9.A_WININ_Window_0_Special_Effect;
		WININ_Window_1_BG0_Enable = Regs_Arm9.Sect_display9.A_WININ_Window_1_BG0_Enable;
		WININ_Window_1_BG1_Enable = Regs_Arm9.Sect_display9.A_WININ_Window_1_BG1_Enable;
		WININ_Window_1_BG2_Enable = Regs_Arm9.Sect_display9.A_WININ_Window_1_BG2_Enable;
		WININ_Window_1_BG3_Enable = Regs_Arm9.Sect_display9.A_WININ_Window_1_BG3_Enable;
		WININ_Window_1_OBJ_Enable = Regs_Arm9.Sect_display9.A_WININ_Window_1_OBJ_Enable;
		WININ_Window_1_Special_Effect = Regs_Arm9.Sect_display9.A_WININ_Window_1_Special_Effect;
		WINOUT = Regs_Arm9.Sect_display9.A_WINOUT;
		WINOUT_Outside_BG0_Enable = Regs_Arm9.Sect_display9.A_WINOUT_Outside_BG0_Enable;
		WINOUT_Outside_BG1_Enable = Regs_Arm9.Sect_display9.A_WINOUT_Outside_BG1_Enable;
		WINOUT_Outside_BG2_Enable = Regs_Arm9.Sect_display9.A_WINOUT_Outside_BG2_Enable;
		WINOUT_Outside_BG3_Enable = Regs_Arm9.Sect_display9.A_WINOUT_Outside_BG3_Enable;
		WINOUT_Outside_OBJ_Enable = Regs_Arm9.Sect_display9.A_WINOUT_Outside_OBJ_Enable;
		WINOUT_Outside_Special_Effect = Regs_Arm9.Sect_display9.A_WINOUT_Outside_Special_Effect;
		WINOUT_Objwnd_BG0_Enable = Regs_Arm9.Sect_display9.A_WINOUT_Objwnd_BG0_Enable;
		WINOUT_Objwnd_BG1_Enable = Regs_Arm9.Sect_display9.A_WINOUT_Objwnd_BG1_Enable;
		WINOUT_Objwnd_BG2_Enable = Regs_Arm9.Sect_display9.A_WINOUT_Objwnd_BG2_Enable;
		WINOUT_Objwnd_BG3_Enable = Regs_Arm9.Sect_display9.A_WINOUT_Objwnd_BG3_Enable;
		WINOUT_Objwnd_OBJ_Enable = Regs_Arm9.Sect_display9.A_WINOUT_Objwnd_OBJ_Enable;
		WINOUT_Objwnd_Special_Effect = Regs_Arm9.Sect_display9.A_WINOUT_Objwnd_Special_Effect;
		MOSAIC_BG_Mosaic_H_Size = Regs_Arm9.Sect_display9.A_MOSAIC_BG_Mosaic_H_Size;
		MOSAIC_BG_Mosaic_V_Size = Regs_Arm9.Sect_display9.A_MOSAIC_BG_Mosaic_V_Size;
		MOSAIC_OBJ_Mosaic_H_Size = Regs_Arm9.Sect_display9.A_MOSAIC_OBJ_Mosaic_H_Size;
		MOSAIC_OBJ_Mosaic_V_Size = Regs_Arm9.Sect_display9.A_MOSAIC_OBJ_Mosaic_V_Size;
		BLDCNT = Regs_Arm9.Sect_display9.A_BLDCNT;
		BLDCNT_BG0_1st_Target_Pixel = Regs_Arm9.Sect_display9.A_BLDCNT_BG0_1st_Target_Pixel;
		BLDCNT_BG1_1st_Target_Pixel = Regs_Arm9.Sect_display9.A_BLDCNT_BG1_1st_Target_Pixel;
		BLDCNT_BG2_1st_Target_Pixel = Regs_Arm9.Sect_display9.A_BLDCNT_BG2_1st_Target_Pixel;
		BLDCNT_BG3_1st_Target_Pixel = Regs_Arm9.Sect_display9.A_BLDCNT_BG3_1st_Target_Pixel;
		BLDCNT_OBJ_1st_Target_Pixel = Regs_Arm9.Sect_display9.A_BLDCNT_OBJ_1st_Target_Pixel;
		BLDCNT_BD_1st_Target_Pixel = Regs_Arm9.Sect_display9.A_BLDCNT_BD_1st_Target_Pixel;
		BLDCNT_Color_Special_Effect = Regs_Arm9.Sect_display9.A_BLDCNT_Color_Special_Effect;
		BLDCNT_BG0_2nd_Target_Pixel = Regs_Arm9.Sect_display9.A_BLDCNT_BG0_2nd_Target_Pixel;
		BLDCNT_BG1_2nd_Target_Pixel = Regs_Arm9.Sect_display9.A_BLDCNT_BG1_2nd_Target_Pixel;
		BLDCNT_BG2_2nd_Target_Pixel = Regs_Arm9.Sect_display9.A_BLDCNT_BG2_2nd_Target_Pixel;
		BLDCNT_BG3_2nd_Target_Pixel = Regs_Arm9.Sect_display9.A_BLDCNT_BG3_2nd_Target_Pixel;
		BLDCNT_OBJ_2nd_Target_Pixel = Regs_Arm9.Sect_display9.A_BLDCNT_OBJ_2nd_Target_Pixel;
		BLDCNT_BD_2nd_Target_Pixel = Regs_Arm9.Sect_display9.A_BLDCNT_BD_2nd_Target_Pixel;
		BLDALPHA_EVA_Coefficient = Regs_Arm9.Sect_display9.A_BLDALPHA_EVA_Coefficient;
		BLDALPHA_EVB_Coefficient = Regs_Arm9.Sect_display9.A_BLDALPHA_EVB_Coefficient;
		BLDY = Regs_Arm9.Sect_display9.A_BLDY;
		MASTER_BRIGHT_Factor = Regs_Arm9.Sect_display9.A_MASTER_BRIGHT_Factor;
		MASTER_BRIGHT_Mode = Regs_Arm9.Sect_display9.A_MASTER_BRIGHT_Mode;
	}
	else
	{
		DISPCNT_BG_Mode = Regs_Arm9.Sect_display9.B_DISPCNT_BG_Mode;
		DISPCNT_BG0_2D_3D = Regs_Arm9.Sect_display9.B_DISPCNT_BG0_2D_3D;
		DISPCNT_Tile_OBJ_Mapping = Regs_Arm9.Sect_display9.B_DISPCNT_Tile_OBJ_Mapping;
		DISPCNT_Bitmap_OBJ_2D_Dim = Regs_Arm9.Sect_display9.B_DISPCNT_Bitmap_OBJ_2D_Dim;
		DISPCNT_Bitmap_OBJ_Mapping = Regs_Arm9.Sect_display9.B_DISPCNT_Bitmap_OBJ_Mapping;
		DISPCNT_Forced_Blank = Regs_Arm9.Sect_display9.B_DISPCNT_Forced_Blank;
		DISPCNT_Screen_Display_BG0 = Regs_Arm9.Sect_display9.B_DISPCNT_Screen_Display_BG0;
		DISPCNT_Screen_Display_BG1 = Regs_Arm9.Sect_display9.B_DISPCNT_Screen_Display_BG1;
		DISPCNT_Screen_Display_BG2 = Regs_Arm9.Sect_display9.B_DISPCNT_Screen_Display_BG2;
		DISPCNT_Screen_Display_BG3 = Regs_Arm9.Sect_display9.B_DISPCNT_Screen_Display_BG3;
		DISPCNT_Screen_Display_OBJ = Regs_Arm9.Sect_display9.B_DISPCNT_Screen_Display_OBJ;
		DISPCNT_Window_0_Display_Flag = Regs_Arm9.Sect_display9.B_DISPCNT_Window_0_Display_Flag;
		DISPCNT_Window_1_Display_Flag = Regs_Arm9.Sect_display9.B_DISPCNT_Window_1_Display_Flag;
		DISPCNT_OBJ_Wnd_Display_Flag = Regs_Arm9.Sect_display9.B_DISPCNT_OBJ_Wnd_Display_Flag;
		DISPCNT_Display_Mode = Regs_Arm9.Sect_display9.B_DISPCNT_Display_Mode;
		DISPCNT_VRAM_block = Regs_Arm9.Sect_display9.B_DISPCNT_VRAM_block;
		DISPCNT_Tile_OBJ_1D_Boundary = Regs_Arm9.Sect_display9.B_DISPCNT_Tile_OBJ_1D_Boundary;
		DISPCNT_Bitmap_OBJ_1D_Boundary = Regs_Arm9.Sect_display9.B_DISPCNT_Bitmap_OBJ_1D_Boundary;
		DISPCNT_OBJ_Process_H_Blank = Regs_Arm9.Sect_display9.B_DISPCNT_OBJ_Process_H_Blank;
		DISPCNT_Character_Base = Regs_Arm9.Sect_display9.B_DISPCNT_Character_Base;
		DISPCNT_Screen_Base = Regs_Arm9.Sect_display9.B_DISPCNT_Screen_Base;
		DISPCNT_BG_Extended_Palettes = Regs_Arm9.Sect_display9.B_DISPCNT_BG_Extended_Palettes;
		DISPCNT_OBJ_Extended_Palettes = Regs_Arm9.Sect_display9.B_DISPCNT_OBJ_Extended_Palettes;
		BG0CNT_BG_Priority = Regs_Arm9.Sect_display9.B_BG0CNT_BG_Priority;
		BG0CNT_Character_Base_Block = Regs_Arm9.Sect_display9.B_BG0CNT_Character_Base_Block;
		BG0CNT_Mosaic = Regs_Arm9.Sect_display9.B_BG0CNT_Mosaic;
		BG0CNT_Colors_Palettes = Regs_Arm9.Sect_display9.B_BG0CNT_Colors_Palettes;
		BG0CNT_Screen_Base_Block = Regs_Arm9.Sect_display9.B_BG0CNT_Screen_Base_Block;
		BG0CNT_Ext_Palette_Slot = Regs_Arm9.Sect_display9.B_BG0CNT_Ext_Palette_Slot;
		BG0CNT_Screen_Size = Regs_Arm9.Sect_display9.B_BG0CNT_Screen_Size;
		BG1CNT_BG_Priority = Regs_Arm9.Sect_display9.B_BG1CNT_BG_Priority;
		BG1CNT_Character_Base_Block = Regs_Arm9.Sect_display9.B_BG1CNT_Character_Base_Block;
		BG1CNT_Mosaic = Regs_Arm9.Sect_display9.B_BG1CNT_Mosaic;
		BG1CNT_Colors_Palettes = Regs_Arm9.Sect_display9.B_BG1CNT_Colors_Palettes;
		BG1CNT_Screen_Base_Block = Regs_Arm9.Sect_display9.B_BG1CNT_Screen_Base_Block;
		BG1CNT_Ext_Palette_Slot = Regs_Arm9.Sect_display9.B_BG1CNT_Ext_Palette_Slot;
		BG1CNT_Screen_Size = Regs_Arm9.Sect_display9.B_BG1CNT_Screen_Size;
		BG2CNT_BG_Priority = Regs_Arm9.Sect_display9.B_BG2CNT_BG_Priority;
		BG2CNT_Character_Base_Block = Regs_Arm9.Sect_display9.B_BG2CNT_Character_Base_Block;
		BG2CNT_Mosaic = Regs_Arm9.Sect_display9.B_BG2CNT_Mosaic;
		BG2CNT_Colors_Palettes = Regs_Arm9.Sect_display9.B_BG2CNT_Colors_Palettes;
		BG2CNT_Screen_Base_Block = Regs_Arm9.Sect_display9.B_BG2CNT_Screen_Base_Block;
		BG2CNT_Display_Area_Overflow = Regs_Arm9.Sect_display9.B_BG2CNT_Display_Area_Overflow;
		BG2CNT_Screen_Size = Regs_Arm9.Sect_display9.B_BG2CNT_Screen_Size;
		BG3CNT_BG_Priority = Regs_Arm9.Sect_display9.B_BG3CNT_BG_Priority;
		BG3CNT_Character_Base_Block = Regs_Arm9.Sect_display9.B_BG3CNT_Character_Base_Block;
		BG3CNT_Mosaic = Regs_Arm9.Sect_display9.B_BG3CNT_Mosaic;
		BG3CNT_Colors_Palettes = Regs_Arm9.Sect_display9.B_BG3CNT_Colors_Palettes;
		BG3CNT_Screen_Base_Block = Regs_Arm9.Sect_display9.B_BG3CNT_Screen_Base_Block;
		BG3CNT_Display_Area_Overflow = Regs_Arm9.Sect_display9.B_BG3CNT_Display_Area_Overflow;
		BG3CNT_Screen_Size = Regs_Arm9.Sect_display9.B_BG3CNT_Screen_Size;
		BG0HOFS = Regs_Arm9.Sect_display9.B_BG0HOFS;
		BG0VOFS = Regs_Arm9.Sect_display9.B_BG0VOFS;
		BG1HOFS = Regs_Arm9.Sect_display9.B_BG1HOFS;
		BG1VOFS = Regs_Arm9.Sect_display9.B_BG1VOFS;
		BG2HOFS = Regs_Arm9.Sect_display9.B_BG2HOFS;
		BG2VOFS = Regs_Arm9.Sect_display9.B_BG2VOFS;
		BG3HOFS = Regs_Arm9.Sect_display9.B_BG3HOFS;
		BG3VOFS = Regs_Arm9.Sect_display9.B_BG3VOFS;
		BG2RotScaleParDX = Regs_Arm9.Sect_display9.B_BG2RotScaleParDX;
		BG2RotScaleParDMX = Regs_Arm9.Sect_display9.B_BG2RotScaleParDMX;
		BG2RotScaleParDY = Regs_Arm9.Sect_display9.B_BG2RotScaleParDY;
		BG2RotScaleParDMY = Regs_Arm9.Sect_display9.B_BG2RotScaleParDMY;
		BG2RefX = Regs_Arm9.Sect_display9.B_BG2RefX;
		BG2RefY = Regs_Arm9.Sect_display9.B_BG2RefY;
		BG3RotScaleParDX = Regs_Arm9.Sect_display9.B_BG3RotScaleParDX;
		BG3RotScaleParDMX = Regs_Arm9.Sect_display9.B_BG3RotScaleParDMX;
		BG3RotScaleParDY = Regs_Arm9.Sect_display9.B_BG3RotScaleParDY;
		BG3RotScaleParDMY = Regs_Arm9.Sect_display9.B_BG3RotScaleParDMY;
		BG3RefX = Regs_Arm9.Sect_display9.B_BG3RefX;
		BG3RefY = Regs_Arm9.Sect_display9.B_BG3RefY;
		WIN0H_X2 = Regs_Arm9.Sect_display9.B_WIN0H_X2;
		WIN0H_X1 = Regs_Arm9.Sect_display9.B_WIN0H_X1;
		WIN1H_X2 = Regs_Arm9.Sect_display9.B_WIN1H_X2;
		WIN1H_X1 = Regs_Arm9.Sect_display9.B_WIN1H_X1;
		WIN0V_Y2 = Regs_Arm9.Sect_display9.B_WIN0V_Y2;
		WIN0V_Y1 = Regs_Arm9.Sect_display9.B_WIN0V_Y1;
		WIN1V_Y2 = Regs_Arm9.Sect_display9.B_WIN1V_Y2;
		WIN1V_Y1 = Regs_Arm9.Sect_display9.B_WIN1V_Y1;
		WININ = Regs_Arm9.Sect_display9.B_WININ;
		WININ_Window_0_BG0_Enable = Regs_Arm9.Sect_display9.B_WININ_Window_0_BG0_Enable;
		WININ_Window_0_BG1_Enable = Regs_Arm9.Sect_display9.B_WININ_Window_0_BG1_Enable;
		WININ_Window_0_BG2_Enable = Regs_Arm9.Sect_display9.B_WININ_Window_0_BG2_Enable;
		WININ_Window_0_BG3_Enable = Regs_Arm9.Sect_display9.B_WININ_Window_0_BG3_Enable;
		WININ_Window_0_OBJ_Enable = Regs_Arm9.Sect_display9.B_WININ_Window_0_OBJ_Enable;
		WININ_Window_0_Special_Effect = Regs_Arm9.Sect_display9.B_WININ_Window_0_Special_Effect;
		WININ_Window_1_BG0_Enable = Regs_Arm9.Sect_display9.B_WININ_Window_1_BG0_Enable;
		WININ_Window_1_BG1_Enable = Regs_Arm9.Sect_display9.B_WININ_Window_1_BG1_Enable;
		WININ_Window_1_BG2_Enable = Regs_Arm9.Sect_display9.B_WININ_Window_1_BG2_Enable;
		WININ_Window_1_BG3_Enable = Regs_Arm9.Sect_display9.B_WININ_Window_1_BG3_Enable;
		WININ_Window_1_OBJ_Enable = Regs_Arm9.Sect_display9.B_WININ_Window_1_OBJ_Enable;
		WININ_Window_1_Special_Effect = Regs_Arm9.Sect_display9.B_WININ_Window_1_Special_Effect;
		WINOUT = Regs_Arm9.Sect_display9.B_WINOUT;
		WINOUT_Outside_BG0_Enable = Regs_Arm9.Sect_display9.B_WINOUT_Outside_BG0_Enable;
		WINOUT_Outside_BG1_Enable = Regs_Arm9.Sect_display9.B_WINOUT_Outside_BG1_Enable;
		WINOUT_Outside_BG2_Enable = Regs_Arm9.Sect_display9.B_WINOUT_Outside_BG2_Enable;
		WINOUT_Outside_BG3_Enable = Regs_Arm9.Sect_display9.B_WINOUT_Outside_BG3_Enable;
		WINOUT_Outside_OBJ_Enable = Regs_Arm9.Sect_display9.B_WINOUT_Outside_OBJ_Enable;
		WINOUT_Outside_Special_Effect = Regs_Arm9.Sect_display9.B_WINOUT_Outside_Special_Effect;
		WINOUT_Objwnd_BG0_Enable = Regs_Arm9.Sect_display9.B_WINOUT_Objwnd_BG0_Enable;
		WINOUT_Objwnd_BG1_Enable = Regs_Arm9.Sect_display9.B_WINOUT_Objwnd_BG1_Enable;
		WINOUT_Objwnd_BG2_Enable = Regs_Arm9.Sect_display9.B_WINOUT_Objwnd_BG2_Enable;
		WINOUT_Objwnd_BG3_Enable = Regs_Arm9.Sect_display9.B_WINOUT_Objwnd_BG3_Enable;
		WINOUT_Objwnd_OBJ_Enable = Regs_Arm9.Sect_display9.B_WINOUT_Objwnd_OBJ_Enable;
		WINOUT_Objwnd_Special_Effect = Regs_Arm9.Sect_display9.B_WINOUT_Objwnd_Special_Effect;
		MOSAIC_BG_Mosaic_H_Size = Regs_Arm9.Sect_display9.B_MOSAIC_BG_Mosaic_H_Size;
		MOSAIC_BG_Mosaic_V_Size = Regs_Arm9.Sect_display9.B_MOSAIC_BG_Mosaic_V_Size;
		MOSAIC_OBJ_Mosaic_H_Size = Regs_Arm9.Sect_display9.B_MOSAIC_OBJ_Mosaic_H_Size;
		MOSAIC_OBJ_Mosaic_V_Size = Regs_Arm9.Sect_display9.B_MOSAIC_OBJ_Mosaic_V_Size;
		BLDCNT = Regs_Arm9.Sect_display9.B_BLDCNT;
		BLDCNT_BG0_1st_Target_Pixel = Regs_Arm9.Sect_display9.B_BLDCNT_BG0_1st_Target_Pixel;
		BLDCNT_BG1_1st_Target_Pixel = Regs_Arm9.Sect_display9.B_BLDCNT_BG1_1st_Target_Pixel;
		BLDCNT_BG2_1st_Target_Pixel = Regs_Arm9.Sect_display9.B_BLDCNT_BG2_1st_Target_Pixel;
		BLDCNT_BG3_1st_Target_Pixel = Regs_Arm9.Sect_display9.B_BLDCNT_BG3_1st_Target_Pixel;
		BLDCNT_OBJ_1st_Target_Pixel = Regs_Arm9.Sect_display9.B_BLDCNT_OBJ_1st_Target_Pixel;
		BLDCNT_BD_1st_Target_Pixel = Regs_Arm9.Sect_display9.B_BLDCNT_BD_1st_Target_Pixel;
		BLDCNT_Color_Special_Effect = Regs_Arm9.Sect_display9.B_BLDCNT_Color_Special_Effect;
		BLDCNT_BG0_2nd_Target_Pixel = Regs_Arm9.Sect_display9.B_BLDCNT_BG0_2nd_Target_Pixel;
		BLDCNT_BG1_2nd_Target_Pixel = Regs_Arm9.Sect_display9.B_BLDCNT_BG1_2nd_Target_Pixel;
		BLDCNT_BG2_2nd_Target_Pixel = Regs_Arm9.Sect_display9.B_BLDCNT_BG2_2nd_Target_Pixel;
		BLDCNT_BG3_2nd_Target_Pixel = Regs_Arm9.Sect_display9.B_BLDCNT_BG3_2nd_Target_Pixel;
		BLDCNT_OBJ_2nd_Target_Pixel = Regs_Arm9.Sect_display9.B_BLDCNT_OBJ_2nd_Target_Pixel;
		BLDCNT_BD_2nd_Target_Pixel = Regs_Arm9.Sect_display9.B_BLDCNT_BD_2nd_Target_Pixel;
		BLDALPHA_EVA_Coefficient = Regs_Arm9.Sect_display9.B_BLDALPHA_EVA_Coefficient;
		BLDALPHA_EVB_Coefficient = Regs_Arm9.Sect_display9.B_BLDALPHA_EVB_Coefficient;
		BLDY = Regs_Arm9.Sect_display9.B_BLDY;
		MASTER_BRIGHT_Factor = Regs_Arm9.Sect_display9.B_MASTER_BRIGHT_Factor;
		MASTER_BRIGHT_Mode = Regs_Arm9.Sect_display9.B_MASTER_BRIGHT_Mode;
	}
}

void Gpu::dispcnt_write()
{
	videomode = (byte)DISPCNT_BG_Mode.read();
	displaymode = (byte)DISPCNT_Display_Mode.read();

	ext_palette_bg = DISPCNT_BG_Extended_Palettes.on();
	ext_palette_obj = DISPCNT_OBJ_Extended_Palettes.on();

	if (isGPUA)
	{
		screenbase = DISPCNT_Screen_Base.read() * 32;
		charbase = DISPCNT_Character_Base.read() * 4;
		is3D = DISPCNT_BG0_2D_3D.on();
	}

	bool new_forcedblank = DISPCNT_Forced_Blank.on();
	if (forcedblank && !new_forcedblank)
	{
		GPU_Timing.restart_line();
	}
	forcedblank = new_forcedblank;
}

void Gpu::refpoint_update_all()
{
	refpoint_update_2x();
	refpoint_update_2y();
	refpoint_update_3x();
	refpoint_update_3y();
}

void Gpu::refpoint_update_2x()
{
	ref2_x = (Int32)BG2RefX.read();
	if (((ref2_x >> 27) & 1) == 1) { ref2_x = (Int32)(ref2_x | 0xF0000000); }
	ref2_x_new = false;
}
void Gpu::refpoint_update_2y()
{
	ref2_y = (Int32)BG2RefY.read();
	if (((ref2_y >> 27) & 1) == 1) { ref2_y = (Int32)(ref2_y | 0xF0000000); }
	ref2_y_new = false;
}
void Gpu::refpoint_update_3x()
{
	ref3_x = (Int32)BG3RefX.read();
	if (((ref3_x >> 27) & 1) == 1) { ref3_x = (Int32)(ref3_x | 0xF0000000); }
}
void Gpu::refpoint_update_3y()
{
	ref3_y = (Int32)BG3RefY.read();
	if (((ref3_y >> 27) & 1) == 1) { ref3_y = (Int32)(ref3_y | 0xF0000000); }
}

void Gpu::refpoint_update_2x_new()
{
	if (GPU_Timing.gpustate == GPUState::VISIBLE)
	{
		ref2_x_next = (Int32)BG2RefX.read();
		if (((ref2_x_next >> 27) & 1) == 1) { ref2_x_next = (Int32)(ref2_x_next | 0xF0000000); }
		ref2_x_new = true;
	}
	else
	{
		refpoint_update_2x();
	}
}
void Gpu::refpoint_update_2y_new()
{
	if (GPU_Timing.gpustate == GPUState::VISIBLE)
	{
		ref2_y_next = (Int32)BG2RefY.read();
		if (((ref2_y_next >> 27) & 1) == 1) { ref2_y_next = (Int32)(ref2_y_next | 0xF0000000); }
		ref2_y_new = true;
	}
	else
	{
		refpoint_update_2y();
	}
}
void Gpu::refpoint_update_3x_new()
{
	if (GPU_Timing.gpustate == GPUState::VISIBLE)
	{
		ref3_x_next = (Int32)BG3RefX.read();
		if (((ref3_x_next >> 27) & 1) == 1) { ref3_x_next = (Int32)(ref3_x_next | 0xF0000000); }
		ref3_x_new = true;
	}
	else
	{
		refpoint_update_3x();
	}
}
void Gpu::refpoint_update_3y_new()
{
	if (GPU_Timing.gpustate == GPUState::VISIBLE)
	{
		ref3_y_next = (Int32)BG3RefY.read();
		if (((ref3_y_next >> 27) & 1) == 1) { ref3_y_next = (Int32)(ref3_y_next | 0xF0000000); }
		ref3_y_new = true;
	}
	else
	{
		refpoint_update_3y();
	}
}

void Gpu::once_per_hblank()
{
	bool Screen_Display_BG0_on = DISPCNT_Screen_Display_BG0.on();
	on_delay_bg0[2] = on_delay_bg0[1] && Screen_Display_BG0_on;
	on_delay_bg0[1] = on_delay_bg0[0] && Screen_Display_BG0_on;
	on_delay_bg0[0] = Screen_Display_BG0_on;
	
	bool Screen_Display_BG1_on = DISPCNT_Screen_Display_BG1.on();
	on_delay_bg1[2] = on_delay_bg1[1] && Screen_Display_BG1_on;
	on_delay_bg1[1] = on_delay_bg1[0] && Screen_Display_BG1_on;
	on_delay_bg1[0] = Screen_Display_BG1_on;
	
	bool Screen_Display_BG2_on = DISPCNT_Screen_Display_BG2.on();
	on_delay_bg2[2] = on_delay_bg2[1] && Screen_Display_BG2_on;
	on_delay_bg2[1] = on_delay_bg2[0] && Screen_Display_BG2_on;
	on_delay_bg2[0] = Screen_Display_BG2_on;
	
	bool Screen_Display_BG3_on = DISPCNT_Screen_Display_BG3.on();
	on_delay_bg3[2] = on_delay_bg3[1] && Screen_Display_BG3_on;
	on_delay_bg3[1] = on_delay_bg3[0] && Screen_Display_BG3_on;
	on_delay_bg3[0] = Screen_Display_BG3_on;
}

void Gpu::next_line(byte line)
{
	if (line == 0)
	{
		mosaik_bg0_vcnt = 0;
		mosaik_bg1_vcnt = 0;
		mosaik_bg2_vcnt = 0;
		mosaik_bg3_vcnt = 0;
		even_frame = !even_frame;
	}

	draw_line(line);
	if (line == 191)
	{
		frameskip_counter++;
		if (frameskip_counter > frameskip)
		{
			frameskip_counter = 0;
		}
		Uint64 currentTime;
		double micros = 0;
		if (lockSpeed)
		{
			while (micros < frametimeleft)
			{
				currentTime = SDL_GetPerformanceCounter();
				micros = (double)((currentTime - lastTime_frame) * 1000000 / (double)SDL_GetPerformanceFrequency());
				if (frametimeleft - micros > 1000)
				{
					//Thread.Sleep(1);
				}
			}
			lastTime_frame = SDL_GetPerformanceCounter();
			//frametimeleft = max(1000, frametimeleft - micros + (FRAMETIME / speedmult));
		}
		if (SDL_LockMutex(drawlock) == 0)
		{
			intern_frames++;
			SDL_UnlockMutex(drawlock);
		}

		if (videomode > 3)
		{
			bool framebuffer_select_new = false;// DISPCNT_Display_Frame_Select.on();
			if (framebuffer_select_new != framebuffer_select)
			{
				framebuffer_select = framebuffer_select_new;
				videomode_frames++;
			}
		}
		else
		{
			videomode_frames++;
		}
	}

	if ((videomode > 0 && DISPCNT_Screen_Display_BG2.on()))
	{
		Int16 BG2_DMX = (Int16)BG2RotScaleParDMX.read();
		Int16 BG2_DMY = (Int16)BG2RotScaleParDMY.read();
		ref2_x += BG2_DMX;
		ref2_y += BG2_DMY;
	}

	if (videomode >= 2 && DISPCNT_Screen_Display_BG3.on())
	{
		Int16 BG3_DMX = (Int16)BG3RotScaleParDMX.read();
		Int16 BG3_DMY = (Int16)BG3RotScaleParDMY.read();
		ref3_x += BG3_DMX;
		ref3_y += BG3_DMY;
	}
}

void Gpu::draw_line(byte y_in)
{
	if (frameskip_counter < frameskip)
	{
		while (!mainmemfifo.empty()) mainmemfifo.pop();
		return;
	}

	if (disabled)
	{
		return;
	}

	byte y = y_in;

	if (forcedblank)
	{
		//if (SDL_LockMutex(drawlock) == 0)
		{
			{
				for (int x = 0; x < 256; x++)
				{
					pixels[x][y].update(255, 255, 255);
				}
			}
			//SDL_UnlockMutex(drawlock);
		}
		return;
	}

	//if (SDL_LockMutex(drawlock) == 0)
	{
		UInt16 colorall = *(UInt16*)&Memory.PaletteRAM[0];
		pixelbackdrop.update((Byte)((colorall & 0x1F) * 8), (byte)(((colorall >> 5) & 0x1F) * 8), (byte)(((colorall >> 10) & 0x1F) * 8));

		byte prio_bg0 = (byte)BG0CNT_BG_Priority.read();
		byte prio_bg1 = (byte)BG1CNT_BG_Priority.read();
		byte prio_bg2 = (byte)BG2CNT_BG_Priority.read();
		byte prio_bg3 = (byte)BG3CNT_BG_Priority.read();

		byte mosaic_bg_h = (byte)MOSAIC_BG_Mosaic_H_Size.read();
		byte mosaic_bg_v = (byte)MOSAIC_BG_Mosaic_V_Size.read();

		int pixelcount = 256;
		if (doubleres)
		{
			pixelcount = 512;
		}

		if (displaymode == 1)
		{
			if (((layerenable & 1) > 0) && on_delay_bg0[2])
			{
				bool mosaic_on = BG0CNT_Mosaic.on();
				if (!mosaic_on || mosaik_bg0_vcnt == 0)
				{
					for (int x = 0; x < 256; x++)
					{
						pixels_bg0[x].prio = prio_bg0;
						pixels_bg0[x].transparent = true;
					}
					if (is3D)
					{
						draw_3D(y);
					}
					else if (videomode < 6)
					{
						draw_bg_mode0(pixels_bg0,
							0,
							y,
							BG0CNT_Screen_Base_Block.read() + screenbase,
							BG0CNT_Character_Base_Block.read() + charbase,
							BG0CNT_Ext_Palette_Slot.read(),
							BG0CNT_Colors_Palettes.on(),
							(byte)BG0CNT_Screen_Size.read(),
							(UInt16)BG0HOFS.read(),
							(UInt16)BG0VOFS.read());
					}
					if (mosaic_on)
					{
						byte mosaic_h = 0;
						for (int x = 0; x < 256; x++)
						{
							if (mosaic_h != 0)
							{
								pixels_bg0[x].copy(pixels_bg0[x - mosaic_h]);
							}
							if (mosaic_h >= mosaic_bg_h) { mosaic_h = 0; }
							else mosaic_h++;
						}
					}
				}
				if (mosaik_bg0_vcnt >= mosaic_bg_v) { mosaik_bg0_vcnt = 0; }
				else mosaik_bg0_vcnt++;
			}
			else
			{
				for (int x = 0; x < 256; x++)
				{
					pixels_bg0[x].transparent = true;
				}
			}

			if (((layerenable & 2) > 0) && on_delay_bg1[2])
			{
				bool mosaic_on = BG1CNT_Mosaic.on();
				if (!mosaic_on || mosaik_bg1_vcnt == 0)
				{
					for (int x = 0; x < 256; x++)
					{
						pixels_bg1[x].prio = prio_bg1;
						pixels_bg1[x].transparent = true;
					}
					if (videomode < 6)
					{
						draw_bg_mode0(pixels_bg1,
							1,
							y,
							BG1CNT_Screen_Base_Block.read() + screenbase,
							BG1CNT_Character_Base_Block.read() + charbase,
							BG1CNT_Ext_Palette_Slot.read(),
							BG1CNT_Colors_Palettes.on(),
							(byte)BG1CNT_Screen_Size.read(),
							(UInt16)BG1HOFS.read(),
							(UInt16)BG1VOFS.read());
					}
					if (mosaic_on)
					{
						byte mosaic_h = 0;
						for (int x = 0; x < 256; x++)
						{
							if (mosaic_h != 0)
							{
								pixels_bg1[x].copy(pixels_bg1[x - mosaic_h]);
							}
							if (mosaic_h >= mosaic_bg_h) { mosaic_h = 0; }
							else mosaic_h++;
						}
					}
				}
				if (mosaik_bg1_vcnt >= mosaic_bg_v) { mosaik_bg1_vcnt = 0; }
				else mosaik_bg1_vcnt++;
			}
			else
			{
				for (int x = 0; x < 256; x++)
				{
					pixels_bg1[x].transparent = true;
				}
			}

			if (((layerenable & 4) > 0) && on_delay_bg2[2])
			{
				bool mosaic_on = BG2CNT_Mosaic.on();
				if (!mosaic_on || mosaik_bg2_vcnt == 0)
				{
					for (int x = 0; x < pixelcount; x++)
					{
						pixels_bg2_1[x].prio = prio_bg2;
						pixels_bg2_1[x].transparent = true;
						if (doubleres)
						{
							pixels_bg2_2[x].prio = prio_bg2;
							pixels_bg2_2[x].transparent = true;
						}
					}
					switch (videomode)
					{
					case 0:
					case 1:
					case 3:
						draw_bg_mode0(pixels_bg2_1,
							2,
							y,
							BG2CNT_Screen_Base_Block.read() + screenbase,
							BG2CNT_Character_Base_Block.read() + charbase,
							0,
							BG2CNT_Colors_Palettes.on(),
							(byte)BG2CNT_Screen_Size.read(),
							(UInt16)BG2HOFS.read(),
							(UInt16)BG2VOFS.read());
						break;
					case 2:
					case 4:
						draw_bg_mode2(pixels_bg2_1,
							2,
							false,
							BG2CNT_Screen_Base_Block.read() + screenbase,
							BG2CNT_Character_Base_Block.read() + charbase,
							0,
							BG2CNT_Display_Area_Overflow.on(),
							(byte)BG2CNT_Screen_Size.read(),
							ref2_x,
							ref2_y,
							(Int16)BG2RotScaleParDX.read(),
							(Int16)BG2RotScaleParDY.read(),
							doubleres,
							true);
						if (doubleres)
						{
							Int16 BG2_DMX = (Int16)BG2RotScaleParDMX.read();
							Int16 BG2_DMY = (Int16)BG2RotScaleParDMY.read();
							draw_bg_mode2(pixels_bg2_2,
								2,
								false,
								BG2CNT_Screen_Base_Block.read() + screenbase,
								BG2CNT_Character_Base_Block.read() + charbase,
								0,
								BG2CNT_Display_Area_Overflow.on(),
								(byte)BG2CNT_Screen_Size.read(),
								ref2_x + BG2_DMX / 2,
								ref2_y + BG2_DMY / 2,
								(Int16)BG2RotScaleParDX.read(),
								(Int16)BG2RotScaleParDY.read(),
								doubleres,
								true);
						}
						break;
					case 5:
						switch ((BG2CNT_Colors_Palettes.read() * 2) + (BG2CNT_Character_Base_Block.read() & 1))
						{
						case 0: //rot / scal with 16bit bgmap entries(Text + Affine mixup)
						case 1:
							draw_bg_mode2(pixels_bg2,
								2,
								true,
								BG2CNT_Screen_Base_Block.read() + screenbase,
								BG2CNT_Character_Base_Block.read() + charbase,
								0,
								BG2CNT_Display_Area_Overflow.on(),
								(byte)BG2CNT_Screen_Size.read(),
								ref2_x,
								ref2_y,
								(Int16)BG2RotScaleParDX.read(),
								(Int16)BG2RotScaleParDY.read(),
								false,
								false);
							break;

						case 2: // rot/scal 256 color bitmap
							draw_bg_mode4(
								pixels_bg2,
								BG2CNT_Display_Area_Overflow.on(),
								BG2CNT_Screen_Base_Block.read(),
								ref2_x,
								ref2_y,
								(Int16)BG2RotScaleParDX.read(),
								(Int16)BG2RotScaleParDY.read());
							break;

						case 3: // rot/scal direct color bitmap
							draw_bg_mode5(
								pixels_bg2,
								BG2CNT_Display_Area_Overflow.on(),
								BG2CNT_Screen_Base_Block.read(),
								ref2_x,
								ref2_y,
								(Int16)BG2RotScaleParDX.read(),
								(Int16)BG2RotScaleParDY.read());
							break;
						}
						break;
					case 6: // large
						break;
					}
					if (mosaic_on)
					{
						byte mosaic_h = 0;
						for (int x = 0; x < 256; x++)
						{
							if (mosaic_h != 0)
							{
								pixels_bg2[x].copy(pixels_bg2[x - mosaic_h]);
							}
							if (mosaic_h >= mosaic_bg_h) { mosaic_h = 0; }
							else mosaic_h++;
						}
					}
				}
				if (mosaik_bg2_vcnt >= mosaic_bg_v) { mosaik_bg2_vcnt = 0; }
				else mosaik_bg2_vcnt++;
			}
			else
			{
				if (doubleres)
				{
					for (int x = 0; x < pixelcount; x++) { pixels_bg2_1[x].transparent = true; pixels_bg2_2[x].transparent = true; }
				}
				else
				{
					for (int x = 0; x < pixelcount; x++) pixels_bg2_1[x].transparent = true;
				}
			}

			if (((layerenable & 8) > 0) && on_delay_bg3[2])
			{
				bool mosaic_on = BG3CNT_Mosaic.on();
				if (!mosaic_on || mosaik_bg3_vcnt == 0)
				{
					for (int x = 0; x < 256; x++)
					{
						pixels_bg3[x].transparent = true;
						pixels_bg3[x].prio = prio_bg3;
					}
					switch (videomode)
					{
					case 0:
						draw_bg_mode0(pixels_bg3,
							3,
							y,
							BG3CNT_Screen_Base_Block.read() + screenbase,
							BG3CNT_Character_Base_Block.read() + charbase,
							0,
							BG3CNT_Colors_Palettes.on(),
							(byte)BG3CNT_Screen_Size.read(),
							(UInt16)BG3HOFS.read(),
							(UInt16)BG3VOFS.read());
						break;
					case 1:
					case 2:
						draw_bg_mode2(pixels_bg3,
							3,
							false,
							BG3CNT_Screen_Base_Block.read() + screenbase,
							BG3CNT_Character_Base_Block.read() + charbase,
							0,
							BG3CNT_Display_Area_Overflow.on(),
							(byte)BG3CNT_Screen_Size.read(),
							ref3_x,
							ref3_y,
							(Int16)BG3RotScaleParDX.read(),
							(Int16)BG3RotScaleParDY.read(),
							false,
							false);
						break;
					case 3:
					case 4:
					case 5:
						switch ((BG3CNT_Colors_Palettes.read() * 2) + (BG3CNT_Character_Base_Block.read() & 1))
						{
						case 0: //rot / scal with 16bit bgmap entries(Text + Affine mixup)
						case 1:
							draw_bg_mode2(pixels_bg3,
								3,
								true,
								BG3CNT_Screen_Base_Block.read() + screenbase,
								BG3CNT_Character_Base_Block.read() + charbase,
								0,
								BG3CNT_Display_Area_Overflow.on(),
								(byte)BG3CNT_Screen_Size.read(),
								ref3_x,
								ref3_y,
								(Int16)BG3RotScaleParDX.read(),
								(Int16)BG3RotScaleParDY.read(),
								false,
								false);
							break;

						case 2: // rot/scal 256 color bitmap
							draw_bg_mode4(
								pixels_bg3,
								BG3CNT_Display_Area_Overflow.on(),
								BG3CNT_Screen_Base_Block.read(),
								ref3_x,
								ref3_y,
								(Int16)BG3RotScaleParDX.read(),
								(Int16)BG3RotScaleParDY.read());
							break;

						case 3: // rot/scal direct color bitmap
							draw_bg_mode5(
								pixels_bg3,
								BG3CNT_Display_Area_Overflow.on(),
								BG3CNT_Screen_Base_Block.read(),
								ref3_x,
								ref3_y,
								(Int16)BG3RotScaleParDX.read(),
								(Int16)BG3RotScaleParDY.read());
							break;
						}
					}
					if (mosaic_on)
					{
						byte mosaic_h = 0;
						for (int x = 0; x < 256; x++)
						{
							if (mosaic_h != 0)
							{
								pixels_bg3[x].copy(pixels_bg3[x - mosaic_h]);
							}
							if (mosaic_h >= mosaic_bg_h) { mosaic_h = 0; }
							else mosaic_h++;
						}
					}
				}
				if (mosaik_bg3_vcnt >= mosaic_bg_v) { mosaik_bg3_vcnt = 0; }
				else mosaik_bg3_vcnt++;
			}
			else
			{
				for (int x = 0; x < 256; x++)
				{
					pixels_bg3[x].transparent = true;
				}
			}

			if (ref2_x_new == true) { ref2_x = ref2_x_next; ref2_x_new = false; }
			if (ref2_y_new == true) { ref2_y = ref2_y_next; ref2_y_new = false; }
			if (ref3_x_new == true) { ref3_x = ref3_x_next; ref3_x_new = false; }
			if (ref3_y_new == true) { ref3_y = ref3_y_next; ref3_y_new = false; }

			bool spriteon = ((layerenable & 0x10) > 0) && DISPCNT_Screen_Display_OBJ.on();
			for (int x = 0; x < 256; x++)
			{
				pixels_obj[x].transparent = true;
			}
			if (spriteon)
			{
				draw_obj(y, 0);
			}

			////////////////////////
			// merge
			////////////////////////
			///

			// check windows on
			bool anywindow = false;

			bool inwin_0y = false;
			UInt32 win0_X1 = 0;
			UInt32 win0_X2 = 0;
			if (DISPCNT_Window_0_Display_Flag.on())
			{
				anywindow = true;
				UInt32 Y1 = WIN0V_Y1.read();
				UInt32 Y2 = WIN0V_Y2.read();
				if ((Y1 <= Y2 && y >= Y1 && y < Y2) || (Y1 > Y2 && (y >= Y1 || y < Y2)))
				{
					inwin_0y = true;
					win0_X1 = WIN0H_X1.read();
					win0_X2 = WIN0H_X2.read();
				}
			}

			bool inwin_1y = false;
			UInt32 win1_X1 = 0;
			UInt32 win1_X2 = 0;
			if (DISPCNT_Window_1_Display_Flag.on())
			{
				anywindow = true;
				UInt32 Y1 = WIN1V_Y1.read();
				UInt32 Y2 = WIN1V_Y2.read();
				if ((Y1 <= Y2 && y >= Y1 && y < Y2) || (Y1 > Y2 && (y >= Y1 || y < Y2)))
				{
					inwin_1y = true;

					win1_X1 = WIN1H_X1.read();
					win1_X2 = WIN1H_X2.read();
				}
			}

			bool objwindow_on = DISPCNT_OBJ_Wnd_Display_Flag.on() && spriteon;
			anywindow |= objwindow_on;

			byte enables_wnd0 = (byte)(WININ.read() & 0x1F);
			byte enables_wnd1 = (byte)((WININ.read() >> 8) & 0x1F);
			byte enables_out = (byte)(WINOUT.read() & 0x1F);
			byte enables_obj = (byte)((WINOUT.read() >> 8) & 0x1F);

			bool inwin_0_special = WININ_Window_0_Special_Effect.on();
			bool inwin_1_special = WININ_Window_1_Special_Effect.on();
			bool obj_special = WINOUT_Objwnd_Special_Effect.on();
			bool outside_special = WINOUT_Outside_Special_Effect.on();

			byte special_effect_base = (byte)BLDCNT_Color_Special_Effect.read();
			byte first_target = (byte)(BLDCNT.read() & 0x3F);
			byte second_target = (byte)((BLDCNT.read() >> 8) & 0x3F);
			byte bldy = (byte)BLDY.read();
			byte eva = (byte)BLDALPHA_EVA_Coefficient.read();
			byte evb = (byte)BLDALPHA_EVB_Coefficient.read();

			byte masterbrightmode = MASTER_BRIGHT_Mode.read();
			byte masterbrightvalue = MASTER_BRIGHT_Factor.read();

			if (bldy > 16) { bldy = 16; }
			if (eva > 16) { eva = 16; }
			if (evb > 16) { evb = 16; }

			int step = 2;
			if (doubleres)
			{
				step = 1;
			}

			pixels_bg2 = pixels_bg2_1;
			for (byte yi = 0; yi <= 2 - step; yi++)
			{
				int yd = y;
				if (doubleres)
				{
					yd = y * 2 + yi;
					if (yi == 1 && (videomode == 1 || videomode == 2))
					{
						pixels_bg2 = pixels_bg2_2;
					}
				}
				for (int xi = 0; xi < 512; xi += step)
				{
					int x = xi / 2;
					int xd = xi / 2;
					int x2 = xi / 2;
					if (doubleres)
					{
						xd = xi;
						if (videomode == 1 || videomode == 2)
						{
							x2 = x2 = xi;
						}
					}

					// base
					byte enables = 0;
					if (!pixels_bg0[x].transparent) { enables |= 1; };
					if (!pixels_bg1[x].transparent) { enables |= 2; };
					if (!pixels_bg2[x2].transparent) { enables |= 4; };
					if (!pixels_bg3[x].transparent) { enables |= 8; };
					if (!pixels_obj[x].transparent) { enables |= 16; };

					// window select
					bool special_enable = true;
					if (anywindow)
					{
						if (inwin_0y && ((win0_X1 <= win0_X2 && x >= win0_X1 && x < win0_X2) || ((win0_X1 > win0_X2 && (x >= win0_X1 || x < win0_X2)))))
						{
							enables &= enables_wnd0;
							special_enable = inwin_0_special;
						}
						else if (inwin_1y && ((win1_X1 <= win1_X2 && x >= win1_X1 && x < win1_X2) || ((win1_X1 > win1_X2 && (x >= win1_X1 || x < win1_X2)))))
						{
							enables &= enables_wnd1;
							special_enable = inwin_1_special;
						}
						else if (pixels_obj[x].objwnd)
						{
							enables &= enables_obj;
							special_enable = obj_special;
						}
						else
						{
							enables &= enables_out;
							special_enable = outside_special;
						}
					}
					enables |= 0x20; //backdrop is always on

					// priority
					byte topprio = enables;
					if ((topprio & 0x11) == 0x11 && pixels_obj[x].prio > pixels_bg0[x].prio) topprio &= 0xF;
					if ((topprio & 0x12) == 0x12 && pixels_obj[x].prio > pixels_bg1[x].prio) topprio &= 0xF;
					if ((topprio & 0x14) == 0x14 && pixels_obj[x].prio > pixels_bg2[x2].prio) topprio &= 0xF;
					if ((topprio & 0x18) == 0x18 && pixels_obj[x].prio > pixels_bg3[x].prio) topprio &= 0xF;

					if ((topprio & 0x01) == 0x1 && (topprio & 0x02) == 0x2 && pixels_bg0[x].prio > pixels_bg1[x].prio) topprio &= 0x1E;
					if ((topprio & 0x01) == 0x1 && (topprio & 0x04) == 0x4 && pixels_bg0[x].prio > pixels_bg2[x2].prio) topprio &= 0x1E;
					if ((topprio & 0x01) == 0x1 && (topprio & 0x08) == 0x8 && pixels_bg0[x].prio > pixels_bg3[x].prio) topprio &= 0x1E;
					if ((topprio & 0x02) == 0x2 && (topprio & 0x04) == 0x4 && pixels_bg1[x].prio > pixels_bg2[x2].prio) topprio &= 0x1D;
					if ((topprio & 0x02) == 0x2 && (topprio & 0x08) == 0x8 && pixels_bg1[x].prio > pixels_bg3[x].prio) topprio &= 0x1D;
					if ((topprio & 0x04) == 0x4 && (topprio & 0x08) == 0x8 && pixels_bg2[x2].prio > pixels_bg3[x].prio) topprio &= 0x1B;

					if ((topprio & 0x10) == 0x10) { topprio = 0x10; }
					else if ((topprio & 0x01) == 0x01) { topprio = 0x01; }
					else if ((topprio & 0x02) == 0x02) { topprio = 0x02; }
					else if ((topprio & 0x04) == 0x04) { topprio = 0x04; }
					else if ((topprio & 0x08) == 0x08) { topprio = 0x08; }
					else { topprio = 0x20; }

					bool special_out = false;
					byte special_effect = special_effect_base;
					if ((special_enable && special_effect > 0) || pixels_obj[x].alpha)
					{
						// special select
						byte first = (byte)(enables & first_target);

						if (pixels_obj[x].alpha)
						{
							first = (byte)(first | 0x10);
						}

						first = (byte)(first & topprio);

						if (first != 0)
						{
							if (pixels_obj[x].alpha && first == 0x10)
							{
								special_effect = 1;
							}

							byte second;
							if (special_effect == 1)
							{
								second = (byte)(enables & (~first));

								if ((second & 0x11) == 0x11) { if (pixels_obj[x].prio > pixels_bg0[x].prio) second &= 0x2F; else second &= 0x3E; }
								if ((second & 0x12) == 0x12) { if (pixels_obj[x].prio > pixels_bg1[x].prio) second &= 0x2F; else second &= 0x3D; }
								if ((second & 0x14) == 0x14) { if (pixels_obj[x].prio > pixels_bg2[x2].prio) second &= 0x2F; else second &= 0x3B; }
								if ((second & 0x18) == 0x18) { if (pixels_obj[x].prio > pixels_bg3[x].prio) second &= 0x2F; else second &= 0x37; }

								if ((second & 0x01) == 0x1 && (second & 0x02) == 0x2) { if (pixels_bg0[x].prio > pixels_bg1[x].prio) second &= 0x3E; else second &= 0x3D; }
								if ((second & 0x01) == 0x1 && (second & 0x04) == 0x4) { if (pixels_bg0[x].prio > pixels_bg2[x2].prio) second &= 0x3E; else second &= 0x3B; }
								if ((second & 0x01) == 0x1 && (second & 0x08) == 0x8) { if (pixels_bg0[x].prio > pixels_bg3[x].prio) second &= 0x3E; else second &= 0x37; }
								if ((second & 0x02) == 0x2 && (second & 0x04) == 0x4) { if (pixels_bg1[x].prio > pixels_bg2[x2].prio) second &= 0x3D; else second &= 0x3B; }
								if ((second & 0x02) == 0x2 && (second & 0x08) == 0x8) { if (pixels_bg1[x].prio > pixels_bg3[x].prio) second &= 0x3D; else second &= 0x37; }
								if ((second & 0x04) == 0x4 && (second & 0x08) == 0x8) { if (pixels_bg2[x2].prio > pixels_bg3[x].prio) second &= 0x3B; else second &= 0x37; }

								second = (byte)(second & second_target);

								if ((first & 0x10) == 0x10) { pixelspecial.copy(pixels_obj[x]); }
								else if ((first & 0x01) == 0x01) { pixelspecial.copy(pixels_bg0[x]); }
								else if ((first & 0x02) == 0x02) { pixelspecial.copy(pixels_bg1[x]); }
								else if ((first & 0x04) == 0x04) { pixelspecial.copy(pixels_bg2[x2]); }
								else if ((first & 0x08) == 0x08) { pixelspecial.copy(pixels_bg3[x]); }
								else { pixelspecial.transparent = true; }

								if ((second & 0x10) == 0x10) { pixelalpha2.copy(pixels_obj[x]); }
								else if ((second & 0x01) == 0x01) { pixelalpha2.copy(pixels_bg0[x]); }
								else if ((second & 0x02) == 0x02) { pixelalpha2.copy(pixels_bg1[x]); }
								else if ((second & 0x04) == 0x04) { pixelalpha2.copy(pixels_bg2[x2]); }
								else if ((second & 0x08) == 0x08) { pixelalpha2.copy(pixels_bg3[x]); }
								else if ((second & 0x20) == 0x20) { pixelalpha2.copy(pixelbackdrop); }
								else { pixelalpha2.transparent = true; }

								if (!pixelspecial.transparent && !pixelalpha2.transparent)
								{
									if (pixelalpha2.prio >= pixelspecial.prio)
									{
										pixelspecial.calcalpha(pixelalpha2, eva, evb);
										special_out = true;
									}
								}
							}
							else
							{
								if ((first & 0x10) == 0x10) { pixelspecial.copycolor(pixels_obj[x]); }
								else if ((first & 0x01) == 0x01) { pixelspecial.copycolor(pixels_bg0[x]); }
								else if ((first & 0x02) == 0x02) { pixelspecial.copycolor(pixels_bg1[x]); }
								else if ((first & 0x04) == 0x04) { pixelspecial.copycolor(pixels_bg2[x2]); }
								else if ((first & 0x08) == 0x08) { pixelspecial.copycolor(pixels_bg3[x]); }
								else { pixelspecial.copycolor(pixelbackdrop); }

								if (special_effect == 2)
								{
									pixelspecial.whiter(bldy);
								}
								else
								{
									pixelspecial.blacker(bldy);
								}

								special_out = true;
							}
						}
					}

					if (special_out)
					{
						pixelfinal.copycolor(pixelspecial);
					}
					else if ((topprio & 0x10) == 0x10)
					{
						pixelfinal.copycolor(pixels_obj[x]);
					}
					else if ((topprio & 0x01) == 0x01)
					{
						pixelfinal.copycolor(pixels_bg0[x]);
					}
					else if ((topprio & 0x02) == 0x02)
					{
						pixelfinal.copycolor(pixels_bg1[x]);
					}
					else if ((topprio & 0x04) == 0x04)
					{
						pixelfinal.copycolor(pixels_bg2[x2]);
					}
					else if ((topprio & 0x08) == 0x08)
					{
						pixelfinal.copycolor(pixels_bg3[x]);
					}
					else
					{
						pixelfinal.copycolor(pixelbackdrop);
					}

					
					if (masterbrightmode == 1)
					{
						pixelfinal.whiter(masterbrightvalue);
					}
					else if (masterbrightmode == 2)
					{
						pixelfinal.blacker(masterbrightvalue);
					}
					

					// choose
					if (interlace_blending)
					{
						pixels[xd][yd].mixcolor(pixelfinal, pixels_interlace[xd][yd]);
						pixels_interlace[xd][yd].copycolor(pixelfinal);
					}
					else
					{
						pixels[xd][yd].copycolor(pixelfinal);
					}
				}
			}
		}
		else if (displaymode == 2)
		{
			uint block = DISPCNT_VRAM_block.read();
			for (int x = 0; x < 256; x++)
			{
				UInt16 color = *(UInt16*)&Memory.VRAM[block * 131072 + y * 512 + x * 2];
				pixels[x][y].color_blue = ((color >> 10) & 0x1F) << 3;
				pixels[x][y].color_green = ((color >> 5) & 0x1F) << 3;
				pixels[x][y].color_red = (color & 0x1F) << 3;
			}
		}
		else if (displaymode == 3 && !mainmemfifo.empty())
		{
			for (int x = 0; x < 256; x++)
			{
				uint color = mainmemfifo.front();
				if ((x & 1) == 1)
				{
					mainmemfifo.pop();
					color = color >> 16;
				}
				pixels[x][y].color_blue = ((color >> 10) & 0x1F) << 3;
				pixels[x][y].color_green = ((color >> 5) & 0x1F) << 3;
				pixels[x][y].color_red = (color & 0x1F) << 3;
			}
		}

		//SDL_UnlockMutex(drawlock);
	}
}

uint Gpu::get_mapped_bg_address(uint address_in)
{
	if (isGPUA)
	{
		for (int i = 0; i < 7; i++) // A..G
		{
			if (Memory.vrammux[i].MST == 1)
			{
				if (address_in >= Memory.vrammux[i].gpustart && address_in <= Memory.vrammux[i].gpuend)
				{
					return Memory.vrammux[i].vramoffset + (address_in - Memory.vrammux[i].gpustart);
				}
			}
		}
	}
	else
	{
		if (Memory.vrammux[VRAMBANK::C].MST == 4 && address_in >= Memory.vrammux[VRAMBANK::C].gpustart && address_in <= Memory.vrammux[VRAMBANK::C].gpuend) return Memory.vrammux[VRAMBANK::C].vramoffset + (address_in - Memory.vrammux[VRAMBANK::C].gpustart);
		if (Memory.vrammux[VRAMBANK::H].MST == 1 && address_in >= Memory.vrammux[VRAMBANK::H].gpustart && address_in <= Memory.vrammux[VRAMBANK::H].gpuend) return Memory.vrammux[VRAMBANK::H].vramoffset + (address_in - Memory.vrammux[VRAMBANK::H].gpustart);
		if (Memory.vrammux[VRAMBANK::I].MST == 1 && address_in >= Memory.vrammux[VRAMBANK::I].gpustart && address_in <= Memory.vrammux[VRAMBANK::I].gpuend) return Memory.vrammux[VRAMBANK::I].vramoffset + (address_in - Memory.vrammux[VRAMBANK::I].gpustart);
	}
	return 0;
}

uint Gpu::get_mapped_bg_extpalette_address(uint address_in)
{
	if (isGPUA)
	{
		if (Memory.vrammux[VRAMBANK::E].MST == 4 && address_in >= Memory.vrammux[VRAMBANK::E].gpustart && address_in <= Memory.vrammux[VRAMBANK::E].gpuend) return Memory.vrammux[VRAMBANK::E].vramoffset + (address_in - Memory.vrammux[VRAMBANK::E].gpustart);
		if (Memory.vrammux[VRAMBANK::F].MST == 4 && address_in >= Memory.vrammux[VRAMBANK::F].gpustart && address_in <= Memory.vrammux[VRAMBANK::F].gpuend) return Memory.vrammux[VRAMBANK::F].vramoffset + (address_in - Memory.vrammux[VRAMBANK::F].gpustart);
		if (Memory.vrammux[VRAMBANK::G].MST == 4 && address_in >= Memory.vrammux[VRAMBANK::G].gpustart && address_in <= Memory.vrammux[VRAMBANK::G].gpuend) return Memory.vrammux[VRAMBANK::G].vramoffset + (address_in - Memory.vrammux[VRAMBANK::G].gpustart);
	}
	else
	{
		if (Memory.vrammux[VRAMBANK::H].MST == 2 && address_in >= Memory.vrammux[VRAMBANK::H].gpustart && address_in <= Memory.vrammux[VRAMBANK::H].gpuend) return Memory.vrammux[VRAMBANK::H].vramoffset + (address_in - Memory.vrammux[VRAMBANK::H].gpustart);
	}
	return 0;
}

void Gpu::draw_bg_mode0(Pixel pixelslocal[], int engine, byte y, UInt32 mapbase, UInt32 tilebase, UInt32 Paletteoffset, bool hicolor, byte screensize, UInt16 scrollX, UInt16 scrollY)
{
	Int32 mapbaseaddr = (int)mapbase * 2048; // 2kb blocks
	Int32 tilebaseaddr = (int)tilebase * 0x4000; // 16kb blocks

	uint offset_display = 0;
	if (!isGPUA) offset_display = 0x400;

	scrollX = (UInt16)(scrollX & 0x1FF);
	scrollY = (UInt16)(scrollY & 0x1FF);

	UInt16 y_scrolled = (UInt16)(y + scrollY);
	byte tilesize = screensize;
	int offset_y = 32;
	int scroll_x_mod = 256;
	int scroll_y_mod = 256;
	switch (screensize)
	{
	case 1: scroll_x_mod = 512; break;
	case 2: scroll_y_mod = 512; break;
	case 3: scroll_x_mod = 512; scroll_y_mod = 512; break;
	}
	y_scrolled = (UInt16)(y_scrolled % scroll_y_mod);
	offset_y = ((y_scrolled % 256) / 8) * offset_y;

	int tilemult;
	int x_flip_offset;
	int x_div;
	int x_size;
	if (!hicolor)
	{
		tilemult = 32;
		x_flip_offset = 3;
		x_div = 2;
		x_size = 4;
	}
	else
	{
		tilemult = 64;
		x_flip_offset = 7;
		x_div = 1;
		x_size = 8;
	}

	for (int x = 0; x < 256; x++)
	{
		UInt16 x_scrolled = (UInt16)(x + scrollX);
		x_scrolled = (UInt16)(x_scrolled % scroll_x_mod);

		int tileindex = 0;
		if (x_scrolled >= 256 || y_scrolled >= 256 && screensize == 2)
		{
			tileindex += 1024;
			x_scrolled = (UInt16)(x_scrolled % 256);
		}
		if (y_scrolled >= 256 && screensize == 3)
		{
			tileindex += 2048;
		}
		tileindex += offset_y + (x_scrolled / 8);

		UInt16 tileinfo = *(UInt16*)&Memory.VRAM[get_mapped_bg_address(mapbaseaddr + (tileindex * 2))];

		UInt16 tilenr = (UInt16)(tileinfo & 0x3FF);
		bool horflip = ((tileinfo >> 10) & 1) == 1;
		bool verflip = ((tileinfo >> 11) & 1) == 1;
		int pixeladdr = tilebaseaddr + tilenr * tilemult;
		if (horflip)
		{
			pixeladdr += (x_flip_offset - ((x_scrolled % 8) / x_div));
		}
		else
		{
			pixeladdr += (x_scrolled % 8) / x_div;
		}
		if (verflip)
		{
			pixeladdr += (7 - (y_scrolled % 8)) * x_size;
		}
		else
		{
			pixeladdr += y_scrolled % 8 * x_size;
		}
		byte colordata = Memory.VRAM[get_mapped_bg_address(pixeladdr)];

		if (!hicolor)
		{
			if (horflip && (x_scrolled & 1) == 0 || !horflip && (x_scrolled & 1) == 1)
			{
				colordata = (byte)(colordata >> 4);
			}
			else
			{
				colordata = (byte)(colordata & 0xF);
			}

			pixelslocal[x].transparent = colordata == 0;
			if (!pixelslocal[x].transparent)
			{
				byte palette = (byte)(tileinfo >> 12);
				UInt16 colorall = *(UInt16*)&Memory.PaletteRAM[offset_display + palette * 32 + colordata * 2];
				pixelslocal[x].update((Byte)((colorall & 0x1F) * 8), (byte)(((colorall >> 5) & 0x1F) * 8), (byte)(((colorall >> 10) & 0x1F) * 8));
			}
		}
		else if (ext_palette_bg)
		{
			byte palette = (byte)(tileinfo >> 12);
			if (hicolor)
			{ 
				pixelslocal[x].transparent = (colordata & 0xFF) == 0;
			}
			else
			{
				pixelslocal[x].transparent = (colordata & 0xF) == 0;
			}
			if (!pixelslocal[x].transparent)
			{
				UInt16 colorall = *(UInt16*)&Memory.VRAM[get_mapped_bg_extpalette_address(0x2000 * (engine + Paletteoffset * 2) + palette * 512 + colordata * 2)];
				pixelslocal[x].update((Byte)((colorall & 0x1F) * 8), (byte)(((colorall >> 5) & 0x1F) * 8), (byte)(((colorall >> 10) & 0x1F) * 8));
			}
		}
		else
		{
			pixelslocal[x].transparent = colordata == 0;
			if (!pixelslocal[x].transparent)
			{
				UInt16 colorall = *(UInt16*)&Memory.PaletteRAM[offset_display + colordata * 2];
				pixelslocal[x].update((Byte)((colorall & 0x1F) * 8), (byte)(((colorall >> 5) & 0x1F) * 8), (byte)(((colorall >> 10) & 0x1F) * 8));
			}
		}
	}
}

void Gpu::draw_bg_mode2(Pixel pixelslocal[], int engine, bool tile16bit, UInt32 mapbase, UInt32 tilebase, UInt32 Paletteoffset, bool wrapping, byte screensize, Int32 refX, Int32 refY, Int16 dx, Int16 dy, bool doubleres, bool is_bg2)
{
	Int32 mapbaseaddr = (int)mapbase * 2048; // 2kb blocks
	Int32 tilebaseaddr = (int)tilebase * 0x4000; // 64kb blocks

	Int32 realX = refX;
	Int32 realY = refY;

	Int32 scroll_x_mod = 128;
	Int32 scroll_y_mod = 128;
	switch (screensize)
	{
	case 1: scroll_x_mod = 256; scroll_y_mod = 256; break;
	case 2: scroll_x_mod = 512; scroll_y_mod = 512; break;
	case 3: scroll_x_mod = 1024; scroll_y_mod = 1024; break;
	}

	int yshift = screensize + 4;

	int pixelcount = 256;
	if (doubleres)
	{
		pixelcount = 512;
	}

	for (int x = 0; x < pixelcount; x++)
	{
		bool draw = true;
		int xxx;
		int yyy;
		if (wrapping)
		{
			xxx = (realX >> 8) & (scroll_x_mod - 1);
			yyy = (realY >> 8) & (scroll_y_mod - 1);
		}
		else
		{
			xxx = (realX >> 8);
			yyy = (realY >> 8);

			if (xxx < 0 || yyy < 0 || xxx >= scroll_x_mod || yyy >= scroll_y_mod)
			{
				pixelslocal[x].transparent = true;
				draw = false;
			}
		}

		if (draw)
		{
			UInt16 tileinfo;
			bool horflip = false;
			bool verflip = false;
			byte palette = 0;
			int tileindex = (xxx >> 3) + ((yyy >> 3) << yshift);
			if (tile16bit)
			{
				tileindex <<= 1;
				int addr = max(0, min(0x17FFF, mapbaseaddr + tileindex));
			    tileinfo = *(UInt16*)&Memory.VRAM[get_mapped_bg_address(addr)]; // 10 bit tilenumber + h/v flip + 4 bit palette
				horflip = ((tileinfo >> 10) & 1) == 1;
				verflip = ((tileinfo >> 11) & 1) == 1;
				palette = (byte)(tileinfo >> 12);
				tileinfo &= 0x3FF;
			}
			else
			{
				int addr = max(0, min(0x17FFF, mapbaseaddr + tileindex));
			    tileinfo = Memory.VRAM[get_mapped_bg_address(addr)];
				horflip = false;
				verflip = false;
				palette = 0;
			}
			
			int tileX;
			int tileY;
			if (horflip)
			{
				tileX = 7 - xxx;
			}
			else
			{
				tileX = xxx;
			}
			if (verflip)
			{
				tileY = 7 - yyy;
			}
			else
			{
				tileY = yyy;
			}
			tileX &= 7;
			tileY &= 7;

			int pixeladdr = (tileinfo << 6) + (tileY * 8) + tileX;
			byte colordata = Memory.VRAM[get_mapped_bg_address(tilebaseaddr + pixeladdr)];

			UInt16 colorall = 0;
			pixelslocal[x].transparent = colordata == 0;
			if (!pixelslocal[x].transparent)
			{
				if (ext_palette_bg)
				{
					colorall = *(UInt16*)&Memory.VRAM[get_mapped_bg_extpalette_address(0x2000 * (engine + Paletteoffset * 2) + palette * 512 + colordata * 2)];
				}
				else
				{
					colorall = *(UInt16*)&Memory.PaletteRAM[colordata * 2];
				}
				pixelslocal[x].update((Byte)((colorall & 0x1F) * 8), (byte)(((colorall >> 5) & 0x1F) * 8), (byte)(((colorall >> 10) & 0x1F) * 8));
			}
			
		}
		if (doubleres)
		{
			realX = refX + (x * dx) / 2;
			realY = refY + (x * dy) / 2;
		}
		else
		{
			realX += dx;
			realY += dy;
		}
	}
}

void Gpu::draw_bg_mode4(Pixel pixelslocal[], bool wrap, UInt32 mapbase, Int32 refX, Int32 refY, Int16 dx, Int16 dy)
{
	Int32 mapbaseaddr = (int)mapbase * 0x4000; // 16kb blocks

	uint offset_display = 0;
	if (!isGPUA) offset_display = 0x400;

	int realX = refX;
	int realY = refY;
	int xxx = (realX >> 8);
	int yyy = (realY >> 8);

	if (yyy > 170)
	{
		int a = 5;
	}

	for (int x = 0; x < 256; x++)
	{
		if (wrap || xxx >= 0 && yyy >= 0 && xxx < 256 && yyy < 256)
		{
			int address = yyy * 256 + xxx;
			byte colorptr = Memory.VRAM[get_mapped_bg_address(mapbaseaddr + address)];
			UInt16 colorall = *(UInt16*)&Memory.PaletteRAM[offset_display + colorptr * 2];
			pixelslocal[x].update((Byte)((colorall & 0x1F) * 8), (byte)(((colorall >> 5) & 0x1F) * 8), (byte)(((colorall >> 10) & 0x1F) * 8));
			pixelslocal[x].transparent = colorptr == 0;
		}
		realX += dx;
		realY += dy;
		xxx = (realX >> 8);
		yyy = (realY >> 8);
	}
}

void Gpu::draw_bg_mode5(Pixel pixelslocal[], bool wrap, UInt32 mapbase, Int32 refX, Int32 refY, Int16 dx, Int16 dy)
{
	Int32 mapbaseaddr = (int)mapbase * 0x4000; // 16kb blocks

	int realX = refX;
	int realY = refY;
	int xxx = (realX >> 8);
	int yyy = (realY >> 8);

	for (int x = 0; x < 256; x++)
	{
		if (wrap || xxx >= 0 && yyy >= 0 && xxx < 256 && yyy < 256)
		{
			int address = yyy * 512 + (xxx * 2);
			UInt16 colorall = *(UInt16*)&Memory.VRAM[get_mapped_bg_address(mapbaseaddr + address)];
			pixelslocal[x].update((Byte)((colorall & 0x1F) * 8), (byte)(((colorall >> 5) & 0x1F) * 8), (byte)(((colorall >> 10) & 0x1F) * 8));
			pixelslocal[x].transparent = false;
		}
		realX += dx;
		realY += dy;
		xxx = (realX >> 8);
		yyy = (realY >> 8);
	}
}

uint Gpu::get_mapped_obj_address(uint address_in)
{
	if (isGPUA)
	{
		if (Memory.vrammux[VRAMBANK::A].MST == 2 && address_in >= Memory.vrammux[VRAMBANK::A].gpustart && address_in <= Memory.vrammux[VRAMBANK::A].gpuend) return Memory.vrammux[VRAMBANK::A].vramoffset + (address_in - Memory.vrammux[VRAMBANK::A].gpustart);
		if (Memory.vrammux[VRAMBANK::B].MST == 2 && address_in >= Memory.vrammux[VRAMBANK::B].gpustart && address_in <= Memory.vrammux[VRAMBANK::B].gpuend) return Memory.vrammux[VRAMBANK::B].vramoffset + (address_in - Memory.vrammux[VRAMBANK::B].gpustart);
		if (Memory.vrammux[VRAMBANK::E].MST == 2 && address_in >= Memory.vrammux[VRAMBANK::E].gpustart && address_in <= Memory.vrammux[VRAMBANK::E].gpuend) return Memory.vrammux[VRAMBANK::E].vramoffset + (address_in - Memory.vrammux[VRAMBANK::E].gpustart);
		if (Memory.vrammux[VRAMBANK::F].MST == 2 && address_in >= Memory.vrammux[VRAMBANK::F].gpustart && address_in <= Memory.vrammux[VRAMBANK::F].gpuend) return Memory.vrammux[VRAMBANK::F].vramoffset + (address_in - Memory.vrammux[VRAMBANK::F].gpustart);
		if (Memory.vrammux[VRAMBANK::G].MST == 2 && address_in >= Memory.vrammux[VRAMBANK::G].gpustart && address_in <= Memory.vrammux[VRAMBANK::G].gpuend) return Memory.vrammux[VRAMBANK::G].vramoffset + (address_in - Memory.vrammux[VRAMBANK::G].gpustart);
	}
	else
	{
		if (Memory.vrammux[VRAMBANK::D].MST == 4 && address_in >= Memory.vrammux[VRAMBANK::D].gpustart && address_in <= Memory.vrammux[VRAMBANK::D].gpuend) return Memory.vrammux[VRAMBANK::D].vramoffset + (address_in - Memory.vrammux[VRAMBANK::D].gpustart);
		if (Memory.vrammux[VRAMBANK::I].MST == 2 && address_in >= Memory.vrammux[VRAMBANK::I].gpustart && address_in <= Memory.vrammux[VRAMBANK::I].gpuend) return Memory.vrammux[VRAMBANK::I].vramoffset + (address_in - Memory.vrammux[VRAMBANK::I].gpustart);
	}
	return 0;
}

uint Gpu::get_mapped_obj_extpalette_address(uint address_in)
{
	if (isGPUA)
	{
		if (Memory.vrammux[VRAMBANK::F].MST == 5 && address_in >= Memory.vrammux[VRAMBANK::F].gpustart && address_in <= Memory.vrammux[VRAMBANK::F].gpuend) return Memory.vrammux[VRAMBANK::F].vramoffset + (address_in - Memory.vrammux[VRAMBANK::F].gpustart);
		if (Memory.vrammux[VRAMBANK::G].MST == 5 && address_in >= Memory.vrammux[VRAMBANK::G].gpustart && address_in <= Memory.vrammux[VRAMBANK::G].gpuend) return Memory.vrammux[VRAMBANK::G].vramoffset + (address_in - Memory.vrammux[VRAMBANK::G].gpustart);
	}
	else
	{
		if (Memory.vrammux[VRAMBANK::I].MST == 3 && address_in >= Memory.vrammux[VRAMBANK::I].gpustart && address_in <= Memory.vrammux[VRAMBANK::I].gpuend) return Memory.vrammux[VRAMBANK::I].vramoffset + (address_in - Memory.vrammux[VRAMBANK::I].gpustart);
	}
	return 0;
}

void Gpu::draw_obj(int y, int baseaddr)
{
	for (int x = 0; x < 256; x++)
	{
		pixels_obj[x].undrawn = true;
		pixels_obj[x].objwnd = false;
		pixels_obj[x].alpha = false;
	}

	uint offset_display = 0;
	if (!isGPUA) offset_display = 0x400;

	byte mosaic_h = (byte)MOSAIC_OBJ_Mosaic_H_Size.read();
	byte mosaic_v = (byte)MOSAIC_OBJ_Mosaic_V_Size.read();

	bool one_dim_mapping = DISPCNT_Tile_OBJ_Mapping.on();
	byte Tile_OBJ_1D_Boundary = (byte)DISPCNT_Tile_OBJ_1D_Boundary.read();
	bool bitmap_OBJ_2D_Dim = DISPCNT_Bitmap_OBJ_2D_Dim.on();
	bool bitmap_OBJ_Mapping = DISPCNT_Bitmap_OBJ_Mapping.on();
	bool bitmap_OBJ_1D_Boundary = DISPCNT_Bitmap_OBJ_1D_Boundary.on();

	int cycles = 0;
	int pixellimit = 2130;
	//if (DISPCNT_H_Blank_IntervalFree.on())
	//{
	//	pixellimit = 954;
	//}

	for (int i = 0; i < 128; i++)
	{
		UInt16 Atr0 = *(UInt16*)&Memory.OAMRAM[offset_display + i * 8];
		if (((Atr0 >> 8) & 1) == 1 || ((Atr0 >> 9) & 1) == 0) // rot/scale or disable
		{
			UInt16 Atr1 = *(UInt16*)&Memory.OAMRAM[offset_display + i * 8 + 2];
			Int16 posY = (Int16)(Atr0 & 0xFF);
			if (posY > 0xC0) { posY = (Int16)(posY - 0x100); }
			bool affine = ((Atr0 >> 8) & 1) == 1;

			UInt16 objshape = (UInt16)((Atr0 >> 14) & 0x3);
			UInt16 objsize = (UInt16)((Atr1 >> 14) & 0x3);

			byte sizeX = 0;
			byte sizeY = 0;

			switch (objshape)
			{
			case 0: // square
				switch (objsize)
				{
				case 0: sizeX = 8; sizeY = 8; break;
				case 1: sizeX = 16; sizeY = 16; break;
				case 2: sizeX = 32; sizeY = 32; break;
				case 3: sizeX = 64; sizeY = 64; break;
				}
				break;
			case 1: // hor
				switch (objsize)
				{
				case 0: sizeX = 16; sizeY = 8; break;
				case 1: sizeX = 32; sizeY = 8; break;
				case 2: sizeX = 32; sizeY = 16; break;
				case 3: sizeX = 64; sizeY = 32; break;
				}
				break;
			case 2: // vert
				switch (objsize)
				{
				case 0: sizeX = 8; sizeY = 16; break;
				case 1: sizeX = 8; sizeY = 32; break;
				case 2: sizeX = 16; sizeY = 32; break;
				case 3: sizeX = 32; sizeY = 64; break;
				}
				break;
			}

			int fieldX = sizeX;
			int fieldY = sizeY;

			if (((Atr0 >> 8) & 3) == 3)
			{
				fieldX *= 2;
				fieldY *= 2;
			}

			int ty = y - posY;

			bool mosaic_on = ((Atr0 >> 12) & 1) == 1;
			if (mosaic_on)
			{
				ty -= (ty % (mosaic_v + 1));
			}

			if (ty >= 0 && ty < fieldY)
			{
				Int16 posX = (Int16)(Atr1 & 0x1FF);
				if (posX > 0x100) { posX = (Int16)(posX - 0x200); }
				UInt16 Atr2 = *(UInt16*)&Memory.OAMRAM[offset_display + i * 8 + 4];

				int tileindex = Atr2 & 0x3FF;

				bool horflip = ((Atr1 >> 12) & 1) == 1;
				bool verflip = ((Atr1 >> 13) & 1) == 1;
				byte prio = (byte)((Atr2 >> 10) & 3);

				bool hicolor = ((Atr0 >> 13) & 1) == 1;

				if (hicolor && !one_dim_mapping)
				{
					tileindex = tileindex & 0x3FE;
				}

				int pixeladdr = baseaddr + tileindex * 32;
				int tilemult;
				int x_flip_offset;
				int y_flip_offset;
				int x_size;
				int x_div;
				if (!hicolor)
				{
					tilemult = 32;
					x_flip_offset = 3;
					y_flip_offset = 28;
					x_div = 2;
					x_size = 4;
				}
				else
				{
					tilemult = 64;
					x_flip_offset = 7;
					y_flip_offset = 56;
					x_div = 1;
					x_size = 8;
				}

				Int16 dx = 0;
				Int16 dmx;
				Int16 dy = 0;
				Int16 dmy;
				int realX = 0;
				int realY = 0;
				bool bitmap_mode = ((Atr0 >> 10) & 3) == 3;
				if (bitmap_mode)
				{
					if (bitmap_OBJ_Mapping)
					{
						if (bitmap_OBJ_1D_Boundary)
						{
							pixeladdr = tileindex * 256;
						}
						else
						{
							pixeladdr = tileindex * 128;
						}
					}
					else
					{
						if (bitmap_OBJ_2D_Dim)
						{
							pixeladdr = (tileindex & 0x3E0) * 128 + (tileindex & 0x01F) * 16;
						}
						else
						{
							pixeladdr = (tileindex & 0x3F0) * 128 + (tileindex & 0x00F) * 16;
						}
					}
				}
				else if (one_dim_mapping && Tile_OBJ_1D_Boundary > 0)
				{
					switch (Tile_OBJ_1D_Boundary)
					{
					case 1: pixeladdr = tileindex * 64; break;
					case 2: pixeladdr = tileindex * 128; break;
					case 3: pixeladdr = tileindex * 256; break;
					}
				}

				if (affine)
				{
					cycles += 10;
					horflip = false;
					verflip = false;
					byte rotparpos = (byte)((Atr1 >> 9) & 0x1F);
					dx = *(UInt16*)&Memory.OAMRAM[offset_display + rotparpos * 32 + 6];
					dmx = *(UInt16*)&Memory.OAMRAM[offset_display + rotparpos * 32 + 14];
					dy = *(UInt16*)&Memory.OAMRAM[offset_display + rotparpos * 32 + 22];
					dmy = *(UInt16*)&Memory.OAMRAM[offset_display + rotparpos * 32 + 30];
					realX = ((sizeX) << 7) - (fieldX >> 1)* dx - (fieldY >> 1)* dmx + ty * dmx;
					realY = ((sizeY) << 7) - (fieldX >> 1)* dy - (fieldY >> 1)* dmy + ty * dmy;
				}
				else if (!bitmap_mode)
				{
					if (verflip)
					{
						if (one_dim_mapping)
						{
							pixeladdr += (y_flip_offset - (ty % 8) * x_size);
							pixeladdr += (((sizeY / 8) - 1) - (ty / 8)) * (sizeX * x_size);
						}
						else
						{
							pixeladdr += (y_flip_offset - (ty % 8) * x_size);
							pixeladdr += (((sizeY / 8) - 1) - (ty / 8)) * 1024;
						}
					}
					else
					{
						if (one_dim_mapping)
						{
							pixeladdr += (ty % 8) * x_size;
							pixeladdr += (ty / 8) * (sizeX * x_size);
						}
						else
						{
							pixeladdr += (ty % 8) * x_size;
							pixeladdr += (ty / 8) * 1024;
						}
					}
				}

				byte mosaik_h_cnt = 0;
				for (UInt16 x = 0; x < fieldX; x++)
				{
					if ((affine && cycles + x * 2 >= pixellimit) || (!affine && cycles + x >= pixellimit))
					{
						return;
					}

					int target = x + posX;
					bool second_pix = false;
					if (target > 255) { break; }
					if (target >= 0)
					{
						if (mosaic_on && mosaik_h_cnt > 0 && (target - mosaik_h_cnt) >= 0)
						{
							pixels_obj[target].copy(pixels_obj[target - mosaik_h_cnt]);
						}
						else
						{
							int pixeladdr_X = -1;
							if (bitmap_mode)
							{
								int xxx; 
								int yyy; 
								if (affine)
								{
									xxx = realX >> 8;
									yyy = realY >> 8;
								}
								else
								{
									xxx = x;
									yyy = ty;
								}
								if (xxx >= 0 && xxx < sizeX && yyy >= 0 && yyy < sizeY)
								{
									pixeladdr_X = pixeladdr;
									if (bitmap_OBJ_2D_Dim)
									{
										if (bitmap_OBJ_2D_Dim)
										{
											pixeladdr_X += yyy * 512;
										}
										else
										{
											pixeladdr_X += yyy * 256;
										}
										pixeladdr_X += xxx * 2;
									}
									else
									{
										pixeladdr_X += (yyy * sizeX + xxx) * 2;
									}
								}
							}
							else if (affine)
							{
								int xxx = realX >> 8;
								int yyy = realY >> 8;
								if (xxx >= 0 && xxx < sizeX && yyy >= 0 && yyy < sizeY)
								{
									second_pix = (xxx & 1) == 1;
									pixeladdr_X = pixeladdr;
									if (one_dim_mapping)
									{
										pixeladdr_X += (yyy % 8) * x_size;
										pixeladdr_X += (yyy / 8) * (sizeX * x_size);
									}
									else
									{
										pixeladdr_X += (yyy % 8) * x_size;
										pixeladdr_X += (yyy / 8) * 1024;
									}
									pixeladdr_X += (xxx % 8) / x_div;
									pixeladdr_X += (xxx / 8) * tilemult;
								}
							}
							else
							{
								pixeladdr_X = pixeladdr;
								if (horflip)
								{
									pixeladdr_X += x_flip_offset - ((x % 8) / x_div);
									pixeladdr_X -= ((x / 8) - ((sizeX / 8) - 1)) * tilemult;
								}
								else
								{
									pixeladdr_X += (x % 8) / x_div;
									pixeladdr_X += (x / 8) * tilemult;
								}
							}

							if (pixeladdr_X >= 0)
							{
								bool transparent;
								byte colordata;
								UInt16 colorall;
								if (bitmap_mode)
								{
									colorall = *(UInt16*)&Memory.VRAM[get_mapped_obj_address(pixeladdr_X)];
									transparent = false; // ((colorall >> 15) & 1) == 0;
								}
								else
								{
								    colordata = Memory.VRAM[get_mapped_obj_address(pixeladdr_X)];
									if (!hicolor)
									{
										if (affine)
										{
											if (second_pix)
											{
												colordata = (byte)(colordata >> 4);
											}
											else
											{
												colordata = (byte)(colordata & 0xF);
											}
										}
										else
										{
											if (horflip && (x & 1) == 0 || !horflip && (x & 1) == 1)
											{
												colordata = (byte)(colordata >> 4);
											}
											else
											{
												colordata = (byte)(colordata & 0xF);
											}
										}
									}

									transparent = colordata == 0;
								}

								bool objwnd = ((Atr0 >> 10) & 3) == 2;
								if (!transparent)
								{
									pixels_obj[target].objwnd |= objwnd;
								}
								if (!objwnd)
								{
									if (pixels_obj[target].undrawn || pixels_obj[target].transparent || prio < pixels_obj[target].prio)
									{
										if (!bitmap_mode)
										{
											if (!hicolor)
											{
												byte palette = (byte)(Atr2 >> 12);
												colorall = *(UInt16*)&Memory.PaletteRAM[offset_display + 512 + palette * 32 + colordata * 2];
											}
											else if (ext_palette_obj)
											{
												byte palette = (byte)(Atr2 >> 12);
												colorall = *(UInt16*)&Memory.VRAM[get_mapped_obj_extpalette_address(palette * 512 + colordata * 2)];
											}
											else
											{
												colorall = *(UInt16*)&Memory.PaletteRAM[offset_display + 512 + colordata * 2];
											}
										}

										if (!transparent)
										{
											pixels_obj[target].update((Byte)((colorall & 0x1F) * 8), (byte)(((colorall >> 5) & 0x1F) * 8), (byte)(((colorall >> 10) & 0x1F) * 8));
											pixels_obj[target].transparent = transparent;
											pixels_obj[target].undrawn = false;
										}
										pixels_obj[target].prio = prio;
										pixels_obj[target].alpha = ((Atr0 >> 10) & 3) == 1;
									}
								}
							}
						}
					}
					realX += dx;
					realY += dy;
					if (mosaik_h_cnt >= mosaic_h) { mosaik_h_cnt = 0; }
					else mosaik_h_cnt++;
				}

				if (affine)
				{
					cycles += fieldX * 2;
				}
				else
				{
					cycles += fieldX;
				}

			}
		}
	}


}

int Gpu::get_mapped_rearplane_address(uint address_in)
{
	if (Memory.vrammux[VRAMBANK::A].MST == 3 && address_in >= Memory.vrammux[VRAMBANK::A].gpustart && address_in <= Memory.vrammux[VRAMBANK::A].gpuend) return Memory.vrammux[VRAMBANK::A].vramoffset + (address_in - Memory.vrammux[VRAMBANK::A].gpustart);
	if (Memory.vrammux[VRAMBANK::B].MST == 3 && address_in >= Memory.vrammux[VRAMBANK::B].gpustart && address_in <= Memory.vrammux[VRAMBANK::B].gpuend) return Memory.vrammux[VRAMBANK::B].vramoffset + (address_in - Memory.vrammux[VRAMBANK::B].gpustart);
	if (Memory.vrammux[VRAMBANK::C].MST == 3 && address_in >= Memory.vrammux[VRAMBANK::C].gpustart && address_in <= Memory.vrammux[VRAMBANK::C].gpuend) return Memory.vrammux[VRAMBANK::C].vramoffset + (address_in - Memory.vrammux[VRAMBANK::C].gpustart);
	if (Memory.vrammux[VRAMBANK::D].MST == 3 && address_in >= Memory.vrammux[VRAMBANK::D].gpustart && address_in <= Memory.vrammux[VRAMBANK::D].gpuend) return Memory.vrammux[VRAMBANK::D].vramoffset + (address_in - Memory.vrammux[VRAMBANK::D].gpustart);

	return -1;
}

void Gpu::draw_3D(int y)
{
	if (Regs_Arm9.Sect_display9.DISP3DCNT_Rear_Plane_Mode.on()) // bitmap
	{
		for (int x = 0; x < 256; x++)
		{
			int address = get_mapped_rearplane_address(0x40000 + y * 512 + x * 2);
			UInt16 color;
			if (address >= 0)
			{
				color = *(UInt16*)&Memory.VRAM[address];
			}
			else
			{
				color = 0;
			}
			pixels_bg0[x].color_blue = ((color >> 10) & 0x1F) << 3;
			pixels_bg0[x].color_green = ((color >> 5) & 0x1F) << 3;
			pixels_bg0[x].color_red = (color & 0x1F) << 3;
			pixels_bg0[x].transparent = ((color >> 15) & 1) == 0;
		}
	}
	else // blank color
	{
		byte red = Regs_Arm9.Sect_3D9.CLEAR_COLOR_Red.read() * 8;
		byte green = Regs_Arm9.Sect_3D9.CLEAR_COLOR_Green.read() * 8;
		byte blue = Regs_Arm9.Sect_3D9.CLEAR_COLOR_Blue.read() * 8;
		byte alpha = Regs_Arm9.Sect_3D9.CLEAR_COLOR_Alpha.read();

		for (int x = 0; x < 256; x++)
		{
			pixels_bg0[x].transparent = alpha == 0;
			pixels_bg0[x].update(red, green, blue);
		}
	}
}

void Gpu::draw_game(uint* framebuffer_raw)
{
	//if (SDL_LockMutex(drawlock) == 0)
	{
		//if (doubleres)
		//{
		//	if (temp_bmp.Width == 480)
		//	{
		//		for (int y = 0; y < 320; y++)
		//		{
		//			for (int x = 0; x < 480; x++)
		//			{
		//				ptr[(x * 3) + y * stride] = pixels[x, y].color_blue;
		//				ptr[(x * 3) + y * stride + 1] = pixels[x, y].color_green;
		//				ptr[(x * 3) + y * stride + 2] = pixels[x, y].color_red;
		//			}
		//		}
		//	}
		//}
		//else
		{
			int addr = 0;
			for (int y = 0; y < 192; y++)
			{
				for (int x = 0; x < 256; x++)
				{
					unsigned int color = (pixels[x][y].color_red << 16) | (pixels[x][y].color_green << 8) | pixels[x][y].color_blue;
					framebuffer_raw[addr] = color;
					addr++;
				}
			}
		}
		//SDL_UnlockMutex(drawlock);
	}
}

/*
void Gpu::GetPointBounds(PointF[] points, out float xmin, out float xmax, out float ymin, out float ymax)
{
	xmin = points[0].X;
	xmax = xmin;
	ymin = points[0].Y;
	ymax = ymin;
	foreach(PointF point in points)
	{
		if (xmin > point.X) xmin = point.X;
		if (xmax < point.X) xmax = point.X;
		if (ymin > point.Y) ymin = point.Y;
		if (ymax < point.Y) ymax = point.Y;
	}
}
*/