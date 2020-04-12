#include "SoundDMA.h"
#include "CPU.h"
#include "Sound.h"
#include "DMA.h"

SOUNDDMA SoundDMA;

SingleSoundDMA::SingleSoundDMA()
{
}

SingleSoundDMA::SingleSoundDMA(DSReg Enable_RIGHT, DSReg Enable_LEFT, DSReg Timer_Select, DSReg Reset_FIFO)
{
	this->Enable_RIGHT = Enable_RIGHT;
	this->Enable_LEFT = Enable_LEFT;
	this->Timer_Select = Timer_Select;
	this->Reset_FIFO = Reset_FIFO;

	timerindex = 0;
	any_on = false;

	outfifo.push(0);
	tickcount = 0;
}

void SingleSoundDMA::work()
{
	tickcount += CPU9.newticks;
	while (tickcount >= Sound.SAMPLERATE)
	{
		tickcount -= Sound.SAMPLERATE;
		if (fifo.size() > 0 && outfifo.size() < 15000)
		{
			outfifo.push(fifo.front());
		}
	}
}

void SOUNDDMA::reset()
{
	//soundDMAs[1] = SingleSoundDMA(Regs_Arm7.Sect_sound7.SOUNDCNT_H_DMA_Sound_B_Enable_RIGHT, Regs_Arm7.Sect_sound7.SOUNDCNT_H_DMA_Sound_B_Enable_LEFT,
	//	Regs_Arm7.Sect_sound7.SOUNDCNT_H_DMA_Sound_B_Timer_Select, Regs_Arm7.Sect_sound7.SOUNDCNT_H_DMA_Sound_B_Reset_FIFO);
	//
	//soundDMAs[0] = SingleSoundDMA(Regs_Arm7.Sect_sound7.SOUNDCNT_H_DMA_Sound_A_Enable_RIGHT, Regs_Arm7.Sect_sound7.SOUNDCNT_H_DMA_Sound_A_Enable_LEFT,
	//	Regs_Arm7.Sect_sound7.SOUNDCNT_H_DMA_Sound_A_Timer_Select, Regs_Arm7.Sect_sound7.SOUNDCNT_H_DMA_Sound_A_Reset_FIFO);
}

void SOUNDDMA::timer_overflow(uint timerindex)
{
	CPU9.newticks = 0;
	for (uint i = 0; i < 2; i++)
	{
		if (soundDMAs[i].any_on && soundDMAs[i].timerindex == timerindex)
		{
			if (soundDMAs[i].fifo.size() > 0)
			{
				soundDMAs[i].fifo.pop();
			}

			if (soundDMAs[i].fifo.size() == 16 || soundDMAs[i].fifo.size() == 0)
			{
				DMA.request_audio(i);
				DMA.work();
				DMA.delayed = true;
			}
		}
	}
}

void SOUNDDMA::fill_fifo(int index, UInt32 value, bool dwaccess)
{
	soundDMAs[index].fifo.push((byte)value);
	soundDMAs[index].fifo.push((byte)(value >> 8));
	if (dwaccess)
	{
		soundDMAs[index].fifo.push((byte)(value >> 16));
		soundDMAs[index].fifo.push((byte)(value >> 24));
	}
}