/*
 * lcd.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: ZAS
 */

#ifndef LCD_H_
#define LCD_H_

#include "macro_config.h"

#define RS  PB1
#define R_W PB2
#define E   PB3

#define UPPER_PORT_PINS
#define DATA_BITS_MODE 4

void init_lcd();
void LCD_sendCommand(uint8 command);
void LCD_displayCharacter(uint8 data);
void LCD_displayString(uint8 *str);
void LCD_intgerToString(int data);


#endif /* LCD_H_ */
