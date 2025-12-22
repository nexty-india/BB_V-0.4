/**
 *******************************************************************************
 * @file        a31m22x_mpwm.h
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


#ifndef _A31M22X_MPWM_H_
#define _A31M22X_MPWM_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>
#include "a31m22x_driver_common.h"

/**
 * MPWM instance id
 */
enum mpwm_id
{
    MPWM_ID_0   = 0,                        /**< MPWM 0 */
    MPWM_ID_MAX = 1,                        /**< MPWM max */
};

/**
 * MPWM mode
 */
enum mpwm_mode
{
    MPWM_MODE_MOTOR         = 0,            /**< MPWM moter mode */
    MPWM_MODE_NORMAL        = 1,            /**< MPWM nomral mode */
};

/**
 * MPWM channel mode
 */
enum mpwm_chan_mode
{
    MPWM_CHAN_MODE_2CH_SYMMETRIC    = 0,    /**< Two-channel symmetric mode */
    MPWM_CHAN_MODE_1CH_ASYMMETRIC   = 1,    /**< One-channel asymmetric mode */
    MPWM_CHAN_MODE_1CH_SYMMETRIC    = 2,    /**< One-channel symmetric mode */
};

/**
 * MPWM counter mode
 */
enum mpwm_counter_mode
{
    MPWM_COUNTER_MODE_UP        = 0,        /**< PWM up counter mode(support only MPWM normal mode) */
    MPWM_COUNTER_MODE_UPDOWN    = 1,        /**< PWM up-down counter mode */
};

/**
 * MPWM phase type
 */
enum mpwm_phase_type
{
    MPWM_PHASE_TYPE_U   = 0,                /**< MPWM phase U */
    MPWM_PHASE_TYPE_V   = 1,                /**< MPWM phase V */
    MPWM_PHASE_TYPE_W   = 2,                /**< MPWM phase W */
    MPWM_PHASE_TYPE_ALL = 3,                /**< MPWM phase ALL */
};

/**
 * MPWM output type
 */
enum mpwm_output_type
{
    MPWM_OUTPUT_TYPE_L  = 0,                /**< output high */
    MPWM_OUTPUT_TYPE_H  = 1,                /**< output low */
};

/**
 * MPWM dead time mode
 */
enum mpwm_dead_time_mode
{
    MPWM_DEAD_TIME_MODE_LH_TL   = 0,        /**< Inserts dead time at the leading edge of MPWMxH and the trailing edge of MPWMxL */
    MPWM_DEAD_TIME_MODE_TH_LL   = 1,        /**< Inserts dead time at the trailing edge of MPWMxH and the leading edge of MPWMxL */
};

/**
 * MPWM dead clock div
 */
enum mpwm_dead_time_clk
{
    MPWM_DEAD_TIME_CLK_PWM_DIV_2    = 0,    /**< MPWM clock devide 2 */
    MPWM_DEAD_TIME_CLK_PWM_DIV_4    = 1,    /**< MPWM clock devide 4 */
    MPWM_DEAD_TIME_CLK_PWM_DIV_8    = 2,    /**< MPWM clock devide 8 */
    MPWM_DEAD_TIME_CLK_PWM_DIV_16   = 3,    /**< MPWM clock devide 16 */
};

/**
 * MPWM trigger souce of ADC
 */
enum mpwm_adc_trigger_source
{
    MPWM_ADC_TRIGGER_SOURCE_U_COUNTER   = 0,    /**< Set MPWM phase U to trigger of ADC */
    MPWM_ADC_TRIGGER_SOURCE_V_COUNTER   = 1,    /**< Set MPWM phase V to trigger of ADC */
    MPWM_ADC_TRIGGER_SOURCE_W_COUNTER   = 2,    /**< Set MPWM phase W to trigger of ADC */
};

/**
 * MPWM trigger mode of ADC
 */
enum mpwm_adc_trigger_mode
{
    MPWM_ADC_TRIGGER_MODE_DISABLE       = 0,    /**< Disable trigger mode */
    MPWM_ADC_TRIGGER_MODE_UP_COUNT      = 1,    /**< Set up count match trigger mode */
    MPWM_ADC_TRIGGER_MODE_DOWN_COUNT    = 2,    /**< Set down count match trigger mode */
    MPWM_ADC_TRIGGER_MODE_UPDOWN_COUNT  = 3,    /**< Set up-down count match trigger mode */
};

