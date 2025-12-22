/**
 *******************************************************************************
 * @file        A31M22x_initclock.h
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


#ifndef _a31m22x_INIT_CLOCK_H_
#define _a31m22x_INIT_CLOCK_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------- */
#include "A31M22x.h"
#include "aa_types.h"


/* Public Macro --------------------------------------------------------------- */
	#if defined(__DEF_A31M22x__)
#define SCU_CMR_MCLKREC                 (0x01UL << SCU_CMR_MCLKREC_Pos)
#define SCU_CMR_LSEMNT                 (0x01UL << SCU_CMR_LSEMNT_Pos)
#define SCU_CMR_LSEIE                  (0x01UL << SCU_CMR_LSEIE_Pos)
#define SCU_CMR_LSEFAIL                (0x01UL << SCU_CMR_LSEFAIL_Pos)
#define SCU_CMR_LSESTS                 (0x01UL << SCU_CMR_LSESTS_Pos)
#define SCU_CMR_MCLKMNT                 (0x01UL << SCU_CMR_MCLKMNT_Pos)
#define SCU_CMR_MCLKIE                  (0x01UL << SCU_CMR_MCLKIE_Pos)
#define SCU_CMR_MCLKFAIL                (0x01UL << SCU_CMR_MCLKFAIL_Pos)
#define SCU_CMR_MCLKSTS                 (0x01UL << SCU_CMR_MCLKSTS_Pos)
#define SCU_CMR_HSEMNT                  (0x01UL << SCU_CMR_HSEMNT_Pos)
#define SCU_CMR_HSEIE                   (0x01UL << SCU_CMR_HSEIE_Pos)
#define SCU_CMR_HSEFAIL                 (0x01UL << SCU_CMR_HSEFAIL_Pos)
#define SCU_CMR_HSESTS                  (0x01UL << SCU_CMR_HSESTS_Pos)

#define PLL_DELAY	160	// @HSE 8MHz
#define PLL_STARTUP_TIMEOUT 8
#endif

/* Public Typedef ------------------------------------------------------------- */


/* Exported Public Variable --------------------------------------------------- */


/* Exported Public Function --------------------------------------------------- */
void A31M22x_InitClock(void);
void HAL_SCU_ClockOutput(uint32_t CLKSource, uint32_t CLKODIV, FunctionalState NewState);
void HAL_SCU_MiscClockConfig(uint32_t MCCRNumber, uint32_t Peripheral, uint32_t ClockSource, uint32_t ClockDIV);

#ifdef __cplusplus
}
#endif

#endif // _a31m22x_INIT_CLOCK_H_

/* --------------------------------- End Of File ------------------------------ */
