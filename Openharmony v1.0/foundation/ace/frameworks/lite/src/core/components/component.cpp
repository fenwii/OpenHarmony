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
#include "component.h"
#include "ace_log.h"
#include "ace_mem_base.h"
#include "directive/descriptor_utils.h"
#include "fatal_handler.h"
#include "handler.h"
#include "js_ability_impl.h"
#include "js_app_context.h"
#include "js_app_environment.h"
#include "js_profiler.h"
#include "js_router.h"
#include "key_parser.h"
#include "keys.h"
#include "stylemgr/app_style.h"
#include "stylemgr/app_style_manager.h"
#include "time_util.h"
#include "wrapper/js.h"
#if ENABLED(SECURE_C_FUNCTION)
#include "securec.h"
#endif // ENABLED(SECURE_C_FUNCTION)

namespace OHOS {
namespace ACELite {
static Component::AnimationsNode *g_animationListHead = nullptr;
static bool g_isAnimatorStarted = false;
void Component::HandlerAnimations()
{
    Component::AnimationsNode *point = g_animationListHead;
    while (point != nullptr) {
        point->transitionImpl->Start();
        point = point->next;
    }
    g_isAnimatorStarted = true;
}

void Component::ReleaseAnimations()
{
    Component::AnimationsNode *point = g_animationListHead;
    while (point != nullptr) {
        Component::AnimationsNode *temp = point->next;
        if (point->transitionImpl) {
            delete (point->transitionImpl);
        }
        delete (point);
        point = temp;
    }
    g_animationListHead = nullptr;
    g_isAnimatorStarted = false;
}

Component::Component(jerry_value_t options, jerry_value_t children, AppStyleManager *styleManager)
    : styleManager_(styleManager),
      options_(options),
      children_(UNDEFINED),
      onClickListener_(nullptr),
      onLongPressListener_(nullptr),
      onSwipeListener_(nullptr),
#ifdef JS_TOUCH_EVENT_SUPPORT
      onTouchStartListener_(nullptr),
      onTouchMoveListener_(nullptr),
      onTouchCancelListener_(nullptr),
      onTouchEndListener_(nullptr),
      keyBoardEventListener_(nullptr),
#endif
      viewId_(nullptr),
      componentName_(K_UNKNOWN),
      rendered_(false),
      isAnimationKeyFramesSet_(false),
      curTransitionImpl_(nullptr),
      trans_(nullptr),
      descriptors_(jerry_acquire_value(children)),
      watchersHead_(nullptr),
      height_(-1),
      width_(-1)
{
    // create native element object before combining styles, as style data binding need it
    nativeElement_ = jerry_create_object();
    jerry_value_t global = jerry_get_global_object();
    viewModel_ = jerryx_get_property_str(global, ATTR_ROOT);
    jerry_release_value(global);
    if (styleManager_) {
        // combine app style for this component by app style list.
        // style apply priority: inline(static style) > #id > .class
        START_TRACING_WITH_COMPONENT_NAME(RENDER_COMBINE_STYLE, componentName_);
        styleManager_->CombineStylesForCurrentTag(options_, *this);
        STOP_TRACING();
    }
}

/**
 * @brief After construct a specific component, call this function to setup this component's native view
 * and process attribute/events/style/children properly before binding it on an JS object.
 * It generally calls a series of functions to complete the render work, some of which are needed to be
 * implemented by child class. See step1~step6 function notes.
 *
 * NOTE: Caller should check the return result to decide if it's needed to recycle the component if the
 * rendering failed.
 *
 * @return true if success, false if any error occurs
 */
bool Component::Render()
{
    if (rendered_) {
        HILOG_ERROR(HILOG_MODULE_ACE, "Render one component twice is not allowed.");
        return false;
    }

    PreRender();
    bool renderResult = false;
    // step1: create native view/views
    START_TRACING_WITH_COMPONENT_NAME(RENDER_CREATE_COMPONENT, componentName_);
    renderResult = CreateNativeViews();
    if (!renderResult) {
        return false;
    }
    STOP_TRACING();

    // step2: binding js object with this component
    jerry_set_object_native_pointer(nativeElement_, this, nullptr);

    // step3: parse options for attributes and events, will call child class's according methods
    ParseOptions();
    // step4: apply styles
    START_TRACING_WITH_COMPONENT_NAME(RENDER_APPLY_STYLE, componentName_);
    ApplyStyles();
    STOP_TRACING();

    // step5:process this component's children
    START_TRACING_WITH_COMPONENT_NAME(RENDER_PROCESS_CHILDREN, componentName_);
    renderResult = ProcessChildren();
    STOP_TRACING();
    if (!renderResult) {
        return false;
    } else {
        RecordAnimation();
    }
    PostRender();
    rendered_ = true;

    return renderResult;
}

void Component::Release()
{
    // detach self from fatal handler monitoring
    FatalHandler::GetInstance().DetachComponentNode(this);
    // stop view animation
    if (curTransitionImpl_) {
        curTransitionImpl_->Stop();
    }
    // release all native views
    ReleaseNativeViews();
    // release transition param
    ReleaseTransitionParam();
    // release the common event listeners if any
    ReleaseCommonEventListeners();
    // release children = jerry_create_array() in Init()
    ClearWatchersCommon(watchersHead_);
    // free viewId string if it's set
    ACE_FREE(viewId_);
    // release js object
    jerry_release_value(nativeElement_);
    jerry_release_value(descriptors_);
    jerry_release_value(children_);
    jerry_release_value(viewModel_);
}

bool Component::UpdateView(uint16_t attrKeyId, jerry_value_t attrValue)
{
    if (!KeyParser::IsKeyValid(attrKeyId)) {
        return false;
    }

    START_TRACING_WITH_EXTRA_INFO(SET_ATTR_SET_TO_NATIVE, componentName_, attrKeyId);
    PreUpdate();

    bool updateResult = SetAttribute(attrKeyId, attrValue);
    if (!updateResult) {
        AppStyleItem *styleItem = AppStyleItem::CreateStyleItem(attrKeyId, attrValue);
        if (styleItem != nullptr) {
            updateResult = ApplyStyle(styleItem);
            delete styleItem;
            styleItem = nullptr;
        }
    }

    RefreshRect();
    ReLayoutChildrenIfNeeded(attrKeyId);

    PostUpdate(attrKeyId, updateResult);
    StartAnimation();
    STOP_TRACING();

    return updateResult;
}
void Component::RegisterNamedFunction(const char * const name, jerry_external_handler_t handler) const
{
    JerrySetFuncProperty(nativeElement_, name, handler);
}
// default implementation
bool Component::SetAttribute(uint16_t attrKeyId, jerry_value_t attrValue)
{
    UIView *uiView = GetComponentRootView();
    if ((uiView == nullptr) || !KeyParser::IsKeyValid(attrKeyId) || IS_UNDEFINED(attrValue)) {
        return false;
    }

    // try private first
    bool setResult = SetPrivateAttribute(attrKeyId, attrValue);
    if (!setResult) {
        // this means no private attributes matches, so need to try private ones
        setResult = SetCommonAttribute(*uiView, attrKeyId, attrValue);
    }

    return setResult;
}

bool Component::SetCommonAttribute(UIView &view, const uint16_t attrKeyId, const jerry_value_t attrValue)
{
    switch (attrKeyId) {
        case K_ID: {
            // this string in component itself.
            ACE_FREE(viewId_);
            viewId_ = MallocStringOf(attrValue);
            if (viewId_ == nullptr) {
                return false;
            }
            view.SetViewId(viewId_);
            break;
        }
        case K_SHOW: {
            view.SetVisible(BoolOf(attrValue));
            break;
        }
        case K_REF: {
            uint16_t length = 0;
            char *refName = MallocStringOf(attrValue, &length);
            if (refName == nullptr) {
                break;
            }
            if (length != 0) {
                jerry_value_t refs = jerryx_get_property_str(viewModel_, ATTR_REFS);
                if (jerry_value_is_undefined(refs)) {
                    jerry_release_value(refs);
                    refs = jerry_create_object();
                    jerryx_set_property_str(viewModel_, ATTR_REFS, refs);
                }
                jerryx_set_property_str(refs, refName, nativeElement_);
                jerry_release_value(refs);
            }
            ace_free(refName);
            refName = nullptr;
            break;
        }
        default: {
            // this is not error case, just no one get matched
            return false;
        }
    }

    return true;
}

void Component::ApplyStyles()
{
    const AppStyle *combinedStyle = GetStyleManager()->GetCombinedStyle();
    if (combinedStyle != nullptr) {
        const AppStyleItem *style = combinedStyle->GetFirst();
        while (style != nullptr) {
            START_TRACING_WITH_EXTRA_INFO(APPLY_STYLE_ITEM, componentName_, GetStylePropNameId(style));
            // call children's apply method
            ApplyStyle(style);
            STOP_TRACING();
            style = style->GetNext();
        }
    }
    RefreshRect();
}

bool Component::RefreshRect() const
{
    UIView *uiView = GetComponentRootView();
    if (uiView == nullptr) {
        return false;
    }
    // set view height and width
    uint8_t borderNum = 2;
    if (height_ >= 0) {
        if ((uiView->GetStyle(STYLE_BORDER_WIDTH) < 0) || (uiView->GetStyle(STYLE_PADDING_TOP) < 0) ||
            (uiView->GetStyle(STYLE_PADDING_BOTTOM) < 0)) {
            HILOG_WARN(HILOG_MODULE_ACE, "border and padding size should not less than 0");
        }
        int16_t contentHeight = height_ - (uiView->GetStyle(STYLE_BORDER_WIDTH) * borderNum) -
                                uiView->GetStyle(STYLE_PADDING_TOP) - uiView->GetStyle(STYLE_PADDING_BOTTOM);
        if (contentHeight <= 0) {
            HILOG_WARN(HILOG_MODULE_ACE,
                "component height can not include padding and border width, padding and border will be set 0");
            uiView->SetStyle(STYLE_BORDER_WIDTH, 0);
            uiView->SetStyle(STYLE_PADDING_TOP, 0);
            uiView->SetStyle(STYLE_PADDING_BOTTOM, 0);
            uiView->SetHeight(height_);
        } else {
            uiView->SetHeight(contentHeight);
        }
    }
    if (width_ >= 0) {
        if ((uiView->GetStyle(STYLE_BORDER_WIDTH) < 0) || (uiView->GetStyle(STYLE_PADDING_LEFT) < 0) ||
            (uiView->GetStyle(STYLE_PADDING_RIGHT) < 0)) {
            HILOG_WARN(HILOG_MODULE_ACE, "border and padding size should not less than 0");
        }
        int16_t contentWidth = width_ - (uiView->GetStyle(STYLE_BORDER_WIDTH) * borderNum) -
                               uiView->GetStyle(STYLE_PADDING_LEFT) - uiView->GetStyle(STYLE_PADDING_RIGHT);
        if (contentWidth <= 0) {
            HILOG_WARN(HILOG_MODULE_ACE,
                "component width can not include padding and border width, padding and border will be set 0");
            uiView->SetStyle(STYLE_BORDER_WIDTH, 0);
            uiView->SetStyle(STYLE_PADDING_LEFT, 0);
            uiView->SetStyle(STYLE_PADDING_RIGHT, 0);
            uiView->SetWidth(width_);
        } else {
            uiView->SetWidth(contentWidth);
        }
    }
    return true;
}

bool Component::ApplyStyle(const AppStyleItem *style)
{
    UIView *uiView = GetComponentRootView();
    if (uiView == nullptr) {
        return false;
    }

    // Try private styles first
    bool applyResult = ApplyPrivateStyle(style);
    if (applyResult) {
        // one private style get matched, no need to try private style ones
        return true;
    }
    applyResult = ApplyCommonStyle(*uiView, style);
    return applyResult;
}

/*
 * support common style items:
 *  [left|top]: number                       # flex layout not work
 * 'width': number,
 * 'height': number,
 * 'margin': number,                         # flex layout work
 * 'border-width': number,
 * 'border-color':number,
 * 'border-radius': number,
 * 'background-color': number,
 * 'opacity': number,
 * 'visibility': bool,
 *
 * not suport common style item:
 * border-[left|top|right|bottom]-width,
 * border-[left|top|right|bottom]-color,
 * border-[top|bottom]-[left|right]-radius,
 * border-style,
 * padding:number,
 * right|bottom
 */
bool Component::ApplyCommonStyle(UIView &view, const AppStyleItem *style)
{
    uint16_t styleNameId = GetStylePropNameId(style);
    if (!KeyParser::IsKeyValid(styleNameId)) {
        return false;
    }

    // we do not support pseudo class for all styles, child must handle itself
    if (style->IsPseudoClassItem()) {
        return false;
    }

    switch (styleNameId) {
        case K_HEIGHT: {
            SetHeight(style);
            break;
        }
        case K_WIDTH: {
            SetWidth(style);
            break;
        }
        case K_DISPLAY: {
            SetVisible(view, style);
            break;
        }
        case K_MARGIN: {
            SetMargin(view, *style);
            break;
        }
        case K_MARGIN_BOTTOM: {
            SetBottomMargin(view, *style);
            break;
        }
        case K_MARGIN_LEFT: {
            SetLeftMargin(view, *style);
            break;
        }
        case K_MARGIN_RIGHT: {
            SetRightMargin(view, *style);
            break;
        }
        case K_MARGIN_TOP: {
            SetTopMargin(view, *style);
            break;
        }
        case K_PADDING:
            SetPadding(view, *style);
            break;
        case K_PADDING_BOTTOM:
            SetBottomPadding(view, *style);
            break;
        case K_PADDING_LEFT:
            SetLeftPadding(view, *style);
            break;
        case K_PADDING_RIGHT:
            SetRightPadding(view, *style);
            break;
        case K_PADDING_TOP: {
            SetTopPadding(view, *style);
            break;
        }
        case K_BORDER_BOTTOM_WIDTH:
        case K_BORDER_LEFT_WIDTH:
        case K_BORDER_RIGHT_WIDTH:
        case K_BORDER_TOP_WIDTH:
        case K_BORDER_WIDTH: {
            SetBorderWidth(view, *style);
            break;
        }
        case K_BORDER_BOTTOM_COLOR:
        case K_BORDER_LEFT_COLOR:
        case K_BORDER_RIGHT_COLOR:
        case K_BORDER_TOP_COLOR:
        case K_BORDER_COLOR: {
            SetBorderColor(view, *style);
            break;
        }
        case K_BORDER_RADIUS: {
            SetBorderRadius(view, *style);
            break;
        }
        case K_BACKGROUND_COLOR: {
            SetBackgroundColor(view, *style);
            break;
        }
        case K_LEFT: {
            SetLeft(view, style);
            break;
        }
        case K_TOP: {
            SetTop(view, style);
            break;
        }
        case K_ANIMATION_DURATION: {
            SetAnimationStyle(view, style, K_ANIMATION_DURATION);
            break;
        }
        case K_ANIMATION_TIMING_FUNCTION: {
            SetAnimationStyle(view, style, K_ANIMATION_TIMING_FUNCTION);
            break;
        }
        case K_ANIMATION_FILL_MODE: {
            SetAnimationStyle(view, style, K_ANIMATION_FILL_MODE);
            break;
        }
        case K_ANIMATION_DELAY: {
            SetAnimationStyle(view, style, K_ANIMATION_DELAY);
            break;
        }
        case K_ANIMATION_ITERATION_COUNT: {
            SetAnimationStyle(view, style, K_ANIMATION_ITERATION_COUNT);
            break;
        }
        case K_ANIMATION_NAME: {
            SetAnimationKeyFrames(view, style);
            break;
        }
        default: {
            return false;
        }
    }
    return true;
}

void Component::Invalidate()
{
    UIView *view = GetComponentRootView();
    if (view == nullptr) {
        return;
    }
    view->Invalidate();
}

void Component::ParseOptions()
{
    if (JSUndefined::Is(options_)) {
        HILOG_WARN(HILOG_MODULE_ACE, "options is null");
        return;
    }

    if (!JSObject::Is(options_)) {
        HILOG_WARN(HILOG_MODULE_ACE, "options is not a object type.");
        return;
    }

    jerry_value_t attrsPropValue = jerryx_get_property_str(options_, ATTR_ATTRS);
    const char * const attrEvent = "on";
    jerry_value_t eventPropValue = jerryx_get_property_str(options_, attrEvent);

    if (!jerry_value_is_undefined(attrsPropValue)) {
        START_TRACING(RENDER_PARSE_ATTR);
        ParseAttrs(attrsPropValue);
        STOP_TRACING();
    }

    if (!jerry_value_is_undefined(eventPropValue)) {
        START_TRACING(RENDER_PARSE_EVENT);
        ParseEvent(eventPropValue);
        STOP_TRACING();
    }
    ReleaseJerryValue(eventPropValue, attrsPropValue, VA_ARG_END_FLAG);
}

void Component::SetAnimationKeyFrames(const UIView &view, const AppStyleItem *styleItem)
{
    if (trans_ == nullptr) {
        trans_ = new TransitionParams();

        if (trans_ == nullptr) {
            HILOG_ERROR(HILOG_MODULE_ACE, "create TransitionParams object error");
            return;
        }
    }

    const char * const value = GetStyleStrValue(styleItem);
    if (value == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "animation name is not string value");
        return;
    }

