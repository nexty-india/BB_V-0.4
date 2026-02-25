#include "Application_Holding_Register.h"
#include "Bharat_Bijlee.h"
#include "A31M22x_pcu.h"
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdarg.h>
#include <stdbool.h>
#include "Relay_Status.h"
#include "Modbus_Status.h"
#include "PID_Sensor_Status.h"
#include "AI1_Sensor_Status.h"
#include "Flash_Writing.h"
ControlMode_t controlmode;
InternalRpm_t InternalRPM;

VdcFilt_t vdcfilt;

BypassTMPMGMT_t BypassTmppmgmt;
uint32_t g_Nodeaddress_Read = 0;
bool g_BYPASS_TMP_IGBT = 0,g_BYPASS_TMP_WINDING = 0;
/**
 * @brief Get the target speed to use when Modbus signal is lost
 *
 * This function reads the pre-configured target RPM from a Modbus holding register
 * that is specifically used when the system loses Modbus communication.
 *
 * @return uint16_t Target RPM value to use during Modbus signal loss
 */
int SET_SPEED_MODBUS_SIGNAL_LOSS_MODE(void)
{
	uint16_t Target_rpm_signal_loss;
	Target_rpm_signal_loss = MODBUS_HOLDING_REGISTERS[HOLDING_SET_SPEED_IN_MODBUS_SIGNAL_LOSS_MODE].actual_value;
	return Target_rpm_signal_loss;
}

/**
 * @brief Get the maximum allowable motor speed from Modbus register
 *
 * This function reads the maximum speed value configured in the Modbus holding register.
 * It is used to limit or validate the target speed sent to the motor.
 *
 * @return uint16_t Maximum allowed RPM
 */
int MAXIMUM_SPEED(void)
{
	uint16_t Maximum_target_rpm;
	Maximum_target_rpm = MODBUS_HOLDING_REGISTERS[HOLDING_MAXIMUM_SPEED].actual_value;
	return Maximum_target_rpm;
}
/**
 * @brief Get the minimum allowable motor speed from Modbus register
 *
 * This function reads the minimum speed value configured in the Modbus holding register.
 * It is used to ensure the motor speed does not go below the safe minimum.
 *
 * @return uint16_t Minimum allowed RPM
 */
int MINIMUM_SPEED(void)
{
	uint16_t Minimum_target_rpm;
	Minimum_target_rpm = MODBUS_HOLDING_REGISTERS[HOLDING_MIN_SPEED].actual_value;
	return Minimum_target_rpm;
}
/**
 * @brief Determine the fan rotation direction
 *
 * This function reads the fan rotation setting from a Modbus holding register
 * and returns the corresponding direction.
 * 0 ? Forward, 1 ? Reverse
 *
 * @return int Fan direction (0 = Forward, 1 = Reverse)
 */
int FAN_ROTATION(void)
{
	uint16_t Fan_Direction = 0,TargetRpm = 0;
	if(MODBUS_HOLDING_REGISTERS[HOLDING_FAN_ROTATION].actual_value == FORWARD_DIRECTION)
	{
		Fan_Direction = 0;    //Forward Direction
//		TargetRpm = g_target_Speed;
	}
	else if(MODBUS_HOLDING_REGISTERS[HOLDING_FAN_ROTATION].actual_value == REVERSE_DIRECTION)
	{
		Fan_Direction = 1;		//Reverse Direction
//		TargetRpm = g_target_Speed & 8000;
	}
	return Fan_Direction;
}


/**
 * @brief Set the switching frequency for the motor/fan drive
 *
 * This function sets a fixed switching frequency value and updates
 * the corresponding Modbus holding register. The switching frequency
 * typically controls the PWM frequency for motor inverter/drive.
 */
void SWITCHING_FREQUENCY(void)
{
	uint16_t Switching_Frequency;
	Switching_Frequency = 8000;
	MODBUS_HOLDING_REGISTERS[HOLDING_SWITCHING_FREQUENCY].actual_value = Switching_Frequency;
}

