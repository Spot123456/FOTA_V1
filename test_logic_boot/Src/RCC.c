

#include "STD_types.h"
#include "Bit_Math.h"

#include "RCC_Config.h"
#include "RCC_Private.h"
#include "RCC_Interface.h"


void RCC_voidSysClkInt(void)
{
	#if	RCC_Mode == HSI

	// select the main clk os  (HSI)
	CLR_Bit(RCC_Reg->RCC_CFGR,1);
	CLR_Bit(RCC_Reg->RCC_CFGR,0);

	// enable HSI
	SET_Bit(RCC_Reg->RCC_CR,0);
	// wait until stabled
	while(GET_Bit(RCC_Reg->RCC_CR,1)==0);

	#elif	RCC_Mode == HSE

	//Clock source selection may generate glitches on MCO2. It is
	//highly recommended to configure these bits
	//SET_Bit(RCC_Reg->RCC_CFGR,31);
	//CLR_Bit(RCC_Reg->RCC_CFGR,30);
	// MCO2 Pre ( no prescaller)
	CLR_Bit(RCC_Reg->RCC_CFGR,27);
	CLR_Bit(RCC_Reg->RCC_CFGR,28);
	CLR_Bit(RCC_Reg->RCC_CFGR,29);

	//Clock source selection may generate glitches on MCO1. It is
	//highly recommended to configure these bits only after reset before enabling the external
	//SET_Bit(RCC_Reg->RCC_CFGR,22);
	//CLR_Bit(RCC_Reg->RCC_CFGR,21);

	// select HSE Prescaler
	RCC_Reg->RCC_CFGR|=(HSE_Pre<<16);



	// CLK Switch the main clk os  (HSI)
	CLR_Bit(RCC_Reg->RCC_CFGR,1);
	CLR_Bit(RCC_Reg->RCC_CFGR,0);

	// enable  HSE clock bypass
	SET_Bit(RCC_Reg->RCC_CR,18);
	// enable HSE
	SET_Bit(RCC_Reg->RCC_CR,16);
	// wait until stabled
	while(GET_Bit(RCC_Reg->RCC_CR,17)==0);

#elif	RCC_Mode == PLL
	#if	PLL_SELECT == PLL_HSE
	// HSE oscillator clock selected as PLL and PLLI2S clock entry
	SET_Bit(RCC_Reg->RCC_PLLCFGR,22);
	#elif PLL_SELECT == PLL_HSI
	// HSI oscillator clock selected as PLL and PLLI2S clock entry
	CLR_Bit(RCC_Reg->RCC_PLLCFGR,22);
	#endif
	// select PLLP by equations
	RCC_Reg->RCC_PLLCFGR|= PLLP_main<<16;
	// select PLLN by equations
	RCC_Reg->RCC_PLLCFGR|= PLLN_main<<6;
	// select PLLN by equations
		RCC_Reg->RCC_PLLCFGR|= PLLM_main<<0;
	// clk security enable
	//SET_Bit(RCC_Reg->RCC_CR,19);

	//Set and cleared by software to indicate which clock source is used as the system clock
	SET_Bit(RCC_Reg->RCC_CFGR,1);
	CLR_Bit(RCC_Reg->RCC_CFGR,0);
	// enable PLL
	SET_Bit(RCC_Reg->RCC_CR,24);
	// wait until stabled
	while(GET_Bit(RCC_Reg->RCC_CR,25)==0);

#endif


}

void RCC_voidEnablePerCLK(u32 Per_ID,u8 Bus_ID)
{
	if(Per_ID<32)
	{
		//control the division factor of the APB high-speed clock
		RCC_Reg->RCC_CFGR|=APBH_speed<<13;
		//control the division factor of the APB2 high-speed clock
		RCC_Reg->RCC_CFGR|=APBL_speed<<10;
		//control the division factor of the APB2 high-speed clock
		RCC_Reg->RCC_CFGR|=AHB_speed<<4;
		switch(Bus_ID)
		{
		case AHB1:SET_Bit(RCC_Reg->RCC_AHB1ENR,Per_ID)	;	break;
		case AHB2:SET_Bit(RCC_Reg->RCC_AHB2ENR,Per_ID)	;	break;
		case AHB3:SET_Bit(RCC_Reg->RCC_AHB3ENR,Per_ID)	;	break;
		case APB1:SET_Bit(RCC_Reg->RCC_APB1ENR,Per_ID)	;	break;
		case APB2:SET_Bit(RCC_Reg->RCC_APB2ENR,Per_ID)	;	break;
		}
	}
}

void RCC_voidDisablePerCLK(u32 Per_ID,u8 Bus_ID)
{
	if(Per_ID<32)
		{
				switch(Bus_ID)
				{
				case AHB1:CLR_Bit(RCC_Reg->RCC_AHB1ENR,Per_ID)	;	break;
				case AHB2:CLR_Bit(RCC_Reg->RCC_AHB2ENR,Per_ID)	;	break;
				case AHB3:CLR_Bit(RCC_Reg->RCC_AHB3ENR,Per_ID)	;	break;
				case APB1:CLR_Bit(RCC_Reg->RCC_APB1ENR,Per_ID)	;	break;
				case APB2:CLR_Bit(RCC_Reg->RCC_APB2ENR,Per_ID)	;	break;
				}
		}

}
