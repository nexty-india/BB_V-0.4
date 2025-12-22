/**
 *******************************************************************************
 * @file        Bharat_Bijleee.c
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
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdarg.h>


/*******************************************************************************
* Pre-processor Definition & Macro
*******************************************************************************/


/*******************************************************************************
* Private Typedef
*******************************************************************************/
void SPI_SendData(SPI_Type* SPIx, uint32_t Data);
void SPI_DelayConfig(SPI_Type* SPIx, uint8_t StartDelay, uint8_t BurstDelay,uint8_t StopDelay);
void SPI_Cmd(SPI_Type* SPIx, FunctionalState NewState);
void SPI_Init(SPI_Type *SPIx, SPI_CFG_Type *SPI_ConfigStruct);

/*******************************************************************************
* Private Variable
*******************************************************************************/


/**********************************************************************
 * @brief		Checks whether the specified SPI status flag is set or not
 * @param[in]	SPIx	SPI peripheral selected, should be:
 * 				 	- SPI	:SPI0~1 peripheral
 * @return		SPI status flag
 **********************************************************************/
uint32_t SPI_GetStatus(SPI_Type* SPIx)
{
	return (SPIx->SR);
}


/*******************************************************************************
* Private Function Prototype
*******************************************************************************/

/*******************************************************************************
* Public Variable
*******************************************************************************/


/*******************************************************************************
* Public Function
*******************************************************************************/

void GPIOB_IRQHandler(void)
{
	
}



void USER_ADC_Init(void)
{
	//SCU_Access_Enable();
		
	// Turn on power and clock
	SCU->PER2 &= ~(SCU_PER2_ADC_Msk);
	SCU->PCER2&= ~(SCU_PCER2_ADC_Msk);
	/* Set up peripheral clock for ADC module */
	SCU->PER2 |= (SCU_PER2_ADC_Msk);
	SCU->PCER2|= (SCU_PCER2_ADC_Msk);
	
	//System config disable
	//SCU_Access_Disable();
	
	ADC->MR = 0
		| (0 << 24) // CTIMELAT
		| (0 << 22) // EXTCONSTAEN
		| (0 << 19) // CDATAT   0 : 15~4 bit  1 : 11~0 bit
		| (0 << 18) // DMAIDE
		| (0 << 17) // DMAEN    0 : DMA DISABLE  1 : DMA ENABLE
		| (0 << 11) // SEQTRGT
		| (4 << 8)  // SEQCNT   0 : single , over 1 Count value (CEQCNT+1 AD conversion)      (3 << 8)
		| (1 << 7)  // ADEN     0 : ADC Disable  1 : ADC Enable
		| (1 << 6)  // ARST     0 : Stop  1 : Restart
		| (2 << 4)  // ADCMOD   0 : Single conversion  1 : Burst conversion  2: multi conversion
		| (1 << 0)  // TRGSEL   0 : Ext  1 : Timer  2 : MPWM
		;
		
	ADC->CSCR = 0x00;

	ADC->CCR = 0
		| (0 << 15) // ADCPDA
		| (A31M22x_ADC_CLKDIV << 8) // CLKDIV
		| (0 << 7)  // ADCPD
		| (0 << 6)  // EXTCLK
		| (0 << 5)  // CLKINVT
		;

	ADC->TRG = 0
		| (0 << 28) // SEQTRG7
		| (0 << 24) // SEQTRG6
		| (0 << 20) // SEQTRG5
		| (0 << 16) // SEQTRG4                        //---------------
		| (0 << 12) // SEQTRG3 (MPART4)
		| (0 << 8)  // SEQTRG2 (MPATR3)
		| (0 << 4)  // SEQTRG1 (MPATR2)
		| (0 << 0)  // SEQTRG0 (MPATR1)
		;
	ADC->CSTR1 = 0
		| (A31M22x_ADC_STSEL << 24) // ST3CH (AN0, IPM TEMP)
		| (A31M22x_ADC_STSEL << 16) // ST2CH (AN7, VDC_LINK)
		| (A31M22x_ADC_STSEL << 8)  // ST1CH (AN17, AO0)
		| (A31M22x_ADC_STSEL << 0)  // ST0CH (AN17, AO1)
		;
		
	//ADC->CSTR2 = 0x00;
	
	ADC->CSTR2 = 0
		| (A31M22x_ADC_STSEL << 24)
		| (A31M22x_ADC_STSEL << 16)
		| (A31M22x_ADC_STSEL << 8) 
		| (A31M22x_ADC_STSEL << 0)  //(AN3 , Vref)
		;
	
		
	ADC->SCSR1 = 0
		| (0 << 24)  // SEQ3CH 
		| (0 << 16)  // SEQ2CH 
		#if 0 //AN1 ADC 
		| (1 << 8)  // SEQ1CH (AN1, I_COM)
		| (1 << 0)  // SEQ0CH (AN1, I_COM)
		#else //AO0 ADC
		| (17 << 8)  // SEQ1CH (AN17, OO1)
		| (18 << 0)   // SEQ0CH (AN18, 002)
		#endif
		;

	ADC->SCSR2 = 0
		| (2 << 24)   // SEQ7CH  
		| (0 << 16)   // SEQ6CH
		| (0 << 8) 	  // SEQ5CH 
		| (6 << 0)  	// SEQ4CH (AN6 , Vref)    6
		;

	ADC->CR = 0
		| (0 << 7)  // ASTOP ADC conversion stop
		| (0 << 4)  // AESTART
		| (0 << 1)  // TRGCLR
		| (1 << 0)  // ASTART
		;
		
	ADC->SR  = 0xFFFFF;
	
	ADC->IER = 0
		| (0 << 9) // CMP1IE
		| (0 << 8) // CMP0IE
		| (0 << 4) // DMAIE
		| (0 << 3) // TRGIE
		| (0 << 2) // EOSIE
		| (0 << 1) // IOCIE
		| (0 << 0) // EOCIE
		;
}


