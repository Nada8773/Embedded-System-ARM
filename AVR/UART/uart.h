/*
 * uart.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: ZAS
 */

#ifndef UART_H_
#define UART_H_

#include "macro_config.h"

void UART_init();
void UART_sendByte(uint8 data);
uint8 UART_recieveByte();
void UART_sendString(uint8 *str);
void UART_recieveString(uint8 *str);

#define true 1
#define recievebyte true

#endif /* UART_H_ */
