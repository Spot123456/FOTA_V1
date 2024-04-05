/*
 * GPIO.c
 *
 *  Created on: Sep 29, 2023
 *      Author:	Ahmed Nour
 */

#include "STD_types.h"
#include "Bit_Math.h"

#include "GPIO_Private.h"
#include "GPIO_Interface.h"

void	DIO_voidSetPinDirection(u8 port, u8 pin, u8 Direction,u8 direction_type,u8 Out_direction_type)
{
	if((port<=PORTE)&&(pin<pin15))
	{
		switch(port)
		{
		case	PORTA:
			switch(Direction)
			{
			case	input :	GPIOA->GPIOA_B_X_MODER&=~(0b11<<pin*2);
							GPIOA->GPIOA_B_X_MODER|=(input<<pin*2);
							switch(direction_type)
							{
							// make masking then set
							case No_pull_up:	GPIOA->GPIOA_B_X_PUPDR&=~(0b11<<pin);GPIOA->GPIOA_B_X_PUPDR&=~(No_pull_up<<pin*2); break;
							case Pull_up:		GPIOA->GPIOA_B_X_PUPDR&=~(0b11<<pin); GPIOA->GPIOA_B_X_PUPDR|=(Pull_up<<pin*2);break;
							case Pull_down:		GPIOA->GPIOA_B_X_PUPDR&=~(0b11<<pin); GPIOA->GPIOA_B_X_PUPDR|=(Pull_down<<pin*2); break;
							}
							break;

			case	output	:	GPIOA->GPIOA_B_X_MODER&=~(0b11<<pin*2);
								GPIOA->GPIOA_B_X_MODER|=(output<<pin*2);
								switch(direction_type)
								{
									// make masking then set
									case No_pull_up:	GPIOA->GPIOA_B_X_PUPDR&=~(0b11<<pin);GPIOA->GPIOA_B_X_PUPDR&=~(No_pull_up<<pin*2); break;
									case Pull_up:		GPIOA->GPIOA_B_X_PUPDR&=~(0b11<<pin); GPIOA->GPIOA_B_X_PUPDR|=(Pull_up<<pin*2);break;
									case Pull_down:		GPIOA->GPIOA_B_X_PUPDR&=~(0b11<<pin); GPIOA->GPIOA_B_X_PUPDR|=(Pull_down<<pin*2); break;
								}
								switch(Out_direction_type)
								{
									case Output_push_pull:	GPIOA->GPIOx_OTYPER&=~(1<<pin); break;
									case Output_open_drain:	GPIOA->GPIOx_OTYPER|=(1<<pin); break;

								}
								break;

			case	AF :	GPIOA->GPIOA_B_X_MODER&=~(0b11<<pin*2);
							GPIOA->GPIOA_B_X_MODER|=(AF<<pin*2);

							switch(direction_type)
							{
								// make masking then set
								case No_pull_up:	GPIOA->GPIOA_B_X_PUPDR&=~(0b11<<pin);GPIOA->GPIOA_B_X_PUPDR&=~(No_pull_up<<pin*2); break;
								case Pull_up:		GPIOA->GPIOA_B_X_PUPDR&=~(0b11<<pin); GPIOA->GPIOA_B_X_PUPDR|=(Pull_up<<pin*2);break;
								case Pull_down:		GPIOA->GPIOA_B_X_PUPDR&=~(0b11<<pin); GPIOA->GPIOA_B_X_PUPDR|=(Pull_down<<pin*2); break;
							}
							switch(Out_direction_type)
							{
								case Output_push_pull:	GPIOA->GPIOx_OTYPER&=~(1<<pin); break;
								case Output_open_drain:	GPIOA->GPIOx_OTYPER|=(1<<pin); break;

							}
				break;



			case	Analog :	GPIOA->GPIOA_B_X_MODER&=~(0b11<<pin*2);
								GPIOA->GPIOA_B_X_MODER|=(Analog<<pin*2);
								break;
			}
			break;
/*************************************************************************************/
			case	PORTB:
					switch(Direction)
					{
					case	input :	GPIOB->GPIOA_B_X_MODER&=~(0b11<<pin*2);
									GPIOB->GPIOA_B_X_MODER|=(input<<pin*2);
									switch(direction_type)
									{
									// make masking then set
									case No_pull_up:	GPIOB->GPIOA_B_X_PUPDR&=~(0b11<<pin); GPIOB->GPIOA_B_X_PUPDR&=~(No_pull_up<<pin*2); break;
									case Pull_up:		GPIOB->GPIOA_B_X_PUPDR&=~(0b11<<pin); GPIOB->GPIOA_B_X_PUPDR|=(Pull_up<<pin*2);break;
									case Pull_down:		GPIOB->GPIOA_B_X_PUPDR&=~(0b11<<pin); GPIOB->GPIOA_B_X_PUPDR|=(Pull_down<<pin*2); break;
									}
									break;

					case	output	:	GPIOB->GPIOA_B_X_MODER&=~(0b11<<pin*2);
										GPIOB->GPIOA_B_X_MODER|=(output<<pin*2);
										break;

					case	AF :	GPIOB->GPIOA_B_X_MODER&=~(0b11<<pin*2);
									GPIOB->GPIOA_B_X_MODER|=(AF<<pin*2);
									switch(direction_type)
									{
										// make masking then set
										case No_pull_up:	GPIOB->GPIOA_B_X_PUPDR&=~(0b11<<pin);GPIOB->GPIOA_B_X_PUPDR&=~(No_pull_up<<pin*2); break;
										case Pull_up:		GPIOB->GPIOA_B_X_PUPDR&=~(0b11<<pin); GPIOB->GPIOA_B_X_PUPDR|=(Pull_up<<pin*2);break;
										case Pull_down:		GPIOB->GPIOA_B_X_PUPDR&=~(0b11<<pin); GPIOB->GPIOA_B_X_PUPDR|=(Pull_down<<pin*2); break;
									}
									switch(Out_direction_type)
									{
										case Output_push_pull:	GPIOB->GPIOx_OTYPER&=~(1<<pin); break;
										case Output_open_drain:	GPIOB->GPIOx_OTYPER|=(1<<pin); break;

									}

							break;


					case	Analog :	GPIOB->GPIOA_B_X_MODER&=~(0b11<<pin*2);
										GPIOB->GPIOA_B_X_MODER|=(Analog<<pin*2);
										break;
					}
			break;
/***********************************************************************************/
			case	PORTC:
					switch(Direction)
					{
					case	input :	GPIOC->GPIOA_B_X_MODER&=~(0b11<<pin*2);
									GPIOC->GPIOA_B_X_MODER|=(input<<pin*2);
									switch(direction_type)
									{
									// make masking then set
									case No_pull_up:	GPIOC->GPIOA_B_X_PUPDR&=~(0b11<<pin); GPIOC->GPIOA_B_X_PUPDR&=~(No_pull_up<<pin*2); break;
									case Pull_up:		GPIOC->GPIOA_B_X_PUPDR&=~(0b11<<pin); GPIOC->GPIOA_B_X_PUPDR|=(Pull_up<<pin*2);break;
									case Pull_down:		GPIOC->GPIOA_B_X_PUPDR&=~(0b11<<pin); GPIOC->GPIOA_B_X_PUPDR|=(Pull_down<<pin*2); break;
									}
									break;


					case	output	:	GPIOC->GPIOA_B_X_MODER&=~(0b11<<pin*2);
										GPIOC->GPIOA_B_X_MODER|=(output<<pin*2);
										break;

					case	AF :	//GPIOC->GPIOA_B_X_MODER&=~(0b11<<pin*2);
									GPIOC->GPIOA_B_X_MODER|=(0b10<<pin*2);
									switch(direction_type)
									{
										// make masking then set
										case No_pull_up:	GPIOC->GPIOA_B_X_PUPDR&=~(0b11<<pin);GPIOC->GPIOA_B_X_PUPDR&=~(No_pull_up<<pin*2); break;
										case Pull_up:		GPIOC->GPIOA_B_X_PUPDR&=~(0b11<<pin); GPIOC->GPIOA_B_X_PUPDR|=(Pull_up<<pin*2);break;
										case Pull_down:		GPIOC->GPIOA_B_X_PUPDR&=~(0b11<<pin); GPIOC->GPIOA_B_X_PUPDR|=(Pull_down<<pin*2); break;
									}
									switch(Out_direction_type)
									{
										case Output_push_pull:	GPIOC->GPIOx_OTYPER&=~(1<<pin); break;
										case Output_open_drain:	GPIOC->GPIOx_OTYPER|=(1<<pin); break;

									}

									break;
					case	Analog :	GPIOC->GPIOA_B_X_MODER&=~(0b11<<pin*2);
										GPIOC->GPIOA_B_X_MODER|=(Analog<<pin*2);
										break;
					}
			break;

/**************************************************************************************/
			case	PORTD:
							switch(Direction)
							{
							case	input :	GPIOD->GPIOA_B_X_MODER&=~(0b11<<pin*2);
											GPIOD->GPIOA_B_X_MODER|=(input<<pin*2);
											switch(direction_type)
											{
											// make masking then set
											case No_pull_up:	GPIOD->GPIOA_B_X_PUPDR&=~(0b11<<pin); GPIOD->GPIOA_B_X_PUPDR&=~(No_pull_up<<pin*2); break;
											case Pull_up:		GPIOD->GPIOA_B_X_PUPDR&=~(0b11<<pin); GPIOD->GPIOA_B_X_PUPDR|=(Pull_up<<pin*2);break;
											case Pull_down:		GPIOD->GPIOA_B_X_PUPDR&=~(0b11<<pin); GPIOD->GPIOA_B_X_PUPDR|=(Pull_down<<pin*2); break;
											}

											break;

							case	output	:	GPIOD->GPIOA_B_X_MODER&=~(0b11<<pin*2);
												GPIOD->GPIOA_B_X_MODER|=(output<<pin*2);
												break;

							case	AF :	GPIOD->GPIOA_B_X_MODER&=~(0b11<<pin*2);
											GPIOD->GPIOA_B_X_MODER|=(AF<<pin*2);
											switch(direction_type)
											{
												// make masking then set
												case No_pull_up:	GPIOD->GPIOA_B_X_PUPDR&=~(0b11<<pin);GPIOD->GPIOA_B_X_PUPDR&=~(No_pull_up<<pin*2); break;
												case Pull_up:		GPIOD->GPIOA_B_X_PUPDR&=~(0b11<<pin); GPIOD->GPIOA_B_X_PUPDR|=(Pull_up<<pin*2);break;
												case Pull_down:		GPIOD->GPIOA_B_X_PUPDR&=~(0b11<<pin); GPIOD->GPIOA_B_X_PUPDR|=(Pull_down<<pin*2); break;
											}
											switch(Out_direction_type)
											{
												case Output_push_pull:	GPIOD->GPIOx_OTYPER&=~(1<<pin); break;
												case Output_open_drain:	GPIOD->GPIOx_OTYPER|=(1<<pin); break;

											}


											break;

							case	Analog :	GPIOD->GPIOA_B_X_MODER&=~(0b11<<pin*2);
												GPIOD->GPIOA_B_X_MODER|=(Analog<<pin*2);
												break;
							}
					break;


/***************************************************************************************/
					case	PORTE:
							switch(Direction)
							{
							case	input :	GPIOE->GPIOA_B_X_MODER&=~(0b11<<pin*2);
											GPIOE->GPIOA_B_X_MODER|=(input<<pin*2);
											switch(direction_type)
											{
											// make masking then set
											case No_pull_up:	GPIOE->GPIOA_B_X_PUPDR&=~(0b11<<pin); GPIOE->GPIOA_B_X_PUPDR&=~(No_pull_up<<pin*2); break;
											case Pull_up:		GPIOE->GPIOA_B_X_PUPDR&=~(0b11<<pin); GPIOE->GPIOA_B_X_PUPDR|=(Pull_up<<pin*2);break;
											case Pull_down:		GPIOE->GPIOA_B_X_PUPDR&=~(0b11<<pin); GPIOE->GPIOA_B_X_PUPDR|=(Pull_down<<pin*2); break;
											}
											break;

							case	output	:	GPIOE->GPIOA_B_X_MODER&=~(0b11<<pin*2);
												GPIOE->GPIOA_B_X_MODER|=(output<<pin*2);
												break;

							case	AF :	GPIOE->GPIOA_B_X_MODER&=~(0b11<<pin*2);
											GPIOE->GPIOA_B_X_MODER|=(AF<<pin*2);
											switch(direction_type)
											{
												// make masking then set
												case No_pull_up:	GPIOE->GPIOA_B_X_PUPDR&=~(0b11<<pin);GPIOE->GPIOA_B_X_PUPDR&=~(No_pull_up<<pin*2); break;
												case Pull_up:		GPIOE->GPIOA_B_X_PUPDR&=~(0b11<<pin); GPIOE->GPIOA_B_X_PUPDR|=(Pull_up<<pin*2);break;
												case Pull_down:		GPIOE->GPIOA_B_X_PUPDR&=~(0b11<<pin); GPIOE->GPIOA_B_X_PUPDR|=(Pull_down<<pin*2); break;
											}
											switch(Out_direction_type)
											{
												case Output_push_pull:	GPIOE->GPIOx_OTYPER&=~(1<<pin); break;
												case Output_open_drain:	GPIOE->GPIOx_OTYPER|=(1<<pin); break;

											}
											break;

							case	Analog :	GPIOE->GPIOA_B_X_MODER&=~(0b11<<pin*2);
												GPIOE->GPIOA_B_X_MODER|=(Analog<<pin*2);
												break;
							}
					break;

		}
	}
	else
	{
		// error handling
	}
}