/**
 * MPWM trigger id of ADC
 */
enum mpwm_trgger_id
{
    MPWM_TRGGER_ID_1    = 0,            /**< MPWM Trigger 1 */
    MPWM_TRGGER_ID_2    = 1,            /**< MPWM Trigger 2 */
    MPWM_TRGGER_ID_3    = 2,            /**< MPWM Trigger 3 */
    MPWM_TRGGER_ID_4    = 3,            /**< MPWM Trigger 4 */
    MPWM_TRGGER_ID_5    = 4,            /**< MPWM Trigger 5 */
    MPWM_TRGGER_ID_6    = 5,            /**< MPWM Trigger 6 */
    MPWM_TRGGER_ID_MAX  = 6,            /**< MPWM Trigger max */
};

/**
 * MPWM interrupt event type
 */
enum mpwm_irq_event_type
{
    MPWM_IRQ_EVENT_TYPE_PRT     = 0,    /**< IRQ event protection */
    MPWM_IRQ_EVENT_TYPE_OC      = 1,    /**< IRQ event over current */
    MPWM_IRQ_EVENT_TYPE_MPWM    = 2,    /**< IRQ event MPWM(bottom/period/duty/ATR) */
};

/**
 *******************************************************************************
 * @brief       MWPM interrupt callback function type
 * @param[in]   event event type (::mpwm_irq_event_type)
 * @param[in]   context context provided during initialization
 ******************************************************************************/
typedef void (*mpwm_irq_handler_t)(uint32_t evnet, void *context);

/**
 * MPWM configuration
 */
struct mpwm_cfg
{
    enum mpwm_mode          mode;           /**< MPWM mode */
    enum mpwm_chan_mode     chan_mode;      /**< MPWM channel mode */
    enum mpwm_counter_mode  counter_mode;   /**< MPWM counter mode */
    uint32_t                clk_div;        /**< MPWM clock divider value */
};

/**
 * MPWM interrupt type
 */
struct irq_en_flag
{
    uint32_t    period : 1;                 /**< nornmal or moter mode period irq */
    uint32_t    bottom : 1;                 /**< nornmal or moter mode bottom irq */
    uint32_t    uh_duty : 1;                /**< phase u output high duty irq */
    uint32_t    vh_duty : 1;                /**< phase v output high duty irq */
    uint32_t    wh_duty : 1;                /**< phase w output high duty irq */
    uint32_t    ul_duty : 1;                /**< phase u output low duty irq */
    uint32_t    vl_duty : 1;                /**< phase v output low duty irq */
    uint32_t    wl_duty : 1;                /**< phase w output low duty irq */
    uint32_t    atr_1 : 1;                  /**< ADC trigger ID 1 irq */
    uint32_t    atr_2 : 1;                  /**< ADC trigger ID 2 irq */
    uint32_t    atr_3 : 1;                  /**< ADC trigger ID 3 irq */
    uint32_t    atr_4 : 1;                  /**< ADC trigger ID 4 irq */
    uint32_t    atr_5 : 1;                  /**< ADC trigger ID 5 irq */
    uint32_t    atr_6 : 1;                  /**< ADC trigger ID 6 irq */
    uint32_t    protect : 1;                /**< protection irq */
    uint32_t    over_current : 1;           /**< over current irq */
#if defined (__CC_ARM) || defined (__GNUC__)
} __attribute__((packed));
#elif defined (__ICCARM__)
#pragma pack(1)
};
#pragma pack()
#endif

/**
 * MPWM interrupt configuration
 */
union mpwm_irq_cfg
{
    struct irq_en_flag  irq_en_bit;         /**< interrupt bit of type */
    uint32_t            irq_en;             /**< interrupt value of type */
};

/**
 * MPWM input protection configuration
 */
