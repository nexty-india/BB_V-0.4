#include "user_statemachine.h"
#include "NXP_Comm_uart.h"
#include "Modbus_Holding_Register.h"
#include "Modbus_Input_Register.h"
#include "Application_Input_Register.h"
#include "Application_Holding_Register.h"
#include "Bharat_Bijlee.h"
#include "MODBUS_Status.h"
#include "Flash_Writing.h"
#include "Default_Values.h"
#include "Modbus_Comm.h"
#include "DI1_Status.h"
#include "Fault_Status.h"
#include "Relay_Status.h"
#include "AI1_Sensor_Status.h"
#include "Suppression_Setting.h"

extern MODBUS_REGISTER_t Modbus_Register;

extern bool Transmit_Tnx;
extern UART_COMM_PARA_t uart_comm;
extern uint16_t Control_mode,g_Pot_voltage_filt_Percentage;

uint32_t tramit_counter,tramit_data_nxp,MOTOR_RECEIVED_DATA;
uint16_t check_tx_time;
uint16_t g_Power = 0,g_Total_Load = 6000;
SYSTEM_STABLE_COUNTER_t sytem_stable_counter_t;
SYSTEM_STABLE_FLAG_t system_flag_stable;
SYSTEM_DRIVE_EVENT_t SYSTEM_DRIVE_EVENT;
uint16_t Motor_status = 0;
uint16_t Check_ADC_Val = 0;
float g_Load_per = 0;
uint16_t g_Load_percentage;
/**
*
*  @brief Handles all events that must occur every 1 millisecond.
*
* This function is triggered periodically (every 1 ms) to execute
* several system-level tasks if the 1 ms event flag is set. 
*	
*	@note This function should be called from the main control loop
*       or an interrupt service routine that operates every 1 ms.
*
*/
void EVENT_OCCUR_1_MS(void) 
{
	if(SYSTEM_DRIVE_EVENT.DRIVE_STATUS.SYSTEM_EVENT_1_MS_PERIODIC == 1)  //Checks if the 1 ms periodic event flag is set.
	{
		SYSTEM_DRIVE_EVENT.DRIVE_STATUS.SYSTEM_EVENT_1_MS_PERIODIC = 0;  //Clears the flag to prevent re-entry until the next cycle.
		MODE_SELECTION();
		ModbusStateMachine();
		ReDeModbus();
		LED_MODE_INDICATION();
		MotorUartStatemachine();
		SystemHourStatus();
		SET_TARGET_SPEED_TO_MOTOR();
		FaultIndication();
		RelayOperation();
		MotorStatusCheck();
		LoadPercentage();
		Power_Filter();
		ANALOG_CONTROL_MODE();
		SEND_RECOVERY_FAULT_STATUS();
		Current_Filt();
		Suppression();
	}
}

/**
* @brief :- This Function Handle all the event which is occur in the FaultState Condition
*	@note This function should be called from the main control loop
*       or an interrupt service routine that operates every 1 ms.
* @return none
*/

void FAULT_EVENT(void)
{
	if(SYSTEM_DRIVE_EVENT.DRIVE_STATUS.SYSTEM_EVENT_1_MS_PERIODIC == 1)  //Checks if the 1 ms periodic event flag is set.
	{
		SYSTEM_DRIVE_EVENT.DRIVE_STATUS.SYSTEM_EVENT_1_MS_PERIODIC = 0;  //Clears the flag to prevent re-entry until the next cycle.
		ModbusStateMachine();
		ReDeModbus();
		RelayOperation();
		SET_TARGET_SPEED_TO_MOTOR();
		SEND_RECOVERY_FAULT_STATUS();
		FaultIndication();
	}
	
}

/**
* @brief :- This Function Handle show all the value of Modbus Input register to the modbus application
*	@note This function should be called from the main control loop
*       or an interrupt service routine that operates every 1 ms.
* @return none
*/
uint16_t g_Fault_Clear_Check;
	float g_IPM_Temp = 0,Winding_Temp=0;
