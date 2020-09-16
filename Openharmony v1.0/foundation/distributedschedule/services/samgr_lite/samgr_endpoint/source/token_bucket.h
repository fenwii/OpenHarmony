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
#ifndef LITE_TOKEN_BUCKET_H
#define LITE_TOKEN_BUCKET_H

#include <ohos_types.h>

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif
#define TOKEN_PRE_MSG 1000
typedef struct TokenBucket TokenBucket;
struct TokenBucket {
    int rate;  // The rate of token generation per millisecond. Now, we use the TPS instead.
    int burst; // The burst size of the token bucket
    uint64 last; // The time of the last message
    int used; // The used buckets. When the rate is TPS, the value is used * TOKEN_PRE_MSG.
};
typedef enum BucketStatus {
    BUCKET_BUSY,
    BUCKET_IDLE,
    BUCKET_INVALID,
} BucketStatus;

inline static void TB_InitBucket(TokenBucket *bucket, int rate, int burst)
{
    bucket->last = 0;
    bucket->rate = rate;
    bucket->burst = burst;
    bucket->used = 0;
}
int TB_CheckMessage(TokenBucket *bucket);
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif
#endif // LITE_TOKEN_BUCKET_H
