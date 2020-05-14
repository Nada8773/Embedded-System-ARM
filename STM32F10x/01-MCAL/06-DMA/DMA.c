/**
 ******************************************************************************
 * @file     DMA.c
 * @author   Nada Mohamed
 * @version  V1.0
 * @date     04-Apr-2020
 * @brief    DMA Peripheral .
 * @platform STM32
 ******************************************************************************/

/*Library */
#include "STD_TYPES.h"
#include "DMA.h"

/*********************** INTERRUPT Registers ************************/
typedef struct
{
	u32 ISR   ;
	u32 IFCR  ;
}DMA_Registers_INTERRUPT_t;
volatile DMA_Registers_INTERRUPT_t* DMA_Reg_INT = (DMA_Registers_INTERRUPT_t*)DMA1_BASE_ADDRESS;

/********************** CHANNEL REGISTER ****************************/
typedef struct
{
	u32 CCRX  ;
	u32 CNDTRX;
	u32 CPARX ;
	u32 CMARX ;
}DMA_Registers_Channel_t;

/***************** Global variable ************************/
//static volatile DMA_Registers_Channel_t* DMA_ChannelX ;
/*************************** Call back function ************/
static void(*APPNotifiactionCbf_t)(void);

/*********************** MASKS ****************************/
#define DMA_CCRX_MINC_MASK        (u32)0xffffff7f
#define DMA_CCRX_PINC_MASK        (u32)0xffffffbf
#define DMA_CCRX_PSIZE_MASK       (u32)0xfffffcff
#define DMA_CCRX_MSIZE_MASK       (u32)0xfffff3ff
#define DMA_CCRX_PL_MASK          (u32)0xffffcfff
#define DMA_CCRX_MEM2MEM_MASK     (u32)0xffffbfff
#define DMA_CCRX_CIRC_MASK        (u32)0xffffffdf
#define DMA_CCRX_DIR_MASK         (u32)0xffffffef
#define DMA_CNDTRX_NDT_MASK       (u32)0x0000
#define DMA_CPARX_PA_MASK         (u32)0x00000000
#define DMA_CMARX_MA_MASK         (u32)0x00000000
#define DMA_CCRX_EN_MASK          (u32)0xfffffffe
#define DMA_CCRX_TCIE_MASK        (u32)0xfffffffd

#define DMA_CCRX_TCIE             (u32)0x02
#define DMA_CCRX_HFIE             (u32)0x04
#define DMA_CCRX_TEIE             (u32)0x08

/********************** MACROS ***************************/
/* channel enable */
#define DMA_CCRX_EN_ENABLE        (u32)0x01

/* channel disabled */
#define DMA_CCRX_EN_DISABLE       (u32)0x00

/* Transfer complete interrupt enable */
/*************************** DMA interrupt status register (DMA_ISR) */
#define DMA1_ISR_GIF1                       ((u32)0x00000001)
#define DMA1_ISR_GIF2                       ((u32)0x00000010)
#define DMA1_ISR_GIF3                       ((u32)0x00000100)
#define DMA1_ISR_GIF4                       ((u32)0x00001000)
#define DMA1_ISR_GIF5                       ((u32)0x00010000)
#define DMA1_ISR_GIF6                       ((u32)0x00100000)
#define DMA1_ISR_GIF7                       ((u32)0x01000000)

#define DMA1_ISR_TCIF1                      ((u32)0x00000002)
#define DMA1_ISR_TCIF2                      ((u32)0x00000020)
#define DMA1_ISR_TCIF3                      ((u32)0x00000200)
#define DMA1_ISR_TCIF4                      ((u32)0x00002000)
#define DMA1_ISR_TCIF5                      ((u32)0x00020000)
#define DMA1_ISR_TCIF6                      ((u32)0x00200000)
#define DMA1_ISR_TCIF7                      ((u32)0x02000000)

#define DMA1_ISR_HTIF1                      ((u32)0x00000004)
#define DMA1_ISR_HTIF2                      ((u32)0x00000040)
#define DMA1_ISR_HTIF3                      ((u32)0x00000400)
#define DMA1_ISR_HTIF4                      ((u32)0x00004000)
#define DMA1_ISR_HTIF5                      ((u32)0x00040000)
#define DMA1_ISR_HTIF6                      ((u32)0x00400000)
#define DMA1_ISR_HTIF7                      ((u32)0x04000000)

