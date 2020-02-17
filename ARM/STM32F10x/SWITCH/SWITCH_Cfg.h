
/********************************************************************************
**  FILENAME     : SWITCH_Cfg.h         			                           **
**  VERSION      : 1.0                                                         **
**  DATE         : 17 Feb 2020                                                 **                                                                         **
**  PLATFORM     : STM		                                                   **
**  AUTHOR       : Nada Mohamed                                                **
*********************************************************************************/

#ifndef SWITCH_CFG_H
#define SWITCH_CFG_H


#include "GPIO.h"



/************************************************************
 * this Function to return the container data (array of struct )
 * Return Type :-
 *            GPIO_t* ( pointer of struct GPIO_t)
 *Input Argument :-
 *             void
 *
 *************************************************************/
GPIO_t* SWITCH_u32GetSwitchConfiguration(void);



#endif
