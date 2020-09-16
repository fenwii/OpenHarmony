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

#ifndef OHOS_ACELITE_EVENT_LISTENER_H
#define OHOS_ACELITE_EVENT_LISTENER_H

#include "js_fwk_common.h"
#include "keys.h"
#include "non_copyable.h"
#include "ui_checkbox.h"
#include "ui_list.h"
#include "ui_radiobutton.h"
#include "ui_scroll_view.h"
#include "ui_slider.h"
#include "ui_toggle_button.h"

namespace OHOS {
namespace ACELite {
class StateChangeListener final : public UICheckBox::OnChangeListener {
public:
    ACE_DISALLOW_COPY_AND_MOVE(StateChangeListener);
    StateChangeListener(jerry_value_t fn, uint16_t componentId)
    {
        fn_ = jerry_acquire_value(fn);
        componentId_ = componentId;
        isChanging_ = false;
        radio_ = nullptr;
        state_ = UICheckBox::UICheckBoxState::UNSELECTED;
    }

    bool OnChange(UICheckBox::UICheckBoxState state) override
    {
        if (radio_ != nullptr) {
            state_ = state;
        }
        if (isChanging_) {
            return false;
        }
        isChanging_ = true;
        jerry_value_t args[1];
        bool result = (UICheckBox::UICheckBoxState::SELECTED == state) ? true : false;
        jerry_value_t resultProp = jerry_create_boolean(result);
        args[0] = jerry_create_object();
        const char * const checked = "checked";
        ReleaseJerryValue(jerryx_set_property_str(args[0], checked, resultProp), resultProp, VA_ARG_END_FLAG);
        if (radio_ != nullptr) {
            const char * const name = "name";
            if (radio_->GetName() != nullptr) {
                jerry_value_t nameVal = jerry_create_string(reinterpret_cast<const jerry_char_t *>(radio_->GetName()));
                ReleaseJerryValue(jerryx_set_property_str(args[0], name, nameVal), nameVal, VA_ARG_END_FLAG);
            }
        }
        jerry_value_t globalObject = jerry_get_global_object();
        jerry_value_t appViewModel = jerryx_get_property_str(globalObject, ATTR_APP);
        if (jerry_value_is_function(fn_)) {
            CallJSFunctionAutoRelease(fn_, appViewModel, args, 1);
        }
        ReleaseJerryValue(globalObject, appViewModel, args[0], VA_ARG_END_FLAG);
        isChanging_ = false;
        return true;
    }

    void TriggerChange(UIView *view)
    {
        UICheckBox::UICheckBoxState state = UICheckBox::UICheckBoxState::UNSELECTED;
        if (componentId_ == K_SWITCH) {
            UIToggleButton *toggleButton = reinterpret_cast<UIToggleButton *>(view);
            if (toggleButton) {
                state = (toggleButton->GetState()) ? UICheckBox::UICheckBoxState::SELECTED
                                                    : UICheckBox::UICheckBoxState::UNSELECTED;
            }
        } else if (componentId_ == K_CHECKBOX) {
            UICheckBox *checkbox = reinterpret_cast<UICheckBox *>(view);
            if (checkbox) {
                state = checkbox->GetState();
            }
        } else if (radio_ != nullptr) {
            state = radio_->GetState();
            if (state == state_) {
                return;
            }
        }
        OnChange(state);
    }

    void SetView(UIRadioButton* radioButton)
    {
        radio_ = radioButton;
    }

    ~StateChangeListener()
    {
        jerry_release_value(fn_);
    }

private:
    jerry_value_t fn_;
    uint16_t componentId_;
    UIRadioButton* radio_;
    UICheckBox::UICheckBoxState state_;
    bool isChanging_; // the flag to avoid change event cycle execute
};

class ViewOnClickListener final : public UIView::OnClickListener {
public:
    ACE_DISALLOW_COPY_AND_MOVE(ViewOnClickListener);
    explicit ViewOnClickListener(jerry_value_t fn, const uint16_t id)
        : fn_(jerry_acquire_value(fn)),
#ifdef JS_TOUCH_EVENT_SUPPORT
          id_(id),
#endif
          changeListener_(nullptr) {}
    ~ViewOnClickListener()
    {
        jerry_release_value(fn_);
    }

