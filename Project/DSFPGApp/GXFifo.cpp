#include "GXFifo.h"
#include "gameboy.h"
#include "IRP.h"

GXFIFO GXFifo;

void GXFIFO::reset()
{
	while (!fifo.empty()) fifo.pop();
	lesshalf = true;
	empty = true;

	swapbuffers = false;
}

void GXFIFO::write(byte command, UInt32 value)
{
	fifo.push((((UInt64)command) << 32) | (UInt64)value);

	lesshalf = fifo.size() < 128;
	empty = false;

	//if (lesshalf_new) triggerDma(EDMAMode_GXFifo);
	//MMU_new.gxstat.sb = gxFIFO.matrix_stack_op_size != 0;

	active = true;
	next_event_time = gameboy.totalticks + 1;

	gameboy.reschedule = true;
	IRP9.check_gxfifobits();
}

void GXFIFO::work()
{
	if (gameboy.totalticks >= next_event_time)
	{
		if (!empty)
		{
			execute_command(fifo.front());
			fifo.pop();
			next_event_time = gameboy.totalticks + 1;
		}
		else
		{
			active = false;
		}
		empty = fifo.empty();
		lesshalf = fifo.size() < 128;
		gameboy.reschedule = true;
		IRP9.check_gxfifobits();
	}
}

void GXFIFO::vblank()
{
	if (swapbuffers)
	{
		active = true;
		next_event_time = gameboy.totalticks + 1;
		swapbuffers = false;
	}
}

void GXFIFO::execute_command(UInt64 command)
{
	byte cmd = (byte)(command >> 32);
	UInt32 value = (UInt32)command;

	switch (cmd)
	{
	case 0x50: swapbuffers = true; break;
	}

}