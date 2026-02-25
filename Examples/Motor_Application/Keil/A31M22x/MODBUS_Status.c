#include "Modbus_Status.h"
#include "NXP_Comm_uart.h"
#include "Modbus_Holding_Register.h"
#include "Modbus_Input_Register.h"
#include "Application_Input_Register.h"
#include "Bharat_Bijlee.h"
#include "Application_Holding_Register.h"
#include "Modbus_Comm.h"
#include "AI1_Sensor_Status.h"

extern MODBUS_REGISTER_t Modbus_Register;

MOTOR_COMM_MODE motor_comm_mode = MODBUS_W_R_MODE;
uint16_t Control_mode = 0;
uint16_t g_target_Speed;
/**
 * @brief  Selects control mode based on Modbus configuration.
 *         This function runs every 1 ms.
 *
 * Control modes:
 *   - PID control
 *   - Modbus speed control
 *   - Analog (0–10V) control
 */
void CONTROL_MODE_SELECT(void)    //Run at every 1 milliseconds
{
	Control_mode = MODBUS_HOLDING_REGISTERS[HOLDING_CONTROL_MODE].actual_value;
	if(Control_mode == PID_Flag)                 /* -------- Set PID control flag -------- */
	{
		controlmode.PID_FLAG_BIT = 1;
	}
	else
	{
		controlmode.PID_FLAG_BIT = 0;
	}
	
	if(Control_mode == MODBUS_FLAG)                  /* -------- Set Modbus control flag -------- */
	{
		controlmode.MODBUS_FLAG_BIT = 1;
	}
	else
	{
		controlmode.MODBUS_FLAG_BIT = 0;
	}
	 
	if(Control_mode == ANALOG_FLAG)                    /* -------- Set Analog control flag -------- */
	{
		controlmode.ANALOG_FLAG_BIT = 1;
	}
	else
	{
		controlmode.ANALOG_FLAG_BIT = 0;
	}
	
	ControlModeOperation();
}


/**
 * @brief  Executes control operation based on selected control mode.
 *
 * Control_mode values:
 *   1 = Analog control
 *   2 = PID control
 *   3 = Modbus control
 */
void ControlModeOperation(void)
{
	switch(Control_mode)
	{
		case 1:       //Analog
			ANALOG_CONTORL_RPM_ENABLE();
			break;
		
		case 3:				//Modbus
			MODBUS_EVENT_OCCURANCE();
			break;
		
		case 2:      // PID
			PID_SENSOR_EVENT_OCCURANCE();
			break;
	}
}

/**
 * @brief  Selects motor communication mode based on active control mode.
 *
 * Communication modes:
 *   MODBUS_R_MODE    : Read-only (RPM set internally)
 *   MODBUS_W_R_MODE  : Write + Read (RPM set via Modbus)
 */
void READ_RPM_SET_STATUS(void)
{
 if((controlmode.PID_FLAG_BIT)||(controlmode.ANALOG_FLAG_BIT)||(controlmode.BMS_CHECK_BIT))                 /* If RPM is controlled internally (PID / Analog / BMS),allow Modbus read-only access */
 {
	 motor_comm_mode = MODBUS_R_MODE;
 }
 else if(controlmode.MODBUS_FLAG_BIT == 1)                                                                    /* If RPM is controlled via Modbus */
 { 
	 motor_comm_mode = MODBUS_W_R_MODE;
 }
}

/**
 * @brief  Sets target RPM based on Modbus command.
 *         Handles Modbus fault, control-bit override,
 *         and maximum RPM limiting.
 */
void SET_TARGET_RPM_FROM_MODBUS(void)
{
	uint16_t Modbus_Target_Rpm = 0,Maximum_Rpm = 0,TargetrpmSet = 0;
	uint16_t ControlBit_Enable = 0,fan_direction = 0;
	bool Modbus_Fault_occur = 0;
	Modbus_Target_Rpm = MODBUS_HOLDING_REGISTERS[HOLDING_TARGET_SPEED_FROM_MODBUS].actual_value;
	Maximum_Rpm = MODBUS_HOLDING_REGISTERS[HOLDING_MAXIMUM_SPEED].actual_value;
	ControlBit_Enable = MODBUS_HOLDING_REGISTERS[HOLDING_CONTROL_BITS].actual_value;
  fan_direction = FAN_ROTATION();
	Modbus_Fault_occur = MODBUS_FAULT_OCCUR;
	
	if(Modbus_Fault_occur == true)                                /* -------- Target RPM Selection -------- */
	{
		TargetrpmSet = SET_SPEED_MODBUS_SIGNAL_LOSS_MODE();
	}
	else if(ControlBit_Enable == 1)
	{
		TargetrpmSet = ContorlBitSystem();                            /* Control bit override mode */
	}
	else
	{ 
		if(Modbus_Target_Rpm < Maximum_Rpm)                           /* Normal Modbus RPM control with limit check */
			TargetrpmSet = Modbus_Target_Rpm*10; 
		else
			TargetrpmSet = Maximum_Rpm;
	}
	 
	if(fan_direction == 1)                    //anticlock direction is activate
	{
		TargetrpmSet |= 0x8000; 
	}
	
	g_target_Speed = TargetrpmSet;
}

/**
 * @brief Check Modbus status and handle motor RPM updates
 *
 * This function is called periodically (event check) to handle
 * motor communication via Modbus based on the selected mode.
 */
static void MODBUS_STAUTS_CHECK(void)    //Event CHeck function
{
	READ_RPM_SET_STATUS();        // Update the current RPM setpoint/status from Modbus or internal logic
	switch(motor_comm_mode)
	{	
		case MODBUS_INT:              // Internal mode: no external Modbus control
            // Nothing to do here          
			break;
		
		case MODBUS_W_R_MODE:     // Writing and Reading via Modbus
            // If Modbus write flag is set, update motor target RPM from Modbus
		
			if(controlmode.MODBUS_FLAG_BIT == 1){
				SET_TARGET_RPM_FROM_MODBUS();
			}
			else{
			}
			break;
		
		case MODBUS_R_MODE:             // Read-only mode via Modbus
            // In read-only mode, motor RPM is not updated from Modbus
			break;
	}
}


/**
 * @brief Handle Modbus event occurrence
 *
 * This function should be called periodically (e.g., in main loop or timer ISR)
 * to process any pending Modbus events.
 *
 * If the MODBUS_FLAG_BIT is set, it indicates that a new write/read
 * operation has occurred from the Modbus master.
 */
void MODBUS_EVENT_OCCURANCE(void)     
{
	if(controlmode.MODBUS_FLAG_BIT == 1){// Check if a Modbus write/read event has occurred
		MODBUS_STAUTS_CHECK();// Process the event based on the current communication mode
	}
}

/**
 * @brief Set target speed to motor via Modbus parameter
 *
 * This function copies the internally calculated target speed
 * (g_target_Speed) to the Modbus target speed register.
 * The Modbus register is later used by the motor control logic
 * or external Modbus master for speed reference.
 */
void SET_TARGET_SPEED_TO_MOTOR(void)
{
	uint16_t User_Set_Speed = 0;
	User_Set_Speed = g_target_Speed;
	modbus_parameter.MODBUS_TARGET_SPEED = User_Set_Speed;
}
