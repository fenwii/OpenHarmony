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

#include "ability_slice_stack.h"

#include <algorithm>

#include "ability_slice.h"

namespace OHOS {
AbilitySliceStack::~AbilitySliceStack()
{
    Clear();
}

bool AbilitySliceStack::IsEmpty() const
{
    return slices_.empty();
}

int AbilitySliceStack::Size() const
{
    return slices_.size();
}

bool AbilitySliceStack::Exist(const AbilitySlice *slice) const
{
    return std::find(slices_.begin(), slices_.end(), slice) != slices_.end();
}

void AbilitySliceStack::Remove(AbilitySlice *slice)
{
    slices_.remove(slice);
}

const AbilitySlice *AbilitySliceStack::Top() const
{
    if (slices_.empty()) {
        return nullptr;
    }

    return slices_.front();
}

AbilitySlice *AbilitySliceStack::Pop()
{
    if (slices_.empty()) {
        return nullptr;
    }

    AbilitySlice *topSlice = slices_.front();
    slices_.pop_front();
    return topSlice;
}

void AbilitySliceStack::Push(AbilitySlice *slice)
{
    slices_.push_front(slice);
}

std::list<AbilitySlice *> AbilitySliceStack::GetAllSlices() const
{
    return slices_;
}

void AbilitySliceStack::Clear()
{
    for (auto node : slices_) {
        delete node;
    }
    slices_.clear();
}
}
