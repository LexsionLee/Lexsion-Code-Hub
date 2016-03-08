/*
*Copyright Lexsion
*All rights reserved
*
*�ļ����ƣ�I2C.c 
*ժҪ��I2C����
*
*��ǰ�汾��0.4
*���ߣ�Lexsion
*������ڣ�2016��02��16��
*
*�ϴΰ汾��0.3
*���ߣ�Lexsion
*������ڣ�2016��02��13��
*
*ȡ���汾��0.3
*���ߣ�Lexsion
*
*/

#include"I2C.h"


/*
*��������I2C_Delay5Us
*�������ܣ�I2C��ʱ����
*���룺__
*�����__
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
*��������I2C_Start
*�������ܣ�I2C������ʼ�ź�,��SCLʱ���ź��ڸߵ�ƽ�ڼ�SDA�źŲ���һ���½���
*���룺__
*�����__
*ע����ʼ�źź�SDA��SCL��Ϊ0����ʾ���߱�ʹ�á�
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
*��������I2C_Stop
*�������ܣ�I2C������ֹ�ź�,��SCLʱ���ź��ڸߵ�ƽ�ڼ�SDA�źŲ���һ��������
*���룺__
*�����__
*ע����ֹ�źź�SDA��SCL��Ϊ1����ʾ���߿��С�
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
*��������I2C_SendByte
*�������ܣ�ͨ��I2C���߷���һ���ֽ�����
*���룺dat
*�����Ӧ�𷵻�1����Ӧ�𷵻�0��
*ע�������ֽڽ�����I2C_SCL=0,I2C_SDA=1
*/
unsigned char I2C_SendByte(unsigned char dat)
{
    unsigned char a;
    unsigned char b = 0;//���ڵȴ�Ӧ���źŵ���ʱ
    for(a = 0; a < 8; a++)   //forѭ������8λ���ݣ���ʼλΪdat�ĸ�λ
    {
        I2C_SDA = dat >> 7;   //dat����7λ�Ľ��Ϊ���λ��MSB�������������I2C_SDA
        dat = dat << 1;   //dat����һλ���θ�λ�������λ��Ϊ��һ��ѭ����׼��
        I2C_Delay5Us();   //��ʱ�ȴ��ȶ�
        I2C_SCL = 1;    
        I2C_Delay5Us();   //����I2CЭ����ʱ
        I2C_SCL = 0;    //SCL�͵�ƽ��Ϊ�´�SDA��ƽ�任��׼��
        I2C_Delay5Us();   //��ʱ�ȶ�
    }
    I2C_SDA = 1;   //�ͷ�SDA
    I2C_Delay5Us(); //��ʱ�ȴ�
    I2C_SCL = 1;   
    while(I2C_SDA)    //�����շ���Receiver���Ƿ�Ӧ��SDA = 0��
    {
        b++;
        if(b > 200)
        {
            I2C_SCL = 0;
            I2C_Delay5Us();
            return 0;   //���շ���Ӧ��
        }
    }
    I2C_SCL = 0;
    I2C_Delay5Us();
    return 1;   //���շ�Ӧ��
}
/*
*��������I2C_ReceiveByte
*�������ܣ�ͨ��I2C���߽���һ���ֽ�����
*���룺--
*�����dat
*ע�������ֽڽ�����I2C_SCL=0,I2C_SDA=1
*/
unsigned char I2C_ReceiveByte()
{
    unsigned char i,dat = 0;   //����ѭ������i���������dat
//    I2C_SCL = 0;
//    I2C_Delay5Us();
    I2C_SDA = 1;   //ȷ��SDA���ͷ�
    I2C_Delay5Us();
    for(i = 0; i < 8; i++)  //ͨ��forѭ������һ���ֽ�(8λ)����,����dat
    {
        I2C_SCL = 1;
        I2C_Delay5Us();
        dat <<= 1;
        dat |= I2C_SDA;
        I2C_Delay5Us();
        I2C_SCL = 0;
        I2C_Delay5Us();
    }
    return dat;   //���dat
}
/*
*��������I2C_Respon
*�������ܣ�����һ���ֽ����ݺ����Ӧ���Ա������һ���ֽ�
*���룺--
*�����--
*ע��Ӧ�������I2C_SCL=0,I2C_SDA=1
*/
void I2C_Respon()
{
    I2C_SDA = 0;
    I2C_Delay5Us();   //I2C_SDA����5us�͵�ƽ
    I2C_SCL = 1;
    I2C_Delay5Us();   //IC_SCL����5us�ߵ�ƽ
    I2C_SCL = 0;
    I2C_Delay5Us();   //����I2C_SCL
    I2C_SDA = 1;
    I2C_Delay5Us();   //�ͷ�I2C_SDA
}
/*
*��������I2C_ByteWrite
*�������ܣ����豸dadr��addr��ַ��д��byte
*���룺dadr,addr,byte
*�����--
*/
void I2C_ByteWrite(unsigned char dadr,addr,byte)
{
    I2C_Start();
    I2C_SendByte(dadr);
    I2C_SendByte(addr);
    I2C_SendByte(byte);
    I2C_Stop();
    Delay10ms();   //��ʱ�ȴ�д�룬Write Cycle Time=10ms
}
/*
*��������I2C_ByteRead
*�������ܣ����豸dadr��addr��ַ�����ݶ���
*���룺dadr,addr
*�����dat
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
*��������I2C_ImByteRead
*�������ܣ����豸dadr�ĵ�ǰ��ַ�����ݶ���
*���룺dadr
*�����dat
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