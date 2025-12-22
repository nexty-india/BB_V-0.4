/**
 *******************************************************************************
 * @file        a31m22x_system.c
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

#include <stdint.h>
#include "a31m22x.h"
#include "a31m22x_cfmc.h"

#define A31M22X_DEFAULT_CORE_CLOCK      (4000000) //  4MHz
#define A31M22X_DEFAULT_PERI_CLOCK      (4000000) //  4MHz
#define A31M22X_DEFAULT_MAIN_CLOCK      (32000000) // 32MHz

uint32_t SystemMainClock = A31M22X_DEFAULT_MAIN_CLOCK;	// 32MHz
uint32_t SystemCoreClock = 32000000;	// 32MHz
uint32_t SystemPeriClock = 32000000;	// 32MHz
uint32_t SystemDelayCount;
uint32_t reg_val;

extern void SystemInit(void)
{
    __disable_irq();

    // Enable WDT Access
    WDT->AEN = 0xA55A;
    // Diable WDT
    WDT->CON = 0;

    // SCU Access Enable
    SCU->SYSTEN = 0x57;
    SCU->SYSTEN = 0x75;

    // GPIO Access Enable
    PORTEN->EN = 0x15;
    PORTEN->EN = 0x51;
	
    SystemMainClock = A31M22X_DEFAULT_MAIN_CLOCK;	// 32MHz
    SystemCoreClock = A31M22X_DEFAULT_CORE_CLOCK;	// 4MHz
    SystemPeriClock = A31M22X_DEFAULT_PERI_CLOCK;	//4MHz

    /* hclk = mclk, pclk = hclk */
    reg_val = SCU->SCCR;
    reg_val &= ~SCU_SCCR_HCLKDIV_Msk;
    reg_val &= ~SCU_SCCR_PCLKDIV_Msk;
    SCU->SCCR = reg_val;

    // =========================================================================
    // Flash Memory Control
    // =========================================================================

    // Instruction Cache Disable
    CFMC->CONF &= ~(CFMC_CONF_ICEN_Msk);

    // Instruction Cache Reset
    CFMC->CONF |= (0x01UL << CFMC_CONF_ICRST_Pos);

    // Flash Wait 2, Up to 80MHz
    CFMC->CONF = (CFMC->CONF & (~CFMC_CONF_LATENCY_Msk))
            | (2 << CFMC_CONF_LATENCY_Pos);

    __enable_irq();
	
}

void SystemDelay(uint32_t ms)
{
    uint32_t delay;

    if (ms)
    {
        delay = SystemDelayCount * ms;
        do
        {
            __NOP();
            delay--;
        }
        while (delay != 0);
    }
}
