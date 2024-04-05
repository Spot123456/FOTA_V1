/*
 * CRC.c
 *
 *  Created on: Nov 13, 2023
 *      Author: yahia
 */

#include "STD_types.h"
#include "Bit_Math.h"

#include "CRC.h"

void CRC_Read_data(u32* data)
{
	*data= CRC_Reg->CRC_DR;
}
void CRC_Write_data(u32 data)
{
	CRC_Reg->CRC_DR= data;
}
void CRC_Write_Arr(u32* data, u16 size_of_arr)
{
	u16 i;
	for (i=0;i<size_of_arr;i++)
	{
		CRC_Reg->CRC_DR= data[size_of_arr];
	}
}

void CRC_ReSet(void)
{
	CRC_Reg->CRC_CR=1;
}