void	DIO_voidSetPinSpeed(u8 port, u8 pin, u8 Speed)
{
	if((port<=PORTE)&&(pin<=15))
	{
		switch(port)
		{
		case	PORTA:
			switch(Speed)
			{
			case Low_speed: 		GPIOA->GPIOx_B_OSPEEDR&=~(0b11<<pin*2);GPIOA->GPIOx_B_OSPEEDR|=(Low_speed<<pin*2); break;
			case Medium_speed:		GPIOA->GPIOx_B_OSPEEDR&=~(0b11<<pin*2);GPIOA->GPIOx_B_OSPEEDR|=(Medium_speed<<pin*2); break;
			case High_speed: 		GPIOA->GPIOx_B_OSPEEDR&=~(0b11<<pin*2);GPIOA->GPIOx_B_OSPEEDR|=(High_speed<<pin*2);	break;
			case Very_high_speed:	GPIOA->GPIOx_B_OSPEEDR&=~(0b11<<pin*2);GPIOA->GPIOx_B_OSPEEDR|=(Very_high_speed<<pin*2);	break;
			}
		break;

		case	PORTB:
		switch(Speed)
		{
		case Low_speed: 		GPIOB->GPIOx_B_OSPEEDR&=~(0b11<<pin*2);GPIOB->GPIOx_B_OSPEEDR|=(Low_speed<<pin*2); break;
		case Medium_speed:		GPIOB->GPIOx_B_OSPEEDR&=~(0b11<<pin*2);GPIOB->GPIOx_B_OSPEEDR|=(Medium_speed<<pin*2); break;
		case High_speed: 		GPIOB->GPIOx_B_OSPEEDR&=~(0b11<<pin*2);GPIOB->GPIOx_B_OSPEEDR|=(High_speed<<pin*2);	break;
		case Very_high_speed:	GPIOB->GPIOx_B_OSPEEDR&=~(0b11<<pin*2);GPIOB->GPIOx_B_OSPEEDR|=(Very_high_speed<<pin*2);	break;
		}
		break;

		case	PORTC:
		switch(Speed)
		{
		case Low_speed: 		GPIOC->GPIOx_B_OSPEEDR&=~(0b11<<pin*2);GPIOC->GPIOx_B_OSPEEDR|=(Low_speed<<pin*2); break;
		case Medium_speed:		GPIOC->GPIOx_B_OSPEEDR&=~(0b11<<pin*2);GPIOC->GPIOx_B_OSPEEDR|=(Medium_speed<<pin*2); break;
		case High_speed: 		GPIOC->GPIOx_B_OSPEEDR&=~(0b11<<pin*2);GPIOC->GPIOx_B_OSPEEDR|=(High_speed<<pin*2);	break;
		case Very_high_speed:	GPIOC->GPIOx_B_OSPEEDR&=~(0b11<<pin*2);GPIOC->GPIOx_B_OSPEEDR|=(Very_high_speed<<pin*2);	break;
		}
		break;

		case	PORTD:
		switch(Speed)
		{
		case Low_speed: 		GPIOD->GPIOx_B_OSPEEDR&=~(0b11<<pin*2);GPIOD->GPIOx_B_OSPEEDR|=(Low_speed<<pin*2); break;
		case Medium_speed:		GPIOD->GPIOx_B_OSPEEDR&=~(0b11<<pin*2);GPIOD->GPIOx_B_OSPEEDR|=(Medium_speed<<pin*2); break;
		case High_speed: 		GPIOD->GPIOx_B_OSPEEDR&=~(0b11<<pin*2);GPIOD->GPIOx_B_OSPEEDR|=(High_speed<<pin*2);	break;
		case Very_high_speed:	GPIOD->GPIOx_B_OSPEEDR&=~(0b11<<pin*2);GPIOD->GPIOx_B_OSPEEDR|=(Very_high_speed<<pin*2);	break;
		}
		break;

		case	PORTE:
		switch(Speed)
		{
		case Low_speed: 		GPIOE->GPIOx_B_OSPEEDR&=~(0b11<<pin*2);GPIOE->GPIOx_B_OSPEEDR|=(Low_speed<<pin*2); break;
		case Medium_speed:		GPIOE->GPIOx_B_OSPEEDR&=~(0b11<<pin*2);GPIOE->GPIOx_B_OSPEEDR|=(Medium_speed<<pin*2); break;
		case High_speed: 		GPIOE->GPIOx_B_OSPEEDR&=~(0b11<<pin*2);GPIOE->GPIOx_B_OSPEEDR|=(High_speed<<pin*2);	break;
		case Very_high_speed:	GPIOE->GPIOx_B_OSPEEDR&=~(0b11<<pin*2);GPIOE->GPIOx_B_OSPEEDR|=(Very_high_speed<<pin*2);	break;
		}
		break;
		}
	}
}


