#include "types.h"
#include "Soundgenerator.h"

class SOUND
{
public:
	SoundGenerator soundGenerator;

	UInt64 lasttime;

	void reset();
	void set_soundreg(UInt32 adr);
	void work();

private:
	bool sound_on;

};
extern SOUND Sound;