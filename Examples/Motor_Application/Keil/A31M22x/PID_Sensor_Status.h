#ifndef _HOLDING_AND_INPUT_REGISTER_H_
#define _HOLDING_AND_INPUT_REGISTER_H_

#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdarg.h>
#include <stdbool.h>
#include "MotorDriverLayer.h"


extern uint16_t Analog_4_20_ma_filt;
static int PID_SENSOR_EXECUTE(void);
static int ANALOG_DIFFERENTIAL_PID_MODE(void);
static int ANALOG_TEMPERATURE_PID_MODE(void);
static int ANALOG_FLOW_SENSOR_PID_MODE(void);
static int ANALOG_SENSE_4_20MA(void);
static int ANALOG_SENSE_4_20MA_FILT(void);
static void PID_Sensor_RPM_ENABLE(void); 

#endif
