#include "DI1_Status.h"
#include "Modbus_Comm.h"
#include "Bharat_Bijlee.h"
#include "user_statemachine.h"
#include "MODBUS_Status.h"
#include "Application_Holding_Register.h"
/**/
extern Modbus_Parameter modbus_parameter;
extern MODBUS_REGISTER_t Modbus_Register;
uint16_t DI1_counter,DI2_counter;
bool DI1_STATUS_CHECK = 0,DI2_STATUS_CHECK;
bool DI1_STATUS_ENABLE,DI2_STATUS_ENABLE;
/**
 * @brief  Selects operating mode and updates target RPM.
 *         This function is executed every 1 ms.
 *
 * Priority order:
 *   1. Fire mode (highest priority)
 *   2. DI1 manual control
 *   3. Stop condition
 */
void MODE_SELECTION(void)    // Run every 1 ms
{
	uint16_t g_Fire_Status = 0;
	uint16_t fire_alarm = 0;
	uint8_t  di1_status = 0;
	uint8_t  di1_pressed = 0;
	/* Read inputs */
	di1_status    = DI1_MOTOR_STATUS();
	di1_pressed   = DI1_ENABLE();
	g_Fire_Status = DI2_ENABLE();

	fire_alarm = MODBUS_HOLDING_REGISTERS[HOLDING_FIRE_ALARM_ACTIVATE].actual_value;
	MODBUS_INPUT_REGISTERS[INPUT_FIRE_STATUS].actual_value = fire_alarm;

	/* ---------------- FIRE MODE ---------------- */
	if (fire_alarm == 1)
	{
			if ((g_Fire_Status == 1) ||(controlmode.MODBUS_FLAG_BIT == 1))    /* Fire mode enabled via DI2 or Modbus command */
			{
					FIRE_STATUS();      // sets speed internally
					return;             
			}
	}

	/* ---------------- DI1 MODE ---------------- */
	if (di1_status == 1)
	{
		if(di1_pressed == 1)
		{
			DI1_SWITCH_RPM_ENABLE();  // sets g_target_Speed
		}
		else{
			 g_target_Speed = 0;
		}
	}
	else
	{
			/* ---------------- STOP ---------------- */
			g_target_Speed = 0;
	}
}



/**
 * @brief  Returns DI1 motor enable status from Modbus configuration.
 *
 * @return 1 = DI1 motor control enabled
 *         0 = DI1 motor control disabled
 */

int DI1_MOTOR_STATUS(void)
{
	bool DI1_check = 0;
	uint16_t MODBUS_DI1_STATUS = 0 ;
	DI1_check = MODBUS_HOLDING_REGISTERS[HOLDING_DI1_FUNCTION].actual_value;    /* Read DI1 function enable status from Modbus holding register */
	
	if(DI1_check == 1)                 /* Return DI1 status */        
	{
		return MODBUS_DI1_STATUS = 1;
	}
	else 
	{
		return MODBUS_DI1_STATUS = 0;
	}
}



/**
 * @brief  Reads DI1 GPIO input and generates a valid DI1 event
 *         after continuous HIGH for 500 ms (debounce / validation).
 *
 * @return true  = DI1 valid event detected
 *         false = DI1 not active
 */
bool DI1_ENABLE(void)
{
	uint16_t digital_1_status;
	digital_1_status = HAL_GPIO_ReadPin(PB);   // Read GPIO port B input data
	if(digital_1_status & (1 << 4))
	{
		DI1_STATUS_CHECK = 1;   //high 
	}
	else 
	{
		DI1_STATUS_CHECK = 0;
	}
	
	if((DI1_counter < 500)&&(DI1_STATUS_CHECK == 1))      /* -------- Debounce / Validation Counter -------- */
	{
		DI1_counter++;
	}
	else if(DI1_STATUS_CHECK == 0)
	{
		DI1_counter = 0;
	}

	if(DI1_counter == 500)                                                   /* -------- Event Generation -------- */
	{
		return SYSTEM_DRIVE_EVENT.DRIVE_STATUS.DI1_STATUS_EVENT_FLAG = 1;
	}
	else
		{
		return 	SYSTEM_DRIVE_EVENT.DRIVE_STATUS.DI1_STATUS_EVENT_FLAG = 0;
	}
}


/**
 * @brief  Enables RPM control via DI1 switch.
 *         Delegates RPM selection to the control mode handler.
 *
 * This function is called when DI1 is active and validated.
 */
void DI1_SWITCH_RPM_ENABLE(void)
{
	CONTROL_MODE_SELECT();
}



/**
 * @brief  Reads DI2 GPIO input and validates Fire input
 *         after continuous HIGH for 500 ms.
 *
 * @return true  = DI2 (Fire input) valid
 *         false = DI2 inactive
 */
bool DI2_ENABLE(void)
{
	uint16_t digital_2_status;
	digital_2_status = HAL_GPIO_ReadPin(PB);   // Read GPIO port B input data
	if(digital_2_status & (1 << 3))
	{
		DI2_STATUS_CHECK = 1;
	}
	else
	{
		DI2_STATUS_CHECK = 0;
	}
	
	/* -------- Debounce / Validation Counter -------- */
	if((DI2_counter < 500)&&(DI2_STATUS_CHECK == 1))
	{
		DI2_counter++;
	}
	else if(DI2_STATUS_CHECK == 0)
	{
		DI2_counter = 0;
	}

	if(DI2_counter == 500)                    /* -------- Fire Input Enable -------- */
	{
		return DI2_STATUS_ENABLE = 1;
	}
	else
		{
		return 	DI2_STATUS_ENABLE = 0;
	}
}


/**
 * @brief  Handles Fire mode operation and sets target speed
 *         based on Fire mode configuration via Modbus.
 *
 * FireMode:
 *   1 = Stop motor
 *   2 = Run forward at fire alarm speed
 *   3 = Run reverse at fire alarm speed
 */
void FIRE_STATUS(void)
{
    uint16_t Fan_direction = 0;
    int16_t  Firealaram_Target_Speed = 0;
    int16_t  Target_DI2_speed = 0;
    int16_t  FireMode = 0;

    /* Read fire-related parameters from Modbus holding registers */
    Fan_direction = MODBUS_HOLDING_REGISTERS[HOLDING_FAN_ROTATION].actual_value;

    Firealaram_Target_Speed = MODBUS_HOLDING_REGISTERS[HOLDING_SET_SPEED_IN_FIRE_ALARAM_MODE].actual_value;

    FireMode = MODBUS_HOLDING_REGISTERS[HOLDING_RESERVED_25].actual_value;

    /* -------- Fire Mode Decision -------- */
    if (FireMode == 1)
    {
        /* Fire Mode 1: Stop motor */
        Target_DI2_speed = 0;
    }
    else if (FireMode == 2)
    {
        /* Fire Mode 2: Forward direction */
        Target_DI2_speed = Firealaram_Target_Speed;
    }
    else if (FireMode == 3)
    {
        /* Fire Mode 3: Reverse direction */
        Target_DI2_speed = Firealaram_Target_Speed |= 0x8000;
    }

    /* Apply fire target speed */
    g_target_Speed = Target_DI2_speed;
}



