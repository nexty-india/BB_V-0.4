#ifndef __SUPPRESSION_SETTING_H_
#define __SUPPRESSION_SETTING_H_
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdarg.h>
#include <stdbool.h>
#include "Modbus_Comm.h"
#include "Relay_Status.h"
#include "Modbus_Status.h"
#include "PID_Sensor_Status.h"
#include "AI1_Sensor_Status.h"
#include "Application_Holding_Register.h"
#include "Application_Input_Register.h"
#include "MotorDriverlayer.h"

#define  VDC_FILT_FACTOR	6
typedef struct{
	bool Winding_temperature_Supress;
	bool IGBT_Temperature_Supress;
	bool Current_Sup;
}Supression_t;


typedef struct{
	
	float Ipmt_Suppressionfactor;
	float Ipmt_RampRate;
	float Sup_MinCurrent;
	float CurrentCutoff;
	uint16_t Ipmt_TaregetSpeed;
	uint16_t Curr_TargetSpeed;
	uint16_t Wind_TargetSpeed;
	uint16_t Sup_MinTemperatureigbt;
	uint16_t Sup_MinTemperatruewind;

	uint16_t Final_TargetSpeed;
}IPMSuprresion_t;


typedef struct{
	uint16_t IpmTemperature;
	uint16_t WindTempertaure;
	float ActualCurrent;
	uint16_t MinSpeed;
	uint16_t ActualSpeed;
}SuppresActual_t;



extern IPMSuprresion_t IPM_Supp;


extern Supression_t SuppressionSet;

extern SuppresActual_t SuppresActual;

int DC_Filter(void);
void IPMTemperatureDegrating(void);
void SuppressionSelection(void);
void Suppression(void);
#endif
