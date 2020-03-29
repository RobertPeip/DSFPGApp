#include "IRP.h"
#include "regs_arm9.h"
#include "regs_arm7.h"

Irp IRP;

void Irp::set_irp_bit(UInt16 mask)
{
	IRP_Flags |= mask;
	Regs_Arm9.Sect_system9.IF.write(IRP_Flags);
}

void Irp::update_IE()
{
	IE = (UInt16)Regs_Arm9.Sect_system9.IE.read();
}

void Irp::clear_irp_bits()
{
	UInt16 clearvector = (UInt16)Regs_Arm9.Sect_system9.IF.read();
	IRP_Flags = (UInt16)(IRP_Flags & (~clearvector));
	Regs_Arm9.Sect_system9.IF.write(IRP_Flags);
}

void Irp::update_IME(UInt16 value)
{
	Master_enable = (value & 1) == 1;
}

UInt16 Irp::get_IF_with_mask()
{
	return (UInt16)(IRP_Flags & IE);
}