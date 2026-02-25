#include "Modbus_Comm.h"
#include "A31M22x_pcu.h"
#include "user_timer.h"
#include "Application_Holding_Register.h"
#include "Fault_Status.h"
//#define UART_SIZE 256

/*-----------------------------------------GLOBLE VARIABLE--------------------------------------------------*/
//char Receive_data_buffer_1[20] = {11,2,3,34,35,36,07,12,22,33,44,55,66,77,88,33,11};
char array[]="MODBUS IMPLEMENTATION CHECKING........................   ";

LOGGER_t data_logger;
MODBUS_TXN modbus_txn_data;
MODBUS_FORMAT modbus_format;

uint32_t g_tramit_counter_1;
/*-----------------------------------------------------------------------------------------------------------*/
uint8_t g_data_rx = 0;
uint16_t g_Recieve_Flag=1;
uint16_t g_Uart_idle_line_counter,g_Rx_rec_len;
extern  uint16_t g_Tx_count_check;
MODBUS_STATMACHINE_t Modbus_state = DATA_RECEIVING;
MODBUS_REG_t MODBUS_INPUT_REGISTERS[INPUT_TOTAL_MEMBERS];
MODBUS_REG_t MODBUS_HOLDING_REGISTERS[HOLDING_TOTAL_MEMBER];
MODBUS_DATA_DECODE_t Modbus_Decode_Data;
uint16_t modbus_fault_counter;
bool MODBUS_FAULT_OCCUR = false;
/**
* @brief 	interrupt Handler for uart 1 (MODBUS PROTOCOL)
* This function handles UART receive and transmit interrupts for Modbus data exchange.
* It processes received bytes, detects complete Modbus frames, and triggers decoding once
* a full message is received.
* @param[in] event   UART interrupt event flag (receive or transmit complete).
* @param[in] context Optional context pointer (not used here). 
*
*
*
* @note This handler supports Modbus RTU-style communication where frames are variable in length
*       depending on the function code and data size.
	*/
void uart_irq_handler(uint32_t event, void *context)
{
	if(event & UART_EVENT_RECEIVE_DONE)                                           													//Receiver Interrupt
	{
		g_Uart_idle_line_counter = 0;   //Resets the idle line counter.
		modbus_fault_counter = 0;		
		HAL_UART_Receive(UART_ID_1,(uint8_t *)&data_logger.RECEPTION_BUFFER,1,UART_IO_TYPE_NON_BLOCK);				// Reads one byte from UART (non-blocking mode).
		data_logger.MODBUS_RECEIVED_BUFFER[data_logger.TOTAL_BYTES_RECEIVED] = data_logger.RECEPTION_BUFFER;  //Stores the received byte in the Modbus receive buffer.
		data_logger.TOTAL_BYTES_RECEIVED++;    																																//Increments the received byte count.
	}

	if(event & UART_EVENT_TRANSMIT_DONE)																																		//Transmitting Interrupt
	{
		g_Tx_count_check = 1;
	}
}




/**
 * @brief Handles the Modbus communication state machine.
 *
 * This function manages the different stages of Modbus data communication:
 * receiving data, verifying completeness, decoding received data, 
 * preparing data for transmission, and completing the transmission cycle.
 *
 * Workflow:
 * 1. DATA_RECEIVING – Counts idle time and checks for data reception timeout.
 * 2. DATA_RECEIVED_COMPLETED – Validates and decodes the received data.
 * 3. DATA_TO_BE_TRANSMITTED – Prepares the response data for transmission.
 * 4. DATA_TRANSMITTED_COMPLETED – Marks completion of transmission.
 */
