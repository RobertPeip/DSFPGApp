#include "Gamecard.h"
#include "regs_arm9.h"
#include "regs_arm7.h"
#include "gameboy.h"
#include "DMA.h"
#include "Memory.h"
#include "Header.h"
#include "DMA.h"

GAMECARD Gamecard9;
GAMECARD Gamecard7;

void GAMECARD::reset(bool isArm9)
{
	this->isArm9 = isArm9;
	active = false;
	operation = 0;
	spi_oldcnt = 0;
	csOld = false;
	auxspi_reset = false;
	cmd = AUXSPICMD::IDLE;
	write_enable = false;
	write_protect = 0;
	addr_size = 0;
	addr_counter = 0;
	addr = 0;
	autodetect = true;
	autodetectsize = 0;
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

		AUXSPICNT_SPI_Baudrate        = Regs_Arm9.Sect_system9.AUXSPICNT_SPI_Baudrate;
		AUXSPICNT_SPI_Hold_Chipselect = Regs_Arm9.Sect_system9.AUXSPICNT_SPI_Hold_Chipselect;
		AUXSPICNT_SPI_Busy            = Regs_Arm9.Sect_system9.AUXSPICNT_SPI_Busy;
		AUXSPICNT_NDS_Slot_Mode       = Regs_Arm9.Sect_system9.AUXSPICNT_NDS_Slot_Mode;
		AUXSPICNT_Transfer_Ready_IRQ  = Regs_Arm9.Sect_system9.AUXSPICNT_Transfer_Ready_IRQ;
	    AUXSPICNT_NDS_Slot_Enable     = Regs_Arm9.Sect_system9.AUXSPICNT_NDS_Slot_Enable;
		AUXSPIDATA                    = Regs_Arm9.Sect_system9.AUXSPIDATA;
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

		AUXSPICNT_SPI_Baudrate        = Regs_Arm7.Sect_system7.AUXSPICNT_SPI_Baudrate;
		AUXSPICNT_SPI_Hold_Chipselect = Regs_Arm7.Sect_system7.AUXSPICNT_SPI_Hold_Chipselect;
		AUXSPICNT_SPI_Busy            = Regs_Arm7.Sect_system7.AUXSPICNT_SPI_Busy;
		AUXSPICNT_NDS_Slot_Mode       = Regs_Arm7.Sect_system7.AUXSPICNT_NDS_Slot_Mode;
		AUXSPICNT_Transfer_Ready_IRQ  = Regs_Arm7.Sect_system7.AUXSPICNT_Transfer_Ready_IRQ;
	    AUXSPICNT_NDS_Slot_Enable     = Regs_Arm7.Sect_system7.AUXSPICNT_NDS_Slot_Enable;
		AUXSPIDATA                    = Regs_Arm7.Sect_system7.AUXSPIDATA;
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
		gameboy.reschedule = true;
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

		DMA.request_cardtransfer(transfercount / 4);
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
			IRP->set_irp_bit(IRP->IRPMASK_NDS_Slot_Transfer_Complete, false);
		}
	}

	return retval;
}

void GAMECARD::write_spi_cnt(UInt16 value)
{
	bool cs = AUXSPICNT_SPI_Hold_Chipselect.on();
	if ((!cs && csOld) || (AUXSPICNT_NDS_Slot_Mode.on() && (spi_oldcnt == 0) && !cs))
	{
		auxspi_reset = true;
	}

	csOld = AUXSPICNT_SPI_Hold_Chipselect.on();
	spi_oldcnt = value;
}

void GAMECARD::write_spi_dat(byte value)
{
	switch (cmd)
	{
	case AUXSPICMD::WRITESTATUS: write_protect = value & 0xFC; break;

	case AUXSPICMD::WRITELOW:
	case AUXSPICMD::READLOW:
		if (autodetect)
		{
			autodetectsize++;
			value = 0xFF;
			if (auxspi_reset)
			{
				switch (autodetectsize)
				{
				case 0:
				case 1:
					addr_size = 1;
					break;

				case 2: addr_size = 1; break;
				case 3: addr_size = 2; break;
				case 4: addr_size = 3; break;

				default: addr_size = autodetectsize & 3; break;
				}
				autodetect = false;
				autodetectsize = 0;
			}
		}
		else
		{
			if (addr_counter < addr_size)
			{
				addr <<= 8;
				addr |= value;
				addr_counter++;
				value = 0xFF;
			}
			else
			{
				//why does tomb raider underworld access 0x180 and go clear through to 0x280?
				//should this wrap around at 0 or at 0x100?
				//TODO - dont other backup memory types have similar wraparound issues?
				if (addr_size == 1)
				{
					addr &= 0x1FF;
				}

				if (cmd == AUXSPICMD::READLOW)
				{
					value = Memory.SaveRam[addr];
				}
				else
				{
					if (write_enable)
					{
						Memory.SaveRam[addr] = value;
					}
				}
				addr++;
			}
		}
		break;

	case AUXSPICMD::READSTATUS:
		value = write_protect;
		if (write_enable) value |= 2;
		break;

	case AUXSPICMD::IRDA: value = 0xAA; break;

	default:
		if (cmd != AUXSPICMD::IDLE) break; // emergency exit
		cmd = (AUXSPICMD)value;
		value = 0xFF;
		switch (cmd)
		{
		case AUXSPICMD::IRDA: value = 0xAA; break;
		case AUXSPICMD::WRITEDISABLE: write_enable = false; break;
		case AUXSPICMD::WRITEENABLE: write_enable = true; break;

		case AUXSPICMD::WRITELOW:
		case AUXSPICMD::READLOW:
			addr_counter = 0;
			addr = 0;
			break;

		case AUXSPICMD::WRITEHIGH:
		case AUXSPICMD::READHIGH:
			if (cmd == AUXSPICMD::WRITEHIGH) cmd = AUXSPICMD::WRITELOW;
			if (cmd == AUXSPICMD::READHIGH) cmd = AUXSPICMD::READLOW;
			addr_counter = 0;
			addr = 0;
			if (addr_size == 1) addr = 1; // due to 256byte space or bugs in games (e.g. pokemon diamond?)
			break;
		}
		break;
	}

	if (auxspi_reset)
	{
		if (cmd == AUXSPICMD::WRITELOW || cmd == AUXSPICMD::WRITEHIGH)
		{
			//flush? -> probably close file -> write ended?
		}
		cmd = AUXSPICMD::IDLE;
		auxspi_reset = false;
	}

	AUXSPIDATA.write(value);
}