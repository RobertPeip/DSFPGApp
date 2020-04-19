#include "Gamecard.h"
#include "regs_arm9.h"
#include "regs_arm7.h"
#include "gameboy.h"
#include "DMA.h"
#include "Memory.h"
#include "Header.h"

GAMECARD Gamecard9;
GAMECARD Gamecard7;

void GAMECARD::reset(bool isArm9)
{
	this->isArm9 = isArm9;
	active = false;
	operation = 0;
	if (isArm9)
	{
		IRP = &IRP9;
		ROMCTRL_KEY1_gap1_length     = Regs_Arm9.Sect_system9.ROMCTRL_KEY1_gap1_length  ;
		ROMCTRL_KEY2_encrypt_data    = Regs_Arm9.Sect_system9.ROMCTRL_KEY2_encrypt_data ;
		ROMCTRL_SE				     = Regs_Arm9.Sect_system9.ROMCTRL_SE				  ;
		ROMCTRL_KEY2_Apply_Seed	     = Regs_Arm9.Sect_system9.ROMCTRL_KEY2_Apply_Seed	  ;
		ROMCTRL_KEY1_gap2_length     = Regs_Arm9.Sect_system9.ROMCTRL_KEY1_gap2_length  ;
		ROMCTRL_KEY2_encrypt_cmd     = Regs_Arm9.Sect_system9.ROMCTRL_KEY2_encrypt_cmd  ;
		ROMCTRL_Data_Word_Status     = Regs_Arm9.Sect_system9.ROMCTRL_Data_Word_Status  ;
		ROMCTRL_Data_Block_size	     = Regs_Arm9.Sect_system9.ROMCTRL_Data_Block_size	  ;
		ROMCTRL_Transfer_CLK_rate    = Regs_Arm9.Sect_system9.ROMCTRL_Transfer_CLK_rate ;
		ROMCTRL_KEY1_Gap_CLKs	     = Regs_Arm9.Sect_system9.ROMCTRL_KEY1_Gap_CLKs	  ;
		ROMCTRL_RESB_Release_Reset   = Regs_Arm9.Sect_system9.ROMCTRL_RESB_Release_Reset;
		ROMCTRL_WR				     = Regs_Arm9.Sect_system9.ROMCTRL_WR				  ;
		ROMCTRL_Block_Start_Status   = Regs_Arm9.Sect_system9.ROMCTRL_Block_Start_Status;
		Gamecard_bus_Command_1	     = Regs_Arm9.Sect_system9.Gamecard_bus_Command_1	  ;
		Gamecard_bus_Command_2	     = Regs_Arm9.Sect_system9.Gamecard_bus_Command_2	  ;
		Gamecard_bus_DataIn		     = Regs_Arm9.Sect_system9.Gamecard_bus_DataIn		  ;
		AUXSPICNT_Transfer_Ready_IRQ = Regs_Arm9.Sect_system9.AUXSPICNT_Transfer_Ready_IRQ;
	}
	else
	{
		IRP = &IRP7;
		ROMCTRL_KEY1_gap1_length     = Regs_Arm7.Sect_system7.ROMCTRL_KEY1_gap1_length  ;
		ROMCTRL_KEY2_encrypt_data    = Regs_Arm7.Sect_system7.ROMCTRL_KEY2_encrypt_data ;
		ROMCTRL_SE				     = Regs_Arm7.Sect_system7.ROMCTRL_SE				  ;
		ROMCTRL_KEY2_Apply_Seed	     = Regs_Arm7.Sect_system7.ROMCTRL_KEY2_Apply_Seed	  ;
		ROMCTRL_KEY1_gap2_length     = Regs_Arm7.Sect_system7.ROMCTRL_KEY1_gap2_length  ;
		ROMCTRL_KEY2_encrypt_cmd     = Regs_Arm7.Sect_system7.ROMCTRL_KEY2_encrypt_cmd  ;
		ROMCTRL_Data_Word_Status     = Regs_Arm7.Sect_system7.ROMCTRL_Data_Word_Status  ;
		ROMCTRL_Data_Block_size	     = Regs_Arm7.Sect_system7.ROMCTRL_Data_Block_size	  ;
		ROMCTRL_Transfer_CLK_rate    = Regs_Arm7.Sect_system7.ROMCTRL_Transfer_CLK_rate ;
		ROMCTRL_KEY1_Gap_CLKs	     = Regs_Arm7.Sect_system7.ROMCTRL_KEY1_Gap_CLKs	  ;
		ROMCTRL_RESB_Release_Reset   = Regs_Arm7.Sect_system7.ROMCTRL_RESB_Release_Reset;
		ROMCTRL_WR				     = Regs_Arm7.Sect_system7.ROMCTRL_WR				  ;
		ROMCTRL_Block_Start_Status   = Regs_Arm7.Sect_system7.ROMCTRL_Block_Start_Status;
		Gamecard_bus_Command_1	     = Regs_Arm7.Sect_system7.Gamecard_bus_Command_1	  ;
		Gamecard_bus_Command_2	     = Regs_Arm7.Sect_system7.Gamecard_bus_Command_2	  ;
		Gamecard_bus_DataIn		     = Regs_Arm7.Sect_system7.Gamecard_bus_DataIn		  ;
		AUXSPICNT_Transfer_Ready_IRQ = Regs_Arm7.Sect_system7.AUXSPICNT_Transfer_Ready_IRQ;
	}
}

