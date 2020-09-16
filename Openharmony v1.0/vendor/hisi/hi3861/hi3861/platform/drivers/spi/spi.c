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

#include "spi.h"
#include <hi_time.h>
#include <hi_stdlib.h>
#include <hi_isr.h>
#include <hi_event.h>
#ifdef CONFIG_SPI_DMA_SUPPORT
#include <dma.h>
#endif

spi_ctrl *g_spi_ctrl[SPI_NUM] = { 0 };

HI_ALWAYS_STAIC_INLINE hi_bool spi_check_rx_fifo_empty(hi_u32 reg_base)
{
    hi_u16 reg_val = 0;
    hi_reg_read16(reg_base + REG_SPI_SR, reg_val);
    if (reg_val & MASK_SPI_SR_RNE) {
        return HI_FALSE;
    }
    return HI_TRUE;
}

HI_ALWAYS_STAIC_INLINE hi_bool spi_check_busy(hi_u32 reg_base)
{
    hi_u16 reg_val = 0;
    hi_reg_read16(reg_base + REG_SPI_SR, reg_val);
    if (reg_val & MASK_SPI_SR_BSY) {
        return HI_TRUE;
    }
    return HI_FALSE;
}

HI_ALWAYS_STAIC_INLINE hi_u32 spi_check_write_timeout(hi_u32 reg_base)
{
    hi_u16 reg_val = 0;
    hi_u32 count = 0;
    while (count++ < SPI_HOST_TIMEOUT_US) {
        hi_reg_read16(reg_base + REG_SPI_SR, reg_val);
        if ((reg_val & MASK_SPI_SR_TFE) && (!(reg_val & MASK_SPI_SR_BSY))) {
            break;
        }
        hi_udelay(1);
    }
    if (count >= SPI_HOST_TIMEOUT_US) {
        spi_process_printf("%s spi transfer wait timeout!", __func__);
        return HI_ERR_SPI_WRITE_TIMEOUT;
    }
    return HI_ERR_SUCCESS;
}

/* check tx fifo not full */
HI_ALWAYS_STAIC_INLINE hi_u32 spi_check_tnf_timeout(hi_u32 reg_base, HI_CONST hi_u32 time_out_us)
{
    hi_u16 reg_val = 0;
    hi_u32 count = 0;
    while (count++ < time_out_us) {
        hi_reg_read16(reg_base + REG_SPI_SR, reg_val);
        if ((reg_val & MASK_SPI_SR_TNF)) {
            break;
        }
        hi_udelay(1);
    }
    if (count >= time_out_us) {
        if (reg_val & MASK_SPI_SR_TNF) {
            spi_process_printf("MASK_SPI_SR_TNF\n");
        }
        if (reg_val & MASK_SPI_SR_BSY) {
            spi_process_printf("MASK_SPI_SR_BSY \n");
        }
        return HI_ERR_SPI_WRITE_TIMEOUT;
    }
    return HI_ERR_SUCCESS;
}
/* check rx fifo not empty */
HI_ALWAYS_STAIC_INLINE hi_u32 spi_check_rne_timeout(hi_u32 reg_base, HI_CONST hi_u32 time_out_us)
{
    hi_u16 reg_val = 0;
    hi_u32 count = 0;
    while (count++ < time_out_us) {
        hi_reg_read16(reg_base + REG_SPI_SR, reg_val);
        if (((reg_val & MASK_SPI_SR_RNE))) {
            break;
        }
        hi_udelay(1);
    }
    if (count >= time_out_us) {
        spi_process_printf("%s timeout!\n", __func__);
        return HI_ERR_SPI_WRITE_TIMEOUT;
    }
    return HI_ERR_SUCCESS;
}

/*
 * spi_flush_fifo: flush spi fifo
 */
hi_void spi_flush_fifo(hi_u32 reg_base)
{
    hi_u16 reg_val = 0;
    hi_u16 fifo_len = (reg_base == HI_SSP0_REG_BASE ? SPI0_FIFO_LEN : SPI1_FIFO_LEN);
    for (hi_u16 i = 0; i < fifo_len; i++) {
        hi_reg_read16(reg_base + REG_SPI_SR, reg_val);
        if (!(reg_val & MASK_SPI_SR_RNE)) {
            break;
        }
        hi_reg_read16(reg_base + REG_SPI_DR, reg_val);
    }
}

hi_void spi_disable(spi_ctrl *ctrl)
{
    hi_u16 reg_val = 0;
    if (ctrl == NULL) {
        spi_process_printf("spi_disable para is null \n");
        return;
    }
    if ((ctrl->spi_cfg.is_slave == 0) && spi_check_busy(ctrl->reg_base)) {
        ctrl->disable_later = HI_TRUE;
        return;
    }
    hi_reg_read16(ctrl->reg_base + REG_SPI_CR1, reg_val);
    reg_val &= ~(1 << SPI_CR1_ST_BIT_SSE);
    hi_reg_write16(ctrl->reg_base + REG_SPI_CR1, reg_val);
}

