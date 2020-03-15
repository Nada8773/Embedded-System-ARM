#include "spi.h"

int main()
{

	SPI_initMaster();

	 SPI_sendString("I am micro1#");

	while(1)
	{

	}

	return 0;
}
