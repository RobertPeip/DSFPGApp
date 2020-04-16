library IEEE;
use IEEE.std_logic_1164.all;  
use IEEE.numeric_std.all;     

use work.pProc_bus_gb.all;
use work.pRegmap.all;

package pReg_ds_sound_7 is

   -- range 0x400 .. 0x51F
   --   (                                                              adr      upper    lower    size   default   accesstype)                                     
   constant SOUNDREGS                                : regmap_type := (16#400#,  31,      0,       64,        0,   readwrite); -- 16 * CNT + SAD + TMR + PNT + LEN  
   
   constant SOUNDCNT                                 : regmap_type := (16#500#,  15,      0,        1,        0,   writeonly); -- 
   constant SOUNDCNT_Master_Volume                   : regmap_type := (16#500#,   6,      0,        1,        0,   readwrite); -- Bit0-6   Master Volume       (0..127=silent..loud)
   constant SOUNDCNT_Left_Output_from                : regmap_type := (16#500#,   9,      8,        1,        0,   readwrite); -- Bit8-9   Left Output from    (0=Left Mixer, 1=Ch1, 2=Ch3, 3=Ch1+Ch3)
   constant SOUNDCNT_Right_Output_from               : regmap_type := (16#500#,  11,     10,        1,        0,   readwrite); -- Bit10-11 Right Output from   (0=Right Mixer, 1=Ch1, 2=Ch3, 3=Ch1+Ch3)
   constant SOUNDCNT_Output_Ch1_to_Mixer             : regmap_type := (16#500#,  12,     12,        1,        0,   readwrite); -- Bit12    Output Ch1 to Mixer (0=Yes, 1=No) (both Left/Right)
   constant SOUNDCNT_Output_Ch3_to_Mixer             : regmap_type := (16#500#,  13,     13,        1,        0,   readwrite); -- Bit13    Output Ch3 to Mixer (0=Yes, 1=No) (both Left/Right)
   constant SOUNDCNT_Master_Enable                   : regmap_type := (16#500#,  15,     15,        1,        0,   readwrite); -- Bit15    Master Enable       (0=Disable, 1=Enable)
   
   constant SOUNDBIAS                                : regmap_type := (16#504#,   9,      0,        1, 16#0200#,   readwrite); -- (0..3FFh, usually 200h)

   constant SOUNDCAP                                 : regmap_type := (16#508#,  15,      0,        1,        0,   writeonly);
   constant SOUNDCAP0_Control                        : regmap_type := (16#508#,   0,      0,        1,        0,   readwrite); -- Bit0     Control of Associated Sound Channels (ANDed with Bit7) SNDCAP0CNT: Output Sound Channel 1 (0=As such, 1=Add to Channel 0) Caution: Addition mode works only if BOTH Bit0 and Bit7 are set.
   constant SOUNDCAP0_Capture_Source                 : regmap_type := (16#508#,   1,      1,        1,        0,   readwrite); -- Bit1     Capture Source Selection SNDCAP0CNT: Capture 0 Source (0=Left Mixer, 1=Channel 0/Bugged)
   constant SOUNDCAP0_Capture_Repeat                 : regmap_type := (16#508#,   2,      2,        1,        0,   readwrite); -- Bit2     Capture Repeat        (0=Loop, 1=One-shot)
   constant SOUNDCAP0_Capture_Format                 : regmap_type := (16#508#,   3,      3,        1,        0,   readwrite); -- Bit3     Capture Format        (0=PCM16, 1=PCM8)
   constant SOUNDCAP0_Capture_Start_Status           : regmap_type := (16#508#,   7,      7,        1,        0,   readwrite); -- Bit7     Capture Start/Status  (0=Stop, 1=Start/Busy)
   constant SOUNDCAP1_Control                        : regmap_type := (16#508#,   8,      8,        1,        0,   readwrite); -- Bit8     Control of Associated Sound Channels (ANDed with Bit7)  SNDCAP1CNT: Output Sound Channel 3 (0=As such, 1=Add to Channel 2) Caution: Addition mode works only if BOTH Bit0 and Bit7 are set.
   constant SOUNDCAP1_Capture_Source                 : regmap_type := (16#508#,   9,      9,        1,        0,   readwrite); -- Bit9     Capture Source Selection SNDCAP1CNT: Capture 1 Source (0=Right Mixer, 1=Channel 2/Bugged)
   constant SOUNDCAP1_Capture_Repeat                 : regmap_type := (16#508#,  10,     10,        1,        0,   readwrite); -- Bit10    Capture Repeat        (0=Loop, 1=One-shot)
   constant SOUNDCAP1_Capture_Format                 : regmap_type := (16#508#,  11,     11,        1,        0,   readwrite); -- Bit11    Capture Format        (0=PCM16, 1=PCM8)
   constant SOUNDCAP1_Capture_Start_Status           : regmap_type := (16#508#,  15,     15,        1,        0,   readwrite); -- Bit15    Capture Start/Status  (0=Stop, 1=Start/Busy)
   
   constant SNDCAP0DAD                               : regmap_type := (16#510#,  26,      0,        1,        0,   readwrite); -- Destination address (word aligned, bit0-1 are always zero)
   constant SNDCAP0LEN                               : regmap_type := (16#510#,  15,      0,        1,        0,   readwrite); -- Buffer length (1..FFFFh words) (ie. N*4 bytes)
   constant SNDCAP1DAD                               : regmap_type := (16#518#,  26,      0,        1,        0,   readwrite); -- Destination address (word aligned, bit0-1 are always zero)
   constant SNDCAP1LEN                               : regmap_type := (16#51C#,  15,      0,        1,        0,   readwrite); -- Buffer length (1..FFFFh words) (ie. N*4 bytes)


end package;