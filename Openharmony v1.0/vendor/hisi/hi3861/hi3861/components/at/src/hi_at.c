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

#include "hi_at.h"

#include <at.h>
#include <at_cmd.h>
#include <hi_stdlib.h>
#include <hi_watchdog.h>
#include <hi_event.h>
#include <hi_lowpower.h>
#include <hi_timer.h>
#include <hi_cpu.h>
#include <sal_inf.h>

#include "at_hipriv.h"
#include "at_general.h"
#include "at_wifi.h"
#include "at_io.h"
#include "at_lowpower.h"
#include "at_printf.h"
#include "hi_uart.h"
#include "hi_task.h"
#include "serial_dw.h"
#include "securec.h"
#include "unistd.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define CMD_MAX_LEN                 256
#define AT_DEFAULT_UART_TASK_SIZE   0x600
#define AT_DEFAULT_PROC_TASK_SIZE   0xC00 /* 0x800:softap start would fail. */
#define AT_UART_TASK_PRIO           9
#define AT_PROC_TASK_PRIO           10
#define AT_CMD_HEADER               "AT"
#define AT_UART_SLEEP               1000
#define AT_DATA_MAX_LEN             1024

#define RECV_DATA_NORMAL_CHAR       0
#define RECV_DATA_END_CHAR          1
#define RECV_DATA_END_CHAR_REPEAT   2

#define STAT_NOMAL_KEY              0
#define STAT_ESC_KEY                1
#define STAT_MULTI_KEY              2

/* AT连续返回busy次数超过20，则系统软复位 */
/* If the AT returns the busy message for more than 20 times, system soft reboot. */
#define SOFT_REBOOT_MAX_BUSY_CNT    20

hi_u32 g_at_event = 0;
hi_uart_idx g_at_uart_port = HI_UART_IDX_1;
const hi_uart_attribute g_at_uart_cfg  = {115200, 8, 1, 0, 0};
static hi_char g_at_buf[CMD_MAX_LEN];
hi_char *g_at_data = HI_NULL;

hi_at_input_func g_at_input_func  = HI_NULL;
static hi_at_output_func g_at_output_func = HI_NULL;

hi_u16 g_at_uart_task_size = AT_DEFAULT_UART_TASK_SIZE;
hi_u16 g_at_proc_task_size = AT_DEFAULT_PROC_TASK_SIZE;

hi_bool g_at_init = HI_FALSE;
/* AT连续返回busy次数计数 */
/* Busy message count */
hi_u8 g_busy_count = 0;

hi_at_output_func hi_at_get_register_output_func(hi_void)
{
    return g_at_output_func;
}

hi_s32 at_monitor_input_func(hi_u8 *data, hi_u32 data_len)
{
    (hi_void)data;
    (hi_void)data_len;

    return 0;
}

hi_s32 at_monitor_output_func(const hi_u8 *data, hi_u32 data_len)
{
    (hi_void)data;
    (hi_void)data_len;

    return 0;
}

hi_u32 hi_at_register_input_func(hi_at_input_func at_input_func)
{
    hi_u32 ret = HI_ERR_SUCCESS;

    hi_task_lock();
    if (at_input_func != HI_NULL) {
        hi_bool last_uart_input = HI_FALSE;
        if (g_at_input_func == HI_NULL && g_at_uart_port != 0xFF) {
            last_uart_input = HI_TRUE;
        }

        g_at_input_func = at_input_func;

        if (last_uart_input == HI_TRUE) {
            ret = hi_uart_quit_read(g_at_uart_port);
            ret |= hi_uart_deinit(g_at_uart_port);
        }
    } else {
        if (g_at_uart_port == 0xFF) {
            g_at_input_func = at_monitor_input_func;
        } else {
            g_at_input_func = HI_NULL;
            ret = hi_uart_deinit(g_at_uart_port);
            ret |= hi_uart_init(g_at_uart_port, &g_at_uart_cfg, HI_NULL);
        }
    }
    hi_task_unlock();

    return ret;
}

hi_void hi_at_register_output_func(hi_at_output_func at_output_func)
{
    hi_task_lock();
    if (at_output_func != HI_NULL) {
        g_at_output_func = at_output_func;
    } else {
        if (g_at_uart_port == 0xFF) {
            g_at_output_func = at_monitor_output_func;
        } else {
            g_at_output_func = HI_NULL;
        }
    }
    hi_task_unlock();

    return;
}

