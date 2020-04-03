#pragma once
#include <string>
using namespace std;

#include "types.h"

class Gameboy
{
public:
	bool on = false;
	bool pause = false;
	bool coldreset = false;

	UInt64 totalticks;

	string filename;

	string statefilename;
	bool do_savestate = false;
	bool do_loadstate = false;
	bool loading_state;
	UInt32 savestate[131072];

	void reset();
	void run();
	UInt64 next_event_time();
	void create_savestate();
	void load_savestate();
};
extern Gameboy gameboy;