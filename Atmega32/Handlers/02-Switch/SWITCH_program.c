#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"

#include "SWITCH_interface.h"
#include "SWITCH_config.h"

u8 getSwitchState(void)
{
  u8 state;
  state = getPinValue(SWITCH_Port,SWITCH_Pin);
  
  #if RELEASE_STATE == 1
      TOGGLE_BIT(state,0);
  #endif 
    
  return state;
    
}