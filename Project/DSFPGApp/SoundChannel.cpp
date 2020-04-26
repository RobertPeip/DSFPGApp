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
		if (!on && SOUNDCNT_Start_Status.on())
		{
			on = true;
			totallength = GetLength();
			freqCounter = 0;
			samplepos = -3;
			
			if (Format == 2)
			{ 
				UInt32 data = read_dword_7(ACCESSTYPE::DMA, source);
				samplepos = 8;
				currentSample = (Int16)(data & 0xFFFF);
				tableindex = ((data >> 16) & 0x7F);
				if (tableindex > 88) tableindex = 88;
				loop_index = 100;
			}
			else if (Format == 3)
			{
				lfsr = 0x7FFF;
				psgcnt = 0;
				samplepos = -1;
			}
		}
		else if (on && !SOUNDCNT_Start_Status.on())
		{
			on = false;
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
			case 2: 
				if (loop_index == 100) // loop was not reached for some reason
				{
					UInt32 data = read_dword_7(ACCESSTYPE::DMA, source);
					samplepos = 8;
					currentSample = (Int16)(data & 0xFFFF);
					tableindex = ((data >> 16) & 0x7F);
					if (tableindex > 88) tableindex = 88;
				}
				else
				{
					samplepos -= (totallength - loopstart * 8);
					currentSample = loop_sample;
					tableindex = loop_index;
				}
				break;
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
				byte data = read_byte_7(ACCESSTYPE::DMA, source + (samplepos / 2));

				if ((samplepos & 1) == 1) data >>= 4;

				Int16 diff = ((data & 7) * 2 + 1) * ADPCMTABLE[tableindex] / 8;
				if ((data & 8) == 0) currentSample = currentSample + diff; if (currentSample > 0x7FFF) currentSample = 0x7FFF;
				if ((data & 8) == 8) currentSample = currentSample - diff; if (currentSample < -0x7FFF) currentSample = -0x7FFF;
				tableindex = tableindex + INDEXTBL[data & 7];
				if (tableindex < 0) tableindex = 0;
				if (tableindex > 88) tableindex = 88;

				if (samplepos == (loopstart * 8))
				{
					loop_sample = currentSample;
					loop_index = tableindex;
				}
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
