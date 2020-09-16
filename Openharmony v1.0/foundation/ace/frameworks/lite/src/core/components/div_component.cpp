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

#include "div_component.h"
#include "ace_log.h"
#include "key_parser.h"
#include "keys.h"

namespace OHOS {
namespace ACELite {
DivComponent::DivComponent(jerry_value_t options,
                           jerry_value_t children,
                           AppStyleManager* styleManager,
                           const LayoutType type)
    : Component(options, children, styleManager),
      isSecondaryAxisAlignSet_(false),
      combinedStyle_(nullptr),
      nativeView_(nullptr),
      layoutType_(FLEX)
{
    SetComponentName(K_DIV);
    // get combined style for style items
    combinedStyle_ = GetStyleManager()->GetCombinedStyle();
    layoutType_ = type;
}

bool DivComponent::CreateNativeViews()
{
    if (layoutType_ == LayoutType::POSITION) {
        nativeView_ = new UIViewGroup();
    } else {
        nativeView_ = new FlexLayout();
    }

    if (nativeView_ == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "div create fail");
        return false;
    }

    return true;
}

void DivComponent::ReleaseNativeViews()
{
    if (nativeView_) {
        delete nativeView_;
        nativeView_ = nullptr;
    }
}

inline UIView *DivComponent::GetComponentRootView() const
{
    return nativeView_;
}

bool DivComponent::ApplyPrivateStyle(const AppStyleItem* style)
{
    bool applyResult = true;
    // set layout
    if (layoutType_ == LayoutType::POSITION) {
        // do nothing
        applyResult = false;
    } else {
        // Set default value
        if (!isSecondaryAxisAlignSet_) {
            (reinterpret_cast<FlexLayout*>(nativeView_))->SetSecondaryAxisAlign(OHOS::ALIGN_START);
        }
        uint16_t stylePropNameId = GetStylePropNameId(style);
        if (!KeyParser::IsKeyValid(stylePropNameId)) {
            return false;
        }
        const char * const strValue = GetStyleStrValue(style);
        if (strValue == nullptr) {
            return false;
        }
        uint16_t valueId = KeyParser::ParseKeyId(strValue, GetStyleStrValueLen(style));
        switch (stylePropNameId) {
            case K_FLEX_DIRECTION: {
                switch (valueId) {
                    case K_COLUMN:
                        (reinterpret_cast<FlexLayout*>(nativeView_))->SetLayoutDirection(LAYOUT_VER);
                        break;
                    case K_ROW:
                        (reinterpret_cast<FlexLayout*>(nativeView_))->SetLayoutDirection(LAYOUT_HOR);
                        break;
                    case K_ROW_REVERSE:
                        (reinterpret_cast<FlexLayout*>(nativeView_))->SetLayoutDirection(LAYOUT_HOR_R);
                        break;
                    case K_COLUMN_REVERSE:
                        (reinterpret_cast<FlexLayout*>(nativeView_))->SetLayoutDirection(LAYOUT_VER_R);
                        break;
                    default:
                        applyResult = false;
                        break;
                }
                break;
            }
            case K_JUSTIFY_CONTENT: {
                switch (valueId) {
                    case K_FLEX_START:
                        (reinterpret_cast<FlexLayout*>(nativeView_))->SetMajorAxisAlign(OHOS::ALIGN_START);
                        break;
                    case K_FLEX_END:
                        (reinterpret_cast<FlexLayout*>(nativeView_))->SetMajorAxisAlign(OHOS::ALIGN_END);
                        break;
                    case K_CENTER:
                        (reinterpret_cast<FlexLayout*>(nativeView_))->SetMajorAxisAlign(OHOS::ALIGN_CENTER);
                        break;
                    case K_SPACE_BETWEEN:
                        (reinterpret_cast<FlexLayout*>(nativeView_))->SetMajorAxisAlign(OHOS::ALIGN_BETWEEN);
                        break;
                    case K_SPACE_AROUND:
                        (reinterpret_cast<FlexLayout*>(nativeView_))->SetMajorAxisAlign(OHOS::ALIGN_EVENLY);
                        break;
                    default:
                        applyResult = false;
                        break;
                }
                break;
            }
            case K_ALIGN_ITEMS: {
                switch (valueId) {
                    case K_FLEX_START:
                        (reinterpret_cast<FlexLayout*>(nativeView_))->SetSecondaryAxisAlign(OHOS::ALIGN_START);
                        break;
                    case K_FLEX_END:
                        (reinterpret_cast<FlexLayout*>(nativeView_))->SetSecondaryAxisAlign(OHOS::ALIGN_END);
                        break;
                    case K_CENTER:
                        (reinterpret_cast<FlexLayout*>(nativeView_))->SetSecondaryAxisAlign(OHOS::ALIGN_CENTER);
                        break;
                    default:
                        applyResult = false;
                        break;
                }
                if (applyResult)
                    isSecondaryAxisAlignSet_ = true;
                break;
            }
            case K_FLEX_WRAP: {
                if (valueId == K_WRAP) {
                    (reinterpret_cast<FlexLayout*>(nativeView_))->SetFlexWrap(FlexLayout::WRAP);
                } else {
                    (reinterpret_cast<FlexLayout*>(nativeView_))->SetFlexWrap(FlexLayout::NOWRAP);
                }
                break;
            }
            default:
                applyResult = false;
                break;
        }
    }

    return applyResult;
}

bool DivComponent::ProcessChildren()
{
    if (!nativeView_) {
        return false;
    }

    // first, add all children to this container
    AppendChildren(nativeView_);
    // second, layout them
    if (layoutType_ != LayoutType::POSITION) {
        nativeView_->LayoutChildren();
    }

    return true;
}

void DivComponent::PostUpdate(uint16_t attrKeyId, bool updateResult)
{
    nativeView_->LayoutChildren();
}
} // namespace ACELite
} // namespace OHOS
