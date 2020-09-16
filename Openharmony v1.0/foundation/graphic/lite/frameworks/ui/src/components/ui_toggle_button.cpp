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

#include "common/image.h"
#include "components/ui_toggle_button.h"
#include "default_resource/toggle_button_res.h"
#include "imgdecode/cache_manager.h"

namespace OHOS {
UIToggleButton::UIToggleButton()
{
    image_[UNSELECTED].SetSrc(GetToggleButtonOffInfo());
    image_[SELECTED].SetSrc(GetToggleButtonOnInfo());
    ImageHeader header = { 0 };
    image_[UNSELECTED].GetHeader(header);
    Resize(header.width, header.height);
}

void UIToggleButton::SetState(bool state)
{
    if (state) {
        UICheckBox::SetState(SELECTED);
    } else {
        UICheckBox::SetState(UNSELECTED);
    }
    Invalidate();
}
}   // namespace OHOS