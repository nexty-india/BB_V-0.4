/**
 *******************************************************************************
 * @file        a31m22x_cfmc.c
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
#include "A31M22x_cfmc.h"
#include "debug_frmwrk.h"

/* Public Function ------------------------------------------------------------ */
/***************************************************************************//**
* @brief      Command cache of code flash memory
* @param[in]  NewState : New state of CFMC cache
*             - Enable : Enable cache
*             - Disable : Disable cache
* @return     None
*******************************************************************************/
void CFMC_CacheCmd(FunctionalState NewState)
{
	uint32_t Reg32;

	Reg32 = CFMC->CONF;

	Reg32 &= (~(CFMC_CONF_ICRST_Msk | CFMC_CONF_ICEN_Msk));

	if (NewState == ENABLE) {
		Reg32 |= ((0x01UL << CFMC_CONF_ICRST_Pos) | (0x01UL << CFMC_CONF_ICEN_Pos));
	} else {
		Reg32 |= 0x01UL << CFMC_CONF_ICRST_Pos;
	}

	CFMC->CONF = Reg32;
}

/**********************************************************************
 * @brief		Code Flash Memory Boot Block Lock
 * @param[in]	NewState
 *					- Enable : Bit Enable
 * 					- Disable : Bit Disable
 * @return		None
 *
 **********************************************************************/
void CFMC_BootBlockCmd(FunctionalState NewState)
{
	uint32_t		reg_val;
	
	reg_val = CFMC->CONF;
	
	reg_val &= ~(0x01<<24);
	
	if (NewState == ENABLE)	{
		reg_val |= (0x01<<24);
	}
	
	CFMC->CONF = reg_val;
}

/**********************************************************************
 * @brief		Code Flash Memory Wait Config
 * @param[in]	Memory Wait Value
 *					- 0~15
 * @return		None
 *
 **********************************************************************/
void CFMC_WaitCmd(uint8_t WaitValue)
{
	uint32_t		reg_val;
	
	reg_val = CFMC->CONF;
	
	reg_val &= ~(0x0F<<0);
	
	reg_val |= (WaitValue&0x0F);
	
	CFMC->CONF = reg_val;
}

/**********************************************************************
 * @brief		Code Flash Memory Access Key Register
 * @param[in]	NewState
 *					- Enable : Bit Enable
 * 					- Disable : Bit Disable
 * @return		None
 *
 **********************************************************************/
void CFMC_FlashAccessCmd(FunctionalState NewState)
{
	if (NewState == ENABLE)	{
		CFMC->FLSKEY = CFMC_FLSKEY_ACCESS_KEY1;		
		CFMC->FLSKEY = CFMC_FLSKEY_ACCESS_KEY2;		
		CFMC->FLSKEY = CFMC_FLSKEY_ACCESS_KEY3;
	}
	
	else if (NewState == DISABLE) {
		CFMC->FLSKEY = CFMC_FLSKEY_ACCESS_RST;
	}
}

/**********************************************************************
 * @brief		Code Flash INFO Access Key Register
 * @param[in]	NewState
 *					- Enable : Bit Enable
 * 					- Disable : Bit Disable
 * @return		None
 *
 **********************************************************************/
void CFMC_INFOAccessCmd(FunctionalState NewState)
{
	if (NewState == ENABLE)	{
		CFMC->OTPKEY = CFMC_INFOKEY_ACCESS_KEY1;		//220914 infokey -> otpkey
		CFMC->OTPKEY = CFMC_INFOKEY_ACCESS_KEY2;		
		CFMC->OTPKEY = CFMC_INFOKEY_ACCESS_KEY3;
	}
	
	else if (NewState == DISABLE) {
		CFMC->OTPKEY = CFMC_INFOKEY_ACCESS_RST;
	}
}


