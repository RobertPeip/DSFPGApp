#pragma once

#include "types.h"

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

	bool Master_enable;

	UInt16 IRP_Flags;
	UInt16 IE;

	void set_irp_bit(UInt16 mask);
	void update_IE();
	void clear_irp_bits();
	void update_IME(UInt16 value);
	UInt16 get_IF_with_mask();
};
extern Irp IRP;