/********************************************************************************/
uint32_t MDL_ADC_OPAMP(uint32_t Number)
{
	uint32_t Data;

	if (Number == 1) {
		Data = (ADC->DR0 >> 4) & 0x0FFF;   //(AN18, OO2)
	} else if (Number == 2) {
		Data = (ADC->DR4 >> 4) & 0x0FFF;   // (AN17, OO1)
	} else if(Number == 3)
	{
		Data = (ADC->DR7 >> 4) & 0x0FFF;  //(AN2 ,Ambient)
	}
		else{
		Data = 0;
	}

	return Data;
}





//uint32_t MDL_ADC_GetVDCLink(void)
//{
//	return (ADC->DR7 >> 4) & 0x0FFF;
//}
/**********************************************************************************/






void MDL_PCU_Init(void)
{
	// Peripheral Enable Register 1 (0 : Disable, 1 : Enable)
	SCU->PER1 = SCU->PER1
		| (0x01UL << SCU_PER1_GPIOD_Pos)
		| (0x01UL << SCU_PER1_GPIOC_Pos)
		| (0x01UL << SCU_PER1_GPIOB_Pos)
		| (0x01UL << SCU_PER1_GPIOA_Pos)
		;

	// Peripheral Clock Enable Register 1 (0 : Disable, 1 : Enable)
	SCU->PCER1 = SCU->PCER1
		| (0x01UL << SCU_PCER1_GPIOD_Pos)
		| (0x01UL << SCU_PCER1_GPIOC_Pos)
		| (0x01UL << SCU_PCER1_GPIOB_Pos)
		| (0x01UL << SCU_PCER1_GPIOA_Pos)
		;

	// Enable Writing Permittion of ALL PCU Register
	PORT_ACCESS_EN();

	// PORT - A
	PA->MR2 = 0x00UL
		| (0x00UL << PCU_MR2_P9MUX_Pos)  // 0 : PA9,   1 : T3IO  2 : T1IO  3 :  4 :  7 : AN9/AO1  -------------- OO2 (4MA-20MA ANALOG INPUT)
		| (0x01UL << PCU_MR2_P8MUX_Pos)  // 0 : PA8,   1 : T2IO  2 : T0IO  3 :  4 :  7 : AN9/AIN1 -------------- OIN2 (4MA-20MA ANALOG INPUT)
		;

	PA->MR1 = 0x00UL
		| (0x07UL << PCU_MR1_P7MUX_Pos)  // 0 : PA7,  1 : T1IO  2 : MISO  3 : T3IO  4 :        7 : AN7/AIP1      -------------- OIP2 (4MA-20MA ANALOG INPUT)
		| (0x07UL << PCU_MR1_P6MUX_Pos)  // 0 : PA6,  1 : T0IO  2 : MOSI  3 : T2IO  4 :        7 : AN6/AO0       -------------- OO1  (0V-10V ANALOG INPUT)
		| (0x07UL << PCU_MR1_P5MUX_Pos)  // 0 : PA5,  1 :       2 :       3 : T1IO  4 : T1IO   7 : AN5/AIN0/CPC  -------------- OIN1 (0V-10V ANALOG INPUT) 
		| (0x07UL << PCU_MR1_P4MUX_Pos)  // 0 : PA4,  1 :       2 :       3 : T0IO  4 : T0IO   7 : AN4/AIP0/CPB  -------------- OIP1 (0V-10V ANALOG INPUT) 
		| (0x00UL << PCU_MR1_P3MUX_Pos)  // 0 : PA3,  1 : SCK   2 : STBO  3 :       4 :        7 : AN3/CPRE0     -------------- FAULT (INTRRUPT PIN) 
		| (0x07UL << PCU_MR1_P2MUX_Pos)  // 0 : PA2,  1 : SS    2 : WDTO  3 :       4 :        7 : AN2/CPA       -------------- AMBIENT_TEMPERATURE
		| (0x00UL << PCU_MR1_P1MUX_Pos)  // 0 : PA1,  1 : T3IO  2 :       3 :       4 : CPOUT  7 : AN1           -------------- RELAY_STATUS 
		| (0x00UL << PCU_MR1_P0MUX_Pos)  // 0 : PA0,  1 : T2IO  2 :       3 :       4 :        7 : AN0/AO2       -------------- RE/DE _ MODBUS PIN
		;

	PA->CR = 0x00 // 0 : Push-pull output, 1 : Open-drain output, 2 / 3 : Input
		| (0x03UL << PCU_CR_P9_Pos)  // PA9, -------------- OO2  (4MA-20MA ANALOG INPUT)
		| (0x03UL << PCU_CR_P8_Pos)  // PA8, -------------- OIN2 (4MA-20MA ANALOG INPUT)
		| (0x03UL << PCU_CR_P7_Pos)  // PA7, -------------- OIP2 (4MA-20MA ANALOG INPUT)
		| (0x03UL << PCU_CR_P6_Pos)  // PA6, -------------- OO1  (0V-10V ANALOG INPUT)
		| (0x03UL << PCU_CR_P5_Pos)  // PA5, -------------- OIN1 (0V-10V ANALOG INPUT) 
		| (0x03UL << PCU_CR_P4_Pos)  // PA4, -------------- OIP1 (0V-10V ANALOG INPUT)
		| (0x03UL << PCU_CR_P3_Pos)  // PA3, -------------- FAULT (INTRRUPT PIN) 
		| (0x03UL << PCU_CR_P2_Pos)  // PA2, -------------- AMBIENT_TEMPERATURE
		| (0x00UL << PCU_CR_P1_Pos)  // PA1, -------------- RELAY_STATUS
		| (0x00UL << PCU_CR_P0_Pos)  // PA0, -------------- RE/DE _ MODBUS PIN
		;

	PA->PRCR = 0x00 // 0 / 1 : Disable pull-up/down resistor, 2 : Enable pull-up resistor, 3 : Enable Pull-down resistor
		| (0x01UL << PCU_PRCR_PUE9_Pos)  // PA9 -------------- OO2 (4MA-20MA ANALOG INPUT)
		| (0x01UL << PCU_PRCR_PUE8_Pos)  // PA8 -------------- OIN2 (4MA-20MA ANALOG INPUT)
		| (0x01UL << PCU_PRCR_PUE7_Pos)  // PA7 -------------- OIP2 (4MA-20MA ANALOG INPUT)
		| (0x01UL << PCU_PRCR_PUE6_Pos)  // PA6 -------------- OO1  (0V-10V ANALOG INPUT)
		| (0x01UL << PCU_PRCR_PUE5_Pos)  // PA5 -------------- OIN1 (0V-10V ANALOG INPUT)
		| (0x01UL << PCU_PRCR_PUE4_Pos)  // PA4 -------------- OIP1 (0V-10V ANALOG INPUT)
		| (0x01UL << PCU_PRCR_PUE3_Pos)  // PA3 -------------- FAULT (INTRRUPT PIN) 
		| (0x02UL << PCU_PRCR_PUE2_Pos)  // PA2 -------------- AMBIENT_TEMPERATURE
		| (0x02UL << PCU_PRCR_PUE1_Pos)  // PA1 -------------- RELAY_STATUS
		| (0x03UL << PCU_PRCR_PUE0_Pos)  // PA0 -------------- RE/DE _ MODBUS PIN
		;

	// PORT - B
	PB->MR1 = 0x00UL
		| (0x03UL << PCU_MR1_P7MUX_Pos)  // 0 : PB7,  1 : OVIN    2 : CLKO  3 : T1IO  4 :  7 :   ||-----DIGITAL PWM
		| (0x00UL << PCU_MR1_P6MUX_Pos)  // 0 : PB6,  1 : PRTIN   2 :       3 : T0IO  4 :  7 :	 ||-----Not used
		| (0x01UL << PCU_MR1_P5MUX_Pos)  // 0 : PB5,  1 : MPWMWL  2 :       3 :       4 :  7 :   ||-----ANALOG PWM
		| (0x00UL << PCU_MR1_P4MUX_Pos)  // 0 : PB4,  1 : MPWMWH  2 :       3 :       4 :  7 :   ||-----CMP1
		| (0x00UL << PCU_MR1_P3MUX_Pos)  // 0 : PB3,  1 : MPWMVL  2 : MISO  3 :       4 :  7 :   ||-----CMP2
		| (0x00UL << PCU_MR1_P2MUX_Pos)  // 0 : PB2,  1 : MPWMVH  2 : MOSI  3 :       4 :  7 :   ||-----SWITCH 1  
		| (0x00UL << PCU_MR1_P1MUX_Pos)  // 0 : PB1,  1 : MPWMUL  2 : SCK   3 :       4 :  7 :   ||-----SWITCH 2
		| (0x00UL << PCU_MR1_P0MUX_Pos)  // 0 : PB0,  1 : MPWMUH  2 : SS    3 :       4 :  7 :   ||-----SWITCH 3 
		;

	PB->CR = 0x00 // 0 : Push-pull output, 1 : Open-drain output, 2 / 3 : Input
		| (0x00UL << PCU_CR_P7_Pos)  // PB7, ||------DIGITAL PWM
		| (0x00UL << PCU_CR_P6_Pos)  // PB6, ||------Not Used
		| (0x01UL << PCU_CR_P5_Pos)  // PB5, ||------ANALOG PWM (WL)   
		| (0x03UL << PCU_CR_P4_Pos)  // PB4, ||------CMP1
		| (0x03UL << PCU_CR_P3_Pos)  // PB3, ||------CMP2
		| (0x03UL << PCU_CR_P2_Pos)  // PB2, ||------SWITCH 1 
		| (0x03UL << PCU_CR_P1_Pos)  // PB1, ||------SWITCH 2 
		| (0x03UL << PCU_CR_P0_Pos)  // PB0, ||------SWITCH 3 
		;

	PB->PRCR = 0x00 // 0 / 1 : Disable pull-up/down resistor, 2 : Enable pull-up resistor, 3 : Enable Pull-down resistor
		| (0x03UL << PCU_PRCR_PUE7_Pos)  // PB7 ||-----DIGITAL PWM
		| (0x03UL << PCU_PRCR_PUE6_Pos)  // PB6 ||-----Not Used
		| (0x01UL << PCU_PRCR_PUE5_Pos)  // PB5 ||-----ANALOG PWM
		| (0x03UL << PCU_PRCR_PUE4_Pos)  // PB4 ||-----CMP1
		| (0x03UL << PCU_PRCR_PUE3_Pos)  // PB3 ||-----CMP2
		| (0x03UL << PCU_PRCR_PUE2_Pos)  // PB2 ||-----SWITCH 1 
		| (0x03UL << PCU_PRCR_PUE1_Pos)  // PB1 ||-----SWITCH 2
		| (0x03UL << PCU_PRCR_PUE0_Pos)  // PB0 ||-----SWITCH 3 
		;

	// PORT - C
	PC->MR2 = 0x00UL
		| (0x00UL << PCU_MR2_P15MUX_Pos) // 0 : PC15,  1 : TXD0    2 :       3 : PRTIN  4 : MISO  7 :
		| (0x00UL << PCU_MR2_P14MUX_Pos) // 0 : PC14,  1 : RXD0    2 : CLKO  3 : OVIN   4 : MOSI  7 :           ||-----SWITCH 4 
		| (0x07UL << PCU_MR2_P13MUX_Pos) // 0 : PC13,  1 : T2IO    2 :       3 :        4 :       7 : XOUT    
		| (0x07UL << PCU_MR2_P12MUX_Pos) // 0 : PC12,  1 : T3IO    2 :       3 :        4 :       7 : XIN
		| (0x01UL << PCU_MR2_P11MUX_Pos) // 0 : PC11,  1 : BOOT    2 : T0IO  3 :        4 :       7 :
		| (0x01UL << PCU_MR2_P10MUX_Pos) // 0 : PC10,  1 : nRESET  2 :       3 :        4 :       7 :
		| (0x03UL << PCU_MR2_P8MUX_Pos)  // 0 : PC8,   1 : SDA     2 : T1IO  3 : TXD1   4 : SCK   7 : AN11/AIN2  ||------RS485  TX
		;

	PC->MR1 = 0x00UL
		| (0x03UL << PCU_MR1_P7MUX_Pos)  // 0 : PC7,  1 : SCL    2 : T3IO  3 : RXD1  4 : SS  7 : AN10/AIP2       ||------RS485 RX
		| (0x01UL << PCU_MR1_P1MUX_Pos)  // 0 : PC1,  1 : SWDIO  2 : TXD1  3 :       4 :     7 : 
		| (0x01UL << PCU_MR1_P0MUX_Pos)  // 0 : PC0,  1 : SWCLK  2 : RXD1  3 :       4 :     7 : 
		;

	PC->CR = 0x00 // 0 : Push-pull output, 1 : Open-drain output, 2 / 3 : Input
		| (0x00UL << PCU_CR_P15_Pos) // PC15, DAC LD
		| (0x03UL << PCU_CR_P14_Pos) // PC14, ||-----SWITCH 4 
		| (0x00UL << PCU_CR_P13_Pos) // PC13, XOUT
		| (0x00UL << PCU_CR_P12_Pos) // PC12, XIN
		| (0x00UL << PCU_CR_P11_Pos) // PC11, nBOOT
		| (0x00UL << PCU_CR_P10_Pos) // PC10, nRESET
		| (0x01UL << PCU_CR_P8_Pos)  // PC8, ||------RS485 TX
		| (0x03UL << PCU_CR_P7_Pos)  // PC7, ||------RS485 RX
		| (0x00UL << PCU_CR_P1_Pos)  // PC1, SWDIO
		| (0x00UL << PCU_CR_P0_Pos)  // PC0, SWDCLK
		;

	PC->PRCR = 0x00 // 0 / 1 : Disable pull-up/down resistor, 2 : Enable pull-up resistor, 3 : Enable Pull-down resistor
		| (0x00UL << PCU_PRCR_PUE15_Pos) // PC15
		| (0x03UL << PCU_PRCR_PUE14_Pos) // PC14  ||-----SWITCH 4 
		| (0x00UL << PCU_PRCR_PUE13_Pos) // PC13
		| (0x00UL << PCU_PRCR_PUE12_Pos) // PC12
		| (0x00UL << PCU_PRCR_PUE11_Pos) // PC11
		| (0x00UL << PCU_PRCR_PUE10_Pos) // PC10
		| (0x01UL << PCU_PRCR_PUE8_Pos)  // PC8   ||------RS485 TX
		| (0x00UL << PCU_PRCR_PUE7_Pos)  // PC7   ||------RS485 RX
		| (0x00UL << PCU_PRCR_PUE1_Pos)  // PC1
		| (0x00UL << PCU_PRCR_PUE0_Pos)  // PC0
		;

	// PORT - D
	PD->MR1 = 0x00UL
		| (0x04UL << PCU_MR1_P3MUX_Pos)  // 0 : PD3,  1 : MISO  2 : SDA  3 :  4 : TXD0  7 : SXIN     ||------TX (NXP CONTROLLER)
		| (0x04UL << PCU_MR1_P2MUX_Pos)  // 0 : PD2,  1 : MOSI  2 : SCL  3 :  4 : RXD0  7 : SXOUT    ||------RX (NXP CONTROLLER)
		;

	PD->CR = 0x00 // 0 : Push-pull output, 1 : Open-drain output, 2 / 3 : Input
		| (0x01UL << PCU_CR_P3_Pos)  // PD3  ||------TX (NXP CONTROLLER) 
		| (0x03UL << PCU_CR_P2_Pos)  // PD2  ||------RX (NXP CONTROLLER)
		;

	PD->PRCR = 0x00 // 0 / 1 : Disable pull-up/down resistor, 2 : Enable pull-up resistor, 3 : Enable Pull-down resistor
		| (0x00UL << PCU_PRCR_PUE3_Pos)  // PD3   ||------TX (NXP CONTROLLER)
		| (0x03UL << PCU_PRCR_PUE2_Pos)  // PD2   ||------RX (NXP CONTROLLER
		;

	// Disable Writing Permittion of ALL PCU register.
	PORT_ACCESS_DIS();


	// Set VFO Port (PB6)
	//HAL_GPIO_SetDebouncePin(PB, 6, ENABLE);
	HAL_GPIO_EXTI_Config(PB, 6, IER_EDGE, ICR_FALLING_EDGE_INT);
	NVIC->ISER[0U] = (uint32_t)(1UL << (((uint32_t)(int32_t)12) & 0x1FUL));
	//NVIC_EnableIRQ(GPIOB_IRQn);
	
	// Set PD2 as external interrupt for PWM capture
//	HAL_GPIO_SetDebouncePin(PD, 2, ENABLE);
//	HAL_GPIO_EXTI_Config(PD, 2, IER_EDGE, ICR_FALLING_EDGE_INT);
//	NVIC_EnableIRQ(GPIOD_IRQn);

}