/**********************************************************************
 * @brief		Code Flash Memory Protection Register
 * @param[in]	Protection Area Bit
 *					UnProtection Area
 *				A31M223 64k
 *					- CFMC_FLSPROT_UNPROT_0x0000FF00_0x0000FFFF	: (0x01UL<<31)
 *					- CFMC_FLSPROT_UNPROT_0x0000FE00_0x0000FEFF	: (0x01UL<<30)
 *					- CFMC_FLSPROT_UNPROT_0x0000FD00_0x0000FDFF	: (0x01UL<<29)
 *					- CFMC_FLSPROT_UNPROT_0x0000FC00_0x0000FCFF	: (0x01UL<<28)
 *					- CFMC_FLSPROT_UNPROT_0x0000FB00_0x0000FBFF	: (0x01UL<<27)
 *					- CFMC_FLSPROT_UNPROT_0x0000FA00_0x0000FAFF	: (0x01UL<<26)
 *					- CFMC_FLSPROT_UNPROT_0x0000F900_0x0000F9FF	: (0x01UL<<25)
 *					- CFMC_FLSPROT_UNPROT_0x0000F800_0x0000F8FF	: (0x01UL<<24)
 *				A31M222 32k
 *					- CFMC_FLSPROT_UNPROT_0x00007F00_0x00007FFF	: (0x01UL<<31)
 *					- CFMC_FLSPROT_UNPROT_0x00007E00_0x00007EFF	: (0x01UL<<30)
 *					- CFMC_FLSPROT_UNPROT_0x00007D00_0x00007DFF	: (0x01UL<<29)
 *					- CFMC_FLSPROT_UNPROT_0x00007C00_0x00007CFF	: (0x01UL<<28)
 *					- CFMC_FLSPROT_UNPROT_0x00007B00_0x00007BFF	: (0x01UL<<27)
 *					- CFMC_FLSPROT_UNPROT_0x00007A00_0x00007AFF	: (0x01UL<<26)
 *					- CFMC_FLSPROT_UNPROT_0x00007900_0x000079FF	: (0x01UL<<25)
 *					- CFMC_FLSPROT_UNPROT_0x00007800_0x000078FF	: (0x01UL<<24)
 *
 *					Protection Area
 *					- CFMC_FLSPROT_PROT_0x0000F000_0x0000FFFF	: (0x01UL<<15)
 *					- CFMC_FLSPROT_PROT_0x0000E000_0x0000EFFF	: (0x01UL<<14)
 *					- CFMC_FLSPROT_PROT_0x0000D000_0x0000DFFF	: (0x01UL<<13)
 *					- CFMC_FLSPROT_PROT_0x0000C000_0x0000CFFF	: (0x01UL<<12)
 *					- CFMC_FLSPROT_PROT_0x0000B000_0x0000BFFF	: (0x01UL<<11)
 * 					- CFMC_FLSPROT_PROT_0x0000A000_0x0000AFFF	: (0x01UL<<10)
 *					- CFMC_FLSPROT_PROT_0x00009000_0x00009FFF	: (0x01UL<<9)
 *					- CFMC_FLSPROT_PROT_0x00008000_0x00008FFF	: (0x01UL<<8)
 *					- CFMC_FLSPROT_PROT_0x00007000_0x00007FFF	: (0x01UL<<7)
 *					- CFMC_FLSPROT_PROT_0x00006000_0x00006FFF	: (0x01UL<<6)
 *					- CFMC_FLSPROT_PROT_0x00005000_0x00005FFF	: (0x01UL<<5)
 *					- CFMC_FLSPROT_PROT_0x00004000_0x00004FFF	: (0x01UL<<4)
 *					- CFMC_FLSPROT_PROT_0x00003000_0x00003FFF	: (0x01UL<<3)
 *					- CFMC_FLSPROT_PROT_0x00002000_0x00002FFF	: (0x01UL<<2)
 * 					- CFMC_FLSPROT_PROT_0x00001000_0x00001FFF	: (0x01UL<<1)
 *					- CFMC_FLSPROT_PROT_0x00000000_0x00000FFF	: (0x01UL<<0)

 * @param[in]	NewState
 *					- Enable : Bit Enable
 * 					- Disable : Bit Disable
 * @return		None
 *
 **********************************************************************/
void CFMC_FlashPROTCmd(uint32_t ProtectionBit, FunctionalState NewState)
{
	uint32_t		reg_val;
	
	reg_val = CFMC->FLSPROT;	
	reg_val &= ~(ProtectionBit);
	
	if (NewState == ENABLE)	{
		reg_val |= (ProtectionBit);
	}
	
	CFMC->FLSPROT = reg_val;
}


/**********************************************************************
 * @brief		Code Flash Memory Read Protection Register
 * @param[in]	Read Protection Area Bit
*					- CFMC_READPROT_RPROT_UNPROTECT	: (0xFFUL<<0)
*					- CFMC_READPROT_RPROT_LEVEL1	: (0x39UL<<0)
*					- CFMC_READPROT_RPROT_LEVEL2	: (0x00UL<<0)
 * @param[in]	NewState
 *					- Enable : Bit Enable
 * 					- Disable : Bit Disable
 * @return		None
 *
 **********************************************************************/
