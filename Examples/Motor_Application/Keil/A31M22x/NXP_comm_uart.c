#include "NXP_Comm_uart.h"

UART_COMM_PARA_t uart_comm;
TRANSMIT_PARA_t transmit_para;
UART__FORMAT uart_format;
Modbus_Parameter modbus_parameter;
MOTOR_UART_t Motor_Uart;
uint16_t g_Transmit_Complete,g_Transmit_Timer;
uint16_t g_Idle_line_counter;
uint8_t g_Index_Parameter_counter;
/**
 * @brief UART0 interrupt handler
 *
 * Handles both receive and transmit events in non-blocking mode.
 */
void uart_irq_handler_uart0(uint32_t event, void *context)
{
	if(event & UART_EVENT_RECEIVE_DONE)               // Receive interrupt 
	{
		g_Idle_line_counter = 0;
		HAL_UART_Receive(UART_ID_0,(uint8_t *)&uart_comm.RECIEVED_DATA_BUFFER,1,UART_IO_TYPE_NON_BLOCK);
		uart_comm.RECEIVED_FRAME[uart_comm.RECEIVED_INDEX] = uart_comm.RECIEVED_DATA_BUFFER;
		uart_comm.RECEIVED_INDEX++;
	}
	else if(event & UART_EVENT_TRANSMIT_DONE)					// Transmit interrrupt
	{ 
		g_Transmit_Complete = 1;
	}
}



/**
 * @brief Motor UART communication state machine
 *
 * Handles transmit and receive sequences for motor parameters
 * using non-blocking UART communication.
 */
void MotorUartStatemachine(void)
{
	switch(Motor_Uart)
	{
		
				// =======================
        // Transmit parameter frame
        // =======================
		case MOTOR_TRANSMIT_STATE:
			TransmitParameter();
			Motor_Uart = MOTOR_DATA_TRAMITTED_COMPLTETED;
				break;
		
				// =======================
        // Wait after transmission for completion
        // =======================
			case MOTOR_DATA_TRAMITTED_COMPLTETED:
			if((g_Transmit_Complete == 1)&&(g_Transmit_Timer++ > 12)) 
			{
				g_Transmit_Complete = 0;
				g_Transmit_Timer = 0;
				Motor_Uart = MOTOR_DATA_RECIEVING;
			}
			break;
		
		 // =======================
        // Receive data from UART
        // =======================
		case MOTOR_DATA_RECIEVING:
			
		if((uart_comm.RECEIVED_INDEX > 0)&&(g_Idle_line_counter < TIME_TO_TRANSMIT_MS))
		{
			g_Idle_line_counter++;
		}
		else if(uart_comm.RECEIVED_INDEX >= 7)
		{
			uart_comm.RECEIVED_INDEX = 0;
			Motor_Uart = MOTOR_RECIVED_COMPLETED;
		}
		else{
			uart_comm.RECEIVED_INDEX = 0;
			g_Idle_line_counter = 0;
			Motor_Uart = MOTOR_TRANSMIT_STATE;
		}
			break;
		
		 // =======================
        // Process received frame
        // =======================
		case MOTOR_RECIVED_COMPLETED:
		ReceiveParameter();
		Motor_Uart = MOTOR_TRANSMIT_STATE;
			break;

	}
}






/**
	* @brief 	Initialization of Uart0 for Communication with NXP Controller
	* @param  
	* @retval 
	*/
void UserUart0init(void)
{
	struct uart_cfg cfg_1;
	 
	cfg_1.baudrate = 9600;                               	//set baut rate 
	cfg_1.data_bit = UART_DATA_BIT_8;											 	//set data bit
	cfg_1.parity_bit = UART_PARITY_BIT_NONE;								// Set Pairty Bit
	cfg_1.stop_bit = UART_STOP_BIT_1;												//set stop bit
	cfg_1.irq_prio = 2;	 																		//intrrupt priorty
	HAL_UART_SetIRQ(UART_ID_0, UART_IRQ_TX_EMPTY, 1);									
	HAL_UART_SetIRQ(UART_ID_0, UART_IRQ_RX_AVAIL, 1);
	HAL_UART_Init(UART_ID_0, &cfg_1, uart_irq_handler_uart0, NULL);         //initialize uart 0 init
	HAL_UART_Receive(UART_ID_0,(uint8_t *)&uart_comm.RECIEVED_DATA_BUFFER,1,UART_IO_TYPE_NON_BLOCK); //receive init function initialize
}

