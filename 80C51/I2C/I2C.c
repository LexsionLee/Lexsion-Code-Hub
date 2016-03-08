/*
*Copyright Lexsion
*All rights reserved
*
*文件名称：I2C.c 
*摘要：I2C函数
*
*当前版本：0.4
*作者：Lexsion
*完成日期：2016年02月16日
*
*上次版本：0.3
*作者：Lexsion
*完成日期：2016年02月13日
*
*取代版本：0.3
*作者：Lexsion
*
*/

#include"I2C.h"


/*
*函数名：I2C_Delay5Us
*函数功能：I2C延时函数
*输入：__
*输出：__
*/
#ifndef MCU_Speed24M
void I2C_Delay5Us()    //@12.000MHz    
{
    _nop_();
    _nop_();
    _nop_();
}
void Delay10ms()        //@12.000MHz
{
    unsigned char i, j;

    i = 20;
    j = 113;
    do
    {
        while (--j);
    } while (--i);
}
#else
void I2C_Delay5Us()        //@24.000MHz
{
    unsigned char i;

    _nop_();
    i = 2;
    while (--i);
}
void Delay10ms()        //@24.000MHz
{
    unsigned char i, j;

    i = 39;
    j = 230;
    do
    {
        while (--j);
    } while (--i);
}

#endif

/*
*函数名：I2C_Start
*函数功能：I2C总线起始信号,在SCL时钟信号在高电平期间SDA信号产生一个下降沿
*输入：__
*输出：__
*注：起始信号后，SDA和SCL都为0，表示总线被使用。
*/
void I2C_Start()
{
    I2C_SDA = 1;
    I2C_Delay5Us();
    I2C_SCL = 1;
    I2C_Delay5Us();
    I2C_SDA = 0;
    I2C_Delay5Us();
    I2C_SCL = 0;
    I2C_Delay5Us();
}
/*
*函数名：I2C_Stop
*函数功能：I2C总线终止信号,在SCL时钟信号在高电平期间SDA信号产生一个上升沿
*输入：__
*输出：__
*注：终止信号后，SDA和SCL都为1，表示总线空闲。
*/
void I2C_Stop()
{
    I2C_SDA = 0;
    I2C_Delay5Us();
    I2C_SCL = 1;
    I2C_Delay5Us();
    I2C_SDA = 1;
    I2C_Delay5Us();
}
/*
*函数名：I2C_SendByte
*函数功能：通过I2C总线发送一个字节数据
*输入：dat
*输出：应答返回1，非应答返回0。
*注：发送字节结束后，I2C_SCL=0,I2C_SDA=1
*/
unsigned char I2C_SendByte(unsigned char dat)
{
    unsigned char a;
    unsigned char b = 0;//用于等待应答信号的延时
    for(a = 0; a < 8; a++)   //for循环发送8位数据，起始位为dat的高位
    {
        I2C_SDA = dat >> 7;   //dat右移7位的结果为最高位（MSB），将结果送至I2C_SDA
        dat = dat << 1;   //dat左移一位，次高位顶替最高位，为下一次循环做准备
        I2C_Delay5Us();   //延时等待稳定
        I2C_SCL = 1;    
        I2C_Delay5Us();   //根据I2C协议延时
        I2C_SCL = 0;    //SCL低电平，为下次SDA电平变换做准备
        I2C_Delay5Us();   //延时稳定
    }
    I2C_SDA = 1;   //释放SDA
    I2C_Delay5Us(); //延时等待
    I2C_SCL = 1;   
    while(I2C_SDA)    //检查接收方（Receiver）是否应答（SDA = 0）
    {
        b++;
        if(b > 200)
        {
            I2C_SCL = 0;
            I2C_Delay5Us();
            return 0;   //接收方非应答？
        }
    }
    I2C_SCL = 0;
    I2C_Delay5Us();
    return 1;   //接收方应答
}
/*
*函数名：I2C_ReceiveByte
*函数功能：通过I2C总线接收一个字节数据
*输入：--
*输出：dat
*注：接收字节结束后，I2C_SCL=0,I2C_SDA=1
*/
unsigned char I2C_ReceiveByte()
{
    unsigned char i,dat = 0;   //定义循环变量i和输出变量dat
//    I2C_SCL = 0;
//    I2C_Delay5Us();
    I2C_SDA = 1;   //确保SDA被释放
    I2C_Delay5Us();
    for(i = 0; i < 8; i++)  //通过for循环接收一个字节(8位)数据,存入dat
    {
        I2C_SCL = 1;
        I2C_Delay5Us();
        dat <<= 1;
        dat |= I2C_SDA;
        I2C_Delay5Us();
        I2C_SCL = 0;
        I2C_Delay5Us();
    }
    return dat;   //输出dat
}
/*
*函数名：I2C_Respon
*函数功能：接收一个字节数据后产生应答，以便接受下一个字节
*输入：--
*输出：--
*注：应答结束后I2C_SCL=0,I2C_SDA=1
*/
void I2C_Respon()
{
    I2C_SDA = 0;
    I2C_Delay5Us();   //I2C_SDA保持5us低电平
    I2C_SCL = 1;
    I2C_Delay5Us();   //IC_SCL保持5us高电平
    I2C_SCL = 0;
    I2C_Delay5Us();   //拉低I2C_SCL
    I2C_SDA = 1;
    I2C_Delay5Us();   //释放I2C_SDA
}
/*
*函数名：I2C_ByteWrite
*函数功能：向设备dadr的addr地址处写入byte
*输入：dadr,addr,byte
*输出：--
*/
void I2C_ByteWrite(unsigned char dadr,addr,byte)
{
    I2C_Start();
    I2C_SendByte(dadr);
    I2C_SendByte(addr);
    I2C_SendByte(byte);
    I2C_Stop();
    Delay10ms();   //延时等待写入，Write Cycle Time=10ms
}
/*
*函数名：I2C_ByteRead
*函数功能：将设备dadr的addr地址处数据读出
*输入：dadr,addr
*输出：dat
*/
unsigned char I2C_ByteRead(unsigned char dadr,addr)
{
    unsigned char dat;
    I2C_Start();
    I2C_SendByte(dadr);
    I2C_SendByte(addr);
    I2C_Start();
    I2C_SendByte(dadr | 0x01);
    //I2C_Delay5Us(); 
    dat = I2C_ReceiveByte();
    I2C_Stop();
    return dat;
}
/*
*函数名：I2C_ImByteRead
*函数功能：将设备dadr的当前地址处数据读出
*输入：dadr
*输出：dat
*/
unsigned char I2C_ImByteRead(unsigned char dadr)
{
    unsigned char dat;
    I2C_Start();
    I2C_SendByte(dadr | 0x01);
    dat = I2C_ReceiveByte();
    I2C_Stop();
    return dat;
}