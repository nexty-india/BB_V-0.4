#ifndef __USER_APPLICATION_INPUT_REGISTER_H_
#define __USER_APPLICATION_INPUT_REGISTER_H_
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdarg.h>
#include <stdbool.h>
#include "Modbus_Comm.h"

#define Power_Filter_FACTOR			16
#define Current_Filter_Factor   6
#define SECONDTOHOURFACTOR			3600 

extern uint64_t g_runhourcountercur,g_powerrunhourcountercurr;
extern uint16_t g_Power_Filt,g_currentFilt;
void HourCounterInit(void);
void Power_Filter(void);
void HourCounterCheck(void) ;
void FlashHourSetting(void);
void Current_Filt(void);
void SystemHourStatus(void);
#endif
