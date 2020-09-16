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
#ifndef LITE_LOCK_FREE_QUEUE_H
#define LITE_LOCK_FREE_QUEUE_H

#include <ohos_types.h>

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

typedef struct LockFreeQueue LockFreeQueue;
struct LockFreeQueue {
    uint32 write;
    uint32 read;
    uint32 itemSize;
    uint32 totalSize;
    uint8 buffer[0];
};
LockFreeQueue *LFQUE_Create(int size, int count);

BOOL LFQUE_IsEmpty(LockFreeQueue *queue);

BOOL LFQUE_IsFull(LockFreeQueue *queue);

int LFQUE_Push(LockFreeQueue *queue, const void *element, uint8 pri);

int LFQUE_Pop(LockFreeQueue *queue, void *element, uint8 *pri);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif
#endif // LITE_LOCK_FREE_QUEUE_H
