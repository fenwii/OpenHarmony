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

#include "key_parser.h"
#include <string.h>
#include "acelite_config.h"
#include "js_config.h"
#include "keys.h"

namespace OHOS {
namespace ACELite {
#ifdef KEYWORD
#undef KEYWORD
#endif // KEYWORD

// Replace the struct keys.h "KEYWORD" sector for init
#if defined(ENABLE_KEY)
#define KEYWORD(enumkey, keystr) {#keystr, K_##enumkey, static_cast<uint8_t>(strlen(#enumkey))},
#else // ENABLE_KEY
#define KEYWORD(enumkey, keystr) {K_##enumkey, static_cast<uint8_t>(strlen(#enumkey))},
#endif // ENABLE_KEY

static const struct {
#if defined(ENABLE_KEY)
    const char * const key;
#endif
    const uint16_t ID;
    const uint8_t LENGTH;
} G_KEYWORD_INFO[KEYWORDS_MAX] = {
#if defined(ENABLE_KEY)
    {"UNKNOWN", K_UNKNOWN, static_cast<uint8_t>(strlen("UNKNOWN"))},
#else  // ENABLE_KEY
    {K_UNKNOWN, static_cast<uint8_t>(strlen("UNKNOWN"))},
#endif // ENABLE_KEY

#ifdef OHOS_ACELITE_KEYS_H
// include the keys.h again to redefine the "KEYWORD"
#undef OHOS_ACELITE_KEYS_H
#include "keys.h"
#endif // OHOS_ACELITE_KEYS_H
};
#undef KEYWORD

uint16_t KeyParser::ParseKeyId(const char *s, const size_t len)
{
    if (s == nullptr || len >= UINT16_MAX || len == 0) {
        return K_UNKNOWN;
    }
    /*
     * The string was compared should be the same as the js define,
     * with xxx-yyy instead the xxx_yyy,
     * but the enum type use K_xxx_yyy for Id return
     */
    switch (*s++) {
            // clang-format off
        case 'a':
            if (!strcmp(s, "lignItems")) {
                return K_ALIGN_ITEMS;
            }
#ifdef FEATURE_COMPONENT_ANALOG_CLOCK
            if (!strcmp(s, "nalog-clock")) {
                return K_ANALOG_CLOCK;
            }
#endif // FEATURE_COMPONENT_ANALOG_CLOCK
            if (!strcmp(s, "nimationDelay")) {
                return K_ANIMATION_DELAY;
            }
            if (!strcmp(s, "nimationDuration")) {
                return K_ANIMATION_DURATION;
            }
            if (!strcmp(s, "nimationFillMode")) {
                return K_ANIMATION_FILL_MODE;
            }
            if (!strcmp(s, "nimationIterationCount")) {
                return K_ANIMATION_ITERATION_COUNT;
            }
            if (!strcmp(s, "nimationName")) {
                return K_ANIMATION_NAME;
            }
            if (!strcmp(s, "nimationTimingFunction")) {
                return K_ANIMATION_TIMING_FUNCTION;
            }
            if (!strcmp(s, "rc")) {
                return K_ARC;
            }
#ifdef FEATURE_COMPONENT_VIDEO
            if (!strcmp(s, "utoplay")) {
                return K_AUTOPLAY;
            }
#endif // FEATURE_COMPONENT_VIDEO
            break;
        case 'b':
            if (!strcmp(s, "ackgroundColor")) {
                return K_BACKGROUND_COLOR;
            }
            if (!strcmp(s, "ackgroundImage")) {
                return K_BACKGROUND_IMAGE;
            }
            if (!strcmp(s, "lockColor")) {
                return K_BLOCK_COLOR;
            }
            if (!strcmp(s, "orderBottomColor")) {
                return K_BORDER_BOTTOM_COLOR;
            }
            if (!strcmp(s, "orderLeftColor")) {
                return K_BORDER_LEFT_COLOR;
            }
            if (!strcmp(s, "orderRightColor")) {
                return K_BORDER_RIGHT_COLOR;
            }
            if (!strcmp(s, "orderTopColor")) {
                return K_BORDER_TOP_COLOR;
            }
            if (!strcmp(s, "orderColor")) {
                return K_BORDER_COLOR;
            }
            if (!strcmp(s, "orderRadius")) {
                return K_BORDER_RADIUS;
            }
            if (!strcmp(s, "orderBottomWidth")) {
                return K_BORDER_BOTTOM_WIDTH;
            }
            if (!strcmp(s, "orderLeftWidth")) {
                return K_BORDER_LEFT_WIDTH;
            }
            if (!strcmp(s, "orderRightWidth")) {
                return K_BORDER_RIGHT_WIDTH;
            }
            if (!strcmp(s, "orderTopWidth")) {
                return K_BORDER_TOP_WIDTH;
            }
            if (!strcmp(s, "orderWidth")) {
                return K_BORDER_WIDTH;
            }
            if (!strcmp(s, "reak")) {
                return K_BREAK;
            }
            break;
        case 'c':
#ifdef FEATURE_COMPONENT_CAMERA
            if (!strcmp(s, "amera")) {
                return K_CAMERA;
            }
#endif // FEATURE_COMPONENT_CAMERA
#ifdef FEATURE_COMPONENT_CANVAS
            if (!strcmp(s, "anvas")) {
                return K_CANVAS;
            }
#endif // FEATURE_COMPONENT_CANVAS
            if (!strcmp(s, "enter")) {
                return K_CENTER;
            }
            if (!strcmp(s, "enterX")) {
                return K_CENTER_X;
            }
            if (!strcmp(s, "enterY")) {
                return K_CENTER_Y;
            }
            if (!strcmp(s, "olor")) {
                return K_COLOR;
            }
            if (!strcmp(s, "olumn")) {
                return K_COLUMN;
            }
            if (!strcmp(s, "olumn-reverse")) {
                return K_COLUMN_REVERSE;
            }
#ifdef FEATURE_COMPONENT_VIDEO
            if (!strcmp(s, "ontrols")) {
                return K_CONTROLS;
            }
#endif // FEATURE_COMPONENT_VIDEO
            if (!strcmp(s, "hange")) {
                return K_CHANGE;
            }
            if (!strcmp(s, "heckbox")) {
                return K_CHECKBOX;
            }
            if (!strcmp(s, "hecked")) {
                return K_CHECKED;
            }
            if (!strcmp(s, "lick")) {
                return K_CLICK;
            }
            if (!strcmp(s, "hart")) {
                return K_CHART;
            }
            if (!strcmp(s, "lip")) {
                return K_CLIP;
            }
#ifdef FEATURE_COMPONENT_ANALOG_CLOCK
            if (!strcmp(s, "lock-hand")) {
                return K_CLOCK_HAND;
            }
#endif // FEATURE_COMPONENT_ANALOG_CLOCK
        case 'd':
            if (!strcmp(s, "atasets")) {
                return K_DATASETS;
            }
#ifdef FEATURE_COMPONENT_DATE_PICKER
            if (!strcmp(s, "ate")) {
                return K_DATE;
            }
#endif // FEATURE_COMPONENT_DATE_PICKER
            if (!strcmp(s, "irection")) {
                return K_DIRECTION;
            }
            if (!strcmp(s, "isplay")) {
                return K_DISPLAY;
            }
            if (!strcmp(s, "iv")) {
                return K_DIV;
            }
            if (!strcmp(s, "rag")) {
                return K_DRAG;
            }
            if (!strcmp(s, "uration")) {
                return K_DURATION;
            }
            break;
        case 'e':
            if (!strcmp(s, "ase-in")) {
                return K_EASE_IN;
            }
            if (!strcmp(s, "ase-in-out")) {
                return K_EASE_IN_OUT;
            }
            if (!strcmp(s, "ase-out")) {
                return K_EASE_OUT;
            }
            if (!strcmp(s, "llipsis")) {
                return K_ELLIPSIS;
            }
#ifdef FEATURE_COMPONENT_DATE_PICKER
            if (!strcmp(s, "nd")) {
                return K_END;
            }
#endif // FEATURE_COMPONENT_DATE_PICKER
#if (defined(FEATURE_COMPONENT_CAMERA) || defined(FEATURE_COMPONENT_VIDEO))
            if (!strcmp(s, "rror")) {
                return K_ERROR;
            }
#endif // defined(FEATURE_COMPONENT_CAMERA) || defined(FEATURE_COMPONENT_VIDEO)
            if (!strcmp(s, "xpand")) {
                return K_EXPAND;
            }
            break;
        case 'f':
            if (!strcmp(s, "alse")) {
                return K_FALSE;
            }
            if (!strcmp(s, "ixedsize")) {
                return K_FIXED_SIZE;
            }
#ifdef FEATURE_COMPONENT_VIDEO
            if (!strcmp(s, "inish")) {
                return K_FINISH;
            }
#endif // FEATURE_COMPONENT_VIDEO
            if (!strcmp(s, "lex-end")) {
                return K_FLEX_END;
            }
            if (!strcmp(s, "lex-start")) {
                return K_FLEX_START;
            }
            if (!strcmp(s, "lexDirection")) {
                return K_FLEX_DIRECTION;
            }
            if (!strcmp(s, "lexWrap")) {
                return K_FLEX_WRAP;
            }
            if (!strcmp(s, "ontSize")) {
                return K_FONT_SIZE;
            }
            if (!strcmp(s, "ontFamily")) {
                return K_FONT_FAMILY;
            }
            if (!strcmp(s, "orwards")) {
                return K_FORWARDS;
            }
            break;
        case 'h':
            if (!strcmp(s, "eight")) {
                return K_HEIGHT;
            }
#ifdef FEATURE_COMPONENT_ANALOG_CLOCK
            if (!strcmp(s, "our")) {
                return K_HOUR;
            }
#endif // FEATURE_COMPONENT_ANALOG_CLOCK
            break;
        case 'i':
            if (!strcmp(s, "d")) {
                return K_ID;
            }
            if (!strcmp(s, "mage")) {
                return K_IMAGE;
            }
            if (!strcmp(s, "mage-animator")) {
                return K_IMAGE_ANIMATOR;
            }
            if (!strcmp(s, "mages")) {
                return K_IMAGES;
            }
            if (!strcmp(s, "nput")) {
                return K_INPUT;
            }
            if (!strcmp(s, "ndex")) {
                return K_INDEX;
            }
            if (!strcmp(s, "temselected")) {
                return K_ITEM_SELECTED;
            }
            if (!strcmp(s, "teration")) {
                return K_ITERATION;
            }
            break;
        case 'j':
            if (!strcmp(s, "ustifyContent")) {
                return K_JUSTIFY_CONTENT;
            }
            break;
#ifdef JS_TOUCH_EVENT_SUPPORT
        case 'k':
            if (!strcmp(s, "ey")) {
                return K_KEY;
            }
            break;
#endif
        case 'l':
            if (!strcmp(s, "abels")) {
                return K_LABELS;
            }
            if (!strcmp(s, "arger")) {
                return K_LARGER;
            }
            if (!strcmp(s, "eft")) {
                return K_LEFT;
            }
            if (!strcmp(s, "etterSpacing")) {
                return K_LETTER_SPACING;
            }
            if (!strcmp(s, "ineHeight")) {
                return K_LINE_HEIGHT;
            }
            if (!strcmp(s, "ist")) {
                return K_LIST;
            }
            if (!strcmp(s, "ist-item")) {
                return K_LIST_ITEM;
            }
            if (!strcmp(s, "ongpress")) {
                return K_LONGPRESS;
            }
            if (!strcmp(s, "oop")) {
                return K_LOOP;
            }
            break;
        case 'm':
            if (!strcmp(s, "argin")) {
                return K_MARGIN;
            }
            if (!strcmp(s, "arginBottom")) {
                return K_MARGIN_BOTTOM;
            }
            if (!strcmp(s, "arginLeft")) {
                return K_MARGIN_LEFT;
            }
            if (!strcmp(s, "arginRight")) {
                return K_MARGIN_RIGHT;
            }
            if (!strcmp(s, "arginTop")) {
                return K_MARGIN_TOP;
            }
            if (!strcmp(s, "arquee")) {
                return K_MARQUEE;
            }
            if (!strcmp(s, "ax")) {
                return K_MAX;
            }
            if (!strcmp(s, "in")) {
                return K_MIN;
            }
            if (!strcmp(s, "ini")) {
                return K_MINI;
            }
#ifdef FEATURE_COMPONENT_VIDEO
            if (!strcmp(s, "uted")) {
                return K_MUTED;
            }
#endif // FEATURE_COMPONENT_VIDEO
            break;
        case 'n':
            if (!strcmp(s, "ame")) {
                return K_NAME;
            }
            if (!strcmp(s, "one")) {
                return K_NONE;
            }
            break;
        case 'o':
            if (!strcmp(s, "pacity")) {
                return K_OPACITY;
            }
            if (!strcmp(s, "ptions")) {
                return K_OPATIONS;
            }
            break;
        case 'p':
            if (!strcmp(s, "adding")) {
                return K_PADDING;
            }
            if (!strcmp(s, "addingBottom")) {
                return K_PADDING_BOTTOM;
            }
            if (!strcmp(s, "addingLeft")) {
                return K_PADDING_LEFT;
            }
            if (!strcmp(s, "addingRight")) {
                return K_PADDING_RIGHT;
            }
            if (!strcmp(s, "addingTop")) {
                return K_PADDING_TOP;
            }
#ifdef FEATURE_COMPONENT_VIDEO
            if (!strcmp(s, "ause")) {
                return K_PAUSE;
            }
#endif // FEATURE_COMPONENT_VIDEO
            if (!strcmp(s, "ercent")) {
                return K_PERCENT;
            }
            if (!strcmp(s, "icker-view")) {
                return K_PICKER_VIEW;
            }
#ifdef FEATURE_COMPONENT_ANALOG_CLOCK
            if (!strcmp(s, "ivotX")) {
                return K_PIVOT_X;
            }
            if (!strcmp(s, "ivotY")) {
                return K_PIVOT_Y;
            }
#endif // FEATURE_COMPONENT_ANALOG_CLOCK
#ifdef FEATURE_COMPONENT_VIDEO
            if (!strcmp(s, "repared")) {
                return K_PREPARED;
            }
#endif // FEATURE_COMPONENT_VIDEO
            if (!strcmp(s, "rogress")) {
                return K_PROGRESS;
            }
            break;
        case 'r':
            if (!strcmp(s, "adio")) {
                return K_RADIO;
            }
            if (!strcmp(s, "adius")) {
                return K_RADIUS;
            }
            if (!strcmp(s, "ange")) {
                return K_RANGE;
            }
            if (!strcmp(s, "ef")) {
                return K_REF;
            }
            if (!strcmp(s, "everse")) {
                return K_REVERSE;
            }
            if (!strcmp(s, "ight")) {
                return K_RIGHT;
            }
            if (!strcmp(s, "otate")) {
                return K_ROTATE;
            }
            if (!strcmp(s, "ow")) {
                return K_ROW;
            }
            if (!strcmp(s, "ow-reverse")) {
                return K_ROW_REVERSE;
            }
            break;
        case 's':
            if (!strcmp(s, "crollamount")) {
                return K_SCROLLAMOUNT;
            }
            if (!strcmp(s, "crollend")) {
                return K_SCROLLEND;
            }
            if (!strcmp(s, "crollstart")) {
                return K_SCROLLSTART;
            }
#ifdef FEATURE_COMPONENT_ANALOG_CLOCK
            if (!strcmp(s, "ec")) {
                return K_SEC;
            }
#endif // FEATURE_COMPONENT_ANALOG_CLOCK
#ifdef FEATURE_COMPONENT_VIDEO
            if (!strcmp(s, "eeked")) {
                return K_SEEKED;
            }
            if (!strcmp(s, "eeking")) {
                return K_SEEKING;
            }
#endif // FEATURE_COMPONENT_VIDEO
            if (!strcmp(s, "elected")) {
                return K_SELECTED;
            }
            if (!strcmp(s, "electedColor")) {
                return K_SELECTED_COLOR;
            }
            if (!strcmp(s, "electedFontFamily")) {
                return K_SELECTED_FONT_FAMILY;
            }
            if (!strcmp(s, "electedFontSize")) {
                return K_SELECTED_FONT_SIZE;
            }
            if (!strcmp(s, "how")) {
                return K_SHOW;
            }
            if (!strcmp(s, "lider")) {
                return K_SLIDER;
            }
            if (!strcmp(s, "pace-around")) {
                return K_SPACE_AROUND;
            }
            if (!strcmp(s, "pace-between")) {
                return K_SPACE_BETWEEN;
            }
            if (!strcmp(s, "rc")) {
                return K_SRC;
            }
            if (!strcmp(s, "tack")) {
                return K_STACK;
            }
            if (!strcmp(s, "top")) {
                return K_STOP;
            }
#if (defined(FEATURE_COMPONENT_DATE_PICKER) || defined(FEATURE_COMPONENT_VIDEO))
            if (!strcmp(s, "tart")) {
                return K_START;
            }
#endif // (defined(FEATURE_COMPONENT_DATE_PICKER) || defined(FEATURE_COMPONENT_VIDEO)
            if (!strcmp(s, "tartAngle")) {
                return K_START_ANGLE;
            }
            if (!strcmp(s, "tandard")) {
                return K_STANDARD;
            }
            if (!strcmp(s, "trokeWidth")) {
                return K_STROKE_WIDTH;
            }
            if (!strcmp(s, "wipe")) {
                return K_SWIPE;
            }
            if (!strcmp(s, "wiper")) {
                return K_SWIPER;
            }
            if (!strcmp(s, "witch")) {
                return K_SWITCH;
            }
            break;
        case 't':
#ifdef FEATURE_COMPONENT_TABS
            if (!strcmp(s, "ab-bar")) {
                return K_TAB_BAR;
            }
            if (!strcmp(s, "ab-content")) {
                return K_TAB_CONTENT;
            }
            if (!strcmp(s, "abs")) {
                return K_TABS;
            }
#endif // FEATURE_COMPONENT_TABS
            if (!strcmp(s, "ime")) {
                return K_TIME;
            }
#ifdef FEATURE_COMPONENT_VIDEO
            if (!strcmp(s, "imeupdate")) {
                return K_TIME_UPDATE;
            }
#endif // FEATURE_COMPONENT_VIDEO
            if (!strcmp(s, "op")) {
                return K_TOP;
            }
            if (!strcmp(s, "otalAngle")) {
                return K_TOTAL_ANGLE;
            }
#ifdef JS_TOUCH_EVENT_SUPPORT
            if (!strcmp(s, "ouchcancel")) {
                return K_TOUCHCANCEL;
            }
            if (!strcmp(s, "ouchend")) {
                return K_TOUCHEND;
            }
            if (!strcmp(s, "ouchmove")) {
                return K_TOUCHMOVE;
            }
            if (!strcmp(s, "ouchstart")) {
                return K_TOUCHSTART;
            }
#endif
            if (!strcmp(s, "ext")) {
                return K_TEXT;
            }
            if (!strcmp(s, "ranslateX")) {
                return K_TRANSLATE_X;
            }
            if (!strcmp(s, "ranslateY")) {
                return K_TRANSLATE_Y;
            }
            if (!strcmp(s, "rue")) {
                return K_TRUE;
            }
            if (!strcmp(s, "extAlign")) {
                return K_TEXT_ALIGN;
            }
            if (!strcmp(s, "extOverflow")) {
                return K_TEXT_OVERFLOW;
            }
#ifdef FEATURE_COMPONENT_ANALOG_CLOCK
            if (!strcmp(s, "ype")) {
                return K_TYPE;
            }
#endif // FEATURE_COMPONENT_ANALOG_CLOCK
            break;
        case 'v':
            if (!strcmp(s, "alue")) {
                return K_VALUE;
            }
            if (!strcmp(s, "ertical")) {
                return K_VERTICAL;
            }
#ifdef FEATURE_COMPONENT_VIDEO
            if (!strcmp(s, "ideo")) {
                return K_VIDEO;
            }
#endif // FEATURE_COMPONENT_VIDEO
            break;
        case 'w':
            if (!strcmp(s, "idth")) {
                return K_WIDTH;
            }
            if (!strcmp(s, "rap")) {
                return K_WRAP;
            }
            break;
        default:
            break;
            // clang-format on
    }
    return K_UNKNOWN;
}

uint16_t KeyParser::ParseKeyId(const char * const s)
{
    if (s == nullptr) {
        return K_UNKNOWN;
    }

    size_t len = strlen(s);
    if (len >= UINT16_MAX) {
        return K_UNKNOWN;
    }
    return ParseKeyId(s, len);
}

bool KeyParser::IsKeyValid(uint16_t id)
{
    return ((id > K_UNKNOWN) && (id < KEYWORDS_MAX));
}

const char *KeyParser::GetKeyById(uint16_t id)
{
    if (!IsKeyValid(id)) {
        return "UNKNOWN";
    }
#if defined(ENABLE_KEY)
    return G_KEYWORD_INFO[id].key;
#else
    return "UNKNOWN";
#endif // ENABLE_KEY
}

uint8_t KeyParser::GetKeyLengthById(uint16_t id)
{
    if (!IsKeyValid(id)) {
        return 0;
    }
    return G_KEYWORD_INFO[id].LENGTH;
}
} // namespace ACELite
} // namespace OHOS
