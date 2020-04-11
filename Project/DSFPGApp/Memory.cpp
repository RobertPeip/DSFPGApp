#include "Memory.h"
#include "CPU.h"
#include "DMA.h"
#include "regs_arm9.h"
#include "regs_arm7.h"
#include "EEProm.h"
#include "Flash.h"
#include "GPU.h"
#include "GPU_Timing.h"
#include "gpio.h"
#include "fileIO.h"
#include "Timer.h"
#include "gameboy.h"
#include "BusTiming.h"
#include "IRP.h"
#include "Sound.h"
#include "SoundDMA.h"
#include "Joypad.h"
#include "Serial.h"
#include "Header.h"
#include "spi_intern.h"
#include "IPC.h"

MEMORY Memory;

void MEMORY::reset(string filename)
{
	FileIO.readfile(Bios7, "bios7.bin", false);
	FileIO.readfile(Bios9, "bios9.bin", false);

	// read in and analyze rom
	GameRom_max = FileIO.readfile(GameRom, filename, true);
	Header.read();

	for (int i = 0; i < Header.ARM9_CODE_SIZE; i += 4)
	{
		uint data = *(UInt32*)&Memory.GameRom[Header.ARM9_CODE_SRC + i];
		write_dword_9(ACCESSTYPE::CPUDATA, Header.ARM9_CODE_DST + i, data);
	}
	for (int i = 0; i < Header.ARM7_CODE_SIZE; i += 4)
	{
		uint data = *(UInt32*)&Memory.GameRom[Header.ARM7_CODE_SRC + i];
		write_dword_7(ACCESSTYPE::CPUDATA, Header.ARM7_CODE_DST + i, data);
	}

	EEPROMEnabled = true;
	FlashEnabled = true;
	SramEnabled = true;
	EEPROMSensorEnabled = false;

	tiltx = 0x3A0;
	tilty = 0x3A0;

	gpio_used = false;
	//gpio.rtcEnable(true);

	load_gameram(filename);
}

void MEMORY::GameRAMSnapshot()
{
	if (createGameRAMSnapshot)
	{
		int index = 0;
		for (int i = 0; i < 131072; i++)
		{
			GameRamSnapshot[index] = Flash.flashSaveMemory[i];
			index++;
		}
		for (int i = 0; i < 8192; i++)
		{
			GameRamSnapshot[index] = EEProm.eepromData[i];
			index++;
		}

		save_gameram(gameboy.filename);

		createGameRAMSnapshot = false;
	}
}


void MEMORY::load_gameram(string gamename)
{
	string filename = gamename.substr(gamename.find_last_of("/\\") + 1);
	filename = filename.substr(0, filename.find_last_of(".") + 1) + "sav";

	if (FileIO.fileExists(filename, false))
	{
		FileIO.readfile(GameRamSnapshot, filename, false);
		int index = 0;
		for (int i = 0; i < 131072; i++)
		{
			Flash.flashSaveMemory[i] = GameRamSnapshot[index];
			index++;
		}
		for (int i = 0; i < 8192; i++)
		{
			EEProm.eepromData[i] = GameRamSnapshot[index];
			index++;
		}
	}
}

void MEMORY::save_gameram(string gamename)
{
	string filename = gamename.substr(gamename.find_last_of("/\\") + 1);
	filename = filename.substr(0, filename.find_last_of(".") + 1) + "sav";

	FileIO.writefile(GameRamSnapshot, filename, 131072 + 8192, false);
}

byte MEMORY::read_unreadable_byte(UInt32 offset)
{
	return 0;

	//byte value;
	//
	//if (CPU9.thumbmode && ((CPU9.regs[15] >> 24) & 15) == 3)
	//{
	//	if ((CPU9.regs[15] & 0x3) == 0)
	//	{
	//		value = read_byte(CPU9.regs[15] - 2 + offset);
	//	}
	//	else
	//	{
	//		value = read_byte(CPU9.regs[15] + offset);
	//	}
	//}
	//else
	//{
	//	value = read_byte(CPU9.regs[15] + offset);
	//}
	//
	//unreadable = true;
	//
	//return value;
}

UInt16 MEMORY::read_unreadable_word()
{
	return 0;

	//UInt16 value;
	//if (CPU9.thumbmode && ((CPU9.regs[15] >> 24) & 15) == 3)
	//{
	//	if ((CPU9.regs[15] & 0x3) == 0)
	//	{
	//		value = (UInt16)read_word(CPU9.regs[15] - 2);
	//	}
	//	else
	//	{
	//		value = (UInt16)read_word(CPU9.regs[15]);
	//	}
	//}
	//else
	//{
	//	value = (UInt16)read_word(CPU9.regs[15]);
	//}
	//
	//unreadable = true;
	//
	//return value;
}

UInt32 MEMORY::read_unreadable_dword()
{
	return 0;

	//if (CPU9.op_since_dma < 2)
	//{
	//	return DMA.last_dma_value;
	//}
	//
	//UInt32 value;
	//
	//if (CPU9.thumbmode)
	//{
	//	//For THUMB code in 32K - WRAM on GBA, GBA SP, GBA Micro, NDS-Lite(but not NDS):
		//LSW = [$+4], MSW = OldHI   ; for opcodes at 4 - byte aligned locations
		//LSW = OldLO, MSW = [$+4]   ; for opcodes at non - 4 - byte aligned locations
		//OldLO=[$+2], OldHI=[$+2]
	//	if (((CPU9.regs[15] >> 24) & 15) == 3)
	//	{
	//		if ((CPU9.regs[15] & 0x3) == 0)
	//		{
	//			UInt32 retval_low = read_word(CPU9.regs[15]) & 0xFFFF;
	//			UInt32 retval_high = read_word(CPU9.regs[15] - 2) & 0xFFFF;
	//			value = retval_high << 16 | retval_low;
	//		}
	//		else
	//		{
	//			UInt32 retval_low = read_word(CPU9.regs[15] - 2) & 0xFFFF;
	//			UInt32 retval_high = read_word(CPU9.regs[15]) & 0xFFFF;
	//			value = retval_high << 16 | retval_low;
	//		}
	//	}
	//	else // standard case LSW = [$+4], MSW = [$+4]
	//	{
	//		UInt32 retval = read_word(CPU9.regs[15]);
	//		value = retval << 16 | retval;
	//	}
	//}
	//else
	//{
	//	value = read_dword(CPU9.regs[15]);
	//}
	//
	//unreadable = true;
	//
	//return value;
}

