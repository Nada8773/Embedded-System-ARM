

/********************************************************************************
**  FILENAME     : GPIO.c         			                                  **
**  VERSION      : 1.0                                                        **
**  DATE         : 6 Feb 2020                                                 **                                                                         **
**  PLATFORM     : STM		                                                  **
**  AUTHOR       : Nada Mohamed                                               **                                     **
*******************************************************************************/

#ifndef GPIO_H_
#define GPIO_H_
#include "STD_TYPE.h"


typedef u32                    ErrorState_ReturnType;
typedef u16                     PINREAD_ReturnType;
typedef u8                      u8Status_Type;



/**************************** GPIO_CRL & GPIO_CRH  Register ******/

#define GPIO_CNF_InputMode_Analog      			 (u32)0x0
#define GPIO_CNF_InputMode_Floating      		 (u32)0x4
#define GPIO_CNF_InputMode_Pull     			 (u32)0x8
#define GPIO_CNF_OutputMode_PushPull     		 (u32)0x00000000
#define GPIO_CNF_OutputMode_OpenDrain      		 (u32)0x4
#define GPIO_CNF_OutputMode_AF_PushPull      	 (u32)0x8
#define GPIO_CNF_OutputMode_AF_OpenDrain     	 (u32)0xc

#define GPIO_MODE_OutputMode_50MHZ     			 (u32)0x3
#define GPIO_MODE_OutputMode_2MHZ      			 (u32)0x00000002
#define GPIO_MODE_OutputMode_10MHZ     			 (u32)0x1
#define GPIO_MODE_InputMode     				 (u32)0x0





/************************* PIN  Number *****************************/
#define GPIO_PIN0        (u16)1
#define GPIO_PIN1        (u16)2
#define GPIO_PIN2        (u16)4
#define GPIO_PIN3        (u16)8
#define GPIO_PIN4        (u16)10
#define GPIO_PIN5        (u16)20
#define GPIO_PIN6        (u16)40
#define GPIO_PIN7        (u16)80
#define GPIO_PIN8        (u16)100
#define GPIO_PIN9        (u16)200
#define GPIO_PIN10       (u16)400
#define GPIO_PIN11       (u16)800
#define GPIO_PIN12       (u16)1000
#define GPIO_PIN13       (u16)2000
#define GPIO_PIN14       (u16)4000
#define GPIO_PIN15       (u16)8000



#define CRL_PINS  0x00FF
#define CRH_PINS  0xFF00



#define NOK    (ErrorState_ReturnType)0
#define OK     (ErrorState_ReturnType)1
#define SET     (u8Status_Type)0
#define RESET   (u8Status_Type)1






/************************************************************************************
  This container contains :- Pin number  & Speed & Mode of the Pin number & PORT

    2-GPIO_PIN_Number
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

 3- GPIO_CNF :-

	In input mode (MODE[1:0]=00):
	 GPIO_CNF_InputMode_Analog         ->  00: Analog mode
	 GPIO_CNF_InputMode_Floating       ->  01: Floating input (reset state)
	 GPIO_CNF_InputMode_Pull     	   ->  10: Input with pull-up / pull-down

	In output mode (MODE[1:0] > 00):
	 GPIO_CNF_OutputMode_PushPull      ->  00: General purpose output push-pull
	 GPIO_CNF_OutputMode_OpenDrain     ->  01: General purpose output Open-drain
	 GPIO_CNF_OutputMode_AF_PushPull   ->  10: Alternate function output Push-pull
	 GPIO_CNF_OutputMode_AF_OpenDrain  ->  11: Alternate function output Open-drain



 4-GPIO_Mode
	 GPIO_MODE_OutputMode_50MHZ       ->   11: Output mode, max speed 50 MHz
	 GPIO_MODE_OutputMode_2MHZ        ->   10: Output mode, max speed 2 MHz.
	 GPIO_MODE_OutputMode_10MHZ       ->   01: Output mode, max speed 10 MHz.
	 GPIO_MODE_InputMode     		  ->   00: Input mode (reset state)
 */

/**************************************************************************************/
typedef struct
{
	u16 u16PinNumber;
	u32 u32SpeedMode;
	u32 u32ConfigurationMode;
	void* GPIO;
}GPIO_t;

/*
 *Return Type    :- return OK  :- if the port is correct .
*                   return NOK :- if the port not correct.
 *Input Argument :-
		1-u8Copy_Status	:-
			   		SET   -> Set the corresponding ODRx bit
			   		RESET -> Reset the corresponding ODRx bit
		2-Copy_ptPeripherial :-
				    this container contain the
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


*************************************************************************************************/

ErrorState_ReturnType voidGPIO_InitializePin( GPIO_t* Copy_ptPeripherial);

/*************************************************************************************
 *Return Type    :-
                  void
 *Input Argument :-
		1-u8Copy_Status	:-
			   		SET   -> Set the corresponding ODRx bit
			   		RESET -> Reset the corresponding ODRx bit
		2-Copy_ptPeripherial :-
				    this container contain the
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


*************************************************************************************************/
void voidGPIO_WritePin( u8Status_Type u8Copy_Status ,GPIO_t* Copy_ptPeripherial);


/***************************************************************************************************/
/*  Return Type :-  PINREAD_ReturnType (u16)
 *                  return the pin value
  *Input Argument :-
		1-u8Copy_Status	:-
			   		SET   -> Set the corresponding ODRx bit
			   		RESET -> Reset the corresponding ODRx bit
		2-Copy_ptPeripherial :-
				    this container contain the
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


*************************************************************************************************/
PINREAD_ReturnType voidGPIO_ReadPin(GPIO_t* Copy_ptPeripherial);



#endif /* GPIO_H_ */
