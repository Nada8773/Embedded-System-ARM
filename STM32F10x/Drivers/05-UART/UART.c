
#include "STD_TYPES.h"
#include "UART.h"
#include "UART_cfg.h"
#include "NVIC.h"
/************************** Register **************/
typedef struct
{
	u32 SR  ;
	u32 DR  ;
	u32 BRR ;
	u32 CR1 ;
	u32 CR2 ;
	u32 CR3 ;
	u32 GTPR;
}UART_Reg;


/*************************** Call back function ************/
static void(*APPTxNotifiactionCbf_t)(void);
static void(*APPRxNotifiactionCbf_t)(void);

/*************************** Global Variable ***************/
static volatile UART_Reg*             UARTX_g;
static volatile UART_CONFIG_t        UART_CONFIG;
static volatile UART_DATABUFFER_t    UART_TXBuffer ;
static volatile UART_DATABUFFER_t    UART_RXBuffer ;


/********************************** Macros *****************/
#define UART_MAX_DATALENGTH        511U

/************************* ******* STATE **************************/
#define UART_STATE_IDLE           (u8)0
#define UART_STATE_BUSY           (u8)1


/********************************** Masks *****************/
#define UART_STOP_BIT_MASK        (u32)0xffffcfff
#define UART_UE_BIT_MASK          (u32)0xffffdfff
#define UART_M_MASK               (u32)0xffffefff
#define UART_PCE_PS_MASK          (u32)0xfffff9ff

#define UART_SR_TXE               (u32)0x80
#define UART_SR_TXE_MASK          (u32)0xffffff7f

#define UART_SR_TC               (u32)0x40
#define UART_SR_TC_MASK          (u32)0xffffffbf

#define UART_SR_RXNE              (u32)0x20
#define UART_SR_RXNE_MASK         (u32)0xffffffdf

#define UART_CR1_RE_TE_MASK       (u32)0xfffffff3

#define UART_BRR_DIVFRACTION      (u32)0x0000000f
#define UART_BRR_DIVMANTISSA      (u32)0x0000fff0


#define UART_CR1_RXNEIE_MASK      (u32)0xffffffdf
#define UART_CR1_RXNEIE           (u32)0x20

#define UART_CR1_TXEIE_MASK      (u32)0xffffff7f
#define UART_CR1_TXEIE           (u32)0x80

#define UART_CR1_TCIE_MASK      (u32)0xffffffbf
#define UART_CR1_TCIE           (u32)0x40


/******************************************************************************
 * Description  : initialize UART
 * ReturnType   : void
    Parameter   :
                 UART_Periphrtal -> UART5   ,UART4  ,USART3 ,USART2  ,USART1
 ********************************************************************************/