#define DMA1_ISR_TEIF1                      ((u32)0x00000008)
#define DMA1_ISR_TEIF2                      ((u32)0x00000080)
#define DMA1_ISR_TEIF3                      ((u32)0x00000800)
#define DMA1_ISR_TEIF4                      ((u32)0x00008000)
#define DMA1_ISR_TEIF5                      ((u32)0x00080000)
#define DMA1_ISR_TEIF6                      ((u32)0x00800000)
#define DMA1_ISR_TEIF7                      ((u32)0x08000000)

/********************* DMA interrupt flag clear register (DMA_IFCR) */
#define DMA1_IFCR_CGIF1                       ((u32)0x00000001)
#define DMA1_IFCR_CGIF2                       ((u32)0x00000010)
#define DMA1_IFCR_CGIF3                       ((u32)0x00000100)
#define DMA1_IFCR_CGIF4                       ((u32)0x00001000)
#define DMA1_IFCR_CGIF5                       ((u32)0x00010000)
#define DMA1_IFCR_CGIF6                       ((u32)0x00100000)
#define DMA1_IFCR_CGIF7                       ((u32)0x01000000)

#define DMA1_IFCR_CTCIF1                      ((u32)0x00000002)
#define DMA1_IFCR_CTCIF2                      ((u32)0x00000020)
#define DMA1_IFCR_CTCIF3                      ((u32)0x00000200)
#define DMA1_IFCR_CTCIF4                      ((u32)0x00002000)
#define DMA1_IFCR_CTCIF5                      ((u32)0x00020000)
#define DMA1_IFCR_CTCIF6                      ((u32)0x00200000)
#define DMA1_IFCR_CTCIF7                      ((u32)0x02000000)

#define DMA1_IFCR_CHTIF1                      ((u32)0x00000004)
#define DMA1_IFCR_CHTIF2                      ((u32)0x00000040)
#define DMA1_IFCR_CHTIF3                      ((u32)0x00000400)
#define DMA1_IFCR_CHTIF4                      ((u32)0x00004000)
#define DMA1_IFCR_CHTIF5                      ((u32)0x00040000)
#define DMA1_IFCR_CHTIF6                      ((u32)0x00400000)
#define DMA1_IFCR_CHTIF7                      ((u32)0x04000000)

#define DMA1_IFCR_CTEIF1                      ((u32)0x00000008)
#define DMA1_IFCR_CTEIF2                      ((u32)0x00000080)
#define DMA1_IFCR_CTEIF3                      ((u32)0x00000800)
#define DMA1_IFCR_CTEIF4                      ((u32)0x00008000)
#define DMA1_IFCR_CTEIF5                      ((u32)0x00080000)
#define DMA1_IFCR_CTEIF6                      ((u32)0x00800000)
#define DMA1_IFCR_CTEIF7                      ((u32)0x08000000)

/* Global Variable */
static u8 DMA_TC_InterruptEnable = 0;
static u8 DMA_HF_InterruptEnable = 0;
static u8 DMA_TE_InterruptEnable = 0;

/* Private Function */
static void DMA1_Channel_IRQHandler(u32 ISR_Status , u32 IFCR_Flag);


/**********************************************************
 * @brief  init DMA
 * @param  DMA_Config
 *              Struct Contain the DMA configuration
 * @return Std_ReturnType \n
			  E_OK     : Service request accepted . \n
			  E_NOT_OK : Service request not accepted .
 ********************************************************/