volatile uint16_t my_time = 10;
bool auto_time_calc_flag = 0;
void ModbusStateMachine(void)
{
	
	switch(Modbus_state)
	{
		/*--------------------------------------------------------------
		 * State 1: Data Receiving
		 * - Increments idle counter and checks if data reception timed out.
		 * - If timeout occurs and minimum data is received, move to next state.
		 * - Resets counters to avoid overflow and handle invalid cases.
		 *--------------------------------------------------------------*/
		case DATA_RECEIVING:
		if((data_logger.TOTAL_BYTES_RECEIVED > 0)&&(g_Uart_idle_line_counter < TIME_OUT))
		{
			g_Uart_idle_line_counter++;
		}
		else if (data_logger.TOTAL_BYTES_RECEIVED >= MIN_UART_SIZE)
		{
			Modbus_state = DATA_RECEIVED_COMPLETED;
		  MODBUS_FAULT_OCCUR = false;
			Fault.Fault_bits.ModbusCommunication_Fault = 0;
		}
		else
		{
			data_logger.TOTAL_BYTES_RECEIVED = 0;
			g_Uart_idle_line_counter = 0;
		}
		
		if(modbus_fault_counter < 2000)
		{
			modbus_fault_counter++;
		}
		else{
			if(controlmode.MODBUS_FLAG_BIT){
			MODBUS_FAULT_OCCUR = true;
			Fault.Fault_bits.ModbusCommunication_Fault = 1;
			Modbus_state = DATA_RECEIVING;}
		}
		
		
			break;
		
		/*--------------------------------------------------------------
		 * State 2: Data Received Completed
		 * - Resets data counter.
		 * - Validates received Modbus frame.
		 * - If valid, decode the received data and prepare for transmission.
		 *--------------------------------------------------------------*/
		case DATA_RECEIVED_COMPLETED:
		
			g_Recieve_Flag = 0;				// Stop Receiving anymore data till the current data is successfully processed
			data_logger.TOTAL_BYTES_RECEIVED = 0;
			// Validate received Modbus frame
			if((ModbusDataValidCheck() == 1)&&(ModbusRxDataDecode() == 1))
			{
				// Decode and process received Modbus frame
					Modbus_state = DATA_TO_BE_TRANSMITTED;
			}
			else
			{
				memset(data_logger.TRANSMISSION_BUFFER,0,TX_DATA_LEN);  // Clear transmit buffer
				memset(data_logger.MODBUS_RECEIVED_BUFFER,0,g_Rx_rec_len);  // Clear receive buffer
				g_Recieve_Flag = 1;
				Modbus_state = DATA_RECEIVING;
			}
		
			break;
		
		/*--------------------------------------------------------------
		 * State 3: Data To Be Transmitted
		 * - Prepares and verifies data to be transmitted.
		 * - Moves to transmission complete state after successful send.
		 *--------------------------------------------------------------*/
		case DATA_TO_BE_TRANSMITTED:
			// TODO: Add condition to check if UART transmission is ready
			if((HOLDING_REG_AND_INPUT_REG_DATA() == 1)&&(!CheckTransmitValidData() == 1))
			{
					Modbus_state = DATA_TRANSMITED_COMPLETED;
				
			}
			else{
				memset(data_logger.TRANSMISSION_BUFFER,0,TX_DATA_LEN);  // Clear transmit buffer
				memset(data_logger.MODBUS_RECEIVED_BUFFER,0,g_Rx_rec_len);  // Clear receive buffer
				g_Recieve_Flag = 1;
				Modbus_state = DATA_RECEIVING;
				
			}
			g_Tx_count_check = 0;
			g_tramit_counter_1 = 0;
			break;
		
		/*--------------------------------------------------------------
		 * State 4: Data Transmitted Completed
		 * - Marks completion of Modbus communication cycle.
		 * - Can be reset externally to DATA_RECEIVING for next communication.
		 *--------------------------------------------------------------*/
		case DATA_TRANSMITED_COMPLETED:
			TransmitData();
			if(g_Tx_count_check == 1)
			{
				if(user_delay(TX_DATA_LEN,&g_tramit_counter_1) == 1)
				{
					g_Recieve_Flag = 1;    // Enable reception mode
					g_Tx_count_check = 0;   // Reset transmission counter check
					memset(data_logger.TRANSMISSION_BUFFER,0,TX_DATA_LEN);  // Clear transmit buffer
					memset(data_logger.MODBUS_RECEIVED_BUFFER,0,g_Rx_rec_len);  // Clear receive buffer
					data_logger.TOTAL_BYTES_RECEIVED = 0;  // ? Reset counter
					g_Uart_idle_line_counter = 0;     
					Modbus_state = DATA_RECEIVING;
				}
			}
			// Transmission completed; waiting for next data reception
			break;
	}
}



