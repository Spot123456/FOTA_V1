/*
 * DMA.c
 *
 *  Created on: Oct 2, 2023
 *      Author: Ahmed Nour
 */

#include "STD_types.h"
#include "Bit_Math.h"

#include "DMA_config.h"
#include "DMA_interface.h"
#include "DMA_private.h"

/*
void	DMA1_voidChannelInit(channel_no)
{
	// select no of channel
	DMA1->channel[0].DMA_SCR&=~(0b111<<25);
	DMA1->channel[0].DMA_SCR|=(channel_no<<25);
	DMA2->channel[0].DMA_SCR|=0;

		#if Burst_Mode_Pre== single_Transfer
		DMA1->channel[0].DMA_SCR|=(single_Transfer<<21);
		#elif Burst_Mode_Pre== INCR4
		DMA1->channel[0].DMA_SCR|=(INCR4<<21);
		#elif Burst_Mode_Pre== INCR8
		DMA1->channel[0].DMA_SCR|=(INCR8<<21);
		#elif Burst_Mode_Pre== INCR16
		DMA1->channel[0].DMA_SCR|=(INCR16<<21);
		#endif

#if Burst_Mode_Mem == single_Transfer
		DMA1->channel[0].DMA_SCR|=(single_Transfer<<23);
		#elif Burst_Mode_Mem == INCR4
		DMA1->channel[0].DMA_SCR|=(INCR4<<23);
		#elif Burst_Mode_Mem == INCR8
		DMA1->channel[0].DMA_SCR|=(INCR8<<23);
		#elif Burst_Mode_Mem == INCR16
		DMA1->channel[0].DMA_SCR|=(INCR16<<23);
		#endif

	#if Buffer_mode	== Single_buffer_mode
		CLR_Bit(DMA1->channel[0].DMA_SCR,19);
	#elif	Buffer_mode	== Double_buffer_mode
		SET_Bit(DMA1->channel[0].DMA_SCR,19);	// current target memory is 1 (DMA_SxM1AR)
		SET_Bit(DMA1->channel[0].DMA_SCR,18);
	#endif

#if		mode	==	single_mode
		CLR_Bit(DMA1->channel[0].DMA_SCR,8);
#elif	mode	==	circular_mode
		SET_Bit(DMA1->channel[0].DMA_SCR,8);
#endif

//					DMA2				//
	//DMA2->channel[0].DMA_SCR&=~(0b111<<25);
	//DMA2->channel[0].DMA_SCR|=(channel_no<<25);

		#if Burst_Mode_Pre== single_Transfer
		DMA2->channel[0].DMA_SCR|=(single_Transfer<<21);
		#elif Burst_Mode_Pre== INCR4
		DMA2->channel[0].DMA_SCR|=(INCR4<<21);
		#elif Burst_Mode_Pre== INCR8
		DMA2->channel[0].DMA_SCR|=(INCR8<<21);
		#elif Burst_Mode_Pre== INCR16
		DMA2->channel[0].DMA_SCR|=(INCR16<<21);
		#endif

#if Burst_Mode_Mem == single_Transfer
		DMA2->channel[0].DMA_SCR|=(single_Transfer<<23);
		#elif Burst_Mode_Mem == INCR4
		DMA2->channel[0].DMA_SCR|=(INCR4<<23);
		#elif Burst_Mode_Mem == INCR8
		DMA2->channel[0].DMA_SCR|=(INCR8<<23);
		#elif Burst_Mode_Mem == INCR16
		DMA2->channel[0].DMA_SCR|=(INCR16<<23);
		#endif

	#if Buffer_mode	== Single_buffer_mode
		CLR_Bit(DMA2->channel[0].DMA_SCR,19);
	#elif	Buffer_mode	== Double_buffer_mode
		SET_Bit(DMA2->channel[0].DMA_SCR,19);	// current target memory is 1 (DMA_SxM1AR)
		SET_Bit(DMA2->channel[0].DMA_SCR,18);
	#endif

#if		mode	==	single_mode
		CLR_Bit(DMA2->channel[0].DMA_SCR,8);
#elif	mode	==	circular_mode
		SET_Bit(DMA2->channel[0].DMA_SCR,8);
#endif
}

void DMA1_Stream0_Config (char DIR, char PSIZE,char MSIZE,char PINC, char MINC)
{
	DMA1->channel[0].DMA_SCR|=(PSIZE<<11);
	DMA1->channel[0].DMA_SCR|=(MSIZE<<13);
	DMA1->channel[0].DMA_SCR|=(MINC<<10);		// inc or not
	DMA1->channel[0].DMA_SCR|=(PINC<<9);	//(PINC<<10);		// inc or  not
	DMA1->channel[0].DMA_SCR|=(DIR<<6);		//pre-to mem | mem to pre | mem to mem
	SET_Bit(DMA1->channel[0].DMA_SCR,4); // complete transfer interrupt Enable
	DMA1->channel[0].DMA_S0FCR |= FIFO_threshold; //fifo thresh hold
}
void DMA1_Stream0_set_ADD(u32 *src,u32 *dst)
{
	DMA1->channel[0].CDMA_SPAR=(u32)src;	//Set the source address to the peripheral port
	DMA1->channel[0].CDMA_SPAR=(u32)dst;	//set the distination address to the memory port
}

void DMA1_Stream_Enable(unsigned int items_no){
	DMA1->channel[0].DMA_SNDTR=items_no ;	//Set number of data items
	DMA1->channel[0].DMA_SCR|=1;	// enable dma
}

void DMA1_Stream0_IntClr(void){
DMA1->DMA_LIFCR|= (1<<0)| (1<<2) | (1<<3) | (1<<4) | (1<<5); // Clear all interrupt flags
}




void DMA2_Stream0_Config (char DIR, char PSIZE,char MSIZE,char PINC, char MINC)
{
	DMA2->channel[0].DMA_SCR|=(PSIZE<<11);
	DMA2->channel[0].DMA_SCR|=(MSIZE<<13);
	DMA2->channel[0].DMA_SCR|=(MINC<<10);		// inc or not
	DMA2->channel[0].DMA_SCR|=		(PINC<<9);//(PINC<<10);		// inc or  not
	DMA2->channel[0].DMA_SCR|=(DIR<<6);		//pre-to mem | mem to pre | mem to mem
	SET_Bit(DMA2->channel[0].DMA_SCR,4); // complete transfer interrupt Enable
	DMA2->channel[0].DMA_S0FCR |= FIFO_threshold; //fifo thresh hold
}
void DMA2_Stream0_set_ADD(u32 *src,u32 *dst)
{
	DMA2->channel[0].DMA_SM0AR=(u32)src;	//Set the source address to the peripheral port
	DMA2->channel[0].DMA_SM1AR=(u32)dst;	//set the distination address to the memory port
}

void DMA2_Stream_Enable(unsigned int items_no){
	DMA2->channel[0].DMA_SNDTR=items_no ;	//Set number of data items
	DMA2->channel[0].DMA_SCR|=1;	// enable dma
}

void DMA2_Stream0_IntClr(void){
DMA2->DMA_LIFCR|= (1<<0)| (1<<2) | (1<<3) | (1<<4) | (1<<5); // Clear all interrupt flags
}*/



