#include "spi_intern.h"
#include "regs_arm7.h"

SPI_INTERN SPI_Intern;

void SPI_INTERN::reset()
{
	powerman_regs[0] = 0x0D;
	powerman_regs[1] = 0x00;
	powerman_regs[2] = 0x01;
	powerman_regs[3] = 0x00;
	powerman_regs[4] = 0x03;
	powerman_control_written = false;
}

void SPI_INTERN::write_data(byte value)
{
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
				value = powerman_regs[reg];
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
			value = 0;
		}
		else
		{
			value = 0; // fw_transfer(&MMU.fw, (u8)val);
		}
		break;

	case 2:
		break;
	}

	Regs_Arm7.Sect_system7.SPIDATA.write(value);

}