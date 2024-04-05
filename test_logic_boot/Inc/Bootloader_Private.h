/*************************************************************************************/
/* Auther         : Mohamed Hoasm                                                    */
/* Date           : 15/10/2023                                                       */
/* Version        : 1.0                                                              */
/*sw              : Bootloader                                                            */
/*************************************************************************************/

#ifndef BOOTLOADER_PRIVATE_H_
#define BOOTLOADER_PRIVATE_H_

#define HEXFILESIZE	40

void RX_Fun(void);

void Bootloader_HandelFlames(void);

static void Bootloader_StateMachienChangeToApp();

static Bool_t localBootloader_updateAvailable(void);


#endif /* BOOTLOADER_PRIVATE_H_ */
