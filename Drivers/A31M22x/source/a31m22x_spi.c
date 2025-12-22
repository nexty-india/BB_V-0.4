/**
 *******************************************************************************
 * @file        a31m22x_spi.c
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
#include <string.h>

#include "A31M22x.h"
#include "A31M22x_scu.h"
#include "A31M22x_spi.h"

#define SPI_REG_OFFSET     0x100

static __INLINE SPI_Type *SPI_REG(enum spi_id id)
{
    return (SPI_Type *)(SPI_BASE + (SPI_REG_OFFSET * id));
}

static __INLINE IRQn_Type SPI_IRQ_NUM(enum spi_id id)
{
    return (IRQn_Type)((uint8_t)SPI_IRQn + id);
}

static __INLINE enum dma_peri SPI_RX_DMA_PERI(enum spi_id id)
{
    return (enum dma_peri)(DMA_PERI_SPI_RX + (id * 2));
}

static __INLINE enum dma_peri SPI_TX_DMA_PERI(enum spi_id id)
{
    return (enum dma_peri)(DMA_PERI_SPI_TX + (id * 2));
}

struct spi_ctrl_block
{
    spi_irq_handler_t   handler;
    void *              context;
    uint8_t             tx_busy : 1;
    uint8_t             rx_busy : 1;
    uint8_t *           tx_buf;
    uint8_t *           rx_buf;
    uint32_t            tx_len;
    uint32_t            rx_len;
    volatile uint32_t   tx_count;
    volatile uint32_t   rx_count;
    uint8_t             tx_dma_enable;
    enum dma_ch         tx_dma_ch;
    uint8_t             rx_dma_enable;
    enum dma_ch         rx_dma_ch;
};


static struct spi_ctrl_block g_scb[SPI_ID_MAX];

static __INLINE uint32_t SPI_StatusCheck(SPI_Type *reg, uint32_t status_mask)
{
    return reg->SR & status_mask;
}

static int32_t SPI_Configure(struct spi_ctrl_block *scb, SPI_Type *spi,
                             struct spi_cfg *cfg)
{
    uint32_t cfg_val = 0;

    spi->EN = 0;

    switch (cfg->mode)
    {
        case SPI_MODE_MASTER:
            cfg_val |= (1 << SPI_CR_MS_Pos);
            break;
        case SPI_MODE_SLAVE:
            break;
        default:
            DRIVER_ASSERT(0);
    }

    switch (cfg->data_bit)
    {
        case SPI_DATA_BIT_8:
            break;
        case SPI_DATA_BIT_9:
            cfg_val |= (1 << SPI_CR_BITSZ_Pos);
            break;
        case SPI_DATA_BIT_16:
            cfg_val |= (2 << SPI_CR_BITSZ_Pos);
            break;
        case SPI_DATA_BIT_17:
            cfg_val |= (3 << SPI_CR_BITSZ_Pos);
            break;
        default:
            DRIVER_ASSERT(0);
    }

    switch (cfg->sync_mode)
    {
        case SPI_SYHC_MODE_CPOL_1_CPHA_0:
            cfg_val |= (1 << SPI_CR_CPOL_Pos);
            break;
        case SPI_SYHC_MODE_CPOL_1_CPHA_1:
            cfg_val |= (1 << SPI_CR_CPOL_Pos) | (1 << SPI_CR_CPHA_Pos);
            break;
        case SPI_SYHC_MODE_CPOL_0_CPHA_0:
            break;
        case SPI_SYHC_MODE_CPOL_0_CPHA_1:
            cfg_val |= (1 << SPI_CR_CPHA_Pos);
            break;
        default:
            DRIVER_ASSERT(0);
    }

    switch (cfg->bit_order)
    {
        case SPI_BIT_ORDER_MSB_FIRST:
            cfg_val |= (1 << SPI_CR_MSBF_Pos);
            break;
        case SPI_BIT_ORDER_LSB_FIRST:
            break;
        default:
            DRIVER_ASSERT(0);
    }

    switch (cfg->ss_type)
    {
        case SPI_SS_AUTO:
            break;
        case SPI_SS_MANUAL:
            cfg_val |= (1 << SPI_CR_SSMOD_Pos);
            break;
        default:
            DRIVER_ASSERT(0);
    }
    ;

    cfg_val |= (1 << SPI_CR_SSMO_Pos);

    spi->CR = cfg_val;
    spi->BR = cfg->freq;
    spi->EN = 1;

    return DRIVER_ERROR_OK;
}

int32_t HAL_SPI_Init(enum spi_id id, struct spi_cfg *cfg,
                     spi_irq_handler_t handler,
                     void *context)
{
    struct spi_ctrl_block *scb;
    SPI_Type *spi;
    int32_t ret;

    DRIVER_ASSERT(id < SPI_ID_MAX);
    DRIVER_ASSERT(cfg != NULL);

    scb = &g_scb[id];
    spi = SPI_REG(id);

    memset(scb, 0, sizeof(struct spi_ctrl_block));

    SCU->PRER2 |= (1 << (SCU_PRER2_SPI_Pos + id));
    SCU->PER2 |= (1 << (SCU_PER2_SPI_Pos + id));
    SCU->PCER2 |= (1 << (SCU_PCER2_SPI_Pos + id));

    scb->context = context;
    scb->handler = handler;
    spi->CR = 0;

    ret = SPI_Configure(scb, spi, cfg);
    if (ret != DRIVER_ERROR_OK)
    {
        HAL_SPI_Deinit(id);
        return ret;
    }

    NVIC_ClearPendingIRQ(SPI_IRQ_NUM(id));
    NVIC_SetPriority(SPI_IRQ_NUM(id), cfg->irq_prio);
    NVIC_EnableIRQ(SPI_IRQ_NUM(id));

    return ret;
}


int32_t HAL_SPI_Deinit(enum spi_id id)
{
    DRIVER_ASSERT(id < SPI_ID_MAX);

    SCU->PRER2 &= ~(1 << (SCU_PRER2_SPI_Pos + id));
    SCU->PER2 &= ~(1 << (SCU_PER2_SPI_Pos + id));
    SCU->PCER2 &= ~(1 << (SCU_PCER2_SPI_Pos + id));

    NVIC_DisableIRQ(SPI_IRQ_NUM(id));

    return DRIVER_ERROR_OK;
}

int32_t HAL_SPI_SetDelay(enum spi_id id, uint8_t start, uint8_t burst, uint8_t stop)
{
    SPI_Type *spi;

    DRIVER_ASSERT(id < SPI_ID_MAX);

    spi = SPI_REG(id);

    spi->LR = (start << SPI_LR_STL_Pos)
              | (burst << SPI_LR_BTL_Pos)
              | (stop << SPI_LR_SPL_Pos);

    return DRIVER_ERROR_OK;
}

int32_t HAL_SPI_SSManual(enum spi_id id, enum ss_state ss_state)
{
    SPI_Type *spi;

    DRIVER_ASSERT(id < SPI_ID_MAX);

    spi = SPI_REG(id);

    switch (ss_state)
    {
        case SPI_SS_STATE_LOW:
            spi->CR &= ~(1 << SPI_CR_SSOUT_Pos);
            break;
        case SPI_SS_STATE_HIGH:
            spi->CR |= (1 << SPI_CR_SSOUT_Pos);
            break;
        default:
            DRIVER_ASSERT(0);
    }

    return DRIVER_ERROR_OK;
}

int32_t HAL_SPI_Transfer(enum spi_id id,
                         uint8_t *out, uint32_t out_len,
                         uint8_t *in, uint32_t in_len,
                         enum spi_io_type io_type)
{
    struct spi_ctrl_block *scb;
    SPI_Type *spi;

    DRIVER_ASSERT(id < SPI_ID_MAX);

    scb = &g_scb[id];
    spi = SPI_REG(id);

    if (scb->rx_busy || scb->tx_busy)
    {
        return DRIVER_ERROR_BUSY;
    }

    spi->CR |= (1 << SPI_CR_RXBC_Pos) | (1 << SPI_CR_TXBC_Pos);
    if (out_len)
    {
        scb->tx_busy = 1;
    }
    if (in_len)
    {
        scb->rx_busy = 1;
    }
    scb->tx_len = out_len;
    scb->rx_len = in_len;
    scb->rx_count = 0;
    scb->tx_count = 0;
    scb->rx_buf = (uint8_t *)in;
    scb->tx_buf = (uint8_t *)out;

    if (io_type == SPI_IO_TYPE_BLOCK)
    {
        while (scb->rx_len > scb->rx_count || scb->tx_len > scb->tx_count)
        {
            uint32_t data;

            if (scb->tx_len > scb->tx_count)
            {
                while (!SPI_StatusCheck(spi, SPI_SR_TRDY_Msk))
                {
                }

                data = *scb->tx_buf++;
                if (spi->CR & SPI_CR_BITSZ_Msk)
                {
                    data |= *(scb->tx_buf++) << 8;
                    if ((spi->CR & SPI_CR_BITSZ_Msk) == SPI_CR_BITSZ_Msk)
                    {
                        data |= *(scb->tx_buf++) << 16;
                    }
                }
                spi->TDR = data;
                scb->tx_count++;
            }
            else if (spi->CR & SPI_CR_MS_Msk)
            {
                while (!SPI_StatusCheck(spi, SPI_SR_TRDY_Msk))
                {
                }

                spi->TDR = 0xFF;
            }

            if (scb->rx_len > scb->rx_count)
            {
                while (!SPI_StatusCheck(spi, SPI_SR_RRDY_Msk))
                {
                }

                data = spi->RDR;
                *(scb->rx_buf++) = (uint8_t)data;

                if (spi->CR & SPI_CR_BITSZ_Msk)
                {
                    *(scb->rx_buf++) = (uint8_t)(data >> 8);
                    if ((spi->CR & SPI_CR_BITSZ_Msk) == SPI_CR_BITSZ_Msk)
                    {
                        *(scb->rx_buf++) = (uint8_t)(data >> 16);
                    }
                }
                scb->rx_count++;
            }
        }

        scb->rx_busy = 0;
        scb->tx_busy = 0;

        if (SPI_StatusCheck(spi, SPI_SR_OVRF_Msk)
            || SPI_StatusCheck(spi, SPI_SR_UDRF_Msk))
        {
            scb->tx_busy = 0;
            return DRIVER_ERROR_HW;
        }
    }
    else
    {
        if (scb->tx_dma_enable)
        {
            spi->CR |= (1 << SPI_CR_DTXIE_Pos) | (1 << SPI_CR_DRXIE_Pos);

            HAL_DMA_Start(scb->tx_dma_ch, (uint32_t)scb->tx_buf, (uint32_t)spi, scb->tx_len);
            HAL_DMA_Start(scb->rx_dma_ch, (uint32_t)spi, (uint32_t)scb->rx_buf, scb->rx_len);
        }
        else
        {
            uint32_t data;

            if (scb->tx_len > scb->tx_count)
            {
                data = *scb->tx_buf++;
                if (spi->CR & SPI_CR_BITSZ_Msk)
                {
                    data |= *(scb->tx_buf++) << 8;
                    if ((spi->CR & SPI_CR_BITSZ_Msk) == SPI_CR_BITSZ_Msk)
                    {
                        data |= *(scb->tx_buf++) << 16;
                    }
                }
                scb->tx_count++;
                spi->TDR = data;
            }
            else if (spi->CR & SPI_CR_MS_Msk)
            {
                spi->TDR = 0xFF;
            }

            spi->CR |= (1 << SPI_CR_TXIE_Pos) | (1 << SPI_CR_RXIE_Pos);
        }
    }

    return DRIVER_ERROR_OK;
}

int32_t HAL_SPI_SetTransmitDMA(enum spi_id id, enum dma_ch ch, uint8_t enable)
{
    struct spi_ctrl_block *scb;
    SPI_Type *spi;

    DRIVER_ASSERT(id < SPI_ID_MAX);

    scb = &g_scb[id];
    spi = SPI_REG(id);

    scb->tx_dma_enable = enable;
    scb->tx_dma_ch = ch;

    if (enable)
    {
        struct dma_cfg cfg =
        {
            .peri = SPI_TX_DMA_PERI(id),
            .size = DMA_BUS_SIZE_BYTE,
            .dir = DMA_DIR_MEM_TO_PERI,
        };

        switch (spi->CR & SPI_CR_BITSZ_Msk)
        {
            case SPI_DATA_BIT_8:
                cfg.size = DMA_BUS_SIZE_BYTE;
                break;
            case SPI_DATA_BIT_16:
                cfg.size = DMA_BUS_SIZE_HALFWORD;
                break;
            default:
                DRIVER_ASSERT(0);
        }

        HAL_DMA_Init();
        HAL_DMA_Setup(ch, &cfg);
    }

    return DRIVER_ERROR_OK;
}


int32_t HAL_SPI_SetReceiveDMA(enum spi_id id, enum dma_ch ch, uint8_t enable)
{
    struct spi_ctrl_block *scb;
    SPI_Type *spi;

    DRIVER_ASSERT(id < SPI_ID_MAX);

    scb = &g_scb[id];
    spi = SPI_REG(id);

    scb->rx_dma_enable = enable;
    scb->rx_dma_ch = ch;

    if (enable)
    {
        struct dma_cfg cfg =
        {
            .peri = SPI_RX_DMA_PERI(id),
            .size = DMA_BUS_SIZE_BYTE,
            .dir = DMA_DIR_PERI_TO_MEM,
        };

        switch (spi->CR & SPI_CR_BITSZ_Msk)
        {
            case SPI_DATA_BIT_8:
                cfg.size = DMA_BUS_SIZE_BYTE;
                break;
            case SPI_DATA_BIT_16:
                cfg.size = DMA_BUS_SIZE_HALFWORD;
                break;
            default:
                DRIVER_ASSERT(0);
        }

        HAL_DMA_Init();
        HAL_DMA_Setup(ch, &cfg);
    }

    return DRIVER_ERROR_OK;
}

void SPI_IRQHandler(enum spi_id id)
//static void SPI_IRQHandler(enum spi_id id)
{
    struct spi_ctrl_block *scb;
    SPI_Type *spi;
    volatile uint32_t data;
    volatile uint32_t event = 0;
    uint32_t rx_count;

    scb = &g_scb[id];
    spi = SPI_REG(id);

    if (!(spi->CR & SPI_CR_MS_Msk))
    {
        if (SPI_StatusCheck(spi, SPI_SR_SSDET_Msk))
        {
            spi->SR &= ~SPI_SR_SSDET_Msk;
        }
    }

    if (SPI_StatusCheck(spi, SPI_SR_TXDMAF_Msk)
        && SPI_StatusCheck(spi, SPI_SR_TXIDLE_Msk))
    {
        spi->SR &= ~SPI_SR_TXDMAF_Msk;
        scb->tx_busy = 0;

        if (scb->handler && !scb->rx_len)
        {
            scb->handler(SPI_EVENT_TRANSFER_DONE, scb->context);
        }

        return;
    }

    if (SPI_StatusCheck(spi, SPI_SR_RXDMAF_Msk))
    {
        spi->SR &= ~SPI_SR_RXDMAF_Msk;
        scb->rx_busy = 0;

        if (scb->handler)
        {
            scb->handler(SPI_EVENT_TRANSFER_DONE, scb->context);
        }

        return;
    }

    if (scb->rx_dma_enable || scb->tx_dma_enable)
    {
        return;
    }

    if (SPI_StatusCheck(spi, SPI_SR_TRDY_Msk)
        && SPI_StatusCheck(spi, SPI_SR_TXIDLE_Msk))
    {
        if (scb->rx_len)
        {
            rx_count = scb->rx_count;
            if (scb->tx_count != rx_count)
            {
                goto rx_check;
            }
        }

        if (scb->tx_count == scb->tx_len && scb->tx_busy == 1)
        {
            scb->tx_busy = 0;

            if (SPI_StatusCheck(spi, SPI_SR_OVRF_Msk))
            {
                event |= SPI_EVENT_OVERRUN;
            }

            if (SPI_StatusCheck(spi, SPI_SR_UDRF_Msk))
            {
                event |= SPI_EVENT_UNDERRUN;
            }

            if (!scb->rx_len)
            {
                spi->CR &= ~SPI_CR_TXIE_Msk;
                event |= SPI_EVENT_TRANSFER_DONE;
            }
        }
        else
        {
            if (scb->tx_count < scb->tx_len)
            {
                if (scb->tx_buf)
                {
                    data = *scb->tx_buf++;
                    if (spi->CR & SPI_CR_BITSZ_Msk)
                    {
                        data |= *(scb->tx_buf++) << 8;
                        if ((spi->CR & SPI_CR_BITSZ_Msk) == SPI_CR_BITSZ_Msk)
                        {
                            data |= *(scb->tx_buf++) << 16;
                        }
                    }
                    scb->tx_count++;
                }
                else
                {
                    data = 0xFFFFFFFF;
                }
            }

            if (scb->tx_busy == 1 || scb->rx_busy == 1)
            {
                spi->TDR = data;
            }
        }
    }

rx_check:
    if (SPI_StatusCheck(spi, SPI_SR_RRDY_Msk)
        && SPI_StatusCheck(spi, SPI_SR_SBUSY_Msk))
    {
        data = spi->RDR;

        if (scb->rx_count < scb->rx_len)
        {
            if (scb->rx_buf)
            {
                *(scb->rx_buf++) = (uint8_t)data;
                if (spi->CR & SPI_CR_BITSZ_Msk)
                {
                    *(scb->rx_buf++) = (uint8_t)(data >> 8);
                    if ((spi->CR & SPI_CR_BITSZ_Msk) == SPI_CR_BITSZ_Msk)
                    {
                        *(scb->rx_buf++) = (uint8_t)(data >> 16);
                    }
                }
                scb->rx_count++;
            }

            if (scb->rx_count == scb->rx_len && scb->rx_busy == 1)
            {
                scb->rx_busy = 0;
                scb->tx_busy = 0;
                spi->CR &= ~(SPI_CR_RXIE_Msk | SPI_CR_TXIE_Msk);
                if (scb->handler)
                {
                    if (SPI_StatusCheck(spi, SPI_SR_OVRF_Msk))
                    {
                        event |= SPI_EVENT_OVERRUN;
                    }

                    if (SPI_StatusCheck(spi, SPI_SR_UDRF_Msk))
                    {
                        event |= SPI_EVENT_UNDERRUN;
                    }

                    event |= SPI_EVENT_TRANSFER_DONE;
                }
            }
        }
    }

    if (scb->handler && event)
    {
        scb->handler(event, scb->context);
    }
}

//void SPI0_IRQHandler(void)
//{
//    SPI_IRQHandler(SPI_ID_0);
//}
