/*******************************************************************************
**  FILENAME     : LCD.h        			                                  **
**  VERSION      : 1.0                                                        **
**  DATE         : 23 Mar 2020                                                **                                                                         **
**  PLATFORM     : STM		                                                  **
**  AUTHOR       : Nada Mohamed                                               **
*******************************************************************************/

#ifndef LCD_H
#define LCD_H



#define LCD_FIRST_LINE                   1U
#define LCD_SECOND_LINE                  2U


typedef void (*APPNotifiactionCbf_t) (void);

/********** LCD COMMAND ********************/

/*****************************************
Function set:
     8 bit or 4 bit interface operation
     1 or 2 line display
     5 x 7 dot character
 *****************************************/
#define LCD_8_BIT_1_LINE   			 0x30
#define LCD_8_BIT_2_LINE   			 0x38
#define LCD_4_BIT_1_LINE   			 0x20
#define LCD_4_BIT_2_LINE   			 0x28

/* Clear Display Screen */
#define LCD_CLEAR_SCREEN   		 	 0x01

/* Cursor and Display */
#define LCD_DISPLAY_OFF_CURSOR_OFF       0x08
#define LCD_DISPLAY_ON_CURSOR_ON         0x0E
#define LCD_DISPLAY_ON_CURSOR_OFF        0x0C
#define LCD_DISPLAY_ON_CURSOR_Blinging   0x0F


/******************************************************************************
* Description   : LCD as Task (must come every 2 ms )
* ReturnType    : void
* Argument (In) : void
  Argument (Out): None
********************************************************************************/
void LCD_Task(void);

/******************************************************************************
* Description   : initliaze lcd pins
* ReturnType    : void
* Argument (In) : void
  Argument (Out): None
********************************************************************************/
void LCD_voidInit(void);

/******************************************************************************
* Description   : write string on lcd
* ReturnType
*          Std_ReturnType  (unsigned char)
			   E_OK     : Service request accepted .
			   E_NOT_OK : Service request not accepted .
			   E_BUSY   :  transmit request could not be processed because no
						   transmit object was available
  Argument (In) :
              Copy_ptStringData    -> pointer to string
              Copy_u16StringLength -> string length
  Argument (Out): None
********************************************************************************/
Std_ReturnType LCD_WriteString(const u8* Copy_ptStringData ,u16 Copy_u16StringLength);

/******************************************************************************
* Description   : clear the lcd screen
* ReturnType
*          Std_ReturnType  (unsigned char)
			   E_OK     : Service request accepted .
			   E_NOT_OK : Service request not accepted .
			   E_BUSY   :  transmit request could not be processed because no
						   transmit object was available
  Argument (In) : None
  Argument (Out): None
********************************************************************************/
Std_ReturnType LCD_ClearScreen(void);

/******************************************************************************
* Description   : to move the cursor to the location .
* ReturnType
*          Std_ReturnType  (unsigned char)
			   E_OK     : Service request accepted .
			   E_NOT_OK : Service request not accepted .
			   E_BUSY   :  transmit request could not be processed because no
						   transmit object was available
  Argument (In) :
              Copy_Line   -> lcd line
              Copy_Column -> lcd column
  Argument (Out): None
********************************************************************************/
Std_ReturnType LCD_GotoLocation(u8 Copy_Line , u8 Copy_Column);

/******************************************************************************
* Description   : call back function to handle any application function
*                 it run after
*                 1- the writing to lcd is finished.  -> LCD_WriteString() finish successfully
*                 2- move cursor                      -> LCD_GotoLocation() finish successfully
*                 3- clear screen                     -> LCD_ClearScreen()  finish successfully
* ReturnType
*          Std_ReturnType  (unsigned char)
			   E_OK     : Service request accepted .
			   E_NOT_OK : Service request not accepted .
			   E_BUSY   :  transmit request could not be processed because no
						   transmit object was available
  Argument (In) :
              Copy_Line   -> lcd line
              Copy_Column -> lcd column
  Argument (Out): None
********************************************************************************/
Std_ReturnType LCD_SetCbf(APPNotifiactionCbf_t Copy_SetCbf);


#endif
