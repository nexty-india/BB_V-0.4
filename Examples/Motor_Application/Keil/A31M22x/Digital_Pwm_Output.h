#ifndef __DIGITAL_PWM_OUTPUT_H_
#define __DIGITAL_PWM_OUTPUT_H_


#include "a31m22x.h"
#include "a31m22x_scu.h"
#include "a31m22x_timer.h"

#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdarg.h>


#define DIGITAL_TIMER   0.0000016f

void DIGITAL_PWM(void);
void DIGITAL_PWM_INIT(void);
void DigitalOutput(void);

#endif




