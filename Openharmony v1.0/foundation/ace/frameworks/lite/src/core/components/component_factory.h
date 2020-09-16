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
#ifndef OHOS_ACELITE_COMPONENT_FACTORY_H
#define OHOS_ACELITE_COMPONENT_FACTORY_H

#include "acelite_config.h"

#ifdef FEATURE_COMPONENT_ANALOG_CLOCK
#include "analog_clock_component.h"
#include "clock_hand_component.h"
#endif // FEATURE_COMPONENT_ANALOG_CLOCK
#ifdef FEATURE_COMPONENT_CAMERA
#include "camera_component.h"
#endif // FEATURE_COMPONENT_CAMERA
#ifdef FEATURE_COMPONENT_CANVAS
#include "canvas_component.h"
#endif // FEATURE_COMPONENT_CANVAS
#include "chart_component.h"
#include "component.h"
#include "div_component.h"
#include "fatal_handler.h"
#include "image_component.h"
#include "input_component.h"
#include "js_fwk_common.h"
#include "key_parser.h"
#include "keys.h"
#include "list_component.h"
#include "marquee_component.h"
#include "non_copyable.h"
#include "picker_view_component.h"
#include "progress_component.h"
#include "slider_component.h"
#include "swiper_component.h"
#include "switch_component.h"
#include "image_animator_component.h"
#ifdef FEATURE_COMPONENT_TABS
#include "tab_bar_component.h"
#include "tab_content_component.h"
#include "tabs_component.h"
#endif // FEATURE_COMPONENT_TABS
#include "text_component.h"
#include "video_component.h"

namespace OHOS {
namespace ACELite {
class ComponentFactory final : public MemoryHeap {
public:
    ACE_DISALLOW_COPY_AND_MOVE(ComponentFactory);
    ~ComponentFactory() {}
    static Component* CreateComponent(uint16_t componentNameId, jerry_value_t options, jerry_value_t children)
    {
        if (!KeyParser::IsKeyValid(componentNameId)) {
            return nullptr;
        }

        JsAppContext* context = JsAppContext::GetInstance();
        if (context == nullptr) {
            return nullptr;
        }
        AppStyleManager* styleManager = const_cast<AppStyleManager *>(context->GetStyleManager());

        Component* component;
        switch (componentNameId) {
#ifdef FEATURE_COMPONENT_CAMERA
            case K_CAMERA:
                component = new CameraComponent(options, children, styleManager);
                break;
#endif
#ifdef FEATURE_COMPONENT_CANVAS
            case K_CANVAS:
                component = new CanvasComponent(options, children, styleManager);
                break;
#endif // FEATURE_COMPONENT_CANVAS
            case K_DIV:
                component = new DivComponent(options, children, styleManager, DivComponent::LayoutType::FLEX);
                break;
            case K_STACK:
                component = new DivComponent(options, children, styleManager, DivComponent::LayoutType::POSITION);
                break;
            case K_IMAGE:
                component = new ImageComponent(options, children, styleManager);
                break;
            case K_IMAGE_ANIMATOR:
                component = new ImageAnimatorComponent(options, children, styleManager);
                break;
            case K_PROGRESS:
                component = new ProgressComponent(options, children, styleManager);
                break;
#ifdef FEATURE_COMPONENT_TABS
            case K_TAB_BAR:
                component = new TabBarComponent(options, children, styleManager);
                break;
            case K_TAB_CONTENT:
                component = new TabContentComponent(options, children, styleManager);
                break;
            case K_TABS:
                component = new TabsComponent(options, children, styleManager);
                break;
#endif // FEATURE_COMPONENT_TABS
            case K_TEXT:
                component = new TextComponent(options, children, styleManager);
                break;
            case K_SWIPER:
                component = new SwiperComponent(options, children, styleManager);
                break;
            case K_SWITCH:
                component = new SwitchComponent(options, children, styleManager);
                break;
            case K_SLIDER:
                component = new SliderComponent(options, children, styleManager);
                break;
            case K_LIST:
                component = new ListComponent(options, children, styleManager);
                break;
            case K_LIST_ITEM:
                component = new DivComponent(options, children, styleManager, DivComponent::LayoutType::FLEX);
                break;
#ifdef FEATURE_COMPONENT_ANALOG_CLOCK
            case K_CLOCK_HAND:
                component = new ClockHandComponent(options, children, styleManager);
                break;
            case K_ANALOG_CLOCK:
                component = new AnalogClockComponent(options, children, styleManager);
                break;
#endif // FEATURE_COMPONENT_ANALOG_CLOCK
            case K_INPUT:
                component = new InputComponent(options, children, styleManager);
                break;
            case K_MARQUEE:
                component = new MarqueeComponent(options, children, styleManager);
                break;
            case K_CHART:
                component = new ChartComponent(options, children, styleManager);
                break;
            case K_PICKER_VIEW:
                component = new PickerViewComponent(options, children, styleManager);
                break;
#ifdef FEATURE_COMPONENT_VIDEO
            case K_VIDEO:
                component = new VideoComponent(options, children, styleManager);
                break;
#endif // FEATURE_COMPONENT_VIDEO
            default:
                component = nullptr;
                break;
        }

        FatalHandler::GetInstance().AttachComponentNode(component);
        return component;
    }
};
} // namespace ACELite
} // namespace OHOS

#endif // OHOS_ACELITE_COMPONENT_FACTORY_H
