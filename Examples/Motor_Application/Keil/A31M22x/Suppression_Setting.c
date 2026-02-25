#include "Suppression_Setting.h"
#include "Fault_Status.h"
Supression_t SuppressionSet;
IPMSuprresion_t IPM_Supp;

uint16_t g_Degrating_Target_Rpm;
SuppresActual_t SuppresActual;
/**
 * @brief  DC voltage digital filter
 *
 * This function implements a simple IIR (low-pass) filter
 * to smooth the DC bus voltage reading.
 *
 * Filtering method:
 * - Uses an accumulator-based exponential moving average
 * - Reduces noise and sudden voltage spikes
 *
 * Equation (conceptual):
 *   VDC_filtered = VDC_filtered + (VDC_input - VDC_filtered) / (2^VDC_FILT_FACTOR)
 *
 * @return Filtered DC voltage value
 */

int DC_Filter(void)
{
	vdcfilt.voltage_temp = modbus_parameter.MODBUS_READ_AC_VOLTAGE;
	vdcfilt.Temp_VDC_factor = vdcfilt.Temp_VDC_factor + (vdcfilt.voltage_temp -  vdcfilt.VDC_Filter);
	vdcfilt.VDC_Filter = vdcfilt.Temp_VDC_factor >> VDC_FILT_FACTOR;
	return vdcfilt.VDC_Filter;
}

float Current_amp=0,Current_temp = 0,currentCutoff=0;
uint16_t IpmTempdegrating = 0,WindingTempDegrating = 0;
void IPMTemperatureDegrating(void)
{
  uint16_t D_Target_rpm;
	uint16_t ipm_alpa,winding_alpha;
	float ipm_beta,winding_beta,Curr_beta,Curr_alpha;
	uint16_t IPMTemperatue = 0,SupRamprate_temp = 0;
	uint16_t WindingTemperture = 0,OverIgbtFault=0,OverWindingTemperature=0;
	
	
	float CurrentDegragting = 0.0f;
	IPMTemperatue = modbus_parameter.MODBUS_IPM_TEMPERATURE/100;
	Current_amp = g_currentFilt;
	WindingTemperture = modbus_parameter.MODBUS_MOTOR_TEMPERATURE/100;
	SuppresActual.IpmTemperature = IPMTemperatue;
	SuppresActual.WindTempertaure = WindingTemperture;
	SuppresActual.ActualCurrent = (float)Current_amp/1000;

	SuppresActual.MinSpeed =  MINIMUM_SPEED();
	SuppresActual.ActualSpeed = g_target_Speed;
	
  OverWindingTemperature = MODBUS_HOLDING_REGISTERS[HOLDING_OVER_LIMIT_WINDING_TEMPERATURE].actual_value;
	OverIgbtFault = MODBUS_HOLDING_REGISTERS[HOLDING_OVER_IPM_TEMPERATURE_LIMIT].actual_value;
	IPM_Supp.Sup_MinTemperatureigbt = MODBUS_HOLDING_REGISTERS[HOLDING_RANGE_MIN_IGBT_TEMPERATUE].actual_value;
  IPM_Supp.Sup_MinTemperatruewind = MODBUS_HOLDING_REGISTERS[HOLDING_RANGE_MIN_WINDING_TEMPERATUE].actual_value;
	Current_temp = MODBUS_HOLDING_REGISTERS[HOLDING_RANGE_MIN_MOTOR_CURRENT].actual_value;
	IPM_Supp.Sup_MinCurrent = Current_temp/100;
	currentCutoff = MODBUS_HOLDING_REGISTERS[HOLDING_CURRENTCUTOFF_LIMIT].actual_value;
	IPM_Supp.CurrentCutoff = currentCutoff/100;
	SupRamprate_temp = MODBUS_HOLDING_REGISTERS[HOLDING_SUPPRESION_RAMPRATE].actual_value;
	
	IpmTempdegrating=IPM_Supp.Sup_MinTemperatureigbt - 3;
	WindingTempDegrating = IPM_Supp.Sup_MinTemperatruewind - 3;
	CurrentDegragting = IPM_Supp.Sup_MinCurrent - 2.0f;

	if(SupRamprate_temp > 10)
	{}else{
		IPM_Supp.Ipmt_RampRate = (float) SupRamprate_temp/100;
}
	

  if(SuppressionSet.IGBT_Temperature_Supress == 1)
	{
		if(SuppresActual.IpmTemperature >= (IPM_Supp.Sup_MinTemperatureigbt))
		{
			ipm_alpa = SuppresActual.IpmTemperature - IPM_Supp.Sup_MinTemperatureigbt;
			ipm_beta = (float)IPM_Supp.Ipmt_RampRate * ipm_alpa;
			IPM_Supp.Ipmt_TaregetSpeed = (1- ipm_beta)*SuppresActual.ActualSpeed;
		}
		 else if(SuppresActual.IpmTemperature < IpmTempdegrating)
		{
			IPM_Supp.Ipmt_TaregetSpeed = g_target_Speed;
		}	
		
	}
	//bypass and cutoff
		if(bypass_Fl.BYPASS_IPMTEMP_F)
		{
     
		}
		else if(SuppresActual.IpmTemperature > OverIgbtFault)
		{
			Fault.Fault_bits.IGBTTemperatue_Fault = 1;
		}
		
	
	
		
  if(SuppressionSet.Winding_temperature_Supress == 1)
	{
		if(SuppresActual.WindTempertaure >= (IPM_Supp.Sup_MinTemperatruewind))
		{
			winding_alpha = SuppresActual.WindTempertaure - IPM_Supp.Sup_MinTemperatruewind;
			winding_beta = (float)IPM_Supp.Ipmt_RampRate * winding_alpha;
			IPM_Supp.Wind_TargetSpeed = (1- winding_beta)*SuppresActual.ActualSpeed;
		}
		else if(SuppresActual.WindTempertaure < WindingTempDegrating)
		{
			IPM_Supp.Wind_TargetSpeed = g_target_Speed;
		}
	}
	
    //cutoff and bypass
		if(bypass_Fl.BYPASS_WINDTEMP_F)
		{
     
		}
		else if(SuppresActual.WindTempertaure > OverWindingTemperature)
		{
			Fault.Fault_bits.WindingTemperature_Fault = 1;
		}


  
 
 
	if(SuppressionSet.Current_Sup == 1)
	{
		if(SuppresActual.ActualCurrent >= IPM_Supp.Sup_MinCurrent)
		{
			Curr_alpha = SuppresActual.ActualCurrent - IPM_Supp.Sup_MinCurrent;
			Curr_beta = (float)IPM_Supp.Ipmt_RampRate * Curr_alpha;
			IPM_Supp.Curr_TargetSpeed = (1- Curr_beta)*SuppresActual.ActualSpeed;
		}
		else if(SuppresActual.ActualCurrent < CurrentDegragting)
		{
			IPM_Supp.Curr_TargetSpeed = g_target_Speed;
		}
	}
	
	
	// bypass and cutoff
	if(bypass_Fl.BYPASS_OCURRNET_F)
	{
		
	}
	else if(SuppresActual.ActualCurrent > IPM_Supp.CurrentCutoff)
	{
		Fault.Fault_bits.overCurrent_Fault = 1;
		//IPM_Supp.Curr_TargetSpeed = 0;
		//g_Fault_Clear = 1;
	}
 
 
 
	
	//check minimum rpm
	if(SuppressionSet.Current_Sup)
	{
		D_Target_rpm = IPM_Supp.Curr_TargetSpeed;
	}
	
	if(SuppressionSet.Winding_temperature_Supress)
	{
		if(IPM_Supp.Wind_TargetSpeed < D_Target_rpm)
		{
			 D_Target_rpm = IPM_Supp.Wind_TargetSpeed ;
		}
		
		
	}

	if(SuppressionSet.IGBT_Temperature_Supress)
	{
		if(IPM_Supp.Ipmt_TaregetSpeed < D_Target_rpm)
		{
			 D_Target_rpm = IPM_Supp.Ipmt_TaregetSpeed ;
		}
	}

   if(SuppressionSet.IGBT_Temperature_Supress||SuppressionSet.Winding_temperature_Supress||SuppressionSet.Current_Sup)
   g_target_Speed = D_Target_rpm;	
}


