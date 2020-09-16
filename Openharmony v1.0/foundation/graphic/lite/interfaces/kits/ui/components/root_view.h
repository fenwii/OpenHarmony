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
 * @file root_view.h
 *
 * @brief Manages a root view.
 *
 * A root view is the view containing its child views. It represents the root node in a tree structure and is
 * the parent to all the children.
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef GRAPHIC_LITE_ROOT_VIEW_H
#define GRAPHIC_LITE_ROOT_VIEW_H

#if defined __linux__ || defined __LITEOS__
#include <pthread.h>
#endif
#include "components/ui_view_group.h"
#include "events/key_event.h"
#include "events/virtual_device_event.h"

namespace OHOS {
#if ENABLE_WINDOW
class Window;
class WindowImpl;
#endif

/**
 * @brief Defines the functions related to a root view which contains its child views and represents
 *        the root node in a tree structure.
 *
 * @since 1.0
 * @version 1.0
 */
class RootView : public UIViewGroup {
public:
    /**
     * @brief Obtains a singleton <b>RootView</b> instance.
     *
     * @return Returns the singleton <b>RootView</b> instance.
     * @since 1.0
     * @version 1.0
     */
    static RootView* GetInstance()
    {
        static RootView instance;
        return &instance;
    }

#if ENABLE_WINDOW
    /**
     * @brief Obtains a <b>RootView</b> instance bound to a window.
     *
     * @return Returns the <b>RootView</b> instance.
     * @since 1.0
     * @version 1.0
     */
    static RootView* GetWindowRootView()
    {
        return new RootView;
    }

    /**
     * @brief Destroys the <b>RootView</b> bound to a window.
     *
     * @param rootView Indicates the pointer to the <b>RootView</b> to destroy.
     * @return Returns <b>true</b> if the operation is successful; returns <b>false</b> otherwise.
     * @since 1.0
     * @version 1.0
     */
    static bool DestoryWindowRootView(RootView* rootView)
    {
        if (rootView == RootView::GetInstance()) {
            return false;
        }
        delete rootView;
        return true;
    }
#endif

    /**
     * @brief Represents the listener for monitoring physical key events.
     *
     * @since 1.0
     * @version 1.0
     */
    class OnKeyActListener : public HeapBase {
    public:
        /**
         * @brief Responds to a physical key event.
         *
         * @param view Indicates the view displayed upon a physical key event.
         * @param event Indicates the physical key event to respond to.
         * @return Returns <b>true</b> if the view is normally displayed upon a physical key
         *         event; returns <b> false</b> otherwise.
         * @since 1.0
         * @version 1.0
         */
        virtual bool OnKeyAct(UIView& view, const KeyEvent& event) = 0;
    };

    /**
     * @brief Obtains the view type.
     *
     * @return Returns <b>UI_ROOT_VIEW</b>, as defined in {@link UIViewType}.
     * @since 1.0
     * @version 1.0
     */
    UIViewType GetViewType() const override
    {
        return UI_ROOT_VIEW;
    }

    /**
     * @brief Executes a physical key event.
     *
     * @param event Indicates the physical key event to execute.
     * @since 1.0
     * @version 1.0
     */
    virtual void OnKeyEvent(const KeyEvent& event)
    {
        if (onKeyActListener_ != nullptr) {
            onKeyActListener_->OnKeyAct(*this, event);
        }
    }

    /**
     * @brief Sets the listener that contains a callback to be invoked upon a physical key event.
     *
     * @param onKeyActListener Indicates the pointer to the listener to set.
     * @since 1.0
     * @version 1.0
     */
    void SetOnKeyActListener(OnKeyActListener* onKeyActListener)
    {
        onKeyActListener_ = onKeyActListener;
    }

    /**
     * @brief Clears the listener for monitoring physical key events.
     *
     * @since 1.0
     * @version 1.0
     */
    void ClearOnKeyActListener()
    {
        onKeyActListener_ = nullptr;
    }

    /**
     * @brief Listens for the input events triggered by a virtual device other than
     *        human touching or physical pressing.
     *
     * @since 1.0
     * @version 1.0
     */
    class OnVirtualDeviceEventListener : public HeapBase {
    public:
        /**
         * @brief Responds to an input event triggered by a virtual device.
         *
          * @param view Indicates the view displayed upon an input event triggered by a virtual device.
         * @param event Indicates the input event to respond to.
         * @return Returns <b>true</b> if this view is normally displayed upon an input event triggered by a
         *         virtual device; returns <b> false</b> otherwise.
         * @since 1.0
         * @version 1.0
         */
        virtual bool OnVirtualDeviceEvent(UIView& view, VirtualDeviceEvent event) = 0;
    };

    /**
     * @brief Executes an input event triggered by a virtual device.
     *
     * @param event Indicates the input event to respond to.
     * @since 1.0
     * @version 1.0
     */
    virtual void OnVirtualDeviceEvent(const VirtualDeviceEvent& event)
    {
        if (onVirtualEventListener_ != nullptr) {
            onVirtualEventListener_->OnVirtualDeviceEvent(*this, event);
        }
    }

    /**
     * @brief Sets a listener for monitoring the input events of a virtual device.
     *
     * @param onVirtualDeviceEventListener Indicates the pointer to the listener to set.
     * @since 1.0
     * @version 1.0
     */
    void SetOnVirtualDeviceEventListener(OnVirtualDeviceEventListener* onVirtualDeviceEventListener)
    {
        onVirtualEventListener_ = onVirtualDeviceEventListener;
    }

    /**
     * @brief Clears the listener for monitoring the input events of a virtual device.
     *
     * @since 1.0
     * @version 1.0
     */
    void ClearOnVirtualDeviceEventListener()
    {
        onVirtualEventListener_ = nullptr;
    }

    /**
     * @brief Checks whether the target view is one of the child views of the specified parent view.
     *
     * @param parentView Indicates the specified parent view.
     * @param subView Indicates the target child view.
     * @return Returns <b>true</b> if the target view is available; returns  <b> false</b> otherwise.
     * @since 1.0
     * @version 1.0
     */
    static bool FindSubView(const UIView& parentView, const UIView* subView);

#if ENABLE_WINDOW
    /**
     * @brief Obtains the window bound with a <b>RootView</b>.
     *
     * @return Returns the window.
     * @since 1.0
     * @version 1.0
     */
    Window* GetBoundWindow() const;
#endif

private:
    friend class RenderManager;
    friend class UIView;
#if ENABLE_WINDOW
    friend class WindowImpl;
#endif

    RootView();

    ~RootView() {}

    void AddInvalidateRect(Rect& rect);
    void Render();
    void DrawTop(UIView* view, const Rect& rect);
    UIView* GetTopUIView(const Rect& rect);

    struct ViewMask {
        UIView* view;
        int16_t left;
        int16_t top;
        int16_t right;
        int16_t bottom;
    };

    OnKeyActListener* onKeyActListener_;
    OnVirtualDeviceEventListener* onVirtualEventListener_;
    Rect invalidRect_;
    bool renderFlag_;
    int16_t stackCount_;
    ViewMask viewStack_[COMPONENT_NESTING_DEPTH];
#if defined __linux__ || defined __LITEOS__
    pthread_mutex_t lock_;
#endif

#if ENABLE_WINDOW
    WindowImpl* boundWindow_;
#endif
};
} // namespace OHOS
#endif // GRAPHIC_LITE_ROOT_VIEW_H
