#include "AI1_Sensor_Status.h"
#include "Bharat_Bijlee.h"
#include "MODBUS_Status.h"
#include "Application_Holding_Register.h"
/**********GLOBLE VARIABLE*****************************/
uint16_t g_Analog_input_10Volt;
extern MODBUS_REGISTER_t Modbus_Register;
extern Modbus_Parameter modbus_parameter;
static uint32_t g_Temp_Pot_volt_factor=0;
uint16_t g_Pot_voltage_filt;
uint16_t g_AI1_Volts_Value = 0;
uint16_t g_Pot_voltage_filt_Percentage = 0;
uint16_t g_Fail_safe_status = 0;
/*******************************************************/

	
/**
	* @brief 	Sensor Voltage (0V - 10V) 
	* @param  Recevied ADC Count
	* @retval ADC Count
	*/
static int ANALOG_SENSE_0_10_VOLT_RAW(void)                     //Sense Analog voltae 0V - 10V.  
{
	g_Analog_input_10Volt = MDL_ADC_OPAMP(2);							//read adc count.
	return g_Analog_input_10Volt;
}


/**
 * @brief  Filters 0–10V analog input using a simple IIR low-pass filter
 *         and converts ADC value to voltage and percentage.
 *
 * @return Filtered ADC value
 */
static int ANALOG_SENSE_0_10_VOLT_FILT(void)
{
    /* Accumulate the difference between raw ADC input and filtered value
       to implement a low-pass (IIR) filter */
    g_Temp_Pot_volt_factor =g_Temp_Pot_volt_factor + (ANALOG_SENSE_0_10_VOLT_RAW() - g_Pot_voltage_filt);

    /* Apply scaling (right shift) to obtain filtered ADC value
       ADC_LPF_FILTER_FACTOR defines filter strength */
    g_Pot_voltage_filt = g_Temp_Pot_volt_factor >> ADC_LPF_FILTER_FACTOR;

    /* Convert filtered ADC count to actual voltage (0–10V range) */
    g_AI1_Volts_Value =(g_Pot_voltage_filt * V_BASE) / TOTAL_ADC_COUNT;

    /* Convert filtered ADC count to percentage (0–100%) */
    g_Pot_voltage_filt_Percentage =(g_Pot_voltage_filt * 100) / TOTAL_ADC_COUNT;

    /* Return filtered ADC value */
    return g_Pot_voltage_filt;
}


/**
 * @brief  Converts measured AI1 voltage to actual 0–10V input level
 *         by compensating external resistor divider.
 *
 * @return Calculated 0–10V scaled voltage value
 */
int Volts_10(void)
{
    uint16_t Volts_10_value = 0;

    /* Scale the measured voltage using resistor divider ratio
       V_actual = V_measured × (R_IN + R_OUT) / R_OUT */
    Volts_10_value =(g_AI1_Volts_Value * (R_IN + R_OUT)) / R_OUT;

    /* Return compensated 0–10V voltage value */
    return Volts_10_value;
}



float g_SLOPE=0,g_INTERCEPT=0;
int g_AI1_Calculated_RPM_Temp = 0;
uint16_t g_AI1_MIN_temp=0,g_AI1_MAX_temp=0,g_AI1_Calculated_RPM = 0;
uint16_t g_AI1_MIN_SPEED = 0;
uint16_t g_AI1_MAX_SPEED=0;
uint16_t g_analog_temp = 0;
uint16_t g_AI1_MIN_temp_percent = 0,g_AI1_MAX_temp_percent = 0;
uint16_t g_Ai1MinimumRunningSpeed = 0;
/**
Purpose :- ANALOG_CONTORL_MODE is caculate RPM according to ADC count and Lower and Upper RPM....
*/
void ANALOG_CONTROL_MODE(void)
{
    uint16_t Min_Run_RPM = 0;

    g_analog_temp = ANALOG_SENSE_0_10_VOLT_FILT();

    /* ---------- AI1 Min / Max ADC ---------- */
    g_AI1_MIN_temp_percent = MODBUS_HOLDING_REGISTERS[HOLDING_AI1_MINIMUM_VALUE].actual_value * 10;
    g_AI1_MIN_temp =(g_AI1_MIN_temp_percent * TOTAL_ADC_COUNT) / 100;
    g_AI1_MAX_temp_percent = MODBUS_HOLDING_REGISTERS[HOLDING_AI1_MAXIMUM_VALUE].actual_value * 10;
    g_AI1_MAX_temp =(g_AI1_MAX_temp_percent * TOTAL_ADC_COUNT) / 100;
    g_AI1_MIN_SPEED = MODBUS_HOLDING_REGISTERS[HOLDING_MIN_SPEED].actual_value;
    g_AI1_MAX_SPEED = MODBUS_HOLDING_REGISTERS[HOLDING_MAXIMUM_SPEED].actual_value;

    /* ---------- Min Running Speed ---------- */
		Min_Run_RPM = (g_AI1_MIN_SPEED < g_Ai1MinimumRunningSpeed) ? g_Ai1MinimumRunningSpeed : g_AI1_MIN_SPEED;

    /* ---------- Protect slope ---------- */
    if (g_AI1_MAX_temp <= g_AI1_MIN_temp)
        return;

    /* ---------- Slope and intercept and RPM Calculation ---------- */
    g_SLOPE =((float)(g_AI1_MAX_SPEED - Min_Run_RPM)) /((float)(g_AI1_MAX_temp - g_AI1_MIN_temp));

    g_INTERCEPT = g_AI1_MAX_SPEED - (g_SLOPE * g_AI1_MAX_temp);

    g_AI1_Calculated_RPM_Temp = (g_SLOPE * g_analog_temp) + g_INTERCEPT;


    /* ---------- Final Decision ---------- */
    if (g_analog_temp < g_AI1_MIN_temp)
    {
        /* Below AI1 minimum input */
        g_AI1_Calculated_RPM = Min_Run_RPM;
    }
    else if (g_analog_temp > g_AI1_MAX_temp_percent)
    {
        g_AI1_Calculated_RPM = g_AI1_MAX_SPEED;
    }
    else 
    {
        g_AI1_Calculated_RPM = g_AI1_Calculated_RPM_Temp;
        SYSTEM_DRIVE_EVENT.DRIVE_STATUS.ADC_AI1_EVENT_FLAG = 1;
    }

    g_Fail_safe_status = MODBUS_HOLDING_REGISTERS[HOLDING_FAIL_SAFE_ON_OFF].actual_value;
}




/**
 * @brief  Enables RPM control using analog input (AI1).
 *         Selects normal or fail-safe RPM based on system status.
 */
uint16_t AI1_Target_rpm = 0;
void ANALOG_CONTORL_RPM_ENABLE(void)   
{
 uint16_t Fan_direction = 0,Target_Speed_Set = 0;
	Fan_direction = FAN_ROTATION();
	if((SYSTEM_DRIVE_EVENT.DRIVE_STATUS.ADC_AI1_EVENT_FLAG == 1)||(controlmode.ANALOG_FLAG_BIT == 1))    /* Check if analog control mode or ADC AI1 event is active */
	{
		if(g_Fail_safe_status == 1)/* If fail-safe condition is active, override target speed */
		{
		Target_Speed_Set	= FailSafeControl();
		}
		else{
			Target_Speed_Set = g_AI1_Calculated_RPM;    /* Normal operation: use RPM calculated from AI1 */
		}
	}
	
	if(Fan_direction == 1)
	{
		Target_Speed_Set |= 0x8000;
	}
	
	g_target_Speed = Target_Speed_Set;
	
}




