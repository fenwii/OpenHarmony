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

#include "uart.h"
#include "uart_drv.h"
#include "hi_isr.h"
#include "serial_dw.h"
#include "dma.h"

#define hi_uart_buf_lock(x) hi_int_lock()
#define hi_uart_buf_unlock(x, val) hi_int_restore(val)
hi_bool g_uart_buf_memcpy_failed = HI_FALSE;

hi_u32 uart_circ_buf_empty(const uart_circ_buf *transfer)
{
    if (transfer->flags & BUF_CIRCLED) {
        return 0;
    }

    if (transfer->wp == transfer->rp) {
        return 1;
    } else {
        return 0;
    }
}

hi_u32 uart_init_circ_buf(uart_driver_data_t *udd, unsigned int rx_buf_size, unsigned int tx_buf_size)
{
    if ((!rx_buf_size) || (!tx_buf_size)) {
        return HI_ERR_UART_INVALID_PARAMETER;
    }

    udd->rx_transfer = (uart_circ_buf *) hi_malloc(HI_MOD_ID_UART, sizeof(uart_circ_buf));
    if (udd->rx_transfer == NULL) {
        goto end;
    }

    memset_s((hi_void *) udd->rx_transfer, sizeof(uart_circ_buf), 0, sizeof(uart_circ_buf));
    udd->rx_transfer->data = (char *) hi_malloc(HI_MOD_ID_UART, rx_buf_size);
    if (udd->rx_transfer->data == NULL) {
        goto free_rx_transfer;
    }

    udd->rx_transfer->size = rx_buf_size;
    udd->tx_transfer = (uart_circ_buf *) hi_malloc(HI_MOD_ID_UART, sizeof(uart_circ_buf));
    if (udd->tx_transfer == NULL) {
        goto free_rx_circ_buf;
    }

    memset_s((hi_void *) udd->tx_transfer, sizeof(uart_circ_buf), 0, sizeof(uart_circ_buf));
    udd->tx_transfer->data = (char *) hi_malloc(HI_MOD_ID_UART, tx_buf_size);
    if (udd->tx_transfer->data == NULL) {
        goto free_tx_circ_buf;
    }

    udd->tx_transfer->size = tx_buf_size;
    return HI_ERR_SUCCESS;

  free_tx_circ_buf:
    hi_free(HI_MOD_ID_UART, udd->tx_transfer);
    udd->tx_transfer = HI_NULL;

  free_rx_circ_buf:
    hi_free(HI_MOD_ID_UART, udd->rx_transfer->data);
    udd->rx_transfer->data = HI_NULL;
  free_rx_transfer:
    hi_free(HI_MOD_ID_UART, udd->rx_transfer->data);
    udd->rx_transfer = HI_NULL;
  end:
    return HI_ERR_FAILURE;
}

hi_void uart_deinit_circ_buf(uart_driver_data_t *udd)
{
    if (udd->rx_transfer != HI_NULL) {
        if (udd->rx_transfer->data != HI_NULL) {
            hi_free(HI_MOD_ID_UART, udd->rx_transfer->data);
            udd->rx_transfer->data = HI_NULL;
        }

        hi_free(HI_MOD_ID_UART, udd->rx_transfer);
        udd->rx_transfer = HI_NULL;
    }

    if (udd->tx_transfer != HI_NULL) {
        if (udd->tx_transfer->data != HI_NULL) {
            hi_free(HI_MOD_ID_UART, udd->tx_transfer->data);
            udd->tx_transfer->data = HI_NULL;
        }
        hi_free(HI_MOD_ID_UART, udd->tx_transfer);
        udd->tx_transfer = HI_NULL;
    }
}

