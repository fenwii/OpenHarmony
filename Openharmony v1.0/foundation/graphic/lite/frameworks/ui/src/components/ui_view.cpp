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

#include "components/ui_view.h"
#include "components/root_view.h"
#include "core/measure_manager.h"
#include "core/render_manager.h"
#include "draw/draw_rect.h"
#include "themes/theme_manager.h"

namespace OHOS {
UIView::UIView()
    : touchable_(false), visible_(true), draggable_(false), dragParentInstead_(true), isViewGroup_(false),
      needRedraw_(false), styleAllocFlag_(false), isIntercept_(true), opaScale_(OPA_OPAQUE), index_(0),
      id_(nullptr), parent_(nullptr), nextSibling_(nullptr), style_(nullptr), transMap_(nullptr),
      onClickListener_(nullptr), onLongPressListener_(nullptr), onDragListener_(nullptr),
      onTouchListener_(nullptr), rect_(0, 0, 0, 0), visibleRect_(nullptr)
{
    SetupThemeStyles();
}

UIView::~UIView()
{
    if (transMap_ != nullptr) {
        delete transMap_;
        transMap_ = nullptr;
    }
    if (visibleRect_ != nullptr) {
        delete visibleRect_;
        visibleRect_ = nullptr;
    }
    if (styleAllocFlag_) {
        delete style_;
        style_ = nullptr;
        styleAllocFlag_ = false;
    }
}

bool UIView::OnPreDraw(const Rect& invalidatedArea)
{
    Rect rect(GetRect());
    int16_t r = style_->borderRadius_;
    if (r != 0) {
        if (r == COORD_MAX) {
            return false;
        }
        rect.SetLeft(rect.GetX() + r);
        rect.SetWidth(rect.GetWidth() - r);
        rect.SetTop(rect.GetY() + r);
        rect.SetHeight(rect.GetHeight() - r);
    }
    return rect.IsContains(invalidatedArea);
}

void UIView::OnDraw(const Rect& invalidatedArea)
{
    DrawRect::Draw(GetRect(), invalidatedArea, *style_);
}

void UIView::SetupThemeStyles()
{
    Theme* theme = ThemeManager::GetInstance().GetCurrent();
    if (theme != nullptr) {
        style_ = &(theme->GetMainStyle());
    } else {
        style_ = &(StyleDefault::GetDefaultStyle());
    }
}

void UIView::SetStyle(Style& style)
{
    if (styleAllocFlag_) {
        delete style_;
        styleAllocFlag_ = false;
    }
    style_ = &style;
}

void UIView::SetStyle(uint8_t key, int64_t value)
{
    if (!styleAllocFlag_) {
        style_ = new Style(*style_);
        styleAllocFlag_ = true;
    }

    style_->SetStyle(key, value);
}

void UIView::AddMeasureView()
{
    MeasureManager::GetInstance().AddMeasureView(this);
}

void UIView::DeleteMeasureView()
{
    MeasureManager::GetInstance().DeleteMeasureView(this);
}

void UIView::Invalidate()
{
    InvalidateRect(GetRect());
}

void UIView::InvalidateRect(const Rect& invalidatedArea)
{
    if (!visible_) {
        if (needRedraw_) {
            needRedraw_ = false;
        } else {
            return;
        }
    }

    Rect trunc(invalidatedArea);
    bool isIntersect = true;
    UIView* par = parent_;
    UIView* cur = this;

    while (par != nullptr) {
        if (!par->visible_) {
            return;
        }

        isIntersect = trunc.Intersect(par->GetContentRect(), trunc);
        if (isIntersect == false) {
            break;
        }

        cur = par;
        par = par->parent_;
    }

    if (isIntersect && cur->GetViewType() == UI_ROOT_VIEW) {
        RootView* rootView = reinterpret_cast<RootView*>(cur);
        rootView->AddInvalidateRect(trunc);
    }
}

void UIView::GetTargetView(const Point& point, UIView** last)
{
    if (last == nullptr) {
        return;
    }
    UIView* par = parent_;
    Rect rect = GetRect();

    if (par != nullptr) {
        rect.Intersect(par->GetContentRect(), rect);
    }

    if (visible_ && touchable_ && rect.IsContains(point)) {
        *last = this;
    }
}

Rect UIView::GetRect() const
{
    if ((transMap_ != nullptr) && !transMap_->IsInvalid()) {
        Rect r = transMap_->GetBoxRect();
        Rect origRect = GetOrigRect();
        r.SetX(r.GetX() + origRect.GetX() - transMap_->GetTransMapRect().GetX());
        r.SetY(r.GetY() + origRect.GetY() - transMap_->GetTransMapRect().GetY());
        return r;
    }
    return GetOrigRect();
}

Rect UIView::GetContentRect()
{
    if ((transMap_ != nullptr) && !transMap_->IsInvalid()) {
        Rect r = transMap_->GetBoxRect();
        Rect origRect = GetOrigRect();
        r.SetX(r.GetX() + origRect.GetX() - transMap_->GetTransMapRect().GetX());
        r.SetY(r.GetY() + origRect.GetY() - transMap_->GetTransMapRect().GetY());
        return r;
    }

    Rect contentRect = GetRect();
    contentRect.SetX(contentRect.GetX() + style_->paddingLeft_ + style_->borderWidth_);
    contentRect.SetY(contentRect.GetY() + style_->paddingTop_ + style_->borderWidth_);
    contentRect.SetWidth(GetWidth());
    contentRect.SetHeight(GetHeight());
    return contentRect;
}

Rect UIView::GetOrigRect() const
{
    int16_t x = rect_.GetX();
    int16_t y = rect_.GetY();
    UIView* par = parent_;
    while (par != nullptr) {
        x += par->GetX() + par->style_->paddingLeft_ + par->style_->borderWidth_;
        y += par->GetY() + par->style_->paddingTop_ + par->style_->borderWidth_;
        par = par->parent_;
    }
    return Rect(x, y, x + rect_.GetWidth() - 1, y + rect_.GetHeight() - 1);
}

Rect UIView::GetMaskedRect() const
{
    Rect mask;
    if (visibleRect_ != nullptr) {
        mask.Intersect(GetRect(), GetVisibleRect());
    } else {
        mask = GetRect();
    }
    return mask;
}

Rect UIView::GetVisibleRect() const
{
    if (visibleRect_ == nullptr) {
        return GetRect();
    }
    Rect absoluteRect;
    int16_t x = visibleRect_->GetX();
    int16_t y = visibleRect_->GetY();
    UIView* par = parent_;
    while (par != nullptr) {
        x += par->GetX();
        y += par->GetY();
        par = par->parent_;
    }
    absoluteRect.SetX(x);
    absoluteRect.SetY(y);
    absoluteRect.SetWidth(visibleRect_->GetWidth());
    absoluteRect.SetHeight(visibleRect_->GetHeight());
    return absoluteRect;
}

void UIView::SetTransformMap(const TransformMap& transMap)
{
    if (transMap.IsInvalid()) {
        return;
    }

    Rect prevRect = GetRect();
    Rect mapRect = transMap.GetBoxRect();

    Rect joinRect;
    joinRect.Join(prevRect, mapRect);

    InvalidateRect(joinRect);

    if (transMap_ == nullptr) {
        transMap_ = new TransformMap();
    }

    *transMap_ = transMap;
}

void UIView::LayoutCenterOfParent(int16_t xOffset, int16_t yOffset)
{
    if (parent_ == nullptr) {
        return;
    }

    int16_t topMargin = style_->marginTop_;
    int16_t leftMargin = style_->marginLeft_;
    int16_t rightMargin = style_->marginRight_;
    int16_t bottomMargin = style_->marginBottom_;
    // 2: half
    int16_t posX = parent_->GetWidth() / 2 - (rect_.GetWidth() - leftMargin + rightMargin) / 2 + xOffset;
    int16_t posY = parent_->GetHeight() / 2 - (rect_.GetHeight() - topMargin + bottomMargin) / 2 + yOffset;
    SetPosition(posX, posY);
}

void UIView::LayoutLeftOfParent(int16_t offset)
{
    if (parent_ == nullptr) {
        return;
    }

    int16_t leftMargin = style_->marginLeft_;
    SetPosition(leftMargin + offset, GetY());
}

void UIView::LayoutRightOfParent(int16_t offset)
{
    if (parent_ == nullptr) {
        return;
    }

    int16_t rightMargin = style_->marginRight_;
    SetPosition(parent_->GetWidth() - offset - rect_.GetWidth() - rightMargin, GetY());
}

void UIView::LayoutTopOfParent(int16_t offset)
{
    if (parent_ == nullptr) {
        return;
    }

    int16_t topMargin = style_->marginTop_;
    SetPosition(GetX(), topMargin + offset);
}

void UIView::LayoutBottomOfParent(int16_t offset)
{
    if (parent_ == nullptr) {
        return;
    }

    int16_t bottomMargin = style_->marginBottom_;
    SetPosition(GetX(), parent_->GetHeight() - offset - rect_.GetHeight() - bottomMargin);
}

void UIView::AlignLeftToSibling(const char* id, int16_t offset)
{
    if (parent_ == nullptr) {
        return;
    }
    UIView* sib = parent_->GetChildById(id);
    if (sib != nullptr) {
        int16_t margin = sib->style_->marginLeft_ - style_->marginLeft_;
        SetPosition(sib->GetX() - margin + offset, GetY());
    }
}

void UIView::AlignRightToSibling(const char* id, int16_t offset)
{
    if (parent_ == nullptr) {
        return;
    }
    UIView* sib = parent_->GetChildById(id);
    if (sib != nullptr) {
        int16_t margin = sib->style_->marginRight_ - style_->marginRight_;
        SetPosition(sib->GetX() + sib->rect_.GetWidth() - rect_.GetWidth() - offset + margin, GetY());
    }
}

void UIView::AlignTopToSibling(const char* id, int16_t offset)
{
    if (parent_ == nullptr) {
        return;
    }
    UIView* sib = parent_->GetChildById(id);
    if (sib != nullptr) {
        int16_t margin = sib->style_->marginTop_ - style_->marginTop_;
        SetPosition(GetX(), sib->GetY() + offset - margin);
    }
}

void UIView::AlignBottomToSibling(const char* id, int16_t offset)
{
    if (parent_ == nullptr) {
        return;
    }
    UIView* sib = parent_->GetChildById(id);
    if (sib != nullptr) {
        int16_t margin = sib->style_->marginBottom_ - style_->marginBottom_;
        SetPosition(GetX(), sib->GetY() + sib->rect_.GetHeight() - rect_.GetHeight() - offset + margin);
    }
}

void UIView::AlignHorCenterToSibling(const char* id, int16_t offset)
{
    if (parent_ == nullptr) {
        return;
    }
    UIView* sib = parent_->GetChildById(id);
    if (sib != nullptr) {
        // 2 : half
        int16_t margin = (sib->style_->marginRight_ - sib->style_->marginLeft_ -
            style_->marginRight_ + style_->marginLeft_) / 2;
        SetPosition(sib->GetX() + sib->rect_.GetWidth() / 2 - rect_.GetWidth() / 2 + margin + offset, GetY());
    }
}
void UIView::AlignVerCenterToSibling(const char* id, int16_t offset)
{
    if (parent_ == nullptr) {
        return;
    }
    UIView* sib = parent_->GetChildById(id);
    if (sib != nullptr) {
        // 2 : half
        int16_t margin = (sib->style_->marginBottom_ - sib->style_->marginTop_ -
            style_->marginBottom_ + style_->marginTop_) / 2;
        SetPosition(GetX(), sib->GetY() + sib->rect_.GetHeight() / 2 - rect_.GetHeight() / 2
            + margin + offset);
    }
}

void UIView::LayoutLeftToSibling(const char* id, int16_t offset)
{
    if (parent_ == nullptr) {
        return;
    }
    UIView* sib = parent_->GetChildById(id);
    if (sib != nullptr) {
        int16_t margin = sib->style_->marginLeft_ + style_->marginRight_;
        SetPosition(sib->GetX() - offset - rect_.GetWidth() - margin, GetY());
    }
}

void UIView::LayoutRightToSibling(const char* id, int16_t offset)
{
    if (parent_ == nullptr) {
        return;
    }
    UIView* sib = parent_->GetChildById(id);
    if (sib != nullptr) {
        int16_t margin = sib->style_->marginRight_ + style_->marginLeft_;
        SetPosition(sib->GetX() + sib->rect_.GetWidth() + offset + margin, GetY());
    }
}

void UIView::LayoutTopToSibling(const char* id, int16_t offset)
{
    if (parent_ == nullptr) {
        return;
    }
    UIView* sib = parent_->GetChildById(id);
    if (sib != nullptr) {
        int16_t margin = sib->style_->marginTop_ + style_->marginBottom_;
        SetPosition(GetX(), sib->GetY() - offset - rect_.GetHeight() - margin);
    }
}

void UIView::LayoutBottomToSibling(const char* id, int16_t offset)
{
    if (parent_ == nullptr) {
        return;
    }
    UIView* sib = parent_->GetChildById(id);
    if (sib != nullptr) {
        int16_t margin = sib->style_->marginBottom_ + style_->marginTop_;
        SetPosition(GetX(), sib->GetY() + sib->rect_.GetHeight() + offset + margin);
    }
}
} // namespace OHOS
