/****************************************************************
 Author  : Nada Mohamed 
Data    : 22 Apr 2020
 Version : v01 
****************************************************************/ 
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"
#include "SPI_interface.h"
#include "STK_interface.h"

#include <Nokia_config.h>
#include <Nokia_interface.h>
#include <Nokia_private.h>
#include <Nokia_register.h>

void Nokia_voidInit(void)
{
    /*reset pulse */
	DIO_SetPinVal('A',2 ,1);
	STK_voidBusyDelay(2000);  /* 2ms */

	DIO_SetPinVal('A',2 ,0);
	STK_voidBusyDelay(2000);  /* 2ms */

	DIO_SetPinVal('A',2 ,1);

	/************ Extend Mode */
	/* PD -> 0
	 * Horizontal v=0  ->
	 * H=1
	 */
	Write_Cmd(0b00100001);

	/*
	 * curve 2 temp room
	 */
	Write_Cmd(0b00000110);

	/* Biase 4 level*/
	Write_Cmd(0b000010011);

	/* Sw Potin  BF*/
	Write_Cmd(0xBE);

	/*********** Normal Mode */
	Write_Cmd(0b00100000);

	Write_Cmd(0b00001100);


}
void Noka_voidDisplay(u8* Copy_DataArray)
{
  u16 i;
  /* y=0*/
    Write_Cmd(0b01000000);

    /* x=0 */
  	Write_Cmd(0b10000000);

	for(i=0 ; i<504;i++)
	{
		Write_Data(Copy_DataArray[i]);
	}
}


static void Write_Data(u8 Copy_u8Data)
{
	/* Clear CE PIN */
	DIO_SetPinVal('A',3 ,0);

	/* DC =1 for data */
	DIO_SetPinVal('A',1 ,1);

	/* Send Data */
	SPI1_u8SendSynch(Copy_u8Data);

	/*Set CE PIN */
	DIO_SetPinVal('A',3 ,1);

}
static void Write_Cmd(u8 Copy_u8Cmd)
{
	/* Clear CE PIN */
	DIO_SetPinVal('A',3 ,0);

	/* DC =0 for data */
	DIO_SetPinVal('A',1 ,0);

	/* Send Data */
	SPI1_u8SendSynch(Copy_u8Cmd);

	/*Set CE PIN */
	DIO_SetPinVal('A',3 ,1);

}
