#include "Suppression_Setting.h"

Supression_t SuppressionSet;
Degrating_t degrating;
uint16_t g_Degrating_Target_Rpm;


/**
 * @brief Reads the ambient temperature sensor value.
 *
 * This function reads the ADC value corresponding to the ambient
 * temperature sensor connected via OPAMP channel 3.
 *
 * @return uint16_t Raw ADC value representing ambient temperature.
 */
int AmbientTemperature(void)
{
    uint16_t AmbientTemperaturetemp = 0;

    // Read ADC value from OPAMP channel 3 (Ambient Temperature Sensor)
    AmbientTemperaturetemp = MDL_ADC_OPAMP(3);

    return AmbientTemperaturetemp;
}

/**
 * @brief  IPM temperature based speed degrading logic
 *
 * This function implements motor speed degrading based on
 * IPM (Intelligent Power Module) temperature to protect
 * power electronics from overheating.
 *
 * Degrading behavior:
 * - Speed is linearly reduced between configured temperature limits
 * - Below degrading OFF threshold, full speed is restored
 * - Speed is clamped to minimum allowable speed
 *
 * Speed source:
 * - Modbus target speed in Modbus control mode
 * - Analog input speed in Analog control mode
 *
 * This function should be called periodically.
 */
void IPMTemperatureDegrating(void)
{
	uint16_t IPMTemperatue = 0,TargetRpm = 0;
	IPMTemperatue = modbus_parameter.MODBUS_IPM_TEMPERATURE;
	degrating.IPM_Supp.Ipmt_IpmTemperatureFilt = IPMTemperatue;

	degrating.IPM_Supp.Ipmt_MinSpeed =  MINIMUM_SPEED();
	
	degrating.IPM_Supp.Ipmt_MaxTemperatue = MODBUS_HOLDING_REGISTERS[HOLDING_RANGE_MAX_WINDING_TEMPERATUE].actual_value;
	degrating.IPM_Supp.Ipmt_MinTemperatue = MODBUS_HOLDING_REGISTERS[HOLDING_RANGE_MIN_WINDING_TEMPERATUE].actual_value;
	if(controlmode.MODBUS_FLAG_BIT == 1)
	{ 
		TargetRpm = MODBUS_HOLDING_REGISTERS[HOLDING_TARGET_SPEED_FROM_MODBUS].actual_value;
		degrating.Current_Supp.Id_ActualSpeed = TargetRpm*10;	
	}
	else if(controlmode.ANALOG_FLAG_BIT == 1)
	{
		TargetRpm = g_AI1_Calculated_RPM;
		degrating.Current_Supp.Id_ActualSpeed = TargetRpm;
	}
	degrating.IPM_Supp.Ipmt_Slope = (float)((degrating.IPM_Supp.Ipmt_ActualSpeed - degrating.IPM_Supp.Ipmt_MinSpeed)/(degrating.IPM_Supp.Ipmt_MinTemperatue-degrating.IPM_Supp.Ipmt_MaxTemperatue));
	degrating.IPM_Supp.Ipmt_Intercept = degrating.IPM_Supp.Ipmt_ActualSpeed - (degrating.IPM_Supp.Ipmt_MinTemperatue * degrating.IPM_Supp.Ipmt_Slope);
	degrating.IPM_Supp.Ipmt_Degrating_off = degrating.IPM_Supp.Ipmt_MinTemperatue - 5.00f;
	if(degrating.IPM_Supp.Ipmt_IpmTemperatureFilt > degrating.IPM_Supp.Ipmt_MinTemperatue)
	{
		degrating.IPM_Supp.Ipmt_TaregetSpeed = (uint16_t)((degrating.IPM_Supp.Ipmt_Slope * degrating.IPM_Supp.Ipmt_IpmTemperatureFilt)+degrating.IPM_Supp.Ipmt_Intercept);
	}
	else if(degrating.IPM_Supp.Ipmt_IpmTemperatureFilt < degrating.IPM_Supp.Ipmt_Degrating_off)
	{
		degrating.IPM_Supp.Ipmt_TaregetSpeed = degrating.IPM_Supp.Ipmt_ActualSpeed;
	}
	
	if(degrating.IPM_Supp.Ipmt_TaregetSpeed < degrating.IPM_Supp.Ipmt_MinSpeed)
	{
		degrating.IPM_Supp.Ipmt_TaregetSpeed = 0;
	}
}

