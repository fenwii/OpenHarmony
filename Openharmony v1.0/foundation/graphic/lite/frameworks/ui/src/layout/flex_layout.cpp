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

#include "layout/flex_layout.h"
#include "core/measure_manager.h"

namespace OHOS {
void FlexLayout::LayoutChildren(bool needInvalidate)
{
    if (childrenHead_ == nullptr) {
        return;
    }

    MeasureManager::GetInstance().ReMeasureRect();

    if (direction_ == LAYOUT_HOR || direction_ == LAYOUT_HOR_R) {
        LayoutHorizontal();
    } else {
        LayoutVertical();
    }
    if (needInvalidate) {
        Invalidate();
    }
}

void FlexLayout::GetStartPos(const int16_t& length, int16_t& pos, int16_t& interval, int16_t count,
    uint16_t* validLengths, uint16_t* childsNum)
{
    if ((!validLengths) || (!childsNum)) {
        return;
    }
    pos = 0;
    interval = 0;

    if (majorAlign_ == ALIGN_START) {
        pos = 0;
    } else if (majorAlign_ == ALIGN_END) {
        pos = length - validLengths[count];
    /* if total length of children is too long or only one child, layout them centerly no matter what key word set. */
    } else if (majorAlign_ == ALIGN_CENTER || validLengths[count] >= length || childsNum[count] == 1) {
        pos = (length - validLengths[count]) / 2;  // 2: half
    } else if (majorAlign_ == ALIGN_AROUND) {
        if (childsNum[count] == 0) {
            return;
        }
        interval = (length - validLengths[count]) / childsNum[count];
        pos = interval / 2;  // 2: half
    } else if (majorAlign_ == ALIGN_EVENLY) {
        interval = (length - validLengths[count]) / (childsNum[count] + 1);
        pos = interval;
    } else {
        if (childsNum[count] == 1) {
            return;
        }
        interval = (length - validLengths[count]) / (childsNum[count] - 1);
        pos = 0;
    }
}

void FlexLayout::GetNoWrapStartPos(const int16_t& length, int16_t& majorPos, int16_t& interval)
{
    uint16_t childrenNum = 0;
    uint16_t totalValidLength = 0;

    CalValidLength(totalValidLength, childrenNum);
    GetStartPos(length, majorPos, interval, 0, &totalValidLength, &childrenNum);
}

void FlexLayout::GetRowStartPos(int16_t& pos, int16_t& interval, int16_t count,
    uint16_t* rowsWidth, uint16_t* rowsChildNum)
{
    GetStartPos(GetWidth(), pos, interval, count, rowsWidth, rowsChildNum);
}

void FlexLayout::GetColumnStartPos(int16_t& pos, int16_t& interval, int16_t count,
    uint16_t* columnsHeight, uint16_t* columnsChildNum)
{
    GetStartPos(GetHeight(), pos, interval, count, columnsHeight, columnsChildNum);
}

void FlexLayout::CalValidLength(uint16_t& totalValidLength, uint16_t& allChildNum)
{
    UIView* child = childrenHead_;
    int16_t left = 0;
    int16_t right = 0;
    int16_t top = 0;
    int16_t bottom = 0;

    /* calculate valid length of all children views */
    while (child != nullptr) {
        if (direction_ == LAYOUT_HOR || direction_ == LAYOUT_HOR_R) {
            left = child->GetStyle(STYLE_MARGIN_LEFT);
            right = child->GetStyle(STYLE_MARGIN_RIGHT);
            totalValidLength += (child->GetRelativeRect().GetWidth() + left + right);
        } else {
            top = child->GetStyle(STYLE_MARGIN_TOP);
            bottom = child->GetStyle(STYLE_MARGIN_BOTTOM);
            totalValidLength += (child->GetRelativeRect().GetHeight() + top + bottom);
        }
        allChildNum++;
        child = child->GetNextSibling();
    }
}

void FlexLayout::CalRowCount()
{
    UIView* child = childrenHead_;
    int16_t pos = 0;
    int16_t left = 0;
    int16_t right = 0;

    rowCount_ = 1;
    while (child != nullptr) {
        left = child->GetStyle(STYLE_MARGIN_LEFT);
        right = child->GetStyle(STYLE_MARGIN_RIGHT);
        pos += left;
        if ((pos + child->GetRelativeRect().GetWidth() + right) > GetWidth()) {
            pos = left;
            rowCount_++;
        }
        pos += child->GetRelativeRect().GetWidth() + right;
        child = child->GetNextSibling();
    }
}

void FlexLayout::GetRowMaxHeight(uint16_t size, uint16_t* maxRosHegiht)
{
    UIView* child = childrenHead_;
    int16_t pos = 0;
    int16_t left = 0;
    int16_t right = 0;
    int16_t top = 0;
    int16_t bottom = 0;
    uint16_t i = 0;
    uint16_t height = 0;

    if ((maxRosHegiht == nullptr) || (size > rowCount_)) {
        return;
    }

    while (child != nullptr) {
        left = child->GetStyle(STYLE_MARGIN_LEFT);
        right = child->GetStyle(STYLE_MARGIN_RIGHT);
        top = child->GetStyle(STYLE_MARGIN_TOP);
        bottom = child->GetStyle(STYLE_MARGIN_BOTTOM);
        pos += left;
        if ((pos + child->GetRelativeRect().GetWidth() + right) > GetWidth()) {
            pos = left;
            maxRosHegiht[i] = height;
            height = 0;
            i++;
        }
        height = MATH_MAX(height, child->GetRelativeRect().GetHeight() + top + bottom);
        maxRosHegiht[i] = height;
        pos += child->GetRelativeRect().GetWidth() + right;
        child = child->GetNextSibling();
    }
}

void FlexLayout::GetRowsWidth(uint16_t rowNum, uint16_t* rowsWidth, uint16_t* rowsChildNum)
{
    UIView* child = childrenHead_;
    int16_t pos = 0;
    int16_t left = 0;
    int16_t right = 0;
    uint16_t rowChildNum = 0;
    uint16_t rowCount = 0;
    uint16_t width = 0;

    if ((rowsWidth == nullptr) || (rowsChildNum == nullptr) || (rowNum > rowCount_)) {
        return;
    }

    while (child != nullptr) {
        left = child->GetStyle(STYLE_MARGIN_LEFT);
        right = child->GetStyle(STYLE_MARGIN_RIGHT);
        pos += left;
        if ((pos + child->GetRelativeRect().GetWidth() + right) > GetWidth()) {
            pos = left;
            rowsWidth[rowCount] = width;
            width = 0;
            rowsChildNum[rowCount] = rowChildNum;
            rowChildNum = 0;
            rowCount++;
        }
        width += child->GetRelativeRect().GetWidth() + right + left;
        rowsWidth[rowCount] = width;
        rowChildNum++;
        rowsChildNum[rowCount] = rowChildNum;
        pos += child->GetRelativeRect().GetWidth() + right;
        child = child->GetNextSibling();
    }
}

void FlexLayout::GetCrossAxisPosY(int16_t& posY, uint16_t& count, uint16_t* rowsMaxHeight, UIView* child)
{
    if (rowsMaxHeight == nullptr || child == nullptr) {
        return;
    }

    uint16_t i = 0;
    uint16_t offset = 0;
    int16_t top = child->GetStyle(STYLE_MARGIN_TOP);
    int16_t bottom = child->GetStyle(STYLE_MARGIN_BOTTOM);

    if (secondaryAlign_ == ALIGN_START) {
        for (i = 0; i < count; i++) {
            offset += rowsMaxHeight[i];
        }
        posY = top + offset;
    } else if (secondaryAlign_ == ALIGN_END) {
        for (i = rowCount_ - 1; i > count; i--) {
            offset += rowsMaxHeight[i];
        }
        posY = GetHeight() - child->GetRelativeRect().GetHeight() - bottom - offset;
    } else {
        for (i = 0; i < rowCount_; i++) {
            offset += rowsMaxHeight[i];
        }
        offset = (rowsMaxHeight[0] - offset) / 2;  // 2: half
        for (i = 1; i <= count; i++) {
            offset += (rowsMaxHeight[i - 1] + rowsMaxHeight[i]) / 2;  // 2: half
        }
        posY = (GetHeight() - child->GetRelativeRect().GetHeight() - top - bottom) / 2 + top + offset;  // 2: half
    }
}

void FlexLayout::LayoutHorizontal()
{
    UIView* child = childrenHead_;
    int16_t interval = 0;
    int16_t posX = 0;
    int16_t posY = 0;
    uint16_t count = 0;
    uint16_t widthsBuf[MAX_COUNT_DEFAULT] = { 0 };
    uint16_t maxHeightsBuf[MAX_COUNT_DEFAULT] = { 0 };
    uint16_t childsNumBuf[MAX_COUNT_DEFAULT] = { 0 };
    uint16_t* rowsWidth = widthsBuf;
    uint16_t* rowsMaxHeight = maxHeightsBuf;
    uint16_t* rowsChildNum = childsNumBuf;
    bool allocFlag = false;

    if (wrap_ == WRAP) {
        CalRowCount();
        if (rowCount_ > MAX_COUNT_DEFAULT) {
            rowsWidth = new uint16_t[rowCount_]();
            rowsMaxHeight = new uint16_t[rowCount_]();
            rowsChildNum = new uint16_t[rowCount_]();
            allocFlag = true;
        }
        GetRowMaxHeight(rowCount_, rowsMaxHeight);
        GetRowsWidth(rowCount_, rowsWidth, rowsChildNum);
        GetRowStartPos(posX, interval, count, rowsWidth, rowsChildNum);
    } else {
        GetNoWrapStartPos(GetWidth(), posX, interval);
    }

    while (child != nullptr) {
        int16_t left = child->GetStyle(STYLE_MARGIN_LEFT);
        int16_t right = child->GetStyle(STYLE_MARGIN_RIGHT);
        posX += left;
        if (((posX + child->GetRelativeRect().GetWidth() + right) > GetWidth()) && (wrap_ == WRAP)) {
            GetRowStartPos(posX, interval, ++count, rowsWidth, rowsChildNum);
            posX += left;
        }

        GetCrossAxisPosY(posY, count, rowsMaxHeight, child);
        if (direction_ == LAYOUT_HOR_R) {
            child->SetPosition(GetWidth() - (posX - left) - child->GetRelativeRect().GetWidth() - right, posY);
        } else {
            child->SetPosition(posX, posY);
        }
        posX += child->GetRelativeRect().GetWidth() + right + interval;
        child->LayoutChildren();
        child = child->GetNextSibling();
    }

    if (allocFlag) {
        delete[] rowsWidth;
        delete[] rowsMaxHeight;
        delete[] rowsChildNum;
    }
}

void FlexLayout::CalColumnCount()
{
    UIView* child = childrenHead_;
    int16_t pos = 0;
    int16_t top = 0;
    int16_t bottom = 0;

    columnCount_ = 1;
    while (child != nullptr) {
        top = child->GetStyle(STYLE_MARGIN_TOP);
        bottom = child->GetStyle(STYLE_MARGIN_BOTTOM);
        pos += top;
        if ((pos + child->GetRelativeRect().GetHeight() + bottom) > GetHeight()) {
            pos = top;
            columnCount_++;
        }
        pos += child->GetRelativeRect().GetHeight() + bottom;
        child = child->GetNextSibling();
    }
}

void FlexLayout::GetColumnMaxWidth(uint16_t size, uint16_t* maxColumnsWidth)
{
    UIView* child = childrenHead_;
    int16_t pos = 0;
    int16_t left = 0;
    int16_t right = 0;
    int16_t bottom = 0;
    uint16_t i = 0;
    uint16_t width = 0;

    if ((maxColumnsWidth == nullptr) || (size > columnCount_)) {
        return;
    }

    while (child != nullptr) {
        left = child->GetStyle(STYLE_MARGIN_LEFT);
        right = child->GetStyle(STYLE_MARGIN_RIGHT);
        bottom = child->GetStyle(STYLE_MARGIN_BOTTOM);
        pos += left;
        if ((pos + child->GetRelativeRect().GetHeight() + bottom) > GetHeight()) {
            pos = left;
            maxColumnsWidth[i] = width;
            width = 0;
            i++;
        }
        width = MATH_MAX(width, child->GetRelativeRect().GetWidth() + left + right);
        maxColumnsWidth[i] = width;
        pos += child->GetRelativeRect().GetHeight() + bottom;
        child = child->GetNextSibling();
    }
}

void FlexLayout::GetColumnsHeight(uint16_t columnNum, uint16_t* columnsHeight, uint16_t* columnsChildNum)
{
    UIView* child = childrenHead_;
    int16_t pos = 0;
    int16_t top = 0;
    int16_t bottom = 0;
    uint16_t columnChildNum = 0;
    uint16_t columnCount = 0;
    uint16_t height = 0;

    if ((columnsHeight == nullptr) || (columnsChildNum == nullptr) || (columnNum > columnCount_)) {
        return;
    }

    while (child != nullptr) {
        top = child->GetStyle(STYLE_MARGIN_TOP);
        bottom = child->GetStyle(STYLE_MARGIN_BOTTOM);
        pos += top;
        if ((pos + child->GetRelativeRect().GetHeight() + bottom) > GetHeight()) {
            pos = top;
            columnsHeight[columnCount] = height;
            height = 0;
            columnsChildNum[columnCount] = columnChildNum;
            columnChildNum = 0;
            columnCount++;
        }
        height += child->GetRelativeRect().GetHeight() + top + bottom;
        columnsHeight[columnCount] = height;
        columnChildNum++;
        columnsChildNum[columnCount] = columnChildNum;
        pos += child->GetRelativeRect().GetHeight() + bottom;
        child = child->GetNextSibling();
    }
}

void FlexLayout::GetCrossAxisPosX(int16_t& posX, uint16_t& count, uint16_t* columnsMaxWidth, UIView* child)
{
    if (columnsMaxWidth == nullptr || child == nullptr) {
        return;
    }

    uint16_t i = 0;
    uint16_t offset = 0;
    int16_t left = child->GetStyle(STYLE_MARGIN_LEFT);
    int16_t right = child->GetStyle(STYLE_MARGIN_RIGHT);

    if (secondaryAlign_ == ALIGN_START) {
        for (i = 0; i < count; i++) {
            offset += columnsMaxWidth[i];
        }
        posX = left + offset;
    } else if (secondaryAlign_ == ALIGN_END) {
        for (i = columnCount_ - 1; i > count; i--) {
            offset += columnsMaxWidth[i];
        }
        posX = GetWidth() - child->GetRelativeRect().GetWidth() - right - offset;
    } else {
        for (i = 0; i < columnCount_; i++) {
            offset += columnsMaxWidth[i];
        }
        offset = (columnsMaxWidth[0] - offset) / 2;  // 2: half
        for (i = 1; i <= count; i++) {
            offset += (columnsMaxWidth[i - 1] + columnsMaxWidth[i]) / 2;  // 2: half
        }
        posX = (GetWidth() - child->GetRelativeRect().GetWidth() - left - right) / 2 + left + offset;  // 2: half
    }
}

void FlexLayout::LayoutVertical()
{
    UIView* child = childrenHead_;
    int16_t interval = 0;
    int16_t posX = 0;
    int16_t posY = 0;
    uint16_t count = 0;
    uint16_t heightsBuf[MAX_COUNT_DEFAULT] = { 0 };
    uint16_t maxWidthsBuf[MAX_COUNT_DEFAULT] = { 0 };
    uint16_t childsNumBuf[MAX_COUNT_DEFAULT] = { 0 };
    uint16_t* columnsHeight = heightsBuf;
    uint16_t* columnsMaxWidth = maxWidthsBuf;
    uint16_t* columnsChildNum = childsNumBuf;
    bool allocFlag = false;

    if (wrap_ == WRAP) {
        CalColumnCount();
        if (columnCount_ > MAX_COUNT_DEFAULT) {
            columnsHeight = new uint16_t[columnCount_]();
            columnsMaxWidth = new uint16_t[columnCount_]();
            columnsChildNum = new uint16_t[columnCount_]();
            allocFlag = true;
        }
        GetColumnMaxWidth(columnCount_, columnsMaxWidth);
        GetColumnsHeight(columnCount_, columnsHeight, columnsChildNum);
        GetColumnStartPos(posY, interval, count, columnsHeight, columnsChildNum);
    } else {
        GetNoWrapStartPos(GetHeight(), posY, interval);
    }

    while (child != nullptr) {
        int16_t top = child->GetStyle(STYLE_MARGIN_TOP);
        int16_t bottom = child->GetStyle(STYLE_MARGIN_BOTTOM);
        posY += top;
        if (((posY + child->GetRelativeRect().GetHeight() + bottom) > GetHeight()) && (wrap_ == WRAP)) {
            GetColumnStartPos(posY, interval, ++count, columnsHeight, columnsChildNum);
            posY += top;
        }

        GetCrossAxisPosX(posX, count, columnsMaxWidth, child);
        if (direction_ == LAYOUT_VER_R) {
            child->SetPosition(posX, GetHeight() - (posY - top) - child->GetRelativeRect().GetHeight() - bottom);
        } else {
            child->SetPosition(posX, posY);
        }
        posY += child->GetRelativeRect().GetHeight() + bottom + interval;
        child->LayoutChildren();
        child = child->GetNextSibling();
    }

    if (allocFlag) {
        delete[] columnsHeight;
        delete[] columnsMaxWidth;
        delete[] columnsChildNum;
    }
}
} // namespace OHOS