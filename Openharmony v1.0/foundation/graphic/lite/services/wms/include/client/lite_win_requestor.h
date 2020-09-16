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

#ifndef GRAPHIC_LITE_LITE_WIN_REQUESTOR_H
#define GRAPHIC_LITE_LITE_WIN_REQUESTOR_H

#include "geometry2d.h"
#include "surface.h"
#include <iproxy_client.h>

namespace OHOS {
class LiteWinRequestor {
public:
    LiteWinRequestor(int32_t id);
    ~LiteWinRequestor();

    static int Callback(void* owner, int code, IpcIo *reply);
    void GenericSurface(IpcIo *reply);

    Surface* GetSurface();
    void Show();
    void Hide();
    void RaiseToTop();
    void LowerToBottom();
    void MoveTo(int16_t x, int16_t y);
    void Resize(int16_t width, int16_t height);
    void Update();

    int32_t GetWindowId()
    {
        return id_;
    }
private:
    IClientProxy* proxy_;
    int32_t id_;
    Surface* surface_;
};
}
#endif