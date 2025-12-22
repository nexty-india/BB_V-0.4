/**
 *******************************************************************************
 * @file        a31m22x_flash.h
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


#ifndef _A31M22X_FLASH_H_
#define _A31M22X_FLASH_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>
#include "a31m22x_driver_common.h"

/** Flash write busy  time-out definitions in case of using function
 * with Blocking Flag mode
 */
#define FLASH_BUSY_BLOCKING_TIMEOUT         (0x35000UL)

/**
 * flash area type
 */
enum flash_area
{
    FLASH_AREA_CODE = 0,                    /**< flash code area, used for instruction and data */
};

/**
 * flash section size
 */
enum flash_sector_size
{
    FLASH_SECTOR_SIZE_512B  = 0,            /**< sector size as 512 byte */
    FLASH_SECTOR_SIZE_2KB   = 1,            /**< sector size as 2048 byte */
};

/**
 * flash protection for 64k byte code area
 */
enum flash_prot64k_code_sector
{
    FLASH_PROT64K_CODE_SECTOR0  = BIT(0),   /**< 0x0000_0000 ~ 0x0000_1000 protect */
    FLASH_PROT64K_CODE_SECTOR1  = BIT(1),   /**< 0x0000_1000 ~ 0x0000_2000 protect */
    FLASH_PROT64K_CODE_SECTOR2  = BIT(2),   /**< 0x0000_2000 ~ 0x0000_3000 protect */
    FLASH_PROT64K_CODE_SECTOR3  = BIT(3),   /**< 0x0000_3000 ~ 0x0000_4000 protect */
    FLASH_PROT64K_CODE_SECTOR4  = BIT(4),   /**< 0x0000_4000 ~ 0x0000_5000 protect */
    FLASH_PROT64K_CODE_SECTOR5  = BIT(5),   /**< 0x0000_5000 ~ 0x0000_6000 protect */
    FLASH_PROT64K_CODE_SECTOR6  = BIT(6),   /**< 0x0000_6000 ~ 0x0000_7000 protect */
    FLASH_PROT64K_CODE_SECTOR7  = BIT(7),   /**< 0x0000_7000 ~ 0x0000_8000 protect */
    FLASH_PROT64K_CODE_SECTOR8  = BIT(8),   /**< 0x0000_8000 ~ 0x0000_9000 protect */
    FLASH_PROT64K_CODE_SECTOR9  = BIT(9),   /**< 0x0000_9000 ~ 0x0000_A000 protect */
    FLASH_PROT64K_CODE_SECTOR10 = BIT(10),  /**< 0x0000_A000 ~ 0x0000_B000 protect */
    FLASH_PROT64K_CODE_SECTOR11 = BIT(11),  /**< 0x0000_B000 ~ 0x0000_C000 protect */
    FLASH_PROT64K_CODE_SECTOR12 = BIT(12),  /**< 0x0000_C000 ~ 0x0000_D000 protect */
    FLASH_PROT64K_CODE_SECTOR13 = BIT(13),  /**< 0x0000_D000 ~ 0x0000_E000 protect */
    FLASH_PROT64K_CODE_SECTOR14 = BIT(14),  /**< 0x0000_E000 ~ 0x0000_F000 protect */
    FLASH_PROT64K_CODE_SECTOR15 = BIT(15),  /**< 0x0000_F000 ~ 0x0001_0000 protect */
};

/**
 * flash protection for 512 byte code area
 * - A31M223
 *   Sector 0 : 0x0000_F000 ~ 0x0000_F1FF
 *   Sector 1 : 0x0000_F200 ~ 0x0000_F3FF
 *   Sector 2 : 0x0000_F400 ~ 0x0000_F5FF
 *   Sector 3 : 0x0000_F600 ~ 0x0000_F7FF
 *   Sector 4 : 0x0000_F800 ~ 0x0000_F9FF
 *   Sector 5 : 0x0000_FA00 ~ 0x0000_FBFF
 *   Sector 6 : 0x0000_FC00 ~ 0x0000_FDFF
 *   Sector 7 : 0x0000_FE00 ~ 0x0000_FFFF
 */
enum flash_prot512b_code_sector
{
    FLASH_PROT512B_CODE_SECTOR0 = BIT(0),
    FLASH_PROT512B_CODE_SECTOR1 = BIT(1),
    FLASH_PROT512B_CODE_SECTOR2 = BIT(2),
    FLASH_PROT512B_CODE_SECTOR3 = BIT(3),
    FLASH_PROT512B_CODE_SECTOR4 = BIT(4),
    FLASH_PROT512B_CODE_SECTOR5 = BIT(5),
    FLASH_PROT512B_CODE_SECTOR6 = BIT(6),
    FLASH_PROT512B_CODE_SECTOR7 = BIT(7),
};

