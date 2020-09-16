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
#include "queue_adapter.h"
#include <ohos_errno.h>
#include <pthread.h>
#include "memory_adapter.h"
#include "lock_free_queue.h"

typedef struct LockFreeBlockQueue LockFreeBlockQueue;
struct LockFreeBlockQueue {
    pthread_mutex_t wMutex;
    pthread_mutex_t rMutex;
    pthread_cond_t cond;
    LockFreeQueue *queue;
};

MQueueId QUEUE_Create(const char *name, int size, int count)
{
    LockFreeBlockQueue *queue = (LockFreeBlockQueue *)SAMGR_Malloc(sizeof(LockFreeBlockQueue));
    if (queue == NULL) {
        return NULL;
    }
    queue->queue = LFQUE_Create(size, count);
    if (queue->queue == NULL) {
        SAMGR_Free(queue);
        return NULL;
    }
    pthread_mutex_init(&queue->wMutex, NULL);
    pthread_mutex_init(&queue->rMutex, NULL);
    pthread_cond_init(&queue->cond, NULL);
    return (MQueueId)queue;
}

int QUEUE_Put(MQueueId queueId, const void *element, uint8 pri, int timeout)
{
    if (queueId == NULL || element == NULL || timeout > 0) {
        return EC_INVALID;
    }
    LockFreeBlockQueue *queue = (LockFreeBlockQueue *)queueId;
    pthread_mutex_lock(&queue->wMutex);
    int ret = LFQUE_Push(queue->queue, element, pri);
    pthread_mutex_unlock(&queue->wMutex);
    pthread_mutex_lock(&queue->rMutex);
    pthread_cond_signal(&queue->cond);
    pthread_mutex_unlock(&queue->rMutex);
    return ret;
}

int QUEUE_Pop(MQueueId queueId, void *element, uint8 *pri, int timeout)
{
    if (queueId == NULL || element == NULL || timeout > 0) {
        return EC_INVALID;
    }

    LockFreeBlockQueue *queue = (LockFreeBlockQueue *)queueId;
    if (LFQUE_Pop(queue->queue, element, pri) == EC_SUCCESS) {
        return EC_SUCCESS;
    }

    pthread_mutex_lock(&queue->rMutex);
    while (LFQUE_Pop(queue->queue, element, pri) != EC_SUCCESS) {
        pthread_cond_wait(&queue->cond, &queue->rMutex);
    }
    pthread_mutex_unlock(&queue->rMutex);
    return EC_SUCCESS;
}

int QUEUE_Destroy(MQueueId queueId)
{
    if (queueId == NULL) {
        return EC_INVALID;
    }

    LockFreeBlockQueue *queue = (LockFreeBlockQueue *)queueId;
    pthread_mutex_destroy(&queue->wMutex);
    pthread_mutex_destroy(&queue->rMutex);
    pthread_cond_destroy(&queue->cond);
    SAMGR_Free(queue->queue);
    SAMGR_Free(queue);
    return EC_SUCCESS;
}