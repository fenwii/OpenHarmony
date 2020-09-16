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

#include "layout/grid_layout.h"
#include "core/measure_manager.h"

namespace OHOS {
void GridLayout::LayoutChildren(bool needInvalidate)
{
    if (childrenHead_ == nullptr) {
        return;
    }
    UIView* child = childrenHead_;
    if (rows_ == 0 || cols_ == 0) {
        RemoveAll();
        return;
    }
    int16_t childrenNum = 0;
    while (child != nullptr) {
        childrenNum++;
        child = child->GetNextSibling();
    }
    if (rows_ * cols_ < childrenNum) {
        RemoveAll();
        return;
    }

    MeasureManager::GetInstance().ReMeasureRect();
    if (direction_ == LAYOUT_HOR) {
        LayoutHorizantal();
    } else {
        LayoutVertical();
    }
    if (needInvalidate) {
        Invalidate();
    }
}

void GridLayout::LayoutHorizantal()
{
    UIView* child = childrenHead_;
    int16_t left = 0;
    int16_t right = 0;
    int16_t top = 0;
    int16_t bottom = 0;
    int16_t layoutWidth = GetWidth() / cols_;
    int16_t layoutHeight = GetHeight() / rows_;
    int16_t posX;
    int16_t posY;
    for (int16_t i = 0; i < rows_; i++) {
        posY = i * layoutHeight;
        for (int16_t j = 0; j < cols_; j++) {
            if (child == nullptr) {
                return;
            }
            posX = j * layoutWidth;
            left = child->GetStyle(STYLE_MARGIN_LEFT);
            right = child->GetStyle(STYLE_MARGIN_RIGHT);
            top = child->GetStyle(STYLE_MARGIN_TOP);
            bottom = child->GetStyle(STYLE_MARGIN_BOTTOM);
            // 2: half
            int16_t actPosX = posX + (layoutWidth - child->GetRelativeRect().GetWidth() - left - right) / 2 + left;
            // 2: half
            int16_t actPosY = posY + (layoutHeight - child->GetRelativeRect().GetHeight() - top - bottom) / 2 + top;
            child->SetPosition(actPosX, actPosY);
            child->LayoutChildren();
            child->ResizeVisibleArea(posX, posY, layoutWidth, layoutHeight);
            child = child->GetNextSibling();
        }
    }
}

void GridLayout::LayoutVertical()
{
    UIView* child = childrenHead_;
    int16_t left = 0;
    int16_t right = 0;
    int16_t top = 0;
    int16_t bottom = 0;
    int16_t layoutWidth = GetWidth() / cols_;
    int16_t layoutHeight = GetHeight() / rows_;
    int16_t posX;
    int16_t posY;
    for (int16_t i = 0; i < cols_; i++) {
        posX = i * layoutWidth;
        for (int16_t j = 0; j < rows_; j++) {
            if (child == nullptr) {
                return;
            }
            posY = j * layoutHeight;
            left = child->GetStyle(STYLE_MARGIN_LEFT);
            right = child->GetStyle(STYLE_MARGIN_RIGHT);
            top = child->GetStyle(STYLE_MARGIN_TOP);
            bottom = child->GetStyle(STYLE_MARGIN_BOTTOM);
            // 2: half
            int16_t actPosX = posX + (layoutWidth - child->GetRelativeRect().GetWidth() - left - right) / 2 + left;
            // 2: half
            int16_t actPosY = posY + (layoutHeight - child->GetRelativeRect().GetHeight() - top - bottom) / 2 + top;
            child->SetPosition(actPosX, actPosY);
            child->LayoutChildren();
            child->ResizeVisibleArea(posX, posY, layoutWidth, layoutHeight);
            child = child->GetNextSibling();
        }
    }
}
} // namespace OHOS