#include "keypad.h"
uint8 KeyPad_PressedKey()
{
	uint8 col,row;
	while(1)
	{
	for(col=0 ; col<no_of_col ;col++)
	{
DDRA=(0b00010000<<col);
		PORTA=~(0b00010000<<col);
		for(row=0 ; row<no_of_row ;row++)
		{
			if (!(PINA & (1<<row)))
				return keypad_4x4((row*no_of_col)+col+1);

		}
		}
	}
}

uint8 keypad_4x4(uint8 keypad_number)
{
	switch (keypad_number)
	{
	case 1 : return 7;
					break;
	case 2 : return 8;
					break;

	case 3 : return 9;
					break;

	case 4 : return '%';
					break;
	case 5 : return 4;
					break;
	case 6 : return 5;
					break;
	case 7 : return 6;
			    	break;

	case 8: return '*'; /* ASCII Code of '*' */
					break;
			case 9: return 1;
					break;
			case 10: return 2;
					break;
			case 11: return 3;
					break;
			case 12: return '-'; /* ASCII Code of '-' */
					break;
			case 13: return 13;  /* ASCII of Enter */
					break;
			case 14: return 0;
					break;
			case 15: return '='; /* ASCII Code of '=' */
					break;
			case 16: return '+'; /* ASCII Code of '+' */
					break;
			default: return keypad_number;

}
}
