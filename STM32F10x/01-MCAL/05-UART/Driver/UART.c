
#include "STD_TYPES.h"
#include "UART.h"
#include "DMA.h"

#include "UART_cfg.h"

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


#define  UART5                ((void*)0x40005000)
#define  UART4                ((void*)0x40004C00)
#define  USART3               ((void*)0x40004800)
#define  USART2               ((void*)0x40004400)
#define  USART1               ((void*)0x40013800)


volatile UART_Reg* const UART_Peripherals[]={USART1 ,USART2 ,USART3 ,UART4,UART5};

/*********************************************USART1         USART2        USART3  */
u32 const UART_DMA_TXChannel[]             ={DMA1_CHANNEL4 ,DMA1_CHANNEL7 ,DMA1_CHANNEL2};
u32 const UART_DMA_RXChannel[]             ={DMA1_CHANNEL5 ,DMA1_CHANNEL6 ,DMA1_CHANNEL3};



/*************************** Call back function ************/
static void(*APPTxNotifiactionCbf_t)(void);
static void(*APPRxNotifiactionCbf_t)(void);
/*************************** Global Variable ***************/
static volatile UART_Reg*            UARTX_g;
static volatile UART_DATABUFFER_t    UART_TXBuffer ;
static volatile UART_DATABUFFER_t    UART_RXBuffer ;

/*********************private function  *********************/
static void IRQ_Handler(UART_Reg* UARTX);
UART_CONFIG_t* UART_Configuration_func ();


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

#define UART_SR_TC                (u32)0x40
#define UART_SR_TC_MASK           (u32)0xffffffbf

#define UART_SR_RXNE              (u32)0x20
#define UART_SR_RXNE_MASK         (u32)0xffffffdf

#define UART_CR1_RE_TE_MASK       (u32)0xfffffff3

#define UART_BRR_DIVFRACTION      (u32)0x0000000f
#define UART_BRR_DIVMANTISSA      (u32)0x0000fff0


#define UART_CR1_RXNEIE_MASK      (u32)0xffffffdf
#define UART_CR1_RXNEIE           (u32)0x20

#define UART_CR1_TXEIE_MASK       (u32)0xffffff7f
#define UART_CR1_TXEIE            (u32)0x80

#define UART_CR1_TCIE_MASK        (u32)0xffffffbf
#define UART_CR1_TCIE             (u32)0x40

/* DMA */
#define UART_CR3_DMAT      (u32)0x80
#define UART_CR3_DMAR      (u32)0x40

#define UART_CR1_IDLEIE    (u32)0x10
#define UART_SR_IDLE       (u32)0x10

/****************************
 * @brief Initialize UART
 * @param void
 * @return void
 *************************/
