#include "Relay_Status.h"
#include "A31M22x_pcu.h"

/**
 * @brief Control relay based on drive system event
 *
 * This function reads the relay event flag from the system drive status
 * and switches the corresponding GPIO pin ON or OFF accordingly.
 */
void RelayControl(void)
{

	if(SYSTEM_DRIVE_EVENT.DRIVE_STATUS.RELAY_EVENT_FLAG == RELAY_ON)           // Check if the relay event flag indicates to turn the relay ON
	{
    HAL_GPIO_SetPin(PA,(1<<1));// Relay GPIO ON	
	}
	else if(SYSTEM_DRIVE_EVENT.DRIVE_STATUS.RELAY_EVENT_FLAG == RELAY_OFF)       // Check if the relay event flag indicates to turn the relay OFF
	{
		HAL_GPIO_ClearPin(PA,(1<<1));//Relay GPIO oFF
	}
}

/**
 * @brief Configure K1 relay behavior based on K1 function setting
 *
 * This function reads the K1 function setting from a Modbus holding register,
 * then controls the relay (K1) depending on motor speed and fault status.
 */
void K1FunctionSetting(void)
{
	uint16_t Fault_Count = 0;
	uint16_t Actual_Speed = 0;
	
	// Read actual motor speed and fault status from Modbus parameters
	Actual_Speed =  modbus_parameter.MODBUS_ACTUAL_SPEED;
	Fault_Count = modbus_parameter.MODBUS_FAULT_STATUS;
	uint16_t K1_setting = 0;
	// Read K1 function setting from Modbus holding register
	K1_setting = MODBUS_HOLDING_REGISTERS[HOLDING_K1FUNCITON].actual_value;
	
	if(K1_setting == 1)                       // Check if K1 function is enabled
	{
		if(Actual_Speed > 0)                        // If motor is running, turn relay ON
		{
			SYSTEM_DRIVE_EVENT.DRIVE_STATUS.RELAY_EVENT_FLAG = RELAY_ON;
		}
		else if(Fault_Count != 0)                      // If a fault exists, turn relay OFF
		{
			SYSTEM_DRIVE_EVENT.DRIVE_STATUS.RELAY_EVENT_FLAG = RELAY_OFF;
		}
	}
	else{
		SYSTEM_DRIVE_EVENT.DRIVE_STATUS.RELAY_EVENT_FLAG = RELAY_OFF;
	}

}

/**
 * @brief Main relay operation handler
 *
 * This function is responsible for controlling the relay(s) in the system.
 * It calls the following sub-functions:
 * 1. RelayControl()      - Directly sets or clears the relay GPIO based on the current event flag.
 * 2. K1FunctionSetting() - Updates the relay event flag based on K1 function, motor speed, and fault status.
 *
 * Note: The order of function calls matters. 
 *       If K1FunctionSetting() changes the RELAY_EVENT_FLAG, RelayControl()
 *       should be called afterwards to apply the change to hardware.
 */
void RelayOperation(void)
{
    RelayControl();       // Apply current relay event flag to hardware
    K1FunctionSetting();  // Update relay event flag based on K1 function logic
}