static hi_void spi_enable(spi_ctrl *ctrl)
{
    hi_u16 reg_val = 0;

    hi_reg_read16(ctrl->reg_base + REG_SPI_CR1, reg_val);
    reg_val |= (1 << SPI_CR1_ST_BIT_SSE);
    hi_reg_write16(ctrl->reg_base + REG_SPI_CR1, reg_val);
    ctrl->disable_later = HI_FALSE;
}

hi_void spi_reset(const spi_ctrl *spi_hw_ctrl)
{
    hi_u8 reset_bit;
    hi_u16 reg_val = 0;
    hi_u32 int_value;
    if (spi_hw_ctrl != HI_NULL &&
        spi_hw_ctrl->reg_base == HI_SSP0_REG_BASE) {
        reset_bit = CRG_REG_SSP_SRST_REQ_OFFSET;
    } else {
        reset_bit = CRG_REG_SSP2_SRST_REQ_OFFSET;
    }
    int_value = hi_int_lock();
    hi_reg_read16(CLDO_CTL_SOFT_RESET_REG, reg_val);
    reg_val &= (~((hi_u16)(1 << reset_bit)));
    hi_reg_write16(CLDO_CTL_SOFT_RESET_REG, reg_val);
    reg_val |= (hi_u16)(1 << reset_bit);
    hi_reg_write16(CLDO_CTL_SOFT_RESET_REG, reg_val);
    hi_int_restore(int_value);
}

hi_u32 spi_config(const spi_ctrl *spi_hw_ctrl)
{
    spi_inner_cfg inner_cfg = { 0 };
    if (spi_hw_ctrl == HI_NULL) {
        return HI_ERR_FAILURE;
    }
    if (memcpy_s(&inner_cfg, sizeof(spi_inner_cfg), &spi_hw_ctrl->spi_cfg, sizeof(spi_inner_cfg)) == EOK) {
        hi_reg_write16(spi_hw_ctrl->reg_base + REG_SPI_CR0, inner_cfg.cr0);
        hi_reg_write16(spi_hw_ctrl->reg_base + REG_SPI_CR1, inner_cfg.cr1);
        hi_reg_write16(spi_hw_ctrl->reg_base + REG_SPI_CPSR, inner_cfg.cpsdvsr);
    } else {
        return HI_ERR_FAILURE;
    }
    return HI_ERR_SUCCESS;
}

hi_void spi_set_fifo_line(const spi_ctrl *spi_hw_ctrl)
{
    hi_u16 reg_val;
    if (spi_hw_ctrl == HI_NULL) {
        return;
    }
    hi_reg_read16(spi_hw_ctrl->reg_base + REG_SPI_TXFIFOCR, reg_val);
    reg_val &= ~(hi_u16)(SPI_FIFO_LINE_MASK << SPI_FIFO_LINE_OFFSET);
    reg_val |= (hi_u16)(spi_hw_ctrl->spi_cfg.tx_fifo_line << SPI_FIFO_LINE_OFFSET);
    hi_reg_write16(spi_hw_ctrl->reg_base + REG_SPI_TXFIFOCR, reg_val);
    hi_reg_read16(spi_hw_ctrl->reg_base + REG_SPI_RXFIFOCR, reg_val);
    reg_val &= ~(hi_u16)(SPI_FIFO_LINE_MASK << SPI_FIFO_LINE_OFFSET);
    reg_val |= (hi_u16)(spi_hw_ctrl->spi_cfg.rx_fifo_line << SPI_FIFO_LINE_OFFSET);
    hi_reg_write16(spi_hw_ctrl->reg_base + REG_SPI_RXFIFOCR, reg_val);
}

#ifdef CONFIG_SPI_DMA_SUPPORT
hi_void spi_set_dma_fifo_line(const spi_ctrl *spi_hw_ctrl)
{
    hi_u16 reg_val;
    if (spi_hw_ctrl == HI_NULL) {
        return;
    }
    hi_reg_read16(spi_hw_ctrl->reg_base + REG_SPI_TXFIFOCR, reg_val);
    reg_val &= ~(hi_u16)(SPI_FIFO_LINE_MASK);
    reg_val |= (hi_u16)(spi_hw_ctrl->spi_cfg.tx_fifo_dma_line);
    hi_reg_write16(spi_hw_ctrl->reg_base + REG_SPI_TXFIFOCR, reg_val);
    hi_reg_read16(spi_hw_ctrl->reg_base + REG_SPI_RXFIFOCR, reg_val);
    reg_val &= ~(hi_u16)(SPI_FIFO_LINE_MASK);
    reg_val |= (hi_u16)(spi_hw_ctrl->spi_cfg.rx_fifo_dma_line);
    hi_reg_write16(spi_hw_ctrl->reg_base + REG_SPI_RXFIFOCR, reg_val);
}