///**
//*@brief Check NodeAddress Validation 
//*@return int
//*/
//int NodeValid(void)
//{
//	uint16_t NodeRec = 0;
//	NodeRec = data_logger.MODBUS_RECEIVED_BUFFER[SLAVE_ID];  
//}

/**
* @brief This function validate the Received data frame 
*        if all the data is valid return true otherwise false
* @return true or false
* @param none
*
*/
uint16_t Slave_id,test_var1;
bool ModbusDataValidCheck(void)
{
	uint16_t Functional_code = 0, Start_address = 0,Byte_count = 0,Quantity_register = 0;//,Flash_Nodeaddress = 0;Slave_id = 0,
	Slave_id = data_logger.MODBUS_RECEIVED_BUFFER[SLAVE_ID_RX];  
	Functional_code = data_logger.MODBUS_RECEIVED_BUFFER[FUNCTION_CODE_RX];
	Start_address = ((data_logger.MODBUS_RECEIVED_BUFFER[START_ADDRESS_HIGH_RX]<<8)|data_logger.MODBUS_RECEIVED_BUFFER[START_ADDRESS_LOW_RX]);
	Quantity_register = ((data_logger.MODBUS_RECEIVED_BUFFER[REGISTER_QUANTITY_HIGH_RX]<<8)|data_logger.MODBUS_RECEIVED_BUFFER[REGISTER_QUANTITY_LOW_RX]); 
	Flash_Nodeaddress = MODBUS_HOLDING_REGISTERS[HOLDING_NODE_ADDRESS].actual_value;
	
	if(Slave_id != g_Nodeaddress_Read)   //Check slave ID
	{
		test_var1 = 12;
		return false;
	}
	else{
		test_var1 = 234;
		return true;
	}
	
	if((Functional_code != READ_HOLDING_REGISTER)||(Functional_code != READ_INPUT_REGISTER)||(Functional_code != WRITE_SINGLE_REGISTER)||(Functional_code != WRITE_MULTIPLE_REGISTER))   //check function code
	{
		return false;
	}
	else{
		return true;
	}
			
	if(!(ADDRESS_MIN_RANGE <= Start_address)&&(!(Start_address < ADDRESS_MAX_RANGE)))  //CHeck address range with limit
	{ 
		return false;
	}
	else{
		return true;
	}
	
	
	if(Functional_code == WRITE_MULTIPLE_REGISTER)    //Check Multple Function code becasue Multiple register request frame contain Byte count.
	{
		Byte_count = data_logger.MODBUS_RECEIVED_BUFFER[6]; //assign byte count inloacal variable
		if(Byte_count != Start_address *2)  //check byte count variable is valid or not
		{
			return false;
		}else{
			return true;
		}
	}
	else{}
		
		
	if(Functional_code != WRITE_SINGLE_REGISTER)	//check Single regiter is not 
	{
		if((!(QUANTITY_MIN_RANGE <= Quantity_register))&&(!(Quantity_register >= QUANTITY_MAX_RANGE)))   //Check quantity in min and max range...
		{
			return false;
		}
		else{
			return true;
		}
	}else{
	}
		
	

		if(!DataReceivedValid())   // Check the Received data is not vaild
		{
			return false;
		}else{
			return true;
		}
	 
}



