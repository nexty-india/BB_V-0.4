#ifndef _BHARAT_BIJLEEE_H_
#define _BHARAT_BIJLEEE_H_

#include "Define.h"

#include "MotorApplicationLayer.h"
#include "Modbus_Comm.h"
#include "Fault_indication.h"
#include "user_statemachine.h"

#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdarg.h>

#include "user_timer.h"

#define NODEADDRESS							 0x0000F000U
#define ONE_MILLISECND_COUNTER   1000

typedef enum{
	INIT_STATE = 0,
	NORMAL_OPERATION_STATE = 1,
	FAULT_OPERATION_STATE = 2,
}DriveStatemachine_t;


//extern uint16_t g_One_millisecond;
void DriveStateMachine(void);
void DriveSystem(void);

extern DriveStatemachine_t DRIVESTATEMACHINE;


#endif
