#pragma once

#include "types.h"
#include "DSReg.h"
#include "IRP.h"

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
	DSReg AUXSPICNT_Transfer_Ready_IRQ;

	void reset(bool isArm9);
	void writeControl();
	void finish();
	UInt32 readData();
};
extern GAMECARD Gamecard9;
extern GAMECARD Gamecard7;