void USER_OPAMP_Init(void)
{
	SCU->PER2 &= ~(1UL << SCU_PER2_OPAMP_Pos);
	SCU->PCER2 &= ~(1UL << SCU_PCER2_OPAMP_Pos);

	SCU->PER2 |= (1UL << SCU_PER2_OPAMP_Pos);
	SCU->PCER2 |= (1UL << SCU_PCER2_OPAMP_Pos);
	
	
	OPAMP->CR  = 0x00
		| (0x00 << OPAMP_CR_UGAINEN_Pos)
		| (0x01 << OPAMP_CR_AMPEN_Pos)
		;
	
}

void MDL_IPM_Fault_Setting(void)
{
//    //PB debounce CLK Setting
//    SCU->MCCR5 =  0x00
//        | (0x00UL << SCU_MCCR5_PGBDCSEL_Pos)  //LSI 500kHz
//        | (0x01UL << SCU_MCCR5_PGBDCDIV_Pos)  //div 1
//        ;
//    HAL_GPIO_SetDebouncePin(PB, 6, ENABLE);
//    HAL_GPIO_EXTI_Config(PB, 6, IER_EDGE, ICR_FALLING_EDGE_INT);
//    NVIC_EnableIRQ(GPIOB_IRQn);
}
void MDL_FRT_Init(void)
{
    SCU->MCCR6 =  0x00
        | (0x04UL << SCU_MCCR6_FRTCSEL_Pos)  //MCLK 80MHz
        | (0x01UL << SCU_MCCR6_FRTCDIV_Pos)  //div 1
        ;
    
    SCU->PER1 &= (~SCU_PER1_FRT_Msk);
    SCU->PCER1 &= (~SCU_PCER1_FRT_Msk);

    SCU->PER1 |= (1 << SCU_PER1_FRT_Pos);
    SCU->PCER1 |= (1 << SCU_PCER1_FRT_Pos);
    
    FRT->CTRL = 0x00
        | (0x00UL << FRT_CTRL_OVFIE_Pos)
        | (0x00UL << FRT_CTRL_MATCHIE_Pos)
        | (0x00UL << FRT_CTRL_MODE_Pos)
        | (0x01UL << FRT_CTRL_EN_Pos)
        ;
    
    FRT->MCNT = 0;
    
    FRT->CNT = 0;
        
    FRT->STAT = 0x00
        | (0x01UL << FRT_STAT_OVFIF_Pos)
        | (0x01UL << FRT_STAT_MATCHIF_Pos)
        ;
}

