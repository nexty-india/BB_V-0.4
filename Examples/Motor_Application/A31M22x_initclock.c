/**
 *******************************************************************************
 * @file        a31m22x_initclock.c
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


/* Includes ------------------------------------------------------------------- */
#include "A31M22x.h"
#include "A31M22x_scu.h"
#include "A31M22x_pcu.h"
#include "A31M22x_cfmc.h"

#include "A31M22x_initclock.h"
#include "MotorApplicationLayer.h"


/* Private Macro -------------------------------------------------------------- */
//#define USED_CLKO

//#define USED_HSI // 32 MHz
//#define USED_HSE // 4 ~ 16 MHz (FPGA 32 MHz)
//#define USED_LSE // 32.768KHz
#define USED_PLL // 80 MHz


/* Private Typedef ------------------------------------------------------------ */


/* Private Variable ----------------------------------------------------------- */


/* Private Function Prototype ------------------------------------------------- */
#if defined(__DEF_A31M22x__)
void HAL_SCU_ClockMonitoringCmd(uint32_t ClockMonitoring, FunctionalState NewState);
void HAL_SCU_ClockSRCCmd(uint32_t ClockSource, FunctionalState NewState);
void HAL_SCU_SystemClockChange(uint32_t MCLKSource);
void HAL_SCU_PLLPREDIVCmd(uint8_t PLLPREDIV);
void HAL_SCU_PLLINCLKCmd(uint32_t PLLClock);
void HAL_SCU_PCLKDIVCmd(uint32_t PCLKDIV);
void HAL_SCU_HCLKDIVCmd(uint32_t HCLKDIV);
Status HAL_SCU_PLL_ClockConfig (uint32_t PLLMODE, uint32_t PREDIV, uint32_t POSTDIV1, uint32_t POSTDIV2, uint32_t OUTDIV, FunctionalState NewState);
void HAL_SCU_ClockOutput(uint32_t CLKSource, uint32_t CLKODIV, FunctionalState NewState);
#endif
/* Public Variable ------------------------------------------------------------ */