/**
 * @brief Get internal preset RPM 1 from Modbus holding register
 *
 * This function reads the internal RPM preset value configured
 * in the Modbus holding register for internal speed selection.
 *
 * @return uint16_t Internal RPM 1 value
 */
int SET_INTERNAL_RPM_1(void)
{
	uint16_t internal_rpm_1;
	internal_rpm_1=MODBUS_HOLDING_REGISTERS[HOLDING_SET_INTERNAL_1].actual_value;
	return internal_rpm_1;
}


/**
 * @brief Get internal preset RPM 2 from Modbus holding register
 *
 * This function reads the internal RPM preset value configured
 * in the Modbus holding register for internal speed selection.
 *
 * @return uint16_t Internal RPM 2 value
 */
int SET_INTERNAL_RPM_2(void)
{
	uint16_t internal_rpm_2;
	internal_rpm_2=MODBUS_HOLDING_REGISTERS[HOLDING_SET_INTERNAL_2].actual_value;
	return internal_rpm_2;
}

/**
 * @brief Get internal preset RPM 3 from Modbus holding register
 *
 * This function reads the internal RPM preset value configured
 * in the Modbus holding register for internal speed selection.
 *
 * @return uint16_t Internal RPM 3 value
 */
int SET_INTERNAL_RPM_3(void)
{
	uint16_t internal_rpm_3;
	internal_rpm_3=MODBUS_HOLDING_REGISTERS[HOLDING_SET_INTERNAL_3].actual_value;
	return internal_rpm_3;
}


/**
 * @brief Control system target speed and temperature bypass management
 *
 * This function selects the target speed based on internal speed selection
 * and sets flags to bypass IGBT or Winding temperature faults if configured.
 */
int ContorlBitSystem(void)
{
	uint16_t Modbus_Enable = 0,Set_Internal_Active = 0,TmpMGMT = 0;
	uint16_t Contorl_bit_Target_speed = 0;
	Modbus_Enable = controlmode.MODBUS_FLAG_BIT;                            // Read Modbus enable flag
	Set_Internal_Active = MODBUS_HOLDING_REGISTERS[HOLDING_SET_INTERNAL_ACTIVE].actual_value;        // Read internal speed selection from Modbus holding register
	
	TmpMGMT = MODBUS_HOLDING_REGISTERS[HOLDING_DISABLE_TEMP_MANAGEMENT].actual_value;                   // Read temperature management bypass configuration from Modbus
	
	
		switch(Set_Internal_Active)             // Determine target speed based on internal selection
		{
			case NO_SELECT:                    // No internal speed selected ? keep previous target speed
				break; 
			
			case SET_INTERNAL_SPEED_1:
				Contorl_bit_Target_speed = SET_INTERNAL_RPM_1();
				break;
			
			case SET_INTERNAL_SPEED_2:
				Contorl_bit_Target_speed = SET_INTERNAL_RPM_2();
				break;
			
			case SET_INTERNAL_SPEED_3:
				Contorl_bit_Target_speed = SET_INTERNAL_RPM_3();
				break;
		}
		
		switch(TmpMGMT)                            // Temperature management bypass logic
		{
			case TmpMGMT_Disable:
			g_BYPASS_TMP_IGBT = 0;
			g_BYPASS_TMP_WINDING = 0;
			break;

			case BYPASS_TMP_IGBT:                 //Disable the IGBT Temperature Fault Forcelly
			g_BYPASS_TMP_IGBT = 1;
			g_BYPASS_TMP_WINDING = 0;
			break;

			case BYPASS_TMP_WINDING:               //Disable the Winding Temperature Fault Forcelly
			g_BYPASS_TMP_WINDING = 1;
			g_BYPASS_TMP_IGBT = 0;
			break;

			case BYPASS_TMP_BOTH:                  //Disable Both IGBT and Winding Temperature Fault Forcelly
			g_BYPASS_TMP_IGBT = 1;
			g_BYPASS_TMP_WINDING = 1;
			break;
		}
		
	g_target_Speed = Contorl_bit_Target_speed;              // Update global target speed variable
}



/**
 * @brief Update LED mode indication status
 *
 * This function reads the LED mode from the Modbus holding register
 * and updates the LED status accordingly. The status is then sent
 * to the NXP controller via the modbus_parameter structure.
 */
