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

#include "image_component.h"
#include "ace_log.h"
#include "ace_mem_base.h"
#include "js_app_context.h"
#include "js_fwk_common.h"
#include "key_parser.h"
#include "keys.h"

namespace OHOS {
namespace ACELite {
ImageComponent::ImageComponent(jerry_value_t options, jerry_value_t children, AppStyleManager *styleManager)
    : Component(options, children, styleManager), imageView_(nullptr)
{
    SetComponentName(K_IMAGE);
}

bool ImageComponent::CreateNativeViews()
{
    imageView_ = new UIImageView();

    if (imageView_ == nullptr) {
        return false;
    } else {
        // set default value
        imageView_->SetAutoEnable(false);
        const int16_t defaultOpacity = 0;
        imageView_->SetStyle(STYLE_BACKGROUND_OPA, defaultOpacity);
    }
    return true;
}

void ImageComponent::ReleaseNativeViews()
{
    if (imageView_) {
        delete imageView_;
        imageView_ = nullptr;
    }
}

inline UIView *ImageComponent::GetComponentRootView() const
{
    return imageView_;
}

bool ImageComponent::SetPrivateAttribute(uint16_t attrKeyId, jerry_value_t attrValue)
{
    bool setResult = true;
    switch (attrKeyId) {
        case K_SRC: {
            char *src = const_cast<char *>(ParseImageSrc(attrValue));
            imageView_->SetSrc(src);
            ACE_FREE(src);
            break;
        }
        default:
            setResult = false;
            break;
    }

    return setResult;
}

bool ImageComponent::ApplyPrivateStyle(const AppStyleItem *style)
{
    uint16_t styleKey = style->GetPropNameId();
    switch (styleKey) {
        case K_OPACITY: {
            SetOpacity(*imageView_, *style);
            return true;
        }
        default:
            return false;
    }
}
} // namespace ACELite
} // namespace OHOS
