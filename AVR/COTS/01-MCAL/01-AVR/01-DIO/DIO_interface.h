/***************************************
*	Author  : Nada Mohamed 
*	Version : v01
****************************************/


#ifndef DIO_INTERFACE_H
#define DIO_INTERFACE_H


#define DIO_u8_PIN0
#define DIO_u8_PIN1
#define DIO_u8_PIN2
#define DIO_u8_PIN3
#define DIO_u8_PIN4
#define DIO_u8_PIN5
#define DIO_u8_PIN6
#define DIO_u8_PIN7
#define DIO_u8_PIN8
#define DIO_u8_PIN9
#define DIO_u8_PIN10
#define DIO_u8_PIN11
#define DIO_u8_PIN12
#define DIO_u8_PIN13
#define DIO_u8_PIN14

#define DIO_u8_PIN15
#define DIO_u8_PIN16
#define DIO_u8_PIN17
#define DIO_u8_PIN18
#define DIO_u8_PIN19
#define DIO_u8_PIN20
#define DIO_u8_PIN21
#define DIO_u8_PIN22
#define DIO_u8_PIN23
#define DIO_u8_PIN24
#define DIO_u8_PIN25
#define DIO_u8_PIN26
#define DIO_u8_PIN27
#define DIO_u8_PIN28
#define DIO_u8_PIN29
#define DIO_u8_PIN30
#define DIO_u8_PIN31

void SetPinVal(u8 Port,u8 Pin ,u8 Val);

void SetPinDir(u8 Port,u8 Pin ,u8 Dir);

u8 GetPinVal(u8 Port,u8 Pin);
void DIO_SetPinVal(u8 Copy_u8Pin,u8 Copy_u8Val);
#endif