    const AppStyleSheet *styleSheet = GetStyleManager()->GetStyleSheet();
    if (styleSheet == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "styleSheet must set when you set animation attribute");
        return;
    }
    AppStyle *style = styleSheet->GetStyleFromKeyFramesSelectors(value);

    if (style) {
        const AppStyleItem *item = style->GetFirst();
        if (item == nullptr) {
            HILOG_ERROR(HILOG_MODULE_ACE, "keyFrame style is not set!");
            return;
        }
        SetAnimationKeyFrames(item);
    }
}

void Component::SetAnimationKeyFrames(const AppStyleItem *item)
{
    if (item == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "keyFrame style is not set!");
        return;
    }

    const int8_t animatorFrom = 1;
    const int8_t animatorTo = 2;

    isAnimationKeyFramesSet_ = false;
    while (item) {
        const char * const itemValue = item->GetStrValue();

        if ((itemValue == nullptr) || (strlen(itemValue) == 0)) {
            return;
        }
        size_t valLength = strlen(itemValue);
        if ((valLength <= 0) || (valLength >= UINT8_MAX)) {
            item = item->GetNext();
            continue;
        }
        char *animationValue = reinterpret_cast<char *>(ace_malloc(sizeof(char) * (valLength + 1)));
        if (animationValue == nullptr) {
            HILOG_ERROR(HILOG_MODULE_ACE, "malloc animationValue memory heap failed.");
            return;
        }
        if (memcpy_s(animationValue, valLength, itemValue, valLength) != 0) {
            ace_free(animationValue);
            animationValue = nullptr;
            return;
        }
        animationValue[valLength] = '\0';
        int32_t valueTo;
        int32_t valueFrom;
        int16_t keyId = item->GetPropNameId();
        if (keyId == K_OPACITY) {
            valueTo = GetAnimatorValue(animationValue, animatorTo, true);
            valueFrom = GetAnimatorValue(animationValue, animatorFrom, true);
        } else {
            valueTo = GetAnimatorValue(animationValue, animatorTo);
            valueFrom = GetAnimatorValue(animationValue, animatorFrom);
        }
        ace_free(animationValue);
        animationValue = nullptr;
        SetAnimationKeyFrames(keyId, valueFrom, valueTo);
        item = item->GetNext();
    }
}

