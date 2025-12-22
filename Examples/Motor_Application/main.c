/**
 *******************************************************************************
 * @file        main.c
 * @author      ABOV R&D Division
 * @brief       
 *
 * Copyright 2023 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

/*******************************************************************************
* Included File
*******************************************************************************/
#include "Define.h"
// Changed
#if defined(__DEF_A33M11x__)
#include "system_A33M11x.h"
#elif defined(__DEF_A34M41x__)
#include "system_A34M41x.h"
#elif defined(__DEF_AC30M1x64__)
#include "system_AC30M1x64.h"
#elif defined(__DEF_AC33Mx064__)
#include "system_AC33Mx064.h"
#elif defined(__DEF_AC33Mx128__)
#include "system_AC33Mx128.h"
#elif defined(__DEF_A31M22x__)
#include "A31M22x_system.h"
#include "A31M22x_initclock.h"
#endif

#include "Bharat_Bijleee.h"
#include "MotorDriverLayer.h"



#include "user_timer.h"
#include "user_adc.h"
#include "user_statemachine.h"
#include "DI1_Status.h"
#include "Fault_indication.h"
#include "user_Switch.h"
#include "NXP_comm_uart.h"
#include "Analog_Pwm_Output.h"
#include "Digital_Pwm_Output.h"
/*******************************************************************************
* Pre-processor Definition & Macro
*******************************************************************************/


/*******************************************************************************
* Private Typedef
*******************************************************************************/


/*******************************************************************************
* Private Variable
*******************************************************************************/


/*******************************************************************************
* Private Function Prototype
*******************************************************************************/


/*******************************************************************************
* Public Variable
*******************************************************************************/


/*******************************************************************************
* Public Function
********************************************************** *********************/
int main(void)
{
	__disable_irq();

	// Initialize System and Peripheral
	SystemInit();

	MDL_PCU_Init();
#if defined(__DEF_A33M11x__)
	//SystemCoreClockUpdate();
#elif defined(__DEF_A31M22x__)
	A31M22x_InitClock();
#else
	SCU_ClockInit();
#endif
	USER_ADC_Init();       //initialize adc .....
	USER_TIMER0_Init();    //initialize timer0 .....
	UserRs485init();     //initialize uart1 (rs485).....
	UserUart0init();     //initialize uart0 (comm with nxp controller)..
	USER_OPAMP_Init();     //initialize opmap for adc....
	MDL_WDT_Init();				//initialize watchdog timer....
	ANALOG_PWM_INIT();      //initialize analog_pwm_init....
	DIGITAL_PWM_INIT();    //initialize digital pwm init......
	
	
//	MDL_FRT_Init();
	
	__enable_irq();
	MAL_MainLoop();

	return (0);
}


/* --------------------------------- End Of File ------------------------------ */
