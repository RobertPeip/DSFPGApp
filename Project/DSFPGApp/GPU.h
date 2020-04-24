#pragma once
#include "SDL.h"
#include "types.h"
#include "DSReg.h"
#include <queue>

class Pixel
{
public:
	Byte color_red;
	Byte color_green;
	Byte color_blue;
	bool transparent;
	byte prio;
	bool undrawn;
	bool objwnd;
	bool alpha;

	void update(Byte color_red, Byte color_green, Byte color_blue);
	void copy(Pixel source);
	void copycolor(Pixel source);
	void mixcolor(Pixel source, Pixel secondpixel);
	void calcalpha(Pixel secondpixel, byte eva, byte evb);
	void whiter(byte change);
	void blacker(byte change);
};

enum WINDOWSTATE
{
	Init,
	Win0,
	Win1,
	Obj,
	Out
};

class Gpu
{
public:
	bool isGPUA;
	bool disabled = false;
	bool swap;
	byte layerenable;

	bool lockSpeed = true;
	int speedmult = 1;
	int frameskip = 0;
	int frameskip_counter = 0;
	bool interlace_blending = false;
	bool colorshader = false;
	bool doubleres = false;
	bool even_frame;

	SDL_mutex* drawlock;

	UInt64 intern_frames;
	UInt64 videomode_frames;
	bool framebuffer_select;

	// registers
	byte videomode;
	byte displaymode;
	bool forcedblank;
	bool ext_palette_bg;
	bool ext_palette_obj;
	uint screenbase;
	uint charbase;
	bool is3D;

	// static array, so less allocate
	Pixel pixels[512][384];
	Pixel pixels_interlace[512][384];

	Pixel pixels_bg0[256];
	Pixel pixels_bg1[256];
	Pixel* pixels_bg2;
	Pixel pixels_bg2_1[512];
	Pixel pixels_bg2_2[512];
	Pixel pixels_bg3[256];
	Pixel pixels_obj[256];
	Pixel pixelbackdrop;
	Pixel pixelspecial;
	Pixel pixelalpha2;
	Pixel pixelfinal;

	Uint64 lastTime_frame;

	// on delay
	bool on_delay_bg0[3];
	bool on_delay_bg1[3];
	bool on_delay_bg2[3];
	bool on_delay_bg3[3];

	// affine bg
	Int32 ref2_x;
	Int32 ref2_y;
	Int32 ref3_x;
	Int32 ref3_y;

	Int32 ref2_x_next;
	Int32 ref2_y_next;
	bool ref2_x_new;
	bool ref2_y_new;
	Int32 ref3_x_next;
	Int32 ref3_y_next;
	bool ref3_x_new;
	bool ref3_y_new;

	// mosaic
	byte mosaik_bg0_vcnt;
	byte mosaik_bg1_vcnt;
	byte mosaik_bg2_vcnt;
	byte mosaik_bg3_vcnt;

	std::queue<uint> mainmemfifo;

	// frametime
	const long FRAMETIME = (1000000 / 60);
	long frametimeleft;

	// regs
	DSReg DISPCNT_BG_Mode;
	DSReg DISPCNT_BG0_2D_3D;
	DSReg DISPCNT_Tile_OBJ_Mapping;
	DSReg DISPCNT_Bitmap_OBJ_2D_Dim;
	DSReg DISPCNT_Bitmap_OBJ_Mapping;
	DSReg DISPCNT_Forced_Blank;
	DSReg DISPCNT_Screen_Display_BG0;
	DSReg DISPCNT_Screen_Display_BG1;
	DSReg DISPCNT_Screen_Display_BG2;
	DSReg DISPCNT_Screen_Display_BG3;
	DSReg DISPCNT_Screen_Display_OBJ;
	DSReg DISPCNT_Window_0_Display_Flag;
	DSReg DISPCNT_Window_1_Display_Flag;
	DSReg DISPCNT_OBJ_Wnd_Display_Flag;
	DSReg DISPCNT_Display_Mode;
	DSReg DISPCNT_VRAM_block;
	DSReg DISPCNT_Tile_OBJ_1D_Boundary;
	DSReg DISPCNT_Bitmap_OBJ_1D_Boundary;
	DSReg DISPCNT_OBJ_Process_H_Blank;
	DSReg DISPCNT_Character_Base;
	DSReg DISPCNT_Screen_Base;
	DSReg DISPCNT_BG_Extended_Palettes;
	DSReg DISPCNT_OBJ_Extended_Palettes;

