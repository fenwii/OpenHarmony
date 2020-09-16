/*
 * Copyright (c) 2020 HiSilicon (Shanghai) Technologies CO., LIMITED.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <hi3861_platform_base.h>
#include <hi_event.h>
#include <hi_isr.h>
#include <hi_mem.h>
#include <hi_sem.h>
#include <hi_spi.h>
#include <hi_stdlib.h>
#include <hi_time.h>
#include <hi_types_base.h>
#ifdef CONFIG_SPI_DMA_SUPPORT
#include <hi_dma.h>
#endif
#include <time.h>

#include "spi.h"

#define SPI_HOST_OPT_BASE (SPI_OPT_ENABLE_SPI |  \
                           SPI_OPT_SET_CFG |  \
                           SPI_OPT_DISABLE_SPI |  \
                           SPI_OPT_WAIT_SIGNAL |  \
                           SPI_OPT_FREE_SIGNAL)

#define SPI_SLAVE_OPT_READ (SPI_OPT_ENABLE_SPI |  \
                            SPI_OPT_SET_CFG)

#define SPI_SLAVE_OPT_WRITE (SPI_OPT_ENABLE_SPI |  \
                             SPI_OPT_SET_CFG |  \
                             SPI_OPT_WAIT_SIGNAL |  \
                             SPI_OPT_FREE_SIGNAL)

#define CLKEN_SPI0 5
#define CLKEN_SPI1 0

hi_u32 g_spi_clk = SPI_DEFAULT_CLK;

static hi_u32 spi_get_clk(hi_void)
{
    hi_reg_write16(W_CTL_W_TCXO_SEL_REG, 1);
    hi_udelay(1);
    return g_spi_clk;
}

static hi_u32 spi_write_data(hi_spi_idx id, hi_u32 timeout_ms)
{
    hi_u32 event_bit;
    hi_u32 ret;
    spi_isr_enable(g_spi_ctrl[id]->reg_base, SPI_INT_BIT_TX_FIFO_WATER_LINE);
    event_bit = 0;
    ret = hi_event_wait(g_spi_ctrl[id]->event_id, HI_EVENT_BIT_TX_DATA, &event_bit, timeout_ms,
                        HI_EVENT_WAITMODE_OR | HI_EVENT_WAITMODE_CLR);
    if (ret == HI_ERR_EVENT_WAIT_TIME_OUT) {
        spi_process_printf("write time out");
        return HI_ERR_SPI_WRITE_TIMEOUT;
    } else {
        return HI_ERR_SUCCESS;
    }
}

static hi_u32 spi_read_data(hi_spi_idx id, hi_u32 timeout_ms)
{
    hi_u32 event_bit = 0;
    hi_u32 ret;

    for (;;) {
        if (g_spi_ctrl[id]->rx_buf.cur_cnt >= g_spi_ctrl[id]->trans_len) {
            g_spi_ctrl[id]->rx_buf.cur_cnt = 0;
            return HI_ERR_SUCCESS;
        }
        spi_isr_enable(g_spi_ctrl[id]->reg_base,
                       SPI_INT_BIT_RX_FIFO_WATER_LINE | SPI_INT_BIT_RX_FIFO_TIME_OUT | SPI_INT_BIT_RX_FIFO_OVER_FLOW);

        ret = hi_event_wait(g_spi_ctrl[id]->event_id,
                            HI_EVENT_BIT_RX_DATA | HI_EVENT_BIT_RX_DATA_TIME_OUT | HI_EVENT_BIT_RX_FIFO_OVER_FLOW,
                            &event_bit, timeout_ms, HI_EVENT_WAITMODE_OR | HI_EVENT_WAITMODE_CLR);
        if (ret == HI_ERR_SUCCESS) {
            continue;
        } else if (ret == HI_ERR_EVENT_WAIT_TIME_OUT) {
            return HI_ERR_SPI_READ_TIMEOUT;
        } else {
            return ret;
        }
    }
}
static hi_u32 spi_host_transfer(hi_spi_idx id, const spi_trans_attr *trans_attr, hi_u32 total_len, hi_u32 read_write)
{
    hi_u32 ret;
    hi_u16 threshold = (id == HI_SPI_ID_0 ? SPI0_FIFO_THRESHOLD : SPI1_FIFO_THRESHOLD);
    hi_u32 len = total_len;
    while (len) {
        if (len > threshold) {
            g_spi_ctrl[id]->single_len = threshold;
            g_spi_ctrl[id]->trans_len = threshold;
        } else {
            g_spi_ctrl[id]->single_len = len;
            g_spi_ctrl[id]->trans_len = len;
        }
        if (read_write & SPI_WRITE_FLAG) {
            ret = spi_write_data(id, trans_attr->time_out_ms);
            if (ret != HI_ERR_SUCCESS) {
                return ret;
            }
        }
        /* if too fast, there should be delay 50-100 us to wait slave */
        if (read_write & SPI_READ_FLAG) {
            ret = spi_read_data(id, trans_attr->time_out_ms);
            if (ret != HI_ERR_SUCCESS) {
                return ret;
            }
        }
        if (len < g_spi_ctrl[id]->single_len) {
            return HI_ERR_FAILURE;
        }
        len -= g_spi_ctrl[id]->single_len;
    }
    return HI_ERR_SUCCESS;
}

