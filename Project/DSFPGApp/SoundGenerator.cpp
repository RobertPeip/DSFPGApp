#include "SoundGenerator.h"
#include "regs_arm7.h"
#include "Memory.h"

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

	Master_Enable = false;
	capturehack = false;

	nextSamples_lock = SDL_CreateMutex();

    SDL_AudioSpec wanted;
	wanted.callback = fill_audio;
	wanted.userdata = this;
	wanted.freq = 44100;
	wanted.format = AUDIO_S16;
	wanted.channels = 2;
	wanted.samples = 4096;

	SDL_OpenAudio(&wanted, NULL);
	SDL_PauseAudio(0);
}

void SoundGenerator::set_soundcontrol()
{
	Master_Volume = Regs_Arm7.Sect_sound7.SOUNDCNT_Master_Volume.read();
	Left_Output_from = Regs_Arm7.Sect_sound7.SOUNDCNT_Left_Output_from.read();
	Right_Output_from = Regs_Arm7.Sect_sound7.SOUNDCNT_Right_Output_from.read();
	Output_Ch1_to_Mixer = Regs_Arm7.Sect_sound7.SOUNDCNT_Output_Ch1_to_Mixer.on();
	Output_Ch3_to_Mixer = Regs_Arm7.Sect_sound7.SOUNDCNT_Output_Ch3_to_Mixer.on();
	Master_Enable = Regs_Arm7.Sect_sound7.SOUNDCNT_Master_Enable.on();
}

void SoundGenerator::set_soundcapture()
{
	capturehack = false;
	if (Regs_Arm7.Sect_sound7.SOUNDCAP.read() == 0x8080)
	{
		capturehack = true;
	}

	if (Regs_Arm7.Sect_sound7.SOUNDCAP0_Capture_Start_Status.on())
	{
		while (!capture[0].capturefifo.empty()) capture[0].capturefifo.pop();
		capture[0].on = true;
		capture[0].add = Regs_Arm7.Sect_sound7.SOUNDCAP1_Control.on();
		capture[0].source = Regs_Arm7.Sect_sound7.SOUNDCAP1_Capture_Source.on();
		capture[0].format8 = Regs_Arm7.Sect_sound7.SOUNDCAP1_Capture_Format.on();
		capture[0].oneshot = Regs_Arm7.Sect_sound7.SOUNDCAP1_Capture_Repeat.on();
		capture[0].start_addr = Regs_Arm7.Sect_sound7.SNDCAP0DAD.read();
		capture[0].capture_addr = Regs_Arm7.Sect_sound7.SNDCAP0DAD.read();
		capture[0].capture_cnt = Regs_Arm7.Sect_sound7.SNDCAP0LEN.read() * 4;
		capture[0].capture_len = Regs_Arm7.Sect_sound7.SNDCAP0LEN.read() * 4;
	}
	else
	{
		capture[0].on = false;
	}

	if (Regs_Arm7.Sect_sound7.SOUNDCAP1_Capture_Start_Status.on())
	{
		while (!capture[1].capturefifo.empty()) capture[1].capturefifo.pop();
		capture[1].on = true;
		capture[1].add = Regs_Arm7.Sect_sound7.SOUNDCAP0_Control.on();
		capture[1].source = Regs_Arm7.Sect_sound7.SOUNDCAP0_Capture_Source.on();
		capture[1].format8 = Regs_Arm7.Sect_sound7.SOUNDCAP0_Capture_Format.on();
		capture[1].oneshot = Regs_Arm7.Sect_sound7.SOUNDCAP0_Capture_Repeat.on();
		capture[1].start_addr = Regs_Arm7.Sect_sound7.SNDCAP1DAD.read();
		capture[1].capture_addr = Regs_Arm7.Sect_sound7.SNDCAP1DAD.read();
		capture[1].capture_cnt = Regs_Arm7.Sect_sound7.SNDCAP1LEN.read() * 4;
		capture[1].capture_len = Regs_Arm7.Sect_sound7.SNDCAP1LEN.read() * 4;
	}
	else
	{
		capture[1].on = false;
	}
}