byte read_byte_9(ACCESSTYPE accesstype, UInt32 address)
{
	Memory.unreadable = false;
	uint adr;

	byte select = (byte)(address >> 24);
	switch (select)
	{
	case 0:
	case 1:
		if (accesstype == ACCESSTYPE::CPUINSTRUCTION || accesstype == ACCESSTYPE::CPUDATA)
		{
			return Memory.ITCM[address & 0x7FFF];
		}
		return 0;

	case 2:
		if ((address & (~0x3FFF)) == Co15.DTCMRegion)
		{
			return Memory.DTCM[address & 0x3FFF];
		}
		else
		{
			return Memory.WRAM_Large[address & 0x03FFFFF];
		}

	case 3: 
		if (address < 0x3800000)
		{
			adr = address & 0x7FFF;
			return Memory.WRAM_Small[adr]; break;
		}
		else
		{
			adr = address & 0xFFFF;
			return Memory.WRAM_Small[0x8000 + adr]; break;
		}
		
	case 4:
		if (address < 0x04000400)
		{
			adr = address & 0x3FF;
			byte rwmask = Regs_Arm9.rwmask[adr];

			if (rwmask == 0)
			{
				return Memory.read_unreadable_byte(address & 1);
			}
			else
			{
				Memory.prepare_read_DSReg9(adr);
				byte value = Regs_Arm9.data[adr];
				value &= rwmask;
				return value;
			}
		}
		else
		{
			return Memory.read_unreadable_byte(address & 1);
		}

	case 5: return Memory.PaletteRAM[address & 0x3FF];

	case 6:
		adr = address & 0x1FFFF;
		if (adr > 0x17FFF) { adr -= 0x8000; }
		return Memory.VRAM[adr & 0x1FFFF];

	case 7: return Memory.OAMRAM[address & 0x3FF];

	case 0xF: return Memory.Bios9[address & 0xFFF];

	default: return 0xFF;

	}
}

UInt32 read_word_9(ACCESSTYPE accesstype, UInt32 address)
{
	Memory.unreadable = false;

	UInt32 value = 0;
	byte rotate = (byte)(address & 1);
	address = address & 0xFFFFFFFE;
	uint adr;

	byte select = (byte)(address >> 24);
	switch (select)
	{
	case 0:
	case 1:
		if (accesstype == ACCESSTYPE::CPUINSTRUCTION || accesstype == ACCESSTYPE::CPUDATA)
		{
			value = *(UInt16*)&Memory.ITCM[address & 0x7FFF];
		}
		break;

	case 2:
		if ((address & (~0x3FFF)) == Co15.DTCMRegion)
		{
			value = *(UInt16*)&Memory.DTCM[address & 0x3FFF];
		}
		else
		{
			value = *(UInt16*)&Memory.WRAM_Large[address & 0x03FFFFF];
		}
		break;

	case 3: 
		if (address < 0x3800000)
		{
			adr = address & 0x7FFF;
			value = *(UInt16*)&Memory.WRAM_Small[adr]; break;
		}
		else
		{
			adr = address & 0xFFFF;
			value = *(UInt16*)&Memory.WRAM_Small[0x8000 + adr]; break;
		}
		
	case 4:
		if (address < 0x04000400)
		{
			adr = address & 0x3FF;

			if (adr == Regs_Arm9.Sect_dma9.DMA0CNT_L.address ||
				adr == Regs_Arm9.Sect_dma9.DMA1CNT_L.address ||
				adr == Regs_Arm9.Sect_dma9.DMA2CNT_L.address ||
				adr == Regs_Arm9.Sect_dma9.DMA3CNT_L.address)
			{
				return 0;
			}
			else
			{
				UInt16 rwmask = *(UInt16*)&Regs_Arm9.rwmask[adr & 0x3FFE];

				if (rwmask == 0)
				{
					value = Memory.read_unreadable_word();
				}
				else
				{
					Memory.prepare_read_DSReg9(adr);
					value = *(UInt16*)&Regs_Arm9.data[adr];
					value &= rwmask;
				}
			}
		}
		else
		{
			value = Memory.read_unreadable_word();
		}
		break;

	case 5: value = *(UInt16*)&Memory.PaletteRAM[address & 0x3FF]; break;

	case 6:
		adr = address & 0x1FFFF;
		if (adr > 0x17FFF) { adr -= 0x8000; }
		value = *(UInt16*)&Memory.VRAM[adr];
		break;

	case 7: value = *(UInt16*)&Memory.OAMRAM[address & 0x3FF]; break;

	case 0xFF: value = *(UInt16*)&Memory.Bios9[address & 0xFFF]; break;

	default: value = 0xFFFF; break;
	}

	Memory.lastreadvalue = value;

	if (rotate == 0)
	{
		return value;
	}
	else
	{
		value = ((value & 0xFF) << 24) | (value >> 8);
	}

	return value;
}

