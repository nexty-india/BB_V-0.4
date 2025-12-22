#include "user_uart.h"

#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdarg.h>


//LOGGER_t data_logger;

//void uart_irq_handler(uint32_t event, void *context)
//{
//	static volatile uint64_t uart_receive_idle_time = 0;
//	if(event & UART_EVENT_RECEIVE_DONE)
//	{
//		// Do Something in case of data received over UART
//		HAL_UART_Receive(UART_ID_1, (uint8_t *)&data_logger.RECEPTION_BUFFER, 1, UART_IO_TYPE_NON_BLOCK);
//		//HAL_UART_Transmit(UART_ID_1, (uint8_t *)&data_logger.RECEPTION_BUFFER, 1, UART_IO_TYPE_NON_BLOCK);
///********/
//		if(get_system_time_ms() > uart_receive_idle_time + 50)
//		{
//			data_logger.TOTAL_BYTES_RECEIVED = 0x00;
//		}
//		else{
//			data_logger.TOTAL_BYTES_RECEIVED++;
//		}
//		uart_receive_idle_time = get_system_time_ms();
//		data_logger.BUFFER[data_logger.TOTAL_BYTES_RECEIVED] = data_logger.RECEPTION_BUFFER;
//		
//		if(data_logger.TOTAL_BYTES_RECEIVED >= UART_PACKET_SIZE-1)
//		{
//			data_logger.DATA_RECEIVED_FLAG = true;
//		}
//		logger_data_decode();
///****/
//	}
//	else if(event & UART_EVENT_TRANSMIT_DONE)
//	{
//		// Do something in case of data trasnmitted over UART
//		////data_logger.LOGGER_TRANSMISSION_STATE = LOGGER_TRANSMISSION_STATE_IDLE;
//		//HAL_UART_Transmit(UART_ID_1, (uint8_t *)data_logger.TRANSMISSION_BUFFER, strlen(data_logger.TRANSMISSION_BUFFER), UART_IO_TYPE_NON_BLOCK);
//	}
//}


//void MDL_UARTn_Init(void)
//{
//	struct uart_cfg cfg;
//	
//	cfg.baudrate = 115200;
//	cfg.data_bit = UART_DATA_BIT_8;
//	cfg.parity_bit = UART_PARITY_BIT_NONE;
//	cfg.stop_bit = UART_STOP_BIT_1;
//	cfg.irq_prio = 5;	
//	HAL_UART_Init(UART_ID_1, &cfg, uart_irq_handler, NULL);
//	
//	HAL_UART_Receive(UART_ID_1, (uint8_t *)&data_logger.RECEPTION_BUFFER, 1, UART_IO_TYPE_NON_BLOCK);
//}


void init_logging(void)
{
//	erase_log_buffer();
//	debug_log("Logger Initialized V 1.01 29_01_2024");
}



void erase_log_buffer(void)
{
//	memset(data_logger.TRANSMISSION_BUFFER, (uint8_t)'\0', LOGGER_BUFFER_SIZE);
//	data_logger.TRANSMISSION_BUFFER_LENGTH = 0;
}


void debug_log(const char *fmt, ...)
{
//	uint64_t current_time;
//	
//	va_list va;
//	va_start(va, fmt);
//	//current_time = get_system_time_ms();
//	if(data_logger.TRANSMISSION_BUFFER_LENGTH > 0)
//	{
//		sprintf (data_logger.TRANSMISSION_BUFFER + strlen(data_logger.TRANSMISSION_BUFFER) ,"\nT = %10" PRIu64 " : ", current_time);
//		vsprintf (data_logger.TRANSMISSION_BUFFER + strlen(data_logger.TRANSMISSION_BUFFER), fmt, va);
//	}
//	else
//	{
//		sprintf(data_logger.TRANSMISSION_BUFFER ,"\nT = %10" PRIu64 " : ", current_time);
//		vsprintf(data_logger.TRANSMISSION_BUFFER + strlen(data_logger.TRANSMISSION_BUFFER), fmt, va);
//	}
//	va_end(va);
//	
//	data_logger.TRANSMISSION_BUFFER_LENGTH = strlen(data_logger.TRANSMISSION_BUFFER);
}


void print_log(void)
{
//	if(data_logger.LOGGER_TRANSMISSION_STATE == LOGGER_TRANSMISSION_STATE_IDLE && data_logger.TRANSMISSION_BUFFER_LENGTH != 0)
//	{
//		data_logger.LOGGER_TRANSMISSION_STATE = LOGGER_TRAMSMISSION_STATE_TRANSMITTING;
//		HAL_UART_Transmit(UART_ID_1, (uint8_t *)data_logger.TRANSMISSION_BUFFER, strlen(data_logger.TRANSMISSION_BUFFER), UART_IO_TYPE_NON_BLOCK);
//		data_logger.TRANSMISSION_BUFFER_LENGTH = 0;
//	}
}

void logger_data_decode(void)
{
//	uint8_t checksum = 0, received_checksum = 0, i = 0;
//	uint8_t External_Rpm;
//	bool ack = 0;
//	if(data_logger.DATA_RECEIVED_FLAG != true)
//		return;
//	else
//	{
//		data_logger.DATA_RECEIVED_FLAG = false;
//		if(data_logger.BUFFER[0] == START_BYTE_1  && data_logger.BUFFER[1] == START_BYTE_2 && data_logger.BUFFER[2] == ack )
//		{
//			if(data_logger.BUFFER[6] == END_BYTE_1 && data_logger.BUFFER[7] == END_BYTE_2)
//			{
//				received_checksum = data_logger.BUFFER[UART_PACKET_SIZE - 3];
//				data_logger.BUFFER[UART_PACKET_SIZE - 3] = 0;
//				for(i = 0; i < UART_PACKET_SIZE; i++)
//				{
//					checksum += data_logger.BUFFER[i];
//				}
//				if(checksum != received_checksum)
//					return;
//				else{
//					External_Rpm = (data_logger.BUFFER[3]);
//				//  MAL_External_RPM = ((data_logger.BUFFER[3]*Parameter[13])/250);
//					data_logger.TRANSMISSION_BUFFER[0] = START_BYTE_1;
//					data_logger.TRANSMISSION_BUFFER[1] = START_BYTE_2;
//					data_logger.TRANSMISSION_BUFFER[2] = 1;
//					data_logger.TRANSMISSION_BUFFER[3] = External_Rpm;
//				//	data_logger.TRANSMISSION_BUFFER[4] = MAL_FaultStatus;
//					data_logger.TRANSMISSION_BUFFER[5] = 0;
//					data_logger.TRANSMISSION_BUFFER[6] = END_BYTE_1;
//					data_logger.TRANSMISSION_BUFFER[7] = END_BYTE_2;
//					checksum = 0;
//					for(i = 0; i < UART_PACKET_SIZE; i++)
//					{
//						checksum += data_logger.TRANSMISSION_BUFFER[i];
//					}
//					data_logger.TRANSMISSION_BUFFER[5] = checksum;
//					HAL_UART_Transmit(UART_ID_1, (uint8_t *)&data_logger.TRANSMISSION_BUFFER, 8, UART_IO_TYPE_NON_BLOCK);
//			}
//		}
//		}
//		else
//			return;
//	}
}
