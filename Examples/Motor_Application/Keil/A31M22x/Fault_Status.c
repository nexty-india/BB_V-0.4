#include "Fault_Status.h"
#include "Application_Holding_Register.h"
uint32_t OVER_TEMPERATUE_HEAT_SINK_COUNTER,LAST_ERROR_CODE_1COUNTER,LINE_FAULT_COUNTER;
uint32_t MOTOR_BLOCK_COUNTER,IGBT_FAULT_COUNTER,DC_UNDER_VOLTAGE_COUNTER,DC_UNDER_VOLTAGE_COUNTER;
uint32_t DC_OVER_VOLTAGE_COUNTER,COMMUNICATION_FAULT_COUNTER,LINE_UNDER_VOLTAGE_COUNTER;
uint32_t LINE_OVER_VOLTAGE_COUNTER,PEAK_CURRENT_COUNTER,OVERLOAD_COUNTER;
uint32_t OVERHEATING_WINDING_COUNTER,FIRE_SIGANL_COUNTER,STATIC_PRESSURE_FILTER_COUNTER,LAST_ERROR_CODE_COUNTER;
uint16_t Fault_COunt =0;

uint32_t g_over_current_fault_counter;
uint16_t g_Fault_Clear = 0;
uint8_t g_Rotor_lock_count = 0;
Fault_Flag Fault;
uint16_t Fault_check;
Counter_t delay_counter;
uint16_t g_previous_rotolock,g_roto_counter=0,g_Retry_flag;
uint8_t g_Retrycount,g_waitFlag,g_previous_fault;
uint16_t Fault_count;
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
			Fault_count = modbus_parameter.MODBUS_FAULT_STATUS;   // Receive fault bitfield
	
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

						case FAULT_OVERVOLTAGE:
						Fault.Fault_bits.OverVoltage_Fault = 1;
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
						Fault.Fault_bits.PIDSensor_Fault = 1;
						break;

						default:
						break;
					}
				}
			}
			
			if(Fault.Fault_Count != 0)
			{
				g_Fault_Clear = 1;
				
			}
			else{
				g_Fault_Clear = 0;
			}
			modbus_parameter.FAULT_CLEAR_STATUS = g_Fault_Clear;
			
}



void FaultDetection(void)
{
	uint16_t Rmsvoltage_temp = 0,Load_temp = 0,Speed_temp = 0,IGBT_temp = 0,Winding_temp = 0;
	
	uint16_t over_voltagelimit_temp = 0;
	uint16_t under_voltagelimit_temp = 0,over_loadlimit_temp = 0;
	uint16_t over_speedlimit_temp = 0,over_ipm_temperaturelimit_temp = 0;
	uint16_t over_winding_temperaturelimit_temp = 0;
	
	Rmsvoltage_temp = modbus_parameter.MODBUS_READ_DC_VOLTAGE;
	Load_temp = modbus_parameter.KW;
	Speed_temp = modbus_parameter.MODBUS_ACTUAL_SPEED;
	IGBT_temp = modbus_parameter.MODBUS_IPM_TEMPERATURE;
	Winding_temp = modbus_parameter.MODBUS_MOTOR_TEMPERATURE;
	
	over_voltagelimit_temp = MODBUS_HOLDING_REGISTERS[HOLDING_OVER_VOLTAGE_LIMIT].actual_value;
	under_voltagelimit_temp = MODBUS_HOLDING_REGISTERS[HOLDING_UNDER_VOLTAGE_FAULT_LIMIT].actual_value;
  over_loadlimit_temp = MODBUS_HOLDING_REGISTERS[HOLDING_OVER_LOAD_LIMIT].actual_value;
	over_speedlimit_temp = MODBUS_HOLDING_REGISTERS[HOLDING_OVER_SPEED_LIMIT].actual_value;
  over_ipm_temperaturelimit_temp = MODBUS_HOLDING_REGISTERS[HOLDING_OVER_IPM_TEMPERATURE_LIMIT].actual_value;
  over_winding_temperaturelimit_temp = MODBUS_HOLDING_REGISTERS[HOLDING_OVER_LIMIT_WINDING_TEMPERATURE].actual_value;
	
	//OverVoltage Fault
	if((Fault.Fault_bits.OverVoltage_Fault == 0)&&(Rmsvoltage_temp > over_voltagelimit_temp))
	{
		if(user_delay(OVER_VOLTAGE_FAULT_COUNTER,&delay_counter.over_voltage_fault))
		{
			Fault.Fault_bits.OverVoltage_Fault = 1;
		}
	}
	else{
		delay_counter.over_voltage_fault = 0;
	}
	
	//UnderVoltage Fault
	if((Fault.Fault_bits.UnderVoltage_Fault == 0)&&(Rmsvoltage_temp < under_voltagelimit_temp))
	{
		if(user_delay(UNDER_VOLTAGE_FAULT_COUNTER,&delay_counter.under_voltage_fault))
		{
			Fault.Fault_bits.UnderVoltage_Fault = 1;
		}
	}
	else{
		delay_counter.under_voltage_fault = 0;
	}
	
	
	//OverLoad Fault
	if((Fault.Fault_bits.OverLoad_Fault == 0)&&(Load_temp > over_loadlimit_temp))
	{
		if(user_delay(OVER_LOAD_FAULT_COUNTER,&delay_counter.over_load_fault))
		{
			Fault.Fault_bits.OverLoad_Fault = 1;
		}
	}
	else{
		delay_counter.over_load_fault = 0;
	}
	
	
	//Overspeed fault
	if((Fault.Fault_bits.OverSpeed_Fault == 0)&&(Speed_temp > over_speedlimit_temp))
	{
		if(user_delay(OVER_SPEED_FAULT_COUNTER,&delay_counter.over_speed_fault))
		{
			Fault.Fault_bits.OverSpeed_Fault = 1;
		}
	}
	else{
		delay_counter.over_speed_fault = 0;
	}
	
	
	//IGBT Temperature Fault
	if(g_BYPASS_TMP_IGBT == 1)
	{
		
	}
	else if((Fault.Fault_bits.IGBTTemperatue_Fault == 0)&&(IGBT_temp > over_ipm_temperaturelimit_temp))
	{
		if(g_BYPASS_TMP_IGBT == 0){
		if(user_delay(OVER_IPM_TEMPERATURE_FAULT_COUNTER,&delay_counter.ipm_temperature_fault))
		{
			Fault.Fault_bits.IGBTTemperatue_Fault = 1;
		}
	}
	}
	else{
		delay_counter.ipm_temperature_fault = 0;
	}
	
	//Winding Temperature Fault
	if(g_BYPASS_TMP_WINDING == 1)
	{
		
	}
	else if((Fault.Fault_bits.WindingTemperature_Fault == 0)&&(Winding_temp > over_winding_temperaturelimit_temp))
	{
		if(g_BYPASS_TMP_WINDING == 0){
		if(user_delay(OVER_WINDING_TEMPERATURE_FAULT_COUNTER,&delay_counter.motor_winding_temperature_fault))
		{
			Fault.Fault_bits.WindingTemperature_Fault = 1;
		}
	}
}
	else{
		delay_counter.motor_winding_temperature_fault = 0;
	}
}


