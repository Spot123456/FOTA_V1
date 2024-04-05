#ifndef		NVIC_PRIVATE_H
#define		NVIC_PRIVATE_H


#define			NVIC_BASE_ADD			(0xE000E100)

#define			NVIC_ISER0				*((u32*)(NVIC_BASE_ADD))
//#define			NVIC_ISER1				*((u32*)(NVIC_BASE_ADD+0x104))
#define			NVIC_ISER1				*((u32*)(NVIC_BASE_ADD+0x04))

#define			NVIC_ICER0				*((u32*)(NVIC_BASE_ADD+0x80 ))
#define			NVIC_ICER1				*((u32*)(NVIC_BASE_ADD+0x84 ))

#define			NVIC_ISPR0				*((u32*)(NVIC_BASE_ADD+0x100))
#define			NVIC_ISPR1				*((u32*)(NVIC_BASE_ADD+0x104))

#define			NVIC_ICPR0				*((u32*)(NVIC_BASE_ADD+0x280))
#define			NVIC_ICPR1				*((u32*)(NVIC_BASE_ADD+0x284))

#define			NVIC_IABR0				*((u32*)(NVIC_BASE_ADD+0x300))
#define			NVIC_IABR1				*((u32*)(NVIC_BASE_ADD+0x304))

// no * bec it pointer to array
#define			NVIC_IPR				((u8*)(NVIC_BASE_ADD+0x400))	// the name of array is a pointer to array

// this address not address its value to SCB_AIRCR 0x5FA for enable to write on regester
// and the sec 0300 we need to write 3 for the third hex reg to select group and sub group (look to data sheet)
#define			GRB_16_SUB_0			(0x05FA0300)
#define 		GRB_8_SUB_2				(0x05FA0400)
#define			GRB_4_SUB_4				(0x05FA0500)
#define 		GRB_2_SUB_8				(0x05FA0600)
#define			GRB_0_SUB_16			(0x05FA0700)


#endif




