#ifndef __USER_APPLICATION_HOLDING_REGISTER_H_
#define __USER_APPLICATION_HOLDING_REGISTER_H_
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdarg.h>
#include <stdbool.h>
#include "Modbus_Comm.h"


typedef enum{
	NO_ERROR_CODE = 0,
	ILLEGAL_SLAVE_ADDRESS_ERROR_CODE = 1,
	ILLEGAL_FUNCTION_ERROR_CODE = 2,
	ILLEGAL_DATA_VALUE_ERROR_CODE = 3,
	ILLEGAL_DATA_ADDRESS_ERROR_CODE = 4,
}ERROR_CODE_t;

typedef struct{
	uint16_t CALCULATE_CRC_FUNCTION_ERROR;
	uint16_t CALCUALTE_CRC_SLAVE_ADDRESS_ERROR;
	uint16_t CALCULATE_CRC_DATA_VALE_ERROR;
	uint16_t CALCUALTE_CRC_DATA_ADDRESS_ERROR;
}ILLEGAL_CODE_CRC;

#endif
