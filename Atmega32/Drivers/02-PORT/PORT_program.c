/****************************************************************
 * Author  : Nada Mohamed
 * Data    : 18 Jan 2019
 * Version : v01
 *****************************************************************/


#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "PORT_interface.h"
#include "PORT_register.h"
#include "PORT_config.h"
#include "PORT_private.h"

void PortInitialize(void)
{
	  DDRA = PORTA_DIR;
	  DDRD = PORTD_DIR;
	  DDRB = PORTB_DIR;
	  DDRC = PORTC_DIR;
	  
	  PORTA = PORTA_Initialize;
	  PORTD = PORTD_Initialize;
	  PORTB = PORTB_Initialize;
	  PORTC = PORTC_Initialize;

}