static hi_u32 spi_slave_transfer(hi_spi_idx id, const spi_trans_attr *trans_attr, hi_u32 read_write)
{
    hi_u32 ret;
    hi_u16 threshold = (id == HI_SPI_ID_0 ? SPI0_FIFO_THRESHOLD : SPI1_FIFO_THRESHOLD);
    hi_u32 len = g_spi_ctrl[id]->trans_len;
    if (read_write & SPI_WRITE_FLAG) {
        while (len) {
            if (len > threshold) {
                g_spi_ctrl[id]->single_len = threshold;
            } else {
                g_spi_ctrl[id]->single_len = len;
            }
            ret = spi_write_data(id, trans_attr->time_out_ms);
            if (ret != HI_ERR_SUCCESS) {
                return ret;
            }
            len -= g_spi_ctrl[id]->single_len;
        }
    }
    if (read_write & SPI_READ_FLAG) {
        g_spi_ctrl[id]->single_len = threshold;
        ret = spi_read_data(id, trans_attr->time_out_ms);
        if (ret != HI_ERR_SUCCESS) {
            return ret;
        }
    }
    return HI_ERR_SUCCESS;
}

#ifdef CONFIG_SPI_DMA_SUPPORT
/* slave using dma transfer data, use read or write, can't use both methods of work at the same time */
static hi_u32 spi_slave_dma_transfer(hi_spi_idx id, const spi_trans_attr *trans_attr, hi_u32 read_write)
{
    hi_u32 ret;
    if (read_write & SPI_WRITE_FLAG) {
        spi_dma_enable(g_spi_ctrl[id]->reg_base, SPI_TX_DMAE);
        ret = spi_hd_dma_write_fifo(g_spi_ctrl[id], trans_attr->time_out_ms);
        spi_dma_disable(g_spi_ctrl[id]->reg_base, SPI_TX_DMAE);
    } else {
        spi_dma_enable(g_spi_ctrl[id]->reg_base, SPI_RX_DMAE);
        ret = spi_hd_dma_read_fifo(g_spi_ctrl[id], trans_attr->time_out_ms);
        spi_dma_disable(g_spi_ctrl[id]->reg_base, SPI_RX_DMAE);
    }
    return ret;
}
#endif