hi_void dma_write_fifo_callback(hi_u32 irq_type)
{
    spi_process_printf("This is callback,irq type is %d\r\n", irq_type);
    if (irq_type == DMA_INT_TC) {
        hi_event_send(g_spi_ctrl[0]->event_id, HI_EVENT_BIT_DMA_TX_DATA);
    } else {
        hi_event_send(g_spi_ctrl[0]->event_id, HI_EVENT_BIT_DMA_TX_ERR_DATA);
    }
}
hi_void dma_read_fifo_callback(hi_u32 irq_type)
{
    spi_process_printf("This is callback,irq type is %d\r\n", irq_type);
    if (irq_type == DMA_INT_TC) {
        hi_event_send(g_spi_ctrl[0]->event_id, HI_EVENT_BIT_DMA_RX_DATA);
    } else {
        hi_event_send(g_spi_ctrl[0]->event_id, HI_EVENT_BIT_DMA_RX_ERR_DATA);
    }
}
hi_void dma_write_fifo_callback_spi1(hi_u32 irq_type)
{
    spi_process_printf("This is callback,irq type is %d\r\n", irq_type);
    if (irq_type == DMA_INT_TC) {
        hi_event_send(g_spi_ctrl[1]->event_id, HI_EVENT_BIT_DMA_TX_DATA);
    } else {
        hi_event_send(g_spi_ctrl[1]->event_id, HI_EVENT_BIT_DMA_TX_ERR_DATA);
    }
}
hi_void dma_read_fifo_callback_spi1(hi_u32 irq_type)
{
    spi_process_printf("This is callback,irq type is %d\r\n", irq_type);
    if (irq_type == DMA_INT_TC) {
        hi_event_send(g_spi_ctrl[1]->event_id, HI_EVENT_BIT_DMA_RX_DATA);
    } else {
        hi_event_send(g_spi_ctrl[1]->event_id, HI_EVENT_BIT_DMA_RX_ERR_DATA);
    }
}

HI_ALWAYS_STAIC_INLINE hi_u32 spi_get_rx_dma_burst_size(spi_ctrl *spi_dev_ctrl)
{
    spi_hw_cfg *spi_cfg = &(spi_dev_ctrl->spi_cfg);
    if (spi_dev_ctrl->reg_base == HI_SSP0_REG_BASE) {
        return spi_cfg->rx_fifo_dma_line >=
                SPI0_RX_FIFO_DMA_WLINE_128 ? DMA_BURST_MSIZE_128 : spi_cfg->rx_fifo_dma_line;
    } else {
        return spi_cfg->rx_fifo_dma_line >= SPI1_RX_FIFO_DMA_WLINE_32 ? DMA_BURST_MSIZE_32 : spi_cfg->rx_fifo_dma_line;
    }
}

HI_ALWAYS_STAIC_INLINE hi_u32 spi_get_tx_dma_burst_size(spi_ctrl *spi_dev_ctrl)
{
    spi_hw_cfg *spi_cfg = &(spi_dev_ctrl->spi_cfg);
    if (spi_dev_ctrl->reg_base == HI_SSP0_REG_BASE) {
        return spi_cfg->tx_fifo_dma_line >= SPI0_TX_FIFO_DMA_WLINE_64 ? DMA_BURST_MSIZE_128 : spi_cfg->tx_fifo_dma_line;
    } else {
        return spi_cfg->tx_fifo_dma_line >= SPI1_TX_FIFO_DMA_WLINE_16 ? DMA_BURST_MSIZE_32 : spi_cfg->tx_fifo_dma_line;
    }
}

hi_void spi_dma_enable(hi_u32 reg_base, hi_u16 enable_bits) /* 使能DMA(按bit操作) */
{
    hi_u16 reg_val = 0;
    hi_u32 int_save;
    int_save = hi_int_lock();
    hi_reg_read16(reg_base + REG_SPI_DMACR, reg_val);
    reg_val |= enable_bits;
    hi_reg_write16(reg_base + REG_SPI_DMACR, reg_val);
    hi_int_restore(int_save);
    spi_process_printf("dma enable 0x%x 0x%x", reg_base, reg_val);
}

hi_void spi_dma_disable(hi_u32 reg_base, hi_u16 disable_bits) /* 清除DMA使能位(按bit操作) */
{
    hi_u16 reg_val = 0;
    hi_u32 int_save;
    int_save = hi_int_lock();
    hi_reg_read16(reg_base + REG_SPI_DMACR, reg_val);
    reg_val &= (~disable_bits);
    hi_reg_write16(reg_base + REG_SPI_DMACR, reg_val);
    hi_int_restore(int_save);
}

