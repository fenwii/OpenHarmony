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

#include "core/measure_manager.h"

namespace OHOS {
void MeasureManager::AddMeasureView(UIView* view)
{
    if (view != nullptr) {
        measureView_.PushBack(view);
    }
}

void MeasureManager::DeleteMeasureView(UIView* view)
{
    if (view == nullptr || measureView_.IsEmpty()) {
        return;
    }
    ListNode<UIView*>* node = measureView_.Begin();
    ListNode<UIView*>* temp;
    while (node != measureView_.End()) {
        if (node->data_ != nullptr && node->data_ == view) {
            temp = node;
            node = node->next_;
            measureView_.Remove(temp);
            continue;
        }
        node = node->next_;
    }
}

void MeasureManager::ReMeasureRect()
{
    if (measureView_.IsEmpty()) {
        return;
    }
    ListNode<UIView*>* node = measureView_.Begin();
    while (node != measureView_.End()) {
        if (node->data_ != nullptr) {
            node->data_->ReMeasure();
        }
        node = node->next_;
    }
    measureView_.Clear();
}
} // namespace OHOS
