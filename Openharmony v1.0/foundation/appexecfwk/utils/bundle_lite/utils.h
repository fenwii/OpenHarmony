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

#ifndef OHOS_UTILS_H
#define OHOS_UTILS_H

#include "adapter.h"
#include "securec.h"
#include "stdint.h"

namespace OHOS {
const uint32_t MAX_STR_SIZE = 4096;

struct Utils {
    static char *Strdup(const char *src)
    {
        if (src == nullptr) {
            return nullptr;
        }

        size_t len = strlen(src);
        if (len > MAX_STR_SIZE) {
            return nullptr;
        }
        char *dst = reinterpret_cast<char *>(AdapterMalloc(len + 1));
        if (dst == nullptr) {
            return nullptr;
        }
        errno_t err = strncpy_s(dst, len + 1, src, len);
        if (err != EOK) {
            AdapterFree(dst);
            return nullptr;
        }
        return dst;
    }

    static void *Memdup(const void *src, uint32_t len)
    {
        if ((src == nullptr) || (len == 0) || (len > MAX_STR_SIZE)) {
            return nullptr;
        }

        void *dst = AdapterMalloc(len);
        if (dst == nullptr) {
            return nullptr;
        }

        int ret = memcpy_s(dst, len, src, len);
        if (ret != 0) {
            AdapterFree(dst);
            return nullptr;
        }

        return dst;
    }
}; // Utils
} // OHOS

#endif // OHOS_UTILS_H
