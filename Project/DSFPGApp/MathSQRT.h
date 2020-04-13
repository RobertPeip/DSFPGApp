#pragma once

#include "types.h"

class MATHSQRT
{
public:
	bool calculating;
	UInt64 next_event_time;

	void reset();
	void write();
	void finish();
};
extern MATHSQRT MathSQRT;