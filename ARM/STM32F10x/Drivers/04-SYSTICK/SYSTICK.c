/********************************************************************************
**  FILENAME     : SYSTICK.C         			                              **
**  VERSION      : 1.1                                                        **
**  DATE         : 16 Mar 2020                                                **                                                                         **
**  PLATFORM     : STM		                                                  **
**  AUTHOR       : Nada Mohamed                                               **
*******************************************************************************/

#include "STD_TYPES.h"
#include "SYSTICK.h"
#include "SYSTICK_CFG.h"

/********************* Global variable ***************************/
static void(*GSystickCbf_t)(void);

/********************************* MASKS *************************/
#define SYSTICK_ENABLE_MASK        (u32)0xFFFFFFFE
#define SYSTICK_Clock_MASK         (u32)0xFFFFFFF9

/***************************************** SYSTICK Registers ****************/
#define BASE_Address_SYSTICK (u32)0xE000E010

typedef struct
{
	u32 STK_CTRL;
	u32 STK_LOAD;
	u32 STK_VAL;
	u32 STK_CALIB;
}SYSTICK_Reg;

volatile SYSTICK_Reg*   const   SYSTICK_t    = (SYSTICK_Reg*)BASE_Address_SYSTICK;

/******************************************************************
 * Function To initialize Systick
 * return Type :- void
 * Input Argument :- void
 *****************************************************************/
extern void SYSTICK_Init(void)
{
	SYSTICK_t->STK_CTRL &=SYSTICK_Clock_MASK;
	SYSTICK_t->STK_CTRL |=CLOCK_PRESCALER|SYSTICK_INTERRUPT_ENABLE;
}


/******************************************************************
 * Function To stop Systick
 * return Type :- void
 * Input Argument :- void
 *****************************************************************/
extern void SYSTICK_Stop(void)
{
	SYSTICK_t->STK_CTRL &= SYSTICK_ENABLE_MASK;
	SYSTICK_t->STK_CTRL |= SYSTICK_DISABLE ;
}

/******************************************************************
 * Function To start Systick
 * return Type :- void
 * Input Argument :- void
 *****************************************************************/
extern void SYSTICK_Start(void)
{
	SYSTICK_t->STK_CTRL &= SYSTICK_ENABLE_MASK;
	SYSTICK_t->STK_CTRL |= SYSTICK_ENABLE ;
}

/******************************************************************
 * Function To set tick time (ms)
 * return Type :- void
 * Input Argument :-
 *               TickMS :- tick time with ms
 *****************************************************************/
extern void SYSTICK_SetTimers(u32 TickMS)
{
	SYSTICK_t->STK_LOAD =((CLOCK_FREQUENCY * TickMS)/1000)-1;;
	SYSTICK_t->STK_VAL=0;
}


/****************************************************************************************************
 * Function callback to handle call back function
 * return Type :- return
 *                        E_OK     :- if the input argument is correct .
 *                                    (if the input pointer to function is valid)
*                         E_NOT_OK :- if there's something wrong with the input argument .
*                                    (if the input pointer to function is not valid)
 * Input Argument :-
 *                        Copy_SystickCbf_t (pointer to function)
 ****************************************************************************************************/
Std_ReturnType SYSTICK_SetCallBack( void(*Copy_SystickCbf_t)(void))
{
	 Std_ReturnType Local_u8Status=E_OK ;
	if(Copy_SystickCbf_t ==NULL)
	{
		Local_u8Status=E_NOT_OK;
	}
	else
	{
		GSystickCbf_t=Copy_SystickCbf_t;
	}
  return Local_u8Status;
}


/****************************************************************************
 * Systick handler to call the notification function
 * return Type :-
 *                void
 * Input Argument :-
 *                void
 *****************************************************************************/
void SysTick_Handler(void)
{
	GSystickCbf_t();
}



