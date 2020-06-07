#include <queue>
using namespace std;

#include "types.h"
#include "SoundChannel.h"
#include "SDL.h"

class SoundCapture
{
public:
	std::queue<Int16> capturefifo;
	uint start_addr;
	uint capture_addr;
	uint capture_cnt;
	uint capture_len;
	bool on;
	bool add;
	bool source;
	bool format8;
	bool oneshot;
};

class SoundGenerator
{
public:
	SoundChannel soundchannels[16];

	byte Master_Volume;
	byte Left_Output_from;
	byte Right_Output_from;
	bool Output_Ch1_to_Mixer;
	bool Output_Ch3_to_Mixer;
	bool Master_Enable;

	bool capturehack;

	std::queue<int> nextSamples_left;
	std::queue<int> nextSamples_right;
	SDL_mutex* nextSamples_lock;

	double samplingCounter;

	SoundGenerator();
	void set_soundcontrol();
	void set_soundcapture();
	void update_timebased(Int32 new_cycles);

	static Uint8* audio_chunk;
	static Uint32 audio_len;
	static Uint8* audio_pos;

	SoundCapture capture[2];
};

extern void fill_audio(void* udata, Uint8* stream, int len);
