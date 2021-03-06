library IEEE;
use IEEE.std_logic_1164.all;  
use IEEE.numeric_std.all;     

use work.pProc_bus_gb.all;
use work.pRegmap.all;

package pReg_ds_keypad_9 is

   -- range 0x130 .. 0x136
   --   (                              adr      upper    lower    size   default   accesstype)                                     
   constant KEYINPUT : regmap_type := (16#130#,  15,       0,        1,        0,   readonly ); -- Key Status            2    R  
   constant KEYCNT   : regmap_type := (16#130#,  31,      16,        1,        0,   readwrite); -- Key Interrupt Control 2    R/W
   
   
end package;