hi_char* at_get_buf(hi_void)
{
    hi_char *buf = NULL;
    hi_u32 buf_len;

    if (g_at_ctrl.at_state == AT_CMD_PROCESS) {
        buf_len = strlen(g_at_buf) + 1;
        buf = hi_malloc(HI_MOD_ID_APP_AT, buf_len);
        if (buf != NULL) {
            memset_s(buf, buf_len, 0, buf_len);
            if (memcpy_s(buf, buf_len, g_at_buf, strlen(g_at_buf)) != EOK) {
                hi_at_printf("buf copy fail in %s[%d]", __FUNCTION__, __LINE__);
                hi_free(HI_MOD_ID_APP_AT, buf);
                buf = NULL;
            }
        }
    } else if (g_at_ctrl.at_state == AT_DATA_SENDING) {
        buf_len = g_at_ctrl.send_len + 1;
        buf = hi_malloc(HI_MOD_ID_APP_AT, buf_len);
        if (buf != NULL) {
            memset_s(buf, buf_len, 0, buf_len);
            if (memcpy_s(buf, buf_len, g_at_data, g_at_ctrl.send_len) != EOK) {
                hi_at_printf("buf copy fail in %s[%d]", __FUNCTION__, __LINE__);
                hi_free(HI_MOD_ID_APP_AT, buf);
                buf = NULL;
            }
        }
    }
    hi_event_send(g_at_event, 0x1000);
    return buf;
}

static hi_void at_notify(hi_void)
{
    hi_u32 event_bit = 0;
    hi_u32 ret;
    hi_watchdog_feed();
    hi_event_send(g_at_event, 0x111);
    ret = hi_event_wait(g_at_event, 0x1000, &event_bit, HI_SYS_WAIT_FOREVER,
        HI_EVENT_WAITMODE_OR | HI_EVENT_WAITMODE_CLR);
    if (ret == HI_ERR_EVENT_WAIT_TIME_OUT) {
        hi_at_printf("wait event timeout");
    }
}

hi_void at_put_c(hi_char ch)
{
    if (g_at_output_func == HI_NULL) {
        (hi_void)serial_putc_at(ch);
    } else {
        g_at_output_func((const hi_u8*)&ch, 1);
    }
}

hi_u32 at_key_filter(hi_char ch, hi_u32 *index, hi_s32 *key_value)
{
    if (ch == '\b') { /* backspace */
        if (((*index) > 0) && ((*index) < (CMD_MAX_LEN - 1))) {
            g_at_buf[(*index) - 1] = '\0';
            (*index)--;
            at_put_c('\b');
            at_put_c(' ');
            at_put_c('\b');
        }
        return HI_ERR_FAILURE;
    } else if (ch == 0x1b) {
        *key_value = STAT_ESC_KEY;
        return HI_ERR_FAILURE;
    } else if (ch == 0x5b) {
        if (*key_value == STAT_ESC_KEY) {
            *key_value = STAT_MULTI_KEY;
            return HI_ERR_FAILURE;
        }
    } else if (ch == 0x41) { /* up */
        if (*key_value == STAT_MULTI_KEY) {
            *key_value = STAT_NOMAL_KEY;
            return HI_ERR_FAILURE;
        }
    } else if (ch == 0x42) { /* down */
        if (*key_value == STAT_MULTI_KEY) {
            *key_value = STAT_NOMAL_KEY;
            return HI_ERR_FAILURE;
        }
    } else if ((ch == 0x43) || (ch == 0x44)) { /* right */
        if (*key_value == STAT_MULTI_KEY) {
            *key_value = STAT_NOMAL_KEY;
            return HI_ERR_FAILURE;
        }
    }

    return HI_ERR_SUCCESS;
}


hi_void at_cmd_print_back(hi_u32 i, hi_char ch)
{
    if (i < (CMD_MAX_LEN - 1)) {
        g_at_buf[i] = ch;
    } else {
        g_at_buf[CMD_MAX_LEN - 1] = '\0';
    }

    at_put_c(ch);
}