UInt32 read_dword_9(ACCESSTYPE accesstype, UInt32 address)
{
	Memory.unreadable = false;

	UInt32 value = 0;
	byte rotate = (byte)(address & 3);
	address = address & 0xFFFFFFFC;
	uint adr;

	byte select = (byte)(address >> 24);
	switch (select)
	{
	case 0:
	case 1: 
		if (accesstype == ACCESSTYPE::CPUINSTRUCTION || accesstype == ACCESSTYPE::CPUDATA)
		{
			value = *(UInt32*)&Memory.ITCM[address & 0x7FFF];
		}
		break;

	case 2:
		if ((address & (~0x3FFF)) == Co15.DTCMRegion)
		{
			value = *(UInt32*)&Memory.DTCM[address & 0x3FFF];
		}
		else
		{
			value = *(UInt32*)&Memory.WRAM_Large[address & 0x03FFFFF];
		}
		break;

	case 3:
		if (address < 0x3800000)
		{
			adr = address & 0x7FFF;
			value = *(UInt32*)&Memory.WRAM_Small[adr]; break;
		}
		else
		{
			adr = address & 0xFFFF;
			value = *(UInt32*)&Memory.WRAM_Small[0x8000 + adr]; break;
		}

	case 4:
		if (address < 0x04000400)
		{
			value = (UInt16)read_word_9(accesstype, address) | (read_word_9(accesstype, address + 2) << 16);
		}
		else if (address == 0x04100000)
		{
			value = IPC7to9.readfifo();
		}
		else
		{
			value = Memory.read_unreadable_dword();
		}
		break;

	case 5: value = *(UInt32*)&Memory.PaletteRAM[address & 0x3FF]; break;

	case 6:
		adr = address & 0x1FFFF;
		if (adr > 0x17FFF) { adr -= 0x8000; }
		value = *(UInt32*)&Memory.VRAM[adr];
		break;

	case 7: value = *(UInt32*)&Memory.OAMRAM[address & 0x3FF]; break;

	case 0xFF: value = *(UInt32*)&Memory.Bios9[address & 0xFFF]; break;

	default: value = 0xFFFFFFFF; break;
	}

	Memory.lastreadvalue = value;

	if (rotate == 0)
	{
		return value;
	}
	else
	{
		value = CPU9.RotateRight(value, 8 * rotate);
	}

	return value;
}

void write_byte_9(ACCESSTYPE accesstype, UInt32 address, byte data)
{
	uint adr;
	byte select = (byte)(address >> 24);
	switch (select)
	{
	case 0:
	case 1:
		if (accesstype == ACCESSTYPE::CPUDATA)
		{
			adr = address & 0x7FFF;
			Memory.ITCM[adr] = data;
		}
		return;

	case 2:
		if ((address & (~0x3FFF)) == Co15.DTCMRegion)
		{
			adr = address & 0x3FFF;
			Memory.DTCM[adr] = (byte)(data & 0xFF);
		}
		else
		{
			adr = address & 0x03FFFFF;
			Memory.WRAM_Large[adr] = (byte)(data & 0xFF);
		}
		return;

	case 3: 
		if (address < 0x3800000)
		{
			adr = address & 0x7FFF;
			Memory.WRAM_Small[adr] = (byte)(data & 0xFF);
		}
		else
		{
			adr = address & 0xFFFF;
			Memory.WRAM_Small[0x8000 + adr] = (byte)(data & 0xFF);
			return;
		}

	case 4:
		if (address < 0x04000400)
		{
			adr = address & 0x3FF;
			Regs_Arm9.data[adr] = data;
			Memory.write_DSReg9(adr & 0xFFFFFFFE, data, false);
		}
		return;

		// Writing 8bit Data to Video Memory
		// Video Memory(BG, OBJ, OAM, Palette) can be written to in 16bit and 32bit units only.Attempts to write 8bit data(by STRB opcode) won't work:
		// Writes to OBJ(6010000h - 6017FFFh)(or 6014000h - 6017FFFh in Bitmap mode) and to OAM(7000000h - 70003FFh) are ignored, the memory content remains unchanged.
		// Writes to BG(6000000h - 600FFFFh)(or 6000000h - 6013FFFh in Bitmap mode) and to Palette(5000000h - 50003FFh) are writing the new 8bit value to BOTH upper and lower 8bits of the addressed halfword, ie. "[addr AND NOT 1]=data*101h".

	case 5: Memory.PaletteRAM[address & 0x3FE] = data; Memory.PaletteRAM[(address & 0x3FE) + 1] = data; return;

	case 6:
		adr = address & 0x1FFFE;
		if ((GPU.videomode <= 2 && adr <= 0xFFFF) || GPU.videomode >= 3 && adr <= 0x013FFF)
		{
			if (adr > 0x17FFF) { adr -= 0x8000; }
			Memory.VRAM[adr] = data;
			Memory.VRAM[adr + 1] = data;
		}
		return;

	case 7: return; // no saving here!
	}
}

void write_word_9(ACCESSTYPE accesstype, UInt32 address, UInt16 data)
{
	byte offset = (byte)(address & 1);
	address = address & 0xFFFFFFFE;
	uint adr;

	byte select = (byte)(address >> 24);
	switch (select)
	{
	case 0:
	case 1:
		if (accesstype == ACCESSTYPE::CPUDATA)
		{
			adr = address & 0x7FFF;
			Memory.ITCM[adr] = (byte)(data & 0xFF);
			Memory.ITCM[adr + 1] = (byte)((data >> 8) & 0xFF);
		}
		return;

	case 2:
		if ((address & (~0x3FFF)) == Co15.DTCMRegion)
		{
			adr = address & 0x3FFF;
			Memory.DTCM[adr] = (byte)(data & 0xFF);
			Memory.DTCM[adr + 1] = (byte)((data >> 8) & 0xFF);
		}
		else
		{
			adr = address & 0x03FFFFF;
			Memory.WRAM_Large[adr] = (byte)(data & 0xFF);
			Memory.WRAM_Large[adr + 1] = (byte)((data >> 8) & 0xFF);
		}
		return;

	case 3:
		if (address < 0x3800000)
		{
			adr = address & 0x7FFF;
			Memory.WRAM_Small[adr] = (byte)(data & 0xFF);
			Memory.WRAM_Small[adr + 1] = (byte)((data >> 8) & 0xFF);
		}
		else
		{
			adr = address & 0xFFFF;
			Memory.WRAM_Small[0x8000 + adr] = (byte)(data & 0xFF);
			Memory.WRAM_Small[0x8000 + adr + 1] = (byte)((data >> 8) & 0xFF);
		}
		return;

	case 4:
		if (address < 0x04000400)
		{
			adr = address & 0x3FF;
			Regs_Arm9.data[adr] = (byte)(data & 0xFF);
			Regs_Arm9.data[adr + 1] = (byte)((data >> 8) & 0xFF);
			Memory.write_DSReg9(adr, data, false);
		}
		return;

	case 5:
		adr = address & 0x3FF;
		Memory.PaletteRAM[adr] = (byte)(data & 0xFF);
		Memory.PaletteRAM[adr + 1] = (byte)((data >> 8) & 0xFF);
		return;

	case 6:
		adr = address & 0x1FFFF;
		if (GPU.videomode < 3 || ((address & 0x1C000) != 0x18000))
		{
			if (adr > 0x17FFF) { adr -= 0x8000; }
			Memory.VRAM[adr] = (byte)(data & 0xFF);
			Memory.VRAM[adr + 1] = (byte)((data >> 8) & 0xFF);
		}
		return;

	case 7:
		adr = address & 0x3FF;
		Memory.OAMRAM[adr] = (byte)(data & 0xFF);
		Memory.OAMRAM[adr + 1] = (byte)((data >> 8) & 0xFF);
		return;
	}
}

