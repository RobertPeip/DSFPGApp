#include "IRP.h"
#include "regs_arm9.h"
#include "regs_arm7.h"
#include "CPU.h"

Irp IRP9;
Irp IRP7;

Irp::Irp()
{

}

void Irp::reset(bool isArm9)
{
	if (isArm9)
	{
		CPU = &CPU9;
		REG_IE = Regs_Arm9.Sect_system9.IE;
		REG_IF = Regs_Arm9.Sect_system9.IF;
	}
	else
	{
		CPU = &CPU7;
		REG_IE = Regs_Arm7.Sect_system7.IE;
		REG_IF = Regs_Arm7.Sect_system7.IF;
	}

	checknext = false;
}

void Irp::set_irp_bit(UInt32 mask)
{
	IRP_Flags |= mask;
	REG_IF.write(IRP_Flags);
	checknext = true;
}

void Irp::update_IE()
{
	IE = REG_IE.read();
	checknext = true;
}

void Irp::clear_irp_bits()
{
	UInt32 clearvector = (UInt32)REG_IF.read();
	IRP_Flags = (UInt32)(IRP_Flags & (~clearvector));
	REG_IF.write(IRP_Flags);
}

void Irp::update_IME(UInt32 value)
{
	Master_enable = (value & 1) == 1;
	checknext = true;
}

UInt32 Irp::get_IF_with_mask()
{
	return IRP_Flags & IE;
}

void Irp::check_and_execute_irp()
{
	if (!CPU->IRQ_disable && Master_enable && get_IF_with_mask() > 0)
	{
		checknext = false;
		CPU->interrupt();
	}
}