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

#ifndef OHOS_ACELITE_LIST_COMPONENT_H
#define OHOS_ACELITE_LIST_COMPONENT_H

#include "component.h"
#include "list_adapter.h"
#include "ui_list.h"

namespace OHOS {
namespace ACELite {
class ListComponent final : public Component {
public:
    ACE_DISALLOW_COPY_AND_MOVE(ListComponent);
    ListComponent() = delete;
    ListComponent(JSValue options, JSValue children, AppStyleManager *styleManager);
    ~ListComponent() override {}

protected:
    bool CreateNativeViews() override;
    void ReleaseNativeViews() override;
    UIView *GetComponentRootView() const override;
    bool RegisterPrivateEventListener(uint16_t eventTypeId, JSValue funcValue) override;
    bool ProcessChildren() override;
    bool UpdateForView() override;

private:
    UIList *list_;
    ListAdapter *adapter_;
    const AppStyle *combinedStyle_;
    ListEventListener *listEventListener_;
    const char *flexDirectionDefault;
    static const char * const FUNC_SCROLLTO;
    static const char * const INDEX_SCROLLTO;
    static JSValue ListScrollTo(const JSValue func, const JSValue dom, const JSValue args[], const jerry_length_t size);
};
} // namespace ACELite
} // namespace OHOS

#endif // OHOS_ACELITE_LIST_COMPONENT_H
