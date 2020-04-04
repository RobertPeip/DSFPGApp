#pragma once
#include <queue>
using namespace std;

#include "types.h"
#include "DSReg.h"

class IPC
{
public:
	void reset(bool isArm9);
	void write_sync();
	void write_control();

private:
	DSReg IPCSYNC_Data_from_IPCSYNC;
	DSReg IPCSYNC_Data_to_IPCSYNC;
	DSReg IPCSYNC_EXTERN_to;
	DSReg IPCSYNC_EXTERN_from;

	DSReg IPCFIFOCNT;
	DSReg Send_Fifo_Empty_Status;
	DSReg Send_Fifo_Full_Status;
	DSReg Send_Fifo_Empty_IRQ;
	DSReg Send_Fifo_Clear;
	DSReg Receive_Fifo_Empty;
	DSReg Receive_Fifo_Full;
	DSReg Receive_Fifo_Not_Empty_IRQ;
	DSReg Error_Read_Empty_Send_Full;
	DSReg Enable_Send_Receive_Fifo;

	bool isArm9;
	std::queue<uint> fifo;
	byte readWriteError;

	void update_status();

};
extern IPC IPC9to7;
extern IPC IPC7to9;