/**
 * @brief  Motor winding temperature based speed degrading logic
 *
 * This function reduces motor speed based on winding temperature
 * to protect the motor from thermal damage.
 *
 * Degrading behavior:
 * - Linear speed reduction between configured temperature limits
 * - Full speed restored below degrading OFF threshold (hysteresis)
 * - Output speed clamped to minimum allowable speed
 *
 * Speed source:
 * - Modbus target speed in Modbus control mode
 * - Analog input speed in Analog control mode
 *
 * This function should be executed periodically.
 */
void WindingTemperatureDegrating(void)
{
	uint16_t WindTemperatue = 0,TargetRpm = 0;
	WindTemperatue = modbus_parameter.MODBUS_MOTOR_TEMPERATURE;
	degrating.Winding_Supp.Wt_WindingTemperatueFilt = WindTemperatue;

	degrating.Winding_Supp.Wt_MinSpeed =  MINIMUM_SPEED();
	
	degrating.Winding_Supp.Wt_MaxTemperatue = MODBUS_HOLDING_REGISTERS[HOLDING_RANGE_MAX_WINDING_TEMPERATUE].actual_value;
	degrating.Winding_Supp.Wt_MinTemperatue = MODBUS_HOLDING_REGISTERS[HOLDING_RANGE_MIN_WINDING_TEMPERATUE].actual_value;
	if(controlmode.MODBUS_FLAG_BIT == 1)
	{ 
		TargetRpm = MODBUS_HOLDING_REGISTERS[HOLDING_TARGET_SPEED_FROM_MODBUS].actual_value;
		degrating.Current_Supp.Id_ActualSpeed = TargetRpm*10;	
	}
	else if(controlmode.ANALOG_FLAG_BIT == 1)
	{
		TargetRpm = g_AI1_Calculated_RPM;
		degrating.Current_Supp.Id_ActualSpeed = TargetRpm;
	}
	degrating.Winding_Supp.Wt_Slope = (float)((degrating.Winding_Supp.Wt_ActualSpeed - degrating.Winding_Supp.Wt_MinSpeed)/(degrating.Winding_Supp.Wt_MinTemperatue-degrating.Winding_Supp.Wt_MaxTemperatue));
	degrating.Winding_Supp.Wt_Intercept = degrating.Winding_Supp.Wt_ActualSpeed - (degrating.Winding_Supp.Wt_MinTemperatue * degrating.Winding_Supp.Wt_Slope);
	degrating.Winding_Supp.Wt_Degrating_off = degrating.Winding_Supp.Wt_MinTemperatue - 5.00f;
	if(degrating.Winding_Supp.Wt_WindingTemperatueFilt > degrating.Winding_Supp.Wt_MinTemperatue)
	{
		degrating.Winding_Supp.Wt_TaregetSpeed = (uint16_t)((degrating.Winding_Supp.Wt_Slope * degrating.Winding_Supp.Wt_WindingTemperatueFilt)+degrating.Winding_Supp.Wt_Intercept);
	}
	else if(degrating.Winding_Supp.Wt_WindingTemperatueFilt < degrating.Winding_Supp.Wt_Degrating_off)
	{
		degrating.Winding_Supp.Wt_TaregetSpeed = degrating.Winding_Supp.Wt_ActualSpeed;
	}
	
	if(degrating.Winding_Supp.Wt_TaregetSpeed < degrating.Winding_Supp.Wt_MinSpeed)
	{
		degrating.Winding_Supp.Wt_TaregetSpeed = 0;
	}
	
}

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

