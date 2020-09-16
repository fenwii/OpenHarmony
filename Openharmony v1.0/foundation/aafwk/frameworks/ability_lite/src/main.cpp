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

#include <cerrno>
#include <climits>
#include <cstddef>
#include <sys/prctl.h>

#include "ability_thread.h"
#include "log.h"

namespace {
    constexpr int HEX = 10;
    constexpr int TOKEN_INDEX = 1;
    constexpr int NAME_INDEX = 2;
}

int main(int argc, char *argv[])
{
    if (argc != NAME_INDEX + 1) {
        HILOG_ERROR(HILOG_MODULE_APP, "arg number is not %{public}d", NAME_INDEX + 1);
        return -1;
    }
    char *endPtr = nullptr;
    errno = 0;
    uint64_t token = std::strtoull(argv[TOKEN_INDEX], &endPtr, HEX);
    if ((errno == ERANGE && token == ULLONG_MAX) || (errno != 0 && token == 0) ||
        endPtr == nullptr || *endPtr != '\0') {
        HILOG_ERROR(HILOG_MODULE_APP, "token is invalid");
        return -1;
    }
    // set process name
    (void) prctl(PR_SET_NAME, argv[NAME_INDEX]);

    OHOS::AbilityThread::ThreadMain(token);
    return 0;
}
