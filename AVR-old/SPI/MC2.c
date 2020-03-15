#include "spi.h"
#include "lcd.h"

int main()
{
	 SPI_initSlave();
	 LCD_init();
	 uint8 str[20];
	 while(1)
	 	{

SPI_receiveString(str);
LCD_displayString(str);

	}

	return 0;
}
