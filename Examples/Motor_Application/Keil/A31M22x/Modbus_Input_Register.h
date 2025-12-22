#ifndef _MODBUS_INPUT_REGISTER_H_
#define _MODBUS_INPUT_REGISTER_H_
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdarg.h>
#include <stdbool.h>


typedef struct{
	uint16_t INPUT_START_ADDRESS;
	uint16_t INPUT_FUNCTION_CODE;
	uint16_t INPUT_SLAVE_ID_CHECK;
	uint16_t INPUT_QUANTITY_VALUE;
	uint16_t INPUT_BYTE_COUNT;
	uint16_t INPUT_RECEIVED_CRC;
	uint16_t INPUT_CALCULATED_CRC;
	uint16_t INPUT_CALCULATE_CRC_TXN;
}INPUT_TX_DATA;


#endif

