#pragma once

#include "types.h"
#include "regs_arm9.h"
#include "regs_arm7.h"

class SingleTimer
{
public:
	UInt16 irpmask;

	DSReg CNT_L;
	DSReg Prescaler;
	DSReg Count_up;
	DSReg Timer_IRQ_Enable;
	DSReg Timer_Start_Stop;

	Int32 value;
	Int32 prescalevalue;
	Int32 reload;
	bool on;
	bool startnow;
	bool stopnow;
	bool irp_on;
	bool countup;
	int prescale;

	UInt16 retval;

	SingleTimer();
	SingleTimer(UInt16 irpmask, DSReg CNT_L, DSReg Prescaler, DSReg Count_up, DSReg Timer_IRQ_Enable, DSReg Timer_Start_Stop);
};

class TIMER
{
public:
	SingleTimer timers[4];

	void reset();
	void set_reload(int index);
	void set_settings(int index);
	void work();
};
extern TIMER Timer;