hi_void at_cmd_line_parse(hi_char c)
{
    hi_char ch = c;
    static hi_u32 i = 0;
    static hi_s32 key_value = 0;
    static hi_u32 enter_flag = 0;

    if ((i == 0) && (ch != '\n')) {
        (hi_void)memset_s(g_at_buf, CMD_MAX_LEN, 0, CMD_MAX_LEN);
    }

    if (ch == '\n') {
        if (i == 0) {
            hi_at_printf("\r\nERROR\r\n");
            g_at_ctrl.at_state = AT_IDLE;
            return;
        }

        if (enter_flag == (i - 1)) {
            i = 0;
            g_at_ctrl.at_state = AT_CMD_PROCESS;
            at_notify();
        }
        return;
    }

    enter_flag = 0;

    if (ch == '\r') {
        if (i == 0) {
            hi_at_printf("\r\nERROR\r\n");
            g_at_ctrl.at_state = AT_IDLE;
            return;
        }
        if (i < (CMD_MAX_LEN - 1)) {
            g_at_buf[i] = '\0';
        }
        enter_flag = i;
        i++;
        return;
    }

    if (at_key_filter(ch, &i, &key_value) != HI_ERR_SUCCESS) {
        return;
    }

    if (ch != '\n') {
        at_cmd_print_back(i, ch);
        i++;
    }

    key_value = STAT_NOMAL_KEY;
}

hi_void at_get_send_data(hi_char c)
{
    static hi_u16 i = 0;

    g_at_data[i] = c;
    if ((g_at_ctrl.is_recv_end_char_flag == RECV_DATA_END_CHAR_REPEAT) && (c == '0')) {
        g_at_data[i - 2] = g_at_data[i - 1]; /* 2:delete '\' */
        g_at_data[i - 1] = g_at_data[i];
        i -= 1;
    }
    if ((i >= (g_at_ctrl.send_len - 1)) || (i >= (AT_DATA_MAX_LEN - 1)) ||
        ((g_at_ctrl.is_recv_end_char_flag == RECV_DATA_END_CHAR) && (c == '0'))) {
        g_at_ctrl.at_state = AT_DATA_SENDING;
        g_at_ctrl.is_first_recv_data = HI_TRUE;
        g_at_ctrl.send_len = i + 1;
        if ((g_at_ctrl.is_recv_end_char_flag == RECV_DATA_END_CHAR) && c == '0') {
            g_at_ctrl.is_recv_end_char_flag = RECV_DATA_NORMAL_CHAR;
            g_at_ctrl.send_len = i - 1;
        }

        i = 0;
        at_notify();
        hi_free(HI_MOD_ID_APP_AT, g_at_data);
        g_at_data = HI_NULL;
    } else {
        if (c == '\\') {
            if (g_at_ctrl.is_recv_end_char_flag == RECV_DATA_NORMAL_CHAR) {
                g_at_ctrl.is_recv_end_char_flag = RECV_DATA_END_CHAR;
            } else if (g_at_ctrl.is_recv_end_char_flag == RECV_DATA_END_CHAR) {
                g_at_ctrl.is_recv_end_char_flag = RECV_DATA_END_CHAR_REPEAT;
            }
        } else {
            g_at_ctrl.is_recv_end_char_flag = RECV_DATA_NORMAL_CHAR;
        }
        i++;
    }
}

hi_u32 at_data_recving(hi_void)
{
    if (g_at_ctrl.is_first_recv_data) {
        g_at_data = hi_malloc(HI_MOD_ID_APP_AT, AT_DATA_MAX_LEN);
        if (g_at_data == HI_NULL) {
            printf("Malloc fail!\r\n");
            return HI_ERR_FAILURE;
        }
        memset_s(g_at_data, AT_DATA_MAX_LEN, 0, AT_DATA_MAX_LEN);
        g_at_ctrl.is_first_recv_data = HI_FALSE;
    }
    return HI_ERR_SUCCESS;
}

hi_u32 g_at_uart_timer_handle;
volatile hi_bool g_at_have_uart_data;
hi_bool g_at_check_empty = HI_TRUE;

#define AT_WAIT_TIME 10000         /* wait 10 seconds */

static hi_void timer_handle(hi_u32 data)
{
    hi_unref_param(data);
    g_at_have_uart_data = HI_FALSE;
}

hi_void hi_at_set_check_uart_busy(hi_bool enable)
{
    g_at_check_empty = enable;
}

BSP_RAM_TEXT_SECTION hi_u32 lp_at_uart_vote(hi_void)
{
    hi_bool val;

    if (g_at_check_empty) {
        if (g_at_have_uart_data) {
            return HI_NO_SLEEP;
        }
        hi_u32 ret = hi_uart_is_busy(g_at_uart_port, &val);
        if ((ret == HI_ERR_SUCCESS) && (val == HI_TRUE)) {
            return HI_NO_SLEEP;
        }
        val = HI_FALSE;
        ret = hi_uart_is_buf_empty(g_at_uart_port, &val);
        if (ret == HI_ERR_SUCCESS && val == HI_FALSE) {
            return HI_NO_SLEEP;
        }
    }
    return HI_DEEP_SLEEP;
}

