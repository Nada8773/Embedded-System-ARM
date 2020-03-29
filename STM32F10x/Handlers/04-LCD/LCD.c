/*******************************************************************************
 **  FILENAME     : LCD.c         			                                  **
 **  VERSION      : 1.0                                                        **
 **  DATE         : 23 Mar 2020                                                **                                                                         **
 **  PLATFORM     : STM		                                                  **
 **  AUTHOR       : Nada Mohamed                                               **
 *******************************************************************************/

/************************* Include header Files ********************/
#include "STD_TYPES.h"
#include "GPIO.h"

#include "LCD.h"
#include "LCD_cfg.h"
static APPNotifiactionCbf_t     AppNotifiactionCbf;

GPIO_t* LCD_u32GetLcdConfiguration();

/*********************** LCD State ******************************/
#define LCD_STATE                    u8
#define LCD_DISPLAY_CLEAR           (LCD_STATE)0
#define LCD_DISPLAY_FUNCTION_SET    (LCD_STATE)1
#define LCD_ONOFF_Control           (LCD_STATE)2

/********************** LCD Process ****************************/
#define LCD_PROCESS                u8
#define LCD_IDLE_PROCESS           (LCD_PROCESS)0
#define LCD_WRITE_PROCESS          (LCD_PROCESS)1
#define LCD_CLEAR_PROCESS          (LCD_PROCESS)2
#define LCD_MOVE_CURSOR_PROCESS    (LCD_PROCESS)3

/**************************************** Command **********************/
#define CLCD_LINE1_COL1_CMD        0x80
#define CLCD_LINE2_COL1_CMD        0xC0

/************************ Global Variable *************************/
static u8 LCD_gComplete_InitProcess;
static u8 LCD_gData[255];
static u8 LCD_gDataLength;
static u8 LCD_gLineNumber;
static u8 LCD_gColumnNumber;

static LCD_PROCESS LCD_CurrentProcess =LCD_IDLE_PROCESS;

/*********************** Private Functions ***********************/
static void LCD_InitProcess(void);
static void LCD_WriteProcess(void);
static void LCD_ClearProcess(void);
static void LCD_MoveCursorProcess(void);

/******************************************************************************
* Description   : initliaze lcd pins
* ReturnType    : void
* Argument (In) : void
  Argument (Out): None
********************************************************************************/
void LCD_voidInit(void)
{
	u8 Local_u8Index;
	GPIO_t* GPIO_ConfigurationLCD =LCD_u32GetLcdConfiguration();

	for(Local_u8Index=0;Local_u8Index<LCD_CONFIGPIN;Local_u8Index++)
	{
		GPIO_voidInitPin(&GPIO_ConfigurationLCD[Local_u8Index]);

	}

}



/******************************************************************************
* Description   : LCD as Task (must come every 2 ms )
* ReturnType    : void
* Argument (In) : void
  Argument (Out): None
********************************************************************************/
void LCD_Task(void)
{

	if(LCD_gComplete_InitProcess == 1)
	{

		switch(LCD_CurrentProcess)
		{
		case LCD_IDLE_PROCESS :

			break;
		case LCD_WRITE_PROCESS :
			LCD_WriteProcess();
			break;
		case LCD_CLEAR_PROCESS :
			LCD_ClearProcess();
			break;
		case LCD_MOVE_CURSOR_PROCESS :
			LCD_MoveCursorProcess();
			break;
		}
	}
	else
	{
		LCD_InitProcess();
	}
}

/******************************************************************************
 * Description  : Lcd initialize
 *
 * ReturnType
 *   Std_ReturnType  (unsigned char)
			   E_OK     : Service request accepted .
			   E_NOT_OK : Service request not accepted .

    Parameter (In)

 ********************************************************************************/