void Component::SetAnimationKeyFrames(int16_t keyId, int32_t valueFrom, int32_t valueTo)
{
    switch (keyId) {
        case K_ROTATE:
            trans_->transformType = const_cast<char *>(TRANSITION_ROTATE);
            trans_->transform_from = valueFrom;
            trans_->transform_to = valueTo;
            isAnimationKeyFramesSet_ = true;
            break;
        case K_TRANSLATE_X:
            trans_->transformType = const_cast<char *>(TRANSITION_TRANSFORM_X);
            trans_->transform_from = valueFrom;
            trans_->transform_to = valueTo;
            isAnimationKeyFramesSet_ = true;
            break;
        case K_TRANSLATE_Y:
            trans_->transformType = const_cast<char *>(TRANSITION_TRANSFORM_Y);
            trans_->transform_from = valueFrom;
            trans_->transform_to = valueTo;
            isAnimationKeyFramesSet_ = true;
            break;
        case K_HEIGHT:
            trans_->height_from = valueFrom;
            trans_->height_to = valueTo;
            isAnimationKeyFramesSet_ = true;
            break;
        case K_WIDTH:
            trans_->width_from = valueFrom;
            trans_->width_to = valueTo;
            isAnimationKeyFramesSet_ = true;
            break;
        case K_BACKGROUND_COLOR:
            trans_->background_color_from = valueFrom;
            trans_->background_color_to = valueTo;
            isAnimationKeyFramesSet_ = true;
            break;
        case K_OPACITY:
            trans_->opacity_from = valueFrom;
            trans_->opacity_to = valueTo;
            isAnimationKeyFramesSet_ = true;
            break;
        default:
            break;
    }
}

