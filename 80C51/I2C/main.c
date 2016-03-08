#include<reg52.h>
#include"I2C.h"



void main()
{
    unsigned char p,q;
    q = 0xa0;
//    I2C_ByteWrite(0x5f,0x04,q);
    p = I2C_ByteRead(0xa0,0x04);
    while(1)
    {
        P2 = p;
    }
//    I2C_ByteWrite(0x0a,0x01,0x87);
//    p = I2C_ByteRead(0x34,0x43);
//    q = I2C_ImByteRead(0x32);
}