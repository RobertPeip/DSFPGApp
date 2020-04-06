#include "Timer.h"
#include "IRP.h"
#include "CPU.h"
#include "gameboy.h"
#include "SoundDMA.h"

TIMER Timer;

SingleTimer::SingleTimer()
{
}

SingleTimer::SingleTimer(UInt16 irpmask, DSReg CNT_L, DSReg Prescaler, DSReg Count_up, DSReg Timer_IRQ_Enable, DSReg Timer_Start_Stop)
{
	this->irpmask = irpmask;

	this->CNT_L = CNT_L;
	this->Prescaler = Prescaler;
	this->Count_up = Count_up;
	this->Timer_IRQ_Enable = Timer_IRQ_Enable;
	this->Timer_Start_Stop = Timer_Start_Stop;

	on = false;
	startnow = false;
	stopnow = false;
	irp_on = false;
	reload = 0;
	value = -1;
	prescale = 0x10000;
	retval = 0;
	countup = false;
}

void TIMER::reset()
{
	timers[3] = SingleTimer(IRP.IRPMASK_Timer_3, Regs_Arm9.Sect_timer9.TM3CNT_L, Regs_Arm9.Sect_timer9.TM3CNT_H_Prescaler, Regs_Arm9.Sect_timer9.TM3CNT_H_Count_up, Regs_Arm9.Sect_timer9.TM3CNT_H_Timer_IRQ_Enable, Regs_Arm9.Sect_timer9.TM3CNT_H_Timer_Start_Stop);
	timers[2] = SingleTimer(IRP.IRPMASK_Timer_2, Regs_Arm9.Sect_timer9.TM2CNT_L, Regs_Arm9.Sect_timer9.TM2CNT_H_Prescaler, Regs_Arm9.Sect_timer9.TM2CNT_H_Count_up, Regs_Arm9.Sect_timer9.TM2CNT_H_Timer_IRQ_Enable, Regs_Arm9.Sect_timer9.TM2CNT_H_Timer_Start_Stop);
	timers[1] = SingleTimer(IRP.IRPMASK_Timer_1, Regs_Arm9.Sect_timer9.TM1CNT_L, Regs_Arm9.Sect_timer9.TM1CNT_H_Prescaler, Regs_Arm9.Sect_timer9.TM1CNT_H_Count_up, Regs_Arm9.Sect_timer9.TM1CNT_H_Timer_IRQ_Enable, Regs_Arm9.Sect_timer9.TM1CNT_H_Timer_Start_Stop);
	timers[0] = SingleTimer(IRP.IRPMASK_Timer_0, Regs_Arm9.Sect_timer9.TM0CNT_L, Regs_Arm9.Sect_timer9.TM0CNT_H_Prescaler, Regs_Arm9.Sect_timer9.TM0CNT_H_Count_up, Regs_Arm9.Sect_timer9.TM0CNT_H_Timer_IRQ_Enable, Regs_Arm9.Sect_timer9.TM0CNT_H_Timer_Start_Stop);

	timers[7] = SingleTimer(IRP.IRPMASK_Timer_3, Regs_Arm7.Sect_timer7.TM3CNT_L, Regs_Arm7.Sect_timer7.TM3CNT_H_Prescaler, Regs_Arm7.Sect_timer7.TM3CNT_H_Count_up, Regs_Arm7.Sect_timer7.TM3CNT_H_Timer_IRQ_Enable, Regs_Arm7.Sect_timer7.TM3CNT_H_Timer_Start_Stop);
	timers[6] = SingleTimer(IRP.IRPMASK_Timer_2, Regs_Arm7.Sect_timer7.TM2CNT_L, Regs_Arm7.Sect_timer7.TM2CNT_H_Prescaler, Regs_Arm7.Sect_timer7.TM2CNT_H_Count_up, Regs_Arm7.Sect_timer7.TM2CNT_H_Timer_IRQ_Enable, Regs_Arm7.Sect_timer7.TM2CNT_H_Timer_Start_Stop);
	timers[5] = SingleTimer(IRP.IRPMASK_Timer_1, Regs_Arm7.Sect_timer7.TM1CNT_L, Regs_Arm7.Sect_timer7.TM1CNT_H_Prescaler, Regs_Arm7.Sect_timer7.TM1CNT_H_Count_up, Regs_Arm7.Sect_timer7.TM1CNT_H_Timer_IRQ_Enable, Regs_Arm7.Sect_timer7.TM1CNT_H_Timer_Start_Stop);
	timers[4] = SingleTimer(IRP.IRPMASK_Timer_0, Regs_Arm7.Sect_timer7.TM0CNT_L, Regs_Arm7.Sect_timer7.TM0CNT_H_Prescaler, Regs_Arm7.Sect_timer7.TM0CNT_H_Count_up, Regs_Arm7.Sect_timer7.TM0CNT_H_Timer_IRQ_Enable, Regs_Arm7.Sect_timer7.TM0CNT_H_Timer_Start_Stop);
}

