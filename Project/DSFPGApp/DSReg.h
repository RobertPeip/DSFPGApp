#pragma once
#include <string>
using namespace std;

#include "types.h"

class DSReg
{
public:
    UInt32 address;
    byte msb;
    byte lsb;
    UInt16 count;
	UInt32 defaultvalue;
	string name;

	byte* data;

	DSReg();
	DSReg(UInt32 address, byte msb, byte lsb, UInt16 count, UInt32 defaultvalue, string accesstype, string name, byte data[]);
    void write(UInt32 value);
    UInt32 read();
    bool on();
    void mask(UInt32 mask);
    void write_reg(UInt32 value);
};
