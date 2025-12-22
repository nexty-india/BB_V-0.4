#include "Modbus_Holding_Register.h"
#include "Bharat_Bijlee.h"
#include "Modbus_comm.h"
#include "Application_holding_register.h"
HOLDING_TX_DATA Holding_Tx_Data;
uint16_t g_Holding_Crc_Data_Size,g_Holding_Calculate_Crc_Txn,g_Calculate_Crc,Data_Size,INPUT_CRC_DATA_SIZE,INPUT_CALCULATE_CRC_TXN,TX_DATA_LEN;

/**
 * @brief Prepares Modbus response data for Holding and Input registers.
 *
 * This function verifies CRC integrity and constructs the Modbus 
 * response frame for either Holding Registers or Input Registers, 
 * depending on the function code received from the master.
 *
 * Steps:
 * 1. Recalculate CRC from received request and verify it.
 * 2. If CRC is valid, prepare transmission buffer with:
 *      - Slave ID
 *      - Function code
 *      - Byte count
 *      - Requested register data (high and low bytes)
 * 3. Append CRC16 to the transmission buffer.
 *
 * @return
 *  - true  : If valid data prepared successfully for transmission.
 *  - false : If CRC mismatch or function code invalid.
 */
bool HOLDING_REG_AND_INPUT_REG_DATA(void)
{
	uint16_t Calculate_crc = 0,Function_Code = 0;
	uint8_t Crc_1 = 0, Crc_2 = 0, Byte_Count = 0,Slave_ID=0;
	uint8_t Cal_Crc_1 = 0, Cal_Crc_2 = 0;
	uint16_t Address_start = 0, Quantity_Register = 0, Data_Size = 0,Transmit_Mul_CRC = 0;
	uint16_t Recieved_CRC = 0;
	uint8_t Received_high = 0, Received_low = 0;

	/*--------------------------------------------------------------
	 * Step 2: Extract Modbus Frame Parameters
	 *--------------------------------------------------------------*/
	Address_start = Modbus_Decode_Data.START_ADDRESS_RECEIVED;
	Quantity_Register = Modbus_Decode_Data.QUANTITY_REGISTR_RECEIVED;
	Byte_Count = Quantity_Register * 2;       // Each register = 2 bytes
	Data_Size = Quantity_Register + Address_start;
	Slave_ID = Modbus_Decode_Data.Slave_ID;
	Function_Code = Modbus_Decode_Data.Function_Code;
	
	/*--------------------------------------------------------------
	 * Step 3: Prepare Response for READ HOLDING REGISTER
	 *--------------------------------------------------------------*/
	if((Modbus_Decode_Data.Slave_ID == SLAVE_ID) && 
	   (Modbus_Decode_Data.Function_Code == READ_HOLDING_REGISTER))   // FIXED: '==' instead of '='
	{
		// Validate CRC from received frame
		Recieved_CRC = Modbus_Decode_Data.Holding_Register_receive_Crc;
		Calculate_crc = Modbus_CRC16(data_logger.MODBUS_RECEIVED_BUFFER, 6);
		Crc_1 = Calculate_crc >> 8;
		Crc_2 = Calculate_crc & 0xFF;
		g_Calculate_Crc = (Crc_2 << 8 | Crc_1);
		if(g_Calculate_Crc == Recieved_CRC)
		{
			// Prepare Modbus transmit buffer
			data_logger.TRANSMISSION_BUFFER[0] = Modbus_Decode_Data.Slave_ID;
			data_logger.TRANSMISSION_BUFFER[1] = Modbus_Decode_Data.Function_Code;
			data_logger.TRANSMISSION_BUFFER[2] = Byte_Count;

			// Fill requested Holding Register data (High + Low bytes)
			for(int i = Address_start; i < Data_Size; i++)
			{
					uint16_t reg_value = MODBUS_HOLDING_REGISTERS[i].actual_value;
					uint16_t offset = 2 * (i - Address_start);

					data_logger.TRANSMISSION_BUFFER[HOLDING_START_DATA + offset]     = (uint8_t)(reg_value >> 8);
					data_logger.TRANSMISSION_BUFFER[HOLDING_START_DATA + offset + 1] = (uint8_t)(reg_value & 0xFF);
			}
			

			// Compute CRC for transmission frame
			g_Holding_Crc_Data_Size = 3 + Byte_Count;
			g_Holding_Calculate_Crc_Txn = Modbus_CRC16((uint8_t *)data_logger.TRANSMISSION_BUFFER, g_Holding_Crc_Data_Size);
			Cal_Crc_1 = g_Holding_Calculate_Crc_Txn >> 8;
			Cal_Crc_2 = g_Holding_Calculate_Crc_Txn & 0xFF;
			g_Holding_Calculate_Crc_Txn = 0;
			// Append CRC to transmission buffer
			data_logger.TRANSMISSION_BUFFER[g_Holding_Crc_Data_Size]     = Cal_Crc_2;
			data_logger.TRANSMISSION_BUFFER[g_Holding_Crc_Data_Size + 1] = Cal_Crc_1;
			TX_DATA_LEN = 3+Byte_Count+2;     // 3:- SLAVE ID,FUNC_ CODE, BYTE COUNT AND 2:- CRC VALUE BUFFER
			
		}
		return true;
	}
//	else
//	{
//		return false;
//	}

	/*--------------------------------------------------------------
	 * Step 4: Prepare Response for READ INPUT REGISTER
	 *--------------------------------------------------------------*/
	else if((Modbus_Decode_Data.Slave_ID == SLAVE_ID) && 
	   (Modbus_Decode_Data.Function_Code == READ_INPUT_REGISTER))    // FIXED: '==' instead of '='
	{
		// Validate CRC from received frame
		Recieved_CRC = Modbus_Decode_Data.Input_Register_receive_Crc;
		Calculate_crc = Modbus_CRC16(data_logger.MODBUS_RECEIVED_BUFFER, 6);
		Crc_1 = Calculate_crc >> 8;
		Crc_2 = Calculate_crc & 0xFF;
		g_Calculate_Crc = (Crc_2 << 8 | Crc_1);
		if(g_Calculate_Crc == Recieved_CRC)
		{
			// Prepare Modbus transmit buffer
			data_logger.TRANSMISSION_BUFFER[0] = Modbus_Decode_Data.Slave_ID;
			data_logger.TRANSMISSION_BUFFER[1] = Modbus_Decode_Data.Function_Code;
			data_logger.TRANSMISSION_BUFFER[2] = Byte_Count;

			// Fill requested Input Register data (High + Low bytes)
			for(int i = Address_start; i < Data_Size; i++)
			{
				data_logger.TRANSMISSION_BUFFER[HOLDING_START_DATA + 2*(i - Address_start)]     = (uint8_t)(MODBUS_INPUT_REGISTERS[i].actual_value >> 8);
				data_logger.TRANSMISSION_BUFFER[HOLDING_START_DATA + 2*(i - Address_start) + 1] = (uint8_t)(MODBUS_INPUT_REGISTERS[i].actual_value & 0xFF);
			}

			// Compute CRC for transmission frame
			INPUT_CRC_DATA_SIZE = 3 + Byte_Count;
			INPUT_CALCULATE_CRC_TXN = Modbus_CRC16((uint8_t *)data_logger.TRANSMISSION_BUFFER, INPUT_CRC_DATA_SIZE);
			Cal_Crc_1 = INPUT_CALCULATE_CRC_TXN >> 8;
			Cal_Crc_2 = INPUT_CALCULATE_CRC_TXN & 0xFF;
			INPUT_CALCULATE_CRC_TXN = 0;
			// Append CRC to transmission buffer
			data_logger.TRANSMISSION_BUFFER[INPUT_CRC_DATA_SIZE]     = Cal_Crc_2;
			data_logger.TRANSMISSION_BUFFER[INPUT_CRC_DATA_SIZE + 1] = Cal_Crc_1;
			TX_DATA_LEN = 3+Byte_Count+2;     // 3:- SLAVE ID,FUNC_ CODE, BYTE COUNT AND 2:- CRC VALUE BUFFER
			
		}
		return true;
	}

	
	else if((Slave_ID == SLAVE_ID)&&(Function_Code == WRITE_MULTIPLE_REGISTER))
	{
		
		Calculate_crc = Modbus_CRC16(data_logger.MODBUS_RECEIVED_BUFFER, 6);
		Crc_1 = Calculate_crc >> 8;
		Crc_2 = Calculate_crc & 0xFF;
		g_Calculate_Crc = (Crc_2 << 8 | Crc_1);
		Recieved_CRC = Modbus_Decode_Data.Write_Multiple_Register_receive_Crc;
		if(g_Calculate_Crc == Recieved_CRC)
		{
			for(int i = Address_start;i<Data_Size;i++)
			{
				Received_high = Modbus_Decode_Data.RECEIVED_DATA[HOLDING_START_DATA + 2*(i - Address_start)];
				Received_low = Modbus_Decode_Data.RECEIVED_DATA[HOLDING_START_DATA + 2*(i - Address_start) + 1];
				MODBUS_HOLDING_REGISTERS[Address_start].actual_value = (Received_high << 8 |Received_low);
			}

			data_logger.TRANSMISSION_BUFFER[0] = Slave_ID;
			data_logger.TRANSMISSION_BUFFER[1] = Function_Code;
			data_logger.TRANSMISSION_BUFFER[2] = Address_start>>8;
			data_logger.TRANSMISSION_BUFFER[3] = Address_start&0xFF;
			data_logger.TRANSMISSION_BUFFER[4] = Quantity_Register>>8;
			data_logger.TRANSMISSION_BUFFER[5] = Quantity_Register&0xFF;
			Transmit_Mul_CRC = Modbus_CRC16((uint8_t *)data_logger.TRANSMISSION_BUFFER,6);
			Cal_Crc_1 = Transmit_Mul_CRC >> 8;
			Cal_Crc_2 = Transmit_Mul_CRC & 0xFF;
			Transmit_Mul_CRC = 0;
			data_logger.TRANSMISSION_BUFFER[6] = Cal_Crc_2;
			data_logger.TRANSMISSION_BUFFER[7] = Cal_Crc_1;
			TX_DATA_LEN = 8;
		}
			return true;
	}
	else if((Function_Code == WRITE_SINGLE_REGISTER)&&(Slave_ID == SLAVE_ID))
	{ 
		Calculate_crc = Modbus_CRC16(data_logger.MODBUS_RECEIVED_BUFFER, 6);
		Crc_1 = Calculate_crc >> 8;
		Crc_2 = Calculate_crc & 0xFF;
		g_Calculate_Crc = (Crc_2 << 8 | Crc_1);
		Recieved_CRC = Modbus_Decode_Data.Write_Single_Register_received_Crc;
		if(g_Calculate_Crc == Recieved_CRC)
		{
			Received_high = Modbus_Decode_Data.RECEIVED_DATA[1];
			Received_low = Modbus_Decode_Data.RECEIVED_DATA[0];
			MODBUS_HOLDING_REGISTERS[Address_start].actual_value = (Received_high << 8 |Received_low);
			data_logger.TRANSMISSION_BUFFER[0] = Slave_ID;
			data_logger.TRANSMISSION_BUFFER[1] = Function_Code;
			data_logger.TRANSMISSION_BUFFER[2] = Address_start>>8;
			data_logger.TRANSMISSION_BUFFER[3] = Address_start&0xFF;
			data_logger.TRANSMISSION_BUFFER[4] = MODBUS_HOLDING_REGISTERS[Address_start].actual_value>>8;						
			data_logger.TRANSMISSION_BUFFER[5] = MODBUS_HOLDING_REGISTERS[Address_start].actual_value&0xFF;
			Transmit_Mul_CRC = Modbus_CRC16((uint8_t *)data_logger.TRANSMISSION_BUFFER,6);
			Crc_1 = Transmit_Mul_CRC & 0xFF;
			Crc_2 = Transmit_Mul_CRC >> 8;
			data_logger.TRANSMISSION_BUFFER[6] = Crc_1;
			data_logger.TRANSMISSION_BUFFER[7] = Crc_2;
			TX_DATA_LEN = 8;
		}
		return true;
	}
	else
	{
		return false;
	}
	
	

	/*--------------------------------------------------------------
	 * Step 5: Invalid Function Code or CRC Mismatch
	 *--------------------------------------------------------------*/
	
}




void DUMMBY_DATA(void)
{
	MODBUS_HOLDING_REGISTERS[HOLDING_AI1_MINIMUM_VALUE].actual_value = 50;//Modbus_Register.holding_register.AI1_MINIMUM_VALUE;
	MODBUS_HOLDING_REGISTERS[HOLDING_AI1_MAXIMUM_VALUE].actual_value = 100;
	 MODBUS_HOLDING_REGISTERS[HOLDING_MAXIMUM_SPEED].actual_value = 1800;
	 MODBUS_HOLDING_REGISTERS[HOLDING_MIN_SPEED].actual_value = 800;
	MODBUS_HOLDING_REGISTERS[HOLDING_DI1_FUNCTION].actual_value = 1;
}
