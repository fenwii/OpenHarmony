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

#include "message_looper.h"

#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <cstring>
#include <iterator>
#include <sys/prctl.h>
#include <cerrno>
#include "media_log.h"
#include "fsm_common.h"

namespace OHOS {
#if (defined(__HuaweiLite__) || defined(__OHOS__))
const uint32_t MSGLOOPER_LITEOS_STACK_SIZE = 0x10000;
#endif
const uint32_t MSGLOOPER_EMPTY_WAIT_TIME_US = 200 * 1000; /* empty wait time is 200 ms, namely 200 * 1000 us */

MessageLooper::MessageLooper(std::string name) : m_name(name)
{
    m_eventQueue.clear();
}

MessageLooper::~MessageLooper()
{
    (void)Deinit();
}

int32_t MessageLooper::Deinit()
{
    int32_t ret = HI_SUCCESS;
    if (m_isInited) {
        ret = Stop();
        if (ret != HI_SUCCESS) {
            MEDIA_ERR_LOG("MessageLooper Stop error");
        }
        m_eventQueue.clear();
        delete m_msgPool;
        m_msgPool = nullptr;
        (void)pthread_mutex_destroy(&m_handlerMutex);
        (void)pthread_cond_destroy(&m_queueCondition);
        (void)pthread_mutex_destroy(&m_queueLock);
        m_isInited = false;
    }
    return ret;
}

int32_t MessageLooper::Init(uint32_t maxQueueSize, uint32_t msgPayloadLen, std::string name)
{
    if (m_isInited) {
        return HI_SUCCESS;
    }
    int32_t ret = pthread_mutex_init(&m_handlerMutex, nullptr);
    if (ret != HI_SUCCESS) {
        MEDIA_ERR_LOG("pthread_mutex_init m_handlerMutex error");
        return HI_FAILURE;
    }
    ret = pthread_mutex_init(&m_queueLock, nullptr);
    if (ret != HI_SUCCESS) {
        MEDIA_ERR_LOG("pthread_mutex_init m_queueLock error");
        goto MUTEX_DEL;
    }
    FsmCondInitRelative(m_queueCondition);
    m_msgPool = new (std::nothrow) MMessagePool(name);
    if (m_msgPool == nullptr) {
        MEDIA_ERR_LOG("create m_msgPool faileld");
        goto COND_DEL;
    }
    if (m_msgPool->Init(maxQueueSize, msgPayloadLen) != HI_SUCCESS) {
        goto DEL_MSGPOOL;
    }
    m_isInited = true;
    return HI_SUCCESS;

DEL_MSGPOOL:
    delete m_msgPool;
    m_msgPool = nullptr;
COND_DEL:
    (void)pthread_cond_destroy(&m_queueCondition);
    (void)pthread_mutex_destroy(&m_queueLock);
MUTEX_DEL:
    (void)pthread_mutex_destroy(&m_handlerMutex);
    return HI_FAILURE;
}

int32_t MessageLooper::RegisterHandler(MessageHandler &handler)
{
    if (m_isThreadRunning) {
        MEDIA_ERR_LOG("looper be in running, do not support reg handlr");
        return HI_FAILURE;
    }
    m_msgHandlr = &handler;
    return HI_SUCCESS;
}

void *MessageLooper::Looper(void *args)
{
    MessageLooper *looper = static_cast<MessageLooper *>(args);
    if (looper == nullptr) {
        MEDIA_ERR_LOG("looper is null");
        return nullptr;
    }
    looper->QueueHandlr();
    return nullptr;
}

int32_t MessageLooper::Start()
{
    if (m_isThreadRunning) {
        MEDIA_ERR_LOG("looper already be running");
        return HI_SUCCESS;
    }

    if (m_msgHandlr == nullptr) {
        MEDIA_ERR_LOG("no message handlr be registered");
        return HI_FAILURE;
    }

    m_isThreadRunning = true;
#if (defined(__HuaweiLite__) || defined(__OHOS__))
    pthread_attr_t attr;

    pthread_attr_init(&attr);
    pthread_attr_setstacksize(&attr, MSGLOOPER_LITEOS_STACK_SIZE);
    int32_t ret = pthread_create(&m_loopThrd, &attr, Looper, this);
#else
    int32_t ret = pthread_create(&m_loopThrd, nullptr, Looper, this);
#endif
    if (ret != 0) {
        MEDIA_ERR_LOG("pthread_create failed %d", ret);
#if (defined(__HuaweiLite__) || defined(__OHOS__))
        pthread_attr_destroy(&attr);
#endif
        m_isThreadRunning = false;
        return HI_FAILURE;
    }

#if (defined(__HuaweiLite__) || defined(__OHOS__))
    pthread_attr_destroy(&attr);
#endif

    return HI_SUCCESS;
}

int32_t MessageLooper::Stop()
{
    int32_t ret = HI_SUCCESS;
    if (m_isThreadRunning) {
        FSM_LOCK(m_queueLock);
        m_isThreadRunning = false;
        (void)pthread_cond_broadcast(&m_queueCondition);
        FSM_UNLOCK(m_queueLock);
        pthread_join(m_loopThrd, nullptr);
        FSM_LOCK(m_queueLock);
        if (!m_eventQueue.empty()) {
            MEDIA_ERR_LOG("%s have msg in queue, could not stop error", m_name.c_str());
            ret = HI_FAILURE;
        }
        FSM_UNLOCK(m_queueLock);
    }
    if (m_msgPool != nullptr) {
        m_msgPool->Dump();
    }
    return ret;
}

void MessageLooper::QueueHandlr()
{
    int32_t ret = HI_SUCCESS;

    prctl(PR_SET_NAME, m_name.c_str(), 0, 0, 0);

    while (m_isThreadRunning) {
        FSM_LOCK(m_queueLock);
        if (!m_isThreadRunning) { // must check value again inside lock
            MEDIA_INFO_LOG("%s will stop", m_name.c_str());
            FSM_UNLOCK(m_queueLock);
            break;
        }
        if (m_eventQueue.empty()) {
            FsmCondTimewait(m_queueCondition, m_queueLock, MSGLOOPER_EMPTY_WAIT_TIME_US);
            FSM_UNLOCK(m_queueLock);
            continue;
        }

        uint64_t whenUs = (*m_eventQueue.begin()).whenUs;
        uint64_t nowUs = FsmGetCurTimeUs();
        if (whenUs > nowUs) {
            uint32_t delayUs = (uint32_t)(whenUs - nowUs);
            ret = FsmCondTimewait(m_queueCondition, m_queueLock, delayUs);
            if (ret != ETIMEDOUT && ret != HI_SUCCESS) {
                MEDIA_INFO_LOG("FSM_Cond_Timewait err: %d", ret);
            }
            FSM_UNLOCK(m_queueLock);
            continue;
        }

        MsgEvent event = *m_eventQueue.begin();
        m_eventQueue.erase(m_eventQueue.begin());

        FSM_UNLOCK(m_queueLock);

        LockHandler();
        if (m_msgHandlr == nullptr || m_msgPool == nullptr) {
            MEDIA_INFO_LOG("msghandler or m_msgPool is null");
            UnlockHandler();
            break;
        }
        m_msgHandlr->OnMessageReceived(*(event.msg));
        UnlockHandler();

        // statemachine.post() set isNeedReply=false, for there is no requirment by now.
        if (event.msg->isNeedReply && event.msg->msgCallback) {
            event.msg->msgCallback(event.msg->privDate);
        }

        m_msgPool->PutMsg(*(event.msg));
    }
}

int32_t MessageLooper::Send(const MsgInfo &msg)
{
    LockHandler();
    if (m_msgHandlr == nullptr) {
        MEDIA_INFO_LOG("no message handlr be registered");
        UnlockHandler();
        return HI_FAILURE;
    }
    int32_t ret = m_msgHandlr->OnMessageReceived(msg);
    UnlockHandler();

    return ret;
}

int32_t MessageLooper::Post(const MsgInfo &msg, uint64_t delayUs)
{
    if (!m_isThreadRunning) {
        MEDIA_ERR_LOG("post failed, looper is stoped");
        return HI_FAILURE;
    }
    if (m_msgPool == nullptr) {
        MEDIA_ERR_LOG("msgPool is null");
        return HI_FAILURE;
    }
    MsgInfo *msgInfo = m_msgPool->GetMsg(msg);
    if (msgInfo == nullptr) {
        MEDIA_ERR_LOG("getMsg err");
        return HI_FAILURE;
    }

    msgInfo->isNeedReply = false;
    InsertQueue(*msgInfo, delayUs);

    return HI_SUCCESS;
}

void MessageLooper::InsertQueue(MsgInfo &msg, uint64_t delayUs)
{
    uint64_t curUs = FsmGetCurTimeUs();
    uint64_t whenUs = (delayUs > 0) ? (curUs + delayUs) : curUs;

    FSM_LOCK(m_queueLock);

    MsgEvent event{&msg, whenUs};

    if (m_eventQueue.empty()) {
        m_eventQueue.push_back(event);
        FSM_COND_SIGNAL(m_queueCondition);
    } else {
        std::list<MsgEvent>::iterator it = m_eventQueue.begin();
        while (it != m_eventQueue.end() && (*it).whenUs <= whenUs) {
            ++it;
        }

        m_eventQueue.insert(it, event);

        if (it == m_eventQueue.begin()) {
            FSM_COND_SIGNAL(m_queueCondition);
        }
    }

    FSM_UNLOCK(m_queueLock);
}

bool MessageLooper::HasMessage(const MsgInfo &msg)
{
    bool isHasMsg = false;

    FSM_LOCK(m_queueLock);

    std::list<MsgEvent>::iterator it = m_eventQueue.begin();
    while (it != m_eventQueue.end()) {
        if (it->msg->what == msg.what) {
            isHasMsg = true;
            break;
        }
        ++it;
    }

    FSM_UNLOCK(m_queueLock);
    return isHasMsg;
}

void MessageLooper::RemoveMessage(const MsgInfo &msg)
{
    MsgEvent event = { nullptr, 0 };
    bool isFound = false;

    FSM_LOCK(m_queueLock);

    std::list<MsgEvent>::iterator it = m_eventQueue.begin();
    while (it != m_eventQueue.end()) {
        if (it->msg->what == msg.what) {
            event = *it;
            m_eventQueue.erase(it);
            isFound = true;
            break;
        }
        ++it;
    }

    FSM_UNLOCK(m_queueLock);

    if (isFound && (m_msgPool != nullptr)) {
        MEDIA_INFO_LOG("%s remove msg: %d", m_name.c_str(), event.msg->what);
        m_msgPool->PutMsg(*(event.msg));
    }
}

void MessageLooper::Dump()
{
    FSM_LOCK(m_queueLock);

    MEDIA_INFO_LOG(
                  "looper[%s], msg cnt: %zd", m_name.c_str(), m_eventQueue.size());
    std::list<MsgEvent>::iterator it = m_eventQueue.begin();
    while (it != m_eventQueue.end()) {
        MEDIA_INFO_LOG("msg id[%d], handleWhen[%llu]", it->msg->what, it->whenUs);
        ++it;
    }
    FSM_UNLOCK(m_queueLock);
    if (m_msgPool != nullptr) {
        m_msgPool->Dump();
    }
}

void MessageLooper::LockHandler()
{
    pthread_mutex_lock(&m_handlerMutex);
}

void MessageLooper::UnlockHandler()
{
    pthread_mutex_unlock(&m_handlerMutex);
}
};