void write_dword_9(ACCESSTYPE accesstype, UInt32 address, UInt32 data)
{
	byte offset = (byte)(address & 3);
	address = address & 0xFFFFFFFC;
	uint adr;

	byte select = (byte)(address >> 24);
	switch (select)
	{
	case 0:
	case 1:
		if (accesstype == ACCESSTYPE::CPUDATA)
		{
			adr = address & 0x7FFF;
			Memory.ITCM[adr] = (byte)(data & 0xFF);
			Memory.ITCM[adr + 1] = (byte)((data >> 8) & 0xFF);
			Memory.ITCM[adr + 2] = (byte)((data >> 16) & 0xFF);
			Memory.ITCM[adr + 3] = (byte)((data >> 24) & 0xFF);
		}
		return;

	case 2:
		if ((address & (~0x3FFF)) == Co15.DTCMRegion)
		{
			adr = address & 0x3FFF;
			Memory.DTCM[adr] = (byte)(data & 0xFF);
			Memory.DTCM[adr + 1] = (byte)((data >> 8) & 0xFF);
			Memory.DTCM[adr + 2] = (byte)((data >> 16) & 0xFF);
			Memory.DTCM[adr + 3] = (byte)((data >> 24) & 0xFF);
		}
		else
		{
			adr = address & 0x03FFFFF;
			Memory.WRAM_Large[adr] = (byte)(data & 0xFF);
			Memory.WRAM_Large[adr + 1] = (byte)((data >> 8) & 0xFF);
			Memory.WRAM_Large[adr + 2] = (byte)((data >> 16) & 0xFF);
			Memory.WRAM_Large[adr + 3] = (byte)((data >> 24) & 0xFF);
		}
		return;

	case 3:
		if (address < 0x3800000)
		{
			adr = address & 0x7FFF;
			Memory.WRAM_Small[adr] = (byte)(data & 0xFF);
			Memory.WRAM_Small[adr + 1] = (byte)((data >> 8) & 0xFF);
			Memory.WRAM_Small[adr + 2] = (byte)((data >> 16) & 0xFF);
			Memory.WRAM_Small[adr + 3] = (byte)((data >> 24) & 0xFF);
		}
		else
		{
			adr = address & 0xFFFF;
			Memory.WRAM_Small[0x8000 + adr] = (byte)(data & 0xFF);
			Memory.WRAM_Small[0x8000 + adr + 1] = (byte)((data >> 8) & 0xFF);
			Memory.WRAM_Small[0x8000 + adr + 2] = (byte)((data >> 16) & 0xFF);
			Memory.WRAM_Small[0x8000 + adr + 3] = (byte)((data >> 24) & 0xFF);
		}
		return;

	case 4:
		if (address < 0x04000400)
		{
			adr = address & 0x3FF;

			Regs_Arm9.data[adr] = (byte)(data & 0xFF);
			Regs_Arm9.data[adr + 1] = (byte)((data >> 8) & 0xFF);
			Regs_Arm9.data[adr + 2] = (byte)((data >> 16) & 0xFF);
			Regs_Arm9.data[adr + 3] = (byte)((data >> 24) & 0xFF);

			Memory.write_DSReg9(adr, data, true);
			Memory.write_DSReg9(adr + 2, data, true);
		}
		return;

	case 5:
		adr = address & 0x3FF;
		Memory.PaletteRAM[adr] = (byte)(data & 0xFF);
		Memory.PaletteRAM[adr + 1] = (byte)((data >> 8) & 0xFF);
		Memory.PaletteRAM[adr + 2] = (byte)((data >> 16) & 0xFF);
		Memory.PaletteRAM[adr + 3] = (byte)((data >> 24) & 0xFF);
		return;

	case 6:
		adr = address & 0x1FFFF;
		if (GPU.videomode < 3 || ((address & 0x1C000) != 0x18000))
		{
			if (adr > 0x17FFF) { adr -= 0x8000; }
			Memory.VRAM[adr] = (byte)(data & 0xFF);
			Memory.VRAM[adr + 1] = (byte)((data >> 8) & 0xFF);
			Memory.VRAM[adr + 2] = (byte)((data >> 16) & 0xFF);
			Memory.VRAM[adr + 3] = (byte)((data >> 24) & 0xFF);
		}
		return;

	case 7:
		adr = address & 0x3FF;
		Memory.OAMRAM[adr] = (byte)(data & 0xFF);
		Memory.OAMRAM[adr + 1] = (byte)((data >> 8) & 0xFF);
		Memory.OAMRAM[adr + 2] = (byte)((data >> 16) & 0xFF);
		Memory.OAMRAM[adr + 3] = (byte)((data >> 24) & 0xFF);
		return;
	}
}

