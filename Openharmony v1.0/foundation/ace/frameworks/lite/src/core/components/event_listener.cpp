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
#include "event_listener.h"
#include "ace_log.h"
#include "jerryscript.h"
#include "js_fwk_common.h"
#include "root_view.h"

namespace OHOS {
namespace ACELite {
#ifdef JS_TOUCH_EVENT_SUPPORT
KeyBoardEventListener::KeyBoardEventListener(jerry_value_t fn, const uint16_t id)
{
    fn_ = jerry_acquire_value(fn);
    id_ = id;
}

KeyBoardEventListener::~KeyBoardEventListener()
{
    jerry_release_value(fn_);
}

bool KeyBoardEventListener::OnKeyAct(UIView &view, const KeyEvent &event)
{
    if (jerry_value_is_undefined(fn_)) {
        return false;
    }

    jerry_value_t *args = ConvertKeyEventInfo(event);
    jerry_release_value(CallJSFunctionOnRoot(fn_, args, 1));
    ClearEventListener(args, 1);
    return true;
}

ViewOnTouchStartListener::ViewOnTouchStartListener(jerry_value_t fn, uint16_t id)
{
    fn_ = jerry_acquire_value(fn);
    id_ = id;
}

ViewOnTouchStartListener::~ViewOnTouchStartListener()
{
    jerry_release_value(fn_);
}

bool ViewOnTouchStartListener::OnPress(UIView &view, const PressEvent &event)
{
    return CallBaseEvent(fn_, event, id_);
}

ViewOnTouchMoveListener::ViewOnTouchMoveListener(jerry_value_t fn, uint16_t id)
{
    fn_ = jerry_acquire_value(fn);
    id_ = id;
}

ViewOnTouchMoveListener::~ViewOnTouchMoveListener()
{
    jerry_release_value(fn_);
}

bool ViewOnTouchMoveListener::OnDrag(UIView &view, const DragEvent &event)
{
    if (jerry_value_is_undefined(fn_)) {
        return false;
    }

    jerry_value_t *args = ConvertDragEventInfo(event, id_);
    jerry_release_value(CallJSFunctionOnRoot(fn_, args, 1));
    ClearEventListener(args, 1);
    return true;
}

ViewOnTouchEndListener::ViewOnTouchEndListener(jerry_value_t fn, uint16_t id)
{
    fn_ = jerry_acquire_value(fn);
    id_ = id;
}

ViewOnTouchEndListener::~ViewOnTouchEndListener()
{
    jerry_release_value(fn_);
}

bool ViewOnTouchEndListener::OnRelease(UIView &view, const ReleaseEvent &event)
{
    return CallBaseEvent(fn_, event, id_);
}

ViewOnTouchCancelListener::ViewOnTouchCancelListener(jerry_value_t fn, uint16_t id)
{
    fn_ = jerry_acquire_value(fn);
    id_ = id;
}

ViewOnTouchCancelListener::~ViewOnTouchCancelListener()
{
    jerry_release_value(fn_);
}
bool ViewOnTouchCancelListener::OnCancel(UIView &view, const CancelEvent &event)
{
    return CallBaseEvent(fn_, event, id_);
}
#endif // JS_TOUCH_EVENT_SUPPORT

bool ViewOnSwipeListener::OnDragStart(UIView &view, const DragEvent &event)
{
    UNUSED(view);
    UNUSED(event);
    HILOG_DEBUG(HILOG_MODULE_ACE, "OnDragStart received");
    return true;
}

bool ViewOnSwipeListener::OnDragEnd(UIView &view, const DragEvent &event)
{
    UNUSED(view);
    if (jerry_value_is_undefined(fn_)) {
        HILOG_ERROR(HILOG_MODULE_ACE, "OnDragEnd received, but no JS function to call");
        return false;
    }

    HILOG_DEBUG(HILOG_MODULE_ACE, "OnDragEnd received");

    jerry_value_t directionValue;
    switch (event.GetDragDirection()) {
        case DragEvent::DIRECTION_LEFT_TO_RIGHT:
            directionValue = jerry_create_string(reinterpret_cast<const jerry_char_t *>(SWIPE_RIGHT));
            break;
        case DragEvent::DIRECTION_RIGHT_TO_LEFT:
            directionValue = jerry_create_string(reinterpret_cast<const jerry_char_t *>(SWIPE_LEFT));
            break;
        case DragEvent::DIRECTION_TOP_TO_BOTTOM:
            directionValue = jerry_create_string(reinterpret_cast<const jerry_char_t *>(SWIPE_DOWN));
            break;
        case DragEvent::DIRECTION_BOTTOM_TO_TOP:
            directionValue = jerry_create_string(reinterpret_cast<const jerry_char_t *>(SWIPE_UP));
            break;
        default:
            directionValue = UNDEFINED;
            break;
    }

    jerry_value_t args[1] = {jerry_create_object()};
    const char * const directionName = "direction";
    jerry_value_t result = jerryx_set_property_str(args[0], directionName, directionValue);
    if (!jerry_value_is_error(result)) {
        CallJSFunctionAutoRelease(fn_, UNDEFINED, args, 1);
    }
    ReleaseJerryValue(result, args[0], directionValue, VA_ARG_END_FLAG);
    return true;
}
} // namespace ACELite
} // namespace OHOS