static hi_u32 spi_get_data_len(hi_u32 data_width, hi_u32 byte_len)
{
    if (data_width > HI_SPI_CFG_DATA_WIDTH_E_8BIT) {
        if ((byte_len % SPI_DATA_WIDTH_2BYTES) != 0) {
            return 0;
        }
        return (byte_len / SPI_DATA_WIDTH_2BYTES);
    } else {
        return byte_len;
    }
}

static hi_u32 spi_host_writeread(hi_spi_idx id, hi_pvoid write_data, hi_pvoid read_data, hi_u32 byte_len,
    hi_u32 options)
{
    hi_u32 data_len;
    hi_u32 ret;
    if ((hi_u32)id > HI_SPI_ID_1 || byte_len == 0 ||
        (!(options & SPI_OPT_SEND_FIX_DATA) && (write_data == HI_NULL)) ||
        (!(options & SPI_OPT_RCV_FIX_DATA) && (read_data == HI_NULL))) {
        return HI_ERR_SPI_PARAMETER_WRONG;
    }
    if (g_spi_ctrl[id] == HI_NULL) {
        return HI_ERR_SPI_NOT_INIT;
    }
    if (g_spi_ctrl[id]->spi_cfg.is_slave == SPI_CFG_ROLE_SLAVE) {
        return HI_ERR_SPI_PARAMETER_WRONG;
    }
    if (g_spi_ctrl[id]->transferring) {
        return HI_ERR_SPI_BUSY;
    }
    data_len = spi_get_data_len(g_spi_ctrl[id]->spi_cfg.data_width, byte_len);
    if (data_len == 0) {
        return HI_ERR_SPI_PARAMETER_WRONG;
    }
    spi_trans_attr trans_attr = { SPI_HOST_TIMEOUT_MS, options };
    g_spi_ctrl[id]->single_len = 0;
    g_spi_ctrl[id]->trans_len = data_len;
    g_spi_ctrl[id]->tx_buf.buf = write_data;
    g_spi_ctrl[id]->tx_buf.cur_pos = 0;
    g_spi_ctrl[id]->tx_buf.cur_cnt = 0;
    g_spi_ctrl[id]->rx_buf.buf = read_data;
    g_spi_ctrl[id]->rx_buf.cur_pos = 0;
    g_spi_ctrl[id]->rx_buf.cur_cnt = 0;
    ret = spi_trans_prepare(g_spi_ctrl[id], &trans_attr);
    if (ret != HI_ERR_SUCCESS) {
        spi_trans_restore(g_spi_ctrl[id], &trans_attr);
        return ret;
    }
    spi_flush_fifo(g_spi_ctrl[id]->reg_base);
    if (!g_spi_ctrl[id]->use_irq) {
        if (g_spi_ctrl[id]->spi_cfg.data_width < HI_SPI_CFG_DATA_WIDTH_E_9BIT) {
            ret = spi_transfer_8bits_block(g_spi_ctrl[id], options);
        } else {
            ret = spi_transfer_16bits_block(g_spi_ctrl[id], options);
        }
    } else {
        ret = spi_host_transfer(id, &trans_attr, data_len, SPI_WRITE_FLAG | SPI_READ_FLAG);
    }

    spi_trans_restore(g_spi_ctrl[id], &trans_attr);
    return ret;
}

hi_u32 hi_spi_set_loop_back_mode(hi_spi_idx id, hi_bool lb_en)
{
    hi_u16 reg_val = 0;
    if (id > HI_SPI_ID_1 || id < HI_SPI_ID_0) {
        return HI_ERR_SPI_PARAMETER_WRONG;
    }
    if (g_spi_ctrl[id] == HI_NULL) {
        return HI_ERR_SPI_NOT_INIT;
    }
    if ((g_spi_ctrl[id]->spi_cfg.fram_mode == HI_SPI_CFG_FRAM_MODE_MICROWIRE ||
        g_spi_ctrl[id]->spi_cfg.is_slave == SPI_CFG_ROLE_SLAVE) && lb_en) {
        return HI_ERR_SPI_PARAMETER_WRONG;
    }
    if (lb_en) {
        hi_reg_read16(g_spi_ctrl[id]->reg_base + REG_SPI_CR1, reg_val);
        reg_val |= (1 << SPI_CR1_ST_BIT_LBM);
        hi_reg_write16(g_spi_ctrl[id]->reg_base + REG_SPI_CR1, reg_val);
        g_spi_ctrl[id]->spi_cfg.loop_back = 1;
    } else {
        g_spi_ctrl[id]->spi_cfg.loop_back = 0;
    }
    return HI_ERR_SUCCESS;
}

