#ifndef _FAULT_STATUS_H_
#define _FAULT_STATUS_H_

#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdarg.h>
#include <stdbool.h>

#include "user_timer.h"
#include "Modbus_Status.h"

#define OVER_VOLTAGE_FAULT_COUNTER    						100
#define UNDER_VOLTAGE_FAULT_COUNTER    						100
#define OVER_LOAD_FAULT_COUNTER    								100
#define OVER_SPEED_FAULT_COUNTER    							100
#define OVER_IPM_TEMPERATURE_FAULT_COUNTER    		1000
#define OVER_WINDING_TEMPERATURE_FAULT_COUNTER    1000
#define OVER_RMS_VOLTAGE_FAULT_COUNTER						100
#define UNDER_RMS_VOLTAGE_FAULT_COUNTER						100

#define OVER_VOLTAGE_FAULT_RECOVERY_COUNTER    						75000
#define UNDER_VOLTAGE_FAULT_RECOVERY_COUNTER    					75000
#define OVER_LOAD_FAULT_RECOVERY_COUNTER    							75000
#define OVER_SPEED_FAULT_RECOVERY_COUNTER    							75000
#define ROTOR_LOCK_FAULT_RECOVERY_COUNTER         				8000
#define OVER_IPM_TEMPERATURE_RECOVERY_FAULT_COUNTER    		75000
#define OVER_WINDING_TEMPERATURE_RECOVERY_FAULT_COUNTER   75000
#define OVER_RMS_VOLTAGE_RECOVERY_FAULT_COUNTER						75000
#define UNDER_RMS_VOLTAGE_RECOVERY_FAULT_COUNTER					75000
#define ROTOR_STATUS_CHECK_COUNTER												4000

#define BYPASS_OCURRNET   (1<<0)
#define BYPASS_DCUNDERVOLTAG  (1<<1)
#define BYPASS_ROTORLOCK   (1<<2)
#define BYPASS_IPMTEMP     (1<<3)
#define BYPASS_WINDTEMP    (1<<4)
#define BYPASS_ACOVERVOLTAGE  (1<<5)

typedef union{
	struct{
			bool CriticalOverCurrent_Fault  : 1;
			bool CriticalOverVoltage_Fault  : 1;
		  bool overCurrent_Fault					:	1;
		  bool UnderVoltage_Fault					: 1;
		  bool OverLoad_Fault             : 1;
		  bool OverSpeed_Fault						: 1;
			bool RotorLock_Fault						: 1;
			bool IGBTTemperatue_Fault				: 1;
			bool WindingTemperature_Fault		: 1;
			bool ACLineBreak_Fault					: 1;
			bool ModbusCommunication_Fault	: 1;
			bool FireSignal_Fault						: 1;
		  bool StaticPressureFilter       : 1;
		  bool OverRMSVoltage_Fault				: 1;
		  //bool UnderRMSVoltage_Fault		  : 1;
	}Fault_bits;
	uint16_t Fault_Count;
}Fault_Flag;



typedef enum{
	FAULT_CRITICALOVERCURRENT=0, 					
	FAULT_CRITICALOVERVOLTAGE,			  
	FAULT_OVERCURRENT,
	FAULT_UNDERVOLTAGE,			
	FAULT_OVERLOAD ,		
	FAULT_OVERSPEED,	
	FAULT_ROTOR_LOCKED ,
	FAULT_IPM_TEMPERATURE,
	FAULT_MOTOR_TEMPERATURE,
	FAULT_AC_LINE_BREAK,
	FAULT_MODBUS_COMMUNICATION,
	FAULT_FIRE_SIGNAL	,
	FAULT_STATIC_PRESSURE_FILTER,
	FAULT_OVER_RMSVOLTAGE,
}SystemFaults_t;

typedef struct{

	uint16_t over_voltage_fault;
	uint16_t under_voltage_fault;
	uint16_t over_load_fault;
	uint16_t over_speed_fault;
	uint16_t over_Rms_Fault;
	uint16_t under_Rms_Fault;
	uint16_t motor_winding_temperature_fault;
	uint16_t ipm_temperature_fault;


	
	
	uint32_t over_voltage_recovery_fault;
	uint32_t under_voltage_recovery_fault;
	uint32_t overload_recovery_fault;
	uint32_t over_speed_recovery_fault;
	uint32_t Rotor_lock_recovery_fault;
	uint32_t motor_winding_temperature_recovery_fault;
	uint16_t ipm_temperature_recovery_fault;
	uint32_t over_Rms_recovery_Fault;
	uint32_t under_Rms_recovery_Fault;
}Counter_t;


typedef struct{
	bool BYPASS_OCURRNET_F;
bool BYPASS_DCUNDERVOLT_F;
bool BYPASS_ROTORLOCK_F;
bool BYPASS_IPMTEMP_F;
bool BYPASS_WINDTEMP_F;
bool BYPASS_ACOVERVOLT_F;
}BYPASS_flag_t;


extern uint16_t Fault_count;
extern bool g_triesout;
extern uint8_t rotolock,g_roto_counter,g_Rotorclear;
extern BYPASS_flag_t bypass_Fl;
extern uint16_t FaultBypass,g_motor_rotorlock_recovery_limit;
extern bool g_per_off;
extern bool g_Fault_Clear;
extern Counter_t delay_counter;
extern Fault_Flag Fault;
void FaultIndication(void);
void FaultRecieve(void);
void DC_Under_VoltageFault(void);
void OverLoadFault(void);
void OverSpeedFault(void);
void RecoveryRotorLock(void);
void IGBTTemperatureFault(void);
void WindingTemperatureFault(void);
void FireFault(void);
void OverRMSVoltageFault(void);
void ClearFaultCheck(void);
void BypassFault(void);
void OccRecFault(void);
void StaticPressureFilter(void);
#endif
