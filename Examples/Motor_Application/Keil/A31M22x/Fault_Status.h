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

#define IGBT_TEMPERATURE_RECOVERY_FAULT     350
#define DC_VOLTAGE_MIN_RECOVERY_FAULT 			150
#define DC_VOLTAGE_MAX_RECOVERY_FAULT 			850
#define AC_VOLTAGE_MIN_RECOVERY_FAULT       200
#define AC_VOLTAGE_MAX_RECOVERY_FAULT				600
#define PEAK_CURRENT_RECOVERY_FAUTL					12
#define WINDING_TEMPERATURE_RECOVERY_FAULT  90
#define OVERLOAD_COUNTER_RECOVERY_FAUTL 5800



#define OVER_CURRENT_FAULT_COUNTER    						2000
#define OVER_VOLTAGE_FAULT_COUNTER    						75000
#define UNDER_VOLTAGE_FAULT_COUNTER    						75000
#define OVER_LOAD_FAULT_COUNTER    								75000
#define OVER_SPEED_FAULT_COUNTER    							75000
#define OVER_IPM_TEMPERATURE_FAULT_COUNTER    		75000
#define OVER_WINDING_TEMPERATURE_FAULT_COUNTER    75000
#define MODBUS_COMMUNICATION_FAULT_COUNTER        2000


#define OVER_CURRENT_FAULT_RECOVERY_COUNTER    						30000
#define OVER_VOLTAGE_FAULT_RECOVERY_COUNTER    						75000
#define UNDER_VOLTAGE_FAULT_RECOVERY_COUNTER    					75000
#define OVER_LOAD_FAULT_RECOVERY_COUNTER    							75000
#define OVER_SPEED_FAULT_RECOVERY_COUNTER    							75000
#define ROTOR_LOCK_FAULT_RECOVERY_COUNTER         				8000
#define OVER_IPM_TEMPERATURE_RECOVERY_FAULT_COUNTER    		75000
#define OVER_WINDING_TEMPERATURE_RECOVERY_FAULT_COUNTER   75000
#define MODBUS_COMMUNICATION_RECOVERY_FAULT_COUNTER        2000
#define AC_LINE_BREAK_RECOVERY_COUNTER										600000
#define ALL_FAULT_CLEAR																		30000

typedef union{
	struct{
			bool CriticalOverCurrent_Fault  : 1;
			bool CriticalOverVoltage_Fault  : 1;
		  bool OverVoltage_Fault					:	1;
		  bool UnderVoltage_Fault					: 1;
		  bool OverLoad_Fault             : 1;
		  bool OverSpeed_Fault						: 1;
			bool RotorLock_Fault						: 1;
			bool IGBTTemperatue_Fault				: 1;
			bool WindingTemperature_Fault		: 1;
			bool ACLineBreak_Fault					: 1;
			bool ModbusCommunication_Fault	: 1;
			bool FireSignal_Fault						: 1;
			bool PIDSensor_Fault						: 1;
	}Fault_bits;
	uint16_t Fault_Count;
}Fault_Flag;


typedef enum{
	FAULT_CRITICALOVERCURRENT=0, 					
	FAULT_CRITICALOVERVOLTAGE,			  
	FAULT_OVERVOLTAGE,
	FAULT_UNDERVOLTAGE,			
	FAULT_OVERLOAD ,		
	FAULT_OVERSPEED,	
	FAULT_ROTOR_LOCKED ,
	FAULT_MOTOR_TEMPERATURE,
	FAULT_IPM_TEMPERATURE,
	FAULT_AC_LINE_BREAK,
	FAULT_MODBUS_COMMUNICATION,
	FAULT_FIRE_SIGNAL	,
	FAULT_STATIC_PRESSURE_FILTER,
}SystemFaults_t;

typedef struct{
	uint32_t over_current_fault;
	uint32_t over_voltage_fault;
	uint32_t under_voltage_fault;
	uint32_t over_load_fault;
	uint32_t over_speed_fault;
	
	uint32_t motor_winding_temperature_fault;
	uint32_t ipm_temperature_fault;
	uint32_t phase_missing_fault;
	uint32_t Modbus_communication_fault;
	
	uint32_t over_current_recovery_fault;
	uint32_t over_voltage_recovery_fault;
	uint32_t under_voltage_recovery_fault;
	uint32_t overload_recovery_fault;
	uint32_t over_speed_recovery_fault;
	uint32_t Rotor_lock_recovery_fault;
	uint32_t motor_winding_temperature_recovery_fault;
	uint32_t ipm_temperature_recovery_fault;
	uint32_t Modbus_communication_recovery_fault;
	uint32_t all_fault_clear_counter;
	uint32_t ac_line_recovery_counter;
}Counter_t;

extern Counter_t delay_counter;
extern Fault_Flag Fault;
void FaultIndication(void);
void FaultDetection(void);
void FaultOccurrance(void);
void FaultRecovery(void);
void FaultRecieve(void);
void SEND_RECOVERY_FAULT_STATUS(void);
#endif
