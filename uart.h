#ifndef _UART_H
#define _UART_H

#include <config.h>

void Delay1000ms();
void Send_Byte1(u8 dat);
void Send_String(u8 *dat);
void UartInit(void);
void Send_text();

#endif