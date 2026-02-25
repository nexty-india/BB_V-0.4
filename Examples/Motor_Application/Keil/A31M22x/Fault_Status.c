#include "Fault_Status.h"
#include "Application_Holding_Register.h"
#include "DI1_Status.h"
#include "Application_Input_Register.h"

bool g_Fault_Clear = 0;
BYPASS_flag_t bypass_Fl;
Fault_Flag Fault;
Counter_t delay_counter;
uint8_t rotolock,g_Retry_flag;
uint8_t g_Retrycount=1,g_waitFlag,g_previous_fault,g_roto_counter;
uint16_t Fault_count,FaultBypass,g_rotorstatus;
bool g_per_off;
/*
 * Function Name : FaultRecieve
 * Description   :
 *  - Reads the fault status bitfield received from Modbus.
 *  - Each bit in MODBUS_FAULT_STATUS represents a specific fault condition.
 *  - The function scans all 16 fault bits and decodes active faults.
 *  - When a fault bit is set, the corresponding internal fault flag
 *    in the Fault.Fault_bits structure is asserted.
 *  - These decoded fault flags are used by the system for protection,
 *    indication, and control logic.
 *  - If at least one fault is active, a global fault-clear request flag
 *    is set and reported back to Modbus.
 */
void FaultRecieve(void)
{
			//Fault_count = modbus_parameter.MODBUS_FAULT_STATUS;   // Receive fault bitfield
	
			for(int i = 0; i < 16; i++)
			{
				if(Fault_count & (1 << i))   // If this fault bit is SET
				{
					switch(i)
					{
						case FAULT_CRITICALOVERCURRENT:
						Fault.Fault_bits.CriticalOverCurrent_Fault = 1;
						break;

						case FAULT_CRITICALOVERVOLTAGE:
						Fault.Fault_bits.CriticalOverVoltage_Fault = 1;
						break;

						case FAULT_OVERCURRENT:
						Fault.Fault_bits.overCurrent_Fault = 1;
						break;

						case FAULT_UNDERVOLTAGE:
						Fault.Fault_bits.UnderVoltage_Fault = 1;
						
						break;

						case FAULT_OVERLOAD:
						Fault.Fault_bits.OverLoad_Fault = 1;
						break;

						case FAULT_OVERSPEED:
						Fault.Fault_bits.OverSpeed_Fault = 1;
						break;

						case FAULT_ROTOR_LOCKED:
						//rotolock = 1;
						Fault.Fault_bits.RotorLock_Fault = 1;
						break;

						case FAULT_MOTOR_TEMPERATURE:
						Fault.Fault_bits.WindingTemperature_Fault = 1;
						break;

						case FAULT_IPM_TEMPERATURE:
						Fault.Fault_bits.IGBTTemperatue_Fault = 1;
						break;

						case FAULT_AC_LINE_BREAK:
						Fault.Fault_bits.ACLineBreak_Fault = 1;
						break;

						case FAULT_MODBUS_COMMUNICATION:
						Fault.Fault_bits.ModbusCommunication_Fault = 1;
						break;

						case FAULT_FIRE_SIGNAL:
						Fault.Fault_bits.FireSignal_Fault = 1;
						break;

						case FAULT_STATIC_PRESSURE_FILTER:
						Fault.Fault_bits.StaticPressureFilter = 1;
						break;

						case FAULT_OVER_RMSVOLTAGE:
							Fault.Fault_bits.OverRMSVoltage_Fault = 1;
						break;
						
						default:
						break;
					}
				}
			}
			
}