hi_void at_parse_uart_char(hi_char ch)
{
    switch (g_at_ctrl.at_state) {
        case AT_IDLE:
            g_busy_count = 0;
            at_cmd_line_parse(ch);
            break;
        case AT_CMD_PROCESS:
            hi_cpup_load_check_proc(hi_task_get_current_id(), LOAD_SLEEP_TIME_DEFAULT);

            if (ch == '\n') {
                if (g_busy_count >= SOFT_REBOOT_MAX_BUSY_CNT) {
                    g_busy_count = 0;
                    hi_soft_reboot(HI_SYS_REBOOT_CAUSE_AT_BUSY);
                }
                hi_at_printf("busy!\r\n");
                g_busy_count++;
            }
            break;
        case AT_DATA_RECVING:
            g_busy_count = 0;
            if (at_data_recving() != HI_ERR_SUCCESS) {
                break;
            }
            at_get_send_data(ch);
            break;
        case AT_DATA_SENDING:
            hi_cpup_load_check_proc(hi_task_get_current_id(), LOAD_SLEEP_TIME_DEFAULT);
            if (g_at_ctrl.is_first_over_data) {
                g_at_ctrl.is_first_over_data = HI_FALSE;
                hi_at_printf("busy!\r\n");
            }
            break;
        case AT_TRANSPARENT:
            hi_at_printf("==TBD==\r\n");
            break;
        default:
            break;
    }
}

hi_void *at_uart_task_body(hi_void* param)
{
    hi_unref_param(param);
    hi_char ch;
    hi_s32 n;
    for (;;) {
        if (g_at_input_func == NULL) {
            n = hi_uart_read(g_at_uart_port, (hi_u8 *)&ch, 1);
        } else {
            n = g_at_input_func((UINT8 *)&ch, 1);
        }
        if (n != 1) {
            (hi_void)hi_sleep(AT_UART_SLEEP);
            continue;
        }
        if ((hi_lpc_get_type() != HI_NO_SLEEP) && (g_at_check_empty == HI_TRUE)) {
            g_at_have_uart_data = HI_TRUE;
            hi_timer_start(g_at_uart_timer_handle, HI_TIMER_TYPE_ONCE, AT_WAIT_TIME, timer_handle, 0);
        }

        at_parse_uart_char(ch);
    }
}

hi_void at_cmd_execute(hi_char *buf)
{
    hi_u32 ret;
    if (memcmp(buf, AT_CMD_HEADER, strlen(AT_CMD_HEADER)) == EOK) {
        hi_char *at_buf = buf + strlen(AT_CMD_HEADER);

        ret = at_cmd_process(at_buf);
        if ((ret != HI_ERR_SUCCESS) && (ret != HI_ERR_RECVING)) {
            g_at_ctrl.at_state = AT_IDLE;
        }
    } else {
        AT_ENTER;
        AT_RESPONSE_ERROR;
        g_at_ctrl.at_state = AT_IDLE;
    }
}

hi_void *at_proc_task_body(hi_void* param)
{
    hi_unref_param(param);
    hi_u32 ret;
    hi_u32 event_bit;
    hi_char   *buf = NULL;
    for (;;) {
        if (g_at_ctrl.at_state != AT_DATA_RECVING) {
            hi_at_printf("\r\n");
        }
        event_bit = 0;
        ret = hi_event_wait(g_at_event, 0xFFF, &event_bit, HI_SYS_WAIT_FOREVER,
            HI_EVENT_WAITMODE_OR | HI_EVENT_WAITMODE_CLR);
        if (ret == HI_ERR_EVENT_WAIT_TIME_OUT) {
            hi_at_printf("get event timeout\r\n");
            continue;
        }
        if (event_bit == 0x111) {
            buf = at_get_buf();
            if (buf == NULL) {
                g_at_ctrl.at_state = AT_IDLE;
                continue;
            }
            if (g_at_ctrl.at_state == AT_CMD_PROCESS) {
                at_cmd_execute(buf);
            } else if (g_at_ctrl.at_state == AT_DATA_SENDING) {
#ifndef CONFIG_FACTORY_TEST_MODE
                at_send_serial_data(buf);
                g_at_ctrl.at_state = AT_IDLE;
                g_at_ctrl.is_first_over_data = HI_TRUE;
#endif
            }
            hi_free(HI_MOD_ID_APP_AT, buf);
        }
    }
}