void MDL_FRT_CNT_Zero(void)
{
    FRT->CNT = 0;
}

uint32_t MDL_FRT_CNT_Read(void)
{
    return (FRT->CNT);
}
void MDL_DAC_Init(void)
{
#if (USE_DAC_DEBUG == ON)
	SPI_CFG_Type SP0_config;

	SP0_config.Databit = SPI_DS_16BITS;
	SP0_config.CPHA = SPI_CPHA_LO;
	SP0_config.CPOL = SPI_CPOL_HI;
	SP0_config.DataDir = SPI_MSB_FIRST;
	SP0_config.Mode = SPI_MASTER_MODE;
	SP0_config.BaudRate = 100;//10;

	SPI_Init(SPI, &SP0_config);
	SPI_DelayConfig(SPI, 5, 0, 2);
	SPI_Cmd(SPI, ENABLE); // Enable SPI

	MDL_DAC_SetData(0, 0x7FF);
	MDL_DAC_SetData(1, 0x7FF);
	MDL_DAC_SetData(2, 0x7FF);
	MDL_DAC_SetData(3, 0x7FF);
#endif // (USE_DAC_DEBUG == ON)
}

void MDL_DAC_SetData(uint32_t Channel, uint16_t Data)
{
#if (USE_DAC_DEBUG == ON)
	uint16_t SPI_Data;

	PC->ODR &= ~(1 << 15);
	SPI_Data = (((Channel & 0x3) << 14) | (Data & 0xFFF) | 0x1000);
	SPI_SendData(SPI, SPI_Data);
	while ((SPI_GetStatus(SPI) & SPI_STAT_TXBUF_EMPTY) != SPI_STAT_TXBUF_EMPTY) {
		__NOP();
	}
	while ((SPI_GetStatus(SPI) & SPI_STAT_IDLE) != SPI_STAT_IDLE) {
		__NOP();
	}
	PC->ODR |= (1 << 15);
#endif // (USE_DAC_DEBUG == ON)
}



