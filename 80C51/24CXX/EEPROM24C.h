/*
*Copyright Lexsion
*All rights reserved
*
*文件名称：EEPROM24C.h 
*摘要：EEPROM24C函数头文件
*
*当前版本：0.3
*作者：Lexsion
*完成日期：2016年02月13日
*
*上次版本：0.2
*作者：Lexsion
*完成日期：2016年02月8日
*
*取代版本：0.2
*作者：Lexsion
*
*/
#ifndef __EEPROM24C_H_
#define __EEPROM24C_H_

/*
*选择MCU速度，默认12M
*/
//#define MCU_Speed24M

/*
*包含单片机头文件
*/
#include<reg52.h>
#include<intrins.h>

//关键词重定义
//#define uchar unsigned char

//IO定义
sbit I2C_SDA = P2^0;
sbit I2C_SCL = P2^1;

/*
*函数声明
*/
/*5Us延时函数*/
void I2C_Delay5Us();
/*10Ms延时函数*/
void Delay10ms();
/*12M晶振tUs延时函数*/
void I2C_DelayUs(unsigned char t);
/*I2C总线起始信号*/
void I2C_Start();
/*I2C总线终止信号*/
void I2C_Stop();
/*I2C总线发送一个字节数据*/
unsigned char I2C_SendByte(unsigned char dat);
/*I2C总线接收一个字节数据*/
unsigned char I2C_ReceiveByte();
/*I2C应答信号（ACK）*/
void I2C_Respon();
/*通过I2C总线向设备dadr的addr处写入byte[Master transmits to slave receiver (WRITE mode)]*/
void I2C_ByteWrite(unsigned char dadr,addr,byte);
/*通过I2C总线从设备dadr的addr处读出数据[Master reads after setting register address (write register address; READ data)]*/
unsigned char I2C_ByteRead(unsigned char dadr,addr);
/*通过I2C总线读取设备dadr当前地址处的数据[Master reads slave immediately after first byte (READ mode)]*/
unsigned char I2C_ImByteRead(unsigned char dadr);
#endif