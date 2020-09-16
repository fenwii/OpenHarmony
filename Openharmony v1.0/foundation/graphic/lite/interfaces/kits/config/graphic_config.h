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
 * @file graphic_config.h
 *
 * @brief Provides configuration items required for graphics.
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef GRAPHIC_LITE_GRAPHIC_CONFIG_H
#define GRAPHIC_LITE_GRAPHIC_CONFIG_H

#include "graphic_types.h"

namespace OHOS {
/**
 * Defines three graphics library versions: lightweight, standard, and extended versions.
 * The three versions have different requirements on the memory and hardware.
 * The standard version is enabled by default.
 *
 * The macros of the versions are defined as follows:
 * Name                | Version Description
 * ------------------- | ----------
 * VERSION_LITE        | Lightweight version
 * VERSION_STANDARD    | Standard version
 * VERSION_EXTENDED    | Extended version
 */
#ifdef _LITEOS
#define VERSION_LITE
#elif _WIN32
#define VERSION_LITE
#else
#define VERSION_STANDARD
#endif

/* Defines some configurations and their default values on Huawei LiteOS and other system platforms. */
#ifdef _LITEOS
/**
 * @brief DMA2D hardware acceleration, which is enabled by default on Huawei LiteOS.
 */
#define ENABLE_DMA2D                      1
/**
 * @brief DMA2D hardware acceleration for font rendering, which is disabled by default on Huawei LiteOS.
 */
#define ENABLE_DMA2D_TEXT                 0
/**
 * @brief Advanced algorithm for line breaks, which is enabled by default on Huawei LiteOS.
 */
#define ENABLE_ICU                        1
/**
 * @brief Multi-window, which does not take effect on Huawei LiteOS.
 */
#define ENABLE_WINDOW                     0
/**
 * @brief Display buffer for rendering data refresh, which is disabled by default on Huawei LiteOS.
 */
#define ENABLE_FRAME_BUFFER               0
/**
 * @brief Vector type font，which is disabled by default on Huawei LiteOS.
 */
#define ENABLE_VECTOR_FONT                0
#elif _WIN32
/**
 * @brief DMA2D hardware acceleration, which does not take effect on WIN32.
 */
#define ENABLE_DMA2D                      0
/**
 * @brief DMA2D hardware acceleration for font rendering, which does not take effect on WIN32.
 */
#define ENABLE_DMA2D_TEXT                 0
/**
 * @brief Advanced algorithm for line breaks, which is enabled by default on WIN32.
 */
#define ENABLE_ICU                        1
/**
 * @brief Multi-window, which is disabled by default on WIN32.
 */
#define ENABLE_WINDOW                     0
/**
 * @brief Display buffer for rendering data refresh, which is disabled by default on WIN32.
 */
#define ENABLE_FRAME_BUFFER               0
/**
 * @brief Vector type font，which is enabled by default on WIN32.
 */
#define ENABLE_VECTOR_FONT                1
#else
/**
 * @brief DMA2D hardware acceleration, which does not take effect on other platforms.
 */
#define ENABLE_DMA2D                      0
/**
 * @brief DMA2D hardware acceleration for font rendering, which does not take effect on other platforms.
 */
#define ENABLE_DMA2D_TEXT                 0
/**
 * @brief Advanced algorithm for line breaks, which is disabled by default on other platforms.
 */
#define ENABLE_ICU                        0
/**
 * @brief Multi-window, which is enabled by default on other platforms.
 */
#define ENABLE_WINDOW                     1
/**
 * @brief Display buffer for rendering data refresh, which is disabled by default on other platforms.
 */
#define ENABLE_FRAME_BUFFER               0
/**
 * @brief Vector type font，which is enabled by default on other platforms.
 */
#define ENABLE_VECTOR_FONT                1
#endif
/**
 * @brief Graphics bottom-layer RGBA, which is enabled by default.
 */
#define ENABLE_BUFFER_RGBA                1
#ifdef _WIN32
/**
 * @brief Graphics rendering hardware acceleration, which is disabled by default on WIN32.
 */
#define ENABLE_HARDWARE_ACCELERATION      0
#else
/**
 * @brief Graphics rendering hardware acceleration, which is enabled by default.
 */
#define ENABLE_HARDWARE_ACCELERATION      1
#endif
/**
 * @brief Debug mode, which is disabled by default.
 */
#define ENABLE_DEBUG                      1
/**
 * @brief Memory hook, which is enabled by default. The system memory allocation is taken over after it is enabled.
 */
#define ENABLE_MEMORY_HOOKS               0
/**
 * @brief Function for monitoring the image refresh frame rate, which is disabled by default.
 */
#define ENABLE_FPS_SUPPORT                0
/**
 * @brief Anti-aliasing, which is enabled by default.
 */
#define ENABLE_ANTIALIAS                  1
/**
 * @brief Rectangle anti-aliasing, which is disabled by default.
 */
#define ENABLE_RECT_ANTIALIAS             0
/**
 * @brief Font color mode, which is disabled by default.
 * After it is enabled, the font color mode is set to <b>4</b> to accelerate font rendering.
 */
#define ENABLE_SPEC_FONT                  0
/**
 * @brief Log function of a graphics subsystem, which is disabled by default
 */
#define ENABLE_GRAPHIC_LOG                0
/**
 * @brief Function for receiving input events in screen-off mode, which is disabled by default.
 */
#define ENABLE_AOD                        0

/**
 * @brief Defines the log level. A smaller value indicates a higher priority.
 * Logs whose priorities are higher than a specified level can be recorded.
 * Log levels:
 * NONE: disabling logs
 * FATAL: fatal level
 * ERROR: error level
 * WARN: warning level
 * INFO: info level
 * DEBUG: debugging level
 */
#define GRAPHIC_LOG_LEVEL                 5
/**
 * @brief Defines the color depth of graphics rendering. The default value is <b>32</b> bits.
 * The value can be <b>16</b> or <b>32</b>.
 */
#define COLOR_DEPTH 32
/**
 * @brief Defines the file name of default vector font.
 */
#define DEFAULT_VECTOR_FONT_FILENAME      "SourceHanSansSC-Regular.otf"

/* Defines some configurations and their default values on Huawei LiteOS and other system platforms. */
#ifdef _LITEOS
/* Resolution width of a graphics display screen. The default value is <b>454</b>. */
static constexpr int16_t HORIZONTAL_RESOLUTION = 454;
/* Resolution height of a graphics display screen. The default value is <b>454</b>. */
static constexpr int16_t VERTICAL_RESOLUTION = 454;
#elif _WIN32
/* Resolution width of a graphics display screen. The default value is <b>454</b>. */
static constexpr int16_t HORIZONTAL_RESOLUTION = 454;
/* Resolution height of a graphics display screen. The default value is <b>454</b>. */
static constexpr int16_t VERTICAL_RESOLUTION = 454;
#else
/* Resolution width of a graphics display screen. The default value is <b>960</b>. */
static constexpr int16_t HORIZONTAL_RESOLUTION = 960;
/* Resolution height of a graphics display screen. The default value is <b>480</b>. */
static constexpr int16_t VERTICAL_RESOLUTION = 480;
#endif

/* Defines some configurations and their default values on Huawei LiteOS and other system platforms. */
#ifdef _WIN32
/* Default file path for DOM tree logs */
static constexpr const char* DEFAULT_DUMP_DOM_TREE_PATH = ".\\dump_dom_tree.json";
/* Default file path for font */
static constexpr const char* VECTOR_FONT_DIR = "..\\..\\tools\\font\\font_tool\\font_tool\\font\\";
#elif defined(_LITEOS)
/* Default file path for screenshots */
static constexpr const char* DEFAULT_SCREENSHOT_PATH = "user/log/screenshot.bin";
/* Default file path for DOM tree logs */
static constexpr const char* DEFAULT_DUMP_DOM_TREE_PATH = "user/log/dump_dom_tree.json";
#else
/* Default file path for screenshots */
static constexpr const char* DEFAULT_SCREENSHOT_PATH = "/data/screenshot.bin";
/* Default file path for DOM tree logs */
static constexpr const char* DEFAULT_DUMP_DOM_TREE_PATH = "/data/dump_dom_tree.json";
/* Default file path for font */
static constexpr const char* VECTOR_FONT_DIR = "/user/data/";
#endif
/* Default task execution period. The default value is <b>30</b> ms. */
static constexpr uint8_t DEFAULT_TASK_PERIOD = 30;
/* Window manager execution period. The default value is <b>30</b> ms. */
static constexpr uint8_t WMS_MAIN_TASK_PERIOD = 30;
static constexpr uint8_t IMG_CACHE_SIZE = 5; /* Maximum number of cached images. The default value is <b>5</b>. */
static constexpr uint8_t INDEV_READ_PERIOD = 20; /* Input event read cycle. The default value is <b>20</b> ms. */
/* Drag distance threshold of a drag event. The default value is <b>10px</b>. */
static constexpr uint8_t INDEV_DRAG_LIMIT = 10;
/* Maximum depth of view nesting. The default value is <b>64</b>. */
static constexpr uint8_t COMPONENT_NESTING_DEPTH = 64;
/* Long-press event threshold. The default value is <b>1000</b> ms. */
static constexpr uint16_t INDEV_LONG_PRESS_TIME = 1000;
/* Delay for reporting a press event on a draggable object. The default value is <b>100</b> ms. */
static constexpr uint16_t INDEV_PRESS_TIME_IN_DRAG = 100;
/* Maximum number of bytes in a text that can be continuously displayed. The default value is <b>4096</b> bytes. */
static constexpr uint16_t MAX_TEXT_LENGTH = 4096;
/* Maximum value of the graphic display range. The default value is <b>16383px</b>. */
static constexpr int32_t COORD_MAX = 16383;
/* Minimum value of the graphic display range. The default value is <b>–16384px</b>. */
static constexpr int32_t COORD_MIN = -16384;
} // namespace OHOS
#endif // GRAPHIC_LITE_GRAPHIC_CONFIG_H
