
#include "spi.h"

void SPI_initMaster()
{

	DDRB|=(1<<MOSI)|(1<<SS)|(1<<SCK); /*output */
	DDRB &=(~(1<<MISO)); /*input*/


		SPCR =(1<<MSTR)|(1<< SPE);
}


void SPI_sendByte(uint8 data)
{
	SPDR=data;
	while(BIT_IS_CLEAR(SPSR, SPIF))
	{

	}
}
void SPI_sendString(uint8 *str)

{
	while (*str !='\0')
	{
		SPI_sendByte(*str);
		str++;

	}


}

uint8 SPI_receiveByte()
{
	while(BIT_IS_CLEAR(SPSR, SPIF))
	{

	}
		return SPDR;
}


