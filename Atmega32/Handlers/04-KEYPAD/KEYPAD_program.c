#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"
#include "KEYPAD_config.h"
#include "KEYPAD_interface.h"
#include "KEYPAD_private.h"


u8 KEYPAD_GetPressedKey(void)
{
	u8 Rows_Counter;
	u8 Cols_Counter;
	
	u8 Pressed_Key=KEYPAD_NO_KeyPressed;
	
	static u8 KEYPAD_COLS_PORTS_Array[KEYPAD_COLS_MaxNum] =KEYPAD_COLS_PORTS;
    static u8 KEYPAD_COLS_PINS_Array[KEYPAD_COLS_MaxNum] =KEYPAD_COLS_PINS;

	static u8 KEYPAD_ROWS_PORTS_Array[KEYPAD_ROWS_MaxNum] =KEYPAD_ROWS_PORTS;
    static u8 KEYPAD_ROWS_PINS_Array[KEYPAD_ROWS_MaxNum] =KEYPAD_ROWS_PINS;
	
	static u8 KEYPAD_KEYS_Array[KEYPAD_ROWS_MaxNum][KEYPAD_COLS_MaxNum]= KEYPAD_KEYS;
	
	for(Rows_Counter=0 ; Rows_Counter<KEYPAD_ROWS_MaxNum ; Rows_Counter++)
	{
		/* put on each ROW 0 */
		setPinValue(KEYPAD_ROWS_PORTS_Array[Rows_Counter],KEYPAD_ROWS_PINS_Array[Rows_Counter],0);
		
		/* check every Col value */
	    for(Cols_Counter=0 ; Cols_Counter<KEYPAD_COLS_MaxNum ; Cols_Counter++)
	    {
			if(!getPinValue(KEYPAD_COLS_PORTS_Array[Cols_Counter],KEYPAD_COLS_PINS_Array[Cols_Counter]))
			{
				Pressed_Key=KEYPAD_KEYS_Array[Rows_Counter][Cols_Counter];
			}
			while(!getPinValue(KEYPAD_COLS_PORTS_Array[Cols_Counter],KEYPAD_COLS_PINS_Array[Cols_Counter]));
		}
		setPinValue(KEYPAD_ROWS_PORTS_Array[Rows_Counter],KEYPAD_ROWS_PINS_Array[Rows_Counter],1);
	}
    return Pressed_Key;	
}
