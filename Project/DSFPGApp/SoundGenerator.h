#include <queue>
using namespace std;

#include "types.h"
#include "SoundChannel.h"
#include "SDL.h"

class SoundGenerator
{
public:
	SoundChannel soundchannels[16];

	std::queue<int> nextSamples;
	SDL_mutex* nextSamples_lock;

	int samplingCounter;

	SoundGenerator();
	void update_timebased(Int32 new_cycles);

	static Uint8* audio_chunk;
	static Uint32 audio_len;
	static Uint8* audio_pos;
};

extern void fill_audio(void* udata, Uint8* stream, int len);
