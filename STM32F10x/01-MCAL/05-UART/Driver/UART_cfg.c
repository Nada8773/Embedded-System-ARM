#include "STD_TYPES.h"
#include "UART.h"

/**********************************************************************************************
   UART_Peripheral ->
                        UART5_Peripherial
                        UART4_Peripherial
                        USART3_Peripherial
                        USART2_Peripherial
                        USART1_Peripherial
   UART_Buadrate   ->
                        UART_BUADRATE_9600
                        UART_BUADRATE_115200
   UART_DataLength ->
                        UART_M_LENGTH_8    ->  1 Start bit, 8 Data bits, n Stop bit
                        UART_M_LENGTH_9    ->  1 Start bit, 9 Data bits, n Stop bit
   UART_StopBits   ->
                        UART_STOP_BIT_1_5  ->  1.5 Stop bit
			  	  	  	      UART_STOP_BIT_2    ->  2 Stop bits
			               UART_STOP_BIT_0_5  ->  0.5 Stop bit (The 0.5 Stop bit and 1.5 Stop bit are not available for UART4 & UART5)
			               UART_STOP_BIT_1    ->   1 Stop bit
   UART_Parity     ->
                	      UART_PCE_Enable_PS_EVEN     ->  even parity
                        UART_PCE_Enable_PS_ODD      ->  odd parity
                        UART_PCE_Disable            ->  Parity control disabled
   UART_TX_RX_Mode ->
                        UART_CR1_TE_Enable  ->  Transmitter is enabled
                        UART_CR1_TE_Disable -> Transmitter is disabled
                        UART_CR1_RE_Enable   ->  Receiver is enabled and begins searching for a start bit
                        UART_CR1_RE_Disable  ->  Receiver is disabled
*************************************************************************************************/
UART_CONFIG_t UART_Configuration_t[]=
{
	{
		.UART_Peripheral = USART1_Peripherial ,
		.UART_Buadrate   = UART_BUADRATE_9600 ,
		.UART_DataLength = UART_M_LENGTH_8   ,
		.UART_StopBits   = UART_STOP_BIT_1    ,
		.UART_Parity     = UART_PCE_Disable   ,
		.UART_TX_RX_Mode = UART_CR1_RE_Enable |  UART_CR1_TE_Enable

	}
};


UART_CONFIG_t* UART_Configuration_func ()
{
	return UART_Configuration_t ;
}