void VoltageDegrating(void)
{
	uint16_t Voltage_ac = 0,TargetRPM = 0;
	Voltage_ac = DC_Filter();
	degrating.voltage_Supp.Vd_VoltageFilt = Voltage_ac/10;

	degrating.voltage_Supp.vd_MinSpeed =  MINIMUM_SPEED();
	if(controlmode.MODBUS_FLAG_BIT == 1)
	{ 
		TargetRPM = MODBUS_HOLDING_REGISTERS[HOLDING_TARGET_SPEED_FROM_MODBUS].actual_value;
		degrating.Current_Supp.Id_ActualSpeed = TargetRPM*10;	
	}
	else if(controlmode.ANALOG_FLAG_BIT == 1)
	{
		TargetRPM = g_AI1_Calculated_RPM;
		degrating.Current_Supp.Id_ActualSpeed = TargetRPM;
	}
	
	degrating.voltage_Supp.vd_MaxVoltage = MODBUS_HOLDING_REGISTERS[HOLDING_RANGE_MAX_VOLTAGE].actual_value;
	degrating.voltage_Supp.vd_MinVoltage = MODBUS_HOLDING_REGISTERS[HOLDING_RANGE_MIN_VOLTAGE].actual_value;
	degrating.voltage_Supp.vd_DegratingStart = degrating.voltage_Supp.vd_MinVoltage - 10;
	degrating.voltage_Supp.vd_Slope = (float)((degrating.voltage_Supp.vd_ActualSpeed  - degrating.voltage_Supp.vd_MinSpeed)/(degrating.voltage_Supp.vd_MinVoltage-degrating.voltage_Supp.vd_MaxVoltage));
	degrating.voltage_Supp.vd_intercept = degrating.voltage_Supp.vd_ActualSpeed  - (degrating.voltage_Supp.vd_DegratingStart * degrating.voltage_Supp.vd_Slope);
  
	if(SuppressionSet.Voltage_Supress == 1){
		if(degrating.voltage_Supp.Vd_VoltageFilt > degrating.voltage_Supp.vd_MinVoltage)
		{
			degrating.voltage_Supp.vd_TargetSpeed = (uint16_t)((degrating.voltage_Supp.vd_Slope * degrating.voltage_Supp.Vd_VoltageFilt)+degrating.voltage_Supp.vd_intercept);
		}
		else if(degrating.voltage_Supp.Vd_VoltageFilt < degrating.voltage_Supp.vd_DegratingStart)
		{
			degrating.voltage_Supp.vd_TargetSpeed = degrating.voltage_Supp.vd_ActualSpeed  ;
		}
		
		if(degrating.voltage_Supp.vd_TargetSpeed < degrating.voltage_Supp.vd_MinSpeed)
		{
			degrating.voltage_Supp.vd_TargetSpeed = 0;
		}
	}
}



