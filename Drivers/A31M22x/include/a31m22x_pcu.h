/**
 *******************************************************************************
 * @file        a31m22x_pcu.h
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


#ifndef _A31M22x_PCU_H_
#define _A31M22x_PCU_H_

/* Includes ------------------------------------------------------------------- */
#include "A31M22x.h"
#include "aa_types.h"

#ifdef __cplusplus
extern "C"
{
#endif

/* Private macros ------------------------------------------------------------- */

#define PORT_ACCESS_EN()  						do { PORTEN->EN=0x15; PORTEN->EN=0x51; } while(0)
#define PORT_ACCESS_DIS()  						do { PORTEN->EN=0x00; } while(0) 

#define PCU_MR_FUNC_Msk                        (0x07UL)
#define PCU_CR_MODE_Msk                        (0x03UL)
#define PCU_PRCR_Msk						   (0x03UL)
#define PCU_STR_Msk							   (0x01UL)

/* ================================================================================ */
/* ================          struct 'PCU' Position & Mask          ================ */
/* ================================================================================ */


/* Pin function */
#define FUNC0 			0x0				/** Function 0 	*/
#define FUNC1 			0x1				/** Function 1 	*/
#define FUNC2 			0x2				/** Function 2	*/
#define FUNC3 			0x3				/** Function 3	*/
#define FUNC4 			0x4				/** Function 4	*/
#define FUNC5			0x7				/** Function 5  */


//==========================================================================
// 	PAMR
//==========================================================================
#define PA0_MUX_PA0								(0)
#define PA0_MUX_T2IO							(1)
#define PA0_MUX_AN0								(7)
#define PA0_MUX_AO2								(7)

#define PA1_MUX_PA1								(0)
#define PA1_MUX_T3IO							(1)
#define PA1_MUX_CPOUT					(4)
#define PA1_MUX_AN1								(7)

#define PA2_MUX_PA2								(0)
#define PA2_MUX_SS							(1)
#define PA2_MUX_WDTO							(2)
#define PA2_MUX_AN2								(7)
#define PA2_MUX_CPA							(7)

#define PA3_MUX_PA3								(0)
#define PA3_MUX_SCK								(1)
#define PA3_MUX_STBO							(2)
#define PA3_MUX_AN3								(7)
#define PA3_MUX_CPRE0							(7)

#define PA4_MUX_PA4								(0)
#define PA4_MUX_T0IO							(3)
#define PA4_MUX_AN4								(7)
#define PA4_MUX_AIP0							(7)
#define PA4_MUX_CPB							(7)

#define PA5_MUX_PA5								(0)
#define PA5_MUX_T1IO							(3)
#define PA5_MUX_AN5								(7)
#define PA5_MUX_AIN0							(7)
#define PA5_MUX_CPC							(7)

#define PA6_MUX_PA6								(0)
#define PA6_MUX_T0IO							(1)
#define PA6_MUX_MOSI							(2)
#define PA6_MUX_T2IO							(3)
#define PA6_MUX_AN6								(7)
#define PA6_MUX_AO0							(7)

#define PA7_MUX_PA7								(0)
#define PA7_MUX_T1IO							(1)
#define PA7_MUX_MISO								(2)
#define PA7_MUX_T3IO							(3)
#define PA7_MUX_AN7								(7)
#define PA7_MUX_AIP1								(7)

#define PA8_MUX_PA8								(0)
#define PA8_MUX_T2IO								(1)
#define PA8_MUX_T0IO							(2)
#define PA8_MUX_AN8						(7)
#define PA8_MUX_AIN1						(7)

#define PA9_MUX_PA9							(0)
#define PA9_MUX_T3IO							(1)
#define PA9_MUX_T1IO							(2)
#define PA9_MUX_AN9							(3)
#define PA9_MUX_AO1					(7)

#define PA10_MUX_PA10							(0)
#define PA10_MUX_AN10							(7)

#define PA11_MUX_PA11							(0)
#define PA11_MUX_AN11						(7)

#define PA12_MUX_PA12							(0)
#define PA12_MUX_T0IO						(1)
#define PA12_MUX_AO2						(7)

#define PA13_MUX_PA13							(0)
#define PA13_MUX_T1IO						(1)

#define PA14_MUX_PA14							(0)
#define PA14_MUX_T2IO						(1)

#define PA15_MUX_PA15							(0)
#define PA15_MUX_T3IO						(1)

//==========================================================================
// 	PBMR
//==========================================================================
#define PB0_MUX_PB0								(0)
#define PB0_MUX_MPWMUH				(1)
#define PB0_MUX_SS									(2)

#define PB1_MUX_PB1								(0)
#define PB1_MUX_MPWMUL				(1)
#define PB1_MUX_SCK									(2)

#define PB2_MUX_PB2								(0)
#define PB2_MUX_MPWMVH							(1)
#define PB2_MUX_MOSI							(2)

#define PB3_MUX_PB3								(0)
#define PB3_MUX_MPWMVL							(1)
#define PB3_MUX_MISO							(2)

#define PB4_MUX_PB4								(0)
#define PB4_MUX_MPWMWH				(1)

#define PB5_MUX_PB5								(0)
#define PB5_MUX_MPWMWL				(1)

#define PB6_MUX_PB6								(0)
#define PB6_MUX_PRTIN							(1)
#define PB6_MUX_T0IO							(3)

#define PB7_MUX_PB7								(0)
#define PB7_MUX_OVIN								(1)
#define PB7_MUX_CLKO								(2)
#define PB7_MUX_T1IO								(3)

//==========================================================================
// 	PCMR
//==========================================================================
#define PC0_MUX_PC0								(0)
#define PC0_MUX_SWCLK								(1)
#define PC0_MUX_RXD1								(2)

#define PC1_MUX_PC1								(0)
#define PC1_MUX_SWDIO								(1)
#define PC1_MUX_TXD1							(2)

#define PC2_MUX_PC2								(0)

#define PC3_MUX_PC3								(0)

#define PC4_MUX_PC4								(0)
#define PC4_MUX_T0IO							(2)

#define PC5_MUX_PC5								(0)
#define PC5_MUX_RXD1							(1)
#define PC5_MUX_T1IO							(2)

#define PC6_MUX_PC6								(0)
#define PC6_MUX_TXD1								(1)
#define PC6_MUX_T2IO							(2)

#define PC7_MUX_PC7								(0)
#define PC7_MUX_SCL								(1)
#define PC7_MUX_T3IO								(2)
#define PC7_MUX_RXD1								(3)
#define PC7_MUX_SS								(4)
#define PC7_MUX_AN10							(7)
#define PC7_MUX_AIP2							(7)

#define PC8_MUX_PC8								(0)
#define PC8_MUX_SDA								(1)
#define PC8_MUX_T1IO								(2)
#define PC8_MUX_TXD1								(3)
#define PC8_MUX_SCK								(4)
#define PC8_MUX_AN11							(7)
#define PC8_MUX_AIN2							(7)

#define PC9_MUX_PC9								(0)
#define PC9_MUX_CLKO							(1)

#define PC10_MUX_PC10							(0)
#define PC10_MUX_nRESET							(1)

#define PC11_MUX_PC11							(0)
#define PC11_MUX_BOOT							(1)
#define PC11_MUX_T0IO							(2)
#define PC11_MUX_T9IO							(3)

#define PC12_MUX_PC12							(0)
#define PC12_MUX_T3IO							(1)
#define PC12_MUX_XIN							(7)

#define PC13_MUX_PC13							(0)
#define PC13_MUX_T2IO							(1)
#define PC13_MUX_XOUT							(7)

#define PC14_MUX_PC14							(0)
#define PC14_MUX_RXD0							(1)
#define PC14_MUX_CLKO							(2)
#define PC14_MUX_OVIN							(3)
#define PC14_MUX_MOSI							(4)

#define PC15_MUX_PC15							(0)
#define PC15_MUX_TXD0							(1)
#define PC15_MUX_PRTIN							(3)
#define PC15_MUX_MISO							(4)

//==========================================================================
// 	PDMR
//==========================================================================
#define PD0_MUX_PD0								(0)
#define PD0_MUX_SS								(1)

#define PD1_MUX_PD1								(0)
#define PD1_MUX_SCK								(1)

#define PD2_MUX_PD2								(0)
#define PD2_MUX_MOSI								(1)
#define PD2_MUX_SCL								(2)
#define PD2_MUX_RXD0								(4)
#define PD2_MUX_SXOUT								(7)

#define PD3_MUX_PD3								(0)
#define PD3_MUX_MISO								(1)
#define PD3_MUX_SDA								(2)
#define PD3_MUX_TXD0								(4)
#define PD3_MUX_SXIN								(7)

//==========================================================================


/*
 * @brief 	PCU port mode enumerate definition
 */
typedef enum {
	PUSH_PULL_OUTPUT = 0,
	OPEN_DRAIN_OUTPUT_GPIO,
	OPEN_DRAIN_OUTPUT_ALT,
	INPUT
}PCU_PORT_MODE;

typedef enum {
	PULL_UP_DOWN_DISABLE = 0,
	PULL_UP_ENABLE = 2,
	PULL_DOWN_ENABLE = 3
}PCU_PULLUP_MODE;

typedef enum {
	LEVEL0 = 0,
	LEVEL1
}PCU_STR_LEVEL;


enum {
	IER_DISABLE = 0,
	IER_LEVEL_NON_PENDING,
	IER_LEVEL_PENDING,
	IER_EDGE
};

enum {
	ICR_PROHIBIT_INT = 0,
	ICR_LOW_LEVEL_INT = 1,
	ICR_FALLING_EDGE_INT = ICR_LOW_LEVEL_INT,
	ICR_HIGH_LEVEL_INT =2,
	ICR_RISING_EDGE_INT = ICR_HIGH_LEVEL_INT,
	ICR_BOTH_EDGE_INT =3	
};


/* Public Functions ----------------------------------------------------------- */

void HAL_GPIO_ConfigFunction(PCU_Type *PCx, uint8_t pin_no, uint32_t func);

void HAL_GPIO_ConfigOutput(PCU_Type *PCx, uint8_t pin_no, PCU_PORT_MODE dir_type);
void HAL_GPIO_ConfigPullup (PCU_Type *PCx, uint8_t pin_no, PCU_PULLUP_MODE pullup);



void HAL_GPIO_EXTI_Config(PCU_Type *PCx, uint8_t pin_no, uint8_t pin_en, uint8_t int_mode);
uint32_t HAL_GPIO_EXTI_GetStatus(PCU_Type *PCx);
void HAL_GPIO_EXTI_ClearPin(PCU_Type *PCx, uint32_t value);

void HAL_GPIO_SetDebouncePin (PCU_Type *PCx, uint8_t pin_no, FunctionalState debounce);


/* Public Functions ----------------------------------------------------------- */
void HAL_GPIO_SetPin(PCU_Type *Px, uint16_t bitValue);
void HAL_GPIO_ClearPin(PCU_Type *Px, uint16_t bitValue);
uint16_t HAL_GPIO_ReadPin(PCU_Type *Px);
void HAL_GPIO_WritePin(PCU_Type *Px, uint16_t Value);



#ifdef __cplusplus
}
#endif


#endif /* end _A31M22x_PCU_H_ */

/* --------------------------------- End Of File ------------------------------ */
