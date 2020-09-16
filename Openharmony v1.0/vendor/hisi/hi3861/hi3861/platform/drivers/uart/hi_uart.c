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

#include "hi_uart.h"

#include <hi_lowpower.h>
#include <hi_stdlib.h>
#ifdef CONFIG_UART_DMA_SUPPORT
#include <hi_dma.h>
#endif

#include "hi_early_debug.h"
#include "uart.h"
#include "uart_drv.h"

#define UART_FR_BUSY (1 << 3)
#define UART_FR_TXFE (1 << 7)
#define UART_FR_RXFE (1 << 4)
#define WAIT_TIME 10000         /* wait 10 seconds */
#define CLKEN_UART2 6
#define CLKEN_UART2_BUS 9
#define OFFSET_14_BITS      14
#define UART_DR                     0x0
#define UART_FR                     0x18
#define UART_IBRD                   0x24
#define UART_FBRD                   0x28
#define UART_LCR_H                  0x2C
#define UART_CR                     0x30
#define UART_IFLS                   0x34
#define UART_IMSC                   0x38
#define UART_DMACR                  0x48
#define UART_DMA_DISABLE            0X04
#define UARTCR_CFG                  0x301     /* UART tx enable, rx enable, uart enable */

#ifndef UART_FR
#define UART_FR 0x18
#endif

typedef struct {
    hi_u16 ibrd;
    hi_u16 fbrd;
    hi_u16 lcr_h;
    hi_u16 cr;
    hi_u16 ifls;
} uart_regs;

uart_regs g_uart_regs_save[UART_NUM] = {0};

hi_u32 g_uart_timer_handle[UART_NUM] = {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF};
volatile hi_bool g_uart_timeout[UART_NUM] = {0};

static void init_uart_param(uart_attr_t *uart_attr, const hi_uart_attribute *attr)
{
    uart_attr->baud_rate = attr->baud_rate;
    uart_attr->data_bits = attr->data_bits;
    uart_attr->stop_bits = attr->stop_bits;
    uart_attr->parity = attr->parity;
    uart_attr->pad = attr->pad;
}

static hi_u32 get_uart_param(const uart_driver_data_t *udd, hi_uart_attribute *attr, hi_uart_extra_attr *extra_attr)
{
    if (udd == HI_NULL) {
        return HI_ERR_UART_INVALID_PARAMETER;
    }

    if (udd->state != UART_STATE_USEABLE) {
        uart_set_errno(UART_ERR_NOT_OPENED);
        return HI_ERR_FAILURE;
    }

    if (extra_attr != HI_NULL) {
        extra_attr->tx_fifo_line = (hi_uart_fifo_line)(udd->attr.tx_fifo_line + 1);
        extra_attr->rx_fifo_line = (hi_uart_fifo_line)(udd->attr.rx_fifo_line + 1);
        extra_attr->flow_fifo_line = (hi_uart_fifo_line)(udd->attr.flow_fifo_line + 1);

        extra_attr->tx_block = (hi_uart_block_state)udd->act.tx_block;
        extra_attr->rx_block = (hi_uart_block_state)udd->act.rx_block;
        extra_attr->tx_buf_size = udd->act.tx_buffer_size;
        extra_attr->rx_buf_size = udd->act.rx_buffer_size;
        extra_attr->tx_use_dma = (hi_uart_dma_state)udd->act.tx_use_dma;
        extra_attr->rx_use_dma = (hi_uart_dma_state)udd->act.rx_use_dma;
    }

    attr->baud_rate = udd->attr.baud_rate;
    attr->data_bits = udd->attr.data_bits;
    attr->stop_bits = udd->attr.stop_bits;
    attr->parity = udd->attr.parity;
    attr->pad = udd->attr.pad;

    return HI_ERR_SUCCESS;
}

BSP_RAM_TEXT_SECTION hi_u32 hi_uart_is_busy(hi_uart_idx id, hi_bool *busy)
{
    hi_u32 port_num = (hi_u32) id;
    uart_driver_data_t *udd = HI_NULL;
    hi_u32 val;
    if (port_num >= UART_NUM || busy == HI_NULL) {
        return HI_ERR_UART_INVALID_PARAMETER;
    }
    udd = g_udd_g[port_num];
    hi_reg_read32(udd->phys_base + UART_FR, val);
    if (val & UART_FR_BUSY) {
        *busy = HI_TRUE;
    } else {
        *busy = HI_FALSE;
    }
    return HI_ERR_SUCCESS;
}