uint8_t calculate_checksum(const uint8_t *data, uint8_t length)
{
	
//	uint8_t i = 0;
//	uint16_t crc = 0;
//	
//	// Check if the data is valid or not
//	if((data == NULL) || (length == 0))
//		return 0;
//	
//	else
//	{
//		/**
//			*	We need to calculate the CRC till the complete data is checked
//			*	We will perform division and then XOR the value one by one
//			*	The remainder we get is the CRC of the data input
//			* If the LSB is 0 then the input will be shifted right till 1 is encountered
//			* If LSB is 1 then it is shifted right by 1 and XORed with the seed_poly
//			*/
//		while(length--)
//		{
//			crc ^= *data++;
//			for(i = 0; i < 8; i++)
//				crc = crc & 1 ? (crc >> 1) ^ seed_poly : crc >> 1;
//		}
//		return crc;	
//	}

	uint8_t calculate_checksum = 0;
	if((data == NULL) || (length == 0))
		return 0;
	
	else
	{
		while(length--)
		{
			calculate_checksum += *data++;
		}
		return calculate_checksum & 0xff;
	}
}


/**
 * @brief Prepare and transmit UART frame for Modbus parameters
 *
 * This function sets up the UART transmit frame based on the current
 * index parameter counter (`g_Index_Parameter_counter`) and sends it
 * over UART. Supports both read and write frames.
 */