/**
* @brief This Function Check the Under DC voltage Occurance and Recovery 
* 
* This Function Execute every 1 miiliseconds
*
*/
uint16_t DC_VoltageActual = 0,Under_Voltage_Limit = 0,Under_voltage_Reovery_Limit = 0;
void DC_Under_VoltageFault(void)
{
	
	DC_VoltageActual = modbus_parameter.MODBUS_READ_AC_VOLTAGE/10;// modbus_parameter.MODBUS_READ_DC_VOLTAGE;
	Under_Voltage_Limit = MODBUS_HOLDING_REGISTERS[HOLDING_UNDER_VOLTAGE_FAULT_LIMIT].actual_value;
	Under_voltage_Reovery_Limit = MODBUS_HOLDING_REGISTERS[HOLDING_RECOVERY_UNDER_VOLTAGE_LIMIT].actual_value;
	
		if(g_per_off == 1)
		return;
	
	
	//UnderVoltage Fault
	if((Fault.Fault_bits.UnderVoltage_Fault == 0)&&(DC_VoltageActual < Under_Voltage_Limit))
	{
		if(delay_counter.under_voltage_fault++ > UNDER_VOLTAGE_FAULT_COUNTER)
		{
			delay_counter.under_voltage_fault = 0;
			Fault.Fault_bits.UnderVoltage_Fault = 1;
					g_flash_check = 1;
g_flash_rem = 1;
			Remain_check = 1;
		}
	}
	else{
		delay_counter.under_voltage_fault = 0;
			
	}
	
	//Recovery Section
	if(Fault.Fault_bits.UnderVoltage_Fault == 1)
	{
		if(delay_counter.under_voltage_recovery_fault < UNDER_VOLTAGE_FAULT_RECOVERY_COUNTER)
		{
			delay_counter.under_voltage_recovery_fault++;
		}
		
		if(delay_counter.under_voltage_recovery_fault < UNDER_VOLTAGE_FAULT_RECOVERY_COUNTER)
		{
			if(DC_VoltageActual > Under_voltage_Reovery_Limit)
			{
				delay_counter.under_voltage_recovery_fault = 0;
				Fault.Fault_bits.UnderVoltage_Fault = 0;
			
			}
		}
		
		if(delay_counter.under_voltage_recovery_fault > UNDER_VOLTAGE_FAULT_RECOVERY_COUNTER)
		{
			g_per_off = 1;
			delay_counter.under_voltage_recovery_fault = 0;
		}
}

}
/**
* @brief This Function Check the Over Load Fault Occurance and Recovery 
* 
* This Function Execute every 1 miiliseconds
*
*/
uint16_t OverloadActual = 0,OverLoadLimit = 0, OverLoadRecovery_Limit = 0;
void OverLoadFault(void)
{
	
	OverloadActual = g_PowerFilt;
	OverLoadLimit = MODBUS_HOLDING_REGISTERS[HOLDING_OVER_LOAD_LIMIT].actual_value;
	OverLoadRecovery_Limit = MODBUS_HOLDING_REGISTERS[HOLDING_RECOVERY_OVERLOAD_FAULT_LIMIT].actual_value;
	
		if(g_per_off == 1)
		return;
	
	//OverLoad Fault....
	if((Fault.Fault_bits.OverLoad_Fault == 0)&&(OverloadActual > OverLoadLimit))
	{
		if(delay_counter.over_load_fault++ >OVER_LOAD_FAULT_COUNTER)
		{
			delay_counter.over_load_fault = 0;
			Fault.Fault_bits.OverLoad_Fault = 1;
		}
	}
	else{
		delay_counter.over_load_fault = 0;
	}
	
	
	if(Fault.Fault_bits.OverLoad_Fault == 1)
	{
		if(delay_counter.overload_recovery_fault < OVER_LOAD_FAULT_RECOVERY_COUNTER)
		{
			delay_counter.overload_recovery_fault++;
		}
		
		if(delay_counter.overload_recovery_fault < OVER_LOAD_FAULT_RECOVERY_COUNTER)
		{
			if(OverloadActual < OverLoadRecovery_Limit)
			{
				delay_counter.overload_recovery_fault = 0;
				Fault.Fault_bits.OverLoad_Fault = 0;
			}
		}
		
		if(delay_counter.overload_recovery_fault > OVER_LOAD_FAULT_RECOVERY_COUNTER)
		{
			g_per_off = 1;
			delay_counter.overload_recovery_fault = 0;
		}
		
	}
}

