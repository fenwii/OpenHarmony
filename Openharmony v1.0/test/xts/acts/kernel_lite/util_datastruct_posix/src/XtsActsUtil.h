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

#ifndef XTS_ACTS_UTIL_H
#define XTS_ACTS_UTIL_H

#include <stdio.h>
#include <stdarg.h>

// 0 not print, 1 print
static int g_xtsDebugLevel = 1;

static int LogPrint(const char *format, ...)
{
    int ret = 0;
    if (g_xtsDebugLevel == 0) {  
    } else {
        va_list ap;
        va_start(ap, format);
        ret = vfprintf(stdout, format, ap);
        va_end(ap);
    }
    return ret;
}

static int NumCompare(const void *p1, const void *p2)
{
    return ((*(int *)p1) - (*(int *)p2));
}

#endif