library IEEE;
use IEEE.std_logic_1164.all;  
use IEEE.numeric_std.all;     

use work.pProc_bus_gb.all;
use work.pRegmap.all;

package pReg_ds_display_7 is

   -- range 0x04..0x04
   --   (                                                   adr      upper    lower    size   default   accesstype)                                                     
   constant DISPSTAT                      : regmap_type := (16#004#,  15,      0,        1, 16#0004#,   readwrite); -- General LCD Status (STAT,LYC)                 2    R/W
   constant DISPSTAT_V_Blank_flag         : regmap_type := (16#004#,   0,      0,        1,        0,   readonly ); -- V-Blank flag   (Read only) (1=VBlank) (set in line 160..226; not 227)
   constant DISPSTAT_H_Blank_flag         : regmap_type := (16#004#,   1,      1,        1,        0,   readonly ); -- H-Blank flag   (Read only) (1=HBlank) (toggled in all lines, 0..227)
   constant DISPSTAT_V_Counter_flag       : regmap_type := (16#004#,   2,      2,        1,        0,   readonly ); -- V-Counter flag (Read only) (1=Match)  (set in selected line)     (R)
   constant DISPSTAT_V_Blank_IRQ_Enable   : regmap_type := (16#004#,   3,      3,        1,        0,   readwrite); -- V-Blank IRQ Enable         (1=Enable)                          (R/W)
   constant DISPSTAT_H_Blank_IRQ_Enable   : regmap_type := (16#004#,   4,      4,        1,        0,   readwrite); -- H-Blank IRQ Enable         (1=Enable)                          (R/W)
   constant DISPSTAT_V_Counter_IRQ_Enable : regmap_type := (16#004#,   5,      5,        1,        0,   readwrite); -- V-Counter IRQ Enable       (1=Enable)                          (R/W)
                                                                                                                    -- Not used (0) / DSi: LCD Initialization Ready (0=Busy, 1=Ready)   (R)
   constant DISPSTAT_V_Count_Setting8     : regmap_type := (16#004#,   7,      7,        1,        0,   readwrite); -- NDS: MSB of V-Vcount Setting (LYC.Bit8) (0..262)(R/W)
   constant DISPSTAT_V_Count_Setting      : regmap_type := (16#004#,  15,      8,        1,        0,   readwrite); -- V-Count Setting (LYC)      (0..227)                            (R/W)

   constant VCOUNT                        : regmap_type := (16#004#,  31,     16,        1,        0,   readwrite); -- Vertical Counter (LY)                         2    R  
end package;