struct mpwm_input_prt_cfg
{
    uint32_t polarity;                      /**< input polarity (0:L-active, 1:H-active) */
    uint32_t clk_div;                       /**< clock divider */
    uint32_t debounce;                      /**< debounce time (0:no debounce, 0x01 ~ 0xFF:MPWM clock * debounce, ) */
    uint32_t enable_prt3;                   /**< enable or disable ADC comparator 1 protection  */
    uint32_t enable_prt2;                   /**< enable or disable ADC comparator 0 protection  */
    uint32_t enable_prt1;                   /**< enable or disable CMP protection  */
    uint32_t enable_prt0;                   /**< enable or disable PRTIN pin protection  */
};

/**
 * MPWM input over current configuration
 */
struct mpwm_input_oc_cfg
{
    uint32_t enable_ovp3;                    /**< enable or disable ADC comparator 1 protection  */
    uint32_t enable_ovp2;                    /**< enable or disable ADC comparator 0 protection  */
    uint32_t enable_ovp1;                    /**< enable or disable CMP protection  */
    uint32_t enable_ovp0;                    /**< enable or disable OVPIN pin protection  */
};

/**
 * MPWM deatime configuration
 */
struct mpwm_dt_cfg
{
    uint32_t                    enable;                     /**< enable or disable dead time function */
    uint32_t                    short_circuit_protect_en;   /**< enable of disable short circuit protection */
    uint32_t                    ouput_level_high_side;      /**< dead time output level of high side */
    uint32_t                    ouput_level_low_side;       /**< dead time output level of low side */
    enum mpwm_dead_time_mode    mode;                       /**< unused */
    enum mpwm_dead_time_clk     clk;                        /**< prescalter of dead time */
    uint32_t                    dead_time;                  /**< dead time value */
};

/**
 * MPWM ADC trigger configuration
 */
struct mpwm_adc_tr_cfg
{
    enum mpwm_adc_trigger_source    tr_src;         /**< unused */
    uint32_t                        reg_mode;       /**< ADC register update mode */
    enum mpwm_adc_trigger_mode      mode;           /**< ADC trigger mode */
    uint32_t                        tr_count;       /**< ADC trigger count value */
};

/**
 *******************************************************************************
 * @brief       Initialize MPWM.
 * @param[in]   id instance id
 * @param[in]   cfg configuration
 * @param[in]   handler callback function to receive event
 * @param[in]   context caller's context
 * @return      driver error code
 ******************************************************************************/
int32_t HAL_MPWM_Init(enum mpwm_id id, struct mpwm_cfg *cfg,
                      mpwm_irq_handler_t handler,
                      void *context);

/**
 *******************************************************************************
 * @brief       Deintialize MPWM.
 * @param[in]   id instance id
 * @return      driver error code
 ******************************************************************************/
int32_t HAL_MPWM_Deinit(enum mpwm_id id);

/**
 *******************************************************************************
 * @brief       configure MPWM interrupt type.
 * @param[in]   id instance id
 * @param[in]   cfg cofigureation
 * @return      driver error code
 ******************************************************************************/
int32_t HAL_MPWM_SetIRQConfig(enum mpwm_id id, union mpwm_irq_cfg *cfg);

/**
 *******************************************************************************
 * @brief       configure MPWM input protection.
                It is possible that set each phase protection in individual mode.
 * @param[in]   id instance id
 * @param[in]   p_type MPWM phase type
 * @param[in]   cfg cofigureation
 * @return      driver error code
 ******************************************************************************/
int32_t HAL_MPWM_SetPotectionInputConfig(enum mpwm_id id, enum mpwm_phase_type p_type,
                                         struct mpwm_input_prt_cfg *cfg);

/**
 *******************************************************************************
 * @brief       configure MPWM output protection.
 * @param[in]   id instance id
 * @param[in]   p_type MPWM phase type
 * @param[in]   ot MPWM output type
 * @param[in]   en enable
 * @return      driver error code
 ******************************************************************************/
int32_t HAL_MPWM_SetProtectionOutputConfig(enum mpwm_id id, enum mpwm_phase_type p_type,
                                           enum mpwm_output_type ot, uint32_t en);

/**
 *******************************************************************************
 * @brief       configure MPWM input over current.
                It is possible that set each phase over volatge in individual mode.
 * @param[in]   id instance id
 * @param[in]   p_type MPWM phase type
 * @param[in]   cfg cofigureation
 * @return      driver error code
 ******************************************************************************/
