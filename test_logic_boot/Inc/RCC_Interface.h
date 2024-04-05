


#ifndef		RCC_INTERFACE_H
#define 	RCC_INTERFACE_H

void RCC_voidSysClkInt(void);

void RCC_voidEnablePerCLK(u32 Per_ID,u8 Bus_ID);

void RCC_voidDisablePerCLK(u32 Per_ID,u8 Bus_ID);


#define		AHB1	0
#define 	AHB2	1
#define		AHB3	2
#define 	APB1	3
#define 	APB2	4


#endif
