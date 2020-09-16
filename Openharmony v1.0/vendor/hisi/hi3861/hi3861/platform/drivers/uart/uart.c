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

static uart_driver_data_t g_uart_0 = {
    .num = UART0,
    .phys_base = HI_UART0_REG_BASE,
    .irq_num = UART_0_IRQ,
    .rx_transfer = HI_NULL,
    .tx_transfer = HI_NULL,
    .rx_recv = uart_write_circ_buf,
    .tx_send = uart_read_circ_buf,
    .count = 0,
    .state = UART_STATE_NOT_OPENED,
    .receive_tx_int = HI_FALSE,
    .ops = &g_uart_driver_uops,
    .tx_use_int = HI_FALSE,
    .attr = UART_ATTR_DEFAULT,
    .act = UART_ACT_DEFAULT,
};

static uart_driver_data_t g_uart_1 = {
    .num = UART1,
    .phys_base = HI_UART1_REG_BASE,
    .irq_num = UART_1_IRQ,
    .rx_transfer = HI_NULL,
    .tx_transfer = HI_NULL,
    .rx_recv = uart_write_circ_buf,
    .tx_send = uart_read_circ_buf,
    .count = 0,
    .state = UART_STATE_NOT_OPENED,
    .receive_tx_int = HI_FALSE,
    .ops = &g_uart_driver_uops,
    .tx_use_int = HI_FALSE,
    .attr = UART_ATTR_DEFAULT,
    .act = UART_ACT_DEFAULT,
};

static uart_driver_data_t g_uart_2 = {
    .num = UART2,
    .phys_base = HI_UART2_REG_BASE,
    .irq_num = UART_2_IRQ,
    .rx_transfer = HI_NULL,
    .tx_transfer = HI_NULL,
    .rx_recv = uart_write_circ_buf,
    .tx_send = uart_read_circ_buf,
    .count = 0,
    .state = UART_STATE_NOT_OPENED,
    .receive_tx_int = HI_FALSE,
    .ops = &g_uart_driver_uops,
    .tx_use_int = HI_FALSE,
    .attr = UART_ATTR_DEFAULT,
    .act = UART_ACT_DEFAULT,
};

uart_driver_data_t *g_udd_g[UART_NUM] = { &g_uart_0, &g_uart_1, &g_uart_2 };

uart_driver_data_t *uart_open(hi_u32 uart_index, uart_mode mode)
{
    hi_u32 ret;
    uart_driver_data_t *udd = HI_NULL;

    if (uart_index >= UART_NUM || mode != UART_232) {
        return HI_NULL;
    }

    udd = (uart_driver_data_t *) g_udd_g[uart_index];

    if (udd->state == UART_STATE_NOT_OPENED) {
        ret = uart_init_circ_buf(udd, udd->act.tx_buffer_size, udd->act.rx_buffer_size);
        if (ret != HI_ERR_SUCCESS) {
            uart_set_errno(UART_ERR_INIT_CIRC_FAILED);
            return HI_NULL;
        }
        ret = hi_event_create(&udd->event_id);
        if (ret != HI_ERR_SUCCESS) {
            uart_deinit_circ_buf(udd);
            return HI_NULL;
        }
        udd->type = mode;

        if (!udd->ops->startup || udd->ops->startup(udd)) {
            uart_deinit_circ_buf(udd);
            hi_event_delete(udd->event_id);
            uart_set_errno(UART_ERR_START_FAILED);
            return HI_NULL;
        }
        udd->state = UART_STATE_USEABLE;
    } else {
        if (mode != udd->type) {
            if (udd->ops->startup != HI_NULL) {
                udd->type = mode;
                udd->ops->startup(udd);
            }
        }
    }

    return udd;
}


