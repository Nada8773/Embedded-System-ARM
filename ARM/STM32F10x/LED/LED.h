

/********************************************************************************
**  FILENAME     : LED.h        			                                  **
**  VERSION      : 1.0                                                        **
**  DATE         : 17 Feb 2020                                                **                                                                         **
**  PLATFORM     : STM		                                                  **
**  AUTHOR       : Nada Mohamed                                               **
*******************************************************************************/

#ifndef LED_H
#define LED_H

#include "GPIO.h"
#include "RCC.h"

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
#define LED_ENABLE_CLOCK        RCC_APB2ENR_IOPAEN_PORTA


#define LED1          			0
#define LED2                    1
#define LED_CFGNUMBER           2






/******************************************************************
 * Function To initialize LED PIN and Clock.
 * return Type :- void
 * Input Argument :- void
 *****************************************************************/
void LED_voidInit(void);

/******************************************************************
 * Function Put led on
 * return Type :- void
 * Input Argument :- u8
 *                   LED number
 *                   LED1
 *                   LED2
 ******************************************************************/
void LED_voidON(u8 LED_Number);

/******************************************************************
 * Function Put led off
 * return Type :- void
 * Input Argument :- (u8)LED Number
 *                   LED1
 *                   LED2
 ******************************************************************/
void LED_voidOFF(u8 LED_Number);

#endif
