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

enum VRAMBANK
{
	A, B, C, D, E, F, G, H, I
};

class VRAMMUX
{
public:
	bool ena9;
	bool ena7;
	uint MST;
	uint start;
	uint end;
	uint vramoffset;
	uint gpustart;
	uint gpuend;
};

class MEMORY
{
public:
	bool has_tilt = false;
	bool gpio_enable = false;

	Byte WRAM_Large[4194304];
	Byte WRAM_Small_64[65536];
	Byte WRAM_Small_32[32768];
	Byte VRAM[671744];
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

	byte wrammux;

	bool unreadable;
	UInt32 lastreadvalue;

	bool gpio_used;

	VRAMMUX vrammux[9];

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
	void set_vrammode();
	void set_single_vrammode(VRAMBANK bank, uint mst, uint OFS);
	UInt32 get_vram_address(bool isArm9, UInt32 address_in);
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