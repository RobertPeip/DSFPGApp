#include "GXFifo.h"
#include "gameboy.h"
#include "IRP.h"
#include "regs_arm9.h"

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
	check_gxfifobits();
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
		check_gxfifobits();
	}
}

void GXFIFO::check_gxfifobits()
{
	Regs_Arm9.Sect_3D9.GXSTAT_Command_FIFO_Less_Half.write(GXFifo.lesshalf);
	Regs_Arm9.Sect_3D9.GXSTAT_Command_FIFO_Empty.write(GXFifo.empty);
	Regs_Arm9.Sect_3D9.GXSTAT_Command_FIFO_Entries.write(GXFifo.fifo.size());

	if (!GXFifo.empty || swapbuffers)
	{
		Regs_Arm9.Sect_3D9.GXSTAT_Geometry_Engine_Busy.write(1);
	}
	else
	{
		Regs_Arm9.Sect_3D9.GXSTAT_Geometry_Engine_Busy.write(0);
	}

	IRP9.check_gxfifobits();
}

void GXFIFO::vblank()
{
	if (swapbuffers)
	{
		active = true;
		next_event_time = gameboy.totalticks + 1;
		swapbuffers = false;
		
		// could do full check here with check_gxfifobits(), but that does way to much without need
		if (!GXFifo.empty || swapbuffers)
		{
			Regs_Arm9.Sect_3D9.GXSTAT_Geometry_Engine_Busy.write(1);
		}
		else
		{
			Regs_Arm9.Sect_3D9.GXSTAT_Geometry_Engine_Busy.write(0);
		}
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