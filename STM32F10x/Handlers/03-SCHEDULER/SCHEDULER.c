/********************************************************************************
**  FILENAME     : SCHEDULER.c        			                              **
**  VERSION      : 1.1                                                        **
**  DATE         : 16 Mar 2020                                                **                                                                         **
**  PLATFORM     : STM		                                                  **
**  AUTHOR       : Nada Mohamed                                               **
*******************************************************************************/
#include "STD_TYPES.h"
#include "SYSTICK.h"
#include "SCHEDULER.h"
#include "SCHEDULER_CFG.h"

/************************* Private Function *************/
static void Schedule(void);

/**** array of struct *********/
static Task_t* SysTasks[NUMBER_OF_TASKS];


/******************************************************************
 * Function To initialize scheduler
 * return Type :- void
 * Input Argument :- void
 *****************************************************************/
void SCHEDULE_Init(void)
{
	SYSTICK_Init();
 	SYSTICK_Stop();

 	SYSTICK_SetTimers(SYSTICK_TICKMS);

 	SYSTICK_SetCallBack(Schedule);
 	SYSTICK_Start();
}

/****************************************************************************************************
 * Function callback to handle call back function
 * return Type :- return
 *                        E_OK     :- if the input argument is correct .
 *                                    (if the input pointer  is valid)
*                         E_NOT_OK :- if there's something wrong with the input argument .
*                                    (if the input pointer  is not valid)
 * Input Argument :-
 *                        Copy_AppTask (pointer to struct)
 ****************************************************************************************************/
Std_ReturnType SCHEDULE_CreateTask(Task_t* Copy_AppTask)
{
	   Std_ReturnType Local_u8Status=E_OK ;
		if(Copy_AppTask ==NULL)
		{
			Local_u8Status=E_NOT_OK;
		}
		else
		{
			SysTasks[Copy_AppTask->Priority]=Copy_AppTask;
		}
	  return Local_u8Status;
}

/******************************************************************
 * private Function used as handler to run the task
 * return Type :- void
 * Input Argument :- void
 *****************************************************************/
static void Schedule(void)
{
	static u32 Local_u32counter;
	u32 Local_u32TaskNumber;
	for(Local_u32TaskNumber=0 ; Local_u32TaskNumber < NUMBER_OF_TASKS ; Local_u32TaskNumber++)
	{
		if(Local_u32counter % (SysTasks[Local_u32TaskNumber]->Periodic_TimeMS/SYSTICK_TICKMS) ==0)
		{
			SysTasks[Local_u32TaskNumber]->TaskRunnable();
		}
		Local_u32counter++;

	}
}
