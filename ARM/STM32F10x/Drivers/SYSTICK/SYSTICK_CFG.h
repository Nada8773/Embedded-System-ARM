
/********************************************************************************
 **  FILENAME     : SYSTICK.H         			                              **
 **  VERSION      : 1.0                                                        **
 **  DATE         : 16 Mar 2020                                                **                                                                         **
 **  PLATFORM     : STM		                                                  **
 **  AUTHOR       : Nada Mohamed                                               **
 *******************************************************************************/


#ifndef SYSTICK_CFG_H_
#define SYSTICK_CFG_H_

/* Options
          CLOCK_PRESCALER_AHB_DIV_8
          CLOCK_PRESCALER_AHB_DIV_1
 */
#define CLOCK_PRESCALER     CLOCK_PRESCALER_AHB_DIV_1


/*
 * Options
 *       CLOCK_FREQUENCY_8_MHZ
 *       CLOCK_FREQUENCY_8_MHZ_DIV8
 */
#define CLOCK_FREQUENCY     (CLOCK_FREQUENCY_8_MHZ)


#endif