void FaultRecovery(void)
{

	uint16_t Rmsvoltage_temp = 0,Load_temp = 0,Speed_temp = 0,IGBT_temp = 0,Winding_temp = 0;
	
	uint16_t motor_over_voltage_recovery_limit = 0;
	uint16_t motor_under_voltage_recovery_limit = 0,motor_overload_recovery_limit = 0;
	uint16_t motor_overspeed_recovery_limit = 0,motor_ipm_temperature_recovery_limit = 0;
	uint16_t motor_winding_temperature_recovery_limit = 0,motor_rotorlock_recovery_limit = 0;
	
	Rmsvoltage_temp = modbus_parameter.MODBUS_READ_DC_VOLTAGE;
	Load_temp = modbus_parameter.KW;
	Speed_temp = modbus_parameter.MODBUS_ACTUAL_SPEED;
	IGBT_temp = modbus_parameter.MODBUS_IPM_TEMPERATURE;
	Winding_temp = modbus_parameter.MODBUS_MOTOR_TEMPERATURE;
	

	motor_over_voltage_recovery_limit = MODBUS_HOLDING_REGISTERS[HOLDING_RECOVERY_OVER_VOLTAGE_LIMIT].actual_value;
	motor_under_voltage_recovery_limit = MODBUS_HOLDING_REGISTERS[HOLDING_RECOVERY_VOLTAGE_FAULT_LIMIT].actual_value;
	motor_overload_recovery_limit = MODBUS_HOLDING_REGISTERS[HOLDING_RECOVERY_VOLTAGE_FAULT_LIMIT].actual_value;
	motor_rotorlock_recovery_limit = MODBUS_HOLDING_REGISTERS[HOLDING_ANTI_LOCK_RETIES_ROTOR_LOCK].actual_value;
	motor_ipm_temperature_recovery_limit = MODBUS_HOLDING_REGISTERS[HOLDING_RECOVERY_IPM_TEMPERATURE_LIMIT].actual_value;
	motor_winding_temperature_recovery_limit = MODBUS_HOLDING_REGISTERS[HOLDING_RECOVERY_LIMIT_WINDING_TEMPERATURE].actual_value;
	
	
	
	//Check Recovery of over voltage limit
	if((Fault.Fault_bits.OverVoltage_Fault == 1)&&(Rmsvoltage_temp < motor_over_voltage_recovery_limit))
	{
		if(user_delay(OVER_VOLTAGE_FAULT_RECOVERY_COUNTER,&delay_counter.over_voltage_recovery_fault))
		{
			Fault.Fault_bits.OverVoltage_Fault = 0;
		}
	}
	else{
		delay_counter.over_voltage_recovery_fault = 0;
	}
	

	//Check Recovery of under voltage limit 	
	if((Fault.Fault_bits.UnderVoltage_Fault == 1)&&(Rmsvoltage_temp > motor_under_voltage_recovery_limit))
	{
		if(user_delay(UNDER_VOLTAGE_FAULT_RECOVERY_COUNTER,&delay_counter.under_voltage_recovery_fault))
		{
			Fault.Fault_bits.UnderVoltage_Fault = 0;
			g_Fault_Clear = 1;
		}
	}
	else{
		delay_counter.under_voltage_recovery_fault = 0;
	}
	
	//Check Recovery of overload limit
	if((Fault.Fault_bits.OverLoad_Fault == 1)&&(Load_temp < motor_overload_recovery_limit))
	{
		if(user_delay(OVER_LOAD_FAULT_RECOVERY_COUNTER,&delay_counter.overload_recovery_fault))
		{
			Fault.Fault_bits.OverLoad_Fault = 0;
			g_Fault_Clear = 1;
		}
	}
	else{
		delay_counter.overload_recovery_fault = 0;
	}
	
//	//Check Recovery of Overspeed Fault limit
	if((Fault.Fault_bits.OverSpeed_Fault == 1)&&(Speed_temp < motor_overspeed_recovery_limit))
	{
		if(user_delay(OVER_SPEED_FAULT_RECOVERY_COUNTER,&delay_counter.over_speed_recovery_fault))
		{
			Fault.Fault_bits.OverSpeed_Fault = 0;
			g_Fault_Clear = 1;
		}
	}
	else{
		delay_counter.over_speed_recovery_fault = 0;
	}
	

	//Check Recovery of Motor Winding Temperature fault
	if((Fault.Fault_bits.WindingTemperature_Fault == 1)&&(Winding_temp < motor_winding_temperature_recovery_limit))
	{
		if(user_delay(OVER_WINDING_TEMPERATURE_RECOVERY_FAULT_COUNTER,&delay_counter.motor_winding_temperature_recovery_fault))
		{
			Fault.Fault_bits.WindingTemperature_Fault = 0;
			g_Fault_Clear = 1;
		}
	}
	else{
		delay_counter.motor_winding_temperature_recovery_fault = 0;
	}
	
	//Check Recovery of ipm Temperature fault

	if((Fault.Fault_bits.IGBTTemperatue_Fault == 1)&&(IGBT_temp < motor_ipm_temperature_recovery_limit))
	{
		if(user_delay(OVER_IPM_TEMPERATURE_RECOVERY_FAULT_COUNTER,&delay_counter.ipm_temperature_recovery_fault))
		{
			Fault.Fault_bits.IGBTTemperatue_Fault = 0;
			g_Fault_Clear = 1;
		}
	}
	else{
		delay_counter.ipm_temperature_recovery_fault = 0;
	}
	
	
	//Recovery Rotor Lock Fault
	if ((g_previous_rotolock != Fault.Fault_bits.RotorLock_Fault)&&(Fault.Fault_bits.RotorLock_Fault == 1))
	{
		g_roto_counter++;
	}
	g_previous_rotolock = Fault.Fault_bits.RotorLock_Fault;
 
	if(g_roto_counter < motor_rotorlock_recovery_limit)
	{
		if(user_delay(ROTOR_LOCK_FAULT_RECOVERY_COUNTER,&delay_counter.Rotor_lock_recovery_fault))
		{
			g_Retry_flag = 1;
		}
	}
	
	if(g_Retry_flag == 1)
	{
		g_Fault_Clear = 1;
	}

	
	if(Fault.Fault_bits.RotorLock_Fault == 0)
	{
		g_Retry_flag = 0;
	}
	
	modbus_parameter.MODBUS_FAULT_STATUS = Fault.Fault_Count;
	
}

