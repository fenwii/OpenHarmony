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
#include "token_bucket.h"
#include <ohos_types.h>
#include <common.h>
#include "time_adapter.h"
int TB_CheckMessage(TokenBucket *bucket)
{
    if (bucket == NULL) {
        return BUCKET_INVALID;
    }
    uint64 now = SAMGR_GetProcessTime();
    uint64 generated = (now > bucket->last) ? ((now - bucket->last) * bucket->rate) : 0;
    int used = bucket->used + TOKEN_PRE_MSG;
    used = (generated > used) ? 0 : (used - (int)generated);
    if (used >= bucket->burst * TOKEN_PRE_MSG) {
        return BUCKET_BUSY;
    }
    bucket->used = used;
    bucket->last = now;
    return BUCKET_IDLE;
}