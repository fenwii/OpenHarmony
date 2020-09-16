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

#ifndef GRAPHIC_LITE_LITE_WIN_H
#define GRAPHIC_LITE_LITE_WIN_H

#include <pthread.h>

#include "client/isurface.h"
#include "common/lite_wm_type.h"
#include "geometry2d.h"
#include "liteipc_adapter.h"
#include "serializer.h"
#include "surface.h"

namespace OHOS {
class LiteWindow {
public:
    friend class LiteWM;
    LiteWindow(const LiteWinConfig& config);
    virtual ~LiteWindow();

    uint32_t GetWindowId() const
    {
        return id_;
    }

    const LiteWinConfig& GetConfig()
    {
        return config_;
    }

    void SetSid(const SvcIdentity& sid)
    {
        needUnregister_ = true;
        sid_ = sid;
    }

    void SetIsShow(bool isShow)
    {
        isShow_ = isShow;
    }

    bool GetIsShow()
    {
        return isShow_;
    }

    void ResizeSurface(int16_t width, int16_t height);

    void Update(Rect rect);
    void UpdateBackBuf();
    void Flush(const Rect& srcRect, const LiteSurfaceData* layerData, int16_t dx, int16_t dy);

    Surface* GetSurface();
    void MoveTo(int16_t x, int16_t y);
    void Resize(int16_t width, int16_t height);
private:
    bool CreateSurface();
    void ReleaseSurface();

    int32_t id_;
    bool isShow_;
    LiteWinConfig config_;
    Surface* surface_;
    SurfaceBuffer* backBuf_;
    pthread_mutex_t backBufMutex_;
    SvcIdentity sid_;
    bool needUnregister_;
};
}
#endif