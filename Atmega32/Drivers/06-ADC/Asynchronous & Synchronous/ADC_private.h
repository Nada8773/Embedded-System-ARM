
 /****************************************************************
 * Author  : Nada Mohamed
 * Data    : 3 Mar 2020
 * Version : v01
 *****************************************************************/

#ifndef ADC_PRIVATE_H
#define ADC_PRIVATE_H

/* ADMUX macros */
#define ADC_ADMUX_MUX0             0
#define ADC_ADMUX_MUX1             1
#define ADC_ADMUX_MUX2             2
#define ADC_ADMUX_MUX3             3
#define ADC_ADMUX_MUX4             4
#define ADC_ADMUX_ADLAR            5
#define ADC_ADMUX_REFS0            6
#define ADC_ADMUX_REFS1            7


/* ADCSRA macros */
#define ADC_ADCSRA_ADPS0           0
#define ADC_ADCSRA_ADPS1           1
#define ADC_ADCSRA_ADPS2           2
#define ADC_ADCSRA_ADIE            3
#define ADC_ADCSRA_ADIF            4
#define ADC_ADCSRA_ADATE           5
#define ADC_ADCSRA_ADSC            6
#define ADC_ADCSRA_ADEN            7


/* Reslotion macros */
#define ADC_u8_8BIT_RESOLUTION     1
#define ADC_u8_10BIT_RESOLUTION    2


#define  ADC_u8_STATE_IDLE         1
#define  ADC_u8_STATE_BUSY         2

#define ADC_u8_SINGLE_CONVERSION   1
#define ADC_u8_CHAIN_CONVERSION    2

#endif