Std_ReturnType DMA_Init(DMA_Config_t* DMA_Config )
{
	Std_ReturnType Local_DMAStatus = E_OK;
	volatile DMA_Registers_Channel_t* DMA_ChannelX ;
	DMA_TC_InterruptEnable =0 ;
	DMA_TE_InterruptEnable =0 ;
	DMA_HF_InterruptEnable =0 ;

	if(DMA_Config == NULL)
	{
		Local_DMAStatus = E_NOT_OK;
	}
	else
	{
		DMA_ChannelX =  DMA_Config->DMA_ChannelNumber ;

		/* channel disable */
		DMA_ChannelX->CCRX &= DMA_CCRX_EN_MASK   ;
		DMA_ChannelX->CCRX |= DMA_CCRX_EN_DISABLE ;

		/*  Peripheral address */
		DMA_ChannelX->CPARX  &= DMA_CPARX_PA_MASK;
		DMA_ChannelX->CPARX  |= DMA_Config->DMA_Peripheral_Address ;

		/* memory address */
		DMA_ChannelX->CMARX &= DMA_CMARX_MA_MASK;
		DMA_ChannelX->CMARX |= DMA_Config->DMA_Memory_Address ;

		/* Number of data to transfer */
		DMA_ChannelX->CNDTRX &= DMA_CNDTRX_NDT_MASK;
		DMA_ChannelX->CNDTRX |= DMA_Config->DMA_DATA_Size ;
		//DMA_ChannelX->CNDTRX |= 100;

		/* Peripheral size */
		DMA_ChannelX->CCRX &= DMA_CCRX_PSIZE_MASK ;
		DMA_ChannelX->CCRX |= DMA_Config->DMA_Peripheral_Size;

		/* memory Size */
		DMA_ChannelX->CCRX &= DMA_CCRX_MSIZE_MASK ;
		DMA_ChannelX->CCRX |= DMA_Config->DMA_Memory_Size;

		/*  Memory increment mode */
		DMA_ChannelX->CCRX &= DMA_CCRX_MINC_MASK ;
		DMA_ChannelX->CCRX |= DMA_Config->DMA_Memory_Increament ;

		/*  Peripheral increment mode */
		DMA_ChannelX->CCRX &= DMA_CCRX_PINC_MASK ;
		DMA_ChannelX->CCRX |= DMA_Config->DMA_Peripheral_Increament ;

		/* Channel priority */
		DMA_ChannelX->CCRX &= DMA_CCRX_PL_MASK;
		DMA_ChannelX->CCRX |= DMA_Config->DMA_ChannelPriority;

		/* Data Direction */
		DMA_ChannelX->CCRX &= DMA_CCRX_DIR_MASK;
		DMA_ChannelX->CCRX |= DMA_Config->DMA_DATA_Direction;

		/* DMA Mode */
		DMA_ChannelX->CCRX &= (DMA_CCRX_MEM2MEM_MASK | DMA_CCRX_CIRC_MASK) ;
		DMA_ChannelX->CCRX |= DMA_Config->DMA_Mode;

	}
	return Local_DMAStatus ;
}

/**********************************************************
 * @brief  Enable Dma Channel
 * @param  DMA_ChannelNumber
 *              dma channel number
 * @return  Std_ReturnType \n
			  E_OK     : Service request accepted . \n
			  E_NOT_OK : Service request not accepted
 ********************************************************/
Std_ReturnType DMA_EnableChannel(u32* DMA_ChannelNumber)
{
	Std_ReturnType Local_DMAStatus = E_OK;
	volatile DMA_Registers_Channel_t* DMA_ChannelX = DMA_ChannelNumber ;
	if(DMA_ChannelNumber == NULL)
	{
		Local_DMAStatus = E_NOT_OK;
	}
	else
	{
		/* channel enable */
		DMA_ChannelX->CCRX &= DMA_CCRX_EN_MASK   ;
		DMA_ChannelX->CCRX |= DMA_CCRX_EN_ENABLE ;
	}
	return Local_DMAStatus;
}

/**********************************************************
 * @brief  Disable Dma Channel
 * @param  DMA_ChannelNumber
 *              dma channel number
 * @return  Std_ReturnType \n
			  E_OK     : Service request accepted . \n
			  E_NOT_OK : Service request not accepted
 ********************************************************/
Std_ReturnType DMA_DisableChannel(u32* DMA_ChannelNumber)
{
	Std_ReturnType Local_DMAStatus = E_OK;
	volatile DMA_Registers_Channel_t* DMA_ChannelX = DMA_ChannelNumber ;
	if(DMA_ChannelNumber == NULL)
	{
		Local_DMAStatus = E_NOT_OK;
	}
	else
	{
		/* channel disable */
		DMA_ChannelX->CCRX &= DMA_CCRX_EN_MASK   ;
		DMA_ChannelX->CCRX |= DMA_CCRX_EN_DISABLE ;
	}
	return Local_DMAStatus;
}

/**********************************************************
 * @brief  Disable all DMA Interrupt
 * @param  DMA_ChannelNumber
 *              dma channel number
 * @return  Std_ReturnType \n
			  E_OK     : Service request accepted . \n
			  E_NOT_OK : Service request not accepted
 ********************************************************/
