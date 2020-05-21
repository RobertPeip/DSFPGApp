#include "Memory.h"
#include "CPU.h"
#include "DMA.h"
#include "regs_arm9.h"
#include "regs_arm7.h"
#include "GPU.h"
#include "GPU_Timing.h"
#include "gpio.h"
#include "fileIO.h"
#include "Timer.h"
#include "gameboy.h"
#include "BusTiming.h"
#include "IRP.h"
#include "Sound.h"
#include "Joypad.h"
#include "Serial.h"
#include "Header.h"
#include "spi_intern.h"
#include "IPC.h"
#include "MathDIV.h"
#include "MathSQRT.h"
#include "Gamecard.h"
#include "GXFifo.h"

MEMORY Memory;

void MEMORY::reset(string filename)
{
	FileIO.readfile(Bios7, "bios7.bin", false);
	FileIO.readfile(Bios9, "bios9.bin", false);
	FileIO.readfile(Firmware, "firmware.bin", false);
	FileIO.readfile(FirmwareUser, "firmware_user.bin", false);

	// clean saveram
	for (int i = 0; i < 1048576; i++) SaveRam[i] = 0xFF;

	wrammux = 3;
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

	// copy header
	for (int i = 0; i < 0x170; i += 4)
	{
		uint data = *(UInt32*)&Memory.GameRom[i];
		write_dword_7(ACCESSTYPE::CPUDATA, 0x027FFE00 + i, data);
	}

	// firmware user to memory
	for (int i = 0; i < 0x70; i++)
	{
		write_byte_9(ACCESSTYPE::CPUDATA, 0x027FFC80 + i, FirmwareUser[i]);
	}

	// init further memory
	write_dword_7(ACCESSTYPE::CPUDATA, 0x02FFFC40, 0x1);

	write_dword_7(ACCESSTYPE::CPUDATA, 0x027FF800, Header.chipID);
	write_dword_7(ACCESSTYPE::CPUDATA, 0x027FF804, Header.chipID);
	write_dword_7(ACCESSTYPE::CPUDATA, 0x027FFC00, Header.chipID);

	write_dword_7(ACCESSTYPE::CPUDATA, 0x027FF808, 0x6ee6); //  header checksum crc16

	for (int i = 0; i < 9; i++)
	{
		vrammux[i].ena9 = false;
		vrammux[i].ena7 = false;
		set_single_vrammode((VRAMBANK)i, 0, 0);
		vrammux[i].MST = 0;
		vrammux[i].start = 0;
		vrammux[i].end = 0;
		vrammux[i].gpustart = 0;
		vrammux[i].gpuend = 0;
	}
	vrammux[0].vramoffset = 0;
	vrammux[1].vramoffset = 0x20000;
	vrammux[2].vramoffset = 0x40000;
	vrammux[3].vramoffset = 0x60000;
	vrammux[4].vramoffset = 0x80000;
	vrammux[5].vramoffset = 0x90000;
	vrammux[6].vramoffset = 0x94000;
	vrammux[7].vramoffset = 0x98000;
	vrammux[8].vramoffset = 0xA0000;

	load_gameram(filename);
}

