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
	bool blockinput = false;
	bool skipcpuonce = false;
	bool newhblank = false;

	UInt64 totalticks;
	bool reschedule;

	string filename;

	string statefilename;
	bool do_savestate = false;
	bool do_loadstate = false;
	bool do_exportmem = false;
	bool loading_state;
	UInt32 savestate[2097152];

	void reset();
	void run();
	UInt64 next_event_time();
	void create_savestate();
	void load_savestate();
	void exportmem();
};
extern Gameboy gameboy;