/**
* @brief This Function Check the Over Speed Occurance and Recovery 
* 
* This Function Execute every 1 miiliseconds
*
*/

void OverSpeedFault(void)
{
	uint16_t ActulSpeed = 0, OverSpeedLimit = 0, OverSpeedRecoveryLimit = 0;
	ActulSpeed = modbus_parameter.MODBUS_ACTUAL_SPEED;
	OverSpeedLimit = MODBUS_HOLDING_REGISTERS[HOLDING_OVER_SPEED_LIMIT].actual_value;
	OverSpeedRecoveryLimit = MODBUS_HOLDING_REGISTERS[HOLDING_RECOVERY_SPEED_FAULT_LIMIT].actual_value;

	
	if(g_per_off == 1)
		return;
  //Overspeed fault
	if((Fault.Fault_bits.OverSpeed_Fault == 0)&&(ActulSpeed > OverSpeedLimit))
	{
		if(delay_counter.over_speed_fault++ > OVER_SPEED_FAULT_COUNTER)
		{
			delay_counter.over_speed_fault = 0;
			Fault.Fault_bits.OverSpeed_Fault = 1;
		}
	}
	else{
		delay_counter.over_speed_fault = 0;
	}
	
 //Recovery Fault
	if(Fault.Fault_bits.OverSpeed_Fault == 1)
	{
		if(delay_counter.over_speed_recovery_fault < OVER_SPEED_FAULT_RECOVERY_COUNTER)
		{
			delay_counter.over_speed_recovery_fault++;
		}
		
		if(delay_counter.over_speed_recovery_fault < OVER_SPEED_FAULT_RECOVERY_COUNTER)
		{
			if(ActulSpeed < OverSpeedRecoveryLimit)
			{
				delay_counter.over_speed_recovery_fault = 0;
				Fault.Fault_bits.OverSpeed_Fault = 0;
			}
		}
		
		if(delay_counter.over_speed_recovery_fault >= OVER_SPEED_FAULT_RECOVERY_COUNTER)
		{
			g_per_off = 1;
			delay_counter.over_speed_recovery_fault = 0;
			Fault.Fault_bits.OverSpeed_Fault = 0;
		}
		
	}

}

/**
* @brief This Function Check the Rotor Lock Recovery 
* 
* This Function Execute every 1 miiliseconds
*
*/
uint16_t g_motor_rotorlock_recovery_limit = 0,Rec_RotorFault;
bool g_triesout;
uint8_t g_Rotorclear;
uint16_t Rotorlockcounter = 5000;
void RecoveryRotorLock(void)
{
	g_motor_rotorlock_recovery_limit = MODBUS_HOLDING_REGISTERS[HOLDING_ANTI_LOCK_RETIES_ROTOR_LOCK].actual_value;
	
	if(((Fault_count & (1 << FAULT_ROTOR_LOCKED))&&(g_Fault_Clear == 0)))
	{
		if(g_Retrycount < g_motor_rotorlock_recovery_limit)
		{
			if(delay_counter.Rotor_lock_recovery_fault++ > Rotorlockcounter)
			{
				delay_counter.Rotor_lock_recovery_fault = 0;
				
				g_Retrycount++;
				g_Fault_Clear = 1;
				
			}
		}
		else if(g_motor_rotorlock_recovery_limit > 255)
		{
			if(delay_counter.Rotor_lock_recovery_fault++ > Rotorlockcounter)
			{
				delay_counter.Rotor_lock_recovery_fault = 0;
				g_Fault_Clear = 1;
			}
		}
	}
	else if(g_Fault_Clear == 1)
	{
		if((Fault_count & (1 << FAULT_ROTOR_LOCKED))==0)
		{
			g_Fault_Clear = 0;
		}
	}
	
	
	if(Fault_count == 0)
	{
		g_Fault_Clear = 0;
		Fault.Fault_bits.RotorLock_Fault = 0;
	}
	
//	if(rotolock == 1)
//	{
//		rotolock = 0;
//		Fault.Fault_bits.RotorLock_Fault = 1;
//	}
}
	

