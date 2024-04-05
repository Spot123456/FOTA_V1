/*
 * Bit_Math.h
 *
 *  Created on: Sep 27, 2023
 *      Author: yahia
 */

#ifndef BIT_MATH_H_
#define BIT_MATH_H_

#define SET_Bit(PORT_Id,PIN_Id)		PORT_Id|=(1<<PIN_Id)
#define CLR_Bit(PORT_Id,PIN_Id)		PORT_Id&=~(1<<PIN_Id)
#define GET_Bit(PORT_Id,PIN_Id)		((PORT_Id>>PIN_Id)&0x01)
#define Toggle_Bit(PORT_Id,PIN_Id)	PORT_Id^=(1<<PIN_Id)

#endif /* BIT_MATH_H_ */