/* Public Function ------------------------------------------------------------ */
/***************************************************************************//**
* @brief      Initialize system clock
* @param      None
* @return     None
*******************************************************************************/
void A31M22x_InitClock(void)
{
	// Flash Wait Config
	CFMC_WaitCmd(2); // @ 80MHz

	// CLKO Function Setting, Must be setting CLKO function at PB5
#ifdef USED_CLKO
	HAL_GPIO_ConfigFunction(PC, 9, PC9_MUX_CLKO);

	HAL_SCU_ClockOutput(SCU_COR_CLKOINSEL_MCLK, 0x5, ENABLE); // CLKOINSEL = MCLK, CLKO = CLKOINSEL / (CLKODIV * 2)
#else
	HAL_SCU_ClockOutput(SCU_COR_CLKOINSEL_MCLK, 0x5, DISABLE);
#endif

	// MCLK Monitoring Disable
	HAL_SCU_ClockMonitoringCmd(SCU_CMR_MCLKMNT, DISABLE);



#ifdef USED_HSI
	HAL_SCU_ClockSRCCmd(SCU_CSCR_HSICON_Msk, ENABLE);
	
	HAL_SCU_HCLKDIVCmd(0); // HCLK = MCLK
	HAL_SCU_PCLKDIVCmd(0); // PCLK = HCLK

	// Main Clock is HSI
	HAL_SCU_SystemClockChange(SCU_SCCR_MCLKSEL_HSI);

	SystemCoreClock = 32000000;
	SystemPeriClock = 32000000;

	CFMC_WaitCmd(1); // ~ 56MHz

	HAL_SCU_MiscClockConfig(7, UART_TYPE, SCU_MCCR_CSEL_HSI, 2);
#endif

#ifdef USED_HSE
	HAL_SCU_ClockSRCCmd(SCU_CSCR_HSECON_Msk, ENABLE);

	HAL_SCU_HCLKDIVCmd(0); // HCLK = MCLK
	HAL_SCU_PCLKDIVCmd(0); // PCLK = HCLK

	HAL_SCU_SystemClockChange(SCU_SCCR_MCLKSEL_HSE);

	SystemCoreClock = 8000000;
	SystemPeriClock = 8000000;

	CFMC_WaitCmd(0); // @8MHz

	HAL_SCU_MiscClockConfig(7, UART_TYPE, SCU_MCCR_CSEL_HSE, 2);
#endif

#ifdef USED_PLL
	HAL_SCU_ClockSRCCmd(SCU_CSCR_HSECON_Msk, ENABLE);

	HAL_SCU_HCLKDIVCmd(0); // HCLK = MCLK
	HAL_SCU_PCLKDIVCmd(0); // PCLK = HCLK

	HAL_SCU_PLLINCLKCmd(SCU_SCCR_PLLCLKSEL_HSI); // PLL Input Clock = HSE

	HAL_SCU_PLLPREDIVCmd(0); // PLLINCLK = 8MHz

	HAL_SCU_PLL_ClockConfig(0, 7, 19, 0, 0, ENABLE);

	HAL_SCU_SystemClockChange(SCU_SCCR_MCLKSEL_PLL);

	SystemCoreClock = 80000000;
	SystemPeriClock = 80000000;

	CFMC_WaitCmd(2); // at 80MHz

	HAL_SCU_MiscClockConfig(7, UART_TYPE, SCU_MCCR_CSEL_PLL, 2);
#endif

#ifdef USED_LSE
	HAL_SCU_ClockSRCCmd(SCU_CSCR_LSECON_Msk, ENABLE);

	HAL_SCU_HCLKDIVCmd(0); // HCLK = MCLK
	HAL_SCU_PCLKDIVCmd(0); // PCLK = HCLK

	HAL_SCU_SystemClockChange(SCU_SCCR_MCLKSEL_LSE);

	SystemCoreClock = 32768;
	SystemPeriClock = 32768;

	CFMC_WaitCmd(1); // ~ 56MHz

	HAL_SCU_MiscClockConfig(7, UART_TYPE, SCU_MCCR_CSEL_LSE, 2);
#endif
}


/* Private Function ----------------------------------------------------------- */