void LowerVoltageDegrating(void)
{
	uint16_t Voltage_ac = 0,TargetRPM = 0;
	Voltage_ac = DC_Filter();
	degrating.lowvoltage_Supp.LVd_VoltageFilt = Voltage_ac/10;

	degrating.lowvoltage_Supp.Lvd_MinSpeed =  MINIMUM_SPEED();
	if(controlmode.MODBUS_FLAG_BIT == 1)
	{ 
		TargetRPM = MODBUS_HOLDING_REGISTERS[HOLDING_TARGET_SPEED_FROM_MODBUS].actual_value;
		degrating.lowvoltage_Supp.Lvd_ActualSpeed = TargetRPM*10;	
	}
	else if(controlmode.ANALOG_FLAG_BIT == 1)
	{
		TargetRPM = g_AI1_Calculated_RPM;
		degrating.lowvoltage_Supp.Lvd_ActualSpeed = TargetRPM;
	}
	
	degrating.lowvoltage_Supp.Lvd_MaxVoltage = MODBUS_HOLDING_REGISTERS[HOLDING_RANGE_MAX_VOLTAGE].actual_value;
	degrating.lowvoltage_Supp.Lvd_MinSpeed = MODBUS_HOLDING_REGISTERS[HOLDING_RANGE_MIN_VOLTAGE].actual_value;
	degrating.lowvoltage_Supp.Lvd_DegratingStart = degrating.lowvoltage_Supp.Lvd_MinVoltage + 10;
	degrating.lowvoltage_Supp.Lvd_Slope = (float)((degrating.lowvoltage_Supp.Lvd_ActualSpeed  - degrating.lowvoltage_Supp.Lvd_MinSpeed)/(degrating.lowvoltage_Supp.Lvd_MinVoltage-degrating.lowvoltage_Supp.Lvd_MaxVoltage));
	degrating.lowvoltage_Supp.Lvd_intercept = degrating.lowvoltage_Supp.Lvd_ActualSpeed  - (degrating.lowvoltage_Supp.Lvd_DegratingStart * degrating.lowvoltage_Supp.Lvd_Slope);
  
	if(SuppressionSet.Lower_voltage_Supress == 1){
		if(degrating.lowvoltage_Supp.LVd_VoltageFilt > degrating.lowvoltage_Supp.Lvd_MinVoltage)
		{
			degrating.lowvoltage_Supp.Lvd_TargetSpeed = (uint16_t)((degrating.lowvoltage_Supp.Lvd_Slope * degrating.lowvoltage_Supp.LVd_VoltageFilt)+degrating.lowvoltage_Supp.Lvd_intercept);
		}
		else if(degrating.lowvoltage_Supp.LVd_VoltageFilt < degrating.lowvoltage_Supp.Lvd_DegratingStart)
		{
			degrating.lowvoltage_Supp.Lvd_TargetSpeed = degrating.lowvoltage_Supp.Lvd_ActualSpeed  ;
		}
		
		if(degrating.lowvoltage_Supp.Lvd_TargetSpeed < degrating.lowvoltage_Supp.Lvd_MinSpeed)
		{
			degrating.lowvoltage_Supp.Lvd_TargetSpeed = 0;
		}
	}
}




/**
*@breif Current Degrating 
*/
void CurrentDegrating(void)
{
  uint16_t motorcurrent = 0,TargetRpm = 0;
	motorcurrent = modbus_parameter.MODBUS_READ_DC_CURRENT;
	degrating.Current_Supp.Id_CurrentFilt = motorcurrent/1000;
  degrating.Current_Supp.Id_MinSpeed = MINIMUM_SPEED();

	degrating.Current_Supp.Id_MaxCurrent = MODBUS_HOLDING_REGISTERS[HOLDING_RANGE_MAX_MOTOR_CURRENT].actual_value;
	degrating.Current_Supp.Id_MinCurrent = MODBUS_HOLDING_REGISTERS[HOLDING_RANGE_MIN_MOTOR_CURRENT].actual_value;
	if(controlmode.MODBUS_FLAG_BIT == 1)
	{ 
		TargetRpm = MODBUS_HOLDING_REGISTERS[HOLDING_TARGET_SPEED_FROM_MODBUS].actual_value;
		degrating.Current_Supp.Id_ActualSpeed = TargetRpm*10;	
	}
	else if(controlmode.ANALOG_FLAG_BIT == 1)
	{
		TargetRpm = g_AI1_Calculated_RPM;
		degrating.Current_Supp.Id_ActualSpeed = TargetRpm;
	}
	
  degrating.Current_Supp.Id_Slope = (float)((degrating.Current_Supp.Id_ActualSpeed - degrating.Current_Supp.Id_MinSpeed)/(degrating.Current_Supp.Id_MinCurrent-degrating.Current_Supp.Id_MaxCurrent));
	degrating.Current_Supp.Id_intercept = degrating.Current_Supp.Id_ActualSpeed- (degrating.Current_Supp.Id_MinCurrent * degrating.Current_Supp.Id_Slope);
  degrating.Current_Supp.Id_Degratingoff = degrating.Current_Supp.Id_MinCurrent - 2.0f;
	
	if(SuppressionSet.Motor_Current_Supress == 1){
	if(degrating.Current_Supp.Id_CurrentFilt > degrating.Current_Supp.Id_MinCurrent)
	{
		degrating.Current_Supp.Id_TargetSpeed = (uint16_t)((degrating.Current_Supp.Id_Slope * degrating.Current_Supp.Id_CurrentFilt)+degrating.Current_Supp.Id_intercept);
	}
	else if(degrating.Current_Supp.Id_CurrentFilt < degrating.Current_Supp.Id_Degratingoff)
	{
		degrating.Current_Supp.Id_TargetSpeed = degrating.Current_Supp.Id_ActualSpeed ;
	}
	
	if(degrating.Current_Supp.Id_TargetSpeed <  degrating.Current_Supp.Id_MinSpeed)
	{
		degrating.Current_Supp.Id_TargetSpeed = 0;
	}
 }
}