	DSReg BG0CNT_BG_Priority;
	DSReg BG0CNT_Character_Base_Block;
	DSReg BG0CNT_Mosaic;
	DSReg BG0CNT_Colors_Palettes;
	DSReg BG0CNT_Screen_Base_Block;
	DSReg BG0CNT_Ext_Palette_Slot;
	DSReg BG0CNT_Screen_Size;

	DSReg BG1CNT_BG_Priority;
	DSReg BG1CNT_Character_Base_Block;
	DSReg BG1CNT_Mosaic;
	DSReg BG1CNT_Colors_Palettes;
	DSReg BG1CNT_Screen_Base_Block;
	DSReg BG1CNT_Ext_Palette_Slot;
	DSReg BG1CNT_Screen_Size;

	DSReg BG2CNT_BG_Priority;
	DSReg BG2CNT_Character_Base_Block;
	DSReg BG2CNT_Mosaic;
	DSReg BG2CNT_Colors_Palettes;
	DSReg BG2CNT_Screen_Base_Block;
	DSReg BG2CNT_Display_Area_Overflow;
	DSReg BG2CNT_Screen_Size;

	DSReg BG3CNT_BG_Priority;
	DSReg BG3CNT_Character_Base_Block;
	DSReg BG3CNT_Mosaic;
	DSReg BG3CNT_Colors_Palettes;
	DSReg BG3CNT_Screen_Base_Block;
	DSReg BG3CNT_Display_Area_Overflow;
	DSReg BG3CNT_Screen_Size;

	DSReg BG0HOFS;
	DSReg BG0VOFS;
	DSReg BG1HOFS;
	DSReg BG1VOFS;
	DSReg BG2HOFS;
	DSReg BG2VOFS;
	DSReg BG3HOFS;
	DSReg BG3VOFS;

	DSReg BG2RotScaleParDX;
	DSReg BG2RotScaleParDMX;
	DSReg BG2RotScaleParDY;
	DSReg BG2RotScaleParDMY;
	DSReg BG2RefX;
	DSReg BG2RefY;

	DSReg BG3RotScaleParDX;
	DSReg BG3RotScaleParDMX;
	DSReg BG3RotScaleParDY;
	DSReg BG3RotScaleParDMY;
	DSReg BG3RefX;
	DSReg BG3RefY;

	DSReg WIN0H_X2;
	DSReg WIN0H_X1;

	DSReg WIN1H_X2;
	DSReg WIN1H_X1;

	DSReg WIN0V_Y2;
	DSReg WIN0V_Y1;

	DSReg WIN1V_Y2;
	DSReg WIN1V_Y1;

	DSReg WININ;
	DSReg WININ_Window_0_BG0_Enable;
	DSReg WININ_Window_0_BG1_Enable;
	DSReg WININ_Window_0_BG2_Enable;
	DSReg WININ_Window_0_BG3_Enable;
	DSReg WININ_Window_0_OBJ_Enable;
	DSReg WININ_Window_0_Special_Effect;
	DSReg WININ_Window_1_BG0_Enable;
	DSReg WININ_Window_1_BG1_Enable;
	DSReg WININ_Window_1_BG2_Enable;
	DSReg WININ_Window_1_BG3_Enable;
	DSReg WININ_Window_1_OBJ_Enable;
	DSReg WININ_Window_1_Special_Effect;

