/**
 ******************************************************************************
 * @file           : main.c
 * @version        : bootloader Version : 1:0:0
 * @Auther         : Ahmed Nour
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2023 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 * this code is bootloader main concept : enter a password to open the
 * flash and move from wait state machine to receiving Hex and flash to the memory
 *
 *
 ******************************************************************************
 */

#include <stdint.h>

#include "STD_types.h"
#include "Bit_Math.h"
#include "Delay.h"
#include "RCC_Interface.h"
#include "GPIO_Interface.h"
#include "STK_interface.h"
#include "USART_Interface.h"
#include "Bootloader_Interface.h"
#include "NVIC_interface.h"
#include "HEX_Parser.h"
#include "FMI_int.h"

/* for test UART */
void RX_Fu(void)
{
	u8 local_data ,flag=0;
	//flag^=1;
	DIO_voidSetPinValue(PORTD, pin12, High);
	UART3_u8RecieveByte(&local_data);
	UART3_u8SendByteBusyw8(local_data);


	//UART3_u8SendStringBusyW8("OK");*/
}

int main(void)
{
	/*Init the RCC Clock*/
	RCC_voidSysClkInt();

	//UART3_u8EnterruptCallBackRX(&RX_Fu);

	Bootloader_Init();

	//u16 data[]={0xAA55};
	//FMI_vFlashWrite(0x08004050,data , 2);
	//FMI_vFlashWrite(0x08004030,data,6);

	while(1)
	{
		/* led indecate for waiting state */
		DIO_voidSetPinValue(PORTD, pin13, High);
		_delay_ms(100);
		DIO_voidSetPinValue(PORTD, pin13, Low);
		_delay_ms(100);
		/* state machine for boot loader */
		Bootloader_voidFlashRunnable();


		//UART3_u8SendStringBusyW8("OK");
	}
}
