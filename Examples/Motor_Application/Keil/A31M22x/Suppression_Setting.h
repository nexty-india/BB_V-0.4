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
	bool Motor_Current_Supress;
	bool Voltage_Supress;
	bool Winding_temperature_Supress;
	bool IGBT_Temperature_Supress;
	bool Lower_voltage_Supress;
	bool LowerAmbientTemperature_Supres;
	bool UpperAmbientTemperature_Supres;
	bool LowerVoltage_Supress;
	bool OverPower_Supress;
}Supression_t;


typedef struct{
	uint16_t Vd_VoltageFilt;
	uint16_t vd_MinSpeed;
	uint16_t vd_ActualSpeed;
	uint16_t vd_MaxVoltage;
	uint16_t vd_MinVoltage;
	float vd_Slope;
	uint16_t vd_intercept;
	uint16_t vd_DegratingStart;
	uint16_t vd_TargetSpeed;
}VoltageSuppresion_t;


typedef struct{
	uint16_t LVd_VoltageFilt;
	uint16_t Lvd_MinSpeed;
	uint16_t Lvd_ActualSpeed;
	uint16_t Lvd_MaxVoltage;
	uint16_t Lvd_MinVoltage;
	float Lvd_Slope;
	uint16_t Lvd_intercept;
	uint16_t Lvd_DegratingStart;
	uint16_t Lvd_TargetSpeed;
}LowerVoltageSuppresion_t;

typedef struct{
	uint16_t Id_CurrentFilt;
	uint16_t Id_MinSpeed;
	uint16_t Id_ActualSpeed;
	uint16_t Id_MaxCurrent;
	uint16_t Id_MinCurrent;
	float Id_Slope;
	uint16_t Id_intercept;
	uint16_t Id_Degratingoff;
	uint16_t Id_TargetSpeed;
}CurrentSuppresion_t;

typedef struct{
	uint16_t Wt_WindingTemperatueFilt;
	uint16_t Wt_MinSpeed;
	uint16_t Wt_ActualSpeed;
	uint16_t Wt_MaxTemperatue;
	uint16_t Wt_MinTemperatue;
	float Wt_Slope;
	uint16_t Wt_Intercept;
	uint16_t Wt_Degrating_off;
	uint16_t Wt_TaregetSpeed;
}WindingSuppression_t;


typedef struct{
	uint16_t Ipmt_IpmTemperatureFilt;
	uint16_t Ipmt_MinSpeed;
	uint16_t Ipmt_ActualSpeed;
	uint16_t Ipmt_MaxTemperatue;
	uint16_t Ipmt_MinTemperatue;
	float Ipmt_Slope;
	uint16_t Ipmt_Intercept;
	uint16_t Ipmt_Degrating_off;
	uint16_t Ipmt_TaregetSpeed;
}IPMSuprresion_t;

typedef struct{
	uint16_t OP_OverPowerFilt;
	uint16_t OP_MinSpeed;
	uint16_t OP_ActualSpeed;
	uint16_t OP_MaxOverPower;
	uint16_t OP_MinOverPower;
	float OP_Slope;
	uint16_t OP_Intercept;
	uint16_t OP_Degratingoff;
	uint16_t OP_TargetSpeed;
}OverPowerSuppression_t;

typedef struct{
	uint16_t LATMP_AmbientTempFilt;
	uint16_t LATMP_MinSpeed;
	uint16_t LATMP_ActualSpeed;
	uint16_t LATMP_MaxAmbientTemp;
	uint16_t LATMP_MinAmbientTemp;
	float LATMP_Slope;
	uint16_t LATMP_Intercept;
	uint16_t LATMP_Degratingoff;
	uint16_t LATMP_TargetSpeed;
}LowerAmbientTemperatureSuppression_t;

typedef struct{
	uint16_t UATMP_AmbientTempFilt;
	uint16_t UATMP_MinSpeed;
	uint16_t UATMP_ActualSpeed;
	uint16_t UATMP_MaxAmbientTemp;
	uint16_t UATMP_MinAmbientTemp;
	float UATMP_Slope;
	uint16_t UATMP_Intercept;
	uint16_t UATMP_Degratingoff;
	uint16_t UATMP_TargetSpeed;
}UpperAmbientTemperatureSuppression_t;


typedef struct{
	VoltageSuppresion_t  voltage_Supp;
	LowerVoltageSuppresion_t  lowvoltage_Supp;
	CurrentSuppresion_t  Current_Supp;
	WindingSuppression_t Winding_Supp;
	IPMSuprresion_t      IPM_Supp;
	OverPowerSuppression_t  OvPwr_Supp;
	LowerAmbientTemperatureSuppression_t  LAmTemp_Supp;
	UpperAmbientTemperatureSuppression_t  UAmTemp_Supp;
}Degrating_t;

extern Supression_t SuppressionSet;
extern Degrating_t degrating;

int DC_Filter(void);
void IPMTemperatureDegrating(void);
int AmbientTemperature(void);
void WindingTemperatureDegrating(void);
void LowerAmbientTemperatureDegrating(void);
void UpperAmbientTemperatureDegrating(void);
void OverPowerDegrating(void);
void VoltageDegrating(void);
void CurrentDegrating(void);
void LowerVoltageDegrating(void);
void SuppressionSelection(void);
void Suppression(void);
#endif
