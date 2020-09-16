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

#include "components/root_view.h"
#include "common/screen.h"
#include "common/screen_device_proxy.h"
#include "core/render_manager.h"
#include "graphic_log.h"
#include "securec.h"
#if ENABLE_WINDOW
#include "window/window_impl.h"
#endif

namespace OHOS {
RootView::RootView()
    : onKeyActListener_(nullptr), onVirtualEventListener_(nullptr), invalidRect_(0, 0, 0, 0), renderFlag_(false),
      stackCount_(0), viewStack_ { { 0 } }
{
#if ENABLE_WINDOW
    boundWindow_ = nullptr;
#endif

#if defined __linux__ || defined __LITEOS__
    pthread_mutex_init(&lock_, nullptr);
#endif
}

#if ENABLE_WINDOW
Window* RootView::GetBoundWindow() const
{
    return boundWindow_;
}
#endif

void RootView::AddInvalidateRect(Rect& rect)
{
#if defined __linux__ || defined __LITEOS__
    pthread_mutex_lock(&lock_);
#endif

#if ENABLE_WINDOW
    Rect screenRect = GetRect();
#else
    Rect screenRect(0, 0, Screen::GetInstance().GetWidth() - 1, Screen::GetInstance().GetHeight() - 1);
#endif

    Rect commonRect;
    if (commonRect.Intersect(rect, screenRect)) {
        invalidRect_.Join(invalidRect_, commonRect);
        renderFlag_ = true;
    }

#if defined __linux__ || defined __LITEOS__
    pthread_mutex_unlock(&lock_);
#endif
}

void RootView::Render()
{
#if defined __linux__ || defined __LITEOS__
    pthread_mutex_lock(&lock_);
#endif

    if (renderFlag_) {
        RenderManager::RenderRect(invalidRect_, this);
#if ENABLE_WINDOW
        if (boundWindow_) {
            boundWindow_->Flush();
            boundWindow_->Update();
        }
#endif
        ScreenDeviceProxy::GetInstance()->OnRenderFinish();
    }

    renderFlag_ = false;
    invalidRect_ = { 0, 0, 0, 0 };
#if defined __linux__ || defined __LITEOS__
    pthread_mutex_unlock(&lock_);
#endif
}

void RootView::DrawTop(UIView* view, const Rect& rect)
{
    if (view == nullptr) {
        return;
    }
    stackCount_ = 0;
    UIView* par = view->GetParent();
    if (par == nullptr) {
        par = view;
    }
    UIView* curView = view;
    Rect curViewRect;
    Rect mask = rect;
    while (par != nullptr) {
        if (curView != nullptr) {
            if (curView->IsVisible()) {
                curViewRect = curView->GetMaskedRect();
                if (curViewRect.Intersect(curViewRect, mask)) {
                    curView->OnDraw(curViewRect);
                    if (curView->IsViewGroup() && stackCount_ < COMPONENT_NESTING_DEPTH) {
                        par = curView;
                        viewStack_[stackCount_] = {
                            curView, mask.GetLeft(), mask.GetTop(), mask.GetRight(), mask.GetBottom()
                        };
                        stackCount_++;
                        curView = static_cast<UIViewGroup*>(curView)->GetChildrenHead();
                        mask = par->GetContentRect();
                        mask.Intersect(mask, curViewRect);
                        continue;
                    }
                    curView->OnPostDraw(curViewRect);
                }
            }
            curView = curView->GetNextSibling();
        } else if (--stackCount_ >= 0) {
            ViewMask sides = viewStack_[stackCount_];
            mask = { sides.left, sides.top, sides.right, sides.bottom };
            curViewRect = par->GetMaskedRect();
            if (curViewRect.Intersect(curViewRect, mask)) {
                par->OnPostDraw(curViewRect);
            }
            curView = sides.view->GetNextSibling();
            par = par->GetParent();
        } else {
            stackCount_ = 0;
            curView = par->GetNextSibling();
            par = par->GetParent();
        }
    }
}

UIView* RootView::GetTopUIView(const Rect& rect)
{
    int16_t stackCount_ = 0;
    UIView* currentView = this;
    UIView* topView = nullptr;
    while (stackCount_ >= 0) {
        while (currentView != nullptr) {
            if (currentView->GetRect().IsContains(rect) && currentView->IsVisible()) {
                if (currentView->GetStyleConst().bgOpa_ == OPA_OPAQUE && currentView->OnPreDraw(rect)) {
                    topView = currentView;
                }
                if (currentView->IsViewGroup() && stackCount_ < COMPONENT_NESTING_DEPTH) {
                    viewStack_[stackCount_++].view = currentView;
                    currentView = static_cast<UIViewGroup*>(currentView)->GetChildrenHead();
                    continue;
                }
            }
            currentView = currentView->GetNextSibling();
        }
        if (--stackCount_ >= 0) {
            currentView = (viewStack_[stackCount_].view)->GetNextSibling();
        }
    }
    return topView;
}

bool RootView::FindSubView(const UIView& parentView, const UIView* subView)
{
    const UIView* root = &parentView;
    if (root == subView) {
        return true;
    } else if (!root->IsViewGroup() || subView == nullptr) {
        return false;
    }

    UIView* currentView = static_cast<const UIViewGroup*>(root)->GetChildrenHead();
    const UIView* parent = root;
    int8_t deep = 1;
    while (deep > 0) {
        if (currentView == subView) {
            return true;
        }
        if (currentView == nullptr) {
            currentView = parent->GetNextSibling();
            parent = parent->GetParent();
            deep--;
        } else if (currentView->IsViewGroup()) {
            parent = currentView;
            currentView = static_cast<UIViewGroup*>(currentView)->GetChildrenHead();
            deep++;
        } else {
            currentView = currentView->GetNextSibling();
        }
    }
    return false;
}
} // namespace OHOS