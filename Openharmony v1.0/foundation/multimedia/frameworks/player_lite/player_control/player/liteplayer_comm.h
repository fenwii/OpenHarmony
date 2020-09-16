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

#ifndef LITEPLAYER_COMM_H
#define LITEPLAYER_COMM_H

#include "player_define.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* End of #ifdef __cplusplus */

#ifdef ENABLE_LOG
#define AV_PRINTF(format, ...) printf(format, ##__VA_ARGS__)
#else
#define AV_PRINTF(format, ...)
#endif

#ifdef ENABLE_LOG
void AV_TRACE(const char *fmt, ...) __attribute__((format(printf, 1, 2)));
#else
#define AV_TRACE(fmt, ...)
#endif

int32_t LiteplayerOnAvEvent(void* priv, EventCbType event, int32_t ext1, int32_t ext2);

int32_t LiteplayerOnAvStatusChange(void *priv, PlayerStatus status);

uint64_t LiteplayerGetCurRelativeTime();

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */

#endif  // LITEPLAYER_COMM_H