/**
* @brief This function validate the Received data 
*        if all the data is valid return true otherwise false
* @return true or false
* @param none
*
*/
bool DataReceivedValid(void)
{
	uint16_t Functional_code = 0,Start_address = 0,Quantity_register=0;
	Functional_code = data_logger.MODBUS_RECEIVED_BUFFER[FUNCTION_CODE_RX];
	Start_address = ((data_logger.MODBUS_RECEIVED_BUFFER[START_ADDRESS_HIGH_RX]<<8)|data_logger.MODBUS_RECEIVED_BUFFER[START_ADDRESS_LOW_RX]);
	Quantity_register = ((data_logger.MODBUS_RECEIVED_BUFFER[REGISTER_QUANTITY_HIGH_RX]<<8)|data_logger.MODBUS_RECEIVED_BUFFER[REGISTER_QUANTITY_LOW_RX]); 
	
	
	if(Functional_code == WRITE_MULTIPLE_REGISTER)
	{
		for(int i= Start_address;i<Quantity_register;i++)
		{
			// Store the values in a temporary variable
			uint16_t temp_data = (data_logger.MODBUS_RECEIVED_BUFFER[DATA_BEGIN_MULTI+(i-Start_address)] << 8) | data_logger.MODBUS_RECEIVED_BUFFER[DATA_BEGIN_MULTI+2*(i-Start_address) + 1];
			uint32_t *flash_data_min_value = ( uint32_t *)HOLDING_REG_MIN_START_ADDR;
			uint32_t *flash_data_max_value = ( uint32_t *)HOLDING_REG_MAX_START_ADDR;
			// Check if the value received is valid or not
			MODBUS_HOLDING_REGISTERS[i].min_valid_value = flash_data_min_value[i];
			MODBUS_HOLDING_REGISTERS[i].max_valid_value = flash_data_max_value[i];
			if(temp_data > MODBUS_HOLDING_REGISTERS[i].min_valid_value && temp_data < MODBUS_HOLDING_REGISTERS[i].max_valid_value)
			{
				return false;
			}
			else
			{
				// There is a problem so return 0
			}	
		}
	}
	else if(Functional_code == WRITE_SINGLE_REGISTER)
	{
		uint16_t temp_data = (data_logger.MODBUS_RECEIVED_BUFFER[5] << 8 | data_logger.MODBUS_RECEIVED_BUFFER[4]);
		
		if(temp_data > MODBUS_HOLDING_REGISTERS[Start_address].min_valid_value && temp_data < MODBUS_HOLDING_REGISTERS[Start_address].max_valid_value)
		{
			return false;// All Good
		}
		else
		{
			// There is a problem so return 0
		}	
	}
	else
	{
		return false;
	}
	
}


