

 /****************************************************************
 * Author  : Nada Mohamed
 * Data    : 26 Feb 2020
 * Version : v01
 *****************************************************************/


#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"
#include "PORT_interface.h"
#include "CLCD_interface.h"

#include "ADC_interface.h"
#include "Temp.h"
#include <util/delay.h>
#include <string.h>

/*********************************************************************
 Description :- read temperature 
                if Temp less than 20  green led on
				   Temp less than 40  yellow led on and fan is opened
				   Temp more then or equal 40  red led on and open alarm
***********************************************************************/
int main()
{
	 PortInitialize();
	 CLCD_voidInitialize();
	 ADC_voidInit();

	 u16 Local_u16Temp;

	 u8 buffer[20];



	CLCD_Clear();
	CLCD_voidWriteString("Temp = ");




	while(1)
	{
		CLCD_voidGotoLocation(2,5);
		Local_u16Temp= Temp();

		CLCD_voidWriteString(itoa(Local_u16Temp,buffer,10));

		if(Local_u16Temp <20)
		{
			SetPinVal('B',0 ,1); //green led
			SetPinVal('B',1 ,0);
			SetPinVal('B',2 ,0);
			SetPinVal('B',3 ,0);
			SetPinVal('B',4 ,0);

		}
		else if(Local_u16Temp <40)
		{
			SetPinVal('B',0 ,0);
			SetPinVal('B',1 ,1); // yellow led
			SetPinVal('B',2 ,0);
			SetPinVal('B',3 ,1); // motor
			SetPinVal('B',4 ,0);

		}

		else if(Local_u16Temp >=40)
		{
			SetPinVal('B',0 ,0);
			SetPinVal('B',1 ,0);
			SetPinVal('B',2 ,1); //red
			SetPinVal('B',3 ,0);
			SetPinVal('B',4 ,1); // buzzer
		}

	}


	return 0;
}
