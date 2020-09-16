/*
 * Copyright (c) 2020 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef _HC_DEBUG_

#include "log.h"
#include <securec.h>
#include "base.h"
#include "../huks_adapter/hks_client.h"

#if defined(_WINDOWS)
#ifdef DLL_EXPORT
#define DLL_API_PUBLIC __declspec(dllexport)
#else
#define DLL_API_PUBLIC __declspec(dllimport)
#endif
#else
#define DLL_API_PUBLIC __attribute__ ((visibility("default")))
#endif

static void hc_logd(const char *tag, const char *func, const char *format, ...);
static void hc_logi(const char *tag, const char *func, const char *format, ...);
static void hc_logw(const char *tag, const char *func, const char *format, ...);
static void hc_loge(const char *tag, const char *func, const char *format, ...);

static struct log_f_group g_log_func = { hc_logd, hc_logi, hc_logw, hc_loge };

log_f get_logd(void)
{
    return g_log_func.log_d;
}

log_f get_logi(void)
{
    return g_log_func.log_i;
}

log_f get_logw(void)
{
    return g_log_func.log_w;
}

log_f get_loge(void)
{
    return g_log_func.log_e;
}

/* no log without register */
DLL_API_PUBLIC void registe_log(struct log_f_group *log)
{
    check_ptr_return(log);
    struct hks_log_f_group hks_log;

    (void)memset_s(&hks_log, sizeof(hks_log), 0, sizeof(hks_log));
    hks_log.log_debug = log->log_d;
    hks_log.log_info = log->log_i;
    hks_log.log_warn = log->log_w;
    hks_log.log_error = log->log_e;
    hks_register_log_interface(&hks_log);

    if (log->log_d != NULL) {
        g_log_func.log_d = log->log_d;
    }
    if (log->log_i != NULL) {
        g_log_func.log_i = log->log_i;
    }
    if (log->log_w != NULL) {
        g_log_func.log_w = log->log_w;
    }
    if (log->log_e != NULL) {
        g_log_func.log_e = log->log_e;
    }
}

static void hc_logd(const char *tag, const char *func, const char *format, ...)
{
    (void)tag;
    (void)func;
    (void)format;
}

static void hc_logi(const char *tag, const char *func, const char *format, ...)
{
    (void)tag;
    (void)func;
    (void)format;
}

static void hc_logw(const char *tag, const char *func, const char *format, ...)
{
    (void)tag;
    (void)func;
    (void)format;
}

static void hc_loge(const char *tag, const char *func, const char *format, ...)
{
    (void)tag;
    (void)func;
    (void)format;
};
#endif /* _HC_DEBUG_ */