hi_s32 uart_read_circ_buf(uart_circ_buf *transfer, hi_char *buf, hi_u32 count)
{
    uintptr_t data;

    if (transfer == NULL) {
        return (hi_s32) HI_ERR_FAILURE;
    }

    hi_u32 last_int_val = hi_uart_buf_lock(transfer);
    hi_u32 wp = transfer->wp;
    hi_u32 rp = transfer->rp;
    hi_u32 flags = transfer->flags;
    hi_uart_buf_unlock(transfer, last_int_val);
    data = (uintptr_t) transfer->data;
    hi_u32 buf_size = transfer->size;
    if (!(flags & BUF_CIRCLED)) {
        if (count >= (wp - rp)) {
            count = wp - rp;
        }

        if (memcpy_s(buf, count, (hi_void *) (uintptr_t)(data + rp), count) != EOK) {
            g_uart_buf_memcpy_failed = HI_TRUE;
        }
        transfer->rp += count;
        return (hi_s32) count;
    }
    if (count < (buf_size - rp)) {
        if (memcpy_s(buf, count, (hi_void *) (uintptr_t)(data + rp), count) != EOK) {
            g_uart_buf_memcpy_failed = HI_TRUE;
        }
        transfer->rp += count;
        return (hi_s32) count;
    }
    hi_u32 copy_size = buf_size - rp;
    hi_u32 left_size = count - copy_size;
    if (memcpy_s(buf, copy_size, (hi_void *) (uintptr_t)(data + rp), copy_size) != EOK) {
        g_uart_buf_memcpy_failed = HI_TRUE;
    }
    rp = 0;
    if (left_size > wp) {
        left_size = wp;
    }

    if (memcpy_s((hi_void*)(buf + copy_size), left_size, (hi_void *)(uintptr_t)(data + rp), left_size) != EOK) {
        g_uart_buf_memcpy_failed = HI_TRUE;
    }
    last_int_val = hi_uart_buf_lock(transfer);
    transfer->rp = left_size;
    transfer->flags &= ~BUF_CIRCLED;
    hi_uart_buf_unlock(transfer, last_int_val);
    return (hi_s32) (copy_size + left_size);
}

hi_s32 uart_write_circ_buf(uart_circ_buf *transfer, const hi_char *buf, hi_u32 count)
{
    uintptr_t data;

    if (transfer == NULL) {
        return (hi_s32) HI_ERR_FAILURE;
    }

    hi_u32 last_int_val = hi_uart_buf_lock(transfer);
    hi_u32 wp = transfer->wp;
    hi_u32 rp = transfer->rp;
    hi_u32 flags = transfer->flags;
    hi_uart_buf_unlock(transfer, last_int_val);

    data = (uintptr_t) transfer->data;
    hi_u32 buf_size = transfer->size;

    if (!(flags & BUF_CIRCLED)) {
        if (count < (buf_size - wp)) {
            if (memcpy_s((hi_void *)(uintptr_t) (data + wp), count, buf, count) != EOK) {
                g_uart_buf_memcpy_failed = HI_TRUE;
            }
            transfer->wp += count;
            return (hi_s32) count;
        }
        hi_u32 copy_size = buf_size - wp;
        hi_u32 left_size = count - copy_size;
        if (memcpy_s((hi_void *)(uintptr_t) (data + wp), copy_size, buf, copy_size) != EOK) {
            g_uart_buf_memcpy_failed = HI_TRUE;
        }
        wp = 0;
        if (left_size > rp) {
            /* overflowed. some new data will be discarded */
            left_size = rp;
        }

        if (memcpy_s((hi_void*)(uintptr_t)(data + wp), left_size, (hi_void *)(buf + copy_size), left_size) != EOK) {
            g_uart_buf_memcpy_failed = HI_TRUE;
        }
        last_int_val = hi_uart_buf_lock(transfer);
        transfer->wp = left_size;
        transfer->flags |= BUF_CIRCLED;
        hi_uart_buf_unlock(transfer, last_int_val);
        return (hi_s32) (copy_size + left_size);
    }
    if (count > (rp - wp)) {
        /* overflowed. some new data will be discarded */
        count = rp - wp;
    }

    if (memcpy_s((hi_void *)(uintptr_t) (data + wp), count, buf, count) != EOK) {
        g_uart_buf_memcpy_failed = HI_TRUE;
    }
    transfer->wp += count;
    return (hi_s32) count;
}

hi_void uart_tx_interrupt_disable(uart_driver_data_t *udd)
{
    udd->receive_tx_int = HI_FALSE; /* when disable tx interrupt, set receive_tx_int false */
    hi_u32 tx_status = hi_reg_read_val32(udd->phys_base + UART_IMSC);
    hi_reg_write32(udd->phys_base + UART_IMSC, (~UART_TX_INT_BIT) & tx_status);
}