    bool OnClick(UIView &view, const ClickEvent &event) override
    {
        if (changeListener_) {
            changeListener_->TriggerChange(&view);
        }
        if (jerry_value_is_undefined(fn_)) {
            return false;
        }
#ifdef JS_TOUCH_EVENT_SUPPORT
        jerry_value_t *args = ConvertBaseEventInfo(event, id_);
        jerry_release_value(CallJSFunctionOnRoot(fn_, args, 1));
        ClearEventListener(args, 1);
#else
        jerry_release_value(CallJSFunctionOnRoot(fn_, nullptr, 0));
#endif
        return true;
    }

    void SetComponentListener(StateChangeListener *changeListener)
    {
        changeListener_ = changeListener;
    }

private:
    jerry_value_t fn_;
#ifdef JS_TOUCH_EVENT_SUPPORT
    uint16_t id_;
#endif
    StateChangeListener *changeListener_;
};

class ViewOnLongPressListener final : public UIView::OnLongPressListener {
public:
    ACE_DISALLOW_COPY_AND_MOVE(ViewOnLongPressListener);
    explicit ViewOnLongPressListener(jerry_value_t fn, const uint16_t id) :
#ifdef JS_TOUCH_EVENT_SUPPORT
        id_(id),
#endif
        fn_(jerry_acquire_value(fn)) {}

    ~ViewOnLongPressListener()
    {
        jerry_release_value(fn_);
    }

    bool OnLongPress(UIView &view, const LongPressEvent &event) override
    {
        if (jerry_value_is_undefined(fn_)) {
            return false;
        }
#ifdef JS_TOUCH_EVENT_SUPPORT
        jerry_value_t *args = ConvertBaseEventInfo(event, id_);
        jerry_release_value(CallJSFunctionOnRoot(fn_, args, 1));
        ClearEventListener(args, 1);
#else
        jerry_release_value(CallJSFunctionOnRoot(fn_, nullptr, 0));
#endif
        return true;
    }

private:
#ifdef JS_TOUCH_EVENT_SUPPORT
    uint16_t id_;
#endif
    jerry_value_t fn_;
};

#ifdef JS_TOUCH_EVENT_SUPPORT
class ViewOnTouchStartListener final : public UIView::OnTouchListener {
public:
    ACE_DISALLOW_COPY_AND_MOVE(ViewOnTouchStartListener);
    explicit ViewOnTouchStartListener(jerry_value_t fn, const uint16_t id);
    ~ViewOnTouchStartListener();
    bool OnPress(UIView &view, const PressEvent &event) override;

private:
    jerry_value_t fn_;
    uint16_t id_;
};

class ViewOnTouchMoveListener final : public UIView::OnDragListener {
public:
    ACE_DISALLOW_COPY_AND_MOVE(ViewOnTouchMoveListener);
    ViewOnTouchMoveListener(jerry_value_t fn, const uint16_t id);
    ~ViewOnTouchMoveListener();
    bool OnDrag(UIView &view, const DragEvent &event) override;

private:
    jerry_value_t fn_;
    uint16_t id_;
};

class ViewOnTouchEndListener final : public UIView::OnTouchListener {
public:
    ACE_DISALLOW_COPY_AND_MOVE(ViewOnTouchEndListener);
    ViewOnTouchEndListener(jerry_value_t fn, const uint16_t id);
    ~ViewOnTouchEndListener();
    bool OnRelease(UIView &view, const ReleaseEvent &event) override;

private:
    jerry_value_t fn_;
    uint16_t id_;
};

class ViewOnTouchCancelListener final : public UIView::OnTouchListener {
public:
    ACE_DISALLOW_COPY_AND_MOVE(ViewOnTouchCancelListener);
    ViewOnTouchCancelListener(jerry_value_t fn, const uint16_t id);
    ~ViewOnTouchCancelListener();
    bool OnCancel(UIView &view, const CancelEvent &event) override;

private:
    jerry_value_t fn_;
    uint16_t id_;
};

class KeyBoardEventListener final : public RootView::OnKeyActListener {
public:
    ACE_DISALLOW_COPY_AND_MOVE(KeyBoardEventListener);
    explicit KeyBoardEventListener(jerry_value_t fn, const uint16_t id);
    ~KeyBoardEventListener();
    bool OnKeyAct(UIView &view, const KeyEvent &event) override;

private:
    jerry_value_t fn_;
    uint16_t id_;
};
#endif

class ViewOnSwipeListener final : public UIView::OnDragListener {
public:
    ACE_DISALLOW_COPY_AND_MOVE(ViewOnSwipeListener);
    explicit ViewOnSwipeListener(jerry_value_t fn)
        : SWIPE_LEFT("left"), SWIPE_RIGHT("right"), SWIPE_UP("up"), SWIPE_DOWN("down")
    {
        fn_ = jerry_acquire_value(fn);
    }

