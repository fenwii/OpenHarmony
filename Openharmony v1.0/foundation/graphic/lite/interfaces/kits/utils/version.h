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
 * @file version.h
 *
 * @brief Declares the version number control for the graphics module. This file defines functions to obtain the version
 * number and library description.
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef GRAPHIC_LITE_VERSION_H
#define GRAPHIC_LITE_VERSION_H
#include <string>

namespace OHOS {
/**
 * @brief Obtains the version number of the graphics module.
 *
 * @return Returns the version number of the graphics module.
 * @since 1.0
 * @version 1.0
 */
std::string GetVersion();

/**
 * @brief Obtains the library description of the graphics module.
 *
 * @return Returns the library description of the graphics module.
 * @since 1.0
 * @version 1.0
 */
std::string GetLibDsc();
} // namespace OHOS
#endif
