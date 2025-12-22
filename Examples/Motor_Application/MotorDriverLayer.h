/**
 *******************************************************************************
 * @file        MotorDriverLayer.h
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


#ifndef _MOTOR_DRIVER_LAYER_H_
#define _MOTOR_DRIVER_LAYER_H_

/*******************************************************************************
* Included File
*******************************************************************************/

#if defined(__DEF_A33M11x__)
#include "a33m11x_pcu.h"
#include "a33m11x_scu.h"
#include "a33m11x_adc.h"
#include "a33m11x_mpwm.h"
#include "a33m11x_adc.h"
#include "a33m11x_afe.h"
#include "a33m11x_spi.h"
#include "a33m11x_timer.h"
#include "a33m11x_uart.h"
#elif defined(__DEF_A34M41x__)
#include "a34m41x_pcu.h"
#include "a34m41x_scu.h"
#include "a34m41x_adc.h"
#include "a34m41x_mpwm.h"
#include "a34m41x_adc.h"
#include "a34m41x_spi.h"
#include "a34m41x_timer.h"
#include "a34m41x_uart.h"
#elif defined(__DEF_AC30M1x64__)
#include "ac30m1x64_pcu.h"
#include "ac30m1x64_scu.h"
#include "ac30m1x64_gpio.h"
#include "ac30m1x64_adc.h"
#include "ac30m1x64_mpwm.h"
#include "ac30m1x64_adc.h"
#include "ac30m1x64_spi.h"
#include "ac30m1x64_timer.h"
#include "ac30m1x64_uart.h"
#elif defined(__DEF_AC33Mx064__)
#include "ac33mx064_pcu.h"
#include "ac33mx064_scu.h"
#include "ac33mx064_gpio.h"
#include "ac33mx064_adc.h"
#include "ac33mx064_mpwm.h"
#include "ac33mx064_adc.h"
#include "ac33mx064_libcfg.h"
#include "ac33mx064_spi.h"
#include "ac33mx064_timer.h"
#include "ac33mx064_uart.h"
#elif defined(__DEF_AC33Mx128__)
#include "ac33mx128_pcu.h"
#include "ac33mx128_scu.h"
#include "ac33mx128_gpio.h"
#include "ac33mx128_dmac.h"
#include "ac33mx128_adc.h"
#include "ac33mx128_mpwm.h"
#include "ac33mx128_adc.h"
#include "ac33mx128_libcfg.h"
#include "ac33mx128_spi.h"
#include "ac33mx128_timer.h"
#include "ac33mx128_uart.h"
#elif defined(__DEF_A31M22x__)
#include "a31m22x_pcu.h"
#include "a31m22x_scu.h"
//#include "a31m22x_gpio.h"
//#include "a31m22x_dmac.h"
#include "a31m22x_adc.h"
#include "a31m22x_mpwm.h"
#include "a31m22x_adc.h"
#include "a31m22x_libcfg.h"
#include "a31m22x_spi.h"
#include "a31m22x_timer.h"
#include "a31m22x_uart.h"
#include <stdbool.h>
#endif


/*******************************************************************************
* Public Macro
*******************************************************************************/

#if defined(__DEF_A31M22x__)
#define MPWM_OLR_Msk                    (MPWM_OLR_FORCEU_Msk | MPWM_OLR_POCWH_Msk | MPWM_OLR_POCVH_Msk | MPWM_OLR_POCUH_Msk |\
                                        MPWM_OLR_POCWL_Msk | MPWM_OLR_POCVL_Msk | MPWM_OLR_POCUL_Msk | MPWM_OLR_DOLWH_Msk |\
                                        MPWM_OLR_DOLVH_Msk | MPWM_OLR_DOLUH_Msk | MPWM_OLR_DOLWL_Msk | MPWM_OLR_DOLVL_Msk |\
                                        MPWM_OLR_DOLUL_Msk | MPWM_OLR_SLWH_Msk | MPWM_OLR_SLVH_Msk | MPWM_OLR_SLUH_Msk |\
                                        MPWM_OLR_SLWL_Msk | MPWM_OLR_SLVL_Msk | MPWM_OLR_SLUL_Msk)

#define MPWM_FOLR_FOLKEY                (0xCA)
#define MPWM_FOLR_Msk                   (MPWM_FOLR_SWFO_Msk | MPWM_FOLR_PRTFO_Msk | MPWM_FOLR_OCFO_Msk | MPWM_FOLR_FLWH_Msk |\
                                        MPWM_FOLR_FLVH_Msk | MPWM_FOLR_FLUH_Msk | MPWM_FOLR_FLWL_Msk | MPWM_FOLR_FLVL_Msk |\
                                        MPWM_FOLR_FLUL_Msk)

#define MPWM_SR_Msk                     (MPWM_SR_PRDIF_Msk | MPWM_SR_BOTIF_Msk | MPWM_SR_DWHIF_ATR6F_Msk | MPWM_SR_DVHIF_ATR5F_Msk |\
                                        MPWM_SR_DUHIF_ATR4F_Msk | MPWM_SR_DWLIF_ATR3F_Msk | MPWM_SR_DVLIF_ATR2F_Msk | MPWM_SR_DULIF_ATR1F_Msk) 

