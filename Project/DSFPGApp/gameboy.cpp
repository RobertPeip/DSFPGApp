#include "gameboy.h"
#include "BusTiming.h"
#include "CPU.h"
#include "Memory.h"
#include "regs_arm9.h"
#include "regs_arm7.h"
#include "GPU.h"
#include "GPU_Timing.h"
#include "Sound.h"
#include "Joypad.h"
#include "Timer.h"
#include "DMA.h"
#include "gpio.h"
#include "Serial.h"
#include "IRP.h"
#include "Header.h"
#include "CPUCache.h"
#include "spi_intern.h"
#include "IPC.h"
#include "MathDIV.h"
#include "MathSQRT.h"
#include "Gamecard.h"
#include "GXFifo.h"

Gameboy gameboy;

void Gameboy::reset()
{
	totalticks = 0;

	if (coldreset)
	{
		Regs_Arm9.reset();
		Regs_Arm7.reset();
		GPU_A.reset(true);
		GPU_B.reset(false);
		Memory.reset(filename);
	}

	Co15.reset();
	CPU9.reset(true);
	CPU7.reset(false);
	IRP9.reset(true);
	IRP7.reset(false);
	MathDIV.reset();
	MathSQRT.reset();
	InstrCache.reset();
	DataCache.reset();
	GPU_Timing.reset();
	Sound.reset();
	Joypad.reset();
	Timer.reset();
	DMA.reset();
	BusTiming.reset();
	//gpio.rtcReset();
	Serial.reset();
	SPI_Intern.reset();
	IPC9to7.reset(true);
	IPC7to9.reset(false);
	Gamecard9.reset(true);
	Gamecard7.reset(false);
	GXFifo.reset();

	loading_state = false;
	coldreset = false;

	CPU9.PC = Header.ARM9_CODE_PC;
	CPU7.PC = Header.ARM7_CODE_PC;

#ifdef DESMUMECOMPATIBLE
	InstrCache.inCache(CPU9.PC, true); // fetch first instruction
#endif

	on = true;
	pause = false;

	savestate[0] = 0;
}

