#ifndef __STC_BH1750_H
#define __STC_BH1750_H

#include  <config.h>	
#include  <math.h>    //Keil library  
#include  <stdio.h>   //Keil library	
#include  <INTRINS.H>




                       
sbit	  SCL=P1^0;      //IIC时钟引脚定义
sbit  	  SDA=P1^1;      //IIC数据引脚定义

void  Single_Write_BH1750(u8 REG_Address);               //单个写入数据
u8 Single_Read_BH1750(u8 REG_Address);                //单个读取内部寄存器数据
void  Multiple_Read_BH1750();                               //连续的读取内部寄存器数据
void Init_BH1750(void);
void Delay5us1();
void Delay5ms();
void BH1750_Start();                    //起始信号
void BH1750_Stop();                     //停止信号
void BH1750_SendACK(bit ack);           //应答ACK
bit  BH1750_RecvACK();                  //读ack
void BH1750_SendByte(u8 dat);         //IIC单个字节写
u8 BH1750_RecvByte(); 
u16 Receive_Data();//IIC单个字节读

#endif  