void Component::SetAnimationStyle(const UIView &view, const AppStyleItem *styleItem, const int16_t keyId)
{
    // special for "animation-iteration-count" which value could be a number or string "infinite"
    if ((styleItem == nullptr) || (!const_cast<AppStyleItem *>(styleItem)->UpdateNumValToStr())) {
        HILOG_ERROR(HILOG_MODULE_ACE, "SetAnimationStyle fail");
        return;
    }
    if (trans_ == nullptr) {
        trans_ = new TransitionParams();
        if (trans_ == nullptr) {
            HILOG_ERROR(HILOG_MODULE_ACE, "create TransitionParams object error");
            return;
        }
    }

    const char * const strValue = GetStyleStrValue(styleItem);
    const size_t strLen = GetStyleStrValueLen(styleItem);
    if (strValue == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "animation style item is null");
        return;
    }
    switch (keyId) {
        case K_ANIMATION_DURATION: {
            if (!IsStyleValueTypeString(styleItem)) {
                HILOG_ERROR(HILOG_MODULE_ACE, "style animation during value is invalid!");
                return;
            }
            trans_->during = ParseToMilliseconds(strValue);
            break;
        }
        case K_ANIMATION_TIMING_FUNCTION: {
            uint16_t animationTimingKeyId = KeyParser::ParseKeyId(strValue, strLen);
            switch (animationTimingKeyId) {
                case K_EASE_IN:
                    trans_->easing = EasingType::EASE_IN;
                    break;
                case K_EASE_OUT:
                    trans_->easing = EasingType::EASE_OUT;
                    break;
                case K_EASE_IN_OUT:
                    trans_->easing = EasingType::EASE_IN_OUT;
                    break;
                default:
                    trans_->easing = EasingType::LINEAR;
                    break;
            }
            break;
        }
        case K_ANIMATION_FILL_MODE: {
            uint16_t animationFillKeyId = KeyParser::ParseKeyId(strValue, strLen);
            switch (animationFillKeyId) {
                case K_FORWARDS:
                    trans_->fill = OptionsFill::FORWARDS;
                    break;
                default:
                    trans_->fill = OptionsFill::FNONE;
                    break;
            }
            break;
        }
        case K_ANIMATION_DELAY: {
            if (!IsStyleValueTypeString(styleItem)) {
                HILOG_ERROR(HILOG_MODULE_ACE, "style animation delay value is invalid!");
                return;
            }
            trans_->delay = ParseToMilliseconds(strValue);
            break;
        }
        case K_ANIMATION_ITERATION_COUNT: {
            if (!IsStyleValueTypeString(styleItem)) {
                HILOG_ERROR(HILOG_MODULE_ACE, "style iteration count value is invalid!");
                return;
            }
            trans_->iterations = TransitionImpl::GetNumIterations(strValue);
            break;
        }
        default:
            break;
    }
}

void Component::AddAnimationToList(const TransitionImpl *transitionImpl) const
{
    AnimationsNode *animation = new AnimationsNode();
    if (animation == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "create animation node error in startAnimation");
        return;
    }
    animation->transitionImpl = const_cast<TransitionImpl *>(transitionImpl);
    animation->next = g_animationListHead;
    g_animationListHead = animation;
}

void Component::RecordAnimation()
{
    if (trans_ == nullptr) {
        return;
    }

    if (trans_->during > 0 && isAnimationKeyFramesSet_) {
        UIView *uiView = GetComponentRootView();
        if (uiView) {
            curTransitionImpl_ = new TransitionImpl(*trans_, uiView);
            if (curTransitionImpl_ == nullptr) {
                HILOG_ERROR(HILOG_MODULE_ACE, "create transitionImpl error");
                isAnimationKeyFramesSet_ = false;
                return;
            }
            curTransitionImpl_->Init();
            AddAnimationToList(curTransitionImpl_);
            isAnimationKeyFramesSet_ = false;
            // special for "if" situation, if g_isAnimatorStarted is started means the page has started all the
            // animators, and the current component is created by "if" situation, so the animator can start immediattly
            if (g_isAnimatorStarted) {
                curTransitionImpl_->Start();
            }
        }
    }
}

void Component::StartAnimation()
{
    if (trans_ == nullptr) {
        return;
    }

    if (trans_->during > 0 && isAnimationKeyFramesSet_) {
        UIView *uiView = GetComponentRootView();
        if (uiView) {
            if (curTransitionImpl_ != nullptr) {
                curTransitionImpl_->Stop();
            }
            curTransitionImpl_ = new TransitionImpl(*trans_, uiView);
            if (curTransitionImpl_ == nullptr) {
                HILOG_ERROR(HILOG_MODULE_ACE, "create transitionImpl error!");
                isAnimationKeyFramesSet_ = false;
                return;
            }
            curTransitionImpl_->Init();
            AddAnimationToList(curTransitionImpl_);
            curTransitionImpl_->Start();
            isAnimationKeyFramesSet_ = false;
        }
    }
}

void Component::ReleaseTransitionParam()
{
    if (trans_) {
        delete trans_;
        trans_ = nullptr;
    }
}

int32_t Component::GetAnimatorValue(char *animatorValue, const int8_t index, bool isOpacity) const
{
    if ((animatorValue == nullptr) || (strlen(animatorValue) == 0) || (strlen(animatorValue) >= UINT8_MAX)) {
        return 0;
    }
    const int8_t animatorfrom = 1;
    const int8_t animatorTo = 2;
    if ((index != animatorfrom) && (index != animatorTo)) {
        return 0;
    }

    char *next = nullptr;
    // try to get from part
    char *value = strtok_s(animatorValue, ANIMATION_VALUE_SEP, &next);
    if (index == animatorTo) {
        // get to part then if needed
        if (value != nullptr) {
            value = strtok_s(nullptr, ANIMATION_VALUE_SEP, &next);
        }
    }
    if (value == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "GetAnimatorValue strtok_s failed.");
        return 0;
    }

    long convertedValue = isOpacity ? (strtod(value, nullptr) * ALPHA_MAX) : strtol(value, nullptr, DEC);
    if (TransitionImpl::IsEndWith(value, "rad")) {
        uint8_t degConversionRate = 57;
        convertedValue = convertedValue * degConversionRate;
    }
    return convertedValue;
}

