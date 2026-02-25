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
#include "Fault_Status.h"
#define Power_Filter_FACTOR							16
#define Current_Filter_Factor   				6
#define DcVoltage_Filter_Factor         10
#define SECONDTOHOURFACTOR							3600 
#define MILLI_TO_SEC										999
#define SEC_TO_MIN											59
#define MIN_TO_HOUR											59
#define POWERCAL_FACTOR									10

typedef struct{
	uint32_t Hourcounter;
	uint32_t Minutecounter;
	uint16_t Secondcounter;
}PowerCounter_t;

typedef struct
{
    uint16_t seconds;
    uint16_t minutes;
    uint16_t hours;
} RunTimeFlash_t;


typedef struct{
	uint32_t FilterHourCounter;
	uint32_t FilterMinuteCounter;
	uint16_t FilterSecondCounter;
}FilterCounter_t;


typedef struct{
	uint16_t seconds;
	uint16_t minutes;
	uint16_t hours;
}FilterrunFlash_t;

typedef struct {
	uint32_t RemHourCounter;
	uint16_t RemMinuteCounter;
	uint16_t RemSecCounter;
}RemainingTimer_t;

typedef struct{
	uint16_t seconds;
	uint16_t minutes;
	uint16_t hours;
}RemTimer_t;


extern RemainingTimer_t remtimer;
extern RemTimer_t rementimer;
extern RunTimeFlash_t runtime;
extern PowerCounter_t counter;
extern FilterrunFlash_t Filterrunner;
extern FilterCounter_t Filtercounter;
extern bool g_flash_check,g_FilterFlash,g_flash_rem,Remain_check;
extern uint16_t g_milliseconscounter,g_milliseconscounter_Remaing,g_PowerFilt;;
extern uint32_t g_tesecondcounter;
extern uint16_t g_currentFilt;
void HourCounterInit(void);
void HourCounterCheck(void) ;
void PowerFilterCal(void);
void HourCounter(void);
void Current_Filt(void);
void SystemHourStatus(void);
int PowerCalculation(void);
void FilterParameter(void);
void LoadPercentage(void);
void ResetFilterStatus(void);
void FilterStatus(void);
void RemainingHour(void);
#endif
