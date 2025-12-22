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



typedef enum{
	READ_ACTUAL_FLASH_VALUE = 0,
	DEFAULT_FLASH_SETTING ,
	WRITE_ACTUAL_VALUE_SETTING,
}FlashState_t;


extern uint32_t g_Actal_value_read,g_Actal_read;
extern FlashState_t FLASHSTATE;
void Data_write_to_flash(uint32_t Start_Address,uint32_t Size,uint32_t * data);

void FlashWriting(void);
uint32_t Read_Flash_U32(uint32_t Address);
#endif
