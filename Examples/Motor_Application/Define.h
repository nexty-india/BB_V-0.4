/**
 *******************************************************************************
 * @file        Define.h
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


#ifndef _DEFINE_H_
#define _DEFINE_H_

/*******************************************************************************
* Included File
*******************************************************************************/
#include "aa_types.h"

#include "A31M22x_system.h"
#include "A31M22x_initclock.h"




#include "Bharat_Bijleee.h"



/*******************************************************************************
* Public Macro
*******************************************************************************/
#define ON							(1)
#define OFF							(0)
#define UP_SIDE						(1)
#define DOWN_SIDE					(0)

// Project Name
#define EV_COMPRESSOR				(ON)

// Function Configuration
#define USE_DAC_DEBUG				(OFF)

// Q Math
#define Q7							(128)
#define Q8							(256)
#define Q9							(512)
#define Q10							(1024)
#define Q11							(2048)
#define Q12							(4096)
#define Q13							(8192)
#define Q14							(16384)
#define Q15							(32768L)
#define Q16							(65536L)
#define Q17							(131072L)
#define Q18							(262144L)
#define Q19							(524288L)
#define Q20							(1048576L)
#define Q21							(2097152L)
#define Q22							(4194304L)

// SQRT
#define INV_SQRT3_Q15				(18919)
#define SQRT_3						((float)1.7320508075688)
#define SQRT_2						((float)1.4142135623731)
#define SQRT3_OVER_TWO_Q15			((int16_t)((float)(SQRT_3 / 2.0 * Q15)))

// PI
#define PI							(3.14159265359)

// User Configuration
// ADC
#define A31M22x_ADC_STSEL			(2)
#define A31M22x_ADC_CLKDIV			(2)

// UART
#define UARTn						(UART1)

// RPM
#define RPM_COMMAND_MIN 			(150)//3000

#define RPM_HIGH_SPEED_THRESHOLD	(700)//2500
#define RPM_LOW_SPEED_THRESHOLD		(600)//2000

#define RPM_15TS_OFF_THRESHOLD 		(800)
#define RPM_15TS_ON_THRESHOLD 		(1200)

// Shunt ADC Offset
#define SHUNT_AVERAGE_SHIFT			(10)
#define SHUNT_AVERAGE_COUNT			(1 << SHUNT_AVERAGE_SHIFT)

// Slope Algorithm
// 1. Start Sequence
#define START_STEP0_INIT_CMD_RPM	(150) // [RPM]///250 /////open loop final hz  motor in //150
#define START_STEP0_END_CMD_RPM		(200) // [RPM]///350////// notrmal opration mode //350
#define START_STEP0_DECIMATION		(20) // [ms]     //// 20 ms me 5 steups up 
#define START_STEP0_STEP_UP			(5) // [RPM / Step]////
#define START_STEP0_ACT_RPM_MIN		(200 - 10) // [RPM] //350-50

#define START_STEP1_WAIT_COUNT		(COUNT_FOR_1_SECOND / 100) // 0.010s

// 2. Normal Operation
#define SLOPE_DECIMATION			(50) // [ms]
#define SLOPE_STEP_UP				(5) // [RPM]
#define SLOPE_STEP_DOWN				(5) // [RPM]

// 3. Stop Sequence
#define STOP_STEP0_END_CMD_RPM		(600) // [RPM]//700
#define STOP_STEP0_SLOPE_DECIMATION	(10) // [ms]
#define STOP_STEP0_SLOPE_STEP_UP	(2) // [RPM]
#define STOP_STEP0_SLOPE_STEP_DOWN	(2) // [RPM]
#define STOP_STEP0_ACT_RPM_MIN		(1500 - 50) // [RPM]
#define STOP_STEP0_ACT_RPM_MAX		(1500 + 50) // [RPM]

#define STOP_STEP1_WAIT_COUNT		(COUNT_FOR_1_SECOND / 10)

#define STOP_STEP0_TIMEOUT_COUNT	(COUNT_FOR_1_SECOND / 10)

// Interrupt Bit
#if (defined(__DEF_A33M11x__) || defined(__DEF_A34M41x__) || defined(__DEF_AC30M1x64__) || defined(__DEF_AC33Mx064__) || defined(__DEF_AC33Mx128__) || defined(__DEF_A31M22x__))
#define MPWM_PERIOD_MATCH_INTERRUPT	(1UL << 7)
#endif