Std_ReturnType DMA_DisableAllInterrupt(u32* DMA_ChannelNumber)
{
	Std_ReturnType Local_DMAStatus = E_OK;
	volatile DMA_Registers_Channel_t* DMA_ChannelX = DMA_ChannelNumber ;

	DMA_TC_InterruptEnable =0 ;
	DMA_TE_InterruptEnable =0 ;
	DMA_HF_InterruptEnable =0 ;

	if(DMA_ChannelNumber == NULL)
	{
		Local_DMAStatus = E_NOT_OK;
	}
	else
	{
		DMA_ChannelX->CCRX &=~ DMA_CCRX_TCIE ;
		DMA_ChannelX->CCRX &=~ DMA_CCRX_HFIE ;
		DMA_ChannelX->CCRX &=~ DMA_CCRX_TEIE ;
	}
	return Local_DMAStatus;
}

/**********************************************************
 * @brief  Enable  transfer complete (TC) Interrupt
 * @param  DMA_ChannelNumber
 *              dma channel number
 * @return  Std_ReturnType \n
			  E_OK     : Service request accepted . \n
			  E_NOT_OK : Service request not accepted
 ********************************************************/
Std_ReturnType DMA_EnableTcInterrupt(u32* DMA_ChannelNumber)
{
	Std_ReturnType Local_DMAStatus = E_OK;
	DMA_TC_InterruptEnable = 1;
	volatile DMA_Registers_Channel_t* DMA_ChannelX = DMA_ChannelNumber ;
	if(DMA_ChannelNumber == NULL)
	{
		Local_DMAStatus = E_NOT_OK;
	}
	else
	{
		/* Enable interrupt */
		DMA_ChannelX->CCRX &= DMA_CCRX_TCIE_MASK ;
		DMA_ChannelX->CCRX |= DMA_CCRX_TCIE ;
	}
	return Local_DMAStatus;
}

/**********************************************************
 * @brief  Disable transfer complete (TC) Interrupt
 * @param  DMA_ChannelNumber
 *              dma channel number
 * @return  Std_ReturnType \n
			  E_OK     : Service request accepted . \n
			  E_NOT_OK : Service request not accepted
 ********************************************************/
Std_ReturnType DMA_DisableTcInterrupt(u32* DMA_ChannelNumber)
{
	Std_ReturnType Local_DMAStatus = E_OK;
	DMA_TC_InterruptEnable =0 ;
	volatile DMA_Registers_Channel_t* DMA_ChannelX = DMA_ChannelNumber ;
	if(DMA_ChannelNumber == NULL)
	{
		Local_DMAStatus = E_NOT_OK;
	}
	else
	{
		/* disable interrupt */
		DMA_ChannelX->CCRX &=~ (DMA_CCRX_TCIE) ;
	}
	return Local_DMAStatus;
}

/**********************************************************
 * @brief  Enable  Transfer error interrupt enable
 *              dma channel number
 * @return  Std_ReturnType \n
			  E_OK     : Service request accepted . \n
			  E_NOT_OK : Service request not accepted
 ********************************************************/
Std_ReturnType DMA_EnableTeInterrupt(u32* DMA_ChannelNumber)
{
	Std_ReturnType Local_DMAStatus = E_OK;
	DMA_TC_InterruptEnable = 1;
	volatile DMA_Registers_Channel_t* DMA_ChannelX = DMA_ChannelNumber ;
	if(DMA_ChannelNumber == NULL)
	{
		Local_DMAStatus = E_NOT_OK;
	}
	else
	{
		/* Enable interrupt */
		DMA_ChannelX->CCRX |= DMA_CCRX_TEIE ;
	}
	return Local_DMAStatus;
}

/**********************************************************
 * @brief  Disable Transfer error interrupt enable
 * @param  DMA_ChannelNumber
 *              dma channel number
 * @return  Std_ReturnType \n
			  E_OK     : Service request accepted . \n
			  E_NOT_OK : Service request not accepted
 ********************************************************/
