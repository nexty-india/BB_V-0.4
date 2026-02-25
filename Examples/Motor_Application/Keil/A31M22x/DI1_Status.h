#ifndef _DI1_STATUS_H_
#define _DI1_STATUS_H_

#include "A31M22x_pcu.h"
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdarg.h>
#include <stdbool.h>

extern bool g_Motor_Status,g_FireEnableMode;
  extern bool  di1_pressed;
 bool DI1_ENABLE(void);
//static void DI1_CHECK_STATUS(void);
 int DI1_MOTOR_STATUS(void);

void MODE_SELECTION(void)  ;
bool DI2_ENABLE(void);
void FIRE_STATUS(void);
#endif
