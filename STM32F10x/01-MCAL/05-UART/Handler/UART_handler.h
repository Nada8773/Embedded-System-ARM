/**
 * @file  LCD.h
 * @brief This file is to be used as an implementation of the UART handler
 *
 * @author MSN
 * @date Mar 31, 2020
 *
 */

#ifndef UART_HANDLER_H_
#define UART_HANDLER_H_


#define UART5_Peripherial         4U
#define UART4_Peripherial         3U
#define USART3_Peripherial        2U
#define USART2_Peripherial        1U
#define USART1_Peripherial        0U

void HUART_InitGPIO(void);
void HUART_EnableIRQ(void);
void HUART_DMAEnableIRQ(void);
void HUART_Init(void);
Std_ReturnType HUART_RecieveData(u8* Copy_u8DataBuffer,u16 Copy_u16DataLength, u8 Copy_u8UARTPeripherail);
Std_ReturnType HUART_SendData(u8* Copy_u8DataBuffer,u16 Copy_u16DataLength, u8 Copy_u8UARTPeripherail);
Std_ReturnType HUART_SetTransmissionCbf(void(*Copy_APPTxNotifiactionCbf)(void));
Std_ReturnType HUART_SetRecieverCbf(void(*Copy_APPRxNotifiactionCbf)(void));




#endif
