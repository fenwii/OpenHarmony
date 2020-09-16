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

#ifndef OHOS_ABILITY_SLICE_STACK_H
#define OHOS_ABILITY_SLICE_STACK_H

#include <list>

#include "nocopyable.h"

namespace OHOS {
class AbilitySlice;

class AbilitySliceStack : public NoCopyable {
public:
    AbilitySliceStack() = default;
    ~AbilitySliceStack() override;

    bool IsEmpty() const;
    int Size() const;
    bool Exist(const AbilitySlice *slice) const;
    void Remove(AbilitySlice *slice);
    const AbilitySlice *Top() const;
    AbilitySlice *Pop();
    void Push(AbilitySlice *slice);
    std::list<AbilitySlice *> GetAllSlices() const;
    void Clear();

private:
    std::list<AbilitySlice *> slices_ {};
};
}

#endif // OHOS_ABILITY_SLICE_STACK_H
