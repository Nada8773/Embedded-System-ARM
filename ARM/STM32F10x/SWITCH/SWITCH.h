
/********************************************************************************
**  FILENAME     : SWITCH.H         			                              **
**  VERSION      : 1.0                                                        **
**  DATE         : 17 Feb 2020                                                **                                                                         **
**  PLATFORM     : STM		                                                  **
**  AUTHOR       : Nada Mohamed                                               **
*******************************************************************************/


#ifndef SWITCH_H_
#define SWITCH_H_

#include "GPIO.h"
#include "RCC.h"

/*  SWITCH_PULL -> PULL UP =0   && PULL DOWN =1   */
#define SWITCH_PULL            0U

/* For PULL UP   SWITCH_PRESSED =0 && SWITCH_NOTPRESSED =1 */
/* For PULL Down SWITCH_PRESSED =1 && SWITCH_NOTPRESSED =0 */
#define SWITCH_PRESSED         0U
#define SWITCH_NOTPRESSED      1U


/*
  RCC_APB2ENR_AFIOEN_Enable     AFIOEN: Alternate function IO clock enable
 RCC_APB2ENR_IOPAEN_PORTA       IOPAEN: IO port A clock enable
 RCC_APB2ENR_IOPBEN_PORTB       IOPBEN: IO port B clock enable
 RCC_APB2ENR_IOPCEN_PORTC       IOPCEN: IO port C clock enable
 RCC_APB2ENR_IOPDEN_PORTD       IOPDEN: IO port D clock enable
 RCC_APB2ENR_IOPEEN_PORTE       IOPEEN: IO port E clock enable
 RCC_APB2ENR_IOPFEN_PORTF       IOPFEN: IO port F clock enable
 RCC_APB2ENR_IOPGEN_PORTG       IOPGEN: IO port G clock enable
 RCC_APB2ENR_ADC1EN      	    ADC1EN: ADC 1 interface clock enable
 RCC_APB2ENR_ADC2EN      	   ADC2EN: ADC 2 interface clock enable
 RCC_APB2ENR_TIM1EN      	   TIM1EN: TIM1 timer clock enable
 RCC_APB2ENR_SPI1EN      	   TIM8EN: TIM8 Timer clock enable
 RCC_APB2ENR_TIM8EN      	   TIM8EN: TIM8 Timer clock enable
 RCC_APB2ENR_TIM9EN      	   TIM9EN: TIM9 Timer clock enable
 RCC_APB2ENR_TIM10EN     	   TIM10EN: TIM10 timer clock enable
 RCC_APB2ENR_TIM11EN    	   TIM11EN: TIM11 Timer clock enable
 RCC_APB2ENR_USARTEN     	   USART1EN: USART1 clock enable
 RCC_APB2ENR_ADC3EN      	   ADC3EN: ADC3 interface clock enable

 */
#define RCC_ENABLEGPIO        RCC_APB2ENR_IOPAEN_PORTA



#define SWITCH1               0
#define SWITCH2               1
#define SWITCH_CFGNUMBER      2  /* Number of switch configurations in the array of struct */




/*******************************************************
 * Initialize switch pins
 * Return Type :-    void
 * Input Argument :- void
 *******************************************************/
void  SWITCH_voidInit(void);

/*******************************************************************
 * Return Type :- u8
 *                SWITCH_PRESSED     -> if switch is pressed
 *                SWITCH_NOTPRESSED  -> if if switch not pressed
 *
 *Input Argument :-
 *                Copy_u8SwitchNumber :- Switch number
 *                                       switch1
 *                                       switch2
 *******************************************************************/
u8Status_Type SWITCH_voidGetState(u8 Copy_u8SwitchNumber);



#endif /* SWITCH_H_ */
