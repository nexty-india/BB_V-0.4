#ifndef _USER_RELAY_STATUS_H_
#define _USER_RELAY_STATUS_H_
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdarg.h>
#include "Define.h"
#include <stdbool.h>



typedef enum{
	RELAY_OFF = 0,
	RELAY_ON
}RelayStatus_t;


typedef enum{
	RUNNING_STATE = 1,
	K1_FAULT,
}K1Functon_t;


void RelayControl(void);
void K1FunctionSetting(void);

void RelayOperation(void);
#endif
