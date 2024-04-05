/*
 * USART_Interface.h
 *
 *  Created on: Oct 25, 2023
 *      Author: yahia
 */

#ifndef USART_INTERFACE_H_
#define USART_INTERFACE_H_


/*
void UART_init();

void UART_enableTX();

void UART_enableRX();

*/
void UART_TXData(u8 Data);

u8 UART_RXData();

void UART_TXString(u8* Str);

u8 Uart_Asy_Rx(u8*arr);

/******************************************************/

#define UART_CALLBACK_SIZE 4
#define UART_FRAME_SIZE 20
#define UART_STR_SIZE   20
#define UART3_ENDFRAM '#'

void UART3_voidInit() ;
Error_t UART3_u8SendByteBusyw8(u8 data ) ;
Error_t UART3_u8RecieveByteBusyw8(u8* data) ;

Error_t UART3_u8SendByteAsynch(u8 data) ;
Error_t UART3_u8RecieveByteAsynch(void) ;

Error_t UART3_u8SendStringBusyW8(char* data) ;
Error_t UART3_u8RecieveStringBusyW8(u8* data) ;

Error_t UART3_u8RecieveByte(volatile u8 *data);

Error_t UART3_u8SendArrayBusyW8(u8 *data , u8 Copy_Size) ;

Error_t UART3_u8EnterruptEnRX(void);
Error_t UART3_u8EnterruptDsRX(void);
Error_t UART3_u8EnterruptCallBackRX(void (*Rx)(void)) ;
Error_t UART3_u8EnterruptEnTX(void);
Error_t UART3_u8EnterruptDsTX(void);
Error_t UART3_u8EnterruptCallBackTX(void);

/*************************************************************************************/

void UART2_voidInit();


Error_t UART2_u8SendByteBusyw8(u8 data) ;
Error_t UART2_u8RecieveByteBusyw8(u8 *data);

Error_t UART2_u8SendStringBusyW8(char *data) ;

Error_t UART2_u8SendArrayBusyW8(u8 *data , u8 Copy_Size);

Error_t UART2_u8RecieveByte(volatile u8 *data) ;
Error_t UART2_u8SendNum(u32 copy_u32num);
Error_t UART2_u8SendNumString(u32 copy_u32num) ;



void UART2_Runnable(void) ;

u8 UART2_IsDataReady(void) ;
void UART2_GETdata(u8 *UART2ptrStr, u16 *UART2ptrNum) ;

Error_t UART2_u8RecieveStringBusyW8(u8 *data);
Error_t UART2_u8EnterruptEnRX(void) ;
Error_t UART2_u8EnterruptDsRX(void) ;
Error_t UART2_u8EnterruptCallBackRX(void (*Rx)(void)) ;

Error_t UART2_u8EnterruptEnTX(void);
Error_t UART2_u8EnterruptDsTX(void) ;
Error_t UART2_u8EnterruptCallBackTX(void) ;

void USART2_IRQHandler(void) ;




#endif /* USART_INTERFACE_H_ */
