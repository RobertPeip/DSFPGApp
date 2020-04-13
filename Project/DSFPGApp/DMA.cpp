#include <algorithm>
using namespace std;

#include "DMA.h"
#include "gameboy.h"
#include "IRP.h"
#include "Memory.h"
#include "BusTiming.h"
#include "GPU_Timing.h"

Dma DMA;

SingleDMA::SingleDMA()
{
}

SingleDMA::SingleDMA(Cpu* CPU, Irp* IRP, UInt16 irpmask,
	DSReg SAD, DSReg DAD, DSReg CNT_L,
	DSReg Dest_Addr_Control, DSReg Source_Adr_Control, DSReg DMA_Repeat, DSReg DMA_Transfer_Type,
	DSReg Game_Pak_DRQ, DSReg DMA_Start_Timing, DSReg IRQ_on, DSReg DMA_Enable, bool hasDRQ)
{
	this->CPU = CPU;
	this->IRP = IRP;
	this->irpmask = irpmask;

	this->SAD = SAD;
	this->DAD = DAD;
	this->CNT_L = CNT_L;

	this->Dest_Addr_Control = Dest_Addr_Control;
	this->Source_Adr_Control = Source_Adr_Control;
	this->DMA_Repeat = DMA_Repeat;
	this->DMA_Transfer_Type = DMA_Transfer_Type;
	this->Game_Pak_DRQ = Game_Pak_DRQ;
	this->DMA_Start_Timing = DMA_Start_Timing;
	this->IRQ_on = IRQ_on;
	this->DMA_Enable = DMA_Enable;

	this->hasDRQ = hasDRQ;

	this->dMA_Enable = false;
	running = false;
	waiting = false;
	finished = false;
	next_event_time = -1;
}

