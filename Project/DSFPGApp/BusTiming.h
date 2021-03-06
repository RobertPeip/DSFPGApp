#pragma once

#include "types.h"

class BUSTiming
{
public:
	byte memoryWait32Arm9[16] = { 0x01, 0x01, 0x04, 0x02, 0x02, 0x04, 0x04, 0x02, 0x20, 0x20, 0x20, 0x02, 0x02, 0x02, 0x02, 0x02 };
	byte memoryWait32Arm7[16] = { 0x01, 0x01, 0x02, 0x01, 0x01, 0x02, 0x02, 0x01, 0x10, 0x10, 0x10, 0x01, 0x01, 0x01, 0x01, 0x01 };
	byte memoryWait16Arm9[16] = { 0x01, 0x01, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x10, 0x10, 0x10, 0x02, 0x02, 0x02, 0x02, 0x02 };
	byte memoryWait16Arm7[16] = { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x08, 0x08, 0x08, 0x01, 0x01, 0x01, 0x01, 0x01 };

	void reset();
	int dataTicksAccess816(bool isArm9, bool is8Bit, UInt32 address, bool isRead, uint& lastAddress); // DATA 8/16bits NON SEQ
	int dataTicksAccess32(bool isArm9, UInt32 address, bool isRead, uint& lastAddress); // DATA 32bits NON SE
	int codeTicksAccess16(bool isArm9, UInt32 address); // THUMB NON SEQ
	int codeTicksAccess32(bool isArm9, UInt32 address); // ARM NON SEQ
	int codeTicksAccessSeq16(bool isArm9, UInt32 address); // THUMB SEQ
	int codeTicksAccessSeq32(bool isArm9, UInt32 address); // ARM SEQ
	int dmaTicksAccess16(bool isArm9, UInt32 address);
	int dmaTicksAccess32(bool isArm9, UInt32 address);
};
extern BUSTiming BusTiming;