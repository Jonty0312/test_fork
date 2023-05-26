#ifndef __ONEWIRE_H
#define __ONEWIRE_H

#include <config.h>
#include "GPIO.h"
#include <intrins.h>

sbit DQ = P0^0;  
bit init_ds18b20();
void Delay_OneWire(unsigned int t);
void Write_DS18B20(unsigned char dat);
unsigned char Read_DS18B20(void);
//void DS1302_Init(void);
void Delay500us();
void Delay645us();
void Delay88us();
u16 read_temp();

#endif
