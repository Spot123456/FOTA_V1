/*************************************************************************************/
/* Auther         : Ahmed Nour                                                   */
/* Date           : 29/10/2023                                                       */
/* Version        : 1.0.0                                                              */
/*sw              : Bootloader                                                            */
/*************************************************************************************/
#ifndef BOOTLOADER_CONF_H_
#define BOOTLOADER_CONF_H_




/************************************/
// Flash memory base addresses
#define FLASH_BASE_ADDRESS 0x08004000
#define FLASH_BASE_ADDRESSTest 0x08000000
#define FLASH_RESET_HANDLER (FLASH_BASE_ADDRESS + 0x00000004)
#define TIMEOUTDEALY 10000000   // 5sec

#define  FLASH_ERASE_SIZE 10

#define  HEXFILESIZE 40



/*************************************************/
// Location of Updates

#define   BOOT_FLASHMARK          0xAA55
#define   BOOT_DDRESSMARK         0x08008000


/*************************************************/


//******************************************************
// local_u16DataCheckOverFrame
// over frame cases

#define BOOT_FRAMECASE_FLASHING      0xAAAA



#endif /* BOOTLOADER_CONF_H_ */
