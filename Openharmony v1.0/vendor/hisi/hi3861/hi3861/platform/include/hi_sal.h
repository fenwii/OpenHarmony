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

/**
* @file hi_sal.h
*
* Copyright (c) Hisilicon Technologies Co., Ltd. 2019. All rights reserved.  \n
*
* Description: sal interfaces. \n
*/

#ifndef __HI_SAL_H__
#define __HI_SAL_H__
#include <hi_types.h>
#include <hi_ft_nv.h>
#include <hi_reset.h>
#include <watchdog.h>
#include <hi_sal_cfg.h>
#include <hi_time.h>
#include <hi_stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

#define WDG_TIMEOUT      6500
#define MS_PER_SEC       1000
#define MS_PER_MIN       (60 * 1000)

#define HI_WDT_FLAG_REG             GLB_CTL_GP_REG1_REG

#define HI_MONITOR_INTERVAL_MS      1000
#define HI_MONITOR_INTERVAL_SEC     (HI_MONITOR_INTERVAL_MS / 1000)

HI_EXTERN hi_u32 g_auto_wdg_rst_sys_timeout;
#define check_wd_timerout_enable()  (g_auto_wdg_rst_sys_timeout > 0)
HI_EXTERN hi_u32 g_cpu_clock;
HI_EXTERN hi_u32 g_flash_prot_sem;

hi_void watchdog_feed(hi_void);
hi_u32 hi_sal_timer_init(hi_void);
hi_u32 hi_sal_timer_suspend(hi_void);
hi_u32 hi_sal_timer_resume(hi_void);
hi_void hi_sal_init(hi_void);
hi_void hi_sal_wdg_clear(hi_void);

hi_bool hi_diag_is_init(hi_void);
hi_bool hi_get_shell_init(hi_void);

/**
* @ingroup  hct_reset_save
* @brief save crash messsage into flash. CNcomment:存储crash信息到flash。CNend
*
* @par 描述:
*           save crash messsage into flash. CNcomment:存储crash信息到flash。CNend
*
* @attention 无。
* @param  data          [IN] type #hi_pvoid ，Exception information pointer.CNcomment:异常信息指针。CNend
* @param  str           [IN] type #hi_char * ，Exception description. CNcomment:异常描述。CNend
*
* @retval None.
* @par 依赖:
*           @li hi_crash.h：文件用于描述异常存储接口。
* @see hi_syserr_store_crash_info。
*/
hi_void hi_syserr_store_crash_info(hi_pvoid data);

#ifdef __cplusplus
}
#endif

#endif /* __HI_SAL_H__ */
