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

#ifndef OHOS_LOGGING_H
#define OHOS_LOGGING_H

#include "log.h"

namespace OHOS {
#undef LOG_TAG
#define LOG_TAG "abilityms"
#undef LOG_DOMAIN
#define LOG_DOMAIN 0xD001300

#ifdef OHOS_DEBUG
#define PRINTD(name, fmt, ...) HILOG_DEBUG(LOG_DOMAIN, "%{public}s::%{public}s(%{public}d): " fmt,  \
    name, __FUNCTION__, __LINE__, ##__VA_ARGS__)
#else
#define PRINTD(name, fmt, ...)
#endif
#define PRINTI(name, fmt, ...) HILOG_INFO(LOG_DOMAIN, "%{public}s::%{public}s(%{public}d): " fmt,   \
    name, __FUNCTION__, __LINE__, ##__VA_ARGS__)
#define PRINTW(name, fmt, ...) HILOG_WARN(LOG_DOMAIN, "%{public}s::%{public}s(%{public}d): " fmt,   \
    name, __FUNCTION__, __LINE__, ##__VA_ARGS__)
#define PRINTE(name, fmt, ...) HILOG_ERROR(LOG_DOMAIN, "%{public}s::%{public}s(%{public}d): " fmt,  \
    name, __FUNCTION__, __LINE__, ##__VA_ARGS__)

#define CHECK_NULLPTR_RETURN_PTR(point, name, fmt)            \
    do {                                                      \
        if (point == nullptr) {                               \
            PRINTE(name, fmt);                                \
            return nullptr;                                   \
        }                                                     \
    } while (0)

#define CHECK_NULLPTR_RETURN(point, name, fmt)            \
    do {                                                  \
        if (point == nullptr) {                           \
            PRINTE(name, fmt);                            \
            return;                                       \
        }                                                 \
    } while (0)

#define CHECK_NULLPTR_RETURN_CODE(point, name, fmt, code) \
    do {                                                  \
        if (point == nullptr) {                           \
            PRINTE(name, fmt);                            \
            return code;                                  \
        }                                                 \
    } while (0)
} // namespace OHOS
#endif // OHOS_LOGGING_H
