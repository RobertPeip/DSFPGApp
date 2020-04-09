#pragma once

#include "types.h"
#include "regs_arm9.h"
#include "regs_arm7.h"
#include "CPU.h"

class SingleDMA
{
public:
    Cpu* CPU;

	UInt16 irpmask;

	DSReg SAD;
	DSReg DAD;
	DSReg CNT_L;

	DSReg Dest_Addr_Control;
	DSReg Source_Adr_Control;
	DSReg DMA_Repeat;
	DSReg DMA_Transfer_Type;
	DSReg Game_Pak_DRQ;
	DSReg DMA_Start_Timing;
	DSReg IRQ_on;
	DSReg DMA_Enable;

	bool hasDRQ = false;

	byte dest_Addr_Control;
	byte source_Adr_Control;
	bool dMA_Repeat;
	bool dMA_Transfer_Type;
	bool game_Pak_DRQ;
	byte dMA_Start_Timing;
	bool iRQ_on;
	bool dMA_Enable;

	bool running;
	bool waiting;
	bool finished;
	bool first;
	UInt32 addr_source;
	UInt32 addr_target;
	UInt32 count;
	UInt32 fullcount;
	int waitTicks;
	bool skipdebugout;
	UInt64 next_event_time;

	SingleDMA();
	SingleDMA(Cpu* CPU, UInt16 irpmask,
		DSReg SAD, DSReg DAD, DSReg CNT_L,
		DSReg Dest_Addr_Control, DSReg Source_Adr_Control, DSReg DMA_Repeat, DSReg DMA_Transfer_Type,
		DSReg Game_Pak_DRQ, DSReg DMA_Start_Timing, DSReg IRQ_on, DSReg DMA_Enable, bool hasDRQ);
};

class Dma
{
public:
	SingleDMA DMAs[8];

	bool dma_active = false;
	bool delayed = false;

	UInt32 debug_dmatranfers = 0;
	int cpuDmaCount = 0;

	bool new_hblank = false;
	bool new_vblank = false;

	UInt32 last_dma_value = 0;
	int last_dma_index= 0;

	void reset();
	void set_settings(int index);
	void check_run(int index);
	void work();
	void request_audio(uint audioindex);
};
extern Dma DMA;