hi_u32 spi_dma_transer(hi_u32 tr_type, spi_ctrl *spi_dev_ctrl, uintptr_t addr, hi_u32 tran_len,
                       hi_void (*cb)(hi_u32),
                       hi_u32 *ch_num)
{
    hi_u32 reg_base = spi_dev_ctrl->reg_base;
    hi_u32 data_width = WIDTH_BIT8;
    if (hi_unlikely(spi_dev_ctrl->spi_cfg.data_width > HI_SPI_CFG_DATA_WIDTH_E_8BIT)) {
        data_width = WIDTH_BIT16;
    }
    hi_u8 dma_burst_size;
    hi_u32 dma_ts;
    hi_dma_para dma_para;
    dma_para.tr_type = tr_type;
    dma_para.src_width = data_width;
    dma_para.dst_width = data_width;
    if (tr_type == MEM_TO_SPI) {
        dma_para.dst_addr = reg_base + REG_SPI_DR;
        dma_para.src_addr = addr;
        dma_para.dst_phl = (reg_base == HI_SSP0_REG_BASE) ? SPI0_TX : SPI1_TX;
        dma_para.src_phl = 0;
        dma_burst_size = spi_get_tx_dma_burst_size(spi_dev_ctrl);
    } else {
        dma_para.dst_addr = addr;
        dma_para.src_addr = reg_base + REG_SPI_DR;
        dma_para.dst_phl = 0;
        dma_para.src_phl = (reg_base == HI_SSP0_REG_BASE) ? SPI0_RX : SPI1_RX;
        dma_burst_size = spi_get_rx_dma_burst_size(spi_dev_ctrl);
    }
    dma_ts = spi_get_transfer_size(dma_burst_size);
    dma_para.dst_burst_size = (dma_ts > tran_len) ? DMA_BURST_MSIZE_1 : dma_burst_size;
    dma_para.src_burst_size = (dma_ts > tran_len) ? DMA_BURST_MSIZE_1 : dma_burst_size;
    dma_para.transfer_size = tran_len;
    dma_para.cb = cb;
    return dma_hw_request_transfer(&dma_para, ch_num);
}

/*
・dma read fifo can used for slave device
 */