uint16_t g_Supress_Select_Para = 0;
void SuppressionSelection(void)
{

	g_Supress_Select_Para = MODBUS_HOLDING_REGISTERS[HOLDING_SUPPRESSION_RANGE_SETTING].actual_value;

	
	
	if(g_Supress_Select_Para == 1)
	{
		SuppressionSet.Current_Sup = 1;
		SuppressionSet.Winding_temperature_Supress = 0;	
		SuppressionSet.IGBT_Temperature_Supress = 0;
	}
	else if(g_Supress_Select_Para == 2)
	{
		SuppressionSet.Current_Sup = 0;
		SuppressionSet.Winding_temperature_Supress = 1;	
		SuppressionSet.IGBT_Temperature_Supress = 0;
	}
	else if(g_Supress_Select_Para == 3)
	{
		SuppressionSet.Current_Sup = 1;
		SuppressionSet.Winding_temperature_Supress = 1;	
		SuppressionSet.IGBT_Temperature_Supress = 0;
	}
	else if(g_Supress_Select_Para == 4)
	{
		SuppressionSet.Current_Sup = 0;
		SuppressionSet.Winding_temperature_Supress = 0;	
		SuppressionSet.IGBT_Temperature_Supress = 1;
	}
	else if(g_Supress_Select_Para == 5)
	{
		SuppressionSet.Current_Sup = 1;
		SuppressionSet.Winding_temperature_Supress = 0;	
		SuppressionSet.IGBT_Temperature_Supress = 1;
	}
	else if(g_Supress_Select_Para == 6)
	{
		SuppressionSet.Current_Sup = 0;
		SuppressionSet.Winding_temperature_Supress = 1;	
		SuppressionSet.IGBT_Temperature_Supress = 1;
	}
	else if(g_Supress_Select_Para == 7)
	{
		SuppressionSet.Current_Sup = 1;
		SuppressionSet.Winding_temperature_Supress = 1;	
		SuppressionSet.IGBT_Temperature_Supress = 1;
	}
	else if(g_Supress_Select_Para == 0)
	{
		SuppressionSet.Current_Sup = 0;
		SuppressionSet.Winding_temperature_Supress = 0;	
		SuppressionSet.IGBT_Temperature_Supress = 0;
	}
}


void Suppression(void)
{
	SuppressionSelection();
	IPMTemperatureDegrating();
}
