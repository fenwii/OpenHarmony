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
#include "components/root_view.h"
#include "components/ui_radiobutton.h"
#include "components/ui_view_group.h"
#include "default_resource/radio_button_res.h"
#include "draw/draw_image.h"
#include "graphic_log.h"
#include "imgdecode/cache_manager.h"
#include "securec.h"

namespace OHOS {
UIRadioButton::UIRadioButton() : name_(nullptr)
{
    image_[UNSELECTED].SetSrc(GetRadioButtonOffInfo());
    image_[SELECTED].SetSrc(GetRadioButtonOnInfo());
    ImageHeader header = { 0 };
    image_[UNSELECTED].GetHeader(header);
    Resize(header.width, header.height);
}

UIRadioButton::UIRadioButton(const char* name) : name_(nullptr)
{
    SetName(name);
    image_[UNSELECTED].SetSrc(GetRadioButtonOffInfo());
    image_[SELECTED].SetSrc(GetRadioButtonOnInfo());
    ImageHeader header = { 0 };
    image_[UNSELECTED].GetHeader(header);
    Resize(header.width, header.height);
}

void UIRadioButton::OnClickEvent(const ClickEvent& event)
{
    SetState(SELECTED);
    Invalidate();
    UIViewGroup* curViewGroup = nullptr;
    UIViewGroup* viewGroup = static_cast<UIViewGroup*>(RootView::GetInstance());
    UIView* uiViewInfo = viewGroup->GetChildrenHead();
    while (uiViewInfo != nullptr) {
        if (!uiViewInfo->IsViewGroup()) {
            UIRadioButton* uiRadioButtonInfo = static_cast<UIRadioButton*>(uiViewInfo);
            if (uiRadioButtonInfo == this || uiViewInfo->GetViewType() != UI_RADIO_BUTTON) {
                if (uiViewInfo->GetNextSibling() != nullptr) {
                    uiViewInfo = uiViewInfo->GetNextSibling();
                } else {
                    if (curViewGroup != nullptr) {
                        uiViewInfo = curViewGroup->GetNextSibling();
                        curViewGroup = static_cast<UIViewGroup*>(curViewGroup->GetParent());
                    } else {
                        uiViewInfo = nullptr;
                    }
                }
                continue;
            }
            if ((uiRadioButtonInfo->GetName() != nullptr) && (strcmp(uiRadioButtonInfo->GetName(), name_) == 0)) {
                uiRadioButtonInfo->SetState(UNSELECTED);
            }
            if (uiViewInfo->GetNextSibling() != nullptr) {
                uiViewInfo = uiViewInfo->GetNextSibling();
            } else {
                if (curViewGroup != nullptr) {
                    uiViewInfo = curViewGroup->GetNextSibling();
                    curViewGroup = static_cast<UIViewGroup*>(curViewGroup->GetParent());
                } else {
                    uiViewInfo = nullptr;
                }
            }
        } else {
            if (uiViewInfo->GetNextSibling() != nullptr) {
                curViewGroup = static_cast<UIViewGroup*>(uiViewInfo);
            }
            uiViewInfo = (static_cast<UIViewGroup*>(uiViewInfo))->GetChildrenHead();
        }
    }
    UIView::OnClickEvent(event);
}

void UIRadioButton::SetName(const char* name)
{
    if (name == nullptr) {
        return;
    }
    if (name_ != nullptr) {
        UIFree(name_);
        name_ = nullptr;
    }
    uint32_t nameLen = static_cast<uint32_t>(strlen(name) + 1);
    if (nameLen > MAX_TEXT_LENGTH) {
        return;
    }
    name_ = static_cast<char*>(UIMalloc(nameLen));
    if (name_ != nullptr) {
        if (memcpy_s(name_, nameLen, name, nameLen) != EOK) {
            UIFree(name_);
            name_ = nullptr;
            return;
        }
    }
}
} // namespace OHOS
