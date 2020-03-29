/*
toggle LED at PF2 every 1 ms 
*/
#define NVIC_EN0              (*((volatile unsigned long *)0xE000E100))  // IRQ 0 to 31 Set Enable Register
#define NVIC_PRI3             (*((volatile unsigned long *)0xE000ED20))  // IRQ 28 to 31 Priority Register
#define GPIO_PORTF_DATA       (*((volatile unsigned long *)0x400253FC))
#define GPIO_PORTF_DIR        (*((volatile unsigned long *)0x40025400))
#define GPIO_PORTF_IS         (*((volatile unsigned long *)0x40025404))
#define GPIO_PORTF_IBE        (*((volatile unsigned long *)0x40025408))
#define GPIO_PORTF_IEV        (*((volatile unsigned long *)0x4002540C))
#define GPIO_PORTF_IM         (*((volatile unsigned long *)0x40025410))
#define GPIO_PORTF_RIS        (*((volatile unsigned long *)0x40025414))
#define GPIO_PORTF_ICR        (*((volatile unsigned long *)0x4002541C))
#define GPIO_PORTF_AFSEL      (*((volatile unsigned long *)0x40025420))
#define GPIO_PORTF_PUR        (*((volatile unsigned long *)0x40025510))
#define GPIO_PORTF_PDR        (*((volatile unsigned long *)0x40025514))
#define GPIO_PORTF_DEN        (*((volatile unsigned long *)0x4002551C))
#define GPIO_PORTF_AMSEL      (*((volatile unsigned long *)0x40025528))
#define GPIO_PORTF_PCTL       (*((volatile unsigned long *)0x4002552C))	
#define SYSCTL_RCGC2          (*((volatile unsigned long *)0x400FE108))
#define SYSCTL_RCGC2_GPIOF    0x00000020  // port F Clock Gating Control
#define SysTick_CTRL          (*((volatile unsigned long *)0xE000E010))
#define SysTick_RELOAD        (*((volatile unsigned long *)0xE000E014))
#define SysTick_CURRENT       (*((volatile unsigned long *)0xE000E018))
	


void wait_interrupt(void);
void Disable_interrupt(void);
void Enable_interrupt(void);


//out at PF4 
void Init_PortF(){
	SYSCTL_RCGC2 |=SYSCTL_RCGC2_GPIOF; // activate port F
	GPIO_PORTF_PCTL  = 0x00000000;        
	GPIO_PORTF_AFSEL &= ~0x04;                //alternate function for PF4
	GPIO_PORTF_DEN   |=  0x04;                // Digital enable for PF4
	GPIO_PORTF_DIR   |=  0x04;	              // out at PF4
	GPIO_PORTF_AMSEL  = 0;                    // analog function clear
}
void init_systick(unsigned long Delay){
	SysTick_CTRL =0; //Disable Systick
	SysTick_RELOAD=Delay-1;
	SysTick_CURRENT=0;
  NVIC_PRI3 = 0x40000000; // priority 2                             
  SysTick_CTRL = 0x07; // Set  En_systick & INTEN & SRC & 
  Enable_interrupt();            
}

void SysTick_Handler(void){
	GPIO_PORTF_DATA ^=  0x04;             //toggle led at PF2 every 1ms
}
/*
count*timeClk=require time  16 MHZ
count * 62.5ns = 1ms
Delay=16000
*/


int main(void){
	
	Init_PortF();
	init_systick(16000);        // initialize SysTick timer
	Enable_interrupt();        //clear I-Bit                    
	while(1){
		wait_interrupt();
	}	
}


