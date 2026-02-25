#ifndef _MODBUS_Status_H_
#define _MODBUS_Status_H_
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdarg.h>
#include <stdbool.h>



typedef enum{
	MODBUS_INT = 0,
	MODBUS_W_R_MODE = 1,
	MODBUS_R_MODE,
}MOTOR_COMM_MODE;


extern uint16_t g_target_Speed;
extern uint8_t Control_mode;
static void MODBUS_STAUTS_CHECK(void);
void CONTROL_MODE_SELECT(void);
void READ_RPM_SET_STATUS(void);
void ControlModeOperation(void);
void SET_TARGET_SPEED_TO_MOTOR(void);
#endif
