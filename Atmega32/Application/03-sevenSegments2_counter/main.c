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
#include <util/delay.h>

/*******************************************************************************
 Description :- By Using 2 SevenSegment connect with same pins 
                one of them count up and the another one count down at same time
*********************************************************************************/


void main()
{

	s8 counter_Seg1_dec=9;
	s8 counter_Seg2_inc=0;
	u32 i;
	u8 flag=0;

	PortInitialize();

	while(1)
	{
		for (int j=0;j<50;j++)
						{
			            SEVENSEG_Enable(0);
						SEVENSEG_SetNumber(counter_Seg1_dec);
			             _delay_ms(7);
			             SEVENSEG_Disable(0);

						SEVENSEG_Enable(1);
						SEVENSEG_SetNumber(counter_Seg2_inc);
			             _delay_ms(7);
			             SEVENSEG_Disable(1);

						}


		counter_Seg1_dec--;
		counter_Seg2_inc++;
		 if(counter_Seg2_inc==10)counter_Seg2_inc=0;

		 if(counter_Seg1_dec<0)counter_Seg1_dec=9;



	}
}