void TransmitParameter(void)
{
volatile	uint8_t checksum_temp=0;
	// Initialize start and end bytes
		uart_comm.TRANSMIT_DATA[start_add] = START_BYTE; 
		uart_comm.TRANSMIT_DATA[end_add] = END_BYTE;
		checksum_temp = 0;
		uart_comm.TRANSMIT_DATA[request_bit_add]=g_Index_Parameter_counter;
		switch(g_Index_Parameter_counter)                    // Determine read/write and data values based on index
		{
			case UART_FRAME_INDEX_READ_SW_VERSION:
			uart_comm.TRANSMIT_DATA[write_read_add] =  READ_BYTE;
			uart_comm.TRANSMIT_DATA[data_high_bit_add]=0x00;
			uart_comm.TRANSMIT_DATA[data_low_bit_add]= 0x00;
			
			break;

			case UART_FRAME_INDEX_READ_DEVICE_ID:
			uart_comm.TRANSMIT_DATA[write_read_add] =  READ_BYTE;
			uart_comm.TRANSMIT_DATA[data_high_bit_add]=0x00;
			uart_comm.TRANSMIT_DATA[data_low_bit_add]= 0x00;
			break;
				
			case UART_FRAME_INDEX_READ_AC_VOLTAGE:
			uart_comm.TRANSMIT_DATA[write_read_add] =  READ_BYTE;
			uart_comm.TRANSMIT_DATA[data_high_bit_add]=0x00;
			uart_comm.TRANSMIT_DATA[data_low_bit_add]= 0x00;
			break;
							
			case UART_FRAME_INDEX_READ_MOTOR_CURRENT:
			uart_comm.TRANSMIT_DATA[write_read_add] =  READ_BYTE;
			uart_comm.TRANSMIT_DATA[data_high_bit_add]=0x00;
			uart_comm.TRANSMIT_DATA[data_low_bit_add]= 0x00;
			break;
										
			case UART_FRAME_INDEX_READ_DC_VOLTAGE:
			uart_comm.TRANSMIT_DATA[write_read_add] =  READ_BYTE;
			uart_comm.TRANSMIT_DATA[data_high_bit_add]=0x00;
			uart_comm.TRANSMIT_DATA[data_low_bit_add]= 0x00;
			break;
														
														
			case UART_FRAME_INDEX_READ_DC_CURRENT:
			uart_comm.TRANSMIT_DATA[write_read_add] =  READ_BYTE;
			uart_comm.TRANSMIT_DATA[data_high_bit_add]=0x00;
			uart_comm.TRANSMIT_DATA[data_low_bit_add]= 0x00;
			break;
																			
			case UART_FRAME_INDEX_READ_ACTUAL_SPEED:
			uart_comm.TRANSMIT_DATA[write_read_add] =  READ_BYTE;
			uart_comm.TRANSMIT_DATA[data_high_bit_add]=0x00;
			uart_comm.TRANSMIT_DATA[data_low_bit_add]= 0x00;
			break;
			
			
			case UART_FRAME_INDEX_READ_IPM_TEMPERATURE:
			uart_comm.TRANSMIT_DATA[write_read_add] =  READ_BYTE;
			uart_comm.TRANSMIT_DATA[data_high_bit_add]=0x00;
			uart_comm.TRANSMIT_DATA[data_low_bit_add]= 0x00;
			break;
			
			
			case UART_FRAME_INDEX_READ_MOTOR_TEMPERATURE:
			uart_comm.TRANSMIT_DATA[write_read_add] =  READ_BYTE;
			uart_comm.TRANSMIT_DATA[data_high_bit_add]=0x00;
			uart_comm.TRANSMIT_DATA[data_low_bit_add]= 0x00;
			break;
			
//			case UART_FRAME_INDEX_READ_FAULT_STATUS:
//			uart_comm.TRANSMIT_DATA[write_read_add] =  READ_BYTE;
//			uart_comm.TRANSMIT_DATA[data_high_bit_add]=0x00;
//			uart_comm.TRANSMIT_DATA[data_low_bit_add]= 0x00;
//			break;
				
			case UART_FRAME_INDEX_READ_KW:
			uart_comm.TRANSMIT_DATA[write_read_add] =  READ_BYTE;
			uart_comm.TRANSMIT_DATA[data_high_bit_add]=0x00;
			uart_comm.TRANSMIT_DATA[data_low_bit_add]= 0x00;
			break;
			
			case UART_FRAME_INDEX_READ_KWH:
			uart_comm.TRANSMIT_DATA[write_read_add] =  READ_BYTE;
			uart_comm.TRANSMIT_DATA[data_high_bit_add]=0x00;
			uart_comm.TRANSMIT_DATA[data_low_bit_add]= 0x00;
			break;
			
			case UART_FRAME_INDEX_READ_TORQUE:
			uart_comm.TRANSMIT_DATA[write_read_add] =  READ_BYTE;
			uart_comm.TRANSMIT_DATA[data_high_bit_add]=0x00;
			uart_comm.TRANSMIT_DATA[data_low_bit_add]= 0x00;
			break;
			
			case UART_FRAME_INDEX_READ_FAULT_STATUS:
				uart_comm.TRANSMIT_DATA[data_high_bit_add]= modbus_parameter.MODBUS_FAULT_STATUS>>8;
			  uart_comm.TRANSMIT_DATA[data_low_bit_add]= modbus_parameter.MODBUS_FAULT_STATUS&0xFF;
				uart_comm.TRANSMIT_DATA[write_read_add] =  WRITE_BYTE;	
				break;
			
			case UART_FRAME_INDEX_SET_MOTOR_STATUS:
				uart_comm.TRANSMIT_DATA[data_high_bit_add]= modbus_parameter.MODBUS_MOTOR_STATUS>>8;
			  uart_comm.TRANSMIT_DATA[data_low_bit_add]= modbus_parameter.MODBUS_MOTOR_STATUS&0xFF;
			uart_comm.TRANSMIT_DATA[write_read_add] =  WRITE_BYTE;	
			break;
			
			case UART_FRAME_INDEX_WRITE_FAN_TARGET_SPEED:
				uart_comm.TRANSMIT_DATA[data_high_bit_add]= modbus_parameter.MODBUS_TARGET_SPEED>>8;
			  uart_comm.TRANSMIT_DATA[data_low_bit_add]= modbus_parameter.MODBUS_TARGET_SPEED&0xFF;
				uart_comm.TRANSMIT_DATA[write_read_add] =  WRITE_BYTE;	
			break;
			
			case UART_FRAME_INDEX_LED_STATUS:
			uart_comm.TRANSMIT_DATA[data_high_bit_add]= modbus_parameter.LED_STATUS>>8;
			uart_comm.TRANSMIT_DATA[data_low_bit_add]= modbus_parameter.LED_STATUS&0xFF;
			uart_comm.TRANSMIT_DATA[write_read_add] =  WRITE_BYTE;	
			break;
			
				case UART_FRAME_INDEX_FAULT_CLEAR_STATUS:
			uart_comm.TRANSMIT_DATA[data_high_bit_add]= modbus_parameter.FAULT_CLEAR_STATUS>>8;
			uart_comm.TRANSMIT_DATA[data_low_bit_add]= modbus_parameter.FAULT_CLEAR_STATUS&0xFF;
			uart_comm.TRANSMIT_DATA[write_read_add] =  WRITE_BYTE;	
			break;
			
			case UART_FRAME_INDEX_FAULT_FREQUENCY:
			uart_comm.TRANSMIT_DATA[write_read_add] =  READ_BYTE;
			uart_comm.TRANSMIT_DATA[data_high_bit_add]=0x00;
			uart_comm.TRANSMIT_DATA[data_low_bit_add]= 0x00;
			break;
				
				
				
		default :
			g_Index_Parameter_counter = 255;
			break;
		}
		checksum_temp = calculate_checksum(uart_comm.TRANSMIT_DATA,5);
		uart_comm.TRANSMIT_DATA[crc_add] = checksum_temp;
		
		HAL_UART_Transmit(UART_ID_0, (uint8_t *)uart_comm.TRANSMIT_DATA, 7, UART_IO_TYPE_NON_BLOCK);
		g_Index_Parameter_counter++;

}

