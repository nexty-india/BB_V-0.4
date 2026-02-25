#ifndef __NXP_COMM_UART_H_
#define __NXP_COMM_UART_H_

#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdarg.h>
#include "a31m22x_uart.h"
#include "user_timer.h"
#define START_BYTE  0xAA
#define END_BYTE    0xFF
#define WRITE_BYTE  0x06
#define READ_BYTE   0x05
#define UART_COMM   7


#define TOTAL_BYTE								10
#define BUFFER_SIZE  							4
#define BAUD_RATE_UART    				9600
#define TIME_TO_TRANSMIT_1_BYTE 	(10/BAUD_RATE_UART)
#define TIME_TO_TRANSMIT_MS  			(5000 *(TOTAL_BYTE + BUFFER_SIZE)/BAUD_RATE_UART)
#define TIME_TO_TRANSMIT_10BYTE  	(TIME_TO_TRANSMIT_1_BYTE * 10 *1000)
#define WAIT_TIME 								(TIME_TO_TRANSMIT_10BYTE + 2)

#define SW_VERSION_MIN			0
#define SW_VERSION_MAX			65535

#define DEVICE_ID_MIN 			0
#define DEVICE_ID_MAX    65535

#define AC_VOLTAGE_MIN  1
#define AC_VOLTAGE_MAX  1

#define MOTOR_CURRENT_MIN  0
#define MOTOR_CURRENT_MAX  24

#define DC_VOLTAGE_MIN  0
#define DC_VOLTAGE_MAX  778
  
#define DC_CURRENT_MIN  0
#define DC_CURRENT_MAX    24

#define ACTUAL_SPEED_MIN	0
#define ACTUAL_SPEED_MAX	10000

#define IPM_TEMPERATURE_MIN			0
#define IPM_TEMPERATURE_MAX			3553

#define MOTOR_TEMPERATURE_MIN	0
#define MOTOR_TEMPERATURE_MAX	320

#define MOTOR_STATUS_MIN	0
#define MOTOR_STATUS_MAX	2

#define READ_KW_MIN			0
#define READ_KW_MAX			6000

#define READ_KWH_MIN		0
#define READ_KWH_MAX		65535

#define READ_TORQUE_MIN		0	
#define READ_TORQUE_MAX		750

#define READ_LOAD_MIN		0
#define READ_LOAD_MAX		100

#define FAULT_STATUS_MIN 0
#define FAULT_STATUS_MAX 65535

#define LED_STATUS_MIN	0
#define LED_STATUS_MAX	2


#define FAULT_CLEAR_MIN		0
#define FAULT_CLEAR_MAX		2

typedef struct{
	uint8_t TRANSMIT_DATA[UART_COMM];
	uint8_t RECEIVED_FRAME[UART_COMM];
	uint8_t RECEIVED_INDEX;
	uint8_t RECEIVED_CHECKSUM;
	uint8_t RECIEVED_DATA_BUFFER;
	bool MOTOR_DATA_RECEIVED;
}UART_COMM_PARA_t;

typedef enum{
	MOTOR_TRANSMIT_STATE = 0,
	MOTOR_DATA_TRAMITTED_COMPLTETED,
	MOTOR_DATA_RECIEVING,
	MOTOR_RECIVED_COMPLETED,
}MOTOR_UART_t;





typedef enum{
	UART_FRAME_INDEX_READ_SW_VERSION          = 0x00,
	UART_FRAME_INDEX_READ_DEVICE_ID						= 0x01,           
	UART_FRAME_INDEX_READ_AC_VOLTAGE					= 0x02,          
	UART_FRAME_INDEX_READ_MOTOR_CURRENT				= 0x03,       
	UART_FRAME_INDEX_READ_DC_VOLTAGE					= 0x04,          
	UART_FRAME_INDEX_READ_DC_CURRENT					= 0x05,         
	UART_FRAME_INDEX_WRITE_FAN_TARGET_SPEED   = 0x06,   
	UART_FRAME_INDEX_READ_ACTUAL_SPEED				= 0x07,        
	UART_FRAME_INDEX_READ_IPM_TEMPERATURE			= 0x08,     
	UART_FRAME_INDEX_READ_MOTOR_TEMPERATURE   = 0x09,   
	UART_FRAME_INDEX_SET_MOTOR_STATUS					= 0x0A,    //10     
	UART_FRAME_INDEX_READ_FAULT_STATUS				= 0x0B,    //11    
	UART_FRAME_INDEX_READ_KW									= 0x0C,    //12              
	UART_FRAME_INDEX_READ_KWH									= 0x0D,    //13             
	UART_FRAME_INDEX_READ_TORQUE							= 0x0E,    //14          
  UART_FRAME_INDEX_LED_STATUS								=	0x0F,    //15
	UART_FRAME_INDEX_FAULT_CLEAR_STATUS       = 0x10,    //16
	UART_FRAME_INDEX_FAULT_FREQUENCY					= 0x11,    //17
	UART_FRAME_TOTAL_INDEX										= 0x12,    //18
}TRANSMIT_PARA_t;

typedef enum{
	start_add											= 0,
	write_read_add								= 1,
	request_bit_add								= 2,
	data_high_bit_add							= 3,
	data_low_bit_add							= 4,
	crc_add												= 5,
	end_add												= 6,	
}UART__FORMAT;



void MotorUartStatemachine(void);
void UserUart0init(void);
uint8_t calculate_checksum(const uint8_t *data, uint8_t length);
void TransmitParameter(void);
void ReceiveParameter(void);
#endif