hi_u32 hi_spi_slave_write(hi_spi_idx id, hi_pvoid write_data, hi_u32 byte_len, hi_u32 time_out_ms)
{
    hi_u32 ret;
    hi_u32 data_len;
    if ((hi_u32)id > HI_SPI_ID_1 || write_data == HI_NULL || byte_len == 0 || id < HI_SPI_ID_0) {
        return HI_ERR_SPI_PARAMETER_WRONG;
    }
    if (g_spi_ctrl[id] == HI_NULL) {
        return HI_ERR_SPI_NOT_INIT;
    }
    if (g_spi_ctrl[id]->spi_cfg.is_slave != SPI_CFG_ROLE_SLAVE) {
        return HI_ERR_SPI_PARAMETER_WRONG;
    }
    data_len = spi_get_data_len(g_spi_ctrl[id]->spi_cfg.data_width, byte_len);
    if (data_len == 0) {
        return HI_ERR_SPI_PARAMETER_WRONG;
    }
    spi_trans_attr trans_attr = { time_out_ms, SPI_SLAVE_OPT_WRITE };
    g_spi_ctrl[id]->single_len = 0;
    g_spi_ctrl[id]->trans_len = data_len;
    g_spi_ctrl[id]->tx_buf.buf = write_data;
    g_spi_ctrl[id]->tx_buf.cur_pos = 0;
    g_spi_ctrl[id]->tx_buf.cur_cnt = 0;
    ret = spi_trans_prepare(g_spi_ctrl[id], &trans_attr);
    if (ret != HI_ERR_SUCCESS) {
        spi_trans_restore(g_spi_ctrl[id], &trans_attr);
        return ret;
    }
#ifdef CONFIG_SPI_DMA_SUPPORT
    if (g_spi_ctrl[id]->use_dma) { /* transfer less fifo size data, use isr modle first */
        ret = spi_slave_dma_transfer(id, &trans_attr, SPI_WRITE_FLAG);
    } else {
        ret = spi_slave_transfer(id, &trans_attr, SPI_WRITE_FLAG);
    }
#else
    ret = spi_slave_transfer(id, &trans_attr, SPI_WRITE_FLAG);
#endif

    spi_trans_restore(g_spi_ctrl[id], &trans_attr);
    return ret;
}

