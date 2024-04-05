/*
 * CRC.h
 *
 *  Created on: Nov 13, 2023
 *      Author: yahia
 */

#ifndef CRC_H_
#define CRC_H_


#define CRC_BaseAdd		(0x40023000)
typedef struct
{
	u32	CRC_DR;
	u32	CRC_IDR;
	u32	CRC_CR;
}ST_CRC;

#define CRC_Reg		((ST_CRC*)(CRC_BaseAdd))

void CRC_Write_Arr(u32* data, u16 size_of_arr);
void CRC_Read_data(u32* data);
void CRC_Write_data(u32 data);
void CRC_ReSet(void);

#endif /* CRC_H_ */
