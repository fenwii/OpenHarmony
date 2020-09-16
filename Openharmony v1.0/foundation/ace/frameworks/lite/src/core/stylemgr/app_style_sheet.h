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

#ifndef OHOS_ACELITE_APP_STYLE_SHEET_H
#define OHOS_ACELITE_APP_STYLE_SHEET_H

#include "non_copyable.h"
#include "stylemgr/app_style_item.h"
#include "stylemgr/app_style_list.h"

namespace OHOS {
namespace ACELite {
class AppStyleSheet final : public MemoryHeap {
public:
    ACE_DISALLOW_COPY_AND_MOVE(AppStyleSheet);
    AppStyleSheet() : idSelectors_(nullptr), classSelectors_(nullptr), keyFrameSelectors_(nullptr) {}
    ~AppStyleSheet()
    {
        Reset();
    }
    void InitSheet(jerry_value_t jsObj);
    void Reset();
    AppStyle* GetStyleFromIDSelectors(const char * const name) const;
    AppStyle* GetStyleFromClassSelectors(const char * const name) const;
    AppStyle* GetStyleFromKeyFramesSelectors(const char * const name) const;
    AppStyle* GetStyleFromSelectors(AppStyleList* selectors, const char * const name) const;

private:
    void InitSelectors(AppStyleList** selectorsList, jerry_value_t selectorsObj, bool isKeyFrames);
    AppStyleList* idSelectors_;
    AppStyleList* classSelectors_;
    AppStyleList* keyFrameSelectors_;
};
} // namespace ACELite
} // namespace OHOS

#endif // OHOS_ACELITE_APP_STYLE_SHEET_H