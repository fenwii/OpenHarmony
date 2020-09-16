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

#include "list_adapter.h"

#include <stdlib.h>

#include "ace_log.h"
#include "ace_mem_base.h"
#include "component_utils.h"
#include "directive/descriptor_utils.h"
#include "fatal_handler.h"
#if ENABLED(SECURE_C_FUNCTION)
#include "securec.h"
#endif // ENABLED(SECURE_C_FUNCTION)

namespace OHOS {
namespace ACELite {
ListAdapter::ListAdapter()
    : listItems_(nullptr), headNode_(nullptr), tailNode_(nullptr), itemsCount_(0), listItemsCount_(0)
{
}

ListAdapter::~ListAdapter()
{
    if (listItems_) {
        delete[] listItems_;
        listItems_ = nullptr;
    }

    ViewNativePair *currentNode = headNode_;
    ViewNativePair *nextNode = nullptr;

    if (currentNode == nullptr) {
        HILOG_DEBUG(HILOG_MODULE_ACE, "the viewNativePair linked list is null");
    }

    // delete nativeElement in viewNativePair link list, then free viewNativePair link list.
    while (currentNode != nullptr) {
        nextNode = currentNode->next;
        // only let list component release its children when the whole application
        // is not in fatal error handling process, as FatalHandler will do the recycle
        if (!FatalHandler::GetInstance().IsFatalErrorHandling()) {
            DescriptorUtils::ReleaseDescriptorOrElement(currentNode->nativeElement);
        }
        ace_free(currentNode);
        currentNode = nextNode;
    }
    headNode_ = nullptr;
    tailNode_ = nullptr;

    itemsCount_ = 0;
    listItemsCount_ = 0;
}

bool ListAdapter::Initialize(const JSValue descriptors)
{
    // check the children can be initialized.
    if (jerry_value_is_undefined(descriptors) || !jerry_value_is_array(descriptors)) {
        HILOG_ERROR(HILOG_MODULE_ACE, "List adapter: initialize children failed!");
        return false;
    }

    int16_t size = JSArray::Length(descriptors);
    if ((size == 0) || (size >= INT16_MAX)) {
        HILOG_ERROR(HILOG_MODULE_ACE, "List adapter: descriptors size invalid.");
        return false;
    }
    listItems_ = new ListItemValue[size];
    // initialize the listItems_ array.
    if (listItems_ == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "List adapter: listItems_ array failed to allocate memory!");
        return false;
    }