hi_void uart_tx_interrupt_enable(const uart_driver_data_t *udd)
{
    hi_u32 tx_status = hi_reg_read_val32(udd->phys_base + UART_IMSC);
    hi_reg_write32(udd->phys_base + UART_IMSC, (unsigned short) (UART_TX_INT_BIT | tx_status));
}

hi_void uart_tx_interrupt_clear(const uart_driver_data_t *udd)
{
    hi_u32 int_clear_status = hi_reg_read_val32(udd->phys_base + UART_ICR);
    hi_reg_write32(udd->phys_base + UART_ICR, (unsigned short) (UART_TX_INT_BIT | int_clear_status));
}

hi_void uart_rx_interrupt_disable(const uart_driver_data_t *udd)
{
    hi_u32 tx_status = hi_reg_read_val32(udd->phys_base + UART_IMSC);
    hi_reg_write32(udd->phys_base + UART_IMSC, ~(UART_RX_INT_ENABLE) & tx_status);
}

hi_void uart_rx_interrupt_enable(const uart_driver_data_t *udd)
{
    hi_u32 tx_status = hi_reg_read_val32(udd->phys_base + UART_IMSC);
    hi_reg_write32(udd->phys_base + UART_IMSC, UART_RX_INT_ENABLE | tx_status);
}

hi_void get_recv_irq_err(unsigned int int_status, uart_drv_stat_info *pst_uart_stat_info)
{
    if (int_status & UART_INTMASK_OVERRUN) {
        (pst_uart_stat_info->recv_irq_err_overrun)++;
    }

    if (int_status & UART_INTMASK_PARERR) {
        (pst_uart_stat_info->recv_irq_err_parity)++;
    }

    if (int_status & UART_INTMASK_FRAMINGERR) {
        (pst_uart_stat_info->recv_irq_err_frame)++;
    }

    if (int_status & UART_INTMASK_BREAKERR) {
        (pst_uart_stat_info->recv_irq_err_break)++;
    }
}

HI_ALWAYS_STAIC_INLINE hi_u32 uart_get_tx_fifo_available_cnt(const uart_driver_data_t *udd)
{
    hi_u32 tx_fifo_line = udd->attr.tx_fifo_line;
    hi_u32 tx_fifo_used_cnt;
    switch (tx_fifo_line) {
        case 0:                     /* 0 */
            tx_fifo_used_cnt = 8;   /* algorithm: UART_FIFO_TX_SIZE / 8; */
            break;
        case 1:                     /* 1 */
            tx_fifo_used_cnt = 16;  /* algorithm: UART_FIFO_TX_SIZE / 4; 16  */
            break;
        case 2:                     /* 2 */
            tx_fifo_used_cnt = 32;  /* algorithm: UART_FIFO_TX_SIZE / 2; 32 */
            break;
        case 3:                     /* 3 */
            tx_fifo_used_cnt = 48;  /* algorithm: UART_FIFO_TX_SIZE / 4 * 3; 48 */
            break;
        case 4:                     /* 4 */
            tx_fifo_used_cnt = 56;  /* algorithm: UART_FIFO_TX_SIZE / 8 * 7; 56 */
            break;
        default:
            tx_fifo_used_cnt = 32;  /* algorithm: UART_FIFO_TX_SIZE / 2; 32 */
        break;
    }
    return (UART_FIFO_TX_SIZE - tx_fifo_used_cnt);
}

HI_ALWAYS_STAIC_INLINE hi_u32 uart_get_rx_fifo_cnt(const uart_driver_data_t *udd)
{
    hi_u32 rx_fifo_line = udd->attr.rx_fifo_line;
    hi_u32 rx_fifo_cnt;
    switch (rx_fifo_line) {
        case 0:                     /* 0 */
            rx_fifo_cnt = 8;        /* algorithm: UART_FIFO_TX_SIZE / 8 -> 8 */
            break;
        case 1:                     /* 1 */
            rx_fifo_cnt = 16;       /* algorithm: UART_FIFO_TX_SIZE / 4 -> 16 */
            break;
        case 2:                     /* 2 */
            rx_fifo_cnt = 32;       /* algorithm: UART_FIFO_TX_SIZE / 2 -> 32 */
            break;
        case 3:                     /* 3 */
            rx_fifo_cnt = 48;       /* algorithm: UART_FIFO_TX_SIZE / 4 * 3 -> 48 */
            break;
        case 4:                     /* 4 */
            rx_fifo_cnt = 56;       /* algorithm: UART_FIFO_TX_SIZE / 8 * 7 -> 56 */
            break;
        default:
            rx_fifo_cnt = 32;       /* algorithm: UART_FIFO_TX_SIZE / 2 -> 32 */
            break;
    }
    return rx_fifo_cnt;
}

