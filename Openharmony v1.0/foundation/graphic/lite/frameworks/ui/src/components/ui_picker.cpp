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

#include "components/ui_picker.h"
#include "draw/draw_line.h"
#include "draw/draw_rect.h"
#include "themes/theme_manager.h"

namespace OHOS {
class PickerListScrollListener : public ListScrollListener {
public:
    PickerListScrollListener(UIPicker* picker, UIList* list)
        : listView_(list), pickerView_(picker), selectView_(nullptr), lastSelectView_(nullptr),
          selectIndex_(0), isInitted_(false){}

    virtual ~PickerListScrollListener() {}

    void OnItemSelected(int16_t index, UIView* view) override
    {
        if (!isInitted_) {
            return;
        }

        if ((lastSelectView_ != nullptr) && (listView_ != nullptr) && (pickerView_ != nullptr) && (view != nullptr)) {
            lastSelectView_->SetStyle(STYLE_TEXT_COLOR, pickerView_->GetBackgroundTextColor().full);
            if (pickerView_->backgroundFontName_ == nullptr) {
                static_cast<UILabel*>(lastSelectView_)->SetFontId(pickerView_->backgroundFontId_);
            } else {
                static_cast<UILabel*>(lastSelectView_)
                    ->SetFont(pickerView_->backgroundFontName_, pickerView_->backgroundFontSize_);
            }
            view->SetStyle(STYLE_TEXT_COLOR, pickerView_->GetHighlightTextColor().full);
            if (pickerView_->highlightFontName_ == nullptr) {
                static_cast<UILabel*>(view)->SetFontId(pickerView_->highlightFontId_);
            } else {
                static_cast<UILabel*>(view)
                    ->SetFont(pickerView_->highlightFontName_, pickerView_->highlightFontSize_);
            }
            lastSelectView_ = view;
            listView_->Invalidate();
        }
    }

    void OnScrollEnd(int16_t index, UIView* view) override
    {
        if ((view == nullptr) || (listView_ == nullptr) || (pickerView_ == nullptr)) {
            return;
        }

        if (lastSelectView_ != nullptr) {
            lastSelectView_->SetStyle(STYLE_TEXT_COLOR, pickerView_->GetBackgroundTextColor().full);
            if (pickerView_->backgroundFontName_ == nullptr) {
                static_cast<UILabel*>(lastSelectView_)->SetFontId(pickerView_->backgroundFontId_);
            } else {
                static_cast<UILabel*>(lastSelectView_)
                    ->SetFont(pickerView_->backgroundFontName_, pickerView_->backgroundFontSize_);
            }
            lastSelectView_ = view;
        }

        view->SetStyle(STYLE_TEXT_COLOR, pickerView_->GetHighlightTextColor().full);
        if (pickerView_->highlightFontName_ == nullptr) {
            static_cast<UILabel*>(view)->SetFontId(pickerView_->highlightFontId_);
        } else {
            static_cast<UILabel*>(view)
                ->SetFont(pickerView_->highlightFontName_, pickerView_->highlightFontSize_);
        }

        listView_->Invalidate();
        selectView_ = view;
        selectIndex_ = index;

        if (pickerView_->pickerListener_) {
            pickerView_->pickerListener_->OnPickerStoped(*pickerView_);
        }
    }

    void SetSelectView(UIView* view)
    {
        selectView_ = view;
        lastSelectView_ = view;
    }

    const UIView* GetSelectView() const
    {
        return selectView_;
    }

    void SetSelectIndex(uint16_t index)
    {
        selectIndex_ = index;
    }

    uint16_t GetSelectIndex() const
    {
        return selectIndex_;
    }