void TIMER::set_reload(int index)
{
	timers[index].reload = (int)timers[index].CNT_L.read();
}

void TIMER::set_settings(int index)
{
	if (timers[index].Timer_Start_Stop.on() && !timers[index].on && !gameboy.loading_state)
	{
		timers[index].startnow = true;
	}
	else if (timers[index].on && !timers[index].Timer_Start_Stop.on() && !gameboy.loading_state)
	{
		timers[index].stopnow = true;
	}
	timers[index].on = timers[index].Timer_Start_Stop.on();
	if (timers[index].on)
	{
		timers[index].irp_on = timers[index].Timer_IRQ_Enable.on();
		timers[index].countup = timers[index].Count_up.on();
		if (index % 4 == 0) timers[index].countup = false;
		switch (timers[index].Prescaler.read())
		{
		case 0: timers[index].prescale = 2; break;
		case 1: timers[index].prescale = 128; break;
		case 2: timers[index].prescale = 512; break;
		case 3: timers[index].prescale = 2048; break;
		}

		if (!timers[index].countup)
		{
			timers[index].next_event_ticks = gameboy.totalticks + (65536 - timers[index].reload) * timers[index].prescale;
		}
	}
}

void TIMER::work()
{
	for (int i = 0; i < 8; i++)
	{
		if (timers[i].startnow)
		{
			timers[i].startnow = false;
			timers[i].value = timers[i].reload;
			timers[i].retval = (UInt16)timers[i].value;
		}
		//else if (timers[i].on || timers[i].stopnow)
		if (timers[i].on || timers[i].stopnow)
		{
			timers[i].stopnow = false;

			if (!timers[i].countup && gameboy.totalticks >= timers[i].next_event_ticks)
			{
				timers[i].next_event_ticks = timers[i].next_event_ticks + (65536 - timers[i].reload) * timers[i].prescale;
				Timer.overflow(i);
			}
		}
	}
}

void TIMER::overflow(int index)
{
	timers[index].value = timers[index].reload;

	if ((index % 4) < 3 && timers[index + 1].countup)
	{
		timers[index + 1].value++;
		if (timers[index + 1].value >= 0x10000)
		{
			Timer.overflow(index + 1);
		}
	}

	if (timers[index].irp_on)
	{
		IRP.set_irp_bit(timers[index].irpmask);
	}
}

void TIMER::updatereg(int index)
{
	if (timers[index].on)
	{
		uint adr = Regs_Arm7.Sect_timer7.TM0CNT_L.address + (index % 4) * 4;

		UInt16 value;

		if (timers[index].countup)
		{
			Timer.timers[index].value;
		}
		else
		{
			int diff = Timer.timers[index].next_event_ticks - gameboy.totalticks;
			diff = diff / timers[index].prescale;
			if (diff == 65536)
			{
				value = 0;
			}
			else
			{
				value = 65535 - diff;
			}
		}

		Regs_Arm7.data[adr] = (byte)(value & 0xFF);
		Regs_Arm7.data[adr + 1] = (byte)((value >> 8) & 0xFF);
	}
}