/**
 * check if the pass-in attrValue is an Expression, if it is, calculate it and bind watcher instance.
 * if it's not, just return the passed-in attrValue itself.
 */
jerry_value_t Component::ParseExpression(jerry_value_t attrKey, jerry_value_t attrValue)
{
    jerry_value_t options = jerry_create_object();
    JerrySetNamedProperty(options, ARG_WATCH_EL, nativeElement_);
    JerrySetNamedProperty(options, ARG_WATCH_ATTR, attrKey);
    jerry_value_t watcher = CallJSWatcher(attrValue, WatcherCallbackFunc, options);
    jerry_value_t propValue = UNDEFINED;
    if (IS_UNDEFINED(watcher) || jerry_value_is_error(watcher)) {
        HILOG_ERROR(HILOG_MODULE_ACE, "Failed to create Watcher instance.");
    } else {
        InsertWatcherCommon(watchersHead_, watcher);
        propValue = jerryx_get_property_str(watcher, "_lastValue");
    }
    jerry_release_value(options);
    return propValue;
}

void Component::ParseAttrs(jerry_value_t attrs)
{
    jerry_value_t attrKeys = jerry_get_object_keys(attrs);
    if (jerry_value_is_undefined(attrKeys)) {
        HILOG_ERROR(HILOG_MODULE_ACE, "None attributes to parse.");
        return;
    }

    uint16_t length = jerry_get_array_length(attrKeys);
    uint16_t attrKeyStrLength = 0;
    for (uint32_t index = 0; index < length; ++index) {
        jerry_value_t attrKey = jerry_get_property_by_index(attrKeys, index);
        jerry_value_t attrValue = jerry_get_property(attrs, attrKey);
        jerry_value_t newAttrValue = attrValue;

        if (jerry_value_is_function(attrValue)) {
            START_TRACING_WITH_COMPONENT_NAME(SET_ATTR_PARSE_EXPRESSION, componentName_);
            newAttrValue = ParseExpression(attrKey, attrValue);
            STOP_TRACING();
        }

        char *attrKeyStr = MallocStringOf(attrKey, &attrKeyStrLength);
        if (attrKeyStr != nullptr) {
            if (attrKeyStrLength != 0) {
                uint16_t attrKeyId = KeyParser::ParseKeyId(attrKeyStr, attrKeyStrLength);
                // ignore the return result for no need to invalided views here
                START_TRACING_WITH_EXTRA_INFO(SET_ATTR_SET_TO_NATIVE, componentName_, attrKeyId);
                SetAttribute(attrKeyId, newAttrValue);
                STOP_TRACING();
            }
            ace_free(attrKeyStr);
            attrKeyStr = nullptr;
        }
        if (newAttrValue != attrValue) {
            // the new value has been calculated out by ParseExpression, need to be released
            jerry_release_value(newAttrValue);
        }
        ReleaseJerryValue(attrKey, attrValue, VA_ARG_END_FLAG);
    }
    jerry_release_value(attrKeys);
}

void Component::SetClickEventListener(UIView &view, const jerry_value_t eventFunc, const uint16_t eventTypeId)
{
    onClickListener_ = new ViewOnClickListener(eventFunc, eventTypeId);
    if (onClickListener_ == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "click listener create failed");
        return;
    }

    view.SetOnClickListener(onClickListener_);
    view.SetTouchable(true);
}

#ifdef JS_TOUCH_EVENT_SUPPORT
void Component::SetTouchStartEventListener(UIView &view, jerry_value_t eventFunc, uint16_t eventTypeId)
{
    onTouchStartListener_ = new ViewOnTouchStartListener(eventFunc, eventTypeId);
    if (onTouchStartListener_ == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "touch move event listener create failed");
        return;
    }

    view.SetOnTouchListener(onTouchStartListener_);
    view.SetTouchable(true);
}

void Component::SetTouchMoveEventListener(UIView &view, jerry_value_t eventFunc, uint16_t eventTypeId)
{
    onTouchMoveListener_ = new ViewOnTouchMoveListener(eventFunc, eventTypeId);
    if (onTouchMoveListener_ == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "touch start event listener create failed");
        return;
    }

    view.SetOnDragListener(onTouchMoveListener_);
    view.SetTouchable(true);
    view.SetDraggable(true);
}

void Component::SetTouchCancelEventListener(UIView &view, jerry_value_t eventFunc, uint16_t eventTypeId)
{
    onTouchCancelListener_ = new ViewOnTouchCancelListener(eventFunc, eventTypeId);
    if (onTouchCancelListener_ == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "touch cancel event listener create failed");
        return;
    }

    view.SetOnTouchListener(onTouchCancelListener_);
    view.SetTouchable(true);
    view.SetDraggable(true);
}

void Component::SetTouchEndEventListener(UIView &view, jerry_value_t eventFunc, uint16_t eventTypeId)
{
    onTouchEndListener_ = new ViewOnTouchEndListener(eventFunc, eventTypeId);
    if (onTouchEndListener_ == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "touch end event listener create failed");
        return;
    }

    view.SetOnTouchListener(onTouchEndListener_);
    view.SetTouchable(true);
}

void Component::SetKeyBoardEventListener(jerry_value_t eventFunc, uint16_t eventTypeId)
{
    RootView *rootView = RootView::GetInstance();
    if (rootView == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "get rootView is nullptr");
        return;
    }
    keyBoardEventListener_ = new KeyBoardEventListener(eventFunc, eventTypeId);
    if (keyBoardEventListener_ == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "on key borard event listener create failed");
        return;
    }
    rootView->SetOnKeyActListener(keyBoardEventListener_);
}
#endif

void Component::SetLongPressEventListener(UIView &view, const jerry_value_t eventFunc, const uint16_t eventTypeId)
{
    onLongPressListener_ = new ViewOnLongPressListener(eventFunc, eventTypeId);
    if (onLongPressListener_ == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "long press listener create failed");
        return;
    }

    view.SetOnLongPressListener(onLongPressListener_);
    view.SetTouchable(true);
}

void Component::SetSwipeEventListener(UIView &view, jerry_value_t eventFunc)
{
    onSwipeListener_ = new ViewOnSwipeListener(eventFunc);
    if (onSwipeListener_ == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "swipe listener create failed");
        return;
    }

    view.SetOnDragListener(onSwipeListener_);
    view.SetDraggable(true);
    view.SetTouchable(true);
    view.SetIntercept(false);
}

// default implementation
bool Component::RegisterEventListener(uint16_t eventTypeId, jerry_value_t funcValue)
{
    UIView *uiView = GetComponentRootView();
    if ((uiView == nullptr) || !KeyParser::IsKeyValid(eventTypeId) || IS_UNDEFINED(funcValue)) {
        return false;
    }

    bool registerResult = RegisterPrivateEventListener(eventTypeId, funcValue);
    if (registerResult) {
        return true;
    }

    return RegisterCommonEventListener(*uiView, eventTypeId, funcValue);
}

