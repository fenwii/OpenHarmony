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

#ifndef OHOS_ACELITE_PROGRESS_COMPONENT_H
#define OHOS_ACELITE_PROGRESS_COMPONENT_H

#include "component.h"
#include "non_copyable.h"
#include "ui_abstract_progress.h"

namespace OHOS {
namespace ACELite {
enum ProgressType { ARC = 0x01, HORIZONTAL = 0x02 };

constexpr int16_t DEFAULT_STROKE_WIDTH = 32;

class ProgressComponent final : public Component {
public:
    ACE_DISALLOW_COPY_AND_MOVE(ProgressComponent);
    ProgressComponent() = delete;
    ProgressComponent(jerry_value_t options, jerry_value_t children, AppStyleManager* styleManager);
    ~ProgressComponent() override {}

protected:
    bool CreateNativeViews() override;
    void ReleaseNativeViews() override;
    UIView *GetComponentRootView() const override;
    bool SetPrivateAttribute(uint16_t attrKeyId, jerry_value_t attrValue) override;
    bool ApplyPrivateStyle(const AppStyleItem* style) override;
    void PostRender() override;
    void PostUpdate(uint16_t attrKeyId, bool updateResult) override;

private:
    ProgressType GetType() const;
    char* GetStringAttrByName(const char * const name, uint16_t* len) const;
    void SetAngles() const;
    void HorizonProgressPostDeal() const;
    bool SetArcProgressStyle(const AppStyleItem* style);
    bool SetHorizonProgressStyle(const AppStyleItem* style);
    jerry_value_t options_;
    UIAbstractProgress* progressView_;
    ProgressType type_;
    int16_t hStrokeWidth_;
    int16_t startAngle_;
    int16_t totalAngle_;
};
} // namespace ACELite
} // namespace OHOS

#endif // OHOS_ACELITE_PROGRESS_COMPONENT_H
