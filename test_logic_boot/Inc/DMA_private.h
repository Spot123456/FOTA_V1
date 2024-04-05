#ifndef	DMA_PRIVATE_H
#define	DMA_PRIVATE_H


#include "Std_Types.h"
#include "Bit_Math.h"

typedef	struct
{
	u32	DMA_SCR;
	u32	DMA_SNDTR;
	u32	CDMA_SPAR;			// set the sorece add to preipheral port
	u32	DMA_SM0AR;			// set the distination add to memory port
	u32	DMA_SM1AR;
	u32	DMA_S0FCR;
}DMA1_channel;

typedef struct
{
	u32 			DMA_LISR;
	u32				DMA_HISR;
	u32				DMA_LIFCR;
	u32				DMA_HIFCR;
	DMA1_channel	channel[7];
}DMA1_Type;



#define 	DMA1			((volatile DMA1_Type*)(0x40026000))
#define 	DMA2			((volatile DMA1_Type*)(0x40026400))

#endif


