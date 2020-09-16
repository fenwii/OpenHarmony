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
#include "task_manager.h"
#include <securec.h>
#include <log.h>
#include <ohos_errno.h>
#include "memory_adapter.h"
#include "time_adapter.h"
#include "queue_adapter.h"
#include "service_impl.h"
#include "message_inner.h"
#include "samgr_lite_inner.h"

#undef LOG_TAG
#undef LOG_DOMAIN
#define LOG_TAG "Samgr"
#define LOG_DOMAIN 0xD001800

#define DONT_WAIT 0
static void BeginWork(ServiceImpl *service);
static void EndWork(ServiceImpl *service, const Exchange *exchange);
static void *TaskEntry(void *);
static void ProcRequest(Exchange *exchange, ServiceImpl *serviceImpl);
static void ProcDirectRequest(Exchange *exchange);
static void ProcResponse(Exchange *exchange);
static ServiceImpl *CorrectServiceImpl(Exchange *exchange, ServiceImpl *serviceImpl);

TaskPool *SAMGR_CreateFixedTaskPool(const TaskConfig *config, const char *name, uint8 size)
{
    if (config == NULL || size == 0 || MAX_TASK_SIZE <= THREAD_Total()) {
        return NULL;
    }

    MQueueId queueId = (MQueueId)QUEUE_Create(name, sizeof(Exchange), config->queueSize);
    if (queueId == NULL) {
        HILOG_ERROR(HILOG_MODULE_SAMGR, "Create Queue<%s> size:%d failed!", name, config->queueSize);
        return NULL;
    }

    TaskPool *taskPool = (TaskPool *)SAMGR_Malloc(sizeof(TaskPool) + sizeof(ThreadId) * size);
    if (taskPool == NULL) {
        HILOG_ERROR(HILOG_MODULE_SAMGR, "Create TaskPool<%s> size:%d failed!", name, config->queueSize);
        QUEUE_Destroy(queueId);
        return NULL;
    }

    (void)memset_s(taskPool, sizeof(TaskPool) + sizeof(ThreadId) * size, 0,
                   sizeof(TaskPool) + sizeof(ThreadId) * size);
    taskPool->queueId = queueId;
    taskPool->stackSize = config->stackSize;
    taskPool->priority = (uint8)config->priority;
    taskPool->size = size;
    taskPool->top = 0;
    taskPool->ref = 1;
    return taskPool;
}

int32 SAMGR_StartTaskPool(TaskPool *pool, const char *name)
{
    if (pool == NULL) {
        return EC_INVALID;
    }

    if (pool->top > 0) {
        return EC_SUCCESS;
    }

    ThreadAttr attr = {name, pool->stackSize, pool->priority, 0, 0};
    while (pool->top < pool->size) {
        register ThreadId threadId = (ThreadId)THREAD_Create(TaskEntry, pool->queueId, &attr);
        if (threadId == NULL) {
            HILOG_ERROR(HILOG_MODULE_SAMGR, "Start Task<%s, %d, %d> failed!", name, pool->stackSize, pool->priority);
            break;
        }
        pool->tasks[pool->top] = threadId;
        ++(pool->top);
    }
    return EC_SUCCESS;
}

int32 SAMGR_ReleaseTaskPool(TaskPool *pool)
{
    if (pool == NULL) {
        return EC_INVALID;
    }

    pool->ref--;
    if (pool->ref == 0) {
        Exchange exchange = {0};
        exchange.type = MSG_EXIT;
        QUEUE_Put(pool->queueId, &exchange, 0, DONT_WAIT);
        SAMGR_Free(pool);
    }
    return EC_SUCCESS;
}

TaskPool *SAMGR_ReferenceTaskPool(TaskPool *pool)
{
    if (pool == NULL) {
        return NULL;
    }

    if (pool->ref >= MAX_REF_NUM) {
        return NULL;
    }

    pool->ref++;
    return pool;
}

