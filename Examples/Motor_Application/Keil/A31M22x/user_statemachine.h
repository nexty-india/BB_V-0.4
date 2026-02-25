#ifndef _USER_STATEMACHINE_H_
#define _USER_STATEMACHINE_H_

#include "user_adc.h"
#include "Fault_indication.h"
#include "user_Switch.h"
#include "NXP_comm_uart.h"
#include "Analog_Pwm_Output.h"
#include "Digital_Pwm_Output.h"



#define LOWER_THRESHOLD_VOLTAGE_STABLE_RANGE   120
#define UPPER_THRESHOLD_VOLTAGE_STABLE_RANGE   200
#define LOWER_THRESHOLD_CURRENT_STABLE_RANGE		100
#define UPPER_THRESHOLD_CURRENT_STABLE_RANGE    100
#define LOWER_THRESHOLD_IGBT_TEMPERATURE_STABLE_RANGE  100
#define UPPER_THRESHOLD_IGBT_TEMPERATURE_STABLE_RANGE   100
#define LOWER_THRESHOLD_WINDING_TEMPERATURE_STABLE_RANGE   100
#define UPPER_THRESHOLD_WINDING_TEMPERATURE_STABLE_RANGE    100






typedef struct{
	uint32_t voltage_stable_counter;
	uint32_t Current_stable_counter;
	uint32_t Inside_temperature_counter;
	uint32_t MCU_temperature_counter;
	uint32_t IGBT_temperature_counter;
	uint32_t Relay_status_counter;
	uint32_t Fault_Flag_counter;
}SYSTEM_STABLE_COUNTER_t;

typedef union{
	 struct{
		 bool AC_VOLTAGE_STABLE_FLAG;
		 bool DC_VOLTAGE_STABLE_FLAG;
		 bool CURRENT_STABLE_FLAG;
		 bool WINDING_TEMPERATURE_FLAG;
		 bool IGBT_TEMPERATURE_STABLE_FLAG;
		 bool MODBUS_FAULT_CHECK;
	}STABLE_t;
	 uint16_t Stable_flag;
}SYSTEM_STABLE_FLAG_t;


typedef union{
	struct{
		uint16_t SYSTEM_EVENT_1_MS_PERIODIC : 1;
		uint16_t SYSTEM_EVEN_150_MS_PERIODIC_NXP_UART : 1;
		uint16_t DI1_STATUS_EVENT_FLAG :1;
		uint16_t DI2_STATUS_EVENT_FLAG :1;
		uint16_t MODBUS_EVENT_FLAG_RECEIVED: 1;
		uint16_t MODBUS_EVENT_FLAG_PROCESSED :1;
		uint16_t ADC_AI1_EVENT_FLAG: 1;
		uint16_t ADC_AI2_EVENT_FLAG :1;
		uint16_t RELAY_EVENT_FLAG :1;
		uint16_t TACHOMETER_EVENT_FLAG :1;
		uint16_t VOLTS_0_10_VOLTS_EVENT_FLAG :1;
		uint16_t FAULT_HANDLING_EVENT_FLAG :1;
		uint16_t STATE_MACHINE_EVENT_FLAG :1;
		uint16_t TEMPERATUE_EXT_EVENT_FLAG :1;
	}DRIVE_STATUS;
	uint16_t DRIVE_CHECK_STATUS;
}SYSTEM_DRIVE_EVENT_t;
extern float g_IPM_Temp,Winding_Temp;
extern SYSTEM_DRIVE_EVENT_t SYSTEM_DRIVE_EVENT;
void SENSOR_UPDATE_DATA(void);
void STATE_MACHINE(void);
void FAULT_EVENT(void);
void EVENT_OCCUR_1_MS(void);
void InputRegisterData(void);
void MotorStatusCheck(void);

#endif
