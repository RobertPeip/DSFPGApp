#pragma once

#include "types.h"

class MATHDIV
{
public:
	bool calculating;
	UInt64 next_event_ticks;

	void reset();
	void write();
	void finish();
};
extern MATHDIV MathDIV;