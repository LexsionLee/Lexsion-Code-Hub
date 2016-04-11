/*
*Copyright Lexsion
*All rights reserved
*
*工程名称：PWM
*摘要：简单PWM输出控制，无定时器
*
*当前版本：0.2
*完成时间：2016年4月11日
*
*上次版本：0.1
*完成时间：2016年4月11日
*
*取代版本：0.1
完成时间：
*/

#include<reg51.h>
#include<intrins.h>

#define ON 0
#define OFF 1    //定义开和关两种状态对应电平
#define TBIT 10

sbit LED = P2^0;   //LED接口定义
sbit Up = P3^0;   //增加亮度按键
sbit Down = P3^1;   //减小亮度按键

unsigned int tON = 0, tOFF = 500;   //tON为接通时间，tOFF为关断时间
unsigned int tH,tL;
//tON = 0;
//tOFF = 500;

//void Delay(unsigned int);  //延时函数，延时单位为ms
void Delay20us();   //20微秒延时，PWM周期由此决定
void PWM();    //PWM的一个周期


void main()
{

    
    while(1)
    {
        PWM();
        
        if(Up == 0)   //如果按键Up按下
        {
            PWM();
            PWM();
            PWM();
            PWM();
            PWM();    //用PWM消抖，防止按键按下时灯光明显变暗
            
            if(Up == 0)
            {
                tON = tON +TBIT;
                tOFF = tOFF -TBIT;
                if(tON > 500)   //如果tON超过最大值，重新初始化
                {
                    tON = 0;
                    tOFF = 500;
                }
            }
        }
        if(Down == 0)   //如果按键Down按下
        {
            PWM();
            PWM();
            PWM();
            PWM();
            PWM();   //用PWM消抖，防止按键按下时灯光明显变暗
            
            if(Down == 0)
            {
                tON = tON -TBIT;
                tOFF = tOFF +TBIT;
                if(tOFF > 500)   //如果tOFF超过最大值，重新初始化
                {
                    tON = 500;
                    tOFF = 0;
                }
            }
        }
    }
}


//void Delay(unsigned int delaytimes)      //@12.000MHz
//{
//    unsigned char i, j;

//    while(delaytimes)
//    {
//	i = 2;
//	j = 230;
//	do
//	{
//		while (--j);
//	} while (--i);
//    delaytimes--;
//    }
//}

void Delay20us()		//@12.000MHz
{
	unsigned char i;

	_nop_();
	i = 7;
	while (--i);
}

void PWM()
{
    for(tH=0; tH<tON; tH++)   //开
    {
        LED = ON;
        Delay20us();
    }
    for(tL=0; tL<tOFF; tL++)   //关
    {
        LED = OFF;
        Delay20us();
    }
}