#include "types.h"
#include "DSReg.h"

//#define SAMPLINGRRATE (67027964.0 / 44100.0)
#define SAMPLINGRRATE   (66907964.0 / 44100.0)

static const SByte INDEXTBL[8] =
{
	-1, -1, -1, -1, 2, 4, 6, 8
};

static const Int16 ADPCMTABLE[89] =
{
	0x0007, 0x0008, 0x0009, 0x000A, 0x000B, 0x000C, 0x000D, 0x000E, 0x0010,
	0x0011, 0x0013, 0x0015, 0x0017, 0x0019, 0x001C, 0x001F, 0x0022, 0x0025,
	0x0029, 0x002D, 0x0032, 0x0037, 0x003C, 0x0042, 0x0049, 0x0050, 0x0058,
	0x0061, 0x006B, 0x0076, 0x0082, 0x008F, 0x009D, 0x00AD, 0x00BE, 0x00D1,
	0x00E6, 0x00FD, 0x0117, 0x0133, 0x0151, 0x0173, 0x0198, 0x01C1, 0x01EE,
	0x0220, 0x0256, 0x0292, 0x02D4, 0x031C, 0x036C, 0x03C3, 0x0424, 0x048E,
	0x0502, 0x0583, 0x0610, 0x06AB, 0x0756, 0x0812, 0x08E0, 0x09C3, 0x0ABD,
	0x0BD0, 0x0CFF, 0x0E4C, 0x0FBA, 0x114C, 0x1307, 0x14EE, 0x1706, 0x1954,
	0x1BDC, 0x1EA5, 0x21B6, 0x2515, 0x28CA, 0x2CDF, 0x315B, 0x364B, 0x3BB9,
	0x41B2, 0x4844, 0x4F7E, 0x5771, 0x602F, 0x69CE, 0x7462, 0x7FFF
};

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

	SByte tableindex;
	SByte loop_index;
	int loop_sample;

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