/**
 *******************************************************************************
 * @file        a31m22x_opamp.h
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



#ifndef _A31M22X_OPAMP_H_
#define _A31M22X_OPAMP_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>
#include "a31m22x_driver_common.h"


/**
 * OPAMP id
 */
enum opamp_id
{
    OPAMP_ID_0,                               /**< OPAMP 0 */
    OPAMP_ID_1,                               /**< OPAMP 1 */
    OPAMP_ID_2,                               /**< OPAMP 2 */
    OPAMP_ID_MAX,                             /**< OPAMP max */
};

/**
 * OPAMP unit gain
 */
enum opamp_ugain
{
    OPAMP_UGAIN_DISABLE   = 0,                /**< unit gain disable */
    OPAMP_UGAIN_ENABLE    = 1,                /**< unit gain enable  */
};

/**
 * OPAMP driver configuration
 */
struct opamp_cfg
{
    enum opamp_ugain      ugain;              /**< unity gain - disabling gain */
};

/**
 *******************************************************************************
 * @brief       Initialize OPAMP.
 * @param[in]   id instance id
 * @param[in]   cfg configuration
 * @return      driver error code
 ******************************************************************************/
int32_t HAL_OPAMP_Init(enum opamp_id id, struct opamp_cfg *cfg);

/**
 *******************************************************************************
 * @brief       Deinitialize OPAMP.
 * @param[in]   id instance id
 * @return      driver error code
 ******************************************************************************/
int32_t HAL_OPAMP_Deinit(enum opamp_id id);

/**
 *******************************************************************************
 * @brief       Start OPAMP.
 * @param[in]   id instance id
 * @return      driver error code
 ******************************************************************************/
int32_t HAL_OPAMP_Start(enum opamp_id id);

/**
 *******************************************************************************
 * @brief       Stop OPAMP.
 * @param[in]   id instance id
 * @return      driver error code
 ******************************************************************************/
int32_t HAL_OPAMP_Stop(enum opamp_id id);


#ifdef __cplusplus
}
#endif

#endif /* _A31M22X_OPAMP_H_ */

/** @} */
/** @} */

