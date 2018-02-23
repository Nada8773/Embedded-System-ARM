#include "uart.h"

int main ()
{
	uint8 str[20];
    uint8 data;
   UART_init();

	while (1){

/*data = UART_recieveByte();
UART_sendByte(data);
*/

UART_sendString(str);
UART_recieveString(str);
}
}
