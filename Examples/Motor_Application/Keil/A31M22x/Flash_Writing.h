#ifndef _FLASH_WRITING_H_
#define _FLASH_WRITING_H_



#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdarg.h>
#include "Define.h"
#include <stdbool.h>

#include "A31M22x_cfmc.h"
#include "debug_frmwrk.h"
#include "BHARAT_BIJLEEE.h"

#define Holding_Register_Total      184
#define FLASH_MAGIC        0xA55A
#define FLASH_INVALID      0xFFFF

#define FLASH_FLAG_OFFSET  0
#define FLASH_DATA_OFFSET  4

/* Select backup region relative to active */
#define FLASH_BACKUP_OFFSET   0x800   // adjust per sector size



typedef enum{
	READ_ACTUAL_FLASH_VALUE = 0,
	DEFAULT_FLASH_SETTING ,
	WRITE_ACTUAL_VALUE_SETTING,
	//WRITE_CONTROL_VALUE_SETT,
}FlashState_t;


extern uint16_t g_Default_Write,g_Flash_Write;
extern FlashState_t FLASHSTATE;
void Data_write_to_flash(uint32_t Start_Address,uint32_t Size,uint16_t * data);

void FlashWriting(void);
uint32_t Read_Flash_U32(uint32_t Address);
#endif
