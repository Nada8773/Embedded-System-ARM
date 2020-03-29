#include "SysTick.h"


/*
1- initial systick 
     - Disable systick
		 - enable systick
		 - enable system clock
2- SysTick_wait
     - set initail value for Reload
		 - set initail value for Current
		 - wait until count flag =1 and restart again
*/

void Init_SysTick(void){	
	SysTick_CTRL =0;
	SysTick_CTRL =0x00000005;	
}

void SysTick_wait(unsigned long Delay){
	SysTick_RELOAD=Delay-1;
	SysTick_CURRENT=0;
	while((SysTick_CTRL&0x00010000)==0){} /*if COUNT in CTRL=0 the systick not count down to zero loop*/             
}

/*10ms*80000000=800000*/
//SysTick_Wait10ms(1) = 10ms
void SysTick_Wait10ms(unsigned long Delay){
	unsigned long i;
	for(i=0;i<Delay;i++){		
		SysTick_wait(delay); // wait 10ms
	}	
}