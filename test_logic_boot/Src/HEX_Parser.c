/*
 * HEX_Parser.c
 *
 *  Created on: Oct 29, 2023
 *      Author: Ahmed Nour
 */

#include "STD_types.h"
#include "Bit_Math.h"

#include "HEX_Parser.h"
#include "FMI_int.h"

u16 my_strlen(const u8 *str)
{
	u16 length =0;
	while(*str++)
	{
		length++;
	}
	return length;
}

u32 swapBytes(u32 value) {
    return ((value >> 24) & 0xFF) |
           ((value >> 8) & 0xFF00) |
           ((value << 8) & 0xFF0000) |
           ((value << 24) & 0xFF000000);
}

void swapBitsInArray(u16 *array, u8 length) {
    for (u8 i = 0; i < length; ++i) {
        array[i] = ((array[i] >> 8) & 0x00FF) | ((array[i] << 8) & 0xFF00);
    }
}

void RedesignHex2Bytes(u16 *CopyStringHex, u32 *OutArray,
		u16 Copy_u16MaxArraySize)
{

	u8 Local_index = 0;
	u8 i=0;
	for (Local_index = 0;Local_index < Copy_u16MaxArraySize; Local_index+=8)
	{

		/*Local_temp0 = 0;
		Local_temp1 = 0;
		Local_temp0 = ((CopyStringHex[(Local_index * 4)] & 0x0f) << 4)
				| (CopyStringHex[(Local_index * 4) ] & 0xf0);
		Local_temp1 = ((CopyStringHex[(Local_index * 4) + 1] & 0x0f) << 4)
				| (CopyStringHex[(Local_index * 4) +1] & 0xf0);

		OutArray[Local_index] = Local_temp0 << 8 | Local_temp1;*/

		OutArray[i] =swapBytes(CopyStringHex[(Local_index)]);
		i++;
	}


}


void reversrBytesInBlock( u8 *input,u8 blockSize)
{
	u8 length= my_strlen(input);
	u8 temp,i=0,j;
	for(i=0;i<length;i+=blockSize)
	{
		for(j=0;j<blockSize/2;++j)
		{
			temp = input[i+j];
			input[i+j]=input[i+blockSize-1-j];
			input[i+blockSize-1+j]=temp;
		}
	}
}


// this function parsing data
void HEX_voidParseFrame(u8 *Array_u8RecivedArray, u16 *ptr_u16ReturnAddress,
		u8 *ptr_u8Data, u8 *ptr_u8SizeData, u8 *ptr_u8checkSum,
		u8 *ptr_u8DataType) {

	u8 local_u8index = 0;

	*ptr_u8SizeData = Array_u8RecivedArray[HEX_RECORD_LEN_POS];   // data size
	*ptr_u16ReturnAddress = (u16) Array_u8RecivedArray[HEX_RECORD_ADDRES_POS]
			<< 8 | Array_u8RecivedArray[HEX_RECORD_ADDRES_POS + 1];   // address
	*ptr_u8DataType = Array_u8RecivedArray[HEX_RECORD_TYPE_POS];    // data type
	for (local_u8index = 0; local_u8index < *ptr_u8SizeData; local_u8index++) { // data array
		ptr_u8Data[local_u8index] = Array_u8RecivedArray[HEX_RECORD_DATA_POS
				+ local_u8index];

	}
	for (; local_u8index < HEX_LINE_MAX; local_u8index++) { // fill array
		ptr_u8Data[local_u8index] = 0;
	}
	*ptr_u8checkSum = Array_u8RecivedArray[HEX_RECORD_CKECKSUM_POS(
			*ptr_u8SizeData)];
}

// we need to convert from text to Number ( hex or decemal or ... )
// so if the text is (No ) is num we (- '0') from it
// if the text is alfa. we (- 55)from the text .    ---> Note ('A' =65 in hex & A = 10 as a number )

static u8 Parser_2_AsciiHex( u8 Ascii)
{
	u8 local_val= 0;
	if(Ascii>='0' && Ascii<='9')
	{
		local_val = Ascii-'0';
	}
	else if (Ascii>='A' && Ascii<='F')
	{
		local_val = Ascii-55;
	}
	else
	{
		// return error
	}
	return local_val;
}


#define flash_add	0x08000000

//u16 buffer[50]; // u16 because we send in Half word