void GAMECARD::writeControl()
{
	if (ROMCTRL_Block_Start_Status.on())
	{
		UInt32 cmd_dw1 = Gamecard_bus_Command_1.read();
		UInt32 cmd_dw2 = Gamecard_bus_Command_2.read();
		byte cmd_byte0 = (byte)cmd_dw1;
		byte cmd_byte1 = (byte)(cmd_dw1 >> 8);
		byte cmd_byte2 = (byte)(cmd_dw1 >> 16);
		byte cmd_byte3 = (byte)(cmd_dw1 >> 24);
		byte cmd_byte4 = (byte)cmd_dw2;
		if (cmd_byte0 == 0xB7)
		{
			address = cmd_byte4 | (cmd_byte3 << 8) | (cmd_byte2 << 16) | (cmd_byte1 << 24);
			length = 0x200;
			transfercount = 0x200;
			operation = cmd_byte0;
			active = true;
		}
		else if (cmd_byte0 == 0xB8)
		{
			length = 4;
			transfercount = 4;
			operation = cmd_byte0;
			active = true;
		}
		else
		{
			int a = 5;
		}

		UInt32 clockdiv = 5;
		if (ROMCTRL_Transfer_CLK_rate.on()) clockdiv = 8;
		UInt32 delay = (ROMCTRL_KEY1_gap1_length.read() + 8) * clockdiv; //time to send 8 command bytes, and then wait for the gap
		if (length > 0) //if data is to be returned, the first word is read before it's available and irqs and dmas fire
		{
			delay += 4;
		}
		delay *= 2; // 33->66mhz

		next_event_time = gameboy.totalticks + delay;
	}
	else
	{
		ROMCTRL_Block_Start_Status.write(0);
		ROMCTRL_Data_Word_Status.write(0);
		return;
	}
}

void GAMECARD::finish()
{
	if (gameboy.totalticks >= next_event_time)
	{
		active = false;
		ROMCTRL_Data_Word_Status.write(1);

		//triggerDma(EDMAMode_Card);
	}
}

UInt32 GAMECARD::readData()
{
	UInt32 retval = 0;

	if (operation == 0xB7)
	{
		if (address < 0x8000) //feature of retail carts : B7 "Can be used only for addresses 8000h and up, smaller addresses will be silently redirected to address `8000h+(addr AND 1FFh)`"
		{
			address = (0x8000 + (address & 0x1FF));
		}

		// todo: protect read after rom

		retval = *(UInt32*)&Memory.GameRom[address];
		address = (address & ~0xFFF) + ((address + 4) & 0xFFF); //"However, the datastream wraps to the begin of the current 4K block when address+length crosses a 4K boundary (1000h bytes)"
	}
	else if (operation == 0xB8)
	{
		retval = Header.chipID;
	}

	transfercount -= 4;
	if (transfercount <= 0)
	{
		ROMCTRL_Block_Start_Status.write(0);
		ROMCTRL_Data_Word_Status.write(0);
		if (AUXSPICNT_Transfer_Ready_IRQ.on())
		{
			IRP->set_irp_bit(IRP->IRPMASK_NDS_Slot_Transfer_Complete);
		}
	}

	return retval;
}