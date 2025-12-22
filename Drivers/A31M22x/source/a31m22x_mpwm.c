/**
 *******************************************************************************
 * @file        a31m22x_mpwm.c
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


#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "a31m22x.h"
#include "a31m22x_scu.h"
#include "a31m22x_mpwm.h"

#define MPWM_FOLR_FOLKEY                   (0xCAUL)

#define MPWM_REG_BIT_SET(r, b, pos)        ((b == 1) ? (r |= (1UL << pos)) : (r &= ~(1UL << pos)))
#define MPWM_REG_BIT_SET2(r, b, b2, pos)   (((b == 1) || (b2 == 1)) ? (r |= (1UL << pos)) : (r &= ~(1UL << pos)))
#define MPWM_REG_VAL_SET(r, d, pos, msk)   r &= ~msk; r |= ((d << pos) & msk)

struct mpwm_ctrl_block
{
    uint8_t             mode;
    mpwm_irq_handler_t  handler;
    void *              context;
};

static struct mpwm_ctrl_block g_mcb[MPWM_ID_MAX];

static __INLINE MPWM_Type *MPWM_REG(enum mpwm_id id)
{
    return (MPWM_Type *)MPWM_BASE;
}

static void MPWM_Configure(MPWM_Type *mpwm, struct mpwm_cfg *cfg)
{
    uint32_t reg_val;

    reg_val = ((0x01UL << MPWM_MR_TFM_Pos) |
               (0x01UL << MPWM_MR_BFM_Pos) |
               ((cfg->clk_div << MPWM_MR_CLKDIV_Pos) & MPWM_MR_CLKDIV_Msk) |
               (cfg->mode << MPWM_MR_MOTORB_Pos) |
               (0x01UL << MPWM_MR_UOL_Pos) |
               (0x00UL << MPWM_MR_TUOL_Pos) |
               (0x00UL << MPWM_MR_BUOL_Pos) |
               (0x01UL << MPWM_MR_UAO_Pos) |
               (0x00UL << MPWM_MR_TUP_Pos) |
               (0x00UL << MPWM_MR_BUP_Pos));

    if (cfg->mode != MPWM_MODE_NORMAL)
    {
        reg_val |= (cfg->chan_mode << MPWM_MR_MCHMOD_Pos);
    }

    mpwm->MR = reg_val;
}

int32_t HAL_MPWM_Init(enum mpwm_id id, struct mpwm_cfg *cfg,
                      mpwm_irq_handler_t handler,
                      void *context)
{
    struct mpwm_ctrl_block *mcb;
    MPWM_Type *mpwm;

    DRIVER_ASSERT(id < MPWM_ID_MAX);
    DRIVER_ASSERT(cfg != NULL);

    mcb = &g_mcb[id];
    mpwm = MPWM_REG(id);

    memset(mcb, 0, sizeof(struct mpwm_ctrl_block));

    SCU->PER2 &= (~SCU_PER2_MPWM_Msk);
    SCU->PCER2 &= (~SCU_PCER2_MPWM_Msk);

    SCU->PER2 |= (1 << SCU_PER2_MPWM_Pos);
    SCU->PCER2 |= (1 << SCU_PCER2_MPWM_Pos);

    mcb->handler = handler;
    mcb->context = context;

    MPWM_REG_BIT_SET(mpwm->CR1, 1, MPWM_CR1_PWMEN_Pos);

    HAL_MPWM_DisablePWMOutput(id);

    MPWM_Configure(mpwm, cfg);

    return DRIVER_ERROR_OK;
}

int32_t HAL_MPWM_Deinit(enum mpwm_id id)
{
    DRIVER_ASSERT(id < MPWM_ID_MAX);

    SCU->PER2 &= (~SCU_PER2_MPWM_Msk);
    SCU->PCER2 &= (~SCU_PCER2_MPWM_Msk);


    NVIC_DisableIRQ(MPWMPRT_IRQn);
    NVIC_DisableIRQ(MPWMOVC_IRQn);
    NVIC_DisableIRQ(MPWM_IRQn);

    return DRIVER_ERROR_OK;
}

int32_t HAL_MPWM_SetIRQConfig(enum mpwm_id id, union mpwm_irq_cfg *cfg)
{
    uint32_t reg_val;
    MPWM_Type *mpwm;

    DRIVER_ASSERT(id < MPWM_ID_MAX);

    mpwm = MPWM_REG(id);

    reg_val = 0;
    MPWM_REG_BIT_SET(reg_val, cfg->irq_en_bit.period, MPWM_IER_PRDIE_Pos);
    MPWM_REG_BIT_SET(reg_val, cfg->irq_en_bit.bottom, MPWM_IER_BOTIE_Pos);
    MPWM_REG_BIT_SET2(reg_val, cfg->irq_en_bit.atr_6, cfg->irq_en_bit.wh_duty, MPWM_IER_WHIE_ATR6IE_Pos);
    MPWM_REG_BIT_SET2(reg_val, cfg->irq_en_bit.atr_5, cfg->irq_en_bit.vh_duty, MPWM_IER_VHIE_ATR5IE_Pos);
    MPWM_REG_BIT_SET2(reg_val, cfg->irq_en_bit.atr_4, cfg->irq_en_bit.uh_duty, MPWM_IER_UHIE_ATR4IE_Pos);
    MPWM_REG_BIT_SET2(reg_val, cfg->irq_en_bit.atr_4, cfg->irq_en_bit.uh_duty, MPWM_IER_UHIE_ATR4IE_Pos);
    MPWM_REG_BIT_SET2(reg_val, cfg->irq_en_bit.atr_2, cfg->irq_en_bit.vl_duty, MPWM_IER_VLIE_ATR2IE_Pos);
    MPWM_REG_BIT_SET2(reg_val, cfg->irq_en_bit.atr_1, cfg->irq_en_bit.ul_duty, MPWM_IER_ULIE_ATR1IE_Pos);

    mpwm->IER = reg_val;

    if (reg_val)
    {
        NVIC_EnableIRQ(MPWM_IRQn);
    }
    else
    {
        NVIC_DisableIRQ(MPWM_IRQn);
    }

    if (cfg->irq_en_bit.protect)
    {
        NVIC_EnableIRQ(MPWMPRT_IRQn);
    }
    else
    {
        NVIC_DisableIRQ(MPWMPRT_IRQn);
    }

    if (cfg->irq_en_bit.over_current)
    {
        NVIC_EnableIRQ(MPWMOVC_IRQn);
    }
    else
    {
        NVIC_DisableIRQ(MPWMOVC_IRQn);
    }

    return DRIVER_ERROR_OK;
}

int32_t HAL_MPWM_SetPotectionInputConfig(enum mpwm_id id, enum mpwm_phase_type p_type,
                                         struct mpwm_input_prt_cfg *cfg)
{
    uint32_t reg_val;
    MPWM_Type *mpwm;

    DRIVER_ASSERT(id < MPWM_ID_MAX);

    mpwm = MPWM_REG(id);

    reg_val = (((cfg->polarity << MPWM_PCR_PROTPOL_Pos) & MPWM_PCR_PROTPOL_Msk) |
               ((cfg->clk_div << MPWM_PCR_PROTDIV_Pos) & MPWM_PCR_PROTDIV_Msk) |
               ((cfg->debounce << MPWM_PCR_PROTD_Pos) & MPWM_PCR_PROTD_Msk) |
               ((cfg->enable_prt3 << MPWM_PCR_PROT3EN_Pos) & MPWM_PCR_PROT3EN_Msk) |
               ((cfg->enable_prt2 << MPWM_PCR_PROT2EN_Pos) & MPWM_PCR_PROT2EN_Msk) |
               ((cfg->enable_prt1 << MPWM_PCR_PROT1EN_Pos) & MPWM_PCR_PROT1EN_Msk) |
               ((cfg->enable_prt0 << MPWM_PCR_PROT0EN_Pos) & MPWM_PCR_PROT0EN_Msk));

    mpwm->PCR = reg_val;

    return DRIVER_ERROR_OK;
}

int32_t HAL_MPWM_SetProtectionOutputConfig(enum mpwm_id id, enum mpwm_phase_type p_type,
                                           enum mpwm_output_type ot, uint32_t en)
{
    return DRIVER_ERROR_NOT_SUPPORTED;
}

int32_t HAL_MPWM_SetOverCurrentInputConfig(enum mpwm_id id, enum mpwm_phase_type p_type,
                                           struct mpwm_input_oc_cfg *cfg)
{
    uint32_t reg_val;
    MPWM_Type *mpwm;

    DRIVER_ASSERT(id < MPWM_ID_MAX);

    mpwm = MPWM_REG(id);

    reg_val = (((cfg->enable_ovp3 << MPWM_OCR_OVIN3EN_Pos) & MPWM_OCR_OVIN3EN_Msk) |
               ((cfg->enable_ovp2 << MPWM_OCR_OVIN2EN_Pos) & MPWM_OCR_OVIN2EN_Msk) |
               ((cfg->enable_ovp1 << MPWM_OCR_OVIN1EN_Pos) & MPWM_OCR_OVIN1EN_Msk) |
               ((cfg->enable_ovp0 << MPWM_OCR_OVIN0EN_Pos) & MPWM_OCR_OVIN0EN_Msk));

    mpwm->OCR = reg_val;

    return DRIVER_ERROR_OK;
}

int32_t HAL_MPWM_SetOverCurrentOutputConfig(enum mpwm_id id, enum mpwm_phase_type p_type,
                                            enum mpwm_output_type ot, uint32_t en)
{
    return DRIVER_ERROR_NOT_SUPPORTED;
}

int32_t HAL_MPWM_SetDeadTimeConfig(enum mpwm_id id, enum mpwm_phase_type p_type, struct mpwm_dt_cfg *cfg)
{
    uint32_t reg_val;
    MPWM_Type *mpwm;

    DRIVER_ASSERT(id < MPWM_ID_MAX);

    mpwm = MPWM_REG(id);

    reg_val = (((cfg->enable << MPWM_DTR_DTEN_Pos) & MPWM_DTR_DTEN_Msk) |
               ((cfg->short_circuit_protect_en << MPWM_DTR_PSHRT_Pos) & MPWM_DTR_PSHRT_Msk) |
               ((cfg->ouput_level_high_side << MPWM_DTR_HDTOL_Pos) & MPWM_DTR_HDTOL_Msk) |
               ((cfg->ouput_level_low_side << MPWM_DTR_LDTOL_Pos) & MPWM_DTR_LDTOL_Msk) |
               ((cfg->clk << MPWM_DTR_DTCLK_Pos) & MPWM_DTR_DTCLK_Msk) |
               ((cfg->dead_time << MPWM_DTR_HDT_Pos) & MPWM_DTR_HDT_Msk) |
               ((cfg->dead_time << MPWM_DTR_LDT_Pos) & MPWM_DTR_LDT_Msk));
    mpwm->DTR = reg_val;

    return DRIVER_ERROR_OK;
}

int32_t HAL_MPWM_SetADCTriggerConfig(enum mpwm_id id, enum mpwm_trgger_id t_id, struct mpwm_adc_tr_cfg *cfg)
{
    uint32_t reg_val;
    MPWM_Type *mpwm;

    DRIVER_ASSERT(id < MPWM_ID_MAX);

    mpwm = MPWM_REG(id);

    reg_val = (((cfg->reg_mode << MPWM_ATR1_ATUDT_Pos) & MPWM_ATR1_ATUDT_Msk) |
               ((cfg->mode << MPWM_ATR1_ATMOD_Pos) & MPWM_ATR1_ATMOD_Msk) |
               ((cfg->tr_count << MPWM_ATR1_ATCNT_Pos) & MPWM_ATR1_ATCNT_Msk));
    switch (t_id)
    {
        case MPWM_TRGGER_ID_1:
            mpwm->ATR1 = reg_val;
            break;
        case MPWM_TRGGER_ID_2:
            mpwm->ATR2 = reg_val;
            break;
        case MPWM_TRGGER_ID_3:
            mpwm->ATR3 = reg_val;
            break;
        case MPWM_TRGGER_ID_4:
            mpwm->ATR4 = reg_val;
            break;
        case MPWM_TRGGER_ID_5:
            mpwm->ATR5 = reg_val;
            break;
        case MPWM_TRGGER_ID_6:
            mpwm->ATR6 = reg_val;
            break;
    }


    return DRIVER_ERROR_OK;
}

int32_t HAL_MPWM_SetIRQinterval(enum mpwm_id id, enum mpwm_phase_type p_type,
                                uint32_t irq_intv)
{
    uint32_t reg_val;
    MPWM_Type *mpwm;

    DRIVER_ASSERT(id < MPWM_ID_MAX);

    mpwm = MPWM_REG(id);

    reg_val = mpwm->CR1;
    MPWM_REG_VAL_SET(reg_val, irq_intv, MPWM_CR1_IRQN_Pos, MPWM_CR1_IRQN_Msk);
    mpwm->CR1 = reg_val;

    return DRIVER_ERROR_OK;
}

int32_t HAL_MPWM_ControlPWMOutput(enum mpwm_id id,
                                        enum mpwm_phase_type p_type,
                                        enum mpwm_output_type ot, uint32_t en)
{
    uint32_t reg_val;
    MPWM_Type *mpwm;

    DRIVER_ASSERT(id < MPWM_ID_MAX);

    mpwm = MPWM_REG(id);

    reg_val = mpwm->OLR;
    if (p_type == MPWM_PHASE_TYPE_U || p_type == MPWM_PHASE_TYPE_ALL)
    {
        if (ot == MPWM_OUTPUT_TYPE_L)
        {
            MPWM_REG_BIT_SET(reg_val, en, MPWM_OLR_POCUL_Pos);
        }
        else
        {
            MPWM_REG_BIT_SET(reg_val, en, MPWM_OLR_POCUH_Pos);
        }
    }

    if (p_type == MPWM_PHASE_TYPE_V || p_type == MPWM_PHASE_TYPE_ALL)
    {
        if (ot == MPWM_OUTPUT_TYPE_L)
        {
            MPWM_REG_BIT_SET(reg_val, en, MPWM_OLR_POCVL_Pos);
        }
        else
        {
            MPWM_REG_BIT_SET(reg_val, en, MPWM_OLR_POCVH_Pos);
        }
    }

    if (p_type == MPWM_PHASE_TYPE_W || p_type == MPWM_PHASE_TYPE_ALL)
    {
        if (ot == MPWM_OUTPUT_TYPE_L)
        {
            MPWM_REG_BIT_SET(reg_val, en, MPWM_OLR_POCWL_Pos);
        }
        else
        {
            MPWM_REG_BIT_SET(reg_val, en, MPWM_OLR_POCWH_Pos);
        }
    }
    mpwm->OLR = reg_val;

    return DRIVER_ERROR_OK;
}

int32_t HAL_MPWM_SetDisabledOutputLevel(enum mpwm_id id,
                                        enum mpwm_phase_type p_type,
                                        enum mpwm_output_type ot, uint32_t hl)
{
    uint32_t reg_val;
    MPWM_Type *mpwm;

    DRIVER_ASSERT(id < MPWM_ID_MAX);

    mpwm = MPWM_REG(id);

    reg_val = mpwm->OLR;
    if (p_type == MPWM_PHASE_TYPE_U || p_type == MPWM_PHASE_TYPE_ALL)
    {
        if (ot == MPWM_OUTPUT_TYPE_L)
        {
            MPWM_REG_BIT_SET(reg_val, hl, MPWM_OLR_DOLUL_Pos);
        }
        else
        {
            MPWM_REG_BIT_SET(reg_val, hl, MPWM_OLR_DOLUH_Pos);
        }
    }

    if (p_type == MPWM_PHASE_TYPE_V || p_type == MPWM_PHASE_TYPE_ALL)
    {
        if (ot == MPWM_OUTPUT_TYPE_L)
        {
            MPWM_REG_BIT_SET(reg_val, hl, MPWM_OLR_DOLVL_Pos);
        }
        else
        {
            MPWM_REG_BIT_SET(reg_val, hl, MPWM_OLR_DOLVH_Pos);
        }
    }

    if (p_type == MPWM_PHASE_TYPE_W || p_type == MPWM_PHASE_TYPE_ALL)
    {
        if (ot == MPWM_OUTPUT_TYPE_L)
        {
            MPWM_REG_BIT_SET(reg_val, hl, MPWM_OLR_DOLWL_Pos);
        }
        else
        {
            MPWM_REG_BIT_SET(reg_val, hl, MPWM_OLR_DOLWH_Pos);
        }
    }
    mpwm->OLR = reg_val;

    return DRIVER_ERROR_OK;
}

int32_t HAL_MPWM_SetStartOutputLevel(enum mpwm_id id,
                                     enum mpwm_phase_type p_type,
                                     enum mpwm_output_type ot, uint32_t hl)
{
    uint32_t reg_val;
    MPWM_Type *mpwm;

    DRIVER_ASSERT(id < MPWM_ID_MAX);

    mpwm = MPWM_REG(id);

    reg_val = mpwm->OLR;
    if (p_type == MPWM_PHASE_TYPE_U || p_type == MPWM_PHASE_TYPE_ALL)
    {
        if (ot == MPWM_OUTPUT_TYPE_L)
        {
            MPWM_REG_BIT_SET(reg_val, hl, MPWM_OLR_SLUL_Pos);
        }
        else
        {
            MPWM_REG_BIT_SET(reg_val, hl, MPWM_OLR_SLUH_Pos);
        }
    }

    if (p_type == MPWM_PHASE_TYPE_V || p_type == MPWM_PHASE_TYPE_ALL)
    {
        if (ot == MPWM_OUTPUT_TYPE_L)
        {
            MPWM_REG_BIT_SET(reg_val, hl, MPWM_OLR_SLVL_Pos);
        }
        else
        {
            MPWM_REG_BIT_SET(reg_val, hl, MPWM_OLR_SLVH_Pos);
        }
    }

    if (p_type == MPWM_PHASE_TYPE_W || p_type == MPWM_PHASE_TYPE_ALL)
    {
        if (ot == MPWM_OUTPUT_TYPE_L)
        {
            MPWM_REG_BIT_SET(reg_val, hl, MPWM_OLR_SLWL_Pos);
        }
        else
        {
            MPWM_REG_BIT_SET(reg_val, hl, MPWM_OLR_SLWH_Pos);
        }
    }
    mpwm->OLR = reg_val;

    return DRIVER_ERROR_OK;
}

int32_t HAL_MPWM_SetForceOutputLevel(enum mpwm_id id,
                                     enum mpwm_phase_type p_type,
                                     enum mpwm_output_type ot, uint8_t hl)
{
    uint32_t reg_val;
    MPWM_Type *mpwm;

    DRIVER_ASSERT(id < MPWM_ID_MAX);

    mpwm = MPWM_REG(id);

    reg_val = mpwm->FOLR;
    if (p_type == MPWM_PHASE_TYPE_U || p_type == MPWM_PHASE_TYPE_ALL)
    {
        if (ot == MPWM_OUTPUT_TYPE_L)
        {
            MPWM_REG_BIT_SET(reg_val, hl, MPWM_FOLR_FLUL_Pos);
        }
        else
        {
            MPWM_REG_BIT_SET(reg_val, hl, MPWM_FOLR_FLUH_Pos);
        }
    }

    if (p_type == MPWM_PHASE_TYPE_V || p_type == MPWM_PHASE_TYPE_ALL)
    {
        if (ot == MPWM_OUTPUT_TYPE_L)
        {
            MPWM_REG_BIT_SET(reg_val, hl, MPWM_FOLR_FLVL_Pos);
        }
        else
        {
            MPWM_REG_BIT_SET(reg_val, hl, MPWM_FOLR_FLVH_Pos);
        }
    }

    if (p_type == MPWM_PHASE_TYPE_W || p_type == MPWM_PHASE_TYPE_ALL)
    {
        if (ot == MPWM_OUTPUT_TYPE_L)
        {
            MPWM_REG_BIT_SET(reg_val, hl, MPWM_FOLR_FLWL_Pos);
        }
        else
        {
            MPWM_REG_BIT_SET(reg_val, hl, MPWM_FOLR_FLWH_Pos);
        }
    }
    mpwm->FOLR = reg_val;

    return DRIVER_ERROR_OK;
}

int32_t HAL_MPWM_SetPeriod(enum mpwm_id id, enum mpwm_phase_type p_type, uint16_t prd)
{
    MPWM_Type *mpwm;

    DRIVER_ASSERT(id < MPWM_ID_MAX);

    mpwm = MPWM_REG(id);

    if (prd < 0x10)
    {
        return DRIVER_ERROR_PARAMETER;
    }

    mpwm->PRD = prd;

    return DRIVER_ERROR_OK;
}

int32_t HAL_MPWM_SetDuty(enum mpwm_id id, enum mpwm_phase_type p_type,
                         enum mpwm_output_type ot, uint16_t duty)
{
    MPWM_Type *mpwm;

    DRIVER_ASSERT(id < MPWM_ID_MAX);

    mpwm = MPWM_REG(id);

    if (p_type == MPWM_PHASE_TYPE_U || p_type == MPWM_PHASE_TYPE_ALL)
    {
        if (ot == MPWM_OUTPUT_TYPE_L)
        {
            mpwm->DUL = duty;
        }
        else
        {
            mpwm->DUH = duty;
        }
    }

    if (p_type == MPWM_PHASE_TYPE_V || p_type == MPWM_PHASE_TYPE_ALL)
    {
        if (ot == MPWM_OUTPUT_TYPE_L)
        {
            mpwm->DVL = duty;
        }
        else
        {
            mpwm->DVH = duty;
        }
    }

    if (p_type == MPWM_PHASE_TYPE_W || p_type == MPWM_PHASE_TYPE_ALL)
    {
        if (ot == MPWM_OUTPUT_TYPE_L)
        {
            mpwm->DWL = duty;
        }
        else
        {
            mpwm->DWH = duty;
        }
    }

    return DRIVER_ERROR_OK;
}

int32_t HAL_MPWM_Start(enum mpwm_id id, enum mpwm_phase_type p_type)
{
    MPWM_Type *mpwm;

    DRIVER_ASSERT(id < MPWM_ID_MAX);

    mpwm = MPWM_REG(id);

    mpwm->CR2 |= (0x01UL << MPWM_CR2_PSTART_Pos);

    return DRIVER_ERROR_OK;
}

int32_t HAL_MPWM_Stop(enum mpwm_id id, enum mpwm_phase_type p_type)
{
    MPWM_Type *mpwm;

    DRIVER_ASSERT(id < MPWM_ID_MAX);

    mpwm = MPWM_REG(id);

    mpwm->CR2 &= ~(0x01UL << MPWM_CR2_PSTART_Pos);

    return DRIVER_ERROR_OK;
}

int32_t HAL_MPWM_Halt(enum mpwm_id id, enum mpwm_phase_type p_type)
{
    MPWM_Type *mpwm;

    DRIVER_ASSERT(id < MPWM_ID_MAX);

    mpwm = MPWM_REG(id);

    mpwm->CR2 |= (0x01UL << MPWM_CR2_HALT_Pos);

    return DRIVER_ERROR_OK;
}

int32_t HAL_MPWM_Resume(enum mpwm_id id, enum mpwm_phase_type p_type)
{
    MPWM_Type *mpwm;

    DRIVER_ASSERT(id < MPWM_ID_MAX);

    mpwm = MPWM_REG(id);

    mpwm->CR2 &= ~(0x01UL << MPWM_CR2_HALT_Pos);

    return DRIVER_ERROR_OK;
}

int32_t HAL_MPWM_ReadCount(enum mpwm_id id, enum mpwm_phase_type p_type, uint16_t *count)
{
    MPWM_Type *mpwm;

    DRIVER_ASSERT(id < MPWM_ID_MAX);

    mpwm = MPWM_REG(id);

    *count = mpwm->CNT;

    return DRIVER_ERROR_OK;
}

int32_t HAL_MPWM_ReadStatus(enum mpwm_id id, uint32_t *status)
{
    MPWM_Type *mpwm;

    DRIVER_ASSERT(id < MPWM_ID_MAX);

    mpwm = MPWM_REG(id);

    *status = mpwm->SR;

    return DRIVER_ERROR_OK;
}

int32_t HAL_MPWM_ReadProtectionStatus(enum mpwm_id id, uint32_t *status)
{
    MPWM_Type *mpwm;

    DRIVER_ASSERT(id < MPWM_ID_MAX);

    mpwm = MPWM_REG(id);

    *status = mpwm->PSR;

    return DRIVER_ERROR_OK;
}

int32_t HAL_MPWM_ReadOverCurrentStatus(enum mpwm_id id, uint32_t *status)
{
    MPWM_Type *mpwm;

    DRIVER_ASSERT(id < MPWM_ID_MAX);

    mpwm = MPWM_REG(id);

    *status = mpwm->OSR;

    return DRIVER_ERROR_OK;
}

int32_t HAL_MPWM_EnablePWMOutput(enum mpwm_id id)
{
    uint32_t reg_val;
    MPWM_Type *mpwm;

    DRIVER_ASSERT(id < MPWM_ID_MAX);

    mpwm = MPWM_REG(id);

    reg_val = mpwm->FOLR;
    reg_val |= (MPWM_FOLR_FOLKEY << MPWM_FOLR_FOLKEY_Pos);
    reg_val &= ~(0x01UL << MPWM_FOLR_SWFO_Pos);
    reg_val &= ~(0x01UL << MPWM_FOLR_PRTFO_Pos);
    reg_val &= ~(0x01UL << MPWM_FOLR_OCFO_Pos);
    mpwm->FOLR = reg_val;

    return DRIVER_ERROR_OK;
}

int32_t HAL_MPWM_DisablePWMOutput(enum mpwm_id id)
{
    uint32_t reg_val;
    MPWM_Type *mpwm;

    DRIVER_ASSERT(id < MPWM_ID_MAX);

    mpwm = MPWM_REG(id);

    reg_val = mpwm->FOLR;
    reg_val |= (MPWM_FOLR_FOLKEY << MPWM_FOLR_FOLKEY_Pos);
    reg_val |= (0x01UL << MPWM_FOLR_SWFO_Pos);
    mpwm->FOLR = reg_val;

    return DRIVER_ERROR_OK;
}

void MPWMPRT_IRQHandler(void)
{
    struct mpwm_ctrl_block *mcb;

    mcb = &g_mcb[MPWM_ID_0];

    if (mcb->handler)
    {
        mcb->handler(MPWM_IRQ_EVENT_TYPE_PRT, mcb->context);
    }
}

void MPWMOV_IRQHandler(void)
{
    struct mpwm_ctrl_block *mcb;

    mcb = &g_mcb[MPWM_ID_0];

    if (mcb->handler)
    {
        mcb->handler(MPWM_IRQ_EVENT_TYPE_OC, mcb->context);
    }
}


/* multiple defined must commentout when use aFPB
void MPWM_IRQHandler(void)
{
    struct mpwm_ctrl_block *mcb;

    mcb = &g_mcb[MPWM_ID_0];

    if (mcb->handler)
    {
        mcb->handler(MPWM_IRQ_EVENT_TYPE_MPWM, mcb->context);
    }
}
*/