/**
 * flash protection level
 */
enum flash_read_prot_lvl
{
    FLASH_READ_PROT_LVL_UNPROTECT   = 0,    /**< flash protection none */
    FLASH_READ_PROT_LVL_1           = 1,    /**< flash protection leve 1 */
    FLASH_READ_PROT_LVL_1_ONE_PW    = 2,    /**< flash protection leve 1 with one password */
    FLASH_READ_PROT_LVL_2_TWO_PW    = 3,    /**< flash protection leve 2 with two password */
    FLASH_READ_PROT_LVL_2_NO_PW     = 4,    /**< flash protection leve 2 with no password */
};

/**
 *******************************************************************************
 * @brief       Flash initalize
 * @return      driver error code
 ******************************************************************************/
int32_t HAL_FLASH_Init(void);

/**
 *******************************************************************************
 * @brief       Read flash memory.
 * @param[in]   flash_addr address of the memory to read
 * @param[out]  data pointer to the memory the data is to be copied to.
 * @param[in]   len length of the memory to read
 * @return      driver error code
 ******************************************************************************/
int32_t HAL_FLASH_Read(uint32_t flash_addr, uint8_t *data, uint32_t len);

/**
 *******************************************************************************
 * @brief       Write flash memory.
 *              The memory must be erased first to write new data.
 *              - memory address can be byte aligned.
 * @param[in]   flash_addr address of the memory to read
 * @param[in]   data pointer to the memory the data is to be copied from.
 * @param[in]   len length of the memory to write
 * @return      driver error code
 ******************************************************************************/
int32_t HAL_FLASH_Write(uint32_t flash_addr, uint8_t *data, uint32_t len);

/**
 *******************************************************************************
 * @brief       Erase flash memory. The whole sector at the
 *              specified memory will be erased.
 * @param[in]   flash_addr address of the memory to erase
 * @return      driver error code
 ******************************************************************************/
int32_t HAL_FLASH_Erase(uint32_t flash_addr);

/**
 *******************************************************************************
 * @brief       Read from OTP flash memory.
 * @param[in]   otp_addr address of the memory to read
 * @param[in]   data pointer to the memory the data is to be copied to.
 * @param[in]   len length of the memory to read
 * @return      driver error code
 ******************************************************************************/
int32_t HAL_FLASH_OTP_Read(uint32_t otp_addr, uint8_t *data, uint32_t len);

/**
 *******************************************************************************
 * @brief       This function set flash erase sector size.
 * @param[in]   area flash area (::flash_area)
 * @param[in]   sector_size flash sector size (::flash_sector_size)
 * @return      driver error code
 ******************************************************************************/
int32_t HAL_FLASH_SetEraseSecotorSize(enum flash_area area, enum flash_sector_size sector_size);

/**
 *******************************************************************************
 * @brief       This function enable write/erase protect of code area by 64kb unit.
 * @param[in]   sector protection sector (::flash_prot32k_code_sector)
 * @param[in]   enable 1 to enable, 0 to disable
 * @return      driver error code
 ******************************************************************************/
int32_t HAL_FLASH_SetWriteProtect64KCodeArea(enum flash_prot64k_code_sector sector, uint8_t enable);

/**
 *******************************************************************************
 * @brief       This function enable write/erase protect of code area by 512b unit.
 * @param[in]   sector protection sector (::flash_prot512b_code_sector)
 * @param[in]   enable 1 to enable, 0 to disable
 * @return      driver error code
 ******************************************************************************/
int32_t HAL_FLASH_SetWriteProtect512BCodeArea(enum flash_prot512b_code_sector sector, uint8_t enable);

/**
 *******************************************************************************
 * @brief       This function select read protection level in debug mode.
 * @param[in]   prot_lvl protection level (::flash_read_prot_lvl)
 * @return      driver error code
 ******************************************************************************/
int32_t HAL_FLASH_SetReadProtectCodeArea(enum flash_read_prot_lvl prot_lvl);

/**
 *******************************************************************************
 * @brief       This function select read protection level in debug mode.
 * @param[in]   prot_lvl protection level (::flash_read_prot_lvl)
 * @return      driver error code
 ******************************************************************************/
int32_t HAL_CFMC_FlashAccessCmd(uint8_t enable);

/**
 *******************************************************************************
 * @brief       Read from opt flash memory.
 * @param[in]   opt_addr address of the memory to read
 * @param[in]   data pointer to the memory the data is to be copied to.
 * @param[in]   len length of the memory to read
 * @return      driver error code
 ******************************************************************************/
int32_t HAL_FLASH_OPT_Read(uint32_t info_addr, uint8_t *data, uint32_t len);

#endif /* _A31M22X_FLASH_H_ */

/** @} */
/** @} */

