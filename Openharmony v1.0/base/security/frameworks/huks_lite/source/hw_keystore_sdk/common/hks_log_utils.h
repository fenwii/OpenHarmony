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

#ifndef HKS_LOG_UTILS_H
#define HKS_LOG_UTILS_H

#include "hks_errno.h"
#include "hks_types.h"

#define HKS_LOG_TAG  "[HKS]"

void hks_register_log(const struct hks_log_f_group *log);

hks_log_func get_log_info(void);
hks_log_func get_log_warn(void);
hks_log_func get_log_error(void);
hks_log_func get_log_debug(void);

#if !(defined(_CUT_LOG_))
#define log_info(...) get_log_info()(HKS_LOG_TAG, __func__, __VA_ARGS__)
#define log_warn(...) get_log_warn()(HKS_LOG_TAG, __func__, __VA_ARGS__)
#define log_error(...) get_log_error()(HKS_LOG_TAG, __func__, __VA_ARGS__)
#define log_debug(...) get_log_debug()(HKS_LOG_TAG, __func__, __VA_ARGS__)
#else
#define log_info(...) {}
#define log_warn(...) {}
#define log_error(...) {}
#define log_debug(...) {}
#endif

#define HKS_TRACE_IN   log_debug("-->")
#define HKS_TRACE_OUT  log_debug("<--")

/*
 * warning: this macro function only can be used in the
 * beginnig of each function
 * do not use it after malloc, alloc etc. you can use goto statement instead
 */
#define hks_if_status_error_return(s) \
    if ((s) != HKS_SUCCESS) { \
        log_error("%s %d return error : %d.\n", __func__, __LINE__, (s)); return s; }

#define hks_if_status_error_return_err(s, err) \
    if ((s) != HKS_SUCCESS) { \
        log_error("%s %d status: %d.return error : %d.\n", __func__, __LINE__, (s), (err)); return err; }

/*
 * warning: this macro function only can be used in the beginnig of
 * each function
 * do not use it after malloc, alloc etc. you can use goto statement instead
 */
#define hks_if_true_return_error(s, err) \
    if ((s) == HKS_BOOL_TRUE) { \
        log_error("%s %d return status: %d.\n", __func__, __LINE__, (err)); return err; }

/*
 * warning: this macro function is suggested to be used after
 * malloc, alloc etc. you can free memory after error label
 */
#define hks_if_status_error_goto_error(s, err) \
    if ((s) != HKS_SUCCESS) { \
        log_error("%s %d status: %d.goto error\n", __func__, __LINE__, (s)); goto err; }
#endif
