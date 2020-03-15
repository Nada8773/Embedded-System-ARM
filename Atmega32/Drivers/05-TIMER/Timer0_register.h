
#ifndef TIMER0_REGISTER_H_
#define TIMER0_REGISTER_H_





#define TIMER_TCCR0 	*((volatile u8*)0x53)
#define TIMER_TCNT0 	*((volatile u8*)0x52)
#define TIMER_TIMSK 	*((volatile u8*)0x59)
#define TIMER_TIFR 		*((volatile u8*)0x58)



#endif /* TIMER0_REGISTER_H_ */