HI_ALWAYS_STAIC_INLINE hi_u32 uart_get_tx_fifo_dma_cnt(hi_u32 tx_fifo_available_cnt)
{
    if (tx_fifo_available_cnt <= 32) {  /* algorithm: UART_FIFO_TX_SIZE / 2 = 32 */
        return tx_fifo_available_cnt;
    } else {
        return 32;    /* algorithm: UART_FIFO_TX_SIZE / 2 = 32 */
    }
}

HI_ALWAYS_STAIC_INLINE hi_u32 uart_get_rx_fifo_dma_cnt(hi_u32 rx_fifo_cnt)
{
    if (rx_fifo_cnt <= 32) {    /* algorithm: UART_FIFO_TX_SIZE / 2 = 32 */
        return rx_fifo_cnt;
    } else {
        return 32;    /* algorithm: UART_FIFO_TX_SIZE / 2 = 32 */
    }
}

HI_ALWAYS_STAIC_INLINE hi_dma_burst_size uart_get_burst_size_e(hi_u32 burst_size)
{
    if (burst_size == 8) {          /* burst_size为8 */
        return DMA_BURST_MSIZE_8;
    } else if (burst_size == 16) {  /* burst_size为16 */
        return DMA_BURST_MSIZE_16;
    } else if (burst_size == 32) {  /* burst_size为32 */
        return DMA_BURST_MSIZE_32;
    } else {
        return DMA_BURST_MSIZE_1;
    }
}

#ifdef CONFIG_UART_DMA_SUPPORT
static hi_void uart_dma_para_cfg(const uart_driver_data_t *udd, hi_dma_para *dma_para, const hi_char *buf)
{
    hi_u32 rx_fifo_dma_cnt = uart_get_rx_fifo_dma_cnt(uart_get_rx_fifo_cnt(udd));
    hi_dma_burst_size burst_size_e = uart_get_burst_size_e(rx_fifo_dma_cnt);

    dma_para->tr_type = DMA_PHL_TO_MEM;
    if (udd->phys_base == UART0_BASE) {
        dma_para->src_phl = UART0_RX;
    } else if (udd->phys_base == UART1_BASE) {
        dma_para->src_phl = UART1_RX;
    } else {
        dma_para->src_phl = UART2_RX;
    }
    dma_para->dst_phl = 0;
    dma_para->src_addr = udd->phys_base;
    dma_para->dst_addr = (uintptr_t) buf;
    dma_para->src_burst_size = burst_size_e;
    dma_para->dst_burst_size = burst_size_e;
    dma_para->src_width = WIDTH_BIT8;
    dma_para->dst_width = WIDTH_BIT8;
    dma_para->transfer_size = rx_fifo_dma_cnt;
    dma_para->cb = HI_NULL;

    uart_error("rx dma start, rx_fifo_dma_cnt:%d\r\n", rx_fifo_dma_cnt);
}

