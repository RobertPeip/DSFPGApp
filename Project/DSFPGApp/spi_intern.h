#pragma once

#include "types.h"

enum class FIRMWARESTATE
{
	IDLE,
	CMD_READ
};

class SPI_INTERN
{
public:
	UInt32 oldselect;
	bool oldhold;

	bool powerman_control_written;
	byte powerman_control;
	byte powerman_regs[5];

	bool first;
	byte lastcommand;

	UInt16 adc_x;
	UInt16 adc_y;
	bool touched;
	int adc_jitterctr;

	FIRMWARESTATE firmwarestate;
	UInt32 firmware_address;
	int firmware_wordcnt;

	void reset();
	void check_reset(UInt16 value);
	void write_data(UInt16 value);
	void updateADCTouchPos(bool touch, int scrX_lsl4, int scrY_lsl4);

private:
	void CalculateTouchPressure(int pressurePercent, UInt16& z1, UInt16& z2);
	byte firmwareCommand(byte data);
};
extern SPI_INTERN SPI_Intern;