/*
 * Copyright (c) 2020 Huawei Device Co., Ltd.
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

#ifndef LIBTEEC_TEEC_LOG_H
#define LIBTEEC_TEEC_LOG_H

#include <stdio.h>

enum {
    TEE_LOG_VERBOSE = 0,
    TEE_LOG_DEBUG,
    TEE_LOG_INFO,
    TEE_LOG_WARN,
    TEE_LOG_ERROR,
};

#ifdef DEF_ENG
#define TEE_LOG_MASK TEE_LOG_INFO
#else
#define TEE_LOG_MASK TEE_LOG_WARN
#endif

#define tlogv(fmt, args...) \
    do { \
        if (TEE_LOG_VERBOSE >= TEE_LOG_MASK) \
            printf("%s: " fmt, __func__, ## args); \
    } while (0)

#define tlogd(fmt, args...) \
    do { \
        if (TEE_LOG_DEBUG >= TEE_LOG_MASK) \
            printf("%s: " fmt, __func__, ## args); \
    } while (0)

#define tlogi(fmt, args...) \
    do { \
        if (TEE_LOG_INFO >= TEE_LOG_MASK) \
            printf("%s: " fmt, __func__, ## args); \
    } while (0)

#define tlogw(fmt, args...) \
    do { \
        if (TEE_LOG_WARN >= TEE_LOG_MASK) \
            printf("%s: " fmt, __func__, ## args); \
    } while (0)

#define tloge(fmt, args...) \
    do { \
        if (TEE_LOG_ERROR >= TEE_LOG_MASK) \
            printf("%s: " fmt, __func__, ## args); \
    } while (0)

#endif
