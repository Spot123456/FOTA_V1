/*
 * USART.c
 *
 *  Created on: Oct 25, 2023
 *      Author: yahia
 */

#include "STD_types.h"
#include "Bit_Math.h"

#include "USART_Private.h"
#include "USART_Config.h"
#include "USART_Interface.h"


#define NULL	(void*)0
void UART_init()
{


	/*UART3_Reg->USART_SR=0;// clear all
	UART3_Reg->USART_CR1=0; // clear all
	// UART Enable
	SET_Bit(UART3_Reg->USART_CR1,13);

	// 1start 8 bit n stop
	CLR_Bit(UART3_Reg->USART_CR1,12);
	// no parity
	CLR_Bit(UART3_Reg->USART_CR1,10);

	// break char
	SET_Bit(UART3_Reg->USART_CR1,0);

	SET_Bit(UART3_Reg->USART_CR3,11);
	// over sampling 16
	// for 8 MHz sys and 9600 boudrate and over =0
	// the boud rate from the equation ((f/ boud)/16)
	// 52 for mantissa and the div fact = 0.0625* 16 = 1

	UART3_Reg->USART_BRR= (13<<4);	// (0x521);  //(52<<4)|(1<<0);
	SET_Bit(UART3_Reg->USART_CR1,3);
	SET_Bit(UART3_Reg->USART_CR1,2);

	// enable interrupt
	//SET_Bit(UART3_Reg->USART_CR1,7);
	//SET_Bit(UART3_Reg->USART_CR1,5);*/

	// UART Enable
		SET_Bit(UART3_Reg->USART_CR1,13);

		// over sampling 16
		// for 8 MHz sys and 9600 boudrate and over =0
		// the boud rate from the equation ((f/ boud)/16)
		// 52 for mantissa and the div fact = 0.0625* 16 = 1

		UART3_Reg->USART_BRR= (13<<4); // (52<<4)|(1<<0); //(0x521);
		SET_Bit(UART3_Reg->USART_CR1,3);
		SET_Bit(UART3_Reg->USART_CR1,2);


		// 2 stop bits
		UART3_Reg->USART_CR2 |=(2<<12);

		// 1start 8 bit n stop
		CLR_Bit(UART3_Reg->USART_CR1,12);
		// no parity
		CLR_Bit(UART3_Reg->USART_CR1,10);

		// break char
		//SET_Bit(UART3_Reg->USART_CR1,0);

		//SET_Bit(UART3_Reg->USART_CR3,11);


		// enable interrupt
		//SET_Bit(UART3_Reg->USART_CR1,7);
	//	SET_Bit(UART3_Reg->USART_CR1,5);



}
void UART_enableTX()
{
	SET_Bit(UART3_Reg->USART_CR1,3);
}

void UART_enableRX()
{
	SET_Bit(UART3_Reg->USART_CR1,2);
}

void UART_TXData(u8 Data)
{
	// wait TX empty
	//while(GET_Bit(UART3_Reg->USART_SR,7)==0);

	UART3_Reg->USART_DR= Data;
	// wait Data TX Complete
	while(GET_Bit(UART3_Reg->USART_SR,6)==0);


}

u8 UART_RXData()
{
	u8 Data1;
	//wait RX data register received data
	while((GET_Bit(UART3_Reg->USART_SR,5)==0));
	Data1=UART3_Reg->USART_DR;
	return Data1;
}

u8 Uart_Asy_Rx(u8* receive_data)
{
	u8 state = 1 ;

		//wait RX data register received data
		if((GET_Bit(UART3_Reg->USART_SR,5)==1))
		{
		*receive_data=UART3_Reg->USART_DR;
		}
		else
		{
			state=0;
		}
		return state;
}


void UART_TXString(u8* Str)
{
	//while(*Str != NULL)  // check the correct one
	while(*Str != NULL)
	{
		UART_TXData(*Str);
		Str++;
	}
}

/*********************************************************************************************************/





/*********************************************************/
//#include "GPIO_Interface.h"  //debuge
//#include "../Systick/SYSTICK_Interface.h" // debuge
/**********************************************************/

static volatile u8 UART3_u8GlobalFrame[UART_FRAME_SIZE] = { 0 };
static volatile u8 UART3_u8index = 0;
static volatile u8 UART3_u8EndFrameRecieved = 0;

static char UART3_StringRX[UART_STR_SIZE] = { 0 };
static u16 UART3_MUNRX = 0;

static u8 UART3_DataReady = 0;