    // generate the listItems_ array and return result.
    return GenerateListItems(descriptors, size);
}

bool ListAdapter::GenerateListItems(const JSValue descriptors, int16_t size)
{
    bool result = false;
    int16_t listItemsIndex = 0;
    int16_t startIndex = 0;

    for (int16_t index = 0; index < size; ++index) {
        JSValue descriptorOrElement = JSArray::Get(descriptors, index);
        if (JSUndefined::Is(descriptorOrElement)) {
            HILOG_ERROR(HILOG_MODULE_ACE, "List adapter: get descriptorOrElement from descriptors failed!");
            continue;
        }

        listItems_[listItemsIndex].descriptorOrElement = descriptorOrElement;
        listItems_[listItemsIndex].startIndex = startIndex;

        // if it is a for type list-item
        if (DescriptorUtils::IsForDescriptor(descriptorOrElement)) {
            bool success = AddForDescriptorToList(descriptorOrElement, listItemsIndex);
            if (!success) {
                JSRelease(descriptorOrElement);
                continue;
            }
        } else { // if it is a if or common type list-item
            if (DescriptorUtils::IsIfDescriptor(descriptorOrElement)) {
                bool isShown = DescriptorUtils::IsIfDescriptorShown(descriptorOrElement);
                if (!isShown) {
                    JSRelease(descriptorOrElement);
                    result = true;
                    continue;
                }
            }
            listItems_[listItemsIndex].getterRetList = UNDEFINED;
            listItems_[listItemsIndex].itemsCount = 1;
        }

        // sum of all descriptors list-items.
        itemsCount_ = itemsCount_ + listItems_[listItemsIndex].itemsCount;
        // sum of all descriptors.
        listItemsCount_ = listItemsCount_ + 1;
        startIndex = startIndex + listItems_[listItemsIndex].itemsCount;
        listItemsIndex++;

        JSRelease(descriptorOrElement);
        result = true;
    }
    return result;
}

bool ListAdapter::AddForDescriptorToList(JSValue descriptorOrElement, int16_t listItemsIndex) const
{
    JSValue getterPropValue = jerryx_get_property_str(descriptorOrElement, DESCRIPTOR_ATTR_GETTER);
    if (!jerry_value_is_function(getterPropValue)) {
        ReleaseJerryValue(getterPropValue, VA_ARG_END_FLAG);
        HILOG_ERROR(HILOG_MODULE_ACE, "List adapter: Getter argument is not a function.");
        return false;
    }

    JSValue getterRetList = CallJSFunctionOnRoot(getterPropValue, nullptr, 0);
    // check whether result is an array
    if (!jerry_value_is_array(getterRetList)) {
        ReleaseJerryValue(getterPropValue, getterRetList, VA_ARG_END_FLAG);
        HILOG_ERROR(HILOG_MODULE_ACE, "List adapter: fetch getter array error.");
        return false;
    }

    // save getterRetList.
    listItems_[listItemsIndex].getterRetList = getterRetList;
    // save getterRetList length.(the length is the count of current descriptor list-item)
    listItems_[listItemsIndex].itemsCount = jerry_get_array_length(getterRetList);
    ReleaseJerryValue(getterPropValue, getterRetList, VA_ARG_END_FLAG);
    return true;
}

// find listItemsIndex according the itemIndex
int16_t ListAdapter::CalculateItemIndex(int16_t itemIndex) const
{
    if (listItems_ == nullptr) {
        return FAILED;
    }

    for (int16_t listItemsIndex = 0; listItemsIndex < listItemsCount_; listItemsIndex++) {
        if (itemIndex >= listItems_[listItemsIndex].startIndex &&
            itemIndex <= (listItems_[listItemsIndex].startIndex + listItems_[listItemsIndex].itemsCount - 1) &&
            itemIndex < itemsCount_) {
            // found.
            return listItemsIndex;
        }
    }
    // not found.
    return FAILED;
}

// 1. get UIView according to index which will show in list.
// 2. delete inView if it is not null(if inView not null, it means this view is out of the list visible area, need
// delete.) if the UIView found belongs to "For type" child, need create it dynamically, or else just get it from native
// Element.
UIView *ListAdapter::GetView(UIView *inView, int16_t index)
{
    if (index < 0) {
        HILOG_ERROR(HILOG_MODULE_ACE, "List adapter: GetView function parameter index error!");
        return nullptr;
    }

    // find listItemsIndex according the item index
    int16_t listItemsIndex = CalculateItemIndex(index);
    if (listItemsIndex < 0) {
        return nullptr;
    }
    // delete "For type" UIView that are not visible in list
    if (inView != nullptr) {
        // this function will check whether the inView is For type UIView, if it is, delete it, or else do nothing.
        DeleteItem(inView);
    }

    bool isFor = false;
    JSValue element = GetElement(listItemsIndex, index, isFor);
    if (jerry_value_is_undefined(element)) {
        HILOG_ERROR(HILOG_MODULE_ACE, "List adapter: Failed to get element.");
        return nullptr;
    }

    // get rootview from nativeElement
    UIView *newView = ComponentUtils::GetViewFromBindingObject(element);
    if (newView == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "List adapter: Failed to get view from js object.");
        jerry_release_value(element);
        return nullptr;
    }

    if (isFor) {
        InsertItem(element, newView);
    }
    return newView;
}

