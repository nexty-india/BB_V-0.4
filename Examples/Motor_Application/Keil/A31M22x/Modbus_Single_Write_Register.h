#ifndef _MODBUS_SINGLE_WRITE_REGISTER_H_
#define _MODBUS_SINGLE_WRITE_REGISTER_H_
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdarg.h>
#include <stdbool.h>


typedef struct{
	uint16_t SINGLE_R_START_ADDRESS;
	uint16_t SINGLE_R_FUNCTION_CODE;
	uint16_t SINGLE_R_SLAVE_ID_CHECK;
	uint16_t SINGLE_R_BYTE_COUNT;
	uint16_t SINGLE_R_RECEIVED_CRC;
	uint16_t SINGLE_R_QUANTITY_VALUE;
	uint16_t SINGLE_R_CALCULATED_CRC;
	uint16_t SINGLE_R_CALCULATE_CRC_CHECK;
}SINGLE_REGISTER_WRITE_TX_DATA;

bool MODBUS_SINGLE_REGISTER_DATA(void);
bool SINGLE_REGISTER_TXN(void);

#endif