void Gameboy::run()
{
	reset();

	byte checkcount = 0;
	bool halt_both = false;

	while (on)
	{
#ifdef FPGACOMPATIBLE
		skipcpuonce = false;
#endif

		GPU_Timing.work();
		if (GPU_A.lockSpeed && newhblank)
		{
			newhblank = false;
			Sound.work();
		}

		if (MathDIV.calculating) { MathDIV.finish(); }
		if (MathSQRT.calculating) { MathSQRT.finish(); }
		if (GXFifo.active) { GXFifo.work(); }
		if (Gamecard9.active) { Gamecard9.finish(); }
		if (Gamecard7.active) { Gamecard7.finish(); }

		DMA.work();
		Timer.work();

		//Serial.work();

		if (IRP9.checknext) IRP9.check_and_execute_irp();
		if (IRP7.checknext) IRP7.check_and_execute_irp();

#ifdef FPGACOMPATIBLE
		if (IRP9.next_mask != 0) { IRP9.set_irp_bit(IRP9.next_mask, false); IRP9.next_mask = 0; }
		if (IRP7.next_mask != 0) { IRP7.set_irp_bit(IRP7.next_mask, false); IRP7.next_mask = 0; }
#endif

		UInt64 nexteventtotal = next_event_time();
		reschedule = false;

#if DEBUG
		//if (tracer.traclist_ptr == 13831)
		if (tracer.commands == 1326903)
		{
			int stop = 1;
		}
		UInt64 startticks = totalticks;
#endif
		while (totalticks < nexteventtotal && !reschedule)
		{
#if DEBUG
			UInt64 runticks = totalticks - startticks;
			//if (totalticks == 0x734896)
			if (runticks == 0x3)
			{
				int stop = 1;
			}
#endif

#ifdef FPGACOMPATIBLE
		halt_both = CPU9.halt & CPU7.halt;
		if (!skipcpuonce)
		{ 
#endif
			if (CPU9.totalticks <= totalticks)
			{
				if (!CPU9.halt)
				{
					CPU9.nextInstr(nexteventtotal);
				}
				else
				{
					CPU9.totalticks = nexteventtotal;
				}
			}
			if (CPU7.totalticks <= totalticks)
			{
				if (!CPU7.halt)
				{
					CPU7.nextInstr(nexteventtotal);
				}
				else
				{
					CPU7.totalticks = nexteventtotal;
				}
			}
#ifdef FPGACOMPATIBLE
		}

			if (halt_both)
			{
				CPU9.totalticks = totalticks + 4;
				CPU7.totalticks = totalticks + 4;
			}
			else
			{
				if (CPU9.halt && !CPU7.halt) CPU9.totalticks = CPU7.totalticks;
				if (CPU7.halt && !CPU9.halt) CPU7.totalticks = CPU9.totalticks;
			}
#endif

#if DEBUG
			if (reschedule)
			{
				int stop = 1;
			}
#endif
			totalticks = min(CPU9.totalticks, CPU7.totalticks);
		}

		if (CPU9.halt) { CPU9.totalticks = totalticks; }
		if (CPU7.halt) { CPU7.totalticks = totalticks; }

#if DEBUG
		if (tracer.commands == 000000 && tracer.runmoretrace == 0)
		{
			tracer.traclist_ptr = 0;
			tracer.runmoretrace = 200000;
			tracer.startindex = 0;
		}

		if (tracer.runmoretrace > 0)
		{
			if (tracer.debug_outdivcnt == 0)
			{
				tracer.Tracelist[tracer.traclist_ptr][0].update(true);
				tracer.Tracelist[tracer.traclist_ptr][1].update(false);
				tracer.traclist_ptr++;
				tracer.runmoretrace = tracer.runmoretrace - 1;
			}
			if (tracer.runmoretrace == 0)
			{
				//tracer.vcd_file_last(tracer.startindex);
				if (true && tracer.commands < 8000000)
				{
					tracer.startindex = tracer.commands + 1;
					tracer.traclist_ptr = 0;
					tracer.runmoretrace = 200000;
				}
				else
				{
					tracer.runmoretrace = -1;
				}
			}
		}
		tracer.commands++;
		//tracer.debug_outdivcnt = (tracer.debug_outdivcnt + 1) % 2000;

		//blockinput = true;
		//if (tracer.commands == 200000) { Joypad.KeyStart = true; Joypad.set_reg(); }
		//if (tracer.commands == 400000) { Joypad.KeyStart = false; Joypad.set_reg(); }
		//if (tracer.commands == 700000) { Joypad.KeyStart = true; Joypad.set_reg(); }
		//if (tracer.commands == 1000000) { Joypad.KeyStart = false; Joypad.set_reg();}
		//if (tracer.commands == 1300000) { Joypad.KeyStart = true; Joypad.set_reg();}
		//if (tracer.commands == 1600000) { Joypad.KeyStart = false; Joypad.set_reg();}
		//if (tracer.commands == 2000000) { Joypad.KeyStart = true; Joypad.set_reg();}
		//if (tracer.commands == 2300000) { Joypad.KeyStart = false; Joypad.set_reg();}
		//if (tracer.commands == 2600000) { Joypad.KeyStart = true; Joypad.set_reg();}
		//if (tracer.commands == 2900000) { Joypad.KeyStart = false; Joypad.set_reg();}

		//if (tracer.commands == 200000) { Joypad.KeyDown = true; Joypad.set_reg(); }
		//if (tracer.commands == 400000) { Joypad.KeyDown = false; Joypad.set_reg(); }
		//if (tracer.commands == 700000) { Joypad.KeyDown = true; Joypad.set_reg(); }
		//if (tracer.commands == 1100000) { Joypad.KeyDown = false; Joypad.set_reg(); }
		//if (tracer.commands == 1500000) { Joypad.KeyDown = true; Joypad.set_reg(); }
		//if (tracer.commands == 1800000) { Joypad.KeyDown = false; Joypad.set_reg(); }
		//if (tracer.commands == 2100000) { Joypad.KeyDown = true; Joypad.set_reg(); }
		//if (tracer.commands == 2400000) { Joypad.KeyDown = false; Joypad.set_reg(); }
		//if (tracer.commands == 2700000) { Joypad.KeyDown = true; Joypad.set_reg(); }
		//if (tracer.commands == 3000000) { Joypad.KeyDown = false; Joypad.set_reg(); }
		//if (tracer.commands == 3300000) { Joypad.KeyDown = true; Joypad.set_reg(); }
		//if (tracer.commands == 3600000) { Joypad.KeyDown = false; Joypad.set_reg(); }
		//if (tracer.commands == 3900000) { Joypad.KeyDown = true; Joypad.set_reg(); }
		//if (tracer.commands == 4200000) { Joypad.KeyDown = false; Joypad.set_reg(); }
		//if (tracer.commands == 4500000) { Joypad.KeyStart = true; Joypad.set_reg(); }
		//if (tracer.commands == 4800000) { Joypad.KeyStart = false; Joypad.set_reg(); }
#endif

		checkcount++;
		if (checkcount == 0)
		{
			Joypad.set_reg();

			Memory.GameRAMSnapshot();

			if (do_savestate)
			{
				create_savestate();
				do_savestate = false;
			}

			if (do_loadstate)
			{
				load_savestate();
				do_loadstate = false;
			}

			if (do_exportmem)
			{
				exportmem();
				do_exportmem = false;
			}

			while (pause && on)
			{
				SDL_Delay(1);
			}
		}
	}
}

