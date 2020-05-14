#include "STD_TYPES.h"

#include "GPIO.h"
#include "NVIC.h"

#include "UART.h"
#include "UART_cfg.h"
#include "UART_handler.h"


#define HUART_TX_PIN 0
#define HUART_RX_PIN 1

extern GPIO_t HUART_GPIO_Configuration[2];

static const u8 UART_IRQ_Number[] = {
		USART1_IRQNUMBER,
		USART2_IRQNUMBER,
		USART3_IRQNUMBER,
		UART4_IRQNUMBER,
		UART5_IRQNUMBER
};

void HUART_InitGPIO(void)
{
	GPIO_InitPin(&HUART_GPIO_Configuration[HUART_TX_PIN]);
	GPIO_InitPin(&HUART_GPIO_Configuration[HUART_RX_PIN]);
}

void HUART_EnableIRQ(void)
{
	for(u8 Copy_index =0 ;Copy_index <UART_COUNT;Copy_index++)
	{
		NVIC_EnableIRQ(UART_IRQ_Number[Copy_index]);
		NVIC_EnableAllInterrupt();
	}
}
void HUART_DMAEnableIRQ(void)
{
	NVIC_EnableIRQ(DMA1_Channel5_IRQHandler);
	NVIC_EnableIRQ(DMA1_Channel4_IRQHandler);
	NVIC_EnableAllInterrupt();
}

void HUART_Init(void)
{
	UART_Init();
}
Std_ReturnType HUART_SendData(u8* Copy_u8DataBuffer,u16 Copy_u16DataLength, u8 Copy_u8UARTPeripherail)
{
	Std_ReturnType HUART_Status= E_OK;
	if(UART_SendData(Copy_u8DataBuffer,Copy_u16DataLength,Copy_u8UARTPeripherail)== E_NOT_OK)
	{
		HUART_Status =E_NOT_OK;
	}
	return HUART_Status;
}
Std_ReturnType HUART_RecieveData(u8* Copy_u8DataBuffer,u16 Copy_u16DataLength, u8 Copy_u8UARTPeripherail)
{
	Std_ReturnType HUART_Status= E_OK;
	if(UART_RecieveData(Copy_u8DataBuffer,Copy_u16DataLength,Copy_u8UARTPeripherail) == E_NOT_OK)
	{
		HUART_Status =E_NOT_OK;
	}
	return HUART_Status;

}

Std_ReturnType HUART_SetTransmissionCbf(void(*Copy_APPTxNotifiactionCbf)(void))
{
	Std_ReturnType Local_u8Status=E_OK ;
	if(UART_SetTransmissionCbf(Copy_APPTxNotifiactionCbf) == E_NOT_OK)
	{
		Local_u8Status=E_NOT_OK;
	}

	return Local_u8Status;

}
Std_ReturnType HUART_SetRecieverCbf(void(*Copy_APPRxNotifiactionCbf)(void))
{
	Std_ReturnType Local_u8Status=E_OK ;
	if(UART_SetRecieverCbf(Copy_APPRxNotifiactionCbf) == E_NOT_OK)
	{
		Local_u8Status=E_NOT_OK;
	}

	return Local_u8Status;
}



