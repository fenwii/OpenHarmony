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

/**
 * @addtogroup Graphic
 * @{
 *
 * @brief Defines a lightweight graphics system that provides basic UI and container views,
 *        including buttons, images, labels, lists, animators, scroll views, swipe views, and layouts.
 *        This system also provides the Design for X (DFX) capability to implement features such as
 *        view rendering, animation, and input event distribution.
 *
 * @since 1.0
 * @version 1.0
 */

/**
 * @file aod_callback.h
 *
 * @brief Defines the callback for the touch event notification in screen-off mode.
 *
 * @since 1.0
 * @version 1.0
 */

#include "components/ui_view.h"
#include "graphic_config.h"

#ifndef AOD_CALLBACK_H
#define AOD_CALLBACK_H

#if ENABLE_AOD
namespace OHOS {
/**
 * @brief Called when a tap event occurs on the state machine. The screen-off display module will be notified of this
 *        event.
 *
 * @param view Indicates the view instance where the tap event occurs.
 */
void OnClickEventHappen(UIView& view);

/**
 * @brief Called when a sliding end event occurs on the state machine. The screen-off display module will be notified of
 *        this event.
 *
 * @param view Indicates the view instance where the sliding end event occurs.
 */
void OnDragEndEventHappen(UIView& view);

/**
 * @brief Called when a press event occurs on the state machine. The screen-off display module will be notified of this
 *        event.
 *
 * @param view the attached view
 */
void OnLongPressEventHappen(UIView& view);
} // namespace OHOS
#endif // ENABLE_AOD
#endif // AOD_CALLBACK_H
