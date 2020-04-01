#pragma once

#include "types.h"

class SPI_INTERN
{
public:
	bool powerman_control_written;
	byte powerman_control;
	byte powerman_regs[5];

	void reset();
	void write_data(byte value);

};
extern SPI_INTERN SPI_Intern;