void Parser_ParseData(u8 data_arr[])
{
	u16 buffer[50];
	u8 i =0 ;
	// we need char count
	u8 CC_High , CC_Low, CC;

	// 4 digit for concat ( conversion )
	u8 dig1 , dig2 , dig3 , dig4;

	// Address Available
	u32 address = 0;

	// convert char count
	CC_High= Parser_2_AsciiHex(data_arr[1]);
	CC_Low= Parser_2_AsciiHex(data_arr[2]);
	CC= (CC_High<<4)|(CC_Low);

	// convert Address ( low address) then concat with the high that is in first frame
	dig1= Parser_2_AsciiHex(data_arr[3]);
	dig2= Parser_2_AsciiHex(data_arr[4]);
	dig3= Parser_2_AsciiHex(data_arr[5]);
	dig4= Parser_2_AsciiHex(data_arr[6]);

	address = (flash_add)| (dig1<<12) | (dig2<<8)|(dig3<<4) | (dig4);

	// then we need to convert data to send it
	// the data so big so we can cut it int small part and fill it to buffer to send it

	for(i=0 ; i< CC/2 ; i++) // CC is the data length this is the two byte in the hex frame
	{
		dig1= Parser_2_AsciiHex(data_arr[(i*4)+9]); // the start of data byte is 9
		dig2= Parser_2_AsciiHex(data_arr[(i*4)+10]);
		dig3= Parser_2_AsciiHex(data_arr[(i*4)+11]);
		dig4= Parser_2_AsciiHex(data_arr[(i*4)+12]);
		buffer[i]= (dig1<<12) | (dig2<<8) | (dig3<<4) | dig4 ;

	}

	// so we have  length of data , address and data

	FMI_vFlashWrite(address, buffer, CC/2);

}

void HEX_voidParseFrame1(u8 data_arr[],u8* size , u32* address_hex,u8*recordtype,u16*data,u8 *checksum)
{
	u16 buffer[50]={0};
	u8 i =0 ;
	// we need char count
	u8 CC_High , CC_Low, CC;

	// 4 digit for concat ( conversion )
	u8 dig1 , dig2 , dig3 , dig4;

	// Address Available
	u32 address = 0;

	// convert char count
	CC_High= Parser_2_AsciiHex(data_arr[0]);
	CC_Low= Parser_2_AsciiHex(data_arr[1]);
	CC= (CC_High<<4)|(CC_Low);

	*size=CC;

	// convert Address ( low address) then concat with the high that is in first frame
	dig1= Parser_2_AsciiHex(data_arr[2]);
	dig2= Parser_2_AsciiHex(data_arr[3]);
	dig3= Parser_2_AsciiHex(data_arr[4]);
	dig4= Parser_2_AsciiHex(data_arr[5]);

	address = (flash_add)| (dig1<<12) | (dig2<<8)|(dig3<<4) | (dig4);

	*address_hex=address;

	dig1= Parser_2_AsciiHex(data_arr[6]);
	dig2= Parser_2_AsciiHex(data_arr[7]);

	*recordtype= (dig1<<4)|dig2;

	// then we need to convert data to send it
	// the data so big so we can cut it int small part and fill it to buffer to send it

	for(i=0 ; i< CC/2 ; i++) // CC is the data length this is the two byte in the hex frame
	{
		dig1= Parser_2_AsciiHex(data_arr[(i*4)+8]); // the start of data byte is 9
		dig2= Parser_2_AsciiHex(data_arr[(i*4)+9]);
		dig3= Parser_2_AsciiHex(data_arr[(i*4)+10]);
		dig4= Parser_2_AsciiHex(data_arr[(i*4)+11]);
		buffer[i]= (dig1<<12) | (dig2<<8) | (dig3<<4) | dig4 ;
		data[i]=buffer[i];
	}

	swapBitsInArray((u16*)buffer,CC/2);
	//RedesignHex2Bytes((u16*)buffer,(u32*) data, CC/2);
	//reversrBytesInBlock((u8*)buffer, 8);
	// check sum = last 2 number
	dig1 = Parser_2_AsciiHex(data_arr[i]);
	dig2 = Parser_2_AsciiHex(data_arr[i+1]);
	*checksum=(dig1<<4) | (dig2);
	// so we have  length of data , address and data


	FMI_vFlashWrite(address,buffer, CC/2);

}



void RedesignHex1Bytes(u8 *CopyStringHex, u8 *OutArray, u8 Copy_u8Size) {
u16 Local_temp0 = 0;

u8 Local_index = 0;

for (Local_index = 0;Local_index < Copy_u8Size && CopyStringHex[(Local_index * 2)];Local_index++)
{
	for (u8 Local_index1 = 0; Local_index1 < 2; Local_index1++)
	{
		if ((CopyStringHex[(Local_index * 2) + Local_index1]) >= '0'
				&& (CopyStringHex[(Local_index * 2) + Local_index1])<= '9')
		{
			(CopyStringHex[(Local_index * 2) + Local_index1]) =
				(CopyStringHex[(Local_index * 2) + Local_index1]) - '0';
		}
		else if ((CopyStringHex[(Local_index * 2) + Local_index1]) >= 'A'
				&& (CopyStringHex[(Local_index * 2) + Local_index1])<= 'F')
		{
			(CopyStringHex[(Local_index * 2) + Local_index1]) =
			((CopyStringHex[(Local_index * 2) + Local_index1]) - 'A')+ 10;

		}
		else
		{
			//do nothing
		}
	}

	Local_temp0 = 0;

	Local_temp0 = ((CopyStringHex[(Local_index * 2)] & 0x0f) << 4)
					| (CopyStringHex[(Local_index * 2) + 1] & 0x0f);


	OutArray[Local_index] = Local_temp0;


}
for (; Local_index < Copy_u8Size; Local_index++) {
	OutArray[Local_index] = 0;
}

}







