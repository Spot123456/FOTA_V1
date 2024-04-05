#ifndef		DMA_INTERFACE_H
#define		DMA_INTERFACE_H

#include "DMA_config.h"
#include "DMA_private.h"
//void	DMA1_voidStartChannel(u32 * SrcAdd,u32 * DestAdd,u16 BlockLength);
//void	DMA1_voidChannelInit(u8 channel_no ,u8 from_to);
//void	DMA1_voidChannelInit(u8 channel_no ,u8 from_to,u8 circular_mode);
//void	DMA1_voidStartChannel(u32 * SrcAdd,u32 * DestAdd,u16 BlockLength,u8 channel_no);






//void	DMA1_voidChannelInit(u8 channel_no ,u8 from_to,u8 circular_mode);

void	DMA1_voidChannelInit(u8 stream ,u8 channel_no);
void DMA1_Stream_Config (char DIR, char PSIZE,char MSIZE,char PINC, char MINC);
void DMA1_Stream_set_ADD(u32 *src,u32 *dst);


void DMA1_Stream_Enable(unsigned int items_no);

void DMA1_Stream_IntClr(void);




void DMA2_Stream_Config (char DIR, char PSIZE,char MSIZE,char PINC, char MINC);

void DMA2_Stream_set_ADD(u32 *src,u32 *dst);

void DMA2_Stream_Enable(unsigned int items_no);

void DMA2_Stream_IntClr(void);

#endif
