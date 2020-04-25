#include "SoundGenerator.h"
#include "regs_arm7.h"

SoundGenerator::SoundGenerator()
{
	RegSect_sound7 sr = Regs_Arm7.Sect_sound7;
	soundchannels[0].reset(0, sr.SOUND0CNT_Volume_Mul, sr.SOUND0CNT_Volume_Div, sr.SOUND0CNT_Hold, sr.SOUND0CNT_Panning, sr.SOUND0CNT_Wave_Duty, sr.SOUND0CNT_Repeat_Mode, sr.SOUND0CNT_Format, sr.SOUND0CNT_Start_Status, sr.SOUND0SAD, sr.SOUND0TMR, sr.SOUND0PNT, sr.SOUND0LEN);
	soundchannels[1].reset(1, sr.SOUND1CNT_Volume_Mul, sr.SOUND1CNT_Volume_Div, sr.SOUND1CNT_Hold, sr.SOUND1CNT_Panning, sr.SOUND1CNT_Wave_Duty, sr.SOUND1CNT_Repeat_Mode, sr.SOUND1CNT_Format, sr.SOUND1CNT_Start_Status, sr.SOUND1SAD, sr.SOUND1TMR, sr.SOUND1PNT, sr.SOUND1LEN);
	soundchannels[2].reset(2, sr.SOUND2CNT_Volume_Mul, sr.SOUND2CNT_Volume_Div, sr.SOUND2CNT_Hold, sr.SOUND2CNT_Panning, sr.SOUND2CNT_Wave_Duty, sr.SOUND2CNT_Repeat_Mode, sr.SOUND2CNT_Format, sr.SOUND2CNT_Start_Status, sr.SOUND2SAD, sr.SOUND2TMR, sr.SOUND2PNT, sr.SOUND2LEN);
	soundchannels[3].reset(3, sr.SOUND3CNT_Volume_Mul, sr.SOUND3CNT_Volume_Div, sr.SOUND3CNT_Hold, sr.SOUND3CNT_Panning, sr.SOUND3CNT_Wave_Duty, sr.SOUND3CNT_Repeat_Mode, sr.SOUND3CNT_Format, sr.SOUND3CNT_Start_Status, sr.SOUND3SAD, sr.SOUND3TMR, sr.SOUND3PNT, sr.SOUND3LEN);
	soundchannels[4].reset(4, sr.SOUND4CNT_Volume_Mul, sr.SOUND4CNT_Volume_Div, sr.SOUND4CNT_Hold, sr.SOUND4CNT_Panning, sr.SOUND4CNT_Wave_Duty, sr.SOUND4CNT_Repeat_Mode, sr.SOUND4CNT_Format, sr.SOUND4CNT_Start_Status, sr.SOUND4SAD, sr.SOUND4TMR, sr.SOUND4PNT, sr.SOUND4LEN);
	soundchannels[5].reset(5, sr.SOUND5CNT_Volume_Mul, sr.SOUND5CNT_Volume_Div, sr.SOUND5CNT_Hold, sr.SOUND5CNT_Panning, sr.SOUND5CNT_Wave_Duty, sr.SOUND5CNT_Repeat_Mode, sr.SOUND5CNT_Format, sr.SOUND5CNT_Start_Status, sr.SOUND5SAD, sr.SOUND5TMR, sr.SOUND5PNT, sr.SOUND5LEN);
	soundchannels[6].reset(6, sr.SOUND6CNT_Volume_Mul, sr.SOUND6CNT_Volume_Div, sr.SOUND6CNT_Hold, sr.SOUND6CNT_Panning, sr.SOUND6CNT_Wave_Duty, sr.SOUND6CNT_Repeat_Mode, sr.SOUND6CNT_Format, sr.SOUND6CNT_Start_Status, sr.SOUND6SAD, sr.SOUND6TMR, sr.SOUND6PNT, sr.SOUND6LEN);
	soundchannels[7].reset(7, sr.SOUND7CNT_Volume_Mul, sr.SOUND7CNT_Volume_Div, sr.SOUND7CNT_Hold, sr.SOUND7CNT_Panning, sr.SOUND7CNT_Wave_Duty, sr.SOUND7CNT_Repeat_Mode, sr.SOUND7CNT_Format, sr.SOUND7CNT_Start_Status, sr.SOUND7SAD, sr.SOUND7TMR, sr.SOUND7PNT, sr.SOUND7LEN);
	soundchannels[8].reset(8, sr.SOUND8CNT_Volume_Mul, sr.SOUND8CNT_Volume_Div, sr.SOUND8CNT_Hold, sr.SOUND8CNT_Panning, sr.SOUND8CNT_Wave_Duty, sr.SOUND8CNT_Repeat_Mode, sr.SOUND8CNT_Format, sr.SOUND8CNT_Start_Status, sr.SOUND8SAD, sr.SOUND8TMR, sr.SOUND8PNT, sr.SOUND8LEN);
	soundchannels[9].reset(9, sr.SOUND9CNT_Volume_Mul, sr.SOUND9CNT_Volume_Div, sr.SOUND9CNT_Hold, sr.SOUND9CNT_Panning, sr.SOUND9CNT_Wave_Duty, sr.SOUND9CNT_Repeat_Mode, sr.SOUND9CNT_Format, sr.SOUND9CNT_Start_Status, sr.SOUND9SAD, sr.SOUND9TMR, sr.SOUND9PNT, sr.SOUND9LEN);
	soundchannels[10].reset(10, sr.SOUND10CNT_Volume_Mul, sr.SOUND10CNT_Volume_Div, sr.SOUND10CNT_Hold, sr.SOUND10CNT_Panning, sr.SOUND10CNT_Wave_Duty, sr.SOUND10CNT_Repeat_Mode, sr.SOUND10CNT_Format, sr.SOUND10CNT_Start_Status, sr.SOUND10SAD, sr.SOUND10TMR, sr.SOUND10PNT, sr.SOUND10LEN);
	soundchannels[11].reset(11, sr.SOUND11CNT_Volume_Mul, sr.SOUND11CNT_Volume_Div, sr.SOUND11CNT_Hold, sr.SOUND11CNT_Panning, sr.SOUND11CNT_Wave_Duty, sr.SOUND11CNT_Repeat_Mode, sr.SOUND11CNT_Format, sr.SOUND11CNT_Start_Status, sr.SOUND11SAD, sr.SOUND11TMR, sr.SOUND11PNT, sr.SOUND11LEN);
	soundchannels[12].reset(12, sr.SOUND12CNT_Volume_Mul, sr.SOUND12CNT_Volume_Div, sr.SOUND12CNT_Hold, sr.SOUND12CNT_Panning, sr.SOUND12CNT_Wave_Duty, sr.SOUND12CNT_Repeat_Mode, sr.SOUND12CNT_Format, sr.SOUND12CNT_Start_Status, sr.SOUND12SAD, sr.SOUND12TMR, sr.SOUND12PNT, sr.SOUND12LEN);
	soundchannels[13].reset(13, sr.SOUND13CNT_Volume_Mul, sr.SOUND13CNT_Volume_Div, sr.SOUND13CNT_Hold, sr.SOUND13CNT_Panning, sr.SOUND13CNT_Wave_Duty, sr.SOUND13CNT_Repeat_Mode, sr.SOUND13CNT_Format, sr.SOUND13CNT_Start_Status, sr.SOUND13SAD, sr.SOUND13TMR, sr.SOUND13PNT, sr.SOUND13LEN);
	soundchannels[14].reset(14, sr.SOUND14CNT_Volume_Mul, sr.SOUND14CNT_Volume_Div, sr.SOUND14CNT_Hold, sr.SOUND14CNT_Panning, sr.SOUND14CNT_Wave_Duty, sr.SOUND14CNT_Repeat_Mode, sr.SOUND14CNT_Format, sr.SOUND14CNT_Start_Status, sr.SOUND14SAD, sr.SOUND14TMR, sr.SOUND14PNT, sr.SOUND14LEN);
	soundchannels[15].reset(15, sr.SOUND15CNT_Volume_Mul, sr.SOUND15CNT_Volume_Div, sr.SOUND15CNT_Hold, sr.SOUND15CNT_Panning, sr.SOUND15CNT_Wave_Duty, sr.SOUND15CNT_Repeat_Mode, sr.SOUND15CNT_Format, sr.SOUND15CNT_Start_Status, sr.SOUND15SAD, sr.SOUND15TMR, sr.SOUND15PNT, sr.SOUND15LEN);

	samplingCounter = 0;

	nextSamples_lock = SDL_CreateMutex();

    SDL_AudioSpec wanted;
	wanted.callback = fill_audio;
	wanted.userdata = this;
	wanted.freq = 44100;
	wanted.format = AUDIO_S16;
	wanted.channels = 1;
	wanted.samples = 4096;

	SDL_OpenAudio(&wanted, NULL);
	SDL_PauseAudio(0);
}

