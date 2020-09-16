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

#include "layout/list_layout.h"

namespace OHOS {
ListLayout::ListLayout(const uint8_t direction) : listDirection_(direction)
{
    SetLayoutDirect(direction);
}

void ListLayout::SetDirection(uint8_t direction)
{
    listDirection_ = direction;
    SetLayoutDirect(direction);
    OnChildChanged();
}

void ListLayout::SetLayoutDirect(uint8_t direction)
{
    if (direction == VERTICAL) {
        direction_ = LAYOUT_VER;
    } else {
        direction_ = LAYOUT_HOR;
    }
}

void ListLayout::OnChildChanged()
{
    LayoutChildren(true);
    Rect rect = GetAllChildRelativeRect();
    if (listDirection_ == VERTICAL) {
        SetHeight(rect.GetHeight() + rect.GetTop());
    } else {
        SetWidth(rect.GetWidth() + rect.GetLeft());
    }
}
} // namespace OHOS