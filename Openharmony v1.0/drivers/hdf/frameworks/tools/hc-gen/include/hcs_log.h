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

#ifndef HCS_COMPILER_LOG_H
#define HCS_COMPILER_LOG_H

#include <stdio.h>
#include <stdlib.h>
#include "hcs_types.h"

#ifdef DEBUG
#define HCS_DEBUG(fmt, args...) fprintf(stdout, fmt"\n", ##args)
#else
#define HCS_DEBUG(fmt, args...) do {} while (0)
#endif

#ifdef OS_LINUX
#define ERROR_COLOR_PREFIX "\033[31m"
#define ERROR_COLOR_END    "\033[0m"
#else
#define ERROR_COLOR_PREFIX
#define ERROR_COLOR_END
#endif

#define HCS_LOG_PRINT(fmt, args...)  fprintf(stdout, ERROR_COLOR_PREFIX fmt ERROR_COLOR_END"\n", ##args)

#define HCS_PRINT(fmt, args...)  fprintf(stdout, fmt, ##args)

#define HCS_INFO(fmt, args...)  fprintf(stdout, fmt"\n", ##args)

#define HCS_ERROR(fmt, args...) HCS_LOG_PRINT("Error: " fmt, ##args)

#define HCS_WARNING(fmt, args...) HCS_LOG_PRINT("Warning: " fmt, ##args)

#define HCS_OBJECT_PR(prefix, object, fmt, args...)                         \
    do {                                                                    \
        HCS_LOG_PRINT (prefix": %s:%u\n\t" fmt"\n",                         \
                    object ? ((ParserObjectBase*)object)->src : "unknown",  \
                    object ? ((ParserObjectBase*)object)->lineno : 0,       \
                    ##args);                                                \
    } while (0)

#define HCS_OBJECT_ERROR(object, fmt, args...) HCS_OBJECT_PR("Error", object, fmt, ##args)

#define HCS_OBJECT_WARNING(object, fmt, args...) HCS_OBJECT_PR("Warning", object, fmt, ##args)

#define PRINTF_CHECK_AND_RETURN(printRes)                                   \
    do {                                                                    \
        if ((printRes) < 0) {                                               \
            HCS_ERROR("Error:%s(%d), sprintf_s fail",                       \
                __FUNCTION__, __LINE__);                                    \
            return EOUTPUT;                                                 \
        }                                                                   \
    } while (0)

#define SPRINTF_ERROR_INFO "sprintf fail"

#endif // HCS_COMPILER_LOG_H
