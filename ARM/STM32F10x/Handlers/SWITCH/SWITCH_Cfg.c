

/********************************************************************************
**  FILENAME     : SWITCH_Cfg.c        			                               **
**  VERSION      : 1.0                                                         **
**  DATE         : 17 Feb 2020                                                 **                                                                         **
**  PLATFORM     : STM		                                                   **
**  AUTHOR       : Nada Mohamed                                                **
*********************************************************************************/


#include "SWITCH_Cfg.h"


/******************************************************************************************************************
 * the container contain this argument
 * 	this container contain the
				     -> u32PinNumber :- Pin numbers
				               	 GPIO_PIN0
	 	 	 	 	 	 	 	 GPIO_PIN1
	 	 	 	 	 	 	 	 GPIO_PIN2
	 	 	 	 	 	 	 	 GPIO_PIN3
	 	 	 	 	 	 	 	 GPIO_PIN4
	 	 	 	 	 	 	 	 GPIO_PIN5
	 	 	 	 	 	 	 	 GPIO_PIN6
	 	 	 	 	 	 	 	 GPIO_PIN7
	 	 	 	 	 	 	 	 GPIO_PIN8
	 	 	 	 	 	 	 	 GPIO_PIN9
	 	 	 	 	 	 	 	 GPIO_PIN10
	 	 	 	 	 	 	 	 GPIO_PIN11
	 	 	 	 	 	 	 	 GPIO_PIN12
	 	 	 	 	 	 	 	 GPIO_PIN13
	 	 	 	 	 	 	 	 GPIO_PIN14
	 	 	 	 	 	 	 	 GPIO_PIN15
                     -> u32SpeedMode :- pin speed Mode
	 	 	 	 	 	 	 	 	 		GPIO_MODE_OutputMode_50MHZ       ->   11: Output mode, max speed 50 MHz
	 	 	 	 	 	 	 	 	 	 	GPIO_MODE_OutputMode_2MHZ        ->   10: Output mode, max speed 2 MHz.
	 	 	 	 	 	 	 	 	 	 	GPIO_MODE_OutputMode_10MHZ       ->   01: Output mode, max speed 10 MHz.
	 	 	 	 	 	 	 	 	 	 	GPIO_MODE_InputMode     		  ->   00: Input mode (reset state)
					-> u32ConfigurationMode :- pin Configuration mode
											In input mode (MODE[1:0]=00):
	 	 	 	 	 	 	 	 	 	 	GPIO_CNF_InputMode_Analog         ->  00: Analog mode
	 	 	 	 	 	 	 	 	 	 	GPIO_CNF_InputMode_Floating       ->  01: Floating input (reset state)
	 	 	 	 	 	 	 	 	 	 	GPIO_CNF_InputMode_Pull     	   ->  10: Input with pull-up / pull-down

											In output mode (MODE[1:0] > 00):
	 	 	 	 	 	 	 	 	 	 	GPIO_CNF_OutputMode_PushPull      ->  00: General purpose output push-pull
	 	 	 	 	 	 	 	 	 	 	GPIO_CNF_OutputMode_OpenDrain     ->  01: General purpose output Open-drain
	 	 	 	 	 	 	 	 	 	    GPIO_CNF_OutputMode_AF_PushPull   ->  10: Alternate function output Push-pull
	 	 	 	 	 	 	 	 	 	 	GPIO_CNF_OutputMode_AF_OpenDrain  ->  11: Alternate function output Open-drain

 ********************************************************************************************************************/


GPIO_t SWITCH_Configuration[] =
{
		{
				 GPIO_PIN0,
				 GPIO_CNF_InputMode_Pull,
				 GPIO_MODE_InputMode,
				 GPIOA
		},
		{
				 GPIO_PIN2,
				 GPIO_CNF_InputMode_Pull,
				 GPIO_MODE_InputMode,
				 GPIOA
		}

};

/************************************************************
 * this Function to return the container data (array of struct )
 * Return Type :-
 *            GPIO_t* ( pointer of struct GPIO_t)
 *Input Argument :-
 *             void
 *
 *************************************************************/
GPIO_t* SWITCH_u32GetSwitchConfiguration(void)
{
	return SWITCH_Configuration;
}
