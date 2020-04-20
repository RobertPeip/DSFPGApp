library IEEE;
use IEEE.std_logic_1164.all;  
use IEEE.numeric_std.all;     

use work.pProc_bus_gb.all;
use work.pRegmap.all;

package pReg_ds_display_9 is

   -- range 0x0000 .. 0x006C + 0x1000 .. 0x106C
   --   (                                                      adr      upper    lower    size   default   accesstype)                                                     
   constant A_DISPCNT                        : regmap_type := (16#0000#,  15,      0,        1,        0,   readwrite); -- LCD Control                                   2    R/W   
   constant A_DISPCNT_BG_Mode                : regmap_type := (16#0000#,   2,      0,        1,        0,   readwrite); -- BG Mode                     (0-5=Video Mode 0-6, 7=Prohibited)
   constant A_DISPCNT_BG0_2D_3D              : regmap_type := (16#0000#,   3,      3,        1,        0,   readwrite); -- A only BG0 2D/3D Selection (instead CGB Mode) (0=2D, 1=3D)
   constant A_DISPCNT_Tile_OBJ_Mapping       : regmap_type := (16#0000#,   4,      4,        1,        0,   readwrite); -- Tile OBJ Mapping        (0=2D; max 32KB, 1=1D; max 32KB..256KB)
   constant A_DISPCNT_Bitmap_OBJ_2D_Dim      : regmap_type := (16#0000#,   5,      5,        1,        0,   readwrite); -- Bitmap OBJ 2D-Dimension (0=128x512 dots, 1=256x256 dots)
   constant A_DISPCNT_Bitmap_OBJ_Mapping     : regmap_type := (16#0000#,   6,      6,        1,        0,   readwrite); -- Bitmap OBJ Mapping      (0=2D; max 128KB, 1=1D; max 128KB..256KB)
   constant A_DISPCNT_Forced_Blank           : regmap_type := (16#0000#,   7,      7,        1,        0,   readwrite); -- Forced Blank                (1=Allow FAST access to VRAM,Palette,OAM)
   constant A_DISPCNT_Screen_Display_BG0     : regmap_type := (16#0000#,   8,      8,        1,        0,   readwrite); -- Screen Display BG0          (0=Off, 1=On)
   constant A_DISPCNT_Screen_Display_BG1     : regmap_type := (16#0000#,   9,      9,        1,        0,   readwrite); -- Screen Display BG1          (0=Off, 1=On)
   constant A_DISPCNT_Screen_Display_BG2     : regmap_type := (16#0000#,  10,     10,        1,        0,   readwrite); -- Screen Display BG2          (0=Off, 1=On)
   constant A_DISPCNT_Screen_Display_BG3     : regmap_type := (16#0000#,  11,     11,        1,        0,   readwrite); -- Screen Display BG3          (0=Off, 1=On)
   constant A_DISPCNT_Screen_Display_OBJ     : regmap_type := (16#0000#,  12,     12,        1,        0,   readwrite); -- Screen Display OBJ          (0=Off, 1=On)
   constant A_DISPCNT_Window_0_Display_Flag  : regmap_type := (16#0000#,  13,     13,        1,        0,   readwrite); -- Window 0 Display Flag       (0=Off, 1=On)
   constant A_DISPCNT_Window_1_Display_Flag  : regmap_type := (16#0000#,  14,     14,        1,        0,   readwrite); -- Window 1 Display Flag       (0=Off, 1=On)
   constant A_DISPCNT_OBJ_Wnd_Display_Flag   : regmap_type := (16#0000#,  15,     15,        1,        0,   readwrite); -- OBJ Window Display Flag     (0=Off, 1=On)                                       
   constant A_DISPCNT_Display_Mode           : regmap_type := (16#0000#,  17,     16,        1,        0,   readwrite); -- 16-17 A+B   Display Mode (Engine A: 0..3, Engine B: 0..1, GBA: Green Swap)
   constant A_DISPCNT_VRAM_block             : regmap_type := (16#0000#,  19,     18,        1,        0,   readwrite); -- 18-19 A     VRAM block (0..3=VRAM A..D) (For Capture & above Display Mode=2)
   constant A_DISPCNT_Tile_OBJ_1D_Boundary   : regmap_type := (16#0000#,  21,     20,        1,        0,   readwrite); -- 20-21 A+B   Tile OBJ 1D-Boundary   (see Bit4)
   constant A_DISPCNT_Bitmap_OBJ_1D_Boundary : regmap_type := (16#0000#,  22,     22,        1,        0,   readwrite); -- 22    A     Bitmap OBJ 1D-Boundary (see Bit5-6)
   constant A_DISPCNT_OBJ_Process_H_Blank    : regmap_type := (16#0000#,  23,     23,        1,        0,   readwrite); -- 23    A+B   OBJ Processing during H-Blank (was located in Bit5 on GBA)
   constant A_DISPCNT_Character_Base         : regmap_type := (16#0000#,  26,     24,        1,        0,   readwrite); -- 24-26 A     Character Base (in 64K steps) (merged with 16K step in BGxCNT)
   constant A_DISPCNT_Screen_Base            : regmap_type := (16#0000#,  29,     27,        1,        0,   readwrite); -- 27-29 A     Screen Base (in 64K steps) (merged with 2K step in BGxCNT)
   constant A_DISPCNT_BG_Extended_Palettes   : regmap_type := (16#0000#,  30,     30,        1,        0,   readwrite); -- 30    A+B   BG Extended Palettes   (0=Disable, 1=Enable)
   constant A_DISPCNT_OBJ_Extended_Palettes  : regmap_type := (16#0000#,  31,     31,        1,        0,   readwrite); -- 31    A+B   OBJ Extended Palettes  (0=Disable, 1=Enable
   
   constant DISPSTAT                         : regmap_type := (16#0004#,  15,      0,        1, 16#0004#,   readwrite); -- General LCD Status (STAT,LYC)                 2    R/W
   constant DISPSTAT_V_Blank_flag            : regmap_type := (16#0004#,   0,      0,        1,        0,   readonly ); -- V-Blank flag   (Read only) (1=VBlank) (set in line 160..226; not 227)
   constant DISPSTAT_H_Blank_flag            : regmap_type := (16#0004#,   1,      1,        1,        0,   readonly ); -- H-Blank flag   (Read only) (1=HBlank) (toggled in all lines, 0..227)
   constant DISPSTAT_V_Counter_flag          : regmap_type := (16#0004#,   2,      2,        1,        0,   readonly ); -- V-Counter flag (Read only) (1=Match)  (set in selected line)     (R)
   constant DISPSTAT_V_Blank_IRQ_Enable      : regmap_type := (16#0004#,   3,      3,        1,        0,   readwrite); -- V-Blank IRQ Enable         (1=Enable)                          (R/W)
   constant DISPSTAT_H_Blank_IRQ_Enable      : regmap_type := (16#0004#,   4,      4,        1,        0,   readwrite); -- H-Blank IRQ Enable         (1=Enable)                          (R/W)
   constant DISPSTAT_V_Counter_IRQ_Enable    : regmap_type := (16#0004#,   5,      5,        1,        0,   readwrite); -- V-Counter IRQ Enable       (1=Enable)                          (R/W)
                                                                                                                     -- Not used (0) / DSi: LCD Initialization Ready (0=Busy, 1=Ready)   (R)
   constant DISPSTAT_V_Count_Setting8        : regmap_type := (16#0004#,   7,      7,        1,        0,   readwrite); -- NDS: MSB of V-Vcount Setting (LYC.Bit8) (0..262)(R/W)
   constant DISPSTAT_V_Count_Setting         : regmap_type := (16#0004#,  15,      8,        1,        0,   readwrite); -- V-Count Setting (LYC)      (0..227)                            (R/W)
                                             
   constant VCOUNT                           : regmap_type := (16#0004#,  31,     16,        1,        0,   readwrite); -- Vertical Counter (LY)                         2    R  
     
   constant A_BG0CNT                         : regmap_type := (16#0008#,  15,      0,        1,        0,   writeonly); -- BG0 Control                                   2    R/W
   constant A_BG0CNT_BG_Priority             : regmap_type := (16#0008#,   1,      0,        1,        0,   readwrite); -- BG Priority           (0-3, 0=Highest)
   constant A_BG0CNT_Character_Base_Block    : regmap_type := (16#0008#,   5,      2,        1,        0,   readwrite); -- Character Base Block  (0-15, in units of 16 KBytes) (=BG Tile Data)
   constant A_BG0CNT_Mosaic                  : regmap_type := (16#0008#,   6,      6,        1,        0,   readwrite); -- Mosaic                (0=Disable, 1=Enable)
   constant A_BG0CNT_Colors_Palettes         : regmap_type := (16#0008#,   7,      7,        1,        0,   readwrite); -- Colors/Palettes       (0=16/16, 1=256/1)
   constant A_BG0CNT_Screen_Base_Block       : regmap_type := (16#0008#,  12,      8,        1,        0,   readwrite); -- Screen Base Block     (0-31, in units of 2 KBytes) (=BG Map Data)
   constant A_BG0CNT_Ext_Palette_Slot        : regmap_type := (16#0008#,  13,     13,        1,        0,   readwrite); -- Ext Palette Slot for BG0/BG1
   constant A_BG0CNT_Screen_Size             : regmap_type := (16#0008#,  15,     14,        1,        0,   readwrite); -- Screen Size (0-3)
                                           
   constant A_BG1CNT                         : regmap_type := (16#0008#,  31,     16,        1,        0,   writeonly); -- BG1 Control                                   2    R/W
   constant A_BG1CNT_BG_Priority             : regmap_type := (16#0008#,  17,     16,        1,        0,   readwrite); -- BG Priority           (0-3, 0=Highest)
   constant A_BG1CNT_Character_Base_Block    : regmap_type := (16#0008#,  21,     18,        1,        0,   readwrite); -- Character Base Block  (0-15, in units of 16 KBytes) (=BG Tile Data)
   constant A_BG1CNT_Mosaic                  : regmap_type := (16#0008#,  22,     22,        1,        0,   readwrite); -- Mosaic                (0=Disable, 1=Enable)
   constant A_BG1CNT_Colors_Palettes         : regmap_type := (16#0008#,  23,     23,        1,        0,   readwrite); -- Colors/Palettes       (0=16/16, 1=256/1)
   constant A_BG1CNT_Screen_Base_Block       : regmap_type := (16#0008#,  28,     24,        1,        0,   readwrite); -- Screen Base Block     (0-31, in units of 2 KBytes) (=BG Map Data)
   constant A_BG1CNT_Ext_Palette_Slot        : regmap_type := (16#0008#,  29,     29,        1,        0,   readwrite); -- Ext Palette Slot for BG0/BG1
   constant A_BG1CNT_Screen_Size             : regmap_type := (16#0008#,  31,     30,        1,        0,   readwrite); -- Screen Size (0-3)
                                           
   constant A_BG2CNT                         : regmap_type := (16#000C#,  15,      0,        1,        0,   readwrite); -- BG2 Control                                   2    R/W
   constant A_BG2CNT_BG_Priority             : regmap_type := (16#000C#,   1,      0,        1,        0,   readwrite); -- BG Priority           (0-3, 0=Highest)
   constant A_BG2CNT_Character_Base_Block    : regmap_type := (16#000C#,   5,      2,        1,        0,   readwrite); -- Character Base Block  (0-15, in units of 16 KBytes) (=BG Tile Data)
   constant A_BG2CNT_Mosaic                  : regmap_type := (16#000C#,   6,      6,        1,        0,   readwrite); -- Mosaic                (0=Disable, 1=Enable)
   constant A_BG2CNT_Colors_Palettes         : regmap_type := (16#000C#,   7,      7,        1,        0,   readwrite); -- Colors/Palettes       (0=16/16, 1=256/1)
   constant A_BG2CNT_Screen_Base_Block       : regmap_type := (16#000C#,  12,      8,        1,        0,   readwrite); -- Screen Base Block     (0-31, in units of 2 KBytes) (=BG Map Data)
   constant A_BG2CNT_Display_Area_Overflow   : regmap_type := (16#000C#,  13,     13,        1,        0,   readwrite); -- Display Area Overflow (0=Transparent, 1=Wraparound; BG2CNT/BG3CNT only)
   constant A_BG2CNT_Screen_Size             : regmap_type := (16#000C#,  15,     14,        1,        0,   readwrite); -- Screen Size (0-3)
                                           
   constant A_BG3CNT                         : regmap_type := (16#000C#,  31,     16,        1,        0,   readwrite); -- BG3 Control                                   2    R/W
   constant A_BG3CNT_BG_Priority             : regmap_type := (16#000C#,  17,     16,        1,        0,   readwrite); -- BG Priority           (0-3, 0=Highest)
   constant A_BG3CNT_Character_Base_Block    : regmap_type := (16#000C#,  21,     18,        1,        0,   readwrite); -- Character Base Block  (0-15, in units of 16 KBytes) (=BG Tile Data)
   constant A_BG3CNT_Mosaic                  : regmap_type := (16#000C#,  22,     22,        1,        0,   readwrite); -- Mosaic                (0=Disable, 1=Enable)
   constant A_BG3CNT_Colors_Palettes         : regmap_type := (16#000C#,  23,     23,        1,        0,   readwrite); -- Colors/Palettes       (0=16/16, 1=256/1)
   constant A_BG3CNT_Screen_Base_Block       : regmap_type := (16#000C#,  28,     24,        1,        0,   readwrite); -- Screen Base Block     (0-31, in units of 2 KBytes) (=BG Map Data)
   constant A_BG3CNT_Display_Area_Overflow   : regmap_type := (16#000C#,  29,     29,        1,        0,   readwrite); -- Display Area Overflow (0=Transparent, 1=Wraparound; BG2CNT/BG3CNT only)
   constant A_BG3CNT_Screen_Size             : regmap_type := (16#000C#,  31,     30,        1,        0,   readwrite); -- Screen Size (0-3)
                                           
   constant A_BG0HOFS                        : regmap_type := (16#0010#,  15,      0,        1,        0,   writeonly); -- BG0 X-Offset                                  2    W  
   constant A_BG0VOFS                        : regmap_type := (16#0010#,  31,     16,        1,        0,   writeonly); -- BG0 Y-Offset                                  2    W  
   constant A_BG1HOFS                        : regmap_type := (16#0014#,  15,      0,        1,        0,   writeonly); -- BG1 X-Offset                                  2    W  
   constant A_BG1VOFS                        : regmap_type := (16#0014#,  31,     16,        1,        0,   writeonly); -- BG1 Y-Offset                                  2    W  
   constant A_BG2HOFS                        : regmap_type := (16#0018#,  15,      0,        1,        0,   writeonly); -- BG2 X-Offset                                  2    W  
   constant A_BG2VOFS                        : regmap_type := (16#0018#,  31,     16,        1,        0,   writeonly); -- BG2 Y-Offset                                  2    W  
   constant A_BG3HOFS                        : regmap_type := (16#001C#,  15,      0,        1,        0,   writeonly); -- BG3 X-Offset                                  2    W  
   constant A_BG3VOFS                        : regmap_type := (16#001C#,  31,     16,        1,        0,   writeonly); -- BG3 Y-Offset                                  2    W  
                                           
   constant A_BG2RotScaleParDX               : regmap_type := (16#0020#,  15,      0,        1,      256,   writeonly); -- BG2 Rotation/Scaling Parameter A (dx)         2    W  
   constant A_BG2RotScaleParDMX              : regmap_type := (16#0020#,  31,     16,        1,        0,   writeonly); -- BG2 Rotation/Scaling Parameter B (dmx)        2    W  
   constant A_BG2RotScaleParDY               : regmap_type := (16#0024#,  15,      0,        1,        0,   writeonly); -- BG2 Rotation/Scaling Parameter C (dy)         2    W  
   constant A_BG2RotScaleParDMY              : regmap_type := (16#0024#,  31,     16,        1,      256,   writeonly); -- BG2 Rotation/Scaling Parameter D (dmy)        2    W  
   constant A_BG2RefX                        : regmap_type := (16#0028#,  27,      0,        1,        0,   writeonly); -- BG2 Reference Point X-Coordinate              4    W  
   constant A_BG2RefY                        : regmap_type := (16#002C#,  27,      0,        1,        0,   writeonly); -- BG2 Reference Point Y-Coordinate              4    W  
                                           
   constant A_BG3RotScaleParDX               : regmap_type := (16#0030#,  15,      0,        1,      256,   writeonly); -- BG3 Rotation/Scaling Parameter A (dx)         2    W  
   constant A_BG3RotScaleParDMX              : regmap_type := (16#0030#,  31,     16,        1,        0,   writeonly); -- BG3 Rotation/Scaling Parameter B (dmx)        2    W  
   constant A_BG3RotScaleParDY               : regmap_type := (16#0034#,  15,      0,        1,        0,   writeonly); -- BG3 Rotation/Scaling Parameter C (dy)         2    W  
   constant A_BG3RotScaleParDMY              : regmap_type := (16#0034#,  31,     16,        1,      256,   writeonly); -- BG3 Rotation/Scaling Parameter D (dmy)        2    W  
   constant A_BG3RefX                        : regmap_type := (16#0038#,  27,      0,        1,        0,   writeonly); -- BG3 Reference Point X-Coordinate              4    W  
   constant A_BG3RefY                        : regmap_type := (16#003C#,  27,      0,        1,        0,   writeonly); -- BG3 Reference Point Y-Coordinate              4    W  
                                           
   constant A_WIN0H                          : regmap_type := (16#0040#,  15,      0,        1,        0,   writeonly); -- Window 0 Horizontal Dimensions                2    W  
   constant A_WIN0H_X2                       : regmap_type := (16#0040#,   7,      0,        1,        0,   writeonly); -- Window 0 Horizontal Dimensions                2    W  
   constant A_WIN0H_X1                       : regmap_type := (16#0040#,  15,      8,        1,        0,   writeonly); -- Window 0 Horizontal Dimensions                2    W  
                                           
   constant A_WIN1H                          : regmap_type := (16#0040#,  31,     16,        1,        0,   writeonly); -- Window 1 Horizontal Dimensions                2    W  
   constant A_WIN1H_X2                       : regmap_type := (16#0040#,  23,     16,        1,        0,   writeonly); -- Window 1 Horizontal Dimensions                2    W  
   constant A_WIN1H_X1                       : regmap_type := (16#0040#,  31,     24,        1,        0,   writeonly); -- Window 1 Horizontal Dimensions                2    W  
                                           
   constant A_WIN0V                          : regmap_type := (16#0044#,  15,      0,        1,        0,   writeonly); -- Window 0 Vertical Dimensions                  2    W  
   constant A_WIN0V_Y2                       : regmap_type := (16#0044#,   7,      0,        1,        0,   writeonly); -- Window 0 Vertical Dimensions                  2    W  
   constant A_WIN0V_Y1                       : regmap_type := (16#0044#,  15,      8,        1,        0,   writeonly); -- Window 0 Vertical Dimensions                  2    W  
                                                                       
   constant A_WIN1V                          : regmap_type := (16#0044#,  31,     16,        1,        0,   writeonly); -- Window 1 Vertical Dimensions                  2    W  
   constant A_WIN1V_Y2                       : regmap_type := (16#0044#,  23,     16,        1,        0,   writeonly); -- Window 1 Vertical Dimensions                  2    W  
   constant A_WIN1V_Y1                       : regmap_type := (16#0044#,  31,     24,        1,        0,   writeonly); -- Window 1 Vertical Dimensions                  2    W  
                                           
   constant A_WININ                          : regmap_type := (16#0048#,  15,      0,        1,        0,   writeonly); -- Inside of Window 0 and 1                      2    R/W
   constant A_WININ_Window_0_BG0_Enable      : regmap_type := (16#0048#,   0,      0,        1,        0,   readwrite); -- 0-3   Window_0_BG0_BG3_Enable     (0=No Display, 1=Display)
   constant A_WININ_Window_0_BG1_Enable      : regmap_type := (16#0048#,   1,      1,        1,        0,   readwrite); -- 0-3   Window_0_BG0_BG3_Enable     (0=No Display, 1=Display)
   constant A_WININ_Window_0_BG2_Enable      : regmap_type := (16#0048#,   2,      2,        1,        0,   readwrite); -- 0-3   Window_0_BG0_BG3_Enable     (0=No Display, 1=Display)
   constant A_WININ_Window_0_BG3_Enable      : regmap_type := (16#0048#,   3,      3,        1,        0,   readwrite); -- 0-3   Window_0_BG0_BG3_Enable     (0=No Display, 1=Display)
   constant A_WININ_Window_0_OBJ_Enable      : regmap_type := (16#0048#,   4,      4,        1,        0,   readwrite); -- 4     Window_0_OBJ_Enable         (0=No Display, 1=Display)
   constant A_WININ_Window_0_Special_Effect  : regmap_type := (16#0048#,   5,      5,        1,        0,   readwrite); -- 5     Window_0_Special_Effect     (0=Disable, 1=Enable)
   constant A_WININ_Window_1_BG0_Enable      : regmap_type := (16#0048#,   8,      8,        1,        0,   readwrite); -- 8-11  Window_1_BG0_BG3_Enable     (0=No Display, 1=Display)
   constant A_WININ_Window_1_BG1_Enable      : regmap_type := (16#0048#,   9,      9,        1,        0,   readwrite); -- 8-11  Window_1_BG0_BG3_Enable     (0=No Display, 1=Display)
   constant A_WININ_Window_1_BG2_Enable      : regmap_type := (16#0048#,  10,     10,        1,        0,   readwrite); -- 8-11  Window_1_BG0_BG3_Enable     (0=No Display, 1=Display)
   constant A_WININ_Window_1_BG3_Enable      : regmap_type := (16#0048#,  11,     11,        1,        0,   readwrite); -- 8-11  Window_1_BG0_BG3_Enable     (0=No Display, 1=Display)
   constant A_WININ_Window_1_OBJ_Enable      : regmap_type := (16#0048#,  12,     12,        1,        0,   readwrite); -- 12    Window_1_OBJ_Enable         (0=No Display, 1=Display)
   constant A_WININ_Window_1_Special_Effect  : regmap_type := (16#0048#,  13,     13,        1,        0,   readwrite); -- 13    Window_1_Special_Effect     (0=Disable, 1=Enable)
                                           
   constant A_WINOUT                         : regmap_type := (16#0048#,  31,     16,        1,        0,   writeonly); -- Inside of OBJ Window & Outside of Windows     2    R/W
   constant A_WINOUT_Outside_BG0_Enable      : regmap_type := (16#0048#,  16,     16,        1,        0,   readwrite); -- 0-3   Outside_BG0_BG3_Enable     (0=No Display, 1=Display)
   constant A_WINOUT_Outside_BG1_Enable      : regmap_type := (16#0048#,  17,     17,        1,        0,   readwrite); -- 0-3   Outside_BG0_BG3_Enable     (0=No Display, 1=Display)
   constant A_WINOUT_Outside_BG2_Enable      : regmap_type := (16#0048#,  18,     18,        1,        0,   readwrite); -- 0-3   Outside_BG0_BG3_Enable     (0=No Display, 1=Display)
   constant A_WINOUT_Outside_BG3_Enable      : regmap_type := (16#0048#,  19,     19,        1,        0,   readwrite); -- 0-3   Outside_BG0_BG3_Enable     (0=No Display, 1=Display)
   constant A_WINOUT_Outside_OBJ_Enable      : regmap_type := (16#0048#,  20,     20,        1,        0,   readwrite); -- 4     Outside_OBJ_Enable         (0=No Display, 1=Display)
   constant A_WINOUT_Outside_Special_Effect  : regmap_type := (16#0048#,  21,     21,        1,        0,   readwrite); -- 5     Outside_Special_Effect     (0=Disable, 1=Enable)
   constant A_WINOUT_Objwnd_BG0_Enable       : regmap_type := (16#0048#,  24,     24,        1,        0,   readwrite); -- 8-11  object window_BG0_BG3_Enable     (0=No Display, 1=Display)
   constant A_WINOUT_Objwnd_BG1_Enable       : regmap_type := (16#0048#,  25,     25,        1,        0,   readwrite); -- 8-11  object window_BG0_BG3_Enable     (0=No Display, 1=Display)
   constant A_WINOUT_Objwnd_BG2_Enable       : regmap_type := (16#0048#,  26,     26,        1,        0,   readwrite); -- 8-11  object window_BG0_BG3_Enable     (0=No Display, 1=Display)
   constant A_WINOUT_Objwnd_BG3_Enable       : regmap_type := (16#0048#,  27,     27,        1,        0,   readwrite); -- 8-11  object window_BG0_BG3_Enable     (0=No Display, 1=Display)
   constant A_WINOUT_Objwnd_OBJ_Enable       : regmap_type := (16#0048#,  28,     28,        1,        0,   readwrite); -- 12    object window_OBJ_Enable         (0=No Display, 1=Display)
   constant A_WINOUT_Objwnd_Special_Effect   : regmap_type := (16#0048#,  29,     29,        1,        0,   readwrite); -- 13    object window_Special_Effect     (0=Disable, 1=Enable)
                                           
   constant A_MOSAIC                         : regmap_type := (16#004C#,  15,      0,        1,        0,   writeonly); -- Mosaic Size                                   2    W  
   constant A_MOSAIC_BG_Mosaic_H_Size        : regmap_type := (16#004C#,   3,      0,        1,        0,   writeonly); --   0-3   BG_Mosaic_H_Size  (minus 1)  
   constant A_MOSAIC_BG_Mosaic_V_Size        : regmap_type := (16#004C#,   7,      4,        1,        0,   writeonly); --   4-7   BG_Mosaic_V_Size  (minus 1)  
   constant A_MOSAIC_OBJ_Mosaic_H_Size       : regmap_type := (16#004C#,  11,      8,        1,        0,   writeonly); --   8-11  OBJ_Mosaic_H_Size (minus 1)  
   constant A_MOSAIC_OBJ_Mosaic_V_Size       : regmap_type := (16#004C#,  15,     12,        1,        0,   writeonly); --   12-15 OBJ_Mosaic_V_Size (minus 1)  
     
   constant A_BLDCNT                         : regmap_type := (16#0050#,  13,      0,        1,        0,   readwrite); -- Color Special Effects Selection               2    R/W
   constant A_BLDCNT_BG0_1st_Target_Pixel    : regmap_type := (16#0050#,   0,      0,        1,        0,   readwrite); -- 0      (Background 0)
   constant A_BLDCNT_BG1_1st_Target_Pixel    : regmap_type := (16#0050#,   1,      1,        1,        0,   readwrite); -- 1      (Background 1)
   constant A_BLDCNT_BG2_1st_Target_Pixel    : regmap_type := (16#0050#,   2,      2,        1,        0,   readwrite); -- 2      (Background 2)
   constant A_BLDCNT_BG3_1st_Target_Pixel    : regmap_type := (16#0050#,   3,      3,        1,        0,   readwrite); -- 3      (Background 3)
   constant A_BLDCNT_OBJ_1st_Target_Pixel    : regmap_type := (16#0050#,   4,      4,        1,        0,   readwrite); -- 4      (Top-most OBJ pixel)
   constant A_BLDCNT_BD_1st_Target_Pixel     : regmap_type := (16#0050#,   5,      5,        1,        0,   readwrite); -- 5      (Backdrop)
   constant A_BLDCNT_Color_Special_Effect    : regmap_type := (16#0050#,   7,      6,        1,        0,   readwrite); -- 6-7    (0-3, see below) 0 = None (Special effects disabled), 1 = Alpha Blending (1st+2nd Target mixed), 2 = Brightness Increase (1st Target becomes whiter), 3 = Brightness Decrease (1st Target becomes blacker)
   constant A_BLDCNT_BG0_2nd_Target_Pixel    : regmap_type := (16#0050#,   8,      8,        1,        0,   readwrite); -- 8      (Background 0)
   constant A_BLDCNT_BG1_2nd_Target_Pixel    : regmap_type := (16#0050#,   9,      9,        1,        0,   readwrite); -- 9      (Background 1)
   constant A_BLDCNT_BG2_2nd_Target_Pixel    : regmap_type := (16#0050#,  10,     10,        1,        0,   readwrite); -- 10     (Background 2)
   constant A_BLDCNT_BG3_2nd_Target_Pixel    : regmap_type := (16#0050#,  11,     11,        1,        0,   readwrite); -- 11     (Background 3)
   constant A_BLDCNT_OBJ_2nd_Target_Pixel    : regmap_type := (16#0050#,  12,     12,        1,        0,   readwrite); -- 12     (Top-most OBJ pixel)
   constant A_BLDCNT_BD_2nd_Target_Pixel     : regmap_type := (16#0050#,  13,     13,        1,        0,   readwrite); -- 13     (Backdrop)
                                           
   constant A_BLDALPHA                       : regmap_type := (16#0050#,  28,     16,        1,        0,   writeonly); -- Alpha Blending Coefficients                   2    W  
   constant A_BLDALPHA_EVA_Coefficient       : regmap_type := (16#0050#,  20,     16,        1,        0,   readwrite); -- 0-4   (1st Target) (0..16 = 0/16..16/16, 17..31=16/16)
   constant A_BLDALPHA_EVB_Coefficient       : regmap_type := (16#0050#,  28,     24,        1,        0,   readwrite); -- 8-12  (2nd Target) (0..16 = 0/16..16/16, 17..31=16/16)
                                           
   constant A_BLDY                           : regmap_type := (16#0054#,   4,      0,        1,        0,   writeonly); -- Brightness (Fade-In/Out) Coefficient  0-4   EVY Coefficient (Brightness) (0..16 = 0/16..16/16, 17..31=16/16 
   
   constant DISP3DCNT                        : regmap_type := (16#0060#,  14,      0,        1,        0,   readwrite); -- 3D Display Control Register (R/W)
   constant DISP3DCNT_Texture_Mapping        : regmap_type := (16#0060#,   0,      0,        1,        0,   readwrite); -- 0     Texture Mapping      (0=Disable, 1=Enable)
   constant DISP3DCNT_PolygonAttr_Shading    : regmap_type := (16#0060#,   1,      1,        1,        0,   readwrite); -- 1     PolygonAttr Shading  (0=Toon Shading, 1=Highlight Shading)
   constant DISP3DCNT_Alpha_Test             : regmap_type := (16#0060#,   2,      2,        1,        0,   readwrite); -- 2     Alpha-Test           (0=Disable, 1=Enable) (see ALPHA_TEST_REF)
   constant DISP3DCNT_Alpha_Blending         : regmap_type := (16#0060#,   3,      3,        1,        0,   readwrite); -- 3     Alpha-Blending       (0=Disable, 1=Enable) (see various Alpha values)
   constant DISP3DCNT_Anti_Aliasing          : regmap_type := (16#0060#,   4,      4,        1,        0,   readwrite); -- 4     Anti-Aliasing        (0=Disable, 1=Enable)
   constant DISP3DCNT_Edge_Marking           : regmap_type := (16#0060#,   5,      5,        1,        0,   readwrite); -- 5     Edge-Marking         (0=Disable, 1=Enable) (see EDGE_COLOR)
   constant DISP3DCNT_Fog_Color_Alpha Mode   : regmap_type := (16#0060#,   6,      6,        1,        0,   readwrite); -- 6     Fog Color/Alpha Mode (0=Alpha and Color, 1=Only Alpha) (see FOG_COLOR)
   constant DISP3DCNT_Fog_Master_Enable      : regmap_type := (16#0060#,   7,      7,        1,        0,   readwrite); -- 7     Fog Master Enable    (0=Disable, 1=Enable)
   constant DISP3DCNT_Fog_Depth_Shift        : regmap_type := (16#0060#,  11,      8,        1,        0,   readwrite); -- 8-11  Fog Depth Shift      (FOG_STEP=400h shr FOG_SHIFT) (see FOG_OFFSET)
   constant DISP3DCNT_RDLINES_Underflow      : regmap_type := (16#0060#,  12,     12,        1,        0,   readwrite); -- 12    Color Buffer RDLINES Underflow (0=None, 1=Underflow/Acknowledge)
   constant DISP3DCNT_RAM_Overflow           : regmap_type := (16#0060#,  13,     13,        1,        0,   readwrite); -- 13    Polygon/Vertex RAM Overflow    (0=None, 1=Overflow/Acknowledge)
   constant DISP3DCNT_Rear_Plane_Mode        : regmap_type := (16#0060#,  14,     14,        1,        0,   readwrite); -- 14    Rear-Plane Mode                (0=Blank, 1=Bitmap)
                  
   constant DISPCAPCNT                       : regmap_type := (16#0064#,  31,      0,        1,        0,   writeonly); -- Alpha Blending Coefficients                   2    W  
   constant DISPCAPCNT_EVA                   : regmap_type := (16#0064#,   4,      0,        1,        0,   writeonly); -- 0-4   EVA               (0..16 = Blending Factor for Source A)
   constant DISPCAPCNT_EVB                   : regmap_type := (16#0064#,  12,      8,        1,        0,   writeonly); -- 8-12  EVB               (0..16 = Blending Factor for Source B)
   constant DISPCAPCNT_VRAM_Write_Block      : regmap_type := (16#0064#,  17,     16,        1,        0,   writeonly); -- 16-17 VRAM Write Block  (0..3 = VRAM A..D) (VRAM must be allocated to LCDC)
   constant DISPCAPCNT_VRAM_Write_Offset     : regmap_type := (16#0064#,  19,     18,        1,        0,   writeonly); -- 18-19 VRAM Write Offset (0=00000h, 0=08000h, 0=10000h, 0=18000h)
   constant DISPCAPCNT_Capture_Size          : regmap_type := (16#0064#,  21,     20,        1,        0,   writeonly); -- 20-21 Capture Size      (0=128x128, 1=256x64, 2=256x128, 3=256x192 dots)
   constant DISPCAPCNT_Source_A              : regmap_type := (16#0064#,  24,     24,        1,        0,   writeonly); -- 24    Source A          (0=Graphics Screen BG+3D+OBJ, 1=3D Screen)
   constant DISPCAPCNT_Source_B              : regmap_type := (16#0064#,  25,     25,        1,        0,   writeonly); -- 25    Source B          (0=VRAM, 1=Main Memory Display FIFO)
   constant DISPCAPCNT_VRAM_Read_Offset      : regmap_type := (16#0064#,  27,     26,        1,        0,   writeonly); -- 26-27 VRAM Read Offset  (0=00000h, 0=08000h, 0=10000h, 0=18000h)
   constant DISPCAPCNT_Capture_Source        : regmap_type := (16#0064#,  30,     29,        1,        0,   writeonly); -- 29-30 Capture Source    (0=Source A, 1=Source B, 2/3=Sources A+B blended)
   constant DISPCAPCNT_Capture_Enable        : regmap_type := (16#0064#,  31,     31,        1,        0,   writeonly); -- 31    Capture Enable    (0=Disable/Ready, 1=Enable/Busy)
                                             
   constant DISP_MMEM_FIFO                   : regmap_type := (16#0068#,  31,      0,        1,        0,   writeonly); -- Main Memory Display FIFO (R?/W)
                                           
   constant A_MASTER_BRIGHT                  : regmap_type := (16#006C#,  15,      0,        1,        0,   writeonly); -- Alpha Blending Coefficients                   2    W  
   constant A_MASTER_BRIGHT_Factor           : regmap_type := (16#006C#,   4,      0,        1,        0,   writeonly); -- Factor used for 6bit R,G,B Intensities (0-16, values >16 same as 16)
   constant A_MASTER_BRIGHT_Mode             : regmap_type := (16#006C#,  15,     14,        1,        0,   writeonly); -- Mode (0=Disable, 1=Up, 2=Down, 3=Reserved)
 
   -- ###################################### 
   -- ##################### Engine B
   -- ###################################### 
   
   constant B_DISPCNT                        : regmap_type := (16#1000#,  15,      0,        1,        0,   readwrite); -- LCD Control                                   2    R/W   
   constant B_DISPCNT_BG_Mode                : regmap_type := (16#1000#,   2,      0,        1,        0,   readwrite); -- BG Mode                     (0-5=Video Mode 0-6, 7=Prohibited)
   constant B_DISPCNT_BG0_2D_3D              : regmap_type := (16#1000#,   3,      3,        1,        0,   readwrite); -- A only BG0 2D/3D Selection (instead CGB Mode) (0=2D, 1=3D)
   constant B_DISPCNT_Tile_OBJ_Mapping       : regmap_type := (16#1000#,   4,      4,        1,        0,   readwrite); -- Tile OBJ Mapping        (0=2D; max 32KB, 1=1D; max 32KB..256KB)
   constant B_DISPCNT_Bitmap_OBJ_2D_Dim      : regmap_type := (16#1000#,   5,      5,        1,        0,   readwrite); -- Bitmap OBJ 2D-Dimension (0=128x512 dots, 1=256x256 dots)
   constant B_DISPCNT_Bitmap_OBJ_Mapping     : regmap_type := (16#1000#,   6,      6,        1,        0,   readwrite); -- Bitmap OBJ Mapping      (0=2D; max 128KB, 1=1D; max 128KB..256KB)
   constant B_DISPCNT_Forced_Blank           : regmap_type := (16#1000#,   7,      7,        1,        0,   readwrite); -- Forced Blank                (1=Allow FAST access to VRAM,Palette,OAM)
   constant B_DISPCNT_Screen_Display_BG0     : regmap_type := (16#1000#,   8,      8,        1,        0,   readwrite); -- Screen Display BG0          (0=Off, 1=On)
   constant B_DISPCNT_Screen_Display_BG1     : regmap_type := (16#1000#,   9,      9,        1,        0,   readwrite); -- Screen Display BG1          (0=Off, 1=On)
   constant B_DISPCNT_Screen_Display_BG2     : regmap_type := (16#1000#,  10,     10,        1,        0,   readwrite); -- Screen Display BG2          (0=Off, 1=On)
   constant B_DISPCNT_Screen_Display_BG3     : regmap_type := (16#1000#,  11,     11,        1,        0,   readwrite); -- Screen Display BG3          (0=Off, 1=On)
   constant B_DISPCNT_Screen_Display_OBJ     : regmap_type := (16#1000#,  12,     12,        1,        0,   readwrite); -- Screen Display OBJ          (0=Off, 1=On)
   constant B_DISPCNT_Window_0_Display_Flag  : regmap_type := (16#1000#,  13,     13,        1,        0,   readwrite); -- Window 0 Display Flag       (0=Off, 1=On)
   constant B_DISPCNT_Window_1_Display_Flag  : regmap_type := (16#1000#,  14,     14,        1,        0,   readwrite); -- Window 1 Display Flag       (0=Off, 1=On)
   constant B_DISPCNT_OBJ_Wnd_Display_Flag   : regmap_type := (16#1000#,  15,     15,        1,        0,   readwrite); -- OBJ Window Display Flag     (0=Off, 1=On)                                       
   constant B_DISPCNT_Display_Mode           : regmap_type := (16#1000#,  17,     16,        1,        0,   readwrite); -- 16-17 A+B   Display Mode (Engine A: 0..3, Engine B: 0..1, GBA: Green Swap)
   constant B_DISPCNT_VRAM_block             : regmap_type := (16#1000#,  19,     18,        1,        0,   readwrite); -- 18-19 A     VRAM block (0..3=VRAM A..D) (For Capture & above Display Mode=2)
   constant B_DISPCNT_Tile_OBJ_1D_Boundary   : regmap_type := (16#1000#,  21,     20,        1,        0,   readwrite); -- 20-21 A+B   Tile OBJ 1D-Boundary   (see Bit4)
   constant B_DISPCNT_Bitmap_OBJ_1D_Boundary : regmap_type := (16#1000#,  22,     22,        1,        0,   readwrite); -- 22    A     Bitmap OBJ 1D-Boundary (see Bit5-6)
   constant B_DISPCNT_OBJ_Process_H_Blank    : regmap_type := (16#1000#,  23,     23,        1,        0,   readwrite); -- 23    A+B   OBJ Processing during H-Blank (was located in Bit5 on GBA)
   constant B_DISPCNT_Character_Base         : regmap_type := (16#1000#,  26,     24,        1,        0,   readwrite); -- 24-26 A     Character Base (in 64K steps) (merged with 16K step in BGxCNT)
   constant B_DISPCNT_Screen_Base            : regmap_type := (16#1000#,  29,     27,        1,        0,   readwrite); -- 27-29 A     Screen Base (in 64K steps) (merged with 2K step in BGxCNT)
   constant B_DISPCNT_BG_Extended_Palettes   : regmap_type := (16#1000#,  30,     30,        1,        0,   readwrite); -- 30    A+B   BG Extended Palettes   (0=Disable, 1=Enable)
   constant B_DISPCNT_OBJ_Extended_Palettes  : regmap_type := (16#1000#,  31,     31,        1,        0,   readwrite); -- 31    A+B   OBJ Extended Palettes  (0=Disable, 1=Enable
   
   constant B_BG0CNT                         : regmap_type := (16#1008#,  15,      0,        1,        0,   writeonly); -- BG0 Control                                   2    R/W
   constant B_BG0CNT_BG_Priority             : regmap_type := (16#1008#,   1,      0,        1,        0,   readwrite); -- BG Priority           (0-3, 0=Highest)
   constant B_BG0CNT_Character_Base_Block    : regmap_type := (16#1008#,   5,      2,        1,        0,   readwrite); -- Character Base Block  (0-15, in units of 16 KBytes) (=BG Tile Data)
   constant B_BG0CNT_Mosaic                  : regmap_type := (16#1008#,   6,      6,        1,        0,   readwrite); -- Mosaic                (0=Disable, 1=Enable)
   constant B_BG0CNT_Colors_Palettes         : regmap_type := (16#1008#,   7,      7,        1,        0,   readwrite); -- Colors/Palettes       (0=16/16, 1=256/1)
   constant B_BG0CNT_Screen_Base_Block       : regmap_type := (16#1008#,  12,      8,        1,        0,   readwrite); -- Screen Base Block     (0-31, in units of 2 KBytes) (=BG Map Data)
   constant B_BG0CNT_Ext_Palette_Slot        : regmap_type := (16#1008#,  13,     13,        1,        0,   readwrite); -- Ext Palette Slot for BG0/BG1
   constant B_BG0CNT_Screen_Size             : regmap_type := (16#1008#,  15,     14,        1,        0,   readwrite); -- Screen Size (0-3)
                                           
   constant B_BG1CNT                         : regmap_type := (16#1008#,  31,     16,        1,        0,   writeonly); -- BG1 Control                                   2    R/W
   constant B_BG1CNT_BG_Priority             : regmap_type := (16#1008#,  17,     16,        1,        0,   readwrite); -- BG Priority           (0-3, 0=Highest)
   constant B_BG1CNT_Character_Base_Block    : regmap_type := (16#1008#,  21,     18,        1,        0,   readwrite); -- Character Base Block  (0-15, in units of 16 KBytes) (=BG Tile Data)
   constant B_BG1CNT_Mosaic                  : regmap_type := (16#1008#,  22,     22,        1,        0,   readwrite); -- Mosaic                (0=Disable, 1=Enable)
   constant B_BG1CNT_Colors_Palettes         : regmap_type := (16#1008#,  23,     23,        1,        0,   readwrite); -- Colors/Palettes       (0=16/16, 1=256/1)
   constant B_BG1CNT_Screen_Base_Block       : regmap_type := (16#1008#,  28,     24,        1,        0,   readwrite); -- Screen Base Block     (0-31, in units of 2 KBytes) (=BG Map Data)
   constant B_BG1CNT_Ext_Palette_Slot        : regmap_type := (16#1008#,  29,     29,        1,        0,   readwrite); -- Ext Palette Slot for BG0/BG1
   constant B_BG1CNT_Screen_Size             : regmap_type := (16#1008#,  31,     30,        1,        0,   readwrite); -- Screen Size (0-3)
                                           
   constant B_BG2CNT                         : regmap_type := (16#100C#,  15,      0,        1,        0,   readwrite); -- BG2 Control                                   2    R/W
   constant B_BG2CNT_BG_Priority             : regmap_type := (16#100C#,   1,      0,        1,        0,   readwrite); -- BG Priority           (0-3, 0=Highest)
   constant B_BG2CNT_Character_Base_Block    : regmap_type := (16#100C#,   5,      2,        1,        0,   readwrite); -- Character Base Block  (0-15, in units of 16 KBytes) (=BG Tile Data)
   constant B_BG2CNT_Mosaic                  : regmap_type := (16#100C#,   6,      6,        1,        0,   readwrite); -- Mosaic                (0=Disable, 1=Enable)
   constant B_BG2CNT_Colors_Palettes         : regmap_type := (16#100C#,   7,      7,        1,        0,   readwrite); -- Colors/Palettes       (0=16/16, 1=256/1)
   constant B_BG2CNT_Screen_Base_Block       : regmap_type := (16#100C#,  12,      8,        1,        0,   readwrite); -- Screen Base Block     (0-31, in units of 2 KBytes) (=BG Map Data)
   constant B_BG2CNT_Display_Area_Overflow   : regmap_type := (16#100C#,  13,     13,        1,        0,   readwrite); -- Display Area Overflow (0=Transparent, 1=Wraparound; BG2CNT/BG3CNT only)
   constant B_BG2CNT_Screen_Size             : regmap_type := (16#100C#,  15,     14,        1,        0,   readwrite); -- Screen Size (0-3)
                                           
   constant B_BG3CNT                         : regmap_type := (16#100C#,  31,     16,        1,        0,   readwrite); -- BG3 Control                                   2    R/W
   constant B_BG3CNT_BG_Priority             : regmap_type := (16#100C#,  17,     16,        1,        0,   readwrite); -- BG Priority           (0-3, 0=Highest)
   constant B_BG3CNT_Character_Base_Block    : regmap_type := (16#100C#,  21,     18,        1,        0,   readwrite); -- Character Base Block  (0-15, in units of 16 KBytes) (=BG Tile Data)
   constant B_BG3CNT_Mosaic                  : regmap_type := (16#100C#,  22,     22,        1,        0,   readwrite); -- Mosaic                (0=Disable, 1=Enable)
   constant B_BG3CNT_Colors_Palettes         : regmap_type := (16#100C#,  23,     23,        1,        0,   readwrite); -- Colors/Palettes       (0=16/16, 1=256/1)
   constant B_BG3CNT_Screen_Base_Block       : regmap_type := (16#100C#,  28,     24,        1,        0,   readwrite); -- Screen Base Block     (0-31, in units of 2 KBytes) (=BG Map Data)
   constant B_BG3CNT_Display_Area_Overflow   : regmap_type := (16#100C#,  29,     29,        1,        0,   readwrite); -- Display Area Overflow (0=Transparent, 1=Wraparound; BG2CNT/BG3CNT only)
   constant B_BG3CNT_Screen_Size             : regmap_type := (16#100C#,  31,     30,        1,        0,   readwrite); -- Screen Size (0-3)
                                           
   constant B_BG0HOFS                        : regmap_type := (16#1010#,  15,      0,        1,        0,   writeonly); -- BG0 X-Offset                                  2    W  
   constant B_BG0VOFS                        : regmap_type := (16#1010#,  31,     16,        1,        0,   writeonly); -- BG0 Y-Offset                                  2    W  
   constant B_BG1HOFS                        : regmap_type := (16#1014#,  15,      0,        1,        0,   writeonly); -- BG1 X-Offset                                  2    W  
   constant B_BG1VOFS                        : regmap_type := (16#1014#,  31,     16,        1,        0,   writeonly); -- BG1 Y-Offset                                  2    W  
   constant B_BG2HOFS                        : regmap_type := (16#1018#,  15,      0,        1,        0,   writeonly); -- BG2 X-Offset                                  2    W  
   constant B_BG2VOFS                        : regmap_type := (16#1018#,  31,     16,        1,        0,   writeonly); -- BG2 Y-Offset                                  2    W  
   constant B_BG3HOFS                        : regmap_type := (16#101C#,  15,      0,        1,        0,   writeonly); -- BG3 X-Offset                                  2    W  
   constant B_BG3VOFS                        : regmap_type := (16#101C#,  31,     16,        1,        0,   writeonly); -- BG3 Y-Offset                                  2    W  
                                           
   constant B_BG2RotScaleParDX               : regmap_type := (16#1020#,  15,      0,        1,      256,   writeonly); -- BG2 Rotation/Scaling Parameter A (dx)         2    W  
   constant B_BG2RotScaleParDMX              : regmap_type := (16#1020#,  31,     16,        1,        0,   writeonly); -- BG2 Rotation/Scaling Parameter B (dmx)        2    W  
   constant B_BG2RotScaleParDY               : regmap_type := (16#1024#,  15,      0,        1,        0,   writeonly); -- BG2 Rotation/Scaling Parameter C (dy)         2    W  
   constant B_BG2RotScaleParDMY              : regmap_type := (16#1024#,  31,     16,        1,      256,   writeonly); -- BG2 Rotation/Scaling Parameter D (dmy)        2    W  
   constant B_BG2RefX                        : regmap_type := (16#1028#,  27,      0,        1,        0,   writeonly); -- BG2 Reference Point X-Coordinate              4    W  
   constant B_BG2RefY                        : regmap_type := (16#102C#,  27,      0,        1,        0,   writeonly); -- BG2 Reference Point Y-Coordinate              4    W  
                                           
   constant B_BG3RotScaleParDX               : regmap_type := (16#1030#,  15,      0,        1,      256,   writeonly); -- BG3 Rotation/Scaling Parameter A (dx)         2    W  
   constant B_BG3RotScaleParDMX              : regmap_type := (16#1030#,  31,     16,        1,        0,   writeonly); -- BG3 Rotation/Scaling Parameter B (dmx)        2    W  
   constant B_BG3RotScaleParDY               : regmap_type := (16#1034#,  15,      0,        1,        0,   writeonly); -- BG3 Rotation/Scaling Parameter C (dy)         2    W  
   constant B_BG3RotScaleParDMY              : regmap_type := (16#1034#,  31,     16,        1,      256,   writeonly); -- BG3 Rotation/Scaling Parameter D (dmy)        2    W  
   constant B_BG3RefX                        : regmap_type := (16#1038#,  27,      0,        1,        0,   writeonly); -- BG3 Reference Point X-Coordinate              4    W  
   constant B_BG3RefY                        : regmap_type := (16#103C#,  27,      0,        1,        0,   writeonly); -- BG3 Reference Point Y-Coordinate              4    W  
                                           
   constant B_WIN0H                          : regmap_type := (16#1040#,  15,      0,        1,        0,   writeonly); -- Window 0 Horizontal Dimensions                2    W  
   constant B_WIN0H_X2                       : regmap_type := (16#1040#,   7,      0,        1,        0,   writeonly); -- Window 0 Horizontal Dimensions                2    W  
   constant B_WIN0H_X1                       : regmap_type := (16#1040#,  15,      8,        1,        0,   writeonly); -- Window 0 Horizontal Dimensions                2    W  
                                           
   constant B_WIN1H                          : regmap_type := (16#1040#,  31,     16,        1,        0,   writeonly); -- Window 1 Horizontal Dimensions                2    W  
   constant B_WIN1H_X2                       : regmap_type := (16#1040#,  23,     16,        1,        0,   writeonly); -- Window 1 Horizontal Dimensions                2    W  
   constant B_WIN1H_X1                       : regmap_type := (16#1040#,  31,     24,        1,        0,   writeonly); -- Window 1 Horizontal Dimensions                2    W  
                                           
   constant B_WIN0V                          : regmap_type := (16#1044#,  15,      0,        1,        0,   writeonly); -- Window 0 Vertical Dimensions                  2    W  
   constant B_WIN0V_Y2                       : regmap_type := (16#1044#,   7,      0,        1,        0,   writeonly); -- Window 0 Vertical Dimensions                  2    W  
   constant B_WIN0V_Y1                       : regmap_type := (16#1044#,  15,      8,        1,        0,   writeonly); -- Window 0 Vertical Dimensions                  2    W  
                                                                       
   constant B_WIN1V                          : regmap_type := (16#1044#,  31,     16,        1,        0,   writeonly); -- Window 1 Vertical Dimensions                  2    W  
   constant B_WIN1V_Y2                       : regmap_type := (16#1044#,  23,     16,        1,        0,   writeonly); -- Window 1 Vertical Dimensions                  2    W  
   constant B_WIN1V_Y1                       : regmap_type := (16#1044#,  31,     24,        1,        0,   writeonly); -- Window 1 Vertical Dimensions                  2    W  
                                           
   constant B_WININ                          : regmap_type := (16#1048#,  15,      0,        1,        0,   writeonly); -- Inside of Window 0 and 1                      2    R/W
   constant B_WININ_Window_0_BG0_Enable      : regmap_type := (16#1048#,   0,      0,        1,        0,   readwrite); -- 0-3   Window_0_BG0_BG3_Enable     (0=No Display, 1=Display)
   constant B_WININ_Window_0_BG1_Enable      : regmap_type := (16#1048#,   1,      1,        1,        0,   readwrite); -- 0-3   Window_0_BG0_BG3_Enable     (0=No Display, 1=Display)
   constant B_WININ_Window_0_BG2_Enable      : regmap_type := (16#1048#,   2,      2,        1,        0,   readwrite); -- 0-3   Window_0_BG0_BG3_Enable     (0=No Display, 1=Display)
   constant B_WININ_Window_0_BG3_Enable      : regmap_type := (16#1048#,   3,      3,        1,        0,   readwrite); -- 0-3   Window_0_BG0_BG3_Enable     (0=No Display, 1=Display)
   constant B_WININ_Window_0_OBJ_Enable      : regmap_type := (16#1048#,   4,      4,        1,        0,   readwrite); -- 4     Window_0_OBJ_Enable         (0=No Display, 1=Display)
   constant B_WININ_Window_0_Special_Effect  : regmap_type := (16#1048#,   5,      5,        1,        0,   readwrite); -- 5     Window_0_Special_Effect     (0=Disable, 1=Enable)
   constant B_WININ_Window_1_BG0_Enable      : regmap_type := (16#1048#,   8,      8,        1,        0,   readwrite); -- 8-11  Window_1_BG0_BG3_Enable     (0=No Display, 1=Display)
   constant B_WININ_Window_1_BG1_Enable      : regmap_type := (16#1048#,   9,      9,        1,        0,   readwrite); -- 8-11  Window_1_BG0_BG3_Enable     (0=No Display, 1=Display)
   constant B_WININ_Window_1_BG2_Enable      : regmap_type := (16#1048#,  10,     10,        1,        0,   readwrite); -- 8-11  Window_1_BG0_BG3_Enable     (0=No Display, 1=Display)
   constant B_WININ_Window_1_BG3_Enable      : regmap_type := (16#1048#,  11,     11,        1,        0,   readwrite); -- 8-11  Window_1_BG0_BG3_Enable     (0=No Display, 1=Display)
   constant B_WININ_Window_1_OBJ_Enable      : regmap_type := (16#1048#,  12,     12,        1,        0,   readwrite); -- 12    Window_1_OBJ_Enable         (0=No Display, 1=Display)
   constant B_WININ_Window_1_Special_Effect  : regmap_type := (16#1048#,  13,     13,        1,        0,   readwrite); -- 13    Window_1_Special_Effect     (0=Disable, 1=Enable)
                                           
   constant B_WINOUT                         : regmap_type := (16#1048#,  31,     16,        1,        0,   writeonly); -- Inside of OBJ Window & Outside of Windows     2    R/W
   constant B_WINOUT_Outside_BG0_Enable      : regmap_type := (16#1048#,  16,     16,        1,        0,   readwrite); -- 0-3   Outside_BG0_BG3_Enable     (0=No Display, 1=Display)
   constant B_WINOUT_Outside_BG1_Enable      : regmap_type := (16#1048#,  17,     17,        1,        0,   readwrite); -- 0-3   Outside_BG0_BG3_Enable     (0=No Display, 1=Display)
   constant B_WINOUT_Outside_BG2_Enable      : regmap_type := (16#1048#,  18,     18,        1,        0,   readwrite); -- 0-3   Outside_BG0_BG3_Enable     (0=No Display, 1=Display)
   constant B_WINOUT_Outside_BG3_Enable      : regmap_type := (16#1048#,  19,     19,        1,        0,   readwrite); -- 0-3   Outside_BG0_BG3_Enable     (0=No Display, 1=Display)
   constant B_WINOUT_Outside_OBJ_Enable      : regmap_type := (16#1048#,  20,     20,        1,        0,   readwrite); -- 4     Outside_OBJ_Enable         (0=No Display, 1=Display)
   constant B_WINOUT_Outside_Special_Effect  : regmap_type := (16#1048#,  21,     21,        1,        0,   readwrite); -- 5     Outside_Special_Effect     (0=Disable, 1=Enable)
   constant B_WINOUT_Objwnd_BG0_Enable       : regmap_type := (16#1048#,  24,     24,        1,        0,   readwrite); -- 8-11  object window_BG0_BG3_Enable     (0=No Display, 1=Display)
   constant B_WINOUT_Objwnd_BG1_Enable       : regmap_type := (16#1048#,  25,     25,        1,        0,   readwrite); -- 8-11  object window_BG0_BG3_Enable     (0=No Display, 1=Display)
   constant B_WINOUT_Objwnd_BG2_Enable       : regmap_type := (16#1048#,  26,     26,        1,        0,   readwrite); -- 8-11  object window_BG0_BG3_Enable     (0=No Display, 1=Display)
   constant B_WINOUT_Objwnd_BG3_Enable       : regmap_type := (16#1048#,  27,     27,        1,        0,   readwrite); -- 8-11  object window_BG0_BG3_Enable     (0=No Display, 1=Display)
   constant B_WINOUT_Objwnd_OBJ_Enable       : regmap_type := (16#1048#,  28,     28,        1,        0,   readwrite); -- 12    object window_OBJ_Enable         (0=No Display, 1=Display)
   constant B_WINOUT_Objwnd_Special_Effect   : regmap_type := (16#1048#,  29,     29,        1,        0,   readwrite); -- 13    object window_Special_Effect     (0=Disable, 1=Enable)
                                           
   constant B_MOSAIC                         : regmap_type := (16#104C#,  15,      0,        1,        0,   writeonly); -- Mosaic Size                                   2    W  
   constant B_MOSAIC_BG_Mosaic_H_Size        : regmap_type := (16#104C#,   3,      0,        1,        0,   writeonly); --   0-3   BG_Mosaic_H_Size  (minus 1)  
   constant B_MOSAIC_BG_Mosaic_V_Size        : regmap_type := (16#104C#,   7,      4,        1,        0,   writeonly); --   4-7   BG_Mosaic_V_Size  (minus 1)  
   constant B_MOSAIC_OBJ_Mosaic_H_Size       : regmap_type := (16#104C#,  11,      8,        1,        0,   writeonly); --   8-11  OBJ_Mosaic_H_Size (minus 1)  
   constant B_MOSAIC_OBJ_Mosaic_V_Size       : regmap_type := (16#104C#,  15,     12,        1,        0,   writeonly); --   12-15 OBJ_Mosaic_V_Size (minus 1)  
     
   constant B_BLDCNT                         : regmap_type := (16#1050#,  13,      0,        1,        0,   readwrite); -- Color Special Effects Selection               2    R/W
   constant B_BLDCNT_BG0_1st_Target_Pixel    : regmap_type := (16#1050#,   0,      0,        1,        0,   readwrite); -- 0      (Background 0)
   constant B_BLDCNT_BG1_1st_Target_Pixel    : regmap_type := (16#1050#,   1,      1,        1,        0,   readwrite); -- 1      (Background 1)
   constant B_BLDCNT_BG2_1st_Target_Pixel    : regmap_type := (16#1050#,   2,      2,        1,        0,   readwrite); -- 2      (Background 2)
   constant B_BLDCNT_BG3_1st_Target_Pixel    : regmap_type := (16#1050#,   3,      3,        1,        0,   readwrite); -- 3      (Background 3)
   constant B_BLDCNT_OBJ_1st_Target_Pixel    : regmap_type := (16#1050#,   4,      4,        1,        0,   readwrite); -- 4      (Top-most OBJ pixel)
   constant B_BLDCNT_BD_1st_Target_Pixel     : regmap_type := (16#1050#,   5,      5,        1,        0,   readwrite); -- 5      (Backdrop)
   constant B_BLDCNT_Color_Special_Effect    : regmap_type := (16#1050#,   7,      6,        1,        0,   readwrite); -- 6-7    (0-3, see below) 0 = None (Special effects disabled), 1 = Alpha Blending (1st+2nd Target mixed), 2 = Brightness Increase (1st Target becomes whiter), 3 = Brightness Decrease (1st Target becomes blacker)
   constant B_BLDCNT_BG0_2nd_Target_Pixel    : regmap_type := (16#1050#,   8,      8,        1,        0,   readwrite); -- 8      (Background 0)
   constant B_BLDCNT_BG1_2nd_Target_Pixel    : regmap_type := (16#1050#,   9,      9,        1,        0,   readwrite); -- 9      (Background 1)
   constant B_BLDCNT_BG2_2nd_Target_Pixel    : regmap_type := (16#1050#,  10,     10,        1,        0,   readwrite); -- 10     (Background 2)
   constant B_BLDCNT_BG3_2nd_Target_Pixel    : regmap_type := (16#1050#,  11,     11,        1,        0,   readwrite); -- 11     (Background 3)
   constant B_BLDCNT_OBJ_2nd_Target_Pixel    : regmap_type := (16#1050#,  12,     12,        1,        0,   readwrite); -- 12     (Top-most OBJ pixel)
   constant B_BLDCNT_BD_2nd_Target_Pixel     : regmap_type := (16#1050#,  13,     13,        1,        0,   readwrite); -- 13     (Backdrop)
                                           
   constant B_BLDALPHA                       : regmap_type := (16#1050#,  28,     16,        1,        0,   writeonly); -- Alpha Blending Coefficients                   2    W  
   constant B_BLDALPHA_EVA_Coefficient       : regmap_type := (16#1050#,  20,     16,        1,        0,   readwrite); -- 0-4   (1st Target) (0..16 = 0/16..16/16, 17..31=16/16)
   constant B_BLDALPHA_EVB_Coefficient       : regmap_type := (16#1050#,  28,     24,        1,        0,   readwrite); -- 8-12  (2nd Target) (0..16 = 0/16..16/16, 17..31=16/16)
                                           
   constant B_BLDY                           : regmap_type := (16#1054#,   4,      0,        1,        0,   writeonly); -- Brightness (Fade-In/Out) Coefficient  0-4   EVY Coefficient (Brightness) (0..16 = 0/16..16/16, 17..31=16/16 
                                                                             
   constant B_MASTER_BRIGHT                  : regmap_type := (16#106C#,  15,      0,        1,        0,   writeonly); -- Alpha Blending Coefficients                   2    W  
   constant B_MASTER_BRIGHT_Factor           : regmap_type := (16#106C#,   4,      0,        1,        0,   writeonly); -- Factor used for 6bit R,G,B Intensities (0-16, values >16 same as 16)
   constant B_MASTER_BRIGHT_Mode             : regmap_type := (16#106C#,  15,     14,        1,        0,   writeonly); -- Mode (0=Disable, 1=Up, 2=Down, 3=Reserved)

  
  
end package;
