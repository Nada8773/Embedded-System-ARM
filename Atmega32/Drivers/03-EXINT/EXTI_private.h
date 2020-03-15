
#ifndef EXTI_PRIVATE_H_
#define EXTI_PRIVATE_H_


#define ENABLED     1
#define DISABLED    2       


#define LOW_LEVEL       1
#define ON_CHANGE       2
#define FALLING_EDGE    3
#define RISING_EDGE     4

void __vector_1 (void) __attribute__((signal));
void __vector_2 (void) __attribute__((signal));
void __vector_3 (void) __attribute__((signal));

#endif
