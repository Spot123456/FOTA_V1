



#ifndef			_STD_TYPES_H
#define 		_STD_TYPES_H


typedef		unsigned char			u8;
typedef		unsigned short	int		u16;
typedef		unsigned int			u32;
typedef		unsigned long	int		u64;

typedef		signed char				s8;
typedef		signed short	int		s16;
typedef		signed int				s32;
typedef		signed long		int		s64;

typedef							float	f32;
typedef							double	f64;


#define PORTA		0
#define PORTB		1
#define PORTC		2
#define PORTD		3
#define PORTE		4

typedef enum{
	FALSE=0X55,
	TRUE=0X80
}Bool_t;

typedef enum{
	OK=0,
	NOK,
	OUT_OF_RANGE,
	NULL_PTR

}Error_t;



#endif