BSP_RAM_TEXT_SECTION hi_u32 hi_uart_is_buf_empty(hi_uart_idx id, hi_bool *empty)
{
    hi_u32 port_num = (hi_u32) id;
    uart_driver_data_t *udd = HI_NULL;
    hi_u32 val;
    hi_u32 ret;
    if (port_num >= UART_NUM || empty == HI_NULL) {
        return HI_ERR_UART_INVALID_PARAMETER;
    }
    udd = g_udd_g[port_num];
    hi_reg_read32(udd->phys_base + UART_FR, val);
    if (((val & UART_FR_RXFE) == 0) || ((val & UART_FR_TXFE) == 0)) {
        *empty = HI_FALSE;
        return HI_ERR_SUCCESS;
    }
    ret = uart_ioctl(udd, UART_CFG_GET_BUF_EMPTY, (hi_u32)(uintptr_t)&val);
    if ((val == 0) && (ret == HI_ERR_SUCCESS)) {
        *empty = HI_FALSE;
    } else {
        *empty = HI_TRUE;
    }
    return ret;
}

hi_bool uart_check_extra_param(const hi_uart_extra_attr *extra_attr)
{
    if (extra_attr->tx_fifo_line <= HI_FIFO_LINE_SEVEN_EIGHTS &&
        extra_attr->rx_fifo_line <= HI_FIFO_LINE_SEVEN_EIGHTS &&
        extra_attr->flow_fifo_line <= HI_FIFO_LINE_SEVEN_EIGHTS &&
        extra_attr->tx_block <= HI_UART_BLOCK_STATE_BLOCK &&
        extra_attr->rx_block <= HI_UART_BLOCK_STATE_BLOCK &&
        extra_attr->tx_use_dma <= HI_UART_USE_DMA &&
        extra_attr->rx_use_dma <= HI_UART_USE_DMA) {
        return HI_TRUE;
    }

    return HI_FALSE;
}

hi_u32 init_uart_extra_param(hi_u32 port_num, const hi_uart_extra_attr *extra_attr)
{
    uart_driver_data_t *udd = HI_NULL;

    udd = g_udd_g[port_num];

    if (udd == HI_NULL || uart_check_extra_param(extra_attr) != HI_TRUE) {
        return HI_ERR_UART_INVALID_PARAMETER;
    }

    if (udd->state != UART_STATE_NOT_OPENED) {
        uart_set_errno(UART_ERR_NOT_IDLE);
        return HI_ERR_FAILURE;
    }

    if (extra_attr->tx_fifo_line != 0) {
        udd->attr.tx_fifo_line = (hi_u8)(extra_attr->tx_fifo_line) - 1;
    }
    if (extra_attr->rx_fifo_line != 0) {
        udd->attr.rx_fifo_line = (hi_u8)(extra_attr->rx_fifo_line) - 1;
    }
    if (extra_attr->flow_fifo_line != 0) {
        udd->attr.flow_fifo_line = (hi_u8)(extra_attr->flow_fifo_line) - 1;
    }
    if (extra_attr->tx_block != 0) {
        udd->act.tx_block = extra_attr->tx_block;
    }
    if (extra_attr->rx_block != 0) {
        udd->act.rx_block = extra_attr->rx_block;
    }
    if (extra_attr->tx_buf_size != 0) {
        udd->act.tx_buffer_size = extra_attr->tx_buf_size;
    }
    if (extra_attr->rx_buf_size != 0) {
        udd->act.rx_buffer_size = extra_attr->rx_buf_size;
    }
    if (extra_attr->tx_use_dma == UART_TX_USE_DMA) {
#ifdef CONFIG_UART_DMA_SUPPORT
        udd->act.tx_use_dma = extra_attr->tx_use_dma;
#else
        return HI_ERR_UART_NOT_SUPPORT_DMA;
#endif
    }
    if (extra_attr->rx_use_dma == UART_RX_USE_DMA) {
#ifdef CONFIG_UART_DMA_SUPPORT
        udd->act.rx_use_dma = extra_attr->rx_use_dma;
#else
        return HI_ERR_UART_NOT_SUPPORT_DMA;
#endif
    }
    return HI_ERR_SUCCESS;
}

