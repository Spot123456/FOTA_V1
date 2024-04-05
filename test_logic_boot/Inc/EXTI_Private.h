/*
 * EXTI_Private.h
 *
 *  Created on: Oct 13, 2023
 *      Author: yahia
 */

#ifndef EXTI_PRIVATE_H_
#define EXTI_PRIVATE_H_

#define		EXTI_BaseAddress		(0x40013C00)

typedef struct
{
	u32		EXTI_IMR;
	u32		EXTI_EMR;
	u32		EXTI_RTSR;
	u32		EXTI_FTSR;
	u32		EXTI_SWIER;
	u32		EXTI_PR;
}EXTI_ST;

#define 		EXTI	(EXTI_ST*)(EXTI_BaseAddress)


#endif /* EXTI_PRIVATE_H_ */
