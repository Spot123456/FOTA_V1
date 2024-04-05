/*
 * GPIO_Private.h
 *
 *  Created on: Sep 29, 2023
 *      Author: Ahmed Nour
 */


#ifndef GPIO_PRIVATE_H_
#define GPIO_PRIVATE_H_

#define GPIOA_BaseAdd		(0x40020000)
#define GPIOB_BaseAdd		(0x40020400)
#define GPIOC_BaseAdd		(0x40020800)
#define GPIOD_BaseAdd		(0x40020C00)
#define GPIOE_BaseAdd		(0x40021000)

/*#define GPIOA_OFFSET		0x0000u
#define GPIOB_OFFSET		0x0400u
#define GPIOC_OFFSET		0x0800u
#define GPIOD_OFFSET		0x0C00u
#define GPIOE_OFFSET		0x1000u*/

typedef struct
{
	u32	GPIOA_B_X_MODER;
	u32	GPIOx_OTYPER;
	u32	GPIOx_B_OSPEEDR;
	u32 GPIOA_B_X_PUPDR;
	u32	GPIOx_IDR;
	u32	GPIOx_ODR;
	u32	GPIOx_BSRR;
	u32	GPIOx_LCKR;
	u32	GPIOx_AFRL;
	u32	GPIOx_AFRH;
}ST_GPIO_Reg;

#define		GPIOA	((ST_GPIO_Reg*)GPIOA_BaseAdd)
#define		GPIOB	((ST_GPIO_Reg*)GPIOB_BaseAdd)
#define		GPIOC	((ST_GPIO_Reg*)GPIOC_BaseAdd)
#define		GPIOD	((ST_GPIO_Reg*)GPIOD_BaseAdd)
#define		GPIOE	((ST_GPIO_Reg*)GPIOE_BaseAdd)




#endif /* GPIO_PRIVATE_H_ */
