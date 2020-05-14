
#include "STD_TYPES.h"

#include "RCC.h"
#include "GPIO.h"
#include "NVIC.h"
#include "DMA.h"
#include "UART_handler.h"

#include "diag/Trace.h"

volatile u8 TX_Arr[6]={1,2,3,4,5,6};
volatile u8 RX_Arr[6];

void func_dma(void)
{
	for(int i=0;i<6 ;i++)
	{
		trace_printf(" Recieve=%d",RX_Arr[i]);
	}

	trace_printf("\n DMA CB \n");

}

void func_tx(void)
{
	/*for(int i=0;i<6 ;i++)
	{
		trace_printf("Array Recieve = %d",RX_Arr[i]);

	}

	trace_printf("\ntx \n");*/

}
void func_rec(void)
{
	for(int i=0;i<6 ;i++)
	{
		trace_printf("Array Recieve = %d",RX_Arr[i]);

	}

	trace_printf("\nrec \n");

}

int main(void){


	RCC_SetClock( RCC_CR_HSE ,ON);
	Select_SystemClock(RCC_CFGR_SW_HSE);
	//RCC_EnablePeripheral_AHB(RCC_AHBENR_DMA1EN);
	RCC_EnablePeripheral_APB2(RCC_APB2ENR_IOPAEN_PORTA);
	RCC_EnablePeripheral_APB2(RCC_APB2ENR_USART1EN);

	HUART_InitGPIO();

	HUART_EnableIRQ();
	HUART_DMAEnableIRQ();

	DMA_SetCallBackFun(func_dma);
	UART_SetTransmissionCbf(func_tx);
	UART_SetRecieverCbf(func_rec);

	UART_Init();
	UART_SendData(TX_Arr,6, USART1_Peripherial);
	//HUART_RecieveData(RX_Arr,6, USART1_Peripherial);

	while(1)
	{

		HUART_RecieveData(RX_Arr,6, USART1_Peripherial);

	}


	return 0 ;
}


