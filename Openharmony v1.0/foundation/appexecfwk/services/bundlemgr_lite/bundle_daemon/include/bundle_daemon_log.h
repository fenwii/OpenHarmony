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

#ifndef OHOS_BUNDLE_DAEMON_LOG_H
#define OHOS_BUNDLE_DAEMON_LOG_H

#include "log.h"

namespace OHOS {
#undef LOG_TAG
#define LOG_TAG "bundle_deamon"
#undef LOG_DOMAIN
#define LOG_DOMAIN 0xD001100

#define PRINTD(name, fmt, ...) HILOG_DEBUG(LOG_DOMAIN, "%{public}s::%{public}s(%{public}d): " fmt,  \
    name, __FUNCTION__, __LINE__, ##__VA_ARGS__)
#define PRINTI(name, fmt, ...) HILOG_INFO(LOG_DOMAIN, "%{public}s::%{public}s(%{public}d): " fmt,   \
    name, __FUNCTION__, __LINE__, ##__VA_ARGS__)
#define PRINTW(name, fmt, ...) HILOG_WARN(LOG_DOMAIN, "%{public}s::%{public}s(%{public}d): " fmt,   \
    name, __FUNCTION__, __LINE__, ##__VA_ARGS__)
#define PRINTE(name, fmt, ...) HILOG_ERROR(LOG_DOMAIN, "%{public}s::%{public}s(%{public}d): " fmt,  \
    name, __FUNCTION__, __LINE__, ##__VA_ARGS__)
} // OHOS
#endif // OHOS_BUNDLE_DAEMON_LOG_H