    void SetInitStatus(bool status)
    {
        isInitted_ = status;
    }

private:
    UIList* listView_;
    UIPicker* pickerView_;
    UIView* selectView_;
    UIView* lastSelectView_;
    uint16_t selectIndex_;
    bool isInitted_;
};

UIPicker::UIPicker()
    : isWidthSet_(false),
      isHeightSet_(false),
      maxCount_(0),
      setSelectedIndex_(0),
      backgroundFontSize_(0),
      highlightFontSize_(0),
      backgroundFontName_(nullptr),
      highlightFontName_(nullptr),
      itemsWidth_(0),
      itemsHeight_(0),
      rangeValue_(nullptr),
      rangeValueCount_(0),
      startValue_(0),
      endValue_(0),
      isSetAdaptered_(false),
      pickerListener_(nullptr)
{
    Theme* theme = ThemeManager::GetInstance().GetCurrent();
    if (theme != nullptr) {
        style_ = &(theme->GetPickerBackgroundStyle());
    } else {
        style_ = &(StyleDefault::GetPickerBackgroundStyle());
    }
    backgroundFontId_ = style_->font_;
    backgroundColor_ = style_->textColor_;
    direct_ = UITextLanguageDirect::TEXT_DIRECT_LTR;

    if (theme != nullptr) {
        style_ = &(theme->GetPickerHighlightStyle());
    } else {
        style_ = &(StyleDefault::GetPickerHighlightStyle());
    }
    highlightFontId_ = style_->font_;
    highlightColor_ = style_->textColor_;

    list_.SetThrowDrag(true);
    list_.SetLoopState(false);
    list_.EnableAutoAlign(true);
    list_.SetIntercept(false);
    PickerListScrollListener* listener = new PickerListScrollListener(this, &list_);
    list_.SetScrollStateListener(listener);
    listListener_ = static_cast<void*>(listener);
    Add(&list_);
}

UIPicker::~UIPicker()
{
    ClearValues();
    Remove(&list_);
    if (listListener_ != nullptr) {
        delete static_cast<PickerListScrollListener *>(listListener_);
        listListener_ = nullptr;
    }

    if (backgroundFontName_ != nullptr) {
        UIFree(backgroundFontName_);
        backgroundFontName_ = nullptr;
    }

    if (highlightFontName_ != nullptr) {
        UIFree(highlightFontName_);
        highlightFontName_ = nullptr;
    }
}

bool UIPicker::SetValues(int16_t start, int16_t end)
{
    if (start > end) {
        return false;
    }

    startValue_ = start;
    endValue_ = end;
    return RefreshValues(start, end);
}

bool UIPicker::SetValues(const char* value[], uint16_t count)
{
    if (value == nullptr) {
        return false;
    }

    rangeValue_ = value;
    rangeValueCount_ = count;
    return RefreshValues(value, count);
}

void UIPicker::Refresh()
{
    if (rangeValue_) {
        RefreshValues(rangeValue_, rangeValueCount_);
    } else if (startValue_ != 0 || endValue_ != 0) {
        RefreshValues(startValue_, endValue_);
    }
}

bool UIPicker::RefreshValues(int16_t start, int16_t end)
{
    if (!isWidthSet_ || !isHeightSet_ || !itemsHeight_ || (start == 0 && end == 0)) {
        return false;
    }

    ClearList();
    textAdapter_.SetData(start, end);
    maxCount_ = end - start + 1;
    RefreshList();
    if (setSelectedIndex_) {
        RefreshSelected(setSelectedIndex_);
    }
    return true;
}

bool UIPicker::RefreshValues(const char* value[], uint16_t count)
{
    if (value == nullptr || !isWidthSet_ || !isHeightSet_ || !itemsHeight_) {
        return false;
    }

    ClearList();
    for (uint16_t i = 0; i < count; i++) {
        dataList_.PushBack(value[i]);
    }
    textAdapter_.SetData(&dataList_);
    maxCount_ = count;
    RefreshList();
    if (setSelectedIndex_) {
        RefreshSelected(setSelectedIndex_);
    }

    return true;
}

void UIPicker::RefreshList()
{
    int16_t height = GetHeight();
    itemsWidth_ = GetWidth();
    textAdapter_.SetWidth(itemsWidth_);
    textAdapter_.SetHeight(itemsHeight_);
    textAdapter_.SetLineBreakMode(UILabel::LINE_BREAK_CLIP);
    if (backgroundFontName_ == nullptr) {
        textAdapter_.SetFontId(backgroundFontId_);
    } else {
        textAdapter_.SetFont(backgroundFontName_, backgroundFontSize_);
    }
    textAdapter_.GetStyle().textColor_ = backgroundColor_;
    textAdapter_.SetDirect(direct_);
    list_.SetHeight(height);
    list_.SetWidth(itemsWidth_);
    list_.SetPosition(GetWidth() / 2 - list_.GetWidth() / 2, 0); // 2: half
    list_.SetScrollBlankSize((height - itemsHeight_) / 2); // 2: half
    list_.SetSelectPosition(height / 2); // 2: half
    list_.SetStyle(*style_);
    list_.SetStyle(STYLE_BORDER_WIDTH, 0);
    list_.SetStyle(STYLE_BACKGROUND_OPA, 0);
    if (!isSetAdaptered_) {
        list_.SetAdapter(&textAdapter_);
        isSetAdaptered_ = true;
    }

    list_.RefreshList();
    RefreshSelected(0);
}

void UIPicker::ClearValues()
{
    rangeValue_ = nullptr;
    rangeValueCount_ = 0;
    setSelectedIndex_ = 0;
    ClearList();
}

void UIPicker::ClearList()
{
    maxCount_ = 0;
    itemsWidth_ = 0;
    if (listListener_) {
        PickerListScrollListener* listListener = static_cast<PickerListScrollListener*>(listListener_);
        listListener->SetSelectView(nullptr);
        listListener->SetSelectIndex(0);
        listListener->SetInitStatus(false);
    }
    dataList_.Clear();
}

bool UIPicker::SetSelected(uint16_t index)
{
    setSelectedIndex_ = index;
    return RefreshSelected(index);
}

bool UIPicker::RefreshSelected(uint16_t index)
{
    if (itemsHeight_ && (maxCount_ > index) && (list_.GetChildrenHead() != nullptr) && isWidthSet_ && isHeightSet_) {
        uint16_t viewIndex;
        PickerListScrollListener* listListener = static_cast<PickerListScrollListener*>(listListener_);
        listListener->SetInitStatus(false);
        // 2: half
        int16_t yOffset = (list_.GetHeight() - itemsHeight_) / 2 -
            itemsHeight_ * (index - list_.GetChildrenHead()->GetViewIndex());
        list_.ScrollBy(yOffset - list_.GetChildrenHead()->GetY());
        listListener->SetScrollState(ListScrollListener::SCROLL_STATE_STOP);
        UIView* childView = static_cast<UIView*>(list_.GetChildrenHead());
        uint16_t lastSelectIndex = listListener->GetSelectIndex();

        while (childView != nullptr) {
            viewIndex = childView->GetViewIndex();
            if (viewIndex == lastSelectIndex) {
                childView->SetStyle(STYLE_TEXT_COLOR, GetBackgroundTextColor().full);
                if (backgroundFontName_ == nullptr) {
                    static_cast<UILabel*>(childView)->SetFontId(backgroundFontId_);
                } else {
                    static_cast<UILabel*>(childView)->SetFont(backgroundFontName_, backgroundFontSize_);
                }
            }
            if (viewIndex == index) {
                childView->SetStyle(STYLE_TEXT_COLOR, GetHighlightTextColor().full);
                if (highlightFontName_ == nullptr) {
                    static_cast<UILabel*>(childView)->SetFontId(highlightFontId_);
                } else {
                    static_cast<UILabel*>(childView)->SetFont(highlightFontName_, highlightFontSize_);
                }
                listListener->SetSelectView(childView);
                listListener->SetSelectIndex(index);
                listListener->SetInitStatus(true);
            }
            childView = childView->GetNextSibling();
        }
        list_.Invalidate();
        return true;
    }
    return false;
}

uint16_t UIPicker::GetSelected() const
{
    PickerListScrollListener* listListener = static_cast<PickerListScrollListener*>(listListener_);
    return listListener->GetSelectIndex();
}

void UIPicker::SetFontId(uint8_t backgroundFontId, uint8_t highlightFontId)
{
    backgroundFontId_ = backgroundFontId;
    if (backgroundFontName_ != nullptr) {
        UIFree(backgroundFontName_);
        backgroundFontName_ = nullptr;
    }

    highlightFontId_ = highlightFontId;
    if (highlightFontName_ != nullptr) {
        UIFree(highlightFontName_);
        highlightFontName_ = nullptr;
    }

    Refresh();
}

void UIPicker::SetBackgroundFont(const char* name, uint8_t size)
{
    Text::SetFont(name, size, backgroundFontName_, backgroundFontSize_);
    Refresh();
}

void UIPicker::SetHighlightFont(const char* name, uint8_t size)
{
    Text::SetFont(name, size, highlightFontName_, highlightFontSize_);
    Refresh();
}

void UIPicker::SetTextColor(ColorType backgroundColor, ColorType highlightColor)
{
    backgroundColor_ = backgroundColor;
    highlightColor_ = highlightColor;
    Refresh();
}

void UIPicker::SetItemHeight(int16_t height)
{
    if (height > 0) {
        itemsHeight_ = height;
        Refresh();
    }
}

void UIPicker::SetWidth(int16_t width)
{
    if (width > 0) {
        UIView::SetWidth(width);
        isWidthSet_ = true;
        Refresh();
    }
}

void UIPicker::SetHeight(int16_t height)
{
    if (height > 0) {
        UIView::SetHeight(height);
        isHeightSet_ = true;
        Refresh();
    }
}

void UIPicker::SetLoopState(bool state)
{
    list_.SetLoopState(state);
}

void UIPicker::SetDirect(UITextLanguageDirect direct)
{
    direct_ = direct;
    Refresh();
}

void UIPicker::SetTextFormatter(TextFormatter* formatter)
{
    textAdapter_.SetTextFormatter(formatter);
    Refresh();
}
}
