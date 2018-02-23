#include "uart.h"

void UART_init()
{
    UCSRA=(1<<U2X);
	UCSRB=(1<<RXEN)|(1<<TXEN);
	UCSRC=(1<<UCSZ1)|(1<<UCSZ0)|(1<<URSEL);
	UBRRH = 0;
	UBRRL = 12;

}

void UART_sendByte(uint8 data)
{
	while (Bit_is_clear(UCSRA,UDRE))
		{

		}
	UDR=data ;
}


uint8 UART_recieveByte()
{
	while (Bit_is_clear(UCSRA,RXC))
	{

	}
	return UDR ;
}

void UART_sendString(uint8 *str)
{
	while (*str !='\0')
	{
		UART_sendByte(*str);
		str++;
	}
}
void UART_recieveString(uint8 *str)
{
		*str= UART_recieveByte();
		while (*str !='#')
		{
str++;
			*str= UART_recieveByte();
		}
		*str='\0';
}
