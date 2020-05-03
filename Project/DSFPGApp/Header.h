#pragma once

#include "types.h"

class HEADER
{
public:
	uint ARM9_CODE_SRC;	 // 020h    4     ARM9 rom_offset(4000h and up, align 1000h)
	uint ARM9_CODE_PC;	 // 024h    4     ARM9 entry_address(2000000h..23BFE00h)
	uint ARM9_CODE_DST;	 // 028h    4     ARM9 ram_address(2000000h..23BFE00h)
	uint ARM9_CODE_SIZE; // 02Ch    4     ARM9 size(max 3BFE00h) (3839.5KB)
	uint ARM7_CODE_SRC;	 // 030h    4     ARM7 rom_offset(8000h and up)
	uint ARM7_CODE_PC;	 // 034h    4     ARM7 entry_address(2000000h..23BFE00h, or 37F8000h..3807E00h)
	uint ARM7_CODE_DST;	 // 038h    4     ARM7 ram_address(2000000h..23BFE00h, or 37F8000h..3807E00h)
	uint ARM7_CODE_SIZE; // 03Ch    4     ARM7 size(max 3BFE00h, or FE00h) (3839.5KB, 63.5KB)

	uint cardSize;
	uint chipID;

	void read();
	bool FindArray(byte* array, unsigned int arraylength, byte* pattern, int patternlength);
};
extern HEADER Header;