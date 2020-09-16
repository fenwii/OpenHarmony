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
 * @file theme_manager.h
 *
 * @brief Declares the singleton class used to manage the current screen theme of an application.
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef GRAPHIC_LITE_THEME_MANAGER_H
#define GRAPHIC_LITE_THEME_MANAGER_H

#include "themes/theme.h"

namespace OHOS {
/**
 * @brief Declares the singleton class used to manage the current screen theme of an application.
 *
 * @since 1.0
 * @version 1.0
 */
class ThemeManager : public HeapBase {
public:
    /**
     * @brief Obtains the singleton instance of the <b>ThemeManager</b> class.
     *
     * @return Returns the singleton instance of the <b>ThemeManager</b> class.
     */
    static ThemeManager& GetInstance()
    {
        static ThemeManager instance;
        return instance;
    }

    /**
     * @brief Sets the current screen theme for this application.
     *
     * @param theme Indicates the theme to set.
     *
     * @since 1.0
     * @version 1.0
     */
    void SetCurrent(Theme* theme);

    /**
     * @brief Obtains the current screen theme of this application.
     *
     * @return Returns the current theme if available; returns <b>nullptr</b> otherwise.
     *
     * @since 1.0
     * @version 1.0
     */
    Theme* GetCurrent()
    {
        return theme_;
    };

private:
    ThemeManager() : theme_(nullptr) {}
    ~ThemeManager() {}

    Theme* theme_;
};
} // namespace OHOS
#endif // GRAPHIC_LITE_THEME_MANAGER_H
