#include <uart.h>
#define u8 unsigned char
#define u32 unsigned int


void Delay1000ms()		//@12.000MHz
{
	unsigned char i, j, k;

	_nop_();
	_nop_();
	i = 46;
	j = 153;
	k = 245;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}

void Send_Byte1(u8 dat)
{
    ES=0;
	SBUF=dat;
	while(!TI);
	TI=0;
    ES=1;
}
void Send_String(u8 *dat)
{
	while(*dat)
	{
		Send_Byte1(*dat++);
	}
}


void UartInit(void)		//115200bps@11.0592MHz
{
	SCON = 0x50;    //8位数据,可变波特率
    S1_USE_P36P37();
	AUXR |= 0x40;		//定时器1时钟为Fosc,即1T
	AUXR &= 0xFE;		//串口1选择定时器1为波特率发生器
	TMOD &= 0x0F;		//设定定时器1为16位自动重装方式
	TL1 = 0xE8;		//设定定时初值
	TH1 = 0xFF;		//设定定时初值
	ET1 = 0;		//禁止定时器1中断
	TR1 = 1;		//启动定时器1
}


void Send_text()
{
    Send_String("AT\r\n");

    Delay1000ms();
    Send_String("AT+CMGF=1\r\n");

    Delay1000ms();
    Send_String("AT+CSMP=17,167,2,25\r\n");
    Delay1000ms();
    Send_String("AT+CSCS=\"UCS2\"\r\n");
    Delay1000ms();
    Send_String("AT+CMGS=\"00310038003500320039003300310039003000340030\"\r\n");
    Delay1000ms();
    Send_String("4ED35E936709706B707E98848B66");
    Delay1000ms();
    Send_Byte1(0x1A); 
    Delay1000ms();
    Delay1000ms();
    Delay1000ms();
    Delay1000ms();
    Delay1000ms();
}