/***************************************************************************//**
* @brief      Set miscellaneous clock for peripheral
* @param[in]  MCCRNumber : Miscellaneous number, should be
*              - SCU_MCCR_NUMBER_1 : WDT, Systick
*              - SCU_MCCR_NUMBER_3 : Timer03 (Timer0 to Timer3)
*              - SCU_MCCR_NUMBER_4 : GPIO A
*              - SCU_MCCR_NUMBER_5 : GPIO B, GPIO C
*              - SCU_MCCR_NUMBER_6 : FRT
*              - SCU_MCCR_NUMBER_7 : UART (UART0 to UART1)
* @param[in]  Peripheral : Peripheral, should be
*              - WDT_TYPE
*              - SYSTICK_TYPE
*              - TIMER03_TYPE
*              - PGA_TYPE
*              - PGB_TYPE
*              - PGC_TYPE
*              - FRT_TYPE
*              - UART_TYPE
* @param[in]  ClockSource : Miscellaneous clock source, should be
*              - SCU_MCCR_CSEL_LSI  : Miscellaneous clock is LSI
*              - SCU_MCCR_CSEL_LSE  : Miscellaneous clock is LSE
*              - SCU_MCCR_CSEL_MCLK : Miscellaneous clock is MCLK
*              - SCU_MCCR_CSEL_HSI  : Miscellaneous clock is HSI
*              - SCU_MCCR_CSEL_HSE  : Miscellaneous clock is HSE
*              - SCU_MCCR_CSEL_PLL  : Miscellaneous clock is PLL
* @param[in]  ClockDIV : Miscellaneous clock divider, should be
*              - 0x00 : Disable
*              - 0x01 ~ 0xFF : Clock = Source / N
* @return     None
*******************************************************************************/
void HAL_SCU_MiscClockConfig(uint32_t MCCRNumber, uint32_t Peripheral, uint32_t ClockSource, uint32_t ClockDIV)
{
	uint32_t Reg32;
	
	switch (MCCRNumber) {
	case SCU_MCCR_NUMBER_1 :
		Reg32 = SCU->MCCR1;
		if (Peripheral == WDT_TYPE) {
			Reg32 &= (~(SCU_MCCR1_WDTCSEL_Msk | SCU_MCCR1_WDTCDIV_Msk));
			Reg32 |= (0x00UL
				| ((ClockSource << SCU_MCCR1_WDTCSEL_Pos) & SCU_MCCR1_WDTCSEL_Msk)
				| ((ClockDIV << SCU_MCCR1_WDTCDIV_Pos) & SCU_MCCR1_WDTCDIV_Msk)
				);
		} else if (Peripheral == SYSTICK_TYPE) {
			Reg32 &= (~(SCU_MCCR1_STCSEL_Msk | SCU_MCCR1_STDIV_Msk));		//220914 fixed
			Reg32 |= (0x00UL
				| ((ClockSource << SCU_MCCR1_STCSEL_Pos) & SCU_MCCR1_STCSEL_Msk)
				| ((ClockDIV << SCU_MCCR1_STDIV_Pos) & SCU_MCCR1_STDIV_Msk)	//220914 fixed
				);
		}
		SCU->MCCR1 = Reg32;
		break;

	case SCU_MCCR_NUMBER_3 :
		Reg32 = SCU->MCCR3;
		if (Peripheral == TIMER03_TYPE) {
			Reg32 &= (~(SCU_MCCR3_TIMER03CSEL_Msk | SCU_MCCR3_TIMER03CDIV_Msk));
			Reg32 |= (0x00UL
				| ((ClockSource << SCU_MCCR3_TIMER03CSEL_Pos) & SCU_MCCR3_TIMER03CSEL_Msk)
				| ((ClockDIV << SCU_MCCR3_TIMER03CDIV_Pos) & SCU_MCCR3_TIMER03CDIV_Msk)
				);
		}
		SCU->MCCR3 = Reg32;
		break;

	case SCU_MCCR_NUMBER_4 :
		Reg32 = SCU->MCCR4;
		if (Peripheral == PGA_TYPE){
			Reg32 &= (~(SCU_MCCR4_PGADCSEL_Msk | SCU_MCCR4_PGADCDIV_Msk));
			Reg32 |= (0x00UL
				| ((ClockSource << SCU_MCCR4_PGADCSEL_Pos) & SCU_MCCR4_PGADCSEL_Msk)
				| ((ClockDIV << SCU_MCCR4_PGADCDIV_Pos) & SCU_MCCR4_PGADCDIV_Msk)
				);
		}
		SCU->MCCR4 = Reg32;
		break;

	case SCU_MCCR_NUMBER_5 :
		Reg32 = SCU->MCCR5;
		if (Peripheral == PGC_TYPE) {
			Reg32 &= (~(SCU_MCCR5_PGCDCSEL_Msk | SCU_MCCR5_PGCDCDIV_Msk));
			Reg32 |= (0x00UL
				| ((ClockSource << SCU_MCCR5_PGCDCSEL_Pos) & SCU_MCCR5_PGCDCSEL_Msk)
				| ((ClockDIV << SCU_MCCR5_PGCDCDIV_Pos) & SCU_MCCR5_PGCDCDIV_Msk)
				);
		} else if (Peripheral == PGB_TYPE) {
			Reg32 &= (~(SCU_MCCR5_PGBDCSEL_Msk | SCU_MCCR5_PGBDCDIV_Msk));
			Reg32 |= (0x00UL
				| ((ClockSource << SCU_MCCR5_PGBDCSEL_Pos) & SCU_MCCR5_PGBDCSEL_Msk)
				| ((ClockDIV << SCU_MCCR5_PGBDCDIV_Pos) & SCU_MCCR5_PGBDCDIV_Msk)
				);
		}
		SCU->MCCR5=Reg32;
		break;

	case SCU_MCCR_NUMBER_6 :
		Reg32 = SCU->MCCR6;
		if (Peripheral == FRT_TYPE) {
			Reg32 &= (~(SCU_MCCR6_FRTCSEL_Msk | SCU_MCCR6_FRTCDIV_Msk));
			Reg32 |= (0x00UL
				| ((ClockSource << SCU_MCCR6_FRTCSEL_Pos) & SCU_MCCR6_FRTCSEL_Msk)
				| ((ClockDIV << SCU_MCCR6_FRTCDIV_Pos) & SCU_MCCR6_FRTCDIV_Msk)
				);
		}
		SCU->MCCR6 = Reg32;
		break;

	case SCU_MCCR_NUMBER_7 :
		Reg32 = SCU->MCCR7;
		if (Peripheral == UART_TYPE) {
			Reg32 &= (~(SCU_MCCR7_UARTCSEL_Msk | SCU_MCCR7_UARTCDIV_Msk));
			Reg32 |= (0x00UL
				| ((ClockSource << SCU_MCCR7_UARTCSEL_Pos) & SCU_MCCR7_UARTCSEL_Msk)
				| ((ClockDIV << SCU_MCCR7_UARTCDIV_Pos) & SCU_MCCR7_UARTCDIV_Msk)
				);
		}
		SCU->MCCR7 = Reg32;
		break;
	}
}

