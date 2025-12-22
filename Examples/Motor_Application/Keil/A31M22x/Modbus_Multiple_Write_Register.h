#ifndef _MODBUS_MULTIPLE_WRITE_REGISTER_H_
#define _MODBUS_MULTIPLE_WRITE_REGISTER_H_


#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdarg.h>
#include <stdbool.h>






typedef struct{
	uint16_t MULTY_START_ADDRESS;
	uint16_t MULTY_FUNCTION_CODE;
	uint16_t MULTY_SLAVE_ID_CHECK;
	uint16_t MULTY_BYTE_COUNT;
	uint16_t MULTY_RECEIVED_CRC;
	uint16_t MULTY_QUANTITY_VALUE;
	uint16_t MULTY_CALCULATED_CRC;
}MULTIPLE_WRITE_TX_DATA;



bool MODBUS_MULTIPLE_WRITE_REGSITER(void);
#endif