int32_t HAL_MPWM_SetOverCurrentInputConfig(enum mpwm_id id, enum mpwm_phase_type p_type,
                                           struct mpwm_input_oc_cfg *cfg);

/**
 *******************************************************************************
 * @brief       configure MPWM output over current.
 * @param[in]   id instance id
 * @param[in]   p_type MPWM phase type
 * @param[in]   ot MPWM output type
 * @param[in]   en enable
 * @return      driver error code
 ******************************************************************************/
int32_t HAL_MPWM_SetOverCurrentOutputConfig(enum mpwm_id id, enum mpwm_phase_type p_type,
                                            enum mpwm_output_type ot, uint32_t en);

/**
 *******************************************************************************
 * @brief       configure MPWM dead time.
                It is possible that set each phase dead time in individual mode.
 * @param[in]   id instance id
 * @param[in]   p_type MPWM phase type
 * @param[in]   cfg cofigureation
 * @return      driver error code
 ******************************************************************************/
int32_t HAL_MPWM_SetDeadTimeConfig(enum mpwm_id id, enum mpwm_phase_type p_type, struct mpwm_dt_cfg *cfg);

/**
 *******************************************************************************
 * @brief       configure MPWM trigger of ADC.
 * @param[in]   id instance id
 * @param[in]   t_id MPWM trigger id
 * @param[in]   cfg cofigureation
 * @return      driver error code
 ******************************************************************************/
int32_t HAL_MPWM_SetADCTriggerConfig(enum mpwm_id id, enum mpwm_trgger_id t_id, struct mpwm_adc_tr_cfg *cfg);

/**
 *******************************************************************************
 * @brief       set MPWM IRQ interval.
                It is possible that set each phase IRQ interval in individual mode.
 * @param[in]   id instance id
 * @param[in]   p_type MPWM phase type
 * @param[in]   irq_intv IRQ interval value
 * @return      driver error code
 ******************************************************************************/
int32_t HAL_MPWM_SetIRQinterval(enum mpwm_id id, enum mpwm_phase_type p_type,
                                uint32_t irq_intv);

/**
 *******************************************************************************
 * @brief       control MPWM output.
 * @param[in]   id instance id
 * @param[in]   p_type MPWM phase type
 * @param[in]   ot MPWM output type
 * @param[in]   en enable(1) or disable(0)
 * @return      driver error code
 ******************************************************************************/
int32_t HAL_MPWM_ControlPWMOutput(enum mpwm_id id,
                                        enum mpwm_phase_type p_type,
                                        enum mpwm_output_type ot, uint32_t en);

/**
 *******************************************************************************
 * @brief       set MPWM output level at disable phase.
 * @param[in]   id instance id
 * @param[in]   p_type MPWM phase type
 * @param[in]   ot MPWM output type
 * @param[in]   hl high(1) or low(0)
 * @return      driver error code
 ******************************************************************************/
int32_t HAL_MPWM_SetDisabledOutputLevel(enum mpwm_id id,
                                        enum mpwm_phase_type p_type,
                                        enum mpwm_output_type ot, uint32_t hl);

/**
 *******************************************************************************
 * @brief       set MPWM start output level.
 * @param[in]   id instance id
 * @param[in]   p_type MPWM phase type
 * @param[in]   ot MPWM output type
 * @param[in]   hl high(1) or low(0)
 * @return      driver error code
 ******************************************************************************/
int32_t HAL_MPWM_SetStartOutputLevel(enum mpwm_id id,
                                     enum mpwm_phase_type p_type,
                                     enum mpwm_output_type ot, uint32_t hl);

/**
 *******************************************************************************
 * @brief       set MPWM force output level.
 * @param[in]   id instance id
 * @param[in]   p_type MPWM phase type
 * @param[in]   ot MPWM output type
 * @param[in]   hl high(1) or low(0)
 * @return      driver error code
 ******************************************************************************/
int32_t HAL_MPWM_SetForceOutputLevel(enum mpwm_id id,
                                     enum mpwm_phase_type p_type,
                                     enum mpwm_output_type ot, uint8_t hl);

