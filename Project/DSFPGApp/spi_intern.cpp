#include "spi_intern.h"
#include "regs_arm7.h"
#include "Joypad.h"
#include "Memory.h"

SPI_INTERN SPI_Intern;

void SPI_INTERN::reset()
{
	oldselect = 0;

	first = true;
	lastcommand = 0;

	adc_x = 0;
	adc_y = 0;
	touched = false;

	firmwarestate = FIRMWARESTATE::IDLE;
	firmware_address = 0;
	firmware_wordcnt = 0;

	powerman_control = 0;
	powerman_regs[0] = 0x0D;
	powerman_regs[1] = 0x00;
	powerman_regs[2] = 0x01;
	powerman_regs[3] = 0x00;
	powerman_regs[4] = 0x03;
	powerman_control_written = false;
}

void SPI_INTERN::check_reset(UInt16 value)
{
	UInt32 newselect = Regs_Arm7.Sect_system7.SPICNT_Device_Select.read();

	bool reset = true;
	if (newselect == 1 && oldselect == 1 && oldhold)
	{
		reset = false;
	}
	if (reset)
	{
		firmwarestate = FIRMWARESTATE::IDLE;
	}

	oldhold = Regs_Arm7.Sect_system7.SPICNT_Chipselect_Hold.read();
	oldselect = newselect;
}

void SPI_INTERN::write_data(UInt16 value)
{
	if (value == 0)
	{
		Regs_Arm7.Sect_system7.SPIDATA.write(lastcommand);
	}
	else
	{
		lastcommand = value;
	}

	UInt16 retval = value;

	switch (Regs_Arm7.Sect_system7.SPICNT_Device_Select.read())
	{
	case 0:
		if (!powerman_control_written)
		{
			powerman_control = value;
		}
		else
		{
			byte reg = powerman_control & 7;
			if (reg > 4) reg = 4; // ds lite register style (DS is 0..3)

			if ((powerman_control & 0x80) > 0) //read
			{
				retval = powerman_regs[reg];
			}
			else
			{
				powerman_regs[reg] = value;
				// everything set here unused in emulation!
			}
		}
		powerman_control_written = !powerman_control_written;
		break;

	case 1:
		if (Regs_Arm7.Sect_system7.SPICNT_Baudrate.read() != 0)
		{
			retval = 0;
		}
		else
		{
			retval = firmwareCommand((byte)value);
		}
		break;

	case 2:
		UInt16 scratch;
		switch (Regs_Arm7.Sect_system7.SPIDATA_Channel_Select.read())
		{
		case 0: // Temperature 0 (requires calibration, step 2.1mV per 1'C accuracy)
			if (Regs_Arm7.Sect_system7.SPICNT_Chipselect_Hold.on())
			{
				if (first)
				{
					retval = ((716 << 3) & 0x7FF);
					first = false;
					break;
				}
				retval = (716 >> 5);
				first = true;
				break;
			}
			retval = ((716 << 3) & 0x7FF);
			first = true;
			break;

		case 1: // Touchscreen Y - Position(somewhat 0B0h..F20h, or FFFh = released)
			adc_jitterctr++;
			if (adc_jitterctr == 25)
			{
				adc_jitterctr = 0;
				//if (CommonSettings.gamehacks.flags.stylusjitter) // simulate a shaky human hand or multiple reads, this is actually important for some games.. seemingly due to bugs.
				//{
				//	nds.adc_touchY ^= 16;
				//	nds.adc_touchX ^= 16;
				//}
			}
			if (Regs_Arm7.Sect_system7.SPICNT_Chipselect_Hold.on())
			{
				if (first)
				{
					retval = (adc_y << 3) & 0xFF;
					first = false;
					break;
				}

				retval = (adc_y >> 5) & 0xFF;
				first = true;
				break;
			}
			retval = (adc_y << 3) & 0xFF;
			first = true;
			break;

		case 2: // Battery Voltage(not used, connected to GND in NDS, always 000h)
			retval = 0;
			break;

		case 3: // Touchscreen Z1 - Position(diagonal position for pressure measurement)
			CalculateTouchPressure(0x32, value, scratch);

			if (Regs_Arm7.Sect_system7.SPICNT_Chipselect_Hold.on())
			{
				if (first)
				{
					retval = ((value << 3) & 0x7FF);
					first = false;
					break;
				}
				retval = (value >> 5);
				first = true;
				break;
			}
			retval = ((value << 3) & 0x7FF);
			first = true;
			break;

		case 4: // Touchscreen Z2 - Position(diagonal position for pressure measurement)
			CalculateTouchPressure(0x32, value, scratch);

			if (Regs_Arm7.Sect_system7.SPICNT_Chipselect_Hold.on())
			{
				if (first)
				{
					retval = ((value << 3) & 0x7FF);
					first = false;
					break;
				}
				retval = (value >> 5);
				first = true;
				break;
			}
			retval = ((value << 3) & 0x7FF);
			first = true;
			break;

		case 5: // Touchscreen X - Position(somewhat 100h..ED0h, or 000h = released)	
			if (Regs_Arm7.Sect_system7.SPICNT_Chipselect_Hold.on())
			{
				if (first)
				{
					retval = (adc_x << 3) & 0xFF;
					first = false;
					break;
				}
				retval = (adc_x >> 5) & 0xFF;
				first = true;
				break;
			}
			retval = (adc_x << 3) & 0xFF;
			first = true;
			break;

		case 6: // AUX Input(connected to Microphone in the NDS)
			retval = 0;
			break;

		case 7: // Temperature 1 (difference to Temp 0, without calibration, 2'C accuracy)
			if (Regs_Arm7.Sect_system7.SPICNT_Chipselect_Hold.on())
			{
				if (first)
				{
					retval = ((865 << 3) & 0x7FF);
					first = false;
					break;
				}
				retval = (865 >> 5);
				first = true;
				break;
			}
			retval = ((865 << 3) & 0x7FF);
			first = true;
			break;
		}
		break;
	}

	Regs_Arm7.Sect_system7.SPIDATA.write(retval & 0xFF);

}

