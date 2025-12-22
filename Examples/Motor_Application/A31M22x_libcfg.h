/**
 *******************************************************************************
 * @file        A31M22x_libcfg.h
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



#ifndef _A31M22x_LIBCFG_H_
#define _A31M22x_LIBCFG_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------- */


/* Public Macro --------------------------------------------------------------- */
// Direct Memory Access Controller
#define _DMAC

// Watchdog Timer
#define _WDT

// 16-bit Timer
#define _TIMER

// Free-run Timer
#define _FRT

// Universal Asynchronous Receiver/Transmitter
#define _UART

// Serial Peripheral Interface
#define _SPI

// Inter Integrated Circuit Interface
#define _I2C

// Motor Pulse Width Modulation
#define _MPWM

// Gate Driver
#define _GD

// Analog-to-Digital Converter
#define _ADC

// Digital-to-Analog Converter
#define _DAC

// COMPARATOR
#define _CMP

// CRC
#define _CRC


/* Public Typedef ------------------------------------------------------------- */


/* Exported Public Variable --------------------------------------------------- */


/* Exported Public Function --------------------------------------------------- */


#ifdef __cplusplus
}
#endif

#endif // _A31M22x_LIBCFG_H_

/* --------------------------------- End Of File ------------------------------ */