/**
 * @brief Process received UART frame and update Modbus parameters
 *
 * This function validates the received UART frame using start/end bytes
 * and checksum, then updates the corresponding Modbus parameters based
 * on the request type.
 */
void ReceiveParameter(void)
{
    uint8_t Calculate_Checksum = 0;
    uint16_t RECIVED_DATA = 0;

    // Calculate simple checksum (sum of relevant frame bytes, mask with 0xFF)
    Calculate_Checksum = (
        (0xFF & (uart_comm.RECEIVED_FRAME[start_add] +
                 uart_comm.RECEIVED_FRAME[write_read_add] +
                 uart_comm.RECEIVED_FRAME[data_high_bit_add] +
                 uart_comm.RECEIVED_FRAME[data_low_bit_add] +
                 uart_comm.RECEIVED_FRAME[request_bit_add]))
    );

    // Validate start byte, end byte, and write/read address
    if ((uart_comm.RECEIVED_FRAME[start_add] == START_BYTE) &&
        (uart_comm.RECEIVED_FRAME[end_add] == END_BYTE) &&
        (uart_comm.RECEIVED_FRAME[write_read_add] == 0x85))
    {
        // Validate checksum
        if (uart_comm.RECEIVED_FRAME[crc_add] == Calculate_Checksum)
        {
            // Reset checksum variable
            Calculate_Checksum = 0;

            // Determine action based on request type
            switch (uart_comm.RECEIVED_FRAME[request_bit_add])
            {
                case UART_FRAME_INDEX_READ_SW_VERSION:
                    RECIVED_DATA = (uart_comm.RECEIVED_FRAME[data_high_bit_add] << 8 |
                                    uart_comm.RECEIVED_FRAME[data_low_bit_add]);
                    modbus_parameter.MODBUS_MOTOR_SW_VERSION = RECIVED_DATA;
                    break;

                case UART_FRAME_INDEX_READ_DEVICE_ID:
                    RECIVED_DATA = (uart_comm.RECEIVED_FRAME[data_high_bit_add] << 8 |
                                    uart_comm.RECEIVED_FRAME[data_low_bit_add]);
                    modbus_parameter.MODBUS_DEVICE_ID = RECIVED_DATA;
                    break;

                case UART_FRAME_INDEX_READ_AC_VOLTAGE:
                    RECIVED_DATA = (uart_comm.RECEIVED_FRAME[data_high_bit_add] << 8 |
                                    uart_comm.RECEIVED_FRAME[data_low_bit_add]);
                    modbus_parameter.MODBUS_READ_AC_VOLTAGE = RECIVED_DATA;
                    break;

                case UART_FRAME_INDEX_READ_MOTOR_CURRENT:
                    RECIVED_DATA = (uart_comm.RECEIVED_FRAME[data_high_bit_add] << 8 |
                                    uart_comm.RECEIVED_FRAME[data_low_bit_add]);
                    modbus_parameter.MODBUS_READ_MOTOR_CURRENT = RECIVED_DATA;
                    break;

                case UART_FRAME_INDEX_READ_DC_VOLTAGE:
                    RECIVED_DATA = (uart_comm.RECEIVED_FRAME[data_high_bit_add] << 8 |
                                    uart_comm.RECEIVED_FRAME[data_low_bit_add]);
                    modbus_parameter.MODBUS_READ_DC_VOLTAGE = RECIVED_DATA;
                    break;

                case UART_FRAME_INDEX_READ_DC_CURRENT:
                    RECIVED_DATA = (uart_comm.RECEIVED_FRAME[data_high_bit_add] << 8 |
                                    uart_comm.RECEIVED_FRAME[data_low_bit_add]);
                    modbus_parameter.MODBUS_READ_DC_CURRENT = RECIVED_DATA;
                    break;

                case UART_FRAME_INDEX_WRITE_FAN_TARGET_SPEED:
                    RECIVED_DATA = (uart_comm.RECEIVED_FRAME[data_high_bit_add] << 8 |
                                    uart_comm.RECEIVED_FRAME[data_low_bit_add]);
                    modbus_parameter.MODBUS_TARGET_SPEED = RECIVED_DATA;
                    break;

                case UART_FRAME_INDEX_READ_ACTUAL_SPEED:
                    RECIVED_DATA = (uart_comm.RECEIVED_FRAME[data_high_bit_add] << 8 |
                                    uart_comm.RECEIVED_FRAME[data_low_bit_add]);
                    modbus_parameter.MODBUS_ACTUAL_SPEED = RECIVED_DATA;
                    break;

                case UART_FRAME_INDEX_READ_IPM_TEMPERATURE:
                    RECIVED_DATA = (uart_comm.RECEIVED_FRAME[data_high_bit_add] << 8 |
                                    uart_comm.RECEIVED_FRAME[data_low_bit_add]);
                    modbus_parameter.MODBUS_IPM_TEMPERATURE = RECIVED_DATA;
                    break;

                case UART_FRAME_INDEX_READ_MOTOR_TEMPERATURE:
                    RECIVED_DATA = (uart_comm.RECEIVED_FRAME[data_high_bit_add] << 8 |
                                    uart_comm.RECEIVED_FRAME[data_low_bit_add]);
                    modbus_parameter.MODBUS_MOTOR_TEMPERATURE = RECIVED_DATA;
                    break;

                case UART_FRAME_INDEX_READ_FAULT_STATUS:
                    RECIVED_DATA = (uart_comm.RECEIVED_FRAME[data_high_bit_add] << 8 |
                                    uart_comm.RECEIVED_FRAME[data_low_bit_add]);
                    modbus_parameter.MODBUS_FAULT_STATUS = RECIVED_DATA;
                    break;

                case UART_FRAME_INDEX_SET_MOTOR_STATUS:
                    RECIVED_DATA = (uart_comm.RECEIVED_FRAME[data_high_bit_add] << 8 |
                                    uart_comm.RECEIVED_FRAME[data_low_bit_add]);
                    modbus_parameter.MODBUS_MOTOR_STATUS = RECIVED_DATA;
                    break;

                case UART_FRAME_INDEX_READ_KW:
                    RECIVED_DATA = (uart_comm.RECEIVED_FRAME[data_high_bit_add] << 8 |
                                    uart_comm.RECEIVED_FRAME[data_low_bit_add]);
                    modbus_parameter.KW = RECIVED_DATA;
                    break;

                case UART_FRAME_INDEX_READ_KWH:
                    RECIVED_DATA = (uart_comm.RECEIVED_FRAME[data_high_bit_add] << 8 |
                                    uart_comm.RECEIVED_FRAME[data_low_bit_add]);
                    modbus_parameter.KWH = RECIVED_DATA;
                    break;

                case UART_FRAME_INDEX_READ_TORQUE:
                    RECIVED_DATA = (uart_comm.RECEIVED_FRAME[data_high_bit_add] << 8 |
                                    uart_comm.RECEIVED_FRAME[data_low_bit_add]);
                    modbus_parameter.TORQUE = RECIVED_DATA;
                    break;

                case UART_FRAME_INDEX_FAULT_CLEAR_STATUS:
                    RECIVED_DATA = (uart_comm.RECEIVED_FRAME[data_high_bit_add] << 8 |
                                    uart_comm.RECEIVED_FRAME[data_low_bit_add]);
                    modbus_parameter.FAULT_CLEAR_STATUS = RECIVED_DATA;
                    break;

                case UART_FRAME_INDEX_FAULT_FREQUENCY:
                    RECIVED_DATA = (uart_comm.RECEIVED_FRAME[data_high_bit_add] << 8 |
                                    uart_comm.RECEIVED_FRAME[data_low_bit_add]);
                    modbus_parameter.OPERTING_FREQUENCY = RECIVED_DATA;
                    break;

                default:
                    // Optional: handle unknown request codes
                    break;
            }
        }
    }
}