bool Component::RegisterCommonEventListener(UIView &view, const uint16_t eventTypeId, const jerry_value_t funcValue)
{
    switch (eventTypeId) {
        case K_CLICK: {
            SetClickEventListener(view, funcValue, eventTypeId);
            break;
        }
        case K_LONGPRESS: {
            SetLongPressEventListener(view, funcValue, eventTypeId);
            break;
        }
#ifdef JS_TOUCH_EVENT_SUPPORT
        case K_KEY: {
            SetKeyBoardEventListener(funcValue, eventTypeId);
            break;
        }
        case K_TOUCHSTART: {
            SetTouchStartEventListener(view, funcValue, eventTypeId);
            break;
        }
        case K_TOUCHCANCEL: {
            SetTouchCancelEventListener(view, funcValue, eventTypeId);
            break;
        }
        case K_TOUCHMOVE: {
            SetTouchMoveEventListener(view, funcValue, eventTypeId);
            break;
        }
        case K_TOUCHEND: {
            SetTouchEndEventListener(view, funcValue, eventTypeId);
            break;
        }
#endif
        case K_SWIPE: {
            SetSwipeEventListener(view, funcValue);
            break;
        }
        default: {
            return false;
        }
    }
    return true;
}

void Component::ReleaseCommonEventListeners()
{
    ACE_DELETE(onClickListener_);
    ACE_DELETE(onLongPressListener_);
#ifdef JS_TOUCH_EVENT_SUPPORT
    ACE_DELETE(keyBoardEventListener_);
    ACE_DELETE(onTouchStartListener_);
    ACE_DELETE(onTouchCancelListener_);
    ACE_DELETE(onTouchMoveListener_);
    ACE_DELETE(onTouchEndListener_);
#endif
    ACE_DELETE(onSwipeListener_);
}

void Component::AppendDescriptorOrElements(UIViewGroup *viewGroup, const JSValue descriptorOrElements)
{
    if (!JSUndefined::Is(descriptorOrElements)) {
        uint16_t size = JSArray::Length(descriptorOrElements);
        for (uint16_t idx = 0; idx < size; ++idx) {
            JSValue descriptorOrElement = JSArray::Get(descriptorOrElements, idx);
            AppendDescriptorOrElement(viewGroup, descriptorOrElement);
            JSRelease(descriptorOrElement);
        }
    }
}

void Component::ReLayoutChildrenIfNeeded(uint16_t attrKeyId) const
{
    UIView *uiView = GetComponentRootView();
    if ((uiView == nullptr) || !KeyParser::IsKeyValid(attrKeyId)) {
        return;
    }

    if (attrKeyId == K_HEIGHT || attrKeyId == K_WIDTH || attrKeyId == K_MARGIN || attrKeyId == K_MARGIN_BOTTOM ||
        attrKeyId == K_MARGIN_LEFT || attrKeyId == K_MARGIN_RIGHT || attrKeyId == K_MARGIN_TOP ||
        attrKeyId == K_PADDING || attrKeyId == K_PADDING_BOTTOM || attrKeyId == K_PADDING_LEFT ||
        attrKeyId == K_PADDING_RIGHT || attrKeyId == K_PADDING_TOP || attrKeyId == K_BORDER_BOTTOM_WIDTH ||
        attrKeyId == K_BORDER_LEFT_WIDTH || attrKeyId == K_BORDER_RIGHT_WIDTH || attrKeyId == K_BORDER_TOP_WIDTH ||
        attrKeyId == K_BORDER_WIDTH || attrKeyId == K_BORDER_RADIUS || attrKeyId == K_LEFT || attrKeyId == K_TOP) {
        UIView *parent = uiView->GetParent();
        if (parent != nullptr) {
            parent->LayoutChildren();
            parent->Invalidate();
        }
    }
}

void Component::ParseEvent(jerry_value_t events)
{
    jerry_value_t eventKeys = jerry_get_object_keys(events);
    if (jerry_value_is_undefined(eventKeys)) {
        HILOG_ERROR(HILOG_MODULE_ACE, "None event to parse.");
        return;
    }

    uint16_t length = jerry_get_array_length(eventKeys);
    if (length == 0) {
        HILOG_ERROR(HILOG_MODULE_ACE, "None event to parse.");
        jerry_release_value(eventKeys);
        return;
    }

    uint16_t eventTypeStrLen = 0;
    for (uint16_t index = 0; index < length; ++index) {
        jerry_value_t eventKey = jerry_get_property_by_index(eventKeys, index);
        jerry_value_t eventFunc = jerry_get_property(events, eventKey);

        char *eventType = MallocStringOf(eventKey, &eventTypeStrLen);
        if (eventType != nullptr) {
            if (eventTypeStrLen != 0) {
                uint16_t eventTypeId = KeyParser::ParseKeyId(eventType, eventTypeStrLen);
                bool isSuccess = RegisterEventListener(eventTypeId, eventFunc);
                if (!isSuccess) {
                    HILOG_ERROR(HILOG_MODULE_ACE, "Register event listener error.");
                }
            }
            ace_free(eventType);
            eventType = nullptr;
        }
        ReleaseJerryValue(eventKey, eventFunc, VA_ARG_END_FLAG);
    }
    jerry_release_value(eventKeys);
}

// set component's left coordinate relative to its parent
void Component::SetLeft(UIView &view, const AppStyleItem *styleItem) const
{
    int16_t left = GetStylePixelValue(styleItem);
    view.SetX(left);
}

// set component's top coordinate relative to its parent
void Component::SetTop(UIView &view, const AppStyleItem *styleItem) const
{
    int16_t top = GetStylePixelValue(styleItem);
    view.SetY(top);
}

void Component::SetHeight(const AppStyleItem *styleItem)
{
    height_ = GetStylePixelValue(styleItem);
}

void Component::SetWidth(const AppStyleItem *styleItem)
{
    width_ = GetStylePixelValue(styleItem);
}

void Component::SetVisible(UIView &view, const AppStyleItem *styleItem) const
{
    if (!IsStyleValueTypeString(styleItem)) {
        HILOG_ERROR(HILOG_MODULE_ACE, "Visible style value is invalid!");
        return;
    }
    const char * const strValue = GetStyleStrValue(styleItem);
    if (strValue == nullptr) {
        return;
    }

    uint16_t valueId = KeyParser::ParseKeyId(strValue, GetStyleStrValueLen(styleItem));
    view.SetVisible((valueId == K_NONE) ? false : true);
}

void Component::SetBackgroundColor(UIView &view, const AppStyleItem &styleItem) const
{
    uint32_t color = 0;
    uint8_t alpha = OPA_OPAQUE;

    if (GetStyleColorValue(&styleItem, color, alpha)) {
        ColorType backgroundRGBColor = GetRGBColor(color);
        view.SetStyle(STYLE_BACKGROUND_COLOR, backgroundRGBColor.full);
        view.SetStyle(STYLE_BACKGROUND_OPA, alpha);
    }
}