byte read_byte_7(ACCESSTYPE accesstype, UInt32 address)
{
	Memory.unreadable = false;
	uint adr;

	byte select = (byte)(address >> 24);
	switch (select)
	{
	case 0:
		return Memory.Bios7[address & 0x3FFF];

	case 1: return Memory.read_unreadable_byte(address & 1);
	case 2: return Memory.WRAM_Large[address & 0x03FFFFF];
	case 3:
		if (address < 0x3800000)
		{
			adr = address & 0x7FFF;
			return Memory.WRAM_Small[adr]; break;
		}
		else
		{
			adr = address & 0xFFFF;
			return Memory.WRAM_Small[0x8000 + adr]; break;
		}

	case 4:
		if (address < 0x04000400)
		{
			adr = address & 0x3FF;

			if (adr == Regs_Arm7.Sect_system7.RTC_reg.address)
			{
				return 0;
			}

			byte rwmask = Regs_Arm7.rwmask[adr];

			if (rwmask == 0)
			{
				return Memory.read_unreadable_byte(address & 1);
			}
			else
			{
				Memory.prepare_read_DSReg7(adr);
				byte value = Regs_Arm7.data[adr];
				value &= rwmask;
				return value;
			}
		}
		else
		{
			return Memory.read_unreadable_byte(address & 1);
		}

	case 5: return Memory.PaletteRAM[address & 0x3FF];

	case 6:
		adr = address & 0x1FFFF;
		if (adr > 0x17FFF) { adr -= 0x8000; }
		return Memory.VRAM[adr & 0x1FFFF];

	case 7: return Memory.OAMRAM[address & 0x3FF];

	case 8:
	case 9:
	case 0xA:
	case 0xB:
	case 0xC:
	case 0xD:
	case 0xE:
	case 0xF:
		return 0xFF;

	default: return Memory.read_unreadable_byte(address & 1);

	}
}

UInt32 read_word_7(ACCESSTYPE accesstype, UInt32 address)
{
	Memory.unreadable = false;

	UInt32 value = 0;
	byte rotate = (byte)(address & 1);
	address = address & 0xFFFFFFFE;
	uint adr;

	byte select = (byte)(address >> 24);
	switch (select)
	{
	case 0:
		value = *(UInt16*)&Memory.Bios7[address & 0x3FFE];
		break;

	case 1: value = Memory.read_unreadable_word(); break;
	case 2: value = *(UInt16*)&Memory.WRAM_Large[address & 0x03FFFFF]; break;
	case 3:
		if (address < 0x3800000)
		{
			adr = address & 0x7FFF;
			value = *(UInt16*)&Memory.WRAM_Small[adr]; break;
		}
		else
		{
			adr = address & 0xFFFF;
			value = *(UInt16*)&Memory.WRAM_Small[0x8000 + adr]; break;
		}

	case 4:
		if (address < 0x04000400)
		{
			adr = address & 0x3FF;

			if (adr == Regs_Arm7.Sect_dma7.DMA0CNT_L.address ||
				adr == Regs_Arm7.Sect_dma7.DMA1CNT_L.address ||
				adr == Regs_Arm7.Sect_dma7.DMA2CNT_L.address ||
				adr == Regs_Arm7.Sect_dma7.DMA3CNT_L.address || 
				adr == Regs_Arm7.Sect_system7.RTC_reg.address)
			{
				return 0;
			}
			else
			{
				UInt16 rwmask = *(UInt16*)&Regs_Arm7.rwmask[adr & 0x3FFE];

				if (rwmask == 0)
				{
					value = Memory.read_unreadable_word();
				}
				else
				{
					Memory.prepare_read_DSReg7(adr);
					value = *(UInt16*)&Regs_Arm7.data[adr];
					value &= rwmask;
				}
			}
		}
		else
		{
			value = Memory.read_unreadable_word();
		}
		break;

	case 5: value = *(UInt16*)&Memory.PaletteRAM[address & 0x3FF]; break;

	case 6:
		adr = address & 0x1FFFF;
		if (adr > 0x17FFF) { adr -= 0x8000; }
		value = *(UInt16*)&Memory.VRAM[adr];
		break;

	case 7: value = *(UInt16*)&Memory.OAMRAM[address & 0x3FF]; break;

	case 8:
	case 9:
	case 0xA:
	case 0xB:
	case 0xC:
	case 0xD:
	case 0xE:
	case 0xF:
		value = 0xFFFF;
		break;

	default: value = Memory.read_unreadable_word(); break;
	}

	Memory.lastreadvalue = value;

	if (rotate == 0)
	{
		return value;
	}
	else
	{
		value = ((value & 0xFF) << 24) | (value >> 8);
	}

	return value;
}

UInt32 read_dword_7(ACCESSTYPE accesstype, UInt32 address)
{
	Memory.unreadable = false;

	UInt32 value = 0;
	byte rotate = (byte)(address & 3);
	address = address & 0xFFFFFFFC;
	uint adr;

	byte select = (byte)(address >> 24);
	switch (select)
	{
	case 0:
		value = *(UInt32*)&Memory.Bios7[address & 0x3FFC];
		break;

	case 1: value = Memory.read_unreadable_dword(); break;
	case 2: value = *(UInt32*)&Memory.WRAM_Large[address & 0x03FFFFF]; break;
	case 3:
		if (address < 0x3800000)
		{
			adr = address & 0x7FFF;
			value = *(UInt32*)&Memory.WRAM_Small[adr]; break;
		}
		else
		{
			adr = address & 0xFFFF;
			value = *(UInt32*)&Memory.WRAM_Small[0x8000 + adr]; break;
		}

	case 4:
		if (address < 0x04000400)
		{
			value = (UInt16)read_word_7(accesstype, address) | (read_word_7(accesstype, address + 2) << 16);
		}
		else if (address == 0x04100000)
		{
			value = IPC9to7.readfifo();
		}
		else
		{
			value = Memory.read_unreadable_dword();
		}
		break;

	case 5: value = *(UInt32*)&Memory.PaletteRAM[address & 0x3FF]; break;

	case 6:
		adr = address & 0x1FFFF;
		if (adr > 0x17FFF) { adr -= 0x8000; }
		value = *(UInt32*)&Memory.VRAM[adr];
		break;

	case 7: value = *(UInt32*)&Memory.OAMRAM[address & 0x3FF]; break;

	case 8:
	case 9:
	case 0xA:
	case 0xB:
	case 0xC:
	case 0xD:
	case 0xE:
	case 0xF:
		value = 0xFFFFFFFF;
		break;

	default: value = Memory.read_unreadable_dword(); break;
	}

	Memory.lastreadvalue = value;

	if (rotate == 0)
	{
		return value;
	}
	else
	{
		value = CPU9.RotateRight(value, 8 * rotate);
	}

	return value;
}

