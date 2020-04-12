#pragma once
#include <queue>
using namespace std;

#include "types.h"
#include "regs_arm7.h"

class SingleSoundDMA
{
public:
	DSReg Enable_RIGHT;
	DSReg Enable_LEFT;
	DSReg Timer_Select;
	DSReg Reset_FIFO;

	byte timerindex;
	std::queue<byte> fifo;
	bool any_on;

	std::queue<byte> outfifo;
	int tickcount;

	SingleSoundDMA();
	SingleSoundDMA(DSReg Enable_RIGHT, DSReg Enable_LEFT, DSReg Timer_Select, DSReg Reset_FIFO);

	void work();
};

class SOUNDDMA
{
public:
	SingleSoundDMA soundDMAs[2];

	void reset();
	void timer_overflow(uint timerindex);
	void fill_fifo(int index, UInt32 value, bool dwaccess);
};
extern SOUNDDMA SoundDMA;