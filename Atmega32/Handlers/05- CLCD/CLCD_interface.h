/**********************************************/
/* Author  : Nada Mohamed 					  */
/* Version : V01     						  */
/* Date    : 14 Jan 2020                      */
/**********************************************/

#ifndef CLCD_INTERFACE_H
#define CLCD_INTERFACE_H

#define CLCD_LINE_1   1
#define CLCD_LINE_2   2


/* Description : this API shall initialize LCD */
void CLCD_voidInitialize(void);

/* Description : this API shall display LCD */
void CLCD_voidWriteData(u8 copy_u8Data);

/* Description : this API shall execute command on LCD */
void CLCD_voidWriteCmd(u8 copy_u8Cmd);

/* Description : this API shall select the location for your display  */
void CLCD_voidGotoLocation(u8 Copy_LineNumber,u8 Copy_Postiion);

void CLCD_voidWriteString(u8* Copy_pu8String);

void CLCD_Clear();

#endif
