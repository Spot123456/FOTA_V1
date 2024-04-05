/*
 * FMI_prg.c
 *
 *  Created on: Oct 18, 2022
 *      Author: mazen
 */

#include "STD_types.h"
#include "Bit_Math.h"


#include "FMI_int.h"
#include "FMI_prv.h"
#include "FMI_cfg.h"



void FMI_vEraseAppArea(void)
{
	for(u8 i=1 ; i< 7 ; i++)
	{
		FMI_vSectorErase(i);
	}
}

void FMI_vSectorErase(u8 A_u8SectorNo)
{
	/* 1- Wait if Flash is Busy (BSY) */
	while(GET_Bit(FMI_Reg->SR, 16) == 1){}
	/* 2- Unlock Flash Register using KEYR */
	if(GET_Bit(FMI_Reg->CR, 31) == 1)
	{
		FMI_Reg->KEYR = FMI_KEY1 ;
		FMI_Reg->KEYR = FMI_KEY2 ;
	}

	/* 3- select Sector Number to erase */
	FMI_Reg->CR &=~((u32)(0b1111<<3)); // masking to clear
	FMI_Reg->CR |= (A_u8SectorNo <<3);

	/* 4- Select Erase operation */
	SET_Bit(FMI_Reg->CR, 1);
	/* 5- Start erase operation  */
	SET_Bit(FMI_Reg->CR, 16);
	/* 6- wait for Busy Flag    */
	while(GET_Bit(FMI_Reg->SR, 16) == 1){}
	/* 7- Clear EOP flag   */
	SET_Bit(FMI_Reg->SR, 0);

	/* 8- DeSelect Erase Operation (reverse of step 4) */
	CLR_Bit(FMI_Reg->CR, 1); // end the operation that open
}

void FMI_vFlashWrite(u32 A_u32Address,
		             u16* A_pu16Data,
					 u16  A_u16Length)
{
	/* 1- Wait if Flash is Busy (BSY) */
	while(GET_Bit(FMI_Reg->SR, 16) == 1){}
	/* 2- Unlock Flash Register using KEYR */
	if(GET_Bit(FMI_Reg->CR, 31) == 1)
	{
		FMI_Reg->KEYR = FMI_KEY1 ;
		FMI_Reg->KEYR = FMI_KEY2 ;
	}

	/* 3- select element size (PSIZE)  */
	FMI_Reg->CR &=~((u32)(0b11<<8)) ;
	FMI_Reg->CR |= (0b01<<8);

	/* 4- Activate Programming Mode (PG bit) */
	SET_Bit(FMI_Reg->CR, 0);

	/* 5- Write Data Array on Flash address */
	for(u16 i=0; i<A_u16Length; i++)
	{
		*((volatile u16*)A_u32Address) = A_pu16Data[i];
		A_u32Address += 2 ;

		/* 6- wait for Busy Flag    */
		while(GET_Bit(FMI_Reg->SR, 16) == 1){}
		/* 7- Clear EOP flag   */
		SET_Bit(FMI_Reg->SR, 0);
	}
	/* 8- deactivate programming mode */
	CLR_Bit(FMI_Reg->CR, 0);

}



/***********************************************************************************/


FLASH_enERR_T FLASH_enWriteArray(u32 ptrAddress, u32 Copy_Size, u16 *Arr_u8Data)
{

	FLASH_enERR_T Local_state = FLASH_OK;
	Local_state = FLASH_enUnlock();
	FLASH_enWaitClr();         // wait and clr
	if (Local_state == FLASH_OK) {
		Local_state = FlASH_enEnablePrograming();

	} else {
		//do nothing
	}

	// wright seq on flash
	for (u32 Local_Index = 0; Local_Index < Copy_Size; Local_Index++) {
		//FLASH_START  FLASH_END
		if ((ptrAddress + (Local_Index * FLASH_WORD)) > 0x08000000
				&& (ptrAddress + (Local_Index * FLASH_WORD)) <0x08004000
				&& Local_state == FLASH_OK) {

			if (*(volatile u32*) (ptrAddress + (Local_Index * FLASH_WORD))
					!= 0xffffffff) {

				Local_state = FLASH_WRITTEN;
				break;
			} else {
				*(volatile u16*) (ptrAddress + (Local_Index * FLASH_WORD)) =
						Arr_u8Data[Local_Index];
			}

		} else {

			//out of range
			Local_state = FLASH_OUTOFRANGE;
			break;
		}
		FLASH_enWaitClr();         // wait and clr

	}
	FlASH_enDisablePrograming(); // close prog session

	return Local_state;
}


