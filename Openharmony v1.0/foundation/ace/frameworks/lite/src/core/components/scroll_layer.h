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

#ifndef OHOS_ACELITE_SCROLL_LAYER_H
#define OHOS_ACELITE_SCROLL_LAYER_H

#include "js_fwk_common.h"
#include "non_copyable.h"
#include "ui_scroll_view.h"

namespace OHOS {
namespace ACELite {
class ScrollLayer final : public MemoryHeap {
public:
    ACE_DISALLOW_COPY_AND_MOVE(ScrollLayer);
    ScrollLayer();
    ~ScrollLayer();
    void AppendScrollLayer(jerry_value_t nativeElement);
    void Hide() const;
    void Show() const;

private:
    UIScrollView *AddScrollLayer(UIView &view) const;
    UIScrollView *scroll_;
    UIView *origView_;
};
} // namespace ACELite
} // namespace OHOS

#endif // OHOS_ACELITE_SCROLL_LAYER_H
