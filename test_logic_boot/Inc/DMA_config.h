#ifndef		DMA_CONFIG_H
#define		DMA_CONFIG_H


// DMA send from
#define Arr_TO_Arr		0
#define Peri_TO_Arr		1
#define Arr_TO_Peri		2
#define Peri_TO_Peri	3

#define enable		1
#define disable		0

#define	Full_Complete_Interrupt		enable
#define	Half_Complete_Interrupt		enable
#define	TX_Erorr_Interrupt			enable

/****************************************************/

#define Single_buffer_mode		0
#define Double_buffer_mode		1

#define Buffer_mode		Single_buffer_mode


/*****************************************/

#define FIFO_Div4		0
#define FIFO_Div2		1
#define	FIFO_Div3_4		2
#define FIFO_Full		3

#define FIFO_threshold	FIFO_Div4
/*******************************************************/
#define	single_Transfer		0
#define INCR4				1
#define INCR8				2
#define INCR16				3

#define Burst_Mode_Pre			single_Transfer
#define Burst_Mode_Mem			single_Transfer
/********************************************************/

#define Circular_mode	1
#define single_mode		0

#define	mode		single_mode



#endif
