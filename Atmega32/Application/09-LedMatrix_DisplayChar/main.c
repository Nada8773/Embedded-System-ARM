/************************************************
 * main.c
 *
 *  Created on: Jan 21, 2020
 *      Author: Nada
 ***********************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_interface.h"
#include "PORT_interface.h"

#include <avr/io.h>
#include <util/delay.h>

#define LED_ROWS_MaxNum  8

/*************************************************
Description :- LED Matrix 
               Display character "N"
**************************************************/
int main(void)
{

    PortInitialize();
    SetPinDir('C',0 ,1); //row
    u8 character[] =
                    {0b10000001,0b10000011,0b10000101,0b10001001,0b10010001,0b10100001,0b11000001,0b10000001};

    for(u8 i=0 ;i<8;i++)
    {
		SetPinDir('B',i ,1); //row
		SetPinDir('A',i,1);  // col
		SetPinVal('B',i,1);  //row

    }


	while(1)
	{
		for( u8 j=0;j<200;j++)
		{

			for(u8 Rows_Counter=0 ; Rows_Counter<LED_ROWS_MaxNum ; Rows_Counter++)
			{
				/* put on each ROW 0 */
				SetPinVal('B',Rows_Counter ,0); //row

				//SetPinVal('A', 0, GET_BIT(character[number],0));
				PORTA=character [ Rows_Counter];

				_delay_ms(2);
				SetPinVal('B',Rows_Counter ,1); //row
		    }
	}
	}
return 0;
}

