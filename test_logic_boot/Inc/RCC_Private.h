/*
 * RCC_Private.h
 *
 *  Created on: Sep 27, 2023
 *      Author: yahia
 */


#ifndef RCC_PRIVATE_H_
#define RCC_PRIVATE_H_

#define RCC_BaseAdd			(0x40023800)

typedef	struct
{
	u32	RCC_CR;
	u32	RCC_PLLCFGR;
	u32	RCC_CFGR;
	u32	RCC_CIR;
	u32	RCC_AHB1RSTR;
	u32	RCC_AHB2RSTR;
	u32	RCC_AHB3RSTR;
	u32	res1;
	u32	RCC_APB1RSTR;
	u32	RCC_APB2RSTR;
	u32	res2;
	u32	res3;
	u32	RCC_AHB1ENR;
	u32	RCC_AHB2ENR;
	u32	RCC_AHB3ENR;
	u32	res4;
	u32	RCC_APB1ENR;
	u32	RCC_APB2ENR;
	u32	res5;
	u32	res6;
	u32	RCC_AHB1LPENR;
	u32	RCC_AHB2LPENR;
	u32	RCC_AHB3LPENR;
	u32	res7;
	u32	RCC_APB1LPENR;
	u32	RCC_APB2LPENR;
	u32	res8;
	u32	res9;
	u32	RCC_BDCR;
	u32	RCC_CSR;
	u32	res10;
	u32	res11;
	u32	RCC_SSCGR;
	u32	RCC_PLLI2SCFGR;

}ST_RCC_REG;

#define		RCC_Reg		((ST_RCC_REG *)(RCC_BaseAdd))




#endif /* RCC_PRIVATE_H_ */
