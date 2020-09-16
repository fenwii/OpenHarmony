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

#include "liteplayer_comm.h"
#include <sys/time.h>
#include <unistd.h>
#ifdef __HuaweiLite__
#include <los_ld_elflib.h>
#else
#include <dlfcn.h>
#endif
#include "liteplayer.h"

using OHOS::Media::LitePlayer;

const long long AV_NS2MS_SCALE = 1000000ll;
const long long AV_SEC2MS_SCALE = 1000ll;

#ifdef ENABLE_LOG
void AV_TRACE(const char *fmt, ...)
{
    char printStr[MAX_PRINT_STR_LEN] = { 0 };

    if (fmt == NULL) {
        return;
    }
    va_list args;
    va_start(args, fmt);
    if (vsnprintf_s(printStr, MAX_PRINT_STR_LEN, MAX_PRINT_STR_LEN - 1, fmt, args) < 0) {
        va_end(args);
        return;
    }
    va_end(args);
    AV_PRINTF("[player] %s", printStr);
}
#endif

int32_t LiteplayerOnAvEvent(void* priv, EventCbType event, int32_t ext1, int32_t ext2)
{
    LitePlayer *player = reinterpret_cast<LitePlayer *>(priv);
    if (player == nullptr) {
        return -1;
    }
    return player->OnAvplayEvent(priv, event);
}

int32_t LiteplayerOnAvStatusChange(void *priv, PlayerStatus status)
{
    LitePlayer *player = reinterpret_cast<LitePlayer *>(priv);
    if (player == nullptr) {
        return -1;
    }
    return player->OnAvplayStatusChange(priv, status);
}

uint64_t LiteplayerGetCurRelativeTime()
{
    struct timespec ts = { 0, 0 };
    (void)clock_gettime(CLOCK_MONOTONIC, &ts);
    uint64_t curTime = ((uint64_t)ts.tv_sec) * AV_SEC2MS_SCALE + ((uint64_t)ts.tv_nsec) / AV_NS2MS_SCALE;
    return curTime;
}

