
#include "keypad.h"

int main ()
{
	unsigned char  keypad_number;
	DDRC |=0x0f;
	PORTC=0;

	while (1)
	{
		keypad_number= keypad();
if ((keypad_number >= 0) && (keypad_number <= 9))
PORTC=keypad_number;
	}
	return 0;
}