void SEND_RECOVERY_FAULT_STATUS(void)   //This Funciton Excute at every 1 milli second loop 
{
	FaultRecieve();
//	FaultDetection();
//	FaultRecovery();
}


/**
*@breif :- Detection 4 fault of Drive system in Circular Buffer manner
*/

uint16_t g_CurrentFault = 0,g_PerviousFault=0;
uint16_t g_arr[4],g_index;
void FaultIndication(void)
{
	g_CurrentFault = modbus_parameter.MODBUS_FAULT_STATUS;
    if ((g_CurrentFault != g_PerviousFault) && (g_CurrentFault != 0))
    {
        g_arr[g_index] = g_CurrentFault;
        g_index = (g_index + 1) % 4;
        g_PerviousFault = g_CurrentFault;
    }
    else if (g_CurrentFault == 0)
    {
        g_PerviousFault = 0;
    }
	MODBUS_INPUT_REGISTERS[INPUT_LAST_ERROR_CODE_1ST].actual_value = g_arr[0];
	MODBUS_INPUT_REGISTERS[INPUT_LAST_ERROR_CODE_2ND].actual_value = g_arr[1];
	MODBUS_INPUT_REGISTERS[INPUT_LAST_ERROR_CODE_3RD].actual_value = g_arr[2];
	MODBUS_INPUT_REGISTERS[INPUT_LAST_ERROR_CODE_4TH_TIME].actual_value = g_arr[3];
}





