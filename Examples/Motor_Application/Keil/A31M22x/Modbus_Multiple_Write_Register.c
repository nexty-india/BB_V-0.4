#include "Modbus_Multiple_Write_Register.h"
#include "Bharat_Bijlee.h"
////#include "HOLDING_AND_INPUT_REGISTER.h"
//MULTIPLE_WRITE_TX_DATA Multiple_Write_tx_data;
//extern HOLDING_PARAMETER_t Holding_Register_Parameter;

//extern uint16_t UART_RX_SIZE;
//uint16_t CALCULATE_CRC_LENGTH;
//extern MODBUS_REGISTER_t Modbus_Register;
//extern uint16_t INDEX_RXN,NEXT_RXN,TX_DATA_SIZE,delay_check;


//bool MULTIPLE_SINGLE_WRITE_REGISTER(void)
//{
//	uint16_t Address_start = 0, Quantity_Register = 0;
//	uint8_t Crc_1 = 0, Crc_2 = 0, Byte_Count = 0,Data_Size = 0;
//	uint16_t CALCULATED_CRC = 0,Transmit_Mul_CRC = 0,Received_single_CRC=0;
//	uint16_t Slave_ID = 0,Function_Code = 0;
//	
//	Slave_ID = Modbus_Decode_Data.Slave_ID;
//	Function_Code = Modbus_Decode_Data.Function_Code;
//	Address_start = Modbus_Decode_Data.START_ADDRESS_RECEIVED;
//	Quantity_Register = Modbus_Decode_Data.QUANTITY_REGISTR_RECEIVED;
//	Byte_Count = Quantity_Register * 2;
//	
//	if((Slave_ID == SLAVE_ID)&&(Function_Code = WRITE_MULTIPLE_REGISTER))
//	{
//		data_logger.TRANSMISSION_BUFFER[0] = Slave_ID;
//		data_logger.TRANSMISSION_BUFFER[1] = Function_Code;
//		data_logger.TRANSMISSION_BUFFER[2] = Address_start>>8;
//		data_logger.TRANSMISSION_BUFFER[3] = Address_start&0xFF;
//		data_logger.TRANSMISSION_BUFFER[4] = Quantity_Register>>8;
//		data_logger.TRANSMISSION_BUFFER[5] = Quantity_Register&0xFF;
//		Transmit_Mul_CRC = Modbus_CRC16((uint8_t *)data_logger.TRANSMISSION_BUFFER,6);
//		Crc_1 = Transmit_Mul_CRC & 0xFF;
//		Crc_2 = Transmit_Mul_CRC >> 8;
//		data_logger.TRANSMISSION_BUFFER[6] = Crc_1;
//		data_logger.TRANSMISSION_BUFFER[7] = Crc_2;
//		TX_DATA_LEN = 8;
//	}
//	
//	
//	if(Function_Code == WRITE_SINGLE_REGISTER)
//	{ 
//		data_logger.TRANSMISSION_BUFFER[0] = Slave_ID;
//		data_logger.TRANSMISSION_BUFFER[1] = Function_Code;
//		data_logger.TRANSMISSION_BUFFER[2] = Address_start>>8;
//		data_logger.TRANSMISSION_BUFFER[3] = Address_start&0xFF;
//		data_logger.TRANSMISSION_BUFFER[4] = MODBUS_HOLDING_REGISTERS[5].actual_value>>8;						
//		data_logger.TRANSMISSION_BUFFER[5] = MODBUS_HOLDING_REGISTERS[4].actual_value&0xFF;
//		Transmit_Mul_CRC = Modbus_CRC16((uint8_t *)data_logger.TRANSMISSION_BUFFER,6);
//		Crc_1 = Transmit_Mul_CRC & 0xFF;
//		Crc_1 = Transmit_Mul_CRC >> 8;
//		data_logger.TRANSMISSION_BUFFER[6] = Crc_1;
//		data_logger.TRANSMISSION_BUFFER[7] = Crc_1;
//		TX_DATA_LEN = 8;

//		return 1;
//	}
//	
//}




