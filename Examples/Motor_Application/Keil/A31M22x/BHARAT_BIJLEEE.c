#include "Bharat_Bijleee.h"
#include "MotorApplicationLayer.h"
#include "Modbus_Comm.h"
#include "Fault_indication.h"
#include "Bharat_Bijlee.h"
#include "Flash_Writing.h"
#include "Fault_Status.h"
#include "Application_Input_Register.h"
#include "Application_Holding_Register.h"
DriveStatemachine_t DRIVESTATEMACHINE = INIT_STATE;
uint32_t Wait_flash_control_counter;
uint16_t g_One_millisecond;
uint32_t g_read_NodeAddress;
/**
 * @brief Drive state machine
 *
 * Handles the initialization, normal operation, and fault operation
 * of the drive system.
 */
void DriveStateMachine(void)
{
	uint16_t flash_value = 0;
	InputRegisterData();
    /* ---- Check All Faults ---- */
    //DriveFaults();             // Updates Fault.Fault_Count etc.
		
    bool has_non_modbus_fault = 
        (Fault.Fault_Count != 0) &&
        (Fault.Fault_bits.ModbusCommunication_Fault == 0);
    FlashWriting();            // Flash Writing.
    /* ---- State Machine ---- */
    switch(DRIVESTATEMACHINE)
    {
        case INIT_STATE:
            
				flash_value = Read_Flash_U32(HOLDING_REG_FLASH_CONTROL_START_ADDR);
				g_Actal_read = flash_value & 0xFFFF;
				g_read_NodeAddress = Read_Flash_U32(NODEADDRESS);
				HourCounterInit();
				NodeAddresInit();
				if (user_delay(1000, &Wait_flash_control_counter))
				DRIVESTATEMACHINE = NORMAL_OPERATION_STATE;
				break;


        case NORMAL_OPERATION_STATE:
            EVENT_OCCUR_1_MS();           // periodic tasks
            SET_TARGET_SPEED_TO_MOTOR(); 
						
            /* Priority 1: NON-MODBUS fault */
            if (has_non_modbus_fault)
            {
                DRIVESTATEMACHINE = FAULT_OPERATION_STATE;
                break;
            }
            break;
        
				case FAULT_OPERATION_STATE:
            g_target_Speed = 0;
						FAULT_EVENT();
            FaultRecovery();      // clears faults if recovered

            /* After fault recovery, go back to normal */
            if (Fault.Fault_Count == 0)
                DRIVESTATEMACHINE = NORMAL_OPERATION_STATE;
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
			DriveStateMachine();             // Execute the main drive state machine
	}
}
