#include "IRP.h"
#include "regs_arm9.h"
#include "regs_arm7.h"
#include "CPU.h"
#include "gameboy.h"
#include "GXFifo.h"

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

	next_mask = 0;
	checknext = false;
}

void Irp::set_irp_bit(UInt32 mask, bool delay)
{
#ifdef FPGACOMPATIBLE
	if (delay)
	{
		next_mask = next_mask | mask;
	}
	else
	{
		IRP_Flags |= mask;
		REG_IF.write(IRP_Flags);
		checknext = true;
		gameboy.reschedule = true;
	}
#else
	IRP_Flags |= mask;
	REG_IF.write(IRP_Flags);
	checknext = true;
	gameboy.reschedule = true;
#endif // FPGACOMPATIBLE
}

void Irp::clear_irp_bit(UInt32 mask)
{
	IRP_Flags = (UInt32)(IRP_Flags & (~mask));
	REG_IF.write(IRP_Flags);
}

void Irp::update_IE()
{
	IE = REG_IE.read();
	checknext = true;
	gameboy.reschedule = true;
}

void Irp::clear_irp_bits()
{
	UInt32 clearvector = (UInt32)REG_IF.read();
	IRP_Flags = (UInt32)(IRP_Flags & (~clearvector));
	REG_IF.write(IRP_Flags);
	gameboy.reschedule = true;
	check_gxfifobits(); // clearing them has no effect if the situation is still the same?
}

void Irp::update_IME(UInt32 value)
{
	Master_enable = (value & 1) == 1;
	checknext = true;
	gameboy.reschedule = true;
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

void Irp::check_gxfifobits()
{
	byte irqsource = Regs_Arm9.Sect_3D9.GXSTAT_Command_FIFO_IRQ.read();
	if ((irqsource == 1 && GXFifo.lesshalf) || (irqsource == 2 && GXFifo.empty))
	{
		IRP9.set_irp_bit(IRP9.IRPMASK_Geometry_Command_FIFO, false);
	}
	else
	{
		IRP9.clear_irp_bit(IRP9.IRPMASK_Geometry_Command_FIFO);
	}
}