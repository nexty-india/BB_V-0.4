/**
 *******************************************************************************
 * @file        a31m22x_div64.h
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


#ifndef _A31M6xx_PCU_H_
#define _A31M6xx_PCU_H_

/* Includes ------------------------------------------------------------------- */
#include "A31M6xx.h"
#include "aa_types.h"

#ifdef __cplusplus
extern "C"
{
#endif

/* Private macros ------------------------------------------------------------- */

#define PORT_ACCESS_EN()  						do { PCU2->PORTEN = 0x15; PCU2->PORTEN = 0x51; } while(0)
#define PORT_ACCESS_DIS()  						do { PCU2->PORTEN = 0x00; } while(0)

#define PCU_MR_FUNC_Msk                        (0x07UL)
#define PCU_CR_MODE_Msk                        (0x03UL)
#define PCU_PRCR_Msk						   (0x03UL)
#define PCU_STR_Msk							   (0x01UL)


//==========================================================================
// 	PAMR
//==========================================================================
#define PA0_MUX_PA0								(0)
#define PA0_MUX_PRTIN							(1)
#define PA0_MUX_CLKO							(3)
#define PA0_MUX_AN0								(7)

#define PA1_MUX_PA1								(0)
#define PA1_MUX_T0IO							(2)
#define PA1_MUX_AN1								(7)
#define PA1_MUX_CMP0S							(7)

#define PA2_MUX_PA2								(0)
#define PA2_MUX_T1IO							(2)
#define PA2_MUX_AN2								(7)
#define PA2_MUX_CMP0R							(7)

#define PA3_MUX_PA3								(0)
#define PA3_MUX_T2IO							(2)
#define PA3_MUX_AN3								(7)
#define PA3_MUX_CMP1S							(7)

#define PA4_MUX_PA4								(0)
#define PA4_MUX_T3IO							(2)
#define PA4_MUX_AN4								(7)
#define PA4_MUX_CMP1R							(7)

#define PA5_MUX_PA5								(0)
#define PA5_MUX_RXD0							(1)
#define PA5_MUX_AN5								(7)
#define PA5_MUX_CMP2S							(7)

#define PA6_MUX_PA6								(0)
#define PA6_MUX_TXD0							(1)
#define PA6_MUX_AN6								(7)
#define PA6_MUX_CMP2R							(7)

#define PA7_MUX_PA7								(0)
#define PA7_MUX_SS								(1)
#define PA7_MUX_T0IO							(2)
#define PA7_MUX_AN7								(7)

#define PA8_MUX_PA8								(0)
#define PA8_MUX_SCK								(1)
#define PA8_MUX_T1IO							(2)
#define PA8_MUX_ICOM0							(3)
#define PA8_MUX_OCCMPS0						(7)

#define PA9_MUX_PA9							(0)
#define PA9_MUX_MOSI							(1)
#define PA9_MUX_T2IO							(2)
#define PA9_MUX_ICOM1							(3)
#define PA9_MUX_OCCMPS1						(7)

#define PA10_MUX_PA10							(0)
#define PA10_MUX_MISO							(1)
#define PA10_MUX_T3IO							(2)
#define PA10_MUX_ICOM2						(3)

#define PA11_MUX_PA11							(0)
#define PA11_MUX_ICOM3						(3)

#define PA12_MUX_PA12							(0)
#define PA12_MUX_ICOM4						(3)

//==========================================================================
// 	PBMR
//==========================================================================
#define PB0_MUX_PB0								(0)
#define PB0_MUX_SCL								(1)
#define PB0_MUX_SWCLK							(3)

#define PB1_MUX_PB1								(0)
#define PB1_MUX_SDA								(1)
#define PB1_MUX_SWDIO							(3)

#define PB2_MUX_PB2								(0)
#define PB2_MUX_RXD0							(1)
#define PB2_MUX_CSAP							(7)

#define PB3_MUX_PB3								(0)
#define PB3_MUX_TXD0							(1)
#define PB3_MUX_CSAN							(7)

#define PB4_MUX_PB4								(0)
#define PB4_MUX_nRST							(3)

#define PB5_MUX_PB5								(0)
#define PB5_MUX_RXD1							(1)
#define PB5_MUX_DACO							(7)

#define PB6_MUX_PB6								(0)
#define PB6_MUX_TXD1							(1)
#define PB6_MUX_BOOT							(3)

#define PB7_MUX_PB7								(0)
#define PB7_MUX_SCL								(1)

#define PB8_MUX_PB8								(0)
#define PB8_MUX_SDA								(1)

#define PB9_MUX_PB9								(0)
#define PB9_MUX_T0IO							(2)

//==========================================================================
// 	PCMR
//==========================================================================
#define PC0_MUX_PC0								(0)
#define PC0_MUX_AN8								(7)
#define PC0_MUX_XIN								(7)

#define PC1_MUX_PC1								(0)
#define PC1_MUX_AN9								(7)
#define PC1_MUX_XOUT							(7)

#define PC2_MUX_PC2								(0)
#define PC2_MUX_SS								(1)
#define PC2_MUX_RXD0							(2)
#define PC2_MUX_AN10							(7)

#define PC3_MUX_PC3								(0)
#define PC3_MUX_SCK								(1)
#define PC3_MUX_TXD0							(2)
#define PC3_MUX_AN11							(7)

#define PC4_MUX_PC4								(0)
#define PC4_MUX_MOSI							(1)
#define PC4_MUX_RXD1							(2)
#define PC4_MUX_AN12							(7)

#define PC5_MUX_PC5								(0)
#define PC5_MUX_MISO							(1)
#define PC5_MUX_TXD1							(2)
#define PC5_MUX_AN13							(7)

#define PC6_MUX_PC6								(0)
#define PC6_MUX_SCL								(1)
#define PC6_MUX_AN14							(7)

#define PC7_MUX_PC7								(0)
#define PC7_MUX_SDA								(1)
#define PC7_MUX_AN15							(7)

#define PC8_MUX_PC8								(0)

#define PC9_MUX_PC9								(0)
#define PC9_MUX_T1IO							(2)

#define PC10_MUX_PC10							(0)
#define PC10_MUX_RXD1							(1)

#define PC11_MUX_PC11							(0)
#define PC11_MUX_TXD1							(1)
//==========================================================================


/*
 * @brief 	PCU port mode enumerate definition
 */
typedef enum {
	PUSH_PULL_OUTPUT = 0,
	OPEN_DRAIN_OUTPUT,
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

/*
 * @brief  PCU2 ICOM output selection enumerated definition
 */
typedef enum {
	PCU2_ICOM_OUTPUT_FLOATING         = 0x00UL, /*!< Floating (open-drain, high) */
	PCU2_ICOM_OUTPUT_HIGH_CURRENT_LOW = 0x01UL, /*!< High Sinking Current (open-drain, low) */
} PCU2_ICOM_OUTPUT_Type;

/*
 * @brief  PCU2 LED Lamp output selection enumerated definition
 */
typedef enum {
	PCU2_LED_LAMP_OUTPUT_FLOATING         = 0x00UL, /*!< Floating (open-drain high) */
	PCU2_LED_LAMP_OUTPUT_HIGH_CURRENT_LOW = 0x01UL, /*!< High Sinking Current (open-drain low) */
} PCU2_LED_LAMP_OUTPUT_Type;


/* Public Functions ----------------------------------------------------------- */
void PCU_ConfigureFunction(PCU_Type *PCx, uint8_t pin_no, uint32_t func);

void PCU_SetDirection(PCU_Type *PCx, uint8_t pin_no, PCU_PORT_MODE dir_type);
void PCU_ConfigurePullup (PCU_Type *PCx, uint8_t pin_no, PCU_PULLUP_MODE pullup);

void PCU_ConfigureStrength (PCU_Type *PCx, uint8_t pin_no, PCU_STR_LEVEL str_level);

void PCU_IntCmd(PCU_Type *PCx, uint8_t pin_no, uint8_t pin_en, uint8_t int_mode);
uint32_t PCU_GetIntStatus(PCU_Type *PCx);
void PCU_ClearInt(PCU_Type *PCx, uint32_t value);

void PCU_ConfigureDebounce (PCU_Type *PCx, uint8_t pin_no, FunctionalState debounce);

void PCU2_ControlICOM(uint32_t ICOM_Number, PCU2_ICOM_OUTPUT_Type Output);
void PCU2_ControlLEDLamp(PCU2_LED_LAMP_OUTPUT_Type Output);
void PCU2_GetRSPIStatus(uint32_t *pCount, uint32_t *pStatus);

void GPIO_SetValue(PCU_Type *Px, uint16_t bitValue);
void GPIO_ClearValue(PCU_Type *Px, uint16_t bitValue);
uint16_t GPIO_ReadValue(PCU_Type *Px);
void GPIO_WriteValue(PCU_Type *Px, uint16_t Value);



#ifdef __cplusplus
}
#endif


#endif /* end _A31M6xx_PCU_H_ */

/* --------------------------------- End Of File ------------------------------ */
