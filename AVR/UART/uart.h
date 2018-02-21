/*
 * uart.h
 *
 *  Created on: ٢٦‏/١٠‏/٢٠١٦
 *      Author: ZAS
 */

#ifndef UART_H_
#define UART_H_

#include "micro_config.h"

void UART_init();

uint8 UART_recieveByte();
void UART_sendByte(uint8 data);


#endif /* UART_H_ */