UInt64 Gameboy::next_event_time()
{
	UInt64 nexttime = GPU_Timing.next_event_time;

	if (MathDIV.calculating) nexttime = min(nexttime, MathDIV.next_event_time);
	if (MathSQRT.calculating) nexttime = min(nexttime, MathSQRT.next_event_time);
	if (GXFifo.active) nexttime = min(nexttime, GXFifo.next_event_time);
	if (Gamecard9.active) nexttime = min(nexttime, Gamecard9.next_event_time);
	if (Gamecard7.active) nexttime = min(nexttime, Gamecard7.next_event_time);

	if (DMA.dma_active)
	{
		for (int i = 0; i < 8; i++)
		{
			nexttime = min(nexttime, DMA.DMAs[i].next_event_time);
		}
	}

	for (int i = 0; i < 8; i++)
	{
		if (Timer.timers[i].on)
		{
			nexttime = min(nexttime, Timer.timers[i].next_event_time);
		}
	}

	return nexttime;
}

void Gameboy::create_savestate()
{
	savestate[0]++; // header -> number of savestate, 0 = invalid

	uint index = 4; // header size = 4 dwords

	for (int i = 0; i < 4194304 / 4; i++) { savestate[index++] = *(UInt32*)&Memory.WRAM_Large[i * 4]; }
	for (int i = 0; i < 65536 / 4; i++) { savestate[index++] = *(UInt32*)&Memory.WRAM_Small_64[i * 4]; }
	for (int i = 0; i < 32768 / 4; i++) { savestate[index++] = *(UInt32*)&Memory.WRAM_Small_32[i * 4]; }
	for (int i = 0; i < 671744 / 4; i++) { savestate[index++] = *(UInt32*)&Memory.VRAM[i * 4]; }
	for (int i = 0; i < 2048 / 4; i++) { savestate[index++] = *(UInt32*)&Memory.OAMRAM[i * 4]; }
	for (int i = 0; i < 2048 / 4; i++) { savestate[index++] = *(UInt32*)&Memory.PaletteRAM[i * 4]; }
	for (int i = 0; i < 32768 / 4; i++) { savestate[index++] = *(UInt32*)&Memory.ITCM[i * 4]; }
	for (int i = 0; i < 16384 / 4; i++) { savestate[index++] = *(UInt32*)&Memory.DTCM[i * 4]; }

	for (int i = 0; i < 8192 / 4; i++)
	{
		UInt32 value = *(UInt32*)&Regs_Arm9.data[i * 4];
		savestate[index++] = value;
	}

	for (int i = 0; i < 8192; i++)
	{
		UInt32 value = *(UInt32*)&Regs_Arm7.data[i * 4];
		savestate[index++] = value;
	}

	for (int i = 0; i < 1024; i++) // todo: internal state
	{
		UInt32 value = 0;
		savestate[index++] = value;
	}

	savestate[1] = index; // header -> size

	/*
	savestate[index++] = CPU.PC;
	for (int i = 0; i < 18; i++)
	{
		savestate[index++] = CPU.regs[i];
	}
	for (int i = 0; i <= 1; i++)
	{
		savestate[index++] = CPU.regbanks[i][8];
		savestate[index++] = CPU.regbanks[i][9];
		savestate[index++] = CPU.regbanks[i][10];
		savestate[index++] = CPU.regbanks[i][11];
		savestate[index++] = CPU.regbanks[i][12];
		savestate[index++] = CPU.regbanks[i][13];
		savestate[index++] = CPU.regbanks[i][14];
	}
	savestate[index++] = CPU.regbanks[1][17];
	for (int i = 2; i <= 5; i++)
	{
		savestate[index++] = CPU.regbanks[i][13];
		savestate[index++] = CPU.regbanks[i][14];
		savestate[index++] = CPU.regbanks[i][17];
	}

	uint cpu_mixed = 0;
	if (CPU.halt) cpu_mixed |= 1;
	if (CPU.Flag_Zero) cpu_mixed |= 1 << 1;
	if (CPU.Flag_Carry) cpu_mixed |= 1 << 2;
	if (CPU.Flag_Negative) cpu_mixed |= 1 << 3;
	if (CPU.Flag_V_Overflow) cpu_mixed |= 1 << 4;
	if (CPU.thumbmode) cpu_mixed |= 1 << 5;
	cpu_mixed |= (CPU.get_CPSR() & 0xF) << 6;
	if (CPU.IRQ_disable) cpu_mixed |= 1 << 10;
	if (CPU.FIQ_disable) cpu_mixed |= 1 << 11;
	savestate[index++] = cpu_mixed;

	savestate[index++] = IRP.IRP_Flags | (uint)((gpio.bits & 0x3F) << 16);

	UInt32 eeprom_mix = 0;
	for (int i = 0; i < 8; i++)
	{
		eeprom_mix |= (uint)((EEProm.eepromBuffer[i] & 1) << i);
	}
	eeprom_mix |= (uint)((EEProm.eepromBits & 0xFF) << 8);
	eeprom_mix |= (uint)((EEProm.eepromByte & 0x3F) << 16);
	eeprom_mix |= (uint)((EEProm.eepromAddress & 0x3FF) << 22);
	savestate[index++] = eeprom_mix;

	UInt32 flash_mix = 0;
	flash_mix |= (uint)((0 & 0x7) << 0); // eeprombitpos
	flash_mix |= (uint)((Flash.flashBank & 0x1) << 3);
	if (!Memory.SramEnabled) { flash_mix |= 1 << 4; }
	if (Memory.SramEnabled && Memory.FlashEnabled) { flash_mix |= 1 << 5; }
	flash_mix |= (uint)((((uint)EEProm.eepromMode) & 0x7) << 6);
	flash_mix |= (uint)((((uint)Flash.flashState) & 0xF) << 9);
	flash_mix |= (uint)((((uint)Flash.flashReadState) & 0xF) << 13);
	savestate[index++] = flash_mix;

	for (int i = 0; i < 4; i++) { savestate[index++] = DMA.DMAs[i].addr_source; }
	for (int i = 0; i < 4; i++) { savestate[index++] = DMA.DMAs[i].addr_target; }
	for (int i = 0; i < 4; i++)
	{
		UInt32 dmamix = DMA.DMAs[i].count & 0x1FFFF;
		if (DMA.DMAs[i].dMA_Enable) dmamix |= 1 << 17;
		if (DMA.DMAs[i].running) dmamix |= 1 << 18;
		if (DMA.DMAs[i].waiting) dmamix |= 1 << 19;
		if (DMA.DMAs[i].first) dmamix |= 1 << 20;
		dmamix |= (uint)((DMA.DMAs[i].dest_Addr_Control & 0x3) << 21);
		dmamix |= (uint)((DMA.DMAs[i].source_Adr_Control & 0x3) << 23);
		dmamix |= (uint)((DMA.DMAs[i].dMA_Start_Timing & 0x3) << 25);
		if (DMA.DMAs[i].dMA_Repeat) dmamix |= 1 << 27;
		if (DMA.DMAs[i].dMA_Transfer_Type) dmamix |= 1 << 28;
		if (DMA.DMAs[i].iRQ_on) dmamix |= 1 << 29;
		// if (DMA.DMAs[i].dmaon) dmamix |= 1 << 30; // only for hardware ?

		savestate[index++] = dmamix;
	}

	for (int i = 0; i < 4; i++)
	{
		UInt32 timermix = 0;
		if (Timer.timers[i].on) timermix |= 1;
		if (Timer.timers[i].startnow) timermix |= 1 << 1;
		timermix |= (uint)((Timer.timers[i].value & 0x1FFFF) << 2);
		timermix |= (uint)((Timer.timers[i].prescalevalue & 0x7FF) << 19);
		savestate[index++] = timermix;
	}

	UInt32 gpumix = (uint)GPU_Timing.cycles & 0xFFF;
	gpumix |= (uint)((GPU_Timing.line & 0xFF) << 12);
	gpumix |= (uint)((((uint)GPU_Timing.gpustate) & 0x3) << 20);
	if (DSRegs.Sect_display.DISPSTAT_V_Counter_flag.read() == 1) gpumix |= 1 << 22;
	if (DSRegs.Sect_display.DISPSTAT_H_Blank_flag.read() == 1) gpumix |= 1 << 23;
	if (DSRegs.Sect_display.DISPSTAT_V_Blank_flag.read() == 1) gpumix |= 1 << 24;
	savestate[index++] = gpumix;

	UInt32 gpiomix = (uint)gpio.clockslow & 0xFF;
	gpiomix |= (uint)((gpio.command & 0xFF) << 8);
	gpiomix |= (uint)((gpio.dataLen & 7) << 16);
	gpiomix |= (uint)((gpio.enable & 1) << 19);
	gpiomix |= (uint)((gpio.retval & 0xF) << 20);
	gpiomix |= (uint)((gpio.select & 0xF) << 24);
	gpiomix |= (uint)((((uint)gpio.state) & 0x3) << 28);
	savestate[index++] = gpiomix;

	for (int i = 0; i < 256; i++)
	{
		UInt32 value = *(UInt32*)&DSRegs.data[i * 4];
		savestate[index++] = value;
	}

	savestate[1] = index; // header -> size
	*/
}

