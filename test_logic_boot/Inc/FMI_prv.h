/*
 * FMI_prv.h
 *
 *  Created on: Oct 28, 2023
 *      Author: Ahmed Nour
 */

#ifndef FMI_FMI_PRV_H_
#define FMI_FMI_PRV_H_


#define FMI_KEY1	0x45670123
#define FMI_KEY2    0xCDEF89AB



#define FMI_BASE_ADDR	0x40023C00

typedef struct
{
	volatile u32 ACR;
	volatile u32 KEYR;
	volatile u32 OPTKEYR;
	volatile u32 SR;
	volatile u32 CR;
	volatile u32 OPTCR;
}FMI_MemMap_t;

#define FMI_Reg   ((volatile FMI_MemMap_t*)(FMI_BASE_ADDR))



#define CR_LOCK     7
#define CR_STRT     6
#define CR_PER      1
#define CR_PG       0


// FLASH_SR  bits
#define SR_BSY            0
#define SR_EOP            0
#define SR_WRPRTERR       0
#define SR_PGERR          0


/********************************************************/


#endif /* FMI_FMI_PRV_H_ */
