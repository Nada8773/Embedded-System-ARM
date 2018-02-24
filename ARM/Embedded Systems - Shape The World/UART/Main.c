
#include "UART.h"
#include "PLL.h" /* Active the PLL  */

int main (void){
	unsigned char i;
	//char string[20]; 
	Init_PLL();
	Init_UART();	
	for(i='A'; i<='Z'; i=i+1)
	{
    UART_sendByte(i);
  }
}
	
	 /*while(1)
		 {
    UART_sendString("InString: ");
    UART_recieveString(string);
		 
    UART_sendString("OutString=");
		 UART_recieveString(string); 
     }
	 }*/
	
