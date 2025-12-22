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
#define INPUT_RUNHOUR_START_ADDR								   (0x0000EA04U)
#define INPUT_REMAININGLIFE_START_ADDR						 (0x0000EA08U)
#define HOLDING_NODEADDRESS_START_ADDR             (0x0000F000U)
#endif