void CFMC_FlashRPROTCmd(uint32_t ReadProtectionBit, FunctionalState NewState)
{
	uint32_t		reg_val;
	
	reg_val = CFMC->READPROT;	
	reg_val &= ~(CFMC_READPROT_RPROT_UNPROTECT);
	
	if (NewState == ENABLE)	{
		reg_val |= (ReadProtectionBit);
	}
	
	CFMC->READPROT = reg_val;
}



/**********************************************************************
 * @brief		Code Flash INFO Protection Register
 * @param[in]	INFO Protection Area Bit
*					- CFMC_OTPPROT_PROT_0x0F000200_0x0F0003FF	: (0x01UL<<1)
*					- CFMC_OTPPROT_PROT_0x0F000000_0x0F0001FF	: (0x01UL<<0)
 * @param[in]	NewState
 *					- Enable : Bit Enable
 * 					- Disable : Bit Disable
 * @return		None
 *
 **********************************************************************/
void CFMC_INFOPROTCmd(uint32_t ProtectionBit, FunctionalState NewState)
{
	uint32_t		reg_val;
	
	reg_val = CFMC->OTPPROT;	//220914 INFOPROT -> OTPPROT
	reg_val &= ~(ProtectionBit);
	
	if (NewState == ENABLE)	{
		reg_val |= (ProtectionBit);
	}
	
	CFMC->OTPPROT = reg_val;
}


/**********************************************************************
 * @brief		Code Flash Lock Control Register
 * @param[in]	Lock Selection Bit
 *					- CFMC_CTRL_FLOCK	: (1<<31)
 *					- CFMC_CTRL_OLOCK	: (1<<30)
 * @return		None
 *
 **********************************************************************/
void CFMC_LockCmd(uint32_t LockBit)
{
	uint32_t		reg_val;
	
	reg_val = CFMC->CTRL;	
	reg_val |= (LockBit&0xC0000000UL);
	
	CFMC->CTRL = reg_val;
}


/**********************************************************************
 * @brief		Code Flash Write Done Interrupt Config
 * @param[in]	NewState
 *					- Enable : Bit Enable
 * 					- Disable : Bit Disable
 * @return		None
 *
 **********************************************************************/
void CFMC_InterruptCmd(FunctionalState NewStatus)
{
	uint32_t		reg_val;
	
	reg_val = CFMC->CTRL;
	
	reg_val &= ~CFMC_CTRL_WDIEN;
	
	if (NewStatus == ENABLE) {
		reg_val |= (CFMC_CTRL_WDIEN);
		
		NVIC_SetPriority(CFMC_IRQn, 7);
		NVIC_EnableIRQ(CFMC_IRQn);
	}
	else {
		NVIC_DisableIRQ(CFMC_IRQn);
	}
	
	CFMC->CTRL = reg_val;
}



/**********************************************************************
 * @brief		Code Flash Access Status Register
 * @param[in]	None
 * @return		Access Status Value
 *
 **********************************************************************/
uint32_t CFMC_GetAccessStatus(void)
{
	return (CFMC->STAT);
}


/**********************************************************************
 * @brief		Code Flash Access Status Clear
 * @param[in]	Clear Flag
 *					- CFMC_STAT_WTERR_Msk	: (1<<22)
 *					- CFMC_STAT_RPERR_Msk	: (1<<21)
 *					- CFMC_STAT_WSERR_Msk	: (1<<20)
 *					- CFMC_STAT_OPERR_Msk	: (1<<19)
 *					- CFMC_STAT_FPERR_Msk	: (1<<18)
 *					- CFMC_STAT_OLERR_Msk	: (1<<17)
 *					- CFMC_STAT_FLERR_Msk	: (1<<16)
 *					- CFMC_STAT_CDONE_Msk	: (1<<9)
 *					- CFMC_STAT_WDONE_Msk	: (1<<8)
 * @return		None
 *
 **********************************************************************/
void CFMC_ClearAccessStatus(uint32_t ClearSRC)
{
	CFMC->STAT = ClearSRC;
}


/**********************************************************************
 * @brief		Code Flash Checksum Control Register
 * @param[in]	Control bit
 *					- CFMC_CHKCTRL_CDRST_RST	: (1<<16)
 *					- CFMC_CHKCTRL_CDIEN_ON		: (1<<8)
 *					- CFMC_CHKCTRL_BSTEN_ON		: (1<<1)
 *					- CFMC_CHKCTRL_BACKGROUND_ON: (1<<0)
 * @param[in]	NewState
 *					- Enable : Bit Enable
 * 					- Disable : Bit Disable
 * @return		None
 *
 **********************************************************************/
