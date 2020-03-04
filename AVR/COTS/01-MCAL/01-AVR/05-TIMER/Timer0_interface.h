/*
 * Timer0_interface.h
 *
 *  Created on: Feb 24, 2020
 *      Author: pc
 */

#ifndef TIMER0_INTERFACE_H_
#define TIMER0_INTERFACE_H_


#define PRELOAD_VAL 131
void TIMER0_voidInit(void);
void Timer0_voidSetCallback(void(*ptr)(void));


#endif /* TIMER0_INTERFACE_H_ */