JSValue ListAdapter::GetElement(int16_t listItemsIndex, int16_t index, bool &isFor) const
{
    JSValue element = UNDEFINED;
    JSValue descriptorOrElement = listItems_[listItemsIndex].descriptorOrElement;
    JSValue getterRetList = listItems_[listItemsIndex].getterRetList;
    int16_t startIndex = listItems_[listItemsIndex].startIndex;
    isFor = DescriptorUtils::IsForDescriptor(descriptorOrElement);
    // if it is a for or for+if type list-item, we need create view dynamically.
    if (isFor) {
        // get render argument
        const int8_t argsLen = 2;
        JSValue item = jerry_get_property_by_index(getterRetList, index - startIndex);
        if (jerry_value_is_undefined(item)) {
            HILOG_ERROR(HILOG_MODULE_ACE, "List adapter: Get item from getterRetList failed.");
            return UNDEFINED;
        }
        JSValue itemIdx = jerry_create_number(index - startIndex);
        JSValue args[argsLen];
        args[0] = {item};
        args[1] = {itemIdx};

        // get render function
        JSValue renderPropValue = jerryx_get_property_str(descriptorOrElement, DESCRIPTOR_ATTR_RENDER);
        if (!jerry_value_is_function(renderPropValue)) {
            HILOG_ERROR(HILOG_MODULE_ACE, "List adapter: Get View failed, render argument is not a function.");
            ReleaseJerryValue(item, itemIdx, renderPropValue, VA_ARG_END_FLAG);
            return UNDEFINED;
        }

        // excute render function, get nativeElement
        JSValue nativeElement = CallJSFunction(renderPropValue, UNDEFINED, args, argsLen);
        if (jerry_value_is_undefined(nativeElement)) {
            ReleaseJerryValue(item, itemIdx, renderPropValue, nativeElement, VA_ARG_END_FLAG);
            return UNDEFINED;
        }

        // if it is a for+if type list-item, here will ignore if attribure
        if (DescriptorUtils::IsIfDescriptor(nativeElement)) {
            element = DescriptorUtils::RenderIfDescriptor(nativeElement);
            ReleaseJerryValue(nativeElement, VA_ARG_END_FLAG);
            HILOG_ERROR(HILOG_MODULE_ACE, "List_adapter: list-item not support setting if and for attribute at once.");
        } else { // if it is a for type list-item
            element = nativeElement;
        }
        ReleaseJerryValue(item, itemIdx, renderPropValue, VA_ARG_END_FLAG);
    } else if (DescriptorUtils::IsIfDescriptor(descriptorOrElement)) { // if it is a if type list-item
        element = DescriptorUtils::RenderIfDescriptor(descriptorOrElement);
    } else { // if it is a common list-item
        element = descriptorOrElement;
    }
    return element;
}

void ListAdapter::InsertItem(JSValue nativeElement, UIView *uiView)
{
    ViewNativePair *insertNode;

    insertNode = (ViewNativePair *)ace_malloc(sizeof(ViewNativePair));
    if (insertNode == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "List adapter: insertNode failed to allocate memory!");
        return;
    }

    insertNode->nativeElement = nativeElement;
    insertNode->uiView = uiView;
    insertNode->next = nullptr;

    // if the link list is null, insertNode as head node.
    if (headNode_ == nullptr) {
        headNode_ = insertNode;
        tailNode_ = headNode_;
        return;
    }

    tailNode_->next = insertNode;
    // update the tailNode_ position
    tailNode_ = insertNode;
    return;
}

void ListAdapter::DeleteItem(const UIView *uiView)
{
    ViewNativePair *delNode;
    ViewNativePair *preNode;

    // delNode point to head node.
    delNode = headNode_;
    preNode = nullptr;

    // if viewNativePair not exsit, can not confirm whether the uiView is belongs For type child or common child,
    // although it can not be deleted, does not effect rendering new View.
    if (delNode == nullptr) {
        return;
    }

    // check this view is belongs For type child
    while (delNode->uiView != uiView && delNode->next != nullptr) {
        preNode = delNode;
        delNode = delNode->next;
    }

    if (delNode->uiView == uiView) {
        // if found it, delete this view's nativeElement.
        if (delNode == headNode_) {
            // it is the head node.
            headNode_ = delNode->next;
            // update the tailNode_ position
            if (headNode_ == nullptr) {
                tailNode_ = headNode_;
            }
        } else if (preNode != nullptr) {
            // it is not head node.
            preNode->next = delNode->next;
            // update the tailNode_ position
            if (preNode->next == nullptr) {
                tailNode_ = preNode;
            }
        } else {
            // Do nothing
        }

        DescriptorUtils::ReleaseDescriptorOrElement(delNode->nativeElement);
        ace_free(delNode);
        delNode = nullptr;
    } else {
        // if not found, it means this view is not belongs For type child, do nothing.
        HILOG_INFO(HILOG_MODULE_ACE,
                   "not found the view can be free, it means this inView is not belongs For type child");
    }
}

void ListAdapter::CleanUp()
{
    itemsCount_ = 0;
    listItemsCount_ = 0;

    if (listItems_ != nullptr) {
        delete[] listItems_;
        listItems_ = nullptr;
    }
}
} // namespace ACELite
} // namespace OHOS