	DSReg WINOUT;
	DSReg WINOUT_Outside_BG0_Enable;
	DSReg WINOUT_Outside_BG1_Enable;
	DSReg WINOUT_Outside_BG2_Enable;
	DSReg WINOUT_Outside_BG3_Enable;
	DSReg WINOUT_Outside_OBJ_Enable;
	DSReg WINOUT_Outside_Special_Effect;
	DSReg WINOUT_Objwnd_BG0_Enable;
	DSReg WINOUT_Objwnd_BG1_Enable;
	DSReg WINOUT_Objwnd_BG2_Enable;
	DSReg WINOUT_Objwnd_BG3_Enable;
	DSReg WINOUT_Objwnd_OBJ_Enable;
	DSReg WINOUT_Objwnd_Special_Effect;

	DSReg MOSAIC_BG_Mosaic_H_Size;
	DSReg MOSAIC_BG_Mosaic_V_Size;
	DSReg MOSAIC_OBJ_Mosaic_H_Size;
	DSReg MOSAIC_OBJ_Mosaic_V_Size;

	DSReg BLDCNT;
	DSReg BLDCNT_BG0_1st_Target_Pixel;
	DSReg BLDCNT_BG1_1st_Target_Pixel;
	DSReg BLDCNT_BG2_1st_Target_Pixel;
	DSReg BLDCNT_BG3_1st_Target_Pixel;
	DSReg BLDCNT_OBJ_1st_Target_Pixel;
	DSReg BLDCNT_BD_1st_Target_Pixel;
	DSReg BLDCNT_Color_Special_Effect;
	DSReg BLDCNT_BG0_2nd_Target_Pixel;
	DSReg BLDCNT_BG1_2nd_Target_Pixel;
	DSReg BLDCNT_BG2_2nd_Target_Pixel;
	DSReg BLDCNT_BG3_2nd_Target_Pixel;
	DSReg BLDCNT_OBJ_2nd_Target_Pixel;
	DSReg BLDCNT_BD_2nd_Target_Pixel;

	DSReg BLDALPHA_EVA_Coefficient;
	DSReg BLDALPHA_EVB_Coefficient;

	DSReg BLDY;

	DSReg MASTER_BRIGHT_Factor;
	DSReg MASTER_BRIGHT_Mode;

	void reset(bool isGPUA);
	void dispcnt_write();
	void refpoint_update_all();
	void refpoint_update_2x();
	void refpoint_update_2y();
	void refpoint_update_3x();
	void refpoint_update_3y();
	void refpoint_update_2x_new();
	void refpoint_update_2y_new();
	void refpoint_update_3x_new();
	void refpoint_update_3y_new();
	void once_per_hblank();
	void next_line(byte line);
	void draw_line(byte y_in);
	uint get_mapped_bg_address(uint address_in);
	uint get_mapped_bg_extpalette_address(uint address_in);
	void draw_bg_mode0(Pixel pixelslocal[], int engine, byte y, UInt32 mapbase, UInt32 Paletteoffset, UInt32 tilebase, bool hicolor, byte screensize, UInt16 scrollX, UInt16 scrollY);
	void draw_bg_mode2(Pixel pixelslocal[], int engine, bool tile16bit, UInt32 mapbase, UInt32 Paletteoffset, UInt32 tilebase, bool wrapping, byte screensize, Int32 refX, Int32 refY, Int16 dx, Int16 dy, bool doubleres, bool is_bg2);
	void draw_bg_mode4(Pixel pixelslocal[], bool wrap, UInt32 mapbase, Int32 refX, Int32 refY, Int16 dx, Int16 dy);
	void draw_bg_mode5(Pixel pixelslocal[], bool wrap, UInt32 mapbase, Int32 refX, Int32 refY, Int16 dx, Int16 dy);
	uint get_mapped_obj_address(uint address_in);
	uint get_mapped_obj_extpalette_address(uint address_in);
	void draw_obj(int y, int baseaddr);
	int get_mapped_rearplane_address(uint address_in);
	void draw_3D(int y);
	void draw_game(uint* framebuffer_raw);

	//private:
		//void GetPointBounds(PointF[] points, out float xmin, out float xmax, out float ymin, out float ymax)
};
extern Gpu GPU_A;
extern Gpu GPU_B;