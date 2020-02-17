/*******************************************************************************
**  FILENAME     : LED.c         			                                  **
**  VERSION      : 1.0                                                        **
**  DATE         : 17 Feb 2020                                                **                                                                         **
**  PLATFORM     : STM		                                                  **
**  AUTHOR       : Nada Mohamed                                               **
*******************************************************************************/


#include "LED.h"
#include "GPIO.h"
#include "RCC.h"
#include "LED_Cfg.h"


/******************************************************************
 * Function To initialize LED PIN and Clock.
 * return Type :- void
 * Input Argument :- void
 *****************************************************************/
void LED_voidInit(void)
{
	RCC_EnablePeripheral_APB2(LED_ENABLE_CLOCK);

	GPIO_t* LED_Configuration= LED_u32GetLedConfiguration();

	for(u8 iterator=0;iterator<LED_CFGNUMBER;iterator++)
	{
		GPIO_voidInitPin(&LED_Configuration[iterator]);

	}
}


/******************************************************************
 * Function To put led  on
 * return Type :- void
 * Input Argument :-LED_Number
 *                  LED1
 *                  LED2
 ******************************************************************/
void LED_voidON(u8 LED_Number)
{
	GPIO_t* LED_Configuration= LED_u32GetLedConfiguration();
    GPIO_voidWritePin( SET ,&LED_Configuration[LED_Number]);
}


/******************************************************************
 * Function To put led  off
 * return Type :- void
 * Input Argument :-LED_Number
 *                  LED1
 *                  LED2
 ******************************************************************/
void LED_voidOFF(u8 LED_Number)
{
	  GPIO_t* LED_Configuration= LED_u32GetLedConfiguration();
	  GPIO_voidWritePin( RESET ,&LED_Configuration[LED_Number]);
}



