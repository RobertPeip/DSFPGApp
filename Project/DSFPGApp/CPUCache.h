#pragma once

#include "types.h"

class CPUCache
{
public:
	const byte LINESIZE = 8;
	const byte ASSOCIATIVITY = 4;
	byte LINES;
	byte SUBTAGBITS; // bits for lower address below tag
	byte LINEMASK;
	uint TAGMASK;
	byte rrb;

	uint tags[64][4];  // upper 32 for datacache unused, but this way it's static

	CPUCache(byte LINES);
	void reset();
	bool inCache(uint address);
};
extern CPUCache InstrCache;
extern CPUCache DataCache;