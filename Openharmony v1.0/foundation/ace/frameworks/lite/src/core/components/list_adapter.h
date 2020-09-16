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

#ifndef OHOS_ACELITE_LIST_ADAPTER_H
#define OHOS_ACELITE_LIST_ADAPTER_H

#include "abstract_adapter.h"
#include "js_fwk_common.h"
#include "non_copyable.h"

namespace OHOS {
namespace ACELite {
struct ListItemValue : public MemoryHeap {
    JSValue descriptorOrElement; // "For type" child or common child
    JSValue getterRetList;       // "For type" list-item list data
    int16_t itemsCount;         // list-item inside "For type" child count
    int16_t startIndex;         // start index of list-item inside "For type" child
    ListItemValue() : descriptorOrElement(UNDEFINED), getterRetList(UNDEFINED), itemsCount(0), startIndex(0) {}
    ACE_DISALLOW_COPY_AND_MOVE(ListItemValue);
};

// mapping link list of UIView<--->nativeElement
struct ViewNativePair : public MemoryHeap {
    JSValue nativeElement;
    UIView *uiView;
    ViewNativePair *next;
    ACE_DISALLOW_COPY_AND_MOVE(ViewNativePair);
};

class ListAdapter final : public AbstractAdapter {
public:
    ACE_DISALLOW_COPY_AND_MOVE(ListAdapter);
    ListAdapter();
    ~ListAdapter();
    bool Initialize(const JSValue descriptors);
    // Get the view from index.
    // if inView is null, adapter will new a view. if not, adapter will delete the inView and new a view.
    UIView *GetView(UIView *inView, int16_t index) override;
    void DeleteView(UIView *&view) override {}

    uint16_t GetCount() override
    {
        return itemsCount_;
    }

    void CleanUp();

private:
    bool GenerateListItems(const JSValue descriptors, int16_t size);
    int16_t CalculateItemIndex(int16_t itemIndex) const;
    JSValue GetElement(int16_t listItemsIndex, int16_t index, bool &isFor) const;
    bool AddForDescriptorToList(JSValue descriptorOrElement, int16_t listItemsIndex) const;
    void InsertItem(JSValue nativeElement, UIView *uiView);
    void DeleteItem(const UIView *uiView);
    ListItemValue *listItems_;
    ViewNativePair *headNode_;
    ViewNativePair *tailNode_;
    int16_t itemsCount_;
    int16_t listItemsCount_;
};
} // namespace ACELite
} // namespace OHOS
#endif // OHOS_ACELITE_LIST_ADAPTER_H