void InputRegisterData(void)
{
	uint16_t Actual_Speed = 0,RMS_Voltage = 0,AC_Voltage = 0, Motor_Current = 0,IPM_Temperature = 0,Winding_Temperature = 0,Fault_Count = 0,Target_Speed = 0;
	uint16_t AI1_Value = 0,AI1_Count = 0,Torque = 0,Load = 0,Drive_Output_Frequency = 0;
	uint16_t KW = 0, KWH = 0,Di1_Status = 0,input_current = 0;
	uint16_t Motor_Status = 0,power_on_hr = 0,Run_hr = 0;

	
	Actual_Speed = modbus_parameter.MODBUS_ACTUAL_SPEED;
	RMS_Voltage = modbus_parameter.MODBUS_READ_AC_VOLTAGE;
	Motor_Current = g_currentFilt;
	IPM_Temperature = modbus_parameter.MODBUS_IPM_TEMPERATURE;
	Winding_Temperature = modbus_parameter.MODBUS_MOTOR_TEMPERATURE;
	Fault_Count = modbus_parameter.MODBUS_FAULT_STATUS;
	Target_Speed = modbus_parameter.MODBUS_TARGET_SPEED;
	AI1_Count = g_Pot_voltage_filt_Percentage;
	Torque = modbus_parameter.TORQUE;
	Load = g_Load_percentage;
	KW = g_Power_Filt;
	KWH = modbus_parameter.KWH;
	Motor_Status = Motor_status;
	AI1_Value = Volts_10();
	Di1_Status = MODBUS_HOLDING_REGISTERS[HOLDING_DI1_FUNCTION].actual_value;
	power_on_hr = g_powerrunhourcountercurr;
	Run_hr = g_runhourcountercur;
	g_Fault_Clear_Check = modbus_parameter.FAULT_CLEAR_STATUS;
	
	MODBUS_INPUT_REGISTERS[INPUT_MOTOR_SPEED].actual_value = Actual_Speed;
	MODBUS_INPUT_REGISTERS[INPUT_DC_VOLTAGE].actual_value = (float)RMS_Voltage/10;

	MODBUS_INPUT_REGISTERS[INPUT_MOTOR_CURRENT].actual_value = Motor_Current/10;
	g_IPM_Temp = (IPM_Temperature-2500)/10;
	if(g_IPM_Temp < 250.0f)
		g_IPM_Temp = 250.0f;
	else
		g_IPM_Temp = g_IPM_Temp;
	MODBUS_INPUT_REGISTERS[INPUT_IGBT_TEMPERATURE].actual_value =(float)g_IPM_Temp;
	MODBUS_INPUT_REGISTERS[INPUT_WINDING_TEMPERATURE].actual_value = (float) Winding_Temperature/10;
	MODBUS_INPUT_REGISTERS[INPUT_FAULT_CODE].actual_value = Fault_Count;
	MODBUS_INPUT_REGISTERS[INPUT_TARGET_SPEED_MODBUS].actual_value = Target_Speed;
	MODBUS_INPUT_REGISTERS[INPUT_AI1_VALUE].actual_value =(float) AI1_Count*10;
	MODBUS_INPUT_REGISTERS[INPUT_AI1_CALCULATED_VALUE].actual_value = AI1_Value;
	MODBUS_INPUT_REGISTERS[INPUT_TORQUE].actual_value = Torque;
	MODBUS_INPUT_REGISTERS[INPUT_LOAD].actual_value = Load;
	MODBUS_INPUT_REGISTERS[INPUT_KW].actual_value = KW;///1000;
	MODBUS_INPUT_REGISTERS[INPUT_KWH].actual_value = KWH;
	MODBUS_INPUT_REGISTERS[INPUT_MOTOR_STATUS].actual_value = Motor_status;
	MODBUS_INPUT_REGISTERS[INPUT_DI1_STATUS].actual_value = Di1_Status;
	
	MODBUS_INPUT_REGISTERS[INPUT_POWER_ON_HOURS].actual_value = power_on_hr;
	MODBUS_INPUT_REGISTERS[INPUT_RUN_HOURS].actual_value = Run_hr;
	MODBUS_INPUT_REGISTERS[INPUT_FAIL_SAFE_STATUS].actual_value = g_Fail_safe_status;
MODBUS_INPUT_REGISTERS[INPUT_X_AXIS_VIBRATION].actual_value = g_Fault_Clear_Check;
}

/**
* @brief :- This Function Handle all the event whicht is show in Motor status of Input register
*	@note This function should be called from the main control loop
*       or an interrupt service routine that operates every 1 ms.
* @return none
*/
void MotorStatusCheck(void)
{

	if(Control_mode == PID_Flag)
	{
		Motor_status = 2;
	}
	
	if(Control_mode == ANALOG_FLAG)
	{
		Motor_status = 1;
	}
	if(Control_mode == MODBUS_FLAG)
	{
		Motor_status = 3;
	}
}

/**
* @brief :- This Function calcuate the percentage of load of motor using the power receved by NXP controller
*	@note This function should be called from the main control loop
*       or an interrupt service routine that operates every 1 ms.
* @return none
*/

void LoadPercentage(void)
{
	
	g_Power =(float)g_Power_Filt;
	g_Load_per = (float)g_Power/g_Total_Load;
	g_Load_percentage = g_Load_per * 100;
}