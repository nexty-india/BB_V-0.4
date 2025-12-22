/**
*/

#ifndef _USER_UART_H_
#define _USER_UART_H_

/*******************************************************************************
* Included File
*******************************************************************************/
#include "Define.h"
#include "user_timer.h"

/*******************************************************************************
* Public Macro
*******************************************************************************/

#define	LOGGER_BUFFER_SIZE	512
#define UART_PACKET_SIZE 8
#define START_BYTE_1		0xAA
#define START_BYTE_2		0x55
#define END_BYTE_1			0x0D
#define END_BYTE_2			0x0A


/*******************************************************************************
* Public Typedef
*******************************************************************************/

typedef enum
{
	LOGGER_TRANSMISSION_STATE_IDLE,
	LOGGER_TRAMSMISSION_STATE_TRANSMITTING,
}LOGGER_TRANSMISSION_STATE_t;

typedef enum
{
	LOGGER_RECEPTION_STATE_IDLE,
	LOGGER_RECEPTION_STATE_RECEIVING,
}LOGGER_RECEPTION_STATE_t;


typedef struct
{
	LOGGER_TRANSMISSION_STATE_t LOGGER_TRANSMISSION_STATE;
	LOGGER_RECEPTION_STATE_t LOGGER_RECEPTION_STATE;
	uint16_t TRANSMISSION_BUFFER_LENGTH;
	char TRANSMISSION_BUFFER[LOGGER_BUFFER_SIZE];
	uint16_t RECEPTION_BUFFER_LENGTH;
	uint8_t RECEPTION_BUFFER;
	
	
	uint8_t RX_Counter;
	uint8_t BUFFER[UART_PACKET_SIZE];
	uint8_t TOTAL_BYTES_RECEIVED;
	bool DATA_RECEIVED_FLAG;
}LOGGER_t;
/*******************************************************************************
* Exported Public Variable
*******************************************************************************/



/*******************************************************************************
* Exported Public Function
*******************************************************************************/

void init_logging(void);
void erase_log_buffer(void);
void debug_log(const char *fmt, ...);
void print_log(void);
void logger_data_decode(void);

#endif