#if defined(__DEF_A31M22x__)
/***************************************************************************//**
* @brief      Command clock monitoring
* @param[in]  Clock : clock of monitoring, should be
*              - SCU_CMR_MCLKREC  : Auto recovery
*              - SCU_CMR_MCLKMNT  : MCLK monitoring
*              - SCU_CMR_MCLKIE   : MCLK interrupt
*              - SCU_CMR_HSEMNT   : HSE monitoring
*              - SCU_CMR_HSEIE    : MCLK interrupt
* @param[in]  NewState
*               - ENABLE : Enable
*               - DISABLE : Disable
* @return     None
*******************************************************************************/
void HAL_SCU_ClockMonitoringCmd(uint32_t ClockMonitoring, FunctionalState NewState)
{
	uint32_t Reg32;

	Reg32 = SCU->CMR;
	Reg32 &= (~ClockMonitoring);
	if (NewState == ENABLE) {
		Reg32 |= ClockMonitoring;
	}
	SCU->CMR = Reg32;
}

/***************************************************************************//**
* @brief      Command clock source
* @param[in]  ClockSource : Clock source, should be
*              - SCU_CSCR_LSICON : LSI (Low Speed Internal, 500 kHz)
*              - SCU_CSCR_HSICON : HSI (High Speed Internal, 32 MHz)
*              - SCU_CSCR_HSECON : LSI (High Speed External, 4 to 16 MHz)
* @param[in]  NewState
*               - ENABLE : Enable clock
*               - DISABLE : Disable clock
* @return     None
*******************************************************************************/
void HAL_SCU_ClockSRCCmd(uint32_t ClockSource, FunctionalState NewState)
{
	uint32_t Reg32;
	volatile uint32_t i;

	Reg32 = SCU->CSCR;
	Reg32 &= (~ClockSource);
	if (NewState == ENABLE) {
		Reg32 |= ClockSource;
	}
	SCU->CSCR = Reg32;

	// Wait stable
	for (i = 0; i < 100; i++);
}

/***************************************************************************//**
* @brief      Command HCLK input clock divider
* @param[in]  HCLKDIV : HCLK divider, should be
*              - SCU_SCCR_HCLKDIV_1   : HCLK = MCLK
*              - SCU_SCCR_HCLKDIV_2   : HCLK = MCLK / 2
*              - SCU_SCCR_HCLKDIV_4   : HCLK = MCLK / 4
*              - SCU_SCCR_HCLKDIV_8   : HCLK = MCLK / 8
*              - SCU_SCCR_HCLKDIV_16  : HCLK = MCLK / 16
*              - SCU_SCCR_HCLKDIV_32  : HCLK = MCLK / 32
*              - SCU_SCCR_HCLKDIV_64  : HCLK = MCLK / 64
*              - SCU_SCCR_HCLKDIV_128 : HCLK = MCLK / 128
*              - SCU_SCCR_HCLKDIV_256 : HCLK = MCLK / 256
*              - SCU_SCCR_HCLKDIV_512 : HCLK = MCLK / 512
* @return     None
*******************************************************************************/
void HAL_SCU_HCLKDIVCmd(uint32_t HCLKDIV)
{
	uint32_t Reg32;

	Reg32 = SCU->SCCR;
	Reg32 &= (~SCU_SCCR_HCLKDIV_Msk);
	Reg32 |= ((HCLKDIV << SCU_SCCR_HCLKDIV_Pos) & SCU_SCCR_HCLKDIV_Msk);
	SCU->SCCR = Reg32;
}

