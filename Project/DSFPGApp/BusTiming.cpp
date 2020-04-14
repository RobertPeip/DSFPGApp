#include <algorithm>
using namespace std;

#include "BusTiming.h"
#include "CPU.h"
#include "GPU_Timing.h"
#include "CPUCache.h"

BUSTiming BusTiming;

void BUSTiming::reset()
{
}

void BUSTiming::update(UInt16 value)
{
}

int BUSTiming::dataTicksAccess816(bool isArm9, bool is8Bit, UInt32 address, bool isRead, uint& lastAddress) // DATA 8/16bits NON SEQ
{
	UInt32 addr = (address >> 24) & 15;

	if (isArm9)
	{
		if ((address & (~0x3FFF)) == Co15.DTCMRegion)
		{
			return 1;
		}

		if (addr == 2)
		{
			if (DataCache.inCache(address, isRead))
			{
				lastAddress = address;
				return 1;
			}
			else
			{
				int ticks = 0;
				if ((is8Bit && address == lastAddress + 1) || (!is8Bit && address == lastAddress + 2))
				{
					ticks = 2;
				}
				else if (isRead)
				{
					ticks += (2 * 5);
				}
				else
				{
					ticks = (2 * 2);
				}

				if (isRead)
				{
					ticks += (8 * 2 * 2);
				}
				lastAddress = address;
				return ticks;
			}
		}

		int value = memoryWait16Arm9[addr];

		if ((is8Bit && address != lastAddress + 1) || (!is8Bit && address != lastAddress + 2))
		{
			value += 6;
		}
	
		lastAddress = address;
		return value;
	}
	else
	{
		int value = memoryWait16Arm7[addr];

		if ((is8Bit && address != lastAddress + 1) ||(!is8Bit && address != lastAddress + 2))
		{
			value += 1;
		}

		lastAddress = address;
		return value;
	}
}

int BUSTiming::dataTicksAccess32(bool isArm9, UInt32 address, bool isRead, uint& lastAddress) // DATA 32bits NON SE
{
	UInt32 addr = (address >> 24) & 15;

	if (isArm9)
	{
		if ((address & (~0x3FFF)) == Co15.DTCMRegion)
		{
			lastAddress = address;
			return 1;
		}

		if (addr == 2)
		{
			if (DataCache.inCache(address, isRead))
			{
				lastAddress = address;
				return 1;
			}
			else
			{
				int ticks = 0;
				if (address == lastAddress + 4)
				{
					ticks = 4;
				}
				else if (isRead)
				{
					ticks += (4 * 5);
				}
				else
				{
					ticks = (4 * 2);
				}

				if (isRead)
				{
					ticks += (8 * 2 * 2);
				}
				lastAddress = address;
				return ticks;
			}
		}

		int value = memoryWait32Arm9[addr];

		if (address != lastAddress + 4)
		{
			value += 6;
		}

		lastAddress = address;
		return value;
	}
	else
	{
		int value = memoryWait32Arm7[addr];

		if (address != lastAddress + 4)
		{
			value += 1;
		}

		lastAddress = address;
		return value;
	}
}

int BUSTiming::codeTicksAccess16(bool isArm9, UInt32 address) // THUMB NON SEQ
{
	UInt32 addr = (address >> 24) & 15;

	return 1; // memoryWait16Arm9[addr];
}

int BUSTiming::codeTicksAccess32(bool isArm9, UInt32 address) // ARM NON SEQ
{
	UInt32 addr = (address >> 24) & 15;

	return 1; // memoryWait32[addr];
}

int BUSTiming::codeTicksAccessSeq16(bool isArm9, UInt32 address) // THUMB SEQ
{
	UInt32 addr = (address >> 24) & 15;

	return 1; //memoryWaitSeq[addr];
}

int BUSTiming::codeTicksAccessSeq32(bool isArm9, UInt32 address) // ARM SEQ
{
	UInt32 addr = (address >> 24) & 15;
	if (isArm9)
	{
		return 1;
	}
	else
	{
		return memoryWait32Arm7[addr];
	}
}

int BUSTiming::dmaTicksAccess16(bool isArm9, UInt32 address)
{
	UInt32 addr = (address >> 24) & 15;
	if (isArm9)
	{
		return memoryWait16Arm9[addr];
	}
	else
	{
		return memoryWait16Arm7[addr];
	}
}
int BUSTiming::dmaTicksAccess32(bool isArm9, UInt32 address)
{
	UInt32 addr = (address >> 24) & 15;
	if (isArm9)
	{
		return memoryWait32Arm9[addr];
	}
	else
	{
		return memoryWait32Arm7[addr];
	}
}