static void *TaskEntry(void *argv)
{
    ServiceImpl *serviceImpl = NULL;
    THREAD_SetThreadLocal(argv);
    while (TRUE) {
        Exchange exchange;
        uint32 msgRcvRet = SAMGR_MsgRecv((MQueueId)argv, (uint8 *)&exchange, sizeof(Exchange));
        if (msgRcvRet != EC_SUCCESS) {
            continue;
        }

        if (exchange.type == MSG_EXIT) {
            SAMGR_FreeMsg(&exchange);
            break;
        }

        serviceImpl = CorrectServiceImpl(&exchange, serviceImpl);
        BeginWork(serviceImpl);
        ProcResponse(&exchange);
        ProcDirectRequest(&exchange);
        ProcRequest(&exchange, serviceImpl);
        EndWork(serviceImpl, &exchange);
        SAMGR_FreeMsg(&exchange);
    }
    QUEUE_Destroy((MQueueId)argv);
    return NULL;
}

static void ProcRequest(Exchange *exchange, ServiceImpl *serviceImpl)
{
    if (serviceImpl == NULL || exchange->type == MSG_ACK || exchange->type == MSG_DIRECT) {
        return;
    }

    DEFAULT_MessageHandle(serviceImpl, &(exchange->id), &(exchange->request));

    if (exchange->type == MSG_CON) {
        SAMGR_SendResponse(&exchange->request, &exchange->response);
    }
}

static void ProcResponse(Exchange *exchange)
{
    if (exchange->handler == NULL) {
        return;
    }

    if (exchange->type != MSG_ACK) {
        return;
    }

    exchange->handler(&exchange->request, &exchange->response);
}

static void ProcDirectRequest(Exchange *exchange)
{
    if (exchange->handler == NULL) {
        return;
    }

    if (exchange->type != MSG_DIRECT) {
        return;
    }

    exchange->handler(&exchange->request, &exchange->response);
}

static ServiceImpl *CorrectServiceImpl(Exchange *exchange, ServiceImpl *serviceImpl)
{
    if (exchange->type == MSG_ACK) {
        // The ack message use the last service.
        return serviceImpl;
    }

    if (serviceImpl == NULL || serviceImpl->serviceId != exchange->id.serviceId) {
        serviceImpl = SAMGR_GetServiceByID(exchange->id.serviceId);
    }

    if (serviceImpl == NULL) {
        return NULL;
    }

    return serviceImpl;
}

MQueueId SAMGR_GetCurrentQueueID()
{
    return (MQueueId)THREAD_GetThreadLocal();
}

static void BeginWork(ServiceImpl *service)
{
    if (service == NULL || service->inited != SVC_IDLE) {
        return;
    }

    if (service->ops.step == BOOT_SYS_WAIT) {
        WDT_Start(MSG_PROC_THRESHOLD);
    }

    service->ops.messages++;
    service->ops.timestamp = SAMGR_GetProcessTime();
    service->inited = SVC_BUSY;
}

static void EndWork(ServiceImpl *service, const Exchange *exchange)
{
    if (service == NULL || service->inited != SVC_BUSY) {
        return;
    }

    if (service->ops.step == BOOT_SYS_WAIT) {
        WDT_Stop();
    }

    uint32 lastTime = service->ops.timestamp;
    service->ops.timestamp = (uint32)SAMGR_GetProcessTime();
    uint32 interval = GET_INTERVAL(lastTime, service->ops.timestamp);
    if (interval > MSG_PROC_THRESHOLD) {
        const char *name = service->service->GetName(service->service);
        HILOG_INFO(HILOG_MODULE_SAMGR, "Message Timeout <service:%s, feature:%d, type:%d, reqId:%d, time:%ums>",
                   name, exchange->id.featureId, exchange->type, exchange->request.msgId, interval);
        service->ops.abnormal++;
    }
    service->inited = SVC_IDLE;
}