static hi_u32 uart_dma_recv_irq(uart_driver_data_t *udd, hi_u32 status, hi_char *buf)
{
    hi_u32 ret;
    hi_dma_para dma_para;
    hi_u32 rx_fifo_dma_cnt;

    uart_error("enter rx dma");
#ifdef CONFIG_UART_DEBUG_INFO
    uart_drv_stat_info *pst_uart_stat_info = &(udd->uart_stat_info);
    get_recv_irq_err(status, pst_uart_stat_info);
#else
    unused_param(status);
#endif

    /* if uart hardware rx fifo is empty, go out of circle */
    hi_u32 usr = hi_reg_read_val32(udd->phys_base + UART_FR);
    if ((usr & UARTFR_RXFE_MASK) == UARTFR_RXFE_MASK) {
#ifdef CONFIG_UART_DEBUG_INFO
        (udd->uart_stat_info.recv_irq_err_emptyfifo_cnt)++;
#endif
        return HI_ERR_FAILURE;
    }

    rx_fifo_dma_cnt = uart_get_rx_fifo_dma_cnt(uart_get_rx_fifo_cnt(udd));
    uart_dma_para_cfg(udd, &dma_para, buf);

    ret = hi_dma_transfer(&dma_para, HI_TRUE);
    uart_error("rx dma end, rx_fifo_dma_cnt:%d\r\n", rx_fifo_dma_cnt);
    if (ret == HI_ERR_SUCCESS) {
        udd->rx_recv(udd->rx_transfer, buf, rx_fifo_dma_cnt);
#ifdef CONFIG_UART_DEBUG_INFO
        for (hi_u32 i = 0; i < rx_fifo_dma_cnt; i++) {
            udd->uart_stat_info.recv_last_context.data[udd->uart_stat_info.recv_last_context.num] = buf[i];
            udd->uart_stat_info.recv_last_context.num++;
            udd->uart_stat_info.recv_last_context.num &= (HI_UART_LAST_RECORD_BYTE_COUNT - 1);
        }
#endif
    } else {
#ifdef CONFIG_UART_DEBUG_INFO
        udd->uart_stat_info.recv_dma_err_cnt++;
#endif
    }
    if (udd->act.rx_block == UART_FLG_RD_BLOCK) {
        hi_event_send(udd->event_id, UART_RD_EVENT);
    }
#ifdef CONFIG_UART_DEBUG_INFO
    udd->uart_stat_info.recv_irq_cnt++;
    udd->uart_stat_info.recv_irq_data_cnt += rx_fifo_dma_cnt;
#endif
    return HI_ERR_SUCCESS;
}
#endif

static hi_void uart_nodma_recv_irq(uart_driver_data_t *udd, hi_u32 status, hi_char *buf)
{
    hi_u32 count = 0;
    uart_error("enter rx not dma");

#ifdef CONFIG_UART_DEBUG_INFO
    uart_drv_stat_info *pst_uart_stat_info = &(udd->uart_stat_info);
    get_recv_irq_err(status, pst_uart_stat_info);
#else
    unused_param(status);
#endif
    do {
        hi_u32 usr = hi_reg_read_val32(udd->phys_base + UART_FR);
        /* if uart hardware rx fifo is empty, go out of circle */
        if ((usr & UARTFR_RXFE_MASK) == UARTFR_RXFE_MASK) {
#ifdef CONFIG_UART_DEBUG_INFO
            if (!count) {
                (udd->uart_stat_info.recv_irq_err_emptyfifo_cnt)++;
            }
#endif
            break;
        }

        if (buf == HI_NULL) {
            break;
        }
        buf[count] = (char) hi_reg_read_val32(udd->phys_base + UART_DR);
#ifdef CONFIG_UART_DEBUG_INFO
        udd->uart_stat_info.recv_last_context.data[udd->uart_stat_info.recv_last_context.num] =
            (unsigned char) buf[count];
        udd->uart_stat_info.recv_last_context.num++;
        udd->uart_stat_info.recv_last_context.num &= (HI_UART_LAST_RECORD_BYTE_COUNT - 1);
#endif
        count++;
    } while (count < 64);   /* 64 */

    if (count >= 1 && udd->rx_recv != HI_NULL) {
        udd->rx_recv(udd->rx_transfer, buf, count);
        if (udd->act.rx_block == UART_FLG_RD_BLOCK) {
            hi_event_send(udd->event_id, UART_RD_EVENT);
        }
    }
#ifdef CONFIG_UART_DEBUG_INFO
    udd->uart_stat_info.recv_irq_cnt++;
    udd->uart_stat_info.recv_irq_data_cnt += count;
#endif
}

