#include <algorithm>
using namespace std;

#include "BusTiming.h"
#include "CPU.h"
#include "GBRegs.h"
#include "GPU_Timing.h"
#include "CPUCache.h"

BUSTiming BusTiming;

void BUSTiming::reset()
{
	byte memoryWait_new[] = { 0, 0, 2, 0, 0, 0, 0, 0, 4, 4, 4, 4, 4, 4, 4, 0 }; std::copy(std::begin(memoryWait_new), std::end(memoryWait_new), std::begin(memoryWait));
	byte memoryWait32_new[] = { 0, 0, 5, 1, 1, 1, 1, 0, 7, 7, 9, 9, 13, 13, 4, 0 }; std::copy(std::begin(memoryWait32_new), std::end(memoryWait32_new), std::begin(memoryWait32));
	byte memoryWaitSeq_new[] = { 0, 0, 2, 0, 0, 0, 0, 0, 2, 2, 4, 4, 8, 8, 4, 0 }; std::copy(std::begin(memoryWaitSeq_new), std::end(memoryWaitSeq_new), std::begin(memoryWaitSeq));
	byte memoryWaitSeq32_new[] = { 0, 0, 5, 0, 0, 1, 1, 0, 5, 5, 9, 9, 17, 17, 4, 0 }; std::copy(std::begin(memoryWaitSeq32_new), std::end(memoryWaitSeq32_new), std::begin(memoryWaitSeq32));

	lastAddress = 0;
}

void BUSTiming::update(UInt16 value)
{
	memoryWait[0x0e] = memoryWaitSeq[0x0e] = gamepakRamWaitState[value & 3];

	memoryWait[0x08] = memoryWait[0x09] = gamepakWaitState[(value >> 2) & 3];
	memoryWaitSeq[0x08] = memoryWaitSeq[0x09] = gamepakWaitState0[(value >> 4) & 1];

	memoryWait[0x0a] = memoryWait[0x0b] = gamepakWaitState[(value >> 5) & 3];
	memoryWaitSeq[0x0a] = memoryWaitSeq[0x0b] = gamepakWaitState1[(value >> 7) & 1];

	memoryWait[0x0c] = memoryWait[0x0d] = gamepakWaitState[(value >> 8) & 3];
	memoryWaitSeq[0x0c] = memoryWaitSeq[0x0d] = gamepakWaitState2[(value >> 10) & 1];

	for (int i = 8; i < 15; i++)
	{
		memoryWait32[i] = (byte)(memoryWait[i] + memoryWaitSeq[i] + 1);
		memoryWaitSeq32[i] = (byte)(memoryWaitSeq[i] * 2 + 1);
	}
}

int BUSTiming::dataTicksAccess16(bool isArm9, UInt32 address, int cycleadd) // DATA 8/16bits NON SEQ
{
	UInt32 addr = (address >> 24) & 15;

	if (isArm9 && addr == 2)
	{
		if (DataCache.inCache(address))
		{
			return 1;
		}
		else
		{
			return (4 * 5) + (8 * 2 * 2);
		}
	}

	int value = memoryWait32[addr];

	if (address != lastAddress + 2)
	{
		if (isArm9)
		{
			value *= 2;
			value += 6;
		}
		else
		{
			value += 1;
		}
	}
	lastAddress = address;

	return value;
}

int BUSTiming::dataTicksAccess32(bool isArm9, UInt32 address, int cycleadd) // DATA 32bits NON SE
{
	UInt32 addr = (address >> 24) & 15;

	if (isArm9 && addr == 2)
	{
		if (DataCache.inCache(address))
		{
			return 1;
		}
		else
		{
			return (4 * 5) + (8 * 2 * 2);
		}
	}

	int value = memoryWait32[addr];

	if (address != lastAddress + 4)
	{
		if (isArm9)
		{
			value *= 2;
			value += 6;
		}
		else
		{
			value += 1;
		}
	}
	lastAddress = address;

	return value;
}

int BUSTiming::dataTicksAccessSeq32(UInt32 address, int cycleadd) // DATA 32bits SEQ
{
	UInt32 addr = (address >> 24) & 15;
	int value = memoryWaitSeq32[addr];


	return value;
}

int BUSTiming::codeTicksAccess16(UInt32 address) // THUMB NON SEQ
{
	UInt32 addr = (address >> 24) & 15;

	return memoryWait[addr];
}

int BUSTiming::codeTicksAccess32(UInt32 address) // ARM NON SEQ
{
	UInt32 addr = (address >> 24) & 15;

	return 0; // memoryWait32[addr];
}

int BUSTiming::codeTicksAccessSeq16(UInt32 address) // THUMB SEQ
{
	UInt32 addr = (address >> 24) & 15;

	return memoryWaitSeq[addr];
}

int BUSTiming::codeTicksAccessSeq32(UInt32 address) // ARM SEQ
{
	UInt32 addr = (address >> 24) & 15;

	return 0; // memoryWaitSeq32[addr];
}

