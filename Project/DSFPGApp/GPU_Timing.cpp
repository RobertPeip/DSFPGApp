#include "GPU_Timing.h"
#include "regs_arm9.h"
#include "regs_arm7.h"
#include "DMA.h"
#include "GPU.h"
#include "CPU.h"
#include "IRP.h"
#include "gameboy.h"

GPUTiming GPU_Timing;

void GPUTiming::reset()
{
	localticks = 0;
	line = 0;
	gpustate = GPUState::HSTART;
	old_dispstat = 0;
}

void GPUTiming::dispstat_write()
{
	UInt16 new_val = (UInt16)Regs_Arm9.Sect_display9.DISPSTAT.read();
	new_val &= 0xFF38;
	old_dispstat &= 0x00C7;
	new_val |= old_dispstat;
	Regs_Arm9.Sect_display9.DISPSTAT.write(new_val);
}

void GPUTiming::work()
{
	bool runagain = true;
	while (runagain)
	{
		Int32 cycles = gameboy.totalticks - localticks;
		runagain = false;

		switch (gpustate)
		{
		case GPUState::HSTART:
			if (cycles >= 12)
			{
				runagain = true;
				localticks += 12;
				next_event_time = localticks + 84;
				gpustate = GPUState::HIRQ;
			}
			break;

		case GPUState::HIRQ:
			if (cycles >= 84)
			{
				runagain = true;
				localticks += 84;
				next_event_time = localticks + 3108;
				gpustate = GPUState::VISIBLE;
			}
			break;

		case GPUState::VISIBLE:
			if (cycles >= 3108)
			{
				runagain = true;
				localticks += 3108;
				next_event_time = localticks + 1056;
				gpustate = GPUState::HBLANK;
				Regs_Arm9.Sect_display9.DISPSTAT_H_Blank_flag.write(1);
				Regs_Arm7.Sect_display7.DISPSTAT_H_Blank_flag.write(1);
				DMA.new_hblank = true;
				if (Regs_Arm9.Sect_display9.DISPSTAT_H_Blank_IRQ_Enable.on()) IRP9.set_irp_bit(IRP9.IRPMASK_LCD_H_Blank);
				if (Regs_Arm7.Sect_display7.DISPSTAT_H_Blank_IRQ_Enable.on()) IRP7.set_irp_bit(IRP7.IRPMASK_LCD_H_Blank);
				old_dispstat = Regs_Arm9.data[4];

				GPU.once_per_hblank();
				GPU.next_line(line);
			}
			break;

		case GPUState::HBLANK:
			if (cycles >= 1056)
			{
				runagain = true;
				localticks += 1056;
				next_event_time = localticks + 12;
				nextline();

				Regs_Arm9.Sect_display9.DISPSTAT_H_Blank_flag.write(0);
				Regs_Arm7.Sect_display7.DISPSTAT_H_Blank_flag.write(0);
				DMA.new_hblank = false;
				if (line < 192)
				{
					gpustate = GPUState::HSTART;
				}
				else
				{
					gpustate = GPUState::VBLANK_START;
					GPU.refpoint_update_all();
					//Cheats.apply_cheats();
					Regs_Arm9.Sect_display9.DISPSTAT_V_Blank_flag.write(1);
					Regs_Arm7.Sect_display7.DISPSTAT_V_Blank_flag.write(1);
					DMA.new_vblank = true;
					if (Regs_Arm9.Sect_display9.DISPSTAT_V_Blank_IRQ_Enable.on()) IRP9.set_irp_bit(IRP9.IRPMASK_LCD_V_Blank);
					if (Regs_Arm7.Sect_display7.DISPSTAT_V_Blank_IRQ_Enable.on()) IRP7.set_irp_bit(IRP7.IRPMASK_LCD_V_Blank);
				}
				old_dispstat = Regs_Arm9.data[4];
			}
			break;

		case GPUState::VBLANK_START:
			if (cycles >= 12)
			{
				runagain = true;
				localticks += 12;
				next_event_time = localticks + 84;
				gpustate = GPUState::VBLANK_HIRQ;
			}
			break;

		case GPUState::VBLANK_HIRQ:
			if (cycles >= 84)
			{
				runagain = true;
				localticks += 84;
				next_event_time = localticks + 3108;
				gpustate = GPUState::VBLANK_DRAWIDLE;
			}
			break;

		case GPUState::VBLANK_DRAWIDLE:
			if (cycles >= 3108)
			{
				runagain = true;
				localticks += 3108;
				next_event_time = localticks + 1056;
				gpustate = GPUState::VBLANKHBLANK;
				Regs_Arm9.Sect_display9.DISPSTAT_H_Blank_flag.write(1);
				Regs_Arm7.Sect_display7.DISPSTAT_H_Blank_flag.write(1);
				//DMA.new_hblank = true; //!!! don't do here!
				if (Regs_Arm9.Sect_display9.DISPSTAT_H_Blank_IRQ_Enable.on()) IRP9.set_irp_bit(IRP9.IRPMASK_LCD_H_Blank); // Note that no H-Blank interrupts are generated within V-Blank period. Really?
				if (Regs_Arm7.Sect_display7.DISPSTAT_H_Blank_IRQ_Enable.on()) IRP7.set_irp_bit(IRP7.IRPMASK_LCD_H_Blank); // Note that no H-Blank interrupts are generated within V-Blank period. Really?
				old_dispstat = Regs_Arm9.data[4];
			}
			break;

		case GPUState::VBLANKHBLANK:
			if (cycles >= 1056)
			{
				runagain = true;
				localticks += 1056;
				next_event_time = localticks + 12;
				nextline();
				Regs_Arm9.Sect_display9.DISPSTAT_H_Blank_flag.write(0);
				Regs_Arm7.Sect_display7.DISPSTAT_H_Blank_flag.write(0);
				DMA.new_hblank = false;
				GPU.once_per_hblank();
				if (line == 0)
				{
					gpustate = GPUState::HSTART;
					//GPU.next_line(line);
					Regs_Arm9.Sect_display9.DISPSTAT_V_Blank_flag.write(0);
					Regs_Arm7.Sect_display7.DISPSTAT_V_Blank_flag.write(0);
					DMA.new_vblank = false;
				}
				else
				{
					gpustate = GPUState::VBLANK_START;
					if (line == 262)
					{
						Regs_Arm9.Sect_display9.DISPSTAT_V_Blank_flag.write(0);
						Regs_Arm7.Sect_display7.DISPSTAT_V_Blank_flag.write(0);
					}
				}
				old_dispstat = Regs_Arm9.data[4];
			}
			break;

		}
	}
}

