#define SysTick_CTRL      (*((volatile unsigned long *)0xE000E010))
#define SysTick_RELOAD    (*((volatile unsigned long *)0xE000E014))
#define SysTick_CURRENT   (*((volatile unsigned long *)0xE000E018))

#define delay 800000      /* 10ms=count*12.5ns  */
void Init_SysTick(void);
void SysTick_wait(unsigned long Delay);
void SysTick_Wait10ms(unsigned long Delay);