/**
*	@brief This function is used for deocode the Received valid Modbus data..
* @para void
* @retun True or false.
*/
bool ModbusRxDataDecode(void)
{
	uint8_t crc_low=0,crc_high= 0;
	uint8_t Quantity_Register_High = 0,Quantity_Register_Low=0;
	
		/*
	* 1. Extracts basic Modbus frame components:
	*    - Slave ID
	*    - Function Code
	*    - Start Address (High + Low bytes)
	*/
	Modbus_Decode_Data.Slave_ID = data_logger.MODBUS_RECEIVED_BUFFER[SLAVE_ID_RX];
	Modbus_Decode_Data.Function_Code = data_logger.MODBUS_RECEIVED_BUFFER[FUNCTION_CODE_RX];
	Modbus_Decode_Data.Start_Address_High = data_logger.MODBUS_RECEIVED_BUFFER[START_ADDRESS_HIGH_RX];
	Modbus_Decode_Data.Start_Address_Low = data_logger.MODBUS_RECEIVED_BUFFER[START_ADDRESS_LOW_RX];
	Modbus_Decode_Data.START_ADDRESS_RECEIVED = ((Modbus_Decode_Data.Start_Address_High<<8)|(Modbus_Decode_Data.Start_Address_Low));
	/**    READ_INPUT_REGISTER / READ_HOLDING_REGISTER:**
	*         - Extracts register quantity and CRC.
	*         - Sets Modbus event and decode-complete flags.
	*/
	if(Modbus_Decode_Data.Function_Code == READ_INPUT_REGISTER)
	{
		Quantity_Register_High = data_logger.MODBUS_RECEIVED_BUFFER[REGISTER_QUANTITY_HIGH_RX];
		Quantity_Register_Low = data_logger.MODBUS_RECEIVED_BUFFER[REGISTER_QUANTITY_LOW_RX];
		Modbus_Decode_Data.QUANTITY_REGISTR_RECEIVED = ((Quantity_Register_High<<8)|(Quantity_Register_Low));
		crc_high = data_logger.MODBUS_RECEIVED_BUFFER[CRC_HIGH_RX];
		crc_low = data_logger.MODBUS_RECEIVED_BUFFER[CRC_LOW_RX];	
		Modbus_Decode_Data.Input_Register_receive_Crc =  (crc_high<<8)|(crc_low);
		g_Rx_rec_len = 8;
		return true;
	}
	else if(Modbus_Decode_Data.Function_Code == READ_HOLDING_REGISTER)
	{
		Quantity_Register_High = data_logger.MODBUS_RECEIVED_BUFFER[REGISTER_QUANTITY_HIGH_RX];
		Quantity_Register_Low = data_logger.MODBUS_RECEIVED_BUFFER[REGISTER_QUANTITY_LOW_RX];
		Modbus_Decode_Data.QUANTITY_REGISTR_RECEIVED = ((Quantity_Register_High<<8)|(Quantity_Register_Low));
		crc_high = data_logger.MODBUS_RECEIVED_BUFFER[CRC_HIGH_RX];
		crc_low = data_logger.MODBUS_RECEIVED_BUFFER[CRC_LOW_RX];	
		Modbus_Decode_Data.Holding_Register_receive_Crc  = (crc_high<<8)|(crc_low);
		g_Rx_rec_len = 8;
		return true;
	}
	/*  - **WRITE_MULTIPLE_REGISTER:**
	*   - Extracts register quantity, byte count, data bytes, and CRC.
	*   - Copies payload data into `modbus_data_decode.RECEIVED_DATA[]`.
	*   - Sets Modbus event and decode-complete flags.
	*/
	else if(data_logger.MODBUS_RECEIVED_BUFFER[1] == WRITE_MULTIPLE_REGISTER)
	{
			
		Quantity_Register_High = data_logger.MODBUS_RECEIVED_BUFFER[REGISTER_QUANTITY_HIGH_RX];
		Quantity_Register_Low = data_logger.MODBUS_RECEIVED_BUFFER[REGISTER_QUANTITY_LOW_RX];
		Modbus_Decode_Data.QUANTITY_REGISTR_RECEIVED = ((Quantity_Register_High<<8)|(Quantity_Register_Low));
		Modbus_Decode_Data.Byte_Count = data_logger.MODBUS_RECEIVED_BUFFER[6];
		for(g_data_rx=0; g_data_rx < Modbus_Decode_Data.Byte_Count; g_data_rx++)
		{
			Modbus_Decode_Data.RECEIVED_DATA[g_data_rx] = data_logger.MODBUS_RECEIVED_BUFFER[g_data_rx+7];
		}
		crc_high = data_logger.MODBUS_RECEIVED_BUFFER[g_data_rx+7];
		crc_low = data_logger.MODBUS_RECEIVED_BUFFER[g_data_rx+8];
		Modbus_Decode_Data.Write_Multiple_Register_receive_Crc = (crc_high<<8)|(crc_low);
		g_Rx_rec_len = 7+Modbus_Decode_Data.QUANTITY_REGISTR_RECEIVED+2;
		return true;
	}
	/*	 **WRITE_SINGLE_REGISTER:**
	*         - Extracts single register value and CRC.
	*         - Sets Modbus event and decode-complete flags.
	*/
	else if(data_logger.MODBUS_RECEIVED_BUFFER[1] == WRITE_SINGLE_REGISTER)
	{
		Modbus_Decode_Data.RECEIVED_DATA[0] = data_logger.MODBUS_RECEIVED_BUFFER[5];    // 5:- High Data Byte
 		Modbus_Decode_Data.RECEIVED_DATA[1] = data_logger.MODBUS_RECEIVED_BUFFER[4];		 // 4:- Low Data Byte
		crc_high = data_logger.MODBUS_RECEIVED_BUFFER[CRC_HIGH_RX];
		crc_low = data_logger.MODBUS_RECEIVED_BUFFER[CRC_LOW_RX];
		Modbus_Decode_Data.Write_Single_Register_received_Crc = (crc_high<<8)|(crc_low);
		g_Rx_rec_len = 8;
		return true;
	}
	else{
		return false;
	}
}