void MDL_WDT_Init(void)
{
  uint32_t reg_val;
  /* Watchdog clock src = MCLK(80hz) / 1 = 80Mhz */
	reg_val = SCU->MCCR1;
	reg_val &= ~(SCU_MCCR1_WDTCSEL_Msk | SCU_MCCR1_WDTCDIV_Msk);
	reg_val |= (4 << SCU_MCCR1_WDTCSEL_Pos   /* Clock cource  = MCLK */
						| 1 << SCU_MCCR1_WDTCDIV_Pos); /* Clock divider = 1 */
	SCU->MCCR1 = reg_val;


	WDT->AEN = 0xA55A;

	WDT->CON = 0
		| (1 << 15) // WDBG      0 : Watchdog counter running when debug mode, 1 : Watchdog counter stoped when debug mode
		| (0 << 8)  // WUF       Watchdog timer underflow flag
		| (0 << 7)  // WDTIE     0 : Disable interrupt, 1 : Enable interrupt
		| (1 << 6)  // WDTRE     0 : Disable reset, 1 : Enable reset
		| (0 << 4)  // WDTEN     0 : Watch dog counter disabled, 1 : Watch dog counter enabled
		| (1 << 3)  // CKSEL     0 : PCLK, 1 : External clock
		| (0 << 0)  // WPRS[2:0] Counter clock prescaler
		;

	WDT->LR = 0xFFFFFFFF;

	WDT->AEN = 0x0;
}