static void LCD_InitProcess(void)
{
	static LCD_STATE Local_CurrentState = LCD_DISPLAY_CLEAR;
	GPIO_t* GPIO_ConfigurationLCD =LCD_u32GetLcdConfiguration();

	switch(Local_CurrentState)
	{
	case LCD_DISPLAY_CLEAR :
		if(GPIO_ReadInputBit(&GPIO_ConfigurationLCD[LCD_E_PIN]))
		{
			Local_CurrentState = LCD_DISPLAY_FUNCTION_SET;

			/* E=0 Disable to Enable pin*/
			GPIO_voidWritePin( RESET ,&GPIO_ConfigurationLCD[LCD_E_PIN]);
		}
		else
		{
			/* RS =0  command */
			GPIO_voidWritePin( RESET ,&GPIO_ConfigurationLCD[LCD_RS_PIN]);

			/* RW =0  write to lcd */
			GPIO_voidWritePin( RESET ,&GPIO_ConfigurationLCD[LCD_RW_PIN]);

			/* Write command in lcd */
			GPIO_voidWritePort(LCD_CLEAR_SCREEN,&GPIO_ConfigurationLCD[LCD_D_PIN]);

			/* E=1 to Enable pin*/
			GPIO_voidWritePin( SET ,&GPIO_ConfigurationLCD[LCD_E_PIN]);
		}
		break;

	case LCD_DISPLAY_FUNCTION_SET :
		if(GPIO_ReadInputBit(&GPIO_ConfigurationLCD[LCD_E_PIN]))
		{
			Local_CurrentState = LCD_ONOFF_Control;

			/* E=0 Disable to Enable pin*/
			GPIO_voidWritePin( RESET ,&GPIO_ConfigurationLCD[LCD_E_PIN]);
		}
		else
		{
			/* RS =0  command */
			GPIO_voidWritePin( RESET ,&GPIO_ConfigurationLCD[LCD_RS_PIN]);

			/* RW =0  write to lcd */
			GPIO_voidWritePin( RESET ,&GPIO_ConfigurationLCD[LCD_RW_PIN]);

			/* Write command in lcd */
			GPIO_voidWritePort(LCD_FUNCTION_SET,&GPIO_ConfigurationLCD[LCD_D_PIN]);

			/* E=1 to Enable pin*/
			GPIO_voidWritePin( SET ,&GPIO_ConfigurationLCD[LCD_E_PIN]);
		}
		break;

	case LCD_ONOFF_Control :
		if(GPIO_ReadInputBit(&GPIO_ConfigurationLCD[LCD_E_PIN]))
		{
			LCD_gComplete_InitProcess = 1;
			GPIO_voidWritePin( RESET ,&GPIO_ConfigurationLCD[LCD_E_PIN]);
		}
		else
		{
			/* RS =0  command */
			GPIO_voidWritePin( RESET ,&GPIO_ConfigurationLCD[LCD_RS_PIN]);

			/* RW =0  write to lcd */
			GPIO_voidWritePin( RESET ,&GPIO_ConfigurationLCD[LCD_RW_PIN]);

			/* Write command in lcd */
			GPIO_voidWritePort(LCD_DISPLAY_CURSOR,&GPIO_ConfigurationLCD[LCD_D_PIN]);


			/* E=1 to Enable pin*/
			GPIO_voidWritePin( SET ,&GPIO_ConfigurationLCD[LCD_E_PIN]);
		}
		break;

	}

}

/******************************************************************************
 * Description  : lcd clear process
 * ReturnType   : void
   Parameter    :  void
 ********************************************************************************/
static void LCD_WriteProcess(void)
{
	static u8 Local_CurrentChar=0;
	GPIO_t* GPIO_ConfigurationLCD =LCD_u32GetLcdConfiguration();

	if(GPIO_ReadInputBit(&GPIO_ConfigurationLCD[LCD_E_PIN]))
	{
		/* E=0 Disable to Enable pin*/
		GPIO_voidWritePin( 1 ,&GPIO_ConfigurationLCD[LCD_E_PIN]);
	}
	else
	{
		if(LCD_gDataLength == Local_CurrentChar)
		{
			Local_CurrentChar =0;
			LCD_CurrentProcess =LCD_IDLE_PROCESS;
			AppNotifiactionCbf();   //Set App Call back function
		}
		else
		{
			/* RS =1  data */
			GPIO_voidWritePin(SET ,&GPIO_ConfigurationLCD[LCD_RS_PIN]);

			/* RW =0  write to lcd */
			GPIO_voidWritePin( RESET ,&GPIO_ConfigurationLCD[LCD_RW_PIN]);

			/* Write data in lcd */
			GPIO_voidWritePort(LCD_gData[Local_CurrentChar],&GPIO_ConfigurationLCD[LCD_D_PIN]);

			/* E=1 to Enable pin*/
			GPIO_voidWritePin( SET ,&GPIO_ConfigurationLCD[LCD_E_PIN]);

			Local_CurrentChar++;
		}
	}
}

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
Std_ReturnType LCD_WriteString(const u8* Copy_ptStringData ,u16 Copy_u16StringLength)
{
	u8 Local_u8Index;
	Std_ReturnType Std_LcdState = E_OK;

	if( Copy_ptStringData == NULL)
	{
		Std_LcdState = E_NOT_OK;
	}
	else
	{

		if(LCD_CurrentProcess ==LCD_IDLE_PROCESS)
		{
			LCD_CurrentProcess =LCD_WRITE_PROCESS;
			for(Local_u8Index=0 ; Local_u8Index < Copy_u16StringLength ; Local_u8Index++)
			{
				LCD_gData[Local_u8Index] =  Copy_ptStringData[Local_u8Index];
			}
			LCD_gDataLength=Copy_u16StringLength;

		}
		else
		{

			Std_LcdState = E_BUSY;
		}
	}
	return Std_LcdState;
}

