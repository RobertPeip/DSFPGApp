library IEEE;
use IEEE.std_logic_1164.all;  
use IEEE.numeric_std.all;     

use work.pProc_bus_gb.all;
use work.pRegmap.all;

package pReg_ds_system_9 is

   -- range 0x180..
   --   (                                                            adr      upper    lower    size   default   accesstype)          
   constant IPCSYNC                                : regmap_type := (16#180#,  15,      0,        1,        0,   writeonly); -- IPC Synchronize Register (R/W)            
   constant IPCSYNC_Data_from_IPCSYNC              : regmap_type := (16#180#,   3,      0,        1,        0,   readonly ); -- 0-3   R    Data input from IPCSYNC Bit8-11 of remote CPU (00h..0Fh)
   constant IPCSYNC_Data_to_IPCSYNC                : regmap_type := (16#180#,  11,      8,        1,        0,   readwrite); -- 8-11  R/W  Data output to IPCSYNC Bit0-3 of remote CPU   (00h..0Fh)
   constant IPCSYNC_IRQ_to_remote_CPU              : regmap_type := (16#180#,  13,     13,        1,        0,   readonly ); -- 13    W    Send IRQ to remote CPU      (0=None, 1=Send IRQ)
   constant IPCSYNC_Ena_IRQ_from_remote_CPU        : regmap_type := (16#180#,  14,     14,        1,        0,   readwrite); -- 14    R/W  Enable IRQ from remote CPU  (0=Disable, 1=Enable)
                                                   
   constant IPCFIFOCNT                             : regmap_type := (16#184#,  15,      0,        1,        0,   writeonly); -- IPC Fifo Control Register (R/W)           
   constant IPCFIFOCNT_Send_Fifo_Empty_Status      : regmap_type := (16#184#,   0,      0,        1,        0,   readonly ); -- 0     R    Send Fifo Empty Status      (0=Not Empty, 1=Empty)
   constant IPCFIFOCNT_Send_Fifo_Full_Status       : regmap_type := (16#184#,   1,      1,        1,        0,   readonly ); -- 1     R    Send Fifo Full Status       (0=Not Full, 1=Full)
   constant IPCFIFOCNT_Send_Fifo_Empty_IRQ         : regmap_type := (16#184#,   2,      2,        1,        0,   readwrite); -- 2     R/W  Send Fifo Empty IRQ         (0=Disable, 1=Enable)
   constant IPCFIFOCNT_Send_Fifo_Clear             : regmap_type := (16#184#,   3,      3,        1,        0,   writeonly); -- 3     W    Send Fifo Clear             (0=Nothing, 1=Flush Send Fifo)
   constant IPCFIFOCNT_Receive_Fifo_Empty          : regmap_type := (16#184#,   8,      8,        1,        0,   readonly ); -- 8     R    Receive Fifo Empty          (0=Not Empty, 1=Empty)
   constant IPCFIFOCNT_Receive_Fifo_Full           : regmap_type := (16#184#,   9,      9,        1,        0,   readonly ); -- 9     R    Receive Fifo Full           (0=Not Full, 1=Full)
   constant IPCFIFOCNT_Receive_Fifo_Not_Empty_IRQ  : regmap_type := (16#184#,  10,     10,        1,        0,   readwrite); -- 10    R/W  Receive Fifo Not Empty IRQ  (0=Disable, 1=Enable)
   constant IPCFIFOCNT_Error_Read_Empty_Send_Full  : regmap_type := (16#184#,  14,     14,        1,        0,   readwrite); -- 14    R/W  Error, Read Empty/Send Full (0=No Error, 1=Error/Acknowledge)
   constant IPCFIFOCNT_Enable_Send_Receive_Fifo    : regmap_type := (16#184#,  15,     15,        1,        0,   readwrite); -- 15    R/W  Enable Send/Receive Fifo    (0=Disable, 1=Enable)

   constant IPCFIFOSEND                            : regmap_type := (16#188#,  31,      0,        1,        0,   writeonly); -- IPC Send Fifo (W) 
   -- relocate from 0xFFF to 0x100000!
   constant IPCFIFORECV                            : regmap_type := (16#FFF#,  31,      0,        1,        0,   readonly ); -- IPC Receive Fifo (R)      
   
   
   constant AUXSPICNT                              : regmap_type := (16#1A0#,  23,      0,        1,        0,   writeonly); -- Gamecard ROM and SPI Control           
   constant AUXSPICNT_SPI_Baudrate                 : regmap_type := (16#1A0#,   1,      0,        1,        0,   readwrite); -- 0-1   SPI Baudrate        (0=4MHz/Default, 1=2MHz, 2=1MHz, 3=512KHz)
   constant AUXSPICNT_SPI_Hold_Chipselect          : regmap_type := (16#1A0#,   6,      6,        1,        0,   readwrite); -- 6     SPI Hold Chipselect (0=Deselect after transfer, 1=Keep selected)
   constant AUXSPICNT_SPI_Busy                     : regmap_type := (16#1A0#,   7,      7,        1,        0,   readonly ); -- 7     SPI Busy            (0=Ready, 1=Busy) (presumably Read-only)
   constant AUXSPICNT_NDS_Slot_Mode                : regmap_type := (16#1A0#,  13,     13,        1,        0,   readwrite); -- 13    NDS Slot Mode       (0=Parallel/ROM, 1=Serial/SPI-Backup)
   constant AUXSPICNT_Transfer_Ready_IRQ           : regmap_type := (16#1A0#,  14,     14,        1,        0,   readwrite); -- 14    Transfer Ready IRQ  (0=Disable, 1=Enable) (for ROM, not for AUXSPI)
   constant AUXSPICNT_NDS_Slot_Enable              : regmap_type := (16#1A0#,  15,     15,        1,        0,   readwrite); -- 15    NDS Slot Enable     (0=Disable, 1=Enable) (for both ROM and AUXSPI)
   constant AUXSPIDATA                             : regmap_type := (16#1A0#,  23,     16,        1,        0,   readwrite); -- Gamecard SPI Bus Data/Strobe (R/W)         

   constant ROMCTRL                                : regmap_type := (16#1A4#,  31,      0,        1,        0,   writeonly); -- Gamecard Bus ROMCTRL (R/W)
   constant ROMCTRL_KEY1_gap1_length               : regmap_type := (16#1A4#,  12,      0,        1,        0,   readwrite); --  0-12  KEY1 gap1 length  (0-1FFFh) (forced min 08F8h by BIOS) (leading gap)
   constant ROMCTRL_KEY2_encrypt_data              : regmap_type := (16#1A4#,  13,     13,        1,        0,   readwrite); --  13    KEY2 encrypt data (0=Disable, 1=Enable KEY2 Encryption for Data)
   constant ROMCTRL_SE                             : regmap_type := (16#1A4#,  14,     14,        1,        0,   readwrite); --  14    SE Unknown? (usually same as Bit13) (does NOT affect timing?)
   constant ROMCTRL_KEY2_Apply_Seed                : regmap_type := (16#1A4#,  15,     15,        1,        0,   readwrite); --  15    KEY2 Apply Seed   (0=No change, 1=Apply Encryption Seed) (Write only)
   constant ROMCTRL_KEY1_gap2_length               : regmap_type := (16#1A4#,  21,     16,        1,        0,   readwrite); --  16-21 KEY1 gap2 length  (0-3Fh)   (forced min 18h by BIOS) (200h-byte gap)
   constant ROMCTRL_KEY2_encrypt_cmd               : regmap_type := (16#1A4#,  22,     22,        1,        0,   readwrite); --  22    KEY2 encrypt cmd  (0=Disable, 1=Enable KEY2 Encryption for Commands)
   constant ROMCTRL_Data_Word_Status               : regmap_type := (16#1A4#,  23,     23,        1,        0,   readwrite); --  23    Data-Word Status  (0=Busy, 1=Ready/DRQ) (Read-only)
   constant ROMCTRL_Data_Block_size                : regmap_type := (16#1A4#,  26,     24,        1,        0,   readwrite); --  24-26 Data Block size   (0=None, 1..6=100h SHL (1..6) bytes, 7=4 bytes)
   constant ROMCTRL_Transfer_CLK_rate              : regmap_type := (16#1A4#,  27,     27,        1,        0,   readwrite); --  27    Transfer CLK rate (0=6.7MHz=33.51MHz/5, 1=4.2MHz=33.51MHz/8)
   constant ROMCTRL_KEY1_Gap_CLKs                  : regmap_type := (16#1A4#,  28,     28,        1,        0,   readwrite); --  28    KEY1 Gap CLKs (0=Hold CLK High during gaps, 1=Output Dummy CLK Pulses)
   constant ROMCTRL_RESB_Release_Reset             : regmap_type := (16#1A4#,  29,     29,        1,        0,   readwrite); --  29    RESB Release Reset (0=Reset, 1=Release) (cannot be cleared once set)
   constant ROMCTRL_WR                             : regmap_type := (16#1A4#,  30,     30,        1,        0,   readwrite); --  30    WR   Unknown, maybe data-write? (usually 0) (read/write-able)
   constant ROMCTRL_Block_Start_Status             : regmap_type := (16#1A4#,  31,     31,        1,        0,   readwrite); --  31    Block Start/Status (0=Ready, 1=Start/Busy) (IRQ See 40001A0h/Bit14)
  
   constant Gamecard_bus_Command_1                 : regmap_type := (16#1A8#,  31,      0,        1,        0,   writeonly); -- Gamecard bus 8-byte Command Out
   constant Gamecard_bus_Command_2                 : regmap_type := (16#1AC#,  31,      0,        1,        0,   writeonly); -- Gamecard bus 8-byte Command Out
   -- relocate from 0xFFF to 0x100010!
   constant Gamecard_bus_DataIn                    : regmap_type := (16#FFF#,  31,      0,        1,        0,   readonly ); -- Gamecard bus 4-byte Data In (R)     
   
   constant Encryption_Seed_0_Lower                : regmap_type := (16#1B0#,  31,      0,        1,        0,   writeonly); -- Encryption Seed 0 Lower 32bit (W)
   constant Encryption_Seed_1_Lower                : regmap_type := (16#1B4#,  31,      0,        1,        0,   writeonly); -- Encryption Seed 1 Lower 32bit (W)
   constant Encryption_Seed_0_Upper                : regmap_type := (16#1B8#,   6,      0,        1,        0,   writeonly); -- Encryption Seed 0 Upper 7bit (bit7-15 unused)
   constant Encryption_Seed_1_Upper                : regmap_type := (16#1B8#,  22,     16,        1,        0,   writeonly); -- Encryption Seed 1 Upper 7bit (bit7-15 unused)
   
   
   constant EXMEMCNT                               : regmap_type := (16#204#,  25,      0,        1,        0,   readwrite); -- External Memory Control (R/W)
   constant EXMEMCNT_GBASlot_SRAM_Access_Time      : regmap_type := (16#204#,   1,      0,        1,        0,   readwrite); -- 0-1   32-pin GBA Slot SRAM Access Time    (0-3 = 10, 8, 6, 18 cycles)
   constant EXMEMCNT_GBASlot_ROM_1st_Access_Time   : regmap_type := (16#204#,   3,      2,        1,        0,   readwrite); -- 2-3   32-pin GBA Slot ROM 1st Access Time (0-3 = 10, 8, 6, 18 cycles)
   constant EXMEMCNT_GBASlot_ROM_2nd_Access_Time   : regmap_type := (16#204#,   4,      4,        1,        0,   readwrite); -- 4     32-pin GBA Slot ROM 2nd Access Time (0-1 = 6, 4 cycles)
   constant EXMEMCNT_GBASlot_PHI_pin_out           : regmap_type := (16#204#,   6,      5,        1,        0,   readwrite); -- 5-6   32-pin GBA Slot PHI-pin out   (0-3 = Low, 4.19MHz, 8.38MHz, 16.76MHz)
   constant EXMEMCNT_GBASlot_Access_Rights         : regmap_type := (16#204#,   7,      7,        1,        0,   readwrite); -- 7     32-pin GBA Slot Access Rights     (0=ARM9, 1=ARM7)
   constant EXMEMCNT_NDSSlot_Access_Rights         : regmap_type := (16#204#,  11,     11,        1,        0,   readwrite); -- 11    17-pin NDS Slot Access Rights     (0=ARM9, 1=ARM7)
   constant EXMEMCNT_SET                           : regmap_type := (16#204#,  13,     13,        1,        0,   readwrite); -- 13    NDS:Always set?  ;set/tested by DSi bootcode: Main RAM enable, CE2 pin?
   constant EXMEMCNT_MainMem_Interface_Mode        : regmap_type := (16#204#,  14,     14,        1,        0,   readonly ); -- 14    Main Memory Interface Mode Switch (0=Async/GBA/Reserved, 1=Synchronous)
   constant EXMEMCNT_MainMem_Access_Priority       : regmap_type := (16#204#,  15,     15,        1,        0,   readwrite); -- 15    Main Memory Access Priority       (0=ARM9 Priority, 1=ARM7 Priority)   
   
   
   constant IME                                    : regmap_type := (16#208#,  31,      0,        1,        0,   readwrite); -- Interrupt Master Enable Register  
         
   constant IE                                     : regmap_type := (16#210#,  31,      0,        1,        0,   writeonly); -- Interrupt Enable              
   constant IE_LCD_V_Blank                         : regmap_type := (16#210#,   0,      0,        1,        0,   readwrite); -- 0     LCD V-Blank
   constant IE_LCD_H_Blank                         : regmap_type := (16#210#,   1,      1,        1,        0,   readwrite); -- 1     LCD H-Blank
   constant IE_LCD_V_Counter_Match                 : regmap_type := (16#210#,   2,      2,        1,        0,   readwrite); -- 2     LCD V-Counter Match
   constant IE_Timer_0                             : regmap_type := (16#210#,   3,      3,        1,        0,   readwrite); -- 3     Timer 0 Overflow
   constant IE_Timer_1                             : regmap_type := (16#210#,   4,      4,        1,        0,   readwrite); -- 4     Timer 1 Overflow
   constant IE_Timer_2                             : regmap_type := (16#210#,   5,      5,        1,        0,   readwrite); -- 5     Timer 2 Overflow
   constant IE_Timer_3                             : regmap_type := (16#210#,   6,      6,        1,        0,   readwrite); -- 6     Timer 3 Overflow
   constant IE_DMA_0                               : regmap_type := (16#210#,   8,      8,        1,        0,   readwrite); -- 8     DMA 0
   constant IE_DMA_1                               : regmap_type := (16#210#,   9,      9,        1,        0,   readwrite); -- 9     DMA 1
   constant IE_DMA_2                               : regmap_type := (16#210#,  10,     10,        1,        0,   readwrite); -- 10    DMA 2
   constant IE_DMA_3                               : regmap_type := (16#210#,  11,     11,        1,        0,   readwrite); -- 11    DMA 3
   constant IE_Keypad                              : regmap_type := (16#210#,  12,     12,        1,        0,   readwrite); -- 12    Keypad
   constant IE_GBA_Slot_external_IRQ               : regmap_type := (16#210#,  13,     13,        1,        0,   readwrite); -- 13    GBA-Slot (external IRQ source)
   constant IE_IPC_Sync                            : regmap_type := (16#210#,  16,     16,        1,        0,   readwrite); -- 16    IPC Sync
   constant IE_IPC_Send_FIFO_Empty                 : regmap_type := (16#210#,  17,     17,        1,        0,   readwrite); -- 17    IPC Send FIFO Empty
   constant IE_IPC_Recv_FIFO_Not_Empty             : regmap_type := (16#210#,  18,     18,        1,        0,   readwrite); -- 18    IPC Recv FIFO Not Empty
   constant IE_NDS_Slot_Transfer_Complete          : regmap_type := (16#210#,  19,     19,        1,        0,   readwrite); -- 19    NDS-Slot Game Card Data Transfer Completion
   constant IE_NDS_Slot_IREQ_MC                    : regmap_type := (16#210#,  20,     20,        1,        0,   readwrite); -- 20    NDS-Slot Game Card IREQ_MC
   constant IE_Geometry_Command_FIFO               : regmap_type := (16#210#,  21,     21,        1,        0,   readwrite); -- 21    NDS9 only: Geometry Command FIFO
   constant IE_unused                              : regmap_type := (16#210#,  31,     22,        1,        0,   readwrite); -- 22-31 unused
                                       
   constant IF                                     : regmap_type := (16#214#,  21,      0,        1,        0,   writeonly); -- Interrupt Request Flags / IRQ Acknowledge
   constant IF_LCD_V_Blank                         : regmap_type := (16#214#,   0,      0,        1,        0,   readwrite); -- 0     LCD V-Blank
   constant IF_LCD_H_Blank                         : regmap_type := (16#214#,   1,      1,        1,        0,   readwrite); -- 1     LCD H-Blank
   constant IF_LCD_V_Counter_Match                 : regmap_type := (16#214#,   2,      2,        1,        0,   readwrite); -- 2     LCD V-Counter Match
   constant IF_Timer_0                             : regmap_type := (16#214#,   3,      3,        1,        0,   readwrite); -- 3     Timer 0 Overflow
   constant IF_Timer_1                             : regmap_type := (16#214#,   4,      4,        1,        0,   readwrite); -- 4     Timer 1 Overflow
   constant IF_Timer_2                             : regmap_type := (16#214#,   5,      5,        1,        0,   readwrite); -- 5     Timer 2 Overflow
   constant IF_Timer_3                             : regmap_type := (16#214#,   6,      6,        1,        0,   readwrite); -- 6     Timer 3 Overflow
   constant IF_DMA_0                               : regmap_type := (16#214#,   8,      8,        1,        0,   readwrite); -- 8     DMA 0
   constant IF_DMA_1                               : regmap_type := (16#214#,   9,      9,        1,        0,   readwrite); -- 9     DMA 1
   constant IF_DMA_2                               : regmap_type := (16#214#,  10,     10,        1,        0,   readwrite); -- 10    DMA 2
   constant IF_DMA_3                               : regmap_type := (16#214#,  11,     11,        1,        0,   readwrite); -- 11    DMA 3
   constant IF_Keypad                              : regmap_type := (16#214#,  12,     12,        1,        0,   readwrite); -- 12    Keypad
   constant IF_GBA_Slot_external_IRQ               : regmap_type := (16#214#,  13,     13,        1,        0,   readwrite); -- 13    GBA-Slot (external IRQ source)
   constant IF_IPC_Sync                            : regmap_type := (16#214#,  16,     16,        1,        0,   readwrite); -- 16    IPC Sync
   constant IF_IPC_Send_FIFO_Empty                 : regmap_type := (16#214#,  17,     17,        1,        0,   readwrite); -- 17    IPC Send FIFO Empty
   constant IF_IPC_Recv_FIFO_Not_Empty             : regmap_type := (16#214#,  18,     18,        1,        0,   readwrite); -- 18    IPC Recv FIFO Not Empty
   constant IF_NDS_Slot_Transfer_Complete          : regmap_type := (16#214#,  19,     19,        1,        0,   readwrite); -- 19    NDS-Slot Game Card Data Transfer Completion
   constant IF_NDS_Slot_IREQ_MC                    : regmap_type := (16#214#,  20,     20,        1,        0,   readwrite); -- 20    NDS-Slot Game Card IREQ_MC
   constant IF_Geometry_Command_FIFO               : regmap_type := (16#214#,  21,     21,        1,        0,   readwrite); -- 21    NDS9 only: Geometry Command FIFO
         
         
   constant MemControl1                            : regmap_type := (16#240#,  31,      0,        1,        0,   writeonly); -- 
   constant MemControl1_VRAM_A_MST                 : regmap_type := (16#240#,   1,      0,        1,        0,   readwrite); -- Bit2 not used by VRAM-A,B,H,I
   constant MemControl1_VRAM_A_Offset              : regmap_type := (16#240#,   4,      3,        1,        0,   readwrite); -- Offset not used by VRAM-E,H,I
   constant MemControl1_VRAM_A_Enable              : regmap_type := (16#240#,   7,      7,        1,        0,   readwrite); -- (0=Disable, 1=Enable)
   constant MemControl1_VRAM_B_MST                 : regmap_type := (16#240#,   9,      8,        1,        0,   readwrite); -- 
   constant MemControl1_VRAM_B_Offset              : regmap_type := (16#240#,  12,     11,        1,        0,   readwrite); -- 
   constant MemControl1_VRAM_B_Enable              : regmap_type := (16#240#,  15,     15,        1,        0,   readwrite); -- 
   constant MemControl1_VRAM_C_MST                 : regmap_type := (16#240#,  18,     16,        1,        0,   readwrite); -- 
   constant MemControl1_VRAM_C_Offset              : regmap_type := (16#240#,  20,     19,        1,        0,   readwrite); -- 
   constant MemControl1_VRAM_C_Enable              : regmap_type := (16#240#,  23,     23,        1,        0,   readwrite); -- 
   constant MemControl1_VRAM_D_MST                 : regmap_type := (16#240#,  26,     24,        1,        0,   readwrite); -- 
   constant MemControl1_VRAM_D_Offset              : regmap_type := (16#240#,  28,     27,        1,        0,   readwrite); -- 
   constant MemControl1_VRAM_D_Enable              : regmap_type := (16#240#,  31,     31,        1,        0,   readwrite); --  
 
   constant MemControl2                            : regmap_type := (16#244#,  25,      0,        1,        0,   writeonly); -- 
   constant MemControl2_VRAM_E_MST                 : regmap_type := (16#244#,   2,      0,        1,        0,   readwrite); -- Bit2 not used by VRAM-A,B,H,I
   constant MemControl2_VRAM_E_Offset              : regmap_type := (16#244#,   4,      3,        1,        0,   readwrite); -- Offset not used by VRAM-E,H,I
   constant MemControl2_VRAM_E_Enable              : regmap_type := (16#244#,   7,      7,        1,        0,   readwrite); -- (0=Disable, 1=Enable)
   constant MemControl2_VRAM_F_MST                 : regmap_type := (16#244#,  10,      8,        1,        0,   readwrite); -- 
   constant MemControl2_VRAM_F_Offset              : regmap_type := (16#244#,  12,     11,        1,        0,   readwrite); -- 
   constant MemControl2_VRAM_F_Enable              : regmap_type := (16#244#,  15,     15,        1,        0,   readwrite); -- 
   constant MemControl2_VRAM_G_MST                 : regmap_type := (16#244#,  18,     16,        1,        0,   readwrite); -- 
   constant MemControl2_VRAM_G_Offset              : regmap_type := (16#244#,  20,     19,        1,        0,   readwrite); -- 
   constant MemControl2_VRAM_G_Enable              : regmap_type := (16#244#,  23,     23,        1,        0,   readwrite); -- 
   constant MemControl2_WRAM                       : regmap_type := (16#244#,  25,     24,        1,        3,   readwrite); -- (0-3 = 32K/0K, 2nd 16K/1st 16K, 1st 16K/2nd 16K, 0K/32K)

   constant MemControl3                            : regmap_type := (16#248#,  15,      0,        1,        0,   writeonly); -- 
   constant MemControl3_VRAM_H_MST                 : regmap_type := (16#248#,   1,      0,        1,        0,   readwrite); -- Bit2 not used by VRAM-A,B,H,I
   constant MemControl3_VRAM_H_Offset              : regmap_type := (16#248#,   4,      3,        1,        0,   readwrite); -- Offset not used by VRAM-E,H,I
   constant MemControl3_VRAM_H_Enable              : regmap_type := (16#248#,   7,      7,        1,        0,   readwrite); -- (0=Disable, 1=Enable)
   constant MemControl3_VRAM_I_MST                 : regmap_type := (16#248#,   9,      8,        1,        0,   readwrite); -- 
   constant MemControl3_VRAM_I_Offset              : regmap_type := (16#248#,  12,     11,        1,        0,   readwrite); -- 
   constant MemControl3_VRAM_I_Enable              : regmap_type := (16#248#,  15,     15,        1,        0,   readwrite); --  

    
   constant DIVCNT                                 : regmap_type := (16#280#,  31,      0,        1,        0,   writeonly); -- Division Control (R/W)             
   constant DIVCNT_Division_Mode                   : regmap_type := (16#280#,   1,      0,        1,        0,   readwrite); -- 0-1   Division Mode    (0-2=See below) (3=Reserved; same as Mode 1)
   constant DIVCNT_Division_by_zero                : regmap_type := (16#280#,  14,     14,        1,        0,   readonly ); -- 14    Division by zero (0=Okay, 1=Division by zero error; 64bit Denom=0)
   constant DIVCNT_Busy                            : regmap_type := (16#280#,  15,     15,        1,        0,   readonly ); -- 15    Busy             (0=Ready, 1=Busy) (Execution time see below)
   constant DIV_NUMER_Low                          : regmap_type := (16#290#,  31,      0,        1,        0,   readwrite); -- 64bit Division Numerator (R/W)           
   constant DIV_NUMER_High                         : regmap_type := (16#294#,  31,      0,        1,        0,   readwrite); -- 64bit Division Numerator (R/W)      
   constant DIV_DENOM_Low                          : regmap_type := (16#298#,  31,      0,        1,        0,   readwrite); -- 64bit Division Denominator (R/W)   
   constant DIV_DENOM_High                         : regmap_type := (16#29C#,  31,      0,        1,        0,   readwrite); -- 64bit Division Denominator (R/W)     
   constant DIV_RESULT_Low                         : regmap_type := (16#2A0#,  31,      0,        1,        0,   readonly ); -- 64bit Division Quotient (=Numer/Denom) (R)
   constant DIV_RESULT_High                        : regmap_type := (16#2A4#,  31,      0,        1,        0,   readonly ); -- 64bit Division Quotient (=Numer/Denom) (R)
   constant DIVREM_RESULT_Low                      : regmap_type := (16#2A8#,  31,      0,        1,        0,   readonly ); -- 64bit Remainder (=Numer MOD Denom) (R)
   constant DIVREM_RESULT_High                     : regmap_type := (16#2AC#,  31,      0,        1,        0,   readonly ); -- 64bit Remainder (=Numer MOD Denom) (R)
         
   constant SQRTCN                                 : regmap_type := (16#2B0#,  31,      0,        1,        0,   writeonly); -- Square Root Control (R/W)      
   constant SQRTCN_Mode                            : regmap_type := (16#2B0#,   0,      0,        1,        0,   readwrite); -- 0     Mode (0=32bit input, 1=64bit input)
   constant SQRTCN_Busy                            : regmap_type := (16#2B0#,  15,     15,        1,        0,   readonly ); -- 15    Busy (0=Ready, 1=Busy) (Execution time is 13 clks, in either Mode)
   constant SQRT_RESULT                            : regmap_type := (16#2B4#,  31,      0,        1,        0,   readonly ); -- Square Root Result (R)       
   constant SQRT_PARAM_Low                         : regmap_type := (16#2B8#,  31,      0,        1,        0,   readwrite); -- Square Root Parameter Input (R/W)          
   constant SQRT_PARAM_High                        : regmap_type := (16#2BC#,  31,      0,        1,        0,   readwrite); -- Square Root Parameter Input (R/W)    
   
   
   constant POSTFLG                                : regmap_type := (16#300#,   1,      0,        1,        0,   writeonly); -- Post Boot Flag (R/W)    
   constant POSTFLG_Flag                           : regmap_type := (16#300#,   0,      0,        1,        1,   readonly ); -- Post Boot Flag (0=Boot in progress, 1=Boot completed)
   constant POSTFLG_RW                             : regmap_type := (16#300#,   1,      1,        1,        0,   readwrite); -- Bit1 is read-writeable   
   
   
   constant POWCNT1                                : regmap_type := (16#304#,  15,      0,        1,    33295,   writeonly); -- Graphics Power Control Register (R/W) - default all available bits set
   constant POWCNT1_Enable_Flag_for_both_LCDs      : regmap_type := (16#304#,   0,      0,        1,        0,   readwrite); -- 0     Enable Flag for both LCDs (0=Disable) (Prohibited, see notes)          
   constant POWCNT1_2D_Graphics_Engine_A           : regmap_type := (16#304#,   1,      1,        1,        0,   readwrite); -- 1     2D Graphics Engine A      (0=Disable) (Ports 008h-05Fh, Pal 5000000h)          
   constant POWCNT1_3D_Rendering_Engine            : regmap_type := (16#304#,   2,      2,        1,        0,   readwrite); -- 2     3D Rendering Engine       (0=Disable) (Ports 320h-3FFh)          
   constant POWCNT1_3D_Geometry_Engine             : regmap_type := (16#304#,   3,      3,        1,        0,   readwrite); -- 3     3D Geometry Engine        (0=Disable) (Ports 400h-6FFh)          
   constant POWCNT1_2D_Graphics_Engine_B           : regmap_type := (16#304#,   9,      9,        1,        0,   readwrite); -- 9     2D Graphics Engine B      (0=Disable) (Ports 1008h-105Fh, Pal 5000400h)          
   constant POWCNT1_Display_Swap                   : regmap_type := (16#304#,  15,     15,        1,        0,   readwrite); -- 15    Display Swap (0=Send Display A to Lower Screen, 1=To Upper Screen)          
   

end package;