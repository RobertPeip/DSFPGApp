library IEEE;
use IEEE.std_logic_1164.all;  
use IEEE.numeric_std.all;     

use work.pProc_bus_gb.all;
use work.pRegmap.all;

package pReg_ds_system_7 is

   -- range 0x200 .. 0x800
   --   (                                                      adr      upper    lower    size   default   accesstype)                       
   constant IPCSYNC                                : regmap_type := (12#180#,  15,      0,        1,        0,   writeonly); -- IPC Synchronize Register (R/W)            
   constant IPCSYNC_Data_from_IPCSYNC              : regmap_type := (12#180#,   3,      0,        1,        0,   readonly ); -- 0-3   R    Data input from IPCSYNC Bit8-11 of remote CPU (00h..0Fh)
   constant IPCSYNC_Data_to_IPCSYNC                : regmap_type := (12#180#,  11,      8,        1,        0,   readwrite); -- 8-11  R/W  Data output to IPCSYNC Bit0-3 of remote CPU   (00h..0Fh)
   constant IPCSYNC_IRQ _o_remote_CPU              : regmap_type := (12#180#,  13,     13,        1,        0,   readonly ); -- 13    W    Send IRQ to remote CPU      (0=None, 1=Send IRQ)
   constant IPCSYNC_Ena_IRQ_from_remote_CPU        : regmap_type := (12#180#,  14,     14,        1,        0,   readwrite); -- 14    R/W  Enable IRQ from remote CPU  (0=Disable, 1=Enable)
                                                   
   constant IPCFIFOCNT                             : regmap_type := (12#184#,  15,      0,        1,        0,   writeonly); -- IPC Fifo Control Register (R/W)           
   constant IPCFIFOCNT_Send_Fifo_Empty_Status      : regmap_type := (12#184#,   0,      0,        1,        0,   readonly ); -- 0     R    Send Fifo Empty Status      (0=Not Empty, 1=Empty)
   constant IPCFIFOCNT_Send_Fifo_Full_Status       : regmap_type := (12#184#,   1,      1,        1,        0,   readonly ); -- 1     R    Send Fifo Full Status       (0=Not Full, 1=Full)
   constant IPCFIFOCNT_Send_Fifo_Empty IRQ         : regmap_type := (12#184#,   2,      2,        1,        0,   readwrite); -- 2     R/W  Send Fifo Empty IRQ         (0=Disable, 1=Enable)
   constant IPCFIFOCNT_Send_Fifo_Clear             : regmap_type := (12#184#,   3,      3,        1,        0,   writeonly); -- 3     W    Send Fifo Clear             (0=Nothing, 1=Flush Send Fifo)
   constant IPCFIFOCNT_Receive_Fifo_Empty          : regmap_type := (12#184#,   8,      8,        1,        0,   readonly ); -- 8     R    Receive Fifo Empty          (0=Not Empty, 1=Empty)
   constant IPCFIFOCNT_Receive_Fifo_Full           : regmap_type := (12#184#,   9,      9,        1,        0,   readonly ); -- 9     R    Receive Fifo Full           (0=Not Full, 1=Full)
   constant IPCFIFOCNT_Receive_Fifo_Not_Empty_IRQ  : regmap_type := (12#184#,  10,     10,        1,        0,   readwrite); -- 10    R/W  Receive Fifo Not Empty IRQ  (0=Disable, 1=Enable)
   constant IPCFIFOCNT_Error_Read_Empty_Send_Full  : regmap_type := (12#184#,  14,     14,        1,        0,   readwrite); -- 14    R/W  Error, Read Empty/Send Full (0=No Error, 1=Error/Acknowledge)
   constant IPCFIFOCNT_Enable_Send_Receive_Fifo    : regmap_type := (12#184#,  15,     15,        1,        0,   readwrite); -- 15    R/W  Enable Send/Receive Fifo    (0=Disable, 1=Enable)

   constant IPCFIFOSEND                            : regmap_type := (12#188#,  31,      0,        1,        0,   writeonly); -- IPC Send Fifo (W) 
   -- relocate from 0xFFF to 0x100000!
   constant IPCFIFORECV                            : regmap_type := (12#FFF#,  31,      0,        1,        0,   readonly ); -- IPC Receive Fifo (R)  
   
   constant IME                                    : regmap_type := (12#208#,  31,      0,        1,        0,   readwrite); -- Interrupt Master Enable Register  
      
   constant IE                                     : regmap_type := (12#210#,  31,      0,        1,        0,   writeonly); -- Interrupt Enable              
   constant IE_LCD_V_Blank                         : regmap_type := (12#210#,   0,      0,        1,        0,   readwrite); -- 0     LCD V-Blank
   constant IE_LCD_H_Blank                         : regmap_type := (12#210#,   1,      1,        1,        0,   readwrite); -- 1     LCD H-Blank
   constant IE_LCD_V_Counter_Match                 : regmap_type := (12#210#,   2,      2,        1,        0,   readwrite); -- 2     LCD V-Counter Match
   constant IE_Timer_0                             : regmap_type := (12#210#,   3,      3,        1,        0,   readwrite); -- 3     Timer 0 Overflow
   constant IE_Timer_1                             : regmap_type := (12#210#,   4,      4,        1,        0,   readwrite); -- 4     Timer 1 Overflow
   constant IE_Timer_2                             : regmap_type := (12#210#,   5,      5,        1,        0,   readwrite); -- 5     Timer 2 Overflow
   constant IE_Timer_3                             : regmap_type := (12#210#,   6,      6,        1,        0,   readwrite); -- 6     Timer 3 Overflow
   constant IE_SIO_RCNT_RTC                        : regmap_type := (12#210#,   7,      7,        1,        0,   readwrite); -- 7     NDS7 only: SIO/RCNT/RTC (Real Time Clock)
   constant IE_DMA_0                               : regmap_type := (12#210#,   8,      8,        1,        0,   readwrite); -- 8     DMA 0
   constant IE_DMA_1                               : regmap_type := (12#210#,   9,      9,        1,        0,   readwrite); -- 9     DMA 1
   constant IE_DMA_2                               : regmap_type := (12#210#,  10,     10,        1,        0,   readwrite); -- 10    DMA 2
   constant IE_DMA_3                               : regmap_type := (12#210#,  11,     11,        1,        0,   readwrite); -- 11    DMA 3
   constant IE_Keypad                              : regmap_type := (12#210#,  12,     12,        1,        0,   readwrite); -- 12    Keypad
   constant IE_GBA_Slot_external_IRQ               : regmap_type := (12#210#,  13,     13,        1,        0,   readwrite); -- 13    GBA-Slot (external IRQ source)
   constant IE_IPC_Sync                            : regmap_type := (12#210#,  16,     16,        1,        0,   readwrite); -- 16    IPC Sync
   constant IE_IPC_Send_FIFO_Empty                 : regmap_type := (12#210#,  17,     17,        1,        0,   readwrite); -- 17    IPC Send FIFO Empty
   constant IE_IPC_Recv_FIFO_Not_Empty             : regmap_type := (12#210#,  18,     18,        1,        0,   readwrite); -- 18    IPC Recv FIFO Not Empty
   constant IE_NDS_Slot_Transfer_Complete          : regmap_type := (12#210#,  19,     19,        1,        0,   readwrite); -- 19    NDS-Slot Game Card Data Transfer Completion
   constant IE_NDS_Slot_IREQ_MC                    : regmap_type := (12#210#,  20,     20,        1,        0,   readwrite); -- 20    NDS-Slot Game Card IREQ_MC
   constant IE_Screens_unfolding                   : regmap_type := (12#210#,  22,     22,        1,        0,   writeonly); -- 22    NDS7 only: Screens unfolding
   constant IE_SPI_bus                             : regmap_type := (12#210#,  23,     23,        1,        0,   writeonly); -- 23    NDS7 only: SPI bus
   constant IE_Wifi                                : regmap_type := (12#210#,  24,     24,        1,        0,   writeonly); -- 24    NDS7 only: Wifi    / DSi9: XpertTeak DSP
                                       
   constant IF                                     : regmap_type := (12#214#,  31,     16,        1,        0,   writeonly); -- Interrupt Request Flags / IRQ Acknowledge
   constant IF_LCD_V_Blank                         : regmap_type := (12#210#,   0,      0,        1,        0,   readwrite); -- 0     LCD V-Blank
   constant IF_LCD_H_Blank                         : regmap_type := (12#210#,   1,      1,        1,        0,   readwrite); -- 1     LCD H-Blank
   constant IF_LCD_V_Counter_Match                 : regmap_type := (12#210#,   2,      2,        1,        0,   readwrite); -- 2     LCD V-Counter Match
   constant IF_Timer_0                             : regmap_type := (12#210#,   3,      3,        1,        0,   readwrite); -- 3     Timer 0 Overflow
   constant IF_Timer_1                             : regmap_type := (12#210#,   4,      4,        1,        0,   readwrite); -- 4     Timer 1 Overflow
   constant IF_Timer_2                             : regmap_type := (12#210#,   5,      5,        1,        0,   readwrite); -- 5     Timer 2 Overflow
   constant IF_Timer_3                             : regmap_type := (12#210#,   6,      6,        1,        0,   readwrite); -- 6     Timer 3 Overflow
   constant IF_SIO_RCNT_RTC                        : regmap_type := (12#210#,   7,      7,        1,        0,   readwrite); -- 7     NDS7 only: SIO/RCNT/RTC (Real Time Clock)
   constant IF_DMA_0                               : regmap_type := (12#210#,   8,      8,        1,        0,   readwrite); -- 8     DMA 0
   constant IF_DMA_1                               : regmap_type := (12#210#,   9,      9,        1,        0,   readwrite); -- 9     DMA 1
   constant IF_DMA_2                               : regmap_type := (12#210#,  10,     10,        1,        0,   readwrite); -- 10    DMA 2
   constant IF_DMA_3                               : regmap_type := (12#210#,  11,     11,        1,        0,   readwrite); -- 11    DMA 3
   constant IF_Keypad                              : regmap_type := (12#210#,  12,     12,        1,        0,   readwrite); -- 12    Keypad
   constant IF_GBA_Slot_external_IRQ               : regmap_type := (12#210#,  13,     13,        1,        0,   readwrite); -- 13    GBA-Slot (external IRQ source)
   constant IF_IPC_Sync                            : regmap_type := (12#210#,  16,     16,        1,        0,   readwrite); -- 16    IPC Sync
   constant IF_IPC_Send_FIFO_Empty                 : regmap_type := (12#210#,  17,     17,        1,        0,   readwrite); -- 17    IPC Send FIFO Empty
   constant IF_IPC_Recv_FIFO_Not_Empty             : regmap_type := (12#210#,  18,     18,        1,        0,   readwrite); -- 18    IPC Recv FIFO Not Empty
   constant IF_NDS_Slot_Transfer_Complete          : regmap_type := (12#210#,  19,     19,        1,        0,   readwrite); -- 19    NDS-Slot Game Card Data Transfer Completion
   constant IF_NDS_Slot_IREQ_MC                    : regmap_type := (12#210#,  20,     20,        1,        0,   readwrite); -- 20    NDS-Slot Game Card IREQ_MC
   constant IF_Screens_unfolding                   : regmap_type := (12#210#,  22,     22,        1,        0,   writeonly); -- 22    NDS7 only: Screens unfolding
   constant IF_SPI_bus                             : regmap_type := (12#210#,  23,     23,        1,        0,   writeonly); -- 23    NDS7 only: SPI bus
   constant IF_Wifi                                : regmap_type := (12#210#,  24,     24,        1,        0,   writeonly); -- 24    NDS7 only: Wifi    / DSi9: XpertTeak DSP
   
   
end package;