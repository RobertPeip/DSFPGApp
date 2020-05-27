#pragma once

#include "types.h"
#include "CPU.h"
#include "DSReg.h"

class Irp
{
public:
	const int IRPMASK_LCD_V_Blank = 0x1;
	const int IRPMASK_LCD_H_Blank = 0x2;
	const int IRPMASK_LCD_V_Counter_Match = 0x4;
	const int IRPMASK_Timer_0 = 0x8;
	const int IRPMASK_Timer_1 = 0x10;
	const int IRPMASK_Timer_2 = 0x20;
	const int IRPMASK_Timer_3 = 0x40;
	const int IRPMASK_SIO_RCNT_RTC = 0x80; // NDS7 only : SIO / RCNT / RTC(Real Time Clock)
	const int IRPMASK_DMA_0 = 0x100;
	const int IRPMASK_DMA_1 = 0x200;
	const int IRPMASK_DMA_2 = 0x400;
	const int IRPMASK_DMA_3 = 0x800;
	const int IRPMASK_Keypad = 0x1000;
	const int IRPMASK_GBA_Game_Pak = 0x2000;
	const int IRPMASK_IPC_Sync = 0x10000;
	const int IRPMASK_IPC_Send_FIFO_Empty = 0x20000;
	const int IRPMASK_IPC_Recv_FIFO_Not_Empty = 0x40000;
	const int IRPMASK_NDS_Slot_Transfer_Complete = 0x80000;
	const int IRPMASK_NDS_Slot_IREQ_MC = 0x100000;
	const int IRPMASK_Geometry_Command_FIFO = 0x200000;
	const int IRPMASK_Screens_unfolding = 0x400000;
	const int IRPMASK_SPI_bus = 0x800000;
	const int IRPMASK_Wifi = 0x1000000;

	DSReg REG_IE;
	DSReg REG_IF;

	Cpu* CPU;

	bool Master_enable;

	UInt32 IRP_Flags;
	UInt32 IE;

	bool checknext;

	UInt32 next_mask;

	Irp();
	void reset(bool isArm9);
	void set_irp_bit(UInt32 mask, bool delay);
	void clear_irp_bit(UInt32 mask);
	void update_IE();
	void clear_irp_bits();
	void update_IME(UInt32 value);
	UInt32 get_IF_with_mask();
	void check_and_execute_irp();
	void check_gxfifobits();
};
extern Irp IRP9;
extern Irp IRP7;