hi_u32 hi_spi_slave_read(hi_spi_idx id, hi_pvoid read_data, hi_u32 byte_len, hi_u32 time_out_ms)
{
    hi_u32 ret;
    hi_u32 data_len;
    if ((hi_u32)id > HI_SPI_ID_1 || read_data == HI_NULL || byte_len == 0 || id < HI_SPI_ID_0) {
        return HI_ERR_SPI_PARAMETER_WRONG;
    }
    if (g_spi_ctrl[id] == HI_NULL) {
        return HI_ERR_SPI_NOT_INIT;
    }
    if (g_spi_ctrl[id]->spi_cfg.is_slave != SPI_CFG_ROLE_SLAVE) {
        return HI_ERR_SPI_PARAMETER_WRONG;
    }
    data_len = spi_get_data_len(g_spi_ctrl[id]->spi_cfg.data_width, byte_len);
    if (data_len == 0) {
        return HI_ERR_SPI_PARAMETER_WRONG;
    }
    spi_trans_attr trans_attr = { time_out_ms, SPI_SLAVE_OPT_READ };
    g_spi_ctrl[id]->single_len = 0;
    g_spi_ctrl[id]->trans_len = data_len;
    g_spi_ctrl[id]->rx_buf.buf = read_data;
    g_spi_ctrl[id]->rx_buf.cur_pos = 0;
    g_spi_ctrl[id]->rx_buf.cur_cnt = 0;
    spi_flush_fifo(g_spi_ctrl[id]->reg_base);
    ret = spi_trans_prepare(g_spi_ctrl[id], &trans_attr);
    if (ret != HI_ERR_SUCCESS) {
        spi_trans_restore(g_spi_ctrl[id], &trans_attr);
        return ret;
    }
#ifdef CONFIG_SPI_DMA_SUPPORT
    if (g_spi_ctrl[id]->use_dma) {
        ret = spi_slave_dma_transfer(id, &trans_attr, SPI_READ_FLAG);
    } else {
        ret = spi_slave_transfer(id, &trans_attr, SPI_READ_FLAG);
    }
#else
    ret = spi_slave_transfer(id, &trans_attr, SPI_READ_FLAG);
#endif

    spi_trans_restore(g_spi_ctrl[id], &trans_attr);
    return ret;
}

hi_u32 hi_spi_host_writeread(hi_spi_idx id, hi_pvoid write_data, hi_pvoid read_data, hi_u32 byte_len)
{
    if ((id > HI_SPI_ID_1) || (id < HI_SPI_ID_0) || byte_len == 0 ||
        (write_data == HI_NULL) || (read_data == HI_NULL)) {
        return HI_ERR_SPI_PARAMETER_WRONG;
    }
    return spi_host_writeread(id, write_data, read_data, byte_len, SPI_HOST_OPT_BASE);
}

hi_u32 hi_spi_host_read(hi_spi_idx id, hi_pvoid read_data, hi_u32 byte_len)
{
    if ((id > HI_SPI_ID_1) || (id < HI_SPI_ID_0) || (byte_len == 0) || (read_data == HI_NULL)) {
        return HI_ERR_SPI_PARAMETER_WRONG;
    }
    return spi_host_writeread(id, HI_NULL, read_data, byte_len, (SPI_HOST_OPT_BASE) | SPI_OPT_SEND_FIX_DATA);
}

hi_u32 hi_spi_host_write(hi_spi_idx id, hi_pvoid write_data, hi_u32 byte_len)
{
    if ((id > HI_SPI_ID_1) || (id < HI_SPI_ID_0) || (byte_len == 0) || (write_data == HI_NULL)) {
        return HI_ERR_SPI_PARAMETER_WRONG;
    }
    return spi_host_writeread(id, write_data, HI_NULL, byte_len, (SPI_HOST_OPT_BASE) | SPI_OPT_RCV_FIX_DATA);
}

hi_u32 hi_spi_set_irq_mode(hi_spi_idx id, hi_bool irq_en)
{
    if ((id > HI_SPI_ID_1) || (id < HI_SPI_ID_0)) {
        return HI_ERR_SPI_PARAMETER_WRONG;
    }
    if (g_spi_ctrl[id] == HI_NULL) {
        return HI_ERR_SPI_NOT_INIT;
    }
    if (g_spi_ctrl[id]->transferring) {
        return HI_ERR_SPI_BUSY;
    }
    g_spi_ctrl[id]->use_irq = irq_en;
    if (!irq_en) {
        spi_isr_disable(g_spi_ctrl[id]->reg_base, SPI_INT_BIT_TX_FIFO_WATER_LINE |
                        SPI_INT_BIT_RX_FIFO_WATER_LINE |
                        SPI_INT_BIT_RX_FIFO_TIME_OUT);
    }
    return HI_ERR_SUCCESS;
}

