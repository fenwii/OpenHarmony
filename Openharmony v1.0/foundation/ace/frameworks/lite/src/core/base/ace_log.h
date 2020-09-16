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

#ifndef OHOS_ACELITE_ACE_LOG_H
#define OHOS_ACELITE_ACE_LOG_H

#include "acelite_config.h"

#if defined(FEATURE_ACELITE_HI_LOG_PRINTF) && defined(FEATURE_ACELITE_MC_LOG_PRINTF)
#error Only one marco can be defined
#elif defined(FEATURE_ACELITE_HI_LOG_PRINTF) && (defined(_WIN32) || defined(_WIN64))
#error Only one marco can be defined
#elif defined(FEATURE_ACELITE_MC_LOG_PRINTF) && (defined(_WIN32) || defined(_WIN64))
#error Only one macro can be defined
#endif

#if defined(FEATURE_ACELITE_HI_LOG_PRINTF)
#undef LOG_DOMAIN
#undef LOG_TAG
#define LOG_DOMAIN 0xD003900
#define LOG_TAG "ACE"
#include "hilog/log.h"
#elif defined(FEATURE_ACELITE_MC_LOG_PRINTF)
#ifndef HILOG_DEBUG
#define HILOG_DEBUG(mod, format, ...)
#endif
#ifndef HILOG_ERROR
#define HILOG_ERROR(mod, format, ...)
#endif
#ifndef HILOG_FATAL
#define HILOG_FATAL(mod, format, ...)
#endif
#ifndef HILOG_INFO
#define HILOG_INFO(mod, format, ...)
#endif
#ifndef HILOG_WARN
#define HILOG_WARN(mod, format, ...)
#endif
#ifndef HILOG_RACE
#define HILOG_RACE(mod, format, ...)
#endif
#elif (defined(_WIN32) || defined(_WIN64))
namespace OHOS {
namespace ACELite {
typedef enum { HILOG_MODULE_ACE = 1 } HiLogModuleType;

void HILOG_FATAL(HiLogModuleType mod, const char *msg, ...);
void HILOG_ERROR(HiLogModuleType mod, const char *msg, ...);
void HILOG_INFO(HiLogModuleType mod, const char *msg, ...);
void HILOG_WARN(HiLogModuleType mod, const char *msg, ...);
void HILOG_DEBUG(HiLogModuleType mod, const char *msg, ...);
} // namespace ACELite
} // namespace OHOS
#else
#error One macro must be defined
#endif
#endif // OHOS_ACELITE_ACE_LOG_H