/**
 * @brief Checks whether the Modbus data requested for transmission is valid.
 *
 * This function validates Modbus register data based on the received
 * Modbus request frame. It supports validation for both
 * READ_HOLDING_REGISTER and READ_INPUT_REGISTER function codes.
 *
 * The validation ensures that each register's actual value lies
 * within its defined minimum and maximum valid range.
 *
 * @return
 *  - true  : If all requested register data is valid and ready for transmission.
 *  - false : If any register data is out of range or invalid.
 */
bool CheckTransmitValidData(void)
{
	uint16_t Functional_code = 0;
	uint16_t Start_address = 0;
	uint16_t Quantity_register = 0;

	// Extract Modbus functional code from received buffer
	Functional_code = data_logger.MODBUS_RECEIVED_BUFFER[FUNCTION_CODE_RX];

	// Combine high and low bytes to form 16-bit start address
	Start_address = ((data_logger.MODBUS_RECEIVED_BUFFER[START_ADDRESS_HIGH_RX] << 8) |
					 data_logger.MODBUS_RECEIVED_BUFFER[START_ADDRESS_LOW_RX]);

	// Combine high and low bytes to form number of registers requested
	Quantity_register = ((data_logger.MODBUS_RECEIVED_BUFFER[REGISTER_QUANTITY_HIGH_RX] << 8) |
						 data_logger.MODBUS_RECEIVED_BUFFER[REGISTER_QUANTITY_LOW_RX]); 

	/*--------------------------------------------------------------
	 * Case 1: READ HOLDING REGISTER
	 * - Validate actual values of holding registers within requested range.
	 *--------------------------------------------------------------*/
	if(Functional_code == READ_HOLDING_REGISTER)
	{
		for(int i = Start_address; i < (Quantity_register + Start_address); i++)
		{
			uint16_t temp_val = (uint16_t)data_logger.TRANSMISSION_BUFFER[i];

			// Check if actual value is within defined valid range
			if(temp_val < MODBUS_HOLDING_REGISTERS[i].min_valid_value ||
			   temp_val > MODBUS_HOLDING_REGISTERS[i].max_valid_value)
			{
				// Invalid data found — stop and report failure
				return false;
			}
		}

		// All holding registers are valid
		return true;
	}

	/*--------------------------------------------------------------
	 * Case 2: READ INPUT REGISTER
	 * - Validate actual values of input registers within requested range.
	 *--------------------------------------------------------------*/
	else if(Functional_code == READ_INPUT_REGISTER)
	{
		for(int i = Start_address; i < (Quantity_register + Start_address); i++)
		{
			uint16_t temp_val =(uint16_t)data_logger.TRANSMISSION_BUFFER;

			// Check if actual value is within defined valid range
			if(temp_val < MODBUS_INPUT_REGISTERS[i].min_valid_value ||
			   temp_val > MODBUS_INPUT_REGISTERS[i].max_valid_value)
			{
				// Invalid data found — stop and report failure
				return false;
			}
		}

		// All input registers are valid
		return true;
	}

	/*--------------------------------------------------------------
	 * Case 3: Unsupported Functional Code
	 * - Return false to indicate invalid request.
	 *--------------------------------------------------------------*/
	else
	{
		return false;
	}
}






