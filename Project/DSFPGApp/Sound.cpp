#include "Sound.h"
#include "regs_arm7.h"
#include "gameboy.h"

SOUND Sound;

void SOUND::reset()
{
	sound_on = true;
	lasttime = 0;
}

void SOUND::set_soundreg(UInt32 adr)
{
	if (adr < 0x500)
	{
		soundGenerator.soundchannels[(adr & 0xFF) / 0x10].set_soundreg((adr % 0x10) / 4);
	}
}

void SOUND::work()
{
	if (sound_on)
	{
		Int32 timediff = gameboy.totalticks - lasttime;
		lasttime = gameboy.totalticks;

		soundGenerator.update_timebased(timediff);
	}
}