#pragma once

#include "types.h"

enum class GPUState
{
	HSTART,
	HIRQ,
	VISIBLE,
	HBLANK,
	VBLANK_START,
	VBLANK_HIRQ,
	VBLANK_DRAWIDLE,
	VBLANKHBLANK
};

class GPUTiming
{
public:
	const int BITPOS_V_Blank_flag = 0;
	const int BITPOS_H_Blank_flag = 1;
	const int BITPOS_V_Counter_flag = 2;
	const int BITPOS_V_Blank_IRQ_Enable = 3;
	const int BITPOS_H_Blank_IRQ_Enable = 4;
	const int BITPOS_V_Counter_IRQ_Enable = 5;
	const int BITPOS_V_Count_Setting = 8;

	UInt64 localticks;
	UInt16 line;
	GPUState gpustate;

	UInt16 old_dispstat;

	UInt64 next_event_time;

	void reset();
	void dispstat_write();
	void work();
	void restart_line();

private:
	void nextline();
};
extern GPUTiming GPU_Timing;