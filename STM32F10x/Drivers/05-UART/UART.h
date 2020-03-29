
/********************************************************************************
**  FILENAME     : UART.H         			                              **
**  VERSION      : 1.0                                                        **
**  DATE         : 24 Mar 2020                                                **                                                                         **
**  PLATFORM     : STM		                                                  **
**  AUTHOR       : Nada Mohamed                                               **
*******************************************************************************/


#ifndef UART_H_
#define UART_H_

/********************* UART Peripheral ***************/
#define  BASE_ADDRESS_UART5   ((volatile u32*)0x40005000)
#define  BASE_ADDRESS_UART4   ((volatile u32*)0x40004C00)
#define  BASE_ADDRESS_USART3  ((volatile u32*)0x40004800)
#define  BASE_ADDRESS_USART2  ((volatile u32*)0x40004400)
#define  BASE_ADDRESS_USART1  ((volatile u32*)0x40013800)

#define  UART5                ((void*)BASE_ADDRESS_UART5)
#define  UART4                ((void*)BASE_ADDRESS_UART4)
#define  USART3               ((void*)BASE_ADDRESS_USART3)
#define  USART2               ((void*)BASE_ADDRESS_USART2)
#define  USART1               ((void*)BASE_ADDRESS_USART1)



/********************************* UART Configuration struct ************************/
typedef struct
{
	void* UART_Peripheral ;
	u32   UART_Buadrate   ;
	u16   UART_DataLength ;
	u32   UART_StopBits   ;
	u32   UART_Parity     ;
    u32   UART_TX_RX_Mode ;
}UART_CONFIG_t;




/******************************** UART DATA BUFFER struct ******************************/
typedef struct
{
	u8*   UART_DATABuffer ;  /* pointer to Data Buffer */
	u16   UART_DataLength ; /* the data buffer length */
	u16   UART_DataIndex  ; /* the index of the data */
    u8    UART_State      ; /* uart state */
}UART_DATABUFFER_t;



/******************** Stop Bits ***************/
#define UART_STOP_BIT_1_5           (u32)0x3000
#define UART_STOP_BIT_2             (u32)0x2000
#define UART_STOP_BIT_0_5           (u32)0x1000
#define UART_STOP_BIT_1             (u32)0x0


/****************** Enable & Disable Bit *************/
#define UART_ENABLE_BIT             (u32)0x2000

/****************** Word Length *********************/
#define UART_M_LENGTH_8             (u32)0x0
#define UART_M_LENGTH_9             (u32)0x1000

/******************* Parity Bit *********************/
#define UART_PCE_Enable_PS_EVEN     (u32)0x400
#define UART_PCE_Enable_PS_ODD      (u32)0x600
#define UART_PCE_Disable            (u32)0x0



/*********************************************************************/

#define UART_BUADRATE_9600          9600U

/*
 * fCK - Input clock to the peripheral (PCLK1 for USART2, USART3, UART4, UART5  (fPCLK = 36 MHz)
 *                                   or PCLK2 for USART1 (fPCLK = 72 MHz) )
 */
#define UART_FREQUENCY              8000000U

/******************* Enable / Disable  Receiver & trasmitter *************/
#define UART_CR1_RE_Enable          (u32)0x4
#define UART_CR1_TE_Enable          (u32)0x8
#define UART_CR1_RE_Disable         (u32)0x0
#define UART_CR1_TE_Disable         (u32)0x0



/******************************************************************************
 * Description  : initialize UART
 * ReturnType   : void
    Parameter   :
                 UART_Periphrtal -> UART5   ,UART4  ,USART3 ,USART2  ,USART1
 ********************************************************************************/
extern void UART_Init(void* UART_Periphrtal);

/******************************************************************************
 * Description  : send data through uart
 *
 * ReturnType
 *   Std_ReturnType  (unsigned char)
			   E_OK     : Service request accepted .
			   E_NOT_OK : Service request not accepted .

    Parameter (In)
              Copy_u8DataBuffer  : pointer to data buffer
              Copy_u16DataLength : Data buffer Length
 ********************************************************************************/
Std_ReturnType UART_SendData(u8* Copy_u8DataBuffer,u16 Copy_u16DataLength);

/******************************************************************************
 * Description  : recieve data Through uart
 * ReturnType
 *   Std_ReturnType  (unsigned char)
			   E_OK     : Service request accepted .
			   E_NOT_OK : Service request not accepted .

    Parameter (In)
              Copy_u16DataLength : Data buffer Length (Range From 0 to 511 )
    Parameter (Out)
              Copy_u8DataBuffer  : pointer to data buffer
 ********************************************************************************/
Std_ReturnType UART_RecieveData(u8* Copy_u8DataBuffer,u16 Copy_u16DataLength);

/******************************************************************************
 * Description  :     this function directly called back when the trasmission complete
 * ReturnType
 *   Std_ReturnType  (unsigned char)
			   E_OK     : Service request accepted .
			   E_NOT_OK : Service request not accepted .

    Parameter (In)
              Copy_APPTxNotifiactionCbf -> pointer to application function
 ********************************************************************************/
Std_ReturnType UART_SetTransmissionCbf(void(*Copy_APPTxNotifiactionCbf)(void));

/******************************************************************************
 * Description  :     this function directly called back when the receiver complete
 * ReturnType
 *   Std_ReturnType  (unsigned char)
			   E_OK     : Service request accepted .
			   E_NOT_OK : Service request not accepted .

    Parameter (In)
             Copy_APPRxNotifiactionCbf-> pointer to application function
 ********************************************************************************/
Std_ReturnType UART_SetRecieverCbf(void(*Copy_APPRxNotifiactionCbf)(void));

#endif
