/**
 *******************************************************************************
 * @file        a31m22x_cfmc.h
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


#ifndef _A31M22x_CFMC_H_
#define _A31M22x_CFMC_H_

/* Includes ------------------------------------------------------------------- */
#include "A31M22x.h"
#include "aa_types.h"

#ifdef __cplusplus
extern "C"
{
#endif

#define CFMC_WRITE_BUSY_POLLING  while(((CFMC->STAT)&CFMC_STAT_WBUSY_Msk)==CFMC_STAT_WBUSY_Msk)

#define MIO32(addr)  (*(volatile unsigned int *)(addr))
	
// Flash Access Key
#define CFMC_FLSKEY_ACCESS_KEY1						0x01234567UL
#define CFMC_FLSKEY_ACCESS_KEY2						0x12345678UL
#define CFMC_FLSKEY_ACCESS_KEY3						0x23456789UL

#define CFMC_FLSKEY_ACCESS_RST						0x00000000UL

// INFO Access Key
#define CFMC_INFOKEY_ACCESS_KEY1					0x3456789AUL
#define CFMC_INFOKEY_ACCESS_KEY2					0x456789ABUL
#define CFMC_INFOKEY_ACCESS_KEY3					0x56789ABCUL
#define CFMC_INFOKEY_ACCESS_RST						0x00000000UL

// FMC CONF Macro
#define CFMC_CONF_INST_CACHE_RST					(0x01UL << CFMC_CONF_ICRST_Pos)
#define CFMC_CONF_INST_CACHE_ON						(0x01UL << CFMC_CONF_ICEN_Pos)

// FMC Read Protection Register
#define CFMC_READPROT_RPROT_UNPROTECT				(0xFFUL<<0)
#define CFMC_READPROT_RPROT_LEVEL1					(0x39UL<<0)
#define CFMC_READPROT_RPROT_LEVEL2					(0x00UL<<0)

// FMC OTP Protection Macro
#define CFMC_OTPPROT_PROT_0x0F000600_0x0F0007FF		(1UL<<3)
#define CFMC_OTPPROT_PROT_0x0F000400_0x0F0005FF		(1UL<<2)
#define CFMC_OTPPROT_PROT_0x0F000200_0x0F0003FF		(1UL<<1)
#define CFMC_OTPPROT_PROT_0x0F000000_0x0F0001FF		(1UL<<0)

// FMC Checksum Control Macro
#define CFMC_CHKCTRL_CDRST_RST				        (1UL<<CFMC_CHKCTRL_CDRST_Pos)
#define CFMC_CHKCTRL_CDIEN_ON				        (1UL<<CFMC_CHKCTRL_CDIEN_Pos)
#define CFMC_CHKCTRL_BSTEN_ON				        (1UL<<CFMC_CHKCTRL_BSTEN_Pos)
#define CFMC_CHKCTRL_BGEN_ON			            (1UL<<CFMC_CHKCTRL_BGEN_Pos)

// FM_CTRL
#define CFMC_CTRL_FLOCK			                    (1UL<<CFMC_CTRL_FLOCK_Pos)
#define CFMC_CTRL_ILOCK			                    (1UL<<CFMC_CTRL_ILOCK_Pos)
#define CFMC_CTRL_WDIEN			                    (1UL<<CFMC_CTRL_WDIEN_Pos)
#define CFMC_CTRL_WABORT		                    (1UL<<CFMC_CTRL_WABORT_Pos)    
#define CFMC_CTRL_CERS			                    (1UL<<CFMC_CTRL_CERS_Pos)
#define CFMC_CTRL_SERS			                    (1UL<<CFMC_CTRL_SERS_Pos)
#define CFMC_CTRL_PERS			                    (1UL<<CFMC_CTRL_PERS_Pos)
#define CFMC_CTRL_PGM			                    (1UL<<CFMC_CTRL_PGM_Pos)
	
/* Public Functions ----------------------------------------------------------- */
void CFMC_CacheCmd(FunctionalState NewState);
void CFMC_BootBlockCmd(FunctionalState NewState);
void CFMC_WaitCmd(uint8_t WaitValue);
void CFMC_FlashAccessCmd(FunctionalState NewState);
void CFMC_INFOAccessCmd(FunctionalState NewState);
void CFMC_FlashPROTCmd(uint32_t ProtectionBit, FunctionalState NewState);
void CFMC_FlashRPROTCmd(uint32_t ReadProtectionBit, FunctionalState NewState);
void CFMC_INFOPROTCmd(uint32_t ProtectionBit, FunctionalState NewState);
void CFMC_LockCmd(uint32_t LockBit);
void CFMC_InterruptCmd(FunctionalState NewStatus);
uint32_t CFMC_GetAccessStatus(void);
void CFMC_ClearAccessStatus(uint32_t ClearSRC);
void CFMC_FlashChecksumCmd(uint32_t ControlBit, FunctionalState NewState);
uint32_t CFMC_GetChecksumData(void);
void CFMC_ChecksumAddrCmd(uint32_t StartAddress, uint32_t EndAddress);
uint32_t CFMC_GetChecksumCmd(void);
void CFMC_WriteCmd(FunctionalState NewState);

void cflash_acc_status_check (void);
void CFMCErase(uint32_t Ersmod,unsigned long addr);
void CFMCProgramPage (unsigned long addr, unsigned long size, unsigned char *buf);
void CFMCBurstProgramPage (unsigned long addr, unsigned long size, unsigned char *buf);
unsigned long CFMCVerify (unsigned long addr, unsigned long size, unsigned char *buf);

#ifdef __cplusplus
}
#endif


#endif /* end _A31M22x_CFMC_H_ */

/* --------------------------------- End Of File ------------------------------ */
