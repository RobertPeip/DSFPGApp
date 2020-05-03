#include "Header.h"
#include "Memory.h"

HEADER Header;

void HEADER::read()
{
	ARM9_CODE_SRC  = *(UInt32*)&Memory.GameRom[0x20];
	ARM9_CODE_PC   = *(UInt32*)&Memory.GameRom[0x24];
	ARM9_CODE_DST  = *(UInt32*)&Memory.GameRom[0x28];
	ARM9_CODE_SIZE = *(UInt32*)&Memory.GameRom[0x2C];
	ARM7_CODE_SRC  = *(UInt32*)&Memory.GameRom[0x30];
	ARM7_CODE_PC   = *(UInt32*)&Memory.GameRom[0x34];
	ARM7_CODE_DST  = *(UInt32*)&Memory.GameRom[0x38];
	ARM7_CODE_SIZE = *(UInt32*)&Memory.GameRom[0x3C];

	cardSize =  *(UInt16*)&Memory.GameRom[0x14];
	chipID = 0xC2;
	chipID |= ((((128 << cardSize) / 1024) - 1) << 8); // Chip size in megabytes minus 1 (07h = 8MB, 0Fh = 16MB, 1Fh = 32MB, 3Fh = 64MB, 7Fh = 128MB)
}

bool HEADER::FindArray(byte* array, unsigned int arraylength,  byte* pattern, int patternlength)
{
	int success = 0;
	for (int i = 0; i < arraylength; i++)
	{
		if (array[i] == pattern[success])
		{
			success++;
		}
		else
		{
			success = 0;
		}

		if (patternlength == success)
		{
			return true;
		}
	}
	return false;
}