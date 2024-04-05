/*
 * EXTI_Interface.h
 *
 *  Created on: Oct 13, 2023
 *      Author: yahia
 */

#ifndef EXTI_INTERFACE_H_
#define EXTI_INTERFACE_H_

void EXTI_Init(u8 port , u8 line);

void EXTI_ENABLE(u8 line);

void EXTI_DISABLE(u8 line);

void EXTI_SenceMode(u8 SenceMode);

void EXTI_SetCallBack(void(*fun_SetCallBack)(void));

#endif /* EXTI_INTERFACE_H_ */