/***************************************************************************//**
* @brief      Command PCLK input clock divider
* @param[in]  PCLKDIV : PCLK divider, should be
*              - SCU_SCCR_PCLKDIV_1  : PCLK = HCLK
*              - SCU_SCCR_PCLKDIV_2  : PCLK = HCLK / 2
*              - SCU_SCCR_PCLKDIV_4  : PCLK = HCLK / 4
*              - SCU_SCCR_PCLKDIV_8  : PCLK = HCLK / 8
*              - SCU_SCCR_PCLKDIV_16 : PCLK = HCLK / 16
* @return     None
*******************************************************************************/

void HAL_SCU_PCLKDIVCmd(uint32_t PCLKDIV)
{
	uint32_t Reg32;

	Reg32 = SCU->SCCR;
	Reg32 &= (~SCU_SCCR_PCLKDIV_Msk);
	Reg32 |= ((PCLKDIV << SCU_SCCR_PCLKDIV_Pos) & SCU_SCCR_PCLKDIV_Msk);
	SCU->SCCR = Reg32;
}

/***************************************************************************//**
* @brief      Command PLL input clock Source
* @param[in]  PLLClock : PLL input clock, should be
*              - SCU_SCCR_PLLCLKSEL_HSI : PLL input = HSI
*              - SCU_SCCR_PLLCLKSEL_HSE : PLL input = HSE
* @return     None
*******************************************************************************/
void HAL_SCU_PLLINCLKCmd(uint32_t PLLClock)
{
	uint32_t Reg32;

	Reg32 = SCU->SCCR;
	Reg32 &= (~SCU_SCCR_PLLCLKSEL_Msk);
	Reg32 |= ((PLLClock << SCU_SCCR_PLLCLKSEL_Pos) & SCU_SCCR_PLLCLKSEL_Msk);
	SCU->SCCR = Reg32;
}

/***************************************************************************//**
* @brief      Command PLL input clock divider
* @param[in]  PLLPREDIV : PCLK input clock divider, should be
*              - SCU_SCCR_PLLPREDIV_1 : PLL input = PLL input source
*              - SCU_SCCR_PLLPREDIV_2 : PLL input = PLL input source / 2
*              - SCU_SCCR_PLLPREDIV_4 : PLL input = PLL input source / 4
*              - SCU_SCCR_PLLPREDIV_8 : PLL input = PLL input source / 8
* @return     None
*******************************************************************************/
void HAL_SCU_PLLPREDIVCmd(uint8_t PLLPREDIV)
{
	uint32_t Reg32;

	Reg32 = SCU->SCCR;
	Reg32 &= (~SCU_SCCR_PLLPREDIV_Msk);
	Reg32 |= ((PLLPREDIV << SCU_SCCR_PLLPREDIV_Pos) & SCU_SCCR_PLLPREDIV_Msk);
	SCU->SCCR = Reg32;
}

/***************************************************************************//**
* @brief      Command MCLK (main clock) source
* @param[in]  MCLKSource : MCLK source, should be
*              - SCU_SCCR_MCLKSEL_LSI : MCLK source is LSI
*              - SCU_SCCR_MCLKSEL_LSI : MCLK source is LSE
*              - SCU_SCCR_MCLKSEL_HSI : MCLK source is HSI
*              - SCU_SCCR_MCLKSEL_HSE : MCLK source is HSE
*              - SCU_SCCR_MCLKSEL_PLL : MCLK source is PLL
* @return     None
*******************************************************************************/
void HAL_SCU_SystemClockChange(uint32_t MCLKSource)
{
	uint32_t Reg32;

	Reg32 = SCU->SCCR;
	Reg32 &= (~SCU_SCCR_MCLKSEL_Msk);
	Reg32 |= ((MCLKSource << SCU_SCCR_MCLKSEL_Pos) & SCU_SCCR_MCLKSEL_Msk);
	SCU->SCCR = Reg32;
}

