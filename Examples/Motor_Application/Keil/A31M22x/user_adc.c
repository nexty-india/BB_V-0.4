#include "user_adc.h"

/**********GLOBLE VARIABLE*****************************/
//uint16_t Analog_input_10Volt;
//uint16_t Analog_input_20Curr;
////int Input_DC_Voltage;
//uint16_t Calcuate_RPM;
//extern Modbus_Parameter modbus_parameter;
//extern uint8_t MOTOR_POT_STATUS,MOTOR_POT_TOGGLE;
/************************************************************/


///**
//	* @brief 	Sensor Voltage (0V - 10V) and Current (4mA - 20mA) using ADC
//	* @param  Recevied ADC Count
//	* @retval ADC Count
//	*/
//void ANALOG_SENSE_0_10_VOLT(void)                     //Sense Analog voltae 0V - 10V.  
//{
//	Analog_input_10Volt = MDL_ADC_OPAMP(2);							//read adc count.
//	Input_DC_Voltage = ( Analog_input_10Volt * 5 )/4096;
//}


//int Calcuate_RPM_0_10_Volt(void)
//{
//	Calcuate_RPM = 0.0588*Analog_input_10Volt+102.71;
//	if(Analog_input_10Volt <= 740)
//	{
//		Calcuate_RPM = 0;
//	}
//	return Calcuate_RPM;
//		//modbus_parameter.MODBUS_TARGET_SPEED = Calcuate_RPM;

//}


//void ANALOG_SENSE_4_20MA(void)												//Sense Current from 4mA - 20mA.
//{
//	Analog_input_20Curr = MDL_ADC_OPAMP(1);							//read adc count.
//}

