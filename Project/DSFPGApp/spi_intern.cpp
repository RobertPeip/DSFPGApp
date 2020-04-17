#include "spi_intern.h"
#include "regs_arm7.h"

SPI_INTERN SPI_Intern;

void SPI_INTERN::reset()
{
	first = true;
	lastcommand = 0;

	powerman_regs[0] = 0x0D;
	powerman_regs[1] = 0x00;
	powerman_regs[2] = 0x01;
	powerman_regs[3] = 0x00;
	powerman_regs[4] = 0x03;
	powerman_control_written = false;
}

void SPI_INTERN::write_data(byte value)
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
			retval = 0; // fw_transfer(&MMU.fw, (u8)val);
		}
		break;

	case 2:
		int path = 0;
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
			first = 1;
			break;

		case 1: // Touchscreen Y - Position(somewhat 0B0h..F20h, or FFFh = released)
		    path = 1;
			break;

		case 2: // Battery Voltage(not used, connected to GND in NDS, always 000h)
			path = 2;
			break;

		case 3: // Touchscreen Z1 - Position(diagonal position for pressure measurement)
			path = 3;
			break;

		case 4: // Touchscreen Z2 - Position(diagonal position for pressure measurement)
			path = 4;
			break;

		case 5: // Touchscreen X - Position(somewhat 100h..ED0h, or 000h = released)	
			path = 5;
			break;

		case 6: // AUX Input(connected to Microphone in the NDS)
			path = 6;
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