void CFMC_FlashChecksumCmd(uint32_t ControlBit, FunctionalState NewState)
{
	uint32_t		reg_val;
	
	reg_val = CFMC->CHKCTRL;	
	reg_val &= ~(ControlBit);
	
	if (NewState == ENABLE)	{
		reg_val |= (ControlBit);
	}
	
	CFMC->CHKCTRL = reg_val;
}


/**********************************************************************
 * @brief		Code Flash Checksum Data output Register
 * @param[in]	
 *
 * @return		Checksum Data
 *
 **********************************************************************/
uint32_t CFMC_GetChecksumData(void)
{
	return (CFMC->CHKDOUT & 0x0000ffff);
}


/**********************************************************************
 * @brief		Get Code Flash Checksum Config Register
 * @param[in]	
 *
 * @return		Config Data
 *
 **********************************************************************/
uint32_t CFMC_GetChecksumCmd(void)
{
	return (CFMC->CHKCTRL & 0x00010103);
}


/**********************************************************************
 * @brief		Code Flash Checksum Address Register
 * @param[in]	StartAddress
 * 				StartAddress = [31:6] bit
 * 				Fixed Address = [5:0] bit - '0'
 *
 *				EndAddress
 * 				EndAddress = [31:6] bit
 *				Fixed Address = [5:0] bit - '1'
 *
 * 				If Start address = 0, End Address = 0
 * 				   0x0000_0000 ~ 0x0000_003F
 *
 * 				Checksum Area Calculation
 *				   Start Address ~ (((End Address+1)*64)-1), (Start Address <= End Address)
 *
 * @return		None
 *
 **********************************************************************/
void CFMC_ChecksumAddrCmd(uint32_t StartAddress, uint32_t EndAddress)
{
	CFMC->CHKSADDR = (StartAddress<<CFMC_CHKSADDR_SADDR_Pos);	
	CFMC->CHKEADDR = (EndAddress<<CFMC_CHKEADDR_EADDR_Pos);
}


void cflash_acc_status_check (void)
{
	if((CFMC_GetAccessStatus()&CFMC_STAT_WDONE_Msk) == CFMC_STAT_WDONE_Msk) {
		__NOP(); __NOP(); __NOP(); __NOP(); __NOP();
		CFMC->STAT = (1<<CFMC_STAT_WDONE_Pos);
		//_DBG("WDONE\r\n");
	}

	if((CFMC_GetAccessStatus()&CFMC_STAT_CDONE_Msk) == CFMC_STAT_CDONE_Msk) {
		__NOP(); __NOP(); __NOP(); __NOP(); __NOP();
		CFMC->STAT = (1<<CFMC_STAT_CDONE_Pos);
		//_DBG("CDONE\r\n");
	}

	if((CFMC_GetAccessStatus()&CFMC_STAT_FLERR_Msk) == CFMC_STAT_FLERR_Msk) {
		__NOP(); __NOP(); __NOP(); __NOP(); __NOP();
		CFMC->STAT = (1<<CFMC_STAT_FLERR_Pos);
		//_DBG("FLERR\r\n");
		// TODO: action for error
	}
	if((CFMC_GetAccessStatus()&CFMC_STAT_OLERR_Msk) == CFMC_STAT_OLERR_Msk) {
		__NOP(); __NOP(); __NOP(); __NOP(); __NOP();
		CFMC->STAT = (1<<CFMC_STAT_OLERR_Pos);		//220914 fixed
		//_DBG("ILERR\r\n");
	}
	if((CFMC_GetAccessStatus()&CFMC_STAT_FPERR_Msk) == CFMC_STAT_FPERR_Msk) {
		__NOP(); __NOP(); __NOP(); __NOP(); __NOP();
		CFMC->STAT = (1<<CFMC_STAT_FPERR_Pos);
		//_DBG("FPERR\r\n");
		// TODO: action for error
	}
	if((CFMC_GetAccessStatus()&CFMC_STAT_OPERR_Msk) == CFMC_STAT_OPERR_Msk) {
		__NOP(); __NOP(); __NOP(); __NOP(); __NOP();//220914 fixed
		CFMC->STAT = (1<<CFMC_STAT_OPERR_Pos);
		//_DBG("IPERR\r\n");
		// TODO: action for error
	}
	if((CFMC_GetAccessStatus()&CFMC_STAT_WSERR_Msk) == CFMC_STAT_WSERR_Msk) {
		__NOP(); __NOP(); __NOP(); __NOP(); __NOP();
		CFMC->STAT |= (1<<CFMC_STAT_WSERR_Pos);
		//_DBG("WSERR\r\n");
		// TODO: action for error
	}
}

