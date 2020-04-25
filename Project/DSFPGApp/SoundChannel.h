#include "types.h"
#include "DSReg.h"

#define SAMPLINGRRATE (67027964 / 44100)

class SoundChannel
{
public:
	DSReg SOUNDCNT_Volume_Mul;
	DSReg SOUNDCNT_Volume_Div;
	DSReg SOUNDCNT_Hold;
	DSReg SOUNDCNT_Panning;
	DSReg SOUNDCNT_Wave_Duty;
	DSReg SOUNDCNT_Repeat_Mode;
	DSReg SOUNDCNT_Format;
	DSReg SOUNDCNT_Start_Status;
	DSReg SOUNDSAD;
	DSReg SOUNDTMR;
	DSReg SOUNDPNT;
	DSReg SOUNDLEN;

	byte index;
	bool on;
	int Volume_Mul;
	int Volume_Div;
	bool Hold;
	int Panning;
	int Wave_Duty;
	int Repeat_Mode;
	int Format;

	uint source;
	uint timer;
	uint loopstart;
	uint length;

	int totallength;
	int samplepos;

	int freqCounter;
	int currentSample;

	int lfsr;
	int psgcnt;

	void reset(
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
	);

	void set_soundreg(int regindex);
	uint GetLength();
	void check_loop_end();
	void update_timebased(Int32 new_cycles);
};