hi_s32 uart_read(uart_driver_data_t *udd, hi_char *buf, hi_u32 count)
{
    hi_s32 len;
    hi_u32 event_val = 0;

    if (udd == HI_NULL) {
        return (hi_s32)HI_ERR_FAILURE;
    }
    if ((buf == HI_NULL) || (count == 0)) {
        uart_set_errno(UART_ERR_PARA_INVALID);
        return (hi_s32)HI_ERR_FAILURE;
    }
    if (udd->state != UART_STATE_USEABLE) {
        uart_set_errno(UART_ERR_NOT_OPENED);
        return (hi_s32)HI_ERR_FAILURE;
    }

    do {
        len = uart_read_circ_buf(udd->rx_transfer, buf, count);
#ifdef UART_DEBUG_INFO
        udd->uart_stat_info.read_circ_cnt += (unsigned int) len;
#endif
        if ((len == 0) && (udd->act.rx_block == UART_FLG_RD_BLOCK)) {
            hi_event_wait(udd->event_id, UART_RD_EVENT | UART_RD_QUIT_EVENT, &event_val,
                          HI_SYS_WAIT_FOREVER, HI_EVENT_WAITMODE_OR | HI_EVENT_WAITMODE_CLR);
            if (event_val == UART_RD_QUIT_EVENT) {
                break;
            }
        } else {
            break;
        }
    } while (len == 0);

    return len;
}

hi_s32 uart_write(uart_driver_data_t *udd, const hi_char *buf, hi_u32 send_count)
{
    hi_s32 len = 0;
    hi_s32 count = (hi_s32)send_count;
    hi_u32 left;
    hi_u32 event_val = 0;
    /* if uart is not in useable, report error */
    if (udd == HI_NULL) {
        return (hi_s32)HI_ERR_FAILURE;
    }

    if ((buf == HI_NULL) || (count == 0)) {
        uart_set_errno(UART_ERR_PARA_INVALID);
        return (hi_s32)HI_ERR_FAILURE;
    }
    left = (hi_u32)count;
    if (udd->state != UART_STATE_USEABLE) {
        uart_set_errno(UART_ERR_NOT_OPENED);
        return (hi_s32)HI_ERR_FAILURE;
    }

    if (udd->receive_tx_int == HI_TRUE) {
        do {
            len += uart_write_circ_buf(udd->tx_transfer, (hi_char *)&buf[len], left);
            if (len >= count) {
                break;
            }
            left = (hi_u32)count - (hi_u32)len;
            if (udd->act.tx_block != UART_FLG_WD_BLOCK) {
                break;
            }
            uart_tx_interrupt_enable(udd);
            (void) hi_event_wait(udd->event_id, UART_WD_EVENT, &event_val,
                                 HI_SYS_WAIT_FOREVER, HI_EVENT_WAITMODE_OR | HI_EVENT_WAITMODE_CLR);
        } while (left > 0);
        uart_tx_interrupt_enable(udd);
    } else {
        uart_tx_interrupt_enable(udd);
        if (udd->ops != HI_NULL &&
            udd->ops->start_tx) {
            len = udd->ops->start_tx(udd, buf, (hi_u32)count);
        }
    }

#ifdef UART_DEBUG_INFO
    udd->uart_stat_info.write_circ_cnt += (unsigned int) len;
#endif

    return len;
}

hi_s32 uart_write_immediately(uart_driver_data_t *udd, const hi_char *buf, hi_u32 send_count)
{
    hi_s32 len = 0;
    hi_s32 count = (hi_s32)send_count;

    /* if uart is not in useable, report error */
    if (udd == HI_NULL) {
        return (hi_s32)HI_ERR_FAILURE;
    }

    if ((buf == HI_NULL) || (count == 0)) {
        uart_set_errno(UART_ERR_PARA_INVALID);
        return (hi_s32)HI_ERR_FAILURE;
    }

    if (udd->state != UART_STATE_USEABLE) {
        uart_set_errno(UART_ERR_NOT_OPENED);
        return (hi_s32)HI_ERR_FAILURE;
    }

    if (udd->ops->start_tx) {
        len = udd->ops->start_tx(udd, buf, (hi_u32)count);
    }

#ifdef UART_DEBUG_INFO
    udd->uart_stat_info.write_circ_cnt += (unsigned int) len;
#endif

    return len;
}

