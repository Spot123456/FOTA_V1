


#ifndef	_USART_PRIVATE_H
#define	_USART_PRIVATE_H

#define UART_3_BASE_ADD			(0x40004800)

typedef	struct
{
	u32		USART_SR;
	u32		USART_DR;
	u32		USART_BRR;
	u32		USART_CR1;
	u32		USART_CR2;
	u32		USART_CR3;
	u32		USART_GTPR;
}ST_UART;

#define		UART3_Reg		((volatile ST_UART*)(0x40004800))
#define		UART2_Reg		((volatile ST_UART*)(0x40004400))
/*****************************************************************************/
//hossam
#define BAUDRATE_9600_8MHZ 0x521
/***************************************/
#define RXNE 5
#define RXNEIE 5
#define TXE  7
#define PCE 10
#define M 12
#define StOP_0 12
#define StOP_1 13
#define RE 2
#define TE 3
#define UE 13
/*****************************************/
#endif
