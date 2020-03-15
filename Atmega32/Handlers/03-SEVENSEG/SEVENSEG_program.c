#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"

#include "SEVENSEG_interface.h"
#include "SEVENSEG_config.h"

#define SEVENSEGMENTS_NUMBER 2

u8 lastNumber = SEVENSEG_INITIAL_VALUE;

u8 SEVENSEG_Enable_Ports [SEVENSEGMENTS_NUMBER] = {SEVENSEGONE_ENABLE_PORT, SEVENSEGTWO_ENABLE_PORT};
u8 SEVENSEG_Enable_Pins [SEVENSEGMENTS_NUMBER] =  {SEVENSEGONE_ENABLE_PIN, SEVENSEGTWO_ENABLE_PIN};


void SEVENSEG_SetNumber(u8 number)
{
  u8 SEVEN_SEG_Numbers [10] = { 0b00111111 , 0b00000110 , 0b01011011 , 0b01001111 , 0b01100110 , 0b01101101 , 0b01111101 , 0b00000111 , 0b01111111 , 0b01101111 };
  
  /* Common Cathode */
  #if SEVENSEG_Mode == 1
  setPinValue(SEVENSEG_PORT_A, SEVENSEG_PIN_A_NUMBER, GET_BIT(SEVEN_SEG_Numbers[number],0));
  setPinValue(SEVENSEG_PORT_B, SEVENSEG_PIN_B_NUMBER, GET_BIT(SEVEN_SEG_Numbers[number],1));
  setPinValue(SEVENSEG_PORT_C, SEVENSEG_PIN_C_NUMBER, GET_BIT(SEVEN_SEG_Numbers[number],2));
  setPinValue(SEVENSEG_PORT_D, SEVENSEG_PIN_D_NUMBER, GET_BIT(SEVEN_SEG_Numbers[number],3));
  setPinValue(SEVENSEG_PORT_E, SEVENSEG_PIN_E_NUMBER, GET_BIT(SEVEN_SEG_Numbers[number],4));
  setPinValue(SEVENSEG_PORT_F, SEVENSEG_PIN_F_NUMBER, GET_BIT(SEVEN_SEG_Numbers[number],5));
  setPinValue(SEVENSEG_PORT_G, SEVENSEG_PIN_G_NUMBER, GET_BIT(SEVEN_SEG_Numbers[number],6));
  setPinValue(SEVENSEG_PORT_H, SEVENSEG_PIN_H_NUMBER, GET_BIT(SEVEN_SEG_Numbers[number],7));
  /* Common Anode */
  #elif SEVENSEG_Mode == 0
  setPinValue(SEVENSEG_PORT_A, SEVENSEG_PIN_A_NUMBER, GET_BIT(SEVEN_SEG_Numbers[number],0) ^0x01);
  setPinValue(SEVENSEG_PORT_B, SEVENSEG_PIN_B_NUMBER, GET_BIT(SEVEN_SEG_Numbers[number],1) ^0x01);
  setPinValue(SEVENSEG_PORT_C, SEVENSEG_PIN_C_NUMBER, GET_BIT(SEVEN_SEG_Numbers[number],2) ^0x01);
  setPinValue(SEVENSEG_PORT_D, SEVENSEG_PIN_D_NUMBER, GET_BIT(SEVEN_SEG_Numbers[number],3) ^0x01);
  setPinValue(SEVENSEG_PORT_E, SEVENSEG_PIN_E_NUMBER, GET_BIT(SEVEN_SEG_Numbers[number],4) ^0x01);
  setPinValue(SEVENSEG_PORT_F, SEVENSEG_PIN_F_NUMBER, GET_BIT(SEVEN_SEG_Numbers[number],5) ^0x01);
  setPinValue(SEVENSEG_PORT_G, SEVENSEG_PIN_G_NUMBER, GET_BIT(SEVEN_SEG_Numbers[number],6) ^0x01);
  setPinValue(SEVENSEG_PORT_H, SEVENSEG_PIN_H_NUMBER, GET_BIT(SEVEN_SEG_Numbers[number],7) ^0x01);
  #endif
  
  lastNumber = number;
}

void SEVENSEG_Enable(u8 SEVENSEGNumber)
{

  /* Common Cathode */
  #if SEVENSEG_Mode == 1
  setPinValue(SEVENSEG_Enable_Ports[SEVENSEGNumber], SEVENSEG_Enable_Pins[SEVENSEGNumber], 0); 
  /* Common Anode */
  #elif SEVENSEG_Mode == 0
  setPinValue(SEVENSEG_Enable_Ports[SEVENSEGNumber], SEVENSEG_Enable_Pins[SEVENSEGNumber], 1); 
  #endif
  
  SEVENSEG_SetNumber (lastNumber);
  
}

void SEVENSEG_Disable(u8 SEVENSEGNumber)
{
  /* Common Cathode */
  #if SEVENSEG_Mode == 1
  setPinValue(SEVENSEG_Enable_Ports[SEVENSEGNumber], SEVENSEG_Enable_Pins[SEVENSEGNumber], 1); 
  /* Common Anode */
  #elif SEVENSEG_Mode == 0
  setPinValue(SEVENSEG_Enable_Ports[SEVENSEGNumber], SEVENSEG_Enable_Pins[SEVENSEGNumber], 0); 
  #endif
  
}