void LED_MODE_INDICATION(void)
{
	uint8_t led_Check=0,Led_status = 0;
	led_Check = MODBUS_HOLDING_REGISTERS[HOLDING_LED_MODE].actual_value;
	switch(led_Check)
	{
		case LED_OFF:
			Led_status = 1;//send led off status to NXP controller
			break;
		
		case LED_ON:
			Led_status = 0;//send led on status to NXP Controller
			break;
	}
	modbus_parameter.LED_STATUS = Led_status;
}

/**
 * @brief Determine fan/motor speed in fail-safe condition
 *
 * This function checks the configured fail-safe source and activation value.
 * If the fail-safe condition is met, it returns the fail-safe target speed
 * with the specified rotation direction.
 *
 * @return uint16_t Fail-safe target RPM
 */

int FailSafeControl(void)
{
	uint16_t Fail_safe_MDirection = 0,Fail_safe_speed = 0;
	uint16_t Fail_safe_Source = 0,Fail_safe_Active_value = 0;
	uint16_t Fail_safe_SRPM = 0;
	uint16_t g_actual_volts = 0;
	
	// Read fail-safe parameters from Modbus holding registers
	Fail_safe_MDirection = MODBUS_HOLDING_REGISTERS[HOLDING_FAIL_SAFE_RUNNING_DIRECTION].actual_value;
	Fail_safe_speed = MODBUS_HOLDING_REGISTERS[HOLDING_FAIL_SAFE_FUNCTION_SET_SPEED].actual_value;
  Fail_safe_Source = MODBUS_HOLDING_REGISTERS[HOLDING_FAIL_SAFE_SOURCE].actual_value;
  Fail_safe_Active_value = MODBUS_HOLDING_REGISTERS[HOLDING_FAIL_SAFE_ACTIVATE_SET_VALUE].actual_value;
  g_actual_volts = Volts_10();
		switch(Fail_safe_Source)                             // Determine if fail-safe condition is active
		{
			case AI1_FAILSAFE:
				if(Fail_safe_Active_value > g_actual_volts)         // Check if analog voltage exceeds fail-safe activation threshold
				{
					if(Fail_safe_MDirection == 1)                       // Set fail-safe RPM depending on configured motor direction
					{
						Fail_safe_SRPM = Fail_safe_speed;
					}
					else{
						Fail_safe_SRPM = Fail_safe_speed & 8000;												//Fan Rotate in AntiClockdirection
					}
				}
				else{
					
				}
				break;
					
			case AI2_FAILSAFE:
				if(Fail_safe_Active_value > g_actual_volts)
				{
					if(Fail_safe_MDirection == 1)
					{
						Fail_safe_SRPM = Fail_safe_speed & 8000;
					}
					else{
						//Fan Rotate in AntiClockdirection
					}
				}
				else
				{
				}
				break;
		}
		return Fail_safe_SRPM;
	
}

/*
 * Function Name : NodeAddresInit
 * Description   :
 *  - Reads the Modbus node address from flash memory.
 *  - Valid Modbus slave address range is 1 to 247.
 *  - If the stored node address is valid, it is used as-is.
 *  - If the stored value is invalid (out of range or corrupted),
 *    the node address is reset to default value (1),
 *    and the default value is written back to flash.
 *  - Finally, the node address is updated into the Modbus holding register
 *    so that Modbus stack uses the correct slave address.
 */
void NodeAddresInit(void)
{
	
	g_Nodeaddress_Read = Read_Flash_U32(HOLDING_NODEADDRESS_START_ADDR);
	
	if((g_Nodeaddress_Read >= 1)&&(g_Nodeaddress_Read <= 247))
	{
		//valid Nodeaddress
	}
	else{
		g_Nodeaddress_Read = 1;
		Data_write_to_flash(HOLDING_NODEADDRESS_START_ADDR,1,(uint32_t *)&g_Nodeaddress_Read);
	}
	MODBUS_HOLDING_REGISTERS[HOLDING_NODE_ADDRESS].actual_value = g_Nodeaddress_Read;
}
