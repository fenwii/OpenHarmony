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
#include "message_inner.h"
#include <ohos_errno.h>
#include <log.h>
#include "memory_adapter.h"
#include "queue_adapter.h"
#include "securec.h"
#include "task_manager.h"

#undef LOG_TAG
#undef LOG_DOMAIN
#define LOG_TAG "Samgr"
#define LOG_DOMAIN 0xD001800

#define DONT_WAIT 0
#define WAIT_FOREVER (-1)
static int32 SharedSend(MQueueId queueId, Exchange *exchange);
static BOOL FreeReference(Exchange *exchange);

int32 SAMGR_SendRequest(const Identity *identity, const Request *request, Handler handler)
{
    if (request == NULL || identity == NULL) {
        return EC_INVALID;
    }

    Exchange exchange = {*identity, *request, {NULL, 0}, MSG_NON, handler, NULL};
    exchange.id.queueId = NULL;
    if (handler != NULL) {
        exchange.id.queueId = SAMGR_GetCurrentQueueID();
        exchange.type = MSG_CON;
    }

    return QUEUE_Put(identity->queueId, &exchange, 0, DONT_WAIT);
}

int32 SAMGR_SendResponse(const Request *request, const Response *response)
{
    // we need send the default the con message or not?
    if (request == NULL) {
        return EC_INVALID;
    }

    Exchange *exchange = GET_OBJECT(request, Exchange, request);
    if (exchange->type == MSG_NON) {
        return EC_INVALID;
    }

    if (exchange->handler == NULL) {
        return EC_SUCCESS;
    }

    exchange->type = MSG_ACK;
    exchange->response.data = NULL;
    exchange->response.len = 0;
    if (response != NULL) {
        exchange->response = *response;
    }

    // If there is no task queue, we will call the response processor in current task.
    if (exchange->id.queueId == NULL) {
        exchange->handler(&exchange->request, &exchange->response);
        return EC_SUCCESS;
    }

    // Send back to the origin to process the task.
    int32 ret = SharedSend(exchange->id.queueId, exchange);
    if (ret != EC_SUCCESS) {
        exchange->handler(&exchange->request, &exchange->response);
        (void)FreeReference(exchange);
    }
    return EC_SUCCESS;
}

int32 SAMGR_MsgRecv(MQueueId queueId, uint8 *interMsg, uint32 size)
{
    if (queueId == NULL || interMsg == NULL || size == 0) {
        return EC_INVALID;
    }

    if (memset_s(interMsg, size, 0x00, size) != EOK) {
        return EC_FAILURE;
    }

    return QUEUE_Pop(queueId, interMsg, 0, WAIT_FOREVER);
}

int32 SAMGR_FreeMsg(Exchange *exchange)
{
    if (!FreeReference(exchange)) {
        return EC_SUCCESS;
    }

    if (exchange->request.len > 0) {
        SAMGR_Free(exchange->request.data);
        exchange->request.data = NULL;
    }

    if (exchange->response.len > 0) {
        SAMGR_Free(exchange->response.data);
        exchange->response.data = NULL;
    }
    return EC_SUCCESS;
}

uint32 *SAMGR_SendSharedRequest(const Identity *identity, const Request *request, uint32 *token, Handler handler)
{
    if (identity == NULL || request == NULL) {
        return NULL;
    }
    Exchange exchange = {*identity, *request, {NULL, 0}, MSG_NON, handler, token};
    exchange.type = (handler == NULL) ? MSG_NON : MSG_CON;
    exchange.id.queueId = NULL;
    int32 err = SharedSend(identity->queueId, &exchange);
    if (err != EC_SUCCESS) {
        HILOG_ERROR(HILOG_MODULE_SAMGR, "SharedSend [%p] failed(%d)!", identity->queueId, err);
        (void)FreeReference(&exchange);
    }
    return exchange.sharedRef;
}

int32 SAMGR_SendSharedDirectRequest(const Identity *id, const Request *req, const Response *resp, uint32 **ref,
                                    Handler handler)
{
    if (handler == NULL || ref == NULL) {
        return EC_INVALID;
    }

    Exchange exchange = {0};
    if (req != NULL) {
        exchange.request = *req;
    }

    if (resp != NULL) {
        exchange.response = *resp;
    }

    exchange.handler = handler;
    exchange.sharedRef = *ref;
    exchange.type = MSG_DIRECT;
    exchange.id = *id;
    exchange.id.queueId = NULL;
    int32 err = SharedSend(id->queueId, &exchange);
    if (err != EC_SUCCESS) {
        HILOG_ERROR(HILOG_MODULE_SAMGR, "SharedSend [%p] failed(%d)!", id->queueId, err);
        (void)FreeReference(&exchange);
    }
    *ref = exchange.sharedRef;
    return err;
}

int32 SAMGR_SendResponseByIdentity(const Identity *id, const Request *request, const Response *response)
{
    // we need send the default the con message or not?
    if (request == NULL || id == NULL) {
        return EC_INVALID;
    }

    Exchange *exchange = GET_OBJECT(request, Exchange, request);
    if (exchange->type == MSG_NON) {
        return EC_INVALID;
    }
    exchange->id.queueId = id->queueId;

    return SAMGR_SendResponse(request, response);
}

static int32 SharedSend(MQueueId queueId, Exchange *exchange)
{
    /* if the msg data and response is NULL, we just direct copy, no need shared the message. */
    if ((exchange->request.data == NULL || exchange->request.len <= 0) &&
        (exchange->response.data == NULL || exchange->response.len <= 0)) {
        return QUEUE_Put(queueId, exchange, 0, DONT_WAIT);
    }

    /* 1.add reference */
    MUTEX_GlobalLock();
    if (exchange->sharedRef == NULL) {
        exchange->sharedRef = (uint32 *)SAMGR_Malloc(sizeof(uint32));
        if (exchange->sharedRef == NULL) {
            MUTEX_GlobalUnlock();
            return EC_NOMEMORY;
        }
        *(exchange->sharedRef) = 0;
    }
    (*(exchange->sharedRef))++;
    MUTEX_GlobalUnlock();

    return QUEUE_Put(queueId, exchange, 0, DONT_WAIT);
}

static BOOL FreeReference(Exchange *exchange)
{
    if (exchange == NULL) {
        return FALSE;
    }

    BOOL needFree = TRUE;
    /* 1. check the shared reference */
    MUTEX_GlobalLock();
    if (exchange->sharedRef != NULL) {
        if (*(exchange->sharedRef) > 0) {
            (*(exchange->sharedRef))--;
        }

        if (*(exchange->sharedRef) > 0) {
            needFree = FALSE;
        }
    }
    MUTEX_GlobalUnlock();

    if (needFree) {
        SAMGR_Free(exchange->sharedRef);
        exchange->sharedRef = NULL;
    }
    return needFree;
}