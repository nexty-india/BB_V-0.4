#ifndef _DEFAULT_VALUES_H_
#define _DEFAULT_VALUES_H_



#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdarg.h>
#include "Define.h"
#include <stdbool.h>
#include <stdint.h>

///* Symbol exported from flash_params.c */
//extern const uint16_t FLASH_SEVEN;

///* Convenience macro for direct address access (if needed) */
//#define FLASH_SEVEN_ADDR ((const uint16_t *)0x0000FE00U)

#define INPUT_REG_MIN_START_ADDR  					       (0x0000FE00U)   
#define INPUT_REG_MAX_START_ADDR  					       (0x0000FC00U) 
#define HOLDING_REG_MIN_START_ADDR  				       (0x0000F800U) 
#define HOLDING_REG_MAX_START_ADDR  			         (0x0000F400U) 
#define HOLDING_REG_DEFAULT_START_ADDR  					 (0x0000F000U) 
#define HOLDING_REG_ACTUAL_START_ADDR       			 (0x0000EC00U)
#define HOLDING_REG_FLASH_CONTROL_START_ADDR       (0x0000EA00U)
#define RUNNING_SECOND_START_ADDR								   (0x0000E800U)
#define RUNNING_MINUTE_START_ADDR									 (RUNNING_SECOND_START_ADDR + 8U)
#define RUNNING_HOUR_START_ADDR										 (RUNNING_MINUTE_START_ADDR + 8U)
#define INPUT_REMAININGLIFE_START_ADDR						 (0x0000F2D8U)
#define HOLDING_NODEADDRESS_START_ADDR             (0x0000E400U)
#define FILTER_SECOND_START_ADDR                   (0x0000E200U)
#define FILTER_MINUTE_START_ADDR                   (FILTER_SECOND_START_ADDR + 8U)
#define FILTER_HOUR_START_ADDR                     (FILTER_MINUTE_START_ADDR + 8U)
#define REAMINING_SECOND_START_ADDR								 (0x0000E000U)
#define REAMINING_MINUTE_START_ADDR                (REAMINING_SECOND_START_ADDR + 8U)
#define REAMINING_HOUR_START_ADDR                  (REAMINING_MINUTE_START_ADDR + 8U)
#define HOLDING_REG_ACTUAL_START_ADDR_1       	   (0x0000DC00U)
#define HOLDING_REG_DEFAULT_START_ADDR_LOW         (0x0000D800U)
#endif