hi_u32 spi_hd_dma_read_fifo(spi_ctrl *spi_dev_ctrl, hi_u32 timeout_ms)
{
    if (spi_dev_ctrl == HI_NULL) {
        return HI_ERR_FAILURE;
    }
    hi_pvoid read_buf = spi_dev_ctrl->rx_buf.buf;
    hi_u32 read_pos = spi_dev_ctrl->rx_buf.cur_pos;
    hi_u32 loop = spi_dev_ctrl->trans_len - spi_dev_ctrl->rx_buf.cur_cnt;
    hi_u32 ret;
    hi_u32 event_bit = 0;
    hi_u32 ch_num = 0xff; /* set invalid value 0xff */
    if (spi_dev_ctrl->reg_base == HI_SSP0_REG_BASE) {
        if (spi_dev_ctrl->spi_cfg.data_width < HI_SPI_CFG_DATA_WIDTH_E_9BIT) {
            ret = spi_dma_transer(SPI_TO_MEM, spi_dev_ctrl, (uintptr_t)((hi_u8 *)read_buf + read_pos), loop,
                                  dma_read_fifo_callback, &ch_num);
        } else {
            ret = spi_dma_transer(SPI_TO_MEM, spi_dev_ctrl, (uintptr_t)((hi_u16 *)read_buf + read_pos), loop,
                                  dma_read_fifo_callback, &ch_num);
        }
    } else {
        if (spi_dev_ctrl->spi_cfg.data_width < HI_SPI_CFG_DATA_WIDTH_E_9BIT) {
            ret = spi_dma_transer(SPI_TO_MEM, spi_dev_ctrl, (uintptr_t)((hi_u8 *)read_buf + read_pos), loop,
                                  dma_read_fifo_callback_spi1, &ch_num);
        } else {
            ret = spi_dma_transer(SPI_TO_MEM, spi_dev_ctrl, (uintptr_t)((hi_u16 *)read_buf + read_pos), loop,
                                  dma_read_fifo_callback_spi1, &ch_num);
        }
    }
    if (ret != HI_ERR_SUCCESS) {
        return ret;
    }
    ret = hi_event_wait(spi_dev_ctrl->event_id, HI_EVENT_BIT_DMA_RX_DATA, &event_bit, timeout_ms,
                        HI_EVENT_WAITMODE_OR | HI_EVENT_WAITMODE_CLR);
    if (event_bit & HI_EVENT_BIT_DMA_RX_ERR_DATA) {
        spi_process_printf("DMA trans err\n");
        return HI_ERR_FAILURE;
    }
    if (ret == HI_ERR_EVENT_WAIT_TIME_OUT) {
        hi_dma_ch_close(ch_num);
        spi_process_printf("read time out\n");
        return HI_ERR_SPI_WRITE_TIMEOUT;
    }
    spi_dev_ctrl->rx_buf.cur_cnt += loop; /* update cur_cnt and read_pos/cur_pos */
    spi_dev_ctrl->rx_buf.cur_pos += loop;
    return ret;
}
hi_u32 spi_hd_dma_write_fifo(spi_ctrl *spi_dev_ctrl, hi_u32 timeout_ms)
{
    if (spi_dev_ctrl == NULL) {
        return HI_ERR_FAILURE;
    }
    hi_pvoid write_buf = spi_dev_ctrl->tx_buf.buf;
    hi_u32 write_pos = spi_dev_ctrl->tx_buf.cur_pos;
    hi_u32 loop = spi_dev_ctrl->trans_len - spi_dev_ctrl->tx_buf.cur_cnt;
    hi_u32 ret;
    hi_u32 event_bit = 0;
    hi_u32 ch_num = 0xff; /* set invalid value 0xff */
    if (spi_dev_ctrl->reg_base == HI_SSP0_REG_BASE) {
        if (spi_dev_ctrl->spi_cfg.data_width < HI_SPI_CFG_DATA_WIDTH_E_9BIT) {
            ret = spi_dma_transer(MEM_TO_SPI, spi_dev_ctrl, (uintptr_t)((hi_u8 *)write_buf + write_pos), loop,
                                  dma_write_fifo_callback, &ch_num);
        } else {
            ret = spi_dma_transer(MEM_TO_SPI, spi_dev_ctrl, (uintptr_t)((hi_u16 *)write_buf + write_pos), loop,
                                  dma_write_fifo_callback, &ch_num);
        }
    } else {
        if (spi_dev_ctrl->spi_cfg.data_width < HI_SPI_CFG_DATA_WIDTH_E_9BIT) {
            ret = spi_dma_transer(MEM_TO_SPI, spi_dev_ctrl, (uintptr_t)((hi_u8 *)write_buf + write_pos), loop,
                                  dma_write_fifo_callback_spi1, &ch_num);
        } else {
            ret = spi_dma_transer(MEM_TO_SPI, spi_dev_ctrl, (uintptr_t)((hi_u16 *)write_buf + write_pos), loop,
                                  dma_write_fifo_callback_spi1, &ch_num);
        }
    }
    if (ret != HI_ERR_SUCCESS) { /* dma fail */
        return ret;
    }
    ret = hi_event_wait(spi_dev_ctrl->event_id, HI_EVENT_BIT_DMA_TX_DATA | HI_EVENT_BIT_DMA_TX_ERR_DATA, &event_bit,
                        timeout_ms, HI_EVENT_WAITMODE_OR | HI_EVENT_WAITMODE_CLR);
    if (event_bit & HI_EVENT_BIT_DMA_TX_ERR_DATA) {
        spi_process_printf("DMA trans err\n");
        return HI_ERR_FAILURE;
    }
    if (ret == HI_ERR_EVENT_WAIT_TIME_OUT) {
        hi_dma_ch_close(ch_num);
        spi_process_printf("WRITE time out, ch_num:%d, ret:%x\n", ch_num, ret);
        return HI_ERR_SPI_WRITE_TIMEOUT;
    }
    spi_dev_ctrl->tx_buf.cur_cnt += loop; /* update cur_cnt and read_pos/cur_pos */
    spi_dev_ctrl->tx_buf.cur_pos += loop;
    return ret;
}
#endif

hi_void spi_isr_enable(hi_u32 reg_base, hi_u16 enable_bits)
{
    hi_u16 reg_val = 0;
    hi_u32 int_save;
    int_save = hi_int_lock();
    hi_reg_read16(reg_base + REG_SPI_IMSC, reg_val);
    reg_val |= enable_bits;
    hi_reg_write16(reg_base + REG_SPI_IMSC, reg_val);
    hi_int_restore(int_save);
    spi_process_printf("isr enable 0x%x 0x%x", reg_base, reg_val);
}

hi_void spi_isr_disable(hi_u32 reg_base, hi_u16 disable_bits)
{
    hi_u16 reg_val = 0;
    hi_u32 int_save;
    int_save = hi_int_lock();
    hi_reg_read16(reg_base + REG_SPI_IMSC, reg_val);
    reg_val &= (~disable_bits);
    hi_reg_write16(reg_base + REG_SPI_IMSC, reg_val);
    hi_int_restore(int_save);
}
hi_void spi_isr_clear_cr(hi_u32 reg_base, hi_u16 clear_bit)
{
    hi_u16 reg_val = 0;
    hi_u32 int_save;
    int_save = hi_int_lock();
    hi_reg_read16(reg_base + REG_SPI_CR, reg_val);
    reg_val |= clear_bit;
    hi_reg_write16(reg_base + REG_SPI_CR, reg_val);
    hi_int_restore(int_save);
}

