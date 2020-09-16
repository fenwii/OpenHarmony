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

#include "themes/theme.h"
#include "components/root_view.h"
#include "components/ui_view.h"

namespace OHOS {
Theme::Theme()
{
    InitBasicStyle();
    InitButtonStyle();
    InitLabelStyle();
    InitPickerStyle();
    InitProgressStyle();
    InitSliderStyle();
};

void Theme::InitBasicStyle()
{
    basicStyle_ = StyleDefault::GetDefaultStyle();
}

void Theme::InitButtonStyle()
{
    buttonStyle_.released = StyleDefault::GetButtonReleasedStyle();
    buttonStyle_.pressed = StyleDefault::GetButtonPressedStyle();
}

void Theme::InitLabelStyle()
{
    labelStyle_ = StyleDefault::GetLabelStyle();
}

void Theme::InitPickerStyle()
{
    pickerBackgroundStyle_ = StyleDefault::GetPickerBackgroundStyle();
    pickerHighlightStyle_ = StyleDefault::GetPickerHighlightStyle();
}

void Theme::InitProgressStyle()
{
    progressBackgroundStyle_ = StyleDefault::GetProgressBackgroundStyle();
    progressForegroundStyle_ = StyleDefault::GetProgressForegroundStyle();
}

void Theme::InitSliderStyle()
{
    sliderKnobStyle_ = StyleDefault::GetPickerBackgroundStyle();
}
} // namespace OHOS