#include "GPU_Timing.h"
#include "regs_arm9.h"
#include "regs_arm7.h"
#include "DMA.h"
#include "GPU.h"
#include "CPU.h"
#include "IRP.h"
#include "gameboy.h"
#include "GXFifo.h"

GPUTiming GPU_Timing;

void GPUTiming::reset()
{
	localticks = 0;
	line = 0;
	gpustate = GPUState::HSTART;
	old_dispstat = 0;
	vcount_irp_next9 = false;
	vcount_irp_next7 = false;
	next_event_time = 12;
}

void GPUTiming::dispstat_write()
{
	UInt16 new_val = (UInt16)Regs_Arm9.Sect_display9.DISPSTAT.read();
	new_val &= 0xFFB8;
	old_dispstat &= 0x0047;
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
				if (vcount_irp_next9)
				{
					vcount_irp_next9 = false;
					IRP9.set_irp_bit(IRP9.IRPMASK_LCD_V_Counter_Match);
				}
				if (vcount_irp_next7)
				{
					vcount_irp_next7 = false;
					IRP7.set_irp_bit(IRP7.IRPMASK_LCD_V_Counter_Match);
				}
			}
			break;

		case GPUState::HIRQ:
			if (cycles >= 84)
			{
				runagain = true;
				localticks += 84;
				next_event_time = localticks + 3108;
				gpustate = GPUState::VISIBLE;
				gameboy.reschedule = true;
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

				GPU_A.once_per_hblank();
				GPU_B.once_per_hblank();
				GPU_A.next_line(line);
				GPU_B.next_line(line);
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
					DMA.new_MemDisplay = true;
				}
				else
				{
					gpustate = GPUState::VBLANK_START;
					GPU_A.refpoint_update_all();
					GPU_B.refpoint_update_all();
					//Cheats.apply_cheats();
					Regs_Arm9.Sect_display9.DISPSTAT_V_Blank_flag.write(1);
					Regs_Arm7.Sect_display7.DISPSTAT_V_Blank_flag.write(1);
					GXFifo.vblank();
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

				if (vcount_irp_next9)
				{
					vcount_irp_next9 = false;
					IRP9.set_irp_bit(IRP9.IRPMASK_LCD_V_Counter_Match);
				}
				if (vcount_irp_next7)
				{
					vcount_irp_next7 = false;
					IRP7.set_irp_bit(IRP7.IRPMASK_LCD_V_Counter_Match);
				}

				if (line == 192)
				{
					DMA.new_vblank = true;
					if (Regs_Arm9.Sect_display9.DISPSTAT_V_Blank_IRQ_Enable.on()) IRP9.set_irp_bit(IRP9.IRPMASK_LCD_V_Blank);
					if (Regs_Arm7.Sect_display7.DISPSTAT_V_Blank_IRQ_Enable.on()) IRP7.set_irp_bit(IRP7.IRPMASK_LCD_V_Blank);
				}
				if (line == 262)
				{
					gameboy.reschedule = true;
				}
			}
			break;

		case GPUState::VBLANK_HIRQ:
			if (cycles >= 84)
			{
				runagain = true;
				localticks += 84;
				next_event_time = localticks + 3108;
				gpustate = GPUState::VBLANK_DRAWIDLE;
				gameboy.reschedule = true;
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
				GPU_A.once_per_hblank();
				GPU_B.once_per_hblank();
				if (line == 0)
				{
					gpustate = GPUState::HSTART;
					//GPU.next_line(line);
					Regs_Arm9.Sect_display9.DISPSTAT_V_Blank_flag.write(0);
					Regs_Arm7.Sect_display7.DISPSTAT_V_Blank_flag.write(0);
					DMA.new_vblank = false;
					DMA.new_MemDisplay = true;
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

	// vcount compare arm9
	UInt16 vcount_compare = Regs_Arm9.Sect_display9.DISPSTAT_V_Count_Setting.read();
	if (Regs_Arm9.Sect_display9.DISPSTAT_V_Count_Setting8.on())
	{
		vcount_compare += 256;
	}

	if (line == vcount_compare)
	{
		if (Regs_Arm9.Sect_display9.DISPSTAT_V_Counter_IRQ_Enable.on()) vcount_irp_next9 = true;
		Regs_Arm9.Sect_display9.DISPSTAT_V_Counter_flag.write(1);
	}
	else
	{
		Regs_Arm9.Sect_display9.DISPSTAT_V_Counter_flag.write(0);
	}

	// vcount compare arm7
    vcount_compare = Regs_Arm7.Sect_display7.DISPSTAT_V_Count_Setting.read();
	if (Regs_Arm7.Sect_display7.DISPSTAT_V_Count_Setting8.on())
	{
		vcount_compare += 256;
	}

	if (line == vcount_compare)
	{
		if (Regs_Arm7.Sect_display7.DISPSTAT_V_Counter_IRQ_Enable.on()) vcount_irp_next7 = true;
		Regs_Arm7.Sect_display7.DISPSTAT_V_Counter_flag.write(1);
	}
	else
	{
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