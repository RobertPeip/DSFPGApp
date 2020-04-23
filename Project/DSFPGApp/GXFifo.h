#pragma once
#include <queue>

#include "types.h"


class GXFIFO
{
public:
	std::queue<UInt64> fifo;

	bool lesshalf;
	bool empty;

	bool active;
	UInt64 next_event_time;

	bool swapbuffers;

	void reset();
	void write(byte command, UInt32 value);
	void work();
	void vblank();

private:
	void execute_command(UInt64 command);

};
extern GXFIFO GXFifo;