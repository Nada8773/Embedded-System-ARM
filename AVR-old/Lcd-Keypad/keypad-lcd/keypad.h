/*
 * keypad.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: ZAS
 */

#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "macro_config.h"

#define no_of_col 4
#define no_of_row 4

uint8 KeyPad_PressedKey();
uint8 keypad_4x4(uint8 keypad_number);

#endif /* KEYPAD_H_ */