void Dma::reset()
{
	new_hblank = false;
	new_vblank = false;
	new_MemDisplay = false;

	dma_active = false;

	debug_dmatranfers = 0;

	DSReg empty;

	DMAs[3] = SingleDMA(&CPU9, &IRP9, IRP9.IRPMASK_DMA_3,
		Regs_Arm9.Sect_dma9.DMA3SAD, Regs_Arm9.Sect_dma9.DMA3DAD, Regs_Arm9.Sect_dma9.DMA3CNT_L,
		Regs_Arm9.Sect_dma9.DMA3CNT_H_Dest_Addr_Control, Regs_Arm9.Sect_dma9.DMA3CNT_H_Source_Adr_Control, Regs_Arm9.Sect_dma9.DMA3CNT_H_DMA_Repeat, Regs_Arm9.Sect_dma9.DMA3CNT_H_DMA_Transfer_Type,
		Regs_Arm9.Sect_dma9.DMA3CNT_H_Game_Pak_DRQ, Regs_Arm9.Sect_dma9.DMA3CNT_H_DMA_Start_Timing, Regs_Arm9.Sect_dma9.DMA3CNT_H_IRQ_on, Regs_Arm9.Sect_dma9.DMA3CNT_H_DMA_Enable, true);

	DMAs[2] = SingleDMA(&CPU9, &IRP9, IRP9.IRPMASK_DMA_1,
		Regs_Arm9.Sect_dma9.DMA2SAD, Regs_Arm9.Sect_dma9.DMA2DAD, Regs_Arm9.Sect_dma9.DMA2CNT_L,
		Regs_Arm9.Sect_dma9.DMA2CNT_H_Dest_Addr_Control, Regs_Arm9.Sect_dma9.DMA2CNT_H_Source_Adr_Control, Regs_Arm9.Sect_dma9.DMA2CNT_H_DMA_Repeat, Regs_Arm9.Sect_dma9.DMA2CNT_H_DMA_Transfer_Type,
		empty, Regs_Arm9.Sect_dma9.DMA2CNT_H_DMA_Start_Timing, Regs_Arm9.Sect_dma9.DMA2CNT_H_IRQ_on, Regs_Arm9.Sect_dma9.DMA2CNT_H_DMA_Enable, false);

	DMAs[1] = SingleDMA(&CPU9, &IRP9, IRP9.IRPMASK_DMA_2,
		Regs_Arm9.Sect_dma9.DMA1SAD, Regs_Arm9.Sect_dma9.DMA1DAD, Regs_Arm9.Sect_dma9.DMA1CNT_L,
		Regs_Arm9.Sect_dma9.DMA1CNT_H_Dest_Addr_Control, Regs_Arm9.Sect_dma9.DMA1CNT_H_Source_Adr_Control, Regs_Arm9.Sect_dma9.DMA1CNT_H_DMA_Repeat, Regs_Arm9.Sect_dma9.DMA1CNT_H_DMA_Transfer_Type,
		empty, Regs_Arm9.Sect_dma9.DMA1CNT_H_DMA_Start_Timing, Regs_Arm9.Sect_dma9.DMA1CNT_H_IRQ_on, Regs_Arm9.Sect_dma9.DMA1CNT_H_DMA_Enable, false);

	DMAs[0] = SingleDMA(&CPU9, &IRP9, IRP9.IRPMASK_DMA_0,
		Regs_Arm9.Sect_dma9.DMA0SAD, Regs_Arm9.Sect_dma9.DMA0DAD, Regs_Arm9.Sect_dma9.DMA0CNT_L,
		Regs_Arm9.Sect_dma9.DMA0CNT_H_Dest_Addr_Control, Regs_Arm9.Sect_dma9.DMA0CNT_H_Source_Adr_Control, Regs_Arm9.Sect_dma9.DMA0CNT_H_DMA_Repeat, Regs_Arm9.Sect_dma9.DMA0CNT_H_DMA_Transfer_Type,
		empty, Regs_Arm9.Sect_dma9.DMA0CNT_H_DMA_Start_Timing, Regs_Arm9.Sect_dma9.DMA0CNT_H_IRQ_on, Regs_Arm9.Sect_dma9.DMA0CNT_H_DMA_Enable, false);

	DMAs[7] = SingleDMA(&CPU7, &IRP7, IRP7.IRPMASK_DMA_3,
		Regs_Arm7.Sect_dma7.DMA3SAD, Regs_Arm7.Sect_dma7.DMA3DAD, Regs_Arm7.Sect_dma7.DMA3CNT_L,
		Regs_Arm7.Sect_dma7.DMA3CNT_H_Dest_Addr_Control, Regs_Arm7.Sect_dma7.DMA3CNT_H_Source_Adr_Control, Regs_Arm7.Sect_dma7.DMA3CNT_H_DMA_Repeat, Regs_Arm7.Sect_dma7.DMA3CNT_H_DMA_Transfer_Type,
		Regs_Arm7.Sect_dma7.DMA3CNT_H_Game_Pak_DRQ, Regs_Arm9.Sect_dma9.DMA3CNT_H_DMA_Start_Timing, Regs_Arm7.Sect_dma7.DMA3CNT_H_IRQ_on, Regs_Arm7.Sect_dma7.DMA3CNT_H_DMA_Enable, true);

	DMAs[6] = SingleDMA(&CPU7, &IRP7, IRP7.IRPMASK_DMA_3,
		Regs_Arm7.Sect_dma7.DMA2SAD, Regs_Arm7.Sect_dma7.DMA2DAD, Regs_Arm7.Sect_dma7.DMA2CNT_L,
		Regs_Arm7.Sect_dma7.DMA2CNT_H_Dest_Addr_Control, Regs_Arm7.Sect_dma7.DMA2CNT_H_Source_Adr_Control, Regs_Arm7.Sect_dma7.DMA2CNT_H_DMA_Repeat, Regs_Arm7.Sect_dma7.DMA2CNT_H_DMA_Transfer_Type,
		empty, Regs_Arm7.Sect_dma7.DMA2CNT_H_DMA_Start_Timing, Regs_Arm7.Sect_dma7.DMA2CNT_H_IRQ_on, Regs_Arm7.Sect_dma7.DMA2CNT_H_DMA_Enable, true);

	DMAs[5] = SingleDMA(&CPU7, &IRP7, IRP7.IRPMASK_DMA_3,
		Regs_Arm7.Sect_dma7.DMA1SAD, Regs_Arm7.Sect_dma7.DMA1DAD, Regs_Arm7.Sect_dma7.DMA1CNT_L,
		Regs_Arm7.Sect_dma7.DMA1CNT_H_Dest_Addr_Control, Regs_Arm7.Sect_dma7.DMA1CNT_H_Source_Adr_Control, Regs_Arm7.Sect_dma7.DMA1CNT_H_DMA_Repeat, Regs_Arm7.Sect_dma7.DMA1CNT_H_DMA_Transfer_Type,
		empty, Regs_Arm7.Sect_dma7.DMA1CNT_H_DMA_Start_Timing, Regs_Arm7.Sect_dma7.DMA1CNT_H_IRQ_on, Regs_Arm7.Sect_dma7.DMA1CNT_H_DMA_Enable, true);

	DMAs[4] = SingleDMA(&CPU7, &IRP7, IRP7.IRPMASK_DMA_3,
		Regs_Arm7.Sect_dma7.DMA0SAD, Regs_Arm7.Sect_dma7.DMA0DAD, Regs_Arm7.Sect_dma7.DMA0CNT_L,
		Regs_Arm7.Sect_dma7.DMA0CNT_H_Dest_Addr_Control, Regs_Arm7.Sect_dma7.DMA0CNT_H_Source_Adr_Control, Regs_Arm7.Sect_dma7.DMA0CNT_H_DMA_Repeat, Regs_Arm7.Sect_dma7.DMA0CNT_H_DMA_Transfer_Type,
		empty, Regs_Arm7.Sect_dma7.DMA0CNT_H_DMA_Start_Timing, Regs_Arm7.Sect_dma7.DMA0CNT_H_IRQ_on, Regs_Arm7.Sect_dma7.DMA0CNT_H_DMA_Enable, true);
}

