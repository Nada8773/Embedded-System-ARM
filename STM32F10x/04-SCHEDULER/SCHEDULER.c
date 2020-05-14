/********************************************************************************
 **  FILENAME     : SCHEDULER.c        			                              **
 **  VERSION      : 1.4                                                        **
 **  DATE         : 19 Mar 2020                                                **                                                                         **
 **  PLATFORM     : STM		                                                  **
 **  AUTHOR       : Nada Mohamed                                               **
 *******************************************************************************/
#include "STD_TYPES.h"
#include "SCHEDULER.h"
#include "SYSTICK.h"
#include "SCHEDULER_CFG.h"

/* Private Function */
SysTaskInfo_t* SysTaskInfoFunc();
static void Schedule(void);
static void Set_OS_Flag(void);
/******************************************** SysTask Struct *************/
typedef struct
{
	SysTaskInfo_t*  TaskInfo    ;
	u32     RemainTickToExecute ;
	u32     PeriodTicks         ;
	u8      State               ;
}SysTask_t;


/****************************************** Global Variables ************/
static SysTask_t SysTasks[NUMBER_OF_TASKS];
static u8 OS_Flag;


/******************************************************************
 * Function To initialize scheduler
 * return Type :- void
 * Input Argument :- void
 *****************************************************************/
void SCHEDULE_Init(void)
{
	u32 Local_u32TaskNumber;
	SYSTICK_Init();
	SYSTICK_Stop();
	SYSTICK_SetTimers(SYSTICK_TICKMS);
	OS_Flag = 0 ;
	SYSTICK_SetCallBack(Set_OS_Flag);

	SysTaskInfo_t* SysTaskInfoFunction = SysTaskInfoFunc();
	for(Local_u32TaskNumber=0 ; Local_u32TaskNumber < NUMBER_OF_TASKS ; Local_u32TaskNumber++)
	{
		SysTasks[Local_u32TaskNumber].TaskInfo             = &SysTaskInfoFunction[Local_u32TaskNumber];
		SysTasks[Local_u32TaskNumber].RemainTickToExecute = SysTasks[Local_u32TaskNumber].TaskInfo->Priority;
		SysTasks[Local_u32TaskNumber].PeriodTicks         = (SysTasks[Local_u32TaskNumber].TaskInfo->AppTask->Periodic_TimeMS)/SYSTICK_TICKMS;
	}
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
			SysTasks[Local_u32TaskNumber].TaskInfo->AppTask->TaskRunnable();
			SysTasks[Local_u32TaskNumber].RemainTickToExecute = SysTasks[Local_u32TaskNumber].TaskInfo->Priority;
		}
		SysTasks[Local_u32TaskNumber].RemainTickToExecute--;
	}
}

/******************************************************************
 * private function to set the scheduler flag
 * return Type :- void
 * Input Argument :- void
 *****************************************************************/
static void Set_OS_Flag(void)
{
	OS_Flag = 1;
}

/******************************************************************
 * start scheduler
 * return Type :- void
 * Input Argument :- void
 *****************************************************************/
extern void SCHEDULE_Start(void)
{
	SYSTICK_Start();
	while(1)
	{
		if(OS_Flag)
		{
			OS_Flag=0;
			Schedule();
		}
	}
}