/******************************************************************************
 * Description  : lcd clear process
 * ReturnType   : void
   Parameter    :  void
 ********************************************************************************/
static void LCD_ClearProcess(void)
{
	GPIO_t* GPIO_ConfigurationLCD =LCD_u32GetLcdConfiguration();

	/* Write command in lcd */
	//GPIO_voidWritePort(LCD_CLEAR_SCREEN,&GPIO_ConfigurationLCD[LCD_D_PIN]);
	//LCD_CurrentProcess =LCD_IDLE_PROCESS;
	//AppNotifiactionCbf();   //Set App Call back function
	if(GPIO_ReadInputBit(&GPIO_ConfigurationLCD[LCD_E_PIN]))
	{
		LCD_CurrentProcess =LCD_IDLE_PROCESS;
		/* E=0 Disable to Enable pin*/
		GPIO_voidWritePin( RESET ,&GPIO_ConfigurationLCD[LCD_E_PIN]);
		AppNotifiactionCbf();
	}
	else
	{
		/* RS =0  command */
		GPIO_voidWritePin( RESET ,&GPIO_ConfigurationLCD[LCD_RS_PIN]);

		/* RW =0  write to lcd */
		GPIO_voidWritePin( RESET ,&GPIO_ConfigurationLCD[LCD_RW_PIN]);

		/* Write command in lcd */
		GPIO_voidWritePort(LCD_CLEAR_SCREEN,&GPIO_ConfigurationLCD[LCD_D_PIN]);

		/* E=1 to Enable pin*/
		GPIO_voidWritePin( SET ,&GPIO_ConfigurationLCD[LCD_E_PIN]);
	}

}

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
Std_ReturnType LCD_ClearScreen(void)
{
	Std_ReturnType Std_LcdState = E_OK;

	if(LCD_CurrentProcess ==LCD_IDLE_PROCESS)
	{
		LCD_CurrentProcess =LCD_CLEAR_PROCESS;
	}
	else
	{
		Std_LcdState = E_BUSY;
	}

	return Std_LcdState;
}

/******************************************************************************
 * Description  : lcd clear process
 * ReturnType   : void
   Parameter    :  void
 ********************************************************************************/
static void LCD_MoveCursorProcess(void)
{
	GPIO_t* GPIO_ConfigurationLCD =LCD_u32GetLcdConfiguration();


	if(GPIO_ReadInputBit(&GPIO_ConfigurationLCD[LCD_E_PIN]))
	{
		LCD_CurrentProcess = LCD_IDLE_PROCESS;
		/* E=0 Disable to Enable pin*/
		GPIO_voidWritePin( RESET ,&GPIO_ConfigurationLCD[LCD_E_PIN]);
		AppNotifiactionCbf();   //Set App Call back function
	}
	else
	{
		/* RS =0  command */
		GPIO_voidWritePin( RESET ,&GPIO_ConfigurationLCD[LCD_RS_PIN]);

		/* RW =0  write to lcd */
		GPIO_voidWritePin( RESET ,&GPIO_ConfigurationLCD[LCD_RW_PIN]);

		if (LCD_gLineNumber == LCD_FIRST_LINE)
		{
			/* Write command in lcd */
			GPIO_voidWritePort(CLCD_LINE1_COL1_CMD + LCD_gColumnNumber ,&GPIO_ConfigurationLCD[LCD_D_PIN]);
		}
		else if( LCD_gLineNumber == LCD_SECOND_LINE)
		{
			/* Write command in lcd */
			GPIO_voidWritePort(CLCD_LINE2_COL1_CMD + LCD_gColumnNumber ,&GPIO_ConfigurationLCD[LCD_D_PIN]);
		}

		/* E=1 to Enable pin*/
		GPIO_voidWritePin( SET ,&GPIO_ConfigurationLCD[LCD_E_PIN]);

	}
}

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
Std_ReturnType LCD_GotoLocation(u8 Copy_LineNumber , u8 Copy_ColumnNumber)
{
	Std_ReturnType Std_LcdState = E_OK;

	if(LCD_CurrentProcess ==LCD_IDLE_PROCESS)
	{
		LCD_gLineNumber    = Copy_LineNumber;
		LCD_gColumnNumber  = Copy_ColumnNumber;
		LCD_CurrentProcess = LCD_MOVE_CURSOR_PROCESS;
	}
	else
	{
		Std_LcdState = E_BUSY;
	}

	return Std_LcdState;
}


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
Std_ReturnType LCD_SetCbf(APPNotifiactionCbf_t Copy_SetCbf)
{
	Std_ReturnType Local_u8Status=E_OK ;
	if(Copy_SetCbf==NULL)
	{
		Local_u8Status=E_NOT_OK;
	}
	else
	{
		AppNotifiactionCbf  = Copy_SetCbf;
	}
	return Local_u8Status;
}


