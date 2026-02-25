#include "Bharat_Bijleee.h"
#include "MotorApplicationLayer.h"
#include "Modbus_Comm.h"
#include "Fault_indication.h"
#include "Bharat_Bijlee.h"
#include "Flash_Writing.h"
#include "Fault_Status.h"
#include "Application_Input_Register.h"
#include "Application_Holding_Register.h"
#include "PID_Sensor_Status.h"
DriveStatemachine_t DRIVESTATEMACHINE = INIT_STATE;
uint32_t Wait_flash_control_counter;
uint16_t g_One_millisecond;
uint32_t g_read_NodeAddress;
uint16_t g_flash_value = 0,onesec= 0;;
/**
 * @brief Drive state machine
 *
 * Handles the initialization, normal operation, and fault operation
 * of the drive system.
 */
bool has_non_modbus_fault;
void DriveStateMachine(void)
{
    /* ---------- Fault classification ---------- */
    if ((Fault.Fault_Count != 0) &&
        (Fault.Fault_bits.ModbusCommunication_Fault == 0) &&
        (Fault.Fault_bits.FireSignal_Fault == 0))   // Rotor lock excluded
    {
        has_non_modbus_fault = 1;
    }
    else
    {
        has_non_modbus_fault = 0;
    }
     SystemHourStatus();
    /* ---------- State Machine ---------- */
    switch (DRIVESTATEMACHINE)
    {
        case INIT_STATE:

            g_Default_Write = 1;
            g_flash_value = Read_Flash_U32(HOLDING_REG_FLASH_CONTROL_START_ADDR);

            if (g_flash_value == 1)
                g_Default_Write = 0;

            HourCounterInit();
            NodeAddresInit();

            if (user_delay(200, &Wait_flash_control_counter))
            {
                DRIVESTATEMACHINE = NORMAL_OPERATION_STATE;
            }
            break;

        /* ===================================================== */

        case NORMAL_OPERATION_STATE:

            EVENT_OCCUR_1_MS();
            SET_TARGET_SPEED_TO_MOTOR();
		

            /* -------- Any other fatal fault -------- */
            if (has_non_modbus_fault)
            {
                DRIVESTATEMACHINE = FAULT_OPERATION_STATE;
                break;
            }

            break;

        
        case FAULT_OPERATION_STATE:

            g_target_Speed = 0;
            FAULT_EVENT();
            
				
//						if(g_triesout == 1)
//						{
//							g_triesout = 0;
//							 DRIVESTATEMACHINE = NORMAL_OPERATION_STATE;
//						}
            /* leave fault only when all faults cleared */
            if (Fault.Fault_Count == 0)
            {
                DRIVESTATEMACHINE = NORMAL_OPERATION_STATE;
            }
            break;
    }
}



/**
 * @brief Main application loop
 *
 * Continuously executes the drive state machine and can be extended
 * to include other periodic tasks such as UART handling, timers, or
 * communication protocols.
 */
void MAL_MainLoop(void)
{
	while(1)
	{   
			
			if(onesec >= 1)
			{
				onesec = 0;
				DriveStateMachine();             // Execute the main drive state machine
			}
	}
}