void OverPowerDegrating(void)
{
	uint16_t OverPower = 0,TargetRPM = 0;
	OverPower = g_Power_Filt;
	degrating.OvPwr_Supp.OP_OverPowerFilt = OverPower;

	degrating.OvPwr_Supp.OP_MinSpeed =  MINIMUM_SPEED();
	if(controlmode.MODBUS_FLAG_BIT == 1)
	{ 
		TargetRPM = MODBUS_HOLDING_REGISTERS[HOLDING_TARGET_SPEED_FROM_MODBUS].actual_value;
		degrating.OvPwr_Supp.OP_ActualSpeed = TargetRPM*10;	
	}
	else if(controlmode.ANALOG_FLAG_BIT == 1)
	{
		TargetRPM = g_AI1_Calculated_RPM;
		degrating.OvPwr_Supp.OP_ActualSpeed = TargetRPM;
	}
	
	degrating.OvPwr_Supp.OP_MaxOverPower = MODBUS_HOLDING_REGISTERS[HOLDING_RANGE_MAX_VOLTAGE].actual_value;
	degrating.OvPwr_Supp.OP_MinOverPower = MODBUS_HOLDING_REGISTERS[HOLDING_RANGE_MIN_VOLTAGE].actual_value;
	degrating.OvPwr_Supp.OP_Degratingoff = degrating.OvPwr_Supp.OP_MinOverPower - 10;
	degrating.OvPwr_Supp.OP_OverPowerFilt = (float)((degrating.OvPwr_Supp.OP_ActualSpeed  - degrating.OvPwr_Supp.OP_MinSpeed)/(degrating.OvPwr_Supp.OP_MinOverPower-degrating.OvPwr_Supp.OP_MaxOverPower));
	degrating.OvPwr_Supp.OP_Intercept = degrating.OvPwr_Supp.OP_ActualSpeed  - (degrating.OvPwr_Supp.OP_Degratingoff * degrating.OvPwr_Supp.OP_Slope);
  
	if(SuppressionSet.Voltage_Supress == 1){
		if(degrating.OvPwr_Supp.OP_OverPowerFilt > degrating.OvPwr_Supp.OP_MinOverPower)
		{
			degrating.OvPwr_Supp.OP_TargetSpeed = (uint16_t)((degrating.OvPwr_Supp.OP_Slope * degrating.OvPwr_Supp.OP_OverPowerFilt)+degrating.OvPwr_Supp.OP_Intercept);
		}
		else if(degrating.OvPwr_Supp.OP_OverPowerFilt < degrating.OvPwr_Supp.OP_Degratingoff)
		{
			degrating.OvPwr_Supp.OP_TargetSpeed = degrating.OvPwr_Supp.OP_ActualSpeed  ;
		}
		
		if(degrating.OvPwr_Supp.OP_TargetSpeed < degrating.OvPwr_Supp.OP_MinSpeed)
		{
			degrating.OvPwr_Supp.OP_TargetSpeed = 0;
		}
	}
}


