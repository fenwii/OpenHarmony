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

#ifndef FSM_OBERVER_H
#define FSM_OBERVER_H
#include <list>
#include <string>
#include "hi_fsm.h"
#include "hi_state_machine.h"

using OHOS::HiStateMachineObserver;
using OHOS::HiStateMachine;
using OHOS::FsmState;

namespace OHOS {
class FsmOberver : public HiStateMachineObserver {
public:
    FsmOberver(HI_FSM_EventCallback msgCallback, void *priv)
        : m_eventCallback(msgCallback), m_privateDate(priv)
    {
    }

    ~FsmOberver()
    {
    }

    void OnEventHandled(const HiStateMachine &stateMachine, int32_t event, int32_t result) override
    {
        HiStateMachine *instance = const_cast<HiStateMachine *>(&stateMachine);
        if (m_eventCallback != nullptr) {
            m_eventCallback(instance, m_privateDate, event, result);
        }
    }

private:
    HI_FSM_EventCallback m_eventCallback;
    void *m_privateDate;
};
}
#endif
