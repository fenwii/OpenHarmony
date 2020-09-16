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

#include "common/graphic_startup.h"
#include "animator/animator.h"
#include "common/input_device_manager.h"
#include "core/render_manager.h"
#include "common/task_manager.h"
#include "file.h"
#include "font/ui_font.h"
#include "graphic_log.h"
#include "imgdecode/cache_manager.h"
#ifdef VERSION_STANDARD
#include "dock/ohos/ohos_input_device.h"
#endif
#if ENABLE_WINDOW
#include "client/iwindows_manager.h"
#if ENABLE_HARDWARE_ACCELERATION
#include "gfx_engines.h"
#endif
#endif

namespace OHOS {
void GraphicStartUp::InitFontEngine(uintptr_t psramAddr, uint32_t psramLen, const char* dPath, const char* ttfName)
{
    UIFont* pFont = UIFont::GetInstance();
    if (pFont == nullptr) {
        GRAPHIC_LOGE("Get UIFont error");
        return;
    }
    int8_t ret = pFont->SetPsramMemory(psramAddr, psramLen);
    if (ret == INVALID_RET_VALUE) {
        GRAPHIC_LOGE("SetPsramMemory failed");
        return;
    }
    // font and glyph path
    ret = pFont->SetFontPath(const_cast<char*>(dPath));
    if (ret == INVALID_RET_VALUE) {
        GRAPHIC_LOGW("SetFontPath failed");
    }
    if (ttfName != nullptr) {
        ret = pFont->RegisterFontInfo(ttfName);
        if (ret == INVALID_RET_VALUE) {
            GRAPHIC_LOGW("SetTtfName failed");
        }
    }
}

void GraphicStartUp::Init()
{
    TaskManager::GetInstance()->SetTaskRun(true);
    FileInit();

    if (INDEV_READ_PERIOD > 0) {
        InputDeviceManager::GetInstance()->Init();
    }
    AnimatorManager::GetInstance()->Init();

    StyleDefault::Init();
    RenderManager::GetInstance().Init();

    CacheManager::GetInstance().Init(IMG_CACHE_SIZE);
#ifdef VERSION_STANDARD
    OHOSInputDevice* input = new OHOSInputDevice();
    InputDeviceManager::GetInstance()->Add(input);
#endif

#if ENABLE_WINDOW
    IWindowsManager::GetInstance()->Init();
#if ENABLE_HARDWARE_ACCELERATION
    GfxEngines::GetInstance()->InitDriver();
#endif
#endif
}
} // namespace OHOS
