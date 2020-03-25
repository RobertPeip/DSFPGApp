#include "Header.h"
#include "Memory.h"
#include "Flash.h"

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
}

//void HEADER::check_flash_size()
//{
//	byte bytes[] = { 'F', 'L', 'A', 'S', 'H', '1', 'M', '_', 'V' };
//	if (FindArray(Memory.GameRom, Memory.GameRom_max, bytes, 9))
//	{
//		Flash.flashSetSize(0x20000);
//	}
//}

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