HI_ALWAYS_STAIC_INLINE hi_void spi_isr_read_16bits(spi_ctrl *spi_dev_ctrl, hi_bool fifo_irq, hi_u32 loop,
                                                   hi_pvoid read_buf, hi_u16 increase_step)
{
    hi_u32 i;
    hi_u32 reg_base = spi_dev_ctrl->reg_base;
    hi_u32 read_pos = spi_dev_ctrl->rx_buf.cur_pos;
    if (fifo_irq) {
        for (i = 0; i < loop; i++) {
            *((hi_u16 *)read_buf + read_pos) = (hi_u16)hi_reg_read_val16(reg_base + REG_SPI_DR);
            read_pos += increase_step;
        }
        spi_dev_ctrl->rx_buf.cur_cnt += loop;
    } else {
        for (i = 0; i < loop; i++) {
            if (hi_likely(!spi_check_rx_fifo_empty(reg_base))) {
                *((hi_u16 *)read_buf + read_pos) = (hi_u16)hi_reg_read_val16(reg_base + REG_SPI_DR);
                read_pos += increase_step;
                spi_dev_ctrl->rx_buf.cur_cnt++;
            } else {
                break;
            }
        }
    }
    spi_dev_ctrl->rx_buf.cur_pos = read_pos;
}

HI_ALWAYS_STAIC_INLINE hi_void spi_isr_read_8bits(spi_ctrl *spi_dev_ctrl, hi_bool fifo_irq, hi_u32 loop,
                                                  hi_pvoid read_buf, hi_u16 increase_step)
{
    hi_u32 i;
    hi_u32 reg_base = spi_dev_ctrl->reg_base;
    hi_u32 read_pos = spi_dev_ctrl->rx_buf.cur_pos;
    if (fifo_irq) {
        for (i = 0; i < loop; i++) {
            *((hi_u8 *)read_buf + read_pos) = (hi_u8)hi_reg_read_val16(reg_base + REG_SPI_DR);
            read_pos += increase_step;
        }
        spi_dev_ctrl->rx_buf.cur_cnt += loop;
    } else {
        for (i = 0; i < loop; i++) {
            if (hi_likely(!spi_check_rx_fifo_empty(reg_base))) {
                *((hi_u8 *)read_buf + read_pos) = (hi_u8)hi_reg_read_val16(reg_base + REG_SPI_DR);
                read_pos += increase_step;
                spi_dev_ctrl->rx_buf.cur_cnt++;
            } else {
                break;
            }
        }
    }
    spi_dev_ctrl->rx_buf.cur_pos = read_pos;
}

static hi_u16 spi_isr_read_fifo(spi_ctrl *spi_dev_ctrl, hi_bool fifo_irq)
{
    hi_pvoid read_buf = spi_dev_ctrl->rx_buf.buf;
    hi_u16 fix_data = SPI_UNUSE_DATA;
    hi_u16 increase_step = 1;
    hi_u32 loop = hi_min(spi_dev_ctrl->single_len, (spi_dev_ctrl->trans_len - spi_dev_ctrl->rx_buf.cur_cnt));
    if (read_buf == HI_NULL) {
        read_buf = &fix_data;
        increase_step = 0;
    }

    if (hi_likely(spi_dev_ctrl->spi_cfg.data_width < HI_SPI_CFG_DATA_WIDTH_E_9BIT)) {
        spi_isr_read_8bits(spi_dev_ctrl, fifo_irq, loop, read_buf, increase_step);
    } else {
        spi_isr_read_16bits(spi_dev_ctrl, fifo_irq, loop, read_buf, increase_step);
    }

    if (spi_dev_ctrl->rx_buf.cur_cnt >= spi_dev_ctrl->trans_len) {
        return SPI_INT_BIT_RX_FIFO_WATER_LINE | SPI_INT_BIT_RX_FIFO_TIME_OUT;
    }
    return 0;
}

