#include "SoundChannel.h"
#include "regs_arm7.h"
#include "Memory.h"

void SoundChannel::reset(
	byte index,
	DSReg SOUNDCNT_Volume_Mul,
	DSReg SOUNDCNT_Volume_Div,
	DSReg SOUNDCNT_Hold,
	DSReg SOUNDCNT_Panning,
	DSReg SOUNDCNT_Wave_Duty,
	DSReg SOUNDCNT_Repeat_Mode,
	DSReg SOUNDCNT_Format,
	DSReg SOUNDCNT_Start_Status,
	DSReg SOUNDSAD,
	DSReg SOUNDTMR,
	DSReg SOUNDPNT,
	DSReg SOUNDLEN
)
{
	this->index = index;
	this->SOUNDCNT_Volume_Mul = SOUNDCNT_Volume_Mul;
	this->SOUNDCNT_Volume_Div = SOUNDCNT_Volume_Div;
	this->SOUNDCNT_Hold = SOUNDCNT_Hold;
	this->SOUNDCNT_Panning = SOUNDCNT_Panning;
	this->SOUNDCNT_Wave_Duty = SOUNDCNT_Wave_Duty;
	this->SOUNDCNT_Repeat_Mode = SOUNDCNT_Repeat_Mode;
	this->SOUNDCNT_Format = SOUNDCNT_Format;
	this->SOUNDCNT_Start_Status = SOUNDCNT_Start_Status;
	this->SOUNDSAD = SOUNDSAD;
	this->SOUNDTMR = SOUNDTMR;
	this->SOUNDPNT = SOUNDPNT;
	this->SOUNDLEN = SOUNDLEN;

	on = false;
	currentSample = 0;
	freqCounter = 0;
}

void SoundChannel::set_soundreg(int regindex)
{
	switch (regindex)
	{
	case 0:
		Volume_Mul = SOUNDCNT_Volume_Mul.read();
		Volume_Div = SOUNDCNT_Volume_Div.read();
		Hold = SOUNDCNT_Hold.on();
		Panning = SOUNDCNT_Panning.read();
		Wave_Duty = SOUNDCNT_Wave_Duty.read();
		Repeat_Mode = SOUNDCNT_Repeat_Mode.read();
		Format = SOUNDCNT_Format.read();
		on = SOUNDCNT_Start_Status.read();
		if (on)
		{
			totallength = GetLength();
			freqCounter = 0;
			lfsr = 0x7FFF;
			psgcnt = 0;
			samplepos = -3;
			if (Format == 3)
			{
				samplepos = -1;
			}
		}
		break;

	case 1:
		source = SOUNDSAD.read();
		break;

	case 2:
		timer = SOUNDTMR.read() * 4;
		loopstart = SOUNDPNT.read();
		if (timer > 0)
		{
			int a = 5;
		}
		break;

	case 3:
		length = SOUNDLEN.read();
		break;
	}
}

uint SoundChannel::GetLength()
{
	switch (Format)
	{
	case 0: return (length + loopstart) * 4;
	case 1: return (length + loopstart) * 2;
	case 2: return (length + loopstart) * 8;
	}

	return 0;
}

void SoundChannel::check_loop_end()
{
	if (Format < 3 && samplepos >= totallength)
	{
		if (Repeat_Mode == 1)
		{
			switch (Format)
			{
			case 0: samplepos -= (totallength - loopstart * 4); break;
			case 1: samplepos -= (totallength - loopstart * 2); break;
			case 2: samplepos -= (totallength - loopstart * 8); break;
			}
		}
		else
		{
			on = false;
			SOUNDCNT_Start_Status.write(0);
		}
	}
}

void SoundChannel::update_timebased(Int32 new_cycles)
{
	freqCounter += new_cycles;
	while (freqCounter > (0x40000 - timer))
	{
		freqCounter -= (0x40000 - timer);

		switch (Format)
		{
		case 0:
			if (samplepos >= 0)
			{
				currentSample = (Int32)((SByte)read_byte_7(ACCESSTYPE::DMA, source + samplepos) * 0x100);
			}
			samplepos++;
			break;

		case 1:
			if (samplepos >= 0)
			{
				currentSample = (Int32)((Int16)read_word_7(ACCESSTYPE::DMA, source + samplepos * 2));
			}
			samplepos++;
			break;

		case 2:
			if (samplepos >= 0)
			{
				//currentSample = read_byte_7(ACCESSTYPE::DMA, ptr);
			}
			samplepos++;
			break;

		case 3:
			if (index >= 14) // noise
			{
				if (lfsr & 1)
				{
					lfsr = lfsr >> 1;
					lfsr = lfsr ^ 0x6000;
					currentSample = -0x8000;
				}
				else
				{
					lfsr = lfsr >> 1;
					currentSample = 0x7FFF;
				}
			}
			else if (index >= 8 && index <= 13) // psg
			{
				if (psgcnt > Wave_Duty)
				{
					currentSample = -0x8000;
				}
				else
				{
					currentSample = 0x7FFF;
				}
				psgcnt = (psgcnt + 1) % 8;
			}
			else
			{
				currentSample = 0;
			}
			break;
		}
		check_loop_end();
	}
}