static void (*GlobalRX)(void) = {NULL };
/*
 void (*UART1_CallBack[UART_CALLBACK_SIZE])(void) =
 {	NULLPTR, NULLPTR,NULLPTR,NULLPTR };
 */

void UART3_voidInit()
{

	/*********UART enable ********/
		SET_Bit(UART3_Reg->USART_CR1, UE);
	/******** baud rate **********/
	UART3_Reg->USART_BRR =(4<<4)|(5);// (13<<4);//(52<<4)|(1<<0);//0xD0; //(13<<4); //0x45; //0x341;//(52<<4)|(1<<0);//BAUDRATE;

	/******** frame format *******/
//no parity
	CLR_Bit(UART3_Reg->USART_CR1, PCE);
// 1 start 8bit data n stop
	CLR_Bit(UART3_Reg->USART_CR1, M);
// 1 stop bit
	CLR_Bit(UART3_Reg->USART_CR2, StOP_0);
	CLR_Bit(UART3_Reg->USART_CR2, StOP_1);

	/******** enable RX **********/
	SET_Bit(UART3_Reg->USART_CR1, RE);
	/******** enable TX **********/
	SET_Bit(UART3_Reg->USART_CR1, TE);

	// clr status reg
	//UART3_Reg->USART_SR = 0;
}

Error_t UART3_u8SendByteBusyw8(u8 data) {
	Error_t local_u8Status = OK;
	while (!GET_Bit(UART3_Reg->USART_SR, TXE))
		; // txe ---- time out is needed
	UART3_Reg->USART_DR = data;
	CLR_Bit(UART3_Reg->USART_SR, TXE);
	return local_u8Status;
}
Error_t UART3_u8RecieveByteBusyw8(u8 *data) {
	Error_t local_u8Status = OK;
	while (!GET_Bit(UART3_Reg->USART_SR, RXNE))
		; // RXne ---- time out is needed
	*data = UART3_Reg->USART_DR;
	CLR_Bit(UART3_Reg->USART_SR, RXNE);
	return local_u8Status;
}

Error_t UART3_u8SendStringBusyW8(char *data) {
	Error_t local_u8Status = OK;

	for (u8 local_index = 0; data[local_index]; local_index++) {
		UART3_u8SendByteBusyw8(data[local_index]);
	}
	return local_u8Status;
}

Error_t UART3_u8SendArrayBusyW8(u8 *data , u8 Copy_Size){
	Error_t local_u8Status = OK;

	for (u8 local_index = 0;local_index< Copy_Size; local_index++) {
			UART3_u8SendByteBusyw8(data[local_index]);
		}

	return local_u8Status;

}

Error_t UART3_u8RecieveByte(volatile u8 *data) {
	Error_t local_u8Status = OK;
// return DR reg
	*data = UART3_Reg->USART_DR;
	CLR_Bit(UART3_Reg->USART_SR, RXNE); //
	return local_u8Status;

}
Error_t UART3_u8SendNum(u32 copy_u32num) {
	Error_t local_u8Status = OK;

	u8 *localptr = (u8*) (&copy_u32num);
	UART3_u8SendByteBusyw8(localptr[0]);
	UART3_u8SendByteBusyw8(localptr[1]);
	UART3_u8SendByteBusyw8(localptr[2]);
	UART3_u8SendByteBusyw8(localptr[3]);

	return local_u8Status;

}
Error_t UART3_u8SendNumString(u32 copy_u32num) {
	Error_t local_u8Status = OK;
	u8 local_String[10];
	s8 index;
	if (copy_u32num != 0) {
		for (index = 0; copy_u32num; index++) {
			local_String[index] = copy_u32num % 10 + '0';
			copy_u32num /= 10;
		}
		index--;
		for (; index >= 0; index--) {
			UART3_u8SendByteBusyw8(local_String[index]);
		}
	} else {
		UART3_u8SendByteBusyw8('0');
	}

	return local_u8Status;

}



void UART3_Runnable(void) {
	if (UART3_u8EndFrameRecieved) {

		//separate_string();
		UART3_DataReady = 1;
		UART3_u8EndFrameRecieved = 0;
		UART3_u8index = 0;
	} else {
		//do nothing
	}

}

u8 UART3_IsDataReady(void) {
	return UART3_DataReady;
}
void UART3_GETdata(u8 *UART3ptrStr, u16 *UART3ptrNum) {
	u8 index = 0;
	*UART3ptrNum = UART3_MUNRX;
	for (; UART3_StringRX[index]; index++) {
		UART3ptrStr[index] = UART3_StringRX[index];
		UART3_StringRX[index] = 0;
	}
	UART3ptrStr[index] = 0;
	UART3_MUNRX = 0;
	UART3_DataReady = 0;
}

