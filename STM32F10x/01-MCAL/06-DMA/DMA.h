/**
  ******************************************************************************
  * @file     DMA.h
  * @author   Nada Mohamed
  * @version  V1.0
  * @date     04-Apr-2020
  * @brief    DMA Header file  .
  * @platform STM32
  ******************************************************************************/

#ifndef DMA_H_
#define DMA_H_
void Clear_ISR();


/********************** DMA Channel Address ************************************/
#define DMA1_BASE_ADDRESS        ((volatile u32)(0x40020000))

#define DMA1_CHANNEL1            ((void*) (DMA1_BASE_ADDRESS + 0x008))
#define DMA1_CHANNEL2            ((void*) (DMA1_BASE_ADDRESS + 0x01C))
#define DMA1_CHANNEL3            ((void*) (DMA1_BASE_ADDRESS + 0x030))
#define DMA1_CHANNEL4            ((void*) (DMA1_BASE_ADDRESS + 0x044))
#define DMA1_CHANNEL5            ((void*) (DMA1_BASE_ADDRESS + 0x058))
#define DMA1_CHANNEL6            ((void*) (DMA1_BASE_ADDRESS + 0x06C))
#define DMA1_CHANNEL7            ((void*) (DMA1_BASE_ADDRESS + 0x080))

/************************ Configuration Struct *****************************************/

/********************** Options *******************
* DMA_ChannelNumber     :-
                     DMA1_CHANNEL1
                     DMA1_CHANNEL2
                     DMA1_CHANNEL3
                     DMA1_CHANNEL4
                     DMA1_CHANNEL5
                     DMA1_CHANNEL6
                     DMA1_CHANNEL7

* DMA_Peripheral_Address :-
 	 	 	 	 	[DMA_PERIPHERAL_ADDRESS]
                    Peripheral address
                    Base address of the peripheral data register from/to which
				    the data will be read/written
				    Range [ 0 :31 ]bits

* DMA_Peripheral_Size     :-
					 DMA_CCRX_PSIZE_BITS_32
					 DMA_CCRX_PSIZE_BITS_8
					 DMA_CCRX_PSIZE_BITS_16

* DMA_Peripheral_Increament :-
					DMA_CCRX_PINC_ENABLE
					DMA_CCRX_PINC_DISABLE

* DMA_Memory_Address     :-
 	 	 	 	 	[DMA_MEMORY_ADDRESS]
                    Base address of the memory area from/to which
					the data will be read/written.
					Range [ 0 :31 ]bits
* DMA_Memory_Size         :-
					DMA_CCRX_MSIZE_BITS_8
					DMA_CCRX_MSIZE_BITS_16
					DMA_CCRX_MSIZE_BITS_32
* DMA_Memory_Increament   :-
					DMA_CCRX_MINC_ENABLE
					DMA_CCRX_MINC_DISABLE
* DMA_DATA_Direction      :-
                    DMA_CCRX_DIR_FROM_PERIPHERAL  //Read from peripheral
                    DMA_CCRX_DIR_FROM_MEMORY     //  Read from memory
* DMA_DATA_Size           :-
                   DMA_DATA_LENGTH

* DMA_ChannelPriority     :-
					DMA_CCRX_PL_LOW
					DMA_CCRX_PL_MEDIUM
					DMA_CCRX_PL_HIGH
					DMA_CCRX_PL_VERYHIGH
* DMA_Mode                :-

					DMA_CCRX_MEM2MEM    // Memory to memory mode
					DMA_CCRX_CIRC      // Circular mode

*/

typedef struct
{
	void* DMA_ChannelNumber          ;
	u32   DMA_Peripheral_Address     ;
	u32   DMA_Peripheral_Size	     ;
	u32   DMA_Peripheral_Increament  ;

	u32   DMA_Memory_Address         ;
    u32   DMA_Memory_Size    	     ;
    u32   DMA_Memory_Increament      ;

	u32   DMA_DATA_Direction         ;
	u32   DMA_DATA_Size     		 ;

	u32  DMA_ChannelPriority 	     ;
	u32  DMA_Mode                    ;
}DMA_Config_t;



/******************* DMA Mode ***************/
/* Memory to memory mode */
#define DMA_CCRX_MEM2MEM          (u32)0x4000
#define DMA_CCRX_MEM2MEM_DISABLE          (u32)0x00
/* Circular mode */
#define DMA_CCRX_CIRC             (u32)0x20

/****************** DMA Priority ***********/
#define DMA_CCRX_PL_LOW           (u32)0x0
#define DMA_CCRX_PL_MEDIUM        (u32)0x1000
#define DMA_CCRX_PL_HIGH          (u32)0x2000
#define DMA_CCRX_PL_VERYHIGH      (u32)0x3000

/***************** DMA Memory Size ********/
#define DMA_CCRX_MSIZE_BITS_8    (u32)0x0
#define DMA_CCRX_MSIZE_BITS_16   (u32)0x400
#define DMA_CCRX_MSIZE_BITS_32   (u32)0x800

/***************** DMA Peripheral Size ***/
#define DMA_CCRX_PSIZE_BITS_32    (u32)0x200
#define DMA_CCRX_PSIZE_BITS_8     (u32)0x0
#define DMA_CCRX_PSIZE_BITS_16    (u32)0x100

/***************** Memory increment mode **/
#define DMA_CCRX_MINC_ENABLE      (u32)0x80
#define DMA_CCRX_MINC_DISABLE     (u32)0x0

/***************** peripheral increment mode **/
#define DMA_CCRX_PINC_ENABLE      (u32)0x40
#define DMA_CCRX_PINC_DISABLE     (u32)0x0

/**************** Direction  */
#define DMA_CCRX_DIR_FROM_PERIPHERAL      (u32)0x0   //Read from peripheral
#define DMA_CCRX_DIR_FROM_MEMORY          (u32)0x10 //  Read from memory



Std_ReturnType DMA_Init(DMA_Config_t* DMA_Config);
Std_ReturnType DMA_DisableAllInterrupt(u32* DMA_ChannelNumber);
Std_ReturnType DMA_SetCallBackFun(void(*Copy_APPRxNotifiactionCbf)(void));
Std_ReturnType DMA_DisableChannle(DMA_Config_t* DMA_Config);
Std_ReturnType DMA_EnableChannle(DMA_Config_t* DMA_Config);
Std_ReturnType DMA_EnableTcInterrupt(u32* DMA_ChannelNumber);
Std_ReturnType DMA_DisableCEInterrupt(u32* DMA_ChannelNumber);
Std_ReturnType DMA_EnableTeInterrupt(u32* DMA_ChannelNumber);
Std_ReturnType DMA_DisableTeInterrupt(u32* DMA_ChannelNumber);
Std_ReturnType DMA_EnableHfInterrupt(u32* DMA_ChannelNumber);
Std_ReturnType DMA_DisableHfInterrupt(u32* DMA_ChannelNumber);



#endif /* DMA_H_ */