hi_u32 at_uart_init(hi_void)
{
    hi_u32 ret;
#ifndef CONFIG_QUICK_SEND_MODE
    hi_u8 uart_port = 0;
    ret = sal_uart_port_allocation(UART_FUNC_AT, &uart_port);
    if (ret != HI_ERR_SUCCESS) {
        hi_at_printf("Get at uart port fail, use default port.\r\n");
    }

    g_at_uart_port = uart_port;
#endif

    if (g_at_uart_port == 0xFF) {
        if (g_at_input_func == HI_NULL || g_at_output_func == HI_NULL) {
            g_at_input_func = at_monitor_input_func;
            g_at_output_func = at_monitor_output_func;
        }
        return HI_ERR_SUCCESS;
    }

    (hi_void)hi_uart_deinit(g_at_uart_port);
    ret = hi_uart_init(g_at_uart_port, &g_at_uart_cfg, HI_NULL);
    if (ret != HI_ERR_SUCCESS) {
        hi_at_printf("open uart%d failed.\r\n", (hi_u32)g_at_uart_port);
        return HI_ERR_FAILURE;
    }
    if (g_at_uart_port == HI_UART_IDX_0) {
        g_at_uart_baseaddr = HI_UART0_REG_BASE;
    } else if (g_at_uart_port == HI_UART_IDX_1) {
        g_at_uart_baseaddr = HI_UART1_REG_BASE;
    } else if (g_at_uart_port == HI_UART_IDX_2) {
        g_at_uart_baseaddr = HI_UART2_REG_BASE;
    }
    return HI_ERR_SUCCESS;
}

static hi_u32 check_name_and_callback(const at_cmd_func_list *ctx, hi_u8 tbl_index, HI_CONST at_cmd_func *cmd_tbl,
                                      hi_u16 cmd_num)
{
    hi_u32 ret = HI_ERR_SUCCESS;
    hi_u16 i;
    hi_u16 j;

    for (i = 0; i < ctx->at_cmd_num[tbl_index]; i++) {
        HI_CONST at_cmd_func *cmd_func = (at_cmd_func *)((ctx->at_cmd_list[tbl_index] + i));

        for (j = 0; j < cmd_num; j++) {
            if (((cmd_func->at_cmd_len == cmd_tbl[j].at_cmd_len) &&
                (strcmp(cmd_func->at_cmd_name, cmd_tbl[j].at_cmd_name) == 0)) ||
                ((cmd_tbl[j].at_test_cmd != HI_NULL) && (cmd_func->at_test_cmd == cmd_tbl[j].at_test_cmd)) ||
                ((cmd_tbl[j].at_query_cmd != HI_NULL) && (cmd_func->at_query_cmd == cmd_tbl[j].at_query_cmd)) ||
                ((cmd_tbl[j].at_setup_cmd != HI_NULL) && (cmd_func->at_setup_cmd == cmd_tbl[j].at_setup_cmd)) ||
                ((cmd_tbl[j].at_exe_cmd != HI_NULL) && (cmd_func->at_exe_cmd == cmd_tbl[j].at_exe_cmd))) {
                return HI_ERR_AT_NAME_OR_FUNC_REPEAT_REGISTERED;
            }
        }
    }

    return ret;
}

static hi_u32 check_cmd_tbl(HI_CONST at_cmd_func *cmd_tbl, hi_u16 cmd_num)
{
    hi_u16 i;
    hi_u16 j;

    for (i = 0; i < cmd_num; i++) {
        if (cmd_tbl[i].at_cmd_len != (hi_s8)strlen(cmd_tbl[i].at_cmd_name)) {
            return HI_ERR_AT_INVALID_PARAMETER;
        }

        for (j = 0; j < cmd_num; j++) {
            if (i == j) {
                continue;
            }

            if (((cmd_tbl[j].at_cmd_len == cmd_tbl[i].at_cmd_len) &&
                (strcmp(cmd_tbl[j].at_cmd_name, cmd_tbl[i].at_cmd_name) == 0)) ||
                ((cmd_tbl[j].at_test_cmd != HI_NULL) && (cmd_tbl[j].at_test_cmd == cmd_tbl[i].at_test_cmd)) ||
                ((cmd_tbl[j].at_query_cmd != HI_NULL) && (cmd_tbl[j].at_query_cmd == cmd_tbl[i].at_query_cmd)) ||
                ((cmd_tbl[j].at_setup_cmd != HI_NULL) && (cmd_tbl[j].at_setup_cmd == cmd_tbl[i].at_setup_cmd)) ||
                ((cmd_tbl[j].at_exe_cmd != HI_NULL) && (cmd_tbl[j].at_exe_cmd == cmd_tbl[i].at_exe_cmd))) {
                return HI_ERR_AT_NAME_OR_FUNC_REPEAT_REGISTERED;
            }
        }
    }

    return HI_ERR_SUCCESS;
}

