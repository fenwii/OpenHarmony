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

#ifndef GRAPHIC_LITE_MEASURE_MANAGER_H
#define GRAPHIC_LITE_MEASURE_MANAGER_H

#include "list.h"
#include "components/ui_view.h"

namespace OHOS {
class MeasureManager : public HeapBase {
public:
    static MeasureManager& GetInstance()
    {
        static MeasureManager instance;
        return instance;
    }

    void AddMeasureView(UIView* view);

    void DeleteMeasureView(UIView* view);

    void ReMeasureRect();

private:
    MeasureManager() {}

    ~MeasureManager()
    {
        measureView_.Clear();
    }

    List<UIView*> measureView_;
};
} // namespace OHOS
#endif // GRAPHIC_LITE_MEASURE_MANAGER_H
