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

#include "dfx/ui_dump_dom_tree.h"

#if ENABLE_DEBUG
#include "components/root_view.h"
#include "components/ui_view.h"
#include "components/ui_label.h"
#include "components/ui_label_button.h"
#include "components/ui_checkbox.h"
#include "components/ui_toggle_button.h"
#include "components/ui_image_view.h"
#include "components/ui_abstract_progress.h"
#include "components/ui_scroll_view.h"
#include "components/ui_list.h"
#include "components/ui_abstract_clock.h"
#include "components/ui_picker.h"
#include "components/ui_swipe_view.h"
#include "components/ui_time_picker.h"
#include "draw/draw_image.h"
#include "file.h"
#include "graphic_log.h"
#endif // ENABLE_DEBUG
namespace OHOS {
#if ENABLE_DEBUG
void UIDumpDomTree::AddNameField(UIViewType type, cJSON* usr) const
{
    if (usr == nullptr) {
        return;
    }

    if (type < UI_NUMBER_MAX) {
        cJSON_AddStringToObject(usr, "name", VIEW_TYPE_STRING[type]);
    } else {
        cJSON_AddStringToObject(usr, "name", "UnknownType");
    }
}

void UIDumpDomTree::AddImageViewSpecialField(const UIView* view, cJSON* usr) const
{
    if ((view == nullptr) || (usr == nullptr)) {
        return;
    }
    const UIImageView* tmpImageView = static_cast<const UIImageView*>(view);
    ImageSrcType srcType = tmpImageView->GetSrcType();
    if (srcType == IMG_SRC_FILE) {
        cJSON_AddStringToObject(usr, "src", reinterpret_cast<const char*>(tmpImageView->GetPath()));
    } else if (srcType == IMG_SRC_VARIABLE) {
        const ImageInfo* imageInfo = reinterpret_cast<const ImageInfo*>(tmpImageView->GetImageInfo());
        if (imageInfo == nullptr || imageInfo->userData == nullptr) {
            cJSON_AddStringToObject(usr, "src", "");
            return;
        }
        uintptr_t userData = reinterpret_cast<uintptr_t>(imageInfo->userData);
        cJSON_AddNumberToObject(usr, "src", static_cast<uint32_t>(userData));
    } else {
        cJSON_AddStringToObject(usr, "src", "");
    }
}

void UIDumpDomTree::AddSpecialField(const UIView* view, cJSON* usr) const
{
    if ((view == nullptr) || (usr == nullptr)) {
        return;
    }
    switch (view->GetViewType()) {
        case UI_LABEL:
        case UI_ARC_LABEL: {
            const UILabel* tmpLabel = static_cast<const UILabel*>(view);
            cJSON_AddStringToObject(usr, "text", tmpLabel->GetText());
            tmpLabel = nullptr;
            break;
        }
        case UI_LABEL_BUTTON: {
            const UILabelButton* tmpLabelButton = static_cast<const UILabelButton*>(view);
            cJSON_AddStringToObject(usr, "text", tmpLabelButton->GetText());
            tmpLabelButton = nullptr;
            break;
        }
        case UI_CHECK_BOX:
        case UI_RADIO_BUTTON: {
            const UICheckBox* tmpCheckBox = static_cast<const UICheckBox*>(view);
            if (tmpCheckBox->GetState()) {
                cJSON_AddStringToObject(usr, "state", "UNSELECTED");
            } else {
                cJSON_AddStringToObject(usr, "state", "SELECTED");
            }
            tmpCheckBox = nullptr;
            break;
        }
        case UI_TOGGLE_BUTTON: {
            const UIToggleButton* tmpToggleButton = static_cast<const UIToggleButton*>(view);
            cJSON_AddBoolToObject(usr, "state", tmpToggleButton->GetState());
            tmpToggleButton = nullptr;
            break;
        }
        case UI_IMAGE_VIEW: {
            AddImageViewSpecialField(view, usr);
            break;
        }
        case UI_BOX_PROGRESS:
        case UI_SLIDER:
        case UI_CIRCLE_PROGRESS: {
            const UIAbstractProgress* tmpAbstractProgress = static_cast<const UIAbstractProgress*>(view);
            cJSON_AddNumberToObject(usr, "currValue", static_cast<double>(tmpAbstractProgress->GetValue()));
            cJSON_AddNumberToObject(usr, "rangeMin", static_cast<double>(tmpAbstractProgress->GetRangeMin()));
            cJSON_AddNumberToObject(usr, "rangeMax", static_cast<double>(tmpAbstractProgress->GetRangeMax()));
            tmpAbstractProgress = nullptr;
            break;
        }
        case UI_SCROLL_VIEW: {
            const UIScrollView* tmpScrollView = static_cast<const UIScrollView*>(view);
            cJSON_AddBoolToObject(usr, "xScrollable", tmpScrollView->GetHorizontalScrollState());
            cJSON_AddBoolToObject(usr, "yScrollable", tmpScrollView->GetVerticalScrollState());
            tmpScrollView = nullptr;
            break;
        }
        case UI_LIST: {
            UIList* tmpList = static_cast<UIList*>(const_cast<UIView*>(view));
            cJSON_AddBoolToObject(usr, "isLoopList", tmpList->GetLoopState());
            UIView* selectView = tmpList->GetSelectView();
            if (selectView != nullptr) {
                cJSON_AddNumberToObject(usr, "selectedIndex", static_cast<double>(selectView->GetViewIndex()));
                selectView = nullptr;
            }
            tmpList = nullptr;
            break;
        }
        case UI_DIGITAL_CLOCK:
        case UI_ANALOG_CLOCK: {
            const UIAbstractClock* tmpAbstractClock = static_cast<const UIAbstractClock*>(view);
            cJSON_AddNumberToObject(usr, "currentHour", static_cast<double>(tmpAbstractClock->GetCurrentHour()));
            cJSON_AddNumberToObject(usr, "currentMinute", static_cast<double>(tmpAbstractClock->GetCurrentMinute()));
            cJSON_AddNumberToObject(usr, "currentSecond", static_cast<double>(tmpAbstractClock->GetCurrentSecond()));
            tmpAbstractClock = nullptr;
            break;
        }
        case UI_PICKER: {
            const UIPicker* tmpPicker = static_cast<const UIPicker*>(view);
            cJSON_AddNumberToObject(usr, "selectedIndex", static_cast<double>(tmpPicker->GetSelected()));
            tmpPicker = nullptr;
            break;
        }
        case UI_SWIPE_VIEW: {
            const UISwipeView* tmpSwipeView = static_cast<const UISwipeView*>(view);
            cJSON_AddNumberToObject(usr, "currentIndex", static_cast<double>(tmpSwipeView->GetCurrentPage()));
            cJSON_AddNumberToObject(usr, "direction", static_cast<double>(tmpSwipeView->GetDirection()));
            tmpSwipeView = nullptr;
            break;
        }
        case UI_TIME_PICKER: {
            const UITimePicker* tmpTimePicker = static_cast<const UITimePicker*>(view);
            cJSON_AddStringToObject(usr, "selectedHour", tmpTimePicker->GetSelectHour());
            cJSON_AddStringToObject(usr, "selectedMinute", tmpTimePicker->GetSelectMinute());
            cJSON_AddStringToObject(usr, "selectedSecond", tmpTimePicker->GetSelectSecond());
            tmpTimePicker = nullptr;
            break;
        }
        default:
            break;
    }
}

void UIDumpDomTree::AddCommonField(UIView* view, cJSON* usr) const
{
    if ((view == nullptr) || (usr == nullptr)) {
        return;
    }
    cJSON_AddNumberToObject(usr, "x", static_cast<double>(view->GetOrigRect().GetX()));
    cJSON_AddNumberToObject(usr, "y", static_cast<double>(view->GetOrigRect().GetY()));
    cJSON_AddNumberToObject(usr, "width", static_cast<double>(view->GetWidth()));
    cJSON_AddNumberToObject(usr, "height", static_cast<double>(view->GetHeight()));
    cJSON_AddStringToObject(usr, "id", view->GetViewId());
    cJSON_AddBoolToObject(usr, "visible", view->IsVisible());
    cJSON_AddBoolToObject(usr, "touchable", view->IsTouchable());
    cJSON_AddBoolToObject(usr, "draggable", view->IsDraggable());
    cJSON_AddBoolToObject(usr, "onClickListener", (view->GetOnClickListener() != nullptr));
    cJSON_AddBoolToObject(usr, "onDragListener", (view->GetOnDragListener() != nullptr));
    cJSON_AddBoolToObject(usr, "onLongPressListener", (view->GetOnLongPressListener() != nullptr));
}

void UIDumpDomTree::OutputDomNode(UIView* view)
{
    if (view == nullptr) {
        return;
    }
    /* Output current view's info into cJSON structure. */
    cJSON* dumpUsr = cJSON_CreateObject();
    if (dumpUsr == nullptr) {
        GRAPHIC_LOGE("UIDumpDomTree::OutputDomNode cJSON create object failed Err!\n");
        return;
    }

    AddNameField(view->GetViewType(), dumpUsr);
    AddCommonField(view, dumpUsr);
    AddSpecialField(view, dumpUsr);

    pJson_ = cJSON_Print(dumpUsr);
    cJSON_Delete(dumpUsr);
}

bool UIDumpDomTree::WriteDumpFile() const
{
    FileUnlink(path_);
    int32_t fd = FileOpen(path_, O_CREAT | O_RDWR);
    if (fd < 0) {
        GRAPHIC_LOGE("UIDumpDomTree::WriteDumpFile open file failed Err!\n");
        return false;
    }

    if (pJson_ == nullptr) {
        FileClose(fd);
        return false;
    }

    uint32_t length = strlen(pJson_);
    if (FileWrite(fd, pJson_, length) != length) {
        GRAPHIC_LOGE("UIDumpDomTree::WriteDumpFile write file failed Err!\n");
        FileClose(fd);
        return false;
    }

    if (FileClose(fd) < 0) {
        return false;
    }
    return true;
}

void UIDumpDomTree::OutputDomTree(UIView* view, cJSON* usr)
{
    if (allocErrorFlag_) {
        return;
    }

    cJSON* dumpUsr = usr;
    if (dumpUsr != rootJson_) {
        dumpUsr = cJSON_CreateObject();
        if (dumpUsr == nullptr) {
            allocErrorFlag_ = true;
            GRAPHIC_LOGE("UIDumpDomTree::OutputDomTree cJSON create object failed Err!\n");
            return;
        }
        /* usr must be a array. */
        cJSON_AddItemToArray(usr, dumpUsr);
    }

    AddNameField(view->GetViewType(), dumpUsr);
    AddCommonField(view, dumpUsr);
    AddSpecialField(view, dumpUsr);

    if (view->IsViewGroup()) {
        cJSON* arrayJson = cJSON_CreateArray();
        if (arrayJson == nullptr) {
            allocErrorFlag_ = true;
            GRAPHIC_LOGE("UIDumpDomTree::OutputDomTree cJSON create object failed Err!\n");
            return;
        }

        cJSON_AddItemToObject(dumpUsr, "child", arrayJson);
        UIViewGroup* tmpViewGroup = static_cast<UIViewGroup*>(view);
        UIView* childView = tmpViewGroup->GetChildrenHead();
        while (childView != nullptr) {
            OutputDomTree(childView, arrayJson);
            childView = childView->GetNextSibling();
        }
    }
}

void UIDumpDomTree::DumpJsonById(UIView* view, const char* id, DumpMode mode)
{
    if (searchFlag_) {
        return;
    }

    /* Check whether current view is the view we are looking for. */
    if ((view->GetViewId() != nullptr) && !strcmp(view->GetViewId(), id)) {
        if (mode == DUMP_NODE) {
            /* Find the view with right id, output its info. */
            OutputDomNode(view);
        } else if (mode == DUMP_TREE) {
            /* Find the view with right id, output its dom tree's info. */
            OutputDomTree(view, rootJson_);
        }
        /* Set flag to stop the tranversion. */
        searchFlag_ = true;
    } else {
        /* Look through all childrens of the current viewGroup. */
        if (view->IsViewGroup()) {
            UIViewGroup* tmpViewGroup = static_cast<UIViewGroup*>(view);
            UIView* childView = tmpViewGroup->GetChildrenHead();
            while (childView != nullptr) {
                DumpJsonById(childView, id, mode);
                childView = childView->GetNextSibling();
            }
        }
    }
}
#endif // ENABLE_DEBUG

char* UIDumpDomTree::DumpDomNode(const char* id)
{
#if ENABLE_DEBUG
    if (id == nullptr) {
        return nullptr;
    }
    /* Reset dump info */
    pJson_ = nullptr;

    RootView* rootView = RootView::GetInstance();
    UIView* currView = static_cast<UIView*>(rootView);
    /* Search through all views from rootView. */
    DumpJsonById(currView, id, DUMP_NODE);

    /* Reset the search flag and pJson for next search */
    searchFlag_ = false;
    return pJson_;
#else
    return nullptr;
#endif // ENABLE_DEBUG
}

bool UIDumpDomTree::DumpDomTree(const char* id, const char* path)
{
#if ENABLE_DEBUG
    path_ = (path == nullptr) ? DEFAULT_DUMP_DOM_TREE_PATH : path;

    RootView* rootView = RootView::GetInstance();
    UIView* currView = static_cast<UIView*>(rootView);
    rootJson_ = cJSON_CreateObject();
    if (rootJson_ == nullptr) {
        GRAPHIC_LOGE("UIDumpDomTree::DumpDomTree cJSON create object failed Err!\n");
        return false;
    }

    if (id == nullptr) {
        OutputDomTree(currView, rootJson_);
    } else {
        DumpJsonById(currView, id, DUMP_TREE);
        if (!searchFlag_) {
            cJSON_Delete(rootJson_);
            rootJson_ = nullptr;
            GRAPHIC_LOGI("UIDumpDomTree::DumpDomTree can not find the node \n");
            return false;
        }
        /* Reset the search flag. */
        searchFlag_ = false;
    }

    pJson_ = cJSON_Print(rootJson_);
    cJSON_Delete(rootJson_);
    rootJson_ = nullptr;
    if (pJson_ == nullptr) {
        GRAPHIC_LOGE("UIDumpDomTree::DumpDomTree convert cJSON object to string failed Err!\n");
        return false;
    }

    if (WriteDumpFile() == false) {
        cJSON_free(pJson_);
        pJson_ = nullptr;
        GRAPHIC_LOGE("UIDumpDomTree::DumpDomTree file operation failed Err!\n");
        return false;
    }

    cJSON_free(pJson_);
    pJson_ = nullptr;
    allocErrorFlag_ = false;
    return true;
#else
    return false;
#endif // ENABLE_DEBUG
}
}
