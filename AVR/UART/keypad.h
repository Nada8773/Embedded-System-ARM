/*
 * keypad.h
 *
 *  Created on: ٢٦‏/١٠‏/٢٠١٦
 *      Author: ZAS
 */

#ifndef KEYPAD_H_
#define KEYPAD_H_



#include "micro_config.h"


#define N_col 4
#define N_row 4

/* Keypad Port Configurations */
#define KEYPAD_PORT_OUT PORTA
#define KEYPAD_PORT_IN  PINA
#define KEYPAD_PORT_DIR DDRA

/*
 * Function responsible for getting the pressed keypad key
 */
uint8 KeyPad_getPressedKey(void);

/*
 * Function responsible for mapping the switch number in the keypad to
 * its corresponding functional number in the proteus for 4x3 keypad
 */
uint8 KeyPad_4x3_adjustKeyNumber(uint8 button_number);

/*
 * Function responsible for mapping the switch number in the keypad to
 * its corresponding functional number in the proteus for 4x4 keypad
 */
uint8 KeyPad_4x4_adjustKeyNumber(uint8 button_number);

#endif /* KEYPAD_H_ */
