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

#ifndef HI_STATE_MACHINE_H
#define HI_STATE_MACHINE_H

#include <pthread.h>
#include <vector>
#include <queue>

#include "hi_state.h"
#include "hi_state_machine_observer.h"
#include "message_looper.h"


namespace OHOS {
class HiStateMachine : public MessageHandler {
public:
    HiStateMachine();

    int32_t Init(uint32_t maxQueueSize, uint32_t maxMsgPayloadSize, const std::string smName);

    int32_t Deinit();

    virtual ~HiStateMachine();

    int32_t AddState(HiState &state);

    int32_t SetInitialState(HiState &state);

    const HiState *CurrentState();

    int32_t RegisterObserver(HiStateMachineObserver &observer);

    int32_t Start(void);

    int32_t Stop(void);

    /* handled immediately */
    int32_t Send(const MsgInfo &msg);

    /* handled immediately */
    int32_t Send(int32_t what);

    /* handled async */
    int32_t Post(const MsgInfo &msg, uint64_t delayUs);

    /* handled async */
    int32_t Post(int32_t what, uint64_t delayUs);

    int32_t RemoveEvent(const MsgInfo &msg);

private:
    int32_t OnMessageReceived(const MsgInfo &msg) override;
    bool StateExist(const HiState &state);
    void Transition(HiState &nextState);

private:
    MessageLooper *m_looper {nullptr};
    HiState *m_currentState {nullptr};
    std::vector<HiState *> m_allStates;
    HiStateMachineObserver *m_observer {nullptr};
    bool m_running {false};
};
};
#endif