void Gameboy::load_savestate()
{
	/*
	if (savestate[0] != 0)
	{
		reset();

		uint index = 2 + 68;

		loading_state = true;
		for (int i = 0; i < 256; i++)
		{
			UInt32 data = savestate[index++];
			int adr = i * 4;
			Memory.write_dword((uint)(i * 4 + 0x4000000), data);
		}
		loading_state = false;

		for (int i = 0; i < 65536; i++)
		{
			UInt32 data = savestate[index++];
			int adr = i * 4;
			Memory.WRAM_Large[adr] = (byte)(data & 0xFF);
			Memory.WRAM_Large[adr + 1] = (byte)((data >> 8) & 0xFF);
			Memory.WRAM_Large[adr + 2] = (byte)((data >> 16) & 0xFF);
			Memory.WRAM_Large[adr + 3] = (byte)((data >> 24) & 0xFF);
		}
		for (int i = 0; i < 8192; i++)
		{
			UInt32 data = savestate[index++];
			int adr = i * 4;
			Memory.WRAM_Small[adr] = (byte)(data & 0xFF);
			Memory.WRAM_Small[adr + 1] = (byte)((data >> 8) & 0xFF);
			Memory.WRAM_Small[adr + 2] = (byte)((data >> 16) & 0xFF);
			Memory.WRAM_Small[adr + 3] = (byte)((data >> 24) & 0xFF);
		}
		for (int i = 0; i < 256; i++)
		{
			UInt32 data = savestate[index++];
			int adr = i * 4;
			Memory.PaletteRAM[adr] = (byte)(data & 0xFF);
			Memory.PaletteRAM[adr + 1] = (byte)((data >> 8) & 0xFF);
			Memory.PaletteRAM[adr + 2] = (byte)((data >> 16) & 0xFF);
			Memory.PaletteRAM[adr + 3] = (byte)((data >> 24) & 0xFF);
		}
		for (int i = 0; i < 24576; i++)
		{
			UInt32 data = savestate[index++];
			int adr = i * 4;
			Memory.VRAM[adr] = (byte)(data & 0xFF);
			Memory.VRAM[adr + 1] = (byte)((data >> 8) & 0xFF);
			Memory.VRAM[adr + 2] = (byte)((data >> 16) & 0xFF);
			Memory.VRAM[adr + 3] = (byte)((data >> 24) & 0xFF);
		}
		for (int i = 0; i < 256; i++)
		{
			UInt32 data = savestate[index++];
			int adr = i * 4;
			Memory.OAMRAM[adr] = (byte)(data & 0xFF);
			Memory.OAMRAM[adr + 1] = (byte)((data >> 8) & 0xFF);
			Memory.OAMRAM[adr + 2] = (byte)((data >> 16) & 0xFF);
			Memory.OAMRAM[adr + 3] = (byte)((data >> 24) & 0xFF);
		}

		index = 2;
		CPU.PC = savestate[index++];
		for (int i = 0; i < 18; i++)
		{
			CPU.regs[i] = savestate[index++];
		}
		for (int i = 0; i <= 1; i++)
		{
			CPU.regbanks[i][8] = savestate[index++];
			CPU.regbanks[i][9] = savestate[index++];
			CPU.regbanks[i][10] = savestate[index++];
			CPU.regbanks[i][11] = savestate[index++];
			CPU.regbanks[i][12] = savestate[index++];
			CPU.regbanks[i][13] = savestate[index++];
			CPU.regbanks[i][14] = savestate[index++];
		}
		CPU.regbanks[1][17] = savestate[index++];
		for (int i = 2; i <= 5; i++)
		{
			CPU.regbanks[i][13] = savestate[index++];
			CPU.regbanks[i][14] = savestate[index++];
			CPU.regbanks[i][17] = savestate[index++];
		}
		uint cpu_mixed = savestate[index++];
		if ((cpu_mixed & 1) > 0) CPU.halt = true; else CPU.halt = false;
		if ((cpu_mixed & (1 << 1)) > 0) CPU.Flag_Zero = true; else CPU.Flag_Zero = false;
		if ((cpu_mixed & (1 << 2)) > 0) CPU.Flag_Carry = true; else CPU.Flag_Carry = false;
		if ((cpu_mixed & (1 << 3)) > 0) CPU.Flag_Negative = true; else CPU.Flag_Negative = false;
		if ((cpu_mixed & (1 << 4)) > 0) CPU.Flag_V_Overflow = true; else CPU.Flag_V_Overflow = false;
		if ((cpu_mixed & (1 << 5)) > 0) CPU.thumbmode = true; else CPU.thumbmode = false;
		CPU.cpu_mode = CPU.get_mode_from_value(0x10 | ((cpu_mixed >> 6) & 0xF));
		if ((cpu_mixed & (1 << 10)) > 0) CPU.IRQ_disable = true; else CPU.IRQ_disable = false;
		if ((cpu_mixed & (1 << 11)) > 0) CPU.FIQ_disable = true; else CPU.FIQ_disable = false;

		IRP.IRP_Flags = (UInt16)(savestate[index] & 0xFFFF);
		DSRegs.Sect_system.IF.write(IRP.IRP_Flags);

		gpio.bits = (UInt16)((savestate[index++] >> 16) & 0x3F);

		UInt32 eeprom_mix = savestate[index++];
		for (int i = 0; i < 8; i++)
		{
			EEProm.eepromBuffer[i] = (byte)((eeprom_mix >> (7 - i)) & 1);
		}
		EEProm.eepromBits = (int)((eeprom_mix >> 8) & 0xFF);
		EEProm.eepromByte = (int)((eeprom_mix >> 16) & 0x3F);
		EEProm.eepromAddress = (int)((eeprom_mix >> 22) & 0x3FF);

		UInt32 flash_mix = savestate[index++];
		// eeprombitpos
		Flash.flashBank = (byte)((flash_mix >> 3) & 0x1);
		if ((flash_mix & (1 << 4)) > 0) Memory.SramEnabled = false; else Memory.SramEnabled = true;
		if ((flash_mix & (1 << 5)) > 0) Memory.SramEnabled = true; Memory.FlashEnabled = true;
		EEProm.eepromMode = (EEPROMSTATE)((flash_mix >> 6) & 0x7);
		Flash.flashState = (FLASHSTATE)((flash_mix >> 9) & 0xF);
		Flash.flashReadState = (FLASHSTATE)((flash_mix >> 13) & 0xF);

		for (int i = 0; i < 4; i++) { DMA.DMAs[i].addr_source = savestate[index++]; }
		for (int i = 0; i < 4; i++) { DMA.DMAs[i].addr_target = savestate[index++]; }
		for (int i = 0; i < 4; i++)
		{
			UInt32 dmamix = savestate[index++];
			DMA.DMAs[i].count = dmamix & 0x1FFFF;
			if ((dmamix & (1 << 17)) > 0) DMA.DMAs[i].dMA_Enable = true; else DMA.DMAs[i].dMA_Enable = false;
			if ((dmamix & (1 << 18)) > 0) DMA.DMAs[i].running = true; else DMA.DMAs[i].running = false;
			if ((dmamix & (1 << 19)) > 0) DMA.DMAs[i].waiting = true; else DMA.DMAs[i].waiting = false;
			if ((dmamix & (1 << 20)) > 0) DMA.DMAs[i].first = true; else DMA.DMAs[i].first = false;
			DMA.DMAs[i].dest_Addr_Control = (byte)((dmamix >> 21) & 0x3);
			DMA.DMAs[i].source_Adr_Control = (byte)((dmamix >> 23) & 0x3);
			DMA.DMAs[i].dMA_Start_Timing = (byte)((dmamix >> 25) & 0x3);
			if ((dmamix & (1 << 27)) > 0) DMA.DMAs[i].dMA_Repeat = true; else DMA.DMAs[i].dMA_Repeat = false;
			if ((dmamix & (1 << 28)) > 0) DMA.DMAs[i].dMA_Transfer_Type = true; else DMA.DMAs[i].dMA_Transfer_Type = false;
			if ((dmamix & (1 << 29)) > 0) DMA.DMAs[i].iRQ_on = true; else DMA.DMAs[i].iRQ_on = false;
		}

		for (int i = 0; i < 4; i++)
		{
			UInt32 timermix = savestate[index++];

			if ((timermix & (1 << 0)) > 0) Timer.timers[i].on = true; else Timer.timers[i].on = false;
			if ((timermix & (1 << 1)) > 0) Timer.timers[i].startnow = true; else Timer.timers[i].startnow = false;
			Timer.timers[i].value = (int)((timermix >> 2) & 0x1FFFF);
			Timer.timers[i].prescalevalue = (int)((timermix >> 19) & 0x7FF);

			if (Timer.timers[i].on && Timer.timers[i].startnow) { Timer.timers[i].startnow = false; } // different handling in hw
			Timer.timers[i].retval = (UInt16)Timer.timers[i].value;
		}

		UInt32 gpumix = savestate[index++];
		GPU_Timing.cycles = (int)((gpumix >> 0) & 0xFFF);
		GPU_Timing.line = (byte)((gpumix >> 12) & 0xFF);
		GPU_Timing.gpustate = (GPUState)((gpumix >> 20) & 0x3);
		DSRegs.Sect_display.DISPSTAT_V_Blank_flag.write((gpumix >> 22) & 1);
		DSRegs.Sect_display.DISPSTAT_H_Blank_flag.write((gpumix >> 23) & 1);
		DSRegs.Sect_display.DISPSTAT_V_Blank_flag.write((gpumix >> 24) & 1);
		DSRegs.Sect_display.VCOUNT.write(GPU_Timing.line);
		GPU_Timing.old_dispstat = DSRegs.data[4];

		UInt32 gpiomix = savestate[index++];
		gpio.clockslow = (byte)((gpiomix >> 0) & 0xFF);
		gpio.command = (byte)((gpiomix >> 8) & 0xFF);
		gpio.dataLen = (byte)((gpiomix >> 16) & 0x7);
		gpio.enable = (byte)((gpiomix >> 19) & 0x1);
		gpio.retval = (byte)((gpiomix >> 20) & 0xF);
		gpio.select = (byte)((gpiomix >> 24) & 0xF);
		gpio.state = (GPIOState)((gpiomix >> 28) & 0x3);
	}
	*/
}

