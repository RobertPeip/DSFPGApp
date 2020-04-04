#include "IPC.h"
#include "regs_arm9.h"
#include "regs_arm7.h"
#include "IRP.h"

IPC IPC9to7;
IPC IPC7to9;

void IPC::reset(bool isArm9)
{
	this->isArm9 = isArm9;
	while (!fifo.empty()) fifo.pop();
	readWriteError = 0;

	if (isArm9)
	{
		IPCFIFOCNT					 = Regs_Arm9.Sect_system9.IPCFIFOCNT                             ;
		Send_Fifo_Empty_Status       = Regs_Arm9.Sect_system9.IPCFIFOCNT_Send_Fifo_Empty_Status      ;
		Send_Fifo_Full_Status		 = Regs_Arm9.Sect_system9.IPCFIFOCNT_Send_Fifo_Full_Status		 ;	
		Send_Fifo_Empty_IRQ			 = Regs_Arm9.Sect_system9.IPCFIFOCNT_Send_Fifo_Empty_IRQ		 ;	
		Send_Fifo_Clear				 = Regs_Arm9.Sect_system9.IPCFIFOCNT_Send_Fifo_Clear			 ;	
		Receive_Fifo_Empty			 = Regs_Arm9.Sect_system9.IPCFIFOCNT_Receive_Fifo_Empty			 ;
		Receive_Fifo_Full			 = Regs_Arm9.Sect_system9.IPCFIFOCNT_Receive_Fifo_Full			 ;
		Receive_Fifo_Not_Empty_IRQ	 = Regs_Arm9.Sect_system9.IPCFIFOCNT_Receive_Fifo_Not_Empty_IRQ	 ;
		Error_Read_Empty_Send_Full	 = Regs_Arm9.Sect_system9.IPCFIFOCNT_Error_Read_Empty_Send_Full	 ;
		Enable_Send_Receive_Fifo	 = Regs_Arm9.Sect_system9.IPCFIFOCNT_Enable_Send_Receive_Fifo	 ;
	}
	else
	{
		IPCFIFOCNT					 = Regs_Arm7.Sect_system7.IPCFIFOCNT                             ;
		Send_Fifo_Empty_Status       = Regs_Arm7.Sect_system7.IPCFIFOCNT_Send_Fifo_Empty_Status      ;
		Send_Fifo_Full_Status		 = Regs_Arm7.Sect_system7.IPCFIFOCNT_Send_Fifo_Full_Status		 ;	
		Send_Fifo_Empty_IRQ			 = Regs_Arm7.Sect_system7.IPCFIFOCNT_Send_Fifo_Empty_IRQ		 ;	
		Send_Fifo_Clear				 = Regs_Arm7.Sect_system7.IPCFIFOCNT_Send_Fifo_Clear			 ;	
		Receive_Fifo_Empty			 = Regs_Arm7.Sect_system7.IPCFIFOCNT_Receive_Fifo_Empty			 ;
		Receive_Fifo_Full			 = Regs_Arm7.Sect_system7.IPCFIFOCNT_Receive_Fifo_Full			 ;
		Receive_Fifo_Not_Empty_IRQ	 = Regs_Arm7.Sect_system7.IPCFIFOCNT_Receive_Fifo_Not_Empty_IRQ	 ;
		Error_Read_Empty_Send_Full	 = Regs_Arm7.Sect_system7.IPCFIFOCNT_Error_Read_Empty_Send_Full	 ;
		Enable_Send_Receive_Fifo	 = Regs_Arm7.Sect_system7.IPCFIFOCNT_Enable_Send_Receive_Fifo	 ;
	}

	update_status();
}

void IPC::write_control()
{
	if (Error_Read_Empty_Send_Full.on())
	{
		readWriteError = 0;
	}

	if (Send_Fifo_Clear.on())
	{
		while (!fifo.empty()) fifo.pop();
		
		Send_Fifo_Empty_Status.write(1);
		Receive_Fifo_Empty.write(1);

		Send_Fifo_Full_Status.write(0);
		Receive_Fifo_Full.write(0);
	}

	update_status();

	if (Send_Fifo_Empty_IRQ.on() && Send_Fifo_Empty_Status.on()) IRP.set_irp_bit(IRP.IRPMASK_IPC_Send_FIFO_Empty);

	if (Receive_Fifo_Not_Empty_IRQ.on() && !Receive_Fifo_Empty.on()) IRP.set_irp_bit(IRP.IRPMASK_IPC_Send_FIFO_Empty);
}

void IPC::update_status()
{
	std::queue<uint> recfifo = IPC9to7.fifo;
	if (isArm9) recfifo = IPC7to9.fifo;

	if (fifo.empty())      Send_Fifo_Empty_Status.write(1); else Send_Fifo_Empty_Status.write(0);
	if (fifo.size() == 16) Send_Fifo_Full_Status.write(1);  else Send_Fifo_Full_Status.write(0);

	if (recfifo.empty())      Receive_Fifo_Empty.write(1);  else Receive_Fifo_Empty.write(0);
	if (recfifo.size() == 16) Receive_Fifo_Full.write(1);   else Receive_Fifo_Full.write(0);
		
	Error_Read_Empty_Send_Full.write(readWriteError);
}