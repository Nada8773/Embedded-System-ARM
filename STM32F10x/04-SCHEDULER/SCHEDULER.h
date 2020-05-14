
/********************************************************************************
**  FILENAME     : SCHEDULER.H         			                              **
**  VERSION      : 1.5                                                       **
**  DATE         : 19 Mar 2020                                                **                                                                         **
**  PLATFORM     : STM		                                                  **
**  AUTHOR       : Nada Mohamed                                               **
*******************************************************************************/


#ifndef SCHEDULER_H_
#define SCHEDULER_H_

typedef void (*TaskRunnable_t)(void);

/*
 * container contain
 *     TaskRunnable_t -> task to run
 *     (u32)          -> Periodic time in ms
 */
typedef struct
{
	TaskRunnable_t    TaskRunnable;
	u32               Periodic_TimeMS;
}Task_t;


/*
 * container contain
 *     AppTask        ->pointer to Task_t struct
 *     (u32)          -> Periodic time in ms
 *     (u32)          -> priority of the task
 */
typedef struct
{
   const Task_t* const AppTask;
   u32   Priority;
}SysTaskInfo_t;

extern Task_t t2;
extern Task_t t1;


/******************************************************************
 * Function To initialize scheduler
 * return Type :- void
 * Input Argument :- void
 *****************************************************************/
void SCHEDULE_Init(void);


/******************************************************************
 * start scheduler
 * return Type :- void
 * Input Argument :- void
 *****************************************************************/
extern void SCHEDULE_Start(void);


#endif
