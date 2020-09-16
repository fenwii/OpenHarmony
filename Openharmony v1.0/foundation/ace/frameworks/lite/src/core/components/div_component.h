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

#ifndef OHOS_ACELITE_DIV_COMPONENT_H
#define OHOS_ACELITE_DIV_COMPONENT_H
#include "component.h"
#include "flex_layout.h"
#include "non_copyable.h"

namespace OHOS {
namespace ACELite {
class DivComponent final : public Component {
public:
    enum LayoutType {
        POSITION,
        FLEX
    };

    ACE_DISALLOW_COPY_AND_MOVE(DivComponent);
    DivComponent() = delete;
    DivComponent(jerry_value_t options, jerry_value_t children, AppStyleManager* styleManager, const LayoutType type);
    ~DivComponent() override {}

protected:
    bool CreateNativeViews() override;
    void ReleaseNativeViews() override;
    UIView *GetComponentRootView() const override;
    bool ApplyPrivateStyle(const AppStyleItem* style) override;
    bool ProcessChildren() override;
    void PostUpdate(uint16_t attrKeyId, bool updateResult) override;

private:
    bool isSecondaryAxisAlignSet_;
    const AppStyle* combinedStyle_;
    UIViewGroup* nativeView_;
    LayoutType layoutType_;
};
} // namespace ACELite
} // namespace OHOS

#endif // OHOS_ACELITE_DIV_COMPONENT_H