#define NULL (void*)0

u8 static stream_x;
static void (*SDMA2_call_back)(void)= NULL;
void	DMA1_voidChannelInit(u8 stream,u8 channel_no)
{
	stream_x=stream;
	// select no of channel
	DMA1->channel[stream].DMA_SCR&=~(0b111<<25);
	DMA1->channel[stream].DMA_SCR|=(channel_no<<25);
	DMA2->channel[stream].DMA_SCR|=0;

		#if Burst_Mode_Pre== single_Transfer
		DMA1->channel[stream].DMA_SCR|=(single_Transfer<<21);
		#elif Burst_Mode_Pre== INCR4
		DMA1->channel[stream].DMA_SCR|=(INCR4<<21);
		#elif Burst_Mode_Pre== INCR8
		DMA1->channel[stream].DMA_SCR|=(INCR8<<21);
		#elif Burst_Mode_Pre== INCR16
		DMA1->channel[stream].DMA_SCR|=(INCR16<<21);
		#endif

#if Burst_Mode_Mem == single_Transfer
		DMA1->channel[stream].DMA_SCR|=(single_Transfer<<23);
		#elif Burst_Mode_Mem == INCR4
		DMA1->channel[stream].DMA_SCR|=(INCR4<<23);
		#elif Burst_Mode_Mem == INCR8
		DMA1->channel[stream].DMA_SCR|=(INCR8<<23);
		#elif Burst_Mode_Mem == INCR16
		DMA1->channel[stream].DMA_SCR|=(INCR16<<23);
		#endif

	#if Buffer_mode	== Single_buffer_mode
		CLR_Bit(DMA1->channel[stream].DMA_SCR,19);
	#elif	Buffer_mode	== Double_buffer_mode
		SET_Bit(DMA1->channel[stream].DMA_SCR,19);	// current target memory is 1 (DMA_SxM1AR)
		SET_Bit(DMA1->channel[stream].DMA_SCR,18);
	#endif

#if		mode	==	single_mode
		CLR_Bit(DMA1->channel[stream].DMA_SCR,8);
#elif	mode	==	circular_mode
		SET_Bit(DMA1->channel[stream].DMA_SCR,8);
#endif
}

