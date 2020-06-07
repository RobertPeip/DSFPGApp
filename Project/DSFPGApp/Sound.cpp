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
	else if (adr >= Regs_Arm7.Sect_sound7.SOUNDCNT.address && adr < Regs_Arm7.Sect_sound7.SOUNDCNT.address + 4)
	{
		soundGenerator.set_soundcontrol();
	}
	else if (adr >= Regs_Arm7.Sect_sound7.SOUNDCAP.address && adr < Regs_Arm7.Sect_sound7.SOUNDCAP.address + 4)
	{
		soundGenerator.set_soundcapture();
	}
}

void SOUND::work()
{
	Int32 timediff = gameboy.totalticks - lasttime;
	lasttime = gameboy.totalticks;
	if (sound_on && soundGenerator.Master_Enable)
	{
		soundGenerator.update_timebased(timediff);
	}
}