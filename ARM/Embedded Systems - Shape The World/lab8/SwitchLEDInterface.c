

// ***** 3. Subroutines Section *****

// PE0, PB0, or PA2 connected to positive logic momentary switch using 10k ohm pull down resistor
// PE1, PB1, or PA3 connected to positive logic LED through 470 ohm current limiting resistor
// To avoid damaging your hardware, ensure that your circuits match the schematic
// shown in Lab8_artist.sch (PCB Artist schematic file) or 
// Lab8_artist.pdf (compatible with many various readers like Adobe Acrobat).

	unsigned long LED;
unsigned long SW;
	void delayms(void);
void PortE_Init(void);

int main(void){ 
	PortE_Init();
//**********************************************************************
// The following version tests input on PE0 and output on PE1
//**********************************************************************
  TExaS_Init(SW_PIN_PE0, LED_PIN_PE1, ScopeOn);  // activate grader and set system clock to 80 MHz
  EnableInterrupts();  
		
 //LED on 	

  while(1){
SW=GPIO_PORTE_DATA_R&0x01;
		LED=GPIO_PORTE_DATA_R|0x02;
if(SW==0x01){
	GPIO_PORTE_DATA_R^=0x02;
				 delayms();
	
}else{ 
GPIO_PORTE_DATA_R|=0x02;  // the sw isn't pressed the LED on 

  }
}
	}
	void delayms(void){
 unsigned long i;
  
    i = 1333333;  // this number means 100ms
    while(i > 0){
      i = i - 1;
    }
   
}
	void PortE_Init(void){ volatile unsigned long delay;
SYSCTL_RCGC2_R |= 0x10;           // 1) E clock
delay = SYSCTL_RCGC2_R;             
GPIO_PORTE_AMSEL_R &= ~0x03; 
GPIO_PORTE_PCTL_R &= ~0x000000FF;
GPIO_PORTE_DIR_R &= ~0x01; 
GPIO_PORTE_DIR_R |= 0x02;
GPIO_PORTE_AFSEL_R &= ~0x03; 
GPIO_PORTE_DEN_R |= 0x03; 
}


