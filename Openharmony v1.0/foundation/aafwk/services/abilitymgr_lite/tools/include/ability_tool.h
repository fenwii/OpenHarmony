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

#ifndef OHOS_ABILITY_TOOL_H
#define OHOS_ABILITY_TOOL_H

#include <iproxy_client.h>
#include "liteipc_adapter.h"
#include "want.h"

namespace OHOS {
class AbilityTool {
public:
    AbilityTool() = default;
    ~AbilityTool();
    bool SetBundleName(const char *bundleName);
    bool SetAbilityName(const char *className);
    void SetExtra(const char *extra);
    bool SetCommand(const char *command);
    bool RunCommand();
    void SetDumpAll();

private:
    Want* BuildWant();
    bool InnerStartAbility();
    bool InnerStopAbility();
    bool TerminateApp(IClientProxy *proxy) const;
    bool Dump(IClientProxy *proxy);
    static int32_t AaCallback(const IpcContext* context, void *ipcMsg, IpcIo *data, void *arg);

    ElementName elementName_ { nullptr, nullptr, nullptr };
    char *extra_ { nullptr };
    char *command_ { nullptr };
    bool dumpAll_ { false };
    SvcIdentity identity_ {};
    static const int MAX_OBJECTS = 2;
};
} // namespace OHOS
#endif // OHOS_ABILITY_TOOL_H
