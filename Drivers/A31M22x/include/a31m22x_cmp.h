/**
 *******************************************************************************
 * @file        a31m22x_cmp.h
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


#ifndef _A31M22X_CMP_H_
#define _A31M22X_CMP_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>
#include "a31m22x_driver_common.h"
#include "a31m22x_dma.h"

/**
 * CMP instance id
 */
enum cmp_id
{
    CMP_ID_0   = 0,                        /**< CMP 0 */
    CMP_ID_MAX = 1,                        /**< CMP max */	
};

/**
 * COMP Filter divider
 */
enum cmp_div
{
    CMP_DIV_0,                          /**< Filter divider 0 */
    CMP_DIV_1,                          /**< Filter divider 1 */
    CMP_DIV_2,                          /**< Filter divider 2 */
    CMP_DIV_3,                          /**< Filter divider 3 */
    CMP_FILTER_MAX,                        /**< Filter count MAX - should not used this */
};

/**
 * CMP hystresis
 */
enum cmp_hystresis_type
{
    CMP_HYSTRESIS_NONE,                    /**< hystresis disabled */
    CMP_HYSTRESIS_10MV,                     /**< hystresis 10mV */
    CMP_HYSTRESIS_20MV,                    /**< hystresis 20mV */
    CMP_HYSTRESIS_30MV,                     /**< hystresis 30mV */
    CMP_HYSTRESIS_40MV,                    /**< hystresis 40mV */
};

/**
 * CMP interrupt type
 */
enum cmp_irq_type
{
    CMP_IRQ_NONE,                          /**< interrupt disabled */
    CMP_IRQ_LEVEL,                         /**< interrupt on level */
    CMP_IRQ_LOW_EDGE,                      /**< interrupt on low (falling) edge */
    CMP_IRQ_HIGH_EDGE,                     /**< interrupt on high (rising) edge */
    CMP_IRQ_BOTH_EDGE,                     /**< interrupt on both edges */
};

/**
 * CMP input reference negative selection
 */
enum cmp_input_neg
{
    CMP_INPUT_NEG_INPUT0,                  /**< negative reference 0 */
    CMP_INPUT_NEG_INPUT1,                  /**< negative reference 1 */
	  CMP_INPUT_NEG_INPUT2,                  /**< negative reference 2 */
};

/**
 * CMP input reference positive selection
 */
enum cmp_input_pos
{
    CMP_INPUT_POS_INPUT0,                  /**< positive input 0 */
    CMP_INPUT_POS_INPUT1,                  /**< positive input 1 */
    CMP_INPUT_POS_INPUT2,                  /**< positive input 2 */
    CMP_INPUT_POS_INPUT3,                  /**< positive input 3 */
};

/**
 * CMP status
 */
enum cmp_status
{
    CMP_STATUS_DOWN,                       /**< comparator voltage crossed down */
    CMP_STATUS_UP,                         /**< comparator voltage crossed up */
};

/**
 * CMP event
 */
enum cmp_event
{
    CMP_EVENT_UP   = BIT(0),               /**< comparater triggered */
    CMP_EVENT_DOWN = BIT(0),               /**< comparater triggered */
};

/**
 *******************************************************************************
 * @brief       CMP interrupt callback function type
 * @param[in]   event event type ::comp_event
 * @param[in]   context context provided during initialization
 ******************************************************************************/
typedef void (*cmp_irq_handler_t)(uint32_t event, void *context);

/**
 * CMP configuration
 */
struct cmp_cfg
{
    uint8_t             filter_count;     /**< filter count*/
	  enum cmp_div           filter_div;     /**< filter divider*/
    enum cmp_hystresis_type    hystresis;  /**< hystresis */
    enum cmp_irq_type          irq_type;   /**< interrupt type */
    enum cmp_input_neg         input_neg;  /**< negative input */
    enum cmp_input_pos         input_pos;  /**< positive input */
    uint8_t                     irq_prio;   /**< interrupt priority */
};

/**
 *******************************************************************************
 * @brief       Initialize CMP
 * @param[in]   id instance id
 * @param[in]   cfg configuration
 * @param[in]   handler callback function to receive event
 * @param[in]   context caller's context
 * @return      driver error code
 ******************************************************************************/
int32_t HAL_CMP_Init(enum cmp_id id, struct cmp_cfg *cfg,
                      cmp_irq_handler_t handler,
                      void *context);

/**
 *******************************************************************************
 * @brief       Deintialize CMP.
 * @param[in]   id instance id
 * @return      driver error code
 ******************************************************************************/
int32_t HAL_CMP_Deinit(enum cmp_id id);

/**
 *******************************************************************************
 * @brief       Start COMP.
 * @param[in]   id instance id
 * @return      driver error code
 ******************************************************************************/
int32_t HAL_CMP_Start(enum cmp_id id);

/**
 *******************************************************************************
 * @brief       Stop CMP.
 * @param[in]   id instance id
 * @return      driver error code
 ******************************************************************************/
int32_t HAL_CMP_Stop(enum cmp_id id);

/**
 *******************************************************************************
 * @brief       Get CMP output status.
 * @param[in]   id instance id
 * @param[out]  status status of the output
 * @return      driver error code
 ******************************************************************************/
int32_t HAL_CMP_GetStatus(enum cmp_id id, uint8_t *status);



#ifdef __cplusplus
}
#endif

#endif /* _A31M22X_CMP_H_ */

/** @} */
/** @} */

