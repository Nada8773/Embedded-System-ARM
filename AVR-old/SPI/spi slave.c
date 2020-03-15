


#include "spi.h"

void SPI_initSlave()
{


	DDRB=(1<<MISO); /*output*/
	                         /*input*/
	DDRB &=~(1<<SS);
	DDRB &=~(1<<MOSI);
	DDRB &=~(1<<SCK);
	SPCR =(1<< SPE);
}

void SPI_sendByte(uint8 data)
{
	SPDR=data;
	while(BIT_IS_CLEAR(SPSR, SPIF))
	{

	}



}

uint8 SPI_receiveByte()
{
	while(BIT_IS_CLEAR(SPSR, SPIF))
	{

	}
		return SPDR;


}
void SPI_receiveString(uint8 *str)
{
	while(*str !='#')
	{
	*str=SPI_receiveByte();

	str++;
	}
	*str='\0';
}
