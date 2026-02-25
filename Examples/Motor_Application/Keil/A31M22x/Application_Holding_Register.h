#ifndef __USER_APPLICATION_HOLDING_REGISTER_H_
#define __USER_APPLICATION_HOLDING_REGISTER_H_
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdarg.h>
#include <stdbool.h>




#define	ANALOG_FLAG 		1
#define	PID_Flag   			2
#define	MODBUS_FLAG 		3
#define BMS_FLAG				4
#define CONTROL_BIT 		5


#define DC_VOLTAGE_SUPRESS 							50
#define WINDING_TEMPERATURE_SUPRESS 		50
#define IGBT_TEMPERATURE_SUPRESS 				50
#define MOTOR_CURRENT_SUPRESS 					50
//#define VDC_FILT_FACTOR									10
typedef enum{
	FORWARD_DIRECTION=0,
	REVERSE_DIRECTION,
}FAN_DIRECTION;

typedef enum{
	NONE_SELECT = 0,
	R1_ONLY = 1,
	R2_ONLY = 2,
	R1_R2 = 3,
	R3_ONLY = 4,
	R1_R3 = 5,
	R2_R3 = 6,
	R1_R2_R3 = 7,
	R4_ONLY = 8,
	R1_R4 = 9,
	R2_R4 = 10,
	R1_R2_R4 = 11,
	R3_R4 = 12,
	R1_R3_R4 = 14,
	R2_R3_R4 = 15,
	R1_R2_R3_R4 = 16,
}SUPPRESSION_RANGE_t;

typedef enum{
	NO_SELECT = 0,
	SET_INTERNAL_SPEED_1,
	SET_INTERNAL_SPEED_2,
	SET_INTERNAL_SPEED_3,
}InternalRpm_t;


typedef enum{
	TmpMGMT_Disable = 0,
	BYPASS_TMP_IGBT,
	BYPASS_TMP_WINDING,
	BYPASS_TMP_BOTH,
}BypassTMPMGMT_t;

typedef enum{
	AI1_FAILSAFE = 0,
	AI2_FAILSAFE,
}FailSafe_t;



typedef enum{
	LED_OFF,
	LED_ON,
}LED_MODE_t;


typedef enum{
	NO_SENSOR = 0,
	DIFFERENTIAL_TEMPERATURE_SENSOR,
	DIFFERENTIAL_PRESSURE_SENSOR,
	FLOW_SENSOR,
}SENSOR_SEL_t;


typedef struct{
	uint16_t voltage_temp;
	uint16_t VDC_Filter;
	uint32_t Temp_VDC_factor;
}VdcFilt_t;




typedef struct{
	bool PID_FLAG_BIT;
	bool MODBUS_FLAG_BIT;
	bool ANALOG_FLAG_BIT;
	bool DI1_CHECK_BIT;
	bool CONTRO_BIT_CHECK;
	bool BMS_CHECK_BIT;
}ControlMode_t;

extern VdcFilt_t vdcfilt;

extern ControlMode_t controlmode;
extern InternalRpm_t InternalRPM;
extern BypassTMPMGMT_t BypassTmppmgmt;
extern bool g_BYPASS_TMP_IGBT,g_BYPASS_TMP_WINDING;

int ContorlBitSystem(void);
int SET_SPEED_MODBUS_SIGNAL_LOSS_MODE(void);
int FailSafeControl(void);
int MAXIMUM_SPEED(void);
int MINIMUM_SPEED(void);
int FAN_ROTATION(void);
void SWITCHING_FREQUENCY(void);
void SuppressionSelection(void);
int SET_INTERNAL_RPM_1(void);
int SET_INTERNAL_RPM_2(void);
int SET_INTERNAL_RPM_3(void);
void LED_MODE_INDICATION(void);
void NodeAddresInit(void);

#endif
