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

#include "time_util.h"
#include <stdlib.h>
#include <string.h>
#include "ace_mem_base.h"
#include "js_fwk_common.h"

namespace OHOS {
namespace ACELite {
constexpr char CHAR_M = 'm';
constexpr char CHAR_S = 's';
constexpr int32_t MILLIONS_PER_SECOND = 1000;
constexpr uint8_t IDX_PENULT = 2;
int32_t ParseToMilliseconds(const char *time)
{
    if ((time == nullptr) || (strlen(time) == 0)) {
        return 0;
    }
    size_t size = strlen(time);
    if (size >= UINT8_MAX) {
        return 0;
    }
    int32_t milliseconds = 0;
    if (size == 1) {
        milliseconds = strtol(time, nullptr, DEC);
        return (milliseconds < 0) ? 0 : milliseconds;
    }

    size_t bufSize = size;
    char last = time[size - 1];
    char penult = time[size - IDX_PENULT];
    bool isSecond = false;
    if (penult == CHAR_M && last == CHAR_S) {
        bufSize = size - IDX_PENULT;
    } else if (last == CHAR_S) {
        bufSize = size - 1;
        isSecond = true;
    }
    if (bufSize == 0) {
        return 0;
    }

    char *buffer = static_cast<char *>(ace_malloc(bufSize + 1));
    if (buffer == nullptr) {
        return 0;
    }
    if (strncpy_s(buffer, bufSize + 1, time, bufSize) == 0) {
        buffer[bufSize] = '\0';
        milliseconds = isSecond ? (strtod(buffer, nullptr) * MILLIONS_PER_SECOND) : strtol(buffer, nullptr, DEC);
    }
    ace_free(buffer);
    buffer = nullptr;
    return (milliseconds < 0) ? 0 : milliseconds;
}
} // namespace ACELite
} // namespace OHOS