void	DIO_voidSetPinValue(u8 port, u8 pin, u8 Value)
{
	if((port<=PORTE)&&(pin<=15))
		{
			if (Value == High)
			{

				switch(port)
				{
				case PORTA: GPIOA->GPIOx_BSRR=1<<pin; break;
				case PORTB: GPIOB->GPIOx_BSRR=1<<pin; break;
				case PORTC: GPIOC->GPIOx_BSRR=1<<pin; break;
				case PORTD: GPIOD->GPIOx_BSRR=1<<pin; break;
				case PORTE: GPIOE->GPIOx_BSRR=1<<pin; break;
				}
			}
			else if (Value == Low)
			{
				switch(port)
				{
				case PORTA: GPIOA->GPIOx_BSRR=(1<<(pin+16)); break;
				case PORTB: GPIOB->GPIOx_BSRR=(1<<(pin+16)); break;
				case PORTC: GPIOC->GPIOx_BSRR=(1<<(pin+16)); break;
				case PORTD: GPIOD->GPIOx_BSRR=(1<<(pin+16)); break;
				case PORTE: GPIOE->GPIOx_BSRR=(1<<(pin+16)); break;
				}
			}
		}

}

u8		DIO_u8GetPinValue(u8 port, u8 pin)
{
	u8 value = 0x99;
	switch (port)
	{
	case PORTA: value= GET_Bit(GPIOA->GPIOx_IDR,pin); break;
	case PORTB: value= GET_Bit(GPIOB->GPIOx_IDR,pin); break;
	case PORTC: value= GET_Bit(GPIOC->GPIOx_IDR,pin); break;
	case PORTD: value= GET_Bit(GPIOD->GPIOx_IDR,pin); break;
	case PORTE: value= GET_Bit(GPIOE->GPIOx_IDR,pin); break;

	}
	return value;

}


void AF_Select_pin_Fun(u8 port ,u8 pin , u8 Fun)
{
	if(pin<8)
	{
		switch (port)
		{
			case PORTA:	GPIOA->GPIOx_AFRL|=(Fun<<pin*4); break;
			case PORTB:	GPIOB->GPIOx_AFRL|=(Fun<<pin*4); break;
			case PORTC:	GPIOC->GPIOx_AFRL|=(Fun<<pin*4); break;
			case PORTD:	GPIOD->GPIOx_AFRL|=(Fun<<pin*4); break;
			case PORTE:	GPIOE->GPIOx_AFRL|=(Fun<<pin*4); break;
		}
	}
	else if (pin<16)
		pin-=8;
	{
		switch (port)
		{
			case PORTA:	GPIOA->GPIOx_AFRH|=(Fun<<pin*4); break;
			case PORTB:	GPIOB->GPIOx_AFRH|=(Fun<<pin*4); break;
			case PORTC:	GPIOC->GPIOx_AFRH|=(Fun<<pin*4); break;
			case PORTD:	GPIOD->GPIOx_AFRH|=(Fun<<pin*4); break;
			case PORTE:	GPIOE->GPIOx_AFRH|=(Fun<<pin*4); break;

		}
	}
}
