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

#ifndef __SAL_COMMON_H__
#define __SAL_COMMON_H__

#include <dfx_sal.h>
#include "hi_crash.h"
#include <hi_early_debug.h>

hi_void sal_show_run_time(hi_void);

#define ID_MSG_DIAG_BASE 0x100

enum {
    ID_MSG_DIAG_DATA_TX = (ID_MSG_DIAG_BASE + 1),
    ID_MSG_DIAG_DATA_USER_TX,
    ID_MSG_DIAG_ACK_RX,
    ID_MSG_DIAG_ACK_TX,
    ID_MSG_DIAG_RX,
    ID_MSG_DIAG_TIMER,
    ID_MSG_DIAG_MSG,
    ID_MSG_DIAG_ACK_MDM_RX
};

#define diag_msg_free(msg)  hi_free(HI_MOD_ID_SAL_DIAG, (hi_pvoid)((msg)->param[0]))
#define diag_msg_free0(msg) hi_free(HI_MOD_ID_SAL_DIAG, (hi_pvoid)((msg)->param[0]))
#define diag_buffering_msg_free(msg) diag_free_buffer((diag_buffer_id)hi_lou16((msg)->param[3]), \
    (hi_pvoid)(uintptr_t)((msg)->param[0]))

// Helper routine
#define init_exception_polling_wait() hi_sleep(HI_DMS_CHL_EXCEPTION_POLLING_WAIT)
#define uart_exception_polling_wait() hi_sleep(HI_DMS_UART_EXCEPTION_POLLING_WAIT)

HI_EXTERN hi_void flash_set_crash_flag(hi_void);
HI_EXTERN hi_u32 flash_read_crash(HI_IN hi_u32 addr, HI_IN hi_void *data, HI_IN hi_u32 size);
HI_EXTERN hi_u32 flash_write_crash(HI_IN hi_u32 addr, HI_IN hi_void *data, HI_IN hi_u32 size);
HI_EXTERN hi_u32 flash_erase_crash(HI_IN hi_u32 addr, HI_IN hi_u32 size);
HI_EXTERN hi_u32 flash_ioctl_crash(hi_u16 cmd, hi_void *data);

#if defined(PRODUCT_CFG_DIAG_FRM_ERR_PK_RPT)
hi_u32 diag_chl_error_report(hi_u32 ret, hi_u32 id);
#else
#define diag_chl_error_report(ret, id) \
    do {                               \
    } while (0)
#endif

/* ERR REPORT ONLY for DIAG inside */
#define diag_chl_err_rpt(id, ret)                                   \
    do {                                                            \
        if ((ret) != HI_ERR_SUCCESS && (ret) != HI_ERR_DIAG_CONSUMED) { \
            diag_chl_error_report((ret), (id));                         \
        }                                                           \
    } while (0)

#define DIAG_ERR_RPT_LEN 48

HI_EXTERN hi_stat_diag g_stat_diag;

hi_u32 hi_syserr_get_at_printf(hi_syserr_info *info);

#define CRASH_INFO_EID_SAVE_ADDR 6
#define CRASH_INFO_EID_SAVE_SIZE 4
#define CRASH_INFO_RID_SAVE_ADDR 10
#define CRASH_INFO_RID_SAVE_SIZE 6

#endif /* __SAL_COMMON_H__ */

