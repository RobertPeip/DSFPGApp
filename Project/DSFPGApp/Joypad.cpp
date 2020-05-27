#include "SDL.h"

#include "Joypad.h"
#include "regs_arm9.h"
#include "regs_arm7.h"
#include "IRP.h"

JOYPAD Joypad;

void JOYPAD::reset()
{
	oldvalue = 0x3FF;
	oldvalue_ext = 0x7F;
	Regs_Arm9.Sect_keypad9.KEYINPUT.write(oldvalue);
	Regs_Arm7.Sect_keypad7.KEYINPUT.write(oldvalue);
	Regs_Arm7.Sect_keypad7.EXTKEYIN.write(oldvalue_ext);

	KeyDebug = false;
	KeyPen = false;
	KeyHinge = true;
}

void JOYPAD::set_reg()
{
	oldvalue = value;
	value = 0x00;

	if (!KeyA) { value |= 1; }
	if (!KeyB) { value |= 2; }
	if (!KeySelect) { value |= 4; }
	if (!KeyStart) { value |= 8; }
	if (!KeyRight) { value |= 16; }
	if (!KeyLeft) { value |= 32; }
	if (!KeyUp) { value |= 64; }
	if (!KeyDown) { value |= 128; }
	if (!KeyR) { value |= 256; }
	if (!KeyL) { value |= 512; }

	double timems = SDL_GetPerformanceCounter() * 1000.0 / (double)SDL_GetPerformanceFrequency();
	UInt64 timeu64 = (UInt64)timems;
	if (KeyAToggle && timeu64 % 50 < 25) { value &= 0x3FE; }
	if (KeyBToggle && timeu64 % 50 < 25) { value &= 0x3FD; }

	if (value != oldvalue)
	{
		Regs_Arm9.Sect_keypad9.KEYINPUT.write(value);
		Regs_Arm7.Sect_keypad7.KEYINPUT.write(value);
		check_irp();
	}

	oldvalue_ext = value_ext;
	value_ext = 0x34;

	if (!KeyX) { value_ext |= 1; }
	if (!KeyY) { value_ext |= 2; }
	if (!KeyDebug) { value_ext |= 8; }
	if (!KeyPen) { value_ext |= 64; }
	if (!KeyHinge) { value_ext |= 128; }

	if (value_ext != oldvalue_ext)
	{
		Regs_Arm7.Sect_keypad7.EXTKEYIN.write(value_ext);
	}
}

void JOYPAD::check_irp()
{
	UInt16 irpmask = (UInt16)Regs_Arm9.Sect_keypad9.KEYCNT.read();
	if ((irpmask & 0x4000) > 0)
	{
		if ((irpmask & 0x8000) > 0) // logical and -> all mentioned
		{
			irpmask &= 0x3FF;
			UInt16 newvalue = (UInt16)((~value) & irpmask);
			if (newvalue == irpmask)
			{
				IRP7.set_irp_bit(IRP7.IRPMASK_Keypad, false);
			}
		}
		else // logical or -> at least one
		{
			irpmask &= 0x3FF;
			UInt16 newvalue = (UInt16)((~value) & irpmask);
			newvalue &= 0x3FF;
			if (newvalue > 0)
			{
				IRP7.set_irp_bit(IRP7.IRPMASK_Keypad, false);
			}
		}
	}

	irpmask = (UInt16)Regs_Arm7.Sect_keypad7.KEYCNT.read();
	if ((irpmask & 0x4000) > 0)
	{
		if ((irpmask & 0x8000) > 0) // logical and -> all mentioned
		{
			irpmask &= 0x3FF;
			UInt16 newvalue = (UInt16)((~value) & irpmask);
			if (newvalue == irpmask)
			{
				IRP7.set_irp_bit(IRP7.IRPMASK_Keypad, false);
			}
		}
		else // logical or -> at least one
		{
			irpmask &= 0x3FF;
			UInt16 newvalue = (UInt16)((~value) & irpmask);
			newvalue &= 0x3FF;
			if (newvalue > 0)
			{
				IRP7.set_irp_bit(IRP7.IRPMASK_Keypad, false);
			}
		}
	}
}