void SoundGenerator::update_timebased(Int32 new_cycles)
{
	for (int i = 0; i < 16; i++)
	{
		if (soundchannels[i].on)
		{
			soundchannels[i].update_timebased(new_cycles);
		}
	}

	samplingCounter += new_cycles;
	if (samplingCounter >= SAMPLINGRRATE)
	{
		if (SDL_LockMutex(nextSamples_lock) == 0)
		{
			while (samplingCounter >= SAMPLINGRRATE)
			{
				samplingCounter -= SAMPLINGRRATE;
				if (nextSamples.size() < 15000)
				{
					int value = 0;
					for (int i = 0; i < 16; i++)
					{
						if (soundchannels[i].on)
						{
							value += soundchannels[i].currentSample / 16;
						}
					}
					nextSamples.push(value);
				}
			}
			SDL_UnlockMutex(nextSamples_lock);
		}
	}
}

void fill_audio(void* udata, Uint8* stream, int len)
{
	SoundGenerator* soundGenerator = (SoundGenerator*)udata;

	if (SDL_LockMutex(soundGenerator->nextSamples_lock) == 0)
	{
		for (int n = 0; n < len; n += 2)
		{
			if (!soundGenerator->nextSamples.empty())
			{
				int valueInt = soundGenerator->nextSamples.front();
				soundGenerator->nextSamples.pop();
				stream[n] = (byte)(valueInt & 0xFF);
				stream[n + 1] = (byte)(valueInt >> 8);
			}
			else
			{
				stream[n] = 0;
				stream[n + 1] = 0;
			}
		}
		SDL_UnlockMutex(soundGenerator->nextSamples_lock);
	}
}