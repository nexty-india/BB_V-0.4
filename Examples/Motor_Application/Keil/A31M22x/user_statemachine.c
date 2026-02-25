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
#include "DI1_Status.h"
extern bool Transmit_Tnx;
extern UART_COMM_PARA_t uart_comm;
extern uint16_t g_Pot_voltage_filt_Percentage;

/* ===== 4-byte aligned first ===== */


uint32_t tramit_counter;
uint32_t tramit_data_nxp;
uint32_t MOTOR_RECEIVED_DATA;

/* ===== Structs (likely 4-byte aligned) ===== */ 
SYSTEM_STABLE_COUNTER_t sytem_stable_counter_t;
SYSTEM_STABLE_FLAG_t    system_flag_stable;
SYSTEM_DRIVE_EVENT_t   SYSTEM_DRIVE_EVENT;

/* ===== 2-byte aligned ===== */
uint16_t check_tx_time;


uint16_t Check_ADC_Val;
uint8_t Motor_status;


uint16_t g_ambienttemperature;
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
		MotorUartStatemachine();
		ReDeModbus();
//		SystemHourStatus();
		
		CONTROL_MODE_SELECT();
		PID_SENSOR_EVENT_OCCURANCE();
		SET_TARGET_SPEED_TO_MOTOR();
		FaultIndication();
		RelayOperation();
		MotorStatusCheck();
		FilterParameter();
		LoadPercentage();
		ANALOG_CONTROL_MODE();
		OccRecFault();
		Current_Filt();
		FireFault();
		Suppression();
		InputRegisterData();
		FlashWriting();            // Flash Writing.
		LED_MODE_INDICATION();
		DigitalOutput();
		PowerFilterCal();
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
		OccRecFault();
		ModbusStateMachine();
		ReDeModbus();
		RelayOperation();
		MotorUartStatemachine();
		SET_TARGET_SPEED_TO_MOTOR();
		FaultIndication();
		InputRegisterData();
		//SystemHourStatus();
		DigitalOutput();
		FilterParameter();
		FlashWriting();            // Flash Writing.
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
	uint16_t Actual_Speed = 0,RMS_Voltage = 0,Motor_Current = 0,IPM_Temperature = 0,Winding_Temperature = 0,Fault_Count = 0,Target_Speed = 0;
	uint16_t AI1_Value = 0,AI1_Count = 0,Torque = 0,Load = 0,Drive_Output_Frequency = 0;
	uint16_t KW = 0, KWH = 0,Di1_Status = 0,input_current = 0;
	uint16_t Motor_Status = 0;

	
	Actual_Speed = modbus_parameter.MODBUS_ACTUAL_SPEED;
	RMS_Voltage = modbus_parameter.MODBUS_READ_AC_VOLTAGE;
	Motor_Current = g_currentFilt;
	IPM_Temperature = modbus_parameter.MODBUS_IPM_TEMPERATURE;
	Winding_Temperature = modbus_parameter.MODBUS_MOTOR_TEMPERATURE;
	//Fault_Count = modbus_parameter.MODBUS_FAULT_STATUS;
	Fault_Count = Fault.Fault_Count;
	Target_Speed = modbus_parameter.MODBUS_TARGET_SPEED;
	AI1_Count = g_Pot_voltage_filt_Percentage;
	Torque = modbus_parameter.TORQUE;


	KWH = modbus_parameter.KWH;
	Motor_Status = Motor_status;
	AI1_Value = Volts_10();
	Di1_Status = di1_pressed;//MODBUS_HOLDING_REGISTERS[HOLDING_DI1_FUNCTION].actual_value;


	g_Fault_Clear_Check = modbus_parameter.FAULT_CLEAR_STATUS;
	
	MODBUS_INPUT_REGISTERS[INPUT_MOTOR_SPEED].actual_value = Actual_Speed;
	MODBUS_INPUT_REGISTERS[INPUT_DC_VOLTAGE].actual_value = (float)RMS_Voltage/10;

	MODBUS_INPUT_REGISTERS[INPUT_MOTOR_CURRENT].actual_value = Motor_Current/10;
//	g_IPM_Temp = (IPM_Temperature-2500)/10;
//	if(g_IPM_Temp < 250.0f)
//		g_IPM_Temp = 250.0f;
//	else
//		g_IPM_Temp = g_IPM_Temp;
	MODBUS_INPUT_REGISTERS[INPUT_IGBT_TEMPERATURE].actual_value =(float)IPM_Temperature/10;
	MODBUS_INPUT_REGISTERS[INPUT_WINDING_TEMPERATURE].actual_value = (float) Winding_Temperature/10;
	MODBUS_INPUT_REGISTERS[INPUT_FAULT_CODE].actual_value = Fault_Count;
	MODBUS_INPUT_REGISTERS[INPUT_TARGET_SPEED_MODBUS].actual_value = Target_Speed;
	MODBUS_INPUT_REGISTERS[INPUT_AI1_VALUE].actual_value =(float) AI1_Count*10;
	MODBUS_INPUT_REGISTERS[INPUT_AI1_CALCULATED_VALUE].actual_value = AI1_Value;
	MODBUS_INPUT_REGISTERS[INPUT_TORQUE].actual_value = Torque;
	MODBUS_INPUT_REGISTERS[INPUT_KWH].actual_value = KWH;
	MODBUS_INPUT_REGISTERS[INPUT_MOTOR_STATUS].actual_value = Motor_status;
	MODBUS_INPUT_REGISTERS[INPUT_DI1_STATUS].actual_value = Di1_Status;
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
  if(Control_mode == ANALOG_FLAG)
	{
		Motor_status = 1;
	}
	if(Control_mode == PID_Flag)
	{
		Motor_status = 2;
	}
	if(Control_mode == MODBUS_FLAG)
	{
		Motor_status = 3;
	}
}


