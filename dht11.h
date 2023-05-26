#ifndef _dht11_H
#define _dht11_H

#include "delay.h"

//管脚定义
sbit DHT11_DQ=P0^0;

//函数声明
void Delay30us();
void Delay10us();
void dht11_gpio_OUT();
u8 DHT11_Init(void);//DHT11初始化 
void DHT11_Rst(void);//复位DHT11
u8 DHT11_Check(void);//等待DHT11的回应
u8 DHT11_Read_Byte(void);//从DHT11读取一个字节
u8 DHT11_Read_Data(u8 *temp,u8 *humi);//从DHT11读取一次数据

#endif