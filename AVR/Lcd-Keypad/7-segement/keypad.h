/*
 * keypad.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: ZAS
 */

#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "macro_confg.h"
#include "common_macros.h"

unsigned char keypad();
unsigned char KeyPad_4x3(unsigned int number);
unsigned char KeyPad_4x4(unsigned int number);

#define number_of_colum 4
#define number_of_row 4
#define KEYPAD_PORT_DIR DDRA
#define KEYPAD_PORT_OUT PORTA
#define KEYPAD_PORT_IN PINA



#endif /* KEYPAD_H_ */