Error_t UART3_u8RecieveStringBusyW8(u8 *data);

Error_t UART3_u8EnterruptEnRX(void) {
	Error_t local_u8Status = OK;
	SET_Bit(UART3_Reg->USART_CR1, RXNEIE);
	return local_u8Status;
}
Error_t UART3_u8EnterruptDsRX(void) {
	Error_t local_u8Status = OK;
	CLR_Bit(UART3_Reg->USART_CR1, RXNEIE);
	return local_u8Status;
}
Error_t UART3_u8EnterruptCallBackRX(void (*Rx)(void)) {
	Error_t local_u8Status = OK;
	if (Rx != NULL) {
		GlobalRX = Rx;
	} else {
		local_u8Status = NULL_PTR;
	}
	return local_u8Status;
}

Error_t UART3_u8EnterruptEnTX(void) {
	Error_t local_u8Status = OK;

	return local_u8Status;
}
Error_t UART3_u8EnterruptDsTX(void) {
	Error_t local_u8Status = OK;

	return local_u8Status;
}
Error_t UART3_u8EnterruptCallBackTX(void) {
	Error_t local_u8Status = OK;

	return local_u8Status;
}

void USART3_IRQHandler(void) {
	/*
	 if (READ_BIT(UART1->USART_SR, RXNE)) {
	 UART1_u8RecieveByte(&UART1_u8GlobalFrame[UART1_u8index]); //-
	 if (UART1_u8GlobalFrame[UART1_u8index] == UART1_ENDFRAM
	 || UART1_u8index == UART_FRAME_SIZE - 1) {
	 UART1_u8EndFrameRecieved = 1;
	 }
	 if (UART1_u8index < UART_FRAME_SIZE - 1) {
	 UART1_u8index++;
	 } else {
	 // do nothing
	 }
	 }
	 */
	if (GET_Bit(UART3_Reg->USART_SR, RXNE)) {
		if (GlobalRX) {
			GlobalRX();

		}
		CLR_Bit(UART3_Reg->USART_SR, RXNE);

	}

}

/**********************************************************************/
/*****************************UART2**********************************/

static volatile u8 UART2_u8GlobalFrame[UART_FRAME_SIZE] = { 0 };
static volatile u8 UART2_u8index = 0;
static volatile u8 UART2_u8EndFrameRecieved = 0;

static char UART2_StringRX[UART_STR_SIZE] = { 0 };
static u16 UART2_MUNRX = 0;

static u8 UART2_DataReady = 0;

static void (*GlobalRX2)(void) = {NULL };
/*
 void (*UART1_CallBack[UART_CALLBACK_SIZE])(void) =
 {	NULLPTR, NULLPTR,NULLPTR,NULLPTR };
 */

void UART2_voidInit() {

	/******** baud rate **********/
	UART2_Reg->USART_BRR =(52<<4)|(1);//(13<<4); //0x45;//(52<<4)|(1<<0);//(13<<4);//BAUDRATE;

	/******** frame format *******/
//no parity
	CLR_Bit(UART2_Reg->USART_CR1, PCE);
// 1 start 8bit data n stop
	CLR_Bit(UART2_Reg->USART_CR1, M);
// 1 stop bit
	CLR_Bit(UART2_Reg->USART_CR2, StOP_0);
	CLR_Bit(UART2_Reg->USART_CR2, StOP_1);

	/******** enable RX **********/
	SET_Bit(UART2_Reg->USART_CR1, RE);
	/******** enable TX **********/
	SET_Bit(UART2_Reg->USART_CR1, TE);
	/*********UART enable ********/
	SET_Bit(UART2_Reg->USART_CR1, UE);
	// clr status reg
	UART2_Reg->USART_SR = 0;
}

Error_t UART2_u8SendByteBusyw8(u8 data) {
	Error_t local_u8Status = OK;
	while (!GET_Bit(UART2_Reg->USART_SR, TXE))
		; // txe ---- time out is needed
	UART2_Reg->USART_DR = data;
	CLR_Bit(UART2_Reg->USART_SR, TXE);
	return local_u8Status;
}
Error_t UART2_u8RecieveByteBusyw8(u8 *data) {
	Error_t local_u8Status = OK;
	while (!GET_Bit(UART2_Reg->USART_SR, RXNE))
		; // RXne ---- time out is needed
	*data = UART2_Reg->USART_DR;
	CLR_Bit(UART2_Reg->USART_SR, RXNE);
	return local_u8Status;
}