/**
* @brief This Function Check the Over RMS voltage Occurance and Recovery 
* 
* This Function Execute every 1 miiliseconds
*
*/

void OverRMSVoltageFault(void)
{
	uint16_t RMSVoltageActual,OverRMSVoltageLimit = 0,OverRecoveryRMSVoltageLimit = 0;
	RMSVoltageActual = modbus_parameter.MODBUS_READ_AC_VOLTAGE/10;
	OverRMSVoltageLimit = MODBUS_HOLDING_REGISTERS[HOLDING_OVER_RMS_VOLTAGE_LIMIT].actual_value;
	OverRecoveryRMSVoltageLimit = MODBUS_HOLDING_REGISTERS[HOLDING_RECOVERY_AC_OVER_VOLTAGE_LIMIT].actual_value;
	
	
	if(g_per_off == 1)
		return;
	
	if((Fault.Fault_bits.OverRMSVoltage_Fault == 0)&&(RMSVoltageActual > OverRMSVoltageLimit))
	{
		if(delay_counter.over_Rms_Fault++ > UNDER_RMS_VOLTAGE_FAULT_COUNTER)
		{
			delay_counter.over_Rms_Fault = 0;
			Fault.Fault_bits.OverRMSVoltage_Fault = 1;
		}
	}
	else{
		delay_counter.over_Rms_Fault = 0;
	}
	
 //Recovery Fault
	if(Fault.Fault_bits.OverRMSVoltage_Fault == 1)
	{
		if(delay_counter.over_Rms_recovery_Fault < OVER_RMS_VOLTAGE_RECOVERY_FAULT_COUNTER)
		{
			delay_counter.over_Rms_recovery_Fault++;
		}
		
		if(delay_counter.over_Rms_recovery_Fault < OVER_RMS_VOLTAGE_RECOVERY_FAULT_COUNTER)
		{
			if(RMSVoltageActual < OverRecoveryRMSVoltageLimit)
			{
				delay_counter.over_Rms_recovery_Fault = 0;
				Fault.Fault_bits.OverRMSVoltage_Fault = 0;
				g_Fault_Clear = 1;
			}
		}
		
		if(delay_counter.over_Rms_recovery_Fault >= OVER_RMS_VOLTAGE_RECOVERY_FAULT_COUNTER)
		{
			g_per_off = 1;
			delay_counter.over_Rms_recovery_Fault = 0;
			Fault.Fault_bits.OverRMSVoltage_Fault = 1;
		}
	}
	
}	


/**
* @brief This Function Check the Fire Fault Occurance and Recovery 
* 
* This Function Execute every 1 miiliseconds
*
*/
bool g_FireCheck;
void FireFault(void)
{
	if(g_FireEnableMode == 1)
	{
		Fault.Fault_bits.FireSignal_Fault = 1;
		g_FireCheck = Fault.Fault_bits.FireSignal_Fault;
		/* Update fire status to Modbus input register */
	}
	else if(g_FireEnableMode == 0)
	{
		Fault.Fault_bits.FireSignal_Fault = 0;
		g_FireCheck = Fault.Fault_bits.FireSignal_Fault;
	}
	else{
	}
	MODBUS_INPUT_REGISTERS[INPUT_FIRE_STATUS].actual_value = g_FireCheck; 
	
}


