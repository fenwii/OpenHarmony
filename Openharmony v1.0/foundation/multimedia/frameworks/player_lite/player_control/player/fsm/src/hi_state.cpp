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

#include "hi_state.h"

#include <cstdio>

namespace OHOS {
HiState::HiState(std::string name) : m_name(name)
{
}

HiState::~HiState()
{
    m_transitionMap.clear();
}

void HiState::AddTransition(int32_t event, HiState &state)
{
    m_transitionMap.insert(std::pair<int32_t, HiState *>(event, &state));
}

HiState *HiState::FindTransition(int32_t event)
{
    std::map<int32_t, HiState *>::iterator it;

    it = m_transitionMap.find(event);
    if (it == m_transitionMap.end()) {
        return nullptr;
    }

    return it->second;
}

std::string HiState::Name() const
{
    return m_name;
}

bool HiState::operator==(const HiState &state)
{
    if (m_name == state.Name()) {
        return true;
    } else {
        return false;
    }
}

int32_t HiState::Enter()
{
    return 0;
}

int32_t HiState::Exit()
{
    return 0;
}
};