void write_byte_7(ACCESSTYPE accesstype, UInt32 address, byte data)
{
	uint adr;
	byte select = (byte)(address >> 24);
	switch (select)
	{
	case 2: Memory.WRAM_Large[address & 0x03FFFFF] = (byte)(data & 0xFF); return;
	case 3:
		if (address < 0x3800000)
		{
			adr = address & 0x7FFF;
			Memory.WRAM_Small[adr] = (byte)(data & 0xFF);
		}
		else
		{
			adr = address & 0xFFFF;
			Memory.WRAM_Small[0x8000 + adr] = (byte)(data & 0xFF);
			return;
		}

	case 4:
		if (address < 0x04000400)
		{
			adr = address & 0x3FF;
			Regs_Arm7.data[adr] = data;
			Memory.write_DSReg7(adr & 0xFFFFFFFE, data, false);
		}
		return;

		// Writing 8bit Data to Video Memory
		// Video Memory(BG, OBJ, OAM, Palette) can be written to in 16bit and 32bit units only.Attempts to write 8bit data(by STRB opcode) won't work:
		// Writes to OBJ(6010000h - 6017FFFh)(or 6014000h - 6017FFFh in Bitmap mode) and to OAM(7000000h - 70003FFh) are ignored, the memory content remains unchanged.
		// Writes to BG(6000000h - 600FFFFh)(or 6000000h - 6013FFFh in Bitmap mode) and to Palette(5000000h - 50003FFh) are writing the new 8bit value to BOTH upper and lower 8bits of the addressed halfword, ie. "[addr AND NOT 1]=data*101h".

	case 5: Memory.PaletteRAM[address & 0x3FE] = data; Memory.PaletteRAM[(address & 0x3FE) + 1] = data; return;

	case 6:
		adr = address & 0x1FFFE;
		if ((GPU.videomode <= 2 && adr <= 0xFFFF) || GPU.videomode >= 3 && adr <= 0x013FFF)
		{
			if (adr > 0x17FFF) { adr -= 0x8000; }
			Memory.VRAM[adr] = data;
			Memory.VRAM[adr + 1] = data;
		}
		return;

	case 7: return; // no saving here!
	}
}

void write_word_7(ACCESSTYPE accesstype, UInt32 address, UInt16 data)
{
	byte offset = (byte)(address & 1);
	address = address & 0xFFFFFFFE;
	uint adr;

	byte select = (byte)(address >> 24);
	switch (select)
	{
	case 2:
		adr = address & 0x03FFFFF;
		Memory.WRAM_Large[adr] = (byte)(data & 0xFF);
		Memory.WRAM_Large[adr + 1] = (byte)((data >> 8) & 0xFF);
		return;

	case 3:
		if (address < 0x3800000)
		{
			adr = address & 0x7FFF;
			Memory.WRAM_Small[adr] = (byte)(data & 0xFF);
			Memory.WRAM_Small[adr + 1] = (byte)((data >> 8) & 0xFF);
		}
		else
		{
			adr = address & 0xFFFF;
			Memory.WRAM_Small[0x8000 + adr] = (byte)(data & 0xFF);
			Memory.WRAM_Small[0x8000 + adr + 1] = (byte)((data >> 8) & 0xFF);
		}
		return;

	case 4:
		if (address < 0x04000400)
		{
			adr = address & 0x3FF;
			Regs_Arm7.data[adr] = (byte)(data & 0xFF);
			Regs_Arm7.data[adr + 1] = (byte)((data >> 8) & 0xFF);
			Memory.write_DSReg7(adr, data, false);
		}
		return;

	case 5:
		adr = address & 0x3FF;
		Memory.PaletteRAM[adr] = (byte)(data & 0xFF);
		Memory.PaletteRAM[adr + 1] = (byte)((data >> 8) & 0xFF);
		return;

	case 6:
		adr = address & 0x1FFFF;
		if (GPU.videomode < 3 || ((address & 0x1C000) != 0x18000))
		{
			if (adr > 0x17FFF) { adr -= 0x8000; }
			Memory.VRAM[adr] = (byte)(data & 0xFF);
			Memory.VRAM[adr + 1] = (byte)((data >> 8) & 0xFF);
		}
		return;

	case 7:
		adr = address & 0x3FF;
		Memory.OAMRAM[adr] = (byte)(data & 0xFF);
		Memory.OAMRAM[adr + 1] = (byte)((data >> 8) & 0xFF);
		return;
	}
}

