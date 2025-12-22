#include "PID_Sensor_Status.h"
#include "Bharat_Bijlee.h"
#include "Application_Holding_Register.h"
#include "MODBUS_Status.h"
#include "AI1_Sensor_Status.h"
/*Globle Variable*/
extern MODBUS_REGISTER_t Modbus_Register;
uint16_t Analog_input_20Curr;

uint16_t Pid_sensor_rpm;
uint16_t Analog_4_20_ma_factor,Analog_4_20_ma_filt;
uint16_t PID_Calculated_RPM = 0;

/**/

/**
Brief :- Adc Count at 4_20 MA outer sensor
*/
static int ANALOG_SENSE_4_20MA(void)												//Sense Current from 4mA - 20mA.
{
	Analog_input_20Curr = MDL_ADC_OPAMP(1);							//read adc count.
	return Analog_input_20Curr;
}


/**
Brief
*/
static int ANALOG_SENSE_4_20MA_FILT(void)
{
	Analog_4_20_ma_factor = Analog_4_20_ma_factor + (ANALOG_SENSE_4_20MA() - Analog_4_20_ma_filt);
	Analog_4_20_ma_filt = Analog_4_20_ma_factor >> 12;
	return Analog_4_20_ma_filt;
}



/**
Brief :- Select PID sensor According to Modbus selection....
*/
static int PID_SENSOR_EXECUTE(void)
{
	uint16_t Sensor_select = 0;
	Sensor_select = MODBUS_HOLDING_REGISTERS[HOLDING_PID_SENSOR_SELECT].actual_value;
	switch(Sensor_select)
	{
		case NO_SENSOR:
			break;
		
		case DIFFERENTIAL_TEMPERATURE_SENSOR:
			Pid_sensor_rpm = ANALOG_DIFFERENTIAL_PID_MODE();
		SYSTEM_DRIVE_EVENT.DRIVE_STATUS.ADC_AI1_EVENT_FLAG = 1;
			break;
		
		case DIFFERENTIAL_PRESSURE_SENSOR:
			Pid_sensor_rpm = ANALOG_DIFFERENTIAL_PID_MODE();
		SYSTEM_DRIVE_EVENT.DRIVE_STATUS.ADC_AI1_EVENT_FLAG = 1;
			break;
		
		case FLOW_SENSOR:
			Pid_sensor_rpm = ANALOG_DIFFERENTIAL_PID_MODE();
		SYSTEM_DRIVE_EVENT.DRIVE_STATUS.ADC_AI1_EVENT_FLAG = 1;
			break;
	}
	return Pid_sensor_rpm;
}


/**
Brief :- Calculate RPM using Pressure Sensor ,Upper and Lower RPM
*/
static int ANALOG_DIFFERENTIAL_PID_MODE(void)
{
	uint16_t CALCULATE_RPM=0,SLOPE=0,INTERCEPT=0;
	uint16_t PRESSURE_WORK_RANGE_MIN=0,PRESSURE_WORK_RANGE_MAX=0;
	uint16_t PRESSURE_SPEED_MIN=0,PRESSURE_SPEED_MAX=0;
	uint16_t PI_DIFF_SET_POINT;
	uint16_t Actual_value = 0;
	PRESSURE_WORK_RANGE_MIN = MODBUS_HOLDING_REGISTERS[HOLDING_DIFFERENTIAL_PRESSURE_RANGE_MIN].actual_value;
	PRESSURE_WORK_RANGE_MAX = MODBUS_HOLDING_REGISTERS[HOLDING_DIFFERNETIAL_PRESEURE_RANGE_MAX].actual_value;
	Actual_value = ANALOG_SENSE_4_20MA_FILT();
	PRESSURE_SPEED_MIN = MODBUS_HOLDING_REGISTERS[HOLDING_PRESSURE_SPEED_MIN].actual_value;
	PRESSURE_SPEED_MAX = MODBUS_HOLDING_REGISTERS[HOLDING_PRESSURE_SPEED_MAX].actual_value;
	PI_DIFF_SET_POINT = MODBUS_HOLDING_REGISTERS[HOLDING_PID_CONFIGURATION_DIFFERENTIAL_PRESSURE_SET_VALUE].actual_value;
	
	SLOPE = ((PRESSURE_WORK_RANGE_MAX - PRESSURE_WORK_RANGE_MIN)/(PRESSURE_SPEED_MAX - PRESSURE_SPEED_MIN));
	INTERCEPT = PRESSURE_WORK_RANGE_MAX - SLOPE *  PRESSURE_SPEED_MAX;
	
	CALCULATE_RPM = PRESSURE_WORK_RANGE_MAX * ANALOG_SENSE_4_20MA_FILT() + INTERCEPT ;
	
	if(PI_DIFF_SET_POINT > Actual_value)
	{
		CALCULATE_RPM ++;
	}
	else{
		CALCULATE_RPM --;
	}
	
	return CALCULATE_RPM;
}




/*
Purpose :- ANALOG_CONTORL_RPM_ENABLE set RPM according to ANALOG_CONTORL_MODE.
*/

static void PID_Sensor_RPM_ENABLE(void)     //Event Check Function
{
	g_Fail_safe_status = MODBUS_HOLDING_REGISTERS[HOLDING_FAIL_SAFE_ON_OFF].actual_value;
	if(g_Fail_safe_status == 1)
	{
		g_target_Speed = FailSafeControl();
	}
	else{
	g_target_Speed = PID_Calculated_RPM;
	}
}



void PID_SENSOR_EVENT_OCCURANCE(void)
{
	PID_Calculated_RPM = PID_SENSOR_EXECUTE();
	if((SYSTEM_DRIVE_EVENT.DRIVE_STATUS.ADC_AI2_EVENT_FLAG == 1)&&(controlmode.PID_FLAG_BIT == 1))
	{
		SYSTEM_DRIVE_EVENT.DRIVE_STATUS.ADC_AI2_EVENT_FLAG = 0;
		PID_Sensor_RPM_ENABLE();
	}
}