void UpperAmbientTemperatureDegrating(void)
{
	uint16_t Ambient_Temperature = 0,TargetRPM = 0;
	Ambient_Temperature = DC_Filter();            //Assign the actual filter value of ambient Temperature;
	degrating.UAmTemp_Supp.UATMP_AmbientTempFilt = Ambient_Temperature/10;

	degrating.UAmTemp_Supp.UATMP_MinSpeed =  MINIMUM_SPEED();
	if(controlmode.MODBUS_FLAG_BIT == 1)
	{ 
		TargetRPM = MODBUS_HOLDING_REGISTERS[HOLDING_TARGET_SPEED_FROM_MODBUS].actual_value;
		degrating.UAmTemp_Supp.UATMP_ActualSpeed = TargetRPM*10;	
	}
	else if(controlmode.ANALOG_FLAG_BIT == 1)
	{
		TargetRPM = g_AI1_Calculated_RPM;
		degrating.UAmTemp_Supp.UATMP_ActualSpeed = TargetRPM;
	}
	
	degrating.UAmTemp_Supp.UATMP_MaxAmbientTemp = MODBUS_HOLDING_REGISTERS[HOLDING_RANGE_MAX_VOLTAGE].actual_value;
	degrating.UAmTemp_Supp.UATMP_MinAmbientTemp = MODBUS_HOLDING_REGISTERS[HOLDING_RANGE_MIN_VOLTAGE].actual_value;
	degrating.UAmTemp_Supp.UATMP_Degratingoff = degrating.UAmTemp_Supp.UATMP_MinAmbientTemp - 10;
	degrating.UAmTemp_Supp.UATMP_Slope = (float)((degrating.UAmTemp_Supp.UATMP_ActualSpeed  - degrating.UAmTemp_Supp.UATMP_MinSpeed)/(degrating.UAmTemp_Supp.UATMP_MinAmbientTemp-degrating.UAmTemp_Supp.UATMP_MaxAmbientTemp));
	degrating.UAmTemp_Supp.UATMP_Intercept = degrating.UAmTemp_Supp.UATMP_ActualSpeed  - (degrating.UAmTemp_Supp.UATMP_Degratingoff * degrating.UAmTemp_Supp.UATMP_Slope);
  
	if(SuppressionSet.Voltage_Supress == 1){
		if(degrating.UAmTemp_Supp.UATMP_AmbientTempFilt > degrating.UAmTemp_Supp.UATMP_MaxAmbientTemp)
		{
			degrating.UAmTemp_Supp.UATMP_TargetSpeed = (uint16_t)((degrating.UAmTemp_Supp.UATMP_Slope * degrating.UAmTemp_Supp.UATMP_AmbientTempFilt)+degrating.UAmTemp_Supp.UATMP_Intercept);
		}
		else if(degrating.UAmTemp_Supp.UATMP_AmbientTempFilt < degrating.UAmTemp_Supp.UATMP_Degratingoff)
		{
			degrating.UAmTemp_Supp.UATMP_TargetSpeed = degrating.UAmTemp_Supp.UATMP_ActualSpeed  ;
		}
		
		if(degrating.UAmTemp_Supp.UATMP_TargetSpeed < degrating.UAmTemp_Supp.UATMP_MinSpeed)
		{
			degrating.UAmTemp_Supp.UATMP_TargetSpeed = 0;
		}
	}
}