void GPUTiming::nextline()
{
	line++;
	if (line == 263)
	{
		line = 0;
	}
	Regs_Arm9.Sect_display9.VCOUNT.write(line);
	Regs_Arm7.Sect_display7.VCOUNT.write(line);

	UInt16 vcount_compare = Regs_Arm9.Sect_display9.DISPSTAT_V_Count_Setting.read();
	if (Regs_Arm9.Sect_display9.DISPSTAT_V_Count_Setting8.on())
	{
		vcount_compare += 256;
	}

	if (line == vcount_compare)
	{
		if (Regs_Arm9.Sect_display9.DISPSTAT_V_Counter_IRQ_Enable.on()) IRP9.set_irp_bit(IRP9.IRPMASK_LCD_V_Counter_Match);
		if (Regs_Arm7.Sect_display7.DISPSTAT_V_Counter_IRQ_Enable.on()) IRP7.set_irp_bit(IRP7.IRPMASK_LCD_V_Counter_Match);
		Regs_Arm9.Sect_display9.DISPSTAT_V_Counter_flag.write(1);
		Regs_Arm7.Sect_display7.DISPSTAT_V_Counter_flag.write(1);
	}
	else
	{
		Regs_Arm9.Sect_display9.DISPSTAT_V_Counter_flag.write(0);
		Regs_Arm7.Sect_display7.DISPSTAT_V_Counter_flag.write(0);
	}
}

void GPUTiming::restart_line()
{
	if (!Regs_Arm9.Sect_display9.DISPSTAT_V_Blank_flag.on())
	{
		// really required
		//  line--;
		//  nextline();
		//  gpustate = GPUState::VISIBLE;
		//  Regs_Arm9.Sect_display9.DISPSTAT_V_Blank_flag.write(0);
		//  Regs_Arm9.Sect_display9.DISPSTAT_H_Blank_flag.write(0);
	}
}