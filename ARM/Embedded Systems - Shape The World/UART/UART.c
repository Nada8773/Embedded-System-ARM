#include "UART.h"
/*
1- Active UART
2- Active port
3- Disable UART
4- Baud rate value 
             IBRD = int(50,000,000 / (16 * 115,200)) = int(27.1267)
             FBRD = int(0.1267 * 64 + 0.5) = 8
                                        
5- number of bits of data and enable FIFO from UARTLCRH Register
6- enable alt funct on PA1-0
7- enable digital I/O on PA1-0 
8- enable alt funct on PA1-0
9- disable analog functionality on PA
*/
void Init_UART(void){
	SYSCTL_RCGC1 |= SYSCTL_RCGC1_UART0;  
  SYSCTL_RCGC2 |= SYSCTL_RCGC2_GPIOA; 
  UARTCTL &= ~UARTCTL_UARTEN;        
  UARTIBRD = 27;   
  UARTFBRD= 8;
  UARTLCRH= (UARTLCRH_WLEN_8|UARTLCRH_FEN);
  UARTCTL |= UARTCTL_UARTEN;       
	
  PORTA_AFSEL |= 0x03;           
  PORTA_DEN   |= 0x03;                                                     
  PORTA_PCTL   = 0x11;//(PORTA_PCTL&0xFFFFFF00)+0x00000011;
  PORTA_AMSEL &= ~0x03; 
}	



void UART_sendByte(unsigned char Data){
  while ((UARTFR & UARTFR_TXFF)  !=0);
  UARTDR=Data;
}



unsigned char UART_recieveByte(void){
	while ((UARTFR & UARTFR_RXFE)  !=0);
	return(UARTDR);
}



void UART_sendString(char *str){
	while(*str)
	{
		UART_sendByte(*str);
		str++;
	}
}
	


void UART_recieveString(char *str){
	*str= UART_recieveByte();
		while (*str !='#')
		{
			str++;
			*str= UART_recieveByte();
		}
		*str='\0';
	}
