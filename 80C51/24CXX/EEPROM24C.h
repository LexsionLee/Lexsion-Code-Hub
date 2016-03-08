/*
*Copyright Lexsion
*All rights reserved
*
*�ļ����ƣ�EEPROM24C.h 
*ժҪ��EEPROM24C����ͷ�ļ�
*
*��ǰ�汾��0.3
*���ߣ�Lexsion
*������ڣ�2016��02��13��
*
*�ϴΰ汾��0.2
*���ߣ�Lexsion
*������ڣ�2016��02��8��
*
*ȡ���汾��0.2
*���ߣ�Lexsion
*
*/
#ifndef __EEPROM24C_H_
#define __EEPROM24C_H_

/*
*ѡ��MCU�ٶȣ�Ĭ��12M
*/
//#define MCU_Speed24M

/*
*������Ƭ��ͷ�ļ�
*/
#include<reg52.h>
#include<intrins.h>

//�ؼ����ض���
//#define uchar unsigned char

//IO����
sbit I2C_SDA = P2^0;
sbit I2C_SCL = P2^1;

/*
*��������
*/
/*5Us��ʱ����*/
void I2C_Delay5Us();
/*10Ms��ʱ����*/
void Delay10ms();
/*12M����tUs��ʱ����*/
void I2C_DelayUs(unsigned char t);
/*I2C������ʼ�ź�*/
void I2C_Start();
/*I2C������ֹ�ź�*/
void I2C_Stop();
/*I2C���߷���һ���ֽ�����*/
unsigned char I2C_SendByte(unsigned char dat);
/*I2C���߽���һ���ֽ�����*/
unsigned char I2C_ReceiveByte();
/*I2CӦ���źţ�ACK��*/
void I2C_Respon();
/*ͨ��I2C�������豸dadr��addr��д��byte[Master transmits to slave receiver (WRITE mode)]*/
void I2C_ByteWrite(unsigned char dadr,addr,byte);
/*ͨ��I2C���ߴ��豸dadr��addr����������[Master reads after setting register address (write register address; READ data)]*/
unsigned char I2C_ByteRead(unsigned char dadr,addr);
/*ͨ��I2C���߶�ȡ�豸dadr��ǰ��ַ��������[Master reads slave immediately after first byte (READ mode)]*/
unsigned char I2C_ImByteRead(unsigned char dadr);
#endif