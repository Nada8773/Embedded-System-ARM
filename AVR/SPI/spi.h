/*
 * spi.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: ZAS
 */

#ifndef SPI_H_
#define SPI_H_

#include "micro_confg.h"

void SPI_initMaster();

void SPI_sendByte(uint8 data);
void SPI_sendString(uint8 *str);

uint8 SPI_receiveByte();





#endif /* SPI_H_ */