hi_bool uart_check_ioctrl_param(const uart_attr_t *attr)
{
    if (attr == HI_NULL) {
        return HI_FALSE;
    }

    if (attr->baud_rate > 0
        && attr->data_bits <= 8 && attr->data_bits >= 5   /* bits>=5 bits<=8 */
        && (attr->parity == 0 || attr->parity == 1 || attr->parity == 2)  /* stop_bits：1 2 */
        && (attr->stop_bits == 1 || attr->stop_bits == 2) /* stop_bits：1 2 */
        && attr->tx_fifo_line <= 4 && attr->rx_fifo_line <= 4 && attr->flow_fifo_line <= 4) { /* 4 */
        return HI_TRUE;
    }

    return HI_FALSE;
}

hi_u32 uart_ioctl(uart_driver_data_t *udd, hi_u32 cmd, uintptr_t arg)
{
    hi_u32 ret = HI_ERR_SUCCESS;
    uart_attr_t *attr = HI_NULL;

    if (udd == HI_NULL) {
        return HI_ERR_UART_INVALID_PARAMETER;
    }

    if (udd->state != UART_STATE_USEABLE) {
        uart_set_errno(UART_ERR_NOT_OPENED);
        return HI_ERR_FAILURE;
    }

    switch (cmd) {
        case UART_CFG_SET_ATTR:
            attr = (uart_attr_t *) arg;
            if (uart_check_ioctrl_param(attr) == HI_TRUE) {
                if (memcpy_s(&udd->attr, sizeof(uart_attr_t), attr, sizeof(uart_attr_t)) != EOK) {
                    return HI_ERR_FAILURE;
                }
                if (udd->ops->ioctl && udd->ops->ioctl(udd)) {
                    uart_set_errno(UART_ERR_IOCTL_FAILED);
                    ret = HI_ERR_FAILURE;
                }
            } else {
                uart_set_errno(UART_ERR_PARA_INVALID);
                ret = HI_ERR_FAILURE;
            }
            break;
        case UART_CFG_GET_ATTR:
            attr = (uart_attr_t *) arg;
            if (memcpy_s(attr, sizeof(uart_attr_t), &udd->attr, sizeof(uart_attr_t)) != EOK) {
                return HI_ERR_FAILURE;
            }
            break;
        case UART_CFG_GET_BUF_EMPTY: {
            hi_u32 *is_empty = (hi_u32 *) arg;
            *is_empty = uart_buf_empty(udd);
            break;
        }
        default:
            uart_set_errno(UART_ERR_PARA_INVALID);
            ret = HI_ERR_FAILURE;
            break;
    }

    return ret;
}

hi_u32 uart_close(uart_driver_data_t *udd)
{
    if (udd == HI_NULL) {
        return HI_ERR_UART_INVALID_PARAMETER;
    }
    if (udd->state != UART_STATE_USEABLE) {
        return HI_ERR_SUCCESS;
    }
    if (udd->ops != HI_NULL && udd->ops->shutdown) {
        udd->ops->shutdown(udd);
    }

    uart_deinit_circ_buf(udd);
    udd->state = UART_STATE_NOT_OPENED;

    if (udd->receive_tx_int != HI_FALSE) {
        udd->receive_tx_int = HI_FALSE;
    }
    if (udd->count != 0) {
        udd->count = 0;
    }

    udd->attr = (uart_attr_t) UART_ATTR_DEFAULT;
    udd->act = (uart_act_t) UART_ACT_DEFAULT;

    if (hi_event_delete(udd->event_id) != HI_ERR_SUCCESS) {
        return HI_ERR_FAILURE;
    }
    return HI_ERR_SUCCESS;
}
