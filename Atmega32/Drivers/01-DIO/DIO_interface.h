/****************************************************************
 * Author  : Nada Mohamed
 * Data    : 5 Dec 2019
 * Version : v01
 *****************************************************************/

#ifndef DIO_INTERFACE_H
#define DIO_INTERFACE_H

void SetPinVal(u8 Port,u8 Pin ,u8 Val);

void SetPinDir(u8 Port,u8 Pin ,u8 Dir);

u8 GetPinVal(u8 Port,u8 Pin);

#endif