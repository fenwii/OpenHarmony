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
#include "lock_free_queue.h"
#include <ohos_errno.h>
#include <pthread.h>
#include <securec.h>
#include <memory_adapter.h>

LockFreeQueue *LFQUE_Create(int size, int count)
{
    if (size <= 0 || count <= 0) {
        return NULL;
    }

    int total = size * count + 1;
    if (total <= 0) {
        return NULL;
    }

    register LockFreeQueue *queue = (LockFreeQueue *)SAMGR_Malloc(sizeof(LockFreeQueue) + total);
    if (queue == NULL) {
        return NULL;
    }
    queue->write = 0;
    queue->read = 0;
    queue->itemSize = size;
    queue->totalSize = total;
    return queue;
}

BOOL LFQUE_IsFull(LockFreeQueue *queue)
{
    uint32 nextWrite = queue->write + 1;
    if (nextWrite >= queue->totalSize) {
        nextWrite = 0;
    }
    return (nextWrite == queue->read);
}

BOOL LFQUE_IsEmpty(LockFreeQueue *queue)
{
    return (queue->write == queue->read);
}

int LFQUE_Push(LockFreeQueue *queue, const void *element, uint8 pri)
{
    (void)pri;
    if (queue == NULL || element == NULL) {
        return EC_INVALID;
    }

    if (LFQUE_IsFull(queue)) {
        return EC_BUSBUSY;
    }
    uint32 copyLen = (queue->totalSize - queue->write < queue->itemSize) ?
                  (queue->totalSize - queue->write) : queue->itemSize;
    if (memcpy_s(&queue->buffer[queue->write], copyLen, element, copyLen) != EOK) {
        return EC_INVALID;
    }

    element += copyLen;
    copyLen = queue->itemSize - copyLen;
    if (copyLen > 0) {
        if (memcpy_s(queue->buffer, copyLen, element, copyLen) != EOK) {
            return EC_INVALID;
        }
    }

    uint32 write = queue->write + queue->itemSize;
    if (write >= queue->totalSize) {
        write = write - queue->totalSize;
    }
    queue->write = write;
    return EC_SUCCESS;
}

int LFQUE_Pop(LockFreeQueue *queue, void *element, uint8 *pri)
{
    (void)pri;
    if (queue == NULL || element == NULL) {
        return EC_INVALID;
    }
    if (LFQUE_IsEmpty(queue)) {
        return EC_FAILURE;
    }

    uint32 copyLen = (queue->totalSize - queue->read < queue->itemSize) ?
                  (queue->totalSize - queue->read) : queue->itemSize;
    if (memcpy_s(element, copyLen, &queue->buffer[queue->read], copyLen) != EOK) {
        return EC_FAILURE;
    }

    element += copyLen;
    copyLen = queue->itemSize - copyLen;
    if (copyLen > 0) {
        if (memcpy_s(element, copyLen, queue->buffer, copyLen) != EOK) {
            return EC_FAILURE;
        }
    }

    uint32 read = queue->read + queue->itemSize;
    if (read >= queue->totalSize) {
        read = read - queue->totalSize;
    }
    queue->read = read;
    return EC_SUCCESS;
}