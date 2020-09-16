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

#include "ace_log.h"
#include <stdarg.h>
#include <stdio.h>

#if (defined(_WIN32) || defined(_WIN64))
namespace OHOS {
namespace ACELite {
void PrintInfo(const char *format, va_list args)
{
    vprintf(format, args);
    printf("\n");
}

void HILOG_FATAL(HiLogModuleType mod, const char *msg, ...)
{
    printf("[FATAL]:");
    va_list args;
    va_start(args, msg);
    PrintInfo(msg, args);
    va_end(args);
}

void HILOG_ERROR(HiLogModuleType mod, const char *msg, ...)
{
    printf("[ERROR]:");
    va_list args;
    va_start(args, msg);
    PrintInfo(msg, args);
    va_end(args);
}

void HILOG_INFO(HiLogModuleType mod, const char *msg, ...)
{
    printf("[INFO]:");
    va_list args;
    va_start(args, msg);
    PrintInfo(msg, args);
    va_end(args);
}

void HILOG_WARN(HiLogModuleType mod, const char *msg, ...)
{
    printf("[WARN]:");
    va_list args;
    va_start(args, msg);
    PrintInfo(msg, args);
    va_end(args);
}

void HILOG_DEBUG(HiLogModuleType mod, const char *msg, ...)
{
    printf("[DEBUG]:");
    va_list args;
    va_start(args, msg);
    PrintInfo(msg, args);
    va_end(args);
}
} // namespace ACELite
} // namespace OHOS
#endif
