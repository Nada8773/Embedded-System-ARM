
/********************************************************************************
 **  FILENAME     : LCD_Cfg.c        			                               **
 **  VERSION      : 1.0                                                         **
 **  DATE         : 23 Mar 2020                                                 **                                                                         **
 **  PLATFORM     : STM		                                                   **
 **  AUTHOR       : Nada Mohamed                                                **
 *********************************************************************************/
#include "STD_TYPES.h"
#include "GPIO.h"
#include "LCD.h"
#include "LCD_cfg.h"


/************************************************************************************
  This container contains :- Pin number  & Speed & Mode of the Pin number & PORT

    1-GPIO_PIN_Number
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

 2- GPIO_CNF :-

	In input mode (MODE[1:0]=00):
	 GPIO_CNF_InputMode_Analog         ->  00: Analog mode
	 GPIO_CNF_InputMode_Floating       ->  01: Floating input (reset state)
	 GPIO_CNF_InputMode_Pull     	   ->  10: Input with pull-up / pull-down

	In output mode (MODE[1:0] > 00):
	 GPIO_CNF_OutputMode_PushPull      ->  00: General purpose output push-pull
	 GPIO_CNF_OutputMode_OpenDrain     ->  01: General purpose output Open-drain
	 GPIO_CNF_OutputMode_AF_PushPull   ->  10: Alternate function output Push-pull
	 GPIO_CNF_OutputMode_AF_OpenDrain  ->  11: Alternate function output Open-drain



 3-GPIO_Mode
	 GPIO_MODE_OutputMode_50MHZ       ->   11: Output mode, max speed 50 MHz
	 GPIO_MODE_OutputMode_2MHZ        ->   10: Output mode, max speed 2 MHz.
	 GPIO_MODE_OutputMode_10MHZ       ->   01: Output mode, max speed 10 MHz.
	 GPIO_MODE_InputMode     		  ->   00: Input mode (reset state)
 4- GPIO port
	 GPIOA ,GPIOB ,GPIOC ,GPIOE

 */



static GPIO_t LCD_Configuration[] =
{
		{        //Data
				GPIO_PIN0|GPIO_PIN1|GPIO_PIN2|GPIO_PIN3|GPIO_PIN4|GPIO_PIN5|GPIO_PIN6|GPIO_PIN7,
				GPIO_CNF_OutputMode_PushPull,
				GPIO_MODE_OutputMode_2MHZ,
				GPIOA
		},
		{        // RS
				GPIO_PIN12,
				GPIO_CNF_OutputMode_PushPull,
				GPIO_MODE_OutputMode_2MHZ,
				GPIOB
		},
		{        // RW
				GPIO_PIN13,
				GPIO_CNF_OutputMode_PushPull,
				GPIO_MODE_OutputMode_2MHZ,
				GPIOB
		},
		{        // E
				GPIO_PIN14,
				GPIO_CNF_OutputMode_PushPull,
				GPIO_MODE_OutputMode_2MHZ,
				GPIOB
		}

};

GPIO_t* LCD_u32GetLcdConfiguration()
{
	return LCD_Configuration;
}
