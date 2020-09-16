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
#ifndef LITE_MESSAGEINNER_H
#define LITE_MESSAGEINNER_H

#include "message.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

enum ExchangeType {
    MSG_EXIT = -1,
    MSG_NON = 0,
    MSG_CON = 1,
    MSG_ACK = 2,
    MSG_SYNC = 3,
    MSG_DIRECT = 4,
};
// Will be used for message interaction, so use one-byte alignment
#pragma pack(1)
typedef struct Exchange Exchange;
struct Exchange {
    Identity id; /**< The target service or feature identity. */
    Request request;
    Response response;
    short type;  /**< The exchange type. */
    Handler handler;   /**< async response or immediately request callback function */
    uint32 *sharedRef; /**< use to share the request and response for saving memory */
};
#pragma pack()

int32 SAMGR_MsgRecv(MQueueId queueId, uint8 *interMsg, uint32 size);

/**
 * The function just release the Message->data and Message->sharedRef(use free), not release the msg entry.
 * If you alloc the msg on the heep, you should release it by yourself, you`d better alloc on the stack.
 * The function will be called automatically.
 * Do not call this function manually, except the SM_SendRequest return error!
 *
 **/
int32 SAMGR_FreeMsg(Exchange *exchange);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif
#endif // LITE_MESSAGEINNER_H
