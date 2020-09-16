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
 * @file flex_layout.h
 *
 * @brief Declares a flexible layout container. You can perform simple adaptive layout on child views that the
 *        container holds, for example, to evenly arrange all child views in the same row or column.
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef GRAPHIC_LITE_FLEX_LAYOUT_H
#define GRAPHIC_LITE_FLEX_LAYOUT_H

#include "layout.h"

namespace OHOS {
/**
 * @brief Defines a flexible layout container. You can perform simple adaptive layout on child views that the
 *        container holds, for example, to evenly arrange all child views in the same row or column.
 *
 * @since 1.0
 * @version 1.0
 */
class FlexLayout : public Layout {
public:
    static constexpr uint8_t NOWRAP = 0;
    static constexpr uint8_t WRAP = 1;

    /**
     * @brief A default constructor used to create a <b>FlexLayout</b> instance.
     * @since 1.0
     * @version 1.0
     */
    FlexLayout()
        : majorAlign_(ALIGN_START), secondaryAlign_(ALIGN_CENTER), wrap_(NOWRAP), rowCount_(1), columnCount_(1) {}

    /**
     * @brief A destructor used to delete the <b>FlexLayout</b> instance.
     * @since 1.0
     * @version 1.0
     */
    virtual ~FlexLayout() {}

    /**
     * @brief Sets the alignment mode of the primary axis (the axis where the layout direction is located).
     *        The child views in the layout are placed in this mode in the direction of the primary axis.
     * @param align Indicates the alignment mode to set. The value can be <b>ALIGN_START</b>, <b>ALIGN_END</b>,
     *              <b>ALIGN_CENTER</b>, <b>ALIGN_EVENLY</b>, <b>ALIGN_AROUND</b>, or <b>ALIGN_BETWEEN</b>.
     * @since 1.0
     * @version 1.0
     */
    void SetMajorAxisAlign(const AlignType& align)
    {
        majorAlign_ = align;
    }

    /**
     * @brief Sets the alignment mode of the secondary axis (the axis perpendicular to the set layout direction).
     * @param align Indicates the alignment mode to set. The value can be <b>ALIGN_START</b>, <b>ALIGN_CENTER</b>,
     *              or <b>ALIGN_END</b>.
     * @since 1.0
     * @version 1.0
     */
    void SetSecondaryAxisAlign(const AlignType& align)
    {
        secondaryAlign_ = align;
    }

    /**
     * @brief Sets whether to support word wrap.
     * @param wrap Indicates the word wrap attribute.
     * @since 1.0
     * @version 1.0
     */
    void SetFlexWrap(uint8_t wrap)
    {
        wrap_ = wrap;
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
    void LayoutHorizontal();
    void LayoutVertical();
    void CalValidLength(uint16_t& totalValidLength, uint16_t& allChildNum);
    void GetStartPos(const int16_t& length, int16_t& pos, int16_t& interval, int16_t count,
        uint16_t* validLengths, uint16_t* childsNum);
    void GetNoWrapStartPos(const int16_t& length, int16_t& majorPos, int16_t& interval);
    void CalRowCount();
    void GetRowMaxHeight(uint16_t size, uint16_t* maxRosHegiht);
    void GetRowsWidth(uint16_t rowNum, uint16_t* rowsWidth, uint16_t* rowsChildNum);
    void GetRowStartPos(int16_t& pos, int16_t& interval, int16_t count,
        uint16_t* rowsWidth, uint16_t* rowsChildNum);
    void CalColumnCount();
    void GetColumnMaxWidth(uint16_t size, uint16_t* maxColumnsWidth);
    void GetColumnsHeight(uint16_t columnNum, uint16_t* columnsHeight, uint16_t* columnsChildNum);
    void GetColumnStartPos(int16_t& pos, int16_t& interval, int16_t count,
        uint16_t* columnsHeight, uint16_t* columnsChildNum);
    void GetCrossAxisPosY(int16_t& posY, uint16_t& count, uint16_t* rowsMaxHeight, UIView* child);
    void GetCrossAxisPosX(int16_t& posX, uint16_t& count, uint16_t* columnsMaxWidth, UIView* child);
    static constexpr uint16_t MAX_COUNT_DEFAULT = 100;
    AlignType majorAlign_;
    AlignType secondaryAlign_;
    uint8_t wrap_;
    uint16_t rowCount_;
    uint16_t columnCount_;
};
} // namespace OHOS
#endif // GRAPHIC_LITE_FLEX_LAYOUT_H