Std_ReturnType DMA_DisableTeInterrupt(u32* DMA_ChannelNumber)
{
	Std_ReturnType Local_DMAStatus = E_OK;
	DMA_TC_InterruptEnable =0 ;
	volatile DMA_Registers_Channel_t* DMA_ChannelX = DMA_ChannelNumber ;
	if(DMA_ChannelNumber == NULL)
	{
		Local_DMAStatus = E_NOT_OK;
	}
	else
	{
		/* disable interrupt */
		DMA_ChannelX->CCRX &=~ (DMA_CCRX_TEIE) ;
	}
	return Local_DMAStatus;
}

/**********************************************************
 * @brief  Enable  Half transfer interrupt enable
 *              dma channel number
 * @return  Std_ReturnType \n
			  E_OK     : Service request accepted . \n
			  E_NOT_OK : Service request not accepted
 ********************************************************/
Std_ReturnType DMA_EnableHfInterrupt(u32* DMA_ChannelNumber)
{
	Std_ReturnType Local_DMAStatus = E_OK;
	DMA_HF_InterruptEnable = 1;
	volatile DMA_Registers_Channel_t* DMA_ChannelX = DMA_ChannelNumber ;
	if(DMA_ChannelNumber == NULL)
	{
		Local_DMAStatus = E_NOT_OK;
	}
	else
	{
		/* Enable interrupt */
		DMA_ChannelX->CCRX |= DMA_CCRX_HFIE ;
	}
	return Local_DMAStatus;
}

/**********************************************************
 * @brief  Disable Half transfer interrupt enable
 * @param  DMA_ChannelNumber
 *              dma channel number
 * @return  Std_ReturnType \n
			  E_OK     : Service request accepted . \n
			  E_NOT_OK : Service request not accepted
 ********************************************************/
Std_ReturnType DMA_DisableHfInterrupt(u32* DMA_ChannelNumber)
{
	Std_ReturnType Local_DMAStatus = E_OK;
	DMA_HF_InterruptEnable =0 ;
	volatile DMA_Registers_Channel_t* DMA_ChannelX = DMA_ChannelNumber ;
	if(DMA_ChannelNumber == NULL)
	{
		Local_DMAStatus = E_NOT_OK;
	}
	else
	{
		/* disable interrupt */
		DMA_ChannelX->CCRX &=~ (DMA_CCRX_HFIE) ;
	}
	return Local_DMAStatus;
}

/************************************************************************
 * @brief This function directly called back when the receiver complete
 * @param Copy_APPRxNotifiactionCbf: pointer to application function
 * @return Std_ReturnType \n
			  E_OK     : Service request accepted . \n
			  E_NOT_OK : Service request not accepted .
 ************************************************************************/
Std_ReturnType DMA_SetCallBackFun(void(*Copy_APPNotifiactionCbf)(void))
{
	Std_ReturnType Local_u8Status=E_OK ;
	if(Copy_APPNotifiactionCbf ==NULL)
	{
		Local_u8Status=E_NOT_OK;
	}
	else
	{
		APPNotifiactionCbf_t = Copy_APPNotifiactionCbf;
	}
	return Local_u8Status;
}

/************************************************************************
 * @brief This function to handle DMA1 Request
 * @param void
 * @return void
 ************************************************************************/
static void DMA1_Channel_IRQHandler(u32 ISR_Status , u32 IFCR_Flag)
{
	if(DMA_Reg_INT->ISR & ISR_Status ) /*  A transfer complete (TC) event occurred on channel x */
	{
		/*  Clears the corresponding TCIF flag in the DMA_ISR register */
		DMA_Reg_INT->IFCR = IFCR_Flag;

		/* Call back Function */
		APPNotifiactionCbf_t();
	}
}
/************************************************************************
 * @brief IRQ Handler in DMA1
 * @param void
 * @return void
 ************************************************************************/
void DMA1_Channel1_IRQHandler(void)
{
	if (DMA_TC_InterruptEnable == 1)
	{
		DMA1_Channel_IRQHandler(DMA1_ISR_TCIF1 , DMA1_IFCR_CTCIF1);
	}
	if(DMA_TE_InterruptEnable == 1)
	{
		DMA1_Channel_IRQHandler(DMA1_ISR_TEIF1 , DMA1_IFCR_CTEIF1);
	}
	if(DMA_HF_InterruptEnable == 1)
	{
		DMA1_Channel_IRQHandler(DMA1_ISR_HTIF1 , DMA1_IFCR_CHTIF1);
	}
}

