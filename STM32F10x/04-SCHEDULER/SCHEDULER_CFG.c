
/********************************************************************************
**  FILENAME     : SCHEDULER_CFG.C     			                              **
**  VERSION      : 1.5                                                        **
**  DATE         : 19 Mar 2020                                                **                                                                         **
**  PLATFORM     : STM		                                                  **
**  AUTHOR       : Nada Mohamed                                               **
*******************************************************************************/
#include "STD_TYPES.h"
#include "SCHEDULER.h"
#include "SYSTICK.h"
#include "SCHEDULER_CFG.h"

Task_t t2;
Task_t t1;
static SysTaskInfo_t SysTaskInfo[]=
	{
			{
			   &t2,
				1
			},
		{
				&t1,
				0
		}

	};


SysTaskInfo_t* SysTaskInfoFunc()
{
	return SysTaskInfo;
}
