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

#include "hks_log_utils.h"

static void logi(const char *tag, const char *func, const char *format, ...);
static void logw(const char *tag, const char *func, const char *format, ...);
static void loge(const char *tag, const char *func, const char *format, ...);
static void logd(const char *tag, const char *func, const char *format, ...);

static struct hks_log_f_group g_log_func = { logi, logw, loge, logd };

void hks_register_log(const struct hks_log_f_group *log)
{
    if (log == NULL)
        return;

    if (log->log_info != NULL)
        g_log_func.log_info = log->log_info;

    if (log->log_warn != NULL)
        g_log_func.log_warn = log->log_warn;

    if (log->log_error != NULL)
        g_log_func.log_error = log->log_error;

    if (log->log_debug != NULL)
        g_log_func.log_debug = log->log_debug;
}

hks_log_func get_log_info(void)
{
    return g_log_func.log_info;
}

hks_log_func get_log_warn(void)
{
    return g_log_func.log_warn;
}

hks_log_func get_log_error(void)
{
    return g_log_func.log_error;
}

hks_log_func get_log_debug(void)
{
    return g_log_func.log_debug;
}

/* Default log info interface, do nothing */
static void logi(const char *tag, const char *func, const char *format, ...)
{
    (void)tag; (void)func; (void)format;
}

/* Default log warn interface, do nothing */
static void logw(const char *tag, const char *func, const char *format, ...)
{
    (void)tag; (void)func; (void)format;
}

/* Default log error interface, do nothing */
static void loge(const char *tag, const char *func, const char *format, ...)
{
    (void)tag; (void)func; (void)format;
}

/* Default log debug interface, do nothing */
static void logd(const char *tag, const char *func, const char *format, ...)
{
    (void)tag; (void)func; (void)format;
}
