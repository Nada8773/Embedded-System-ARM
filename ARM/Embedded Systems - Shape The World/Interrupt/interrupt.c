#define NVIC_EN0              (*((volatile unsigned long *)0xE000E100))  // IRQ 0 to 31 Set Enable Register
#define NVIC_PRI7             (*((volatile unsigned long *)0xE000E41C))  // IRQ 28 to 31 Priority Register
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



void wait_interrupt(void);
void Disable_interrupt(void);
void Enable_interrupt(void);
long StartCritical (void);    // previous I bit, disable interrupts
void EndCritical(long sr);    // restore I bit to previous value
/*
at Input falling edge trigger 
DIR   =0
AFSEL =0
IS    =0
IBE   =0
IEV   =0
*/
volatile unsigned long count = 0;
void Init_edge(){
	SYSCTL_RCGC2 =SYSCTL_RCGC2_GPIOF;
	count=0;
	GPIO_PORTF_PCTL  = 0x00000000;        
	GPIO_PORTF_AFSEL &= ~0x10;                //alternate function
	GPIO_PORTF_DEN   |=  0x10;                // Digital enable 
	GPIO_PORTF_PUR   |=  0x10;                // enable pull up at pF4
	GPIO_PORTF_DIR   &= ~0x10;	              // input at PF4
	GPIO_PORTF_AMSEL  = 0;                // analog function clear
  GPIO_PORTF_IS    &= ~0x10;                //interrupt sense
  GPIO_PORTF_IBE   &= ~0x10;               //interrupt both edge if =1 both have interrupts    
  GPIO_PORTF_IEV   &= ~0x10;               //interrup event define active edge      
  GPIO_PORTF_IM    |=  0x10;              //set the interrupt synchronization 
	GPIO_PORTF_ICR   |=  0x10;             //clear trigger flag
  NVIC_PRI7         =0x00A00000;            // set priority from 0 to 7 at bits 21,22,23  here priorty 5 
	NVIC_EN0          =0x40000000;          // enable NVIC at bit 30
  Enable_interrupt();                    //clear I-Bit                    
}
void GPIOPortF_Handler(void){
	GPIO_PORTF_ICR   |=  0x10;             //clear trigger flag
	count=count+1;	
}
int main(void){
	Init_edge();
	while(1){
		wait_interrupt();
	}	
}