hi_u32 hi_spi_set_dma_mode(hi_spi_idx id, hi_bool dma_en)
{
    if (id > HI_SPI_ID_1) {
        return HI_ERR_SPI_PARAMETER_WRONG;
    }
    if (g_spi_ctrl[id] == HI_NULL) {
        return HI_ERR_SPI_NOT_INIT;
    }
    if (g_spi_ctrl[id]->transferring) {
        return HI_ERR_SPI_BUSY;
    }
#ifdef CONFIG_SPI_DMA_SUPPORT
    g_spi_ctrl[id]->use_dma = dma_en;
#else
    hi_unref_param(dma_en);
    return HI_ERR_SPI_NOT_SUPPORT_DMA;
#endif
    return HI_ERR_SUCCESS;
}

hi_u32 hi_spi_register_usr_func(hi_spi_idx id, hi_spi_usr_func prepare_func, hi_spi_usr_func restore_func)
{
    if ((id > HI_SPI_ID_1) || (id < HI_SPI_ID_0)) {
        return HI_ERR_SPI_PARAMETER_WRONG;
    }
    if (g_spi_ctrl[id] == HI_NULL) {
        return HI_ERR_SPI_NOT_INIT;
    }

    if (g_spi_ctrl[id]->transferring) {
        return HI_ERR_SPI_BUSY;
    }
    g_spi_ctrl[id]->prepare_func = prepare_func;
    g_spi_ctrl[id]->restore_func = restore_func;
    return HI_ERR_SUCCESS;
}

hi_u32 hi_spi_set_basic_info(hi_spi_idx id, const hi_spi_cfg_basic_info *param)
{
    hi_u32 ret;
    hi_u32 spi_clk = spi_get_clk();
    if (((hi_u32)id > HI_SPI_ID_1) || (param == HI_NULL) || (id < HI_SPI_ID_0)) {
        return HI_ERR_SPI_PARAMETER_WRONG;
    }

    if (g_spi_ctrl[id] == HI_NULL) {
        return HI_ERR_SPI_NOT_INIT;
    }

    if (g_spi_ctrl[id]->transferring) {
        return HI_ERR_SPI_BUSY;
    }

    if (param->fram_mode > HI_SPI_CFG_FRAM_MODE_MICROWIRE || param->data_width < HI_SPI_CFG_DATA_WIDTH_E_4BIT ||
        param->freq > spi_max_speed(spi_clk) || param->freq < spi_min_speed(spi_clk)) {
        return HI_ERR_SPI_PARAMETER_WRONG;
    }
    if (g_spi_ctrl[id]->spi_cfg.loop_back == HI_TRUE && (param->fram_mode == HI_SPI_CFG_FRAM_MODE_MICROWIRE ||
        g_spi_ctrl[id]->spi_cfg.is_slave == SPI_CFG_ROLE_SLAVE)) {
        return HI_ERR_SPI_PARAMETER_WRONG;
    }

    /* compute spi speed, speed=clk/(cpsdvsr*(scr+1)) */
    hi_u32 tmp = spi_clk / param->freq;
    if (tmp < CPSDVSR_MIN) {
        g_spi_ctrl[id]->spi_cfg.cpsdvsr = CPSDVSR_MIN;
        g_spi_ctrl[id]->spi_cfg.scr = 0;
    } else if (tmp <= CPSDVSR_MAX) {
        g_spi_ctrl[id]->spi_cfg.cpsdvsr = (hi_u16)(tmp & (~0x1));
        g_spi_ctrl[id]->spi_cfg.scr = (tmp / g_spi_ctrl[id]->spi_cfg.cpsdvsr) - 1;
    } else {
        g_spi_ctrl[id]->spi_cfg.cpsdvsr = CPSDVSR_MAX;
        g_spi_ctrl[id]->spi_cfg.scr = (tmp / g_spi_ctrl[id]->spi_cfg.cpsdvsr) - 1;
    }

    g_spi_ctrl[id]->spi_cfg.data_width = param->data_width;
    g_spi_ctrl[id]->spi_cfg.fram_mode = param->fram_mode;
    g_spi_ctrl[id]->spi_cfg.cpol = param->cpol;
    g_spi_ctrl[id]->spi_cfg.cpha = param->cpha;
    g_spi_ctrl[id]->spi_cfg.endian = param->endian;
    /* write reg */
    ret = spi_config(g_spi_ctrl[id]);
    return ret;
}