#define MPWM_PCR_Msk                    (MPWM_PCR_PROTPOL_Msk | MPWM_PCR_PROTDIV_Msk | MPWM_PCR_PROTD_Msk | MPWM_PCR_PROT3EN_Msk |\
                                        MPWM_PCR_PROT2EN_Msk |  MPWM_PCR_PROT1EN_Msk |\
                                        MPWM_PCR_PROT0EN_Msk)  //220914 fixed

#define MPWM_PSR_Msk                    (MPWM_PSR_PROT3IF_Msk | MPWM_PSR_PROT2IF_Msk |  \
                                        MPWM_PSR_PROT1IF_Msk | MPWM_PSR_PROT0IF_Msk)				//220914 fixed

#define MPWM_OCR_Msk                    (MPWM_OCR_OVIN3EN_Msk |\
                                        MPWM_OCR_OVIN2EN_Msk | MPWM_OCR_OVIN1EN_Msk | MPWM_OCR_OVIN0EN_Msk) //220914 fixed

#define MPWM_OSR_Msk                    (MPWM_OSR_OVIN3IF_Msk |\
                                        MPWM_OSR_OVIN2IF_Msk | MPWM_OSR_OVIN1IF_Msk | MPWM_OSR_OVIN0IF_Msk) //220914 fixed


#define SPI_STAT_RXBUF_READY				((uint32_t)SPI_SR_RRDY_Msk)	/** SPI status RX buffer ready bit */
#define SPI_STAT_TXBUF_EMPTY				((uint32_t)SPI_SR_TRDY_Msk)	/** SPI status TX buffer empty bit */
#define SPI_STAT_IDLE						((uint32_t)SPI_SR_TXIDLE_Msk)	/** SPI status TX/RX IDLE bit */
#define SPI_STAT_TXUNDERRUN_ERR				((uint32_t)SPI_SR_UDRF_Msk)	/** SPI status TX underrun error bit */
#define SPI_STAT_RXOVERRUN_ERR				((uint32_t)SPI_SR_OVRF_Msk)	/** SPI status RX overrun error bit */
#define SPI_STAT_SS_ACT						((uint32_t)SPI_SR_SSON_Msk)	/** SPI status SS active bit */
#define SPI_STAT_SS_DET						((uint32_t)SPI_SR_SSDET_Msk)	/** SPI status SS detect bit */

#define SPI_STAT_SBUSY						((uint32_t)SPI_SR_SBUSY_Msk)	/** SPI status Sbusy Operation Flag */
#define SPI_STAT_RXDMA_DONE					((uint32_t)SPI_SR_RXDMAF_Msk)	/** SPI status RX DMA done bit */
#define SPI_STAT_TXDMA_DONE					((uint32_t)SPI_SR_TXDMAF_Msk)	/** SPI status TX DMA done bit */


#endif

/*******************************************************************************
* Public Typedef
*******************************************************************************/


/*******************************************************************************
* Exported Public Variable
*******************************************************************************/


/*******************************************************************************
* Exported Public Function
*******************************************************************************/
void USER_ADC_Init(void);
uint32_t MDL_ADC_OPAMP(uint32_t Number);
//uint32_t MDL_ADC_GetVDCLink(void);
//uint32_t MDL_ADC_GetTemperature(void);
uint32_t MDL_ADC_V_Reference(void);
void ADC_Filtered_Vref(void);
void ADC_RPM_SET(void);
void MDL_ADC_ResetDMA(void);

uint32_t MDL_MPWM_GetStatus(void);
void MDL_MPWM_ClearStatus(uint32_t Status);
void MDL_MPWM_SetDefaultDuty(void);
void MDL_MPWM_SetDuty(uint16_t *pDutyArray);
void MDL_MPWM_EnablePWMOutput(void);
void MDL_MPWM_DisablePWMOutput(void);
void MDL_MPWM_InitShuntATR(void);
void MDL_MPWM_SetATR(void);
void MDL_PCU_Init(void);
void USER_OPAMP_Init(void);
void MDL_DAC_Init(void);
void MDL_DAC_SetData(uint32_t Channel, uint16_t Data);
void MDL_FRT_Init(void);
void MDL_FRT_CNT_Zero(void);
uint32_t MDL_FRT_CNT_Read(void);
void MDL_UARTn_Init(void);
void MDL_UARTn_SendByte(uint8_t Data);
uint32_t MDL_UARTn_CheckTxStatus(void);
uint8_t MDL_UARTn_ReceiveByte(void);
uint32_t MDL_UARTn_CheckRxStatus(void);
void MDL_WDT_Init(void);
void MDL_WDT_Start(void);
void MDL_WDT_Clear(void);
void MDL_IPM_Fault_Setting(void);


uint32_t MDL_IPM_TEMP(void);
uint32_t MDL_VDC_SENSE(void);
#endif //_MOTOR_DRIVER_LAYER_H_

/* --------------------------------- End Of File ------------------------------ */