void write_dword_7(ACCESSTYPE accesstype, UInt32 address, UInt32 data)
{
	byte offset = (byte)(address & 3);
	address = address & 0xFFFFFFFC;
	uint adr;

	byte select = (byte)(address >> 24);
	switch (select)
	{
	case 2:
		adr = address & 0x03FFFFF;
		Memory.WRAM_Large[adr] = (byte)(data & 0xFF);
		Memory.WRAM_Large[adr + 1] = (byte)((data >> 8) & 0xFF);
		Memory.WRAM_Large[adr + 2] = (byte)((data >> 16) & 0xFF);
		Memory.WRAM_Large[adr + 3] = (byte)((data >> 24) & 0xFF);
		return;

	case 3:
		if (address < 0x3800000)
		{
			adr = address & 0x7FFF;
			Memory.WRAM_Small[adr] = (byte)(data & 0xFF);
			Memory.WRAM_Small[adr + 1] = (byte)((data >> 8) & 0xFF);
			Memory.WRAM_Small[adr + 2] = (byte)((data >> 16) & 0xFF);
			Memory.WRAM_Small[adr + 3] = (byte)((data >> 24) & 0xFF);
		}
		else
		{
			adr = address & 0xFFFF;
			Memory.WRAM_Small[0x8000 + adr] = (byte)(data & 0xFF);
			Memory.WRAM_Small[0x8000 + adr + 1] = (byte)((data >> 8) & 0xFF);
			Memory.WRAM_Small[0x8000 + adr + 2] = (byte)((data >> 16) & 0xFF);
			Memory.WRAM_Small[0x8000 + adr + 3] = (byte)((data >> 24) & 0xFF);
		}
		return;

	case 4:
		if (address < 0x04000400)
		{
			adr = address & 0x3FF;

			Regs_Arm7.data[adr] = (byte)(data & 0xFF);
			Regs_Arm7.data[adr + 1] = (byte)((data >> 8) & 0xFF);
			Regs_Arm7.data[adr + 2] = (byte)((data >> 16) & 0xFF);
			Regs_Arm7.data[adr + 3] = (byte)((data >> 24) & 0xFF);

			Memory.write_DSReg7(adr, data, true);
			Memory.write_DSReg7(adr + 2, data, true);
		}
		return;

	case 5:
		adr = address & 0x3FF;
		Memory.PaletteRAM[adr] = (byte)(data & 0xFF);
		Memory.PaletteRAM[adr + 1] = (byte)((data >> 8) & 0xFF);
		Memory.PaletteRAM[adr + 2] = (byte)((data >> 16) & 0xFF);
		Memory.PaletteRAM[adr + 3] = (byte)((data >> 24) & 0xFF);
		return;

	case 6:
		adr = address & 0x1FFFF;
		if (GPU.videomode < 3 || ((address & 0x1C000) != 0x18000))
		{
			if (adr > 0x17FFF) { adr -= 0x8000; }
			Memory.VRAM[adr] = (byte)(data & 0xFF);
			Memory.VRAM[adr + 1] = (byte)((data >> 8) & 0xFF);
			Memory.VRAM[adr + 2] = (byte)((data >> 16) & 0xFF);
			Memory.VRAM[adr + 3] = (byte)((data >> 24) & 0xFF);
		}
		return;

	case 7:
		adr = address & 0x3FF;
		Memory.OAMRAM[adr] = (byte)(data & 0xFF);
		Memory.OAMRAM[adr + 1] = (byte)((data >> 8) & 0xFF);
		Memory.OAMRAM[adr + 2] = (byte)((data >> 16) & 0xFF);
		Memory.OAMRAM[adr + 3] = (byte)((data >> 24) & 0xFF);
		return;

	}
}


void MEMORY::prepare_read_DSReg9(UInt32 adr)
{
	if (adr == Regs_Arm9.Sect_timer9.TM0CNT_L.address) { Timer.updatereg(0); return; }
	if (adr == Regs_Arm9.Sect_timer9.TM1CNT_L.address) { Timer.updatereg(1); return; }
	if (adr == Regs_Arm9.Sect_timer9.TM2CNT_L.address) { Timer.updatereg(2); return; }
	if (adr == Regs_Arm9.Sect_timer9.TM3CNT_L.address) { Timer.updatereg(3); return; }
}

void MEMORY::prepare_read_DSReg7(UInt32 adr)
{
	if (adr == Regs_Arm7.Sect_timer7.TM0CNT_L.address) { Timer.updatereg(4); return; }
	if (adr == Regs_Arm7.Sect_timer7.TM1CNT_L.address) { Timer.updatereg(5); return; }
	if (adr == Regs_Arm7.Sect_timer7.TM2CNT_L.address) { Timer.updatereg(6); return; }
	if (adr == Regs_Arm7.Sect_timer7.TM3CNT_L.address) { Timer.updatereg(7); return; }

	else if (adr == Regs_Arm7.Sect_sound7.SOUNDCNT_X.address)
	{
		Regs_Arm7.data[adr] = (byte)(Regs_Arm7.data[adr] & 0x80);
		if (Sound.soundGenerator.soundchannels[0].on && Sound.soundGenerator.enable_channels_left[0] || Sound.soundGenerator.enable_channels_right[0]) { Regs_Arm7.data[adr] |= 0x01; }
		if (Sound.soundGenerator.soundchannels[1].on && Sound.soundGenerator.enable_channels_left[1] || Sound.soundGenerator.enable_channels_right[1]) { Regs_Arm7.data[adr] |= 0x02; }
		if (Sound.soundGenerator.soundchannels[2].on && Sound.soundGenerator.enable_channels_left[2] || Sound.soundGenerator.enable_channels_right[2]) { Regs_Arm7.data[adr] |= 0x04; }
		if (Sound.soundGenerator.soundchannels[3].on && Sound.soundGenerator.enable_channels_left[3] || Sound.soundGenerator.enable_channels_right[3]) { Regs_Arm7.data[adr] |= 0x08; }
	}
}

