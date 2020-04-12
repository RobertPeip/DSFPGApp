#include "Sound.h"
#include "regs_arm7.h"
#include "SoundDMA.h"

SOUND Sound;

void SOUND::reset()
{
	sound_on = false;
}

void SOUND::set_soundreg(UInt32 adr)
{
	
}

void SOUND::work()
{
	if (sound_on)
	{
		soundGenerator.work();
	}
}