extern void UART_Init(void)
{
	u32 Local_u32Temp =0 ;
	f64 Local_f64BaudrateCounter ;
	u8  Local_u8BaudrateMantissa ;
	f32 Local_f32BaudrateFraction ;
	UART_CONFIG_t* UART_Configuration = UART_Configuration_func ();

	for(u8 Copy_index =0 ;Copy_index <UART_COUNT;Copy_index++)
	{
		UARTX_g = UART_Peripherals[UART_Configuration[Copy_index].UART_Peripheral] ;

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
		UARTX_g->CR1 |= UART_Configuration[Copy_index].UART_TX_RX_Mode ;

		/* word Length */
		UARTX_g->CR1 &= UART_M_MASK ;
		UARTX_g->CR1 |= UART_Configuration[Copy_index].UART_DataLength;

		/* Parity Selection */
		UARTX_g->CR1 &= UART_PCE_PS_MASK;
		UARTX_g->CR1 |= UART_Configuration[Copy_index].UART_Parity ;

		/* Stop Bit */
		UARTX_g->CR2 &= UART_STOP_BIT_MASK ;
		UARTX_g->CR2 |= UART_Configuration[Copy_index].UART_StopBits ;

		/* Baud Rate counter
	          Tx/ Rx baud =fCK /(16*USARTDIV)
	         USARTDIV = fck / (16 *baud) */

		Local_f64BaudrateCounter   = (UART_FREQUENCY /( UART_Configuration[Copy_index].UART_Buadrate * 16 )) ;
		Local_u8BaudrateMantissa   = Local_f64BaudrateCounter ;
		Local_f32BaudrateFraction  = Local_f64BaudrateCounter - (u32)Local_u8BaudrateMantissa ;
		Local_f32BaudrateFraction  = Local_f32BaudrateFraction *16 ;

		Local_u32Temp = UARTX_g->BRR ;
		Local_u32Temp |= ((Local_u8BaudrateMantissa<<4) & UART_BRR_DIVMANTISSA) | ((u32)Local_f32BaudrateFraction & UART_BRR_DIVFRACTION) ;
		UARTX_g->BRR   = Local_u32Temp;

#if UART_DMA == UART_MODE
		UARTX_g->CR3 |= UART_CR3_DMAT ;
		UARTX_g->CR3 |= UART_CR3_DMAR ;

		/*UARTX_g->CR1 &= UART_CR1_TCIE_MASK;
		UARTX_g->CR1 |= UART_CR1_TCIE;*/

		//UARTX_g->CR1 |= UART_CR1_IDLEIE;

#elif UART_INTERRUPT == UART_MODE

		/* Enable interrupt */
		UARTX_g->CR1 &= UART_CR1_RXNEIE_MASK;
		UARTX_g->CR1 |= UART_CR1_RXNEIE;    // UART Receive Interrupt Enable.

		UARTX_g->CR1 &= UART_CR1_TCIE_MASK;
		UARTX_g->CR1 |= UART_CR1_TCIE;      // UART transmit Interrupt Enable.#elif  UART_POLLING == UART_MODE
		/* Disable Interrupt */
#endif



	}



}





/******************************************************************************
 * Description  :
 *
 * ReturnType
 *   Std_ReturnType  (unsigned char)
			   E_OK     : Service request accepted .
			   E_NOT_OK : Service request not accepted .

    Parameter (In)
              Copy_u8DataBuffer  : pointer to data buffer
              Copy_u16DataLength : Data buffer Length (Range From 0 to 511 )
              Copy_u8UARTPeripherail  ->
									UART5_Peripherial
									UART4_Peripherial
									USART3_Peripherial
									USART2_Peripherial
									USART1_Peripherial
 ********************************************************************************/
