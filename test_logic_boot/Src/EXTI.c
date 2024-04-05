/*
 * EXTI.c
 *
 *  Created on: Oct 13, 2023
 *      Author: yahia
 */


#include "STD_types.h"
#include "math.h"

#include "EXTI_Private.h"
#include "EXTI_Interface.h"
#include "EXTI_Config.h"



void EXTI_Init(u8 port,u8 line)  // select line
{
#ifndef SYSCFG_EXTICR
#define SYSCFG_EXTICR
#define SYSCFG_EXTICR1		*(volatile u32*)(0x40013800)
#define SYSCFG_EXTICR2		*(volatile u32*)((0x40013800)+0x04)
#define SYSCFG_EXTICR3		*(volatile u32*)((0x40013800)+0x08)
#define SYSCFG_EXTICR4		*(volatile u32*)((0x40013800)+0x0C)



#endif

	if (line<4)
	{
		switch(port)
		{
			case PORTA :	SYSCFG_EXTICR1&=~(0b1111<<line*4) ;SYSCFG_EXTICR1|=(PORTA<<line*4); break;
			case PORTB :	SYSCFG_EXTICR1&=~(0b1111<<line*4) ;SYSCFG_EXTICR1|=(PORTB<<line*4); break;
			case PORTC :	SYSCFG_EXTICR1&=~(0b1111<<line*4) ;SYSCFG_EXTICR1|=(PORTC<<line*4); break;
			case PORTD :	SYSCFG_EXTICR1&=~(0b1111<<line*4) ;SYSCFG_EXTICR1|=(PORTD<<line*4); break;
			case PORTE :	SYSCFG_EXTICR1&=~(0b1111<<line*4) ;SYSCFG_EXTICR1|=(PORTE<<line*4); break;
		}
	}
	else if (line<8)
	{
		line-=4;
		switch(port)
		{
			case PORTA :	SYSCFG_EXTICR2&=~(0b1111<<line*4) ;SYSCFG_EXTICR2|=(PORTA<<line*4); break;
			case PORTB :	SYSCFG_EXTICR2&=~(0b1111<<line*4) ;SYSCFG_EXTICR2|=(PORTB<<line*4); break;
			case PORTC :	SYSCFG_EXTICR2&=~(0b1111<<line*4) ;SYSCFG_EXTICR2|=(PORTC<<line*4); break;
			case PORTD :	SYSCFG_EXTICR2&=~(0b1111<<line*4) ;SYSCFG_EXTICR2|=(PORTD<<line*4); break;
			case PORTE :	SYSCFG_EXTICR2&=~(0b1111<<line*4) ;SYSCFG_EXTICR2|=(PORTE<<line*4); break;
		}
	}
	else if (line<12)
	{
		line-=8;
		switch(port)
		{
			case PORTA :	SYSCFG_EXTICR3&=~(0b1111<<line*4) ;SYSCFG_EXTICR3|=(PORTA<<line*4); break;
			case PORTB :	SYSCFG_EXTICR3&=~(0b1111<<line*4) ;SYSCFG_EXTICR3|=(PORTB<<line*4); break;
			case PORTC :	SYSCFG_EXTICR3&=~(0b1111<<line*4) ;SYSCFG_EXTICR3|=(PORTC<<line*4); break;
			case PORTD :	SYSCFG_EXTICR3&=~(0b1111<<line*4) ;SYSCFG_EXTICR3|=(PORTD<<line*4); break;
			case PORTE :	SYSCFG_EXTICR3&=~(0b1111<<line*4) ;SYSCFG_EXTICR3|=(PORTE<<line*4); break;
		}
	}
	else if (line<16)
		{
			line-=12;
			switch(port)
			{
				case PORTA :	SYSCFG_EXTICR4&=~(0b1111<<line*4) ;SYSCFG_EXTICR4|=(PORTA<<line*4); break;
				case PORTB :	SYSCFG_EXTICR4&=~(0b1111<<line*4) ;SYSCFG_EXTICR4|=(PORTB<<line*4); break;
				case PORTC :	SYSCFG_EXTICR4&=~(0b1111<<line*4) ;SYSCFG_EXTICR4|=(PORTC<<line*4); break;
				case PORTD :	SYSCFG_EXTICR4&=~(0b1111<<line*4) ;SYSCFG_EXTICR4|=(PORTD<<line*4); break;
				case PORTE :	SYSCFG_EXTICR4&=~(0b1111<<line*4) ;SYSCFG_EXTICR4|=(PORTE<<line*4); break;
			}
		}


}
