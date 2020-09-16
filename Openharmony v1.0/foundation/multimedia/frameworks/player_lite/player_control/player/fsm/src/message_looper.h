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

#ifndef AVPLAY_MESSAGE_LOOPER_H
#define AVPLAY_MESSAGE_LOOPER_H
#include <pthread.h>
#include <list>
#include <string>
#include "message_handler.h"
#include "message.h"
#include "mmessage_pool.h"

namespace OHOS {
struct MsgEvent {
    MsgInfo *msg;
    uint64_t whenUs;
};

class MessageLooper {
public:
    explicit MessageLooper(std::string name);
    int32_t Init(uint32_t maxQueueSize, uint32_t msgPayloadLen, std::string name);
    int32_t Deinit();
    virtual ~MessageLooper();
    int32_t RegisterHandler(MessageHandler &handler);
    int32_t Start();
    int32_t Stop();
    int32_t Send(const MsgInfo &msg);
    int32_t Post(const MsgInfo &msg, uint64_t delayUs);
    bool HasMessage(const MsgInfo &msg);
    void RemoveMessage(const MsgInfo &msg);
    void Dump();
    MessageLooper(const MessageLooper &) = delete;
    MessageLooper &operator=(const MessageLooper &) = delete;

private:
    static void *Looper(void *args);
    void QueueHandlr();
    void InsertQueue(MsgInfo &msg, uint64_t delayUs);
    void LockHandler();
    void UnlockHandler();

private:
    MessageHandler *m_msgHandlr = nullptr;
    bool m_isThreadRunning = false;
    std::list<MsgEvent> m_eventQueue;
    pthread_cond_t m_queueCondition = PTHREAD_COND_INITIALIZER;
    pthread_mutex_t m_queueLock = PTHREAD_MUTEX_INITIALIZER;
    pthread_t m_loopThrd = 0;
    std::string m_name;
    pthread_mutex_t m_handlerMutex = PTHREAD_MUTEX_INITIALIZER;
    bool m_isInited = false;
    MMessagePool *m_msgPool = nullptr;
};
};
#endif  // AVPLAY_MESSAGE_LOOPER_H
