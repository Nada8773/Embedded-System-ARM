/**
 * @file  UART.h
 * @brief This file is to be used as an implementation of the UART driver.
 *
 * @author MSN
 * @date Mar 31, 2020
 *
 */

#ifndef UART_H_
#define UART_H_


typedef struct
{
	u8    UART_Peripheral ;
	u32   UART_Buadrate   ;
	u16   UART_DataLength ;
	u32   UART_StopBits   ;
	u32   UART_Parity     ;
    u32   UART_TX_RX_Mode ;
}UART_CONFIG_t;


typedef struct
{
	u8*   UART_DATABuffer ;
	u16   UART_DataLength ;
	u16   UART_DataIndex  ;
    u8    UART_State      ;
}UART_DATABUFFER_t;



#define UART_STOP_BIT_1_5           (u32)0x3000
#define UART_STOP_BIT_2             (u32)0x2000
#define UART_STOP_BIT_0_5           (u32)0x1000
#define UART_STOP_BIT_1             (u32)0x0

#define UART_ENABLE_BIT             (u32)0x2000

#define UART_M_LENGTH_8             (u32)0x0
#define UART_M_LENGTH_9             (u32)0x1000

#define UART_PCE_Enable_PS_EVEN     (u32)0x400
#define UART_PCE_Enable_PS_ODD      (u32)0x600
#define UART_PCE_Disable            (u32)0x0

#define UART_BUADRATE_9600          9600U
#define UART_BUADRATE_115200        115200U
#define UART_FREQUENCY              8000000U

#define UART_CR1_RE_Enable          (u32)0x4
#define UART_CR1_TE_Enable          (u32)0x8
#define UART_CR1_RE_Disable         (u32)0x0
#define UART_CR1_TE_Disable         (u32)0x0

#define UART5_Peripherial         4U
#define UART4_Peripherial         3U
#define USART3_Peripherial        2U
#define USART2_Peripherial        1U
#define USART1_Peripherial        0U


#define UART_DMA          0U
#define UART_INTERRUPT    1U

/**
 * @brief Initialize UART
 * @param void
 * @return void
 */
extern void UART_Init(void);


/**
 * @brief Send data through UART
 * @param Copy_u8DataBuffer: pointer to data buffer
 * @param Copy_u16DataLength:  Data buffer Length
 * @param Copy_u8UARTPeripherail: \n
 *        UART5_Peripherial \n
			 UART4_Peripherial \n
			 USART3_Peripherial \n
			 USART2_Peripherial \n
			 USART1_Peripherial
 * @return void
 */
Std_ReturnType UART_SendData(u8* Copy_u8DataBuffer,u16 Copy_u16DataLength, u8 Copy_u8UARTPeripherail);


/**
 *
 * @param Copy_u8DataBuffer: pointer to data buffer
 * @param Copy_u16DataLength: Data buffer Length (Range From 0 to 511)
 * @param Copy_u8UARTPeripherail: \n
 *        UART5_Peripherial \n
			 UART4_Peripherial \n
			 USART3_Peripherial \n
			 USART2_Peripherial \n
			 USART1_Peripherial
 * @return Std_ReturnType \n
			  E_OK     : Service request accepted . \n
			  E_NOT_OK : Service request not accepted .
 */
Std_ReturnType UART_RecieveData(u8* Copy_u8DataBuffer,u16 Copy_u16DataLength, u8 Copy_u8UARTPeripherail);


 /**
  * @brief This function directly called back when the transmission complete
  * @param Copy_APPTxNotifiactionCbf: pointer to application function
  * @return Std_ReturnType \n
 			   E_OK     : Service request accepted . \n
 			   E_NOT_OK : Service request not accepted .
  *
  */
Std_ReturnType UART_SetTransmissionCbf(void(*Copy_APPTxNotifiactionCbf)(void));


/**
 * @brief This function directly called back when the receiver complete
 * @param Copy_APPRxNotifiactionCbf: pointer to application function
 * @return Std_ReturnType \n
			  E_OK     : Service request accepted . \n
			  E_NOT_OK : Service request not accepted .
 */
Std_ReturnType UART_SetRecieverCbf(void(*Copy_APPRxNotifiactionCbf)(void));


#endif
