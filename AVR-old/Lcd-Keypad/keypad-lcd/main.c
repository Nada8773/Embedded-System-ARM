#include "keypad.h"
#include "lcd.h"

int main ()
{
	uint8 key;
	 init_lcd();
	LCD_displayString("Enter your Key");
	_delay_ms(400);
	 LCD_sendCommand(0x01);
	while(1)
	{
		key=KeyPad_PressedKey();
		if ((key<=9) && (key>=0))
		{
			/* PORTD = key;*/
			 LCD_intgerToString(key);
			 _delay_ms(500);
		}
		else
		{
			 LCD_displayCharacter(key);

		 _delay_ms(500);
	}
	}
}


