

// Runs on LM4F120 or TM4C123 LaunchPad
// Input from PF4(SW1) is AS (atrial sensor), 
// Output to PF3, Green LED, is Ready,
// Output to PF1, Red LED, is VT (ventricular trigger) 
// Make PF4 input, PF3,PF1 output
// Initialize Ready to high and VT to low
// Repeat this sequence of operation over and over
// 1) Wait for AS to fall (touch SW1 switch)
// 2) Clear Ready low
// 3) Wait 10ms (debounces the switch)
// 4) Wait for AS to rise (release SW1)
// 5) Wait 250ms (simulates the time between atrial and ventricular contraction)
// 6) set VT high, which will pulse the ventricles 
// 7) Wait 250ms
// 8) clear VT low 
// 9) set Ready high

int main(void){
  TExaS_Init(SW_PIN_PF40, LED_PIN_PF31,ScopeOn);  // activate grader and set system clock to 80 MHz
  PortF_Init();                            // Init port PF4 PF3 PF1    
  EnableInterrupts();                      // enable interrupts for the grader  
  while(1){  

			// Follows the nine steps list above
   SetReady(); 
	                     	// a) Ready signal goes high
      	 WaitForASLow();		 // b) wait for switch to be pressed
ClearReady();				                       // c) Ready signal goes low
                                        // d) wait 10ms
		 Delay1ms(10);   

WaitForASHigh();
				 Delay1ms(250);        // e) wait for switch to be released
          SetVT();                // f) wait 250ms
            Delay1ms(250);
				 ClearVT();
				 SetReady();
				 // g) VT signal goes high
			              // h) wait 250ms
}                 // i) VT signal goes low
  }

// Subroutine to initialize port F pins for input and output
// PF4 is input SW1 and PF3-1 is output LEDs
// Inputs: None
// Outputs: None
// Notes: ...
void PortF_Init(void){ volatile unsigned long delay;
  SYSCTL_RCGC2_R |= 0x00000020;      // 1) F clock
  delay = SYSCTL_RCGC2_R;            // delay to allow clock to stabilize     
  GPIO_PORTF_AMSEL_R &= 0x00;        // 2) disable analog function
  GPIO_PORTF_PCTL_R &= 0x00000000;   // 3) GPIO clear bit PCTL  
  GPIO_PORTF_DIR_R &= ~0x10;         // 4.1) PF4 input,
  GPIO_PORTF_DIR_R |= 0x0E;          // 4.2) PF3,2,1 output  
  GPIO_PORTF_AFSEL_R &= 0x00;        // 5) no alternate function
  GPIO_PORTF_PUR_R |= 0x10;          // 6) enable pullup resistor on PF4       
  GPIO_PORTF_DEN_R |= 0x1E;          // 7) enable digital pins PF4-PF1
}
// Color    LED(s) PortF
// dark     ---    0
// red      R--    0x02
// blue     --B    0x04
// green    -G-    0x08
// yellow   RG-    0x0A
// sky blue -GB    0x0C
// white    RGB    0x0E


// Subroutine reads AS input and waits for signal to be low
// If AS is already low, it returns right away
// If AS is currently high, it will wait until it to go low
// Inputs:  None
// Outputs: None
void WaitForASLow(void){
// write this function
	
while((GPIO_PORTF_DATA_R&0x10));

}

// Subroutine reads AS input and waits for signal to be high
// If AS is already high, it returns right away
// If AS is currently low, it will wait until it to go high
// Inputs:  None
// Outputs: None
void WaitForASHigh(void){
// write this function
	
while(!(GPIO_PORTF_DATA_R&0x10));

}

// Subroutine sets VT high
// Inputs:  None
// Outputs: None
// Notes:   friendly means it does not affect other bits in the port
void SetVT(void){
GPIO_PORTF_DATA_R |= 0x02;


// write this function
}

// Subroutine clears VT low
// Inputs:  None
// Outputs: None
// Notes:   friendly means it does not affect other bits in the port
void ClearVT(void){
	GPIO_PORTF_DATA_R &= ~0x02;

// write this function
}

// Subroutine sets Ready high
// Inputs:  None
// Outputs: None
// Notes:   friendly means it does not affect other bits in the port
void SetReady(void){
		GPIO_PORTF_DATA_R |= 0x08;


// write this function
}


// Subroutine clears Ready low
// Inputs:  None
// Outputs: None
// Notes:   friendly means it does not affect other bits in the port
void ClearReady(void){
GPIO_PORTF_DATA_R &= ~0x08;
	
// write this function
}

// Subroutine to delay in units of milliseconds
// Inputs:  Number of milliseconds to delay
// Outputs: None
// Notes:   assumes 80 MHz clock
void Delay1ms(unsigned long msec){
	while (msec>0){
		unsigned long i=13333;
			while (i>0){
				i--;
			}
			msec--;
		}
				
// write this function

}

