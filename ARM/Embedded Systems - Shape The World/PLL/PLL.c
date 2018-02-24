#include "PLL.h"

/*
**Using RCC2 register that have USERCC2 bit 31
 1-Bypass PLL at bit 11
**Using RCC register that have
  Crystal Value at XTAL bit form 6-10 bits
 2-main oscillitor from 4-6 bits clear
 3-Active PLL clear PWRDN bit 13
 4-set the system divider set Div400 bit 30
 5-wait PLL to lock by polling 
 6-enable PLL by clearing Bypass2 bit 11
*/

#define SYSDIV2 7

void Init_PLL(void){
  RCC2_R |=	RCC2_USERCC2 ;
	RCC2_R |=	RCC2_BYPASS2 ;
	RCC_R  &= ~RCC_XTAL ;      //clear XTAL value
	RCC_R  |= RCC_XTAL_16MZ ; //set XTAL 16MHZ
  RCC2_R &=	~RCC2_OSCSRC2;
  RCC2_R |=	RCC2_OSCSRC2_Main ;
  RCC2_R &=	~RCC2_PWRDN2  ;
	RCC2_R |= RCC2_DIV400; 
	// bus frequency is 400MHz/(SYSDIV2+1) = 400MHz/(7+1) = 50 MHz
	RCC2_R = (RCC2_R&~0x1FC00000) + (SYSDIV2<<22); //clear SYSDIV2 and SYSDIV2 then configure for 50 MHz clock
	/*) wait for the PLL to lock by polling PLLLRIS???????*/
	while((RIS_PLLLRIS &RIS_R)==0){};
	RCC2_R &=	~RCC2_BYPASS2 ;
	}
