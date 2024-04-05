/*************************************************************************************/
/* Auther         : Ahmed Nour                                                   */
/* Date           : 29/10/2023                                                       */
/* Version        : 1.0.0                                                              */
/*sw              : Bootloader                                                            */
/*************************************************************************************/

#ifndef BOOTLOADER_INTERFACE_H_
#define BOOTLOADER_INTERFACE_H_


#define FLASH_START  0x08000000
#define FLASH_END    0x08008000
typedef void (*Function_t)(void);


void Bootloader_Jump_To_Application1(u32 address);
void Bootloader_Jump_To_Application();
void BootLocationEreas() ;
void Bootloader_voidfReciveFlash1(u8 A_u8SectorNo);
void Bootloader_voidfReciveFlash();
void Bootloader_Init();


/****************************************************/
void  bootloader_disable_interrupt();
void Bootloader_voidFlashRunnable();

typedef enum
{
	BOOT_WAITING,
	BOOT_CHECKFORUPDATE,
	BOOT_CHECKSTATE,
	BOOT_RECEIVINGHEX,
	BOOT_JUMPTOTHEMAINAPP,
	BOOTERROR,
	BOOTREQESTHEX


}BootloaderStates_t;


#endif /* BOOTLOADER_INTERFACE_H_ */
