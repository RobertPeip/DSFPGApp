library IEEE;
use IEEE.std_logic_1164.all;  
use IEEE.numeric_std.all;     

use work.pProc_bus_gb.all;
use work.pRegmap.all;

package pReg_ds_dma_9 is

   -- range 0xB0 .. 0xE0
   --   (                                                adr      upper    lower    size   default   accesstype)                                     
   constant DMA0SAD                      : regmap_type := (12#B0#,  31,      0,        1,        0,   readwrite); -- Source Address       4    W  
   constant DMA0DAD                      : regmap_type := (12#B4#,  31,      0,        1,        0,   readwrite); -- Destination Address  4    W  
   constant DMA0CNT_L                    : regmap_type := (12#B8#,  20,      0,        1,        0,   readwrite); -- Word Count           2    W  
   constant DMA0CNT_H                    : regmap_type := (12#B8#,  31,     16,        1,        0,   readwrite); -- Control              2    R/W
   constant DMA0CNT_H_Dest_Addr_Control  : regmap_type := (12#B8#,  22,     21,        1,        0,   readwrite); -- 5-6   Dest Addr Control  (0=Increment,1=Decrement,2=Fixed,3=Increment/Reload)
   constant DMA0CNT_H_Source_Adr_Control : regmap_type := (12#B8#,  24,     23,        1,        0,   readwrite); -- 7-8   Source Adr Control (0=Increment,1=Decrement,2=Fixed,3=Prohibited)
   constant DMA0CNT_H_DMA_Repeat         : regmap_type := (12#B8#,  25,     25,        1,        0,   readwrite); -- 9     DMA Repeat                   (0=Off, 1=On) (Must be zero if Bit 11 set)
   constant DMA0CNT_H_DMA_Transfer_Type  : regmap_type := (12#B8#,  26,     26,        1,        0,   readwrite); -- 10    DMA Transfer Type            (0=16bit, 1=32bit)
   constant DMA0CNT_H_DMA_Start_Timing   : regmap_type := (12#B8#,  29,     27,        1,        0,   readwrite); -- 11-13 Transfer mode  0  Start Immediately, 1  Start at V-Blank, 2  Start at H-Blank (paused during V-Blank), 3  Synchronize to start of display , 4  Main memory display, 5  DS Cartridge Slot ,6  GBA Cartridge Slot ,7  Geometry Command FIFO
   constant DMA0CNT_H_IRQ_on             : regmap_type := (12#B8#,  30,     30,        1,        0,   readwrite); -- 14    IRQ upon end of Word Count   (0=Disable, 1=Enable)
   constant DMA0CNT_H_DMA_Enable         : regmap_type := (12#B8#,  31,     31,        1,        0,   readwrite); -- 15    DMA Enable                   (0=Off, 1=On)

   constant DMA1SAD                      : regmap_type := (12#BC#,  31,      0,        1,        0,   readwrite); -- Source Address       4    W  
   constant DMA1DAD                      : regmap_type := (12#C0#,  31,      0,        1,        0,   readwrite); -- Destination Address  4    W  
   constant DMA1CNT_L                    : regmap_type := (12#C4#,  20,      0,        1,        0,   readwrite); -- Word Count           2    W  
   constant DMA1CNT_H                    : regmap_type := (12#C4#,  31,     16,        1,        0,   readwrite); -- Control              2    R/W
   constant DMA1CNT_H_Dest_Addr_Control  : regmap_type := (12#C4#,  22,     21,        1,        0,   readwrite); -- 5-6   Dest Addr Control  (0=Increment,1=Decrement,2=Fixed,3=Increment/Reload)
   constant DMA1CNT_H_Source_Adr_Control : regmap_type := (12#C4#,  24,     23,        1,        0,   readwrite); -- 7-8   Source Adr Control (0=Increment,1=Decrement,2=Fixed,3=Prohibited)
   constant DMA1CNT_H_DMA_Repeat         : regmap_type := (12#C4#,  25,     25,        1,        0,   readwrite); -- 9     DMA Repeat                   (0=Off, 1=On) (Must be zero if Bit 11 set)
   constant DMA1CNT_H_DMA_Transfer_Type  : regmap_type := (12#C4#,  26,     26,        1,        0,   readwrite); -- 10    DMA Transfer Type            (0=16bit, 1=32bit)
   constant DMA1CNT_H_DMA_Start_Timing   : regmap_type := (12#C4#,  29,     27,        1,        0,   readwrite); -- 11-13 Transfer mode  0  Start Immediately, 1  Start at V-Blank, 2  Start at H-Blank (paused during V-Blank), 3  Synchronize to start of display , 4  Main memory display, 5  DS Cartridge Slot ,6  GBA Cartridge Slot ,7  Geometry Command FIFO
   constant DMA1CNT_H_IRQ_on             : regmap_type := (12#C4#,  30,     30,        1,        0,   readwrite); -- 14    IRQ upon end of Word Count   (0=Disable, 1=Enable)
   constant DMA1CNT_H_DMA_Enable         : regmap_type := (12#C4#,  31,     31,        1,        0,   readwrite); -- 15    DMA Enable                   (0=Off, 1=On)
   
   constant DMA2SAD                      : regmap_type := (12#C8#,  31,      0,        1,        0,   readwrite); -- Source Address       4    W  
   constant DMA2DAD                      : regmap_type := (12#CC#,  31,      0,        1,        0,   readwrite); -- Destination Address  4    W  
   constant DMA2CNT_L                    : regmap_type := (12#D0#,  20,      0,        1,        0,   readwrite); -- Word Count           2    W  
   constant DMA2CNT_H                    : regmap_type := (12#D0#,  31,     16,        1,        0,   readwrite); -- Control              2    R/W
   constant DMA2CNT_H_Dest_Addr_Control  : regmap_type := (12#D0#,  22,     21,        1,        0,   readwrite); -- 5-6   Dest Addr Control  (0=Increment,1=Decrement,2=Fixed,3=Increment/Reload)
   constant DMA2CNT_H_Source_Adr_Control : regmap_type := (12#D0#,  24,     23,        1,        0,   readwrite); -- 7-8   Source Adr Control (0=Increment,1=Decrement,2=Fixed,3=Prohibited)
   constant DMA2CNT_H_DMA_Repeat         : regmap_type := (12#D0#,  25,     25,        1,        0,   readwrite); -- 9     DMA Repeat                   (0=Off, 1=On) (Must be zero if Bit 11 set)
   constant DMA2CNT_H_DMA_Transfer_Type  : regmap_type := (12#D0#,  26,     26,        1,        0,   readwrite); -- 10    DMA Transfer Type            (0=16bit, 1=32bit)
   constant DMA2CNT_H_DMA_Start_Timing   : regmap_type := (12#D0#,  29,     27,        1,        0,   readwrite); -- 11-13 Transfer mode  0  Start Immediately, 1  Start at V-Blank, 2  Start at H-Blank (paused during V-Blank), 3  Synchronize to start of display , 4  Main memory display, 5  DS Cartridge Slot ,6  GBA Cartridge Slot ,7  Geometry Command FIFO
   constant DMA2CNT_H_IRQ_on             : regmap_type := (12#D0#,  30,     30,        1,        0,   readwrite); -- 14    IRQ upon end of Word Count   (0=Disable, 1=Enable)
   constant DMA2CNT_H_DMA_Enable         : regmap_type := (12#D0#,  31,     31,        1,        0,   readwrite); -- 15    DMA Enable                   (0=Off, 1=On)
   
   constant DMA3SAD                      : regmap_type := (12#D4#,  31,      0,        1,        0,   readwrite); -- Source Address       4    W  
   constant DMA3DAD                      : regmap_type := (12#D8#,  31,      0,        1,        0,   readwrite); -- Destination Address  4    W  
   constant DMA3CNT_L                    : regmap_type := (12#DC#,  20,      0,        1,        0,   readwrite); -- Word Count           2    W  
   constant DMA3CNT_H                    : regmap_type := (12#DC#,  31,     16,        1,        0,   readwrite); -- Control              2    R/W
   constant DMA3CNT_H_Dest_Addr_Control  : regmap_type := (12#DC#,  22,     21,        1,        0,   readwrite); -- 5-6   Dest Addr Control  (0=Increment,1=Decrement,2=Fixed,3=Increment/Reload)
   constant DMA3CNT_H_Source_Adr_Control : regmap_type := (12#DC#,  24,     23,        1,        0,   readwrite); -- 7-8   Source Adr Control (0=Increment,1=Decrement,2=Fixed,3=Prohibited)
   constant DMA3CNT_H_DMA_Repeat         : regmap_type := (12#DC#,  25,     25,        1,        0,   readwrite); -- 9     DMA Repeat                   (0=Off, 1=On) (Must be zero if Bit 11 set)
   constant DMA3CNT_H_DMA_Transfer_Type  : regmap_type := (12#DC#,  26,     26,        1,        0,   readwrite); -- 10    DMA Transfer Type            (0=16bit, 1=32bit)
   constant DMA3CNT_H_Game_Pak_DRQ       : regmap_type := (12#DC#,  27,     27,        1,        0,   readwrite); -- 11    Game Pak DRQ  - DMA3 only -  (0=Normal, 1=DRQ <from> Game Pak, DMA3)
   constant DMA3CNT_H_DMA_Start_Timing   : regmap_type := (12#DC#,  29,     27,        1,        0,   readwrite); -- 11-13 Transfer mode  0  Start Immediately, 1  Start at V-Blank, 2  Start at H-Blank (paused during V-Blank), 3  Synchronize to start of display , 4  Main memory display, 5  DS Cartridge Slot ,6  GBA Cartridge Slot ,7  Geometry Command FIFO
   constant DMA3CNT_H_IRQ_on             : regmap_type := (12#DC#,  30,     30,        1,        0,   readwrite); -- 14    IRQ upon end of Word Count   (0=Disable, 1=Enable)
   constant DMA3CNT_H_DMA_Enable         : regmap_type := (12#DC#,  31,     31,        1,        0,   readwrite); -- 15    DMA Enable                   (0=Off, 1=On)

   constant DMA0FILL                     : regmap_type := (12#E0#,  31,      0,        1,        0,   readwrite); -- DMA0FILL - DMA 0 Filldata (R/W)
   constant DMA1FILL                     : regmap_type := (12#E4#,  31,      0,        1,        0,   readwrite); -- DMA1FILL - DMA 1 Filldata (R/W)
   constant DMA2FILL                     : regmap_type := (12#E8#,  31,      0,        1,        0,   readwrite); -- DMA2FILL - DMA 2 Filldata (R/W)
   constant DMA3FILL                     : regmap_type := (12#EC#,  31,      0,        1,        0,   readwrite); -- DMA3FILL - DMA 3 Filldata (R/W)

   
end package;
