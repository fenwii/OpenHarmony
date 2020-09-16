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

#ifndef GRAPHIC_LITE_GRAPHIC_LOG_H
#define GRAPHIC_LITE_GRAPHIC_LOG_H

#include "graphic_config.h"
#if ENABLE_GRAPHIC_LOG
#ifdef __LITEOS__
#include <cstring>
#include "hilog/log.h"
#elif defined _WIN32
#include <stdio.h>
#endif
#endif

namespace OHOS {
#if ENABLE_GRAPHIC_LOG
#ifdef __LITEOS__
typedef enum {
    LOG_LEVEL_FATAL = 0,
    LOG_LEVEL_ERROR,
    LOG_LEVEL_WARN,
    LOG_LEVEL_INFO,
    LOG_LEVEL_DEBUG,
    LOG_LEVEL_MAX
} LOG_LEVEL;

static constexpr HiviewDFX::HiLogLabel GRPHIC_LABEL = {LOG_CORE, 0xD001400, "Graphic"};

#define FILE_NAME(x) (strrchr(x, '/') ? (strrchr(x, '/') + 1) : x)

#define DECORATOR_HILOG(level, op, fmt, args...)                                                            \
do {                                                                                                        \
    if ((level < GRAPHIC_LOG_LEVEL) && (level < LOG_LEVEL_MAX)) {                                           \
        op(GRPHIC_LABEL, "{%s()-%s:%d} " fmt, __FUNCTION__, FILE_NAME(__FILE__), __LINE__, ##args);         \
    }                                                                                                       \
} while (0)

#define GRAPHIC_LOGF(fmt, args...)  DECORATOR_HILOG(LOG_LEVEL_FATAL, HiviewDFX::HiLog::Fatal, fmt, ##args)
#define GRAPHIC_LOGE(fmt, args...)  DECORATOR_HILOG(LOG_LEVEL_ERROR, HiviewDFX::HiLog::Error, fmt, ##args)
#define GRAPHIC_LOGW(fmt, args...)  DECORATOR_HILOG(LOG_LEVEL_WARN, HiviewDFX::HiLog::Warn, fmt, ##args)
#define GRAPHIC_LOGI(fmt, args...)  DECORATOR_HILOG(LOG_LEVEL_INFO, HiviewDFX::HiLog::Info, fmt, ##args)
#define GRAPHIC_LOGD(fmt, args...)  DECORATOR_HILOG(LOG_LEVEL_DEBUG, HiviewDFX::HiLog::Debug, fmt, ##args)

#elif defined _WIN32
#define GRAPHIC_LOGF(...)               \
do {                                    \
    printf("%s\n", __VA_ARGS__);        \
} while (0)

#define GRAPHIC_LOGE(...)               \
do {                                    \
    printf("%s\n", __VA_ARGS__);        \
} while (0)

#define GRAPHIC_LOGW(...)               \
do {                                    \
    printf("%s\n", __VA_ARGS__);        \
} while (0)

#define GRAPHIC_LOGI(...)               \
do {                                    \
    printf("%s\n", __VA_ARGS__);        \
} while (0)

#define GRAPHIC_LOGD(...)               \
do {                                    \
    printf("%s\n", __VA_ARGS__);        \
} while (0)
#else
#define GRAPHIC_LOGF(...)
#define GRAPHIC_LOGE(...)
#define GRAPHIC_LOGW(...)
#define GRAPHIC_LOGI(...)
#define GRAPHIC_LOGD(...)
#endif

#else // ENABLE_GRAPHIC_LOG

#define GRAPHIC_LOGF(...)
#define GRAPHIC_LOGE(...)
#define GRAPHIC_LOGW(...)
#define GRAPHIC_LOGI(...)
#define GRAPHIC_LOGD(...)

#endif // ENABLE_GRAPHIC_LOG
} // namespace OHOS
#endif // GRAPHIC_LITE_GRAPHIC_LOG_H