void SPI_INTERN::updateADCTouchPos(bool touch, int touch_x, int touch_y)
{
	touched = touch;
	if (touch)
	{
		byte screen_x1 = 33;
		byte screen_y1 = 33;
		UInt16 screen_width = 192;
		UInt16 screen_height = 96;
		UInt16 adc_x1 = 512;
		UInt16 adc_y1 = 512;
		UInt16 adc_width = 3072;
		UInt16 adc_height = 1536;

		//touch_x >>= 4;
		int rv = ((touch_x - screen_x1 + 1) * adc_width) / screen_width + adc_x1;
		if (rv < 0) rv = 0;
		if (rv > 0xFFF) rv = 0xFFF;
		adc_x = rv;

		//touch_y >>= 4;
		rv = ((touch_y - screen_y1 + 1) * adc_height) / screen_height + adc_y1;
		if (rv < 0) rv = 0;
		if (rv > 0xFFF) rv = 0xFFF;
		adc_y = rv;

		adc_jitterctr = 0;
	}
	//else
	//{
	//	adc_x = 0;
	//	adc_y = 0;
	//}

	Joypad.KeyPen = touched;
}

void SPI_INTERN::CalculateTouchPressure(int pressurePercent, UInt16& z1, UInt16& z2)
{
	if (!touched)
	{
		z1 = z2 = 0;
		return;
	}
	int y = adc_x; // nds.scr_touchY;
	int x = adc_y; // nds.scr_touchX;
	float u = (x / 256.0f);
	float v = (y / 192.0f);

	//these coefficients 

	float fPressurePercent = pressurePercent / 100.0f;
	//z1 goes up as pressure goes up
	{
		float b0 = (96 - 80) * fPressurePercent + 80;
		float b1 = (970 - 864) * fPressurePercent + 864;
		float b2 = (192 - 136) * fPressurePercent + 136;
		float b3 = (1560 - 1100) * fPressurePercent + 1100;
		z1 = (UInt16)(int)(b0 + (b1 - b0) * u + (b2 - b0) * v + (b3 - b2 - b1 + b0) * u * v);
	}

	//z2 goes down as pressure goes up
	{
		float b0 = (1976 - 2300) * fPressurePercent + 2300;
		float b1 = (2360 - 2600) * fPressurePercent + 2600;
		float b2 = (3840 - 3900) * fPressurePercent + 3900;
		float b3 = (3912 - 3950) * fPressurePercent + 3950;
		z2 = (UInt16)(int)(b0 + (b1 - b0) * u + (b2 - b0) * v + (b3 - b2 - b1 + b0) * u * v);
	}
}

byte SPI_INTERN::firmwareCommand(byte data)
{
	switch (firmwarestate)
	{
	case FIRMWARESTATE::IDLE:
		switch (data)
		{
		case 0x03:
			firmwarestate = FIRMWARESTATE::CMD_READ;
			firmware_address = 0;
			firmware_wordcnt = 3;
		}
		break;

	case FIRMWARESTATE::CMD_READ:
		if (firmware_wordcnt > 0)
		{
			firmware_wordcnt--;
			firmware_address |= data << (firmware_wordcnt * 8);
		}
		else
		{
			if (firmware_address < 262144)
			{
				data = Memory.Firmware[firmware_address];
				firmware_address++;
			}
		}
		break;

	}

	return data;
}