Error_t UART2_u8SendStringBusyW8(char *data) {
	Error_t local_u8Status = OK;

	for (u8 local_index = 0; data[local_index]; local_index++) {
		UART3_u8SendByteBusyw8(data[local_index]);
	}
	return local_u8Status;
}

Error_t UART2_u8SendArrayBusyW8(u8 *data , u8 Copy_Size){
	Error_t local_u8Status = OK;

	for (u8 local_index = 0;local_index< Copy_Size; local_index++) {
			UART2_u8SendByteBusyw8(data[local_index]);
		}

	return local_u8Status;

}

Error_t UART2_u8RecieveByte(volatile u8 *data) {
	Error_t local_u8Status = OK;
// return DR reg
	*data = UART2_Reg->USART_DR;
	return local_u8Status;

}
Error_t UART2_u8SendNum(u32 copy_u32num) {
	Error_t local_u8Status = OK;

	u8 *localptr = (u8*) (&copy_u32num);
	UART2_u8SendByteBusyw8(localptr[0]);
	UART2_u8SendByteBusyw8(localptr[1]);
	UART2_u8SendByteBusyw8(localptr[2]);
	UART2_u8SendByteBusyw8(localptr[3]);

	return local_u8Status;

}
Error_t UART2_u8SendNumString(u32 copy_u32num) {
	Error_t local_u8Status = OK;
	u8 local_String[10];
	s8 index;
	if (copy_u32num != 0) {
		for (index = 0; copy_u32num; index++) {
			local_String[index] = copy_u32num % 10 + '0';
			copy_u32num /= 10;
		}
		index--;
		for (; index >= 0; index--) {
			UART2_u8SendByteBusyw8(local_String[index]);
		}
	} else {
		UART2_u8SendByteBusyw8('0');
	}

	return local_u8Status;

}



void UART2_Runnable(void) {
	if (UART2_u8EndFrameRecieved) {

		//separate_string();
		UART2_DataReady = 1;
		UART2_u8EndFrameRecieved = 0;
		UART2_u8index = 0;
	} else {
		//do nothing
	}

}

u8 UART2_IsDataReady(void) {
	return UART2_DataReady;
}
void UART2_GETdata(u8 *UART2ptrStr, u16 *UART2ptrNum) {
	u8 index = 0;
	*UART2ptrNum = UART2_MUNRX;
	for (; UART2_StringRX[index]; index++) {
		UART2ptrStr[index] = UART2_StringRX[index];
		UART2_StringRX[index] = 0;
	}
	UART2ptrStr[index] = 0;
	UART2_MUNRX = 0;
	UART2_DataReady = 0;
}

Error_t UART2_u8RecieveStringBusyW8(u8 *data);
Error_t UART2_u8EnterruptEnRX(void) {
	Error_t local_u8Status = OK;
	SET_Bit(UART2_Reg->USART_CR1, RXNEIE);
	return local_u8Status;
}
Error_t UART2_u8EnterruptDsRX(void) {
	Error_t local_u8Status = OK;
	CLR_Bit(UART2_Reg->USART_CR1, RXNEIE);
	return local_u8Status;
}
Error_t UART2_u8EnterruptCallBackRX(void (*Rx)(void)) {
	Error_t local_u8Status = OK;
	if (Rx != NULL) {
		GlobalRX2 = Rx;
	} else {
		local_u8Status = NULL_PTR;
	}
	return local_u8Status;
}

Error_t UART2_u8EnterruptEnTX(void) {
	Error_t local_u8Status = OK;

	return local_u8Status;
}
Error_t UART2_u8EnterruptDsTX(void) {
	Error_t local_u8Status = OK;

	return local_u8Status;
}
Error_t UART2_u8EnterruptCallBackTX(void) {
	Error_t local_u8Status = OK;

	return local_u8Status;
}

void USART2_IRQHandler(void) {
	/*
	 if (READ_BIT(UART1->USART_SR, RXNE)) {
	 UART1_u8RecieveByte(&UART1_u8GlobalFrame[UART1_u8index]); //-
	 if (UART1_u8GlobalFrame[UART1_u8index] == UART1_ENDFRAM
	 || UART1_u8index == UART_FRAME_SIZE - 1) {
	 UART1_u8EndFrameRecieved = 1;
	 }
	 if (UART1_u8index < UART_FRAME_SIZE - 1) {
	 UART1_u8index++;
	 } else {
	 // do nothing
	 }
	 }
	 */
	if (GET_Bit(UART2_Reg->USART_SR, RXNE)) {
		if (GlobalRX2)
		{
			GlobalRX2();

		}
		CLR_Bit(UART2_Reg->USART_SR, RXNE);

	}

}