    ~ViewOnSwipeListener()
    {
        jerry_release_value(fn_);
    }

    bool OnDragStart(UIView& view, const DragEvent& event) override;
    bool OnDragEnd(UIView &view, const DragEvent &event) override;

private:
    jerry_value_t fn_;
    const char * const SWIPE_LEFT;
    const char * const SWIPE_RIGHT;
    const char * const SWIPE_UP;
    const char * const SWIPE_DOWN;
};

class SliderEventListener final : public UISlider::UISliderEventListener {
public:
    ACE_DISALLOW_COPY_AND_MOVE(SliderEventListener);
    SliderEventListener() : bindChangeFunc_(UNDEFINED) {}
    ~SliderEventListener()
    {
        jerry_release_value(bindChangeFunc_);
    }
    void OnChange(int16_t progress) override
    {
        jerry_value_t knobValue = jerry_create_number(progress);
        jerry_value_t args[1];
        args[0] = jerry_create_object();
        constexpr char sliderAttrProgress[] = "progress";
        jerry_value_t result = jerryx_set_property_str(args[0], sliderAttrProgress, knobValue);
        if (!jerry_value_is_error(result)) {
            CallJSFunctionAutoRelease(bindChangeFunc_, UNDEFINED, args, 1);
        }
        ReleaseJerryValue(result, args[0], knobValue, VA_ARG_END_FLAG);
    }

    void SetBindChangeFuncName(jerry_value_t bindChageFunc)
    {
        bindChangeFunc_ = jerry_acquire_value(bindChageFunc);
    }

private:
    jerry_value_t bindChangeFunc_;
};

class ListEventListener final : public ListScrollListener {
public:
    ACE_DISALLOW_COPY_AND_MOVE(ListEventListener);
    ListEventListener()
        : bindScrollStartFunc_(UNDEFINED), bindScrollEndFunc_(UNDEFINED), bindScrollSelectedFunc_(UNDEFINED)
    {
    }
    ~ListEventListener()
    {
        ReleaseJerryValue(bindScrollStartFunc_, bindScrollEndFunc_, bindScrollSelectedFunc_, VA_ARG_END_FLAG);
    }

    void EventExcute(const int16_t index, jerry_value_t bindScrollFunc) const
    {
        int8_t currentState = this->GetScrollState();
        jerry_value_t currentStateValue = jerry_create_number(currentState);
        jerry_value_t componentIndex = jerry_create_number(index);
        jerry_value_t args[ARGS_LEN] = {currentStateValue, componentIndex};
        CallJSFunctionAutoRelease(bindScrollFunc, UNDEFINED, args, ARGS_LEN);
        ReleaseJerryValue(currentStateValue, componentIndex, VA_ARG_END_FLAG);
    }

// list specific event switch
#ifdef FEATURE_LIST_SPECIFIC_EVENT_ENABLE
    void OnScrollStart(int16_t index, UIView *view) override
    {
        EventExcute(index, bindScrollStartFunc_);
    }
    void OnItemSelected(int16_t index, UIView *view) override
    {
        EventExcute(index, bindScrollSelectedFunc_);
    }
    void SetBindScrollStartFuncName(jerry_value_t bindScrollStartFunc)
    {
        if (!jerry_value_is_undefined(bindScrollStartFunc)) {
            bindScrollStartFunc_ = jerry_acquire_value(bindScrollStartFunc);
        }
    }
    void SetBindScrollItemSelectedFuncName(jerry_value_t bindScrollItemSelectedFunc)
    {
        if (!jerry_value_is_undefined(bindScrollItemSelectedFunc)) {
            bindScrollSelectedFunc_ = jerry_acquire_value(bindScrollItemSelectedFunc);
        }
    }
#endif // FEATURE_LIST_SPECIFIC_EVENT_ENABLE

    void OnScrollEnd(int16_t index, UIView* view) override
    {
        EventExcute(index, bindScrollEndFunc_);
    }

    void SetBindScrollEndFuncName(jerry_value_t bindScrollEndFunc)
    {
        if (!jerry_value_is_undefined(bindScrollEndFunc)) {
            bindScrollEndFunc_ = jerry_acquire_value(bindScrollEndFunc);
        }
    }

private:
    static constexpr int8_t ARGS_LEN = 2;
    jerry_value_t bindScrollStartFunc_;
    jerry_value_t bindScrollEndFunc_;
    jerry_value_t bindScrollSelectedFunc_;
};
} // namespace ACELite
} // namespace OHOS
#endif // OHOS_ACELITE_EVENT_LISTENER_H
