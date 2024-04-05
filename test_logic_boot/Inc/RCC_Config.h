/*
 * RCC_Config.h
 *
 *  Created on: Sep 27, 2023
 *      Author: Ahmed Nour
 */

#ifndef RCC_CONFIG_H_
#define RCC_CONFIG_H_

#define HSI		0
#define HSE		1
#define	PLL		2

#define RCC_Mode	HSI

#define	PLL_HSI		0
#define PLL_HSE		1

#define PLL_SELECT	PLL_HSI

#define	HSE_noClk	0
#define	HSE_Div2	2
#define	HSE_Div3	3
// from 2 to 31
#define HSE_Div31	31

#define	HSE_Pre		HSE_noClk
/********************************************/
// PLLQ/N/M/P all is div factor look at equation in my book

#define PLLQ		10		// the fclk usb otg =36 mhz if we use pll =180 , HSE=8 ,fvco = 360 mhz

#define PLLP_2		0
#define PLLP_4		1
#define PLLP_6		2
#define PLLP_8		3

#define PLLP_main	PLLP_4
#define	PLLN_main	180
#define PLLM_main	4

/********************************************/

//select Adv Peripheral Bus  (low / high)

#define	APB_No_Div		0
#define	APB_Div2		4
#define APB_Div4		5
#define APB_Div8		6
#define APB_Div16		7

#define APBH_speed		APB_Div2
#define APBL_speed		APB_Div2

/**********************************************/
#define AHB_No_Div		0
#define	AHB_DIV2		8
#define	AHB_DIV4		9
#define	AHB_DIV8		10
#define	AHB_DIV16		11
#define	AHB_DIV64		12
#define	AHB_DIV128		13
#define	AHB_DIV256		14
#define	AHB_DIV512		15

#define AHB_speed		AHB_No_Div
#endif /* RCC_CONFIG_H_ */
