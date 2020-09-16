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

#include "sal_cfg.h"

#include <hi_early_debug.h>
#include <hi_nv.h>
#include <hi_sal.h>
#include <hi_sal_cfg.h>
#include <hi_watchdog.h>

hi_u32 g_auto_wdg_rst_sys_timeout = PRODUCT_CFG_AUTO_WDG_RESET_SYSTEM_TIMEOUT;

// #define CONFIG_HILINK_PKI_SUPPORT /* currently hilink not support PKI provision */
hi_void hi_tee_irq_handler(void)
{
#ifdef CONFIG_TEE_HUKS_SUPPORT
#if defined(CONFIG_FACTORY_TEST_MODE) && defined(CONFIG_HILINK) && defined(CONFIG_HILINK_PKI_SUPPORT)
    hks_handle_secure_pki_provision();
#else
    hks_handle_secure_call();
#endif
#else
    printf("receive tee irq\r\n");
#endif
}

hi_u32 hi_get_rf_xtal_compesation_param(rf_cfg_xtal_compesation *xtal_param)
{
    if (xtal_param == HI_NULL) {
        return HI_ERR_FAILURE;
    }

    return hi_factory_nv_read(INIT_CONFIG_XTAL_COMPESATION, (hi_void *)xtal_param, sizeof(rf_cfg_xtal_compesation), 0);
}

hi_void hi_diag_register_wifi_log()
{
#ifdef CONFIG_DIAG_SUPPORT
    oam_log_hook_func log_hook = {
        hi_diag_log_msg0,
        hi_diag_log_msg1,
        hi_diag_log_msg2,
        hi_diag_log_msg3,
        hi_diag_log_msg4,
        hi_diag_log_msg_buffer
    };
    oam_log_register_hook_func(&log_hook);
#endif
}

hi_u32 hi_watchdog_set_timeout(hi_u32 timeout_ms)
{
    if (timeout_ms < HI_WDG_MIN_TIMEOUT) {
        return HI_ERR_FAILURE;
    }
    g_auto_wdg_rst_sys_timeout = timeout_ms;

    hi_sal_wdg_clear();
    return HI_ERR_SUCCESS;
}

