#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DELAY_MS_interface.h"




/*
loop iteration                                 ->time1
calculations execute one instruction           -> time2
context Switch when going to execute Delay     -> time3
context Switch when return from delay function -> time4
count=(value-time2-time3-time4)/time1
*/


/* Time Mandatory =  Context Switching + Calculations Time + Return Time */
#define TM 0.009605 
/* Iteration Time */
#define T1  0.004375

void Delay_ms(u32 value)
{
  u32 i;
  u32 count = (value - TM) / T1;
  
  for (i = 0; i<count; i++) 
  {
    asm("NOP");
  }
  
}