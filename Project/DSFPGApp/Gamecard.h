#pragma once

#include "types.h"
#include "DSReg.h"
#include "IRP.h"

enum class AUXSPICMD
{
	IDLE	     =	0x00,
	AUTODETECT	 =	0xFF,
	WRITESTATUS	 =	0x01,
	WRITELOW	 =	0x02,
	READLOW		 =	0x03,
	WRITEDISABLE =	0x04,
	READSTATUS	 =	0x05,
	WRITEENABLE	 =	0x06,
	WRITEHIGH	 =	0x0A,
	READHIGH	 =	0x0B,
	IRDA		 =	0x08,
	PAGE_WRITE	 =	0x0A,
	PAGE_ERASE	 =	0xDB,
	SECTOR_ERASE =	0xD8,
	CHIP_ERASE	 =	0xC7
 //CARDFLASH_READ_BYTES_FAST	0x0B    /* Not used*/
 //CARDFLASH_DEEP_POWDOWN		0xB9    /* Not used*/
 //CARDFLASH_WAKEUP			0xAB    /* Not used*/
};

class GAMECARD
{
public:
	bool isArm9;

	bool active;
	UInt64 next_event_time;

	UInt32 address;
	UInt32 length;
	int transfercount;
	byte operation;

	Irp* IRP;

	UInt16 spi_oldcnt;
	bool csOld;

	bool auxspi_reset;
	AUXSPICMD cmd;
	bool write_enable;
	byte write_protect;
    UInt32 addr_size;
	UInt32 addr_counter;
	UInt32 addr;
	bool autodetect;
	int autodetectsize;

	int accessindex = 0;

	DSReg ROMCTRL_KEY1_gap1_length;
	DSReg ROMCTRL_KEY2_encrypt_data;
	DSReg ROMCTRL_SE;
	DSReg ROMCTRL_KEY2_Apply_Seed;
	DSReg ROMCTRL_KEY1_gap2_length;
	DSReg ROMCTRL_KEY2_encrypt_cmd;
	DSReg ROMCTRL_Data_Word_Status;
	DSReg ROMCTRL_Data_Block_size;
	DSReg ROMCTRL_Transfer_CLK_rate;
	DSReg ROMCTRL_KEY1_Gap_CLKs;
	DSReg ROMCTRL_RESB_Release_Reset;
	DSReg ROMCTRL_WR;
	DSReg ROMCTRL_Block_Start_Status;
	DSReg Gamecard_bus_Command_1;
	DSReg Gamecard_bus_Command_2;
	DSReg Gamecard_bus_DataIn;

	DSReg AUXSPICNT_SPI_Baudrate;
	DSReg AUXSPICNT_SPI_Hold_Chipselect;
	DSReg AUXSPICNT_SPI_Busy;
	DSReg AUXSPICNT_NDS_Slot_Mode;
	DSReg AUXSPICNT_Transfer_Ready_IRQ;
	DSReg AUXSPICNT_NDS_Slot_Enable;
	DSReg AUXSPIDATA;

	void reset(bool isArm9);
	void writeControl();
	void finish();
	UInt32 readData();

	void write_spi_cnt(UInt16 value);
	void write_spi_dat(byte value);
};
extern GAMECARD Gamecard9;
extern GAMECARD Gamecard7;