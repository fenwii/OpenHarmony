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

#include "hi_state_machine.h"

#include <cstdio>
#include <cstdlib>
#include <sys/prctl.h>
#include <unistd.h>
#include "fsm_common.h"
#include "media_log.h"

namespace OHOS {
HiStateMachine::HiStateMachine()
{
    m_looper = nullptr;
    m_currentState = nullptr;
    m_observer = nullptr;
    m_running = false;
    m_allStates.clear();
}

int32_t HiStateMachine::Deinit()
{
    int32_t ret = Stop();
    if (ret != HI_SUCCESS) {
        MEDIA_ERR_LOG("Stop err ");
    }
    m_allStates.clear();
    if (m_looper != nullptr) {
        ret = m_looper->Deinit();
        if (ret != HI_SUCCESS) {
            MEDIA_ERR_LOG("m_looper->Deinit err !");
        }
        delete m_looper;
        m_looper = nullptr;
    }
    return HI_SUCCESS;
}

int32_t HiStateMachine::Init(uint32_t maxQueueSize, uint32_t maxMsgPayloadSize, const std::string smName)
{
    if (m_looper != nullptr) {
        MEDIA_ERR_LOG("HiStateMachine::Init is init already !");
        return HI_SUCCESS;
    }
    m_running = false;
    m_looper = new (std::nothrow) MessageLooper(smName);
    if (m_looper == nullptr) {
        MEDIA_ERR_LOG("fail to create MessageLooper !");
        return HI_FAILURE;
    }
    if (m_looper->Init(maxQueueSize, maxMsgPayloadSize, smName) != HI_SUCCESS) {
        MEDIA_ERR_LOG("MessageLooper init error !");
        goto LOOPER_DEL;
    }
    if (m_looper->RegisterHandler(*this) != HI_SUCCESS) {
        MEDIA_ERR_LOG("fail to RegisterHandler !");
        goto LOOPER_DEINIT;
    }
    return HI_SUCCESS;

LOOPER_DEINIT:
    (void)m_looper->Deinit();
LOOPER_DEL:
    delete m_looper;
    m_looper = nullptr;
    return HI_FAILURE;
}

HiStateMachine::~HiStateMachine()
{
    (void)Deinit();
}

int32_t HiStateMachine::AddState(HiState &state)
{
    if (m_running) {
        MEDIA_ERR_LOG("can't addState when running");
        return HI_FAILURE;
    }
    if (!StateExist(state)) {
        m_allStates.push_back(&state);
    } else {
        MEDIA_ERR_LOG("state already exist");
        return HI_FAILURE;
    }
    return HI_SUCCESS;
}

int32_t HiStateMachine::RegisterObserver(HiStateMachineObserver &observer)
{
    if (m_running) {
        MEDIA_ERR_LOG("can't registerObserver when running");
        return HI_FAILURE;
    }
    m_observer = &observer;
    return HI_SUCCESS;
}

int32_t HiStateMachine::SetInitialState(HiState &state)
{
    if (m_running) {
        MEDIA_ERR_LOG("can't set initstae when running");
        return HI_FAILURE;
    }

    if (StateExist(state)) {
        m_currentState = &state;
    } else {
        MEDIA_ERR_LOG("init state not exist:%s", state.Name().c_str());
        return HI_FAILURE;
    }
    return HI_SUCCESS;
}

const HiState *HiStateMachine::CurrentState()
{
    return m_currentState;
}

void HiStateMachine::Transition(HiState &nextState)
{
    if (m_currentState == nullptr) {
        MEDIA_ERR_LOG("m_currentState == nullptr");
        return;
    }
    if (StateExist(nextState)) {
        m_currentState->Exit();
        nextState.Enter();
        m_currentState = &nextState;
    } else {
        MEDIA_ERR_LOG("transition state not exist:%s", nextState.Name().c_str());
    }
}

int32_t HiStateMachine::Start()
{
    if (m_running) {
        MEDIA_ERR_LOG("already running");
        return HI_FAILURE;
    }
    if (m_currentState == nullptr) {
        MEDIA_ERR_LOG("initstate not set");
        return HI_FAILURE;
    }
    if (m_looper == nullptr) {
        MEDIA_ERR_LOG("mlooper is nullptr !");
        return HI_FAILURE;
    }
    int32_t ret = m_looper->Start();
    if (ret != HI_SUCCESS) {
        return HI_FAILURE;
    }
    m_running = true;
    return HI_SUCCESS;
}

int32_t HiStateMachine::Stop()
{
    int32_t ret = HI_SUCCESS;
    if (m_running) {
        if (m_looper == nullptr) {
            MEDIA_ERR_LOG("mlooper is nullptr !");
            return HI_FAILURE;
        }
        ret = m_looper->Stop();
        m_running = false;
    }
    return ret;
}

int32_t HiStateMachine::Send(const MsgInfo &msg)
{
    if (m_looper == nullptr) {
        MEDIA_ERR_LOG("mlooper is nullptr !");
        return HI_FAILURE;
    }
    return m_looper->Send(msg);
}

int32_t HiStateMachine::Send(int32_t what)
{
    MsgInfo msg;
    msg.what = what;
    msg.arg1 = 0;
    msg.arg2 = 0;
    msg.msgData = nullptr;
    msg.msgDataLen = 0;
    msg.isNeedReply = false;
    msg.privDate = nullptr;
    msg.msgCallback = nullptr;
    if (m_looper == nullptr) {
        MEDIA_ERR_LOG("mlooper is nullptr !");
        return HI_FAILURE;
    }
    return m_looper->Send(msg);
}

int32_t HiStateMachine::Post(const MsgInfo &msg, uint64_t delayUs)
{
    if (!m_running) {
        MEDIA_ERR_LOG("post fail: FSM stoped");
        return HI_FAILURE;
    }
    if (m_looper == nullptr) {
        MEDIA_ERR_LOG("mlooper is nullptr !");
        return HI_FAILURE;
    }
    return m_looper->Post(msg, delayUs);
}

int32_t HiStateMachine::Post(int32_t what, uint64_t delayUs)
{
    MsgInfo msg;
    msg.what = what;
    msg.arg1 = 0;
    msg.arg2 = 0;
    msg.msgData = nullptr;
    msg.msgDataLen = 0;
    msg.isNeedReply = false;  // no requirment to reply by now, should check it in the future
    msg.privDate = nullptr;
    msg.msgCallback = nullptr;
    if (!m_running) {
        MEDIA_ERR_LOG("post fail: FSM stoped");
        return HI_FAILURE;
    }
    if (m_looper == nullptr) {
        MEDIA_ERR_LOG("mlooper is nullptr !");
        return HI_FAILURE;
    }
    return m_looper->Post(msg, delayUs);
}

int32_t HiStateMachine::RemoveEvent(const MsgInfo &msg)
{
    if (!m_running) {
        MEDIA_ERR_LOG("removeEvent fail: FSM stoped");
        return HI_FAILURE;
    }
    if (m_looper == nullptr) {
        MEDIA_ERR_LOG("mlooper is nullptr !");
        return HI_FAILURE;
    }
    m_looper->RemoveMessage(msg);
    return HI_SUCCESS;
}

int32_t HiStateMachine::OnMessageReceived(const MsgInfo &msg)
{
    if (m_currentState == nullptr) {
        MEDIA_ERR_LOG("initstate not set");
        return HI_FAILURE;
    }
    int32_t ret = m_currentState->HandleMessage(msg);
    if (ret == HI_SUCCESS) {
        HiState *nextState = m_currentState->FindTransition(msg.what);
        if (nextState != nullptr) {
            Transition(*nextState);
        }
    }

    if (m_observer != nullptr) {
        m_observer->OnEventHandled(*this, msg.what, ret);
    }
    return ret;
}

bool HiStateMachine::StateExist(const HiState &state)
{
    std::vector<HiState *>::iterator it;

    for (it = m_allStates.begin(); it != m_allStates.end(); it++) {
        if (*it == &state || (*it)->Name() == state.Name()) {
            return true;
        }
    }
    return false;
}
};
