library IEEE;
use IEEE.std_logic_1164.all;  
use IEEE.numeric_std.all;     

use work.pProc_bus_gb.all;
use work.pRegmap.all;

package pReg_ds_display_9 is

   -- range 0x320..6A3
   --   (                                                         adr      upper    lower    size   default   accesstype)                                                     
   constant CLEAR_COLOR                         : regmap_type := (16#0350#,  29,      0,        1,        0,   Writeonly); -- Clear Color Attribute Register (W)
   constant CLEAR_COLOR_Red                     : regmap_type := (16#0350#,   4,      0,        1,        0,   Writeonly); -- 0-4    Clear Color, Red
   constant CLEAR_COLOR_Green                   : regmap_type := (16#0350#,   9,      5,        1,        0,   Writeonly); -- 5-9    Clear Color, Green
   constant CLEAR_COLOR_Blue                    : regmap_type := (16#0350#,  14,     10,        1,        0,   Writeonly); -- 10-14  Clear Color, Blue
   constant CLEAR_COLOR_Fog                     : regmap_type := (16#0350#,  15,     15,        1,        0,   Writeonly); -- 15     Fog (enables Fog to the rear-plane) (doesn't affect Fog of polygons)
   constant CLEAR_COLOR_Alpha                   : regmap_type := (16#0350#,  20,     16,        1,        0,   Writeonly); -- 16-20  Alpha
   constant CLEAR_COLOR_Clear_Polygon_ID        : regmap_type := (16#0350#,  29,     24,        1,        0,   Writeonly); -- 24-29  Clear Polygon ID (affects edge-marking, at the screen-edges?)
  
   constant CLEAR_DEPTH                         : regmap_type := (16#0354#,  31,      0,        1,        0,   Writeonly); -- Clear Depth Register (W)
   constant CLEAR_DEPTH_DEPTH                   : regmap_type := (16#0354#,  14,      0,        1,        0,   Writeonly); -- 0-14   Clear Depth (0..7FFFh) (usually 7FFFh = most distant)
   constant CLEAR_DEPTH_X_Offset                : regmap_type := (16#0354#,  23,     16,        1,        0,   Writeonly); -- Bit16-23  X-Offset (0..255; 0=upper row of bitmap)
   constant CLEAR_DEPTH_Y_Offset                : regmap_type := (16#0354#,  31,     24,        1,        0,   Writeonly); -- Bit24-30  Y-Offset (0..255; 0=left column of bitmap)
  
   constant GXFIFO                              : regmap_type := (16#0400#,  31,      0,        1,        0,   Writeonly); -- Geometry Command FIFO (mirrored up to 400043Fh?)
   
   constant GXSTAT                              : regmap_type := (16#0600#,  31,      0,     1, 16#6000000#,   Writeonly); -- Geometry Engine Status Register (R and R/W)   
   constant GXSTAT_TestBusy                     : regmap_type := (16#0600#,   0,      0,        1,        0,   readonly ); -- 0     BoxTest,PositionTest,VectorTest Busy (0=Ready, 1=Busy)
   constant GXSTAT_BoxTest_Result               : regmap_type := (16#0600#,   1,      1,        1,        0,   readonly ); -- 1     BoxTest Result  (0=All Outside View, 1=Parts or Fully Inside View)
   constant GXSTAT_PosVect_Matrix_Stack_Level   : regmap_type := (16#0600#,  12,      8,        1,        0,   readonly ); -- 8-12  Position & Vector Matrix Stack Level (0..31) (lower 5bit of 6bit value)
   constant GXSTAT_Proj_Matrix_Stack_Level      : regmap_type := (16#0600#,  13,     13,        1,        0,   readonly ); -- 13    Projection Matrix Stack Level        (0..1)
   constant GXSTAT_Matrix_Stack_Busy            : regmap_type := (16#0600#,  14,     14,        1,        0,   readonly ); -- 14    Matrix Stack Busy (0=No, 1=Yes; Currently executing a Push/Pop command)
   constant GXSTAT_Matrix_Stack_Error           : regmap_type := (16#0600#,  15,     15,        1,        0,   readwrite); -- 15    Matrix Stack Overflow/Underflow Error (0=No, 1=Error/Acknowledge/Reset)
   constant GXSTAT_Command_FIFO_Entries         : regmap_type := (16#0600#,  24,     16,        1,        0,   readonly ); -- 16-24 Number of 40bit-entries in Command FIFO  (0..256) (24)   Command FIFO Full (MSB of above)  (0=No, 1=Yes; Full)
   constant GXSTAT_Command_FIFO_Less_Half       : regmap_type := (16#0600#,  25,     25,        1,        0,   readonly ); -- 25    Command FIFO Less Than Half Full  (0=No, 1=Yes; Less than Half-full)
   constant GXSTAT_Command_FIFO_Empty           : regmap_type := (16#0600#,  26,     26,        1,        0,   readonly ); -- 26    Command FIFO Empty                (0=No, 1=Yes; Empty)
   constant GXSTAT_Geometry_Engine_Busy         : regmap_type := (16#0600#,  27,     27,        1,        0,   readwrite); -- 27    Geometry Engine Busy (0=No, 1=Yes; Busy; Commands are executing)
   constant GXSTAT_Command_FIFO_IRQ             : regmap_type := (16#0600#,  31,     30,        1,        0,   readwrite); -- 30-31 Command FIFO IRQ (0=Never, 1=Less than half full, 2=Empty, 3=Reserved)


end package;