/**
 * @brief Calculates the CRC16 checksum for a given Modbus data frame.
 *
 * This function computes the standard Modbus RTU CRC16 value used for
 * error detection in Modbus communication. It processes each byte in
 * the input data array and performs bitwise operations according to
 * the Modbus CRC16 (polynomial 0xA001) algorithm.
 *
 * @param[in]  data    Pointer to the data buffer for which CRC is to be calculated.
 * @param[in]  length  Number of bytes in the data buffer.
 *
 * @return The calculated 16-bit CRC value.
 *
 * @note
 * - The CRC is initialized with 0xFFFF.
 * - The polynomial used is 0xA001 (standard Modbus).
 * - The low byte of the CRC is transmitted first in Modbus RTU frames.
 *
 * **Example:**
 * @code
 * uint8_t frame[] = {0x01, 0x03, 0x00, 0x00, 0x00, 0x0A};
 * uint16_t crc = Modbus_CRC16(frame, 6);
 * // crc will contain the Modbus CRC16 checksum for the frame
 * @endcode
 */

uint16_t Modbus_CRC16(uint8_t *data, uint16_t length) {
    uint16_t crc = 0xFFFF;
    for (int i = 0; i < length; i++) {
        crc ^= data[i];
        for (int j = 0; j < 8; j++) {
            if (crc & 0x0001) {
                crc >>= 1;
                crc ^= 0xA001;
            } else {
                crc >>= 1;
            }
        }
    }
    return crc;
}


/**
	* @brief 	Initialization of Uart1 for Communication with GUI uisng MODBUS Protocol
	* @param  Initialize Uart 1
	* @retval 
	*/
void UserRs485init(void)
{
	struct uart_cfg cfg;
	
	cfg.baudrate = 19200;																							//SET buad rate
	cfg.data_bit = UART_DATA_BIT_8;																		//data  bit
	cfg.parity_bit = UART_PARITY_BIT_NONE;                            //set parity bit
	cfg.stop_bit = UART_STOP_BIT_1;                                  //set stop bit
	cfg.irq_prio = 1;																													//set interrupt priority
	HAL_UART_SetIRQ(UART_ID_1, UART_IRQ_TX_EMPTY, 1);									
	HAL_UART_SetIRQ(UART_ID_1, UART_IRQ_RX_AVAIL, 1);
	HAL_UART_Init(UART_ID_1, &cfg, uart_irq_handler, NULL);								//init function for uart for modbus protocol
	HAL_UART_Receive(UART_ID_1, (uint8_t *)&data_logger.RECEPTION_BUFFER, 1, UART_IO_TYPE_NON_BLOCK); //init receive data function
}



/**
	* @brief 	Contorl Receive enable and Data enable using Gpio pin Port A
	* @param  received and Transmit
	* @retval 
	*/
void ReDeModbus(void)
{
	if(g_Recieve_Flag == 1)
	{

		HAL_GPIO_ClearPin(PA,(1<<0));      // Receiving Mode.............
	}
	else if(g_Recieve_Flag == 0)
	 {
		HAL_GPIO_SetPin(PA,(1<<0));      //Transmitting Mode......
	 }
	 
	  // If transmission is complete and the specified delay has elapsed,
		// reset flags and clear communication buffers to prepare for the next Modbus frame.
	 
}

/**
 * @brief Initiates Modbus data transmission over UART.
 *
 * This function sets the system to transmission mode and sends the data stored
 * in the Modbus transmission buffer using non-blocking UART communication.
 * It also updates the transmission buffer counter for tracking purposes.
 *
 * @note This function is typically called by the Modbus state machine after
 *       preparing a valid response or acknowledgment frame.
*/

void TransmitData(void)
{
	g_Recieve_Flag = 0;     //Clears `Recieve_Flag` to disable receiving during transmission.
	HAL_UART_Transmit(UART_ID_1, (uint8_t *)data_logger.TRANSMISSION_BUFFER, TX_DATA_LEN, UART_IO_TYPE_NON_BLOCK);  //Calls `HAL_UART_Transmit()` to send the data via UART (non-blocking).
	data_logger.TRANSMISSION_BUFFER_LENGTH++;		  //Increments `TRANSMISSION_BUFFER_LENGTH` counter
}