static hi_u16 spi_isr_write_fifo(spi_ctrl *spi_dev_ctrl)
{
    hi_pvoid write_buf = spi_dev_ctrl->tx_buf.buf;
    hi_u32 i;
    hi_u16 fix_data = SPI_UNUSE_DATA;
    hi_u16 increase_step = 1;
    hi_u32 reg_base = spi_dev_ctrl->reg_base;
    hi_u32 len = spi_dev_ctrl->single_len;
    hi_u32 write_pos = spi_dev_ctrl->tx_buf.cur_pos;
    if (write_buf == HI_NULL) {
        write_buf = &fix_data;
        increase_step = 0;
    }
    if (hi_likely(spi_dev_ctrl->spi_cfg.data_width < HI_SPI_CFG_DATA_WIDTH_E_9BIT)) {
        for (i = 0; i < len; i++) {
            spi_process_printf("[wreg8][0x%x]", *((hi_u8 *)write_buf + write_pos));
            hi_reg_write16(reg_base + REG_SPI_DR, *((hi_u8 *)write_buf + write_pos));
            write_pos += increase_step;
        }
        spi_dev_ctrl->tx_buf.cur_cnt += len;
    } else {
        for (i = 0; i < len; i++) {
            spi_process_printf("[wreg16][0x%x]", *((hi_u16 *)write_buf + write_pos));
            hi_reg_write16(reg_base + REG_SPI_DR, *((hi_u16 *)write_buf + write_pos));
            write_pos += increase_step;
        }
        spi_dev_ctrl->tx_buf.cur_cnt += len;
    }
    spi_dev_ctrl->tx_buf.cur_pos = write_pos;
    if (spi_dev_ctrl->tx_buf.cur_cnt == spi_dev_ctrl->single_len) {
        spi_dev_ctrl->tx_buf.cur_cnt = 0;
        return SPI_INT_BIT_TX_FIFO_WATER_LINE;
    }
    return 0;
}

hi_void spi_isr(spi_ctrl *spi_dev_ctrl)
{
    if (spi_dev_ctrl == NULL) {
        spi_process_printf("spi_isr para is null \n");
        return;
    }
    hi_u32 reg_base = spi_dev_ctrl->reg_base;
    hi_u16 int_val;
    hi_u32 event_bits = 0;
    hi_u16 dis_int_bis = 0;
    hi_u16 clear_int_bits = 0;
    hi_u32 ret;
    hi_reg_read16(reg_base + REG_SPI_MIS, int_val);
    if (int_val & SPI_INT_BIT_TX_FIFO_WATER_LINE) {
        dis_int_bis |= spi_isr_write_fifo(spi_dev_ctrl);
        event_bits |= HI_EVENT_BIT_TX_DATA;
    }
    if (int_val & SPI_INT_BIT_RX_FIFO_WATER_LINE) {
        dis_int_bis |= spi_isr_read_fifo(spi_dev_ctrl, HI_TRUE);
        event_bits |= HI_EVENT_BIT_RX_DATA;
    }
    if (int_val & SPI_INT_BIT_RX_FIFO_TIME_OUT) {
        dis_int_bis |= spi_isr_read_fifo(spi_dev_ctrl, HI_FALSE);
        event_bits |= HI_EVENT_BIT_RX_DATA;
        clear_int_bits |= SPI_INT_BIT_RTIC;
    }
    if (int_val & SPI_INT_BIT_RX_FIFO_OVER_FLOW) {
        dis_int_bis |= SPI_INT_BIT_RX_FIFO_OVER_FLOW;
        event_bits |= HI_EVENT_BIT_RX_FIFO_OVER_FLOW;
        clear_int_bits |= SPI_INT_BIT_RORIC;
    }
    spi_isr_clear_cr(reg_base, clear_int_bits);
    spi_isr_disable(reg_base, dis_int_bis);
    if (spi_dev_ctrl->disable_later && !spi_check_busy(reg_base)) {
        spi_dev_ctrl->disable_later = HI_FALSE;
    }
    ret = hi_event_send(spi_dev_ctrl->event_id, event_bits);
    if (ret != HI_ERR_SUCCESS) {
        spi_process_printf("spi_isr send sig fail \n");
    }
}

hi_u32 spi_trans_prepare(spi_ctrl *spi_hw_ctrl, spi_trans_attr *trans_attr)
{
    hi_u32 ret = HI_ERR_SUCCESS;
    if ((spi_hw_ctrl == NULL) || (trans_attr == NULL)) {
        return HI_ERR_FAILURE;
    }

    if (trans_attr->trans_opt & SPI_OPT_WAIT_SIGNAL) {
        spi_process_printf("wait_sem\n");
        ret = hi_sem_wait(spi_hw_ctrl->sem_id, trans_attr->time_out_ms);
        if (ret != HI_ERR_SUCCESS) {
            return ret;
        }
        trans_attr->trans_opt |= SPI_OPT_TASKED_SIGNAL;
    }
    spi_hw_ctrl->transferring = HI_TRUE;
    if (spi_hw_ctrl->prepare_func) {
        spi_hw_ctrl->prepare_func();
    }
    if (trans_attr->trans_opt & SPI_OPT_ENABLE_SPI) {
        spi_enable(spi_hw_ctrl);
    }
    return ret;
}

