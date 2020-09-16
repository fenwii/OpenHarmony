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

#ifndef GRAPHIC_LITE_GRID_LAYOUT_H
#define GRAPHIC_LITE_GRID_LAYOUT_H

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
 * @file grid_layout.h
 *
 * @brief Declares a grid layout container. You can perform simple grid layout on child views that the container holds.
 *
 * @since 1.0
 * @version 1.0
 */

#include "layout.h"

namespace OHOS {
/**
 * @brief Defines a grid layout container. You can perform simple grid layout on child views that the container holds.
 *
 * @since 1.0
 * @version 1.0
 */
class GridLayout : public Layout {
public:
    /**
     * @brief A default constructor used to create a <b>GridLayout</b> instance.
     * @since 1.0
     * @version 1.0
     */
    GridLayout() : rows_(0), cols_(0) {}

    /**
     * @brief A destructor used to delete the <b>GridLayout</b> instance.
     * @since 1.0
     * @version 1.0
     */
    virtual ~GridLayout() {}

    /**
     * @brief Sets the number of rows in a grid.
     * @param rows Indicates the number of rows to set.
     * @since 1.0
     * @version 1.0
     */
    void SetRows(const uint16_t& rows)
    {
        rows_ = rows;
    }

    /**
     * @brief Sets the number of columns in a grid.
     * @param cols Indicates the number of columns to set.
     * @since 1.0
     * @version 1.0
     */
    void SetCols(const uint16_t& cols)
    {
        cols_ = cols;
    }

    /**
     * @brief Lays out all child views according to the preset arrangement mode.
     * @param needInvalidate Specifies whether to refresh the invalidated area after the layout is complete.
     *                       Value <b>true</b> means to refresh the invalidated area after the layout is complete,
     *                       and <b>false</b> means the opposite.
     * @since 1.0
     * @version 1.0
     */
    virtual void LayoutChildren(bool needInvalidate = false) override;
private:
    void LayoutHorizantal();
    void LayoutVertical();

    uint16_t rows_;
    uint16_t cols_;
};
} // namespace OHOS
#endif // GRAPHIC_LITE_GRID_LAYOUT_H

