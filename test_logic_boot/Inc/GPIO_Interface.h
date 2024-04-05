/*
 * GPIO_Interface.h
 *
 *  Created on: Sep 29, 2023
 *      Author: Ahmed Nour
 */

#ifndef GPIO_INTERFACE_H_
#define GPIO_INTERFACE_H_

void	DIO_voidSetPinDirection(u8 port, u8 pin, u8 Direction,u8 direction_type,u8 Out_direction_type);
void	DIO_voidSetPinSpeed(u8 port, u8 pin, u8 Speed);
void	DIO_voidSetPinValue(u8 port, u8 pin, u8 Value);
void 	AF_Select_pin_Fun(u8 port ,u8 pin , u8 Fun);


#define		pin0	0
#define		pin1	1
#define		pin2	2
#define		pin3	3

#define		pin4	4
#define		pin5	5
#define		pin6	6
#define		pin7	7

#define		pin8	8
#define		pin9	9
#define		pin10	10
#define		pin11	11

#define		pin12	12
#define		pin13	13
#define		pin14	14
#define		pin15	15

#define PORTA		0
#define PORTB		1
#define PORTC		2
#define PORTD		3
#define PORTE		4

#define	High		1
#define Low			0

/****************************/
/*		mode				*/

#define	input	0
#define	output	1
#define	AF		2
#define Analog	3

/********************************************/
/*		GPIO port output type register 		*/


#define Output_push_pull		0
#define	Output_open_drain		1

/********************************************/
/*				speed register				*/

#define Low_speed			0
#define	Medium_speed		1
#define	High_speed			2
#define Very_high_speed		3

/***********************************************/
/*				Input Type Reg					*/

#define No_pull_up		0
#define  Pull_up		1
#define Pull_down		2

/****************************************************/
/*					GPIO alternate function			*/

#define AF_Timer1_2			1
#define AF_Timer3_5			2
#define AF_Timer8_11		3
#define AF_I2C1_3			4
#define AF_SPI1_2			5
#define AF_SPI3				6
#define AF_UART1_3			7
#define AF_UART4_6			8
#define AF_CAN_Tim12_14		9
#define AF_OTG				10
#define AF_ETH				11
#define AF_FSIMC			12
#define AF_DCMI				13
#define AF_EventOut			15


/**************************************************/



#endif /* GPIO_INTERFACE_H_ */