void DMA1_Channel2_IRQHandler(void)
{
	if (DMA_TC_InterruptEnable == 1)
	{
		DMA1_Channel_IRQHandler(DMA1_ISR_TCIF2 , DMA1_IFCR_CTCIF2);
	}
	if(DMA_TE_InterruptEnable == 1)
	{
		DMA1_Channel_IRQHandler(DMA1_ISR_TEIF2 , DMA1_IFCR_CTEIF2);
	}
	if(DMA_HF_InterruptEnable == 1)
	{
		DMA1_Channel_IRQHandler(DMA1_ISR_HTIF2 , DMA1_IFCR_CHTIF2);
	}
}
void DMA1_Channel3_IRQHandler(void)
{
	if (DMA_TC_InterruptEnable == 1)
	{
		DMA1_Channel_IRQHandler(DMA1_ISR_TCIF3 , DMA1_IFCR_CTCIF3);
	}
	if(DMA_TE_InterruptEnable == 1)
	{
		DMA1_Channel_IRQHandler(DMA1_ISR_TEIF3 , DMA1_IFCR_CTEIF3);
	}
	if(DMA_HF_InterruptEnable == 1)
	{
		DMA1_Channel_IRQHandler(DMA1_ISR_HTIF3 , DMA1_IFCR_CHTIF3);
	}
}

void DMA1_Channel4_IRQHandler(void)
{
	if (DMA_TC_InterruptEnable == 1)
	{
		DMA1_Channel_IRQHandler(DMA1_ISR_TCIF4 , DMA1_IFCR_CTCIF4);
	}
	if(DMA_TE_InterruptEnable == 1)
	{
		DMA1_Channel_IRQHandler(DMA1_ISR_TEIF4 , DMA1_IFCR_CTEIF4);
	}
	if(DMA_HF_InterruptEnable == 1)
	{
		DMA1_Channel_IRQHandler(DMA1_ISR_HTIF4 , DMA1_IFCR_CHTIF4);
	}
}

void DMA1_Channel5_IRQHandler(void)
{
	if (DMA_TC_InterruptEnable == 1)
	{
		DMA1_Channel_IRQHandler(DMA1_ISR_TCIF5 , DMA1_IFCR_CTCIF5);
	}
	if(DMA_TE_InterruptEnable == 1)
	{
		DMA1_Channel_IRQHandler(DMA1_ISR_TEIF5 , DMA1_IFCR_CTEIF5);
	}
	if(DMA_HF_InterruptEnable == 1)
	{
		DMA1_Channel_IRQHandler(DMA1_ISR_HTIF5 , DMA1_IFCR_CHTIF5);
	}
}

void DMA1_Channel6_IRQHandler(void)
{
	if (DMA_TC_InterruptEnable == 1)
	{
		DMA1_Channel_IRQHandler(DMA1_ISR_TCIF6 , DMA1_IFCR_CTCIF6);
	}
	if(DMA_TE_InterruptEnable == 1)
	{
		DMA1_Channel_IRQHandler(DMA1_ISR_TEIF6 , DMA1_IFCR_CTEIF6);
	}
	if(DMA_HF_InterruptEnable == 1)
	{
		DMA1_Channel_IRQHandler(DMA1_ISR_HTIF6 , DMA1_IFCR_CHTIF6);
	}
}
void DMA1_Channel7_IRQHandler(void)
{
	if (DMA_TC_InterruptEnable == 1)
	{
		DMA1_Channel_IRQHandler(DMA1_ISR_TCIF7 , DMA1_IFCR_CTCIF7);
	}
	if(DMA_TE_InterruptEnable == 1)
	{
		DMA1_Channel_IRQHandler(DMA1_ISR_TEIF7 , DMA1_IFCR_CTEIF7);
	}
	if(DMA_HF_InterruptEnable == 1)
	{
		DMA1_Channel_IRQHandler(DMA1_ISR_HTIF7 , DMA1_IFCR_CHTIF7);
	}
}
void DMA2_Channel1_IRQHandler(void)
{
	APPNotifiactionCbf_t();
}
void DMA2_Channel2_IRQHandler(void)
{
	APPNotifiactionCbf_t();
}

void DMA2_Channel3_IRQHandler(void)
{
	APPNotifiactionCbf_t();
}
void DMA2_Channel4_5_IRQHandler(void)
{
	APPNotifiactionCbf_t();
}
