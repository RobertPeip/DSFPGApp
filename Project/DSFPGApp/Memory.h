#pragma once
#include <string>
using namespace std;

#include "types.h"

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

	UInt32 GameRom_max;
	byte blockcmd_lowerbits;

	Byte GameRamSnapshot[131072 + 8192];
	bool createGameRAMSnapshot;

	Byte GBRom[16384];

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
	byte read_byte(UInt32 address);
	UInt32 read_word(UInt32 address);
	UInt32 read_dword(UInt32 address);
	void write_byte(UInt32 address, byte data);
	void write_word(UInt32 address, UInt16 data);
	void write_dword(UInt32 address, UInt32 data);
	void prepare_read_DSReg(UInt32 adr);
	void write_DSReg(UInt32 adr, UInt32 value, bool dwaccess);
};
extern MEMORY Memory;