void MDL_WDT_Start(void)
{
	WDT->AEN = 0xA55A;
	WDT->CON |= (1 << 4);
	WDT->AEN = 0x0;
}

void MDL_WDT_Clear(void)
{
	WDT->AEN = 0x555A;
}


/* Public Functions ----------------------------------------------------------- */
/*********************************************************************
 * @brief		Initializes the SPIx peripheral according to the specified
 *              parameters in the SPI_ConfigStruct.
 * @param[in]	SPIx SPI peripheral selected, should be:
 * 				 	- SPI	:SPI0~1 peripheral
 * @param[in]	SPI_ConfigStruct Pointer to a SPI_CFG_Type structure that
 * 				contains the configuration information for the specified
 * 				SPI peripheral.
 * @return 		None
 *********************************************************************/
void SPI_Init(SPI_Type *SPIx, SPI_CFG_Type *SPI_ConfigStruct)
{
	uint32_t tmp;
//	uint32_t prescale, cr0_div, cmp_clk, ssp_clk;

		
	/* SPI0 enable */
	SCU->PER2 &= ~(SCU_PER2_SPI_Msk);
	SCU->PCER2 &= ~(SCU_PCER2_SPI_Msk);
	
	SCU->PER2 |= (SCU_PER2_SPI_Msk);
	SCU->PCER2 |= (SCU_PCER2_SPI_Msk);
		
	
	/* Configure SPI, interrupt is disable, LoopBack mode is disable,
	 * SPI is disable, SS is auto mode.
	 */
	SPIx->EN = 0;
	
	tmp = 0
	|(1<<SPI_CR_TXBC_Pos)  // TXBC tx buffer clear  
	|(1<<SPI_CR_RXBC_Pos)  // RXBC rx buffer clear
	|(0<<SPI_CR_DTXIE_Pos)  // TXDIE
	|(0<<SPI_CR_DRXIE_Pos)  // RXDIE
	|(0<<SPI_CR_SSCIE_Pos)  // SSCIE
	|(0<<SPI_CR_TXIE_Pos)  // TXIE
	|(0<<SPI_CR_RXIE_Pos)  // RXIE
	|(0<<SPI_CR_SSMOD_Pos)  // SSMOD       0:SS auto, 1:SS is controlled by SSOUT
	|(0<<SPI_CR_SSOUT_Pos)  // SSOUT        0:SS is low, 1:SS is high
	|(0<<SPI_CR_LBE_Pos)  // LBE             loop-back mode 
	|(0<<SPI_CR_SSMASK_Pos)  // SSMASK     0:receive data when SS signal is active, 1:receive data at SCLK edge
	|(1<<SPI_CR_SSMO_Pos)   // SSMO          0:SS output signal is disabled, 1:SS output signal is enabled
	|(0<<SPI_CR_SSPOL_Pos)   // SSPOL         0:SS is active-low, 1:SS is active-high 
	|((SPI_ConfigStruct->Mode & 0x01) << SPI_CR_MS_Pos)   // MS               0:slave mode, 1:master mode 
	|((SPI_ConfigStruct->DataDir & 0x01) << SPI_CR_MSBF_Pos)   // MSBF           0:LSB first, 1:MSB first
	|((SPI_ConfigStruct->CPHA & 0x01) << SPI_CR_CPHA_Pos)   // CPHA
	|((SPI_ConfigStruct->CPOL & 0x01) << SPI_CR_CPOL_Pos)   // CPOL
	|((SPI_ConfigStruct->Databit & SPI_DS_BITMASK)<< SPI_CR_BITSZ_Pos)   // BITSZ           0:8bit, 1:9bit, 2:16bit, 3:17bit
		;
	SPIx->CR = tmp;
	
	if (SPI_ConfigStruct->Mode == SPI_MASTER_MODE){
		SPIx->BR = (SPI_ConfigStruct->BaudRate & 0xFFFF); // PCLK / (BR + 1) ex) if BR=71, 72Mhz / (71+1)
	} else { // SPI_SLAVE_MODE   if using slave, BR has fast clock set and LR has minimum set. 
		SPIx->BR = 2; // PCLK / (BR + 1) ex) if BR=2 and PCLK=72Mhz,  72Mhz / (2 +1)	
	}
	
	SPIx->LR = 0
	|(1<<SPI_LR_SPL_Pos)  // SPL >= 1 
	|(1<<SPI_LR_BTL_Pos)   // BTL >= 1
	|(1<<SPI_LR_STL_Pos)   // STL >= 1
		;		
}
/**********************************************************************
 * @brief		Enable or disable SPI peripheral's operation
 * @param[in]	SPIx	SPI peripheral, should be:
 * 				 	- SPI	:SPI0~1 peripheral
 * @param[in]	NewState New State of SPIx peripheral's operation, should be:
 * 					- ENABLE
 * 					- DISABLE
 * @return 		none
 **********************************************************************/