void DMA2_Stream_Config (char DIR, char PSIZE,char MSIZE,char PINC, char MINC)
{
	DMA2->channel[stream_x].DMA_SCR|=(DIR<<6);		//pre-to mem | mem to pre | mem to mem
	DMA2->channel[stream_x].DMA_SCR|=	(PINC<<9);	//(PINC<<10); 	// inc or not
	DMA2->channel[stream_x].DMA_SCR|=(MINC<<10);	// inc or not
	DMA2->channel[stream_x].DMA_SCR|=(PSIZE<<11);
	DMA2->channel[stream_x].DMA_SCR|=(MSIZE<<13);



	SET_Bit(DMA2->channel[stream_x].DMA_SCR,4); // complete transfer interrupt Enable
	DMA2->channel[stream_x].DMA_S0FCR |= FIFO_threshold; //fifo thresh hold
}
void DMA2_Stream_set_ADD(u32 *src,u32 *dst)
{
#if	Buffer_mode == Single_buffer_mode
	DMA2->channel[stream_x].CDMA_SPAR=(u32)src;	//Set the source address to the peripheral port
	DMA2->channel[stream_x].DMA_SM0AR=(u32)dst;	//set the distination address to the memory port
#elif Buffer_mode== Double_buffer_mode
	DMA2->channel[stream_x].DMA_SM0AR=(u32)src;	//Set the source address to the peripheral port
	DMA2->channel[stream_x].DMA_SM1AR=(u32)dst;	//set the distination address to the memory port
#endif
}

void DMA2_Stream_Enable(unsigned int items_no){
	DMA2->channel[stream_x].DMA_SNDTR=items_no ;	//Set number of data items
	DMA2->channel[stream_x].DMA_SCR|=1;	// enable dma
}

void DMA2_Stream_IntClr(void){
	if (stream_x==0)
	{
		DMA2->DMA_LIFCR|= (1<<0)| (1<<2) | (1<<3) | (1<<4) | (1<<5); // Clear all interrupt flags
	}
	else if (stream_x==1)
	{
		DMA2->DMA_LIFCR|= (1<<6)| (1<<8) | (1<<9) | (1<<10) | (1<<11); // Clear all interrupt flags
	}
	else if (stream_x==2)
	{
		DMA2->DMA_LIFCR|= (1<<16)| (1<<18) | (1<<19) | (1<<20) | (1<<21); // Clear all interrupt flags
	}
	else if (stream_x==3)
	{
		DMA2->DMA_LIFCR|= (1<<22)| (1<<24) | (1<<25) | (1<<26) | (1<<27); // Clear all interrupt flags
	}
}



#define  busy	1 // state of set call back function
#define	 free	0
static	u8 state; // use to handle the state of call back
void DMA2_setCallBackFun(void (*fun_callBack)(void),u8 stream)
{
	state = free;
	if(fun_callBack!=NULL && state==free)
	{
		state=busy;
		stream_x= stream;
		SDMA2_call_back=fun_callBack;
	}
	else
	{
		// error handler
	}
}



void	DMA2_Stream0_IRQHandler()
{
	if (stream_x==0&&SDMA2_call_back!=NULL)
	{
		SDMA2_call_back();
		state=free;
	}
	else
	{
		// error handler
	}
}

void	DMA2_Stream1_IRQHandler()
{
	if (stream_x==1&&SDMA2_call_back!=NULL)
	{
		SDMA2_call_back();
		state=free;
	}
	else
	{
		// error handler
	}
}

void	DMA2_Stream2_IRQHandler()
{
	if (stream_x==2&&SDMA2_call_back!=NULL)
	{
		SDMA2_call_back();
		state=free;
	}
	else
	{
		// error handler
	}
}




