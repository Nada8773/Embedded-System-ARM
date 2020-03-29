/*******************************************************************************
**  FILENAME     : LCD._cfg.c        			                                  **
**  VERSION      : 1.0                                                        **
**  DATE         : 23 Mar 2020                                                **                                                                         **
**  PLATFORM     : STM		                                                  **
**  AUTHOR       : Nada Mohamed                                               **
*******************************************************************************/


#ifndef LCD_CFG_H
#define LCD_CFG_H



#define LCD_CONFIGPIN   5


#define LCD_D_PIN    0U
#define LCD_RS_PIN   1U
#define LCD_RW_PIN   2U
#define LCD_E_PIN    3U

/* Options :
 *   LCD_FIST_LINE
 *   LCD_SECOND_LINE
 */
#define LCD_LINE     LCD_FIRST_LINE

/* Options : from 0 to 15 */
#define LCD_CoLumn   5U

/*******************************/
/* Options :
		 LCD_8_BIT_1_LINE
		 LCD_8_BIT_2_LINE
		 LCD_4_BIT_1_LINE
		 LCD_4_BIT_2_LINE
********************************/
#define LCD_FUNCTION_SET   LCD_8_BIT_2_LINE

/******************************/
/* Options :
         LCD_DISPLAY_OFF_CURSOR_OFF
         LCD_DISPLAY_ON_CURSOR_ON
         LCD_DISPLAY_ON_CURSOR_OFF
         LCD_DISPLAY_ON_CURSOR_Blinging
*********************************/
#define LCD_DISPLAY_CURSOR  LCD_DISPLAY_ON_CURSOR_OFF


#endif