extern void UART_Init(void* UART_Periphrtal)
{

	u32 Local_u32Temp =0 ;
	f64 Local_f64BaudrateCounter ;
	u8  Local_u8BaudrateMantissa ;
	f32 Local_f32BaudrateFraction ;


	UART_CONFIG.UART_Peripheral   = (UART_Reg*)UART_Periphrtal;
	UART_CONFIG.UART_Buadrate     = UART_BUADRATE ;
	UART_CONFIG.UART_DataLength   = UART_WORD_LENGTH ;
	UART_CONFIG.UART_StopBits     = UART_STOP_BIT ;
	UART_CONFIG.UART_Parity       = UART_PAIRTY_BIT ;
	UART_CONFIG.UART_TX_RX_Mode   = UART_CR1_RE | UART_CR1_TE ;

	UARTX_g = UART_CONFIG.UART_Peripheral ;

	/* Default Data Configuration */
	UART_TXBuffer.UART_DATABuffer = NULL;
	UART_TXBuffer.UART_DataIndex  = 0   ;
	UART_TXBuffer.UART_DataLength = 0   ;
	UART_TXBuffer.UART_State      =  UART_STATE_IDLE ;

	UART_RXBuffer.UART_DATABuffer = NULL;
	UART_RXBuffer.UART_DataIndex  = 0   ;
	UART_RXBuffer.UART_DataLength = 0   ;
	UART_RXBuffer.UART_State      =  UART_STATE_IDLE ;


	/* Enable UART */
	UARTX_g->CR1 &= UART_UE_BIT_MASK ;
	UARTX_g->CR1 |= UART_ENABLE_BIT  ;

	/* enable TX & RX */
	UARTX_g->CR1 &= UART_CR1_RE_TE_MASK ;
	UARTX_g->CR1 |= UART_CONFIG.UART_TX_RX_Mode ;

	/* word Length */
	UARTX_g->CR1 &= UART_M_MASK ;
	UARTX_g->CR1 |=  UART_CONFIG.UART_DataLength;

	/* Parity Selection */
	UARTX_g->CR1 &= UART_PCE_PS_MASK;
	UARTX_g->CR1 |= UART_CONFIG.UART_Parity ;

	/* Stop Bit */
	UARTX_g->CR2 &= UART_STOP_BIT_MASK ;
	UARTX_g->CR2 |= UART_CONFIG.UART_StopBits ;

	/* Baud Rate counter
	          Tx/ Rx baud =fCK /(16*USARTDIV)
	         USARTDIV = fck / (16 *baud) */

	Local_f64BaudrateCounter   = (UART_FREQUENCY /( UART_CONFIG.UART_Buadrate * 16 )) ;
	Local_u8BaudrateMantissa   = Local_f64BaudrateCounter ;
	Local_f32BaudrateFraction  = Local_f64BaudrateCounter - (u32)Local_u8BaudrateMantissa ;
	Local_f32BaudrateFraction  = Local_f32BaudrateFraction *16 ;

	Local_u32Temp = UARTX_g->BRR ;
	Local_u32Temp |= ((Local_u8BaudrateMantissa<<4) & UART_BRR_DIVMANTISSA) | ((u32)Local_f32BaudrateFraction & UART_BRR_DIVFRACTION) ;
	UARTX_g->BRR   = Local_u32Temp;

	/* Enable interrupt */
	UARTX_g->CR1 &= UART_CR1_RXNEIE_MASK;
	UARTX_g->CR1 |= UART_CR1_RXNEIE;    // UART Receive Interrupt Enable.

	UARTX_g->CR1 &= UART_CR1_TCIE_MASK;
	UARTX_g->CR1 |= UART_CR1_TCIE;      // UART transmit Interrupt Enable.

	NVIC_ClearPendingIRQ(USART1_IRQNUMBER);
	NVIC_SetPriorityGrouping(3);
	/* Set priority levels */
	NVIC_SetPriority(USART1_IRQNUMBER, 1);
	NVIC_EnableIRQ(USART1_IRQNUMBER);
	NVIC_EnableAllInterrupt();
}





/******************************************************************************
 * Description  :
 *
 * ReturnType
 *   Std_ReturnType  (unsigned char)
			   E_OK     : Service request accepted .
			   E_NOT_OK : Service request not accepted .

    Parameter (In)

 ********************************************************************************/
