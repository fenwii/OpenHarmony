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

#ifndef GRAPHIC_LITE_RENDER_MANAGER_H
#define GRAPHIC_LITE_RENDER_MANAGER_H

#include "components/ui_view.h"
#include "components/root_view.h"
#include "common/task_manager.h"
#include "geometry2d.h"
#include "list.h"
#include "sys_info.h"
#if ENABLE_WINDOW
#include "window/window.h"
#endif

namespace OHOS {
static constexpr float MAX_FPS = 60.f;

static constexpr int16_t SAMPLE_NUMBER = 100;

static constexpr uint16_t MILLISECONDS_PER_SECOND = 1000;

class RenderManager : public Task {
public:
    static RenderManager& GetInstance()
    {
        static RenderManager instance;
        return instance;
    }

    virtual void Init() override;

#if ENABLE_WINDOW
    Window* GetWindowById(int32_t id)
    {
        auto node = winList_.Begin();
        while (node != winList_.End()) {
            if (node->data_->GetWindowId() == id) {
                return node->data_;
            }
            node = node->next_;
        }
        return nullptr;
    }
#endif

    virtual void Callback() override
    {
        RenderTask();
    }

    float GetFPS() const
    {
        return fps_;
    }

    void RegisterFPSChangedListener(SysInfo::OnFPSChangedListener* onFPSChangedListener)
    {
        onFPSChangedListener_ = onFPSChangedListener;
        needResetFPS_ = true;
    }

#if ENABLE_WINDOW
    void AddToDisplay(Window* window);

    void RemoveFromDisplay(Window* window);
#endif

private:
    friend class RootView;

    RenderManager();

    ~RenderManager();

    void RenderTask();

    static void RenderRect(const Rect& rect, RootView* rootView);

#if ENABLE_FPS_SUPPORT
    void UpdateFPS();

    void UpdateFPSByFixedTimeMethod();

    void UpdateFPSByAverageSamplingMethod();

    void UpdateFPSByPreciseSamplingMethod();

    void OnFPSChanged(float newFPS)
    {
        if (onFPSChangedListener_) {
            onFPSChangedListener_->OnFPSChanged(newFPS);
        }
    }
#endif

    float fps_;

    bool needResetFPS_;

    SysInfo::OnFPSChangedListener* onFPSChangedListener_;

#if ENABLE_WINDOW
    List<Window*> winList_;
#endif
};
} // namespace OHOS
#endif // GRAPHIC_LITE_RENDER_MANAGER_H
