/*
 * Bootloader_prog.c
 *
 *  Created on: Nov 5, 2023
 *      Author: Ahmed Nour
 */



#include "STD_types.h"
#include "Bit_Math.h"

#include "RCC_Interface.h"
#include "GPIO_Interface.h"
#include "NVIC_interface.h"
#include "STK_interface.h"
#include "DMA_interface.h"
#include "USART_Interface.h"
#include "HEX_Parser.h"
#include "FMI_int.h"

#include "Bootloader_Conf.h"
#include "Bootloader_Interface.h"
#include "Bootloader_Private.h"

u8 flash_lock=1;
BootloaderStates_t Global_bootloader_stateMachine = BOOT_WAITING;
u8 Global_FrameRequestFlag=0;
u32 RX_Flag_counter=0;
u8 Global_u8ArrayReceiveDirectUart[100]={0};
u8 Global_u8stackPointerArrayReceive = 0;
u8 RedesignHexdata[40]={0};
u8 HEXFileSize=40;
u8 dataReceiv =0;







void DMB(void) {
	__asm volatile ("dmb");
	// Use "dmb" assembly instruction
}

__attribute__((always_inline)) static inline void __set_MSP(u32 topOfMainStack) {
	__asm volatile("MSR msp, %0\n" : : "r" (topOfMainStack) );
}


void Bootloader_Init()
{

	RCC_voidEnablePerCLK(15, AHB1);		// enable flash interface
		RCC_voidEnablePerCLK(2, AHB1);		//	Enable port c
		RCC_voidEnablePerCLK(18,APB1 );		// enable Uart 3

		// this is the problem dnfanfalknjflajf
		RCC_voidEnablePerCLK(1, AHB1); // port b
		RCC_voidEnablePerCLK(3, AHB1); // port d

		DIO_voidSetPinDirection(PORTB, pin11, AF, No_pull_up, Output_push_pull); // uart rx
		AF_Select_pin_Fun(PORTB, pin11, AF_UART1_3);
		DIO_voidSetPinSpeed(PORTB, pin11,Very_high_speed );

		DIO_voidSetPinDirection(PORTD, pin8, AF,No_pull_up, Output_push_pull); // uart tx
		AF_Select_pin_Fun(PORTD, pin8, AF_UART1_3);
		DIO_voidSetPinSpeed(PORTD, pin8,Very_high_speed );

		DIO_voidSetPinDirection(PORTD, pin14,output,No_pull_up, Output_push_pull);
		DIO_voidSetPinSpeed(PORTD, pin14,Low_speed );

		DIO_voidSetPinDirection(PORTD, pin13,output,No_pull_up, Output_push_pull);
		DIO_voidSetPinSpeed(PORTD, pin13,Low_speed );

		DIO_voidSetPinDirection(PORTD, pin12,output,No_pull_up, Output_push_pull);
			DIO_voidSetPinSpeed(PORTD, pin12,Low_speed );

		NVIC_voidInit();
				UART3_voidInit(); // init uart 9600

				NVIC_voidEnablePerInt(39); // enable uart3 interrupt
				UART3_u8EnterruptEnRX();

			UART3_u8EnterruptCallBackRX(&RX_Fun);


}

void Bootloader_voidFlashRunnable()
{
	u8 local_state;
	switch (Global_bootloader_stateMachine)
	{

	/* check for upadate :
	 * value in memory location as AA55 if true clear this regoin and start flash
	 * if true change the state to boot reqest and send to server (flash req)
	 * if not change to waiting state
	 */

		case BOOT_CHECKFORUPDATE:
			local_state=localBootloader_updateAvailable();
			if(local_state==TRUE)
			{
				Global_bootloader_stateMachine = BOOT_RECEIVINGHEX;
				Global_FrameRequestFlag=1;
			}
			else
			{
				Global_bootloader_stateMachine= BOOT_WAITING;
			}

		break;

		/* if time out global state machine jump to app
		 * else change to receiving hex
		 */
		case BOOT_WAITING:
			STK_voidInit();
			STK_voidSetIntervalPeriodic(TIMEOUTDEALY, Bootloader_StateMachienChangeToApp);
			Bootloader_HandelFlames();
			UART3_u8SendStringBusyW8("wait");
		break;

		case BOOT_RECEIVINGHEX:
			Bootloader_voidfReciveFlash();
			break;

		case BOOT_JUMPTOTHEMAINAPP:
			Bootloader_Jump_To_Application();
			break;
		case BOOTERROR:
				// report error  and go Waiting
			Global_bootloader_stateMachine= BOOT_WAITING;
				break;
			default:
				break;

	}
}

/* using to make marker in memory (AA55)
   if the address location has value AA55 after SW reset
   clear and move to boot loader
*/
static Bool_t localBootloader_updateAvailable(void)
{
	u8 local_state= OK;
	u16* prt_FlashMarker = (u16*) BOOT_DDRESSMARK;
	if(*prt_FlashMarker==BOOT_FLASHMARK)
	{
		// erase this location
		FMI_vSectorErase(2);
	}
	else
	{
		local_state= FALSE;
	}
	return local_state;
}


