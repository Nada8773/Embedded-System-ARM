/****************************************************************
 * Author  : Nada Mohamed
 * Data    : 18 Jan 2019
 * Version : v01
 *****************************************************************/

#ifndef PORT_PRIVATE_H
#define PORT_PRIVATE_H

#define Conc(b7,b6,b5,b4,b3,b2,b1,b0)          Conc_Helper(b7,b6,b5,b4,b3,b2,b1,b0)
#define Conc_Helper(b7,b6,b5,b4,b3,b2,b1,b0)   0b##b7##b6##b5##b4##b3##b2##b1##b0
#define PORTA_DIR                              Conc(PORTA_PIN7_DIR,PORTA_PIN6_DIR,PORTA_PIN5_DIR,PORTA_PIN4_DIR,PORTA_PIN3_DIR,PORTA_PIN2_DIR,PORTA_PIN1_DIR ,PORTA_PIN0_DIR)
#define PORTB_DIR                              Conc(PORTB_PIN7_DIR,PORTB_PIN6_DIR,PORTB_PIN5_DIR,PORTB_PIN4_DIR,PORTB_PIN3_DIR,PORTB_PIN2_DIR,PORTB_PIN1_DIR ,PORTB_PIN0_DIR)
#define PORTC_DIR                              Conc(PORTC_PIN7_DIR,PORTC_PIN6_DIR,PORTC_PIN5_DIR,PORTC_PIN4_DIR,PORTC_PIN3_DIR,PORTC_PIN2_DIR,PORTC_PIN1_DIR ,PORTC_PIN0_DIR)
#define PORTD_DIR                              Conc(PORTD_PIN7_DIR,PORTD_PIN6_DIR,PORTD_PIN5_DIR,PORTD_PIN4_DIR,PORTD_PIN3_DIR,PORTD_PIN2_DIR,PORTD_PIN1_DIR ,PORTD_PIN0_DIR)


#define PORTA_Initialize Conc(PORTA_PIN7_InitalValue,PORTA_PIN6_InitalValue,PORTA_PIN5_InitalValue,PORTA_PIN4_InitalValue,PORTA_PIN3_InitalValue,PORTA_PIN2_InitalValue,PORTA_PIN1_InitalValue,PORTA_PIN0_InitalValue)
#define PORTB_Initialize Conc(PORTB_PIN7_InitalValue,PORTB_PIN6_InitalValue,PORTB_PIN5_InitalValue,PORTB_PIN4_InitalValue,PORTB_PIN3_InitalValue,PORTB_PIN2_InitalValue,PORTB_PIN1_InitalValue,PORTB_PIN0_InitalValue)
#define PORTC_Initialize Conc(PORTC_PIN7_InitalValue,PORTC_PIN6_InitalValue,PORTC_PIN5_InitalValue,PORTC_PIN4_InitalValue,PORTC_PIN3_InitalValue,PORTC_PIN2_InitalValue,PORTC_PIN1_InitalValue,PORTC_PIN0_InitalValue)
#define PORTD_Initialize Conc(PORTD_PIN7_InitalValue,PORTD_PIN6_InitalValue,PORTD_PIN5_InitalValue,PORTD_PIN4_InitalValue,PORTD_PIN3_InitalValue,PORTD_PIN2_InitalValue,PORTD_PIN1_InitalValue,PORTD_PIN0_InitalValue)

#endif