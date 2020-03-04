/*
 * EXTI_config.h
 *
 *  Created on: Jan 28, 2020
 *      Author: pc
 */

#ifndef EXTI_CONFIG_H_
#define EXTI_CONFIG_H_
/*
 * options:-
            1- ENABLED
            0- DISABLED
*/

#define EXTI_u8_INT0_CONTROL     ENABLED

/*
 * options:-
            1- ENABLED
            0- DISABLED
*/

#define EXTI_u8_INT1_CONTROL     ENABLED

/*
 * options:-
            1- ENABLED
            0- DISABLED
*/

#define EXTI_u8_INT2_CONTROL     ENABLED
/*
* option :-
*        1- LOW_LEVEL
*        2- ON_CHANGE
*        3- FALLING_EDGE
*        4- RISING_EDGE
*
*/
#define EXTI_u8_INT0_SENSE      FALLING_EDGE

/*
* option :-
*        1- LOW_LEVEL
*        2- ON_CHANGE
*        3- FALLING_EDGE
*        4- RISING_EDGE
*
*/
#define EXTI_u8_INT1_SENSE      FALLING_EDGE


/*
* option :-
*      
*        1- FALLING_EDGE
*        2- RISING_EDGE
*
*/
#define EXTI_u8_INT2_SENSE      FALLING_EDGE





#endif /* EXTI_CONFIG_H_ */
