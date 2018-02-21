
#include "uart.h"
#include "lcd.h"
#define M2_READY 0x01

int main ()
{
	 uint8 num;
	 DDRC=0xff;
	 	PORTC=0;
		LCD_init();
		UART_init();

		UART_sendByte(M2_READY);
		num=UART_recieveByte();
		LCD_intgerToString(num);


		while (1)
		{

	}
	return 0;
}