void LowerAmbientTemperatureDegrating(void)
{
	uint16_t Ambient_Temperature = 0,TargetRPM = 0;
	Ambient_Temperature = DC_Filter();            //Assign the actual filter value of ambient Temperature;
	degrating.LAmTemp_Supp.LATMP_AmbientTempFilt = Ambient_Temperature/10;

	degrating.LAmTemp_Supp.LATMP_MinSpeed =  MINIMUM_SPEED();
	if(controlmode.MODBUS_FLAG_BIT == 1)
	{ 
		TargetRPM = MODBUS_HOLDING_REGISTERS[HOLDING_TARGET_SPEED_FROM_MODBUS].actual_value;
		degrating.LAmTemp_Supp.LATMP_ActualSpeed = TargetRPM*10;	
	}
	else if(controlmode.ANALOG_FLAG_BIT == 1)
	{
		TargetRPM = g_AI1_Calculated_RPM;
		degrating.LAmTemp_Supp.LATMP_ActualSpeed = TargetRPM;
	}
	
	degrating.LAmTemp_Supp.LATMP_MaxAmbientTemp = MODBUS_HOLDING_REGISTERS[HOLDING_RANGE_MAX_VOLTAGE].actual_value;
	degrating.LAmTemp_Supp.LATMP_MinAmbientTemp = MODBUS_HOLDING_REGISTERS[HOLDING_RANGE_MIN_VOLTAGE].actual_value;
	degrating.LAmTemp_Supp.LATMP_Degratingoff = degrating.LAmTemp_Supp.LATMP_MinAmbientTemp - 10;
	degrating.LAmTemp_Supp.LATMP_Slope = (float)((degrating.LAmTemp_Supp.LATMP_ActualSpeed  - degrating.LAmTemp_Supp.LATMP_MinSpeed)/(degrating.LAmTemp_Supp.LATMP_MinAmbientTemp-degrating.LAmTemp_Supp.LATMP_MaxAmbientTemp));
	degrating.LAmTemp_Supp.LATMP_Intercept = degrating.LAmTemp_Supp.LATMP_ActualSpeed  - (degrating.LAmTemp_Supp.LATMP_Degratingoff * degrating.LAmTemp_Supp.LATMP_Slope);
  
	if(SuppressionSet.Voltage_Supress == 1){
		if(degrating.LAmTemp_Supp.LATMP_AmbientTempFilt > degrating.LAmTemp_Supp.LATMP_AmbientTempFilt)
		{
			degrating.LAmTemp_Supp.LATMP_TargetSpeed = (uint16_t)((degrating.LAmTemp_Supp.LATMP_Slope * degrating.LAmTemp_Supp.LATMP_AmbientTempFilt)+degrating.LAmTemp_Supp.LATMP_Intercept);
		}
		else if(degrating.LAmTemp_Supp.LATMP_AmbientTempFilt < degrating.LAmTemp_Supp.LATMP_Degratingoff)
		{
			degrating.LAmTemp_Supp.LATMP_TargetSpeed = degrating.LAmTemp_Supp.LATMP_ActualSpeed  ;
		}
		
		if(degrating.LAmTemp_Supp.LATMP_TargetSpeed < degrating.LAmTemp_Supp.LATMP_MinSpeed)
		{
			degrating.LAmTemp_Supp.LATMP_TargetSpeed = 0;
		}
	}
}