void Gameboy::exportmem()
{
	//register
	FILE* file = fopen("R:\\regs.csv", "w");
	for (int i = 0; i < Regs_Arm9.allregcount; i++)
	{
		fprintf(file, "0x%08x %-40s(0x%08x)\n", Regs_Arm9.allregs[i].read(), Regs_Arm9.allregs[i].name.c_str(), Regs_Arm9.allregs[i].address);
	}
	for (int i = 0; i < Regs_Arm7.allregcount; i++)
	{
		fprintf(file, "0x%08x %-40s(0x%08x)\n", Regs_Arm7.allregs[i].read(), Regs_Arm7.allregs[i].name.c_str(), Regs_Arm7.allregs[i].address);
	}
	fclose(file);

	// vram
	file = fopen("R:\\vram_a.csv", "w"); for (int i = 0; i < 0x20000; i++) { fprintf(file, "0x%08x 0x%02x\n", 0x6000000 + i, Memory.VRAM[0x00000 + i]); } fclose(file);
	file = fopen("R:\\vram_b.csv", "w"); for (int i = 0; i < 0x20000; i++) { fprintf(file, "0x%08x 0x%02x\n", 0x6020000 + i, Memory.VRAM[0x20000 + i]); } fclose(file);
	file = fopen("R:\\vram_c.csv", "w"); for (int i = 0; i < 0x20000; i++) { fprintf(file, "0x%08x 0x%02x\n", 0x6040000 + i, Memory.VRAM[0x40000 + i]); } fclose(file);
	file = fopen("R:\\vram_d.csv", "w"); for (int i = 0; i < 0x20000; i++) { fprintf(file, "0x%08x 0x%02x\n", 0x6060000 + i, Memory.VRAM[0x60000 + i]); } fclose(file);
	file = fopen("R:\\vram_e.csv", "w"); for (int i = 0; i < 0x10000; i++) { fprintf(file, "0x%08x 0x%02x\n", 0x6080000 + i, Memory.VRAM[0x80000 + i]); } fclose(file);
	file = fopen("R:\\vram_f.csv", "w"); for (int i = 0; i < 0x04000; i++) { fprintf(file, "0x%08x 0x%02x\n", 0x6090000 + i, Memory.VRAM[0x90000 + i]); } fclose(file);
	file = fopen("R:\\vram_g.csv", "w"); for (int i = 0; i < 0x04000; i++) { fprintf(file, "0x%08x 0x%02x\n", 0x6094000 + i, Memory.VRAM[0x94000 + i]); } fclose(file);
	file = fopen("R:\\vram_h.csv", "w"); for (int i = 0; i < 0x08000; i++) { fprintf(file, "0x%08x 0x%02x\n", 0x6098000 + i, Memory.VRAM[0x98000 + i]); } fclose(file);
	file = fopen("R:\\vram_i.csv", "w"); for (int i = 0; i < 0x04000; i++) { fprintf(file, "0x%08x 0x%02x\n", 0x60A0000 + i, Memory.VRAM[0xA0000 + i]); } fclose(file);

	file = fopen("R:\\palette.csv", "w"); for (int i = 0; i < 2048; i++) { fprintf(file, "0x%08x 0x%02x\n", 0x5000000 + i, Memory.PaletteRAM[0x00000 + i]); } fclose(file);
	file = fopen("R:\\oam.csv", "w");     for (int i = 0; i < 2048; i++) { fprintf(file, "0x%08x 0x%02x\n", 0x7000000 + i, Memory.OAMRAM[0x00000 + i]); }     fclose(file);

	file = fopen("R:\\vram_a_32.csv", "w"); for (int i = 0; i < 0x20000; i+=4) { fprintf(file, "0x%08x 0x%08x\n", 0x6000000 + i, *(UInt32*)&Memory.VRAM[0x00000 + i]); } fclose(file);
	file = fopen("R:\\vram_b_32.csv", "w"); for (int i = 0; i < 0x20000; i+=4) { fprintf(file, "0x%08x 0x%08x\n", 0x6020000 + i, *(UInt32*)&Memory.VRAM[0x20000 + i]); } fclose(file);
	file = fopen("R:\\vram_c_32.csv", "w"); for (int i = 0; i < 0x20000; i+=4) { fprintf(file, "0x%08x 0x%08x\n", 0x6040000 + i, *(UInt32*)&Memory.VRAM[0x40000 + i]); } fclose(file);
	file = fopen("R:\\vram_d_32.csv", "w"); for (int i = 0; i < 0x20000; i+=4) { fprintf(file, "0x%08x 0x%08x\n", 0x6060000 + i, *(UInt32*)&Memory.VRAM[0x60000 + i]); } fclose(file);
	file = fopen("R:\\vram_e_32.csv", "w"); for (int i = 0; i < 0x10000; i+=4) { fprintf(file, "0x%08x 0x%08x\n", 0x6080000 + i, *(UInt32*)&Memory.VRAM[0x80000 + i]); } fclose(file);
	file = fopen("R:\\vram_f_32.csv", "w"); for (int i = 0; i < 0x04000; i+=4) { fprintf(file, "0x%08x 0x%08x\n", 0x6090000 + i, *(UInt32*)&Memory.VRAM[0x90000 + i]); } fclose(file);
	file = fopen("R:\\vram_g_32.csv", "w"); for (int i = 0; i < 0x04000; i+=4) { fprintf(file, "0x%08x 0x%08x\n", 0x6094000 + i, *(UInt32*)&Memory.VRAM[0x94000 + i]); } fclose(file);
	file = fopen("R:\\vram_h_32.csv", "w"); for (int i = 0; i < 0x08000; i+=4) { fprintf(file, "0x%08x 0x%08x\n", 0x6098000 + i, *(UInt32*)&Memory.VRAM[0x98000 + i]); } fclose(file);
	file = fopen("R:\\vram_i_32.csv", "w"); for (int i = 0; i < 0x04000; i+=4) { fprintf(file, "0x%08x 0x%08x\n", 0x60A0000 + i, *(UInt32*)&Memory.VRAM[0xA0000 + i]); } fclose(file);

	file = fopen("R:\\palette_32.csv", "w"); for (int i = 0; i < 2048; i+=4) { fprintf(file, "0x%08x 0x%08x\n", 0x5000000 + i, *(UInt32*)&Memory.PaletteRAM[0x00000 + i]); } fclose(file);
	file = fopen("R:\\oam_32.csv", "w");     for (int i = 0; i < 2048; i+=4) { fprintf(file, "0x%08x 0x%08x\n", 0x7000000 + i, *(UInt32*)&Memory.OAMRAM[0x00000 + i]); }     fclose(file);
}