#include "STD_TYPES.h"
#include "GPIO.h"

/* UART1 IO pins */
GPIO_t HUART_GPIO_Configuration[2] =
{
	/* Tx pin: A9 */
	{
		 GPIO_PIN9,
		 GPIO_CNF_OutputMode_AF_PushPull,
		 GPIO_MODE_OutputMode_50MHZ,
		 GPIOA
	},

	/* Rx pin: A10 */
	{

		 GPIO_PIN10,
		 GPIO_CNF_InputMode_Floating ,
		 GPIO_MODE_InputMode,
		 GPIOA
	}
};

