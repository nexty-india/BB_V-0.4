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


#define G_Counter 100
typedef struct{
	int TargetSetPoint;
	int Actual_SensorValue;
	float Kp_Constant;
	float Ki_Constant;
	float Control_Signal;
	int Error_siganl;
	float Target_Rpm;
	float Proportional_Output;
	float Integral_Output;
	int Control_signalMaxlimit;
	int Control_signalMinlimit;
	int Minumumrpm;
}PID_Sensor_t;


extern PID_Sensor_t pid_sensor;

extern uint16_t g_Analog_4_20_ma_filt;
int PidSensorCalculation(void);
static int ANALOG_SENSE_4_20MA(void);
static int ANALOG_SENSE_4_20MA_FILT(void);
void PIDinit(void);

#endif
