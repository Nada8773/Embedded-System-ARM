#include "STD_TYPES.h"

#include "BIT_MATHS.h"
#include "INTGLB_interface.h"
#include "INTGLB_register.h"


void INT_voidEnableGlobal(void)
{
  SET_BIT(SREG,SREG_I);
}
void INT_voidDisableGlobal(void)
{
  CLR_BIT(SREG,SREG_I);
}
  
  
  
