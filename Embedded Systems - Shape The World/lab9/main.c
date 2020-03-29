

/* 
This Lab9 starter project is the same as C9_Debugging example but 
includes the connections to the Lab9 grader. You will make three changes. 
First, make the LED flash at 10 Hz. In other words, make it turn on for 0.05 seconds, 
and then turn off for 0.05 seconds. 
Second, make the LED flash if either switch SW1 or SW2 is pressed 
(this means flash the LED if either PF4 or PF0 is 0). 
Third, record PortF bits 4,1,0 every time the input changes or the output changes. 
For example, if your system detects a change in either PF4 or PF0 input, 
record PortF bits 4,1,0. If your system causes a change in PF1, record PortF bits 4,1,0. 

If both PF4 and PF0 switch are not pressed, the PF1 output should be low.  
If either PF4 or PF0 switches is pressed, the output toggles at 10 Hz (±10%). 
Information collected in the Data array matches the I/O on PortF.
50 data points are collected only on a change in input or a change in output.
This means no adjacent elements in the array should be equal.

*/

unsigned long SW1;
unsigned long SW2;
unsigned long   Led ;
// Initialize SysTick with busy wait running at bus clock.
void SysTick_Init(void){
  NVIC_ST_CTRL_R = 0;                   // disable SysTick during setup
  NVIC_ST_RELOAD_R = 0x00FFFFFF;        // maximum reload value
  NVIC_ST_CURRENT_R = 0;                // any write to current clears it             
  NVIC_ST_CTRL_R = 0x00000005;          // enable SysTick with core clock
}
unsigned long Led;
void Delay(void){unsigned long volatile time;
  time = 75000; // 0.03sec with 10MHZ 4cycle 
  while(time){
   time--;
  }
}
// first data point is wrong, the other 49 will be correct
unsigned long Time[50];
// you must leave the Data array defined exactly as it is
unsigned long Data[50];

int main(void){  unsigned long i,last,now;
  TExaS_Init(SW_PIN_PF40, LED_PIN_PF1);  // activate grader and set system clock to 16 MHz
  PortF_Init();   // initialize PF1 to output
  SysTick_Init(); // initialize SysTick, runs at 16 MHz
  i = 0;          // array index
  last = NVIC_ST_CURRENT_R;
  EnableInterrupts();           // enable interrupts for the grader
  while(1){
		SW1=GPIO_PORTF_DATA_R&0x10;
		SW2=GPIO_PORTF_DATA_R&0x01;
		if((SW1==0)||(SW2==0)){
    Led = GPIO_PORTF_DATA_R;   // read previous
    Led = Led^0x02;            // toggle red LED
    GPIO_PORTF_DATA_R = Led;   // output 
    if(i<50){
      now = NVIC_ST_CURRENT_R;
      Time[i] = (last-now)&0x00FFFFFF;  // 24-bit time difference
      Data[i] = GPIO_PORTF_DATA_R&0x13; // record PF1 pf0 pf4
      last = now;
      i++;
    }
    Delay();
  }
		else{
			Led = GPIO_PORTF_DATA_R&0x00; 
			GPIO_PORTF_DATA_R=Led;
		}
}
}

// Color    LED(s) PortF
// dark     ---    0
// red      R--    0x02
// blue     --B    0x04
// green    -G-    0x08
// yellow   RG-    0x0A
// sky blue -GB    0x0C
// white    RGB    0x0E
// pink     R-B    0x06