void Component::SetOpacity(UIView &view, const AppStyleItem &styleItem) const
{
    if (styleItem.GetValueType() != STYLE_PROP_VALUE_TYPE_FLOATING) {
        return;
    }
    double opacity = styleItem.GetFloatingValue();
    view.SetStyle(STYLE_BACKGROUND_OPA, view.GetStyle(STYLE_BACKGROUND_OPA) * opacity);
    view.SetStyle(STYLE_IMAGE_OPA, view.GetStyle(STYLE_IMAGE_OPA) * opacity);
    view.SetStyle(STYLE_LINE_OPA, view.GetStyle(STYLE_LINE_OPA) * opacity);
    view.SetStyle(STYLE_TEXT_OPA, view.GetStyle(STYLE_TEXT_OPA) * opacity);
}

void Component::SetMargin(UIView &view, const AppStyleItem &styleItem) const
{
    SetLeftMargin(view, styleItem);
    SetTopMargin(view, styleItem);
    SetRightMargin(view, styleItem);
    SetBottomMargin(view, styleItem);
}

void Component::SetLeftMargin(UIView &view, const AppStyleItem &styleItem) const
{
    view.SetStyle(STYLE_MARGIN_LEFT, GetStylePixelValue(&styleItem));
}

void Component::SetTopMargin(UIView &view, const AppStyleItem &styleItem) const
{
    view.SetStyle(STYLE_MARGIN_TOP, GetStylePixelValue(&styleItem));
}

void Component::SetRightMargin(UIView &view, const AppStyleItem &styleItem) const
{
    view.SetStyle(STYLE_MARGIN_RIGHT, GetStylePixelValue(&styleItem));
}

void Component::SetBottomMargin(UIView &view, const AppStyleItem &styleItem) const
{
    view.SetStyle(STYLE_MARGIN_BOTTOM, GetStylePixelValue(&styleItem));
}

void Component::SetPadding(UIView &view, const AppStyleItem &styleItem) const
{
    SetLeftPadding(view, styleItem);
    SetTopPadding(view, styleItem);
    SetRightPadding(view, styleItem);
    SetBottomPadding(view, styleItem);
}

void Component::SetLeftPadding(UIView &view, const AppStyleItem &styleItem) const
{
    int32_t paddingLeft = GetStylePixelValue(&styleItem);
    if (paddingLeft >= 0) {
        view.SetStyle(STYLE_PADDING_LEFT, paddingLeft);
    }
}

void Component::SetTopPadding(UIView &view, const AppStyleItem &styleItem) const
{
    int32_t paddingTop = GetStylePixelValue(&styleItem);
    if (paddingTop >= 0) {
        view.SetStyle(STYLE_PADDING_TOP, paddingTop);
    }
}

void Component::SetRightPadding(UIView &view, const AppStyleItem &styleItem) const
{
    int32_t paddingRight = GetStylePixelValue(&styleItem);
    if (paddingRight >= 0) {
        view.SetStyle(STYLE_PADDING_RIGHT, paddingRight);
    }
}

void Component::SetBottomPadding(UIView &view, const AppStyleItem &styleItem) const
{
    int32_t paddingBottom = GetStylePixelValue(&styleItem);
    if (paddingBottom >= 0) {
        view.SetStyle(STYLE_PADDING_BOTTOM, paddingBottom);
    }
}

void Component::SetBorderColor(UIView &view, const AppStyleItem &styleItem) const
{
    uint32_t color = 0;
    uint8_t alpha = OPA_OPAQUE;
    if (GetStyleColorValue(&styleItem, color, alpha)) {
        view.SetStyle(STYLE_BORDER_COLOR, GetRGBColor(color).full);
        view.SetStyle(STYLE_BORDER_OPA, alpha);
    }
}

void Component::SetBorderRadius(UIView &view, const AppStyleItem &styleItem) const
{
    view.SetStyle(STYLE_BORDER_RADIUS, GetStylePixelValue(&styleItem));
}

void Component::SetBorderWidth(UIView &view, const AppStyleItem &styleItem) const
{
    view.SetStyle(STYLE_BORDER_WIDTH, GetStylePixelValue(&styleItem));
}

jerry_value_t Component::SetListForWatcher(jerry_value_t getter, jerry_value_t children)
{
    jerry_value_t options = jerry_create_object();
    JerrySetNamedProperty(options, ARG_WATCH_EL, nativeElement_);

    jerry_value_t watcher = CallJSWatcher(getter, ListForWatcherCallbackFunc, options);
    if (IS_UNDEFINED(watcher) || jerry_value_is_error(watcher)) {
        HILOG_ERROR(HILOG_MODULE_ACE, "Failed to create ListForWatcher instance.");
    } else {
        InsertWatcherCommon(watchersHead_, watcher);
    }
    jerry_release_value(options);
    return UNDEFINED;
}

void Component::HandleListForDireactive()
{
    uint16_t childrenLength = jerry_get_array_length(descriptors_);
    for (uint16_t index = 0; index < childrenLength; index++) {
        jerry_value_t child = jerry_get_property_by_index(descriptors_, index);
        jerry_value_t getterName = jerry_create_string(reinterpret_cast<const jerry_char_t *>(DESCRIPTOR_ATTR_GETTER));
        // add watcher to the array which the getter function returned
        if (JerryHasProperty(child, getterName)) {
            jerry_value_t getter = jerry_get_property(child, getterName);
            SetListForWatcher(getter, descriptors_);
            jerry_release_value(getter);
        }
        ReleaseJerryValue(getterName, child, VA_ARG_END_FLAG);
    }
}

void Component::AppendChildren(UIViewGroup *viewGroup)
{
    if (JSUndefined::Is(descriptors_)) {
        return;
    }

    children_ = JSArray::Create(0);
    uint16_t size = JSArray::Length(descriptors_);
    for (uint16_t index = 0; index < size; ++index) {
        JSValue descriptorOrElement = JSArray::Get(descriptors_, index);
        if (!JSUndefined::Is(descriptorOrElement)) {
            bool isDescriptor = AppendDescriptorOrElement(viewGroup, descriptorOrElement);
            if (isDescriptor) {
                CreateDirectiveWatcher(descriptorOrElement);
            }
        }
        JSRelease(descriptorOrElement);
    }
}

bool Component::AppendDescriptorOrElement(UIViewGroup *viewGroup, const jerry_value_t descriptorOrElement)
{
    if (DescriptorUtils::IsIfDescriptor(descriptorOrElement)) {
        AppendIfDescriptor(viewGroup, descriptorOrElement);
        return true;
    }

    if (DescriptorUtils::IsForDescriptor(descriptorOrElement)) {
        AppendForDescriptor(viewGroup, descriptorOrElement);
        return true;
    }
    AppendElement(viewGroup, descriptorOrElement);
    return false;
}