hi_u32 uart_attribute_ioctl(uart_driver_data_t *udd, const hi_uart_attribute *attr)
{
    if (udd == HI_NULL) {
        return HI_ERR_UART_INVALID_PARAMETER;
    }
    uart_attr_t uart_attr = { 0 };

    if (memcpy_s(&uart_attr, sizeof(uart_attr_t), &udd->attr, sizeof(uart_attr_t)) != EOK) {
        return HI_ERR_FAILURE;
    }
    init_uart_param(&uart_attr, attr);

    return uart_ioctl(udd, UART_CFG_SET_ATTR, (uintptr_t)&uart_attr);
}

hi_u32 hi_uart_init(hi_uart_idx id, const hi_uart_attribute *param, const hi_uart_extra_attr *extra_attr)
{
    hi_u32 port_num = (hi_u32) id;
    uart_driver_data_t *udd = HI_NULL;

    if (port_num >= UART_NUM || param == HI_NULL) {
        return HI_ERR_UART_INVALID_PARAMETER;
    }

    if (extra_attr != HI_NULL) {
        hi_u32 ret = init_uart_extra_param(port_num, extra_attr);
        if (ret != HI_ERR_SUCCESS) {
            return ret;
        }
    }
    if (id == HI_UART_IDX_2) {
        hi_u16 reg_val;
        hi_reg_read16(W_CTL_UART_MAC80M_CLKEN_REG, reg_val);
        reg_val |= (1 << CLKEN_UART2) | (1 << CLKEN_UART2_BUS);
        hi_reg_write16(W_CTL_UART_MAC80M_CLKEN_REG, reg_val); /* enable uart2 clk */
    }
    udd = uart_open(port_num, UART_232);
    if (udd == HI_NULL) {
        return HI_ERR_FAILURE;
    }

#ifdef CONFIG_UART_DMA_SUPPORT
    if (extra_attr != HI_NULL && (extra_attr->tx_use_dma == HI_TRUE || extra_attr->rx_use_dma == HI_TRUE)) {
        if (hi_dma_is_init() == HI_FALSE) {
            hi_u32 ret = hi_dma_init();
            if (ret != HI_ERR_SUCCESS) {
                return ret;
            }
        }
    }
#endif

    if (g_uart_timer_handle[id] == 0xFFFFFFFF) {
        hi_u32 ret = hi_timer_create(&(g_uart_timer_handle[id]));
        if (ret != HI_ERR_SUCCESS) {
            return ret;
        }
    }

    return uart_attribute_ioctl(udd, param);
}

hi_u32 hi_uart_set_flow_ctrl(hi_uart_idx id, hi_flow_ctrl flow_ctrl)
{
    hi_u32 port_num = (hi_u32) id;
    uart_driver_data_t *udd = HI_NULL;
    uart_attr_t uart_attr = { 0 };

    if (port_num >= UART_NUM || flow_ctrl > HI_FLOW_CTRL_CTS_ONLY) {
        return HI_ERR_UART_INVALID_PARAMETER;
    }

    udd = g_udd_g[port_num];
    if (memcpy_s(&uart_attr, sizeof(uart_attr_t), &udd->attr, sizeof(uart_attr_t)) != EOK) {
        return HI_ERR_FAILURE;
    }
    uart_attr.flow_ctrl = (hi_u8) flow_ctrl;

    return uart_ioctl(udd, UART_CFG_SET_ATTR, (uintptr_t)&uart_attr);
}

hi_s32 hi_uart_read(hi_uart_idx id, hi_u8 *data, hi_u32 data_len)
{
    hi_u32 port_num = (hi_u32) id;
    hi_s32 num;

    if (port_num >= UART_NUM) {
        return (hi_s32)HI_ERR_FAILURE;
    }

    num = uart_read(g_udd_g[port_num], (hi_char *) data, data_len);
    return num;
}