void SuppressionSelection(void)
{
	
	uint16_t g_Supress_Select_Para = 0;
	g_Supress_Select_Para = MODBUS_HOLDING_REGISTERS[HOLDING_SUPPRESSION_RANGE_SETTING].actual_value;
	g_Degrating_Target_Rpm = g_target_Speed;
	
	for(int i=0;i<16;i++)
	{
		if(g_Supress_Select_Para & 1)    //Current Degrating
		{
			SuppressionSet.Motor_Current_Supress = 1;
			g_Degrating_Target_Rpm = (g_Degrating_Target_Rpm < degrating.Current_Supp.Id_TargetSpeed) ? g_Degrating_Target_Rpm: degrating.Current_Supp.Id_TargetSpeed;
		}
		else{
			SuppressionSet.Motor_Current_Supress = 0;
			degrating.Current_Supp.Id_TargetSpeed = g_target_Speed;
		}
		
		if(g_Supress_Select_Para & 2)   //Voltage Degrating
		{
			SuppressionSet.Voltage_Supress = 1;
			g_Degrating_Target_Rpm = (g_Degrating_Target_Rpm <degrating.voltage_Supp.vd_TargetSpeed) ? g_Degrating_Target_Rpm : degrating.voltage_Supp.vd_TargetSpeed;
		}
		else{
			SuppressionSet.Voltage_Supress = 0;
			degrating.voltage_Supp.vd_TargetSpeed = g_target_Speed;
		}
		 
		if(g_Supress_Select_Para & 4)   //Winding Temperature Degrating
		{
			SuppressionSet.Winding_temperature_Supress = 1;
			g_Degrating_Target_Rpm = (g_Degrating_Target_Rpm <degrating.Winding_Supp.Wt_TaregetSpeed) ? g_Degrating_Target_Rpm: degrating.Winding_Supp.Wt_TaregetSpeed;
		}else
		{
			SuppressionSet.Winding_temperature_Supress = 0;
			degrating.Winding_Supp.Wt_TaregetSpeed = g_target_Speed;
		}
		
		
		if(g_Supress_Select_Para & 8)   //IGBT Temperature Degrating
		{
			SuppressionSet.IGBT_Temperature_Supress = 1;
			g_Degrating_Target_Rpm = (g_Degrating_Target_Rpm <degrating.IPM_Supp.Ipmt_TaregetSpeed) ? g_Degrating_Target_Rpm: degrating.IPM_Supp.Ipmt_TaregetSpeed;
		}
		else{
			SuppressionSet.IGBT_Temperature_Supress = 0;
			degrating.IPM_Supp.Ipmt_TaregetSpeed = g_target_Speed;
		}
		
		
		if(g_Supress_Select_Para & 16)   //Lower Voltage
		{
			SuppressionSet.LowerVoltage_Supress = 1;
			g_Degrating_Target_Rpm = (g_Degrating_Target_Rpm <degrating.lowvoltage_Supp.Lvd_TargetSpeed) ? g_Degrating_Target_Rpm: degrating.lowvoltage_Supp.Lvd_TargetSpeed;
		}
		else{
			SuppressionSet.LowerVoltage_Supress = 0;
			degrating.lowvoltage_Supp.Lvd_TargetSpeed = g_target_Speed;
		}
		
		
		if(g_Supress_Select_Para & 32)   //Overpower Degrating
		{
			SuppressionSet.OverPower_Supress = 1;
			g_Degrating_Target_Rpm = (g_Degrating_Target_Rpm <degrating.OvPwr_Supp.OP_TargetSpeed) ? g_Degrating_Target_Rpm: degrating.OvPwr_Supp.OP_TargetSpeed;
		}
		else{
			SuppressionSet.OverPower_Supress = 0;
			degrating.OvPwr_Supp.OP_TargetSpeed = g_target_Speed;
		}
		
		
		if(g_Supress_Select_Para & 64)   //Ambient Upper Side
		{
			SuppressionSet.UpperAmbientTemperature_Supres = 1;
			g_Degrating_Target_Rpm = (g_Degrating_Target_Rpm <degrating.UAmTemp_Supp.UATMP_TargetSpeed) ? g_Degrating_Target_Rpm: degrating.UAmTemp_Supp.UATMP_TargetSpeed;
		}
		else{
			SuppressionSet.UpperAmbientTemperature_Supres = 0;
			degrating.UAmTemp_Supp.UATMP_TargetSpeed = g_target_Speed;
		}
		
		
		if(g_Supress_Select_Para & 128)   //Ambient Lower Side
		{
			SuppressionSet.LowerAmbientTemperature_Supres = 1;
			g_Degrating_Target_Rpm = (g_Degrating_Target_Rpm <degrating.LAmTemp_Supp.LATMP_TargetSpeed) ? g_Degrating_Target_Rpm: degrating.LAmTemp_Supp.LATMP_TargetSpeed;
		}
		else{
			SuppressionSet.LowerAmbientTemperature_Supres = 0;
			degrating.LAmTemp_Supp.LATMP_TargetSpeed = g_target_Speed;
		}
		
	}	
	 g_target_Speed=g_Degrating_Target_Rpm;
}


void Suppression(void)
{
	SuppressionSelection();
	CurrentDegrating();
	VoltageDegrating();
	WindingTemperatureDegrating();
	IPMTemperatureDegrating();
	LowerAmbientTemperatureDegrating();
	UpperAmbientTemperatureDegrating();
	LowerVoltageDegrating();
	OverPowerDegrating();
}