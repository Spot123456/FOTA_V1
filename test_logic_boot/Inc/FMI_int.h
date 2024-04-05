/*
 * FMI_int.h
 *
 *  Created on: Oct 28, 2023
 *      Author: Ahmed Nour
 */

#ifndef FMI_FMI_INT_H_
#define FMI_FMI_INT_H_


typedef enum {
	FLASH_OK = 0,
	FLASH_WRITTEN,
	FLASH_OUTOFRANGE,
	FLASH_UNLOCKERR,
	FLASH_PROTECTIONERR,
	FlASH_BUSY,
	FLASH_PROGRAMINGERR,
	FLASH_ERR

}FLASH_enERR_T;

void FMI_vEraseAppArea(void);
void FMI_vSectorErase(u8 A_u8SectorNo);
void FMI_vFlashWrite(u32 A_u32Address,u16* A_pu16Data,u16  A_u16Length);

FLASH_enERR_T FLASH_enWriteArray(u32 ptrAddress, u32 Copy_Size, u16 *Arr_u8Data);
FLASH_enERR_T FLASH_enUnlock() ;

FLASH_enERR_T FLASH_enWaitClr() ;

FLASH_enERR_T FlASH_enEnablePrograming();


// disable flash programming by set PG bit
FLASH_enERR_T FlASH_enDisablePrograming() ;

FLASH_enERR_T FLASH_enCalculatePages(u32 Copy_Address, u16 *Ptr_u16ReturnData) ;
FLASH_enERR_T FLASH_enErasePage(u8 Copy_u8page);
FLASH_enERR_T FLASH_enlock();

#endif /* FMI_FMI_INT_H_ */
