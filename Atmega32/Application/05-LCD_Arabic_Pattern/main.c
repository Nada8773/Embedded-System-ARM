/***********************************************************
 * main.c
 *
 *  Created on: Jan 21, 2020
 *      Author: Nada
 **********************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"
#include "PORT_interface.h"
#include "CLCD_interface.h"

/****************************************************************
 Description :- Display Arabic Pattern on lcd 
****************************************************************/
void main(void)
{
	 PortInitialize();
	CLCD_voidInitialize();
	CLCD_Clear();
	/* AC point to address 0 in CGRAM *'
	 */
	CLCD_voidWriteCmd(0b01000000);
	/* write 8 rows */
	CLCD_voidWriteData(0b00000001);
	CLCD_voidWriteData(0b00000001);
	CLCD_voidWriteData(0b00000001);
	CLCD_voidWriteData(0b00000001);
	CLCD_voidWriteData(0b00000001);
	CLCD_voidWriteData(0b00000001);
	CLCD_voidWriteData(0b00000000);
	CLCD_voidWriteData(0b00000000);
	/* Back to DDRAM */
	CLCD_voidGotoLocation(1,0);
	/* write pattern 0 */
	CLCD_voidWriteData(0);


	CLCD_voidWriteCmd(0b01001000);
	CLCD_voidWriteData(0b00000000);
	CLCD_voidWriteData(0b00000000);
	CLCD_voidWriteData(0b00000001);
	CLCD_voidWriteData(0b00000001);
	CLCD_voidWriteData(0b00000001);
	CLCD_voidWriteData(0b00000001);
	CLCD_voidWriteData(0b00000001);
	CLCD_voidWriteData(0b00011111);
	/* Back to DDRAM */
	/* write pattern 0 */
	CLCD_voidGotoLocation(1,1);
	CLCD_voidWriteData(1);


	    CLCD_voidWriteCmd(0b01010000);
		CLCD_voidWriteData(0b00000000);
		CLCD_voidWriteData(0b00000100);
		CLCD_voidWriteData(0b00000001);
		CLCD_voidWriteData(0b00000001);
		CLCD_voidWriteData(0b00000001);
		CLCD_voidWriteData(0b00000001);
		CLCD_voidWriteData(0b00000001);
		CLCD_voidWriteData(0b00011111);
		/* Back to DDRAM */
		/* write pattern 0 */
		CLCD_voidGotoLocation(1,2);
		CLCD_voidWriteData(2);


		/* Hamoksha */
	    CLCD_voidWriteCmd(0b01011000);

		CLCD_voidWriteData(0b00001110);
		CLCD_voidWriteData(0b00001110);
		CLCD_voidWriteData(0b00000100);
		CLCD_voidWriteData(0b00001110);
		CLCD_voidWriteData(0b00010101);
		CLCD_voidWriteData(0b00000100);
		CLCD_voidWriteData(0b00000100);
		CLCD_voidWriteData(0b00001010);
		/* Back to DDRAM */
		/* write pattern 0 */
		CLCD_voidGotoLocation(1,4);
		CLCD_voidWriteData(3);

while(1);



}

