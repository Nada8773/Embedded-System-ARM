/*
 * main.c
 *
 *  Created on: Dec 19, 2019
 *      Author: Nada
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DELAY_MS_interface.h"

#include "DIO_interface.h"
#include "PORT_interface.h"
#include "SEVENSEG_interface.h"

/*****************************************************
 Description :- Display numbers from 0 to 9 
                and back to 0 again using sevensegment
*******************************************************/
void main()
{
	u8 counter=0;
	PortInitialize();
	SEVENSEG_Enable(0);

	while(1)
	{

		SEVENSEG_SetNumber(counter);
		counter++;
		if(counter>=10)
		{
			counter=0;
		}
		Delay_ms(100);

	}


}