hi_void spi_trans_restore(spi_ctrl *spi_hw_ctrl, const spi_trans_attr *trans_attr)
{
    if ((spi_hw_ctrl == NULL) || (trans_attr == NULL)) {
        return;
    }
    if (spi_hw_ctrl->restore_func) {
        spi_hw_ctrl->restore_func();
    }

    if ((trans_attr->trans_opt & SPI_OPT_TASKED_SIGNAL) && (trans_attr->trans_opt & SPI_OPT_FREE_SIGNAL)) {
        spi_process_printf("free_sem\n");
        hi_u32 ret = hi_sem_signal(spi_hw_ctrl->sem_id);
        if (ret != HI_ERR_SUCCESS) {
            spi_process_printf("free_sem fail\n");
        }
    }
    spi_hw_ctrl->transferring = HI_FALSE;
}

hi_u32 spi_transfer_8bits_block(const spi_ctrl *spi_hw_ctrl, hi_u32 options)
{
    if (spi_hw_ctrl == NULL) {
        return HI_ERR_FAILURE;
    }
    hi_u32 tmp_len, count;
    hi_u16 value;
    hi_u8 *tx = (hi_u8 *)spi_hw_ctrl->tx_buf.buf;
    hi_u8 *rx = (hi_u8 *)spi_hw_ctrl->rx_buf.buf;
    hi_u32 len = spi_hw_ctrl->trans_len;
    hi_u16 fifo_len = (spi_hw_ctrl->reg_base == HI_SSP0_REG_BASE ? SPI0_FIFO_LEN : SPI1_FIFO_LEN);
    hi_bool write_not_fix = ((options & SPI_OPT_SEND_FIX_DATA) == 0);
    hi_bool read_not_fix = ((options & SPI_OPT_RCV_FIX_DATA) == 0);
    hi_u32 ret;
    while (len) {
        if (len > fifo_len) {
            tmp_len = fifo_len;
        } else {
            tmp_len = len;
        }
        len -= tmp_len;
        /* wirte fifo */
        count = tmp_len;
        value = SPI_UNUSE_DATA;
        while (count) {
            if (write_not_fix && tx != HI_NULL) {
                value = *tx++;
            }
            hi_reg_write16(spi_hw_ctrl->reg_base + REG_SPI_DR, value);
            count -= 1;
        }
        ret = spi_check_write_timeout(spi_hw_ctrl->reg_base);
        if (ret != HI_ERR_SUCCESS) {
            return HI_ERR_SPI_WRITE_TIMEOUT;
        }
        /* if host device too fast, there be delay 50-100us */
        /* read fifo */
        count = tmp_len;
        while (count) {
            hi_reg_read16(spi_hw_ctrl->reg_base + REG_SPI_DR, value);
            if (read_not_fix && rx != HI_NULL) {
                *rx++ = (hi_u8)value;
            }
            count -= 1;
        }
    }
    return HI_ERR_SUCCESS;
}

/*
 * spi_txrx16: send and receive 16bit data
 */
hi_u32 spi_transfer_16bits_block(const spi_ctrl *spi_hw_ctrl, hi_u32 options)
{
    if (spi_hw_ctrl == NULL) {
        return HI_ERR_FAILURE;
    }
    hi_u32 len = spi_hw_ctrl->trans_len;
    hi_u32 tmp_len;
    hi_u32 count;
    hi_u16 *tx = (hi_u16 *)spi_hw_ctrl->tx_buf.buf;
    hi_u16 *rx = (hi_u16 *)spi_hw_ctrl->rx_buf.buf;
    hi_u16 value;
    hi_u16 fifo_len = (spi_hw_ctrl->reg_base == HI_SSP0_REG_BASE ? SPI0_FIFO_LEN : SPI1_FIFO_LEN);
    hi_bool write_not_fix = ((options & SPI_OPT_SEND_FIX_DATA) == 0);
    hi_bool read_not_fix = ((options & SPI_OPT_RCV_FIX_DATA) == 0);
    hi_u32 ret;
    while (len) {
        if (len > fifo_len) {
            tmp_len = fifo_len;
        } else {
            tmp_len = len;
        }
        len -= tmp_len;
        /* wirte fifo */
        count = tmp_len;
        value = SPI_UNUSE_DATA;
        while (count) {
            if (write_not_fix && tx != HI_NULL) {
                value = *tx++;
            }
            hi_reg_write16(spi_hw_ctrl->reg_base + REG_SPI_DR, value);
            count--;
        }
        ret = spi_check_write_timeout(spi_hw_ctrl->reg_base);
        if (ret != HI_ERR_SUCCESS) {
            return HI_ERR_SPI_WRITE_TIMEOUT;
        }
        /* if host device too fast, there be delay 50-100us */
        count = tmp_len;
        while (count) {
            hi_reg_read16(spi_hw_ctrl->reg_base + REG_SPI_DR, value);
            if (read_not_fix && rx != HI_NULL) {
                *rx++ = value;
            }
            count--;
        }
    }
    return HI_ERR_SUCCESS;
}