// use to cahnge global machine into jump to application
static void Bootloader_StateMachienChangeToApp()
{
	STK_voidStopInterval();
	Global_bootloader_stateMachine= BOOT_JUMPTOTHEMAINAPP;

}

// set callback for uart 3 receive record and change global flag of receiving ( dataReceiv )
void RX_Fun (void)
{
	RX_Flag_counter++;
	static u8 receive_data;
	UART3_u8RecieveByte(&receive_data);

	//UART3_u8SendByteBusyw8(receive_data);

	if(receive_data !=':' && receive_data!= '#')
	//if(receive_data!= '#')
	{
		Global_u8ArrayReceiveDirectUart[Global_u8stackPointerArrayReceive]=receive_data;
		Global_u8stackPointerArrayReceive++;
	}

	if(receive_data=='#')
	{
		Global_u8ArrayReceiveDirectUart[Global_u8stackPointerArrayReceive]=0;
		Global_u8stackPointerArrayReceive=0;
		//UART3_u8SendStringBusyW8("hamada");
		dataReceiv=1;
	}
	u8 static led=1;
	DIO_voidSetPinValue(PORTD, pin12,led);
	led=!led;
}


void Bootloader_voidfReciveFlash()
{
//	u8 size , record_type ,data,address_hex,checksum;
	if(dataReceiv == 1)
	{
	//	RedesignHex1Bytes((u8*)Global_u8ArrayReceiveDirectUart,(u8*) RedesignHexdata, HEXFileSize); ///////
		u32 address_hex=0;
		u8 size=0 , record_type=0,checksum=0;
		u16 data[16]={0};

		//Parser_ParseData(&Global_u8ArrayReceiveDirectUart);
		HEX_voidParseFrame1((u8*) Global_u8ArrayReceiveDirectUart,&size,(u32*)address_hex,&record_type,(u16*)data,&checksum);
		if(record_type==HEX_DATARECORDER)
		{
			UART3_u8SendStringBusyW8("OK");

		}
		else if(record_type==HEX_ENDOFRECORD)
		{
			UART3_u8SendStringBusyW8("\n");
			UART3_u8SendStringBusyW8("END");
			UART3_u8SendStringBusyW8("\n");
			UART3_u8SendStringBusyW8("OK");
			STK_voidStopInterval();
			Global_bootloader_stateMachine=BOOT_JUMPTOTHEMAINAPP;
		}
		else if(record_type==HEX_STARTLINEARADD )
		{
			// updata address ( upper address )
		}



	}
	//UART3_u8SendStringBusyW8("OK");
	dataReceiv=0;
}

void Bootloader_Jump_To_Application()
{
	/* update vector table to application (main application) */
	#ifndef SCB_VTOR
	#define SCB_VTOR	*(volatile u32*)(0xE000ED00+0x08)
	#endif
	// disable all interrupt
	UART3_u8EnterruptDsRX();
	// Deinitialize peripherals
		RCC_voidDisablePerCLK(APB1,18);
		RCC_voidDisablePerCLK(1, AHB1); // port b
		RCC_voidDisablePerCLK(3, AHB1); // port d

		// Set the MSP value
			DMB();
			SCB_VTOR = FLASH_RESET_HANDLER;
			DMB();
	//set MSP
			u32* address=(u32*)(FLASH_RESET_HANDLER);
			u32 instruction = * address;
			if(instruction!=0xffffffff) // check if the address not empty
			{
				((void(*)(void))instruction)(); // jump to app
			}
			else
			{
				// error handler
			}
}



void Bootloader_HandelFlames(void)
{
	u16 local_u16DataCheckOverFrame = 0;
	u8 localArray_u8temparr[2] = { 0 };
// check on frist 2bytes for Stages data
	if (Global_u8stackPointerArrayReceive > 1)
	{
		RedesignHex1Bytes((u8*) Global_u8ArrayReceiveDirectUart,
				localArray_u8temparr, 2);
		local_u16DataCheckOverFrame = ((u16) localArray_u8temparr[0] << 8)
				| localArray_u8temparr[1];
		Global_u8stackPointerArrayReceive = 0;
		*(u16*) Global_u8ArrayReceiveDirectUart = 0;

	}
	else
	{
		//do nothing
	}

// switch on cases .. flash sequence .. update sequances ..
	switch (local_u16DataCheckOverFrame)
	{

	case BOOT_FRAMECASE_FLASHING:
		//STK_u8StopTimer();
		STK_voidStopInterval();
		if(flash_lock==1)
				{
					FMI_vSectorErase(1);
					flash_lock=0;
				}
				else
				{
					// do nothing
				}
		//send for server for data .
		UART3_u8SendStringBusyW8("ACKFLASH");
		Global_bootloader_stateMachine = BOOT_RECEIVINGHEX;
		break;
	default:
		break;
	}

}

