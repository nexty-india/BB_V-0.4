#ifndef _AI1_Sensor_Status_H_
#define _AI1_Sensor_Status_H_




#include "Bharat_Bijleee.h"
#include "MotorDriverLayer.h"
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdarg.h>

#define ADC_LPF_FILTER_FACTOR 6

#define V_BASE    5
#define R_158    110
#define R_159		 110
#define R_152    110 
#define R_156    330
#define R_IN 		 (R_158+R_159+R_152)
#define R_OUT     R_156

#define TOTAL_ADC_COUNT 4096
#define POTENIOMETER_LOW_VLAUE  110
#define POTENIOMETER_HIGH_VLAUE 4050



extern uint16_t g_Fail_safe_status;
extern uint16_t g_Pot_voltage_filt;
extern uint16_t g_AI1_Volts_Value;
extern uint16_t g_AI1_Calculated_RPM;

static int ANALOG_SENSE_0_10_VOLT_RAW(void);
 int ANALOG_SENSE_0_10_VOLT_FILT(void);
static int Calcuate_RPM_0_10_Volt(void);
 void ANALOG_CONTROL_MODE(void);
void ANALOG_CONTORL_RPM_ENABLE(void);
int Volts_10(void);
#endif
