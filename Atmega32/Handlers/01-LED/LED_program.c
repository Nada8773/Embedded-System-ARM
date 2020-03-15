#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"

#include "LED_interface.h"
#include "LED_config.h"



void setLedON (void)
{
  setPinValue(LED_Port,LED_Pin,LED_Mode);
}


void setLedOff (void)
{
  /* Toggle Bit */
  setPinValue(LED_Port,LED_Pin, LED_Mode ^ 0x01);
}