bool MODBUS_MULTIPLE_WRITE_REGSITER(void)
{
//	uint16_t calculate_crc = 0;
//	uint8_t cal_crc1=0,cal_crc2=0;
//	uint16_t RECEIVED_HIGH=0,RECEIVED_LOW=0;
//	Multiple_Write_tx_data.MULTY_SLAVE_ID_CHECK = modbus_data_decode.Slave_ID;
//	Multiple_Write_tx_data.MULTY_FUNCTION_CODE = modbus_data_decode.Function_Code;
//	Multiple_Write_tx_data.MULTY_START_ADDRESS= modbus_data_decode.START_ADDRESS_RECEIVED;
//	Multiple_Write_tx_data.MULTY_QUANTITY_VALUE = modbus_data_decode.QUANTITY_REGISTR_RECEIVED;
//	Multiple_Write_tx_data.MULTY_RECEIVED_CRC=modbus_data_decode.Write_Multiple_Register_receive_Crc;
//	Multiple_Write_tx_data.MULTY_BYTE_COUNT = modbus_data_decode.Byte_Count;
//	CALCULATE_CRC_LENGTH = UART_RX_SIZE - 2;
//	
//	calculate_crc=Modbus_CRC16(data_logger.MODBUS_RECEIVED_BUFFER,CALCULATE_CRC_LENGTH);
//	cal_crc1 = calculate_crc>>8;
//	cal_crc2 = calculate_crc&0xFF;
//	Multiple_Write_tx_data.MULTY_CALCULATED_CRC =(cal_crc2<<8|cal_crc1);
//	
//	if((Multiple_Write_tx_data.MULTY_FUNCTION_CODE == WRITE_MULTIPLE_REGISTER)&&(Multiple_Write_tx_data.MULTY_SLAVE_ID_CHECK == SLAVE_ID))
//	{
//		if(Multiple_Write_tx_data.MULTY_RECEIVED_CRC == Multiple_Write_tx_data.MULTY_CALCULATED_CRC)
//		{
//			for(int i= Multiple_Write_tx_data.MULTY_START_ADDRESS; i<Multiple_Write_tx_data.MULTY_QUANTITY_VALUE;i++)
//			{
//				switch(i)
//				{
//						case HOLDING_NODE_ADDRESS:																																					
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.NODE_ADDRESS = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;

//						case HOLDING_BAUD_RATE:																																		
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.BAUD_RATE = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;

//						case HOLDING_PARITY_SET:																																					
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.PARITY_SET = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;


//						case HOLDING_STOP_BIT:																																					
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.STOP_BIT = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;

//						case HOLDING_CONTROL_MODE:																																				
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.CONTROL_MODE = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;


//						case HOLDING_SET_SPEED_IN_MODBUS_SIGNAL_LOSS_MODE:																																					
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.SET_SPEED_IN_MODBUS_SIGNAL_LOSS_MODE = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;


//						case HOLDING_SET_SPEED_IN_FIRE_ALARAM_MODE:																																					
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.SET_SPEED_IN_FIRE_ALARAM_MODE = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;


//						case HOLDING_MAXIMUM_SPEED:																																					
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.MAXIMUM_SPEED = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;


//						case HOLDING_TARGET_SPEED_FROM_MODBUS:																																					
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.TARGET_SPEED_FROM_MODBUS = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;


//						case HOLDING_FAN_ROTATION:																																				
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.FAN_ROTATION = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;

//						case HOLDING_RAMP_UP_TIME:																																					
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.RAMP_UP_TIME = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;

//						case HOLDING_RAMP_DOWN_TIME:																																				
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.RAMP_DOWN_TIME = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;


//						case HOLDING_FIRE_ALARM_MODE_SOURCE:																																					
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.FIRE_ALARM_MODE_SOURCE = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;


//						case HOLDING_FIRE_ALARM_ACTIVATE:																																					
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.FIRE_ALARM_ACTIVATE = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;


//						case HOLDING_DI1_FUNCTION:																																					
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.DI1_FUNCTION = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;


//						case HOLDING_DI2_FUNCTION:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.DI2_FUNCTION = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;

//						case HOLDING_SET_FILTER_RUN_HOURS:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.SET_FILTER_RUN_HOURS = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;

//						case HOLDING_RESET_FILTER_RUN_HOURS:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.RESET_FILTER_RUN_HOURS = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;

//						case HOLDING_AI1_MINIMUM_VALUE:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.AI1_MINIMUM_VALUE = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;

//						case HOLDING_SWITCHING_FREQUENCY:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.SWITCHING_FREQUENCY = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;

//						case HOLDING_AI1_MAXIMUM_VALUE:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.AI1_MAXIMUM_VALUE = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;

//						case HOLDING_PID_SENSOR_SELECT:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.PID_SENSOR_SELECT = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;

//						case HOLDING_RESERVED_23:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.RESERVED_23 = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;

//						case HOLDING_RESERVED_24:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.RESERVED_24 = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;

//						case HOLDING_RESERVED_25:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.RESERVED_25 = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;

//						case HOLDING_RESERVED_26:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.RESERVED_26 = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;

//						case HOLDING_RESERVED_27:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.RESERVED_27 = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;


//						case HOLDING_RESERVED_28:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.RESERVED_28 = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;

//						case HOLDING_RESERVED_29:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.RESERVED_29 = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;


//						case HOLDING_RESERVED_30:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.RESERVED_30 = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;


//						case HOLDING_SET_DEFAULT_FACTORY:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.SET_DEFAULT_FACTORY = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;


//					


//						case HOLDING_RESERVED_32:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.RESERVED_32 = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;


//						case HOLDING_RESERVED_33:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.RESERVED_33 = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;


//						case HOLDING_RESERVED_34:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.RESERVED_34 = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;


//						case HOLDING_RESERVED_35:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.RESERVED_35 = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;


//						case HOLDING_RESERVED_36:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.RESERVED_36 = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;

//						case HOLDING_RESERVED_37:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.RESERVED_37 = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;


//						case HOLDING_RESERVED_38:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.RESERVED_38 = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;


//						case HOLDING_RESERVED_39:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.RESERVED_39 = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;


//						case HOLDING_RESERVED_40:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.RESERVED_40 = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;


//						case HOLDING_RESERVED_41:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.RESERVED_41 = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;


//						case HOLDING_RESERVED_42:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.RESERVED_42 = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;


//						case HOLDING_RESERVED_43:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.RESERVED_43 = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;


//						case HOLDING_RESERVED_44:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.RESERVED_44 = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;


//						case HOLDING_RESERVED_45:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.RESERVED_45 = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;

//						
//							case HOLDING_RESERVED_46:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.RESERVED_46 = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;

//						case HOLDING_BMS_FUNCTION:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.BMS_FUNCTION = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;


//						case HOLDING_SUPPRESSION_RANGE_SETTING:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.SUPPRESSION_RANGE_SETTING = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;


//						case HOLDING_RANGE_MIN_SPEED:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.RANGE_1_MIN_SPEED = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;

//						case HOLDING_RANGE_MAX_SPEED:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.RANGE_1_MAX_SPEED = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;

//						case HOLDING_RANGE_MIN_WINDING_TEMPERATUE:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.RANGE_2_WINDING_MIN_TEMPERATUE = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;


//						case HOLDING_RANGE_MAX_WINDING_TEMPERATUE:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.RANGE_2_WINDING_MAX_TEMPERATUE = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;

//						case HOLDING_RANGE_MIN_MOTOR_CURRENT:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.RANGE_3_MIN_CURRENT = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;


//						case HOLDING_RANGE_MAX_MOTOR_CURRENT:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.RANGE_3_MAX_CURRENT = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;


//						case HOLDING_PID_CONFIGURATION_DIFFERENTIAL_PRESSURE_SET_VALUE:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.PID_CONFIGURATION_DIFFERENTIAL_PRESSURE_SET_VALUE = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;


//						case HOLDING_DIFFERENTIAL_PRESSURE_RANGE_MIN:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.DIFFERENTIAL_PRESSURE_RANGE_MIN = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;

//						case HOLDING_DIFFERNETIAL_PRESEURE_RANGE_MAX:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.DIFFERNETIAL_PRESEURE_RANGE_MAX = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;


//						case HOLDING_PRESSURE_SPEED_MIN:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.PRESSURE_SPEED_MIN = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;


//						case HOLDING_PRESSURE_SPEED_MAX:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.PRESSURE_SPEED_MAX = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;


//						case HOLDING_PID_CONFIGURATION_DIFFERNETIAL_TEMPERAUTE_SET_VALUE:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.PID_CONFIGURATION_DIFFERNETIAL_TEMPERAUTE_SET_VALUE = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;


//						case HOLDING_RESERVED_61:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.RESERVED_61 = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;


//						case HOLDING_RESERVED_62:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.RESERVED_62 = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;



//						case HOLDING_DIFFERNTIAL_TEMPERATURE_SPEED_MIN:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.DIFFERNTIAL_TEMPERATURE_SPEED_MIN = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;


//						case HOLDING_DIFFERNTIAL_TEMPERATURE_SPEED_MAX:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.DIFFERNTIAL_TEMPERATURE_SPEED_MAX = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;



//						case HOLDING_PID_CONFIGURE_FLOW_RATE_SET_VALUE:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.PID_CONFIGURE_FLOW_RATE_SET_VALUE = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;


//						case HOLDING_FLOW_RATE_RANGE_MIN:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.FLOW_RATE_RANGE_MIN = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;



//						case HOLDING_FLOW_RATE_RANGE_MAX:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.FLOW_RATE_RANGE_MAX = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;


//						case HOLDING_FLOW_SPEED_MIN:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.FLOW_SPEED_MIN = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;


//						case HOLDING_FLOW_SPEED_MAX:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.FLOW_SPEED_MAX = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;


//						case HOLDING_K1_FUNCTION:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.K1_FUNCTION = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;


//						case HOLDING_SET_INTERNAL_1:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.SET_INTERNAL_1 = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;


//						case HOLDING_SET_INTERNAL_2:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.SET_INTERNAL_2 = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;


//						case HOLDING_SET_INTERNAL_3:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.SET_INTERNAL_3 = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;


//						case HOLDING_MIN_SPEED:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.MIN_SPEED = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;

//						case HOLDING_RESERVED_75:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.RESERVED_75 = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;


//						case HOLDING_CONTROL_BITS:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.CONTROL_BITS = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;


//						case HOLDING_RESERVED_77:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.RESERVED_77 = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;


//						case HOLDING_LED_MODE:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.LED_MODE = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;


//						case HOLDING_RESERVED_79:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.RESERVED_79 = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;


//						case HOLDING_RESERVED_80:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.RESERVED_80 = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;


//						case HOLDING_RESERVED_81:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.RESERVED_81 = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;

//						case HOLDING_RESERVED_82:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.RESERVED_82 = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;

//						case HOLDING_RESERVED_83:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.RESERVED_83 = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;

//						case HOLDING_RESERVED_84:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.RESERVED_84 = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;

//						case HOLDING_RESERVED_85:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.RESERVED_85 = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;

//						case HOLDING_RESERVED_86:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.RESERVED_86 = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;

//						case HOLDING_RESERVED_87:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.RESERVED_87 = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;

//						case HOLDING_RESERVED_88:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.RESERVED_88 = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;

//						case HOLDING_RESERVED_89:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.RESERVED_89 = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;

//						case HOLDING_BLOCKING_PROTECTION_CHANGE_OF_DIRECTION:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.BLOCKING_PROTECTION_CHANGE_OF_DIRECTION = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;

//						case HOLDING_RESERVED_91:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.RESERVED_91 = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;


//						case HOLDING_RESET:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.RESET = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;


//						case HOLDING_ANTI_LOCK_RETIES_ROTOR_LOCK:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.ANTI_LOCK_RETIES_ROTOR_LOCK = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;


//						case HOLDING_SYSTEM_DESIGNER:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.SYSTEM_DESIGNER = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;


//						case HOLDING_END_CUSTOMER:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.END_CUSTOMER = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;


//						case HOLDING_SENSOR_PRESSURE_UNIT:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.SENSOR_PRESSURE_UNIT = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;


//						case HOLDING_SENSOR_TEMPERATURE_UNIT:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.SENSOR_TEMPERATURE_UNIT = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;


//						case HOLDING_SENSOR_FLOW_UNIT:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.SENSOR_FLOW_UNIT = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;


//						case HOLDING_RESERVED_99:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.RESERVED_99 = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;


//						case HOLDING_RESERVED_100:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.RESERVED_100 = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;


//						case HOLDING_RESERVED_101:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.RESERVED_101 = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;


//						case HOLDING_SYSTEM_ADMINISTRATOR:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.SYSTEM_ADMINISTRATOR = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;


//						case HOLDING_RESERVED_103:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.RESERVED_103 = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;


//						case HOLDING_MOTOR_MODEL_NAME_104:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.MOTOR_MODEL_NAME_104 = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;

//						case HOLDING_MOTOR_MODEL_NAME_105:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.MOTOR_MODEL_NAME_105 = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;
//						
//						case HOLDING_MOTOR_MODEL_NAME_106:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.MOTOR_MODEL_NAME_106 = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;
//						
//						case HOLDING_MOTOR_MODEL_NAME_107:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.MOTOR_MODEL_NAME_107 = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;
//						
//						case HOLDING_MOTOR_MODEL_NAME_108:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.MOTOR_MODEL_NAME_108 = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;
//						
//						case HOLDING_MOTOR_MODEL_NAME_109:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.MOTOR_MODEL_NAME_109 = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;
//						
//						case HOLDING_MOTOR_MODEL_NAME_110:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.MOTOR_MODEL_NAME_110 = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;
//						
//						case HOLDING_MOTOR_MODEL_NAME_111:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.MOTOR_MODEL_NAME_111 = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;
//						
//						
//						
//						case HOLDING_MOTOR_MACHINE_NUMBER_112:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.MOTOR_MACHINE_NUMBER_112 = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;
//						
//						case HOLDING_MOTOR_MACHINE_NUMBER_113:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.MOTOR_MACHINE_NUMBER_113 = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;
//							
//						case HOLDING_MOTOR_MACHINE_NUMBER_114:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.MOTOR_MACHINE_NUMBER_114 = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;
//								
//						case HOLDING_MOTOR_MACHINE_NUMBER_115:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.MOTOR_MACHINE_NUMBER_115 = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;
//									
//						case HOLDING_MOTOR_MACHINE_NUMBER_116:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.MOTOR_MACHINE_NUMBER_116 = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;
//										
//						case HOLDING_MOTOR_MACHINE_NUMBER_117:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.MOTOR_MACHINE_NUMBER_117 = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;
//											
//											


//						case HOLDING_MOTOR_PRODUCTION_YEAR:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.MOTOR_PRODUCTION_YEAR = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;


//						case HOLDING_MOTOR_PRODUCTION_MONTH:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.MOTOR_PRODUCTION_MONTH = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;


//						case HOLDING_MOTOR_PRODUCTION_DAY:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.MOTOR_PRODUCTION_DAY = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;


//						case HOLDING_MODEL_NAME_121:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.MODEL_NAME_121 = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;
//						
//						case HOLDING_MODEL_NAME_122:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.MODEL_NAME_122 = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;
//						
//						case HOLDING_MODEL_NAME_123:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.MODEL_NAME_123 = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;
//						
//						case HOLDING_MODEL_NAME_124:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.MODEL_NAME_124 = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;
//						
//						case HOLDING_MODEL_NAME_125:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.MODEL_NAME_125 = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;
//						
//						case HOLDING_MODEL_NAME_126:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.MODEL_NAME_126 = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;
//						
//						case HOLDING_MODEL_NAME_127:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.MODEL_NAME_127 = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;
//						
//						case HOLDING_MODEL_NAME_128:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.MODEL_NAME_128 = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;


//						case HOLDING_MACHINE_NUMBER_129:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.MACHINE_NUMBER_129 = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;
//						
//						case HOLDING_MACHINE_NUMBER_130:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.MACHINE_NUMBER_130 = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;
//							
//					  case HOLDING_MACHINE_NUMBER_131:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.MACHINE_NUMBER_131 = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;
//								
//						case HOLDING_MACHINE_NUMBER_132:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.MACHINE_NUMBER_132 = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;
//									
//						case HOLDING_MACHINE_NUMBER_133:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.MACHINE_NUMBER_133 = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;
//										
//						case HOLDING_MACHINE_NUMBER_134:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.MACHINE_NUMBER_134 = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;
//						
//						
//						


//						case HOLDING_MACHINE_PRODUCTION_YEAR:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.MACHINE_PRODUCTION_YEAR = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;


//						case HOLDING_MACHINE_PRODUCITON_MONTH:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.MACHINE_PRODUCITON_MONTH = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;


//						case HOLDING_MACHINE_PRODUCITON_DAY:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.MACHINE_PRODUCITON_DAY = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;


//						case HOLDING_RATED_POWER_RATING:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.RATED_POWER_RATING = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;

//						case HOLDING_RESERVED_139:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.RESERVED_139 = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;
//						case HOLDING_RESERVED_140:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.RESERVED_140 = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;
//						case HOLDING_RATED_CURRENT:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.RATED_CURRENT = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;


//						case HOLDING_RESERVED_142:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.RESERVED_142 = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;

//						case HOLDING_NO_OF_POLES:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.NO_OF_POLES = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;

//						case HOLDING_RESERVED_144:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.RESERVED_144 = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;

//						case HOLDING_RATED_TORQUE:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.RATED_TORQUE = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;

//						case HOLDING_DRIVE_INPUT_VOLTAGE_MIN_RANGE:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.DRIVE_INPUT_VOLTAGE_MIN_RANGE = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;


//						case HOLDING_DRIVE_MAXIMUM_OUTPUT_MAX_POWER:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.DRIVE_MAXIMUM_OUTPUT_MAX_POWER = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;


//						case HOLDING_DRIVE_MAXIMUM_CURRENT_RATING:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.DRIVE_MAXIMUM_CURRENT_RATING = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;


//						case HOLDING_DRIVE_FRQUENCY_MAX_RANGE:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.DRIVE_FRQUENCY_MAX_RANGE = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;


//						case HOLIDNG_TEMPERATURE_MIN_WORKING_RANGE:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.TEMPERATURE_MIN_WORKING_RANGE = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;


//						case HOLIDNG_TEMPERATURE_MAX_WORKING_RANGE:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.TEMPERATURE_MAX_WORKING_RANGE = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;


//						case HOLDING_RANGE_MIN_IGBT_TEMPERATUE:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.RANGE_MIN_IGBT_TEMPERATUE = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;


//						case HOLDING_RANGE_MAX_IGBT_TEMPERATUE:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.RANGE_MAX_IGBT_TEMPERATUE = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;


//						case HOLDING_DRIVE_INPUT_VOLTAGE_MAX_RANGE:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.DRIVE_INPUT_VOLTAGE_MAX_RANGE = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;


//						case HOLDING_DRIVE_FRQUENCY_MIN_RANGE:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.DRIVE_FRQUENCY_MIN_RANGE = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;


//						case HOLDING_INPUT_FREQUENCY_MAX_RANGE:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.INPUT_FREQUENCY_MAX_RANGE = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;


//						case HOLIDNG_INPUT_FREQUENCY_MIN_RANE:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.INPUT_FREQUENCY_MIN_RANE = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;

//						
//						case HOLIDNG_TORQUE_CONSTANT:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.TORQUE_CONSTANT = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;
//						
//						
//						case HOLDING_FAIL_SAFE_ON_OFF:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.FAIL_SAFE_ON_OFF = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;


//						case HOLDING_FAIL_SAFE_RUNNING_DIRECTION:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.FAIL_SAFE_RUNNING_DIRECTION = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;


//						case HOLDING_FAIL_SAFE_FUNCTION_SET_SPEED:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.FAIL_SAFE_FUNCTION_SET_SPEED = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;



//						case HOLDING_FAIL_SAFE_SOURCE:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.FAIL_SAFE_SOURCE = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;



//						case HOLDING_FAIL_SAFE_ACTIVATE_SET_VALUE:
//						RECEIVED_HIGH = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN];
//						RECEIVED_LOW = modbus_data_decode.RECEIVED_DATA[INDEX_RXN+NEXT_RXN+1];
//						Modbus_Register.holding_register.FAIL_SAFE_ACTIVATE_SET_VALUE = (RECEIVED_HIGH<<8 | RECEIVED_LOW);
//						break;
//					
//				}
//				INDEX_RXN++;
//			NEXT_RXN++;
//			}
//		}	
//		return 1;
//	}
//	else{
//	return 0;
//	}
}



