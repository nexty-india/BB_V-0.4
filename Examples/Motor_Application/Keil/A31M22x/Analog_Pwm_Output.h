#ifndef __ANALOG_PWM_OUTPUT_H_
#define __ANALOG_PWM_OUTPUT_H_



#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdarg.h>


#include "a31m22x_mpwm.h"
#include "a31m22x.h"
#include "a31m22x_scu.h"



void ANALOG_PWM_INIT(void);
void Set_duty_period_Analog_PWM(void);

#endif