Std_ReturnType UART_SendData(u8* Copy_u8DataBuffer,u16 Copy_u16DataLength, u8 Copy_u8UARTPeripherail)
{
	Std_ReturnType Std_UartState = E_OK;
	volatile UART_Reg* UARTX = UART_Peripherals[Copy_u8UARTPeripherail];
	u32 DMA_ChannelNumber;

	if( Copy_u8DataBuffer == NULL)
	{
		Std_UartState = E_NOT_OK;
	}
	else
	{
#if UART_INTERRUPT == UART_MODE
		if( UART_TXBuffer.UART_State     ==  UART_STATE_IDLE )
		{
			UART_TXBuffer.UART_State = UART_STATE_BUSY;

			UART_TXBuffer.UART_DATABuffer = Copy_u8DataBuffer;
			UART_TXBuffer.UART_DataIndex  = 0;
			UART_TXBuffer.UART_DataLength = Copy_u16DataLength ;
			UARTX->DR                   = UART_TXBuffer.UART_DATABuffer[UART_TXBuffer.UART_DataIndex];
			UART_TXBuffer.UART_DataIndex ++;
		}
		else
		{
			Std_UartState = E_BUSY;
		}
#elif UART_DMA == UART_MODE
		DMA_Config_t DMA_Config ;

		if( UART_TXBuffer.UART_State     ==  UART_STATE_IDLE )
		{
			/* DMA Config */
			DMA_ChannelNumber                    = UART_DMA_TXChannel[Copy_u8UARTPeripherail];
			DMA_Config.DMA_ChannelNumber         = UART_DMA_TXChannel[Copy_u8UARTPeripherail];
			DMA_Config.DMA_Peripheral_Address    = (u32)&(UARTX->DR)             ;
			DMA_Config.DMA_Peripheral_Size       = DMA_CCRX_PSIZE_BITS_8         ;
			DMA_Config.DMA_Peripheral_Increament = DMA_CCRX_PINC_DISABLE         ;
			DMA_Config.DMA_Memory_Address        = Copy_u8DataBuffer             ;
			DMA_Config.DMA_Memory_Size           = DMA_CCRX_MSIZE_BITS_8         ;
			DMA_Config.DMA_Memory_Increament     = DMA_CCRX_MINC_ENABLE          ;
			DMA_Config.DMA_DATA_Direction        = DMA_CCRX_DIR_FROM_MEMORY      ;
			DMA_Config.DMA_DATA_Size             = Copy_u16DataLength            ;
			DMA_Config.DMA_ChannelPriority       = DMA_CCRX_PL_VERYHIGH          ;
			DMA_Config.DMA_Mode                  = DMA_CCRX_MEM2MEM_DISABLE      ;
			UART_TXBuffer.UART_State = UART_STATE_BUSY;

			UARTX->SR  &= ~UART_SR_TC ;
			UARTX->CR1 &= UART_CR1_TCIE_MASK;
			UARTX->CR1 |= UART_CR1_TCIE;

			DMA_Init(&DMA_Config);
			DMA_DisableAllInterrupt(DMA_ChannelNumber);
			DMA_DisableTcInterrupt(DMA_ChannelNumber);
			DMA_EnableChannel(DMA_ChannelNumber);
		}

#endif


	}
	return Std_UartState;
}

/******************************************************************************
 * Description  : UART Recieve Data
 * ReturnType
 *   Std_ReturnType  (unsigned char)
			   E_OK     : Service request accepted .
			   E_NOT_OK : Service request not accepted .

    Parameter (In)
              Copy_u8DataBuffer  : pointer to data buffer
              Copy_u16DataLength : Data buffer Length (Range From 0 to 511 )
              Copy_u8UARTPeripherail  ->
									UART5_Peripherial
									UART4_Peripherial
									USART3_Peripherial
									USART2_Peripherial
									USART1_Peripherial
 ********************************************************************************/
Std_ReturnType UART_RecieveData(u8* Copy_u8DataBuffer,u16 Copy_u16DataLength , u8 Copy_u8UARTPeripherail)
{
	Std_ReturnType Std_UartState = E_OK;
	u32 DMA_ChannelNumber;
	volatile UART_Reg* UARTX = UART_Peripherals[Copy_u8UARTPeripherail];


	if( Copy_u8DataBuffer == NULL)
	{
		Std_UartState = E_NOT_OK;
	}
	else
	{
#if UART_INTERRUPT == UART_MODE
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
#elif UART_DMA == UART_MODE
		DMA_Config_t DMA_Config ;

		/* DMA Config */
		DMA_ChannelNumber                    = UART_DMA_RXChannel[Copy_u8UARTPeripherail];
		DMA_Config.DMA_ChannelNumber         = UART_DMA_RXChannel[Copy_u8UARTPeripherail];
		DMA_Config.DMA_Peripheral_Address    = (u32)&(UARTX->DR)            ;
		DMA_Config.DMA_Peripheral_Size       = DMA_CCRX_PSIZE_BITS_8       ;
		DMA_Config.DMA_Peripheral_Increament = DMA_CCRX_PINC_DISABLE        ;
		DMA_Config.DMA_Memory_Address        = Copy_u8DataBuffer            ;
		DMA_Config.DMA_Memory_Size           = DMA_CCRX_MSIZE_BITS_8        ;
		DMA_Config.DMA_Memory_Increament     = DMA_CCRX_MINC_ENABLE         ;
		DMA_Config.DMA_DATA_Direction        = DMA_CCRX_DIR_FROM_PERIPHERAL ;
		DMA_Config.DMA_DATA_Size             = Copy_u16DataLength           ;
		DMA_Config.DMA_ChannelPriority       = DMA_CCRX_PL_VERYHIGH         ;
		DMA_Config.DMA_Mode                  = DMA_CCRX_MEM2MEM_DISABLE     ;
		UART_RXBuffer.UART_State =  UART_STATE_BUSY;

		DMA_Init(&DMA_Config);
		DMA_DisableAllInterrupt(DMA_ChannelNumber);
		DMA_EnableTcInterrupt(DMA_ChannelNumber);
		DMA_EnableChannel(DMA_ChannelNumber);




#endif
	}
	return Std_UartState;
}