/**********************************************************************//**
 * @brief 		PLL Control Register  
 * @param[in]	clock Function mode, should be:
 * 					
 *								Fin*(N1+1)
 *					Fout = --------------------- x D
 *							(R+1)*(N2+1)*(P+1)
 *
 *					-> List
 * 					  D  = PLLMODE  [20:20]
 * 					  R  = PREDIV   [18:16]
 *			 		  N1 = POSTDIV1 [15:08]
 *					  N2 = POSTDIV2 [07:04]
 *					  P  = OUTDIV   [03:00]

* @return     None
*******************************************************************************/
Status HAL_SCU_PLL_ClockConfig (uint32_t PLLMODE, uint32_t PREDIV, uint32_t POSTDIV1, uint32_t POSTDIV2, uint32_t OUTDIV, FunctionalState NewState)
{
	__IO uint32_t StartUpCounter = 0; 
	__IO uint32_t reg_val;
	__IO uint32_t i;
	
	if (NewState == DISABLE){
		SCU->PLLCON =0;
		return SUCCESS;
	}
	else {
		SCU->PLLCON |= (1<<SCU_PLLCON_PLLEN_Pos);	// PLLEN	
		__NOP();	//1us wait
		
		reg_val = SCU->PLLCON;
		
		reg_val &= ~(0x001FFFFF);
		
		reg_val |= (1<<SCU_PLLCON_PLLRSTB_Pos) |(1<<SCU_PLLCON_BYPASSB_Pos) ;

		reg_val |= (PLLMODE | ((PREDIV&0x7)<<16) | ((POSTDIV1&0xFF)<<8) | ((POSTDIV2&0xF)<<4) | ((OUTDIV&0xF)<<0));

		SCU->PLLCON |= reg_val;	// PLL Configure setting
		
		/* wait over 190us */
		for(i=0;i<PLL_DELAY;i++); 
		
		/* Check the PLLCON State */
		while((SCU->PLLCON & (1UL<<31)) == RESET)
		{		
			/* Time out for HSE start up, in 1ms */
			if(StartUpCounter++ > PLL_STARTUP_TIMEOUT)
			{
				 return ERROR;
			}	
		}
		return SUCCESS;
	}
}
/***************************************************************************//**
* @brief      Command clock output
* @param[in]  CLKSource : Clock output source, should be
*              - SCU_COR_CLKOINSEL_LSI  : Clock output source is LSI
*              - SCU_COR_CLKOINSEL_MCLK : Clock output source is MCLK
*              - SCU_COR_CLKOINSEL_HSI  : Clock output source is HSI
*              - SCU_COR_CLKOINSEL_HSE  : Clock output source is HSE
*              - SCU_COR_CLKOINSEL_PLL  : Clock output source is PLL
* @param[in]  CLKODIV : Clock output divider, should be
*              - 0x00 ~ 0x0F
* @param[in]  NewState
*               - ENABLE : Enable clock output
*               - DISABLE : Disable clock output
* @return     None
*******************************************************************************/
void HAL_SCU_ClockOutput(uint32_t CLKSource, uint32_t CLKODIV, FunctionalState NewState)
{
	SCU->COR = 0
		| ((CLKSource << SCU_COR_CLKOINSEL_Pos) & SCU_COR_CLKOINSEL_Msk)
		| ((NewState << SCU_COR_CLKOEN_Pos) & SCU_COR_CLKOEN_Msk)
		| ((CLKODIV << SCU_COR_CLKODIV_Pos) & SCU_COR_CLKODIV_Msk)
		;
}
#endif

/* --------------------------------- End Of File ------------------------------ */