static hi_void spi_ctrl_init(hi_spi_idx id, hi_spi_cfg_init_param init_param)
{
    g_spi_ctrl[id]->spi_cfg.loop_back = HI_FALSE;
    hi_u16 reg_val;
    hi_reg_read16(CLDO_CTL_CLKEN_REG, reg_val);
    if (id == HI_SPI_ID_0) {
        g_spi_ctrl[id]->spi_cfg.tx_fifo_line = SPI0_TX_FIFO_WATER_LINE;
        g_spi_ctrl[id]->spi_cfg.rx_fifo_line = SPI0_RX_FIFO_WATER_LINE;
        g_spi_ctrl[id]->spi_cfg.tx_fifo_dma_line = SPI0_TX_FIFO_DMA_WLINE_64;
        g_spi_ctrl[id]->spi_cfg.rx_fifo_dma_line = SPI0_RX_FIFO_DMA_WLINE_128;
        reg_val |= 1 << CLKEN_SPI0;
    } else {
        g_spi_ctrl[id]->spi_cfg.tx_fifo_line = SPI1_TX_FIFO_WATER_LINE;
        g_spi_ctrl[id]->spi_cfg.rx_fifo_line = SPI1_RX_FIFO_WATER_LINE;
        g_spi_ctrl[id]->spi_cfg.tx_fifo_dma_line = SPI1_TX_FIFO_DMA_WLINE_16;
        g_spi_ctrl[id]->spi_cfg.rx_fifo_dma_line = SPI1_RX_FIFO_DMA_WLINE_32;
        reg_val |= 1 << CLKEN_SPI1;
    }
    hi_reg_write16(CLDO_CTL_CLKEN_REG, reg_val); /* enable spix clk bus */
    g_spi_ctrl[id]->spi_cfg.is_slave = init_param.is_slave ? SPI_CFG_ROLE_SLAVE : SPI_CFG_ROLE_MASTER;
    spi_reset(g_spi_ctrl[id]);
    spi_set_fifo_line(g_spi_ctrl[id]);
#ifdef CONFIG_SPI_DMA_SUPPORT
    spi_set_dma_fifo_line(g_spi_ctrl[id]);
#endif
    spi_isr_disable(g_spi_ctrl[id]->reg_base,
                    SPI_INT_BIT_RX_FIFO_WATER_LINE | SPI_INT_BIT_RX_FIFO_TIME_OUT | SPI_INT_BIT_RX_FIFO_OVER_FLOW);
}

#ifdef CONFIG_SPI_DMA_SUPPORT
static hi_u32 spi_dma_init(hi_void)
{
    hi_u32 ret = HI_ERR_SUCCESS;
    if (hi_dma_is_init() == HI_FALSE) {
        ret = hi_dma_init();
    }
    return ret;
}
#endif