void StaticPressureFilter(void)
{
	bool StaticFilterinput = 0;
	StaticFilterinput = MODBUS_HOLDING_REGISTERS[HOLDING_STATIC_PRESSURE_FILTER_CHOKE].actual_value;
	
	if(StaticFilterinput == 1)
	{
		Fault.Fault_bits.StaticPressureFilter = 1;
	}
	else{
		Fault.Fault_bits.StaticPressureFilter = 0;
	}
	
}

void ClearFaultCheck(void)
{
	if(Fault_count & (1<< FAULT_CRITICALOVERCURRENT)||
		 Fault_count & (1<< FAULT_CRITICALOVERVOLTAGE))
	{
		g_Fault_Clear = 1;
		Fault.Fault_bits.CriticalOverCurrent_Fault = 0;
		Fault.Fault_bits.CriticalOverVoltage_Fault = 0;
	}
}


/**
* @brief This Function Check All the Fault Seprately 
* 
* This Function Execute every 1 miiliseconds
*
*/
void OccRecFault(void)   //This Funciton Excute at every 1 milli second loop 
{
	FaultRecieve();
	BypassFault();
	if(bypass_Fl.BYPASS_DCUNDERVOLT_F)
	{
	}else{
	DC_Under_VoltageFault();
		}
	
	OverSpeedFault();
	OverLoadFault();

	RecoveryRotorLock();
	ClearFaultCheck();

  if(bypass_Fl.BYPASS_ACOVERVOLT_F){}else{
	OverRMSVoltageFault();}

	
	
	if(Fault.Fault_Count != 0)
	{
		g_Fault_Clear = 1;
	}		
	
	modbus_parameter.FAULT_CLEAR_STATUS = g_Fault_Clear;
}





/**
*@breif :- Detection 4 fault of Drive system in Circular Buffer manner
*/

uint16_t g_CurrentFault = 0,g_PerviousFault=0;
uint16_t g_arr[4],g_index;
void FaultIndication(void)
{
//	g_CurrentFault = modbus_parameter.MODBUS_FAULT_STATUS;
//    if ((g_CurrentFault != g_PerviousFault) && (g_CurrentFault != 0))
//    {
//        g_arr[g_index] = g_CurrentFault;
//        g_index = (g_index + 1) % 4;
//        g_PerviousFault = g_CurrentFault;
//    }
//    else if (g_CurrentFault == 0)
//    {
//        g_PerviousFault = 0;
//    }
//	MODBUS_INPUT_REGISTERS[INPUT_LAST_ERROR_CODE_1ST].actual_value = g_arr[0];
//	MODBUS_INPUT_REGISTERS[INPUT_LAST_ERROR_CODE_2ND].actual_value = g_arr[1];
//	MODBUS_INPUT_REGISTERS[INPUT_LAST_ERROR_CODE_3RD].actual_value = g_arr[2];
//	MODBUS_INPUT_REGISTERS[INPUT_LAST_ERROR_CODE_4TH_TIME].actual_value = g_arr[3];
}



void BypassFault(void)
{
	FaultBypass = MODBUS_HOLDING_REGISTERS[HOLDING_FAULTCHECK].actual_value;
	
	bypass_Fl.BYPASS_OCURRNET_F     = (FaultBypass & BYPASS_OCURRNET)      ? 1U : 0U;
	bypass_Fl.BYPASS_DCUNDERVOLT_F  = (FaultBypass & BYPASS_DCUNDERVOLTAG)   ? 1U : 0U;
	bypass_Fl.BYPASS_ROTORLOCK_F    = (FaultBypass & BYPASS_ROTORLOCK)     ? 1U : 0U;
	bypass_Fl.BYPASS_IPMTEMP_F      = (FaultBypass & BYPASS_IPMTEMP)       ? 1U : 0U;
	bypass_Fl.BYPASS_WINDTEMP_F     = (FaultBypass & BYPASS_WINDTEMP)      ? 1U : 0U;
	bypass_Fl.BYPASS_ACOVERVOLT_F   = (FaultBypass & BYPASS_ACOVERVOLTAGE) ? 1U : 0U;
	
}