// IPM Temperature
#define TEMP_L1_THRESHOLD			(1950)  // 10 kOhm Pull-up resistance, 105 degree, 0.999519942V
#define TEMP_L0_THRESHOLD			(1240) // 10 kOhm Pull-up resistance, 95 degree,  1.269909359V
#define TEMP_OFF_THRESHOLD			(819) // 10 kOhm Pull-up resistance, 85 degree,  1.60025838V
#define THERMISTOR_POSITION			(UP_SIDE)
//#define TEMP_L1_THRESHOLD			(819)  // 10 kOhm Pull-up resistance, 105 degree, 0.999519942V
//#define TEMP_L0_THRESHOLD			(1040) // 10 kOhm Pull-up resistance, 95 degree,  1.269909359V
//#define TEMP_OFF_THRESHOLD			(1311) // 10 kOhm Pull-up resistance, 85 degree,  1.60025838V
//#define THERMISTOR_POSITION			(DOWN_SIDE)

// DC Link Fault, R1 = 900k, R2 = 10k
//#define DC_LINK_UV_OFF_THRESHOLD	(2418) // AV 190V
//#define DC_LINK_UV_L0_THRESHOLD		(2291) // AC 180V
//#define DC_LINK_UV_L1_THRESHOLD		(1463) // AC 115V
#define DC_LINK_UV_OFF_THRESHOLD	(1327) // AV 120V
#define DC_LINK_UV_L0_THRESHOLD		(1072) // AC 100V
#define DC_LINK_UV_L1_THRESHOLD		(1072) // AC 100V

#define DC_LINK_UV_L0_TARGET_RPM	(1800) // [RPM]

//#define DC_LINK_OV_L1_THRESHOLD		(3500) // AC 275V
//#define DC_LINK_OV_L0_THRESHOLD		(3220) // AC 253V
//#define DC_LINK_OV_OFF_THRESHOLD	(3092) // AC 243V
#define DC_LINK_OV_L1_THRESHOLD		(3618) // AC 300V
#define DC_LINK_OV_L0_THRESHOLD		(3618) // AC 300V
#define DC_LINK_OV_OFF_THRESHOLD	(3364) // AC 280V

// Shunt Offset Fault
#define SHUNT_OFFSET_LOW_THRESHOLD	(2048 - 200)
#define SHUNT_OFFSET_HIGH_THRESHOLD	(2048 + 200)

#define USE_OVERLOAD				(ON)

// Power Fault
#define P_BASE						(250) //unit = [Watt], do not change P_BASE value.///////////d total power calcllate 
#define Kpower_Q10					(int32_t)((1.5 * 165 * 5 / P_BASE) * Q10 + 0.5)

#define Gr_POWER					(15.0)
#define Ts_CC						(0.0000667) // 16kHz
#define FA_LPF_POWER_Q14			(int32_t)(((2.0 - Gr_POWER * Ts_CC) / (2.0 + Gr_POWER * Ts_CC)) * Q14 + 0.5)
#define FB_LPF_POWER_Q14			(int32_t)(((Gr_POWER * Ts_CC) / (2.0 + Gr_POWER * Ts_CC)) * Q14 + 0.5)

#define OVERLOAD_ON_THRESHOLD		((205 * Q14) / P_BASE)
#define OVERLOAD_OFF_THRESHOLD		((130 * Q14) / P_BASE)

#define OVERLOAD_DOWN_RPM			(10)  /// when  power exceed more than 200 watt   it will gradually decrease  150 
#define OVERLOAD_LOW_RPM			(800)  ///////////////////// comes to 1200  humderd .

#define OVERLOAD_ON_COUNTTHRESHOLD	(COUNT_FOR_1_SECOND * 2) // 60 Second  ///  overload thersold 
#define OVERLOAD_OFF_COUNTTHRESHOLD	(COUNT_FOR_1_SECOND * 30) // 30 Second   ////overload down  thershold 

#define FAULT_MAX_COUNT				(COUNT_FOR_1_SECOND * 60 * 5) // 5 Minutes  //////////restart this time 

//#define PWM_HZ						((uint32_t)Parameter[89])
#define PWM_FULL_PRD				((uint16_t)(SystemPeriClock / (PWM_HZ * 2)))

//#define COUNT_FOR_1_SECOND 			((uint32_t)(PWM_HZ / (Parameter[91] + 1)))

// Macro Function
#if (THERMISTOR_POSITION == UP_SIDE)
#define CHECK_TEMP_L1(TEMP_ADC)		(TEMP_ADC >= TEMP_L1_THRESHOLD)
#define CHECK_TEMP_L0(TEMP_ADC)		(TEMP_ADC >= TEMP_L0_THRESHOLD)
#elif (THERMISTOR_POSITION == DOWN_SIDE)
#define CHECK_TEMP_L1(TEMP_ADC)		(TEMP_ADC <= TEMP_L1_THRESHOLD)
#define CHECK_TEMP_L0(TEMP_ADC)		(TEMP_ADC <= TEMP_L0_THRESHOLD)
#endif

#define PHASE_LOSS_MARGIN_PERCENT (10)//10

/*******************************************************************************
* Public Typedef
*******************************************************************************/


/*******************************************************************************
* Exported Public Function
*******************************************************************************/


#endif // _DEFINE_H_

/* --------------------------------- End Of File ------------------------------ */