hi_void uart_read_timeout_func(hi_u32 uart_id)
{
    g_uart_timeout[uart_id] = HI_TRUE;
    hi_u32 ret = hi_uart_quit_read(uart_id);
    if (ret != HI_ERR_SUCCESS) {
        printf("uart:%d quit fail:0x%x\r\n", uart_id, ret);
    }
}

hi_s32 hi_uart_read_timeout(hi_uart_idx id, hi_u8 *data, hi_u32 len, hi_u32 timeout_ms)
{
    hi_s32 need_read_len = len;

    g_uart_timeout[id] = HI_FALSE;
    hi_u32 ret = hi_timer_start(g_uart_timer_handle[id], HI_TIMER_TYPE_ONCE, timeout_ms,
        uart_read_timeout_func, id);
    if (ret != HI_ERR_SUCCESS) {
        return ret;
    }

    while ((need_read_len > 0) && (g_uart_timeout[id] == HI_FALSE)) {
        hi_s32 read_len = hi_uart_read(id, data, need_read_len);
        if (read_len == -1) {
            (hi_void)hi_timer_stop(g_uart_timer_handle[id]);
            return HI_ERR_FAILURE;
        }
        data += read_len;
        need_read_len -= read_len;
    }

    if (g_uart_timeout[id] == HI_FALSE) {
        (hi_void)hi_timer_stop(g_uart_timer_handle[id]);
    }

    return (len - need_read_len);
}

hi_s32 hi_uart_write(hi_uart_idx id, const hi_u8 *data, hi_u32 data_len)
{
    hi_u32 port_num = (hi_u32) id;
    uart_driver_data_t *udd = HI_NULL;

    if (port_num >= UART_NUM) {
        return (hi_s32)HI_ERR_FAILURE;
    }

    udd = g_udd_g[port_num];
    if (udd->tx_use_int != HI_TRUE) {
        udd->tx_use_int = HI_TRUE;
    }

    return uart_write(udd, (hi_char *) data, data_len);
}

hi_s32 hi_uart_write_immediately(hi_uart_idx id, const hi_u8 *data, hi_u32 data_len)
{
    hi_u32 port_num = (hi_u32) id;
    uart_driver_data_t *udd = HI_NULL;

    if (port_num >= UART_NUM) {
        return (hi_s32)HI_ERR_FAILURE;
    }

    udd = g_udd_g[port_num];
    if (udd->tx_use_int != HI_FALSE) {
        udd->tx_use_int = HI_FALSE;
    }

    return uart_write_immediately(udd, (hi_char *) data, data_len);
}

hi_u32 hi_uart_deinit(hi_uart_idx id)
{
    hi_u32 port_num = (hi_u32) id;
    hi_u32 ret;
    if (port_num >= UART_NUM) {
        return HI_ERR_UART_INVALID_PARAMETER;
    }

    ret = uart_close(g_udd_g[port_num]);
    if (ret != HI_ERR_SUCCESS) {
        return ret;
    }

    if (id == HI_UART_IDX_2) {
        hi_u16 reg_val;
        hi_reg_read16(W_CTL_UART_MAC80M_CLKEN_REG, reg_val);
        reg_val &= ~((1 << CLKEN_UART2) | (1 << CLKEN_UART2_BUS));
        hi_reg_write16(W_CTL_UART_MAC80M_CLKEN_REG, reg_val); /* disable uart2 clk */
    }

    if (g_uart_timer_handle[id] != 0xFFFFFFFF) {
        ret = hi_timer_delete(g_uart_timer_handle[id]);
        if (ret != HI_ERR_SUCCESS) {
            return ret;
        }
        g_uart_timer_handle[id] = 0xFFFFFFFF;
    }

    return ret;
}

hi_u32 hi_uart_get_attribute(hi_uart_idx id, hi_uart_attribute *attr, hi_uart_extra_attr *extra_attr)
{
    hi_u32 port_num = (hi_u32) id;

    if (port_num >= UART_NUM || attr == HI_NULL) {
        return HI_ERR_UART_INVALID_PARAMETER;
    }

    return get_uart_param(g_udd_g[port_num], attr, extra_attr);
}

