#ifndef _KEY_H
#define _KEY_H

#include "config.h"

sbit k1=P1^2;//修改模式
sbit k2=P1^3;//加
sbit k3=P1^4;//减

void Delay10ms();
unsigned char Key_Scan();



#endif