static hi_void uart_send_irq(uart_driver_data_t *udd, hi_char *buf)
{
#ifdef CONFIG_UART_DEBUG_INFO
    udd->uart_stat_info.send_irq_cnt++;
#endif

    if (udd->receive_tx_int == HI_FALSE) {
        udd->receive_tx_int = HI_TRUE;
        return;
    }

    if (uart_circ_buf_empty(udd->tx_transfer)) {
        uart_tx_interrupt_disable(udd);
    } else {
        hi_u32 count = (unsigned int) udd->tx_send(udd->tx_transfer, buf, uart_get_tx_fifo_available_cnt(udd));
        if (udd->ops->start_tx) {
            (void) udd->ops->start_tx(udd, buf, count);
        }
        if (udd->act.tx_block == UART_FLG_WD_BLOCK) {
            (void) hi_event_send(udd->event_id, UART_WD_EVENT);
        }
    }
}

static hi_void uart_drv_irq(void *data)
{
    hi_u32 status;
    hi_char buf[64] = { 0 };  /* size 64 */
    uart_driver_data_t *udd = (uart_driver_data_t *) data;
    char *buff = buf;
    if (udd == NULL) {
        return;
    }
    status = hi_reg_read_val32(udd->phys_base + UART_MIS);
#ifdef CONFIG_UART_DMA_SUPPORT
    /* recv irq */
    if ((UART_INTMASK_RX & status) && (udd->act.rx_use_dma == UART_RX_USE_DMA)) {
        if (uart_dma_recv_irq(udd, status, buff) != HI_ERR_SUCCESS) {
            /* send irq */
            if (UART_INTMASK_TX & status) {
                uart_send_irq(udd, buff);
            }
            return;
        }
    } else if ((UART_INTMASK_RX & status) || (UART_INTMASK_RECTIMEOUT & status)) {
        uart_nodma_recv_irq(udd, status, buff);
    }
#else
    if ((UART_INTMASK_RX & status) || (UART_INTMASK_RECTIMEOUT & status)) {
        uart_nodma_recv_irq(udd, status, buff);
    }
#endif

    /* send irq */
    if (UART_INTMASK_TX & status) {
        uart_send_irq(udd, buff);
    }
}

hi_u32 uart_buf_empty(const uart_driver_data_t *udd)
{
    if ((uart_circ_buf_empty(udd->tx_transfer)) &&
        (uart_circ_buf_empty(udd->rx_transfer))) {
        return 1;
    }
    return 0;
}

static hi_u32 uart_drv_set_attr(uart_driver_data_t *udd)
{
    hi_u32 ret;
    hi_u32 int_save;
    uart_param_stru uart_param;
    if (memset_s(&uart_param, sizeof(uart_param_stru), 0, sizeof(uart_param_stru)) != EOK) {
        return HI_ERR_MEMSET_S;
    }
    uart_param.baudrate = udd->attr.baud_rate;
    uart_param.databit = udd->attr.data_bits;
    uart_param.stopbit = udd->attr.stop_bits;
    uart_param.parity = udd->attr.parity;
    uart_param.flow_ctrl = udd->attr.flow_ctrl;
    uart_param.fifoline_tx_int = udd->attr.tx_fifo_line;
    uart_param.fifoline_rx_int = udd->attr.rx_fifo_line;
    uart_param.fifoline_rts = udd->attr.flow_fifo_line;

    int_save = hi_int_lock();
    ret = set_uart_param(udd->phys_base, uart_param);
    (hi_void) hi_int_restore(int_save);

    udd->receive_tx_int = HI_FALSE; /* when reset uart module, set receive_tx_int false */

    return ret;
}

static hi_u32 uart_drv_startup(uart_driver_data_t *udd)
{
    hi_u32 ret;

    /* disable interrupt */
    hi_reg_write32(udd->phys_base + UART_IMSC, 0);

    /* set baudrate,data_bit,stop_bit,parity */
    if (uart_drv_set_attr(udd) != HI_ERR_SUCCESS) {
        return HI_ERR_FAILURE;
    }

    /* creat interrupt function for uart */
    ret = hi_irq_request(udd->irq_num, HI_IRQ_FLAG_PRI3, (irq_routine) uart_drv_irq, (uintptr_t) udd);
    if (ret == HI_ERR_SUCCESS || ret == HI_ERR_ISR_ALREADY_CREATED) {
        ret = HI_ERR_SUCCESS;
        uart_rx_interrupt_enable(udd);
    }

    return ret;
}

