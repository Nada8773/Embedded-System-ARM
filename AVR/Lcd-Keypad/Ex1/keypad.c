
#include "keypad.h"

unsigned char keypad()
{
	 unsigned char col,row;

	while (1)
	{
		for(col=0 ; col < number_of_colum  ; col++)
		{
			KEYPAD_PORT_DIR =  (0b00010000 << col ); /*internal pull up resistance*/
			KEYPAD_PORT_OUT = ~(0b00010000 << col );

			for (row=0 ; row < number_of_row ; row++)
			{
				if (BIT_IS_CLEAR(KEYPAD_PORT_IN,row))//switch pressed

                #if(number_of_colum==3)
				 return KeyPad_4x3((row*number_of_colum)+col+1);

                #elif(number_of_colum==4)
				 return KeyPad_4x4((row*number_of_colum)+col+1);
                #endif
			}
		}
	}
}

#if(number_of_colum==3)
unsigned char KeyPad_4x3(unsigned int number)
{
	switch(number)
	{
	case 10 :
		return '*';
		break;
	case 11 :
			return '0';
		break;
	case 12 :
			return '#';
		break;
	default :
		    return number;
	}

}
#elif(number_of_colum==4)
unsigned char KeyPad_4x4(unsigned int number)
{
	switch(number)
	{
	/*case 1 :
			return '7';
			break;
	case 2 :
			return '8';
			break;
	case 3 :
			return '9';
			break;
	case 4 :
			return '-';
			break;
	case 5 :
			return '4';
			break;
	case 6 :
			return '5';
			break;
	case 7 :
		return '6';
		break;
	case 8 :
			return '*';
		break;
	case 9 :
			return '1';
		break;
	case 10 :
				return '2';
			break;
	case 11 :
				return '3';
			break;
	case 12 :
				return '-';
			break;
	case 13 :
				return 'c';
			break;
	case 14:
		return 0;
			break;
			case 15: return '=';
					break;
			case 16: return '+';
					break;

	default :
		    return number;*/
	case 1: return 7;
					break;
			case 2: return 8;
					break;
			case 3: return 9;
					break;
			case 4: return '%'; // ASCII Code of %
					break;
			case 5: return 4;
					break;
			case 6: return 5;
					break;
			case 7: return 6;
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
			default: return number;
	}

}
#endif