FLASH_enERR_T FLASH_enUnlock() {
	FLASH_enERR_T Local_state = FLASH_OK;
	u8 local_FlashLockStatus = GET_Bit(FMI_Reg ->CR, CR_LOCK);
	if (local_FlashLockStatus == 1) // flash is locked
			{
		// unlock sequance
		FMI_Reg->KEYR = FMI_KEY1;
		FMI_Reg->KEYR = FMI_KEY2;

	} else {
		//dp noting
	}
	 local_FlashLockStatus = GET_Bit(FMI_Reg ->CR, CR_LOCK);

	if (local_FlashLockStatus == 1) {

		Local_state = FLASH_UNLOCKERR;
	} else {

		Local_state = FLASH_OK;

	}
	return Local_state;
}

FLASH_enERR_T FLASH_enWaitClr() {
	FLASH_enERR_T Local_state = FLASH_OK;
	while (GET_Bit(FMI_Reg ->SR, SR_BSY))
		; // Wait while the flash is busy
	if (GET_Bit(FMI_Reg ->SR, SR_EOP)) // Check if End of Operation flag is set
		SET_Bit(FMI_Reg ->SR, SR_EOP);    // Clear the flag
	if (GET_Bit(FMI_Reg ->SR, SR_PGERR)) // Check for programming error
		SET_Bit(FMI_Reg ->SR, SR_PGERR);       // Clear the flag
	if (GET_Bit(FMI_Reg ->SR, SR_WRPRTERR)) // Check for write protection error
		SET_Bit(FMI_Reg ->SR, SR_WRPRTERR);  // Clear the flag

	return Local_state;
}

FLASH_enERR_T FlASH_enEnablePrograming() {
	FLASH_enERR_T Local_state = FLASH_OK;
	SET_Bit(FMI_Reg->CR, CR_PG);
	return Local_state;
}

FLASH_enERR_T FLASH_enCalculatePages(u32 Copy_Address, u16 *Ptr_u16ReturnData) {
	FLASH_enERR_T Local_state = FLASH_OK;

	//flash start
	s64 Local_calculatedData = Copy_Address - FLASH_START;

	Local_calculatedData = Local_calculatedData / FLASH_PAGE;

	if (Local_calculatedData < 0) {
		Local_state = FLASH_ERR;
	} else {
		*Ptr_u16ReturnData = Local_calculatedData;
	}

	return Local_state;
}

// disable flash programming by set PG bit
FLASH_enERR_T FlASH_enDisablePrograming()
{
	FLASH_enERR_T Local_state = FLASH_OK;
	CLR_Bit(FMI_Reg->CR, CR_PG);
	return Local_state;
}



FLASH_enERR_T FLASH_enErasePage(u8 Copy_u8page) {

	FLASH_enERR_T Local_state = FLASH_OK;

	u32 local_u32PageAddress = FLASH_START + (Copy_u8page * FLASH_PAGE);
	if (local_u32PageAddress <  FLASH_END) {
		FLASH_enUnlock();
		SET_Bit(FMI_Reg->CR, CR_PER);           // set page erase
		FMI_Reg->ACR = local_u32PageAddress;   //select page add
		SET_Bit(FMI_Reg->CR, CR_STRT);          // Start

		FLASH_enWaitClr();                                 //wait and clr
		CLR_Bit(FMI_Reg->CR, CR_PER);           // clr page erase
		FLASH_enlock();
	} else {
		//do nothing
	}
	return Local_state;
}

FLASH_enERR_T FLASH_enlock() {
	FLASH_enERR_T Local_state = FLASH_OK;

	SET_Bit(FMI_Reg->CR, CR_LOCK); // lock flash

	return Local_state;
}