void MEMORY::GameRAMSnapshot()
{
	if (createGameRAMSnapshot)
	{
		int index = 0;
		for (int i = 0; i < 131072; i++)
		{
			//GameRamSnapshot[index] = Flash.flashSaveMemory[i];
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
			//Flash.flashSaveMemory[i] = GameRamSnapshot[index];
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

	if (accesstype == ACCESSTYPE::CPUDATA && (address & (~0x3FFF)) == Co15.DTCMRegion)
	{
		return Memory.DTCM[address & 0x3FFF];
	}

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
		return Memory.WRAM_Large[address & 0x03FFFFF];

	case 3: 
		switch (Memory.wrammux)
		{
		case 0:  adr = address & 0x7FFF; return Memory.WRAM_Small_32[adr]; break;
		case 1:  adr = address & 0x3FFF; return Memory.WRAM_Small_32[adr + 16384]; break;
		case 2:  adr = address & 0x3FFF; return Memory.WRAM_Small_32[adr]; break;
		case 3:  return 0; break;
		}
		
	case 4:
		if (address <= 0x0400106C)
		{
			adr = address & 0x1FFF;
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

	case 5: return Memory.PaletteRAM[address & 0x7FF];

	case 6:
		adr = Memory.get_vram_address(true, address);
		if (adr != 0xFFFFFFFF)
		{
			return Memory.VRAM[adr];
		}
		return 0;

	case 7: return Memory.OAMRAM[address & 0x7FF];

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

	if (accesstype == ACCESSTYPE::CPUDATA && (address & (~0x3FFF)) == Co15.DTCMRegion)
	{
		value = *(UInt16*)&Memory.DTCM[address & 0x3FFF];
	}
	else
	{
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
			value = *(UInt16*)&Memory.WRAM_Large[address & 0x03FFFFF];
			break;

		case 3:
			switch (Memory.wrammux)
			{
			case 0:  adr = address & 0x7FFF; value = *(UInt16*)&Memory.WRAM_Small_32[adr]; break;
			case 1:  adr = address & 0x3FFF; value = *(UInt16*)&Memory.WRAM_Small_32[adr + 16384]; break;
			case 2:  adr = address & 0x3FFF; value = *(UInt16*)&Memory.WRAM_Small_32[adr]; break;
			case 3:  value = 0; break;
			}
			break;

		case 4:
			if (address <= 0x0400106C)
			{
				adr = address & 0x1FFF;

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
			else
			{
				value = Memory.read_unreadable_word();
			}
			break;

		case 5: value = *(UInt16*)&Memory.PaletteRAM[address & 0x7FF]; break;

		case 6:
			adr = Memory.get_vram_address(true, address);
			if (adr != 0xFFFFFFFF)
			{
				value = *(UInt16*)&Memory.VRAM[adr];
			}
			break;

		case 7: value = *(UInt16*)&Memory.OAMRAM[address & 0x7FF]; break;

		case 0xFF: value = *(UInt16*)&Memory.Bios9[address & 0xFFF]; break;

		default: value = 0xFFFF; break;
		}
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

	if (accesstype == ACCESSTYPE::CPUDATA && (address & (~0x3FFF)) == Co15.DTCMRegion)
	{
		value = *(UInt32*)&Memory.DTCM[address & 0x3FFF];
	}
	else
	{
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
			value = *(UInt32*)&Memory.WRAM_Large[address & 0x03FFFFF];
			break;

		case 3:
			switch (Memory.wrammux)
			{
			case 0:  adr = address & 0x7FFF; value = *(UInt32*)&Memory.WRAM_Small_32[adr]; break;
			case 1:  adr = address & 0x3FFF; value = *(UInt32*)&Memory.WRAM_Small_32[adr + 16384]; break;
			case 2:  adr = address & 0x3FFF; value = *(UInt32*)&Memory.WRAM_Small_32[adr]; break;
			case 3:  value = 0; break;
			}
			break;

		case 4:
			if (address == 0x040001A0)
			{
				value = (read_word_9(accesstype, address + 2) << 16); // only for desmume wrong aux spi control handling....
			}
			else if (address <= 0x0400106C)
			{
				value = (UInt16)read_word_9(accesstype, address) | (read_word_9(accesstype, address + 2) << 16);
			}
			else if (address == 0x04100000)
			{
				value = IPC7to9.readfifo();
			}
			else if (address == 0x04100010)
			{
				value = Gamecard9.readData();
			}
			else
			{
				value = Memory.read_unreadable_dword();
			}
			break;

		case 5: value = *(UInt32*)&Memory.PaletteRAM[address & 0x7FF]; break;

		case 6:
			adr = Memory.get_vram_address(true, address);
			if (adr != 0xFFFFFFFF)
			{
				value = *(UInt32*)&Memory.VRAM[adr];
			}
			break;

		case 7: value = *(UInt32*)&Memory.OAMRAM[address & 0x7FF]; break;

		case 0xFF: value = *(UInt32*)&Memory.Bios9[address & 0xFFF]; break;

		default: value = 0xFFFFFFFF; break;
		}
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

	if (accesstype == ACCESSTYPE::CPUDATA && (address & (~0x3FFF)) == Co15.DTCMRegion)
	{
		adr = address & 0x3FFF;
		Memory.DTCM[adr] = (byte)(data & 0xFF);
		return;
	}

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
		adr = address & 0x03FFFFF;
		Memory.WRAM_Large[adr] = (byte)(data & 0xFF);
		return;

	case 3: 
		switch (Memory.wrammux)
		{
		case 0:  adr = address & 0x7FFF; Memory.WRAM_Small_32[adr] = data; return;
		case 1:  adr = address & 0x3FFF; Memory.WRAM_Small_32[adr + 16384] = data; return;
		case 2:  adr = address & 0x3FFF; Memory.WRAM_Small_32[adr] = data; return;
		case 3:  return;
		}

	case 4:
		if (address <= 0x0400106C)
		{
			adr = address & 0x1FFF;
			Regs_Arm9.data[adr] = data;
			Memory.write_DSReg9(adr & 0xFFFFFFFE, data, false);
		}
		return;

	case 5: 
		Memory.PaletteRAM[address & 0x7FE] = data;
		Memory.PaletteRAM[(address & 0x7FE) + 1] = data; 
		return;

	case 6: // byte write not supported
		return;

	case 7: return; // no saving here!
	}
}

void write_word_9(ACCESSTYPE accesstype, UInt32 address, UInt16 data)
{
	byte offset = (byte)(address & 1);
	address = address & 0xFFFFFFFE;
	uint adr;

	if (accesstype == ACCESSTYPE::CPUDATA && (address & (~0x3FFF)) == Co15.DTCMRegion)
	{
		adr = address & 0x3FFF;
		Memory.DTCM[adr] = (byte)(data & 0xFF);
		Memory.DTCM[adr + 1] = (byte)((data >> 8) & 0xFF);
		return;
	}

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
		adr = address & 0x03FFFFF;
		Memory.WRAM_Large[adr] = (byte)(data & 0xFF);
		Memory.WRAM_Large[adr + 1] = (byte)((data >> 8) & 0xFF);
		return;

	case 3:
		switch (Memory.wrammux)
		{
		case 0:  
			adr = address & 0x7FFF; 
			Memory.WRAM_Small_32[adr] = (byte)(data & 0xFF);
			Memory.WRAM_Small_32[adr + 1] = (byte)((data >> 8) & 0xFF);
			return;
		case 1:  
			adr = address & 0x3FFF; 
			Memory.WRAM_Small_32[adr + 16384] = data; 
			Memory.WRAM_Small_32[adr + 16385] = (byte)((data >> 8) & 0xFF);
			return;
		case 2:  
			adr = address & 0x3FFF; 
			Memory.WRAM_Small_32[adr] = (byte)(data & 0xFF);
			Memory.WRAM_Small_32[adr + 1] = (byte)((data >> 8) & 0xFF);
			return;
		case 3:  return;
		}
		return;

	case 4:
		if (address <= 0x0400106C)
		{
			adr = address & 0x1FFF;
			Regs_Arm9.data[adr] = (byte)(data & 0xFF);
			Regs_Arm9.data[adr + 1] = (byte)((data >> 8) & 0xFF);
			Memory.write_DSReg9(adr, data, false);
		}
		return;

	case 5:
		adr = address & 0x7FF;
		Memory.PaletteRAM[adr] = (byte)(data & 0xFF);
		Memory.PaletteRAM[adr + 1] = (byte)((data >> 8) & 0xFF);
		return;

	case 6:
		adr = Memory.get_vram_address(true, address);
		if (adr != 0xFFFFFFFF)
		{
			Memory.VRAM[adr] = (byte)(data & 0xFF);
			Memory.VRAM[adr + 1] = (byte)((data >> 8) & 0xFF);
		}
		return;

	case 7:
		adr = address & 0x7FF;
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

	if (accesstype == ACCESSTYPE::CPUDATA && (address & (~0x3FFF)) == Co15.DTCMRegion)
	{
		adr = address & 0x3FFF;
		Memory.DTCM[adr] = (byte)(data & 0xFF);
		Memory.DTCM[adr + 1] = (byte)((data >> 8) & 0xFF);
		Memory.DTCM[adr + 2] = (byte)((data >> 16) & 0xFF);
		Memory.DTCM[adr + 3] = (byte)((data >> 24) & 0xFF);
		return;
	}

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
		adr = address & 0x03FFFFF;
		Memory.WRAM_Large[adr] = (byte)(data & 0xFF);
		Memory.WRAM_Large[adr + 1] = (byte)((data >> 8) & 0xFF);
		Memory.WRAM_Large[adr + 2] = (byte)((data >> 16) & 0xFF);
		Memory.WRAM_Large[adr + 3] = (byte)((data >> 24) & 0xFF);
		return;

	case 3:
		switch (Memory.wrammux)
		{
		case 0:
			adr = address & 0x7FFF;
			Memory.WRAM_Small_32[adr] = (byte)(data & 0xFF);
			Memory.WRAM_Small_32[adr + 1] = (byte)((data >> 8) & 0xFF);
			Memory.WRAM_Small_32[adr + 2] = (byte)((data >> 16) & 0xFF);
			Memory.WRAM_Small_32[adr + 3] = (byte)((data >> 24) & 0xFF);
			return;
		case 1:
			adr = address & 0x3FFF;
			Memory.WRAM_Small_32[adr + 16384] = data;
			Memory.WRAM_Small_32[adr + 16385] = (byte)((data >> 8) & 0xFF);
			Memory.WRAM_Small_32[adr + 16386] = (byte)((data >> 16) & 0xFF);
			Memory.WRAM_Small_32[adr + 16387] = (byte)((data >> 24) & 0xFF);
			return;
		case 2:
			adr = address & 0x3FFF;
			Memory.WRAM_Small_32[adr] = (byte)(data & 0xFF);
			Memory.WRAM_Small_32[adr + 1] = (byte)((data >> 8) & 0xFF);
			Memory.WRAM_Small_32[adr + 2] = (byte)((data >> 16) & 0xFF);
			Memory.WRAM_Small_32[adr + 3] = (byte)((data >> 24) & 0xFF);
			return;
		case 3:  return;
		}

	case 4:
		if (address <= 0x0400106C)
		{
			adr = address & 0x1FFF;

			Regs_Arm9.data[adr] = (byte)(data & 0xFF);
			Regs_Arm9.data[adr + 1] = (byte)((data >> 8) & 0xFF);
			Regs_Arm9.data[adr + 2] = (byte)((data >> 16) & 0xFF);
			Regs_Arm9.data[adr + 3] = (byte)((data >> 24) & 0xFF);

			Memory.write_DSReg9(adr, data, true);
			Memory.write_DSReg9(adr + 2, data, true);
		}
		return;

	case 5:
		adr = address & 0x7FF;
		Memory.PaletteRAM[adr] = (byte)(data & 0xFF);
		Memory.PaletteRAM[adr + 1] = (byte)((data >> 8) & 0xFF);
		Memory.PaletteRAM[adr + 2] = (byte)((data >> 16) & 0xFF);
		Memory.PaletteRAM[adr + 3] = (byte)((data >> 24) & 0xFF);
		return;

	case 6:
		adr = Memory.get_vram_address(true, address);
		if (adr != 0xFFFFFFFF)
		{
			Memory.VRAM[adr] = (byte)(data & 0xFF);
			Memory.VRAM[adr + 1] = (byte)((data >> 8) & 0xFF);
			Memory.VRAM[adr + 2] = (byte)((data >> 16) & 0xFF);
			Memory.VRAM[adr + 3] = (byte)((data >> 24) & 0xFF);
		}
		return;

	case 7:
		adr = address & 0x7FF;
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
		if (CPU7.PC < 0x4000)
		{
			return Memory.Bios7[address & 0x3FFF];
		}
		else
		{
			return 0xFF;
		}

	case 1: return Memory.read_unreadable_byte(address & 1);
	case 2: return Memory.WRAM_Large[address & 0x03FFFFF];
	case 3:
		if (address < 0x3800000)
		{
			switch (Memory.wrammux)
			{
			case 0:  adr = address & 0xFFFF; return Memory.WRAM_Small_64[adr]; break;
			case 1:  adr = address & 0x3FFF; return Memory.WRAM_Small_32[adr]; break;
			case 2:  adr = address & 0x3FFF; return Memory.WRAM_Small_32[adr + 16384]; break;
			case 3:  adr = address & 0x7FFF; return Memory.WRAM_Small_32[adr]; break;
			}
		}
		else
		{
			adr = address & 0xFFFF;
			return Memory.WRAM_Small_64[adr]; break;
		}

	case 4:
		if (address < 0x04001000)
		{
			adr = address & 0xFFF;

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

	case 6:
		adr = Memory.get_vram_address(false, address);
		if (adr != 0xFFFFFFFF)
		{
			return Memory.VRAM[adr];
		}
		return 0;

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
		if (CPU7.PC < 0x4000)
		{
			value = *(UInt16*)&Memory.Bios7[address & 0x3FFE];
		}
		else
		{
			value = 0xFFFF;
		}
		break;

	case 1: value = Memory.read_unreadable_word(); break;
	case 2: value = *(UInt16*)&Memory.WRAM_Large[address & 0x03FFFFF]; break;
	case 3:
		if (address < 0x3800000)
		{
			switch (Memory.wrammux)
			{
			case 0:  adr = address & 0xFFFF; value = *(UInt16*)&Memory.WRAM_Small_64[adr];; break;
			case 1:  adr = address & 0x3FFF; value = *(UInt16*)&Memory.WRAM_Small_32[adr]; break;
			case 2:  adr = address & 0x3FFF; value = *(UInt16*)&Memory.WRAM_Small_32[adr + 16384]; break;
			case 3:  adr = address & 0x7FFF; value = *(UInt16*)&Memory.WRAM_Small_32[adr]; break;
			}
		}
		else
		{
			adr = address & 0xFFFF;
			value = *(UInt16*)&Memory.WRAM_Small_64[adr]; break;
		}
		break;

	case 4:
		if (address < 0x04001000)
		{
			adr = address & 0xFFF;

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
		else
		{
			value = Memory.read_unreadable_word();
		}
		break;

	case 6:
		adr = Memory.get_vram_address(false, address);
		if (adr != 0xFFFFFFFF)
		{
			value = *(UInt16*)&Memory.VRAM[adr];
		}
		break;

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
		if (CPU7.PC < 0x4000)
		{
			value = *(UInt32*)&Memory.Bios7[address & 0x3FFE];
		}
		else
		{
			value = 0xFFFFFFFF;
		}
		break;

	case 1: value = Memory.read_unreadable_dword(); break;
	case 2: value = *(UInt32*)&Memory.WRAM_Large[address & 0x03FFFFF]; break;
	case 3:
		if (address < 0x3800000)
		{
			switch (Memory.wrammux)
			{
			case 0:  adr = address & 0xFFFF; value = *(UInt32*)&Memory.WRAM_Small_64[adr]; break;
			case 1:  adr = address & 0x3FFF; value = *(UInt32*)&Memory.WRAM_Small_32[adr]; break;
			case 2:  adr = address & 0x3FFF; value = *(UInt32*)&Memory.WRAM_Small_32[adr + 16384]; break;
			case 3:  adr = address & 0x7FFF; value = *(UInt32*)&Memory.WRAM_Small_32[adr]; break;
			}
		}
		else
		{
			adr = address & 0xFFFF;
			value = *(UInt32*)&Memory.WRAM_Small_64[adr]; break;
		}
		break;

	case 4:
		if (address == 0x040001A0)
		{
			value = (read_word_7(accesstype, address + 2) << 16); // only for desmume wrong aux spi control handling....
		}
		else if (address < 0x04001000)
		{
			value = (UInt16)read_word_7(accesstype, address) | (read_word_7(accesstype, address + 2) << 16);
		}
		else if (address == 0x04100000)
		{
			value = IPC9to7.readfifo();
		}
		else if (address == 0x04100010)
		{
			value = Gamecard7.readData();
		}
		else
		{
			value = Memory.read_unreadable_dword();
		}
		break;

	case 6:
		adr = Memory.get_vram_address(false, address);
		if (adr != 0xFFFFFFFF)
		{
			value = *(UInt32*)&Memory.VRAM[adr];
		}
		break;

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
			switch (Memory.wrammux)
			{
			case 0: adr = address & 0xFFFF; Memory.WRAM_Small_64[adr] = data; return;
			case 1: adr = address & 0x3FFF; Memory.WRAM_Small_32[adr] = data; return;
			case 2: adr = address & 0x3FFF; Memory.WRAM_Small_32[adr + 16384] = data; return;
			case 3: adr = address & 0x7FFF; Memory.WRAM_Small_32[adr] = data; return;
			}
		}
		else
		{
			adr = address & 0xFFFF;
			Memory.WRAM_Small_64[adr] = (byte)(data & 0xFF);
			return;
		}

	case 4:
		if (address < 0x04001000)
		{
			adr = address & 0xFFF;
			Regs_Arm7.data[adr] = data;
			Memory.write_DSReg7(adr & 0xFFFFFFFE, data, false);
		}
		return;

	case 6:
		adr = Memory.get_vram_address(false, address);
		if (adr != 0xFFFFFFFF)
		{
			Memory.VRAM[adr] = (byte)(data & 0xFF);
		}
		return;
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
			switch (Memory.wrammux)
			{
			case 0: 
				adr = address & 0xFFFF; 
				Memory.WRAM_Small_64[adr] = (byte)(data & 0xFF);
				Memory.WRAM_Small_64[adr + 1] = (byte)((data >> 8) & 0xFF);
				return;
			case 1: 
				adr = address & 0x3FFF; 
				Memory.WRAM_Small_32[adr] = (byte)(data & 0xFF);
				Memory.WRAM_Small_32[adr + 1] = (byte)((data >> 8) & 0xFF);
				return;
			case 2: 
				adr = address & 0x3FFF; 
				Memory.WRAM_Small_32[adr + 16384] = (byte)(data & 0xFF);
				Memory.WRAM_Small_32[adr + 16385] = (byte)((data >> 8) & 0xFF);
				return;
			case 3: 
				adr = address & 0x7FFF; 
				Memory.WRAM_Small_32[adr] = (byte)(data & 0xFF);
				Memory.WRAM_Small_32[adr + 1] = (byte)((data >> 8) & 0xFF);
				return;
			}
		}
		else
		{
			adr = address & 0xFFFF;
			Memory.WRAM_Small_64[adr] = (byte)(data & 0xFF);
			Memory.WRAM_Small_64[adr + 1] = (byte)((data >> 8) & 0xFF);
		}
		return;

	case 4:
		if (address < 0x04001000)
		{
			adr = address & 0xFFF;
			Regs_Arm7.data[adr] = (byte)(data & 0xFF);
			Regs_Arm7.data[adr + 1] = (byte)((data >> 8) & 0xFF);
			Memory.write_DSReg7(adr, data, false);
		}
		return;

	case 6:
		adr = Memory.get_vram_address(false, address);
		if (adr != 0xFFFFFFFF)
		{
			Memory.VRAM[adr] = (byte)(data & 0xFF);
			Memory.VRAM[adr + 1] = (byte)((data >> 8) & 0xFF);
		}
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
			switch (Memory.wrammux)
			{
			case 0:
				adr = address & 0xFFFF;
				Memory.WRAM_Small_64[adr] = (byte)(data & 0xFF);
				Memory.WRAM_Small_64[adr + 1] = (byte)((data >> 8) & 0xFF);
				Memory.WRAM_Small_64[adr + 2] = (byte)((data >> 16) & 0xFF);
				Memory.WRAM_Small_64[adr + 3] = (byte)((data >> 24) & 0xFF);
				return;
			case 1:
				adr = address & 0x3FFF;
				Memory.WRAM_Small_32[adr] = (byte)(data & 0xFF);
				Memory.WRAM_Small_32[adr + 1] = (byte)((data >> 8) & 0xFF);
				Memory.WRAM_Small_32[adr + 2] = (byte)((data >> 16) & 0xFF);
				Memory.WRAM_Small_32[adr + 3] = (byte)((data >> 24) & 0xFF);
				return;
			case 2:
				adr = address & 0x3FFF;
				Memory.WRAM_Small_32[adr + 16384] = (byte)(data & 0xFF);
				Memory.WRAM_Small_32[adr + 16385] = (byte)((data >> 8) & 0xFF);
				Memory.WRAM_Small_32[adr + 16386] = (byte)((data >> 16) & 0xFF);
				Memory.WRAM_Small_32[adr + 16387] = (byte)((data >> 24) & 0xFF);
				return;
			case 3:
				adr = address & 0x7FFF;
				Memory.WRAM_Small_32[adr] = (byte)(data & 0xFF);
				Memory.WRAM_Small_32[adr + 1] = (byte)((data >> 8) & 0xFF);
				Memory.WRAM_Small_32[adr + 2] = (byte)((data >> 16) & 0xFF);
				Memory.WRAM_Small_32[adr + 3] = (byte)((data >> 24) & 0xFF);
				return;
			}
		}
		else
		{
			adr = address & 0xFFFF;
			Memory.WRAM_Small_64[adr] = (byte)(data & 0xFF);
			Memory.WRAM_Small_64[adr + 1] = (byte)((data >> 8) & 0xFF);
			Memory.WRAM_Small_64[adr + 2] = (byte)((data >> 16) & 0xFF);
			Memory.WRAM_Small_64[adr + 3] = (byte)((data >> 24) & 0xFF);
		}
		return;

	case 4:
		if (address < 0x04001000)
		{
			adr = address & 0xFFF;

			Regs_Arm7.data[adr] = (byte)(data & 0xFF);
			Regs_Arm7.data[adr + 1] = (byte)((data >> 8) & 0xFF);
			Regs_Arm7.data[adr + 2] = (byte)((data >> 16) & 0xFF);
			Regs_Arm7.data[adr + 3] = (byte)((data >> 24) & 0xFF);

			Memory.write_DSReg7(adr, data, true);
			Memory.write_DSReg7(adr + 2, data, true);
		}
		return;

	case 6:
		adr = Memory.get_vram_address(false, address);
		if (adr != 0xFFFFFFFF)
		{
			Memory.VRAM[adr] = (byte)(data & 0xFF);
			Memory.VRAM[adr + 1] = (byte)((data >> 8) & 0xFF);
			Memory.VRAM[adr + 2] = (byte)((data >> 16) & 0xFF);
			Memory.VRAM[adr + 3] = (byte)((data >> 24) & 0xFF);
		}
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
}

void MEMORY::write_DSReg9(UInt32 adr, UInt32 value, bool dwaccess)
{
	// 3D first
	if (adr == Regs_Arm9.Sect_3D9.GXFIFO.address)
	{
		int a = 5;
	}
	if (adr == Regs_Arm9.Sect_3D9.GXSTAT.address)
	{
		if (Regs_Arm9.Sect_3D9.GXSTAT_Matrix_Stack_Error.on()) { Regs_Arm9.Sect_3D9.GXSTAT_Matrix_Stack_Error.write(0); }
		bool oldschedule = gameboy.reschedule; // hack because setting IF bit should usually always set reschedule, but we want to stay compatible for now...
		GXFifo.check_gxfifobits();
		gameboy.reschedule = oldschedule;
	}

	if (adr == Regs_Arm9.Sect_display9.DISP3DCNT.address)
	{
		if (Regs_Arm9.Sect_display9.DISP3DCNT_RDLINES_Underflow.on()) { Regs_Arm9.Sect_display9.DISP3DCNT_RDLINES_Underflow.write(0); }
		if (Regs_Arm9.Sect_display9.DISP3DCNT_RAM_Overflow.on()) { Regs_Arm9.Sect_display9.DISP3DCNT_RAM_Overflow.write(0); }
	}

	if (adr == 0x540) // swap buffers
	{
		GXFifo.write(0x50, value);
	}
	// end of 3D

	if (adr == Regs_Arm9.Sect_display9.A_DISPCNT.address) { GPU_A.dispcnt_write(); return; }
	if (adr == Regs_Arm9.Sect_display9.B_DISPCNT.address) { GPU_B.dispcnt_write(); return; }

	if (adr == Regs_Arm9.Sect_display9.DISPSTAT.address) { GPU_Timing.dispstat_write(); return; }

	if (adr >= Regs_Arm9.Sect_display9.A_BG2RefX.address && adr < Regs_Arm9.Sect_display9.A_BG2RefX.address + 4) { GPU_A.refpoint_update_2x_new(); return; }
	if (adr >= Regs_Arm9.Sect_display9.A_BG2RefY.address && adr < Regs_Arm9.Sect_display9.A_BG2RefY.address + 4) { GPU_A.refpoint_update_2y_new(); return; }
	if (adr >= Regs_Arm9.Sect_display9.A_BG3RefX.address && adr < Regs_Arm9.Sect_display9.A_BG3RefX.address + 4) { GPU_A.refpoint_update_3x_new(); return; }
	if (adr >= Regs_Arm9.Sect_display9.A_BG3RefY.address && adr < Regs_Arm9.Sect_display9.A_BG3RefY.address + 4) { GPU_A.refpoint_update_3y_new(); return; }
	if (adr >= Regs_Arm9.Sect_display9.B_BG2RefX.address && adr < Regs_Arm9.Sect_display9.B_BG2RefX.address + 4) { GPU_B.refpoint_update_2x_new(); return; }
	if (adr >= Regs_Arm9.Sect_display9.B_BG2RefY.address && adr < Regs_Arm9.Sect_display9.B_BG2RefY.address + 4) { GPU_B.refpoint_update_2y_new(); return; }
	if (adr >= Regs_Arm9.Sect_display9.B_BG3RefX.address && adr < Regs_Arm9.Sect_display9.B_BG3RefX.address + 4) { GPU_B.refpoint_update_3x_new(); return; }
	if (adr >= Regs_Arm9.Sect_display9.B_BG3RefY.address && adr < Regs_Arm9.Sect_display9.B_BG3RefY.address + 4) { GPU_B.refpoint_update_3y_new(); return; }

	if (adr == Regs_Arm9.Sect_display9.DISP_MMEM_FIFO.address) { GPU_A.mainmemfifo.push(value); }

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

	if (adr == Regs_Arm9.Sect_system9.ROMCTRL.address) { Gamecard9.writeControl(); return; }

	if (adr == Regs_Arm9.Sect_system9.IPCSYNC.address) { IPC9to7.write_sync(); return; }
	if (adr == Regs_Arm9.Sect_system9.IPCFIFOCNT.address) { IPC9to7.write_control(); return; }
	if (adr == Regs_Arm9.Sect_system9.IPCFIFOSEND.address) { IPC9to7.writefifo(value); return; }

	if (adr == Regs_Arm9.Sect_system9.AUXSPICNT.address) { Gamecard9.write_spi_cnt((UInt16)value); return; }
	if (adr == Regs_Arm9.Sect_system9.AUXSPICNT.address + 2) { Gamecard9.write_spi_dat((byte)value); return; }

	if (adr == Regs_Arm9.Sect_system9.EXMEMCNT.address) // first two bytes readable from arm7 side
	{ 
		Regs_Arm7.data[0x204] = Regs_Arm7.data[0x204] & 0x7F | Regs_Arm9.data[0x204] & 0x80; // lower 7 bit can be changed on arm7 side, so keep them
		Regs_Arm7.data[0x205] = Regs_Arm9.data[0x205]; 
		return; 
	} 

	if (adr == Regs_Arm9.Sect_system9.MemControl2_WRAM.address + 2) { Regs_Arm7.Sect_system7.MemControl2_WRAM.write(Regs_Arm9.Sect_system9.MemControl2_WRAM.read()); } // no return as check below
	if (adr >= Regs_Arm9.Sect_system9.MemControl1.address && adr < Regs_Arm9.Sect_system9.MemControl3.address + 4) { set_vrammode(); return; }

	if (adr >= Regs_Arm9.Sect_system9.DIVCNT.address && adr < Regs_Arm9.Sect_system9.DIV_DENOM_High.address + 4) { MathDIV.write(); return; }
	if (adr >= Regs_Arm9.Sect_system9.SQRTCN.address && adr < Regs_Arm9.Sect_system9.SQRTCN.address + 4) { MathSQRT.write(); return; }
	if (adr >= Regs_Arm9.Sect_system9.SQRT_PARAM_Low.address && adr < Regs_Arm9.Sect_system9.SQRT_PARAM_High.address + 4) { MathSQRT.write(); return; }

	if (adr == Regs_Arm9.Sect_system9.POWCNT1.address) 
	{
		GPU_B.swap = Regs_Arm9.Sect_system9.POWCNT1_Display_Swap.on();
		GPU_A.swap = !GPU_B.swap;

		return; 
	}
}

void MEMORY::write_DSReg7(UInt32 adr, UInt32 value, bool dwaccess)
{
	if (adr >= Regs_Arm7.Sect_sound7.SOUND0CNT.address && adr < Regs_Arm7.Sect_sound7.SNDCAP1LEN.address + 4) { if (!dwaccess || (adr & 2) == 0) Sound.set_soundreg(adr); return; }

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

	if (adr == Regs_Arm7.Sect_system7.ROMCTRL.address) { Gamecard7.writeControl(); return; }

	if (adr == Regs_Arm7.Sect_system7.IPCSYNC.address) { IPC7to9.write_sync(); return; }
	if (adr == Regs_Arm7.Sect_system7.IPCFIFOCNT.address) { IPC7to9.write_control(); return; }
	if (adr == Regs_Arm7.Sect_system7.IPCFIFOSEND.address) { IPC7to9.writefifo(value); return; }

	if (adr == Regs_Arm7.Sect_system7.AUXSPICNT.address) { Gamecard7.write_spi_cnt((UInt16)value); return; }
	if (adr == Regs_Arm7.Sect_system7.AUXSPICNT.address + 2) { Gamecard7.write_spi_dat((byte)value); return; }

	if (adr == Regs_Arm7.Sect_system7.SPICNT.address) { SPI_Intern.check_reset((UInt16)value); return; }
	if (adr == Regs_Arm7.Sect_system7.SPICNT.address + 2) { SPI_Intern.write_data((byte)value); return; }

	if (adr == Regs_Arm7.Sect_system7.POSTFLG_Flag.address) { CPU7.halt = true; return; }

	if (adr == Regs_Arm7.Sect_system7.POWCNT2.address) { Regs_Arm7.Sect_system7.POWCNT2.write(1); return; } // desmume uses written values, but does not set memory...
}

void MEMORY::set_vrammode()
{
	wrammux = Regs_Arm9.Sect_system9.MemControl2_WRAM.read();

	uint mst_a = Regs_Arm9.Sect_system9.MemControl1_VRAM_A_MST.read();
	uint mst_b = Regs_Arm9.Sect_system9.MemControl1_VRAM_B_MST.read();
	uint mst_c = Regs_Arm9.Sect_system9.MemControl1_VRAM_C_MST.read();
	uint mst_d = Regs_Arm9.Sect_system9.MemControl1_VRAM_D_MST.read();
	uint mst_e = Regs_Arm9.Sect_system9.MemControl2_VRAM_E_MST.read();
	uint mst_f = Regs_Arm9.Sect_system9.MemControl2_VRAM_F_MST.read();
	uint mst_g = Regs_Arm9.Sect_system9.MemControl2_VRAM_G_MST.read();
	uint mst_h = Regs_Arm9.Sect_system9.MemControl3_VRAM_H_MST.read();
	uint mst_i = Regs_Arm9.Sect_system9.MemControl3_VRAM_I_MST.read();

	uint offset_a = Regs_Arm9.Sect_system9.MemControl1_VRAM_A_Offset.read();
	uint offset_b = Regs_Arm9.Sect_system9.MemControl1_VRAM_B_Offset.read();
	uint offset_c = Regs_Arm9.Sect_system9.MemControl1_VRAM_C_Offset.read();
	uint offset_d = Regs_Arm9.Sect_system9.MemControl1_VRAM_D_Offset.read();
	uint offset_e = Regs_Arm9.Sect_system9.MemControl2_VRAM_E_Offset.read();
	uint offset_f = Regs_Arm9.Sect_system9.MemControl2_VRAM_F_Offset.read();
	uint offset_g = Regs_Arm9.Sect_system9.MemControl2_VRAM_G_Offset.read();
	uint offset_h = Regs_Arm9.Sect_system9.MemControl3_VRAM_H_Offset.read();
	uint offset_i = Regs_Arm9.Sect_system9.MemControl3_VRAM_I_Offset.read();

	bool ena_a = Regs_Arm9.Sect_system9.MemControl1_VRAM_A_Enable.on();
	bool ena_b = Regs_Arm9.Sect_system9.MemControl1_VRAM_B_Enable.on();
	bool ena_c = Regs_Arm9.Sect_system9.MemControl1_VRAM_C_Enable.on();
	bool ena_d = Regs_Arm9.Sect_system9.MemControl1_VRAM_D_Enable.on();
	bool ena_e = Regs_Arm9.Sect_system9.MemControl2_VRAM_E_Enable.on();
	bool ena_f = Regs_Arm9.Sect_system9.MemControl2_VRAM_F_Enable.on();
	bool ena_g = Regs_Arm9.Sect_system9.MemControl2_VRAM_G_Enable.on();
	bool ena_h = Regs_Arm9.Sect_system9.MemControl3_VRAM_H_Enable.on();
	bool ena_i = Regs_Arm9.Sect_system9.MemControl3_VRAM_I_Enable.on();

	for (int i = 0; i < 9; i++)
	{
		vrammux[i].ena9 = false;
		vrammux[i].ena7 = false;
		vrammux[i].MST = -1;
	}

	if (ena_a) set_single_vrammode(VRAMBANK::A, mst_a, offset_a);
	if (ena_b) set_single_vrammode(VRAMBANK::B, mst_b, offset_b);
	if (ena_c) set_single_vrammode(VRAMBANK::C, mst_c, offset_c);
	if (ena_d) set_single_vrammode(VRAMBANK::D, mst_d, offset_d);
	if (ena_e) set_single_vrammode(VRAMBANK::E, mst_e, offset_e);
	if (ena_f) set_single_vrammode(VRAMBANK::F, mst_f, offset_f);
	if (ena_g) set_single_vrammode(VRAMBANK::G, mst_g, offset_g);
	if (ena_h) set_single_vrammode(VRAMBANK::H, mst_h, offset_h);
	if (ena_i) set_single_vrammode(VRAMBANK::I, mst_i, offset_i);
}

void MEMORY::set_single_vrammode(VRAMBANK bank, uint mst, uint OFS)
{
	int i = (int)bank;

	vrammux[i].MST = mst;

	switch (bank)
	{
	case VRAMBANK::A:
	case VRAMBANK::B:
		switch (mst)
		{
		case 0: //LCDC
			vrammux[i].ena9 = true;
			vrammux[i].start = 0x6800000 + i * 0x20000;
			vrammux[i].end = vrammux[i].start + 0x1FFFF;
			break;
		case 1: // ARM9, 2D Graphics Engine A, BG-VRAM (max 512K)
			vrammux[i].ena9 = true;
			vrammux[i].start = 0x6000000 + OFS * 0x20000;
			vrammux[i].end = vrammux[i].start + 0x1FFFF;
			vrammux[i].gpustart = OFS * 0x20000;
			vrammux[i].gpuend = vrammux[i].gpustart + 0x1FFFF;
			break;
		case 2: // ARM9, 2D Graphics Engine A, OBJ-VRAM (max 256K)
			if (OFS < 2)
			{
				vrammux[i].ena9 = true;
				vrammux[i].start = 0x6400000 + OFS * 0x20000;
				vrammux[i].end = vrammux[i].start + 0x1FFFF;			
				vrammux[i].gpustart = OFS * 0x20000;
				vrammux[i].gpuend = vrammux[i].gpustart + 0x1FFFF;
			}
			break;
		case 3: // Texture/Rear-plane Image todo!
			vrammux[i].gpustart = OFS * 0x20000;
			vrammux[i].gpuend = vrammux[i].gpustart + 0x1FFFF;
			break;
		}
		break;

	case VRAMBANK::C:
	case VRAMBANK::D:
		switch (mst)
		{
		case 0: //LCDC
			vrammux[i].ena9 = true;
			vrammux[i].start = 0x6800000 + i * 0x20000;
			vrammux[i].end = vrammux[i].start + 0x1FFFF;
			break;
		case 1: // ARM9, 2D Graphics Engine A, BG-VRAM (max 512K)
			vrammux[i].ena9 = true;
			vrammux[i].start = 0x6000000 + OFS * 0x20000;
			vrammux[i].end = vrammux[i].start + 0x1FFFF;
			vrammux[i].gpustart = OFS * 0x20000;
			vrammux[i].gpuend = vrammux[i].gpustart + 0x1FFFF;
			break;
		case 2: // <ARM7>, Plain <ARM7>-CPU Access
			if (OFS < 2)
			{
				vrammux[i].ena7 = true;
				vrammux[i].start = 0x6000000 + OFS * 0x20000;
				vrammux[i].end = vrammux[i].start + 0x1FFFF;
				vrammux[i].gpustart = OFS * 0x20000;
				vrammux[i].gpuend = vrammux[i].gpustart + 0x1FFFF;
			}
			break;
		case 3: // Texture/Rear-plane Image todo!
			vrammux[i].gpustart = OFS * 0x20000;
			vrammux[i].gpuend = vrammux[i].gpustart + 0x1FFFF;
			break;
		case 4: // ARM9, 2D Graphics Engine B, BG - VRAM(max 128K) (C) - ARM9, 2D Graphics Engine B, OBJ-VRAM (max 128K) (D)
			vrammux[i].ena9 = true;
			vrammux[i].start = 0x6200000 + (i - 2) * 0x400000;
			vrammux[i].end = vrammux[i].start + 0x1FFFF;
			vrammux[i].gpustart = OFS * 0x20000;
			vrammux[i].gpuend = vrammux[i].gpustart + 0x1FFFF;
		}
		break;


	case VRAMBANK::E:
		switch (mst)
		{
		case 0: //LCDC
			vrammux[i].ena9 = true;
			vrammux[i].start = 0x6880000;
			vrammux[i].end = vrammux[i].start + 0xFFFF;
			vrammux[i].gpustart = 0;
			vrammux[i].gpuend = vrammux[i].gpustart + 0xFFFF;
			break;
		case 1: // ARM9, 2D Graphics Engine A, BG-VRAM (max 512K)
			vrammux[i].ena9 = true;
			vrammux[i].start = 0x6000000;
			vrammux[i].end = vrammux[i].start + 0xFFFF;
			vrammux[i].gpustart = 0;
			vrammux[i].gpuend = vrammux[i].gpustart + 0xFFFF;
			break;
		case 2: // ARM9, 2D Graphics Engine A, OBJ-VRAM (max 256K)
			vrammux[i].ena9 = true;
			vrammux[i].start = 0x6400000;
			vrammux[i].end = vrammux[i].start + 0xFFFF;
			vrammux[i].gpustart = 0;
			vrammux[i].gpuend = vrammux[i].gpustart + 0xFFFF;
			break;
		case 3: // Texture Palette todo!
			// vrammux[i].gpustart = 0;
			// vrammux[i].gpuend = vrammux[i].gpustart + 0xFFFF;
			break;
		case 4: // 2D Graphics Engine A, BG Extended Palette
			vrammux[i].gpustart = 0;
			vrammux[i].gpuend = vrammux[i].gpustart + 0xFFFF;
			break;
		}
		break;

	case VRAMBANK::F:
	case VRAMBANK::G:
		switch (mst)
		{
		case 0: //LCDC
			vrammux[i].ena9 = true;
			vrammux[i].start = 0x6890000 + 0x4000 * (i - 5);
			vrammux[i].end = vrammux[i].start + 0x3FFF;
			break;
		case 1: // ARM9, 2D Graphics Engine A, BG-VRAM (max 512K)
			vrammux[i].ena9 = true;
			switch (OFS)
			{
			case 0: vrammux[i].start = 0x6000000; vrammux[i].gpustart = 0x00000; break;
			case 1: vrammux[i].start = 0x6004000; vrammux[i].gpustart = 0x04000; break;
			case 2: vrammux[i].start = 0x6010000; vrammux[i].gpustart = 0x10000; break;
			case 3: vrammux[i].start = 0x6014000; vrammux[i].gpustart = 0x14000; break;
			}
			vrammux[i].gpuend = vrammux[i].gpustart + 0x3FFF;
			vrammux[i].end = vrammux[i].start + 0x3FFF;
			break;
		case 2: // ARM9, 2D Graphics Engine A, OBJ-VRAM (max 256K)
			vrammux[i].ena9 = true;
			switch (OFS)
			{
			case 0: vrammux[i].start = 0x6400000; vrammux[i].gpustart = 0x00000; break;
			case 1: vrammux[i].start = 0x6404000; vrammux[i].gpustart = 0x04000; break;
			case 2: vrammux[i].start = 0x6410000; vrammux[i].gpustart = 0x10000; break;
			case 3: vrammux[i].start = 0x6414000; vrammux[i].gpustart = 0x14000; break;
			}
			vrammux[i].gpuend = vrammux[i].gpustart + 0x3FFF;
			vrammux[i].end = vrammux[i].start + 0x3FFF;
			break;
		case 3: // Texture Palette todo! -> also slot choose to be done
			// vrammux[i].gpustart = 0;
			// vrammux[i].gpuend = vrammux[i].gpustart + 0x3FFF;
			break;
		case 4: // 2D Graphics Engine A, BG Extended Palette
			vrammux[i].gpustart = 0;
			if (OFS == 1) vrammux[i].gpustart += 0x4000;
			vrammux[i].gpuend = vrammux[i].gpustart + 0x3FFF;
			break;
		case 5: // 2D Graphics Engine A, OBJ Extended Palette
			vrammux[i].gpustart = 0;
			vrammux[i].gpuend = vrammux[i].gpustart + 0x3FFF;
			break;
		}
		break;

	case VRAMBANK::H:
		switch (mst)
		{
		case 0: //LCDC
			vrammux[i].ena9 = true;
			vrammux[i].start = 0x6898000;
			vrammux[i].end = vrammux[i].start + 0x7FFF;
			break;
		case 1: //ARM9, 2D Graphics Engine B, BG-VRAM (max 128K)
			vrammux[i].ena9 = true;
			vrammux[i].start = 0x6200000;
			vrammux[i].end = vrammux[i].start + 0x7FFF;
			vrammux[i].gpustart = 0;
			vrammux[i].gpuend = vrammux[i].gpustart + 0x7FFF;
			break;
		case 2: //2D Graphics Engine B, BG Extended Palette
			vrammux[i].gpustart = 0;
			vrammux[i].gpuend = vrammux[i].gpustart + 0x7FFF;
			break;
		}
		break;

	case VRAMBANK::I:
		switch (mst)
		{
		case 0: //LCDC
			vrammux[i].ena9 = true;
			vrammux[i].start = 0x68A0000;
			vrammux[i].end = vrammux[i].start + 0x3FFF;
			break;
		case 1: //ARM9, 2D Graphics Engine B, BG-VRAM (max 128K)
			vrammux[i].ena9 = true;
			vrammux[i].start = 0x6208000;
			vrammux[i].end = vrammux[i].start + 0x3FFF;
			vrammux[i].gpustart = 0;
			vrammux[i].gpuend = vrammux[i].gpustart + 0x3FFF;
		case 2: //ARM9, 2D Graphics Engine B, OBJ-VRAM (max 128K)
			vrammux[i].ena9 = true;
			vrammux[i].start = 0x6600000;
			vrammux[i].end = vrammux[i].start + 0x3FFF;
			vrammux[i].gpustart = 0;
			vrammux[i].gpuend = vrammux[i].gpustart + 0x3FFF;
			break;
		case 3: //2D Graphics Engine B, OBJ Extended Palette
			vrammux[i].gpustart = 0;
			vrammux[i].gpuend = vrammux[i].gpustart + 0x3FFF;
			break;
		}
		break;

	}
}

UInt32 MEMORY::get_vram_address(bool isArm9, UInt32 address_in)
{
	for (int i = 0; i < 9; i++)
	{
		if ((isArm9 && vrammux[i].ena9) || (!isArm9 && vrammux[i].ena7))
		{
			if (address_in >= vrammux[i].start && address_in <= vrammux[i].end)
			{
				return vrammux[i].vramoffset + (address_in - vrammux[i].start);
			}
		}
	}

	return 0xFFFFFFFF;
}