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

#ifndef OHOS_ACELITE_KEYS_H
#define OHOS_ACELITE_KEYS_H

#include "acelite_config.h"

#ifndef KEYWORD
#define KEYWORDS_ENUM_DEFINE
#define KEYWORD(enumkey, keystr) K_##enumkey,

namespace OHOS {
namespace ACELite {
enum {
    K_UNKNOWN, // enum start from 0
#endif         // KEYWORD

    /*
     * Rules to define the KEYWORD:
     * Should not be duplicated,
     * and use xxx_yyy instead the xxx-yyy as enumstr
     * because of enum define limitation
     */
    // clang-format off
    // Reused by the struct begin
    // Sample:KEYWORD(enum_string, real-key-string)
    KEYWORD(ALIGN_ITEMS, alignItems) // layout style
#ifdef FEATURE_COMPONENT_ANALOG_CLOCK
    KEYWORD(ANALOG_CLOCK, analog-clock) // tag name
#endif // FEATURE_COMPONENT_ANALOG_CLOCK
    KEYWORD(ANIMATION_DELAY, animationDelay) // animation delay
    KEYWORD(ANIMATION_DURATION, animationDuration) // animation during
    KEYWORD(ANIMATION_FILL_MODE, animationFillMode) // animation fill mode
    KEYWORD(ANIMATION_ITERATION_COUNT, animationIterationCount) // animation iteration count
    KEYWORD(ANIMATION_NAME, animationName) // animation name
    KEYWORD(ANIMATION_TIMING_FUNCTION, animationTimingFunction) // animation timing function
    KEYWORD(ARC, arc) // circle progress
#ifdef FEATURE_COMPONENT_VIDEO
    KEYWORD(AUTOPLAY, autoplay) // video component autoplay attribute
#endif // FEATURE_COMPONENT_VIDEO
    KEYWORD(BACKGROUND_COLOR, backgroundColor) // chart line color
    KEYWORD(BACKGROUND_IMAGE, backgroundImage) // common style, but only button, checkbox, radio support
    KEYWORD(BLOCK_COLOR, blockColor)
    KEYWORD(BORDER_BOTTOM_COLOR, borderBottomColor) // common style border bottom color
    KEYWORD(BORDER_LEFT_COLOR, borderLeftColor) // common style border left color
    KEYWORD(BORDER_RIGHT_COLOR, borderRightColor) // common style border right color
    KEYWORD(BORDER_TOP_COLOR, borderTopColor) // common style border top color
    KEYWORD(BORDER_COLOR, borderColor) // common style, horizon progress style
    KEYWORD(BORDER_RADIUS, borderRadius) // horizon progress style
    KEYWORD(BORDER_BOTTOM_WIDTH, borderBottomWidth) // common style border bottom width
    KEYWORD(BORDER_LEFT_WIDTH, borderLeftWidth) // common style border left width
    KEYWORD(BORDER_RIGHT_WIDTH, borderRightWidth) // common style border right width
    KEYWORD(BORDER_TOP_WIDTH, borderTopWidth) // common style border top width
    KEYWORD(BORDER_WIDTH, borderWidth) // common style, horizon progress style
    KEYWORD(BREAK, break) // text overflow type
#ifdef FEATURE_COMPONENT_CAMERA
    KEYWORD(CAMERA, camera) // camera component
#endif // FEATURE_COMPONENT_CAMERA
#ifdef FEATURE_COMPONENT_CANVAS
    KEYWORD(CANVAS, canvas) // tag name
#endif // FEATURE_COMPONENT_CANVAS
    KEYWORD(CENTER, center) // text align type
    KEYWORD(CENTER_X, centerX) // circle progress x
    KEYWORD(CENTER_Y, centerY) // circle progress y
    KEYWORD(CHANGE, change) // the input component event name, picker-view event name
    KEYWORD(CHECKED, checked) // the input and switch component of checkbox attribute
    KEYWORD(CHECKBOX, checkbox) // the input component type value
    KEYWORD(CLICK, click) // click event listener
    KEYWORD(CLIP, clip) // text overflow type
    KEYWORD(CHART, chart) // tag name
#ifdef FEATURE_COMPONENT_ANALOG_CLOCK
    KEYWORD(CLOCK_HAND, clock-hand) // tag name
#endif // FEATURE_COMPONENT_ANALOG_CLOCK
    KEYWORD(COLOR, color) // text style type, rectangular clock-hand fill color, horizon progress style
    KEYWORD(COLUMN, column) // layout style
    KEYWORD(COLUMN_REVERSE, column-reverse) // layout style
#ifdef FEATURE_COMPONENT_VIDEO
    KEYWORD(CONTROLS, controls) // video component controls attribute
#endif // FEATURE_COMPONENT_VIDEO
    KEYWORD(DATASETS, datasets) // chart data
#ifdef FEATURE_COMPONENT_DATE_PICKER
    KEYWORD(DATE, date) // picker-view attr value
#endif // FEATURE_COMPONENT_DATE_PICKER
    KEYWORD(DIRECTION, direction) // progress direction
    KEYWORD(DISPLAY, display) // div layout
    KEYWORD(DIV, div) // tag name
    KEYWORD(DRAG, drag) // drag event listener
    KEYWORD(DURATION, duration)
    KEYWORD(EASE_IN, ease-in) // animation time function value
    KEYWORD(EASE_IN_OUT, ease-in-out) // animation time function value
    KEYWORD(EASE_OUT, ease-out) // animation time function value
    KEYWORD(ELLIPSIS, ellipsis) // text overflow type
#ifdef FEATURE_COMPONENT_DATE_PICKER
    KEYWORD(END, end) // date picker-view attr
#endif // FEATURE_COMPONENT_DATE_PICKER
#if (defined(FEATURE_COMPONENT_CAMERA) || defined(FEATURE_COMPONENT_VIDEO))
    KEYWORD(ERROR, error) // camera component error event
#endif // FEATURE_COMPONENT_CAMERA
    KEYWORD(EXPAND, expand) // text overflow type
    KEYWORD(FALSE, false) // common attributes
#ifdef FEATURE_COMPONENT_VIDEO
    KEYWORD(FINISH, finish) // video component finish event tag
#endif // FEATURE_COMPONENT_VIDEO
    KEYWORD(FIXED_SIZE, fixedsize) // image-animator attribute
    KEYWORD(FLEX_DIRECTION, flexDirection) // layout style
    KEYWORD(FLEX_END, flex-end) // layout style
    KEYWORD(FLEX_START, flex-start) // layout style
    KEYWORD(FLEX_WRAP, flexWrap) // layout style
    KEYWORD(FONT_SIZE, fontSize) // text style type
    KEYWORD(FONT_FAMILY, fontFamily) // text style type
    KEYWORD(FORWARDS, forwards) // animation fill value
    KEYWORD(HEIGHT, height) // common attributes
#ifdef FEATURE_COMPONENT_ANALOG_CLOCK
    KEYWORD(HOUR, hour) // analog-clock hour
#endif // FEATURE_COMPONENT_ANALOG_CLOCK
    KEYWORD(ID, id) // common attributes
    KEYWORD(IMAGE, image) // tag name
    KEYWORD(IMAGE_ANIMATOR, image-animator) // tag name
    KEYWORD(IMAGES, images) // image-animator attribute
    KEYWORD(INDEX, index) // swiper attr index
    KEYWORD(INPUT, input) // input component name
    KEYWORD(ITEM_SELECTED, itemselected) // scroll item selected event listener
    KEYWORD(ITERATION, iteration) // image-animator attribute
    KEYWORD(JUSTIFY_CONTENT, justifyContent) // layout style
#ifdef JS_TOUCH_EVENT_SUPPORT
    KEYWORD(KEY, key) // onkey event
#endif
    KEYWORD(LABELS, labels) // chart labels
    KEYWORD(LARGER, larger) // text font size type
    KEYWORD(LEFT, left) // text align type
    KEYWORD(LETTER_SPACING, letterSpacing) // text style type
    KEYWORD(LINE_HEIGHT, lineHeight) // text style type
    KEYWORD(LIST, list) // list tag name
    KEYWORD(LIST_ITEM, list-item) // list-item tag name
    KEYWORD(LONGPRESS, longpress) // long progress event listener
    KEYWORD(LOOP, loop) // swiper loop attribute
    KEYWORD(MARGIN, margin) // common style margin
    KEYWORD(MARGIN_BOTTOM, marginBottom) // common style margin
    KEYWORD(MARGIN_LEFT, marginLeft) // common style margin left
    KEYWORD(MARGIN_RIGHT, marginRight) // common style margin right
    KEYWORD(MARGIN_TOP, marginTop) // common style margin top
    KEYWORD(MARQUEE, marquee) // marquee tag name
    KEYWORD(MAX, max) // common attributes
    KEYWORD(MIN, min) // common attributes, analog-clock minute
    KEYWORD(MINI, mini) // text font size type
#ifdef FEATURE_COMPONENT_VIDEO
    KEYWORD(MUTED, muted) // video component muted attribute
#endif // FEATURE_COMPONENT_VIDEO
    KEYWORD(NAME, name) // the attribute name
    KEYWORD(NONE, none) // animation fill value
    KEYWORD(OPACITY, opacity) // common style opacity
    KEYWORD(OPATIONS, opations) // chart options
    KEYWORD(PADDING, padding)
    KEYWORD(PADDING_BOTTOM, paddingBottom)
    KEYWORD(PADDING_LEFT, paddingLeft)
    KEYWORD(PADDING_RIGHT, paddingRight)
    KEYWORD(PADDING_TOP, paddingTop)
    KEYWORD(PERCENT, percent)
    KEYWORD(PICKER_VIEW, picker-view) // tag name
    KEYWORD(REF, ref) // common attribute
#ifdef FEATURE_COMPONENT_VIDEO
    KEYWORD(PREPARED, prepared) // video component prepared event
#endif // FEATURE_COMPONENT_VIDEO
#ifdef FEATURE_COMPONENT_ANALOG_CLOCK
    KEYWORD(PIVOT_X, pivotX) // clock-hand pivot-x
    KEYWORD(PIVOT_Y, pivotY) // clock-hand pivot-y
#endif // FEATURE_COMPONENT_ANALOG_CLOCK
    KEYWORD(PROGRESS, progress) // progress tag name
    KEYWORD(RADIO, radio) // the type in input
    KEYWORD(RADIUS, radius) // circle progress radius
    KEYWORD(RANGE, range) // picker-view attr
#ifdef FEATURE_COMPONENT_VIDEO
    KEYWORD(PAUSE, pause) // video component pause event tag
#endif // FEATURE_COMPONENT_VIDEO
    KEYWORD(REVERSE, reverse) // image-animator attribute
    KEYWORD(RIGHT, right) // text align type
    KEYWORD(ROTATE, rotate) // animation rotate
    KEYWORD(ROW, row) // layout style
    KEYWORD(ROW_REVERSE, row-reverse) // layout style
    KEYWORD(SCROLLAMOUNT, scrollamount) // marquee scroll speed
    KEYWORD(SCROLLEND, scrollend) // scroll end event listener
    KEYWORD(SCROLLSTART, scrollstart) // scroll start event listener
#ifdef FEATURE_COMPONENT_ANALOG_CLOCK
    KEYWORD(SEC, sec) // analog-clock second
#endif // FEATURE_COMPONENT_ANALOG_CLOCK
#ifdef FEATURE_COMPONENT_VIDEO
    KEYWORD(SEEKING, seeking) // // video component seeking event tag
    KEYWORD(SEEKED, seeked) // // video component seeked event tag
#endif // FEATURE_COMPONENT_VIDEO
    KEYWORD(SELECTED, selected) // picker-view attr
    KEYWORD(SELECTED_COLOR, selectedColor) // picker-view style
    KEYWORD(SELECTED_FONT_FAMILY, selectedFontFamily) // picker-view style
    KEYWORD(SELECTED_FONT_SIZE, selectedFontSize) // picker-view style
    KEYWORD(SHOW, show)
    KEYWORD(SLIDER, slider) // tag name
    KEYWORD(SPACE_AROUND, space-around) // layout style
    KEYWORD(SPACE_BETWEEN, space-between) // layout style
    KEYWORD(SRC, src) // common attributes, use for image view, video compnent
    KEYWORD(STACK, stack) // tag name
    KEYWORD(STANDARD, standard) // text font size type
    KEYWORD(STOP, stop) // image-animator stop event, video component end event tag
#if (defined(FEATURE_COMPONENT_DATE_PICKER) || defined(FEATURE_COMPONENT_VIDEO))
    KEYWORD(START, start) // date picker-view attr, video component start event tag
#endif // (defined(FEATURE_COMPONENT_DATE_PICKER) || defined(FEATURE_COMPONENT_VIDEO)
    KEYWORD(START_ANGLE, startAngle) // circle progress start angle
    KEYWORD(STEP, step)
    KEYWORD(STROKE_WIDTH, strokeWidth) // horizon/arc progress style
    KEYWORD(SWIPE, swipe)  // swipe event listener
    KEYWORD(SWIPER, swiper) // tag name
    KEYWORD(SWITCH, switch) // tag name
#ifdef FEATURE_COMPONENT_TABS
    KEYWORD(TAB_BAR, tab-bar) // tag name
    KEYWORD(TAB_CONTENT, tab-content) // tag name
    KEYWORD(TABS, tabs) // tag name
#endif // FEATURE_COMPONENT_TABS
    KEYWORD(TEXT, text) // tag name, picker-view attr value
    KEYWORD(TEXT_ALIGN, textAlign) // text style type
    KEYWORD(TEXT_OVERFLOW, textOverflow) // text style type
    KEYWORD(TIME, time) // picker-view attr value
#ifdef FEATURE_COMPONENT_VIDEO
    KEYWORD(TIME_UPDATE, timeupdate) // video component timeupdate event tag
#endif // FEATURE_COMPONENT_VIDEO
    KEYWORD(TOP, top)
    KEYWORD(TOTAL_ANGLE, total-angle) // circle progress style
#ifdef JS_TOUCH_EVENT_SUPPORT
    KEYWORD(TOUCHCANCEL, touchcancel) // ontouchcancel event
    KEYWORD(TOUCHEND, touchend) // ontouchend event
    KEYWORD(TOUCHMOVE, touchmove) // ontouchmove event
    KEYWORD(TOUCHSTART, touchstart) // ontouchstart event
#endif
    KEYWORD(TRANSLATE_X, translateX) // animation transform x
    KEYWORD(TRANSLATE_Y, translateY) // animation transform y
    KEYWORD(TRUE, true) // common attributes
#ifdef FEATURE_COMPONENT_ANALOG_CLOCK
    KEYWORD(TYPE, type) // clock-hand type
#endif // FEATURE_COMPONENT_ANALOG_CLOCK
    KEYWORD(VALUE, value) // common attributes
    KEYWORD(VERTICAL, vertical) // swiper attr vertical
#ifdef FEATURE_COMPONENT_VIDEO
    KEYWORD(VIDEO, video) // video tag name
#endif // FEATURE_COMPONENT_VIDEO
    KEYWORD(WIDTH, width) // common attributes
    KEYWORD(WRAP, wrap) // flex wrap
    // Reused by the struct end
// clang-format on
#ifdef KEYWORDS_ENUM_DEFINE
    KEYWORDS_MAX, // max size is UINT16_MAX
};
#undef KEYWORDS_ENUM_DEFINE
#undef KEYWORD
} // namespace ACELite
} // OHOS namespace
#endif // KEYWORDS_ENUM_DEFINE

#endif // OHOS_ACELITE_KEYS_H
