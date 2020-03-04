#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"
#include "PORT_interface.h"
#include "DELAY_MS_interface.h"



void main(void)
{
  u8 switchState;
  
  PortInitialize();
  

  
  while(1)
  {
    switchState = getPinValue('A',0);
    
    /* Pull Up Resistor */
    if (switchState  == 0)
    {
      setLedON();
    }
    else
    {
      setLedOff();
    }
  }
  
  
}