void Dma::set_settings(int index)
{
	if (gameboy.loading_state)
	{
		return;
	}

	bool old_ena = DMAs[index].dMA_Enable;
	DMAs[index].dMA_Enable = DMAs[index].DMA_Enable.on();

	if (!DMAs[index].dMA_Enable)
	{
		DMAs[index].running = false;
		DMAs[index].waiting = false;
		DMAs[index].finished = false;
	}

	if (DMAs[index].dMA_Enable && !old_ena)
	{
		DMAs[index].dest_Addr_Control = (byte)DMAs[index].Dest_Addr_Control.read();
		DMAs[index].source_Adr_Control = (byte)DMAs[index].Source_Adr_Control.read();
		DMAs[index].dMA_Repeat = DMAs[index].DMA_Repeat.on();
		DMAs[index].dMA_Transfer_Type = DMAs[index].DMA_Transfer_Type.on();
		if (DMAs[index].hasDRQ)
		{
			DMAs[index].game_Pak_DRQ = DMAs[index].Game_Pak_DRQ.on();
			if (DMAs[index].game_Pak_DRQ)
			{
				//throw new Exception("gamepak drq?");
			}
		}
		else
		{
			DMAs[index].game_Pak_DRQ = false;
		}
		DMAs[index].dMA_Start_Timing = (byte)DMAs[index].DMA_Start_Timing.read();
		DMAs[index].iRQ_on = DMAs[index].IRQ_on.on();

		DMAs[index].addr_source = DMAs[index].SAD.read();
		DMAs[index].addr_target = DMAs[index].DAD.read();

		switch (index)
		{
		case 0: DMAs[index].addr_source &= 0x07FFFFFE; DMAs[index].addr_target &= 0x07FFFFFE; break;
		case 1: DMAs[index].addr_source &= 0x0FFFFFFE; DMAs[index].addr_target &= 0x07FFFFFE; break;
		case 2: DMAs[index].addr_source &= 0x0FFFFFFE; DMAs[index].addr_target &= 0x07FFFFFE; break;
		case 3: DMAs[index].addr_source &= 0x0FFFFFFE; DMAs[index].addr_target &= 0x0FFFFFFE; break;
		}

		if (DMAs[index].dMA_Transfer_Type)
		{
			DMAs[index].addr_source &= 0x0FFFFFFC;
			DMAs[index].addr_target &= 0x0FFFFFFC;
		}

		DMAs[index].count = DMAs[index].CNT_L.read();

		if (DMAs[index].count == 0)
		{
			DMAs[index].count = 0x4000;
			if (index == 3)
			{
				DMAs[index].count = 0x10000;
			}
		}
		DMAs[index].waiting = true;
		check_run(index);

		if (index < 4 && DMAs[index].dMA_Start_Timing == 4)
		{
			DMAs[index].count = 128;
		}
	}
}

