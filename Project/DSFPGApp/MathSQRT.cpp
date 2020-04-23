#include "MathSQRT.h"
#include "regs_arm9.h"
#include "gameboy.h"

MATHSQRT MathSQRT;

void MATHSQRT::reset()
{
	calculating = false;
}

void MATHSQRT::write()
{
	calculating = true;
	Regs_Arm9.Sect_system9.SQRTCN_Busy.write(1);
	next_event_time = gameboy.totalticks + 13 * 2;
	gameboy.reschedule = true;
}

void MATHSQRT::finish()
{
	if (gameboy.totalticks >= next_event_time)
	{
		calculating = false;
		Regs_Arm9.Sect_system9.SQRTCN_Busy.write(0);
		uint param_low = Regs_Arm9.Sect_system9.SQRT_PARAM_Low.read();

		if (Regs_Arm9.Sect_system9.SQRTCN_Mode.on())
		{
			uint param_high = Regs_Arm9.Sect_system9.SQRT_PARAM_High.read();
			UInt64 param64 = (Int64)(((UInt64)param_low) | (((UInt64)param_high) << 32));
			param64 = sqrt(param64);
			Regs_Arm9.Sect_system9.SQRT_RESULT.write(param64);
		}
		else
		{
			param_low = sqrt(param_low);
			Regs_Arm9.Sect_system9.SQRT_RESULT.write(param_low);
		}
	}
}