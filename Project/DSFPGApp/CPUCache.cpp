#include "CPUCache.h"

CPUCache InstrCache(64);
CPUCache DataCache(32);

CPUCache::CPUCache(byte LINES)
{
	this->LINES = LINES;
	SUBTAGBITS = 10; // dword = 2, 32 lines = 5, 8 dwords = 3
	TAGMASK = 0xFFFFFC00;
	LINEMASK = 0x3E0;
	if (LINES == 64)
	{
		SUBTAGBITS++;
		TAGMASK = 0xFFFFF800;
		LINEMASK = 0x7E0;
	}
}

void CPUCache::reset()
{
	for (int i = 0; i < LINES; i++)
	{
		for (int a = 0; a < ASSOCIATIVITY; a++)
		{
			tags[i][a] = 0xFFFFFFFF;
		}
		rrb[i] = 0;
	}

}

bool CPUCache::inCache(uint address, bool isRead)
{
	address &= 0x03FFFFF; // mask for wram large
	uint maskedaddress = (address & TAGMASK) >> SUBTAGBITS;
	int line = (address & LINEMASK) >> 5;
	for (int a = 0; a < ASSOCIATIVITY; a++)
	{
		if (tags[line][a] == maskedaddress)
		{
			return true;
		}
	}
	if (isRead)
	{
		tags[line][rrb[line]] = maskedaddress;
		rrb[line] = (rrb[line] + 1) % 4;
	}
	return false;
}