static hi_void uart_drv_shutdown(struct uart_driver_data *udd)
{
    uart_tx_interrupt_disable(udd);
    uart_rx_interrupt_disable(udd);
    hi_irq_disable((hi_u32) udd->irq_num);
    if (hi_irq_free(udd->irq_num) != HI_ERR_SUCCESS) {
        uart_error("uart irq free fail");
    }
}

#ifdef CONFIG_UART_DMA_SUPPORT
hi_u32 uart_drv_dma_start_tx_cfg(struct uart_driver_data *udd, const hi_char *buf, hi_u32 count)
{
    hi_u32 send_cnt = 0;
    hi_u32 tx_fifo_available_cnt = uart_get_tx_fifo_available_cnt(udd);
    hi_u32 dma_busrt_size = uart_get_tx_fifo_dma_cnt(tx_fifo_available_cnt);
    hi_dma_burst_size burst_size_e = uart_get_burst_size_e(dma_busrt_size);
    hi_u32 ret;
    hi_dma_para dma_para;

    dma_para.tr_type = DMA_MEM_TO_PHL;
    dma_para.src_phl = 0;
    if (udd->phys_base == UART0_BASE) {
        dma_para.dst_phl = UART0_TX;
    } else if (udd->phys_base == UART1_BASE) {
        dma_para.dst_phl = UART1_TX;
    } else {
        dma_para.dst_phl = UART2_TX;
    }

    dma_para.src_addr = (uintptr_t) buf;
    dma_para.dst_addr = udd->phys_base;
    dma_para.src_burst_size = burst_size_e;
    dma_para.dst_burst_size = burst_size_e;
    dma_para.src_width = WIDTH_BIT8;
    dma_para.dst_width = WIDTH_BIT8;
    dma_para.transfer_size = dma_busrt_size;
    dma_para.cb = HI_NULL;
    send_cnt += dma_busrt_size;
    uart_error("tx dma start, dma_busrt_size:%d\r\n", dma_busrt_size);
    ret = hi_dma_transfer(&dma_para, HI_TRUE);
    uart_error("tx dma end, dma_busrt_size:%d\r\n", dma_busrt_size);
    if (ret != HI_ERR_SUCCESS) {
#ifdef CONFIG_UART_DEBUG_INFO
    udd->uart_stat_info.send_dma_err_cnt++;
#endif
        return (hi_u32)ret;
    }

    for (; send_cnt < count; send_cnt++) {
        /* Wait until there is space in the FIFO */
        while ((hi_reg_read_val32(udd->phys_base + UART_FR) & UARTFR_TXFF_MASK) != 0) { }
        hi_reg_write32(udd->phys_base + UART_DR, (unsigned) (hi_u8) buf[send_cnt]);
    }
    return HI_ERR_SUCCESS;
}

hi_u32 uart_drv_dma_start_tx(struct uart_driver_data *udd, const hi_char *buf, hi_u32 count)
{
    hi_u32 tx_fifo_available_cnt = uart_get_tx_fifo_available_cnt(udd);
    hi_u32 dma_busrt_size = uart_get_tx_fifo_dma_cnt(tx_fifo_available_cnt);
    if (count >= dma_busrt_size) {
        hi_u32 ret = uart_drv_dma_start_tx_cfg(udd, buf, count);
        if (ret != HI_ERR_SUCCESS) {
#ifdef CONFIG_UART_DEBUG_INFO
            udd->uart_stat_info.send_dma_err_cnt++;
#endif
            return (hi_s32)ret;
        }
    } else {
        for (hi_u32 i = 0; i < count; i++) {
            /* Wait until there is space in the FIFO */
            while ((hi_reg_read_val32(udd->phys_base + UART_FR) & UARTFR_TXFF_MASK) != 0) { }
            hi_reg_write32(udd->phys_base + UART_DR, (unsigned) (hi_u8) buf[i]);
        }
    }

#ifdef CONFIG_UART_DEBUG_INFO
    hi_u32 idx;
    for (idx = 0; idx < count; idx++) {
        udd->uart_stat_info.send_last_context.data[udd->uart_stat_info.send_last_context.num] = buf[idx];
        udd->uart_stat_info.send_last_context.num++;
        udd->uart_stat_info.send_last_context.num &= (HI_UART_LAST_RECORD_BYTE_COUNT - 1);
    }
#endif

#ifdef CONFIG_UART_DEBUG_INFO
    udd->uart_stat_info.send_irq_data_cnt += count;
#endif
    return count;
}
#endif

