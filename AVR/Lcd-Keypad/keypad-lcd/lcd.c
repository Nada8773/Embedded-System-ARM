#include "lcd.h"

void init_lcd()
{
	DDRB =(1<<RS)|(1<<R_W )|(1<<E);


 #ifdef lower_bit
	DDRD=0x0f;
 #else
	DDRD=0xf0;
 #endif

	        LCD_sendCommand(0x02);
			LCD_sendCommand(0x28);
	        LCD_sendCommand(0x01);
			LCD_sendCommand(0x0c);
}

void LCD_sendCommand(uint8 command)
{
	PORTB &=~(1<<RS);
	PORTB &=~(1<<R_W);
	_delay_ms(1);
	PORTB |=(1<<E);
	_delay_ms(1);
#ifdef lower_bit
		PORTD = (command>>4) & 0x0f;
#else
		PORTD = (command & 0xf0);
#endif

	_delay_ms(1);
	PORTB &=~(1<<E);
	_delay_ms(1);
	PORTB |=(1<<E);
		_delay_ms(1);
#ifdef lower_bit
		PORTD = command & 0x0f;
#else
		PORTD = ((command <<4) & 0xf0);
#endif
		_delay_ms(1);
		PORTB &=~(1<<E);
		_delay_ms(1);
}



void LCD_displayCharacter(uint8 data)
{
	PORTB |=(1<<RS);
	PORTB &=~(1<<R_W);
		_delay_ms(1);
		PORTB |=(1<<E);
		_delay_ms(1);

#ifdef lower_bit
		PORTD = (data>>4) & 0x0f;
#else
		PORTD = (data & 0xf0);
#endif
		_delay_ms(1);
		PORTB &=~(1<<E);
			_delay_ms(1);
			PORTB |=(1<<E);
				_delay_ms(1);
#ifdef lower_bit
		PORTD = data & 0x0f;
#else
		PORTD = ((data <<4) & 0xf0);
#endif
		_delay_ms(1);
		PORTB &=~(1<<E);
		_delay_ms(1);

}
void LCD_displayString(uint8 *str)
{
	while ((*str) !='\0')
	{
		LCD_displayCharacter(*str);
		str++;
	}
}



void LCD_intgerToString(int data)
{
	uint8 buffer[20];

	 itoa(data,buffer,10);
	 LCD_displayString(buffer);
}
