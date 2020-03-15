

#include "STD_TYPES.h"
#include "BIT_MATHS.h"

#include "Timer0_interface.h"
#include "Timer0_private.h"
#include "Timer0_register.h"
#include "INTGLB_interface.h"



static void (*Timer_pfunc)(void);

void TIMER0_voidInit(void)
{
	// Set mode -> normal mode
	// enable ovf int
	// enable global int
	// set preload
	// set prescaler    // last step as it start counting after put any value on 3 bits of prescalar

	SET_BIT(TIMER_TIMSK,0);
	// call global int func
	INT_voidEnableGlobal();

	 TIMER_TCNT0 = PRELOAD_VAL;
	// set prescalar ->64

	CLR_BIT(TIMER_TCCR0,2);
	SET_BIT(TIMER_TCCR0,1);
	SET_BIT(TIMER_TCCR0,0);


}

void Timer0_voidSetCallback(void(*pfunc)(void))
{
	Timer_pfunc=pfunc;

}

void __vector_11(void)
{

	static u16 Local_u16Counter;
	Local_u16Counter++;
	if (Local_u16Counter == 1000)
	{
		Timer_pfunc();
		Local_u16Counter=0;
	}
	 TIMER_TCNT0 = PRELOAD_VAL;

}
