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
 * @file layout.h
 *
 * @brief Declares the base class of the layout, which indicates the basic data types and operations that may be
 *        used in the layout.
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef GRAPHIC_LITE_LAYOUT_H
#define GRAPHIC_LITE_LAYOUT_H

#include "components/ui_view_group.h"

namespace OHOS {
using DirectionType = uint8_t;
using AlignType = uint8_t;
/* Arranges child views by row from left to right. */
const DirectionType LAYOUT_HOR = 0;
/* Arranges child views by row from right to left. */
const DirectionType LAYOUT_HOR_R = 1;
/* Arranges child views by column from top to bottom. */
const DirectionType LAYOUT_VER = 2;
/* Arranges child views by column from bottom to top. */
const DirectionType LAYOUT_VER_R = 3;

/* Places all child views from the start point to the end point. */
const AlignType ALIGN_START = 0;
/* Places all child views from the end point to the start point. */
const AlignType ALIGN_END = 1;
/* Places all child views in the center. */
const AlignType ALIGN_CENTER = 2;
/* Evenly places all child views between the start point and end point. The distance between the start point and
   the end as well as the distance between the end point and the end is the same as that between child views. */
const AlignType ALIGN_EVENLY = 3;
/* Evenly places all child views between the start point and end point. The distance between the start point and
   the end as well as the distance between the end point and the end is half of the distance between child views. */
const AlignType ALIGN_AROUND = 4;
/* Evenly places all child views between the start point and end point. No left or right margin is reserved. */
const AlignType ALIGN_BETWEEN = 5;

/**
 * @brief Defines the base class of the layout, which indicates the basic data types and operations that may be used in
 *        the layout.
 *
 * @since 1.0
 * @version 1.0
 */
class Layout : public UIViewGroup {
public:
    /**
     * @brief A default constructor used to create a <b>Layout</b> instance.
     * @since 1.0
     * @version 1.0
     */
    Layout() : direction_(LAYOUT_HOR) {}

    /**
     * @brief A destructor used to delete the <b>Layout</b> instance.
     * @since 1.0
     * @version 1.0
     */
    virtual ~Layout() {}

/**
 * @brief Sets the layout direction.
 * @param direction Indicates the direction of the layout. Available values are as follows:
 *                  LAYOUT_HOR: from left to right
 *                  LAYOUT_HOR_R: from right to left
 *                  LAYOUT_VER: from top to bottom
 *                  LAYOUT_VER_R: from bottom to top
 * @since 1.0
 * @version 1.0
 */
    void SetLayoutDirection(const DirectionType& direction)
    {
        direction_ = direction;
    }

protected:
    DirectionType direction_;
};
} // namespace OHOS
#endif // GRAPHIC_LITE_LAYOUT_H

