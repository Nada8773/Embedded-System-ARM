
/********************************************************************************
**  FILENAME     : SYSTICK.H         			                              **
**  VERSION      : 1.0                                                        **
**  DATE         : 16 Mar 2020                                                **                                                                         **
**  PLATFORM     : STM		                                                  **
**  AUTHOR       : Nada Mohamed                                               **
*******************************************************************************/


#ifndef SYSTICK_H_
#define SYSTICK_H_

#define SYSTICK_ENABLE                 1U
#define SYSTICK_DISABLE                0U
#define SYSTICK_INTERRUPT_ENABLE      (u32)0x00000002


#define CLOCK_PRESCALER_AHB_DIV_8     (u32)0x00000000
#define CLOCK_PRESCALER_AHB_DIV_1     (u32)0x00000004

#define CLOCK_FREQUENCY_8_MHZ         (u32)8000000UL
#define CLOCK_FREQUENCY_8_MHZ_DIV8    (u32)1000000UL

/******************************************************************
 * Function To initialize Systick
 * return Type :- void
 * Input Argument :- void
 *****************************************************************/
extern void SYSTICK_Init(void);

/******************************************************************
 * Function To start Systick
 * return Type :- void
 * Input Argument :- void
 *****************************************************************/
extern void SYSTICK_Stop(void);

/******************************************************************
 * Function To start Systick
 * return Type :- void
 * Input Argument :- void
 *****************************************************************/
extern void SYSTICK_Start(void);

/******************************************************************
 * Function To set tick time (ms)
 * return Type :- void
 * Input Argument :-
 *               TickMS :- tick time with ms
 *****************************************************************/
extern void SYSTICK_SetTimers(u32 Timers);


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
Std_ReturnType SYSTICK_SetCallBack( void(*Copy_SystickCbf_t)(void));


#endif