void Component::AppendIfDescriptor(UIViewGroup *viewGroup, const jerry_value_t descriptor)
{
    bool isShown = DescriptorUtils::IsIfDescriptorShown(descriptor);
    if (isShown) {
        JSValue decriptorOrElement = DescriptorUtils::GetDescriptorRendered(descriptor);
        if (!JSUndefined::Is(decriptorOrElement)) {
            AppendDescriptorOrElement(viewGroup, decriptorOrElement);
            JSRelease(decriptorOrElement);
        } else {
            // Don't release decriptorOrElement
            // because decriptorOrElement is the result of jerry_create_object but jerry_get_property
            decriptorOrElement = DescriptorUtils::RenderIfDescriptor(descriptor);
            AppendDescriptorOrElement(viewGroup, decriptorOrElement);

            // does decriptorOrElement need to be release if decriptorOrElement is descriptor
        }
    } else {
        DescriptorUtils::DelIfDescriptorRendered(descriptor);
    }
}
void Component::AppendForDescriptor(UIViewGroup *viewGroup, const jerry_value_t descriptor)
{
    JSValue descriptorOrelements = DescriptorUtils::GetDescriptorRendered(descriptor);
    if (!JSUndefined::Is(descriptorOrelements)) {
        AppendDescriptorOrElements(viewGroup, descriptorOrelements);
        JSRelease(descriptorOrelements);
    } else {
        // Don't release decriptorOrElements
        // because decriptorOrElements is the result of jerry_create_object but jerry_get_property
        descriptorOrelements = DescriptorUtils::RenderForDescriptor(descriptor);
        AppendDescriptorOrElements(viewGroup, descriptorOrelements);
    }
}
void Component::AppendElement(UIViewGroup *viewGroup, const jerry_value_t element)
{
    Component *component = nullptr;
    if (!JSObject::GetNativePointer(element, reinterpret_cast<void **>(&component))) {
        // if get binding component native pointer failed from a child element, just release that element
        HILOG_ERROR(HILOG_MODULE_ACE, "fatal error, no component is binded to the child element, not allowed.");
        // try to release this element and its children, it means we drop them all
        DescriptorUtils::ReleaseDescriptorOrElement(element);
        return;
    }
    JSArray::Push(children_, element);
    viewGroup->Add(component->GetComponentRootView());
}
void Component::CreateDirectiveWatcher(jerry_value_t descriptor)
{
    JSValue watcher = DescriptorUtils::CreateDescriptorWatcher(nativeElement_, descriptor);
    if (!JSUndefined::Is(watcher)) {
        InsertWatcherCommon(watchersHead_, watcher);
    }
}
void Component::HandleChildrenChange(jerry_value_t descriptor)
{
    UIViewGroup *viewGroup = reinterpret_cast<UIViewGroup *>(GetComponentRootView());

    if (viewGroup != nullptr) {
        viewGroup->RemoveAll();
    } else {
        HILOG_ERROR(HILOG_MODULE_ACE, "Get root component error");
        return;
    }

    if (!JSUndefined::Is(children_)) {
        JSRelease(children_);
        children_ = JSArray::Create(0);
    }

    uint16_t size = JSArray::Length(descriptors_);
    for (uint16_t idx = 0; idx < size; ++idx) {
        JSValue descriptorOrElement = JSArray::Get(descriptors_, idx);
        if (IS_UNDEFINED(descriptorOrElement)) {
            continue;
        }
        if (descriptorOrElement == descriptor) {
            UpdateDescriptor(viewGroup, descriptorOrElement);
        } else {
            ReappendDescriptorOrElement(viewGroup, descriptorOrElement);
        }
        JSRelease(descriptorOrElement);
    }

    viewGroup->LayoutChildren();
    viewGroup->Invalidate();
}

void Component::UpdateDescriptor(UIViewGroup *viewGroup, const jerry_value_t descriptor)
{
    if (DescriptorUtils::IsIfDescriptor(descriptor)) {
        AppendIfDescriptor(viewGroup, descriptor);
    } else if (DescriptorUtils::IsForDescriptor(descriptor)) {
        // Release descriptor last rendered
        DescriptorUtils::DelForDescriptorRendered(descriptor);

        // Re-render descriptor
        JSValue descriptorOrElements = DescriptorUtils::RenderForDescriptor(descriptor);
        AppendDescriptorOrElements(viewGroup, descriptorOrElements);
    } else {
        // never
    }
}

void Component::ReappendDescriptorOrElement(UIViewGroup *viewGroup, const jerry_value_t descriptor)
{
    if (DescriptorUtils::IsIfDescriptor(descriptor)) {
        JSValue descriptorOrElement = DescriptorUtils::GetDescriptorRendered(descriptor);
        if (!JSUndefined::Is(descriptorOrElement)) {
            AppendDescriptorOrElement(viewGroup, descriptor);
        }
        JSRelease(descriptorOrElement);
    } else if (DescriptorUtils::IsForDescriptor(descriptor)) {
        JSValue descriptorOrElements = DescriptorUtils::GetDescriptorRendered(descriptor);
        if (!JSUndefined::Is(descriptorOrElements)) {
            AppendDescriptorOrElements(viewGroup, descriptorOrElements);
        }
        JSRelease(descriptorOrElements);
    } else {
        AppendElement(viewGroup, descriptor);
    }
}

int32_t Component::GetStylePixelValue(const AppStyleItem *style, int32_t defaultValue) const
{
    if (style->GetValueType() == STYLE_PROP_VALUE_TYPE_NUMBER) {
        return style->GetNumValue();
    }
    if (style->GetValueType() == STYLE_PROP_VALUE_TYPE_STRING) {
        if (style->GetStrValue() == nullptr) {
            HILOG_WARN(HILOG_MODULE_ACE, "Get Style PixelValue failed, return default value!");
            return defaultValue;
        }
        return strtol(style->GetStrValue(), nullptr, DEC);
    }
    return defaultValue;
}

int16_t Component::GetStyleDegValue(const AppStyleItem *style, int16_t defaultValue) const
{
    if (style->GetValueType() == STYLE_PROP_VALUE_TYPE_NUMBER) {
        return style->GetNumValue();
    }
    if (style->GetValueType() == STYLE_PROP_VALUE_TYPE_STRING) {
        if (style->GetStrValue() == nullptr) {
            HILOG_WARN(HILOG_MODULE_ACE, "Get Style DegValue failed, return default value!");
            return defaultValue;
        }
        return strtol(style->GetStrValue(), nullptr, DEC);
    }
    return defaultValue;
}

bool Component::GetStyleColorValue(const AppStyleItem *style, uint32_t &color, uint8_t &alpha) const
{
    if (style->GetValueType() == STYLE_PROP_VALUE_TYPE_NUMBER) {
        color = style->GetNumValue();
        alpha = OPA_OPAQUE;
        return true;
    } else if (style->GetValueType() == STYLE_PROP_VALUE_TYPE_STRING) {
        return ParseColor(style->GetStrValue(), color, alpha);
    } else {
        HILOG_ERROR(HILOG_MODULE_ACE, "invalid color format!");
        return false;
    }
}
} // namespace ACELite
} // namespace OHOS
