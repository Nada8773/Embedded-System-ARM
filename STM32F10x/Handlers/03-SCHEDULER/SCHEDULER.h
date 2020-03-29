
/********************************************************************************
**  FILENAME     : SCHEDULER.H         			                              **
**  VERSION      : 1.2                                                       **
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
 *     (u32)          -> priority of the task
 */
typedef struct
{
	TaskRunnable_t    TaskRunnable;
	u32               Periodic_TimeMS;
	u32               Priority ;
}Task_t;


/******************************************************************
 * Function To initialize scheduler
 * return Type :- void
 * Input Argument :- void
 *****************************************************************/
void SCHEDULE_Init(void);

/****************************************************************************************************
 * Function create scheduler task
 * return Type :- return
 *                        E_OK     :- if the input argument is correct .
 *                                    (if the input pointer  is valid)
*                         E_NOT_OK :- if there's something wrong with the input argument .
*                                    (if the input pointer  is not valid)
 * Input Argument :-
 *                        Copy_AppTask (pointer to struct)
 ****************************************************************************************************/
Std_ReturnType SCHEDULE_CreateTask(Task_t* Copy_AppTask);


#endif
