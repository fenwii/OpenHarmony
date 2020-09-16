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

#ifndef FSM_STATE_H
#define FSM_STATE_H

#include <string>
#include "hi_fsm.h"
#include "hi_state.h"

namespace OHOS {
class FsmState : public HiState {
public:
    FsmState(HI_FSM_StateHandleEvent event, HI_FSM_StateEnter enter, HI_FSM_StateExit exit, void *priv,
                 std::string name)
        : HiState(name), m_eventHandler(event), m_stateEnter(enter), m_stateExit(exit), m_privateDate(priv)
        {
        }

    virtual ~FsmState(){}

    int32_t HandleMessage(const MsgInfo &msg) override
    {
        if (m_eventHandler == nullptr) {
            return HI_FAILURE;
        }
        return m_eventHandler(m_privateDate, &msg);
    }

    int32_t Enter() override
    {
        if (m_stateEnter == nullptr) {
            return HI_FAILURE;
        }
        return m_stateEnter(m_privateDate, Name().c_str());
    }

    int32_t Exit() override
    {
        if (m_stateExit == nullptr) {
            return HI_FAILURE;
        }
        return m_stateExit(m_privateDate, Name().c_str());
    }

private:
    HI_FSM_StateHandleEvent m_eventHandler {nullptr};
    HI_FSM_StateEnter m_stateEnter {nullptr};
    HI_FSM_StateExit m_stateExit {nullptr};
    void *m_privateDate {nullptr};
};
};
#endif
