#include "DSReg.h"

DSReg::DSReg()
{
    address = 0;
    count = 0;
    defaultvalue = 0;
    lsb = 0;
    msb = 0;
}

DSReg::DSReg(UInt32 address, byte msb, byte lsb, UInt16 count, UInt32 defaultvalue, string accesstype, byte data[])
{
    this->address = address;
    this->msb = msb;
    this->lsb = lsb;
    this->count = count;
    this->defaultvalue = defaultvalue;
	this->data = data;
}

void DSReg::write(UInt32 value)
{
    UInt32 newvalue = *(UInt32*)&data[address];
    UInt32 filter = ~((((UInt32)pow(2, msb + 1)) - 1) - (((UInt32)pow(2, lsb)) - 1));
    newvalue = newvalue & filter;
    newvalue |= value << lsb;

    write_reg(newvalue);
}

UInt32 DSReg::read()
{
    UInt32 value = *(UInt32*)&data[address];
    UInt32 filter = ((((UInt32)pow(2, msb + 1)) - 1) - (((UInt32)pow(2, lsb)) - 1));
    value = (value & filter) >> lsb;

    return value;
}

bool DSReg::on()
{
    UInt32 value = *(UInt32*)&data[address];
    return (((value >> lsb) & 1) == 1);
}

void DSReg::mask(UInt32 mask)
{
    UInt32 value = *(UInt32*)&data[address];
    write_reg(value & mask);
}

void DSReg::write_reg(UInt32 value)
{
    if (msb < 8)
    {
        data[address] = (byte)value;
    }
    else if (msb < 16)
    {
        data[address] = (byte)(value & 0xFF);
        data[address + 1] = (byte)((value >> 8) & 0xFF);
    }
    else
    {
        data[address] = (byte)(value & 0xFF);
        data[address + 1] = (byte)((value >> 8) & 0xFF);
        data[address + 2] = (byte)((value >> 16) & 0xFF);
        data[address + 3] = (byte)((value >> 24) & 0xFF);
    }
}