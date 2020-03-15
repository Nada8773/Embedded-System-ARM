/**************************************************
 * main.c
 *
 *  Created on: Dec 24, 2019
 *      Author: Nada
 **************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"
#include "PORT_interface.h"
#include "SEVENSEG_interface.h"
#include "KEYPAD_interface.h"
#include "KEYPAD_config.h"

/******************************************************************
 Description :- take input from keypad then display the number  
                on the sevensegment
******************************************************************/

void main(void)
{
	PortInitialize();
	SEVENSEG_Enable(0);
	u8 Get_Key;
	while(1)
	{
	  Get_Key=KEYPAD_GetPressedKey();
      if( Get_Key != KEYPAD_NO_KeyPressed)
        {
    	  SEVENSEG_SetNumber(Get_Key);
        }
	}


}