void USART1_IRQHandler(void)
{
	u32 Local_u32Temp=0;

	/*  Transmit data is sent. */
	if( UARTX_g->SR  & UART_SR_TC )
	{
		/* CLEAR TC */
		Local_u32Temp =  UARTX_g->SR          ;
		Local_u32Temp &= UART_SR_TC_MASK ;
		UARTX_g->SR   =  Local_u32Temp     ;

		/* Transmission is not complete */
		if(UART_TXBuffer.UART_DataLength != UART_TXBuffer.UART_DataIndex)
		{
			UARTX_g->DR = UART_TXBuffer.UART_DATABuffer[UART_TXBuffer.UART_DataIndex];
			UART_TXBuffer.UART_DataIndex++ ;
		}
		else // Transmission is complete (buffer is finished)
		{
			UART_TXBuffer.UART_DATABuffer = NULL;
			UART_TXBuffer.UART_DataIndex  = 0   ;
			UART_TXBuffer.UART_DataLength = 0   ;
			UART_TXBuffer.UART_State      =  UART_STATE_IDLE ;
			APPTxNotifiactionCbf_t();
		}
	}



	/*  Received data is ready to be read. */
	if( UARTX_g->SR  & UART_SR_RXNE )
	{
		/* CLEAR RXNE */
		Local_u32Temp =  UARTX_g->SR       ;
		Local_u32Temp &= UART_SR_RXNE_MASK ;
		UARTX_g->SR   =  Local_u32Temp     ;

		if( UART_RXBuffer.UART_State == UART_STATE_BUSY )
		{
			UART_RXBuffer.UART_DATABuffer[ UART_RXBuffer.UART_DataIndex] = UARTX_g->DR ;
			UART_RXBuffer.UART_DataIndex++;
			if( UART_RXBuffer.UART_DataIndex ==  UART_RXBuffer.UART_DataLength)
			{
				UART_RXBuffer.UART_DATABuffer = NULL;
				UART_RXBuffer.UART_DataIndex  = 0   ;
				UART_RXBuffer.UART_DataLength = 0   ;
				UART_RXBuffer.UART_State      =  UART_STATE_IDLE ;
				APPRxNotifiactionCbf_t();
			}
		}
	}
	else
	{
		/* nothong */
	}
}



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
Std_ReturnType UART_SendData(u8* Copy_u8DataBuffer,u16 Copy_u16DataLength)
{
	Std_ReturnType Std_UartState = E_OK;

	if( Copy_u8DataBuffer == NULL)
	{
		Std_UartState = E_NOT_OK;
	}
	else
	{
		if( UART_TXBuffer.UART_State     ==  UART_STATE_IDLE )
		{
			UART_TXBuffer.UART_State = UART_STATE_BUSY;

			UART_TXBuffer.UART_DATABuffer = Copy_u8DataBuffer;
			UART_TXBuffer.UART_DataIndex  = 0;
			UART_TXBuffer.UART_DataLength = Copy_u16DataLength ;
			UARTX_g->DR                   = UART_TXBuffer.UART_DATABuffer[UART_TXBuffer.UART_DataIndex];
			UART_TXBuffer.UART_DataIndex ++;
		}
		else
		{
			Std_UartState = E_BUSY;
		}

	}
	return Std_UartState;
}

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
Std_ReturnType UART_RecieveData(u8* Copy_u8DataBuffer,u16 Copy_u16DataLength)
{
	Std_ReturnType Std_UartState = E_OK;

	if( Copy_u8DataBuffer == NULL)
	{
		Std_UartState = E_NOT_OK;
	}
	else
	{
		if (UART_RXBuffer.UART_State ==  UART_STATE_IDLE )
		{
			UART_RXBuffer.UART_DATABuffer = Copy_u8DataBuffer;
			UART_RXBuffer.UART_DataIndex  = 0;
			UART_RXBuffer.UART_DataLength = Copy_u16DataLength ;
			UART_RXBuffer.UART_State =  UART_STATE_BUSY;
		}
		else
		{
			Std_UartState = E_BUSY;
		}

	}
	return Std_UartState;
}



/******************************************************************************
 * Description  :     this function directly called back when the trasmission complete
 * ReturnType
 *   Std_ReturnType  (unsigned char)
			   E_OK     : Service request accepted .
			   E_NOT_OK : Service request not accepted .

    Parameter (In)
              Copy_APPTxNotifiactionCbf -> pointer to application function
 ********************************************************************************/
Std_ReturnType UART_SetTransmissionCbf(void(*Copy_APPTxNotifiactionCbf)(void))
{
	Std_ReturnType Local_u8Status=E_OK ;
	if(Copy_APPTxNotifiactionCbf ==NULL)
	{
		Local_u8Status=E_NOT_OK;
	}
	else
	{
		APPTxNotifiactionCbf_t = Copy_APPTxNotifiactionCbf;
	}
	return Local_u8Status;
}

/******************************************************************************
 * Description  :     this function directly called back when the receiver complete
 * ReturnType
 *   Std_ReturnType  (unsigned char)
			   E_OK     : Service request accepted .
			   E_NOT_OK : Service request not accepted .

    Parameter (In)
             Copy_APPRxNotifiactionCbf-> pointer to application function
 ********************************************************************************/
Std_ReturnType UART_SetRecieverCbf(void(*Copy_APPRxNotifiactionCbf)(void))
{
	Std_ReturnType Local_u8Status=E_OK ;
	if(Copy_APPRxNotifiactionCbf ==NULL)
	{
		Local_u8Status=E_NOT_OK;
	}
	else
	{
		APPRxNotifiactionCbf_t = Copy_APPRxNotifiactionCbf;
	}
	return Local_u8Status;
}