static hi_u32 uart_drv_irq_start_tx(struct uart_driver_data *udd, const hi_char *buf, hi_u32 count)
{
    hi_u32 tx_fifo_available_cnt = 0;
    hi_u32 send_cnt = count > tx_fifo_available_cnt ? tx_fifo_available_cnt : count;
    hi_u32 idx = 0;

    while (idx < send_cnt) {
        hi_reg_write32(udd->phys_base + UART_DR, (unsigned) (hi_u8) buf[idx]);
#ifdef CONFIG_UART_DEBUG_INFO
        udd->uart_stat_info.send_last_context.data[udd->uart_stat_info.send_last_context.num] = buf[idx];
        udd->uart_stat_info.send_last_context.num++;
        udd->uart_stat_info.send_last_context.num &= (HI_UART_LAST_RECORD_BYTE_COUNT - 1);
#endif
        idx++;
    }

    for (; send_cnt < count; send_cnt++) {
        /* Wait until there is space in the FIFO */
        while ((hi_reg_read_val32(udd->phys_base + UART_FR) & UARTFR_TXFF_MASK) != 0) { }
        hi_reg_write32(udd->phys_base + UART_DR, (unsigned) (hi_u8) buf[send_cnt]);
#ifdef CONFIG_UART_DEBUG_INFO
        udd->uart_stat_info.send_last_context.data[udd->uart_stat_info.send_last_context.num] = buf[send_cnt];
        udd->uart_stat_info.send_last_context.num++;
        udd->uart_stat_info.send_last_context.num &= (HI_UART_LAST_RECORD_BYTE_COUNT - 1);
#endif
    }

#ifdef CONFIG_UART_DEBUG_INFO
    udd->uart_stat_info.send_irq_data_cnt += count;
#endif
    return count;
}

static hi_s32 uart_drv_start_tx(struct uart_driver_data *udd, const hi_char *buf, hi_u32 count)
{
    hi_u32 idx = 0;
    hi_u32 ret;

#ifdef CONFIG_UART_DMA_SUPPORT
    if (udd->tx_use_int == HI_TRUE && udd->receive_tx_int == HI_TRUE && udd->act.tx_use_dma == UART_TX_USE_DMA) {
        ret = uart_drv_dma_start_tx(udd, buf, count);
        return (hi_s32)ret;
    } else if (udd->tx_use_int == HI_TRUE && udd->receive_tx_int == HI_TRUE) {
#else
    if (udd->tx_use_int == HI_TRUE && udd->receive_tx_int == HI_TRUE) {
#endif
        ret = uart_drv_irq_start_tx(udd, buf, count);
        return (hi_s32)ret;
    } else {
        while (idx < count) {
            /* Wait until there is space in the FIFO */
            while ((hi_reg_read_val32(udd->phys_base + UART_FR) & UARTFR_TXFF_MASK) != 0) { }
            hi_reg_write32(udd->phys_base + UART_DR, (unsigned) (hi_u8) buf[idx]);
#ifdef CONFIG_UART_DEBUG_INFO
            udd->uart_stat_info.send_last_context.data[udd->uart_stat_info.send_last_context.num] = buf[idx];
            udd->uart_stat_info.send_last_context.num++;
            udd->uart_stat_info.send_last_context.num &= (HI_UART_LAST_RECORD_BYTE_COUNT - 1);
#endif
            idx++;
        }
#ifdef CONFIG_UART_DEBUG_INFO
        udd->uart_stat_info.send_irq_data_cnt += count;
#endif
        return (hi_s32) count;
    }
}

static hi_u32 uart_drv_ioctl(uart_driver_data_t *udd)
{
    hi_u32 ret;
    ret = uart_drv_set_attr(udd);
    uart_rx_interrupt_enable(udd);
    return ret;
}

uart_ops g_uart_driver_uops = {
    .startup = uart_drv_startup,
    .shutdown = uart_drv_shutdown,
    .start_tx = uart_drv_start_tx,
    .ioctl = uart_drv_ioctl,
};
