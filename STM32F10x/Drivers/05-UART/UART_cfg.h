
/********************************************************************************
 **  FILENAME     : UART.H         			                              **
 **  VERSION      : 1.0                                                        **
 **  DATE         : 25 Mar 2020                                                **                                                                         **
 **  PLATFORM     : STM		                                                  **
 **  AUTHOR       : Nada Mohamed                                               **
 *******************************************************************************/


#ifndef UART_CFG_H_
#define UART_CFG_H_


/******************************************************************************
 * Options :-
			  UART_STOP_BIT_1_5  ->  1.5 Stop bit
			  UART_STOP_BIT_2    ->  2 Stop bits
			  UART_STOP_BIT_0_5  ->  0.5 Stop bit (The 0.5 Stop bit and 1.5 Stop bit are not available for UART4 & UART5)
			  UART_STOP_BIT_1    ->   1 Stop bit
 ******************************************************************************/
#define UART_STOP_BIT     		 UART_STOP_BIT_1

/******************************************************************************
 * Options :-
             UART_M_LENGTH_8    ->  1 Start bit, 8 Data bits, n Stop bit
             UART_M_LENGTH_9    ->  1 Start bit, 9 Data bits, n Stop bit
 ********************************************************************************/
#define UART_WORD_LENGTH  	    UART_M_LENGTH_8

/******************************************************************************
 * Options :-
             UART_PCE_Enable_PS_EVEN     ->  even parity
             UART_PCE_Enable_PS_ODD      ->  odd parity
             UART_PCE_Disable            ->  Parity control disabled
 ********************************************************************************/
#define UART_PAIRTY_BIT          UART_PCE_Disable

/******************************************************************************
 * Options :-
            UART_BUADRATE_9600
 ********************************************************************************/
#define UART_BUADRATE            UART_BUADRATE_9600

/******************************************************************************
 * Options :-
            UART_CR1_RE_Enable   ->  Receiver is enabled and begins searching for a start bit
            UART_CR1_RE_Disable  ->  Receiver is disabled
 ********************************************************************************/
#define UART_CR1_RE              UART_CR1_RE_Enable

/******************************************************************************
 * Options :-
            UART_CR1_TE_Enable  ->  Transmitter is enabled
            UART_CR1_TE_Disable -> Transmitter is disabled
 ********************************************************************************/
#define UART_CR1_TE              UART_CR1_TE_Enable


#endif