hi_u32 hi_spi_init(hi_spi_idx id, hi_spi_cfg_init_param init_param, const hi_spi_cfg_basic_info *param)
{
    if ((id > HI_SPI_ID_1) || (param == HI_NULL) || (id < HI_SPI_ID_0)) {
        return HI_ERR_SPI_PARAMETER_WRONG;
    }
    hi_u32 ret;
    if (g_spi_ctrl[id] != HI_NULL) {
        return HI_ERR_SPI_REINIT;
    }

    g_spi_ctrl[id] = (spi_ctrl *)hi_malloc(HI_MOD_ID_DRV_SPI, sizeof(spi_ctrl));
    if (g_spi_ctrl[id] == HI_NULL) {
        return HI_ERR_MALLOC_FAILUE;
    }
    memset_s(g_spi_ctrl[id], sizeof(spi_ctrl), 0x0, sizeof(spi_ctrl));
    g_spi_ctrl[id]->reg_base = (id == HI_SPI_ID_0) ? HI_SSP0_REG_BASE : HI_SSP1_REG_BASE;

    ret = hi_sem_bcreate(&g_spi_ctrl[id]->sem_id, 1);
    if (ret != HI_ERR_SUCCESS) {
        goto init_fail;
    }

    ret = hi_event_create(&g_spi_ctrl[id]->event_id);
    if (ret != HI_ERR_SUCCESS) {
        goto init_fail2;
    }

    g_spi_ctrl[id]->irq_num = (id == HI_SPI_ID_0) ? SSP_0_IRQ : SSP_1_IRQ;
    ret = hi_irq_request(g_spi_ctrl[id]->irq_num, HI_IRQ_FLAG_PRI2, (irq_routine)spi_isr, (uintptr_t)g_spi_ctrl[id]);
    if (ret != HI_ERR_SUCCESS) {
        goto init_fail3;
    }
    spi_ctrl_init(id, init_param);
    ret = (hi_u32)hi_spi_set_basic_info(id, param);
    if (ret != HI_ERR_SUCCESS) {
        goto init_fail4;
    }

#ifdef CONFIG_SPI_DMA_SUPPORT
    return spi_dma_init();
#endif

    return HI_ERR_SUCCESS;

init_fail4:
    (hi_void) hi_irq_free(g_spi_ctrl[id]->irq_num);
init_fail3:
    (hi_void) hi_event_delete(g_spi_ctrl[id]->event_id);
init_fail2:
    (hi_void) hi_sem_delete(g_spi_ctrl[id]->sem_id);
init_fail:
    hi_free(HI_MOD_ID_DRV_SPI, g_spi_ctrl[id]);
    g_spi_ctrl[id] = HI_NULL;
    return ret;
}

hi_u32 hi_spi_deinit(hi_spi_idx id)
{
    hi_u16 reg_val;
    if ((id > HI_SPI_ID_1) || (id < HI_SPI_ID_0)) {
        return HI_ERR_SPI_PARAMETER_WRONG;
    }
    if (g_spi_ctrl[id] == HI_NULL) {
        return HI_ERR_SUCCESS; /* HI_ERR_SPI_NOT_INIT return success */
    }
    if (g_spi_ctrl[id]->transferring) {
        return HI_ERR_SPI_BUSY;
    }

    spi_isr_disable(g_spi_ctrl[id]->reg_base,
                    SPI_INT_BIT_RX_FIFO_WATER_LINE | SPI_INT_BIT_RX_FIFO_TIME_OUT | SPI_INT_BIT_RX_FIFO_OVER_FLOW);
    hi_irq_disable(g_spi_ctrl[id]->irq_num);
    (hi_void) hi_irq_free(g_spi_ctrl[id]->irq_num);

    (hi_void) hi_sem_delete(g_spi_ctrl[id]->sem_id);
    (hi_void) hi_event_delete(g_spi_ctrl[id]->event_id);
    /* disable spi */
    spi_disable(g_spi_ctrl[id]);
    hi_free(HI_MOD_ID_DRV_SPI, g_spi_ctrl[id]);
    g_spi_ctrl[id] = HI_NULL;
    hi_reg_read16(CLDO_CTL_CLKEN_REG, reg_val);
    reg_val &= (id == HI_SPI_ID_0) ? ~(1 << CLKEN_SPI0) : ~(1 << CLKEN_SPI1);
    hi_reg_write16(CLDO_CTL_CLKEN_REG, reg_val); /* disable spix clk bus */
    return HI_ERR_SUCCESS;
}
