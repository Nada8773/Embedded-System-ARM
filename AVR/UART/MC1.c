#include "keypad.h"
#include "uart.h"
#define M2_READY 0x01
int main ()
{
	uint8 key;
	UART_init();

	while(1)
				{
		while(UART_recieveByte() !=M2_READY )
					{

					}

		key=KeyPad_getPressedKey();

if ((key<10) &&(key>=0))


	 UART_sendByte(key);

	}
return 0;
}
