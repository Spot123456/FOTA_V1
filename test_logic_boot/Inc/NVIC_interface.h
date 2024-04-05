/*
 * HEX_Parser.h
 *
 *  Created on: Oct 29, 2023
 *      Author: Ahmed Nour
 */

#ifndef		NVIC_INTERFACE_H
#define		NVIC_INTERFACE_H

void		NVIC_voidInit();

void		NVIC_voidEnablePerInt(u8 IntNum);
void		NVIC_voidDisablePerInt(u8 IntNum);

void		NVIC_voidSetPendingFlag(u8 IntNum);
void		NVIC_voidClrPendingFlag(u8 IntNum);

u8			NVIC_u8ReadActiveFlag(u8 IntNum);

void		NVIC_voidSetSwIntPriority(u8 IntNum , u8 priority);

#endif
