/*
 * Copyright (c) 2013-2019, Huawei Technologies Co., Ltd. All rights reserved.
 * Copyright (c) 2020, Huawei Device Co., Ltd. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this list of
 *    conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice, this list
 *    of conditions and the following disclaimer in the documentation and/or other materials
 *    provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its contributors may be used
 *    to endorse or promote products derived from this software without specific prior written
 *    permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef TC_NS_LOG_H_
#define TC_NS_LOG_H_

#include <linux/kernel.h>
enum {
    TZ_DEBUG_VERBOSE = 0,
    TZ_DEBUG_DEBUG,
    TZ_DEBUG_INFO,
    TZ_DEBUG_WARN,
    TZ_DEBUG_ERROR,
};

#ifdef DEF_ENG
#define TEE_ENG_LOG_MASK 2
#define TEE_LOG_MASK TEE_ENG_LOG_MASK
#else
#define TEE_USR_LOG_MASK 3
#define TEE_LOG_MASK TEE_USR_LOG_MASK
#endif

#define tlogv(fmt, args...) \
do { \
    if (TZ_DEBUG_VERBOSE >= TEE_LOG_MASK) \
        pr_info("(%i, %s)%s: " fmt, OsCurrTaskGet()->taskID, OsCurrTaskGet()->taskName, __func__, ## args); \
} while (0)


#define tlogd(fmt, args...) \
do { \
    if (TZ_DEBUG_DEBUG >= TEE_LOG_MASK) \
        pr_info("(%i, %s)%s: " fmt, OsCurrTaskGet()->taskID, OsCurrTaskGet()->taskName, __func__, ## args); \
} while (0)


#define tlogi(fmt, args...) \
do { \
    if (TZ_DEBUG_INFO >= TEE_LOG_MASK) \
        pr_info("(%i, %s)%s: " fmt, OsCurrTaskGet()->taskID, OsCurrTaskGet()->taskName, __func__, ## args); \
} while (0)


#define tlogw(fmt, args...) \
do { \
    if (TZ_DEBUG_WARN >= TEE_LOG_MASK) \
        pr_warn("(%i, %s)%s: " fmt, OsCurrTaskGet()->taskID, OsCurrTaskGet()->taskName, __func__, ## args); \
} while (0)


#define tloge(fmt, args...) \
        pr_err("(%i, %s)%s: " fmt, OsCurrTaskGet()->taskID, OsCurrTaskGet()->taskName, __func__, ## args)

#endif