void Dma::check_run(int index)
{
	bool start = false;
	if (index < 4)
	{
		switch (DMAs[index].dMA_Start_Timing)
		{
		case 0: start = true; break; // 0  Start Immediately
		case 1: start = new_vblank; break; // 1  Start at V - Blank
		case 2: start = new_hblank; break; // 2  Start at H - Blank(paused during V - Blank)
		// 3  Synchronize to start of display
		case 4: start = new_MemDisplay; break;// 4  Main memory display
		// 5  DS Cartridge Slot
		// 6  GBA Cartridge Slot
		// 7  Geometry Command FIFO
		}
	}
	else
	{
		switch (DMAs[index].dMA_Start_Timing)
		{
		case 0: start = true; break; // Start Immediately
		case 1: start = new_vblank; break; // Start at V - Blank
		// 2  DS Cartridge Slot
		// 3  DMA0 / DMA2: Wireless interrupt, DMA1 / DMA3 : GBA Cartridge Slot
		}
	}

	if (start)
	{
		DMAs[index].waitTicks = 3;
		DMAs[index].waiting = false;
		DMAs[index].first = true;
		DMAs[index].fullcount = DMAs[index].count;
	}
}

void Dma::work()
{
	dma_active = false;
	delayed = false;

	for (int i = 0; i < 8; i++)
	{
		if (DMAs[i].finished)
		{
			if (gameboy.totalticks >= DMAs[i].next_event_time)
			{
				DMAs[i].finished = false;
				DMAs[i].next_event_time = -1;
			}
			else
			{
				dma_active = true;
			}
		}

		if (DMAs[i].dMA_Enable)
		{
			if (DMAs[i].waiting)
			{
				check_run(i);
			}

			if (DMAs[i].waitTicks > 0)
			{
				//if (DMAs[i].CPU.newticks >= DMAs[i].waitTicks)
				{
					DMAs[i].running = true;
					DMAs[i].waitTicks = 0;
				}
				//else
				//{
				//	DMAs[i].waitTicks -= DMAs[i].CPU.newticks;
				//}
			}

			//if (DMAs[i].running)
			int ticks = 0;
			while (DMAs[i].running)
			{
				// remember for timing
				UInt32 sm = (DMAs[i].addr_source >> 24) & 0xF;
				UInt32 dm = (DMAs[i].addr_target >> 24) & 0xF;

				// calc timing
				
				//if (DMAs[i].first)
				//{
				//	if (DMAs[i].dMA_Transfer_Type)
				//	{
				//		ticks = 4 + BusTiming.memoryWait32Arm9[sm & 15] + BusTiming.memoryWait32Arm9[dm & 15]; // nonseq + seq!
				//	}
				//	else
				//	{
				//		ticks = 4 + BusTiming.memoryWait16Arm9[sm & 15] + BusTiming.memoryWait16Arm9[dm & 15];  // nonseq + seq!
				//	}
				//	DMAs[i].first = false;
				//}
				//else
				{
					if (DMAs[i].dMA_Transfer_Type)
					{
						ticks += BusTiming.dmaTicksAccess32(i < 4, DMAs[i].addr_source);
						ticks += BusTiming.dmaTicksAccess32(i < 4, DMAs[i].addr_target);
					}
					else
					{
						ticks += BusTiming.dmaTicksAccess16(i < 4, DMAs[i].addr_source);
						ticks += BusTiming.dmaTicksAccess16(i < 4, DMAs[i].addr_target);
					}
				}

				DMAs[i].next_event_time = gameboy.totalticks + ticks;
				//DMAs[i].CPU->totalticks += ticks;

				// transfer
				dma_active = true;

				if (DMAs[i].dMA_Transfer_Type)
				{
					UInt32 value = read_dword_9(ACCESSTYPE::DMA, DMAs[i].addr_source);
					write_dword_9(ACCESSTYPE::DMA, DMAs[i].addr_target, value);

					if (DMAs[i].source_Adr_Control == 0 || DMAs[i].source_Adr_Control == 3 || (DMAs[i].addr_source >= 0x08000000 && DMAs[i].addr_source < 0x0E000000)) { DMAs[i].addr_source += 4; }
					else if (DMAs[i].source_Adr_Control == 1) { DMAs[i].addr_source -= 4; }

					if (DMAs[i].dest_Addr_Control == 0 || (DMAs[i].dest_Addr_Control == 3 && DMAs[i].dMA_Start_Timing != 3)) { DMAs[i].addr_target += 4; }
					else if (DMAs[i].dest_Addr_Control == 1) { DMAs[i].addr_target -= 4; }
				}
				else
				{
					UInt16 value = read_word_9(ACCESSTYPE::DMA, DMAs[i].addr_source);
					write_word_9(ACCESSTYPE::DMA, DMAs[i].addr_target, value);

					if (DMAs[i].source_Adr_Control == 0 || DMAs[i].source_Adr_Control == 3 || (DMAs[i].addr_source >= 0x08000000 && DMAs[i].addr_source < 0x0E000000)) { DMAs[i].addr_source += 2; }
					else if (DMAs[i].source_Adr_Control == 1) { DMAs[i].addr_source -= 2; }

					if (DMAs[i].dest_Addr_Control == 0 || (DMAs[i].dest_Addr_Control == 3 && DMAs[i].dMA_Start_Timing != 3)) { DMAs[i].addr_target += 2; }
					else if (DMAs[i].dest_Addr_Control == 1) { DMAs[i].addr_target -= 2; }
				}

				debug_dmatranfers++;

				DMAs[i].count--;

				if (DMAs[i].count == 0)
				{
					DMAs[i].running = false;
					DMAs[i].finished = true;

					if (DMAs[i].iRQ_on)
					{
						switch (i % 4)
						{
						case 0: DMAs[i].IRP->set_irp_bit(DMAs[i].IRP->IRPMASK_DMA_0); break;
						case 1: DMAs[i].IRP->set_irp_bit(DMAs[i].IRP->IRPMASK_DMA_1); break;
						case 2: DMAs[i].IRP->set_irp_bit(DMAs[i].IRP->IRPMASK_DMA_2); break;
						case 3: DMAs[i].IRP->set_irp_bit(DMAs[i].IRP->IRPMASK_DMA_3); break;
						}
					}

					if (DMAs[i].dMA_Repeat && DMAs[i].dMA_Start_Timing != 0)
					{
						DMAs[i].waiting = true;
						if (DMAs[i].dMA_Start_Timing == 4 && i < 4)
						{
							DMAs[i].count = 128;
							if (GPU_Timing.line == 191)
							{
								DMAs[i].waiting = false;
								DMAs[i].dMA_Enable = false;
							}
						}
						else
						{
							DMAs[i].count = DMAs[i].CNT_L.read();
							if (DMAs[i].dest_Addr_Control == 3)
							{
								DMAs[i].addr_target = DMAs[i].DAD.read();
								switch (i)
								{
								case 0: DMAs[i].addr_target &= 0x07FFFFFF; break;
								case 1: DMAs[i].addr_target &= 0x07FFFFFF; break;
								case 2: DMAs[i].addr_target &= 0x07FFFFFF; break;
								case 3: DMAs[i].addr_target &= 0x0FFFFFFF; break;
								}
							}
						}
					}
					else
					{
						DMAs[i].DMA_Enable.write(0);
						DMAs[i].dMA_Enable = false;
					}

#if DEBUG
					//if (CPU.traclist_ptr > 0 && !DMAs[i].skipdebugout)
					//{
					//    CPU.Tracelist[CPU.traclist_ptr - 1].thumbmode = 3;
					//    CPU.Tracelist[CPU.traclist_ptr - 1].memory01 = (UInt32) DMAs[i].totalTicks;
					//    CPU.Tracelist[CPU.traclist_ptr - 1].memory02 = DMAs[i].addr_source_save;
					//}
					DMAs[i].skipdebugout = false;
#endif
				}

				//break;
			}
		}
	}

	new_hblank = false;
	new_vblank = false;
	new_MemDisplay = false;
}

void Dma::request_audio(uint audioindex)
{
	for (int i = 1; i < 3; i++)
	{
		if (DMAs[i].dMA_Enable && DMAs[i].waiting && DMAs[i].dMA_Start_Timing == 3)
		{
			if (audioindex + 1 == i)
			{
				DMAs[i].running = true;
				DMAs[i].first = true;
				DMAs[i].fullcount = DMAs[i].count;
				DMAs[i].skipdebugout = true;
			}
		}
	}
}