const int soundlist_Length = 8192;
int soundlist[8192][20];
int soundlist_ptr = 0;
bool soundlist_first = true;

void SoundGenerator::update_timebased(Int32 new_cycles)
{
	samplingCounter += new_cycles;
	if (samplingCounter >= SAMPLINGRRATE)
	{
		if (SDL_LockMutex(nextSamples_lock) == 0)
		{
			while (samplingCounter >= SAMPLINGRRATE)
			{
				samplingCounter -= SAMPLINGRRATE;
				//if (soundlist_ptr == 5771)
				//{
				//	int a = 5;
				//}
				for (int i = 0; i < 16; i++)
				{
					if (soundchannels[i].on)
					{
						soundchannels[i].update_timebased(SAMPLINGRRATE);
					}
				}
				if (nextSamples_left.size() < 15000)
				{
					Int64 value_left = 0;
					Int64 value_right = 0;
					Int64 value_left_1 = 0;
					Int64 value_right_1 = 0;
					Int64 value_left_3 = 0;
					Int64 value_right_3 = 0;
					if (Master_Enable)
					{
						Int16 allchannels[16];
						for (int i = 0; i < 16; i++)
						{
							if (soundchannels[i].on)
							{
								Int64 next_sample = (Int64)soundchannels[i].currentSample; // Incoming PCM16 Data 16.0

								switch (soundchannels[i].Volume_Div) // Volume Divider(div 1..16) 16.4
								{
								case 0: next_sample = next_sample * 16; break;
								case 1: next_sample = next_sample * 8; break;
								case 2: next_sample = next_sample * 4; break;
								case 3: next_sample = next_sample * 1; break;
								}

								allchannels[i] = (Int16)(next_sample / 16);
								
								//soundlist[soundlist_ptr][i] = next_sample / 16;

								next_sample *= soundchannels[i].Volume_Mul; // Volume Factor(mul N / 128) 16.11

								Int64 next_left  = next_sample * (127 - soundchannels[i].Panning) / 1024; //Panning(mul N / 128) 16.18
								Int64 next_right = next_sample * soundchannels[i].Panning / 1024;//  Rounding Down(strip 10bit) 16.8
								
								if (i == 1)
								{
									value_left_1 = next_left;
									value_right_1 = next_right;
								}
								else if (i == 3)
								{
									value_left_3 = next_left;
									value_right_3 = next_right;
								}

								if (i == 1 && Output_Ch1_to_Mixer) continue; //(0=Yes, 1=No)
								if (i == 3 && Output_Ch3_to_Mixer) continue; //(0=Yes, 1=No)
								value_left += next_left;
								value_right += next_right;
							}
							else
							{
								allchannels[i] = 0;
							}
						}

						int capout[2];
						if (capture[0].on)
						{
							if (capture[0].source == 0)
								capout[0] = (Int16)(value_left / 256); //cap0 = L-mix
							else if (capture[0].add)
								capout[0] = allchannels[0] + allchannels[1]; //cap0 = ch0+ch1
							else capout[0] = allchannels[0]; //cap0 = ch0
						}

						if (capture[1].on)
						{
							if (capture[1].source == 0)
								capout[1] = (Int16)(value_right / 256); //cap1 = R-mix
							else if (capture[1].add)
								capout[1] = allchannels[2] + allchannels[3]; //cap1 = ch2+ch3
							else capout[1] = allchannels[2]; //cap1 = ch2
						}

						if (!capturehack)
						{
							switch (Left_Output_from)
							{
							case 0: value_left = value_left; break;
							case 1: value_left = value_left_1; break;
							case 2: value_left = value_left_3; break;
							case 3: value_left = value_left_1 + value_left_3; break;
							}
							switch (Right_Output_from)
							{
							case 0: value_right = value_right; break;
							case 1: value_right = value_right_1; break;
							case 2: value_right = value_right_3; break;
							case 3: value_right = value_right_1 + value_right_3; break;
							}
						}

						value_left  = value_left  * Master_Volume / 0x20000; // Master Volume(mul N / 128 / 64) 14.21
						value_right = value_right * Master_Volume / 0x20000; // Strip fraction                  14.0

						for (int cap = 0; cap < 2; cap++)
						{
							if (capture[cap].on)
							{
								if (capture[cap].capturefifo.size() < 16)
								{
									capture[cap].capturefifo.push(capout[cap]);
								}
								else
								{
									Int16 oldvalue = capture[cap].capturefifo.front();
									capture[cap].capturefifo.pop();
									capture[cap].capturefifo.push(capout[cap]);

									if (capture[cap].format8)
									{
										SByte val8 = (SByte)(oldvalue / 256);
										write_byte_7(ACCESSTYPE::DMA, capture[cap].capture_addr, val8);
										capture[cap].capture_addr++;
										capture[cap].capture_cnt--;
									}
									else
									{
										write_word_7(ACCESSTYPE::DMA, capture[cap].capture_addr, oldvalue);
										capture[cap].capture_addr+=2;
										capture[cap].capture_cnt-=2;
									}

									if (capture[cap].capture_cnt <= 0)
									{
										if (capture[cap].oneshot)
										{
											capture[cap].on = false;
										}
										else
										{
											capture[cap].capture_addr = capture[cap].start_addr;
											capture[cap].capture_cnt = capture[cap].capture_len;
										}
									}
								}
							}
						}

						// 8 Add Bias(0..3FFh, def = 200h)   15.0 - 2000h + 0 + 1FF0h + 3FFh
						// 9 Clip(min / max 0h..3FFh)        10.0  0 + 3FFh
					}

					nextSamples_left.push((Int32)value_left);
					nextSamples_right.push((Int32)value_right);

					//soundlist[soundlist_ptr][16] = value_left;
					//soundlist[soundlist_ptr][17] = value_right;
					//soundlist[soundlist_ptr][18] = 0; //capout[0];
					//soundlist[soundlist_ptr][19] = 0; //capout[1];

					//soundlist_ptr++;
					//if (soundlist_ptr == soundlist_Length)
					//{
					//	soundlist_ptr = 0;
					//	if (soundlist_first)
					//	{
					//		FILE* file = fopen("R:\\debug_sound_DSFPGApp.csv", "w");
					//		fclose(file);
					//		soundlist_first = false;
					//	}
					//	FILE* file = fopen("R:\\debug_sound_DSFPGApp.csv", "a");
					//	for (int sample = 0; sample < soundlist_Length; sample++)
					//	{
					//		for (int ch = 0; ch < 20; ch++)
					//		{
					//			fprintf(file, "%d;", soundlist[sample][ch]);
					//		}
					//		fprintf(file, "\n");
					//	}
					//	fclose(file);
					//}
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
		for (int n = 0; n < len; n += 4)
		{
			if (!soundGenerator->nextSamples_left.empty())
			{
				int valueInt_left = soundGenerator->nextSamples_left.front();
				int valueInt_right = soundGenerator->nextSamples_right.front();

				soundGenerator->nextSamples_left.pop();
				soundGenerator->nextSamples_right.pop();
				stream[n] = (byte)(valueInt_left & 0xFF);
				stream[n + 1] = (byte)(valueInt_left >> 8);
				stream[n + 2] = (byte)(valueInt_right & 0xFF);
				stream[n + 3] = (byte)(valueInt_right >> 8);
			}
			else
			{
				stream[n] = 0;
				stream[n + 1] = 0;
				stream[n + 2] = 0;
				stream[n + 3] = 0;
			}
		}
		SDL_UnlockMutex(soundGenerator->nextSamples_lock);
	}
}