hi_u32 hi_at_register_cmd(HI_CONST at_cmd_func *cmd_tbl, hi_u16 cmd_num)
{
    hi_u32 ret = HI_ERR_FAILURE;
    hi_u8 i;

    if (cmd_tbl == HI_NULL || cmd_num == 0) {
        return HI_ERR_FAILURE;
    }

    ret = check_cmd_tbl(cmd_tbl, cmd_num);
    if (ret != HI_ERR_SUCCESS) {
        return ret;
    }

    at_cmd_func_list *cmd_list = at_get_list();
    for (i = 0; i < AT_CMD_LIST_NUM; i++) {
        if ((cmd_list->at_cmd_list[i] == HI_NULL) || (cmd_list->at_cmd_num[i] == 0)) {
            cmd_list->at_cmd_list[i] = cmd_tbl;
            cmd_list->at_cmd_num[i] = cmd_num;
            ret = HI_ERR_SUCCESS;
            break;
        }

        ret = check_name_and_callback(cmd_list, i, cmd_tbl, cmd_num);
        if (ret != HI_ERR_SUCCESS) {
            break;
        }
    }

    return ret;
}

hi_void hi_at_sys_cmd_register(hi_void)
{
    hi_at_general_cmd_register();
#ifndef CONFIG_FACTORY_TEST_MODE
    hi_at_sta_cmd_register();
    hi_at_softap_cmd_register();
#endif
    hi_at_hipriv_cmd_register();
#ifndef CONFIG_FACTORY_TEST_MODE
#ifdef LOSCFG_APP_MESH
    hi_at_mesh_cmd_register();
#endif
    hi_at_lowpower_cmd_register();
#endif
    hi_at_general_factory_test_cmd_register();
    hi_at_sta_factory_test_cmd_register();
    hi_at_hipriv_factory_test_cmd_register();
    hi_at_io_cmd_register();
}

hi_u32 hi_at_init(hi_void)
{
    hi_u32 ret;
    hi_u32 at_uart_task, at_proc_task;

    if (g_at_init == HI_TRUE) {
        return HI_ERR_SUCCESS;
    }

    ret = at_uart_init();
    if (ret != HI_ERR_SUCCESS) {
        return ret;
    }
    hi_event_create(&g_at_event);

    hi_task_attr attr = {0};

    attr.stack_size  = g_at_proc_task_size;
    attr.task_prio   = AT_PROC_TASK_PRIO;
    attr.task_name   = (hi_char*)"at_proc";
    ret = hi_task_create(&at_proc_task, &attr, at_proc_task_body, 0);
    if (ret != HI_ERR_SUCCESS) {
        hi_at_printf("AT_PROC_TSK init fail\r\n");
        return ret;
    }

    attr.stack_size  = g_at_uart_task_size;
    attr.task_prio   = AT_UART_TASK_PRIO;
    attr.task_name   = (hi_char*)"at_uart";
    ret = hi_task_create(&at_uart_task, &attr, at_uart_task_body, 0);
    if (ret != HI_ERR_SUCCESS) {
        hi_at_printf("AT_UART_TSK init fail\r\n");
        return ret;
    }
    hi_timer_create(&g_at_uart_timer_handle);
    hi_lpc_register_check_handler((hi_u32_void_callback) lp_at_uart_vote);

    g_at_init = HI_TRUE;

    return HI_ERR_SUCCESS;
}

hi_void hi_at_set_task_size(hi_u16 uart_task_size, hi_u16 process_task_size)
{
    if (uart_task_size < AT_DEFAULT_UART_TASK_SIZE) {
        g_at_uart_task_size = AT_DEFAULT_UART_TASK_SIZE;
    } else {
        g_at_uart_task_size = uart_task_size;
    }

    if (process_task_size < AT_DEFAULT_PROC_TASK_SIZE) {
        g_at_proc_task_size = AT_DEFAULT_PROC_TASK_SIZE;
    } else {
        g_at_proc_task_size = process_task_size;
    }
}

#ifdef __cplusplus
#if __cplusplus
    }
#endif
#endif
