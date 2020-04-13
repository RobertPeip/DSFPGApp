#pragma once

#include "types.h"

class JOYPAD
{
public:
	bool KeyA;
	bool KeyB;
	bool KeyX;
	bool KeyY;
	bool KeyL;
	bool KeyR;
	bool KeyStart;
	bool KeySelect;
	bool KeyUp;
	bool KeyDown;
	bool KeyLeft;
	bool KeyRight;

	bool KeyDebug;
	bool KeyPen;
	bool KeyHinge;

	bool KeyAToggle;
	bool KeyBToggle;

	UInt16 oldvalue;
	byte oldvalue_ext;

	void reset();
	void set_reg();
	void check_irp();

private:
	UInt16 value;
	byte value_ext;
};
extern JOYPAD Joypad;