
 /****************************************************************
 * Author  : Nada Mohamed
 * Data    : 3 Mar2020
 * Version : v01
 *****************************************************************/

#ifndef ADC_CONFIG_H
#define ADC_CONFIG_H

/* Configuration for Vref
 * 1- ADC_u8_VCC_Vref
 * 2- ADC_u8_AREF_Vref
 * 3- ADC_u8_INTERNAL_Vref*/
#define ADC_u8_VCC   ADC_u8_VCC_Vref


/* Config for prescaler*/
 /* Config for resolution
   1- ADC_u8_8BIT_RESOLUTION
   2- ADC_u8_10BIT_RESOLUTION*/
#define ADC_u8_RESOLUTION   ADC_u8_16BIT_RESOLUTION


/* Time out value */
#define ADC_u32TIMEOUT           (u32)40000



#endif

