#include <avr/io.h>
#include <avr/interrupt.h>

void interrupt (void)
{
	SREG &=~(1<<7);
	MCUCR= (1<<ISC01)|(1<<ISC00);
	GICR |=(1<<INT0);
	SREG |=(1<<7);
}

ISR (INT0_vect)
{

	   	PORTC ^= (1<<PC0); 
}

int main (void)
{
	DDRD &=~(1<<PD2);
	DDRC |=(1<<PC0);
	PORTC |= (1<<PC0); // initialize led off
	interrupt ();
	while(1)
	{}
	return 0;
}