/**
********************************************************************************************************
* @ Name : CFMCErase
*
* @ Parameters
*		Ersmod			Erase mode select
*						- CFMC_CTRL_CERS		(1UL<<4)
*						- CFMC_CTRL_SERS		(1UL<<2)
*						- CFMC_CTRL_PERS		(1UL<<1)
*		addr			start address of flash memory to be erase (in terms of byte)
*
********************************************************************************************************
*/
void CFMCErase(uint32_t Ersmod, unsigned long addr)
{
	uint32_t		reg_val;
	
	__NOP();	__NOP();	__NOP();	__NOP();
	
	CFMC_WRITE_BUSY_POLLING;	
	reg_val = CFMC->CTRL;	
	reg_val &= ~(Ersmod);
	reg_val |= (Ersmod);	
	CFMC->CTRL = reg_val;
	
	MIO32(addr) = 0x0;
#ifdef FLASH_ACC_INT_MODE
	while(!flash_acc_write_done);
	flash_acc_write_done = 0;
#else
	CFMC_WRITE_BUSY_POLLING;
#endif
	
	CFMC->CTRL &= ~(Ersmod);	
	cflash_acc_status_check();
	
}

/**********************************************************************
 * @brief		Code Flash Write Enable
 * @param[in]	NewState
 *					- Enable : Bit Enable
 * 					- Disable : Bit Disable
 * @return		None
 *
 **********************************************************************/
void CFMC_WriteCmd(FunctionalState NewState)
{
	uint32_t		reg_val;
	
	reg_val = CFMC->CONF;	
	reg_val &= ~CFMC_CONF_WRITE_Msk;	
	if (NewState == ENABLE)	{
		reg_val |= CFMC_CONF_WRITE_Msk;
	}
	CFMC->CONF = reg_val;
}

/**
********************************************************************************************************
* @ Name : CFMCProgramPage
*
*
* @ Parameters
*		addr				start address of flash memory to be written (in terms of byte)
*		size				write size (in terms of byte)
*		buf				start address of buffer 
*
*
*
********************************************************************************************************
*/
void CFMCProgramPage (unsigned long addr, unsigned long size, unsigned char *buf)
{
	unsigned long *ptr;
	int 					i;

	ptr = (unsigned long*)buf;

	__NOP();
	__NOP();
	__NOP();
	__NOP();
	__NOP();
	
	__NOP();
	__NOP();
	__NOP();

	CFMC_WRITE_BUSY_POLLING;
	
	__NOP();
	__NOP();
	__NOP();
	__NOP();
	
	CFMC->CTRL |= CFMC_CTRL_PGM_Msk;
	

	for (i=0; i<size; i++) {
		
	MIO32(addr+(i*4)) = *ptr++;

	__NOP();
	__NOP();
	__NOP();
	__NOP();	
	
	CFMC_WRITE_BUSY_POLLING;
		
	}

	__NOP();
	__NOP();
	__NOP();
	__NOP();

	CFMC->CTRL &= ~(CFMC_CTRL_PGM_Msk);
	
	cflash_acc_status_check();

}

/**
********************************************************************************************************
* @ Name : CMFCVerify
*
*
* @ Parameters
*		addr				start address of flash memory to be written (in terms of byte)
*		size				write size (in terms of byte)
*		buf				start address of buffer 
*
*
* @ return value
*		(addr+size)		success
*		other value		error 
*
********************************************************************************************************
*/
unsigned long CFMCVerify (unsigned long addr, unsigned long size, unsigned char *buf)
{
	unsigned long			i; 
	unsigned char			*p_org, *p_flash; 
	unsigned long			result; 
	volatile unsigned long	reg_val; 


//	unsigned char test[4];
//	test[0]= 0xAA;
//	test[1]= 0x55;
//	test[2] =0xAA;
//	test[3] = 0x55;
	
	//---------------------------------------------------------------------------------
	// init variable 
	//---------------------------------------------------------------------------------
	result = addr + size; 


	
	//---------------------------------------------------------------------------------
	// verify 
	//---------------------------------------------------------------------------------
	p_org = (unsigned char *) buf; 
	p_flash = (unsigned char *) addr; 


	for (i=0; i<size; i ++)
	{
//		if (*p_flash++ != test[i%4])
		if (*p_flash++ != *p_org++)
		{
			result = addr + i; 
			break; 
		}			
	}
	
	return (result); 

}

/* --------------------------------- End Of File ------------------------------ */

