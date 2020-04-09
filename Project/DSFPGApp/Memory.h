#pragma once
#include <string>
using namespace std;

#include "types.h"

enum class ACCESSTYPE
{
	CPUINSTRUCTION,
	CPUDATA,
	DMA
};

class MEMORY
{
public:
	bool has_tilt = false;
	bool gpio_enable = false;

	Byte WRAM_Large[4194304];
	Byte WRAM_Small[98304];
	Byte VRAM[655360];
	Byte OAMRAM[2048];
	Byte PaletteRAM[2048];
	Byte GameRom[33554432]; // 32mbyte max for now

	Byte ITCM[32768];
	Byte DTCM[16384];

	UInt32 GameRom_max;
	byte blockcmd_lowerbits;

	Byte GameRamSnapshot[131072 + 8192];
	bool createGameRAMSnapshot;

	Byte Bios7[16384];
	Byte Bios9[4096];

	bool EEPROMEnabled;
	bool FlashEnabled;
	bool SramEnabled;
	bool EEPROMSensorEnabled;
	//Func<UInt32, byte, object> SaveGameFunc;

	byte biosProtected[4];

	UInt16 tiltx;
	UInt16 tilty;

	bool unreadable;
	UInt32 lastreadvalue;

	bool gpio_used;

	void reset(string filename);
	void GameRAMSnapshot();
	void load_gameram(string gamename);
	void save_gameram(string gamename);
	byte read_unreadable_byte(UInt32 offset);
	UInt16 read_unreadable_word();
	UInt32 read_unreadable_dword();

	void prepare_read_DSReg9(UInt32 adr);
	void prepare_read_DSReg7(UInt32 adr);
	void write_DSReg9(UInt32 adr, UInt32 value, bool dwaccess);
	void write_DSReg7(UInt32 adr, UInt32 value, bool dwaccess);
};
extern MEMORY Memory;

byte read_byte_9(ACCESSTYPE accesstype, UInt32 address);
UInt32 read_word_9(ACCESSTYPE accesstype, UInt32 address);
UInt32 read_dword_9(ACCESSTYPE accesstype, UInt32 address);
void write_byte_9(ACCESSTYPE accesstype, UInt32 address, byte data);
void write_word_9(ACCESSTYPE accesstype, UInt32 address, UInt16 data);
void write_dword_9(ACCESSTYPE accesstype, UInt32 address, UInt32 data);

byte read_byte_7(ACCESSTYPE accesstype, UInt32 address);
UInt32 read_word_7(ACCESSTYPE accesstype, UInt32 address);
UInt32 read_dword_7(ACCESSTYPE accesstype, UInt32 address);
void write_byte_7(ACCESSTYPE accesstype, UInt32 address, byte data);
void write_word_7(ACCESSTYPE accesstype, UInt32 address, UInt16 data);
void write_dword_7(ACCESSTYPE accesstype, UInt32 address, UInt32 data);