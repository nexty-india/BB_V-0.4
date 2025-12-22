#ifndef _MODBUS_HOLDING_REGISTER_H_
#define _MODBUS_HOLDING_REGISTER_H_
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdarg.h>
#include <stdbool.h>

#define HOLDING_START_DATA  3

typedef struct{



	uint16_t HOLDING_QUANTITY_VALUE;
	uint16_t HOLDING_BYTE_COUNT;
	uint16_t HOLDING_RECEIVED_CRC;
	uint16_t HOLDING_CALCULATED_CRC;
}HOLDING_TX_DATA;

extern uint16_t TX_DATA_LEN;
extern HOLDING_TX_DATA Holding_Tx_Data;
bool HOLDING_REG_AND_INPUT_REG_DATA(void);
void DUMMBY_DATA(void);
#endif
