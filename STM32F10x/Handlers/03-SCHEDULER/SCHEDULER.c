/********************************************************************************
**  FILENAME     : SCHEDULER.c        			                              **
**  VERSION      : 1.2                                                        **
**  DATE         : 19 Mar 2020                                                **                                                                         **
**  PLATFORM     : STM		                                                  **
**  AUTHOR       : Nada Mohamed                                               **
*******************************************************************************/
#include "STD_TYPES.h"
#include "SCHEDULER.h"
#include "SYSTICK.h"
#include "SCHEDULER_CFG.h"

/* Private Function */
static void Schedule(void);

/*
 * container contain
 *     Task_t*  AppTask                    ->  pointer struct Task_t
 *     (u32)    RemainTickToExecute        ->  remain tick to execute
 *
 */
typedef struct
{
	Task_t* AppTask             ;
	u32     RemainTickToExecute ;
}SysTask_t;


/* Array of struct */
static SysTask_t SysTasks[NUMBER_OF_TASKS];

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
 * private Function create scheduler task
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
	    Std_ReturnType Local_u8Status=E_OK;
		if(Copy_AppTask ==NULL)
		{
			Local_u8Status=E_NOT_OK;
		}
		else
		{
			SysTasks[Copy_AppTask->Priority].AppTask = Copy_AppTask;
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
	u32 Local_u32TaskNumber;

	for(Local_u32TaskNumber=0 ; Local_u32TaskNumber < NUMBER_OF_TASKS ; Local_u32TaskNumber++)
	{
		if(SysTasks[Local_u32TaskNumber].RemainTickToExecute == 0)
		{
			SysTasks[Local_u32TaskNumber].AppTask->TaskRunnable();
			SysTasks[Local_u32TaskNumber].RemainTickToExecute = (SysTasks[Local_u32TaskNumber].AppTask->Periodic_TimeMS)/SYSTICK_TICKMS;
		}
		SysTasks[Local_u32TaskNumber].RemainTickToExecute--;
	}
}
