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

#ifndef OHOS_JS_APP_HOST_H
#define OHOS_JS_APP_HOST_H

#include "js_ability.h"
#include "cmsis_os2.h"
#include "js_async_work.h"

namespace OHOS {
class JsAppHost {
public:
    JsAppHost();
    ~JsAppHost();

    static void JsAppTaskHandler(uint32_t uwArg);

    void SetMessageQueueId(const osMessageQueueId_t jsAppQueueId)
    {
        jsAppQueueId_ = jsAppQueueId;
        ACELite::JsAsyncWork::SetAppQueueHandler(reinterpret_cast<ACELite::QueueHandler>(jsAppQueueId));
    }

    const osMessageQueueId_t& GetMessageQueueId() const
    {
        return jsAppQueueId_;
    }

    void ForceDestroy() const;

private:
    void StartAbility(uint16_t token);
    void OnActive(uint16_t token, const char *bundleName, const char *path);
    void OnBackground(uint16_t token);
    void OnDestroy(uint16_t token);
    void BackPressed();
    void SendMsgToAbilityService(uint16_t token, int32_t id);
    void HandleTickEvent();

    ACELite::JSAbility *jsAbility_ { nullptr };
    osMessageQueueId_t jsAppQueueId_ { nullptr };
    bool isBackground_ { false };
};
} // namespace OHOS
#endif  // OHOS_JS_APP_HOST_H
