#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include <util/delay.h>
#include "DIO_interface.h"
#include "CLCD_config.h"
#include "CLCD_interface.h"
#include "CLCD_private.h"



/* Description : this API shall initialize LCD */
void CLCD_voidInitialize(void)
{
	_delay_ms(40);   
	CLCD_voidWriteCmd(0b00111000);
	CLCD_voidWriteCmd(0b00001100);
	CLCD_voidWriteCmd(0b00000001);
	_delay_ms(2);


}

/* Description : this API shall clear all string from lcd */
void CLCD_Clear()
{
	CLCD_voidWriteCmd(0b00000001);
}

/* Description : this API shall display LCD */
void CLCD_voidWriteData(u8 copy_u8Data)
{
	SetPinVal(CLCD_u8_RS_PORT, CLCD_u8_RS_PIN , 1);

	/* Set RW = 0 */
	SetPinVal(CLCD_u8_RW_PORT, CLCD_u8_RW_PIN , 0);

	CLCD_voidWriteDataPort(copy_u8Data);

	SetPinVal(CLCD_u8_E_PORT, CLCD_u8_E_PIN , 1);
	_delay_ms(1);
	SetPinVal(CLCD_u8_E_PORT, CLCD_u8_E_PIN , 0);
	_delay_ms(1);


}
/* Description : this API shall display LCD */
static void CLCD_voidWriteDataPort(u8 copy_u8Data)
{
	u8 Local_u8BitVal;

	Local_u8BitVal = GET_BIT(copy_u8Data,0);
	SetPinVal(CLCD_u8_DATA_PORT, CLCD_u8_D0_PIN , Local_u8BitVal);

	Local_u8BitVal = GET_BIT(copy_u8Data,1);
	SetPinVal(CLCD_u8_DATA_PORT, CLCD_u8_D1_PIN , Local_u8BitVal);

	Local_u8BitVal = GET_BIT(copy_u8Data,2);
	SetPinVal(CLCD_u8_DATA_PORT, CLCD_u8_D2_PIN , Local_u8BitVal);

	Local_u8BitVal = GET_BIT(copy_u8Data,3);
	SetPinVal(CLCD_u8_DATA_PORT, CLCD_u8_D3_PIN , Local_u8BitVal);


	Local_u8BitVal = GET_BIT(copy_u8Data,4);
	SetPinVal(CLCD_u8_DATA_PORT, CLCD_u8_D4_PIN , Local_u8BitVal);

	Local_u8BitVal = GET_BIT(copy_u8Data,5);
	SetPinVal(CLCD_u8_DATA_PORT, CLCD_u8_D5_PIN , Local_u8BitVal);

	Local_u8BitVal = GET_BIT(copy_u8Data,6);
	SetPinVal(CLCD_u8_DATA_PORT, CLCD_u8_D6_PIN , Local_u8BitVal);

	Local_u8BitVal = GET_BIT(copy_u8Data,7);
	SetPinVal(CLCD_u8_DATA_PORT, CLCD_u8_D7_PIN , Local_u8BitVal);	
}

/* Description : this API shall execute command on LCD */
void CLCD_voidWriteCmd(u8 copy_u8Cmd)
{
	SetPinVal(CLCD_u8_RS_PORT, CLCD_u8_RS_PIN , 0);

	/* Set RW = 0 */
	SetPinVal(CLCD_u8_RW_PORT, CLCD_u8_RW_PIN , 0);

	CLCD_voidWriteDataPort(copy_u8Cmd);

	SetPinVal(CLCD_u8_E_PORT, CLCD_u8_E_PIN , 1);
	_delay_ms(1);
	SetPinVal(CLCD_u8_E_PORT, CLCD_u8_E_PIN , 0);
	_delay_ms(1);
}


void CLCD_voidGotoLocation(u8 Copy_LineNumber,u8 Copy_Postiion)
{
	if(Copy_LineNumber == CLCD_LINE_1)
	{
		CLCD_voidWriteCmd(CLCD_LINE_1_CMD + Copy_Postiion);
	}
	else if(Copy_LineNumber == CLCD_LINE_2)
	{
		CLCD_voidWriteCmd(CLCD_LINE_2_CMD + Copy_Postiion);
	}
	else{}
}


void CLCD_voidWriteString(u8 *Copy_pu8String)
{
	u8 Local_u8Index=0;
	while (Copy_pu8String[Local_u8Index] != '\0')
	{
		CLCD_voidWriteData(Copy_pu8String[Local_u8Index]);
		Local_u8Index++;

	}
}





