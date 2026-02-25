#include "PID_Sensor_Status.h"
#include "Bharat_Bijlee.h"
#include "Application_Holding_Register.h"
#include "MODBUS_Status.h"
#include "AI1_Sensor_Status.h"
/*Globle Variable*/
PID_Sensor_t pid_sensor;
uint8_t g_Pidsensorcounter;
uint16_t g_Analog_input_20Curr;
uint16_t g_Analog_4_20_ma_factor,g_Analog_4_20_ma_filt;
/**/

/**
 * @brief Reads 4–20 mA analog current input.
 *
 * This function senses the current signal in the range of
 * 4 mA to 20 mA by reading the ADC value from OPAMP channel 1.
 *
 * @return int Raw ADC count corresponding to the 4–20 mA input current.
 */
static int ANALOG_SENSE_4_20MA(void)   // Sense current from 4 mA – 20 mA
{
    g_Analog_input_20Curr = MDL_ADC_OPAMP(1);   // Read ADC count from OPAMP channel 1
    return g_Analog_input_20Curr;
}



/**
 * @brief Filtered 4–20 mA analog current sensing.
 *
 * This function applies a simple digital low-pass (IIR) filter
 * to the raw 4–20 mA ADC input to reduce noise.
 *
 * Filter equation:
 *   acc = acc + (raw_value - filtered_value)
 *   filtered_value = acc >> 12
 *
 * The right shift (>> 12) defines the filter strength
 * (larger shift = smoother output, slower response).
 *
 * @return int Filtered ADC value corresponding to 4–20 mA input.
 */
static int ANALOG_SENSE_4_20MA_FILT(void)
{
    // Accumulate difference between raw ADC and filtered value
    g_Analog_4_20_ma_factor = g_Analog_4_20_ma_factor + (ANALOG_SENSE_4_20MA() - g_Analog_4_20_ma_filt);

    // Scale accumulator to get filtered output
    g_Analog_4_20_ma_filt = g_Analog_4_20_ma_factor >> 12;

    return g_Analog_4_20_ma_filt;
}


void PIDinit(void)
{
	pid_sensor.Actual_SensorValue = 50;
	pid_sensor.Control_signalMaxlimit = 20;
	pid_sensor.Control_signalMinlimit = -20;
	pid_sensor.Ki_Constant = 0.01;
	pid_sensor.Kp_Constant = 0.1;
}

uint16_t rpm_ff,Target_PID;
int PidSensorCalculation(void)
{
		uint16_t Kp_temp = 0,Ki_temp = 0;
		uint16_t MaxiSpeed = 0,MinSpeed = 0;
		pid_sensor.TargetSetPoint = MODBUS_HOLDING_REGISTERS[HOLDING_TARGET_SET_POINT].actual_value;
		Kp_temp = MODBUS_HOLDING_REGISTERS[HOLDING_Kp_CONSTANT].actual_value;
		Ki_temp = MODBUS_HOLDING_REGISTERS[HOLDING_ki_CONSTANT].actual_value;
		MaxiSpeed = MODBUS_HOLDING_REGISTERS[HOLDING_MAXIMUM_SPEED].actual_value;
		MinSpeed = MODBUS_HOLDING_REGISTERS[HOLDING_MIN_SPEED].actual_value;
		pid_sensor.Kp_Constant = Kp_temp/100;
		pid_sensor.Ki_Constant=Ki_temp/1000;
		pid_sensor.Actual_SensorValue = modbus_parameter.MODBUS_IPM_TEMPERATURE/100;
		pid_sensor.Error_siganl =pid_sensor.TargetSetPoint - pid_sensor.Actual_SensorValue;
		pid_sensor.Control_signalMinlimit = -20;
		pid_sensor.Control_signalMaxlimit = 20;

    /* Proportional */
    pid_sensor.Proportional_Output = pid_sensor.Kp_Constant * pid_sensor.Error_siganl;

    /* Anti-windup integration */
    if ((pid_sensor.Control_Signal < pid_sensor.Control_signalMaxlimit) &&(pid_sensor.Control_Signal > pid_sensor.Control_signalMinlimit))
    {
        pid_sensor.Integral_Output += pid_sensor.Error_siganl;
    }

    pid_sensor.Integral_Output = pid_sensor.Ki_Constant * pid_sensor.Integral_Output;

    /* PI output */
    pid_sensor.Control_Signal =pid_sensor.Proportional_Output + pid_sensor.Integral_Output;

    /* Clamp control signal */
    if(pid_sensor.Control_Signal > pid_sensor.Control_signalMaxlimit)
        pid_sensor.Control_Signal = pid_sensor.Control_signalMaxlimit;
    else if(pid_sensor.Control_Signal < pid_sensor.Control_signalMinlimit)
        pid_sensor.Control_Signal = pid_sensor.Control_signalMinlimit;

    /* Apply to RPM */
    pid_sensor.Target_Rpm += pid_sensor.Minumumrpm + pid_sensor.Control_Signal;

    /* Clamp RPM */
    if(pid_sensor.Target_Rpm > MaxiSpeed)
        pid_sensor.Target_Rpm = MaxiSpeed;
    else if(pid_sensor.Target_Rpm < MinSpeed)
        pid_sensor.Target_Rpm = MinSpeed;

    return pid_sensor.Target_Rpm;
}


void PID_SENSOR_EVENT_OCCURANCE(void)
{
	
	if(controlmode.PID_FLAG_BIT == 1)
	{
		if(g_Pidsensorcounter++ > G_Counter){
			g_Pidsensorcounter = 0;
			PidSensorCalculation();
		g_target_Speed = pid_sensor.Target_Rpm;
			}
		//g_target_Speed = target_rpm;
	}
	
	
}
