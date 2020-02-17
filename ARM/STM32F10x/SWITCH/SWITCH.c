
/********************************************************************************
**  FILENAME     : SWITCH.c        			                                  **
**  VERSION      : 1.0                                                        **
**  DATE         : 8 Feb 2020                                                 **                                                                         **
**  PLATFORM     : STM		                                                  **
**  AUTHOR       : Nada Mohamed                                               **
*******************************************************************************/

#include "SWITCH.h"
#include "SWITCH_Cfg.h"



/*******************************************************
 * Initialize switch pins
 * Return Type :-    void
 * Input Argument :- void
 *******************************************************/
void  SWITCH_voidInit(void)
{

	RCC_EnablePeripheral_APB2(RCC_ENABLEGPIO);

	GPIO_t* SWITCH_Configuration= SWITCH_u32GetSwitchConfiguration();

		for(u8 iterator=0;iterator<SWITCH_CFGNUMBER;iterator++)
		{
			GPIO_voidInitPin(&SWITCH_Configuration[iterator]);

		   #if SWITCH_PULL==1 // pull down
		     GPIO_voidWritePin( RESET ,&SWITCH_Configuration[iterator]);
		   #else
		     GPIO_voidWritePin( SET ,&SWITCH_Configuration[iterator]);
           #endif
		}
}


/**********************************************************************
 * Return Type :- u8
 *                SWITCH_PRESSED     -> if switch is pressed
 *                SWITCH_NOTPRESSED  -> if if switch not pressed
 *
 *Input Argument :-
 *                Copy_u8SwitchNumber :- Switch number
 *                                       switch1
 *                                       switch2
 **********************************************************************/
u8Status_Type SWITCH_voidGetState(u8 Copy_u8SwitchNumber)
{
   u8 Local_u8GetPinState;
	GPIO_t* SWITCH_Configuration= SWITCH_u32GetSwitchConfiguration();

   Local_u8GetPinState = GPIO_voidReadPin(&SWITCH_Configuration[Copy_u8SwitchNumber]);

   #if SWITCH_PULL==1 // pull down
   Local_u8GetPinState = Local_u8GetPinState ^ 1;
   #endif

   return Local_u8GetPinState;

}
