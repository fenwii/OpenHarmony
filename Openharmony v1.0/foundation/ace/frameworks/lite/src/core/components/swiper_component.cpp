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

#include "swiper_component.h"
#include "ace_log.h"
#include "js_fwk_common.h"
#include "key_parser.h"
#include "keys.h"

namespace OHOS {
namespace ACELite {
SwiperComponent::SwiperComponent(jerry_value_t options, jerry_value_t children, AppStyleManager* styleManager)
    : Component(options, children, styleManager),
      swiperView_(nullptr),
      hasChildren_(false),
      index_(0),
      changeListener_(nullptr)
{
    SetComponentName(K_SWIPER);
}

bool SwiperComponent::CreateNativeViews()
{
    swiperView_ = new UISwipeView();
    if (swiperView_ == nullptr) {
        return false;
    }
    swiperView_->SetLoopState(true);
    return true;
}

void SwiperComponent::ReleaseNativeViews()
{
    if (swiperView_) {
        delete swiperView_;
        swiperView_ = nullptr;
    }
    if (changeListener_) {
        delete changeListener_;
        changeListener_ = nullptr;
    }
}

inline UIView *SwiperComponent::GetComponentRootView() const
{
    return swiperView_;
}

bool SwiperComponent::SetPrivateAttribute(uint16_t attrKeyId, jerry_value_t attrValue)
{
    if (attrKeyId == K_DURATION) {
        int16_t duration = IntegerOf(attrValue);
        if (duration < 0) {
            HILOG_ERROR(HILOG_MODULE_ACE, "duration value has problem.");
            return false;
        }
        swiperView_->SetAnimatorTime(duration);
        return true;
    } else if (attrKeyId == K_LOOP) {
        if (jerry_value_is_boolean(attrValue)) {
            swiperView_->SetLoopState(BoolOf(attrValue));
        } else {
            swiperView_->SetLoopState(true);
        }
        return true;
    } else if (attrKeyId == K_INDEX) {
        if (!jerry_value_is_number(attrValue) && !jerry_value_is_string(attrValue)) {
            index_ = 0;
        } else {
            index_ = IntegerOf(attrValue);
        }
        return true;
    } else if (attrKeyId == K_VERTICAL) {
        if (!hasChildren_) {
            if (jerry_value_is_boolean(attrValue)) {
                swiperView_->SetDirection(BoolOf(attrValue));
            } else {
                swiperView_->SetDirection(0);
            }
        }
    }

    return false;
}

void SwiperComponent::PostUpdate(uint16_t attrKeyId, bool updateResult)
{
    if (updateResult) {
        SetPageIndex();
    }
}

void SwiperComponent::PostRender()
{
    SetPageIndex();
}

bool SwiperComponent::ProcessChildren()
{
    if (swiperView_ == nullptr) {
        return false;
    }
    AppendChildren(swiperView_);
    hasChildren_ = true;
    return true;
}

bool SwiperComponent::RegisterPrivateEventListener(uint16_t eventTypeId, jerry_value_t funcValue)
{
    if (eventTypeId == K_CHANGE) {
        if (swiperView_) {
            changeListener_ = new ChangeListener(funcValue);
            if (changeListener_ == nullptr) {
                HILOG_ERROR(HILOG_MODULE_ACE, "Create ChangeListener error.");
                return false;
            }
            swiperView_->SetOnSwipeListener(changeListener_);
            return true;
        }
    }
    return false;
}

void SwiperComponent::SetPageIndex() const
{
    if (jerry_value_is_undefined(GetChildren())) {
        HILOG_INFO(HILOG_MODULE_ACE, "Swiper children don't exsit.");
        return;
    }
    uint16_t length = jerry_get_array_length(GetChildren());
    if (index_ < 0 || index_ >= length) {
        swiperView_->SetCurrentPage(0);
    } else {
        swiperView_->SetCurrentPage(index_);
    }
}

void SwiperComponent::ChangeListener::OnSwipe(UISwipeView& view)
{
    if (jerry_value_is_undefined(fn_)) {
        return;
    }
    UISwipeView* swipeView = reinterpret_cast<UISwipeView *>(&view);
    if (swipeView == nullptr) {
        return;
    }
    const uint8_t argsNum = 1;
    jerry_value_t args[argsNum];
    args[0] = jerry_create_object();
    jerry_value_t indexValHandler = jerry_create_number(swipeView->GetCurrentPage());
    jerry_value_t result = jerryx_set_property_str(args[0], SWIPER_ATTR_INDEX, indexValHandler);
    jerry_release_value(indexValHandler);
    if (jerry_value_is_error(result)) {
        HILOG_ERROR(HILOG_MODULE_ACE, "set index value failed.");
        ReleaseJerryValue(args[0], result, VA_ARG_END_FLAG);
        return;
    }
    jerry_release_value(result);
    if (jerry_value_is_function(fn_)) {
        jerry_value_t retVal = CallJSFunctionOnRoot(fn_, args, argsNum);
        if (jerry_value_is_error(retVal)) {
            HILOG_ERROR(HILOG_MODULE_ACE, "Change event is error.");
        }
        jerry_release_value(retVal);
    } else {
        HILOG_ERROR(HILOG_MODULE_ACE, "Change event is not a function.");
    }
    jerry_release_value(args[0]);
}
} // namespace ACELite
} // namespace OHOS
