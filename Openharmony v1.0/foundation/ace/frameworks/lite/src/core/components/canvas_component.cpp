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

#include "acelite_config.h"

#ifdef FEATURE_COMPONENT_CANVAS
#include "canvas_component.h"
#include "js_fwk_common.h"

namespace OHOS {
namespace ACELite {
// default fill style color=black
const char * const CanvasComponent::DEFAULT_FILLSTYLE = "#000000";
// default stroke style color=black
const char * const CanvasComponent::DEFAULT_STROKESTYLE = "#000000";
// default font size=30px, font family=HYQiHei-65S
const char * const CanvasComponent::DEFAULT_FONT = "30px HYQiHei-65S";
// default text align=left
const char * const CanvasComponent::DEFAULT_TEXTALIGN = "left";

const uint8_t CanvasComponent::ARGS_COUNT_ONE = 1;
const uint8_t CanvasComponent::ARGS_COUNT_THREE = 3;
const uint8_t CanvasComponent::ARGS_COUNT_FOUR = 4;
const uint8_t CanvasComponent::ARGS_INDEX_0 = 0;
const uint8_t CanvasComponent::ARGS_INDEX_1 = 1;
const uint8_t CanvasComponent::ARGS_INDEX_2 = 2;
const uint8_t CanvasComponent::ARGS_INDEX_3 = 3;

// API-attribute
const char * const CanvasComponent::ATTR_FILLSTYLE = "fillStyle";
const char * const CanvasComponent::ATTR_STROKESTYLE = "strokeStyle";
const char * const CanvasComponent::ATTR_LINEWIDTH = "lineWidth";
const char * const CanvasComponent::ATTR_FONT = "font";
const char * const CanvasComponent::ATTR_TEXTALIGN = "textAlign";

// API-method
const char * const CanvasComponent::FUNC_GETCONTEXT = "getContext";
const char * const CanvasComponent::FUNC_FILLRECT = "fillRect";
const char * const CanvasComponent::FUNC_STROKERECT = "strokeRect";
const char * const CanvasComponent::FUNC_FILLTEXT = "fillText";

// create canvas draw attribute-callback mapping
const AttrMap CanvasComponent::attrMap_[] = {
    {ATTR_FILLSTYLE, FillStyleSetter, FillStyleGetter},
    {ATTR_STROKESTYLE, StrokeStyleSetter, StrokeStyleGetter},
    {ATTR_LINEWIDTH, LineWidthSetter, LineWidthGetter},
    {ATTR_FONT, FontSetter, FontGetter},
    {ATTR_TEXTALIGN, TextAlignSetter, TextAlignGetter}
};

// create canvas draw method-callback mapping
const MethodMap CanvasComponent::methodMap_[] = {
    {FUNC_GETCONTEXT, CanvasGetContext},
    {FUNC_FILLRECT, CanvasFillRect},
    {FUNC_STROKERECT, CanvasStrokeRect},
    {FUNC_FILLTEXT, CanvasFillText}
};

CanvasComponent::CanvasComponent(jerry_value_t options, jerry_value_t children, AppStyleManager *styleManager)
    : Component(options, children, styleManager),
      canvas_(nullptr),
      canvas2dContext_(UNDEFINED),
      fillStyleValue_(nullptr),
      strokeStyleValue_(nullptr),
      fontValue_(nullptr),
      textAlignValue_(nullptr),
      lineWidthValue_(1)
{
    SetComponentName(K_CANVAS);
    // set default paint pattern
    paint_.SetFillColor(Color::Black());
    paint_.SetOpacity(OPA_OPAQUE);
    paint_.SetStrokeColor(Color::Black());
    paint_.SetStrokeWidth(1);

    // set default text font pattern
    fontStyle_.align = TEXT_ALIGNMENT_LEFT;
    fontStyle_.direct = TEXT_DIRECT_LTR;
    fontStyle_.fontSize = DEFAULT_FONT_SIZE;
    char *defaultFontName = nullptr;
    CopyFontFamily(defaultFontName, DEFAULT_FONT_FAMILY);
    fontStyle_.fontName = defaultFontName;
    fontStyle_.letterSpace = DEFAULT_FONT_LETTERSPACE;

    RegisterNamedFunction(methodMap_[0].methodName, methodMap_[0].callbackName);
}
// Create FlexLayout
bool CanvasComponent::CreateNativeViews()
{
    canvas_ = new UICanvas();
    if (canvas_ == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "create native canvas view failed");
        return false;
    }
    return true;
}

void CanvasComponent::ReleaseNativeViews()
{
    ACE_DELETE(canvas_);
    ACE_FREE(fillStyleValue_);
    ACE_FREE(strokeStyleValue_);
    ACE_FREE(fontValue_);
    ACE_FREE(textAlignValue_);
    if (!IS_UNDEFINED(canvas2dContext_)) {
        bool deleted = jerry_delete_object_native_pointer(canvas2dContext_, nullptr);
        if (!deleted) {
            HILOG_WARN(HILOG_MODULE_ACE, "canvas_component: delete object native pointer canvas2dContext_ failed!");
        }
        jerry_release_value(canvas2dContext_);
    }
}

UIView *CanvasComponent::GetComponentRootView() const
{
    return canvas_;
}

jerry_value_t CanvasComponent::CanvasGetContext(const jerry_value_t func,
                                                const jerry_value_t context,
                                                const jerry_value_t args[],
                                                const jerry_length_t argsNum)
{
    (void)func;
    (void)args;
    if (argsNum != ARGS_COUNT_ONE) {
        HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: the number of getContext method parameter error!");
        return UNDEFINED;
    }

    CanvasComponent *component = static_cast<CanvasComponent *>(ComponentUtils::GetComponentFromBindingObject(context));
    if (component == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: get canvas component from js object failed!");
        return UNDEFINED;
    }

    if (IS_UNDEFINED(component->canvas2dContext_)) {
        component->canvas2dContext_ = jerry_create_object();
        jerry_set_object_native_pointer(component->canvas2dContext_, component, nullptr);

        // register fillStyle, strokeStyle, lineWidth, font, textAlign attribute
        uint16_t attrMapLength = sizeof(attrMap_) / sizeof(attrMap_[0]);
        for (uint16_t index = 0; index < attrMapLength; index++) {
            RegisterAttributeFunc(component->canvas2dContext_, attrMap_[index].attrName, attrMap_[index].setterName,
                                  attrMap_[index].getterName);
        }

        // register fillRect, strokeRect, fillText method
        uint16_t methodMapLength = sizeof(methodMap_) / sizeof(methodMap_[0]);
        for (uint16_t index = 1; index < methodMapLength; index++) {
            RegisterDrawMethodFunc(component->canvas2dContext_, methodMap_[index].methodName,
                                   methodMap_[index].callbackName);
        }
    }

    jerry_acquire_value(component->canvas2dContext_);
    return component->canvas2dContext_;
}

jerry_value_t CanvasComponent::FillStyleSetter(const jerry_value_t func,
                                               const jerry_value_t context,
                                               const jerry_value_t args[],
                                               const jerry_length_t argsNum)
{
    (void)func;
    if (argsNum != ARGS_COUNT_ONE) {
        HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: the value of fillStyle is null!");
        return UNDEFINED;
    }

    CanvasComponent *component = static_cast<CanvasComponent *>(ComponentUtils::GetComponentFromBindingObject(context));
    if (component == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: get canvas component from js object failed!");
        return UNDEFINED;
    }

    ACE_FREE(component->fillStyleValue_);

    component->fillStyleValue_ = MallocStringOf(args[ARGS_INDEX_0]);
    if (component->fillStyleValue_ == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: get fillStyle value failed");
        return UNDEFINED;
    }

    uint32_t color = 0;
    uint8_t alpha = OPA_OPAQUE;
    ParseColor(component->fillStyleValue_, color, alpha);
    component->paint_.SetFillColor(component->GetRGBColor(color));
    component->paint_.SetOpacity(alpha);
    return UNDEFINED;
}

jerry_value_t CanvasComponent::FillStyleGetter(const jerry_value_t func,
                                               const jerry_value_t dom,
                                               const jerry_value_t args[],
                                               const jerry_length_t argsNum)
{
    (void)func;
    (void)args;
    (void)argsNum;
    CanvasComponent *component = static_cast<CanvasComponent *>(ComponentUtils::GetComponentFromBindingObject(dom));
    if (component == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: get canvas component from js object failed!");
        return UNDEFINED;
    }

    if (component->fillStyleValue_ == nullptr) {
        CopyFontFamily(component->fillStyleValue_, DEFAULT_FILLSTYLE);
    }

    if (component->fillStyleValue_ != nullptr) {
        return jerry_create_string(reinterpret_cast<const jerry_char_t *>(component->fillStyleValue_));
    } else {
        return UNDEFINED;
    }
}

jerry_value_t CanvasComponent::StrokeStyleSetter(const jerry_value_t func,
                                                 const jerry_value_t context,
                                                 const jerry_value_t args[],
                                                 const jerry_length_t argsNum)
{
    (void)func;
    if (argsNum != ARGS_COUNT_ONE) {
        HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: the value of strokeStyle is null!");
        return UNDEFINED;
    }

    CanvasComponent *component = static_cast<CanvasComponent *>(ComponentUtils::GetComponentFromBindingObject(context));
    if (component == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: get canvas component from js object failed!");
        return UNDEFINED;
    }

    ACE_FREE(component->strokeStyleValue_);

    component->strokeStyleValue_ = MallocStringOf(args[ARGS_INDEX_0]);
    if (component->strokeStyleValue_ == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: get strokeStyle value failed");
        return UNDEFINED;
    }

    uint32_t color = 0;
    uint8_t alpha = OPA_OPAQUE;
    ParseColor(component->strokeStyleValue_, color, alpha);
    component->paint_.SetStrokeColor(component->GetRGBColor(color));
    component->paint_.SetOpacity(alpha);
    return UNDEFINED;
}

jerry_value_t CanvasComponent::StrokeStyleGetter(const jerry_value_t func,
                                                 const jerry_value_t dom,
                                                 const jerry_value_t args[],
                                                 const jerry_length_t argsNum)
{
    (void)func;
    (void)args;
    (void)argsNum;
    CanvasComponent *component = static_cast<CanvasComponent *>(ComponentUtils::GetComponentFromBindingObject(dom));
    if (component == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: get canvas component from js object failed!");
        return UNDEFINED;
    }

    if (component->strokeStyleValue_ == nullptr) {
        CopyFontFamily(component->strokeStyleValue_, DEFAULT_STROKESTYLE);
    }

    if (component->strokeStyleValue_ != nullptr) {
        return jerry_create_string(reinterpret_cast<const jerry_char_t *>(component->strokeStyleValue_));
    } else {
        return UNDEFINED;
    }
}

jerry_value_t CanvasComponent::LineWidthSetter(const jerry_value_t func,
                                               const jerry_value_t context,
                                               const jerry_value_t args[],
                                               const jerry_length_t argsNum)
{
    (void)func;
    if (argsNum != ARGS_COUNT_ONE) {
        HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: the value of lineWidth is null!");
        return UNDEFINED;
    }

    CanvasComponent *component = static_cast<CanvasComponent *>(ComponentUtils::GetComponentFromBindingObject(context));
    if (component == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: get canvas component from js object failed!");
        return UNDEFINED;
    }

    component->lineWidthValue_ = IntegerOf(args[ARGS_INDEX_0]);
    component->paint_.SetStrokeWidth(component->lineWidthValue_);
    return UNDEFINED;
}

jerry_value_t CanvasComponent::LineWidthGetter(const jerry_value_t func,
                                               const jerry_value_t dom,
                                               const jerry_value_t args[],
                                               const jerry_length_t argsNum)
{
    (void)func;
    (void)args;
    (void)argsNum;
    CanvasComponent *component = static_cast<CanvasComponent *>(ComponentUtils::GetComponentFromBindingObject(dom));
    if (component == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: get canvas component from js object failed!");
        return UNDEFINED;
    }
    return jerry_create_number(component->lineWidthValue_);
}

jerry_value_t CanvasComponent::FontSetter(const jerry_value_t func,
                                          const jerry_value_t context,
                                          const jerry_value_t args[],
                                          const jerry_length_t argsNum)
{
    (void)func;
    if (argsNum != ARGS_COUNT_ONE) {
        HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: the value of font is null!");
        return UNDEFINED;
    }

    CanvasComponent *component = static_cast<CanvasComponent *>(ComponentUtils::GetComponentFromBindingObject(context));
    if (component == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: get canvas component from js object failed!");
        return UNDEFINED;
    }

    ACE_FREE(component->fontValue_);

    component->fontValue_ = MallocStringOf(args[ARGS_INDEX_0]);
    if (component->fontValue_ == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: get text font value failed");
        return UNDEFINED;
    }

    const int8_t maxParamCount = 2;
    for (int8_t index = 0; index < maxParamCount; index++) {
        // get font size or font family from fontValue.
        char *mallocSubFont = nullptr;
        component->GetSubFont(component->fontValue_, index, mallocSubFont);
        if (mallocSubFont == nullptr) {
            HILOG_WARN(HILOG_MODULE_ACE, "canvas_component: get text font size or font family failed");
            ace_free(component->fontValue_);
            component->fontValue_ = nullptr;
            return UNDEFINED;
        }

        // if it is a font size
        if (*mallocSubFont >= '0' && *mallocSubFont <= '9') {
            component->fontStyle_.fontSize = strtol(mallocSubFont, nullptr, DEC);
            ace_free(mallocSubFont);
            mallocSubFont = nullptr;
        } else { // if it is a font family
            // free default component->fontStyle_.fontName memory.
            if (component->fontStyle_.fontName != nullptr) {
                ace_free(const_cast<char *>(component->fontStyle_.fontName));
                component->fontStyle_.fontName = nullptr;
            }
            // set customized font name, the memory of mallocFontFamily need be free in CanvasFillText method.
            component->fontStyle_.fontName = mallocSubFont;
        }
    }
    return UNDEFINED;
}

jerry_value_t CanvasComponent::FontGetter(const jerry_value_t func,
                                          const jerry_value_t dom,
                                          const jerry_value_t args[],
                                          const jerry_length_t argsNum)
{
    (void)func;
    (void)args;
    (void)argsNum;
    CanvasComponent *component = static_cast<CanvasComponent *>(ComponentUtils::GetComponentFromBindingObject(dom));
    if (component == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: get canvas component from js object failed!");
        return UNDEFINED;
    }

    if (component->fontValue_ == nullptr) {
        CopyFontFamily(component->fontValue_, DEFAULT_FONT);
    }

    if (component->fontValue_ != nullptr) {
        return jerry_create_string(reinterpret_cast<const jerry_char_t *>(component->fontValue_));
    } else {
        return UNDEFINED;
    }
}

jerry_value_t CanvasComponent::TextAlignSetter(const jerry_value_t func,
                                               const jerry_value_t context,
                                               const jerry_value_t args[],
                                               const jerry_length_t argsNum)
{
    (void)func;
    if (argsNum != ARGS_COUNT_ONE) {
        HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: the value of textAlign is null!");
        return UNDEFINED;
    }

    CanvasComponent *component = static_cast<CanvasComponent *>(ComponentUtils::GetComponentFromBindingObject(context));
    if (component == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: get canvas component from js object failed!");
        return UNDEFINED;
    }

    ACE_FREE(component->textAlignValue_);

    uint16_t textAlignLength = 0;
    component->textAlignValue_ = MallocStringOf(args[ARGS_INDEX_0], &textAlignLength);
    if (component->textAlignValue_ == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: get text align value failed");
        return UNDEFINED;
    }

    uint16_t textAlignId = KeyParser::ParseKeyId(component->textAlignValue_, textAlignLength);
    if (textAlignId == K_LEFT) {
        component->fontStyle_.align = TEXT_ALIGNMENT_LEFT;
    } else if (textAlignId == K_RIGHT) {
        component->fontStyle_.align = TEXT_ALIGNMENT_RIGHT;
    } else if (textAlignId == K_CENTER) {
        component->fontStyle_.align = TEXT_ALIGNMENT_CENTER;
    } else {
        // do nothing(use defualt align=TEXT_ALIGNMENT_LEFT)
    }
    return UNDEFINED;
}

jerry_value_t CanvasComponent::TextAlignGetter(const jerry_value_t func,
                                               const jerry_value_t dom,
                                               const jerry_value_t args[],
                                               const jerry_length_t argsNum)
{
    (void)func;
    (void)args;
    (void)argsNum;
    CanvasComponent *component = static_cast<CanvasComponent *>(ComponentUtils::GetComponentFromBindingObject(dom));
    if (component == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: get canvas component from js object failed!");
        return UNDEFINED;
    }

    if (component->textAlignValue_ == nullptr) {
        CopyFontFamily(component->textAlignValue_, DEFAULT_TEXTALIGN);
    }

    if (component->textAlignValue_ != nullptr) {
        return jerry_create_string(reinterpret_cast<const jerry_char_t *>(component->textAlignValue_));
    } else {
        return UNDEFINED;
    }
}

jerry_value_t CanvasComponent::CanvasFillRect(const jerry_value_t func,
                                              const jerry_value_t context,
                                              const jerry_value_t args[],
                                              const jerry_length_t argsNum)
{
    (void)func;
    if (argsNum != ARGS_COUNT_FOUR) {
        HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: the number of fillRect method parameter error!");
        return UNDEFINED;
    }

    CanvasComponent *component = static_cast<CanvasComponent *>(ComponentUtils::GetComponentFromBindingObject(context));
    if (component == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: get canvas component from js object failed!");
        return UNDEFINED;
    }

    int16_t startX = IntegerOf(args[ARGS_INDEX_0]);
    int16_t startY = IntegerOf(args[ARGS_INDEX_1]);
    int16_t endX = IntegerOf(args[ARGS_INDEX_2]);
    int16_t endY = IntegerOf(args[ARGS_INDEX_3]);

    // FILL_STYLE: fill rect support fill shapses only
    component->paint_.SetStyle(component->paint_.FILL_STYLE);

    Point startPoint;
    startPoint.x = startX;
    startPoint.y = startY;
    component->canvas_->DrawRect(startPoint, endX, endY, component->paint_);
    return UNDEFINED;
}

jerry_value_t CanvasComponent::CanvasStrokeRect(const jerry_value_t func,
                                                const jerry_value_t context,
                                                const jerry_value_t args[],
                                                const jerry_length_t argsNum)
{
    (void)func;
    if (argsNum != ARGS_COUNT_FOUR) {
        HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: the number of strokeRect method parameter error!");
        return UNDEFINED;
    }

    CanvasComponent *component = static_cast<CanvasComponent *>(ComponentUtils::GetComponentFromBindingObject(context));
    if (component == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: get canvas component from js object failed!");
        return UNDEFINED;
    }

    int16_t startX = IntegerOf(args[ARGS_INDEX_0]);
    int16_t startY = IntegerOf(args[ARGS_INDEX_1]);
    int16_t endX = IntegerOf(args[ARGS_INDEX_2]);
    int16_t endY = IntegerOf(args[ARGS_INDEX_3]);

    // STROKE_STYLE: stroke rect support draw borders only
    component->paint_.SetStyle(component->paint_.STROKE_STYLE);

    Point startPoint;
    startPoint.x = startX;
    startPoint.y = startY;
    component->canvas_->DrawRect(startPoint, endX, endY, component->paint_);
    return UNDEFINED;
}

jerry_value_t CanvasComponent::CanvasFillText(const jerry_value_t func,
                                              const jerry_value_t context,
                                              const jerry_value_t args[],
                                              const jerry_length_t argsNum)
{
    (void)func;
    if (argsNum != ARGS_COUNT_THREE) {
        HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: the number of fillText method parameter error!");
        return UNDEFINED;
    }

    CanvasComponent *component = static_cast<CanvasComponent *>(ComponentUtils::GetComponentFromBindingObject(context));
    if (component == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: get canvas component from js object failed!");
        return UNDEFINED;
    }

    char *textValue = MallocStringOf(args[ARGS_INDEX_0]);
    if (textValue == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: get text value failed");
        return UNDEFINED;
    }

    int16_t startX = IntegerOf(args[ARGS_INDEX_1]);
    int16_t startY = IntegerOf(args[ARGS_INDEX_2]);
    int16_t maxWidth = component->canvas_->GetWidth();

    // FILL_STYLE: fillText support fill shapses only
    component->paint_.SetStyle(component->paint_.FILL_STYLE);

    Point startPoint;
    const int8_t half = 2;
    startPoint.x = startX;
    startPoint.y = startY;

    // if textAlign=left, not need transfer startX, if textAlign=right or center, need transfer startX
    if (component->fontStyle_.align == TEXT_ALIGNMENT_RIGHT) {
        startPoint.x = startX - maxWidth;
    } else if (component->fontStyle_.align == TEXT_ALIGNMENT_CENTER) {
        startPoint.x = (startX + startX - maxWidth) / half;
    } else {
        startPoint.x = startX;
    }

    component->canvas_->DrawLabel(startPoint, textValue, maxWidth, component->fontStyle_, component->paint_);

    // free component->fontStyle_.fontName memory which malloc in FontSetter method.
    if (component->fontStyle_.fontName != nullptr) {
        ace_free(const_cast<char *>(component->fontStyle_.fontName));
        component->fontStyle_.fontName = nullptr;
    }

    ACE_FREE(textValue);
    return UNDEFINED;
}

void CanvasComponent::GetSubFont(const char *font, const uint8_t index, char *&subFont) const
{
    if (font == nullptr || *font == '\0') {
        HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: get font attribute failed");
        return;
    }

    if (strlen(font) >= UINT16_MAX) {
        HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: font size overflow.");
        return;
    }

    // skip space character at the head of string.
    while (*font != '\0') {
        if (*font == ' ') {
            font++;
        } else {
            break;
        }
    }

    uint8_t currentIndex = 0;
    const char *currentPos = font;
    const char *endPos = font;
    while (*currentPos != '\0') {
        // find the sub font string
        if (currentIndex == index) {
            if (*endPos != ' ' && *endPos != '\0') {
                endPos++;
                continue;
            }
            uint16_t len = endPos - currentPos;
            uint16_t startIndex = currentPos - font;
            subFont = static_cast<char *>(ace_malloc(len + 1));
            if (subFont == nullptr) {
                HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: malloc buffer failed for subFont");
                return;
            }
            errno_t error = strncpy_s(subFont, len + 1, font + startIndex, len);
            if (error != 0) {
                HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: copy string failed");
                ace_free(subFont);
                subFont = nullptr;
                return;
            }
            subFont[len] = '\0';
            break;
        } else { // go forward to next sub font string.
            if (*(currentPos) == ' ' && *(currentPos + 1) != ' ') {
                currentIndex = currentIndex + 1;
                endPos = currentPos + 1;
            }
            currentPos++;
        }
    }
}

void CanvasComponent::RegisterAttributeFunc(jerry_value_t canvas2dContext,
                                            const char *attributeName,
                                            jerry_external_handler_t setterHandler,
                                            jerry_external_handler_t getterHandler)
{
    // register canvas js attribute setter property via the jerry_define_own_property method
    jerry_value_t propName = jerry_create_string(reinterpret_cast<const jerry_char_t *>(attributeName));
    jerry_property_descriptor_t desc;
    jerry_init_property_descriptor_fields(&desc);
    desc.is_set_defined = true;
    desc.setter = jerry_create_external_function(setterHandler);
    desc.is_get_defined = true;
    desc.getter = jerry_create_external_function(getterHandler);
    jerry_value_t returnValue = jerry_define_own_property(canvas2dContext, propName, &desc);
    jerry_free_property_descriptor_fields(&desc);
    ReleaseJerryValue(propName, returnValue, VA_ARG_END_FLAG);
}

void CanvasComponent::RegisterDrawMethodFunc(jerry_value_t canvas2dContext,
                                             const char *drawMethodName,
                                             jerry_external_handler_t handler)
{
    JerrySetFuncProperty(canvas2dContext, drawMethodName, handler);
}
} // namespace ACELite
} // namespace OHOS
#endif // FEATURE_COMPONENT_CANVAS