void SPI_Cmd(SPI_Type* SPIx, FunctionalState NewState)
{
	if (NewState == ENABLE)
	{
		SPIx->EN = 1;
	} else {
		SPIx->EN = 0;
	}
}
/**********************************************************************
 * @brief		configure SPI delay length 
 * @param[in]	SPIx	SPI peripheral, should be:
 * 				 	- SPI	:SPI0~1 peripheral
 * @param[in]	StartDelay : SPL >= 1 (1~255)
 * @param[in]	BurstDelay : BTL >= 1 (1~255)
 * @param[in]	StopDelay : STL >= 1 (1~255)
 * @return 		none
 **********************************************************************/
void SPI_DelayConfig(SPI_Type* SPIx, uint8_t StartDelay, uint8_t BurstDelay,uint8_t StopDelay)
{
	if (SPIx->CR & (SPI_MASTER_MODE << 5)){
		SPIx->LR = 0
		|((StopDelay&0xFF)<<SPI_LR_SPL_Pos)  // SPL >= 1 (1~255) 
		|((BurstDelay&0xFF)<<SPI_LR_BTL_Pos)   // BTL >= 1 (1~255)
		|((StartDelay&0xFF)<<SPI_LR_STL_Pos)   // STL >= 1 (1~255)
			;
	} else {
		SPIx->LR = 0
		|(1<<SPI_LR_SPL_Pos)  // SPL >= 1 
		|(1<<SPI_LR_BTL_Pos)   // BTL >= 1
		|(1<<SPI_LR_STL_Pos)   // STL >= 1
			;
	}
}
/**********************************************************************
 * @brief		Transmit a single data through SPIx peripheral
 * @param[in]	SPIx	SPI peripheral selected, should be:
 * 				 	- SPI	:SPI0~1 peripheral
 * @param[in]	Data	Data to transmit 
 * @return 		none
 **********************************************************************/
void SPI_SendData(SPI_Type* SPIx, uint32_t Data)
{
	SPIx->TDR = (Data);
}

// User Defined functions





void GPIODE_IRQHandler(void)
{
//	uint32_t Status;

//	Status = HAL_GPIO_EXTI_GetStatus(PB);
	
//	HAL_GPIO_EXTI_ClearPin(PB, Status);
}

/* --------------------------------- End Of File ------------------------------ */
