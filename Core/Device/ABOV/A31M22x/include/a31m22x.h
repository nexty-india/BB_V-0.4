/**
 *******************************************************************************
 * @file        a31m22x.h
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

#ifndef A31M22X_H
#define A31M22X_H

#ifdef __cplusplus
extern "C" {
#endif


/* -------------------------  Interrupt Number Definition  ------------------------ */

typedef enum {
/* -----------------  Cortex-M0PLUS Processor Exceptions Numbers  ----------------- */
  Reset_IRQn                = -15,              /*!< -15  Reset Vector, invoked on Power up and warm reset                     */
  NonMaskableInt_IRQn       = -14,              /*!< -14  Non maskable Interrupt, cannot be stopped or preempted               */
  HardFault_IRQn            = -13,              /*!< -13  Hard Fault, all classes of Fault                                     */
  SVCall_IRQn               =  -5,              /*!< -5 System Service Call via SVC instruction                                */
  PendSV_IRQn               =  -2,              /*!< -2 Pendable request for system service                                    */
  SysTick_IRQn              =  -1,              /*!< -1 System Tick Timer                                                      */
/* ---------------------  A31M22x Specific Interrupt Numbers  --------------------- */
  LVI_IRQn                      =   0,              /*!<   0  LVI                                                              */
  SYSCLKFAIL_IRQn               =   1,              /*!<   1  SYSCLKFAIL                                                       */
  HSEFAIL_IRQn                  =   2,              /*!<   2  HSEFAIL                                                          */
  LSEFAIL_IRQn                  =   3,              /*!<   3  LSEFAIL                                                          */
  WDT_IRQn                      =   4,              /*!<   4  WDT                                                              */
  FRT_IRQn                      =   5,              /*!<   5  FRT                                                              */
  CFMC_IRQn                     =   6,              /*!<   6  CFMC                                                             */
  TIMER0_IRQn                   =   7,              /*!<   7  TIMER0                                                           */
  TIMER1_IRQn                   =   8,              /*!<   8  TIMER1                                                           */
  TIMER2_IRQn                   =   9,              /*!<   9  TIMER2                                                           */
  TIMER3_IRQn                   =  10,              /*!<  10  TIMER3                                                           */
  GPIOA_IRQn                    =  11,              /*!<  11  GPIOA                                                            */
  GPIOB_IRQn                    =  12,              /*!<  12  GPIOB                                                            */
  GPIOC_IRQn                    =  13,              /*!<  13  GPIOC                                                            */
  GPIOD_IRQn                    =  14,              /*!<  14  GPIOD                                                            */
  MPWMPRT_IRQn                  =  15,              /*!<  15  MPWMPRT                                                          */
  MPWMOVC_IRQn                  =  16,              /*!<  16  MPWMOVC                                                          */
  MPWM_IRQn                     =  17,              /*!<  17  MPWM                                                             */
  SPI_IRQn                      =  18,              /*!<  18  SPI                                                              */
  I2C_IRQn                      =  19,              /*!<  19  I2C                                                              */
  UART0_IRQn                    =  20,              /*!<  20  UART0                                                            */
  UART1_IRQn                    =  21,              /*!<  21  UART1                                                            */
  ADC_IRQn                      =  22,              /*!<  22  ADC                                                              */
  CRC_IRQn                      =  23,              /*!<  23  CRC                                                              */
  SRAM_IRQn                     =  24,              /*!<  24  SRAM                                                             */
  CMP_IRQn                      =  25               /*!<  25  CMP                                                              */
} IRQn_Type;


/** @addtogroup Configuration_of_CMSIS
  * @{
  */


/* ================================================================================ */
/* ================      Processor and Core Peripheral Section     ================ */
/* ================================================================================ */

/* ----------------Configuration of the Cortex-M0PLUS Processor and Core Peripherals---------------- */
#define __CM0PLUS_REV                 0x0001        /*!< Cortex-M0PLUS Core Revision                                           */
                                              
#define __NVIC_PRIO_BITS               2            /*!< Number of Bits used for Priority Levels                               */
#define __Vendor_SysTickConfig         0            /*!< Set to 1 if different SysTick Config is used                          */
#define __VTOR_PRESENT                 1            /*!< Set to 1 if CPU supports Vector Table Offset Register                 */
/** @} */ /* End of group Configuration_of_CMSIS */

#include "core_cm0plus.h"                           /*!< Cortex-M0PLUS processor and core peripherals                          */
#include "a31m22x_system.h"                         /*!< A31M22x System                                                        */


/* ================================================================================ */
/* ================       Device Specific Peripheral Section       ================ */
/* ================================================================================ */


/** @addtogroup Device_Peripheral_Registers
  * @{
  */


/* -------------------  Start of section using anonymous unions  ------------------ */
#if defined(__CC_ARM)
  #pragma push
  #pragma anon_unions
#elif defined(__ICCARM__)
  #pragma language=extended
#elif defined(__GNUC__)
  /* anonymous unions are enabled by default */
#elif defined(__TMS470__)
/* anonymous unions are enabled by default */
#elif defined(__TASKING__)
  #pragma warning 586
#else
  #warning Not supported compiler type
#endif



/* ================================================================================ */
/* ================                   CHIPCONFIG                   ================ */
/* ================================================================================ */


/**
  * @brief Chip Configuration (CHIPCONFIG)
  */

typedef struct {                                    /*!< (@ 0x4000F000) CHIPCONFIG Structure                                   */
  __I  uint32_t  VENDORID;                          /*!< (@ 0x4000F000) Vendor ID Register                                     */
  __I  uint32_t  CHIPID;                            /*!< (@ 0x4000F004) Chip ID Register                                       */
  __I  uint32_t  REVNR;                             /*!< (@ 0x4000F008) Revision Number Register                               */
} CHIPCONFIG_Type;


/* ================================================================================ */
/* ================                       SCU                      ================ */
/* ================================================================================ */


/**
  * @brief System Control Unit (SCU)
  */

typedef struct {                                    /*!< (@ 0x40000000) SCU Structure                                          */
  __I  uint32_t  RESERVED;
  __IO uint32_t  SMR;                               /*!< (@ 0x40000004) System Mode Register                                   */
  __IO uint32_t  SRCR;                              /*!< (@ 0x40000008) System Reset Control Register                          */
  __I  uint32_t  RESERVED1;
  __IO uint32_t  WUER;                              /*!< (@ 0x40000010) Wake-up Source Enable Register                         */
  __I  uint32_t  WUSR;                              /*!< (@ 0x40000014) Wake-up Source Status Register                         */
  __IO uint32_t  RSER;                              /*!< (@ 0x40000018) Reset Source Enable Register                           */
  __IO uint32_t  RSSR;                              /*!< (@ 0x4000001C) Reset Source Status Register                           */
  __IO uint32_t  PRER1;                             /*!< (@ 0x40000020) Peripheral Reset Setting Register1                     */
  __IO uint32_t  PRER2;                             /*!< (@ 0x40000024) Peripheral Reset Setting Register2                     */
  __IO uint32_t  PER1;                              /*!< (@ 0x40000028) Peripheral Enable Register1                            */
  __IO uint32_t  PER2;                              /*!< (@ 0x4000002C) Peripheral Enable Register2                            */
  __IO uint32_t  PCER1;                             /*!< (@ 0x40000030) Peripheral Clock Enable Register1                      */
  __IO uint32_t  PCER2;                             /*!< (@ 0x40000034) Peripheral Clock Enable Register2                      */
  __I  uint32_t  RESERVED2[2];
  __IO uint32_t  CSCR;                              /*!< (@ 0x40000040) Clock Source Control Register                          */
  __IO uint32_t  SCCR;                              /*!< (@ 0x40000044) System Clock Control Register                          */
  __IO uint32_t  CMR;                               /*!< (@ 0x40000048) Clock Monitoring Register                              */
  __I  uint32_t  RESERVED3;
  __IO uint32_t  COR;                               /*!< (@ 0x40000050) Clock Output Register                                  */
  __IO uint32_t  NMICR;                             /*!< (@ 0x40000054) NMI Control Register                                   */
  __IO uint32_t  NMISR;                             /*!< (@ 0x40000058) NMI Status Register                                    */
  __I  uint32_t  RESERVED4;
  __IO uint32_t  PLLCON;                            /*!< (@ 0x40000060) PLL Control Register                                   */
  __IO uint32_t  VDCCON;                            /*!< (@ 0x40000064) VDC Control Register                                   */
  __IO uint32_t  LVICR;                             /*!< (@ 0x40000068) Low Voltage Indicator Interrupt Control Register       */
  __IO uint32_t  LVISR;                             /*!< (@ 0x4000006C) Low Voltage Indicator Interrupt Status Register        */
  __IO uint32_t  LVRCR;                             /*!< (@ 0x40000070) Low Voltage Detect Reset Control Register              */
  __I  uint32_t  RESERVED5[3];
  __IO uint32_t  EOSCR;                             /*!< (@ 0x40000080) External Oscillator Control Register                   */
  __I  uint32_t  RESERVED6[3];
  __IO uint32_t  MCCR1;                             /*!< (@ 0x40000090) MISC Clock Control Register1                           */
  __I  uint32_t  RESERVED7;
  __IO uint32_t  MCCR3;                             /*!< (@ 0x40000098) MISC Clock Control Register3                           */
  __IO uint32_t  MCCR4;                             /*!< (@ 0x4000009C) MISC Clock Control Register4                           */
  __IO uint32_t  MCCR5;                             /*!< (@ 0x400000A0) MISC Clock Control Register5                           */
  __IO uint32_t  MCCR6;                             /*!< (@ 0x400000A4) MISC Clock Control Register6                           */
  __IO uint32_t  MCCR7;                             /*!< (@ 0x400000A8) MISC Clock Control Register7                           */
  __I  uint32_t  RESERVED8[17];
  __IO uint32_t  SYSTEN;                            /*!< (@ 0x400000F0) System Access Enable Register                          */
} SCU_Type;


/* ================================================================================ */
/* ================                    PCU [PA]                    ================ */
/* ================================================================================ */


/**
  * @brief General Port A (PCU)
  */

typedef struct {                                    /*!< (@ 0x42000000) PCU Structure                                          */
  __IO uint32_t  MR1;                               /*!< (@ 0x42000000) Port n MUX Control Register 1                          */
  __IO uint32_t  MR2;                               /*!< (@ 0x42000004) Port n MUX Control Register 2                          */
  __IO uint32_t  CR;                                /*!< (@ 0x42000008) Port n Type Control Register                           */
  __IO uint32_t  PRCR;                              /*!< (@ 0x4200000C) Port n Pull-up/Pull-down Selection Register            */
  __IO uint32_t  DER;                               /*!< (@ 0x42000010) Port n Debounce Enable Register                        */
  __IO uint32_t  STR;                               /*!< (@ 0x42000014) Port n Strength Configuraiton Register                 */
  __I  uint32_t  RESERVED[2];
  __IO uint32_t  IER;                               /*!< (@ 0x42000020) Port n Interrupt Enable Register                       */
  __IO uint32_t  ISR;                               /*!< (@ 0x42000024) Port n Interrupt Status Register                       */
  __IO uint32_t  ICR;                               /*!< (@ 0x42000028) Port n Interrupt Control Register                      */
  __I  uint32_t  RESERVED1;
  __IO uint32_t  ODR;                               /*!< (@ 0x42000030) Port n Output Data Register                            */
  __I  uint32_t  IDR;                               /*!< (@ 0x42000034) Port n Input Data Register                             */
  __O  uint32_t  BSR;                               /*!< (@ 0x42000038) Port n Bit Set/Reset Register                          */
  __O  uint32_t  BCR;                               /*!< (@ 0x4200003C) Port n Bit Reset Register                              */
} PCU_Type;


/* ================================================================================ */
/* ================                     PORTEN                     ================ */
/* ================================================================================ */


/**
  * @brief Port Access Enable Register (PORTEN)
  */

typedef struct {                                    /*!< (@ 0x42000FF0) PORTEN Structure                                       */
  __O  uint32_t  EN;                            /*!< (@ 0x42000FF0) Port Access Enable Register                            */
} PORTEN_Type;


/* ================================================================================ */
/* ================                      CFMC                      ================ */
/* ================================================================================ */


/**
  * @brief CODE FLASH MEMORY CONTROLLER (CFMC)
  */

typedef struct {                                    /*!< (@ 0x41000000) CFMC Structure                                         */
  __IO uint32_t  CONF;                              /*!< (@ 0x41000000) Code Flash Control Register                            */
  __O  uint32_t  FLSKEY;                            /*!< (@ 0x41000004) Code Flash Access Key Register                         */
  __O  uint32_t  OTPKEY;                            /*!< (@ 0x41000008) Code Flash OTP Access Key Register                     */
  __IO uint32_t  FLSPROT;                           /*!< (@ 0x4100000C) Code Flash Protection Register                         */
  __IO uint32_t  OTPPROT;                           /*!< (@ 0x41000010) Code Flash OTP Protection Register                     */
  __IO uint32_t  CTRL;                              /*!< (@ 0x41000014) Code Flash Access Control Register                     */
  __IO uint32_t  STAT;                              /*!< (@ 0x41000018) Code Flash Access Status Register                      */
  __IO uint32_t  READPROT;                          /*!< (@ 0x4100001C) Code Flash Read Protection Register                    */
  __O  uint32_t  PWIN;                              /*!< (@ 0x41000020) Code Flash Password Input Register                     */
  __I  uint32_t  RESERVED[3];
  __IO uint32_t  CHKCTRL;                           /*!< (@ 0x41000030) Code Flash CRC Check Control Register                  */
  __IO uint32_t  CHKDOUT;                           /*!< (@ 0x41000034) Code Flash CRC Check Data Output Register              */
  __IO uint32_t  CHKSADDR;                          /*!< (@ 0x41000038) Code Flash CRC Check Start Address Register            */
  __IO uint32_t  CHKEADDR;                          /*!< (@ 0x4100003C) Code Flash CRC Check End Address Register              */
  __IO uint32_t  WTIMEOUT;                          /*!< (@ 0x41000040) Code Flash Write TimeOut Register                      */
  __I  uint32_t  RESERVED1[949];
  __O  uint32_t  PWPRST;                            /*!< (@ 0x41000F18) Code Flash Password Preset Register                    */
} CFMC_Type;


/* ================================================================================ */
/* ================                      SRAM                      ================ */
/* ================================================================================ */


/**
  * @brief SRAM MEMORY CONTROLLER (SRAM)
  */

typedef struct {                                    /*!< (@ 0x41003000) SRAM Structure                                         */
  __IO uint32_t  CONF;                              /*!< (@ 0x41003000) SRAM Memory Configuration Register                     */
  __IO uint32_t  CTRL;                              /*!< (@ 0x41003004) SRAM Memory Control Register                           */
  __IO uint32_t  STAT;                              /*!< (@ 0x41003008) SRAM Memory Status Register                            */
  __I  uint32_t  FTFADDR;                           /*!< (@ 0x4100300C) SRAM FAULT TEST FAIL ADDRESS Register                  */
  __I  uint32_t  FTFBITR;                           /*!< (@ 0x41003010) SRAM FAULT TEST FAIL BIT Register                      */
  __I  uint32_t  FTFPADDR;                          /*!< (@ 0x41003014) SRAM Fault Test Fail PTR Address Register              */
  __IO uint32_t  TESTCTRL;                          /*!< (@ 0x41003018) SRAM TEST Control Register                             */
} SRAM_Type;


/* ================================================================================ */
/* ================                   DMA             		       ================ */
/* ================================================================================ */


/**
  * @brief Direct Memory Access Control  (DMA)
  */

typedef struct {                                    /*!< (@ 0x40000400) DMA Structure                                          */
  __IO uint32_t  CR;                                /*!< (@ 0x40000400) DMA Control Register                                   */
  __IO uint32_t  SR;                                /*!< (@ 0x40000404) DMA Status Register                                    */
  __IO uint32_t  PAR;                               /*!< (@ 0x40000408) DMA Peripheral address register                        */
  __IO uint32_t  MAR;                               /*!< (@ 0x4000040C) DMA Memory address register                            */
} DMA_Type;


/* ================================================================================ */
/* ================                       WDT                      ================ */
/* ================================================================================ */


/**
  * @brief WATCH-DOG TIMER (WDT)
  */

typedef struct {                                    /*!< (@ 0x40000200) WDT Structure                                          */
  __IO uint32_t  LR;                                /*!< (@ 0x40000200) WDT Load Register                                      */
  __I  uint32_t  CNT;                               /*!< (@ 0x40000204) WDT Current Count Register                             */
  __IO uint32_t  CON;                               /*!< (@ 0x40000208) WDT Control Register                                   */
  __I  uint32_t  RESERVED[57];
  __IO uint32_t  AEN;                               /*!< (@ 0x400002F0) WDT Access Enable Register                             */
} WDT_Type;


/* ================================================================================ */
/* ================                 TIMER		                   ================ */
/* ================================================================================ */


/**
  * @brief TIMER COUNTER (TIMER)
  */

typedef struct {                                    /*!< (@ 0x40003000) TIMER Structure                                        */
  __IO uint32_t  CR1;                               /*!< (@ 0x40003000) Timer Control Register1                                */
  __IO uint32_t  CR2;                               /*!< (@ 0x40003004) Timer Control Register2                                */
  __IO uint32_t  PRS;                               /*!< (@ 0x40003008) Timer Prescaler Register                               */
  __IO uint32_t  GRA;                               /*!< (@ 0x4000300C) Timer General A Data Register                          */
  __IO uint32_t  GRB;                               /*!< (@ 0x40003010) Timer General B Data Register                          */
  __IO uint32_t  CNT;                               /*!< (@ 0x40003014) Timer Counter Register                                 */
  __IO uint32_t  SR;                                /*!< (@ 0x40003018) Timer Status Register                                  */
  __IO uint32_t  IER;                               /*!< (@ 0x4000301C) Timer Interrupt Enable Register                        */
  __IO uint32_t  TRGPNT;                            /*!< (@ 0x40003020) Timer Trigger Point Register                           */
  __IO uint32_t  SYNC;                              /*!< (@ 0x40003024) Timer Sync Setting Register                            */
} TIMER_Type;


/* ================================================================================ */
/* ================                       FRT                      ================ */
/* ================================================================================ */


/**
  * @brief Free Run Timer (FRT)
  */

typedef struct {                                    /*!< (@ 0x40000600) FRT Structure                                          */
  __IO uint32_t  CTRL;                              /*!< (@ 0x40000600) FRT Control Register                                   */
  __IO uint32_t  MCNT;                              /*!< (@ 0x40000604) FRT Match Counter Register                             */
  __IO uint32_t  CNT;                               /*!< (@ 0x40000608) FRT Counter Register                                   */
  __IO uint32_t  STAT;                              /*!< (@ 0x4000060C) FRT Status Register                                    */
} FRT_Type;


/* ================================================================================ */
/* ================                  UART                 		   ================ */
/* ================================================================================ */


/**
  * @brief Universal Asynchronous Receiver/Transmitter (UART)
  */

typedef struct {                                    /*!< (@ 0x40008000) UART Structure                                         */
  
  union {
    __O  uint32_t  THR;                             /*!< (@ 0x40008000) UARTn Transmit Data Hold Register                      */
    __I  uint32_t  RBR;                             /*!< (@ 0x40008000) UARTn Receive Data Buffer Register                     */
  };
  __IO uint32_t  IER;                               /*!< (@ 0x40008004) UARTn Interrupt Enable Register                        */
  __I  uint32_t  IIR;                               /*!< (@ 0x40008008) UARTn Interrupt ID Register                            */
  __IO uint32_t  LCR;                               /*!< (@ 0x4000800C) UARTn Line Control Register                            */
  __IO uint32_t  DCR;                               /*!< (@ 0x40008010) UARTn Data Control Register                            */
  __I  uint32_t  LSR;                               /*!< (@ 0x40008014) UARTn Line Status Register                             */
  __I  uint32_t  RESERVED[2];
  __IO uint32_t  BDR;                               /*!< (@ 0x40008020) UARTn Baud Rate Register                               */
  __IO uint32_t  BFR;                               /*!< (@ 0x40008024) UARTn Baud Rate Fractional Register                    */
  __I  uint32_t  RESERVED1[2];
  __IO uint32_t  IDTR;                              /*!< (@ 0x40008030) UARTn Inter-frame Delay Time Register                  */
} UART_Type;


/* ================================================================================ */
/* ================                       SPI                      ================ */
/* ================================================================================ */


/**
  * @brief Serial Peripheral Interface Bus (SPI)
  */

typedef struct {                                    /*!< (@ 0x40009000) SPI Structure                                          */
  
  union {
    __I  uint32_t  RDR;                             /*!< (@ 0x40009000) SPI Received Data Register                             */
    __O  uint32_t  TDR;                             /*!< (@ 0x40009000) SPI Transmit Data Register                             */
  };
  __IO uint32_t  CR;                                /*!< (@ 0x40009004) SPI Control Register                                   */
  __IO uint32_t  SR;                                /*!< (@ 0x40009008) SPI Status Register                                    */
  __IO uint32_t  BR;                                /*!< (@ 0x4000900C) SPI Baud Rate Register                                 */
  __IO uint32_t  EN;                                /*!< (@ 0x40009010) SPI Enable Register                                    */
  __IO uint32_t  LR;                                /*!< (@ 0x40009014) SPI Delay Length Register                              */
} SPI_Type;


/* ================================================================================ */
/* ================                       I2C                      ================ */
/* ================================================================================ */


/**
  * @brief Inter-Integrated Circuit (I2C)
  */

typedef struct {                                    /*!< (@ 0x4000A000) I2C Structure                                          */
  __IO uint32_t  DR;                                /*!< (@ 0x4000A000) I2C Data Register                                      */
  __I  uint32_t  RESERVED;
  __IO uint32_t  SR;                                /*!< (@ 0x4000A008) I2C Status Register                                    */
  __IO uint32_t  SAR;                               /*!< (@ 0x4000A00C) I2C Slave Address Register                             */
  __I  uint32_t  RESERVED1;
  __IO uint32_t  CR;                                /*!< (@ 0x4000A014) I2C Control Register                                   */
  __IO uint32_t  SCLL;                              /*!< (@ 0x4000A018) I2C SCL Low Duration Register                          */
  __IO uint32_t  SCLH;                              /*!< (@ 0x4000A01C) I2C SCL High Duration Register                         */
  __IO uint32_t  SDH;                               /*!< (@ 0x4000A020) I2C SDA Hold Register                                  */
} I2C_Type;


/* ================================================================================ */
/* ================                      MPWM                      ================ */
/* ================================================================================ */


/**
  * @brief Motor Pulse Width Modulation (MPWM)
  */

typedef struct {                                    /*!< (@ 0x42001000) MPWM Structure                                         */
  __IO uint32_t  MR;                                /*!< (@ 0x42001000) MPWM Mode Register                                     */
  __IO uint32_t  OLR;                               /*!< (@ 0x42001004) MPWM Output Level Register                             */
  __IO uint32_t  FOLR;                              /*!< (@ 0x42001008) MPWM Forced Output Register                            */
  __IO uint32_t  PRD;                               /*!< (@ 0x4200100C) MPWM Period Register                                   */
  __IO uint32_t  DUH;                               /*!< (@ 0x42001010) MPWM DUTY UH Register                                  */
  __IO uint32_t  DVH;                               /*!< (@ 0x42001014) MPWM DUTY VH Register                                  */
  __IO uint32_t  DWH;                               /*!< (@ 0x42001018) MPWM DUTY WH Register                                  */
  __IO uint32_t  DUL;                               /*!< (@ 0x4200101C) MPWM DUTY UL Register                                  */
  __IO uint32_t  DVL;                               /*!< (@ 0x42001020) MPWM DUTY VL Register                                  */
  __IO uint32_t  DWL;                               /*!< (@ 0x42001024) MPWM DUTY WL Register                                  */
  __IO uint32_t  CR1;                               /*!< (@ 0x42001028) MPWM Control Register 1                                */
  __IO uint32_t  CR2;                               /*!< (@ 0x4200102C) MPWM Control Register 2                                */
  __IO uint32_t  SR;                                /*!< (@ 0x42001030) MPWM Status Register                                   */
  __IO uint32_t  IER;                               /*!< (@ 0x42001034) MPWM Interrupt Enable Register                         */
  __IO uint32_t  CNT;                               /*!< (@ 0x42001038) MPWM Counter Register                                  */
  __IO uint32_t  DTR;                               /*!< (@ 0x4200103C) MPWM Dead-Time Register                                */
  __IO uint32_t  PCR;                               /*!< (@ 0x42001040) MPWM Protection Control Register                       */
  __IO uint32_t  PSR;                               /*!< (@ 0x42001044) MPWM Protection Status Register                        */
  __IO uint32_t  OCR;                               /*!< (@ 0x42001048) MPWM Over Voltage Detection Register                   */
  __IO uint32_t  OSR;                               /*!< (@ 0x4200104C) MPWM Over Voltage Detection Status Register            */
  __I  uint32_t  RESERVED[2];
  __IO uint32_t  ATR1;                              /*!< (@ 0x42001058) MPWM ADC Trigger Counter Register                      */
  __IO uint32_t  ATR2;                              /*!< (@ 0x4200105C) MPWM ADC Trigger Counter Register                      */
  __IO uint32_t  ATR3;                              /*!< (@ 0x42001060) MPWM ADC Trigger Counter Register                      */
  __IO uint32_t  ATR4;                              /*!< (@ 0x42001064) MPWM ADC Trigger Counter Register                      */
  __IO uint32_t  ATR5;                              /*!< (@ 0x42001068) MPWM ADC Trigger Counter Register                      */
  __IO uint32_t  ATR6;                              /*!< (@ 0x4200106C) MPWM ADC Trigger Counter Register                      */
} MPWM_Type;


/* ================================================================================ */
/* ================                       ADC                      ================ */
/* ================================================================================ */


/**
  * @brief 12-BIT A/D CONVERTER (ADC)
  */

typedef struct {                                    /*!< (@ 0x42002000) ADC Structure                                          */
  __IO uint32_t  MR;                                /*!< (@ 0x42002000) ADC Mode Register                                      */
  __IO uint32_t  CSCR;                              /*!< (@ 0x42002004) ADC Current Sequence_Channel Register                  */
  __IO uint32_t  CCR;                               /*!< (@ 0x42002008) ADC Clock Control Register                             */
  __IO uint32_t  TRG;                               /*!< (@ 0x4200200C) ADC Trigger Selection Register                         */
  __IO uint32_t  CSTR1;                             /*!< (@ 0x42002010) ADC channel sampling time register 1                   */
  __IO uint32_t  CSTR2;                             /*!< (@ 0x42002014) ADC channel sampling time register 2                   */
  __IO uint32_t  SCSR1;                             /*!< (@ 0x42002018) ADC Channel selection Register 1                       */
  __IO uint32_t  SCSR2;                             /*!< (@ 0x4200201C) ADC Channel selection Register 2                       */
  __IO uint32_t  CR;                                /*!< (@ 0x42002020) ADC Control Register                                   */
  __IO uint32_t  SR;                                /*!< (@ 0x42002024) ADC Status Register                                    */
  __IO uint32_t  IER;                               /*!< (@ 0x42002028) ADC Interrupt Enable Register                          */
  __I  uint32_t  DDR;                               /*!< (@ 0x4200202C) ADC DMA Data Register                                  */
  __IO uint32_t  DR0;                               /*!< (@ 0x42002030) ADC Data Register0                                     */
  __IO uint32_t  DR1;                               /*!< (@ 0x42002034) ADC Sequence Data Register1                            */
  __IO uint32_t  DR2;                               /*!< (@ 0x42002038) ADC Sequence Data Register2                            */
  __IO uint32_t  DR3;                               /*!< (@ 0x4200203C) ADC Sequence Data Register3                            */
  __IO uint32_t  DR4;                               /*!< (@ 0x42002040) ADC Sequence Data Register4                            */
  __IO uint32_t  DR5;                               /*!< (@ 0x42002044) ADC Sequence Data Register5                            */
  __IO uint32_t  DR6;                               /*!< (@ 0x42002048) ADC Sequence Data Register6                            */
  __IO uint32_t  DR7;                               /*!< (@ 0x4200204C) ADC Sequence Data Register7                            */
  __IO uint32_t  IMR;                               /*!< (@ 0x42002050) ADC Inject mode Register                               */
  __IO uint32_t  ICR;                               /*!< (@ 0x42002054) ADC Inject control Register                            */
  __I  uint32_t  IDR;                               /*!< (@ 0x42002058) ADC Inject Data Register                               */
  __I  uint32_t  RESERVED;
  __IO uint32_t  CMP0R;                             /*!< (@ 0x42002060) ADC Channel Comparison 0 Register                      */
  __IO uint32_t  CMP1R;                             /*!< (@ 0x42002064) ADC Channel Comparison 1 Register                      */
} ADC_Type;


/* ================================================================================ */
/* ================                      OPAMP                     ================ */
/* ================================================================================ */


/**
  * @brief Opamp (OPAMP)
  */

typedef struct {                                    /*!< (@ 0x4000B300) OPAMP Structure                                        */
  __IO uint32_t  CR;                         /*!< (@ 0x4000B300) OPAMP Control Register                               */
} OPAMP_Type;


/* ================================================================================ */
/* ================                       CMP                      ================ */
/* ================================================================================ */


/**
  * @brief Comparator (CMP)
  */

typedef struct {                                    /*!< (@ 0x4000B380) CMP Structure                                          */
  __IO uint32_t  CONF;                              /*!< (@ 0x4000B380) Comparator Configure Register                          */
  __IO uint32_t  CTRL;                              /*!< (@ 0x4000B384) Comparator Control Register                            */
  __IO uint32_t  STAT;                              /*!< (@ 0x4000B388) Comparator Status Register                             */
  __I  uint32_t  RESERVED[9];
  __IO uint32_t  DBCR;                              /*!< (@ 0x4000B3B0) Comparator Debounce Control Register                   */
} CMP_Type;


/* ================================================================================ */
/* ================                       CRC                      ================ */
/* ================================================================================ */


/**
  * @brief CYCLIC REDUNDANCY CHECK AND CHECKSUM (CRC)
  */

typedef struct {                                    /*!< (@ 0x41002000) CRC Structure                                          */
  __IO uint32_t  CTRL;                              /*!< (@ 0x41002000) CRC Control Register                                   */
  __IO uint32_t  INIT;                              /*!< (@ 0x41002004) CRC Initial Data Register                              */
  
  union {
    __I  uint32_t  ODR;                             /*!< (@ 0x41002008) CRC Output Data Register                               */
    __O  uint32_t  IDR;                             /*!< (@ 0x41002008) CRC Input Data Register                                */
  };
  __IO uint32_t  STAT;                              /*!< (@ 0x4100200C) CRC Status Register                                    */
} CRC_Type;


/* --------------------  End of section using anonymous unions  ------------------- */
#if defined(__CC_ARM)
  #pragma pop
#elif defined(__ICCARM__)
  /* leave anonymous unions enabled */
#elif defined(__GNUC__)
  /* anonymous unions are enabled by default */
#elif defined(__TMS470__)
  /* anonymous unions are enabled by default */
#elif defined(__TASKING__)
  #pragma warning restore
#else
  #warning Not supported compiler type
#endif



/* ================================================================================ */
/* ================          struct 'SCU' Position & Mask          ================ */
/* ================================================================================ */


/* -----------------------------------  SCU_SMR  ---------------------------------- */
#define SCU_SMR_PREVMODE_Pos                  4                                                       /*!< SCU SMR: PREVMODE Position              */
#define SCU_SMR_PREVMODE_Msk                  (0x03UL << SCU_SMR_PREVMODE_Pos)                        /*!< SCU SMR: PREVMODE Mask                  */
#define SCU_SMR_VDCAON_Pos                    8                                                       /*!< SCU SMR: VDCAON Position                */
#define SCU_SMR_VDCAON_Msk                    (0x01UL << SCU_SMR_VDCAON_Pos)                          /*!< SCU SMR: VDCAON Mask                    */
#define SCU_SMR_LSIAON_Pos                    9                                                       /*!< SCU SMR: LSIAON Position                */
#define SCU_SMR_LSIAON_Msk                    (0x01UL << SCU_SMR_LSIAON_Pos)                          /*!< SCU SMR: LSIAON Mask                    */
#define SCU_SMR_HSIAON_Pos                    10                                                      /*!< SCU SMR: HSIAON Position                */
#define SCU_SMR_HSIAON_Msk                    (0x01UL << SCU_SMR_HSIAON_Pos)                          /*!< SCU SMR: HSIAON Mask                    */
#define SCU_SMR_PLLAON_Pos                    11                                                      /*!< SCU SMR: PLLAON Position                */
#define SCU_SMR_PLLAON_Msk                    (0x01UL << SCU_SMR_PLLAON_Pos)                          /*!< SCU SMR: PLLAON Mask                    */
#define SCU_SMR_HSEAON_Pos                    12                                                      /*!< SCU SMR: HSEAON Position                */
#define SCU_SMR_HSEAON_Msk                    (0x01UL << SCU_SMR_HSEAON_Pos)                          /*!< SCU SMR: HSEAON Mask                    */
#define SCU_SMR_LSEAON_Pos                    13                                                      /*!< SCU SMR: LSEAON Position                */
#define SCU_SMR_LSEAON_Msk                    (0x01UL << SCU_SMR_LSEAON_Pos)                          /*!< SCU SMR: LSEAON Mask                    */

/* ----------------------------------  SCU_SRCR  ---------------------------------- */
#define SCU_SRCR_SWRST_Pos                    0                                                       /*!< SCU SRCR: SWRST Position                */
#define SCU_SRCR_SWRST_Msk                    (0x01UL << SCU_SRCR_SWRST_Pos)                          /*!< SCU SRCR: SWRST Mask                    */
#define SCU_SRCR_STBYO_Pos                    4                                                       /*!< SCU SRCR: STBYO Position                */
#define SCU_SRCR_STBYO_Msk                    (0x01UL << SCU_SRCR_STBYO_Pos)                          /*!< SCU SRCR: STBYO Mask                    */

/* ----------------------------------  SCU_WUER  ---------------------------------- */
#define SCU_WUER_LVIWUE_Pos                   0                                                       /*!< SCU WUER: LVIWUE Position               */
#define SCU_WUER_LVIWUE_Msk                   (0x01UL << SCU_WUER_LVIWUE_Pos)                         /*!< SCU WUER: LVIWUE Mask                   */
#define SCU_WUER_WDTWUE_Pos                   1                                                       /*!< SCU WUER: WDTWUE Position               */
#define SCU_WUER_WDTWUE_Msk                   (0x01UL << SCU_WUER_WDTWUE_Pos)                         /*!< SCU WUER: WDTWUE Mask                   */
#define SCU_WUER_FRTWUE_Pos                   2                                                       /*!< SCU WUER: FRTWUE Position               */
#define SCU_WUER_FRTWUE_Msk                   (0x01UL << SCU_WUER_FRTWUE_Pos)                         /*!< SCU WUER: FRTWUE Mask                   */
#define SCU_WUER_GPIOAWUE_Pos                 8                                                       /*!< SCU WUER: GPIOAWUE Position             */
#define SCU_WUER_GPIOAWUE_Msk                 (0x01UL << SCU_WUER_GPIOAWUE_Pos)                       /*!< SCU WUER: GPIOAWUE Mask                 */
#define SCU_WUER_GPIOBWUE_Pos                 9                                                       /*!< SCU WUER: GPIOBWUE Position             */
#define SCU_WUER_GPIOBWUE_Msk                 (0x01UL << SCU_WUER_GPIOBWUE_Pos)                       /*!< SCU WUER: GPIOBWUE Mask                 */
#define SCU_WUER_GPIOCWUE_Pos                 10                                                      /*!< SCU WUER: GPIOCWUE Position             */
#define SCU_WUER_GPIOCWUE_Msk                 (0x01UL << SCU_WUER_GPIOCWUE_Pos)                       /*!< SCU WUER: GPIOCWUE Mask                 */
#define SCU_WUER_GPIODWUE_Pos                 11                                                      /*!< SCU WUER: GPIODWUE Position             */
#define SCU_WUER_GPIODWUE_Msk                 (0x01UL << SCU_WUER_GPIODWUE_Pos)                       /*!< SCU WUER: GPIODWUE Mask                 */

/* ----------------------------------  SCU_WUSR  ---------------------------------- */
#define SCU_WUSR_LVIWU_Pos                    0                                                       /*!< SCU WUSR: LVIWU Position                */
#define SCU_WUSR_LVIWU_Msk                    (0x01UL << SCU_WUSR_LVIWU_Pos)                          /*!< SCU WUSR: LVIWU Mask                    */
#define SCU_WUSR_WDTWU_Pos                    1                                                       /*!< SCU WUSR: WDTWU Position                */
#define SCU_WUSR_WDTWU_Msk                    (0x01UL << SCU_WUSR_WDTWU_Pos)                          /*!< SCU WUSR: WDTWU Mask                    */
#define SCU_WUSR_FRTWU_Pos                    2                                                       /*!< SCU WUSR: FRTWU Position                */
#define SCU_WUSR_FRTWU_Msk                    (0x01UL << SCU_WUSR_FRTWU_Pos)                          /*!< SCU WUSR: FRTWU Mask                    */
#define SCU_WUSR_GPIOAWU_Pos                  8                                                       /*!< SCU WUSR: GPIOAWU Position              */
#define SCU_WUSR_GPIOAWU_Msk                  (0x01UL << SCU_WUSR_GPIOAWU_Pos)                        /*!< SCU WUSR: GPIOAWU Mask                  */
#define SCU_WUSR_GPIOBWU_Pos                  9                                                       /*!< SCU WUSR: GPIOBWU Position              */
#define SCU_WUSR_GPIOBWU_Msk                  (0x01UL << SCU_WUSR_GPIOBWU_Pos)                        /*!< SCU WUSR: GPIOBWU Mask                  */
#define SCU_WUSR_GPIOCWU_Pos                  10                                                      /*!< SCU WUSR: GPIOCWU Position              */
#define SCU_WUSR_GPIOCWU_Msk                  (0x01UL << SCU_WUSR_GPIOCWU_Pos)                        /*!< SCU WUSR: GPIOCWU Mask                  */
#define SCU_WUSR_GPIODWU_Pos                  11                                                      /*!< SCU WUSR: GPIODWU Position              */
#define SCU_WUSR_GPIODWU_Msk                  (0x01UL << SCU_WUSR_GPIODWU_Pos)                        /*!< SCU WUSR: GPIODWU Mask                  */

/* ----------------------------------  SCU_RSER  ---------------------------------- */
#define SCU_RSER_LVDRST_Pos                   0                                                       /*!< SCU RSER: LVDRST Position               */
#define SCU_RSER_LVDRST_Msk                   (0x01UL << SCU_RSER_LVDRST_Pos)                         /*!< SCU RSER: LVDRST Mask                   */
#define SCU_RSER_HSEFRST_Pos                  1                                                       /*!< SCU RSER: HSEFRST Position              */
#define SCU_RSER_HSEFRST_Msk                  (0x01UL << SCU_RSER_HSEFRST_Pos)                        /*!< SCU RSER: HSEFRST Mask                  */
#define SCU_RSER_LSEFRST_Pos                  2                                                       /*!< SCU RSER: LSEFRST Position              */
#define SCU_RSER_LSEFRST_Msk                  (0x01UL << SCU_RSER_LSEFRST_Pos)                        /*!< SCU RSER: LSEFRST Mask                  */
#define SCU_RSER_MCKFRST_Pos                  3                                                       /*!< SCU RSER: MCKFRST Position              */
#define SCU_RSER_MCKFRST_Msk                  (0x01UL << SCU_RSER_MCKFRST_Pos)                        /*!< SCU RSER: MCKFRST Mask                  */
#define SCU_RSER_WDTRST_Pos                   4                                                       /*!< SCU RSER: WDTRST Position               */
#define SCU_RSER_WDTRST_Msk                   (0x01UL << SCU_RSER_WDTRST_Pos)                         /*!< SCU RSER: WDTRST Mask                   */
#define SCU_RSER_SWRST_Pos                    5                                                       /*!< SCU RSER: SWRST Position                */
#define SCU_RSER_SWRST_Msk                    (0x01UL << SCU_RSER_SWRST_Pos)                          /*!< SCU RSER: SWRST Mask                    */
#define SCU_RSER_CPURST_Pos                   6                                                       /*!< SCU RSER: CPURST Position               */
#define SCU_RSER_CPURST_Msk                   (0x01UL << SCU_RSER_CPURST_Pos)                         /*!< SCU RSER: CPURST Mask                   */
#define SCU_RSER_PINRST_Pos                   7                                                       /*!< SCU RSER: PINRST Position               */
#define SCU_RSER_PINRST_Msk                   (0x01UL << SCU_RSER_PINRST_Pos)                         /*!< SCU RSER: PINRST Mask                   */
#define SCU_RSER_LOCKUPRST_Pos                9                                                       /*!< SCU RSER: LOCKUPRST Position            */
#define SCU_RSER_LOCKUPRST_Msk                (0x01UL << SCU_RSER_LOCKUPRST_Pos)                      /*!< SCU RSER: LOCKUPRST Mask                */

/* ----------------------------------  SCU_RSSR  ---------------------------------- */
#define SCU_RSSR_LVDRST_Pos                   0                                                       /*!< SCU RSSR: LVDRST Position               */
#define SCU_RSSR_LVDRST_Msk                   (0x01UL << SCU_RSSR_LVDRST_Pos)                         /*!< SCU RSSR: LVDRST Mask                   */
#define SCU_RSSR_HSEFRST_Pos                  1                                                       /*!< SCU RSSR: HSEFRST Position              */
#define SCU_RSSR_HSEFRST_Msk                  (0x01UL << SCU_RSSR_HSEFRST_Pos)                        /*!< SCU RSSR: HSEFRST Mask                  */
#define SCU_RSSR_LSEFRST_Pos                  2                                                       /*!< SCU RSSR: LSEFRST Position              */
#define SCU_RSSR_LSEFRST_Msk                  (0x01UL << SCU_RSSR_LSEFRST_Pos)                        /*!< SCU RSSR: LSEFRST Mask                  */
#define SCU_RSSR_MCLKFRST_Pos                 3                                                       /*!< SCU RSSR: MCLKFRST Position             */
#define SCU_RSSR_MCLKFRST_Msk                 (0x01UL << SCU_RSSR_MCLKFRST_Pos)                       /*!< SCU RSSR: MCLKFRST Mask                 */
#define SCU_RSSR_WDTRST_Pos                   4                                                       /*!< SCU RSSR: WDTRST Position               */
#define SCU_RSSR_WDTRST_Msk                   (0x01UL << SCU_RSSR_WDTRST_Pos)                         /*!< SCU RSSR: WDTRST Mask                   */
#define SCU_RSSR_SWRST_Pos                    5                                                       /*!< SCU RSSR: SWRST Position                */
#define SCU_RSSR_SWRST_Msk                    (0x01UL << SCU_RSSR_SWRST_Pos)                          /*!< SCU RSSR: SWRST Mask                    */
#define SCU_RSSR_CPURST_Pos                   6                                                       /*!< SCU RSSR: CPURST Position               */
#define SCU_RSSR_CPURST_Msk                   (0x01UL << SCU_RSSR_CPURST_Pos)                         /*!< SCU RSSR: CPURST Mask                   */
#define SCU_RSSR_PINRST_Pos                   7                                                       /*!< SCU RSSR: PINRST Position               */
#define SCU_RSSR_PINRST_Msk                   (0x01UL << SCU_RSSR_PINRST_Pos)                         /*!< SCU RSSR: PINRST Mask                   */
#define SCU_RSSR_PORST_Pos                    8                                                       /*!< SCU RSSR: PORST Position                */
#define SCU_RSSR_PORST_Msk                    (0x01UL << SCU_RSSR_PORST_Pos)                          /*!< SCU RSSR: PORST Mask                    */
#define SCU_RSSR_LOCKUPRST_Pos                9                                                       /*!< SCU RSSR: LOCKUPRST Position            */
#define SCU_RSSR_LOCKUPRST_Msk                (0x01UL << SCU_RSSR_LOCKUPRST_Pos)                      /*!< SCU RSSR: LOCKUPRST Mask                */

/* ----------------------------------  SCU_PRER1  --------------------------------- */
#define SCU_PRER1_SCU_Pos                     0                                                       /*!< SCU PRER1: SCU Position                 */
#define SCU_PRER1_SCU_Msk                     (0x01UL << SCU_PRER1_SCU_Pos)                           /*!< SCU PRER1: SCU Mask                     */
#define SCU_PRER1_CFMC_Pos                    1                                                       /*!< SCU PRER1: CFMC Position                */
#define SCU_PRER1_CFMC_Msk                    (0x01UL << SCU_PRER1_CFMC_Pos)                          /*!< SCU PRER1: CFMC Mask                    */
#define SCU_PRER1_WDT_Pos                     2                                                       /*!< SCU PRER1: WDT Position                 */
#define SCU_PRER1_WDT_Msk                     (0x01UL << SCU_PRER1_WDT_Pos)                           /*!< SCU PRER1: WDT Mask                     */
#define SCU_PRER1_DMA_Pos                     4                                                       /*!< SCU PRER1: DMA Position                 */
#define SCU_PRER1_DMA_Msk                     (0x01UL << SCU_PRER1_DMA_Pos)                           /*!< SCU PRER1: DMA Mask                     */
#define SCU_PRER1_FRT_Pos                     6                                                       /*!< SCU PRER1: FRT Position                 */
#define SCU_PRER1_FRT_Msk                     (0x01UL << SCU_PRER1_FRT_Pos)                           /*!< SCU PRER1: FRT Mask                     */
#define SCU_PRER1_GPIOA_Pos                   8                                                       /*!< SCU PRER1: GPIOA Position               */
#define SCU_PRER1_GPIOA_Msk                   (0x01UL << SCU_PRER1_GPIOA_Pos)                         /*!< SCU PRER1: GPIOA Mask                   */
#define SCU_PRER1_GPIOB_Pos                   9                                                       /*!< SCU PRER1: GPIOB Position               */
#define SCU_PRER1_GPIOB_Msk                   (0x01UL << SCU_PRER1_GPIOB_Pos)                         /*!< SCU PRER1: GPIOB Mask                   */
#define SCU_PRER1_GPIOC_Pos                   10                                                      /*!< SCU PRER1: GPIOC Position               */
#define SCU_PRER1_GPIOC_Msk                   (0x01UL << SCU_PRER1_GPIOC_Pos)                         /*!< SCU PRER1: GPIOC Mask                   */
#define SCU_PRER1_GPIOD_Pos                   11                                                      /*!< SCU PRER1: GPIOD Position               */
#define SCU_PRER1_GPIOD_Msk                   (0x01UL << SCU_PRER1_GPIOD_Pos)                         /*!< SCU PRER1: GPIOD Mask                   */
#define SCU_PRER1_TIMER0_Pos                  16                                                      /*!< SCU PRER1: TIMER0 Position              */
#define SCU_PRER1_TIMER0_Msk                  (0x01UL << SCU_PRER1_TIMER0_Pos)                        /*!< SCU PRER1: TIMER0 Mask                  */
#define SCU_PRER1_TIMER1_Pos                  17                                                      /*!< SCU PRER1: TIMER1 Position              */
#define SCU_PRER1_TIMER1_Msk                  (0x01UL << SCU_PRER1_TIMER1_Pos)                        /*!< SCU PRER1: TIMER1 Mask                  */
#define SCU_PRER1_TIMER2_Pos                  18                                                      /*!< SCU PRER1: TIMER2 Position              */
#define SCU_PRER1_TIMER2_Msk                  (0x01UL << SCU_PRER1_TIMER2_Pos)                        /*!< SCU PRER1: TIMER2 Mask                  */
#define SCU_PRER1_TIMER3_Pos                  19                                                      /*!< SCU PRER1: TIMER3 Position              */
#define SCU_PRER1_TIMER3_Msk                  (0x01UL << SCU_PRER1_TIMER3_Pos)                        /*!< SCU PRER1: TIMER3 Mask                  */

/* ----------------------------------  SCU_PRER2  --------------------------------- */
#define SCU_PRER2_SPI_Pos                     0                                                       /*!< SCU PRER2: SPI Position                 */
#define SCU_PRER2_SPI_Msk                     (0x01UL << SCU_PRER2_SPI_Pos)                           /*!< SCU PRER2: SPI Mask                     */
#define SCU_PRER2_I2C_Pos                     4                                                       /*!< SCU PRER2: I2C Position                 */
#define SCU_PRER2_I2C_Msk                     (0x01UL << SCU_PRER2_I2C_Pos)                           /*!< SCU PRER2: I2C Mask                     */
#define SCU_PRER2_UART0_Pos                   8                                                       /*!< SCU PRER2: UART0 Position               */
#define SCU_PRER2_UART0_Msk                   (0x01UL << SCU_PRER2_UART0_Pos)                         /*!< SCU PRER2: UART0 Mask                   */
#define SCU_PRER2_UART1_Pos                   9                                                       /*!< SCU PRER2: UART1 Position               */
#define SCU_PRER2_UART1_Msk                   (0x01UL << SCU_PRER2_UART1_Pos)                         /*!< SCU PRER2: UART1 Mask                   */
#define SCU_PRER2_MPWM_Pos                    16                                                      /*!< SCU PRER2: MPWM Position                */
#define SCU_PRER2_MPWM_Msk                    (0x01UL << SCU_PRER2_MPWM_Pos)                          /*!< SCU PRER2: MPWM Mask                    */
#define SCU_PRER2_ADC_Pos                     20                                                      /*!< SCU PRER2: ADC Position                 */
#define SCU_PRER2_ADC_Msk                     (0x01UL << SCU_PRER2_ADC_Pos)                           /*!< SCU PRER2: ADC Mask                     */
#define SCU_PRER2_OPAMP_Pos                   24                                                      /*!< SCU PRER2: OPAMP Position               */
#define SCU_PRER2_OPAMP_Msk                   (0x01UL << SCU_PRER2_OPAMP_Pos)                         /*!< SCU PRER2: OPAMP Mask                   */
#define SCU_PRER2_CMP_Pos                     28                                                      /*!< SCU PRER2: CMP Position                 */
#define SCU_PRER2_CMP_Msk                     (0x01UL << SCU_PRER2_CMP_Pos)                           /*!< SCU PRER2: CMP Mask                     */
#define SCU_PRER2_CRC_Pos                     29                                                      /*!< SCU PRER2: CRC Position                 */
#define SCU_PRER2_CRC_Msk                     (0x01UL << SCU_PRER2_CRC_Pos)                           /*!< SCU PRER2: CRC Mask                     */

/* ----------------------------------  SCU_PER1  ---------------------------------- */
#define SCU_PER1_DMA_Pos                      4                                                       /*!< SCU PER1: DMA Position                  */
#define SCU_PER1_DMA_Msk                      (0x01UL << SCU_PER1_DMA_Pos)                            /*!< SCU PER1: DMA Mask                      */
#define SCU_PER1_FRT_Pos                      6                                                       /*!< SCU PER1: FRT Position                  */
#define SCU_PER1_FRT_Msk                      (0x01UL << SCU_PER1_FRT_Pos)                            /*!< SCU PER1: FRT Mask                      */
#define SCU_PER1_GPIOA_Pos                    8                                                       /*!< SCU PER1: GPIOA Position                */
#define SCU_PER1_GPIOA_Msk                    (0x01UL << SCU_PER1_GPIOA_Pos)                          /*!< SCU PER1: GPIOA Mask                    */
#define SCU_PER1_GPIOB_Pos                    9                                                       /*!< SCU PER1: GPIOB Position                */
#define SCU_PER1_GPIOB_Msk                    (0x01UL << SCU_PER1_GPIOB_Pos)                          /*!< SCU PER1: GPIOB Mask                    */
#define SCU_PER1_GPIOC_Pos                    10                                                      /*!< SCU PER1: GPIOC Position                */
#define SCU_PER1_GPIOC_Msk                    (0x01UL << SCU_PER1_GPIOC_Pos)                          /*!< SCU PER1: GPIOC Mask                    */
#define SCU_PER1_GPIOD_Pos                    11                                                      /*!< SCU PER1: GPIOD Position                */
#define SCU_PER1_GPIOD_Msk                    (0x01UL << SCU_PER1_GPIOD_Pos)                          /*!< SCU PER1: GPIOD Mask                    */
#define SCU_PER1_TIMER0_Pos                   16                                                      /*!< SCU PER1: TIMER0 Position               */
#define SCU_PER1_TIMER0_Msk                   (0x01UL << SCU_PER1_TIMER0_Pos)                         /*!< SCU PER1: TIMER0 Mask                   */
#define SCU_PER1_TIMER1_Pos                   17                                                      /*!< SCU PER1: TIMER1 Position               */
#define SCU_PER1_TIMER1_Msk                   (0x01UL << SCU_PER1_TIMER1_Pos)                         /*!< SCU PER1: TIMER1 Mask                   */
#define SCU_PER1_TIMER2_Pos                   18                                                      /*!< SCU PER1: TIMER2 Position               */
#define SCU_PER1_TIMER2_Msk                   (0x01UL << SCU_PER1_TIMER2_Pos)                         /*!< SCU PER1: TIMER2 Mask                   */
#define SCU_PER1_TIMER3_Pos                   19                                                      /*!< SCU PER1: TIMER3 Position               */
#define SCU_PER1_TIMER3_Msk                   (0x01UL << SCU_PER1_TIMER3_Pos)                         /*!< SCU PER1: TIMER3 Mask                   */

/* ----------------------------------  SCU_PER2  ---------------------------------- */
#define SCU_PER2_SPI_Pos                      0                                                       /*!< SCU PER2: SPI Position                  */
#define SCU_PER2_SPI_Msk                      (0x01UL << SCU_PER2_SPI_Pos)                            /*!< SCU PER2: SPI Mask                      */
#define SCU_PER2_I2C_Pos                      4                                                       /*!< SCU PER2: I2C Position                  */
#define SCU_PER2_I2C_Msk                      (0x01UL << SCU_PER2_I2C_Pos)                            /*!< SCU PER2: I2C Mask                      */
#define SCU_PER2_UART0_Pos                    8                                                       /*!< SCU PER2: UART0 Position                */
#define SCU_PER2_UART0_Msk                    (0x01UL << SCU_PER2_UART0_Pos)                          /*!< SCU PER2: UART0 Mask                    */
#define SCU_PER2_UART1_Pos                    9                                                       /*!< SCU PER2: UART1 Position                */
#define SCU_PER2_UART1_Msk                    (0x01UL << SCU_PER2_UART1_Pos)                          /*!< SCU PER2: UART1 Mask                    */
#define SCU_PER2_MPWM_Pos                     16                                                      /*!< SCU PER2: MPWM Position                 */
#define SCU_PER2_MPWM_Msk                     (0x01UL << SCU_PER2_MPWM_Pos)                           /*!< SCU PER2: MPWM Mask                     */
#define SCU_PER2_ADC_Pos                      20                                                      /*!< SCU PER2: ADC Position                  */
#define SCU_PER2_ADC_Msk                      (0x01UL << SCU_PER2_ADC_Pos)                            /*!< SCU PER2: ADC Mask                      */
#define SCU_PER2_OPAMP_Pos                    24                                                      /*!< SCU PER2: OPAMP Position                */
#define SCU_PER2_OPAMP_Msk                    (0x01UL << SCU_PER2_OPAMP_Pos)                          /*!< SCU PER2: OPAMP Mask                    */
#define SCU_PER2_CMP_Pos                      28                                                      /*!< SCU PER2: CMP Position                  */
#define SCU_PER2_CMP_Msk                      (0x01UL << SCU_PER2_CMP_Pos)                            /*!< SCU PER2: CMP Mask                      */
#define SCU_PER2_CRC_Pos                      29                                                      /*!< SCU PER2: CRC Position                  */
#define SCU_PER2_CRC_Msk                      (0x01UL << SCU_PER2_CRC_Pos)                            /*!< SCU PER2: CRC Mask                      */

/* ----------------------------------  SCU_PCER1  --------------------------------- */
#define SCU_PCER1_DMA_Pos                     4                                                       /*!< SCU PCER1: DMA Position                 */
#define SCU_PCER1_DMA_Msk                     (0x01UL << SCU_PCER1_DMA_Pos)                           /*!< SCU PCER1: DMA Mask                     */
#define SCU_PCER1_FRT_Pos                     6                                                       /*!< SCU PCER1: FRT Position                 */
#define SCU_PCER1_FRT_Msk                     (0x01UL << SCU_PCER1_FRT_Pos)                           /*!< SCU PCER1: FRT Mask                     */
#define SCU_PCER1_GPIOA_Pos                   8                                                       /*!< SCU PCER1: GPIOA Position               */
#define SCU_PCER1_GPIOA_Msk                   (0x01UL << SCU_PCER1_GPIOA_Pos)                         /*!< SCU PCER1: GPIOA Mask                   */
#define SCU_PCER1_GPIOB_Pos                   9                                                       /*!< SCU PCER1: GPIOB Position               */
#define SCU_PCER1_GPIOB_Msk                   (0x01UL << SCU_PCER1_GPIOB_Pos)                         /*!< SCU PCER1: GPIOB Mask                   */
#define SCU_PCER1_GPIOC_Pos                   10                                                      /*!< SCU PCER1: GPIOC Position               */
#define SCU_PCER1_GPIOC_Msk                   (0x01UL << SCU_PCER1_GPIOC_Pos)                         /*!< SCU PCER1: GPIOC Mask                   */
#define SCU_PCER1_GPIOD_Pos                   11                                                      /*!< SCU PCER1: GPIOD Position               */
#define SCU_PCER1_GPIOD_Msk                   (0x01UL << SCU_PCER1_GPIOD_Pos)                         /*!< SCU PCER1: GPIOD Mask                   */
#define SCU_PCER1_TIMER0_Pos                  16                                                      /*!< SCU PCER1: TIMER0 Position              */
#define SCU_PCER1_TIMER0_Msk                  (0x01UL << SCU_PCER1_TIMER0_Pos)                        /*!< SCU PCER1: TIMER0 Mask                  */
#define SCU_PCER1_TIMER1_Pos                  17                                                      /*!< SCU PCER1: TIMER1 Position              */
#define SCU_PCER1_TIMER1_Msk                  (0x01UL << SCU_PCER1_TIMER1_Pos)                        /*!< SCU PCER1: TIMER1 Mask                  */
#define SCU_PCER1_TIMER2_Pos                  18                                                      /*!< SCU PCER1: TIMER2 Position              */
#define SCU_PCER1_TIMER2_Msk                  (0x01UL << SCU_PCER1_TIMER2_Pos)                        /*!< SCU PCER1: TIMER2 Mask                  */
#define SCU_PCER1_TIMER3_Pos                  19                                                      /*!< SCU PCER1: TIMER3 Position              */
#define SCU_PCER1_TIMER3_Msk                  (0x01UL << SCU_PCER1_TIMER3_Pos)                        /*!< SCU PCER1: TIMER3 Mask                  */

/* ----------------------------------  SCU_PCER2  --------------------------------- */
#define SCU_PCER2_SPI_Pos                     0                                                       /*!< SCU PCER2: SPI Position                 */
#define SCU_PCER2_SPI_Msk                     (0x01UL << SCU_PCER2_SPI_Pos)                           /*!< SCU PCER2: SPI Mask                     */
#define SCU_PCER2_I2C_Pos                     4                                                       /*!< SCU PCER2: I2C Position                 */
#define SCU_PCER2_I2C_Msk                     (0x01UL << SCU_PCER2_I2C_Pos)                           /*!< SCU PCER2: I2C Mask                     */
#define SCU_PCER2_UART0_Pos                   8                                                       /*!< SCU PCER2: UART0 Position               */
#define SCU_PCER2_UART0_Msk                   (0x01UL << SCU_PCER2_UART0_Pos)                         /*!< SCU PCER2: UART0 Mask                   */
#define SCU_PCER2_UART1_Pos                   9                                                       /*!< SCU PCER2: UART1 Position               */
#define SCU_PCER2_UART1_Msk                   (0x01UL << SCU_PCER2_UART1_Pos)                         /*!< SCU PCER2: UART1 Mask                   */
#define SCU_PCER2_MPWM_Pos                    16                                                      /*!< SCU PCER2: MPWM Position                */
#define SCU_PCER2_MPWM_Msk                    (0x01UL << SCU_PCER2_MPWM_Pos)                          /*!< SCU PCER2: MPWM Mask                    */
#define SCU_PCER2_ADC_Pos                     20                                                      /*!< SCU PCER2: ADC Position                 */
#define SCU_PCER2_ADC_Msk                     (0x01UL << SCU_PCER2_ADC_Pos)                           /*!< SCU PCER2: ADC Mask                     */
#define SCU_PCER2_OPAMP_Pos                   24                                                      /*!< SCU PCER2: OPAMP Position               */
#define SCU_PCER2_OPAMP_Msk                   (0x01UL << SCU_PCER2_OPAMP_Pos)                         /*!< SCU PCER2: OPAMP Mask                   */
#define SCU_PCER2_CMP_Pos                     28                                                      /*!< SCU PCER2: CMP Position                 */
#define SCU_PCER2_CMP_Msk                     (0x01UL << SCU_PCER2_CMP_Pos)                           /*!< SCU PCER2: CMP Mask                     */
#define SCU_PCER2_CRC_Pos                     29                                                      /*!< SCU PCER2: CRC Position                 */
#define SCU_PCER2_CRC_Msk                     (0x01UL << SCU_PCER2_CRC_Pos)                           /*!< SCU PCER2: CRC Mask                     */

/* ----------------------------------  SCU_CSCR  ---------------------------------- */
#define SCU_CSCR_HSECON_Pos                   1                                                       /*!< SCU CSCR: HSECON Position               */
#define SCU_CSCR_HSECON_Msk                   (0x01UL << SCU_CSCR_HSECON_Pos)                         /*!< SCU CSCR: HSECON Mask                   */
#define SCU_CSCR_HSICON_Pos                   3                                                       /*!< SCU CSCR: HSICON Position               */
#define SCU_CSCR_HSICON_Msk                   (0x01UL << SCU_CSCR_HSICON_Pos)                         /*!< SCU CSCR: HSICON Mask                   */
#define SCU_CSCR_LSICON_Pos                   5                                                       /*!< SCU CSCR: LSICON Position               */
#define SCU_CSCR_LSICON_Msk                   (0x01UL << SCU_CSCR_LSICON_Pos)                         /*!< SCU CSCR: LSICON Mask                   */
#define SCU_CSCR_LSECON_Pos                   7                                                       /*!< SCU CSCR: LSECON Position               */
#define SCU_CSCR_LSECON_Msk                   (0x01UL << SCU_CSCR_LSECON_Pos)                         /*!< SCU CSCR: LSECON Mask                   */

/* ----------------------------------  SCU_SCCR  ---------------------------------- */
#define SCU_SCCR_MCLKSEL_Pos                  0                                                       /*!< SCU SCCR: MCLKSEL Position              */
#define SCU_SCCR_MCLKSEL_Msk                  (0x07UL << SCU_SCCR_MCLKSEL_Pos)                        /*!< SCU SCCR: MCLKSEL Mask                  */
#define SCU_SCCR_PLLPREDIV_Pos                8                                                       /*!< SCU SCCR: PLLPREDIV Position            */
#define SCU_SCCR_PLLPREDIV_Msk                (0x03UL << SCU_SCCR_PLLPREDIV_Pos)                      /*!< SCU SCCR: PLLPREDIV Mask                */
#define SCU_SCCR_PLLCLKSEL_Pos                12                                                      /*!< SCU SCCR: PLLCLKSEL Position            */
#define SCU_SCCR_PLLCLKSEL_Msk                (0x01UL << SCU_SCCR_PLLCLKSEL_Pos)                      /*!< SCU SCCR: PLLCLKSEL Mask                */
#define SCU_SCCR_PCLKDIV_Pos                  16                                                      /*!< SCU SCCR: PCLKDIV Position              */
#define SCU_SCCR_PCLKDIV_Msk                  (0x07UL << SCU_SCCR_PCLKDIV_Pos)                        /*!< SCU SCCR: PCLKDIV Mask                  */
#define SCU_SCCR_HCLKDIV_Pos                  24                                                      /*!< SCU SCCR: HCLKDIV Position              */
#define SCU_SCCR_HCLKDIV_Msk                  (0x0fUL << SCU_SCCR_HCLKDIV_Pos)                        /*!< SCU SCCR: HCLKDIV Mask                  */

/* -----------------------------------  SCU_CMR  ---------------------------------- */
#define SCU_CMR_HSESTS_Pos                    0                                                       /*!< SCU CMR: HSESTS Position                */
#define SCU_CMR_HSESTS_Msk                    (0x01UL << SCU_CMR_HSESTS_Pos)                          /*!< SCU CMR: HSESTS Mask                    */
#define SCU_CMR_HSEFAIL_Pos                   1                                                       /*!< SCU CMR: HSEFAIL Position               */
#define SCU_CMR_HSEFAIL_Msk                   (0x01UL << SCU_CMR_HSEFAIL_Pos)                         /*!< SCU CMR: HSEFAIL Mask                   */
#define SCU_CMR_HSEIE_Pos                     2                                                       /*!< SCU CMR: HSEIE Position                 */
#define SCU_CMR_HSEIE_Msk                     (0x01UL << SCU_CMR_HSEIE_Pos)                           /*!< SCU CMR: HSEIE Mask                     */
#define SCU_CMR_HSEMNT_Pos                    3                                                       /*!< SCU CMR: HSEMNT Position                */
#define SCU_CMR_HSEMNT_Msk                    (0x01UL << SCU_CMR_HSEMNT_Pos)                          /*!< SCU CMR: HSEMNT Mask                    */
#define SCU_CMR_MCLKSTS_Pos                   4                                                       /*!< SCU CMR: MCLKSTS Position               */
#define SCU_CMR_MCLKSTS_Msk                   (0x01UL << SCU_CMR_MCLKSTS_Pos)                         /*!< SCU CMR: MCLKSTS Mask                   */
#define SCU_CMR_MCLKFAIL_Pos                  5                                                       /*!< SCU CMR: MCLKFAIL Position              */
#define SCU_CMR_MCLKFAIL_Msk                  (0x01UL << SCU_CMR_MCLKFAIL_Pos)                        /*!< SCU CMR: MCLKFAIL Mask                  */
#define SCU_CMR_MCLKIE_Pos                    6                                                       /*!< SCU CMR: MCLKIE Position                */
#define SCU_CMR_MCLKIE_Msk                    (0x01UL << SCU_CMR_MCLKIE_Pos)                          /*!< SCU CMR: MCLKIE Mask                    */
#define SCU_CMR_MCLKMNT_Pos                   7                                                       /*!< SCU CMR: MCLKMNT Position               */
#define SCU_CMR_MCLKMNT_Msk                   (0x01UL << SCU_CMR_MCLKMNT_Pos)                         /*!< SCU CMR: MCLKMNT Mask                   */
#define SCU_CMR_LSESTS_Pos                    8                                                       /*!< SCU CMR: LSESTS Position                */
#define SCU_CMR_LSESTS_Msk                    (0x01UL << SCU_CMR_LSESTS_Pos)                          /*!< SCU CMR: LSESTS Mask                    */
#define SCU_CMR_LSEFAIL_Pos                   9                                                       /*!< SCU CMR: LSEFAIL Position               */
#define SCU_CMR_LSEFAIL_Msk                   (0x01UL << SCU_CMR_LSEFAIL_Pos)                         /*!< SCU CMR: LSEFAIL Mask                   */
#define SCU_CMR_LSEIE_Pos                     10                                                      /*!< SCU CMR: LSEIE Position                 */
#define SCU_CMR_LSEIE_Msk                     (0x01UL << SCU_CMR_LSEIE_Pos)                           /*!< SCU CMR: LSEIE Mask                     */
#define SCU_CMR_LSEMNT_Pos                    11                                                      /*!< SCU CMR: LSEMNT Position                */
#define SCU_CMR_LSEMNT_Msk                    (0x01UL << SCU_CMR_LSEMNT_Pos)                          /*!< SCU CMR: LSEMNT Mask                    */
#define SCU_CMR_MCLKREC_Pos                   15                                                      /*!< SCU CMR: MCLKREC Position               */
#define SCU_CMR_MCLKREC_Msk                   (0x01UL << SCU_CMR_MCLKREC_Pos)                         /*!< SCU CMR: MCLKREC Mask                   */

/* -----------------------------------  SCU_COR  ---------------------------------- */
#define SCU_COR_CLKODIV_Pos                   0                                                       /*!< SCU COR: CLKODIV Position               */
#define SCU_COR_CLKODIV_Msk                   (0x0fUL << SCU_COR_CLKODIV_Pos)                         /*!< SCU COR: CLKODIV Mask                   */
#define SCU_COR_CLKOEN_Pos                    4                                                       /*!< SCU COR: CLKOEN Position                */
#define SCU_COR_CLKOEN_Msk                    (0x01UL << SCU_COR_CLKOEN_Pos)                          /*!< SCU COR: CLKOEN Mask                    */
#define SCU_COR_CLKOINSEL_Pos                 5                                                       /*!< SCU COR: CLKOINSEL Position             */
#define SCU_COR_CLKOINSEL_Msk                 (0x07UL << SCU_COR_CLKOINSEL_Pos)                       /*!< SCU COR: CLKOINSEL Mask                 */

/* ----------------------------------  SCU_NMICR  --------------------------------- */
#define SCU_NMICR_LVIEN_Pos                   0                                                       /*!< SCU NMICR: LVIEN Position               */
#define SCU_NMICR_LVIEN_Msk                   (0x01UL << SCU_NMICR_LVIEN_Pos)                         /*!< SCU NMICR: LVIEN Mask                   */
#define SCU_NMICR_MCLKFAILEN_Pos              1                                                       /*!< SCU NMICR: MCLKFAILEN Position          */
#define SCU_NMICR_MCLKFAILEN_Msk              (0x01UL << SCU_NMICR_MCLKFAILEN_Pos)                    /*!< SCU NMICR: MCLKFAILEN Mask              */
#define SCU_NMICR_WDTINTEN_Pos                2                                                       /*!< SCU NMICR: WDTINTEN Position            */
#define SCU_NMICR_WDTINTEN_Msk                (0x01UL << SCU_NMICR_WDTINTEN_Pos)                      /*!< SCU NMICR: WDTINTEN Mask                */
#define SCU_NMICR_OVPEN_Pos                   3                                                       /*!< SCU NMICR: OVPEN Position               */
#define SCU_NMICR_OVPEN_Msk                   (0x01UL << SCU_NMICR_OVPEN_Pos)                         /*!< SCU NMICR: OVPEN Mask                   */
#define SCU_NMICR_PROTEN_Pos                  4                                                       /*!< SCU NMICR: PROTEN Position              */
#define SCU_NMICR_PROTEN_Msk                  (0x01UL << SCU_NMICR_PROTEN_Pos)                        /*!< SCU NMICR: PROTEN Mask                  */
#define SCU_NMICR_NMIINEN_Pos                 15                                                      /*!< SCU NMICR: NMIINEN Position             */
#define SCU_NMICR_NMIINEN_Msk                 (0x01UL << SCU_NMICR_NMIINEN_Pos)                       /*!< SCU NMICR: NMIINEN Mask                 */
#define SCU_NMICR_NMISRC_Pos                  16                                                      /*!< SCU NMICR: NMISRC Position              */
#define SCU_NMICR_NMISRC_Msk                  (0x000000ffUL << SCU_NMICR_NMISRC_Pos)                  /*!< SCU NMICR: NMISRC Mask                  */

/* ----------------------------------  SCU_NMISR  --------------------------------- */
#define SCU_NMISR_LVISTS_Pos                  0                                                       /*!< SCU NMISR: LVISTS Position              */
#define SCU_NMISR_LVISTS_Msk                  (0x01UL << SCU_NMISR_LVISTS_Pos)                        /*!< SCU NMISR: LVISTS Mask                  */
#define SCU_NMISR_MCLKFAILSTS_Pos             1                                                       /*!< SCU NMISR: MCLKFAILSTS Position         */
#define SCU_NMISR_MCLKFAILSTS_Msk             (0x01UL << SCU_NMISR_MCLKFAILSTS_Pos)                   /*!< SCU NMISR: MCLKFAILSTS Mask             */
#define SCU_NMISR_WDTINTSTS_Pos               2                                                       /*!< SCU NMISR: WDTINTSTS Position           */
#define SCU_NMISR_WDTINTSTS_Msk               (0x01UL << SCU_NMISR_WDTINTSTS_Pos)                     /*!< SCU NMISR: WDTINTSTS Mask               */
#define SCU_NMISR_OVPSTS_Pos                  3                                                       /*!< SCU NMISR: OVPSTS Position              */
#define SCU_NMISR_OVPSTS_Msk                  (0x01UL << SCU_NMISR_OVPSTS_Pos)                        /*!< SCU NMISR: OVPSTS Mask                  */
#define SCU_NMISR_PROTSTS_Pos                 4                                                       /*!< SCU NMISR: PROTSTS Position             */
#define SCU_NMISR_PROTSTS_Msk                 (0x01UL << SCU_NMISR_PROTSTS_Pos)                       /*!< SCU NMISR: PROTSTS Mask                 */
#define SCU_NMISR_NMIINTSTS_Pos               15                                                      /*!< SCU NMISR: NMIINTSTS Position           */
#define SCU_NMISR_NMIINTSTS_Msk               (0x01UL << SCU_NMISR_NMIINTSTS_Pos)                     /*!< SCU NMISR: NMIINTSTS Mask               */
#define SCU_NMISR_WTIDKY_Pos                  24                                                      /*!< SCU NMISR: WTIDKY Position              */
#define SCU_NMISR_WTIDKY_Msk                  (0x000000ffUL << SCU_NMISR_WTIDKY_Pos)                  /*!< SCU NMISR: WTIDKY Mask                  */

/* ---------------------------------  SCU_PLLCON  --------------------------------- */
#define SCU_PLLCON_OUTDIV_Pos                 0                                                       /*!< SCU PLLCON: OUTDIV Position             */
#define SCU_PLLCON_OUTDIV_Msk                 (0x0fUL << SCU_PLLCON_OUTDIV_Pos)                       /*!< SCU PLLCON: OUTDIV Mask                 */
#define SCU_PLLCON_POSTDIV2_Pos               4                                                       /*!< SCU PLLCON: POSTDIV2 Position           */
#define SCU_PLLCON_POSTDIV2_Msk               (0x0fUL << SCU_PLLCON_POSTDIV2_Pos)                     /*!< SCU PLLCON: POSTDIV2 Mask               */
#define SCU_PLLCON_POSTDIV1_Pos               8                                                       /*!< SCU PLLCON: POSTDIV1 Position           */
#define SCU_PLLCON_POSTDIV1_Msk               (0x000000ffUL << SCU_PLLCON_POSTDIV1_Pos)               /*!< SCU PLLCON: POSTDIV1 Mask               */
#define SCU_PLLCON_PREDIV_Pos                 16                                                      /*!< SCU PLLCON: PREDIV Position             */
#define SCU_PLLCON_PREDIV_Msk                 (0x07UL << SCU_PLLCON_PREDIV_Pos)                       /*!< SCU PLLCON: PREDIV Mask                 */
#define SCU_PLLCON_PLLMODE_Pos                20                                                      /*!< SCU PLLCON: PLLMODE Position            */
#define SCU_PLLCON_PLLMODE_Msk                (0x01UL << SCU_PLLCON_PLLMODE_Pos)                      /*!< SCU PLLCON: PLLMODE Mask                */
#define SCU_PLLCON_BYPASSB_Pos                21                                                      /*!< SCU PLLCON: BYPASSB Position            */
#define SCU_PLLCON_BYPASSB_Msk                (0x01UL << SCU_PLLCON_BYPASSB_Pos)                      /*!< SCU PLLCON: BYPASSB Mask                */
#define SCU_PLLCON_PLLEN_Pos                  22                                                      /*!< SCU PLLCON: PLLEN Position              */
#define SCU_PLLCON_PLLEN_Msk                  (0x01UL << SCU_PLLCON_PLLEN_Pos)                        /*!< SCU PLLCON: PLLEN Mask                  */
#define SCU_PLLCON_PLLRSTB_Pos                23                                                      /*!< SCU PLLCON: PLLRSTB Position            */
#define SCU_PLLCON_PLLRSTB_Msk                (0x01UL << SCU_PLLCON_PLLRSTB_Pos)                      /*!< SCU PLLCON: PLLRSTB Mask                */
#define SCU_PLLCON_PLLVCOC_Pos                24                                                      /*!< SCU PLLCON: PLLVCOC Position            */
#define SCU_PLLCON_PLLVCOC_Msk                (0x03UL << SCU_PLLCON_PLLVCOC_Pos)                      /*!< SCU PLLCON: PLLVCOC Mask                */
#define SCU_PLLCON_PLLICP_Pos                 26                                                      /*!< SCU PLLCON: PLLICP Position             */
#define SCU_PLLCON_PLLICP_Msk                 (0x03UL << SCU_PLLCON_PLLICP_Pos)                       /*!< SCU PLLCON: PLLICP Mask                 */
#define SCU_PLLCON_PLLLOCK_Pos                31                                                      /*!< SCU PLLCON: PLLLOCK Position            */
#define SCU_PLLCON_PLLLOCK_Msk                (0x01UL << SCU_PLLCON_PLLLOCK_Pos)                      /*!< SCU PLLCON: PLLLOCK Mask                */

/* ---------------------------------  SCU_VDCCON  --------------------------------- */
#define SCU_VDCCON_VDCWDLY_Pos                0                                                       /*!< SCU VDCCON: VDCWDLY Position            */
#define SCU_VDCCON_VDCWDLY_Msk                (0x000000ffUL << SCU_VDCCON_VDCWDLY_Pos)                /*!< SCU VDCCON: VDCWDLY Mask                */

/* ----------------------------------  SCU_LVICR  --------------------------------- */
#define SCU_LVICR_LVIVS_Pos                   0                                                       /*!< SCU LVICR: LVIVS Position               */
#define SCU_LVICR_LVIVS_Msk                   (0x0fUL << SCU_LVICR_LVIVS_Pos)                         /*!< SCU LVICR: LVIVS Mask                   */
#define SCU_LVICR_LVIAON_Pos                  4                                                       /*!< SCU LVICR: LVIAON Position              */
#define SCU_LVICR_LVIAON_Msk                  (0x01UL << SCU_LVICR_LVIAON_Pos)                        /*!< SCU LVICR: LVIAON Mask                  */
#define SCU_LVICR_LVIINTEN_Pos                5                                                       /*!< SCU LVICR: LVIINTEN Position            */
#define SCU_LVICR_LVIINTEN_Msk                (0x01UL << SCU_LVICR_LVIINTEN_Pos)                      /*!< SCU LVICR: LVIINTEN Mask                */
#define SCU_LVICR_LVIEN_Pos                   7                                                       /*!< SCU LVICR: LVIEN Position               */
#define SCU_LVICR_LVIEN_Msk                   (0x01UL << SCU_LVICR_LVIEN_Pos)                         /*!< SCU LVICR: LVIEN Mask                   */

/* ----------------------------------  SCU_LVISR  --------------------------------- */
#define SCU_LVISR_LVIINTSTS_Pos               0                                                       /*!< SCU LVISR: LVIINTSTS Position           */
#define SCU_LVISR_LVIINTSTS_Msk               (0x01UL << SCU_LVISR_LVIINTSTS_Pos)                     /*!< SCU LVISR: LVIINTSTS Mask               */
#define SCU_LVISR_LVIFLAG_Pos                 5                                                       /*!< SCU LVISR: LVIFLAG Position             */
#define SCU_LVISR_LVIFLAG_Msk                 (0x01UL << SCU_LVISR_LVIFLAG_Pos)                       /*!< SCU LVISR: LVIFLAG Mask                 */
#define SCU_LVISR_WTIDKY_Pos                  24                                                      /*!< SCU LVISR: WTIDKY Position              */
#define SCU_LVISR_WTIDKY_Msk                  (0x000000ffUL << SCU_LVISR_WTIDKY_Pos)                  /*!< SCU LVISR: WTIDKY Mask                  */

/* ----------------------------------  SCU_LVRCR  --------------------------------- */
#define SCU_LVRCR_LVRVS_Pos                   0                                                       /*!< SCU LVRCR: LVRVS Position               */
#define SCU_LVRCR_LVRVS_Msk                   (0x0fUL << SCU_LVRCR_LVRVS_Pos)                         /*!< SCU LVRCR: LVRVS Mask                   */
#define SCU_LVRCR_LVRAON_Pos                  4                                                       /*!< SCU LVRCR: LVRAON Position              */
#define SCU_LVRCR_LVRAON_Msk                  (0x01UL << SCU_LVRCR_LVRAON_Pos)                        /*!< SCU LVRCR: LVRAON Mask                  */
#define SCU_LVRCR_LVREN_Pos                   8                                                       /*!< SCU LVRCR: LVREN Position               */
#define SCU_LVRCR_LVREN_Msk                   (0x000000ffUL << SCU_LVRCR_LVREN_Pos)                   /*!< SCU LVRCR: LVREN Mask                   */
#define SCU_LVRCR_LVRFLAG_Pos                 31                                                      /*!< SCU LVRCR: LVRFLAG Position             */
#define SCU_LVRCR_LVRFLAG_Msk                 (0x01UL << SCU_LVRCR_LVRFLAG_Pos)                       /*!< SCU LVRCR: LVRFLAG Mask                 */

/* ----------------------------------  SCU_EOSCR  --------------------------------- */
#define SCU_EOSCR_HSENFSEL_Pos                0                                                       /*!< SCU EOSCR: HSENFSEL Position            */
#define SCU_EOSCR_HSENFSEL_Msk                (0x03UL << SCU_EOSCR_HSENFSEL_Pos)                      /*!< SCU EOSCR: HSENFSEL Mask                */
#define SCU_EOSCR_HSENFEN_Pos                 4                                                       /*!< SCU EOSCR: HSENFEN Position             */
#define SCU_EOSCR_HSENFEN_Msk                 (0x01UL << SCU_EOSCR_HSENFEN_Pos)                       /*!< SCU EOSCR: HSENFEN Mask                 */
#define SCU_EOSCR_HSEISEL_Pos                 8                                                       /*!< SCU EOSCR: HSEISEL Position             */
#define SCU_EOSCR_HSEISEL_Msk                 (0x03UL << SCU_EOSCR_HSEISEL_Pos)                       /*!< SCU EOSCR: HSEISEL Mask                 */
#define SCU_EOSCR_LSENFEN_Pos                 16                                                      /*!< SCU EOSCR: LSENFEN Position             */
#define SCU_EOSCR_LSENFEN_Msk                 (0x01UL << SCU_EOSCR_LSENFEN_Pos)                       /*!< SCU EOSCR: LSENFEN Mask                 */
#define SCU_EOSCR_LSEISEL_Pos                 24                                                      /*!< SCU EOSCR: LSEISEL Position             */
#define SCU_EOSCR_LSEISEL_Msk                 (0x03UL << SCU_EOSCR_LSEISEL_Pos)                       /*!< SCU EOSCR: LSEISEL Mask                 */

/* ----------------------------------  SCU_MCCR1  --------------------------------- */
#define SCU_MCCR1_STDIV_Pos                   0                                                       /*!< SCU MCCR1: STDIV Position               */
#define SCU_MCCR1_STDIV_Msk                   (0x000000ffUL << SCU_MCCR1_STDIV_Pos)                   /*!< SCU MCCR1: STDIV Mask                   */
#define SCU_MCCR1_STCSEL_Pos                  8                                                       /*!< SCU MCCR1: STCSEL Position              */
#define SCU_MCCR1_STCSEL_Msk                  (0x07UL << SCU_MCCR1_STCSEL_Pos)                        /*!< SCU MCCR1: STCSEL Mask                  */
#define SCU_MCCR1_WDTCDIV_Pos                 16                                                      /*!< SCU MCCR1: WDTCDIV Position             */
#define SCU_MCCR1_WDTCDIV_Msk                 (0x000000ffUL << SCU_MCCR1_WDTCDIV_Pos)                 /*!< SCU MCCR1: WDTCDIV Mask                 */
#define SCU_MCCR1_WDTCSEL_Pos                 24                                                      /*!< SCU MCCR1: WDTCSEL Position             */
#define SCU_MCCR1_WDTCSEL_Msk                 (0x07UL << SCU_MCCR1_WDTCSEL_Pos)                       /*!< SCU MCCR1: WDTCSEL Mask                 */

/* ----------------------------------  SCU_MCCR3  --------------------------------- */
#define SCU_MCCR3_TIMER03CDIV_Pos             0                                                       /*!< SCU MCCR3: TIMER03CDIV Position         */
#define SCU_MCCR3_TIMER03CDIV_Msk             (0x000000ffUL << SCU_MCCR3_TIMER03CDIV_Pos)             /*!< SCU MCCR3: TIMER03CDIV Mask             */
#define SCU_MCCR3_TIMER03CSEL_Pos             8                                                       /*!< SCU MCCR3: TIMER03CSEL Position         */
#define SCU_MCCR3_TIMER03CSEL_Msk             (0x07UL << SCU_MCCR3_TIMER03CSEL_Pos)                   /*!< SCU MCCR3: TIMER03CSEL Mask             */

/* ----------------------------------  SCU_MCCR4  --------------------------------- */
#define SCU_MCCR4_PGADCDIV_Pos                16                                                      /*!< SCU MCCR4: PGADCDIV Position            */
#define SCU_MCCR4_PGADCDIV_Msk                (0x000000ffUL << SCU_MCCR4_PGADCDIV_Pos)                /*!< SCU MCCR4: PGADCDIV Mask                */
#define SCU_MCCR4_PGADCSEL_Pos                24                                                      /*!< SCU MCCR4: PGADCSEL Position            */
#define SCU_MCCR4_PGADCSEL_Msk                (0x07UL << SCU_MCCR4_PGADCSEL_Pos)                      /*!< SCU MCCR4: PGADCSEL Mask                */

/* ----------------------------------  SCU_MCCR5  --------------------------------- */
#define SCU_MCCR5_PGBDCDIV_Pos                0                                                       /*!< SCU MCCR5: PGBDCDIV Position            */
#define SCU_MCCR5_PGBDCDIV_Msk                (0x000000ffUL << SCU_MCCR5_PGBDCDIV_Pos)                /*!< SCU MCCR5: PGBDCDIV Mask                */
#define SCU_MCCR5_PGBDCSEL_Pos                8                                                       /*!< SCU MCCR5: PGBDCSEL Position            */
#define SCU_MCCR5_PGBDCSEL_Msk                (0x07UL << SCU_MCCR5_PGBDCSEL_Pos)                      /*!< SCU MCCR5: PGBDCSEL Mask                */
#define SCU_MCCR5_PGCDCDIV_Pos                16                                                      /*!< SCU MCCR5: PGCDCDIV Position            */
#define SCU_MCCR5_PGCDCDIV_Msk                (0x000000ffUL << SCU_MCCR5_PGCDCDIV_Pos)                /*!< SCU MCCR5: PGCDCDIV Mask                */
#define SCU_MCCR5_PGCDCSEL_Pos                24                                                      /*!< SCU MCCR5: PGCDCSEL Position            */
#define SCU_MCCR5_PGCDCSEL_Msk                (0x07UL << SCU_MCCR5_PGCDCSEL_Pos)                      /*!< SCU MCCR5: PGCDCSEL Mask                */

/* ----------------------------------  SCU_MCCR6  --------------------------------- */
#define SCU_MCCR6_FRTCDIV_Pos                 0                                                       /*!< SCU MCCR6: FRTCDIV Position             */
#define SCU_MCCR6_FRTCDIV_Msk                 (0x000000ffUL << SCU_MCCR6_FRTCDIV_Pos)                 /*!< SCU MCCR6: FRTCDIV Mask                 */
#define SCU_MCCR6_FRTCSEL_Pos                 8                                                       /*!< SCU MCCR6: FRTCSEL Position             */
#define SCU_MCCR6_FRTCSEL_Msk                 (0x07UL << SCU_MCCR6_FRTCSEL_Pos)                       /*!< SCU MCCR6: FRTCSEL Mask                 */

/* ----------------------------------  SCU_MCCR7  --------------------------------- */
#define SCU_MCCR7_UARTCDIV_Pos                16                                                      /*!< SCU MCCR7: UARTCDIV Position            */
#define SCU_MCCR7_UARTCDIV_Msk                (0x000000ffUL << SCU_MCCR7_UARTCDIV_Pos)                /*!< SCU MCCR7: UARTCDIV Mask                */
#define SCU_MCCR7_UARTCSEL_Pos                24                                                      /*!< SCU MCCR7: UARTCSEL Position            */
#define SCU_MCCR7_UARTCSEL_Msk                (0x07UL << SCU_MCCR7_UARTCSEL_Pos)                      /*!< SCU MCCR7: UARTCSEL Mask                */

/* ---------------------------------  SCU_SYSTEN  --------------------------------- */
#define SCU_SYSTEN_SYSTEN_Pos                 0                                                       /*!< SCU SYSTEN: SYSTEN Position             */
#define SCU_SYSTEN_SYSTEN_Msk                 (0x000000ffUL << SCU_SYSTEN_SYSTEN_Pos)                 /*!< SCU SYSTEN: SYSTEN Mask                 */
#define SCU_SYSTEN_ENS_Pos                    8                                                       /*!< SCU SYSTEN: ENS Position                */
#define SCU_SYSTEN_ENS_Msk                    (0x01UL << SCU_SYSTEN_ENS_Pos)                          /*!< SCU SYSTEN: ENS Mask                    */


/* ================================================================================ */
/* ================           Group 'PCU' Position & Mask          ================ */
/* ================================================================================ */


/* -----------------------------------  PCU_MR1  ---------------------------------- */
#define PCU_MR1_P0MUX_Pos                     0                                                       /*!< PCU MR1: P0MUX Position                 */
#define PCU_MR1_P0MUX_Msk                     (0x07UL << PCU_MR1_P0MUX_Pos)                           /*!< PCU MR1: P0MUX Mask                     */
#define PCU_MR1_P1MUX_Pos                     4                                                       /*!< PCU MR1: P1MUX Position                 */
#define PCU_MR1_P1MUX_Msk                     (0x07UL << PCU_MR1_P1MUX_Pos)                           /*!< PCU MR1: P1MUX Mask                     */
#define PCU_MR1_P2MUX_Pos                     8                                                       /*!< PCU MR1: P2MUX Position                 */
#define PCU_MR1_P2MUX_Msk                     (0x07UL << PCU_MR1_P2MUX_Pos)                           /*!< PCU MR1: P2MUX Mask                     */
#define PCU_MR1_P3MUX_Pos                     12                                                      /*!< PCU MR1: P3MUX Position                 */
#define PCU_MR1_P3MUX_Msk                     (0x07UL << PCU_MR1_P3MUX_Pos)                           /*!< PCU MR1: P3MUX Mask                     */
#define PCU_MR1_P4MUX_Pos                     16                                                      /*!< PCU MR1: P4MUX Position                 */
#define PCU_MR1_P4MUX_Msk                     (0x07UL << PCU_MR1_P4MUX_Pos)                           /*!< PCU MR1: P4MUX Mask                     */
#define PCU_MR1_P5MUX_Pos                     20                                                      /*!< PCU MR1: P5MUX Position                 */
#define PCU_MR1_P5MUX_Msk                     (0x07UL << PCU_MR1_P5MUX_Pos)                           /*!< PCU MR1: P5MUX Mask                     */
#define PCU_MR1_P6MUX_Pos                     24                                                      /*!< PCU MR1: P6MUX Position                 */
#define PCU_MR1_P6MUX_Msk                     (0x07UL << PCU_MR1_P6MUX_Pos)                           /*!< PCU MR1: P6MUX Mask                     */
#define PCU_MR1_P7MUX_Pos                     28                                                      /*!< PCU MR1: P7MUX Position                 */
#define PCU_MR1_P7MUX_Msk                     (0x07UL << PCU_MR1_P7MUX_Pos)                           /*!< PCU MR1: P7MUX Mask                     */

/* -----------------------------------  PCU_MR2  ---------------------------------- */
#define PCU_MR2_P8MUX_Pos                     0                                                       /*!< PCU MR2: P8MUX Position                 */
#define PCU_MR2_P8MUX_Msk                     (0x07UL << PCU_MR2_P8MUX_Pos)                           /*!< PCU MR2: P8MUX Mask                     */
#define PCU_MR2_P9MUX_Pos                     4                                                       /*!< PCU MR2: P9MUX Position                 */
#define PCU_MR2_P9MUX_Msk                     (0x07UL << PCU_MR2_P9MUX_Pos)                           /*!< PCU MR2: P9MUX Mask                     */
#define PCU_MR2_P10MUX_Pos                    8                                                       /*!< PCU MR2: P10MUX Position                */
#define PCU_MR2_P10MUX_Msk                    (0x07UL << PCU_MR2_P10MUX_Pos)                          /*!< PCU MR2: P10MUX Mask                    */
#define PCU_MR2_P11MUX_Pos                    12                                                      /*!< PCU MR2: P11MUX Position                */
#define PCU_MR2_P11MUX_Msk                    (0x07UL << PCU_MR2_P11MUX_Pos)                          /*!< PCU MR2: P11MUX Mask                    */
#define PCU_MR2_P12MUX_Pos                    16                                                      /*!< PCU MR2: P12MUX Position                */
#define PCU_MR2_P12MUX_Msk                    (0x07UL << PCU_MR2_P12MUX_Pos)                          /*!< PCU MR2: P12MUX Mask                    */
#define PCU_MR2_P13MUX_Pos                    20                                                      /*!< PCU MR2: P13MUX Position                */
#define PCU_MR2_P13MUX_Msk                    (0x07UL << PCU_MR2_P13MUX_Pos)                          /*!< PCU MR2: P13MUX Mask                    */
#define PCU_MR2_P14MUX_Pos                    24                                                      /*!< PCU MR2: P14MUX Position                */
#define PCU_MR2_P14MUX_Msk                    (0x07UL << PCU_MR2_P14MUX_Pos)                          /*!< PCU MR2: P14MUX Mask                    */
#define PCU_MR2_P15MUX_Pos                    28                                                      /*!< PCU MR2: P15MUX Position                */
#define PCU_MR2_P15MUX_Msk                    (0x07UL << PCU_MR2_P15MUX_Pos)                          /*!< PCU MR2: P15MUX Mask                    */

/* -----------------------------------  PCU_CR  ----------------------------------- */
#define PCU_CR_P0_Pos                         0                                                       /*!< PCU CR: P0 Position                     */
#define PCU_CR_P0_Msk                         (0x03UL << PCU_CR_P0_Pos)                               /*!< PCU CR: P0 Mask                         */
#define PCU_CR_P1_Pos                         2                                                       /*!< PCU CR: P1 Position                     */
#define PCU_CR_P1_Msk                         (0x03UL << PCU_CR_P1_Pos)                               /*!< PCU CR: P1 Mask                         */
#define PCU_CR_P2_Pos                         4                                                       /*!< PCU CR: P2 Position                     */
#define PCU_CR_P2_Msk                         (0x03UL << PCU_CR_P2_Pos)                               /*!< PCU CR: P2 Mask                         */
#define PCU_CR_P3_Pos                         6                                                       /*!< PCU CR: P3 Position                     */
#define PCU_CR_P3_Msk                         (0x03UL << PCU_CR_P3_Pos)                               /*!< PCU CR: P3 Mask                         */
#define PCU_CR_P4_Pos                         8                                                       /*!< PCU CR: P4 Position                     */
#define PCU_CR_P4_Msk                         (0x03UL << PCU_CR_P4_Pos)                               /*!< PCU CR: P4 Mask                         */
#define PCU_CR_P5_Pos                         10                                                      /*!< PCU CR: P5 Position                     */
#define PCU_CR_P5_Msk                         (0x03UL << PCU_CR_P5_Pos)                               /*!< PCU CR: P5 Mask                         */
#define PCU_CR_P6_Pos                         12                                                      /*!< PCU CR: P6 Position                     */
#define PCU_CR_P6_Msk                         (0x03UL << PCU_CR_P6_Pos)                               /*!< PCU CR: P6 Mask                         */
#define PCU_CR_P7_Pos                         14                                                      /*!< PCU CR: P7 Position                     */
#define PCU_CR_P7_Msk                         (0x03UL << PCU_CR_P7_Pos)                               /*!< PCU CR: P7 Mask                         */
#define PCU_CR_P8_Pos                         16                                                      /*!< PCU CR: P8 Position                     */
#define PCU_CR_P8_Msk                         (0x03UL << PCU_CR_P8_Pos)                               /*!< PCU CR: P8 Mask                         */
#define PCU_CR_P9_Pos                         18                                                      /*!< PCU CR: P9 Position                     */
#define PCU_CR_P9_Msk                         (0x03UL << PCU_CR_P9_Pos)                               /*!< PCU CR: P9 Mask                         */
#define PCU_CR_P10_Pos                        20                                                      /*!< PCU CR: P10 Position                    */
#define PCU_CR_P10_Msk                        (0x03UL << PCU_CR_P10_Pos)                              /*!< PCU CR: P10 Mask                        */
#define PCU_CR_P11_Pos                        22                                                      /*!< PCU CR: P11 Position                    */
#define PCU_CR_P11_Msk                        (0x03UL << PCU_CR_P11_Pos)                              /*!< PCU CR: P11 Mask                        */
#define PCU_CR_P12_Pos                        24                                                      /*!< PCU CR: P12 Position                    */
#define PCU_CR_P12_Msk                        (0x03UL << PCU_CR_P12_Pos)                              /*!< PCU CR: P12 Mask                        */
#define PCU_CR_P13_Pos                        26                                                      /*!< PCU CR: P13 Position                    */
#define PCU_CR_P13_Msk                        (0x03UL << PCU_CR_P13_Pos)                              /*!< PCU CR: P13 Mask                        */
#define PCU_CR_P14_Pos                        28                                                      /*!< PCU CR: P14 Position                    */
#define PCU_CR_P14_Msk                        (0x03UL << PCU_CR_P14_Pos)                              /*!< PCU CR: P14 Mask                        */
#define PCU_CR_P15_Pos                        30                                                      /*!< PCU CR: P15 Position                    */
#define PCU_CR_P15_Msk                        (0x03UL << PCU_CR_P15_Pos)                              /*!< PCU CR: P15 Mask                        */

/* ----------------------------------  PCU_PRCR  ---------------------------------- */
#define PCU_PRCR_PUE0_Pos                     0                                                       /*!< PCU PRCR: PUE0 Position                 */
#define PCU_PRCR_PUE0_Msk                     (0x03UL << PCU_PRCR_PUE0_Pos)                           /*!< PCU PRCR: PUE0 Mask                     */
#define PCU_PRCR_PUE1_Pos                     2                                                       /*!< PCU PRCR: PUE1 Position                 */
#define PCU_PRCR_PUE1_Msk                     (0x03UL << PCU_PRCR_PUE1_Pos)                           /*!< PCU PRCR: PUE1 Mask                     */
#define PCU_PRCR_PUE2_Pos                     4                                                       /*!< PCU PRCR: PUE2 Position                 */
#define PCU_PRCR_PUE2_Msk                     (0x03UL << PCU_PRCR_PUE2_Pos)                           /*!< PCU PRCR: PUE2 Mask                     */
#define PCU_PRCR_PUE3_Pos                     6                                                       /*!< PCU PRCR: PUE3 Position                 */
#define PCU_PRCR_PUE3_Msk                     (0x03UL << PCU_PRCR_PUE3_Pos)                           /*!< PCU PRCR: PUE3 Mask                     */
#define PCU_PRCR_PUE4_Pos                     8                                                       /*!< PCU PRCR: PUE4 Position                 */
#define PCU_PRCR_PUE4_Msk                     (0x03UL << PCU_PRCR_PUE4_Pos)                           /*!< PCU PRCR: PUE4 Mask                     */
#define PCU_PRCR_PUE5_Pos                     10                                                      /*!< PCU PRCR: PUE5 Position                 */
#define PCU_PRCR_PUE5_Msk                     (0x03UL << PCU_PRCR_PUE5_Pos)                           /*!< PCU PRCR: PUE5 Mask                     */
#define PCU_PRCR_PUE6_Pos                     12                                                      /*!< PCU PRCR: PUE6 Position                 */
#define PCU_PRCR_PUE6_Msk                     (0x03UL << PCU_PRCR_PUE6_Pos)                           /*!< PCU PRCR: PUE6 Mask                     */
#define PCU_PRCR_PUE7_Pos                     14                                                      /*!< PCU PRCR: PUE7 Position                 */
#define PCU_PRCR_PUE7_Msk                     (0x03UL << PCU_PRCR_PUE7_Pos)                           /*!< PCU PRCR: PUE7 Mask                     */
#define PCU_PRCR_PUE8_Pos                     16                                                      /*!< PCU PRCR: PUE8 Position                 */
#define PCU_PRCR_PUE8_Msk                     (0x03UL << PCU_PRCR_PUE8_Pos)                           /*!< PCU PRCR: PUE8 Mask                     */
#define PCU_PRCR_PUE9_Pos                     18                                                      /*!< PCU PRCR: PUE9 Position                 */
#define PCU_PRCR_PUE9_Msk                     (0x03UL << PCU_PRCR_PUE9_Pos)                           /*!< PCU PRCR: PUE9 Mask                     */
#define PCU_PRCR_PUE10_Pos                    20                                                      /*!< PCU PRCR: PUE10 Position                */
#define PCU_PRCR_PUE10_Msk                    (0x03UL << PCU_PRCR_PUE10_Pos)                          /*!< PCU PRCR: PUE10 Mask                    */
#define PCU_PRCR_PUE11_Pos                    22                                                      /*!< PCU PRCR: PUE11 Position                */
#define PCU_PRCR_PUE11_Msk                    (0x03UL << PCU_PRCR_PUE11_Pos)                          /*!< PCU PRCR: PUE11 Mask                    */
#define PCU_PRCR_PUE12_Pos                    24                                                      /*!< PCU PRCR: PUE12 Position                */
#define PCU_PRCR_PUE12_Msk                    (0x03UL << PCU_PRCR_PUE12_Pos)                          /*!< PCU PRCR: PUE12 Mask                    */
#define PCU_PRCR_PUE13_Pos                    26                                                      /*!< PCU PRCR: PUE13 Position                */
#define PCU_PRCR_PUE13_Msk                    (0x03UL << PCU_PRCR_PUE13_Pos)                          /*!< PCU PRCR: PUE13 Mask                    */
#define PCU_PRCR_PUE14_Pos                    28                                                      /*!< PCU PRCR: PUE14 Position                */
#define PCU_PRCR_PUE14_Msk                    (0x03UL << PCU_PRCR_PUE14_Pos)                          /*!< PCU PRCR: PUE14 Mask                    */
#define PCU_PRCR_PUE15_Pos                    30                                                      /*!< PCU PRCR: PUE15 Position                */
#define PCU_PRCR_PUE15_Msk                    (0x03UL << PCU_PRCR_PUE15_Pos)                          /*!< PCU PRCR: PUE15 Mask                    */

/* -----------------------------------  PCU_DER  ---------------------------------- */
#define PCU_DER_PDE0_Pos                      0                                                       /*!< PCU DER: PDE0 Position                  */
#define PCU_DER_PDE0_Msk                      (0x01UL << PCU_DER_PDE0_Pos)                            /*!< PCU DER: PDE0 Mask                      */
#define PCU_DER_PDE1_Pos                      1                                                       /*!< PCU DER: PDE1 Position                  */
#define PCU_DER_PDE1_Msk                      (0x01UL << PCU_DER_PDE1_Pos)                            /*!< PCU DER: PDE1 Mask                      */
#define PCU_DER_PDE2_Pos                      2                                                       /*!< PCU DER: PDE2 Position                  */
#define PCU_DER_PDE2_Msk                      (0x01UL << PCU_DER_PDE2_Pos)                            /*!< PCU DER: PDE2 Mask                      */
#define PCU_DER_PDE3_Pos                      3                                                       /*!< PCU DER: PDE3 Position                  */
#define PCU_DER_PDE3_Msk                      (0x01UL << PCU_DER_PDE3_Pos)                            /*!< PCU DER: PDE3 Mask                      */
#define PCU_DER_PDE4_Pos                      4                                                       /*!< PCU DER: PDE4 Position                  */
#define PCU_DER_PDE4_Msk                      (0x01UL << PCU_DER_PDE4_Pos)                            /*!< PCU DER: PDE4 Mask                      */
#define PCU_DER_PDE5_Pos                      5                                                       /*!< PCU DER: PDE5 Position                  */
#define PCU_DER_PDE5_Msk                      (0x01UL << PCU_DER_PDE5_Pos)                            /*!< PCU DER: PDE5 Mask                      */
#define PCU_DER_PDE6_Pos                      6                                                       /*!< PCU DER: PDE6 Position                  */
#define PCU_DER_PDE6_Msk                      (0x01UL << PCU_DER_PDE6_Pos)                            /*!< PCU DER: PDE6 Mask                      */
#define PCU_DER_PDE7_Pos                      7                                                       /*!< PCU DER: PDE7 Position                  */
#define PCU_DER_PDE7_Msk                      (0x01UL << PCU_DER_PDE7_Pos)                            /*!< PCU DER: PDE7 Mask                      */
#define PCU_DER_PDE8_Pos                      8                                                       /*!< PCU DER: PDE8 Position                  */
#define PCU_DER_PDE8_Msk                      (0x01UL << PCU_DER_PDE8_Pos)                            /*!< PCU DER: PDE8 Mask                      */
#define PCU_DER_PDE9_Pos                      9                                                       /*!< PCU DER: PDE9 Position                  */
#define PCU_DER_PDE9_Msk                      (0x01UL << PCU_DER_PDE9_Pos)                            /*!< PCU DER: PDE9 Mask                      */
#define PCU_DER_PDE10_Pos                     10                                                      /*!< PCU DER: PDE10 Position                 */
#define PCU_DER_PDE10_Msk                     (0x01UL << PCU_DER_PDE10_Pos)                           /*!< PCU DER: PDE10 Mask                     */
#define PCU_DER_PDE11_Pos                     11                                                      /*!< PCU DER: PDE11 Position                 */
#define PCU_DER_PDE11_Msk                     (0x01UL << PCU_DER_PDE11_Pos)                           /*!< PCU DER: PDE11 Mask                     */
#define PCU_DER_PDE12_Pos                     12                                                      /*!< PCU DER: PDE12 Position                 */
#define PCU_DER_PDE12_Msk                     (0x01UL << PCU_DER_PDE12_Pos)                           /*!< PCU DER: PDE12 Mask                     */
#define PCU_DER_PDE13_Pos                     13                                                      /*!< PCU DER: PDE13 Position                 */
#define PCU_DER_PDE13_Msk                     (0x01UL << PCU_DER_PDE13_Pos)                           /*!< PCU DER: PDE13 Mask                     */
#define PCU_DER_PDE14_Pos                     14                                                      /*!< PCU DER: PDE14 Position                 */
#define PCU_DER_PDE14_Msk                     (0x01UL << PCU_DER_PDE14_Pos)                           /*!< PCU DER: PDE14 Mask                     */
#define PCU_DER_PDE15_Pos                     15                                                      /*!< PCU DER: PDE15 Position                 */
#define PCU_DER_PDE15_Msk                     (0x01UL << PCU_DER_PDE15_Pos)                           /*!< PCU DER: PDE15 Mask                     */

/* -----------------------------------  PCU_STR  ---------------------------------- */
#define PCU_STR_PST0_Pos                      0                                                       /*!< PCU STR: PST0 Position                  */
#define PCU_STR_PST0_Msk                      (0x01UL << PCU_STR_PST0_Pos)                            /*!< PCU STR: PST0 Mask                      */
#define PCU_STR_PST1_Pos                      1                                                       /*!< PCU STR: PST1 Position                  */
#define PCU_STR_PST1_Msk                      (0x01UL << PCU_STR_PST1_Pos)                            /*!< PCU STR: PST1 Mask                      */
#define PCU_STR_PST2_Pos                      2                                                       /*!< PCU STR: PST2 Position                  */
#define PCU_STR_PST2_Msk                      (0x01UL << PCU_STR_PST2_Pos)                            /*!< PCU STR: PST2 Mask                      */
#define PCU_STR_PST3_Pos                      3                                                       /*!< PCU STR: PST3 Position                  */
#define PCU_STR_PST3_Msk                      (0x01UL << PCU_STR_PST3_Pos)                            /*!< PCU STR: PST3 Mask                      */
#define PCU_STR_PST4_Pos                      4                                                       /*!< PCU STR: PST4 Position                  */
#define PCU_STR_PST4_Msk                      (0x01UL << PCU_STR_PST4_Pos)                            /*!< PCU STR: PST4 Mask                      */
#define PCU_STR_PST5_Pos                      5                                                       /*!< PCU STR: PST5 Position                  */
#define PCU_STR_PST5_Msk                      (0x01UL << PCU_STR_PST5_Pos)                            /*!< PCU STR: PST5 Mask                      */
#define PCU_STR_PST6_Pos                      6                                                       /*!< PCU STR: PST6 Position                  */
#define PCU_STR_PST6_Msk                      (0x01UL << PCU_STR_PST6_Pos)                            /*!< PCU STR: PST6 Mask                      */
#define PCU_STR_PST7_Pos                      7                                                       /*!< PCU STR: PST7 Position                  */
#define PCU_STR_PST7_Msk                      (0x01UL << PCU_STR_PST7_Pos)                            /*!< PCU STR: PST7 Mask                      */
#define PCU_STR_PST8_Pos                      8                                                       /*!< PCU STR: PST8 Position                  */
#define PCU_STR_PST8_Msk                      (0x01UL << PCU_STR_PST8_Pos)                            /*!< PCU STR: PST8 Mask                      */
#define PCU_STR_PST9_Pos                      9                                                       /*!< PCU STR: PST9 Position                  */
#define PCU_STR_PST9_Msk                      (0x01UL << PCU_STR_PST9_Pos)                            /*!< PCU STR: PST9 Mask                      */
#define PCU_STR_PST10_Pos                     10                                                      /*!< PCU STR: PST10 Position                 */
#define PCU_STR_PST10_Msk                     (0x01UL << PCU_STR_PST10_Pos)                           /*!< PCU STR: PST10 Mask                     */
#define PCU_STR_PST11_Pos                     11                                                      /*!< PCU STR: PST11 Position                 */
#define PCU_STR_PST11_Msk                     (0x01UL << PCU_STR_PST11_Pos)                           /*!< PCU STR: PST11 Mask                     */
#define PCU_STR_PST12_Pos                     12                                                      /*!< PCU STR: PST12 Position                 */
#define PCU_STR_PST12_Msk                     (0x01UL << PCU_STR_PST12_Pos)                           /*!< PCU STR: PST12 Mask                     */
#define PCU_STR_PST13_Pos                     13                                                      /*!< PCU STR: PST13 Position                 */
#define PCU_STR_PST13_Msk                     (0x01UL << PCU_STR_PST13_Pos)                           /*!< PCU STR: PST13 Mask                     */
#define PCU_STR_PST14_Pos                     14                                                      /*!< PCU STR: PST14 Position                 */
#define PCU_STR_PST14_Msk                     (0x01UL << PCU_STR_PST14_Pos)                           /*!< PCU STR: PST14 Mask                     */
#define PCU_STR_PST15_Pos                     15                                                      /*!< PCU STR: PST15 Position                 */
#define PCU_STR_PST15_Msk                     (0x01UL << PCU_STR_PST15_Pos)                           /*!< PCU STR: PST15 Mask                     */

/* -----------------------------------  PCU_IER  ---------------------------------- */
#define PCU_IER_PIE0_Pos                      0                                                       /*!< PCU IER: PIE0 Position                  */
#define PCU_IER_PIE0_Msk                      (0x03UL << PCU_IER_PIE0_Pos)                            /*!< PCU IER: PIE0 Mask                      */
#define PCU_IER_PIE1_Pos                      2                                                       /*!< PCU IER: PIE1 Position                  */
#define PCU_IER_PIE1_Msk                      (0x03UL << PCU_IER_PIE1_Pos)                            /*!< PCU IER: PIE1 Mask                      */
#define PCU_IER_PIE2_Pos                      4                                                       /*!< PCU IER: PIE2 Position                  */
#define PCU_IER_PIE2_Msk                      (0x03UL << PCU_IER_PIE2_Pos)                            /*!< PCU IER: PIE2 Mask                      */
#define PCU_IER_PIE3_Pos                      6                                                       /*!< PCU IER: PIE3 Position                  */
#define PCU_IER_PIE3_Msk                      (0x03UL << PCU_IER_PIE3_Pos)                            /*!< PCU IER: PIE3 Mask                      */
#define PCU_IER_PIE4_Pos                      8                                                       /*!< PCU IER: PIE4 Position                  */
#define PCU_IER_PIE4_Msk                      (0x03UL << PCU_IER_PIE4_Pos)                            /*!< PCU IER: PIE4 Mask                      */
#define PCU_IER_PIE5_Pos                      10                                                      /*!< PCU IER: PIE5 Position                  */
#define PCU_IER_PIE5_Msk                      (0x03UL << PCU_IER_PIE5_Pos)                            /*!< PCU IER: PIE5 Mask                      */
#define PCU_IER_PIE6_Pos                      12                                                      /*!< PCU IER: PIE6 Position                  */
#define PCU_IER_PIE6_Msk                      (0x03UL << PCU_IER_PIE6_Pos)                            /*!< PCU IER: PIE6 Mask                      */
#define PCU_IER_PIE7_Pos                      14                                                      /*!< PCU IER: PIE7 Position                  */
#define PCU_IER_PIE7_Msk                      (0x03UL << PCU_IER_PIE7_Pos)                            /*!< PCU IER: PIE7 Mask                      */
#define PCU_IER_PIE8_Pos                      16                                                      /*!< PCU IER: PIE8 Position                  */
#define PCU_IER_PIE8_Msk                      (0x03UL << PCU_IER_PIE8_Pos)                            /*!< PCU IER: PIE8 Mask                      */
#define PCU_IER_PIE9_Pos                      18                                                      /*!< PCU IER: PIE9 Position                  */
#define PCU_IER_PIE9_Msk                      (0x03UL << PCU_IER_PIE9_Pos)                            /*!< PCU IER: PIE9 Mask                      */
#define PCU_IER_PIE10_Pos                     20                                                      /*!< PCU IER: PIE10 Position                 */
#define PCU_IER_PIE10_Msk                     (0x03UL << PCU_IER_PIE10_Pos)                           /*!< PCU IER: PIE10 Mask                     */
#define PCU_IER_PIE11_Pos                     22                                                      /*!< PCU IER: PIE11 Position                 */
#define PCU_IER_PIE11_Msk                     (0x03UL << PCU_IER_PIE11_Pos)                           /*!< PCU IER: PIE11 Mask                     */
#define PCU_IER_PIE12_Pos                     24                                                      /*!< PCU IER: PIE12 Position                 */
#define PCU_IER_PIE12_Msk                     (0x03UL << PCU_IER_PIE12_Pos)                           /*!< PCU IER: PIE12 Mask                     */
#define PCU_IER_PIE13_Pos                     26                                                      /*!< PCU IER: PIE13 Position                 */
#define PCU_IER_PIE13_Msk                     (0x03UL << PCU_IER_PIE13_Pos)                           /*!< PCU IER: PIE13 Mask                     */
#define PCU_IER_PIE14_Pos                     28                                                      /*!< PCU IER: PIE14 Position                 */
#define PCU_IER_PIE14_Msk                     (0x03UL << PCU_IER_PIE14_Pos)                           /*!< PCU IER: PIE14 Mask                     */
#define PCU_IER_PIE15_Pos                     30                                                      /*!< PCU IER: PIE15 Position                 */
#define PCU_IER_PIE15_Msk                     (0x03UL << PCU_IER_PIE15_Pos)                           /*!< PCU IER: PIE15 Mask                     */

/* -----------------------------------  PCU_ISR  ---------------------------------- */
#define PCU_ISR_PIS0_Pos                      0                                                       /*!< PCU ISR: PIS0 Position                  */
#define PCU_ISR_PIS0_Msk                      (0x03UL << PCU_ISR_PIS0_Pos)                            /*!< PCU ISR: PIS0 Mask                      */
#define PCU_ISR_PIS1_Pos                      2                                                       /*!< PCU ISR: PIS1 Position                  */
#define PCU_ISR_PIS1_Msk                      (0x03UL << PCU_ISR_PIS1_Pos)                            /*!< PCU ISR: PIS1 Mask                      */
#define PCU_ISR_PIS2_Pos                      4                                                       /*!< PCU ISR: PIS2 Position                  */
#define PCU_ISR_PIS2_Msk                      (0x03UL << PCU_ISR_PIS2_Pos)                            /*!< PCU ISR: PIS2 Mask                      */
#define PCU_ISR_PIS3_Pos                      6                                                       /*!< PCU ISR: PIS3 Position                  */
#define PCU_ISR_PIS3_Msk                      (0x03UL << PCU_ISR_PIS3_Pos)                            /*!< PCU ISR: PIS3 Mask                      */
#define PCU_ISR_PIS4_Pos                      8                                                       /*!< PCU ISR: PIS4 Position                  */
#define PCU_ISR_PIS4_Msk                      (0x03UL << PCU_ISR_PIS4_Pos)                            /*!< PCU ISR: PIS4 Mask                      */
#define PCU_ISR_PIS5_Pos                      10                                                      /*!< PCU ISR: PIS5 Position                  */
#define PCU_ISR_PIS5_Msk                      (0x03UL << PCU_ISR_PIS5_Pos)                            /*!< PCU ISR: PIS5 Mask                      */
#define PCU_ISR_PIS6_Pos                      12                                                      /*!< PCU ISR: PIS6 Position                  */
#define PCU_ISR_PIS6_Msk                      (0x03UL << PCU_ISR_PIS6_Pos)                            /*!< PCU ISR: PIS6 Mask                      */
#define PCU_ISR_PIS7_Pos                      14                                                      /*!< PCU ISR: PIS7 Position                  */
#define PCU_ISR_PIS7_Msk                      (0x03UL << PCU_ISR_PIS7_Pos)                            /*!< PCU ISR: PIS7 Mask                      */
#define PCU_ISR_PIS8_Pos                      16                                                      /*!< PCU ISR: PIS8 Position                  */
#define PCU_ISR_PIS8_Msk                      (0x03UL << PCU_ISR_PIS8_Pos)                            /*!< PCU ISR: PIS8 Mask                      */
#define PCU_ISR_PIS9_Pos                      18                                                      /*!< PCU ISR: PIS9 Position                  */
#define PCU_ISR_PIS9_Msk                      (0x03UL << PCU_ISR_PIS9_Pos)                            /*!< PCU ISR: PIS9 Mask                      */
#define PCU_ISR_PIS10_Pos                     20                                                      /*!< PCU ISR: PIS10 Position                 */
#define PCU_ISR_PIS10_Msk                     (0x03UL << PCU_ISR_PIS10_Pos)                           /*!< PCU ISR: PIS10 Mask                     */
#define PCU_ISR_PIS11_Pos                     22                                                      /*!< PCU ISR: PIS11 Position                 */
#define PCU_ISR_PIS11_Msk                     (0x03UL << PCU_ISR_PIS11_Pos)                           /*!< PCU ISR: PIS11 Mask                     */
#define PCU_ISR_PIS12_Pos                     24                                                      /*!< PCU ISR: PIS12 Position                 */
#define PCU_ISR_PIS12_Msk                     (0x03UL << PCU_ISR_PIS12_Pos)                           /*!< PCU ISR: PIS12 Mask                     */
#define PCU_ISR_PIS13_Pos                     26                                                      /*!< PCU ISR: PIS13 Position                 */
#define PCU_ISR_PIS13_Msk                     (0x03UL << PCU_ISR_PIS13_Pos)                           /*!< PCU ISR: PIS13 Mask                     */
#define PCU_ISR_PIS14_Pos                     28                                                      /*!< PCU ISR: PIS14 Position                 */
#define PCU_ISR_PIS14_Msk                     (0x03UL << PCU_ISR_PIS14_Pos)                           /*!< PCU ISR: PIS14 Mask                     */
#define PCU_ISR_PIS15_Pos                     30                                                      /*!< PCU ISR: PIS15 Position                 */
#define PCU_ISR_PIS15_Msk                     (0x03UL << PCU_ISR_PIS15_Pos)                           /*!< PCU ISR: PIS15 Mask                     */

/* -----------------------------------  PCU_ICR  ---------------------------------- */
#define PCU_ICR_PIC0_Pos                      0                                                       /*!< PCU ICR: PIC0 Position                  */
#define PCU_ICR_PIC0_Msk                      (0x03UL << PCU_ICR_PIC0_Pos)                            /*!< PCU ICR: PIC0 Mask                      */
#define PCU_ICR_PIC1_Pos                      2                                                       /*!< PCU ICR: PIC1 Position                  */
#define PCU_ICR_PIC1_Msk                      (0x03UL << PCU_ICR_PIC1_Pos)                            /*!< PCU ICR: PIC1 Mask                      */
#define PCU_ICR_PIC2_Pos                      4                                                       /*!< PCU ICR: PIC2 Position                  */
#define PCU_ICR_PIC2_Msk                      (0x03UL << PCU_ICR_PIC2_Pos)                            /*!< PCU ICR: PIC2 Mask                      */
#define PCU_ICR_PIC3_Pos                      6                                                       /*!< PCU ICR: PIC3 Position                  */
#define PCU_ICR_PIC3_Msk                      (0x03UL << PCU_ICR_PIC3_Pos)                            /*!< PCU ICR: PIC3 Mask                      */
#define PCU_ICR_PIC4_Pos                      8                                                       /*!< PCU ICR: PIC4 Position                  */
#define PCU_ICR_PIC4_Msk                      (0x03UL << PCU_ICR_PIC4_Pos)                            /*!< PCU ICR: PIC4 Mask                      */
#define PCU_ICR_PIC5_Pos                      10                                                      /*!< PCU ICR: PIC5 Position                  */
#define PCU_ICR_PIC5_Msk                      (0x03UL << PCU_ICR_PIC5_Pos)                            /*!< PCU ICR: PIC5 Mask                      */
#define PCU_ICR_PIC6_Pos                      12                                                      /*!< PCU ICR: PIC6 Position                  */
#define PCU_ICR_PIC6_Msk                      (0x03UL << PCU_ICR_PIC6_Pos)                            /*!< PCU ICR: PIC6 Mask                      */
#define PCU_ICR_PIC7_Pos                      14                                                      /*!< PCU ICR: PIC7 Position                  */
#define PCU_ICR_PIC7_Msk                      (0x03UL << PCU_ICR_PIC7_Pos)                            /*!< PCU ICR: PIC7 Mask                      */
#define PCU_ICR_PIC8_Pos                      16                                                      /*!< PCU ICR: PIC8 Position                  */
#define PCU_ICR_PIC8_Msk                      (0x03UL << PCU_ICR_PIC8_Pos)                            /*!< PCU ICR: PIC8 Mask                      */
#define PCU_ICR_PIC9_Pos                      18                                                      /*!< PCU ICR: PIC9 Position                  */
#define PCU_ICR_PIC9_Msk                      (0x03UL << PCU_ICR_PIC9_Pos)                            /*!< PCU ICR: PIC9 Mask                      */
#define PCU_ICR_PIC10_Pos                     20                                                      /*!< PCU ICR: PIC10 Position                 */
#define PCU_ICR_PIC10_Msk                     (0x03UL << PCU_ICR_PIC10_Pos)                           /*!< PCU ICR: PIC10 Mask                     */
#define PCU_ICR_PIC11_Pos                     22                                                      /*!< PCU ICR: PIC11 Position                 */
#define PCU_ICR_PIC11_Msk                     (0x03UL << PCU_ICR_PIC11_Pos)                           /*!< PCU ICR: PIC11 Mask                     */
#define PCU_ICR_PIC12_Pos                     24                                                      /*!< PCU ICR: PIC12 Position                 */
#define PCU_ICR_PIC12_Msk                     (0x03UL << PCU_ICR_PIC12_Pos)                           /*!< PCU ICR: PIC12 Mask                     */
#define PCU_ICR_PIC13_Pos                     26                                                      /*!< PCU ICR: PIC13 Position                 */
#define PCU_ICR_PIC13_Msk                     (0x03UL << PCU_ICR_PIC13_Pos)                           /*!< PCU ICR: PIC13 Mask                     */
#define PCU_ICR_PIC14_Pos                     28                                                      /*!< PCU ICR: PIC14 Position                 */
#define PCU_ICR_PIC14_Msk                     (0x03UL << PCU_ICR_PIC14_Pos)                           /*!< PCU ICR: PIC14 Mask                     */
#define PCU_ICR_PIC15_Pos                     30                                                      /*!< PCU ICR: PIC15 Position                 */
#define PCU_ICR_PIC15_Msk                     (0x03UL << PCU_ICR_PIC15_Pos)                           /*!< PCU ICR: PIC15 Mask                     */

/* -----------------------------------  PCU_ODR  ---------------------------------- */
#define PCU_ODR_POD_Pos                       0                                                       /*!< PCU ODR: POD Position                   */
#define PCU_ODR_POD_Msk                       (0x0000ffffUL << PCU_ODR_POD_Pos)                       /*!< PCU ODR: POD Mask                       */

/* -----------------------------------  PCU_IDR  ---------------------------------- */
#define PCU_IDR_PID_Pos                       0                                                       /*!< PCU IDR: PID Position                   */
#define PCU_IDR_PID_Msk                       (0x0000ffffUL << PCU_IDR_PID_Pos)                       /*!< PCU IDR: PID Mask                       */

/* -----------------------------------  PCU_BSR  ---------------------------------- */
#define PCU_BSR_BSD0_Pos                      0                                                       /*!< PCU BSR: BSD0 Position                  */
#define PCU_BSR_BSD0_Msk                      (0x01UL << PCU_BSR_BSD0_Pos)                            /*!< PCU BSR: BSD0 Mask                      */
#define PCU_BSR_BSD1_Pos                      1                                                       /*!< PCU BSR: BSD1 Position                  */
#define PCU_BSR_BSD1_Msk                      (0x01UL << PCU_BSR_BSD1_Pos)                            /*!< PCU BSR: BSD1 Mask                      */
#define PCU_BSR_BSD2_Pos                      2                                                       /*!< PCU BSR: BSD2 Position                  */
#define PCU_BSR_BSD2_Msk                      (0x01UL << PCU_BSR_BSD2_Pos)                            /*!< PCU BSR: BSD2 Mask                      */
#define PCU_BSR_BSD3_Pos                      3                                                       /*!< PCU BSR: BSD3 Position                  */
#define PCU_BSR_BSD3_Msk                      (0x01UL << PCU_BSR_BSD3_Pos)                            /*!< PCU BSR: BSD3 Mask                      */
#define PCU_BSR_BSD4_Pos                      4                                                       /*!< PCU BSR: BSD4 Position                  */
#define PCU_BSR_BSD4_Msk                      (0x01UL << PCU_BSR_BSD4_Pos)                            /*!< PCU BSR: BSD4 Mask                      */
#define PCU_BSR_BSD5_Pos                      5                                                       /*!< PCU BSR: BSD5 Position                  */
#define PCU_BSR_BSD5_Msk                      (0x01UL << PCU_BSR_BSD5_Pos)                            /*!< PCU BSR: BSD5 Mask                      */
#define PCU_BSR_BSD6_Pos                      6                                                       /*!< PCU BSR: BSD6 Position                  */
#define PCU_BSR_BSD6_Msk                      (0x01UL << PCU_BSR_BSD6_Pos)                            /*!< PCU BSR: BSD6 Mask                      */
#define PCU_BSR_BSD7_Pos                      7                                                       /*!< PCU BSR: BSD7 Position                  */
#define PCU_BSR_BSD7_Msk                      (0x01UL << PCU_BSR_BSD7_Pos)                            /*!< PCU BSR: BSD7 Mask                      */
#define PCU_BSR_BSD8_Pos                      8                                                       /*!< PCU BSR: BSD8 Position                  */
#define PCU_BSR_BSD8_Msk                      (0x01UL << PCU_BSR_BSD8_Pos)                            /*!< PCU BSR: BSD8 Mask                      */
#define PCU_BSR_BSD9_Pos                      9                                                       /*!< PCU BSR: BSD9 Position                  */
#define PCU_BSR_BSD9_Msk                      (0x01UL << PCU_BSR_BSD9_Pos)                            /*!< PCU BSR: BSD9 Mask                      */
#define PCU_BSR_BSD10_Pos                     10                                                      /*!< PCU BSR: BSD10 Position                 */
#define PCU_BSR_BSD10_Msk                     (0x01UL << PCU_BSR_BSD10_Pos)                           /*!< PCU BSR: BSD10 Mask                     */
#define PCU_BSR_BSD11_Pos                     11                                                      /*!< PCU BSR: BSD11 Position                 */
#define PCU_BSR_BSD11_Msk                     (0x01UL << PCU_BSR_BSD11_Pos)                           /*!< PCU BSR: BSD11 Mask                     */
#define PCU_BSR_BSD12_Pos                     12                                                      /*!< PCU BSR: BSD12 Position                 */
#define PCU_BSR_BSD12_Msk                     (0x01UL << PCU_BSR_BSD12_Pos)                           /*!< PCU BSR: BSD12 Mask                     */
#define PCU_BSR_BSD13_Pos                     13                                                      /*!< PCU BSR: BSD13 Position                 */
#define PCU_BSR_BSD13_Msk                     (0x01UL << PCU_BSR_BSD13_Pos)                           /*!< PCU BSR: BSD13 Mask                     */
#define PCU_BSR_BSD14_Pos                     14                                                      /*!< PCU BSR: BSD14 Position                 */
#define PCU_BSR_BSD14_Msk                     (0x01UL << PCU_BSR_BSD14_Pos)                           /*!< PCU BSR: BSD14 Mask                     */
#define PCU_BSR_BSD15_Pos                     15                                                      /*!< PCU BSR: BSD15 Position                 */
#define PCU_BSR_BSD15_Msk                     (0x01UL << PCU_BSR_BSD15_Pos)                           /*!< PCU BSR: BSD15 Mask                     */
#define PCU_BSR_BCD0_Pos                      16                                                      /*!< PCU BSR: BCD0 Position                  */
#define PCU_BSR_BCD0_Msk                      (0x01UL << PCU_BSR_BCD0_Pos)                            /*!< PCU BSR: BCD0 Mask                      */
#define PCU_BSR_BCD1_Pos                      17                                                      /*!< PCU BSR: BCD1 Position                  */
#define PCU_BSR_BCD1_Msk                      (0x01UL << PCU_BSR_BCD1_Pos)                            /*!< PCU BSR: BCD1 Mask                      */
#define PCU_BSR_BCD2_Pos                      18                                                      /*!< PCU BSR: BCD2 Position                  */
#define PCU_BSR_BCD2_Msk                      (0x01UL << PCU_BSR_BCD2_Pos)                            /*!< PCU BSR: BCD2 Mask                      */
#define PCU_BSR_BCD3_Pos                      19                                                      /*!< PCU BSR: BCD3 Position                  */
#define PCU_BSR_BCD3_Msk                      (0x01UL << PCU_BSR_BCD3_Pos)                            /*!< PCU BSR: BCD3 Mask                      */
#define PCU_BSR_BCD4_Pos                      20                                                      /*!< PCU BSR: BCD4 Position                  */
#define PCU_BSR_BCD4_Msk                      (0x01UL << PCU_BSR_BCD4_Pos)                            /*!< PCU BSR: BCD4 Mask                      */
#define PCU_BSR_BCD5_Pos                      21                                                      /*!< PCU BSR: BCD5 Position                  */
#define PCU_BSR_BCD5_Msk                      (0x01UL << PCU_BSR_BCD5_Pos)                            /*!< PCU BSR: BCD5 Mask                      */
#define PCU_BSR_BCD6_Pos                      22                                                      /*!< PCU BSR: BCD6 Position                  */
#define PCU_BSR_BCD6_Msk                      (0x01UL << PCU_BSR_BCD6_Pos)                            /*!< PCU BSR: BCD6 Mask                      */
#define PCU_BSR_BCD7_Pos                      23                                                      /*!< PCU BSR: BCD7 Position                  */
#define PCU_BSR_BCD7_Msk                      (0x01UL << PCU_BSR_BCD7_Pos)                            /*!< PCU BSR: BCD7 Mask                      */
#define PCU_BSR_BCD8_Pos                      24                                                      /*!< PCU BSR: BCD8 Position                  */
#define PCU_BSR_BCD8_Msk                      (0x01UL << PCU_BSR_BCD8_Pos)                            /*!< PCU BSR: BCD8 Mask                      */
#define PCU_BSR_BCD9_Pos                      25                                                      /*!< PCU BSR: BCD9 Position                  */
#define PCU_BSR_BCD9_Msk                      (0x01UL << PCU_BSR_BCD9_Pos)                            /*!< PCU BSR: BCD9 Mask                      */
#define PCU_BSR_BCD10_Pos                     26                                                      /*!< PCU BSR: BCD10 Position                 */
#define PCU_BSR_BCD10_Msk                     (0x01UL << PCU_BSR_BCD10_Pos)                           /*!< PCU BSR: BCD10 Mask                     */
#define PCU_BSR_BCD11_Pos                     27                                                      /*!< PCU BSR: BCD11 Position                 */
#define PCU_BSR_BCD11_Msk                     (0x01UL << PCU_BSR_BCD11_Pos)                           /*!< PCU BSR: BCD11 Mask                     */
#define PCU_BSR_BCD12_Pos                     28                                                      /*!< PCU BSR: BCD12 Position                 */
#define PCU_BSR_BCD12_Msk                     (0x01UL << PCU_BSR_BCD12_Pos)                           /*!< PCU BSR: BCD12 Mask                     */
#define PCU_BSR_BCD13_Pos                     29                                                      /*!< PCU BSR: BCD13 Position                 */
#define PCU_BSR_BCD13_Msk                     (0x01UL << PCU_BSR_BCD13_Pos)                           /*!< PCU BSR: BCD13 Mask                     */
#define PCU_BSR_BCD14_Pos                     30                                                      /*!< PCU BSR: BCD14 Position                 */
#define PCU_BSR_BCD14_Msk                     (0x01UL << PCU_BSR_BCD14_Pos)                           /*!< PCU BSR: BCD14 Mask                     */
#define PCU_BSR_BCD15_Pos                     31                                                      /*!< PCU BSR: BCD15 Position                 */
#define PCU_BSR_BCD15_Msk                     (0x01UL << PCU_BSR_BCD15_Pos)                           /*!< PCU BSR: BCD15 Mask                     */

/* -----------------------------------  PCU_BCR  ---------------------------------- */
#define PCU_BCR_BCD0_Pos                      0                                                       /*!< PCU BCR: BCD0 Position                  */
#define PCU_BCR_BCD0_Msk                      (0x01UL << PCU_BCR_BCD0_Pos)                            /*!< PCU BCR: BCD0 Mask                      */
#define PCU_BCR_BCD1_Pos                      1                                                       /*!< PCU BCR: BCD1 Position                  */
#define PCU_BCR_BCD1_Msk                      (0x01UL << PCU_BCR_BCD1_Pos)                            /*!< PCU BCR: BCD1 Mask                      */
#define PCU_BCR_BCD2_Pos                      2                                                       /*!< PCU BCR: BCD2 Position                  */
#define PCU_BCR_BCD2_Msk                      (0x01UL << PCU_BCR_BCD2_Pos)                            /*!< PCU BCR: BCD2 Mask                      */
#define PCU_BCR_BCD3_Pos                      3                                                       /*!< PCU BCR: BCD3 Position                  */
#define PCU_BCR_BCD3_Msk                      (0x01UL << PCU_BCR_BCD3_Pos)                            /*!< PCU BCR: BCD3 Mask                      */
#define PCU_BCR_BCD4_Pos                      4                                                       /*!< PCU BCR: BCD4 Position                  */
#define PCU_BCR_BCD4_Msk                      (0x01UL << PCU_BCR_BCD4_Pos)                            /*!< PCU BCR: BCD4 Mask                      */
#define PCU_BCR_BCD5_Pos                      5                                                       /*!< PCU BCR: BCD5 Position                  */
#define PCU_BCR_BCD5_Msk                      (0x01UL << PCU_BCR_BCD5_Pos)                            /*!< PCU BCR: BCD5 Mask                      */
#define PCU_BCR_BCD6_Pos                      6                                                       /*!< PCU BCR: BCD6 Position                  */
#define PCU_BCR_BCD6_Msk                      (0x01UL << PCU_BCR_BCD6_Pos)                            /*!< PCU BCR: BCD6 Mask                      */
#define PCU_BCR_BCD7_Pos                      7                                                       /*!< PCU BCR: BCD7 Position                  */
#define PCU_BCR_BCD7_Msk                      (0x01UL << PCU_BCR_BCD7_Pos)                            /*!< PCU BCR: BCD7 Mask                      */
#define PCU_BCR_BCD8_Pos                      8                                                       /*!< PCU BCR: BCD8 Position                  */
#define PCU_BCR_BCD8_Msk                      (0x01UL << PCU_BCR_BCD8_Pos)                            /*!< PCU BCR: BCD8 Mask                      */
#define PCU_BCR_BCD9_Pos                      9                                                       /*!< PCU BCR: BCD9 Position                  */
#define PCU_BCR_BCD9_Msk                      (0x01UL << PCU_BCR_BCD9_Pos)                            /*!< PCU BCR: BCD9 Mask                      */
#define PCU_BCR_BCD10_Pos                     10                                                      /*!< PCU BCR: BCD10 Position                 */
#define PCU_BCR_BCD10_Msk                     (0x01UL << PCU_BCR_BCD10_Pos)                           /*!< PCU BCR: BCD10 Mask                     */
#define PCU_BCR_BCD11_Pos                     11                                                      /*!< PCU BCR: BCD11 Position                 */
#define PCU_BCR_BCD11_Msk                     (0x01UL << PCU_BCR_BCD11_Pos)                           /*!< PCU BCR: BCD11 Mask                     */
#define PCU_BCR_BCD12_Pos                     12                                                      /*!< PCU BCR: BCD12 Position                 */
#define PCU_BCR_BCD12_Msk                     (0x01UL << PCU_BCR_BCD12_Pos)                           /*!< PCU BCR: BCD12 Mask                     */
#define PCU_BCR_BCD13_Pos                     13                                                      /*!< PCU BCR: BCD13 Position                 */
#define PCU_BCR_BCD13_Msk                     (0x01UL << PCU_BCR_BCD13_Pos)                           /*!< PCU BCR: BCD13 Mask                     */
#define PCU_BCR_BCD14_Pos                     14                                                      /*!< PCU BCR: BCD14 Position                 */
#define PCU_BCR_BCD14_Msk                     (0x01UL << PCU_BCR_BCD14_Pos)                           /*!< PCU BCR: BCD14 Mask                     */
#define PCU_BCR_BCD15_Pos                     15                                                      /*!< PCU BCR: BCD15 Position                 */
#define PCU_BCR_BCD15_Msk                     (0x01UL << PCU_BCR_BCD15_Pos)                           /*!< PCU BCR: BCD15 Mask                     */


 





/* ================================================================================ */
/* ================         struct 'PORTEN' Position & Mask        ================ */
/* ================================================================================ */


/* --------------------------------  PORTEN_PORTEN  ------------------------------- */
#define PORTEN_PORTEN_Pos              0                                                       /*!< PORTEN PORTEN: PORTEN Position          */
#define PORTEN_PORTEN_Msk              (0x000000ffUL << PORTEN_PORTEN_Pos)              /*!< PORTEN PORTEN: PORTEN Mask              */
#define PORTEN_ENS_Pos                 8                                                       /*!< PORTEN PORTEN: ENS Position             */
#define PORTEN_ENS_Msk                 (0x01UL << PORTEN_ENS_Pos)                       /*!< PORTEN PORTEN: ENS Mask                 */


/* ================================================================================ */
/* ================          struct 'CFMC' Position & Mask         ================ */
/* ================================================================================ */


/* ----------------------------------  CFMC_CONF  --------------------------------- */
#define CFMC_CONF_LATENCY_Pos                 0                                                       /*!< CFMC CONF: LATENCY Position             */
#define CFMC_CONF_LATENCY_Msk                 (0x0fUL << CFMC_CONF_LATENCY_Pos)                       /*!< CFMC CONF: LATENCY Mask                 */
#define CFMC_CONF_ICEN_Pos                    8                                                       /*!< CFMC CONF: ICEN Position                */
#define CFMC_CONF_ICEN_Msk                    (0x01UL << CFMC_CONF_ICEN_Pos)                          /*!< CFMC CONF: ICEN Mask                    */
#define CFMC_CONF_ICRST_Pos                   16                                                      /*!< CFMC CONF: ICRST Position               */
#define CFMC_CONF_ICRST_Msk                   (0x01UL << CFMC_CONF_ICRST_Pos)                         /*!< CFMC CONF: ICRST Mask                   */
#define CFMC_CONF_BBLOCK_Pos                  24                                                      /*!< CFMC CONF: BBLOCK Position              */
#define CFMC_CONF_BBLOCK_Msk                  (0x01UL << CFMC_CONF_BBLOCK_Pos)                        /*!< CFMC CONF: BBLOCK Mask                  */
#define CFMC_CONF_WRITE_Pos                   25                                                      /*!< CFMC CONF: WRITE Position               */
#define CFMC_CONF_WRITE_Msk                   (0x01UL << CFMC_CONF_WRITE_Pos)                         /*!< CFMC CONF: WRITE Mask                   */

/* ---------------------------------  CFMC_FLSKEY  -------------------------------- */
#define CFMC_FLSKEY_FKEY_Pos                  0                                                       /*!< CFMC FLSKEY: FKEY Position              */
#define CFMC_FLSKEY_FKEY_Msk                  (0xffffffffUL << CFMC_FLSKEY_FKEY_Pos)                  /*!< CFMC FLSKEY: FKEY Mask                  */

/* ---------------------------------  CFMC_OTPKEY  -------------------------------- */
#define CFMC_OTPKEY_OKEY_Pos                  0                                                       /*!< CFMC OTPKEY: OKEY Position              */
#define CFMC_OTPKEY_OKEY_Msk                  (0xffffffffUL << CFMC_OTPKEY_OKEY_Pos)                  /*!< CFMC OTPKEY: OKEY Mask                  */

/* --------------------------------  CFMC_FLSPROT  -------------------------------- */
#define CFMC_FLSPROT_FPBY4K_0_Pos             0                                                       /*!< CFMC FLSPROT: FPBY4K_0 Position         */
#define CFMC_FLSPROT_FPBY4K_0_Msk             (0x01UL << CFMC_FLSPROT_FPBY4K_0_Pos)                   /*!< CFMC FLSPROT: FPBY4K_0 Mask             */
#define CFMC_FLSPROT_FPBY4K_1_Pos             1                                                       /*!< CFMC FLSPROT: FPBY4K_1 Position         */
#define CFMC_FLSPROT_FPBY4K_1_Msk             (0x01UL << CFMC_FLSPROT_FPBY4K_1_Pos)                   /*!< CFMC FLSPROT: FPBY4K_1 Mask             */
#define CFMC_FLSPROT_FPBY4K_2_Pos             2                                                       /*!< CFMC FLSPROT: FPBY4K_2 Position         */
#define CFMC_FLSPROT_FPBY4K_2_Msk             (0x01UL << CFMC_FLSPROT_FPBY4K_2_Pos)                   /*!< CFMC FLSPROT: FPBY4K_2 Mask             */
#define CFMC_FLSPROT_FPBY4K_3_Pos             3                                                       /*!< CFMC FLSPROT: FPBY4K_3 Position         */
#define CFMC_FLSPROT_FPBY4K_3_Msk             (0x01UL << CFMC_FLSPROT_FPBY4K_3_Pos)                   /*!< CFMC FLSPROT: FPBY4K_3 Mask             */
#define CFMC_FLSPROT_FPBY4K_4_Pos             4                                                       /*!< CFMC FLSPROT: FPBY4K_4 Position         */
#define CFMC_FLSPROT_FPBY4K_4_Msk             (0x01UL << CFMC_FLSPROT_FPBY4K_4_Pos)                   /*!< CFMC FLSPROT: FPBY4K_4 Mask             */
#define CFMC_FLSPROT_FPBY4K_5_Pos             5                                                       /*!< CFMC FLSPROT: FPBY4K_5 Position         */
#define CFMC_FLSPROT_FPBY4K_5_Msk             (0x01UL << CFMC_FLSPROT_FPBY4K_5_Pos)                   /*!< CFMC FLSPROT: FPBY4K_5 Mask             */
#define CFMC_FLSPROT_FPBY4K_6_Pos             6                                                       /*!< CFMC FLSPROT: FPBY4K_6 Position         */
#define CFMC_FLSPROT_FPBY4K_6_Msk             (0x01UL << CFMC_FLSPROT_FPBY4K_6_Pos)                   /*!< CFMC FLSPROT: FPBY4K_6 Mask             */
#define CFMC_FLSPROT_FPBY4K_7_Pos             7                                                       /*!< CFMC FLSPROT: FPBY4K_7 Position         */
#define CFMC_FLSPROT_FPBY4K_7_Msk             (0x01UL << CFMC_FLSPROT_FPBY4K_7_Pos)                   /*!< CFMC FLSPROT: FPBY4K_7 Mask             */
#define CFMC_FLSPROT_FPBY4K_8_Pos             8                                                       /*!< CFMC FLSPROT: FPBY4K_8 Position         */
#define CFMC_FLSPROT_FPBY4K_8_Msk             (0x01UL << CFMC_FLSPROT_FPBY4K_8_Pos)                   /*!< CFMC FLSPROT: FPBY4K_8 Mask             */
#define CFMC_FLSPROT_FPBY4K_9_Pos             9                                                       /*!< CFMC FLSPROT: FPBY4K_9 Position         */
#define CFMC_FLSPROT_FPBY4K_9_Msk             (0x01UL << CFMC_FLSPROT_FPBY4K_9_Pos)                   /*!< CFMC FLSPROT: FPBY4K_9 Mask             */
#define CFMC_FLSPROT_FPBY4K_10_Pos            10                                                      /*!< CFMC FLSPROT: FPBY4K_10 Position        */
#define CFMC_FLSPROT_FPBY4K_10_Msk            (0x01UL << CFMC_FLSPROT_FPBY4K_10_Pos)                  /*!< CFMC FLSPROT: FPBY4K_10 Mask            */
#define CFMC_FLSPROT_FPBY4K_11_Pos            11                                                      /*!< CFMC FLSPROT: FPBY4K_11 Position        */
#define CFMC_FLSPROT_FPBY4K_11_Msk            (0x01UL << CFMC_FLSPROT_FPBY4K_11_Pos)                  /*!< CFMC FLSPROT: FPBY4K_11 Mask            */
#define CFMC_FLSPROT_FPBY4K_12_Pos            12                                                      /*!< CFMC FLSPROT: FPBY4K_12 Position        */
#define CFMC_FLSPROT_FPBY4K_12_Msk            (0x01UL << CFMC_FLSPROT_FPBY4K_12_Pos)                  /*!< CFMC FLSPROT: FPBY4K_12 Mask            */
#define CFMC_FLSPROT_FPBY4K_13_Pos            13                                                      /*!< CFMC FLSPROT: FPBY4K_13 Position        */
#define CFMC_FLSPROT_FPBY4K_13_Msk            (0x01UL << CFMC_FLSPROT_FPBY4K_13_Pos)                  /*!< CFMC FLSPROT: FPBY4K_13 Mask            */
#define CFMC_FLSPROT_FPBY4K_14_Pos            14                                                      /*!< CFMC FLSPROT: FPBY4K_14 Position        */
#define CFMC_FLSPROT_FPBY4K_14_Msk            (0x01UL << CFMC_FLSPROT_FPBY4K_14_Pos)                  /*!< CFMC FLSPROT: FPBY4K_14 Mask            */
#define CFMC_FLSPROT_FPBY4K_15_Pos            15                                                      /*!< CFMC FLSPROT: FPBY4K_15 Position        */
#define CFMC_FLSPROT_FPBY4K_15_Msk            (0x01UL << CFMC_FLSPROT_FPBY4K_15_Pos)                  /*!< CFMC FLSPROT: FPBY4K_15 Mask            */
#define CFMC_FLSPROT_FUP512B_0_Pos            24                                                      /*!< CFMC FLSPROT: FUP512B_0 Position        */
#define CFMC_FLSPROT_FUP512B_0_Msk            (0x01UL << CFMC_FLSPROT_FUP512B_0_Pos)                  /*!< CFMC FLSPROT: FUP512B_0 Mask            */
#define CFMC_FLSPROT_FUP512B_1_Pos            25                                                      /*!< CFMC FLSPROT: FUP512B_1 Position        */
#define CFMC_FLSPROT_FUP512B_1_Msk            (0x01UL << CFMC_FLSPROT_FUP512B_1_Pos)                  /*!< CFMC FLSPROT: FUP512B_1 Mask            */
#define CFMC_FLSPROT_FUP512B_2_Pos            26                                                      /*!< CFMC FLSPROT: FUP512B_2 Position        */
#define CFMC_FLSPROT_FUP512B_2_Msk            (0x01UL << CFMC_FLSPROT_FUP512B_2_Pos)                  /*!< CFMC FLSPROT: FUP512B_2 Mask            */
#define CFMC_FLSPROT_FUP512B_3_Pos            27                                                      /*!< CFMC FLSPROT: FUP512B_3 Position        */
#define CFMC_FLSPROT_FUP512B_3_Msk            (0x01UL << CFMC_FLSPROT_FUP512B_3_Pos)                  /*!< CFMC FLSPROT: FUP512B_3 Mask            */
#define CFMC_FLSPROT_FUP512B_4_Pos            28                                                      /*!< CFMC FLSPROT: FUP512B_4 Position        */
#define CFMC_FLSPROT_FUP512B_4_Msk            (0x01UL << CFMC_FLSPROT_FUP512B_4_Pos)                  /*!< CFMC FLSPROT: FUP512B_4 Mask            */
#define CFMC_FLSPROT_FUP512B_5_Pos            29                                                      /*!< CFMC FLSPROT: FUP512B_5 Position        */
#define CFMC_FLSPROT_FUP512B_5_Msk            (0x01UL << CFMC_FLSPROT_FUP512B_5_Pos)                  /*!< CFMC FLSPROT: FUP512B_5 Mask            */
#define CFMC_FLSPROT_FUP512B_6_Pos            30                                                      /*!< CFMC FLSPROT: FUP512B_6 Position        */
#define CFMC_FLSPROT_FUP512B_6_Msk            (0x01UL << CFMC_FLSPROT_FUP512B_6_Pos)                  /*!< CFMC FLSPROT: FUP512B_6 Mask            */
#define CFMC_FLSPROT_FUP512B_7_Pos            31                                                      /*!< CFMC FLSPROT: FUP512B_7 Position        */
#define CFMC_FLSPROT_FUP512B_7_Msk            (0x01UL << CFMC_FLSPROT_FUP512B_7_Pos)                  /*!< CFMC FLSPROT: FUP512B_7 Mask            */

/* --------------------------------  CFMC_OTPPROT  -------------------------------- */
#define CFMC_OTPPROT_OTP0_Pos                 0                                                       /*!< CFMC OTPPROT: OTP0 Position             */
#define CFMC_OTPPROT_OTP0_Msk                 (0x01UL << CFMC_OTPPROT_OTP0_Pos)                       /*!< CFMC OTPPROT: OTP0 Mask                 */
#define CFMC_OTPPROT_OTP1_Pos                 1                                                       /*!< CFMC OTPPROT: OTP1 Position             */
#define CFMC_OTPPROT_OTP1_Msk                 (0x01UL << CFMC_OTPPROT_OTP1_Pos)                       /*!< CFMC OTPPROT: OTP1 Mask                 */
#define CFMC_OTPPROT_OTP2_Pos                 2                                                       /*!< CFMC OTPPROT: OTP2 Position             */
#define CFMC_OTPPROT_OTP2_Msk                 (0x01UL << CFMC_OTPPROT_OTP2_Pos)                       /*!< CFMC OTPPROT: OTP2 Mask                 */
#define CFMC_OTPPROT_OTP3_Pos                 3                                                       /*!< CFMC OTPPROT: OTP3 Position             */
#define CFMC_OTPPROT_OTP3_Msk                 (0x01UL << CFMC_OTPPROT_OTP3_Pos)                       /*!< CFMC OTPPROT: OTP3 Mask                 */

/* ----------------------------------  CFMC_CTRL  --------------------------------- */
#define CFMC_CTRL_PGM_Pos                     0                                                       /*!< CFMC CTRL: PGM Position                 */
#define CFMC_CTRL_PGM_Msk                     (0x01UL << CFMC_CTRL_PGM_Pos)                           /*!< CFMC CTRL: PGM Mask                     */
#define CFMC_CTRL_PERS_Pos                    1                                                       /*!< CFMC CTRL: PERS Position                */
#define CFMC_CTRL_PERS_Msk                    (0x01UL << CFMC_CTRL_PERS_Pos)                          /*!< CFMC CTRL: PERS Mask                    */
#define CFMC_CTRL_SERS_Pos                    2                                                       /*!< CFMC CTRL: SERS Position                */
#define CFMC_CTRL_SERS_Msk                    (0x01UL << CFMC_CTRL_SERS_Pos)                          /*!< CFMC CTRL: SERS Mask                    */
#define CFMC_CTRL_CERS_Pos                    3                                                       /*!< CFMC CTRL: CERS Position                */
#define CFMC_CTRL_CERS_Msk                    (0x01UL << CFMC_CTRL_CERS_Pos)                          /*!< CFMC CTRL: CERS Mask                    */
#define CFMC_CTRL_WABOART_Pos                 7                                                       /*!< CFMC CTRL: WABOART Position             */
#define CFMC_CTRL_WABOART_Msk                 (0x01UL << CFMC_CTRL_WABOART_Pos)                       /*!< CFMC CTRL: WABOART Mask                 */
#define CFMC_CTRL_WDIEN_Pos                   8                                                       /*!< CFMC CTRL: WDIEN Position               */
#define CFMC_CTRL_WDIEN_Msk                   (0x01UL << CFMC_CTRL_WDIEN_Pos)                         /*!< CFMC CTRL: WDIEN Mask                   */
#define CFMC_CTRL_OTPLOCK_Pos                 30                                                      /*!< CFMC CTRL: OTPLOCK Position             */
#define CFMC_CTRL_OTPLOCK_Msk                 (0x01UL << CFMC_CTRL_OTPLOCK_Pos)                       /*!< CFMC CTRL: OTPLOCK Mask                 */
#define CFMC_CTRL_FLOCK_Pos                   31                                                      /*!< CFMC CTRL: FLOCK Position               */
#define CFMC_CTRL_FLOCK_Msk                   (0x01UL << CFMC_CTRL_FLOCK_Pos)                         /*!< CFMC CTRL: FLOCK Mask                   */

/* ----------------------------------  CFMC_STAT  --------------------------------- */
#define CFMC_STAT_WBUSY_Pos                   0                                                       /*!< CFMC STAT: WBUSY Position               */
#define CFMC_STAT_WBUSY_Msk                   (0x01UL << CFMC_STAT_WBUSY_Pos)                         /*!< CFMC STAT: WBUSY Mask                   */
#define CFMC_STAT_CBUSY_Pos                   1                                                       /*!< CFMC STAT: CBUSY Position               */
#define CFMC_STAT_CBUSY_Msk                   (0x01UL << CFMC_STAT_CBUSY_Pos)                         /*!< CFMC STAT: CBUSY Mask                   */
#define CFMC_STAT_WDONE_Pos                   8                                                       /*!< CFMC STAT: WDONE Position               */
#define CFMC_STAT_WDONE_Msk                   (0x01UL << CFMC_STAT_WDONE_Pos)                         /*!< CFMC STAT: WDONE Mask                   */
#define CFMC_STAT_CDONE_Pos                   9                                                       /*!< CFMC STAT: CDONE Position               */
#define CFMC_STAT_CDONE_Msk                   (0x01UL << CFMC_STAT_CDONE_Pos)                         /*!< CFMC STAT: CDONE Mask                   */
#define CFMC_STAT_FLERR_Pos                   16                                                      /*!< CFMC STAT: FLERR Position               */
#define CFMC_STAT_FLERR_Msk                   (0x01UL << CFMC_STAT_FLERR_Pos)                         /*!< CFMC STAT: FLERR Mask                   */
#define CFMC_STAT_OLERR_Pos                   17                                                      /*!< CFMC STAT: OLERR Position               */
#define CFMC_STAT_OLERR_Msk                   (0x01UL << CFMC_STAT_OLERR_Pos)                         /*!< CFMC STAT: OLERR Mask                   */
#define CFMC_STAT_FPERR_Pos                   18                                                      /*!< CFMC STAT: FPERR Position               */
#define CFMC_STAT_FPERR_Msk                   (0x01UL << CFMC_STAT_FPERR_Pos)                         /*!< CFMC STAT: FPERR Mask                   */
#define CFMC_STAT_OPERR_Pos                   19                                                      /*!< CFMC STAT: OPERR Position               */
#define CFMC_STAT_OPERR_Msk                   (0x01UL << CFMC_STAT_OPERR_Pos)                         /*!< CFMC STAT: OPERR Mask                   */
#define CFMC_STAT_WSERR_Pos                   20                                                      /*!< CFMC STAT: WSERR Position               */
#define CFMC_STAT_WSERR_Msk                   (0x01UL << CFMC_STAT_WSERR_Pos)                         /*!< CFMC STAT: WSERR Mask                   */
#define CFMC_STAT_RPERR_Pos                   21                                                      /*!< CFMC STAT: RPERR Position               */
#define CFMC_STAT_RPERR_Msk                   (0x01UL << CFMC_STAT_RPERR_Pos)                         /*!< CFMC STAT: RPERR Mask                   */
#define CFMC_STAT_WTERR_Pos                   22                                                      /*!< CFMC STAT: WTERR Position               */
#define CFMC_STAT_WTERR_Msk                   (0x01UL << CFMC_STAT_WTERR_Pos)                         /*!< CFMC STAT: WTERR Mask                   */

/* --------------------------------  CFMC_READPROT  ------------------------------- */
#define CFMC_READPROT_RPROT_Pos               0                                                       /*!< CFMC READPROT: RPROT Position           */
#define CFMC_READPROT_RPROT_Msk               (0x000000ffUL << CFMC_READPROT_RPROT_Pos)               /*!< CFMC READPROT: RPROT Mask               */
#define CFMC_READPROT_LVL1_EN_Pos             8                                                       /*!< CFMC READPROT: LVL1_EN Position         */
#define CFMC_READPROT_LVL1_EN_Msk             (0x01UL << CFMC_READPROT_LVL1_EN_Pos)                   /*!< CFMC READPROT: LVL1_EN Mask             */
#define CFMC_READPROT_LVL2_EN_Pos             9                                                       /*!< CFMC READPROT: LVL2_EN Position         */
#define CFMC_READPROT_LVL2_EN_Msk             (0x01UL << CFMC_READPROT_LVL2_EN_Pos)                   /*!< CFMC READPROT: LVL2_EN Mask             */
#define CFMC_READPROT_LVL1_STS_Pos            16                                                      /*!< CFMC READPROT: LVL1_STS Position        */
#define CFMC_READPROT_LVL1_STS_Msk            (0x01UL << CFMC_READPROT_LVL1_STS_Pos)                  /*!< CFMC READPROT: LVL1_STS Mask            */
#define CFMC_READPROT_LVL2_STS_Pos            17                                                      /*!< CFMC READPROT: LVL2_STS Position        */
#define CFMC_READPROT_LVL2_STS_Msk            (0x01UL << CFMC_READPROT_LVL2_STS_Pos)                  /*!< CFMC READPROT: LVL2_STS Mask            */
#define CFMC_READPROT_CERSD_Pos               24                                                      /*!< CFMC READPROT: CERSD Position           */
#define CFMC_READPROT_CERSD_Msk               (0x01UL << CFMC_READPROT_CERSD_Pos)                     /*!< CFMC READPROT: CERSD Mask               */
#define CFMC_READPROT_OTP0ERSD_Pos            25                                                      /*!< CFMC READPROT: OTP0ERSD Position        */
#define CFMC_READPROT_OTP0ERSD_Msk            (0x01UL << CFMC_READPROT_OTP0ERSD_Pos)                  /*!< CFMC READPROT: OTP0ERSD Mask            */
#define CFMC_READPROT_PWMATCH_Pos             26                                                      /*!< CFMC READPROT: PWMATCH Position         */
#define CFMC_READPROT_PWMATCH_Msk             (0x01UL << CFMC_READPROT_PWMATCH_Pos)                   /*!< CFMC READPROT: PWMATCH Mask             */
#define CFMC_READPROT_SRBOOT_Pos              30                                                      /*!< CFMC READPROT: SRBOOT Position          */
#define CFMC_READPROT_SRBOOT_Msk              (0x01UL << CFMC_READPROT_SRBOOT_Pos)                    /*!< CFMC READPROT: SRBOOT Mask              */
#define CFMC_READPROT_DBGMOD_Pos              31                                                      /*!< CFMC READPROT: DBGMOD Position          */
#define CFMC_READPROT_DBGMOD_Msk              (0x01UL << CFMC_READPROT_DBGMOD_Pos)                    /*!< CFMC READPROT: DBGMOD Mask              */

/* ----------------------------------  CFMC_PWIN  --------------------------------- */
#define CFMC_PWIN_PWIN_Pos                    0                                                       /*!< CFMC PWIN: PWIN Position                */
#define CFMC_PWIN_PWIN_Msk                    (0xffffffffUL << CFMC_PWIN_PWIN_Pos)                    /*!< CFMC PWIN: PWIN Mask                    */

/* --------------------------------  CFMC_CHKCTRL  -------------------------------- */
#define CFMC_CHKCTRL_BGEN_Pos                 0                                                       /*!< CFMC CHKCTRL: BGEN Position             */
#define CFMC_CHKCTRL_BGEN_Msk                 (0x01UL << CFMC_CHKCTRL_BGEN_Pos)                       /*!< CFMC CHKCTRL: BGEN Mask                 */
#define CFMC_CHKCTRL_BSTEN_Pos                1                                                       /*!< CFMC CHKCTRL: BSTEN Position            */
#define CFMC_CHKCTRL_BSTEN_Msk                (0x01UL << CFMC_CHKCTRL_BSTEN_Pos)                      /*!< CFMC CHKCTRL: BSTEN Mask                */
#define CFMC_CHKCTRL_CDIEN_Pos                8                                                       /*!< CFMC CHKCTRL: CDIEN Position            */
#define CFMC_CHKCTRL_CDIEN_Msk                (0x01UL << CFMC_CHKCTRL_CDIEN_Pos)                      /*!< CFMC CHKCTRL: CDIEN Mask                */
#define CFMC_CHKCTRL_CDRST_Pos                16                                                      /*!< CFMC CHKCTRL: CDRST Position            */
#define CFMC_CHKCTRL_CDRST_Msk                (0x01UL << CFMC_CHKCTRL_CDRST_Pos)                      /*!< CFMC CHKCTRL: CDRST Mask                */

/* --------------------------------  CFMC_CHKDOUT  -------------------------------- */
#define CFMC_CHKDOUT_CDOUT_Pos                0                                                       /*!< CFMC CHKDOUT: CDOUT Position            */
#define CFMC_CHKDOUT_CDOUT_Msk                (0x0000ffffUL << CFMC_CHKDOUT_CDOUT_Pos)                /*!< CFMC CHKDOUT: CDOUT Mask                */

/* --------------------------------  CFMC_CHKSADDR  ------------------------------- */
#define CFMC_CHKSADDR_FIXED_VALUE_Pos         0                                                       /*!< CFMC CHKSADDR: FIXED_VALUE Position     */
#define CFMC_CHKSADDR_FIXED_VALUE_Msk         (0x7fUL << CFMC_CHKSADDR_FIXED_VALUE_Pos)               /*!< CFMC CHKSADDR: FIXED_VALUE Mask         */
#define CFMC_CHKSADDR_SADDR_Pos               7                                                       /*!< CFMC CHKSADDR: SADDR Position           */
#define CFMC_CHKSADDR_SADDR_Msk               (0x01ffffffUL << CFMC_CHKSADDR_SADDR_Pos)               /*!< CFMC CHKSADDR: SADDR Mask               */

/* --------------------------------  CFMC_CHKEADDR  ------------------------------- */
#define CFMC_CHKEADDR_FIXED_VALUE_Pos         0                                                       /*!< CFMC CHKEADDR: FIXED_VALUE Position     */
#define CFMC_CHKEADDR_FIXED_VALUE_Msk         (0x7fUL << CFMC_CHKEADDR_FIXED_VALUE_Pos)               /*!< CFMC CHKEADDR: FIXED_VALUE Mask         */
#define CFMC_CHKEADDR_EADDR_Pos               7                                                       /*!< CFMC CHKEADDR: EADDR Position           */
#define CFMC_CHKEADDR_EADDR_Msk               (0x01ffffffUL << CFMC_CHKEADDR_EADDR_Pos)               /*!< CFMC CHKEADDR: EADDR Mask               */

/* --------------------------------  CFMC_WTIMEOUT  ------------------------------- */
#define CFMC_WTIMEOUT_WTIMEOUT_Pos            0                                                       /*!< CFMC WTIMEOUT: WTIMEOUT Position        */
#define CFMC_WTIMEOUT_WTIMEOUT_Msk            (0x000000ffUL << CFMC_WTIMEOUT_WTIMEOUT_Pos)            /*!< CFMC WTIMEOUT: WTIMEOUT Mask            */

/* ---------------------------------  CFMC_PWPRST  -------------------------------- */
#define CFMC_PWPRST_PWPRST_Pos                0                                                       /*!< CFMC PWPRST: PWPRST Position            */
#define CFMC_PWPRST_PWPRST_Msk                (0xffffffffUL << CFMC_PWPRST_PWPRST_Pos)                /*!< CFMC PWPRST: PWPRST Mask                */


/* ================================================================================ */
/* ================          struct 'SRAM' Position & Mask         ================ */
/* ================================================================================ */


/* ----------------------------------  SRAM_CONF  --------------------------------- */
#define SRAM_CONF_WALK0S_Pos                  0                                                       /*!< SRAM CONF: WALK0S Position              */
#define SRAM_CONF_WALK0S_Msk                  (0x01UL << SRAM_CONF_WALK0S_Pos)                        /*!< SRAM CONF: WALK0S Mask                  */
#define SRAM_CONF_WALK1S_Pos                  1                                                       /*!< SRAM CONF: WALK1S Position              */
#define SRAM_CONF_WALK1S_Msk                  (0x01UL << SRAM_CONF_WALK1S_Pos)                        /*!< SRAM CONF: WALK1S Mask                  */

/* ----------------------------------  SRAM_CTRL  --------------------------------- */
#define SRAM_CTRL_START_Pos                   0                                                       /*!< SRAM CTRL: START Position               */
#define SRAM_CTRL_START_Msk                   (0x01UL << SRAM_CTRL_START_Pos)                         /*!< SRAM CTRL: START Mask                   */
#define SRAM_CTRL_ABORT_Pos                   1                                                       /*!< SRAM CTRL: ABORT Position               */
#define SRAM_CTRL_ABORT_Msk                   (0x01UL << SRAM_CTRL_ABORT_Pos)                         /*!< SRAM CTRL: ABORT Mask                   */
#define SRAM_CTRL_INTEN_Pos                   8                                                       /*!< SRAM CTRL: INTEN Position               */
#define SRAM_CTRL_INTEN_Msk                   (0x01UL << SRAM_CTRL_INTEN_Pos)                         /*!< SRAM CTRL: INTEN Mask                   */

/* ----------------------------------  SRAM_STAT  --------------------------------- */
#define SRAM_STAT_BUSY_Pos                    0                                                       /*!< SRAM STAT: BUSY Position                */
#define SRAM_STAT_BUSY_Msk                    (0x01UL << SRAM_STAT_BUSY_Pos)                          /*!< SRAM STAT: BUSY Mask                    */
#define SRAM_STAT_DONE_Pos                    8                                                       /*!< SRAM STAT: DONE Position                */
#define SRAM_STAT_DONE_Msk                    (0x01UL << SRAM_STAT_DONE_Pos)                          /*!< SRAM STAT: DONE Mask                    */
#define SRAM_STAT_PASS_Pos                    16                                                      /*!< SRAM STAT: PASS Position                */
#define SRAM_STAT_PASS_Msk                    (0x01UL << SRAM_STAT_PASS_Pos)                          /*!< SRAM STAT: PASS Mask                    */
#define SRAM_STAT_FAIL_Pos                    17                                                      /*!< SRAM STAT: FAIL Position                */
#define SRAM_STAT_FAIL_Msk                    (0x01UL << SRAM_STAT_FAIL_Pos)                          /*!< SRAM STAT: FAIL Mask                    */
#define SRAM_STAT_ABORT_Pos                   18                                                      /*!< SRAM STAT: ABORT Position               */
#define SRAM_STAT_ABORT_Msk                   (0x01UL << SRAM_STAT_ABORT_Pos)                         /*!< SRAM STAT: ABORT Mask                   */
#define SRAM_STAT_ERROR_Pos                   19                                                      /*!< SRAM STAT: ERROR Position               */
#define SRAM_STAT_ERROR_Msk                   (0x01UL << SRAM_STAT_ERROR_Pos)                         /*!< SRAM STAT: ERROR Mask                   */

/* --------------------------------  SRAM_FTFADDR  -------------------------------- */
#define SRAM_FTFADDR_FTFADDR_Pos              0                                                       /*!< SRAM FTFADDR: FTFADDR Position          */
#define SRAM_FTFADDR_FTFADDR_Msk              (0x00001fffUL << SRAM_FTFADDR_FTFADDR_Pos)              /*!< SRAM FTFADDR: FTFADDR Mask              */

/* --------------------------------  SRAM_FTFBITR  -------------------------------- */
#define SRAM_FTFBITR_FTFBIT_Pos               0                                                       /*!< SRAM FTFBITR: FTFBIT Position           */
#define SRAM_FTFBITR_FTFBIT_Msk               (0xffffffffUL << SRAM_FTFBITR_FTFBIT_Pos)               /*!< SRAM FTFBITR: FTFBIT Mask               */

/* --------------------------------  SRAM_FTFPADDR  ------------------------------- */
#define SRAM_FTFPADDR_FTFPADDR_Pos            0                                                       /*!< SRAM FTFPADDR: FTFPADDR Position        */
#define SRAM_FTFPADDR_FTFPADDR_Msk            (0x00001fffUL << SRAM_FTFPADDR_FTFPADDR_Pos)            /*!< SRAM FTFPADDR: FTFPADDR Mask            */

/* --------------------------------  SRAM_TESTCTRL  ------------------------------- */
#define SRAM_TESTCTRL_ALL0_PTN_Pos            0                                                       /*!< SRAM TESTCTRL: ALL0_PTN Position        */
#define SRAM_TESTCTRL_ALL0_PTN_Msk            (0x01UL << SRAM_TESTCTRL_ALL0_PTN_Pos)                  /*!< SRAM TESTCTRL: ALL0_PTN Mask            */
#define SRAM_TESTCTRL_ALL1_PTN_Pos            1                                                       /*!< SRAM TESTCTRL: ALL1_PTN Position        */
#define SRAM_TESTCTRL_ALL1_PTN_Msk            (0x01UL << SRAM_TESTCTRL_ALL1_PTN_Pos)                  /*!< SRAM TESTCTRL: ALL1_PTN Mask            */
#define SRAM_TESTCTRL_CHK_BD_PTN_Pos          2                                                       /*!< SRAM TESTCTRL: CHK_BD_PTN Position      */
#define SRAM_TESTCTRL_CHK_BD_PTN_Msk          (0x01UL << SRAM_TESTCTRL_CHK_BD_PTN_Pos)                /*!< SRAM TESTCTRL: CHK_BD_PTN Mask          */
#define SRAM_TESTCTRL_INV_CHK_PTN_Pos         3                                                       /*!< SRAM TESTCTRL: INV_CHK_PTN Position     */
#define SRAM_TESTCTRL_INV_CHK_PTN_Msk         (0x01UL << SRAM_TESTCTRL_INV_CHK_PTN_Pos)               /*!< SRAM TESTCTRL: INV_CHK_PTN Mask         */


/* ================================================================================ */
/* ================           Group 'DMA' Position & Mask          ================ */
/* ================================================================================ */


/* -----------------------------------  DMA_CR  ----------------------------------- */
#define DMA_CR_DIR_Pos                        1                                                       /*!< DMA CR: DIR Position                    */
#define DMA_CR_DIR_Msk                        (0x01UL << DMA_CR_DIR_Pos)                              /*!< DMA CR: DIR Mask                        */
#define DMA_CR_SIZE_Pos                       2                                                       /*!< DMA CR: SIZE Position                   */
#define DMA_CR_SIZE_Msk                       (0x03UL << DMA_CR_SIZE_Pos)                             /*!< DMA CR: SIZE Mask                       */
#define DMA_CR_PERISEL_Pos                    8                                                       /*!< DMA CR: PERISEL Position                */
#define DMA_CR_PERISEL_Msk                    (0x0fUL << DMA_CR_PERISEL_Pos)                          /*!< DMA CR: PERISEL Mask                    */
#define DMA_CR_TRANSCNT_Pos                   16                                                      /*!< DMA CR: TRANSCNT Position               */
#define DMA_CR_TRANSCNT_Msk                   (0x00000fffUL << DMA_CR_TRANSCNT_Pos)                   /*!< DMA CR: TRANSCNT Mask                   */

/* -----------------------------------  DMA_SR  ----------------------------------- */
#define DMA_SR_DMAEN_Pos                      0                                                       /*!< DMA SR: DMAEN Position                  */
#define DMA_SR_DMAEN_Msk                      (0x01UL << DMA_SR_DMAEN_Pos)                            /*!< DMA SR: DMAEN Mask                      */
#define DMA_SR_DMARC_Pos                      4                                                       /*!< DMA SR: DMARC Position                  */
#define DMA_SR_DMARC_Msk                      (0x01UL << DMA_SR_DMARC_Pos)                            /*!< DMA SR: DMARC Mask                      */
#define DMA_SR_EOT_Pos                        7                                                       /*!< DMA SR: EOT Position                    */
#define DMA_SR_EOT_Msk                        (0x01UL << DMA_SR_EOT_Pos)                              /*!< DMA SR: EOT Mask                        */

/* -----------------------------------  DMA_PAR  ---------------------------------- */
#define DMA_PAR_PAR_Pos                       0                                                       /*!< DMA PAR: PAR Position                   */
#define DMA_PAR_PAR_Msk                       (0x0000ffffUL << DMA_PAR_PAR_Pos)                       /*!< DMA PAR: PAR Mask                       */
#define DMA_PAR_PARBASEOFFSET_Pos             16                                                      /*!< DMA PAR: PARBASEOFFSET Position         */
#define DMA_PAR_PARBASEOFFSET_Msk             (0x0000ffffUL << DMA_PAR_PARBASEOFFSET_Pos)             /*!< DMA PAR: PARBASEOFFSET Mask             */

/* -----------------------------------  DMA_MAR  ---------------------------------- */
#define DMA_MAR_MAR_Pos                       0                                                       /*!< DMA MAR: MAR Position                   */
#define DMA_MAR_MAR_Msk                       (0x0000ffffUL << DMA_MAR_MAR_Pos)                       /*!< DMA MAR: MAR Mask                       */
#define DMA_MAR_MEMBASEADDRESS_Pos            16                                                      /*!< DMA MAR: MEMBASEADDRESS Position        */
#define DMA_MAR_MEMBASEADDRESS_Msk            (0x0000ffffUL << DMA_MAR_MEMBASEADDRESS_Pos)            /*!< DMA MAR: MEMBASEADDRESS Mask            */



/* ================================================================================ */
/* ================          struct 'WDT' Position & Mask          ================ */
/* ================================================================================ */


/* -----------------------------------  WDT_LR  ----------------------------------- */
#define WDT_LR_LR_Pos                         0                                                       /*!< WDT LR: LR Position                     */
#define WDT_LR_LR_Msk                         (0xffffffffUL << WDT_LR_LR_Pos)                         /*!< WDT LR: LR Mask                         */

/* -----------------------------------  WDT_CNT  ---------------------------------- */
#define WDT_CNT_CNT_Pos                       0                                                       /*!< WDT CNT: CNT Position                   */
#define WDT_CNT_CNT_Msk                       (0xffffffffUL << WDT_CNT_CNT_Pos)                       /*!< WDT CNT: CNT Mask                       */

/* -----------------------------------  WDT_CON  ---------------------------------- */
#define WDT_CON_WPRS_Pos                      0                                                       /*!< WDT CON: WPRS Position                  */
#define WDT_CON_WPRS_Msk                      (0x07UL << WDT_CON_WPRS_Pos)                            /*!< WDT CON: WPRS Mask                      */
#define WDT_CON_CKSEL_Pos                     3                                                       /*!< WDT CON: CKSEL Position                 */
#define WDT_CON_CKSEL_Msk                     (0x01UL << WDT_CON_CKSEL_Pos)                           /*!< WDT CON: CKSEL Mask                     */
#define WDT_CON_WDTEN_Pos                     4                                                       /*!< WDT CON: WDTEN Position                 */
#define WDT_CON_WDTEN_Msk                     (0x01UL << WDT_CON_WDTEN_Pos)                           /*!< WDT CON: WDTEN Mask                     */
#define WDT_CON_WDTRE_Pos                     6                                                       /*!< WDT CON: WDTRE Position                 */
#define WDT_CON_WDTRE_Msk                     (0x01UL << WDT_CON_WDTRE_Pos)                           /*!< WDT CON: WDTRE Mask                     */
#define WDT_CON_WDTIE_Pos                     7                                                       /*!< WDT CON: WDTIE Position                 */
#define WDT_CON_WDTIE_Msk                     (0x01UL << WDT_CON_WDTIE_Pos)                           /*!< WDT CON: WDTIE Mask                     */
#define WDT_CON_WUF_Pos                       8                                                       /*!< WDT CON: WUF Position                   */
#define WDT_CON_WUF_Msk                       (0x01UL << WDT_CON_WUF_Pos)                             /*!< WDT CON: WUF Mask                       */
#define WDT_CON_WDBG_Pos                      15                                                      /*!< WDT CON: WDBG Position                  */
#define WDT_CON_WDBG_Msk                      (0x01UL << WDT_CON_WDBG_Pos)                            /*!< WDT CON: WDBG Mask                      */

/* -----------------------------------  WDT_AEN  ---------------------------------- */
#define WDT_AEN_AEN_Pos                       0                                                       /*!< WDT AEN: AEN Position                   */
#define WDT_AEN_AEN_Msk                       (0x0000ffffUL << WDT_AEN_AEN_Pos)                       /*!< WDT AEN: AEN Mask                       */
#define WDT_AEN_ENS_Pos                       16                                                      /*!< WDT AEN: ENS Position                   */
#define WDT_AEN_ENS_Msk                       (0x01UL << WDT_AEN_ENS_Pos)                             /*!< WDT AEN: ENS Mask                       */


/* ================================================================================ */
/* ================          Group 'TIMER' Position & Mask         ================ */
/* ================================================================================ */


/* ----------------------------------  TIMER_CR1  --------------------------------- */
#define TIMER_CR1_MODE_Pos                    0                                                       /*!< TIMER CR1: MODE Position                */
#define TIMER_CR1_MODE_Msk                    (0x03UL << TIMER_CR1_MODE_Pos)                          /*!< TIMER CR1: MODE Mask                    */
#define TIMER_CR1_CLRMOD_Pos                  2                                                       /*!< TIMER CR1: CLRMOD Position              */
#define TIMER_CR1_CLRMOD_Msk                  (0x03UL << TIMER_CR1_CLRMOD_Pos)                        /*!< TIMER CR1: CLRMOD Mask                  */
#define TIMER_CR1_CKSEL_Pos                   4                                                       /*!< TIMER CR1: CKSEL Position               */
#define TIMER_CR1_CKSEL_Msk                   (0x07UL << TIMER_CR1_CKSEL_Pos)                         /*!< TIMER CR1: CKSEL Mask                   */
#define TIMER_CR1_STARTLVL_Pos                7                                                       /*!< TIMER CR1: STARTLVL Position            */
#define TIMER_CR1_STARTLVL_Msk                (0x01UL << TIMER_CR1_STARTLVL_Pos)                      /*!< TIMER CR1: STARTLVL Mask                */
#define TIMER_CR1_ADCTRGEN_Pos                8                                                       /*!< TIMER CR1: ADCTRGEN Position            */
#define TIMER_CR1_ADCTRGEN_Msk                (0x01UL << TIMER_CR1_ADCTRGEN_Pos)                      /*!< TIMER CR1: ADCTRGEN Mask                */
#define TIMER_CR1_IOSEL_Pos                   11                                                      /*!< TIMER CR1: IOSEL Position               */
#define TIMER_CR1_IOSEL_Msk                   (0x01UL << TIMER_CR1_IOSEL_Pos)                         /*!< TIMER CR1: IOSEL Mask                   */
#define TIMER_CR1_OUTPOL_Pos                  12                                                      /*!< TIMER CR1: OUTPOL Position              */
#define TIMER_CR1_OUTPOL_Msk                  (0x01UL << TIMER_CR1_OUTPOL_Pos)                        /*!< TIMER CR1: OUTPOL Mask                  */
#define TIMER_CR1_UAO_Pos                     13                                                      /*!< TIMER CR1: UAO Position                 */
#define TIMER_CR1_UAO_Msk                     (0x01UL << TIMER_CR1_UAO_Pos)                           /*!< TIMER CR1: UAO Mask                     */
#define TIMER_CR1_TRGMOD_Pos                  14                                                      /*!< TIMER CR1: TRGMOD Position              */
#define TIMER_CR1_TRGMOD_Msk                  (0x03UL << TIMER_CR1_TRGMOD_Pos)                        /*!< TIMER CR1: TRGMOD Mask                  */

/* ----------------------------------  TIMER_CR2  --------------------------------- */
#define TIMER_CR2_TEN_Pos                     0                                                       /*!< TIMER CR2: TEN Position                 */
#define TIMER_CR2_TEN_Msk                     (0x01UL << TIMER_CR2_TEN_Pos)                           /*!< TIMER CR2: TEN Mask                     */
#define TIMER_CR2_TCLR_Pos                    1                                                       /*!< TIMER CR2: TCLR Position                */
#define TIMER_CR2_TCLR_Msk                    (0x01UL << TIMER_CR2_TCLR_Pos)                          /*!< TIMER CR2: TCLR Mask                    */

/* ----------------------------------  TIMER_PRS  --------------------------------- */
#define TIMER_PRS_PRS_Pos                     0                                                       /*!< TIMER PRS: PRS Position                 */
#define TIMER_PRS_PRS_Msk                     (0x000003ffUL << TIMER_PRS_PRS_Pos)                     /*!< TIMER PRS: PRS Mask                     */

/* ----------------------------------  TIMER_GRA  --------------------------------- */
#define TIMER_GRA_GRA_Pos                     0                                                       /*!< TIMER GRA: GRA Position                 */
#define TIMER_GRA_GRA_Msk                     (0x0000ffffUL << TIMER_GRA_GRA_Pos)                     /*!< TIMER GRA: GRA Mask                     */

/* ----------------------------------  TIMER_GRB  --------------------------------- */
#define TIMER_GRB_GRB_Pos                     0                                                       /*!< TIMER GRB: GRB Position                 */
#define TIMER_GRB_GRB_Msk                     (0x0000ffffUL << TIMER_GRB_GRB_Pos)                     /*!< TIMER GRB: GRB Mask                     */

/* ----------------------------------  TIMER_CNT  --------------------------------- */
#define TIMER_CNT_CNT_Pos                     0                                                       /*!< TIMER CNT: CNT Position                 */
#define TIMER_CNT_CNT_Msk                     (0x0000ffffUL << TIMER_CNT_CNT_Pos)                     /*!< TIMER CNT: CNT Mask                     */

/* ----------------------------------  TIMER_SR  ---------------------------------- */
#define TIMER_SR_OVF_Pos                      0                                                       /*!< TIMER SR: OVF Position                  */
#define TIMER_SR_OVF_Msk                      (0x01UL << TIMER_SR_OVF_Pos)                            /*!< TIMER SR: OVF Mask                      */
#define TIMER_SR_MFB_Pos                      1                                                       /*!< TIMER SR: MFB Position                  */
#define TIMER_SR_MFB_Msk                      (0x01UL << TIMER_SR_MFB_Pos)                            /*!< TIMER SR: MFB Mask                      */
#define TIMER_SR_MFA_Pos                      2                                                       /*!< TIMER SR: MFA Position                  */
#define TIMER_SR_MFA_Msk                      (0x01UL << TIMER_SR_MFA_Pos)                            /*!< TIMER SR: MFA Mask                      */

/* ----------------------------------  TIMER_IER  --------------------------------- */
#define TIMER_IER_OVIE_Pos                    0                                                       /*!< TIMER IER: OVIE Position                */
#define TIMER_IER_OVIE_Msk                    (0x01UL << TIMER_IER_OVIE_Pos)                          /*!< TIMER IER: OVIE Mask                    */
#define TIMER_IER_MBIE_Pos                    1                                                       /*!< TIMER IER: MBIE Position                */
#define TIMER_IER_MBIE_Msk                    (0x01UL << TIMER_IER_MBIE_Pos)                          /*!< TIMER IER: MBIE Mask                    */
#define TIMER_IER_MAIE_Pos                    2                                                       /*!< TIMER IER: MAIE Position                */
#define TIMER_IER_MAIE_Msk                    (0x01UL << TIMER_IER_MAIE_Pos)                          /*!< TIMER IER: MAIE Mask                    */

/* --------------------------------  TIMER_TRGPNT  -------------------------------- */
#define TIMER_TRGPNT_TRGPNT_Pos               0                                                       /*!< TIMER TRGPNT: TRGPNT Position           */
#define TIMER_TRGPNT_TRGPNT_Msk               (0x0000ffffUL << TIMER_TRGPNT_TRGPNT_Pos)               /*!< TIMER TRGPNT: TRGPNT Mask               */

/* ---------------------------------  TIMER_SYNC  --------------------------------- */
#define TIMER_SYNC_SYNCDLY_Pos                0                                                       /*!< TIMER SYNC: SYNCDLY Position            */
#define TIMER_SYNC_SYNCDLY_Msk                (0x0000ffffUL << TIMER_SYNC_SYNCDLY_Pos)                /*!< TIMER SYNC: SYNCDLY Mask                */
#define TIMER_SYNC_CSYNC_Pos                  16                                                      /*!< TIMER SYNC: CSYNC Position              */
#define TIMER_SYNC_CSYNC_Msk                  (0x01UL << TIMER_SYNC_CSYNC_Pos)                        /*!< TIMER SYNC: CSYNC Mask                  */
#define TIMER_SYNC_SSYNC_Pos                  17                                                      /*!< TIMER SYNC: SSYNC Position              */
#define TIMER_SYNC_SSYNC_Msk                  (0x01UL << TIMER_SYNC_SSYNC_Pos)                        /*!< TIMER SYNC: SSYNC Mask                  */
#define TIMER_SYNC_T0SYNCB_Pos                20                                                      /*!< TIMER SYNC: T0SYNCB Position            */
#define TIMER_SYNC_T0SYNCB_Msk                (0x01UL << TIMER_SYNC_T0SYNCB_Pos)                      /*!< TIMER SYNC: T0SYNCB Mask                */
#define TIMER_SYNC_T1SYNCB_Pos                21                                                      /*!< TIMER SYNC: T1SYNCB Position            */
#define TIMER_SYNC_T1SYNCB_Msk                (0x01UL << TIMER_SYNC_T1SYNCB_Pos)                      /*!< TIMER SYNC: T1SYNCB Mask                */
#define TIMER_SYNC_T2SYNCB_Pos                22                                                      /*!< TIMER SYNC: T2SYNCB Position            */
#define TIMER_SYNC_T2SYNCB_Msk                (0x01UL << TIMER_SYNC_T2SYNCB_Pos)                      /*!< TIMER SYNC: T2SYNCB Mask                */
#define TIMER_SYNC_T3SYNCB_Pos                23                                                      /*!< TIMER SYNC: T3SYNCB Position            */
#define TIMER_SYNC_T3SYNCB_Msk                (0x01UL << TIMER_SYNC_T3SYNCB_Pos)                      /*!< TIMER SYNC: T3SYNCB Mask                */



/* ================================================================================ */
/* ================          struct 'FRT' Position & Mask          ================ */
/* ================================================================================ */


/* ----------------------------------  FRT_CTRL  ---------------------------------- */
#define FRT_CTRL_EN_Pos                       0                                                       /*!< FRT CTRL: EN Position                   */
#define FRT_CTRL_EN_Msk                       (0x01UL << FRT_CTRL_EN_Pos)                             /*!< FRT CTRL: EN Mask                       */
#define FRT_CTRL_MODE_Pos                     1                                                       /*!< FRT CTRL: MODE Position                 */
#define FRT_CTRL_MODE_Msk                     (0x01UL << FRT_CTRL_MODE_Pos)                           /*!< FRT CTRL: MODE Mask                     */
#define FRT_CTRL_MATCHIE_Pos                  8                                                       /*!< FRT CTRL: MATCHIE Position              */
#define FRT_CTRL_MATCHIE_Msk                  (0x01UL << FRT_CTRL_MATCHIE_Pos)                        /*!< FRT CTRL: MATCHIE Mask                  */
#define FRT_CTRL_OVFIE_Pos                    9                                                       /*!< FRT CTRL: OVFIE Position                */
#define FRT_CTRL_OVFIE_Msk                    (0x01UL << FRT_CTRL_OVFIE_Pos)                          /*!< FRT CTRL: OVFIE Mask                    */

/* ----------------------------------  FRT_MCNT  ---------------------------------- */
#define FRT_MCNT_MCNT_Pos                     0                                                       /*!< FRT MCNT: MCNT Position                 */
#define FRT_MCNT_MCNT_Msk                     (0xffffffffUL << FRT_MCNT_MCNT_Pos)                     /*!< FRT MCNT: MCNT Mask                     */

/* -----------------------------------  FRT_CNT  ---------------------------------- */
#define FRT_CNT_CNT_Pos                       0                                                       /*!< FRT CNT: CNT Position                   */
#define FRT_CNT_CNT_Msk                       (0xffffffffUL << FRT_CNT_CNT_Pos)                       /*!< FRT CNT: CNT Mask                       */

/* ----------------------------------  FRT_STAT  ---------------------------------- */
#define FRT_STAT_MATCHIF_Pos                  8                                                       /*!< FRT STAT: MATCHIF Position              */
#define FRT_STAT_MATCHIF_Msk                  (0x01UL << FRT_STAT_MATCHIF_Pos)                        /*!< FRT STAT: MATCHIF Mask                  */
#define FRT_STAT_OVFIF_Pos                    9                                                       /*!< FRT STAT: OVFIF Position                */
#define FRT_STAT_OVFIF_Msk                    (0x01UL << FRT_STAT_OVFIF_Pos)                          /*!< FRT STAT: OVFIF Mask                    */


/* ================================================================================ */
/* ================          Group 'UART' Position & Mask          ================ */
/* ================================================================================ */


/* ----------------------------------  UART_RBR  ---------------------------------- */
#define UART_RBR_DATA_Pos                     0                                                       /*!< UART RBR: DATA Position                 */
#define UART_RBR_DATA_Msk                     (0x000000ffUL << UART_RBR_DATA_Pos)                     /*!< UART RBR: DATA Mask                     */

/* ----------------------------------  UART_THR  ---------------------------------- */
#define UART_THR_DATA_Pos                     0                                                       /*!< UART THR: DATA Position                 */
#define UART_THR_DATA_Msk                     (0x000000ffUL << UART_THR_DATA_Pos)                     /*!< UART THR: DATA Mask                     */

/* ----------------------------------  UART_IER  ---------------------------------- */
#define UART_IER_DRIE_Pos                     0                                                       /*!< UART IER: DRIE Position                 */
#define UART_IER_DRIE_Msk                     (0x01UL << UART_IER_DRIE_Pos)                           /*!< UART IER: DRIE Mask                     */
#define UART_IER_THREIE_Pos                   1                                                       /*!< UART IER: THREIE Position               */
#define UART_IER_THREIE_Msk                   (0x01UL << UART_IER_THREIE_Pos)                         /*!< UART IER: THREIE Mask                   */
#define UART_IER_RLSIE_Pos                    2                                                       /*!< UART IER: RLSIE Position                */
#define UART_IER_RLSIE_Msk                    (0x01UL << UART_IER_RLSIE_Pos)                          /*!< UART IER: RLSIE Mask                    */
#define UART_IER_TXEIE_Pos                    3                                                       /*!< UART IER: TXEIE Position                */
#define UART_IER_TXEIE_Msk                    (0x01UL << UART_IER_TXEIE_Pos)                          /*!< UART IER: TXEIE Mask                    */
#define UART_IER_DRXIEN_Pos                   4                                                       /*!< UART IER: DRXIEN Position               */
#define UART_IER_DRXIEN_Msk                   (0x01UL << UART_IER_DRXIEN_Pos)                         /*!< UART IER: DRXIEN Mask                   */
#define UART_IER_DTXIEN_Pos                   5                                                       /*!< UART IER: DTXIEN Position               */
#define UART_IER_DTXIEN_Msk                   (0x01UL << UART_IER_DTXIEN_Pos)                         /*!< UART IER: DTXIEN Mask                   */

/* ----------------------------------  UART_IIR  ---------------------------------- */
#define UART_IIR_IPEN_Pos                     0                                                       /*!< UART IIR: IPEN Position                 */
#define UART_IIR_IPEN_Msk                     (0x01UL << UART_IIR_IPEN_Pos)                           /*!< UART IIR: IPEN Mask                     */
#define UART_IIR_IID_Pos                      1                                                       /*!< UART IIR: IID Position                  */
#define UART_IIR_IID_Msk                      (0x07UL << UART_IIR_IID_Pos)                            /*!< UART IIR: IID Mask                      */
#define UART_IIR_TXE_Pos                      4                                                       /*!< UART IIR: TXE Position                  */
#define UART_IIR_TXE_Msk                      (0x01UL << UART_IIR_TXE_Pos)                            /*!< UART IIR: TXE Mask                      */

/* ----------------------------------  UART_LCR  ---------------------------------- */
#define UART_LCR_DLEN_Pos                     0                                                       /*!< UART LCR: DLEN Position                 */
#define UART_LCR_DLEN_Msk                     (0x03UL << UART_LCR_DLEN_Pos)                           /*!< UART LCR: DLEN Mask                     */
#define UART_LCR_STOPBIT_Pos                  2                                                       /*!< UART LCR: STOPBIT Position              */
#define UART_LCR_STOPBIT_Msk                  (0x01UL << UART_LCR_STOPBIT_Pos)                        /*!< UART LCR: STOPBIT Mask                  */
#define UART_LCR_PEN_Pos                      3                                                       /*!< UART LCR: PEN Position                  */
#define UART_LCR_PEN_Msk                      (0x01UL << UART_LCR_PEN_Pos)                            /*!< UART LCR: PEN Mask                      */
#define UART_LCR_PARITY_Pos                   4                                                       /*!< UART LCR: PARITY Position               */
#define UART_LCR_PARITY_Msk                   (0x01UL << UART_LCR_PARITY_Pos)                         /*!< UART LCR: PARITY Mask                   */
#define UART_LCR_STICKP_Pos                   5                                                       /*!< UART LCR: STICKP Position               */
#define UART_LCR_STICKP_Msk                   (0x01UL << UART_LCR_STICKP_Pos)                         /*!< UART LCR: STICKP Mask                   */
#define UART_LCR_BREAK_Pos                    6                                                       /*!< UART LCR: BREAK Position                */
#define UART_LCR_BREAK_Msk                    (0x01UL << UART_LCR_BREAK_Pos)                          /*!< UART LCR: BREAK Mask                    */

/* ----------------------------------  UART_DCR  ---------------------------------- */
#define UART_DCR_TXINV_Pos                    2                                                       /*!< UART DCR: TXINV Position                */
#define UART_DCR_TXINV_Msk                    (0x01UL << UART_DCR_TXINV_Pos)                          /*!< UART DCR: TXINV Mask                    */
#define UART_DCR_RXINV_Pos                    3                                                       /*!< UART DCR: RXINV Position                */
#define UART_DCR_RXINV_Msk                    (0x01UL << UART_DCR_RXINV_Pos)                          /*!< UART DCR: RXINV Mask                    */

/* ----------------------------------  UART_LSR  ---------------------------------- */
#define UART_LSR_DR_Pos                       0                                                       /*!< UART LSR: DR Position                   */
#define UART_LSR_DR_Msk                       (0x01UL << UART_LSR_DR_Pos)                             /*!< UART LSR: DR Mask                       */
#define UART_LSR_OE_Pos                       1                                                       /*!< UART LSR: OE Position                   */
#define UART_LSR_OE_Msk                       (0x01UL << UART_LSR_OE_Pos)                             /*!< UART LSR: OE Mask                       */
#define UART_LSR_PE_Pos                       2                                                       /*!< UART LSR: PE Position                   */
#define UART_LSR_PE_Msk                       (0x01UL << UART_LSR_PE_Pos)                             /*!< UART LSR: PE Mask                       */
#define UART_LSR_FE_Pos                       3                                                       /*!< UART LSR: FE Position                   */
#define UART_LSR_FE_Msk                       (0x01UL << UART_LSR_FE_Pos)                             /*!< UART LSR: FE Mask                       */
#define UART_LSR_BI_Pos                       4                                                       /*!< UART LSR: BI Position                   */
#define UART_LSR_BI_Msk                       (0x01UL << UART_LSR_BI_Pos)                             /*!< UART LSR: BI Mask                       */
#define UART_LSR_THRE_Pos                     5                                                       /*!< UART LSR: THRE Position                 */
#define UART_LSR_THRE_Msk                     (0x01UL << UART_LSR_THRE_Pos)                           /*!< UART LSR: THRE Mask                     */
#define UART_LSR_TEMT_Pos                     6                                                       /*!< UART LSR: TEMT Position                 */
#define UART_LSR_TEMT_Msk                     (0x01UL << UART_LSR_TEMT_Pos)                           /*!< UART LSR: TEMT Mask                     */

/* ----------------------------------  UART_BDR  ---------------------------------- */
#define UART_BDR_BDR_Pos                      0                                                       /*!< UART BDR: BDR Position                  */
#define UART_BDR_BDR_Msk                      (0x0000ffffUL << UART_BDR_BDR_Pos)                      /*!< UART BDR: BDR Mask                      */

/* ----------------------------------  UART_BFR  ---------------------------------- */
#define UART_BFR_BFR_Pos                      0                                                       /*!< UART BFR: BFR Position                  */
#define UART_BFR_BFR_Msk                      (0x000000ffUL << UART_BFR_BFR_Pos)                      /*!< UART BFR: BFR Mask                      */

/* ----------------------------------  UART_IDTR  --------------------------------- */
#define UART_IDTR_WAITVAL_Pos                 0                                                       /*!< UART IDTR: WAITVAL Position             */
#define UART_IDTR_WAITVAL_Msk                 (0x07UL << UART_IDTR_WAITVAL_Pos)                       /*!< UART IDTR: WAITVAL Mask                 */
#define UART_IDTR_DMS_Pos                     6                                                       /*!< UART IDTR: DMS Position                 */
#define UART_IDTR_DMS_Msk                     (0x01UL << UART_IDTR_DMS_Pos)                           /*!< UART IDTR: DMS Mask                     */
#define UART_IDTR_SMS_Pos                     7                                                       /*!< UART IDTR: SMS Position                 */
#define UART_IDTR_SMS_Msk                     (0x01UL << UART_IDTR_SMS_Pos)                           /*!< UART IDTR: SMS Mask                     */




/* ================================================================================ */
/* ================          struct 'SPI' Position & Mask          ================ */
/* ================================================================================ */


/* -----------------------------------  SPI_TDR  ---------------------------------- */
#define SPI_TDR_TDR_Pos                       0                                                       /*!< SPI TDR: TDR Position                   */
#define SPI_TDR_TDR_Msk                       (0x0001ffffUL << SPI_TDR_TDR_Pos)                       /*!< SPI TDR: TDR Mask                       */

/* -----------------------------------  SPI_RDR  ---------------------------------- */
#define SPI_RDR_RDR_Pos                       0                                                       /*!< SPI RDR: RDR Position                   */
#define SPI_RDR_RDR_Msk                       (0x0001ffffUL << SPI_RDR_RDR_Pos)                       /*!< SPI RDR: RDR Mask                       */

/* -----------------------------------  SPI_CR  ----------------------------------- */
#define SPI_CR_BITSZ_Pos                      0                                                       /*!< SPI CR: BITSZ Position                  */
#define SPI_CR_BITSZ_Msk                      (0x03UL << SPI_CR_BITSZ_Pos)                            /*!< SPI CR: BITSZ Mask                      */
#define SPI_CR_CPOL_Pos                       2                                                       /*!< SPI CR: CPOL Position                   */
#define SPI_CR_CPOL_Msk                       (0x01UL << SPI_CR_CPOL_Pos)                             /*!< SPI CR: CPOL Mask                       */
#define SPI_CR_CPHA_Pos                       3                                                       /*!< SPI CR: CPHA Position                   */
#define SPI_CR_CPHA_Msk                       (0x01UL << SPI_CR_CPHA_Pos)                             /*!< SPI CR: CPHA Mask                       */
#define SPI_CR_MSBF_Pos                       4                                                       /*!< SPI CR: MSBF Position                   */
#define SPI_CR_MSBF_Msk                       (0x01UL << SPI_CR_MSBF_Pos)                             /*!< SPI CR: MSBF Mask                       */
#define SPI_CR_MS_Pos                         5                                                       /*!< SPI CR: MS Position                     */
#define SPI_CR_MS_Msk                         (0x01UL << SPI_CR_MS_Pos)                               /*!< SPI CR: MS Mask                         */
#define SPI_CR_SSPOL_Pos                      8                                                       /*!< SPI CR: SSPOL Position                  */
#define SPI_CR_SSPOL_Msk                      (0x01UL << SPI_CR_SSPOL_Pos)                            /*!< SPI CR: SSPOL Mask                      */
#define SPI_CR_SSMO_Pos                       9                                                       /*!< SPI CR: SSMO Position                   */
#define SPI_CR_SSMO_Msk                       (0x01UL << SPI_CR_SSMO_Pos)                             /*!< SPI CR: SSMO Mask                       */
#define SPI_CR_SSMASK_Pos                     10                                                      /*!< SPI CR: SSMASK Position                 */
#define SPI_CR_SSMASK_Msk                     (0x01UL << SPI_CR_SSMASK_Pos)                           /*!< SPI CR: SSMASK Mask                     */
#define SPI_CR_LBE_Pos                        11                                                      /*!< SPI CR: LBE Position                    */
#define SPI_CR_LBE_Msk                        (0x01UL << SPI_CR_LBE_Pos)                              /*!< SPI CR: LBE Mask                        */
#define SPI_CR_SSOUT_Pos                      12                                                      /*!< SPI CR: SSOUT Position                  */
#define SPI_CR_SSOUT_Msk                      (0x01UL << SPI_CR_SSOUT_Pos)                            /*!< SPI CR: SSOUT Mask                      */
#define SPI_CR_SSMOD_Pos                      13                                                      /*!< SPI CR: SSMOD Position                  */
#define SPI_CR_SSMOD_Msk                      (0x01UL << SPI_CR_SSMOD_Pos)                            /*!< SPI CR: SSMOD Mask                      */
#define SPI_CR_RXIE_Pos                       14                                                      /*!< SPI CR: RXIE Position                   */
#define SPI_CR_RXIE_Msk                       (0x01UL << SPI_CR_RXIE_Pos)                             /*!< SPI CR: RXIE Mask                       */
#define SPI_CR_TXIE_Pos                       15                                                      /*!< SPI CR: TXIE Position                   */
#define SPI_CR_TXIE_Msk                       (0x01UL << SPI_CR_TXIE_Pos)                             /*!< SPI CR: TXIE Mask                       */
#define SPI_CR_SSCIE_Pos                      16                                                      /*!< SPI CR: SSCIE Position                  */
#define SPI_CR_SSCIE_Msk                      (0x01UL << SPI_CR_SSCIE_Pos)                            /*!< SPI CR: SSCIE Mask                      */
#define SPI_CR_DRXIE_Pos                      17                                                      /*!< SPI CR: DRXIE Position                  */
#define SPI_CR_DRXIE_Msk                      (0x01UL << SPI_CR_DRXIE_Pos)                            /*!< SPI CR: DRXIE Mask                      */
#define SPI_CR_DTXIE_Pos                      18                                                      /*!< SPI CR: DTXIE Position                  */
#define SPI_CR_DTXIE_Msk                      (0x01UL << SPI_CR_DTXIE_Pos)                            /*!< SPI CR: DTXIE Mask                      */
#define SPI_CR_RXBC_Pos                       19                                                      /*!< SPI CR: RXBC Position                   */
#define SPI_CR_RXBC_Msk                       (0x01UL << SPI_CR_RXBC_Pos)                             /*!< SPI CR: RXBC Mask                       */
#define SPI_CR_TXBC_Pos                       20                                                      /*!< SPI CR: TXBC Position                   */
#define SPI_CR_TXBC_Msk                       (0x01UL << SPI_CR_TXBC_Pos)                             /*!< SPI CR: TXBC Mask                       */

/* -----------------------------------  SPI_SR  ----------------------------------- */
#define SPI_SR_RRDY_Pos                       0                                                       /*!< SPI SR: RRDY Position                   */
#define SPI_SR_RRDY_Msk                       (0x01UL << SPI_SR_RRDY_Pos)                             /*!< SPI SR: RRDY Mask                       */
#define SPI_SR_TRDY_Pos                       1                                                       /*!< SPI SR: TRDY Position                   */
#define SPI_SR_TRDY_Msk                       (0x01UL << SPI_SR_TRDY_Pos)                             /*!< SPI SR: TRDY Mask                       */
#define SPI_SR_TXIDLE_Pos                     2                                                       /*!< SPI SR: TXIDLE Position                 */
#define SPI_SR_TXIDLE_Msk                     (0x01UL << SPI_SR_TXIDLE_Pos)                           /*!< SPI SR: TXIDLE Mask                     */
#define SPI_SR_UDRF_Pos                       3                                                       /*!< SPI SR: UDRF Position                   */
#define SPI_SR_UDRF_Msk                       (0x01UL << SPI_SR_UDRF_Pos)                             /*!< SPI SR: UDRF Mask                       */
#define SPI_SR_OVRF_Pos                       4                                                       /*!< SPI SR: OVRF Position                   */
#define SPI_SR_OVRF_Msk                       (0x01UL << SPI_SR_OVRF_Pos)                             /*!< SPI SR: OVRF Mask                       */
#define SPI_SR_SSON_Pos                       5                                                       /*!< SPI SR: SSON Position                   */
#define SPI_SR_SSON_Msk                       (0x01UL << SPI_SR_SSON_Pos)                             /*!< SPI SR: SSON Mask                       */
#define SPI_SR_SSDET_Pos                      6                                                       /*!< SPI SR: SSDET Position                  */
#define SPI_SR_SSDET_Msk                      (0x01UL << SPI_SR_SSDET_Pos)                            /*!< SPI SR: SSDET Mask                      */
#define SPI_SR_SBUSY_Pos                      7                                                       /*!< SPI SR: SBUSY Position                  */
#define SPI_SR_SBUSY_Msk                      (0x01UL << SPI_SR_SBUSY_Pos)                            /*!< SPI SR: SBUSY Mask                      */
#define SPI_SR_RXDMAF_Pos                     8                                                       /*!< SPI SR: RXDMAF Position                 */
#define SPI_SR_RXDMAF_Msk                     (0x01UL << SPI_SR_RXDMAF_Pos)                           /*!< SPI SR: RXDMAF Mask                     */
#define SPI_SR_TXDMAF_Pos                     9                                                       /*!< SPI SR: TXDMAF Position                 */
#define SPI_SR_TXDMAF_Msk                     (0x01UL << SPI_SR_TXDMAF_Pos)                           /*!< SPI SR: TXDMAF Mask                     */

/* -----------------------------------  SPI_BR  ----------------------------------- */
#define SPI_BR_BR_Pos                         0                                                       /*!< SPI BR: BR Position                     */
#define SPI_BR_BR_Msk                         (0x0000ffffUL << SPI_BR_BR_Pos)                         /*!< SPI BR: BR Mask                         */

/* -----------------------------------  SPI_EN  ----------------------------------- */
#define SPI_EN_ENABLE_Pos                     0                                                       /*!< SPI EN: ENABLE Position                 */
#define SPI_EN_ENABLE_Msk                     (0x01UL << SPI_EN_ENABLE_Pos)                           /*!< SPI EN: ENABLE Mask                     */

/* -----------------------------------  SPI_LR  ----------------------------------- */
#define SPI_LR_STL_Pos                        0                                                       /*!< SPI LR: STL Position                    */
#define SPI_LR_STL_Msk                        (0x000000ffUL << SPI_LR_STL_Pos)                        /*!< SPI LR: STL Mask                        */
#define SPI_LR_BTL_Pos                        8                                                       /*!< SPI LR: BTL Position                    */
#define SPI_LR_BTL_Msk                        (0x000000ffUL << SPI_LR_BTL_Pos)                        /*!< SPI LR: BTL Mask                        */
#define SPI_LR_SPL_Pos                        16                                                      /*!< SPI LR: SPL Position                    */
#define SPI_LR_SPL_Msk                        (0x000000ffUL << SPI_LR_SPL_Pos)                        /*!< SPI LR: SPL Mask                        */


/* ================================================================================ */
/* ================          struct 'I2C' Position & Mask          ================ */
/* ================================================================================ */


/* -----------------------------------  I2C_DR  ----------------------------------- */
#define I2C_DR_ICDR_Pos                       0                                                       /*!< I2C DR: ICDR Position                   */
#define I2C_DR_ICDR_Msk                       (0x000000ffUL << I2C_DR_ICDR_Pos)                       /*!< I2C DR: ICDR Mask                       */

/* -----------------------------------  I2C_SR  ----------------------------------- */
#define I2C_SR_RXACK_Pos                      0                                                       /*!< I2C SR: RXACK Position                  */
#define I2C_SR_RXACK_Msk                      (0x01UL << I2C_SR_RXACK_Pos)                            /*!< I2C SR: RXACK Mask                      */
#define I2C_SR_TMOD_Pos                       1                                                       /*!< I2C SR: TMOD Position                   */
#define I2C_SR_TMOD_Msk                       (0x01UL << I2C_SR_TMOD_Pos)                             /*!< I2C SR: TMOD Mask                       */
#define I2C_SR_BUSY_Pos                       2                                                       /*!< I2C SR: BUSY Position                   */
#define I2C_SR_BUSY_Msk                       (0x01UL << I2C_SR_BUSY_Pos)                             /*!< I2C SR: BUSY Mask                       */
#define I2C_SR_MLOST_Pos                      3                                                       /*!< I2C SR: MLOST Position                  */
#define I2C_SR_MLOST_Msk                      (0x01UL << I2C_SR_MLOST_Pos)                            /*!< I2C SR: MLOST Mask                      */
#define I2C_SR_SSEL_Pos                       4                                                       /*!< I2C SR: SSEL Position                   */
#define I2C_SR_SSEL_Msk                       (0x01UL << I2C_SR_SSEL_Pos)                             /*!< I2C SR: SSEL Mask                       */
#define I2C_SR_STOP_Pos                       5                                                       /*!< I2C SR: STOP Position                   */
#define I2C_SR_STOP_Msk                       (0x01UL << I2C_SR_STOP_Pos)                             /*!< I2C SR: STOP Mask                       */
#define I2C_SR_TEND_Pos                       6                                                       /*!< I2C SR: TEND Position                   */
#define I2C_SR_TEND_Msk                       (0x01UL << I2C_SR_TEND_Pos)                             /*!< I2C SR: TEND Mask                       */
#define I2C_SR_GCALL_Pos                      7                                                       /*!< I2C SR: GCALL Position                  */
#define I2C_SR_GCALL_Msk                      (0x01UL << I2C_SR_GCALL_Pos)                            /*!< I2C SR: GCALL Mask                      */

/* -----------------------------------  I2C_SAR  ---------------------------------- */
#define I2C_SAR_GCEN_Pos                      0                                                       /*!< I2C SAR: GCEN Position                  */
#define I2C_SAR_GCEN_Msk                      (0x01UL << I2C_SAR_GCEN_Pos)                            /*!< I2C SAR: GCEN Mask                      */
#define I2C_SAR_SVAD_Pos                      1                                                       /*!< I2C SAR: SVAD Position                  */
#define I2C_SAR_SVAD_Msk                      (0x7fUL << I2C_SAR_SVAD_Pos)                            /*!< I2C SAR: SVAD Mask                      */

/* -----------------------------------  I2C_CR  ----------------------------------- */
#define I2C_CR_START_Pos                      0                                                       /*!< I2C CR: START Position                  */
#define I2C_CR_START_Msk                      (0x01UL << I2C_CR_START_Pos)                            /*!< I2C CR: START Mask                      */
#define I2C_CR_STOP_Pos                       1                                                       /*!< I2C CR: STOP Position                   */
#define I2C_CR_STOP_Msk                       (0x01UL << I2C_CR_STOP_Pos)                             /*!< I2C CR: STOP Mask                       */
#define I2C_CR_ACKEN_Pos                      3                                                       /*!< I2C CR: ACKEN Position                  */
#define I2C_CR_ACKEN_Msk                      (0x01UL << I2C_CR_ACKEN_Pos)                            /*!< I2C CR: ACKEN Mask                      */
#define I2C_CR_INTEN_Pos                      4                                                       /*!< I2C CR: INTEN Position                  */
#define I2C_CR_INTEN_Msk                      (0x01UL << I2C_CR_INTEN_Pos)                            /*!< I2C CR: INTEN Mask                      */
#define I2C_CR_IIF_Pos                        7                                                       /*!< I2C CR: IIF Position                    */
#define I2C_CR_IIF_Msk                        (0x01UL << I2C_CR_IIF_Pos)                              /*!< I2C CR: IIF Mask                        */
#define I2C_CR_INTDEL_Pos                     8                                                       /*!< I2C CR: INTDEL Position                 */
#define I2C_CR_INTDEL_Msk                     (0x03UL << I2C_CR_INTDEL_Pos)                           /*!< I2C CR: INTDEL Mask                     */

/* ----------------------------------  I2C_SCLL  ---------------------------------- */
#define I2C_SCLL_SCLL_Pos                     0                                                       /*!< I2C SCLL: SCLL Position                 */
#define I2C_SCLL_SCLL_Msk                     (0x0000ffffUL << I2C_SCLL_SCLL_Pos)                     /*!< I2C SCLL: SCLL Mask                     */

/* ----------------------------------  I2C_SCLH  ---------------------------------- */
#define I2C_SCLH_SCLH_Pos                     0                                                       /*!< I2C SCLH: SCLH Position                 */
#define I2C_SCLH_SCLH_Msk                     (0x0000ffffUL << I2C_SCLH_SCLH_Pos)                     /*!< I2C SCLH: SCLH Mask                     */

/* -----------------------------------  I2C_SDH  ---------------------------------- */
#define I2C_SDH_SDH_Pos                       0                                                       /*!< I2C SDH: SDH Position                   */
#define I2C_SDH_SDH_Msk                       (0x00007fffUL << I2C_SDH_SDH_Pos)                       /*!< I2C SDH: SDH Mask                       */


/* ================================================================================ */
/* ================          struct 'MPWM' Position & Mask         ================ */
/* ================================================================================ */


/* -----------------------------------  MPWM_MR  ---------------------------------- */
#define MPWM_MR_MCHMOD_Pos                    1                                                       /*!< MPWM MR: MCHMOD Position                */
#define MPWM_MR_MCHMOD_Msk                    (0x03UL << MPWM_MR_MCHMOD_Pos)                          /*!< MPWM MR: MCHMOD Mask                    */
#define MPWM_MR_BUP_Pos                       4                                                       /*!< MPWM MR: BUP Position                   */
#define MPWM_MR_BUP_Msk                       (0x01UL << MPWM_MR_BUP_Pos)                             /*!< MPWM MR: BUP Mask                       */
#define MPWM_MR_TUP_Pos                       5                                                       /*!< MPWM MR: TUP Position                   */
#define MPWM_MR_TUP_Msk                       (0x01UL << MPWM_MR_TUP_Pos)                             /*!< MPWM MR: TUP Mask                       */
#define MPWM_MR_UAO_Pos                       7                                                       /*!< MPWM MR: UAO Position                   */
#define MPWM_MR_UAO_Msk                       (0x01UL << MPWM_MR_UAO_Pos)                             /*!< MPWM MR: UAO Mask                       */
#define MPWM_MR_BUOL_Pos                      8                                                       /*!< MPWM MR: BUOL Position                  */
#define MPWM_MR_BUOL_Msk                      (0x01UL << MPWM_MR_BUOL_Pos)                            /*!< MPWM MR: BUOL Mask                      */
#define MPWM_MR_TUOL_Pos                      9                                                       /*!< MPWM MR: TUOL Position                  */
#define MPWM_MR_TUOL_Msk                      (0x01UL << MPWM_MR_TUOL_Pos)                            /*!< MPWM MR: TUOL Mask                      */
#define MPWM_MR_UOL_Pos                       11                                                      /*!< MPWM MR: UOL Position                   */
#define MPWM_MR_UOL_Msk                       (0x01UL << MPWM_MR_UOL_Pos)                             /*!< MPWM MR: UOL Mask                       */
#define MPWM_MR_MOTORB_Pos                    14                                                      /*!< MPWM MR: MOTORB Position                */
#define MPWM_MR_MOTORB_Msk                    (0x03UL << MPWM_MR_MOTORB_Pos)                          /*!< MPWM MR: MOTORB Mask                    */
#define MPWM_MR_CLKDIV_Pos                    16                                                      /*!< MPWM MR: CLKDIV Position                */
#define MPWM_MR_CLKDIV_Msk                    (0x0fUL << MPWM_MR_CLKDIV_Pos)                          /*!< MPWM MR: CLKDIV Mask                    */
#define MPWM_MR_BFM_Pos                       30                                                      /*!< MPWM MR: BFM Position                   */
#define MPWM_MR_BFM_Msk                       (0x01UL << MPWM_MR_BFM_Pos)                             /*!< MPWM MR: BFM Mask                       */
#define MPWM_MR_TFM_Pos                       31                                                      /*!< MPWM MR: TFM Position                   */
#define MPWM_MR_TFM_Msk                       (0x01UL << MPWM_MR_TFM_Pos)                             /*!< MPWM MR: TFM Mask                       */

/* ----------------------------------  MPWM_OLR  ---------------------------------- */
#define MPWM_OLR_SLUL_Pos                     0                                                       /*!< MPWM OLR: SLUL Position                 */
#define MPWM_OLR_SLUL_Msk                     (0x01UL << MPWM_OLR_SLUL_Pos)                           /*!< MPWM OLR: SLUL Mask                     */
#define MPWM_OLR_SLVL_Pos                     1                                                       /*!< MPWM OLR: SLVL Position                 */
#define MPWM_OLR_SLVL_Msk                     (0x01UL << MPWM_OLR_SLVL_Pos)                           /*!< MPWM OLR: SLVL Mask                     */
#define MPWM_OLR_SLWL_Pos                     2                                                       /*!< MPWM OLR: SLWL Position                 */
#define MPWM_OLR_SLWL_Msk                     (0x01UL << MPWM_OLR_SLWL_Pos)                           /*!< MPWM OLR: SLWL Mask                     */
#define MPWM_OLR_SLUH_Pos                     3                                                       /*!< MPWM OLR: SLUH Position                 */
#define MPWM_OLR_SLUH_Msk                     (0x01UL << MPWM_OLR_SLUH_Pos)                           /*!< MPWM OLR: SLUH Mask                     */
#define MPWM_OLR_SLVH_Pos                     4                                                       /*!< MPWM OLR: SLVH Position                 */
#define MPWM_OLR_SLVH_Msk                     (0x01UL << MPWM_OLR_SLVH_Pos)                           /*!< MPWM OLR: SLVH Mask                     */
#define MPWM_OLR_SLWH_Pos                     5                                                       /*!< MPWM OLR: SLWH Position                 */
#define MPWM_OLR_SLWH_Msk                     (0x01UL << MPWM_OLR_SLWH_Pos)                           /*!< MPWM OLR: SLWH Mask                     */
#define MPWM_OLR_DOLUL_Pos                    8                                                       /*!< MPWM OLR: DOLUL Position                */
#define MPWM_OLR_DOLUL_Msk                    (0x01UL << MPWM_OLR_DOLUL_Pos)                          /*!< MPWM OLR: DOLUL Mask                    */
#define MPWM_OLR_DOLVL_Pos                    9                                                       /*!< MPWM OLR: DOLVL Position                */
#define MPWM_OLR_DOLVL_Msk                    (0x01UL << MPWM_OLR_DOLVL_Pos)                          /*!< MPWM OLR: DOLVL Mask                    */
#define MPWM_OLR_DOLWL_Pos                    10                                                      /*!< MPWM OLR: DOLWL Position                */
#define MPWM_OLR_DOLWL_Msk                    (0x01UL << MPWM_OLR_DOLWL_Pos)                          /*!< MPWM OLR: DOLWL Mask                    */
#define MPWM_OLR_DOLUH_Pos                    11                                                      /*!< MPWM OLR: DOLUH Position                */
#define MPWM_OLR_DOLUH_Msk                    (0x01UL << MPWM_OLR_DOLUH_Pos)                          /*!< MPWM OLR: DOLUH Mask                    */
#define MPWM_OLR_DOLVH_Pos                    12                                                      /*!< MPWM OLR: DOLVH Position                */
#define MPWM_OLR_DOLVH_Msk                    (0x01UL << MPWM_OLR_DOLVH_Pos)                          /*!< MPWM OLR: DOLVH Mask                    */
#define MPWM_OLR_DOLWH_Pos                    13                                                      /*!< MPWM OLR: DOLWH Position                */
#define MPWM_OLR_DOLWH_Msk                    (0x01UL << MPWM_OLR_DOLWH_Pos)                          /*!< MPWM OLR: DOLWH Mask                    */
#define MPWM_OLR_POCUL_Pos                    16                                                      /*!< MPWM OLR: POCUL Position                */
#define MPWM_OLR_POCUL_Msk                    (0x01UL << MPWM_OLR_POCUL_Pos)                          /*!< MPWM OLR: POCUL Mask                    */
#define MPWM_OLR_POCVL_Pos                    17                                                      /*!< MPWM OLR: POCVL Position                */
#define MPWM_OLR_POCVL_Msk                    (0x01UL << MPWM_OLR_POCVL_Pos)                          /*!< MPWM OLR: POCVL Mask                    */
#define MPWM_OLR_POCWL_Pos                    18                                                      /*!< MPWM OLR: POCWL Position                */
#define MPWM_OLR_POCWL_Msk                    (0x01UL << MPWM_OLR_POCWL_Pos)                          /*!< MPWM OLR: POCWL Mask                    */
#define MPWM_OLR_POCUH_Pos                    19                                                      /*!< MPWM OLR: POCUH Position                */
#define MPWM_OLR_POCUH_Msk                    (0x01UL << MPWM_OLR_POCUH_Pos)                          /*!< MPWM OLR: POCUH Mask                    */
#define MPWM_OLR_POCVH_Pos                    20                                                      /*!< MPWM OLR: POCVH Position                */
#define MPWM_OLR_POCVH_Msk                    (0x01UL << MPWM_OLR_POCVH_Pos)                          /*!< MPWM OLR: POCVH Mask                    */
#define MPWM_OLR_POCWH_Pos                    21                                                      /*!< MPWM OLR: POCWH Position                */
#define MPWM_OLR_POCWH_Msk                    (0x01UL << MPWM_OLR_POCWH_Pos)                          /*!< MPWM OLR: POCWH Mask                    */
#define MPWM_OLR_FORCEU_Pos                   24                                                      /*!< MPWM OLR: FORCEU Position               */
#define MPWM_OLR_FORCEU_Msk                   (0x01UL << MPWM_OLR_FORCEU_Pos)                         /*!< MPWM OLR: FORCEU Mask                   */

/* ----------------------------------  MPWM_FOLR  --------------------------------- */
#define MPWM_FOLR_FLUL_Pos                    0                                                       /*!< MPWM FOLR: FLUL Position                */
#define MPWM_FOLR_FLUL_Msk                    (0x01UL << MPWM_FOLR_FLUL_Pos)                          /*!< MPWM FOLR: FLUL Mask                    */
#define MPWM_FOLR_FLVL_Pos                    1                                                       /*!< MPWM FOLR: FLVL Position                */
#define MPWM_FOLR_FLVL_Msk                    (0x01UL << MPWM_FOLR_FLVL_Pos)                          /*!< MPWM FOLR: FLVL Mask                    */
#define MPWM_FOLR_FLWL_Pos                    2                                                       /*!< MPWM FOLR: FLWL Position                */
#define MPWM_FOLR_FLWL_Msk                    (0x01UL << MPWM_FOLR_FLWL_Pos)                          /*!< MPWM FOLR: FLWL Mask                    */
#define MPWM_FOLR_FLUH_Pos                    3                                                       /*!< MPWM FOLR: FLUH Position                */
#define MPWM_FOLR_FLUH_Msk                    (0x01UL << MPWM_FOLR_FLUH_Pos)                          /*!< MPWM FOLR: FLUH Mask                    */
#define MPWM_FOLR_FLVH_Pos                    4                                                       /*!< MPWM FOLR: FLVH Position                */
#define MPWM_FOLR_FLVH_Msk                    (0x01UL << MPWM_FOLR_FLVH_Pos)                          /*!< MPWM FOLR: FLVH Mask                    */
#define MPWM_FOLR_FLWH_Pos                    5                                                       /*!< MPWM FOLR: FLWH Position                */
#define MPWM_FOLR_FLWH_Msk                    (0x01UL << MPWM_FOLR_FLWH_Pos)                          /*!< MPWM FOLR: FLWH Mask                    */
#define MPWM_FOLR_OCFO_Pos                    8                                                       /*!< MPWM FOLR: OCFO Position                */
#define MPWM_FOLR_OCFO_Msk                    (0x01UL << MPWM_FOLR_OCFO_Pos)                          /*!< MPWM FOLR: OCFO Mask                    */
#define MPWM_FOLR_PRTFO_Pos                   9                                                       /*!< MPWM FOLR: PRTFO Position               */
#define MPWM_FOLR_PRTFO_Msk                   (0x01UL << MPWM_FOLR_PRTFO_Pos)                         /*!< MPWM FOLR: PRTFO Mask                   */
#define MPWM_FOLR_SWFO_Pos                    10                                                      /*!< MPWM FOLR: SWFO Position                */
#define MPWM_FOLR_SWFO_Msk                    (0x01UL << MPWM_FOLR_SWFO_Pos)                          /*!< MPWM FOLR: SWFO Mask                    */
#define MPWM_FOLR_FOLKEY_Pos                  16                                                      /*!< MPWM FOLR: FOLKEY Position              */
#define MPWM_FOLR_FOLKEY_Msk                  (0x000000ffUL << MPWM_FOLR_FOLKEY_Pos)                  /*!< MPWM FOLR: FOLKEY Mask                  */

/* ----------------------------------  MPWM_PRD  ---------------------------------- */
#define MPWM_PRD_PERIOD_Pos                   0                                                       /*!< MPWM PRD: PERIOD Position               */
#define MPWM_PRD_PERIOD_Msk                   (0x0000ffffUL << MPWM_PRD_PERIOD_Pos)                   /*!< MPWM PRD: PERIOD Mask                   */

/* ----------------------------------  MPWM_DUH  ---------------------------------- */
#define MPWM_DUH_DUTY_UH_Pos                  0                                                       /*!< MPWM DUH: DUTY_UH Position              */
#define MPWM_DUH_DUTY_UH_Msk                  (0x0000ffffUL << MPWM_DUH_DUTY_UH_Pos)                  /*!< MPWM DUH: DUTY_UH Mask                  */

/* ----------------------------------  MPWM_DVH  ---------------------------------- */
#define MPWM_DVH_DUTY_VH_Pos                  0                                                       /*!< MPWM DVH: DUTY_VH Position              */
#define MPWM_DVH_DUTY_VH_Msk                  (0x0000ffffUL << MPWM_DVH_DUTY_VH_Pos)                  /*!< MPWM DVH: DUTY_VH Mask                  */

/* ----------------------------------  MPWM_DWH  ---------------------------------- */
#define MPWM_DWH_DUTY_WH_Pos                  0                                                       /*!< MPWM DWH: DUTY_WH Position              */
#define MPWM_DWH_DUTY_WH_Msk                  (0x0000ffffUL << MPWM_DWH_DUTY_WH_Pos)                  /*!< MPWM DWH: DUTY_WH Mask                  */

/* ----------------------------------  MPWM_DUL  ---------------------------------- */
#define MPWM_DUL_DUTY_UL_Pos                  0                                                       /*!< MPWM DUL: DUTY_UL Position              */
#define MPWM_DUL_DUTY_UL_Msk                  (0x0000ffffUL << MPWM_DUL_DUTY_UL_Pos)                  /*!< MPWM DUL: DUTY_UL Mask                  */

/* ----------------------------------  MPWM_DVL  ---------------------------------- */
#define MPWM_DVL_DUTY_VL_Pos                  0                                                       /*!< MPWM DVL: DUTY_VL Position              */
#define MPWM_DVL_DUTY_VL_Msk                  (0x0000ffffUL << MPWM_DVL_DUTY_VL_Pos)                  /*!< MPWM DVL: DUTY_VL Mask                  */

/* ----------------------------------  MPWM_DWL  ---------------------------------- */
#define MPWM_DWL_DUTY_WL_Pos                  0                                                       /*!< MPWM DWL: DUTY_WL Position              */
#define MPWM_DWL_DUTY_WL_Msk                  (0x0000ffffUL << MPWM_DWL_DUTY_WL_Pos)                  /*!< MPWM DWL: DUTY_WL Mask                  */

/* ----------------------------------  MPWM_CR1  ---------------------------------- */
#define MPWM_CR1_PWMEN_Pos                    0                                                       /*!< MPWM CR1: PWMEN Position                */
#define MPWM_CR1_PWMEN_Msk                    (0x01UL << MPWM_CR1_PWMEN_Pos)                          /*!< MPWM CR1: PWMEN Mask                    */
#define MPWM_CR1_IRQN_Pos                     8                                                       /*!< MPWM CR1: IRQN Position                 */
#define MPWM_CR1_IRQN_Msk                     (0x07UL << MPWM_CR1_IRQN_Pos)                           /*!< MPWM CR1: IRQN Mask                     */

/* ----------------------------------  MPWM_CR2  ---------------------------------- */
#define MPWM_CR2_PSTART_Pos                   0                                                       /*!< MPWM CR2: PSTART Position               */
#define MPWM_CR2_PSTART_Msk                   (0x01UL << MPWM_CR2_PSTART_Pos)                         /*!< MPWM CR2: PSTART Mask                   */
#define MPWM_CR2_HALT_Pos                     7                                                       /*!< MPWM CR2: HALT Position                 */
#define MPWM_CR2_HALT_Msk                     (0x01UL << MPWM_CR2_HALT_Pos)                           /*!< MPWM CR2: HALT Mask                     */

/* -----------------------------------  MPWM_SR  ---------------------------------- */
#define MPWM_SR_DULIF_ATR1F_Pos               0                                                       /*!< MPWM SR: DULIF_ATR1F Position           */
#define MPWM_SR_DULIF_ATR1F_Msk               (0x01UL << MPWM_SR_DULIF_ATR1F_Pos)                     /*!< MPWM SR: DULIF_ATR1F Mask               */
#define MPWM_SR_DVLIF_ATR2F_Pos               1                                                       /*!< MPWM SR: DVLIF_ATR2F Position           */
#define MPWM_SR_DVLIF_ATR2F_Msk               (0x01UL << MPWM_SR_DVLIF_ATR2F_Pos)                     /*!< MPWM SR: DVLIF_ATR2F Mask               */
#define MPWM_SR_DWLIF_ATR3F_Pos               2                                                       /*!< MPWM SR: DWLIF_ATR3F Position           */
#define MPWM_SR_DWLIF_ATR3F_Msk               (0x01UL << MPWM_SR_DWLIF_ATR3F_Pos)                     /*!< MPWM SR: DWLIF_ATR3F Mask               */
#define MPWM_SR_DUHIF_ATR4F_Pos               3                                                       /*!< MPWM SR: DUHIF_ATR4F Position           */
#define MPWM_SR_DUHIF_ATR4F_Msk               (0x01UL << MPWM_SR_DUHIF_ATR4F_Pos)                     /*!< MPWM SR: DUHIF_ATR4F Mask               */
#define MPWM_SR_DVHIF_ATR5F_Pos               4                                                       /*!< MPWM SR: DVHIF_ATR5F Position           */
#define MPWM_SR_DVHIF_ATR5F_Msk               (0x01UL << MPWM_SR_DVHIF_ATR5F_Pos)                     /*!< MPWM SR: DVHIF_ATR5F Mask               */
#define MPWM_SR_DWHIF_ATR6F_Pos               5                                                       /*!< MPWM SR: DWHIF_ATR6F Position           */
#define MPWM_SR_DWHIF_ATR6F_Msk               (0x01UL << MPWM_SR_DWHIF_ATR6F_Pos)                     /*!< MPWM SR: DWHIF_ATR6F Mask               */
#define MPWM_SR_BOTIF_Pos                     6                                                       /*!< MPWM SR: BOTIF Position                 */
#define MPWM_SR_BOTIF_Msk                     (0x01UL << MPWM_SR_BOTIF_Pos)                           /*!< MPWM SR: BOTIF Mask                     */
#define MPWM_SR_PRDIF_Pos                     7                                                       /*!< MPWM SR: PRDIF Position                 */
#define MPWM_SR_PRDIF_Msk                     (0x01UL << MPWM_SR_PRDIF_Pos)                           /*!< MPWM SR: PRDIF Mask                     */
#define MPWM_SR_IRQCNT_Pos                    12                                                      /*!< MPWM SR: IRQCNT Position                */
#define MPWM_SR_IRQCNT_Msk                    (0x07UL << MPWM_SR_IRQCNT_Pos)                          /*!< MPWM SR: IRQCNT Mask                    */
#define MPWM_SR_DOWN_Pos                      15                                                      /*!< MPWM SR: DOWN Position                  */
#define MPWM_SR_DOWN_Msk                      (0x01UL << MPWM_SR_DOWN_Pos)                            /*!< MPWM SR: DOWN Mask                      */

/* ----------------------------------  MPWM_IER  ---------------------------------- */
#define MPWM_IER_ULIE_ATR1IE_Pos              0                                                       /*!< MPWM IER: ULIE_ATR1IE Position          */
#define MPWM_IER_ULIE_ATR1IE_Msk              (0x01UL << MPWM_IER_ULIE_ATR1IE_Pos)                    /*!< MPWM IER: ULIE_ATR1IE Mask              */
#define MPWM_IER_VLIE_ATR2IE_Pos              1                                                       /*!< MPWM IER: VLIE_ATR2IE Position          */
#define MPWM_IER_VLIE_ATR2IE_Msk              (0x01UL << MPWM_IER_VLIE_ATR2IE_Pos)                    /*!< MPWM IER: VLIE_ATR2IE Mask              */
#define MPWM_IER_WLIE_ATR3IE_Pos              2                                                       /*!< MPWM IER: WLIE_ATR3IE Position          */
#define MPWM_IER_WLIE_ATR3IE_Msk              (0x01UL << MPWM_IER_WLIE_ATR3IE_Pos)                    /*!< MPWM IER: WLIE_ATR3IE Mask              */
#define MPWM_IER_UHIE_ATR4IE_Pos              3                                                       /*!< MPWM IER: UHIE_ATR4IE Position          */
#define MPWM_IER_UHIE_ATR4IE_Msk              (0x01UL << MPWM_IER_UHIE_ATR4IE_Pos)                    /*!< MPWM IER: UHIE_ATR4IE Mask              */
#define MPWM_IER_VHIE_ATR5IE_Pos              4                                                       /*!< MPWM IER: VHIE_ATR5IE Position          */
#define MPWM_IER_VHIE_ATR5IE_Msk              (0x01UL << MPWM_IER_VHIE_ATR5IE_Pos)                    /*!< MPWM IER: VHIE_ATR5IE Mask              */
#define MPWM_IER_WHIE_ATR6IE_Pos              5                                                       /*!< MPWM IER: WHIE_ATR6IE Position          */
#define MPWM_IER_WHIE_ATR6IE_Msk              (0x01UL << MPWM_IER_WHIE_ATR6IE_Pos)                    /*!< MPWM IER: WHIE_ATR6IE Mask              */
#define MPWM_IER_BOTIE_Pos                    6                                                       /*!< MPWM IER: BOTIE Position                */
#define MPWM_IER_BOTIE_Msk                    (0x01UL << MPWM_IER_BOTIE_Pos)                          /*!< MPWM IER: BOTIE Mask                    */
#define MPWM_IER_PRDIE_Pos                    7                                                       /*!< MPWM IER: PRDIE Position                */
#define MPWM_IER_PRDIE_Msk                    (0x01UL << MPWM_IER_PRDIE_Pos)                          /*!< MPWM IER: PRDIE Mask                    */

/* ----------------------------------  MPWM_CNT  ---------------------------------- */
#define MPWM_CNT_CNT_Pos                      0                                                       /*!< MPWM CNT: CNT Position                  */
#define MPWM_CNT_CNT_Msk                      (0x0000ffffUL << MPWM_CNT_CNT_Pos)                      /*!< MPWM CNT: CNT Mask                      */

/* ----------------------------------  MPWM_DTR  ---------------------------------- */
#define MPWM_DTR_LDT_Pos                      0                                                       /*!< MPWM DTR: LDT Position                  */
#define MPWM_DTR_LDT_Msk                      (0x000000ffUL << MPWM_DTR_LDT_Pos)                      /*!< MPWM DTR: LDT Mask                      */
#define MPWM_DTR_HDT_Pos                      8                                                       /*!< MPWM DTR: HDT Position                  */
#define MPWM_DTR_HDT_Msk                      (0x000000ffUL << MPWM_DTR_HDT_Pos)                      /*!< MPWM DTR: HDT Mask                      */
#define MPWM_DTR_DTCLK_Pos                    16                                                      /*!< MPWM DTR: DTCLK Position                */
#define MPWM_DTR_DTCLK_Msk                    (0x03UL << MPWM_DTR_DTCLK_Pos)                          /*!< MPWM DTR: DTCLK Mask                    */
#define MPWM_DTR_LDTOL_Pos                    20                                                      /*!< MPWM DTR: LDTOL Position                */
#define MPWM_DTR_LDTOL_Msk                    (0x01UL << MPWM_DTR_LDTOL_Pos)                          /*!< MPWM DTR: LDTOL Mask                    */
#define MPWM_DTR_HDTOL_Pos                    21                                                      /*!< MPWM DTR: HDTOL Position                */
#define MPWM_DTR_HDTOL_Msk                    (0x01UL << MPWM_DTR_HDTOL_Pos)                          /*!< MPWM DTR: HDTOL Mask                    */
#define MPWM_DTR_PSHRT_Pos                    24                                                      /*!< MPWM DTR: PSHRT Position                */
#define MPWM_DTR_PSHRT_Msk                    (0x01UL << MPWM_DTR_PSHRT_Pos)                          /*!< MPWM DTR: PSHRT Mask                    */
#define MPWM_DTR_DTEN_Pos                     25                                                      /*!< MPWM DTR: DTEN Position                 */
#define MPWM_DTR_DTEN_Msk                     (0x01UL << MPWM_DTR_DTEN_Pos)                           /*!< MPWM DTR: DTEN Mask                     */

/* ----------------------------------  MPWM_PCR  ---------------------------------- */
#define MPWM_PCR_PROT0EN_Pos                  0                                                       /*!< MPWM PCR: PROT0EN Position              */
#define MPWM_PCR_PROT0EN_Msk                  (0x01UL << MPWM_PCR_PROT0EN_Pos)                        /*!< MPWM PCR: PROT0EN Mask                  */
#define MPWM_PCR_PROT1EN_Pos                  2                                                       /*!< MPWM PCR: PROT1EN Position              */
#define MPWM_PCR_PROT1EN_Msk                  (0x01UL << MPWM_PCR_PROT1EN_Pos)                        /*!< MPWM PCR: PROT1EN Mask                  */
#define MPWM_PCR_PROT2EN_Pos                  8                                                       /*!< MPWM PCR: PROT2EN Position              */
#define MPWM_PCR_PROT2EN_Msk                  (0x01UL << MPWM_PCR_PROT2EN_Pos)                        /*!< MPWM PCR: PROT2EN Mask                  */
#define MPWM_PCR_PROT3EN_Pos                  9                                                       /*!< MPWM PCR: PROT3EN Position              */
#define MPWM_PCR_PROT3EN_Msk                  (0x01UL << MPWM_PCR_PROT3EN_Pos)                        /*!< MPWM PCR: PROT3EN Mask                  */
#define MPWM_PCR_PROTD_Pos                    16                                                      /*!< MPWM PCR: PROTD Position                */
#define MPWM_PCR_PROTD_Msk                    (0x000000ffUL << MPWM_PCR_PROTD_Pos)                    /*!< MPWM PCR: PROTD Mask                    */
#define MPWM_PCR_PROTDIV_Pos                  24                                                      /*!< MPWM PCR: PROTDIV Position              */
#define MPWM_PCR_PROTDIV_Msk                  (0x07UL << MPWM_PCR_PROTDIV_Pos)                        /*!< MPWM PCR: PROTDIV Mask                  */
#define MPWM_PCR_PROTPOL_Pos                  31                                                      /*!< MPWM PCR: PROTPOL Position              */
#define MPWM_PCR_PROTPOL_Msk                  (0x01UL << MPWM_PCR_PROTPOL_Pos)                        /*!< MPWM PCR: PROTPOL Mask                  */

/* ----------------------------------  MPWM_PSR  ---------------------------------- */
#define MPWM_PSR_PROT0IF_Pos                  0                                                       /*!< MPWM PSR: PROT0IF Position              */
#define MPWM_PSR_PROT0IF_Msk                  (0x01UL << MPWM_PSR_PROT0IF_Pos)                        /*!< MPWM PSR: PROT0IF Mask                  */
#define MPWM_PSR_PROT1IF_Pos                  2                                                       /*!< MPWM PSR: PROT1IF Position              */
#define MPWM_PSR_PROT1IF_Msk                  (0x01UL << MPWM_PSR_PROT1IF_Pos)                        /*!< MPWM PSR: PROT1IF Mask                  */
#define MPWM_PSR_PROT2IF_Pos                  8                                                       /*!< MPWM PSR: PROT2IF Position              */
#define MPWM_PSR_PROT2IF_Msk                  (0x01UL << MPWM_PSR_PROT2IF_Pos)                        /*!< MPWM PSR: PROT2IF Mask                  */
#define MPWM_PSR_PROT3IF_Pos                  9                                                       /*!< MPWM PSR: PROT3IF Position              */
#define MPWM_PSR_PROT3IF_Msk                  (0x01UL << MPWM_PSR_PROT3IF_Pos)                        /*!< MPWM PSR: PROT3IF Mask                  */

/* ----------------------------------  MPWM_OCR  ---------------------------------- */
#define MPWM_OCR_OVIN0EN_Pos                  0                                                       /*!< MPWM OCR: OVIN0EN Position              */
#define MPWM_OCR_OVIN0EN_Msk                  (0x01UL << MPWM_OCR_OVIN0EN_Pos)                        /*!< MPWM OCR: OVIN0EN Mask                  */
#define MPWM_OCR_OVIN1EN_Pos                  2                                                       /*!< MPWM OCR: OVIN1EN Position              */
#define MPWM_OCR_OVIN1EN_Msk                  (0x01UL << MPWM_OCR_OVIN1EN_Pos)                        /*!< MPWM OCR: OVIN1EN Mask                  */
#define MPWM_OCR_OVIN2EN_Pos                  8                                                       /*!< MPWM OCR: OVIN2EN Position              */
#define MPWM_OCR_OVIN2EN_Msk                  (0x01UL << MPWM_OCR_OVIN2EN_Pos)                        /*!< MPWM OCR: OVIN2EN Mask                  */
#define MPWM_OCR_OVIN3EN_Pos                  9                                                       /*!< MPWM OCR: OVIN3EN Position              */
#define MPWM_OCR_OVIN3EN_Msk                  (0x01UL << MPWM_OCR_OVIN3EN_Pos)                        /*!< MPWM OCR: OVIN3EN Mask                  */
#define MPWM_OCR_OVIND_Pos                    16                                                      /*!< MPWM OCR: OVIND Position                */
#define MPWM_OCR_OVIND_Msk                    (0x000000ffUL << MPWM_OCR_OVIND_Pos)                    /*!< MPWM OCR: OVIND Mask                    */
#define MPWM_OCR_OVINDIV_Pos                  24                                                      /*!< MPWM OCR: OVINDIV Position              */
#define MPWM_OCR_OVINDIV_Msk                  (0x07UL << MPWM_OCR_OVINDIV_Pos)                        /*!< MPWM OCR: OVINDIV Mask                  */
#define MPWM_OCR_OVINPOL_Pos                  31                                                      /*!< MPWM OCR: OVINPOL Position              */
#define MPWM_OCR_OVINPOL_Msk                  (0x01UL << MPWM_OCR_OVINPOL_Pos)                        /*!< MPWM OCR: OVINPOL Mask                  */

/* ----------------------------------  MPWM_OSR  ---------------------------------- */
#define MPWM_OSR_OVIN0IF_Pos                    0                                                       /*!< MPWM OSR: OV0IF Position                */
#define MPWM_OSR_OVIN0IF_Msk                    (0x01UL << MPWM_OSR_OVIN0IF_Pos)                          /*!< MPWM OSR: OVIN0IF Mask                    */
#define MPWM_OSR_OVIN1IF_Pos                    2                                                       /*!< MPWM OSR: OV1IF Position                */
#define MPWM_OSR_OVIN1IF_Msk                    (0x01UL << MPWM_OSR_OVIN1IF_Pos)                          /*!< MPWM OSR: OVIN1IF Mask                    */
#define MPWM_OSR_OVIN2IF_Pos                    8                                                       /*!< MPWM OSR: OV2IF Position                */
#define MPWM_OSR_OVIN2IF_Msk                    (0x01UL << MPWM_OSR_OVIN2IF_Pos)                          /*!< MPWM OSR: OVIN2IF Mask                    */
#define MPWM_OSR_OVIN3IF_Pos                    9                                                       /*!< MPWM OSR: OV3IF Position                */
#define MPWM_OSR_OVIN3IF_Msk                    (0x01UL << MPWM_OSR_OVIN3IF_Pos)                          /*!< MPWM OSR: OVIN3IF Mask                    */

/* ----------------------------------  MPWM_ATR1  --------------------------------- */
#define MPWM_ATR1_ATCNT_Pos                   0                                                       /*!< MPWM ATR1: ATCNT Position               */
#define MPWM_ATR1_ATCNT_Msk                   (0x0000ffffUL << MPWM_ATR1_ATCNT_Pos)                   /*!< MPWM ATR1: ATCNT Mask                   */
#define MPWM_ATR1_ATMOD_Pos                   16                                                      /*!< MPWM ATR1: ATMOD Position               */
#define MPWM_ATR1_ATMOD_Msk                   (0x03UL << MPWM_ATR1_ATMOD_Pos)                         /*!< MPWM ATR1: ATMOD Mask                   */
#define MPWM_ATR1_ATUDT_Pos                   19                                                      /*!< MPWM ATR1: ATUDT Position               */
#define MPWM_ATR1_ATUDT_Msk                   (0x01UL << MPWM_ATR1_ATUDT_Pos)                         /*!< MPWM ATR1: ATUDT Mask                   */

/* ----------------------------------  MPWM_ATR2  --------------------------------- */
#define MPWM_ATR2_ATCNT_Pos                   0                                                       /*!< MPWM ATR2: ATCNT Position               */
#define MPWM_ATR2_ATCNT_Msk                   (0x0000ffffUL << MPWM_ATR2_ATCNT_Pos)                   /*!< MPWM ATR2: ATCNT Mask                   */
#define MPWM_ATR2_ATMOD_Pos                   16                                                      /*!< MPWM ATR2: ATMOD Position               */
#define MPWM_ATR2_ATMOD_Msk                   (0x03UL << MPWM_ATR2_ATMOD_Pos)                         /*!< MPWM ATR2: ATMOD Mask                   */
#define MPWM_ATR2_ATUDT_Pos                   19                                                      /*!< MPWM ATR2: ATUDT Position               */
#define MPWM_ATR2_ATUDT_Msk                   (0x01UL << MPWM_ATR2_ATUDT_Pos)                         /*!< MPWM ATR2: ATUDT Mask                   */

/* ----------------------------------  MPWM_ATR3  --------------------------------- */
#define MPWM_ATR3_ATCNT_Pos                   0                                                       /*!< MPWM ATR3: ATCNT Position               */
#define MPWM_ATR3_ATCNT_Msk                   (0x0000ffffUL << MPWM_ATR3_ATCNT_Pos)                   /*!< MPWM ATR3: ATCNT Mask                   */
#define MPWM_ATR3_ATMOD_Pos                   16                                                      /*!< MPWM ATR3: ATMOD Position               */
#define MPWM_ATR3_ATMOD_Msk                   (0x03UL << MPWM_ATR3_ATMOD_Pos)                         /*!< MPWM ATR3: ATMOD Mask                   */
#define MPWM_ATR3_ATUDT_Pos                   19                                                      /*!< MPWM ATR3: ATUDT Position               */
#define MPWM_ATR3_ATUDT_Msk                   (0x01UL << MPWM_ATR3_ATUDT_Pos)                         /*!< MPWM ATR3: ATUDT Mask                   */

/* ----------------------------------  MPWM_ATR4  --------------------------------- */
#define MPWM_ATR4_ATCNT_Pos                   0                                                       /*!< MPWM ATR4: ATCNT Position               */
#define MPWM_ATR4_ATCNT_Msk                   (0x0000ffffUL << MPWM_ATR4_ATCNT_Pos)                   /*!< MPWM ATR4: ATCNT Mask                   */
#define MPWM_ATR4_ATMOD_Pos                   16                                                      /*!< MPWM ATR4: ATMOD Position               */
#define MPWM_ATR4_ATMOD_Msk                   (0x03UL << MPWM_ATR4_ATMOD_Pos)                         /*!< MPWM ATR4: ATMOD Mask                   */
#define MPWM_ATR4_ATUDT_Pos                   19                                                      /*!< MPWM ATR4: ATUDT Position               */
#define MPWM_ATR4_ATUDT_Msk                   (0x01UL << MPWM_ATR4_ATUDT_Pos)                         /*!< MPWM ATR4: ATUDT Mask                   */

/* ----------------------------------  MPWM_ATR5  --------------------------------- */
#define MPWM_ATR5_ATCNT_Pos                   0                                                       /*!< MPWM ATR5: ATCNT Position               */
#define MPWM_ATR5_ATCNT_Msk                   (0x0000ffffUL << MPWM_ATR5_ATCNT_Pos)                   /*!< MPWM ATR5: ATCNT Mask                   */
#define MPWM_ATR5_ATMOD_Pos                   16                                                      /*!< MPWM ATR5: ATMOD Position               */
#define MPWM_ATR5_ATMOD_Msk                   (0x03UL << MPWM_ATR5_ATMOD_Pos)                         /*!< MPWM ATR5: ATMOD Mask                   */
#define MPWM_ATR5_ATUDT_Pos                   19                                                      /*!< MPWM ATR5: ATUDT Position               */
#define MPWM_ATR5_ATUDT_Msk                   (0x01UL << MPWM_ATR5_ATUDT_Pos)                         /*!< MPWM ATR5: ATUDT Mask                   */

/* ----------------------------------  MPWM_ATR6  --------------------------------- */
#define MPWM_ATR6_ATCNT_Pos                   0                                                       /*!< MPWM ATR6: ATCNT Position               */
#define MPWM_ATR6_ATCNT_Msk                   (0x0000ffffUL << MPWM_ATR6_ATCNT_Pos)                   /*!< MPWM ATR6: ATCNT Mask                   */
#define MPWM_ATR6_ATMOD_Pos                   16                                                      /*!< MPWM ATR6: ATMOD Position               */
#define MPWM_ATR6_ATMOD_Msk                   (0x03UL << MPWM_ATR6_ATMOD_Pos)                         /*!< MPWM ATR6: ATMOD Mask                   */
#define MPWM_ATR6_ATUDT_Pos                   19                                                      /*!< MPWM ATR6: ATUDT Position               */
#define MPWM_ATR6_ATUDT_Msk                   (0x01UL << MPWM_ATR6_ATUDT_Pos)                         /*!< MPWM ATR6: ATUDT Mask                   */


/* ================================================================================ */
/* ================          struct 'ADC' Position & Mask          ================ */
/* ================================================================================ */


/* -----------------------------------  ADC_MR  ----------------------------------- */
#define ADC_MR_TRGSEL_Pos                     0                                                       /*!< ADC MR: TRGSEL Position                 */
#define ADC_MR_TRGSEL_Msk                     (0x03UL << ADC_MR_TRGSEL_Pos)                           /*!< ADC MR: TRGSEL Mask                     */
#define ADC_MR_ADMOD_Pos                      4                                                       /*!< ADC MR: ADMOD Position                  */
#define ADC_MR_ADMOD_Msk                      (0x03UL << ADC_MR_ADMOD_Pos)                            /*!< ADC MR: ADMOD Mask                      */
#define ADC_MR_ARST_Pos                       6                                                       /*!< ADC MR: ARST Position                   */
#define ADC_MR_ARST_Msk                       (0x01UL << ADC_MR_ARST_Pos)                             /*!< ADC MR: ARST Mask                       */
#define ADC_MR_ADEN_Pos                       7                                                       /*!< ADC MR: ADEN Position                   */
#define ADC_MR_ADEN_Msk                       (0x01UL << ADC_MR_ADEN_Pos)                             /*!< ADC MR: ADEN Mask                       */
#define ADC_MR_SEQCNT_Pos                     8                                                       /*!< ADC MR: SEQCNT Position                 */
#define ADC_MR_SEQCNT_Msk                     (0x07UL << ADC_MR_SEQCNT_Pos)                           /*!< ADC MR: SEQCNT Mask                     */
#define ADC_MR_SEQTRGT_Pos                    11                                                      /*!< ADC MR: SEQTRGT Position                */
#define ADC_MR_SEQTRGT_Msk                    (0x01UL << ADC_MR_SEQTRGT_Pos)                          /*!< ADC MR: SEQTRGT Mask                    */
#define ADC_MR_DMAEN_Pos                      17                                                      /*!< ADC MR: DMAEN Position                  */
#define ADC_MR_DMAEN_Msk                      (0x01UL << ADC_MR_DMAEN_Pos)                            /*!< ADC MR: DMAEN Mask                      */
#define ADC_MR_DMAIDE_Pos                     18                                                      /*!< ADC MR: DMAIDE Position                 */
#define ADC_MR_DMAIDE_Msk                     (0x01UL << ADC_MR_DMAIDE_Pos)                           /*!< ADC MR: DMAIDE Mask                     */
#define ADC_MR_CDATAT_Pos                     19                                                      /*!< ADC MR: CDATAT Position                 */
#define ADC_MR_CDATAT_Msk                     (0x01UL << ADC_MR_CDATAT_Pos)                           /*!< ADC MR: CDATAT Mask                     */
#define ADC_MR_CTIMELAT_Pos                   24                                                      /*!< ADC MR: CTIMELAT Position               */
#define ADC_MR_CTIMELAT_Msk                   (0x07UL << ADC_MR_CTIMELAT_Pos)                         /*!< ADC MR: CTIMELAT Mask                   */

/* ----------------------------------  ADC_CSCR  ---------------------------------- */
#define ADC_CSCR_CACH_Pos                     0                                                       /*!< ADC CSCR: CACH Position                 */
#define ADC_CSCR_CACH_Msk                     (0x1fUL << ADC_CSCR_CACH_Pos)                           /*!< ADC CSCR: CACH Mask                     */
#define ADC_CSCR_CSEQN_Pos                    8                                                       /*!< ADC CSCR: CSEQN Position                */
#define ADC_CSCR_CSEQN_Msk                    (0x07UL << ADC_CSCR_CSEQN_Pos)                          /*!< ADC CSCR: CSEQN Mask                    */

/* -----------------------------------  ADC_CCR  ---------------------------------- */
#define ADC_CCR_CLKDIV_Pos                    8                                                       /*!< ADC CCR: CLKDIV Position                */
#define ADC_CCR_CLKDIV_Msk                    (0x7fUL << ADC_CCR_CLKDIV_Pos)                          /*!< ADC CCR: CLKDIV Mask                    */

/* -----------------------------------  ADC_TRG  ---------------------------------- */
#define ADC_TRG_SEQTRG0_BSTTRG_Pos            0                                                       /*!< ADC TRG: SEQTRG0_BSTTRG Position        */
#define ADC_TRG_SEQTRG0_BSTTRG_Msk            (0x0fUL << ADC_TRG_SEQTRG0_BSTTRG_Pos)                  /*!< ADC TRG: SEQTRG0_BSTTRG Mask            */
#define ADC_TRG_SEQTRG1_Pos                   4                                                       /*!< ADC TRG: SEQTRG1 Position               */
#define ADC_TRG_SEQTRG1_Msk                   (0x0fUL << ADC_TRG_SEQTRG1_Pos)                         /*!< ADC TRG: SEQTRG1 Mask                   */
#define ADC_TRG_SEQTRG2_Pos                   8                                                       /*!< ADC TRG: SEQTRG2 Position               */
#define ADC_TRG_SEQTRG2_Msk                   (0x0fUL << ADC_TRG_SEQTRG2_Pos)                         /*!< ADC TRG: SEQTRG2 Mask                   */
#define ADC_TRG_SEQTRG3_Pos                   12                                                      /*!< ADC TRG: SEQTRG3 Position               */
#define ADC_TRG_SEQTRG3_Msk                   (0x0fUL << ADC_TRG_SEQTRG3_Pos)                         /*!< ADC TRG: SEQTRG3 Mask                   */
#define ADC_TRG_SEQTRG4_Pos                   16                                                      /*!< ADC TRG: SEQTRG4 Position               */
#define ADC_TRG_SEQTRG4_Msk                   (0x0fUL << ADC_TRG_SEQTRG4_Pos)                         /*!< ADC TRG: SEQTRG4 Mask                   */
#define ADC_TRG_SEQTRG5_Pos                   20                                                      /*!< ADC TRG: SEQTRG5 Position               */
#define ADC_TRG_SEQTRG5_Msk                   (0x0fUL << ADC_TRG_SEQTRG5_Pos)                         /*!< ADC TRG: SEQTRG5 Mask                   */
#define ADC_TRG_SEQTRG6_Pos                   24                                                      /*!< ADC TRG: SEQTRG6 Position               */
#define ADC_TRG_SEQTRG6_Msk                   (0x0fUL << ADC_TRG_SEQTRG6_Pos)                         /*!< ADC TRG: SEQTRG6 Mask                   */
#define ADC_TRG_SEQTRG7_Pos                   28                                                      /*!< ADC TRG: SEQTRG7 Position               */
#define ADC_TRG_SEQTRG7_Msk                   (0x0fUL << ADC_TRG_SEQTRG7_Pos)                         /*!< ADC TRG: SEQTRG7 Mask                   */

/* ----------------------------------  ADC_CSTR1  --------------------------------- */
#define ADC_CSTR1_ST0CH_Pos                   0                                                       /*!< ADC CSTR1: ST0CH Position               */
#define ADC_CSTR1_ST0CH_Msk                   (0x1fUL << ADC_CSTR1_ST0CH_Pos)                         /*!< ADC CSTR1: ST0CH Mask                   */
#define ADC_CSTR1_ST1CH_Pos                   8                                                       /*!< ADC CSTR1: ST1CH Position               */
#define ADC_CSTR1_ST1CH_Msk                   (0x1fUL << ADC_CSTR1_ST1CH_Pos)                         /*!< ADC CSTR1: ST1CH Mask                   */
#define ADC_CSTR1_ST2CH_Pos                   16                                                      /*!< ADC CSTR1: ST2CH Position               */
#define ADC_CSTR1_ST2CH_Msk                   (0x1fUL << ADC_CSTR1_ST2CH_Pos)                         /*!< ADC CSTR1: ST2CH Mask                   */
#define ADC_CSTR1_ST3CH_Pos                   24                                                      /*!< ADC CSTR1: ST3CH Position               */
#define ADC_CSTR1_ST3CH_Msk                   (0x1fUL << ADC_CSTR1_ST3CH_Pos)                         /*!< ADC CSTR1: ST3CH Mask                   */

/* ----------------------------------  ADC_CSTR2  --------------------------------- */
#define ADC_CSTR2_ST4CH_Pos                   0                                                       /*!< ADC CSTR2: ST4CH Position               */
#define ADC_CSTR2_ST4CH_Msk                   (0x1fUL << ADC_CSTR2_ST4CH_Pos)                         /*!< ADC CSTR2: ST4CH Mask                   */
#define ADC_CSTR2_ST5CH_Pos                   8                                                       /*!< ADC CSTR2: ST5CH Position               */
#define ADC_CSTR2_ST5CH_Msk                   (0x1fUL << ADC_CSTR2_ST5CH_Pos)                         /*!< ADC CSTR2: ST5CH Mask                   */
#define ADC_CSTR2_ST6CH_Pos                   16                                                      /*!< ADC CSTR2: ST6CH Position               */
#define ADC_CSTR2_ST6CH_Msk                   (0x1fUL << ADC_CSTR2_ST6CH_Pos)                         /*!< ADC CSTR2: ST6CH Mask                   */
#define ADC_CSTR2_ST7CH_Pos                   24                                                      /*!< ADC CSTR2: ST7CH Position               */
#define ADC_CSTR2_ST7CH_Msk                   (0x1fUL << ADC_CSTR2_ST7CH_Pos)                         /*!< ADC CSTR2: ST7CH Mask                   */

/* ----------------------------------  ADC_SCSR1  --------------------------------- */
#define ADC_SCSR1_SEQ0CH_Pos                  0                                                       /*!< ADC SCSR1: SEQ0CH Position              */
#define ADC_SCSR1_SEQ0CH_Msk                  (0x1fUL << ADC_SCSR1_SEQ0CH_Pos)                        /*!< ADC SCSR1: SEQ0CH Mask                  */
#define ADC_SCSR1_SEQ1CH_Pos                  8                                                       /*!< ADC SCSR1: SEQ1CH Position              */
#define ADC_SCSR1_SEQ1CH_Msk                  (0x1fUL << ADC_SCSR1_SEQ1CH_Pos)                        /*!< ADC SCSR1: SEQ1CH Mask                  */
#define ADC_SCSR1_SEQ2CH_Pos                  16                                                      /*!< ADC SCSR1: SEQ2CH Position              */
#define ADC_SCSR1_SEQ2CH_Msk                  (0x1fUL << ADC_SCSR1_SEQ2CH_Pos)                        /*!< ADC SCSR1: SEQ2CH Mask                  */
#define ADC_SCSR1_SEQ3CH_Pos                  24                                                      /*!< ADC SCSR1: SEQ3CH Position              */
#define ADC_SCSR1_SEQ3CH_Msk                  (0x1fUL << ADC_SCSR1_SEQ3CH_Pos)                        /*!< ADC SCSR1: SEQ3CH Mask                  */

/* ----------------------------------  ADC_SCSR2  --------------------------------- */
#define ADC_SCSR2_SEQ4CH_Pos                  0                                                       /*!< ADC SCSR2: SEQ4CH Position              */
#define ADC_SCSR2_SEQ4CH_Msk                  (0x1fUL << ADC_SCSR2_SEQ4CH_Pos)                        /*!< ADC SCSR2: SEQ4CH Mask                  */
#define ADC_SCSR2_SEQ5CH_Pos                  8                                                       /*!< ADC SCSR2: SEQ5CH Position              */
#define ADC_SCSR2_SEQ5CH_Msk                  (0x1fUL << ADC_SCSR2_SEQ5CH_Pos)                        /*!< ADC SCSR2: SEQ5CH Mask                  */
#define ADC_SCSR2_SEQ6CH_Pos                  16                                                      /*!< ADC SCSR2: SEQ6CH Position              */
#define ADC_SCSR2_SEQ6CH_Msk                  (0x1fUL << ADC_SCSR2_SEQ6CH_Pos)                        /*!< ADC SCSR2: SEQ6CH Mask                  */
#define ADC_SCSR2_SEQ7CH_Pos                  24                                                      /*!< ADC SCSR2: SEQ7CH Position              */
#define ADC_SCSR2_SEQ7CH_Msk                  (0x1fUL << ADC_SCSR2_SEQ7CH_Pos)                        /*!< ADC SCSR2: SEQ7CH Mask                  */

/* -----------------------------------  ADC_CR  ----------------------------------- */
#define ADC_CR_ASTART_Pos                     0                                                       /*!< ADC CR: ASTART Position                 */
#define ADC_CR_ASTART_Msk                     (0x01UL << ADC_CR_ASTART_Pos)                           /*!< ADC CR: ASTART Mask                     */
#define ADC_CR_TRGCLR_Pos                     1                                                       /*!< ADC CR: TRGCLR Position                 */
#define ADC_CR_TRGCLR_Msk                     (0x01UL << ADC_CR_TRGCLR_Pos)                           /*!< ADC CR: TRGCLR Mask                     */
#define ADC_CR_ASTOP_Pos                      7                                                       /*!< ADC CR: ASTOP Position                  */
#define ADC_CR_ASTOP_Msk                      (0x01UL << ADC_CR_ASTOP_Pos)                            /*!< ADC CR: ASTOP Mask                      */

/* -----------------------------------  ADC_SR  ----------------------------------- */
#define ADC_SR_EOCIF_Pos                      0                                                       /*!< ADC SR: EOCIF Position                  */
#define ADC_SR_EOCIF_Msk                      (0x01UL << ADC_SR_EOCIF_Pos)                            /*!< ADC SR: EOCIF Mask                      */
#define ADC_SR_IOCIF_Pos                      1                                                       /*!< ADC SR: IOCIF Position                  */
#define ADC_SR_IOCIF_Msk                      (0x01UL << ADC_SR_IOCIF_Pos)                            /*!< ADC SR: IOCIF Mask                      */
#define ADC_SR_EOSIF_Pos                      2                                                       /*!< ADC SR: EOSIF Position                  */
#define ADC_SR_EOSIF_Msk                      (0x01UL << ADC_SR_EOSIF_Pos)                            /*!< ADC SR: EOSIF Mask                      */
#define ADC_SR_TRGIF_Pos                      3                                                       /*!< ADC SR: TRGIF Position                  */
#define ADC_SR_TRGIF_Msk                      (0x01UL << ADC_SR_TRGIF_Pos)                            /*!< ADC SR: TRGIF Mask                      */
#define ADC_SR_DMAF_Pos                       4                                                       /*!< ADC SR: DMAF Position                   */
#define ADC_SR_DMAF_Msk                       (0x01UL << ADC_SR_DMAF_Pos)                             /*!< ADC SR: DMAF Mask                       */
#define ADC_SR_DOVRUN_Pos                     5                                                       /*!< ADC SR: DOVRUN Position                 */
#define ADC_SR_DOVRUN_Msk                     (0x01UL << ADC_SR_DOVRUN_Pos)                           /*!< ADC SR: DOVRUN Mask                     */
#define ADC_SR_CMP0IF_Pos                     8                                                       /*!< ADC SR: CMP0IF Position                 */
#define ADC_SR_CMP0IF_Msk                     (0x01UL << ADC_SR_CMP0IF_Pos)                           /*!< ADC SR: CMP0IF Mask                     */
#define ADC_SR_CMP1IF_Pos                     9                                                       /*!< ADC SR: CMP1IF Position                 */
#define ADC_SR_CMP1IF_Msk                     (0x01UL << ADC_SR_CMP1IF_Pos)                           /*!< ADC SR: CMP1IF Mask                     */
#define ADC_SR_ABUSY_Pos                      16                                                      /*!< ADC SR: ABUSY Position                  */
#define ADC_SR_ABUSY_Msk                      (0x01UL << ADC_SR_ABUSY_Pos)                            /*!< ADC SR: ABUSY Mask                      */

/* -----------------------------------  ADC_IER  ---------------------------------- */
#define ADC_IER_EOCIE_Pos                     0                                                       /*!< ADC IER: EOCIE Position                 */
#define ADC_IER_EOCIE_Msk                     (0x01UL << ADC_IER_EOCIE_Pos)                           /*!< ADC IER: EOCIE Mask                     */
#define ADC_IER_IOCIE_Pos                     1                                                       /*!< ADC IER: IOCIE Position                 */
#define ADC_IER_IOCIE_Msk                     (0x01UL << ADC_IER_IOCIE_Pos)                           /*!< ADC IER: IOCIE Mask                     */
#define ADC_IER_EOSIE_Pos                     2                                                       /*!< ADC IER: EOSIE Position                 */
#define ADC_IER_EOSIE_Msk                     (0x01UL << ADC_IER_EOSIE_Pos)                           /*!< ADC IER: EOSIE Mask                     */
#define ADC_IER_TRGIE_Pos                     3                                                       /*!< ADC IER: TRGIE Position                 */
#define ADC_IER_TRGIE_Msk                     (0x01UL << ADC_IER_TRGIE_Pos)                           /*!< ADC IER: TRGIE Mask                     */
#define ADC_IER_DMAIE_Pos                     4                                                       /*!< ADC IER: DMAIE Position                 */
#define ADC_IER_DMAIE_Msk                     (0x01UL << ADC_IER_DMAIE_Pos)                           /*!< ADC IER: DMAIE Mask                     */
#define ADC_IER_CMP0IE_Pos                    8                                                       /*!< ADC IER: CMP0IE Position                */
#define ADC_IER_CMP0IE_Msk                    (0x01UL << ADC_IER_CMP0IE_Pos)                          /*!< ADC IER: CMP0IE Mask                    */
#define ADC_IER_CMP1IE_Pos                    9                                                       /*!< ADC IER: CMP1IE Position                */
#define ADC_IER_CMP1IE_Msk                    (0x01UL << ADC_IER_CMP1IE_Pos)                          /*!< ADC IER: CMP1IE Mask                    */

/* -----------------------------------  ADC_DDR  ---------------------------------- */
#define ADC_DDR_ADDMAR_Pos                    4                                                       /*!< ADC DDR: ADDMAR Position                */
#define ADC_DDR_ADDMAR_Msk                    (0x00000fffUL << ADC_DDR_ADDMAR_Pos)                    /*!< ADC DDR: ADDMAR Mask                    */
#define ADC_DDR_ADMACH_Pos                    16                                                      /*!< ADC DDR: ADMACH Position                */
#define ADC_DDR_ADMACH_Msk                    (0x1fUL << ADC_DDR_ADMACH_Pos)                          /*!< ADC DDR: ADMACH Mask                    */
#define ADC_DDR_ITRG_Pos                      23                                                      /*!< ADC DDR: ITRG Position                  */
#define ADC_DDR_ITRG_Msk                      (0x01UL << ADC_DDR_ITRG_Pos)                            /*!< ADC DDR: ITRG Mask                      */
#define ADC_DDR_TRGINFO0_Pos                  24                                                      /*!< ADC DDR: TRGINFO0 Position              */
#define ADC_DDR_TRGINFO0_Msk                  (0x01UL << ADC_DDR_TRGINFO0_Pos)                        /*!< ADC DDR: TRGINFO0 Mask                  */
#define ADC_DDR_TRGINFO1_Pos                  25                                                      /*!< ADC DDR: TRGINFO1 Position              */
#define ADC_DDR_TRGINFO1_Msk                  (0x01UL << ADC_DDR_TRGINFO1_Pos)                        /*!< ADC DDR: TRGINFO1 Mask                  */
#define ADC_DDR_TRGINFO2_Pos                  26                                                      /*!< ADC DDR: TRGINFO2 Position              */
#define ADC_DDR_TRGINFO2_Msk                  (0x01UL << ADC_DDR_TRGINFO2_Pos)                        /*!< ADC DDR: TRGINFO2 Mask                  */
#define ADC_DDR_TRGINFO3_Pos                  27                                                      /*!< ADC DDR: TRGINFO3 Position              */
#define ADC_DDR_TRGINFO3_Msk                  (0x01UL << ADC_DDR_TRGINFO3_Pos)                        /*!< ADC DDR: TRGINFO3 Mask                  */
#define ADC_DDR_TRGINFO4_Pos                  28                                                      /*!< ADC DDR: TRGINFO4 Position              */
#define ADC_DDR_TRGINFO4_Msk                  (0x01UL << ADC_DDR_TRGINFO4_Pos)                        /*!< ADC DDR: TRGINFO4 Mask                  */
#define ADC_DDR_TRGINFO5_Pos                  29                                                      /*!< ADC DDR: TRGINFO5 Position              */
#define ADC_DDR_TRGINFO5_Msk                  (0x01UL << ADC_DDR_TRGINFO5_Pos)                        /*!< ADC DDR: TRGINFO5 Mask                  */
#define ADC_DDR_TRGINFO6_Pos                  30                                                      /*!< ADC DDR: TRGINFO6 Position              */
#define ADC_DDR_TRGINFO6_Msk                  (0x01UL << ADC_DDR_TRGINFO6_Pos)                        /*!< ADC DDR: TRGINFO6 Mask                  */
#define ADC_DDR_TRGINFO7_Pos                  31                                                      /*!< ADC DDR: TRGINFO7 Position              */
#define ADC_DDR_TRGINFO7_Msk                  (0x01UL << ADC_DDR_TRGINFO7_Pos)                        /*!< ADC DDR: TRGINFO7 Mask                  */

/* -----------------------------------  ADC_DR0  ---------------------------------- */
#define ADC_DR0_ADDATA_Pos                    4                                                       /*!< ADC DR0: ADDATA Position                */
#define ADC_DR0_ADDATA_Msk                    (0x00000fffUL << ADC_DR0_ADDATA_Pos)                    /*!< ADC DR0: ADDATA Mask                    */
#define ADC_DR0_ACH_Pos                       16                                                      /*!< ADC DR0: ACH Position                   */
#define ADC_DR0_ACH_Msk                       (0x1fUL << ADC_DR0_ACH_Pos)                             /*!< ADC DR0: ACH Mask                       */
#define ADC_DR0_TRGINFO0_Pos                  24                                                      /*!< ADC DR0: TRGINFO0 Position              */
#define ADC_DR0_TRGINFO0_Msk                  (0x01UL << ADC_DR0_TRGINFO0_Pos)                        /*!< ADC DR0: TRGINFO0 Mask                  */
#define ADC_DR0_TRGINFO1_Pos                  25                                                      /*!< ADC DR0: TRGINFO1 Position              */
#define ADC_DR0_TRGINFO1_Msk                  (0x01UL << ADC_DR0_TRGINFO1_Pos)                        /*!< ADC DR0: TRGINFO1 Mask                  */
#define ADC_DR0_TRGINFO2_Pos                  26                                                      /*!< ADC DR0: TRGINFO2 Position              */
#define ADC_DR0_TRGINFO2_Msk                  (0x01UL << ADC_DR0_TRGINFO2_Pos)                        /*!< ADC DR0: TRGINFO2 Mask                  */
#define ADC_DR0_TRGINFO3_Pos                  27                                                      /*!< ADC DR0: TRGINFO3 Position              */
#define ADC_DR0_TRGINFO3_Msk                  (0x01UL << ADC_DR0_TRGINFO3_Pos)                        /*!< ADC DR0: TRGINFO3 Mask                  */
#define ADC_DR0_TRGINFO4_Pos                  28                                                      /*!< ADC DR0: TRGINFO4 Position              */
#define ADC_DR0_TRGINFO4_Msk                  (0x01UL << ADC_DR0_TRGINFO4_Pos)                        /*!< ADC DR0: TRGINFO4 Mask                  */
#define ADC_DR0_TRGINFO5_Pos                  29                                                      /*!< ADC DR0: TRGINFO5 Position              */
#define ADC_DR0_TRGINFO5_Msk                  (0x01UL << ADC_DR0_TRGINFO5_Pos)                        /*!< ADC DR0: TRGINFO5 Mask                  */
#define ADC_DR0_TRGINFO6_Pos                  30                                                      /*!< ADC DR0: TRGINFO6 Position              */
#define ADC_DR0_TRGINFO6_Msk                  (0x01UL << ADC_DR0_TRGINFO6_Pos)                        /*!< ADC DR0: TRGINFO6 Mask                  */
#define ADC_DR0_TRGINFO7_Pos                  31                                                      /*!< ADC DR0: TRGINFO7 Position              */
#define ADC_DR0_TRGINFO7_Msk                  (0x01UL << ADC_DR0_TRGINFO7_Pos)                        /*!< ADC DR0: TRGINFO7 Mask                  */

/* -----------------------------------  ADC_DR1  ---------------------------------- */
#define ADC_DR1_ADDATA_Pos                    4                                                       /*!< ADC DR1: ADDATA Position                */
#define ADC_DR1_ADDATA_Msk                    (0x00000fffUL << ADC_DR1_ADDATA_Pos)                    /*!< ADC DR1: ADDATA Mask                    */
#define ADC_DR1_ACH_Pos                       16                                                      /*!< ADC DR1: ACH Position                   */
#define ADC_DR1_ACH_Msk                       (0x1fUL << ADC_DR1_ACH_Pos)                             /*!< ADC DR1: ACH Mask                       */
#define ADC_DR1_TRGINFO0_Pos                  24                                                      /*!< ADC DR1: TRGINFO0 Position              */
#define ADC_DR1_TRGINFO0_Msk                  (0x01UL << ADC_DR1_TRGINFO0_Pos)                        /*!< ADC DR1: TRGINFO0 Mask                  */
#define ADC_DR1_TRGINFO1_Pos                  25                                                      /*!< ADC DR1: TRGINFO1 Position              */
#define ADC_DR1_TRGINFO1_Msk                  (0x01UL << ADC_DR1_TRGINFO1_Pos)                        /*!< ADC DR1: TRGINFO1 Mask                  */
#define ADC_DR1_TRGINFO2_Pos                  26                                                      /*!< ADC DR1: TRGINFO2 Position              */
#define ADC_DR1_TRGINFO2_Msk                  (0x01UL << ADC_DR1_TRGINFO2_Pos)                        /*!< ADC DR1: TRGINFO2 Mask                  */
#define ADC_DR1_TRGINFO3_Pos                  27                                                      /*!< ADC DR1: TRGINFO3 Position              */
#define ADC_DR1_TRGINFO3_Msk                  (0x01UL << ADC_DR1_TRGINFO3_Pos)                        /*!< ADC DR1: TRGINFO3 Mask                  */
#define ADC_DR1_TRGINFO4_Pos                  28                                                      /*!< ADC DR1: TRGINFO4 Position              */
#define ADC_DR1_TRGINFO4_Msk                  (0x01UL << ADC_DR1_TRGINFO4_Pos)                        /*!< ADC DR1: TRGINFO4 Mask                  */
#define ADC_DR1_TRGINFO5_Pos                  29                                                      /*!< ADC DR1: TRGINFO5 Position              */
#define ADC_DR1_TRGINFO5_Msk                  (0x01UL << ADC_DR1_TRGINFO5_Pos)                        /*!< ADC DR1: TRGINFO5 Mask                  */
#define ADC_DR1_TRGINFO6_Pos                  30                                                      /*!< ADC DR1: TRGINFO6 Position              */
#define ADC_DR1_TRGINFO6_Msk                  (0x01UL << ADC_DR1_TRGINFO6_Pos)                        /*!< ADC DR1: TRGINFO6 Mask                  */
#define ADC_DR1_TRGINFO7_Pos                  31                                                      /*!< ADC DR1: TRGINFO7 Position              */
#define ADC_DR1_TRGINFO7_Msk                  (0x01UL << ADC_DR1_TRGINFO7_Pos)                        /*!< ADC DR1: TRGINFO7 Mask                  */

/* -----------------------------------  ADC_DR2  ---------------------------------- */
#define ADC_DR2_ADDATA_Pos                    4                                                       /*!< ADC DR2: ADDATA Position                */
#define ADC_DR2_ADDATA_Msk                    (0x00000fffUL << ADC_DR2_ADDATA_Pos)                    /*!< ADC DR2: ADDATA Mask                    */
#define ADC_DR2_ACH_Pos                       16                                                      /*!< ADC DR2: ACH Position                   */
#define ADC_DR2_ACH_Msk                       (0x1fUL << ADC_DR2_ACH_Pos)                             /*!< ADC DR2: ACH Mask                       */
#define ADC_DR2_TRGINFO0_Pos                  24                                                      /*!< ADC DR2: TRGINFO0 Position              */
#define ADC_DR2_TRGINFO0_Msk                  (0x01UL << ADC_DR2_TRGINFO0_Pos)                        /*!< ADC DR2: TRGINFO0 Mask                  */
#define ADC_DR2_TRGINFO1_Pos                  25                                                      /*!< ADC DR2: TRGINFO1 Position              */
#define ADC_DR2_TRGINFO1_Msk                  (0x01UL << ADC_DR2_TRGINFO1_Pos)                        /*!< ADC DR2: TRGINFO1 Mask                  */
#define ADC_DR2_TRGINFO2_Pos                  26                                                      /*!< ADC DR2: TRGINFO2 Position              */
#define ADC_DR2_TRGINFO2_Msk                  (0x01UL << ADC_DR2_TRGINFO2_Pos)                        /*!< ADC DR2: TRGINFO2 Mask                  */
#define ADC_DR2_TRGINFO3_Pos                  27                                                      /*!< ADC DR2: TRGINFO3 Position              */
#define ADC_DR2_TRGINFO3_Msk                  (0x01UL << ADC_DR2_TRGINFO3_Pos)                        /*!< ADC DR2: TRGINFO3 Mask                  */
#define ADC_DR2_TRGINFO4_Pos                  28                                                      /*!< ADC DR2: TRGINFO4 Position              */
#define ADC_DR2_TRGINFO4_Msk                  (0x01UL << ADC_DR2_TRGINFO4_Pos)                        /*!< ADC DR2: TRGINFO4 Mask                  */
#define ADC_DR2_TRGINFO5_Pos                  29                                                      /*!< ADC DR2: TRGINFO5 Position              */
#define ADC_DR2_TRGINFO5_Msk                  (0x01UL << ADC_DR2_TRGINFO5_Pos)                        /*!< ADC DR2: TRGINFO5 Mask                  */
#define ADC_DR2_TRGINFO6_Pos                  30                                                      /*!< ADC DR2: TRGINFO6 Position              */
#define ADC_DR2_TRGINFO6_Msk                  (0x01UL << ADC_DR2_TRGINFO6_Pos)                        /*!< ADC DR2: TRGINFO6 Mask                  */
#define ADC_DR2_TRGINFO7_Pos                  31                                                      /*!< ADC DR2: TRGINFO7 Position              */
#define ADC_DR2_TRGINFO7_Msk                  (0x01UL << ADC_DR2_TRGINFO7_Pos)                        /*!< ADC DR2: TRGINFO7 Mask                  */

/* -----------------------------------  ADC_DR3  ---------------------------------- */
#define ADC_DR3_ADDATA_Pos                    4                                                       /*!< ADC DR3: ADDATA Position                */
#define ADC_DR3_ADDATA_Msk                    (0x00000fffUL << ADC_DR3_ADDATA_Pos)                    /*!< ADC DR3: ADDATA Mask                    */
#define ADC_DR3_ACH_Pos                       16                                                      /*!< ADC DR3: ACH Position                   */
#define ADC_DR3_ACH_Msk                       (0x1fUL << ADC_DR3_ACH_Pos)                             /*!< ADC DR3: ACH Mask                       */
#define ADC_DR3_TRGINFO0_Pos                  24                                                      /*!< ADC DR3: TRGINFO0 Position              */
#define ADC_DR3_TRGINFO0_Msk                  (0x01UL << ADC_DR3_TRGINFO0_Pos)                        /*!< ADC DR3: TRGINFO0 Mask                  */
#define ADC_DR3_TRGINFO1_Pos                  25                                                      /*!< ADC DR3: TRGINFO1 Position              */
#define ADC_DR3_TRGINFO1_Msk                  (0x01UL << ADC_DR3_TRGINFO1_Pos)                        /*!< ADC DR3: TRGINFO1 Mask                  */
#define ADC_DR3_TRGINFO2_Pos                  26                                                      /*!< ADC DR3: TRGINFO2 Position              */
#define ADC_DR3_TRGINFO2_Msk                  (0x01UL << ADC_DR3_TRGINFO2_Pos)                        /*!< ADC DR3: TRGINFO2 Mask                  */
#define ADC_DR3_TRGINFO3_Pos                  27                                                      /*!< ADC DR3: TRGINFO3 Position              */
#define ADC_DR3_TRGINFO3_Msk                  (0x01UL << ADC_DR3_TRGINFO3_Pos)                        /*!< ADC DR3: TRGINFO3 Mask                  */
#define ADC_DR3_TRGINFO4_Pos                  28                                                      /*!< ADC DR3: TRGINFO4 Position              */
#define ADC_DR3_TRGINFO4_Msk                  (0x01UL << ADC_DR3_TRGINFO4_Pos)                        /*!< ADC DR3: TRGINFO4 Mask                  */
#define ADC_DR3_TRGINFO5_Pos                  29                                                      /*!< ADC DR3: TRGINFO5 Position              */
#define ADC_DR3_TRGINFO5_Msk                  (0x01UL << ADC_DR3_TRGINFO5_Pos)                        /*!< ADC DR3: TRGINFO5 Mask                  */
#define ADC_DR3_TRGINFO6_Pos                  30                                                      /*!< ADC DR3: TRGINFO6 Position              */
#define ADC_DR3_TRGINFO6_Msk                  (0x01UL << ADC_DR3_TRGINFO6_Pos)                        /*!< ADC DR3: TRGINFO6 Mask                  */
#define ADC_DR3_TRGINFO7_Pos                  31                                                      /*!< ADC DR3: TRGINFO7 Position              */
#define ADC_DR3_TRGINFO7_Msk                  (0x01UL << ADC_DR3_TRGINFO7_Pos)                        /*!< ADC DR3: TRGINFO7 Mask                  */

/* -----------------------------------  ADC_DR4  ---------------------------------- */
#define ADC_DR4_ADDATA_Pos                    4                                                       /*!< ADC DR4: ADDATA Position                */
#define ADC_DR4_ADDATA_Msk                    (0x00000fffUL << ADC_DR4_ADDATA_Pos)                    /*!< ADC DR4: ADDATA Mask                    */
#define ADC_DR4_ACH_Pos                       16                                                      /*!< ADC DR4: ACH Position                   */
#define ADC_DR4_ACH_Msk                       (0x1fUL << ADC_DR4_ACH_Pos)                             /*!< ADC DR4: ACH Mask                       */
#define ADC_DR4_TRGINFO0_Pos                  24                                                      /*!< ADC DR4: TRGINFO0 Position              */
#define ADC_DR4_TRGINFO0_Msk                  (0x01UL << ADC_DR4_TRGINFO0_Pos)                        /*!< ADC DR4: TRGINFO0 Mask                  */
#define ADC_DR4_TRGINFO1_Pos                  25                                                      /*!< ADC DR4: TRGINFO1 Position              */
#define ADC_DR4_TRGINFO1_Msk                  (0x01UL << ADC_DR4_TRGINFO1_Pos)                        /*!< ADC DR4: TRGINFO1 Mask                  */
#define ADC_DR4_TRGINFO2_Pos                  26                                                      /*!< ADC DR4: TRGINFO2 Position              */
#define ADC_DR4_TRGINFO2_Msk                  (0x01UL << ADC_DR4_TRGINFO2_Pos)                        /*!< ADC DR4: TRGINFO2 Mask                  */
#define ADC_DR4_TRGINFO3_Pos                  27                                                      /*!< ADC DR4: TRGINFO3 Position              */
#define ADC_DR4_TRGINFO3_Msk                  (0x01UL << ADC_DR4_TRGINFO3_Pos)                        /*!< ADC DR4: TRGINFO3 Mask                  */
#define ADC_DR4_TRGINFO4_Pos                  28                                                      /*!< ADC DR4: TRGINFO4 Position              */
#define ADC_DR4_TRGINFO4_Msk                  (0x01UL << ADC_DR4_TRGINFO4_Pos)                        /*!< ADC DR4: TRGINFO4 Mask                  */
#define ADC_DR4_TRGINFO5_Pos                  29                                                      /*!< ADC DR4: TRGINFO5 Position              */
#define ADC_DR4_TRGINFO5_Msk                  (0x01UL << ADC_DR4_TRGINFO5_Pos)                        /*!< ADC DR4: TRGINFO5 Mask                  */
#define ADC_DR4_TRGINFO6_Pos                  30                                                      /*!< ADC DR4: TRGINFO6 Position              */
#define ADC_DR4_TRGINFO6_Msk                  (0x01UL << ADC_DR4_TRGINFO6_Pos)                        /*!< ADC DR4: TRGINFO6 Mask                  */
#define ADC_DR4_TRGINFO7_Pos                  31                                                      /*!< ADC DR4: TRGINFO7 Position              */
#define ADC_DR4_TRGINFO7_Msk                  (0x01UL << ADC_DR4_TRGINFO7_Pos)                        /*!< ADC DR4: TRGINFO7 Mask                  */

/* -----------------------------------  ADC_DR5  ---------------------------------- */
#define ADC_DR5_ADDATA_Pos                    4                                                       /*!< ADC DR5: ADDATA Position                */
#define ADC_DR5_ADDATA_Msk                    (0x00000fffUL << ADC_DR5_ADDATA_Pos)                    /*!< ADC DR5: ADDATA Mask                    */
#define ADC_DR5_ACH_Pos                       16                                                      /*!< ADC DR5: ACH Position                   */
#define ADC_DR5_ACH_Msk                       (0x1fUL << ADC_DR5_ACH_Pos)                             /*!< ADC DR5: ACH Mask                       */
#define ADC_DR5_TRGINFO0_Pos                  24                                                      /*!< ADC DR5: TRGINFO0 Position              */
#define ADC_DR5_TRGINFO0_Msk                  (0x01UL << ADC_DR5_TRGINFO0_Pos)                        /*!< ADC DR5: TRGINFO0 Mask                  */
#define ADC_DR5_TRGINFO1_Pos                  25                                                      /*!< ADC DR5: TRGINFO1 Position              */
#define ADC_DR5_TRGINFO1_Msk                  (0x01UL << ADC_DR5_TRGINFO1_Pos)                        /*!< ADC DR5: TRGINFO1 Mask                  */
#define ADC_DR5_TRGINFO2_Pos                  26                                                      /*!< ADC DR5: TRGINFO2 Position              */
#define ADC_DR5_TRGINFO2_Msk                  (0x01UL << ADC_DR5_TRGINFO2_Pos)                        /*!< ADC DR5: TRGINFO2 Mask                  */
#define ADC_DR5_TRGINFO3_Pos                  27                                                      /*!< ADC DR5: TRGINFO3 Position              */
#define ADC_DR5_TRGINFO3_Msk                  (0x01UL << ADC_DR5_TRGINFO3_Pos)                        /*!< ADC DR5: TRGINFO3 Mask                  */
#define ADC_DR5_TRGINFO4_Pos                  28                                                      /*!< ADC DR5: TRGINFO4 Position              */
#define ADC_DR5_TRGINFO4_Msk                  (0x01UL << ADC_DR5_TRGINFO4_Pos)                        /*!< ADC DR5: TRGINFO4 Mask                  */
#define ADC_DR5_TRGINFO5_Pos                  29                                                      /*!< ADC DR5: TRGINFO5 Position              */
#define ADC_DR5_TRGINFO5_Msk                  (0x01UL << ADC_DR5_TRGINFO5_Pos)                        /*!< ADC DR5: TRGINFO5 Mask                  */
#define ADC_DR5_TRGINFO6_Pos                  30                                                      /*!< ADC DR5: TRGINFO6 Position              */
#define ADC_DR5_TRGINFO6_Msk                  (0x01UL << ADC_DR5_TRGINFO6_Pos)                        /*!< ADC DR5: TRGINFO6 Mask                  */
#define ADC_DR5_TRGINFO7_Pos                  31                                                      /*!< ADC DR5: TRGINFO7 Position              */
#define ADC_DR5_TRGINFO7_Msk                  (0x01UL << ADC_DR5_TRGINFO7_Pos)                        /*!< ADC DR5: TRGINFO7 Mask                  */

/* -----------------------------------  ADC_DR6  ---------------------------------- */
#define ADC_DR6_ADDATA_Pos                    4                                                       /*!< ADC DR6: ADDATA Position                */
#define ADC_DR6_ADDATA_Msk                    (0x00000fffUL << ADC_DR6_ADDATA_Pos)                    /*!< ADC DR6: ADDATA Mask                    */
#define ADC_DR6_ACH_Pos                       16                                                      /*!< ADC DR6: ACH Position                   */
#define ADC_DR6_ACH_Msk                       (0x1fUL << ADC_DR6_ACH_Pos)                             /*!< ADC DR6: ACH Mask                       */
#define ADC_DR6_TRGINFO0_Pos                  24                                                      /*!< ADC DR6: TRGINFO0 Position              */
#define ADC_DR6_TRGINFO0_Msk                  (0x01UL << ADC_DR6_TRGINFO0_Pos)                        /*!< ADC DR6: TRGINFO0 Mask                  */
#define ADC_DR6_TRGINFO1_Pos                  25                                                      /*!< ADC DR6: TRGINFO1 Position              */
#define ADC_DR6_TRGINFO1_Msk                  (0x01UL << ADC_DR6_TRGINFO1_Pos)                        /*!< ADC DR6: TRGINFO1 Mask                  */
#define ADC_DR6_TRGINFO2_Pos                  26                                                      /*!< ADC DR6: TRGINFO2 Position              */
#define ADC_DR6_TRGINFO2_Msk                  (0x01UL << ADC_DR6_TRGINFO2_Pos)                        /*!< ADC DR6: TRGINFO2 Mask                  */
#define ADC_DR6_TRGINFO3_Pos                  27                                                      /*!< ADC DR6: TRGINFO3 Position              */
#define ADC_DR6_TRGINFO3_Msk                  (0x01UL << ADC_DR6_TRGINFO3_Pos)                        /*!< ADC DR6: TRGINFO3 Mask                  */
#define ADC_DR6_TRGINFO4_Pos                  28                                                      /*!< ADC DR6: TRGINFO4 Position              */
#define ADC_DR6_TRGINFO4_Msk                  (0x01UL << ADC_DR6_TRGINFO4_Pos)                        /*!< ADC DR6: TRGINFO4 Mask                  */
#define ADC_DR6_TRGINFO5_Pos                  29                                                      /*!< ADC DR6: TRGINFO5 Position              */
#define ADC_DR6_TRGINFO5_Msk                  (0x01UL << ADC_DR6_TRGINFO5_Pos)                        /*!< ADC DR6: TRGINFO5 Mask                  */
#define ADC_DR6_TRGINFO6_Pos                  30                                                      /*!< ADC DR6: TRGINFO6 Position              */
#define ADC_DR6_TRGINFO6_Msk                  (0x01UL << ADC_DR6_TRGINFO6_Pos)                        /*!< ADC DR6: TRGINFO6 Mask                  */
#define ADC_DR6_TRGINFO7_Pos                  31                                                      /*!< ADC DR6: TRGINFO7 Position              */
#define ADC_DR6_TRGINFO7_Msk                  (0x01UL << ADC_DR6_TRGINFO7_Pos)                        /*!< ADC DR6: TRGINFO7 Mask                  */

/* -----------------------------------  ADC_DR7  ---------------------------------- */
#define ADC_DR7_ADDATA_Pos                    4                                                       /*!< ADC DR7: ADDATA Position                */
#define ADC_DR7_ADDATA_Msk                    (0x00000fffUL << ADC_DR7_ADDATA_Pos)                    /*!< ADC DR7: ADDATA Mask                    */
#define ADC_DR7_ACH_Pos                       16                                                      /*!< ADC DR7: ACH Position                   */
#define ADC_DR7_ACH_Msk                       (0x1fUL << ADC_DR7_ACH_Pos)                             /*!< ADC DR7: ACH Mask                       */
#define ADC_DR7_TRGINFO0_Pos                  24                                                      /*!< ADC DR7: TRGINFO0 Position              */
#define ADC_DR7_TRGINFO0_Msk                  (0x01UL << ADC_DR7_TRGINFO0_Pos)                        /*!< ADC DR7: TRGINFO0 Mask                  */
#define ADC_DR7_TRGINFO1_Pos                  25                                                      /*!< ADC DR7: TRGINFO1 Position              */
#define ADC_DR7_TRGINFO1_Msk                  (0x01UL << ADC_DR7_TRGINFO1_Pos)                        /*!< ADC DR7: TRGINFO1 Mask                  */
#define ADC_DR7_TRGINFO2_Pos                  26                                                      /*!< ADC DR7: TRGINFO2 Position              */
#define ADC_DR7_TRGINFO2_Msk                  (0x01UL << ADC_DR7_TRGINFO2_Pos)                        /*!< ADC DR7: TRGINFO2 Mask                  */
#define ADC_DR7_TRGINFO3_Pos                  27                                                      /*!< ADC DR7: TRGINFO3 Position              */
#define ADC_DR7_TRGINFO3_Msk                  (0x01UL << ADC_DR7_TRGINFO3_Pos)                        /*!< ADC DR7: TRGINFO3 Mask                  */
#define ADC_DR7_TRGINFO4_Pos                  28                                                      /*!< ADC DR7: TRGINFO4 Position              */
#define ADC_DR7_TRGINFO4_Msk                  (0x01UL << ADC_DR7_TRGINFO4_Pos)                        /*!< ADC DR7: TRGINFO4 Mask                  */
#define ADC_DR7_TRGINFO5_Pos                  29                                                      /*!< ADC DR7: TRGINFO5 Position              */
#define ADC_DR7_TRGINFO5_Msk                  (0x01UL << ADC_DR7_TRGINFO5_Pos)                        /*!< ADC DR7: TRGINFO5 Mask                  */
#define ADC_DR7_TRGINFO6_Pos                  30                                                      /*!< ADC DR7: TRGINFO6 Position              */
#define ADC_DR7_TRGINFO6_Msk                  (0x01UL << ADC_DR7_TRGINFO6_Pos)                        /*!< ADC DR7: TRGINFO6 Mask                  */
#define ADC_DR7_TRGINFO7_Pos                  31                                                      /*!< ADC DR7: TRGINFO7 Position              */
#define ADC_DR7_TRGINFO7_Msk                  (0x01UL << ADC_DR7_TRGINFO7_Pos)                        /*!< ADC DR7: TRGINFO7 Mask                  */

/* -----------------------------------  ADC_IMR  ---------------------------------- */
#define ADC_IMR_INJECTMODE_Pos                0                                                       /*!< ADC IMR: INJECTMODE Position            */
#define ADC_IMR_INJECTMODE_Msk                (0x01UL << ADC_IMR_INJECTMODE_Pos)                      /*!< ADC IMR: INJECTMODE Mask                */
#define ADC_IMR_TRGSEL_Pos                    4                                                       /*!< ADC IMR: TRGSEL Position                */
#define ADC_IMR_TRGSEL_Msk                    (0x03UL << ADC_IMR_TRGSEL_Pos)                          /*!< ADC IMR: TRGSEL Mask                    */
#define ADC_IMR_CHSEL_Pos                     8                                                       /*!< ADC IMR: CHSEL Position                 */
#define ADC_IMR_CHSEL_Msk                     (0x1fUL << ADC_IMR_CHSEL_Pos)                           /*!< ADC IMR: CHSEL Mask                     */
#define ADC_IMR_CST_Pos                       16                                                      /*!< ADC IMR: CST Position                   */
#define ADC_IMR_CST_Msk                       (0x1fUL << ADC_IMR_CST_Pos)                             /*!< ADC IMR: CST Mask                       */
#define ADC_IMR_TRGSRC_Pos                    24                                                      /*!< ADC IMR: TRGSRC Position                */
#define ADC_IMR_TRGSRC_Msk                    (0x0fUL << ADC_IMR_TRGSRC_Pos)                          /*!< ADC IMR: TRGSRC Mask                    */

/* -----------------------------------  ADC_ICR  ---------------------------------- */
#define ADC_ICR_ASTART_Pos                    0                                                       /*!< ADC ICR: ASTART Position                */
#define ADC_ICR_ASTART_Msk                    (0x01UL << ADC_ICR_ASTART_Pos)                          /*!< ADC ICR: ASTART Mask                    */

/* -----------------------------------  ADC_IDR  ---------------------------------- */
#define ADC_IDR_ADDATA_Pos                    4                                                       /*!< ADC IDR: ADDATA Position                */
#define ADC_IDR_ADDATA_Msk                    (0x00000fffUL << ADC_IDR_ADDATA_Pos)                    /*!< ADC IDR: ADDATA Mask                    */
#define ADC_IDR_ACH_Pos                       16                                                      /*!< ADC IDR: ACH Position                   */
#define ADC_IDR_ACH_Msk                       (0x1fUL << ADC_IDR_ACH_Pos)                             /*!< ADC IDR: ACH Mask                       */

/* ----------------------------------  ADC_CMP0R  --------------------------------- */
#define ADC_CMP0R_CVAL_Pos                    4                                                       /*!< ADC CMP0R: CVAL Position                */
#define ADC_CMP0R_CVAL_Msk                    (0x00000fffUL << ADC_CMP0R_CVAL_Pos)                    /*!< ADC CMP0R: CVAL Mask                    */
#define ADC_CMP0R_CCH_Pos                     16                                                      /*!< ADC CMP0R: CCH Position                 */
#define ADC_CMP0R_CCH_Msk                     (0x1fUL << ADC_CMP0R_CCH_Pos)                           /*!< ADC CMP0R: CCH Mask                     */
#define ADC_CMP0R_CMPM_Pos                    21                                                      /*!< ADC CMP0R: CMPM Position                */
#define ADC_CMP0R_CMPM_Msk                    (0x01UL << ADC_CMP0R_CMPM_Pos)                          /*!< ADC CMP0R: CMPM Mask                    */
#define ADC_CMP0R_CMPEN_Pos                   23                                                      /*!< ADC CMP0R: CMPEN Position               */
#define ADC_CMP0R_CMPEN_Msk                   (0x01UL << ADC_CMP0R_CMPEN_Pos)                         /*!< ADC CMP0R: CMPEN Mask                   */
#define ADC_CMP0R_CMPIEN_Pos                  24                                                      /*!< ADC CMP0R: CMPIEN Position              */
#define ADC_CMP0R_CMPIEN_Msk                  (0x01UL << ADC_CMP0R_CMPIEN_Pos)                        /*!< ADC CMP0R: CMPIEN Mask                  */
#define ADC_CMP0R_MATCH_CNT_Pos               26                                                      /*!< ADC CMP0R: MATCH_CNT Position           */
#define ADC_CMP0R_MATCH_CNT_Msk               (0x3fUL << ADC_CMP0R_MATCH_CNT_Pos)                     /*!< ADC CMP0R: MATCH_CNT Mask               */

/* ----------------------------------  ADC_CMP1R  --------------------------------- */
#define ADC_CMP1R_CVAL_Pos                    4                                                       /*!< ADC CMP1R: CVAL Position                */
#define ADC_CMP1R_CVAL_Msk                    (0x00000fffUL << ADC_CMP1R_CVAL_Pos)                    /*!< ADC CMP1R: CVAL Mask                    */
#define ADC_CMP1R_CCH_Pos                     16                                                      /*!< ADC CMP1R: CCH Position                 */
#define ADC_CMP1R_CCH_Msk                     (0x1fUL << ADC_CMP1R_CCH_Pos)                           /*!< ADC CMP1R: CCH Mask                     */
#define ADC_CMP1R_CMPM_Pos                    21                                                      /*!< ADC CMP1R: CMPM Position                */
#define ADC_CMP1R_CMPM_Msk                    (0x01UL << ADC_CMP1R_CMPM_Pos)                          /*!< ADC CMP1R: CMPM Mask                    */
#define ADC_CMP1R_CMPEN_Pos                   23                                                      /*!< ADC CMP1R: CMPEN Position               */
#define ADC_CMP1R_CMPEN_Msk                   (0x01UL << ADC_CMP1R_CMPEN_Pos)                         /*!< ADC CMP1R: CMPEN Mask                   */
#define ADC_CMP1R_CMPIEN_Pos                  24                                                      /*!< ADC CMP1R: CMPIEN Position              */
#define ADC_CMP1R_CMPIEN_Msk                  (0x01UL << ADC_CMP1R_CMPIEN_Pos)                        /*!< ADC CMP1R: CMPIEN Mask                  */
#define ADC_CMP1R_MATCH_CNT_Pos               26                                                      /*!< ADC CMP1R: MATCH_CNT Position           */
#define ADC_CMP1R_MATCH_CNT_Msk               (0x3fUL << ADC_CMP1R_MATCH_CNT_Pos)                     /*!< ADC CMP1R: MATCH_CNT Mask               */


/* ================================================================================ */
/* ================         struct 'OPAMP' Position & Mask         ================ */
/* ================================================================================ */


/* -------------------------------  OPAMP_CR  ------------------------------ */
#define OPAMP_CR_AMPEN_Pos             0                                                       /*!< OPAMP CR: AMPEN Position         */
#define OPAMP_CR_AMPEN_Msk             (0x01UL << OPAMP_CR_AMPEN_Pos)                   /*!< OPAMP CR: AMPEN Mask             */
#define OPAMP_CR_UGAINEN_Pos           1                                                       /*!< OPAMP CR: UGAINEN Position       */
#define OPAMP_CR_UGAINEN_Msk           (0x01UL << OPAMP_CR_UGAINEN_Pos)                 /*!< OPAMP CR: UGAINEN Mask           */



/* ================================================================================ */
/* ================          struct 'CMP' Position & Mask          ================ */
/* ================================================================================ */


/* ----------------------------------  CMP_CONF  ---------------------------------- */
#define CMP_CONF_CINPSEL_Pos                  0                                                       /*!< CMP CONF: CINPSEL Position              */
#define CMP_CONF_CINPSEL_Msk                  (0x03UL << CMP_CONF_CINPSEL_Pos)                        /*!< CMP CONF: CINPSEL Mask                  */
#define CMP_CONF_CINNSEL_Pos                  4                                                       /*!< CMP CONF: CINNSEL Position              */
#define CMP_CONF_CINNSEL_Msk                  (0x03UL << CMP_CONF_CINNSEL_Pos)                        /*!< CMP CONF: CINNSEL Mask                  */
#define CMP_CONF_INTTYPE_Pos                  8                                                       /*!< CMP CONF: INTTYPE Position              */
#define CMP_CONF_INTTYPE_Msk                  (0x03UL << CMP_CONF_INTTYPE_Pos)                        /*!< CMP CONF: INTTYPE Mask                  */
#define CMP_CONF_INTPOL_Pos                   10                                                      /*!< CMP CONF: INTPOL Position               */
#define CMP_CONF_INTPOL_Msk                   (0x01UL << CMP_CONF_INTPOL_Pos)                         /*!< CMP CONF: INTPOL Mask                   */
#define CMP_CONF_HYSSEL_Pos                   16                                                      /*!< CMP CONF: HYSSEL Position               */
#define CMP_CONF_HYSSEL_Msk                   (0x03UL << CMP_CONF_HYSSEL_Pos)                         /*!< CMP CONF: HYSSEL Mask                   */
#define CMP_CONF_HYSEN_Pos                    20                                                      /*!< CMP CONF: HYSEN Position                */
#define CMP_CONF_HYSEN_Msk                    (0x01UL << CMP_CONF_HYSEN_Pos)                          /*!< CMP CONF: HYSEN Mask                    */
#define CMP_CONF_FLTSEL_Pos                   24                                                      /*!< CMP CONF: FLTSEL Position               */
#define CMP_CONF_FLTSEL_Msk                   (0x3fUL << CMP_CONF_FLTSEL_Pos)                         /*!< CMP CONF: FLTSEL Mask                   */
#define CMP_CONF_FLTDIV_Pos                   30                                                      /*!< CMP CONF: FLTDIV Position               */
#define CMP_CONF_FLTDIV_Msk                   (0x03UL << CMP_CONF_FLTDIV_Pos)                         /*!< CMP CONF: FLTDIV Mask                   */

/* ----------------------------------  CMP_CTRL  ---------------------------------- */
#define CMP_CTRL_CMPEN_Pos                    0                                                       /*!< CMP CTRL: CMPEN Position                */
#define CMP_CTRL_CMPEN_Msk                    (0x01UL << CMP_CTRL_CMPEN_Pos)                          /*!< CMP CTRL: CMPEN Mask                    */
#define CMP_CTRL_CMPINTEN_Pos                 8                                                       /*!< CMP CTRL: CMPINTEN Position             */
#define CMP_CTRL_CMPINTEN_Msk                 (0x01UL << CMP_CTRL_CMPINTEN_Pos)                       /*!< CMP CTRL: CMPINTEN Mask                 */

/* ----------------------------------  CMP_STAT  ---------------------------------- */
#define CMP_STAT_CMPFLAG_Pos                  0                                                       /*!< CMP STAT: CMPFLAG Position              */
#define CMP_STAT_CMPFLAG_Msk                  (0x01UL << CMP_STAT_CMPFLAG_Pos)                        /*!< CMP STAT: CMPFLAG Mask                  */
#define CMP_STAT_CMPINTF_Pos                  8                                                       /*!< CMP STAT: CMPINTF Position              */
#define CMP_STAT_CMPINTF_Msk                  (0x01UL << CMP_STAT_CMPINTF_Pos)                        /*!< CMP STAT: CMPINTF Mask                  */

/* ----------------------------------  CMP_DBCR  ---------------------------------- */
#define CMP_DBCR_DBEN_Pos                     0                                                       /*!< CMP DBCR: DBEN Position                 */
#define CMP_DBCR_DBEN_Msk                     (0x01UL << CMP_DBCR_DBEN_Pos)                           /*!< CMP DBCR: DBEN Mask                     */


/* ================================================================================ */
/* ================          struct 'CRC' Position & Mask          ================ */
/* ================================================================================ */


/* ----------------------------------  CRC_CTRL  ---------------------------------- */
#define CRC_CTRL_INIT_EN_Pos                  0                                                       /*!< CRC CTRL: INIT_EN Position              */
#define CRC_CTRL_INIT_EN_Msk                  (0x01UL << CRC_CTRL_INIT_EN_Pos)                        /*!< CRC CTRL: INIT_EN Mask                  */
#define CRC_CTRL_POLY_Pos                     1                                                       /*!< CRC CTRL: POLY Position                 */
#define CRC_CTRL_POLY_Msk                     (0x03UL << CRC_CTRL_POLY_Pos)                           /*!< CRC CTRL: POLY Mask                     */
#define CRC_CTRL_DMADINTEN_Pos                8                                                       /*!< CRC CTRL: DMADINTEN Position            */
#define CRC_CTRL_DMADINTEN_Msk                (0x01UL << CRC_CTRL_DMADINTEN_Pos)                      /*!< CRC CTRL: DMADINTEN Mask                */
#define CRC_CTRL_IN_REV_Pos                   16                                                      /*!< CRC CTRL: IN_REV Position               */
#define CRC_CTRL_IN_REV_Msk                   (0x01UL << CRC_CTRL_IN_REV_Pos)                         /*!< CRC CTRL: IN_REV Mask                   */
#define CRC_CTRL_OUT_REV_Pos                  20                                                      /*!< CRC CTRL: OUT_REV Position              */
#define CRC_CTRL_OUT_REV_Msk                  (0x01UL << CRC_CTRL_OUT_REV_Pos)                        /*!< CRC CTRL: OUT_REV Mask                  */
#define CRC_CTRL_OUT_INV_Pos                  21                                                      /*!< CRC CTRL: OUT_INV Position              */
#define CRC_CTRL_OUT_INV_Msk                  (0x01UL << CRC_CTRL_OUT_INV_Pos)                        /*!< CRC CTRL: OUT_INV Mask                  */

/* ----------------------------------  CRC_INIT  ---------------------------------- */
#define CRC_INIT_INIT_Pos                     0                                                       /*!< CRC INIT: INIT Position                 */
#define CRC_INIT_INIT_Msk                     (0xffffffffUL << CRC_INIT_INIT_Pos)                     /*!< CRC INIT: INIT Mask                     */

/* -----------------------------------  CRC_IDR  ---------------------------------- */
#define CRC_IDR_IDR_Pos                       0                                                       /*!< CRC IDR: IDR Position                   */
#define CRC_IDR_IDR_Msk                       (0xffffffffUL << CRC_IDR_IDR_Pos)                       /*!< CRC IDR: IDR Mask                       */

/* -----------------------------------  CRC_ODR  ---------------------------------- */
#define CRC_ODR_ODR_Pos                       0                                                       /*!< CRC ODR: ODR Position                   */
#define CRC_ODR_ODR_Msk                       (0xffffffffUL << CRC_ODR_ODR_Pos)                       /*!< CRC ODR: ODR Mask                       */

/* ----------------------------------  CRC_STAT  ---------------------------------- */
#define CRC_STAT_DMADINT_Pos                  8                                                       /*!< CRC STAT: DMADINT Position              */
#define CRC_STAT_DMADINT_Msk                  (0x01UL << CRC_STAT_DMADINT_Pos)                        /*!< CRC STAT: DMADINT Mask                  */



/* ================================================================================ */
/* ================              Peripheral memory map             ================ */
/* ================================================================================ */

#define CHIPCONFIG_BASE                 0x4000F000UL
#define SCU_BASE                        0x40000000UL
#define PA_BASE                         0x42000000UL
#define PB_BASE                         0x42000100UL
#define PC_BASE                         0x42000200UL
#define PD_BASE                         0x42000300UL
#define PORTEN_BASE                     0x42000FF0UL
#define CFMC_BASE                       0x41000000UL
#define SRAM_BASE                       0x41003000UL
#define DMA0_BASE                       0x40000400UL
#define DMA1_BASE                       0x40000410UL
#define DMA2_BASE                       0x40000420UL
#define DMA3_BASE                       0x40000430UL
#define WDT_BASE                        0x40000200UL
#define TIMER0_BASE                     0x40003000UL
#define TIMER1_BASE                     0x40003040UL
#define TIMER2_BASE                     0x40003080UL
#define TIMER3_BASE                     0x400030C0UL
#define FRT_BASE                        0x40000600UL
#define UART0_BASE                      0x40008000UL
#define UART1_BASE                      0x40008100UL
#define SPI_BASE                        0x40009000UL
#define I2C_BASE                        0x4000A000UL
#define MPWM_BASE                       0x42001000UL
#define ADC_BASE                        0x42002000UL
#define OPAMP0_BASE                      0x4000B300UL
#define OPAMP1_BASE                      0x4000B304UL
#define OPAMP2_BASE                      0x4000B308UL
#define CMP_BASE                        0x4000B380UL
#define CRC_BASE                        0x41002000UL


/* ================================================================================ */
/* ================             Peripheral declaration             ================ */
/* ================================================================================ */

#define CHIPCONFIG                      ((CHIPCONFIG_Type         *) CHIPCONFIG_BASE)
#define SCU                             ((SCU_Type                *) SCU_BASE)
#define PA                              ((PCU_Type                *) PA_BASE)
#define PB                              ((PCU_Type                *) PB_BASE)
#define PC                              ((PCU_Type                *) PC_BASE)
#define PD                              ((PCU_Type                *) PD_BASE)
#define PORTEN                          ((PORTEN_Type             *) PORTEN_BASE)
#define CFMC                            ((CFMC_Type               *) CFMC_BASE)
#define SRAM                            ((SRAM_Type               *) SRAM_BASE)
#define DMA0                            ((DMA_Type                *) DMA0_BASE)
#define DMA1                            ((DMA_Type                *) DMA1_BASE)
#define DMA2                            ((DMA_Type                *) DMA2_BASE)
#define DMA3                            ((DMA_Type                *) DMA3_BASE)
#define WDT                             ((WDT_Type                *) WDT_BASE)
#define TIMER0                          ((TIMER_Type              *) TIMER0_BASE)
#define TIMER1                          ((TIMER_Type              *) TIMER1_BASE)
#define TIMER2                          ((TIMER_Type              *) TIMER2_BASE)
#define TIMER3                          ((TIMER_Type              *) TIMER3_BASE)
#define FRT                             ((FRT_Type                *) FRT_BASE)
#define UART0                           ((UART_Type               *) UART0_BASE)
#define UART1                           ((UART_Type               *) UART1_BASE)
#define SPI                             ((SPI_Type                *) SPI_BASE)
#define I2C                             ((I2C_Type                *) I2C_BASE)
#define MPWM                            ((MPWM_Type               *) MPWM_BASE)
#define ADC                             ((ADC_Type                *) ADC_BASE)
#define OPAMP                           ((OPAMP_Type              *) OPAMP0_BASE)
#define CMP                             ((CMP_Type                *) CMP_BASE)
#define CRC                             ((CRC_Type                *) CRC_BASE)


/** @} */ /* End of group Device_Peripheral_Registers */
/** @} */ /* End of group A31M22x */
/** @} */ /* End of group ABOV Semiconductor Co., Ltd. */

#ifdef __cplusplus
}
#endif


#endif  /* A31M22x_H */