hi_u32 hi_uart_quit_read(hi_uart_idx id)
{
    hi_u32 port_num = (hi_u32) id;
    if (port_num >= UART_NUM) {
        return HI_ERR_UART_INVALID_PARAMETER;
    }

    uart_driver_data_t *udd = (uart_driver_data_t *) g_udd_g[id];
    if (udd->act.rx_block != UART_FLG_RD_BLOCK) {
        return HI_ERR_UART_NOT_BLOCK_MODE;
    }

    if (hi_event_send(udd->event_id, UART_RD_QUIT_EVENT) != HI_ERR_SUCCESS) {
        return HI_ERR_FAILURE;
    }

    return HI_ERR_SUCCESS;
}

hi_u32 hi_uart_lp_save(hi_uart_idx id)
{
    hi_u32 port_num = (hi_u32) id;
    if (port_num >= UART_NUM) {
        return HI_ERR_UART_INVALID_PARAMETER;
    }
    uart_driver_data_t *udd = HI_NULL;
    udd = (uart_driver_data_t *) g_udd_g[port_num];
    g_uart_regs_save[port_num].ibrd = hi_reg_read_val16(udd->phys_base + UART_IBRD);
    g_uart_regs_save[port_num].fbrd = hi_reg_read_val16(udd->phys_base + UART_FBRD);
    g_uart_regs_save[port_num].lcr_h = hi_reg_read_val16(udd->phys_base + UART_LCR_H);
    g_uart_regs_save[port_num].cr = hi_reg_read_val16(udd->phys_base + UART_CR);
    g_uart_regs_save[port_num].ifls = hi_reg_read_val16(udd->phys_base + UART_IFLS);
    return HI_ERR_SUCCESS;
}

hi_u32 hi_uart_lp_restore(hi_uart_idx id)
{
    hi_u32 port_num = (hi_u32) id;
    if (port_num >= UART_NUM) {
        return HI_ERR_UART_INVALID_PARAMETER;
    }
    hi_u32 phys_base = ((uart_driver_data_t *) g_udd_g[port_num])->phys_base;
    hi_u16 temp;
    if (id == HI_UART_IDX_2) {
        hi_reg_read16(W_CTL_UART_MAC80M_CLKEN_REG, temp);
        temp |= (1 << CLKEN_UART2) | (1 << CLKEN_UART2_BUS);
        hi_reg_write16(W_CTL_UART_MAC80M_CLKEN_REG, temp); /* enable uart2 clk */
    }
    /* wait until tx fifo is null, in order to let data send before reset work normal. */
    while ((hi_reg_read_val16(phys_base + UART_FR) & 0x08) == 0x08) { }
     /* disable uart tx rx and uart */
    hi_reg_write16((phys_base + UART_CR), 0);
    /* flush fifo */
    hi_reg_write16((phys_base + UART_LCR_H), 0);
    /* set baudrate */
    hi_reg_write16((phys_base + UART_IBRD), g_uart_regs_save[port_num].ibrd);
    hi_reg_write16((phys_base + UART_FBRD), g_uart_regs_save[port_num].fbrd);
    /* set databit stopbit parity */
    hi_reg_write16((phys_base + UART_LCR_H), g_uart_regs_save[port_num].lcr_h);
    /* set fifo line */
    hi_reg_write16(phys_base + UART_IFLS, g_uart_regs_save[port_num].ifls);  /* default val: 0x10A */
    /* disable the transmit DMA */
    hi_reg_write16((phys_base + UART_DMACR), UART_DMA_DISABLE);
    /* set flow ctrl */
    if (phys_base != HI_UART0_REG_BASE) {
        temp = hi_reg_read_val16(phys_base + UART_CR);
        temp &= ~(0x3 << OFFSET_14_BITS);
        temp |= g_uart_regs_save[port_num].cr & (0x3 << OFFSET_14_BITS);
        hi_reg_write16(phys_base + UART_CR, temp); /* 14 15 bit */
    }
    /* enable uart tx rx and uart */
    temp = hi_reg_read_val16(phys_base + UART_CR);
    temp |= UARTCR_CFG;
    hi_reg_write16((phys_base + UART_CR), temp);
    temp = hi_reg_read_val16(phys_base + UART_IMSC);
    hi_reg_write16(phys_base + UART_IMSC, UART_RX_INT_ENABLE | temp);
    return HI_ERR_SUCCESS;
}
