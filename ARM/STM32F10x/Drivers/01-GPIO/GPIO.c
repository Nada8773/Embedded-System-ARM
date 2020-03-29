
/********************************************************************************
**  FILENAME     : GPIO.c         			                                  **
**  VERSION      : 1.1                                                        **
**  DATE         : 16 Feb 2020                                                 **                                                                         **
**  PLATFORM     : STM		                                                  **
**  AUTHOR       : Nada Mohamed                                               **
*******************************************************************************/


/********************************** Include header *****************/
#include "GPIO.h"


/************************* GPIO Registers **********************************/
typedef struct
{
	u32 CRL;
	u32 CRH;
	u32 IDR;
	u32 ODR;
	u32 BSRR;
	u32 BRR;
	u32 LCKR;
}GPIO_Peripheral;

/******************************** PORT **************************/

#define GPIO_PORTA_Address    ((volatile u32*)0x40010800)
#define GPIO_PORTB_Address    ((volatile u32*)0x40010C00)
#define GPIO_PORTC_Address    ((volatile u32*)0x40011000)
#define GPIO_PORTD_Address    ((volatile u32*)0x40011400)
#define GPIO_PORTE_Address    ((volatile u32*)0x40011800)
#define GPIO_PORTF_Address    ((volatile u32*)0x40011C00)
#define GPIO_PORTG_Address    ((volatile u32*)0x40012000)




#define GPIOA       (void*)GPIO_PORTA_Address
#define GPIOB       (void*)GPIO_PORTB_Address
#define GPIOC       (void*)GPIO_PORTC_Address
#define	GPIOD       (void*)GPIO_PORTD_Address
#define GPIOE       (void*)GPIO_PORTE_Address
#define	GPIOF       (void*)GPIO_PORTF_Address
#define	GPIOG       (void*)GPIO_PORTG_Address






/***************************** Masks ********************************************************************/
#define GPIO_PIN_Mask         (u32)0x0000000F
#define GPIO_RESETPIN_Mask    (u32)0x00010000
#define GPIO_SETPIN_Mask      (u32)0x00000001



#define SHIFT_NUMBER          4U
#define PIN_NUMBER            8U


/*****************************************************************************************************
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

ErrorState_ReturnType GPIO_voidInitializePin( GPIO_t* Copy_ptPeripherial)
{
	u32 Local_u32Temp=0;
	u32 Local_u32ErrorState=OK;
	u32 Local_u32Mode=0;


	if(Copy_ptPeripherial->GPIO == GPIOA || Copy_ptPeripherial->GPIO == GPIOB ||Copy_ptPeripherial->GPIO == GPIOC
			              || Copy_ptPeripherial->GPIO == GPIOD || Copy_ptPeripherial->GPIO == GPIOE
						  || Copy_ptPeripherial->GPIO == GPIOF || Copy_ptPeripherial->GPIO == GPIOG)
	{

        Local_u32Mode |= Copy_ptPeripherial->u32SpeedMode |(Copy_ptPeripherial->u32ConfigurationMode);
        Local_u32Temp=((GPIO_Peripheral*)(Copy_ptPeripherial->GPIO))->CRL;

        /* Port configuration register low from PINS 0 to 7*/
        if(Copy_ptPeripherial->u16PinNumber & CRL_PINS)
				{
        	for (u8 Copy_u8Iterator=0 ; Copy_u8Iterator <PIN_NUMBER ;Copy_u8Iterator++)
        	{
        		if((Copy_ptPeripherial->u16PinNumber>> Copy_u8Iterator) &1)
        		{
			       Local_u32Temp &= ~(GPIO_PIN_Mask   << (Copy_u8Iterator * SHIFT_NUMBER));
			       Local_u32Temp |=  (Local_u32Mode   << (Copy_u8Iterator * SHIFT_NUMBER));
			       ((GPIO_Peripheral*)(Copy_ptPeripherial->GPIO))->CRL= Local_u32Temp;

        		}
        	}
				}
        /* Port configuration register high (GPIOx_CRH) from PINS 8 to 15 */
        else if (Copy_ptPeripherial->u16PinNumber & CRH_PINS)
			{
        	for (u8 Copy_u8Iterator=0 ; Copy_u8Iterator <PIN_NUMBER ;Copy_u8Iterator++)
        	    {
        		if((Copy_ptPeripherial->u16PinNumber>> Copy_u8Iterator) &1)
        		{
			       Local_u32Temp &= ~(GPIO_PIN_Mask   << (Copy_u8Iterator * SHIFT_NUMBER));
			       Local_u32Temp |=  (Local_u32Mode   << (Copy_u8Iterator * SHIFT_NUMBER));
			       ((GPIO_Peripheral*)(Copy_ptPeripherial->GPIO))->CRH= Local_u32Temp;
        		}

        	    }
			}
		
	}
	else
	{
		Local_u32ErrorState=NOK;
		
	}

	
	return Local_u32ErrorState;
}


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

void voidGPIO_WritePin( u8Status_Type u8Copy_Status ,GPIO_t* Copy_ptPeripherial)
{

	switch(u8Copy_Status)
	{
	   case SET :
		   ((GPIO_Peripheral*)(Copy_ptPeripherial->GPIO))->BSRR = (Copy_ptPeripherial->u16PinNumber);
		break;
	   case RESET :
		   ((GPIO_Peripheral*)(Copy_ptPeripherial->GPIO))->BRR  = (Copy_ptPeripherial->u16PinNumber);
		break;

	}
}

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


PINREAD_ReturnType voidGPIO_ReadPin(GPIO_t* Copy_ptPeripherial)
{
	u16 u16Local_GetPin =0;
	u16Local_GetPin = (((GPIO_Peripheral*)(Copy_ptPeripherial->GPIO))->IDR & (u16)Copy_ptPeripherial->u16PinNumber);

  return u16Local_GetPin;
}







