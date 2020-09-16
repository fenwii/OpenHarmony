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

#ifndef OHOS_ACELITE_IMAGE_COMPONENT_H
#define OHOS_ACELITE_IMAGE_COMPONENT_H

#include "component.h"
#include "key_parser.h"
#include "layout/flex_layout.h"
#include "non_copyable.h"
#include "ui_image_view.h"

namespace OHOS {
namespace ACELite {
class ImageComponent final : public Component {
public:
    ACE_DISALLOW_COPY_AND_MOVE(ImageComponent);
    ImageComponent() = delete;
    ImageComponent(jerry_value_t options, jerry_value_t children, AppStyleManager *styleManager);
    ~ImageComponent() override {}

protected:
    bool CreateNativeViews() override;
    void ReleaseNativeViews() override;
    UIView *GetComponentRootView() const override;
    bool SetPrivateAttribute(uint16_t attrKeyId, jerry_value_t attrValue) override;
    bool ApplyPrivateStyle(const AppStyleItem *style) override;

private:
    UIImageView *imageView_;
};
} // namespace ACELite
} // namespace OHOS

#endif // OHOS_ACELITE_IMAGE_COMPONENT_H
