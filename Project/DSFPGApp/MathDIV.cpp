#include "MathDIV.h"
#include "regs_arm9.h"
#include "gameboy.h"

MATHDIV MathDIV;

void MATHDIV::reset()
{
	calculating = false;
}

void MATHDIV::write()
{
	calculating = true;
	Regs_Arm9.Sect_system9.DIVCNT_Busy.write(1);
	if (Regs_Arm9.Sect_system9.DIVCNT_Division_Mode.read() == 0)
	{
		next_event_time = gameboy.totalticks + 18 * 2;
	}
	else
	{
		next_event_time = gameboy.totalticks + 34 * 2;
	}
}

void MATHDIV::finish()
{
	if (gameboy.totalticks >= next_event_time)
	{
		calculating = false;
		Regs_Arm9.Sect_system9.DIVCNT_Busy.write(0);
		uint numer_low = Regs_Arm9.Sect_system9.DIV_NUMER_Low.read();
		uint numer_high = Regs_Arm9.Sect_system9.DIV_NUMER_High.read();
		uint denom_low = Regs_Arm9.Sect_system9.DIV_DENOM_Low.read();
		uint denom_high = Regs_Arm9.Sect_system9.DIV_DENOM_High.read();
		Int64 numer64 = (Int64)(((UInt64)numer_low) | (((UInt64)numer_high) << 32));
		Int64 denom64 = (Int64)(((UInt64)denom_low) | (((UInt64)denom_high) << 32));
		if (denom_low == 0 && denom_high == 0) // the DIV0 flag in DIVCNT is set only if the full 64bit DIV_DENOM value is zero, even in 32bit mode
		{
			Regs_Arm9.Sect_system9.DIVCNT_Division_by_zero.write(1);

			if (numer64 < 0)
			{
				Regs_Arm9.Sect_system9.DIV_RESULT_Low.write(1);
			}
			else
			{
				Regs_Arm9.Sect_system9.DIV_RESULT_Low.write(-1);
			}
			Regs_Arm9.Sect_system9.DIV_RESULT_Low.write(0); // +-1?
			Regs_Arm9.Sect_system9.DIV_RESULT_High.write(0);
			Regs_Arm9.Sect_system9.DIVREM_RESULT_Low.write(numer_low);
			Regs_Arm9.Sect_system9.DIVREM_RESULT_High.write(numer_high);
			return;
		}
		else
		{
			Regs_Arm9.Sect_system9.DIVCNT_Division_by_zero.write(0);
		}

		uint mode = Regs_Arm9.Sect_system9.DIVCNT_Division_Mode.read();
		if (mode == 3) mode = 1;

		Int64 result = 0;
		Int64 remain = 0;
		switch (mode) // Numer / Denom = Result, Remainder
		{
		case 0: // 32bit / 32bit = 32bit , 32bit
			if (denom_low != 0)
			{
				result = (int)numer_low / (int)denom_low;
				remain = (int)numer_low % (int)denom_low;
			}
			else
			{
				result = -1;
				if (numer64 < 0)
				{
					result = 1;
				}
			}
			break;
		case 1: // 64bit / 32bit = 64bit , 32bit
			if (denom_low != 0)
			{
				result = numer64 / (int)denom_low;
				remain = numer64 % (int)denom_low;
			}
			else
			{
				result = -1;
				if (numer64 < 0)
				{
					result = 1;
				}
			}
			break;
		case 2: // 64bit / 64bit = 64bit , 64bit
			result = numer64 / denom64;
			remain = numer64 % denom64;
			break;
		}

		Regs_Arm9.Sect_system9.DIV_RESULT_Low.write((uint)result);
		Regs_Arm9.Sect_system9.DIV_RESULT_High.write(result >> 32);
		Regs_Arm9.Sect_system9.DIVREM_RESULT_Low.write((uint)remain);
		Regs_Arm9.Sect_system9.DIVREM_RESULT_High.write(remain >> 32);
	}
}