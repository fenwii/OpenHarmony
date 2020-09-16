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

#ifndef HI_STATE_H
#define HI_STATE_H

#include <string>
#include <vector>
#include <map>
#include "message.h"

namespace OHOS {
class HiState {
public:
    explicit HiState(std::string name);
    virtual ~HiState();

    virtual void AddTransition(int32_t event, HiState &state);

    virtual HiState *FindTransition(int32_t event);

    virtual int32_t HandleMessage(const MsgInfo &msg) = 0;

    virtual int32_t Enter();

    virtual int32_t Exit();

    std::string Name() const;

    bool operator==(const HiState &state);

    friend class HiStateMachine;

private:
    std::map<int32_t, HiState *> m_transitionMap;
    std::string m_name;
};
};

#endif  // HI_STATE_H