void MEMORY::write_DSReg9(UInt32 adr, UInt32 value, bool dwaccess)
{
	if (adr == Regs_Arm9.Sect_display9.DISPCNT.address) { GPU.dispcnt_write(); }
	if (adr == Regs_Arm9.Sect_display9.DISPSTAT.address) { GPU_Timing.dispstat_write(); }
	else if (adr == Regs_Arm9.Sect_display9.BG2RefX.address) { GPU.refpoint_update_2x_new(); }
	else if (adr == Regs_Arm9.Sect_display9.BG2RefX.address + 2) { GPU.refpoint_update_2x_new(); }
	else if (adr == Regs_Arm9.Sect_display9.BG2RefY.address) { GPU.refpoint_update_2y_new(); }
	else if (adr == Regs_Arm9.Sect_display9.BG2RefY.address + 2) { GPU.refpoint_update_2y_new(); }
	else if (adr == Regs_Arm9.Sect_display9.BG3RefX.address) { GPU.refpoint_update_3x_new(); }
	else if (adr == Regs_Arm9.Sect_display9.BG3RefX.address + 2) { GPU.refpoint_update_3x_new(); }
	else if (adr == Regs_Arm9.Sect_display9.BG3RefY.address) { GPU.refpoint_update_3y_new(); }
	else if (adr == Regs_Arm9.Sect_display9.BG3RefY.address + 2) { GPU.refpoint_update_3y_new(); }

	else if (adr >= Regs_Arm7.Sect_sound7.SOUND1CNT_L.address && adr < Regs_Arm7.Sect_sound7.FIFO_A.address)
	{
		Sound.set_soundreg(adr);
	}

	else if (adr == Regs_Arm7.Sect_sound7.FIFO_A.address) { SoundDMA.fill_fifo(0, value, dwaccess); }
	else if (adr == Regs_Arm7.Sect_sound7.FIFO_B.address) { SoundDMA.fill_fifo(1, value, dwaccess); }

	else if (adr == Regs_Arm9.Sect_timer9.TM0CNT_L.address) { Timer.set_reload(0); }
	else if (adr == Regs_Arm9.Sect_timer9.TM0CNT_L.address + 2) { Timer.set_settings(0); }
	else if (adr == Regs_Arm9.Sect_timer9.TM1CNT_L.address) { Timer.set_reload(1); }
	else if (adr == Regs_Arm9.Sect_timer9.TM1CNT_L.address + 2) { Timer.set_settings(1); }
	else if (adr == Regs_Arm9.Sect_timer9.TM2CNT_L.address) { Timer.set_reload(2); }
	else if (adr == Regs_Arm9.Sect_timer9.TM2CNT_L.address + 2) { Timer.set_settings(2); }
	else if (adr == Regs_Arm9.Sect_timer9.TM3CNT_L.address) { Timer.set_reload(3); }
	else if (adr == Regs_Arm9.Sect_timer9.TM3CNT_L.address + 2) { Timer.set_settings(3); }

	else if (adr == Regs_Arm9.Sect_dma9.DMA0CNT_H.address + 2) { DMA.set_settings(0); }
	else if (adr == Regs_Arm9.Sect_dma9.DMA1CNT_H.address + 2) { DMA.set_settings(1); }
	else if (adr == Regs_Arm9.Sect_dma9.DMA2CNT_H.address + 2) { DMA.set_settings(2); }
	else if (adr == Regs_Arm9.Sect_dma9.DMA3CNT_H.address + 2) { DMA.set_settings(3); }

	else if (adr == Regs_Arm9.Sect_keypad9.KEYINPUT.address) { Joypad.set_reg(); }

	else if (adr == Regs_Arm9.Sect_system9.IME.address) { IRP9.update_IME(value); Regs_Arm9.Sect_system9.IME.write(value & 1); }
	else if (adr == Regs_Arm9.Sect_system9.IE.address) { IRP9.update_IE(); }
	else if (adr == Regs_Arm9.Sect_system9.IF.address + 2) { IRP9.clear_irp_bits(); }

	if (adr == Regs_Arm9.Sect_system9.IPCSYNC.address) { IPC9to7.write_sync(); return; }
	if (adr == Regs_Arm9.Sect_system9.IPCFIFOCNT.address) { IPC9to7.write_control(); return; }
	if (adr == Regs_Arm9.Sect_system9.IPCFIFOSEND.address) { IPC9to7.writefifo(value); return; }

	if (adr == Regs_Arm9.Sect_system9.EXMEMCNT.address) // first two bytes readable from arm7 side
	{ 
		Regs_Arm7.data[0x204] = Regs_Arm7.data[0x204] & 0x7F | Regs_Arm9.data[0x204] & 0x80; // lower 7 bit can be changed on arm7 side, so keep them
		Regs_Arm7.data[0x205] = Regs_Arm9.data[0x205]; 
		return; 
	} 
}

void MEMORY::write_DSReg7(UInt32 adr, UInt32 value, bool dwaccess)
{
	if (adr == Regs_Arm7.Sect_dma7.DMA0CNT_H.address + 2) { DMA.set_settings(4); return; }
	if (adr == Regs_Arm7.Sect_dma7.DMA1CNT_H.address + 2) { DMA.set_settings(5); return; }
	if (adr == Regs_Arm7.Sect_dma7.DMA2CNT_H.address + 2) { DMA.set_settings(6); return; }
	if (adr == Regs_Arm7.Sect_dma7.DMA3CNT_H.address + 2) { DMA.set_settings(7); return; }

	if (adr == Regs_Arm7.Sect_timer7.TM0CNT_L.address) { Timer.set_reload(4); return; }
	if (adr == Regs_Arm7.Sect_timer7.TM0CNT_L.address + 2) { Timer.set_settings(4); return; }
	if (adr == Regs_Arm7.Sect_timer7.TM1CNT_L.address) { Timer.set_reload(5); return; }
	if (adr == Regs_Arm7.Sect_timer7.TM1CNT_L.address + 2) { Timer.set_settings(5); return; }
	if (adr == Regs_Arm7.Sect_timer7.TM2CNT_L.address) { Timer.set_reload(6); return; }
	if (adr == Regs_Arm7.Sect_timer7.TM2CNT_L.address + 2) { Timer.set_settings(6); return; }
	if (adr == Regs_Arm7.Sect_timer7.TM3CNT_L.address) { Timer.set_reload(7); return; }
	if (adr == Regs_Arm7.Sect_timer7.TM3CNT_L.address + 2) { Timer.set_settings(7); return; }

	if (adr == Regs_Arm7.Sect_system7.IME.address) { IRP7.update_IME(value); Regs_Arm7.Sect_system7.IME.write(value & 1); return; }
	if (adr == Regs_Arm7.Sect_system7.IE.address) { IRP7.update_IE(); return; }
	if (adr == Regs_Arm7.Sect_system7.IF.address + 2) { IRP7.clear_irp_bits(); return; }

	if (adr == Regs_Arm7.Sect_system7.IPCSYNC.address) { IPC7to9.write_sync(); return; }
	if (adr == Regs_Arm7.Sect_system7.IPCFIFOCNT.address) { IPC7to9.write_control(); return; }
	if (adr == Regs_Arm7.Sect_system7.IPCFIFOSEND.address) { IPC7to9.writefifo(value); return; }

	if (adr == Regs_Arm7.Sect_system7.SPICNT.address + 2) { SPI_Intern.write_data((byte)value); return; }

	if (adr == Regs_Arm7.Sect_system7.POSTFLG_Flag.address) { CPU7.halt = true; return; }
}