static void IRQ_Handler(UART_Reg* UARTX)
{
	u32 Local_u32Temp=0;

#if UART_MODE == UART_INTERRUPT

	/*  Transmit data is sent. */
	if( UARTX->SR  & UART_SR_TC )
	{
		/* CLEAR TC */
		Local_u32Temp =  UARTX->SR          ;
		Local_u32Temp &= UART_SR_TC_MASK ;
		UARTX->SR   =  Local_u32Temp     ;
		/* Transmission is not complete */
		if(UART_TXBuffer.UART_DataLength != UART_TXBuffer.UART_DataIndex)
		{
			UARTX->DR = UART_TXBuffer.UART_DATABuffer[UART_TXBuffer.UART_DataIndex];
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
#elif UART_MODE == UART_DMA
	if( UARTX->SR  & UART_SR_TC )
	{
		/* CLEAR TC */
		Local_u32Temp =  UARTX->SR          ;
		Local_u32Temp &= UART_SR_TC_MASK ;
		UARTX->SR   =  Local_u32Temp     ;
		if( UART_TXBuffer.UART_State == UART_STATE_BUSY )
		{
			UART_TXBuffer.UART_State      =  UART_STATE_IDLE ;
			APPTxNotifiactionCbf_t();
		}
	}
#endif



#if UART_MODE == UART_INTERRUPT

	/*  Received data is ready to be read. */
	if( UARTX->SR  & UART_SR_RXNE )
	{
		/* CLEAR RXNE */
		Local_u32Temp =  UARTX->SR       ;
		Local_u32Temp &= UART_SR_RXNE_MASK ;
		UARTX->SR   =  Local_u32Temp     ;

		if( UART_RXBuffer.UART_State == UART_STATE_BUSY )
		{
			UART_RXBuffer.UART_DATABuffer[ UART_RXBuffer.UART_DataIndex] = UARTX->DR ;
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
		/* nothing */
	}
#endif


}


/*****************************************************************
 * @brief This function directly called back when the transmission complete
 * @param Copy_APPTxNotifiactionCbf: pointer to application function
 * @return Std_ReturnType \n
			   E_OK     : Service request accepted . \n
			   E_NOT_OK : Service request not accepted .
 *
 *****************************************************************/
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

/**********************************************************************
 * @brief This function directly called back when the receiver complete
 * @param Copy_APPRxNotifiactionCbf: pointer to application function
 * @return Std_ReturnType \n
			  E_OK     : Service request accepted . \n
			  E_NOT_OK : Service request not accepted .
 ***********************************************************************/
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



/******************************************************************************
 * Description  : UART Handler
 * ReturnType   : void
 ********************************************************************************/
void USART1_IRQHandler(void)
{
	IRQ_Handler(UART_Peripherals[0]);
}


void USART2_IRQHandler(void)
{
	IRQ_Handler(UART_Peripherals[1]);
}

void USART3_IRQHandler(void)
{
	IRQ_Handler(UART_Peripherals[2]);
}


void UART4_IRQHandler(void)
{
	IRQ_Handler(UART_Peripherals[3]);
}

void UART5_IRQHandler(void)
{
	IRQ_Handler(UART_Peripherals[4]);
}