/**
 *******************************************************************************
 * @brief       set MPWM period.
                It is possible that set each phase period in individual mode.
 * @param[in]   id instance id
 * @param[in]   p_type MPWM phase type
 * @param[in]   prd period value
 * @return      driver error code
 ******************************************************************************/
int32_t HAL_MPWM_SetPeriod(enum mpwm_id id, enum mpwm_phase_type p_type, uint16_t prd);

/**
 *******************************************************************************
 * @brief       set MPWM duty.
 * @param[in]   id instance id
 * @param[in]   p_type MPWM phase type
 * @param[in]   ot MPWM output type
 * @param[in]   duty period value
 * @return      driver error code
 ******************************************************************************/
int32_t HAL_MPWM_SetDuty(enum mpwm_id id, enum mpwm_phase_type p_type,
                         enum mpwm_output_type ot, uint16_t duty);

/**
 *******************************************************************************
 * @brief       start MPWM.
                It is possible that start each phase in individual mode.
 * @param[in]   id instance id
 * @param[in]   p_type MPWM phase type
 * @return      driver error code
 ******************************************************************************/
int32_t HAL_MPWM_Start(enum mpwm_id id, enum mpwm_phase_type p_type);

/**
 *******************************************************************************
 * @brief       stop MPWM.
                It is possible that stop each phase in individual mode.
 * @param[in]   id instance id
 * @param[in]   p_type MPWM phase type
 * @return      driver error code
 ******************************************************************************/
int32_t HAL_MPWM_Stop(enum mpwm_id id, enum mpwm_phase_type p_type);

/**
 *******************************************************************************
 * @brief       Halt MPWM.
                It is possible that halt each phase in individual mode.
 * @param[in]   id instance id
 * @param[in]   p_type MPWM phase type
 * @return      driver error code
 ******************************************************************************/
int32_t HAL_MPWM_Halt(enum mpwm_id id, enum mpwm_phase_type p_type);

/**
 *******************************************************************************
 * @brief       Resume MPWM.
                It is possible that resume each phase in individual mode.
 * @param[in]   id instance id
 * @param[in]   p_type MPWM phase type
 * @return      driver error code
 ******************************************************************************/
int32_t HAL_MPWM_Resume(enum mpwm_id id, enum mpwm_phase_type p_type);

/**
 *******************************************************************************
 * @brief       read count.
                It is possible that read count of each phase in individual mode.
 * @param[in]   id instance id
 * @param[in]   p_type MPWM phase type
 * @param[out]  count MPWM count
 * @return      driver error code
 ******************************************************************************/
int32_t HAL_MPWM_ReadCount(enum mpwm_id id, enum mpwm_phase_type p_type, uint16_t *count);

/**
 *******************************************************************************
 * @brief       read status.
 * @param[in]   id instance id
 * @param[out]  status MPWM status
 * @return      driver error code
 ******************************************************************************/
int32_t HAL_MPWM_ReadStatus(enum mpwm_id id, uint32_t *status);

/**
 *******************************************************************************
 * @brief       read protection status.
 * @param[in]   id instance id
 * @param[out]  status MPWM protection status
 * @return      driver error code
 ******************************************************************************/
int32_t HAL_MPWM_ReadProtectionStatus(enum mpwm_id id, uint32_t *status);

/**
 *******************************************************************************
 * @brief       read prortion status.
 * @param[in]   id instance id
 * @param[out]  status MPWM over current status
 * @return      driver error code
 ******************************************************************************/
int32_t HAL_MPWM_ReadOverCurrentStatus(enum mpwm_id id, uint32_t *status);

/**
 *******************************************************************************
 * @brief       enable MPWM output.
 * @param[in]   id instance id
 * @return      driver error code
 ******************************************************************************/
int32_t HAL_MPWM_EnablePWMOutput(enum mpwm_id id);

/**
 *******************************************************************************
 * @brief       disable MPWM output.
 * @param[in]   id instance id
 * @return      driver error code
 ******************************************************************************/
int32_t HAL_MPWM_DisablePWMOutput(enum mpwm_id id);


#endif /* _A31M6XX_MPWM_H_ */

/** @} */
/** @} */

