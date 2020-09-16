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

#ifndef OHOS_ACELITE_CANVAS_COMPONENT_H
#define OHOS_ACELITE_CANVAS_COMPONENT_H

#include "acelite_config.h"

#ifdef FEATURE_COMPONENT_CANVAS
#include "component.h"
#include "non_copyable.h"
#include "ui_canvas.h"

namespace OHOS {
namespace ACELite {
struct AttrMap {
    ACE_DISALLOW_COPY_AND_MOVE(AttrMap);
    const char *attrName;
    jerry_external_handler_t setterName;
    jerry_external_handler_t getterName;
};
struct MethodMap {
    ACE_DISALLOW_COPY_AND_MOVE(MethodMap);
    const char *methodName;
    jerry_external_handler_t callbackName;
};

class CanvasComponent final : public Component {
public:
    ACE_DISALLOW_COPY_AND_MOVE(CanvasComponent);
    CanvasComponent() = delete;
    CanvasComponent(jerry_value_t options, jerry_value_t children, AppStyleManager *styleManager);
    ~CanvasComponent() override {}

protected:
    bool CreateNativeViews() override;
    void ReleaseNativeViews() override;
    UIView *GetComponentRootView() const override;

private:
    void GetSubFont(const char *font, const uint8_t index, char *&subFont) const;

    static void RegisterAttributeFunc(jerry_value_t canvas2dContext,
                                      const char *attributeName,
                                      jerry_external_handler_t setterHandler,
                                      jerry_external_handler_t getterHandler);

    static void RegisterDrawMethodFunc(jerry_value_t canvas2dContext,
                                       const char *drawMethodName,
                                       jerry_external_handler_t handler);

    static jerry_value_t CanvasGetContext(const jerry_value_t func,
                                          const jerry_value_t dom,
                                          const jerry_value_t args[],
                                          const jerry_length_t argsNum);

    static jerry_value_t FillStyleSetter(const jerry_value_t func,
                                         const jerry_value_t dom,
                                         const jerry_value_t args[],
                                         const jerry_length_t argsNum);

    static jerry_value_t FillStyleGetter(const jerry_value_t func,
                                         const jerry_value_t dom,
                                         const jerry_value_t args[],
                                         const jerry_length_t argsNum);

    static jerry_value_t StrokeStyleSetter(const jerry_value_t func,
                                           const jerry_value_t dom,
                                           const jerry_value_t args[],
                                           const jerry_length_t argsNum);

    static jerry_value_t StrokeStyleGetter(const jerry_value_t func,
                                           const jerry_value_t dom,
                                           const jerry_value_t args[],
                                           const jerry_length_t argsNum);

    static jerry_value_t LineWidthSetter(const jerry_value_t func,
                                         const jerry_value_t dom,
                                         const jerry_value_t args[],
                                         const jerry_length_t argsNum);

    static jerry_value_t LineWidthGetter(const jerry_value_t func,
                                         const jerry_value_t dom,
                                         const jerry_value_t args[],
                                         const jerry_length_t argsNum);

    static jerry_value_t FontSetter(const jerry_value_t func,
                                    const jerry_value_t dom,
                                    const jerry_value_t args[],
                                    const jerry_length_t argsNum);

    static jerry_value_t FontGetter(const jerry_value_t func,
                                    const jerry_value_t dom,
                                    const jerry_value_t args[],
                                    const jerry_length_t argsNum);

    static jerry_value_t TextAlignSetter(const jerry_value_t func,
                                         const jerry_value_t dom,
                                         const jerry_value_t args[],
                                         const jerry_length_t argsNum);

    static jerry_value_t TextAlignGetter(const jerry_value_t func,
                                         const jerry_value_t dom,
                                         const jerry_value_t args[],
                                         const jerry_length_t argsNum);

    static jerry_value_t CanvasFillRect(const jerry_value_t func,
                                        const jerry_value_t dom,
                                        const jerry_value_t args[],
                                        const jerry_length_t argsNum);

    static jerry_value_t CanvasStrokeRect(const jerry_value_t func,
                                          const jerry_value_t dom,
                                          const jerry_value_t args[],
                                          const jerry_length_t argsNum);

    static jerry_value_t CanvasFillText(const jerry_value_t func,
                                        const jerry_value_t context,
                                        const jerry_value_t args[],
                                        const jerry_length_t argsNum);

    UICanvas *canvas_;
    jerry_value_t canvas2dContext_;
    Paint paint_;
    UICanvas::FontStyle fontStyle_;
    char *fillStyleValue_;
    char *strokeStyleValue_;
    char *fontValue_;
    char *textAlignValue_;
    int16_t lineWidthValue_;
    static const char * const DEFAULT_FILLSTYLE;
    static const char * const DEFAULT_STROKESTYLE;
    static const char * const DEFAULT_FONT;
    static const char * const DEFAULT_TEXTALIGN;
    static const AttrMap attrMap_[];
    static const MethodMap methodMap_[];
    static const uint8_t ARGS_COUNT_ONE;
    static const uint8_t ARGS_COUNT_THREE;
    static const uint8_t ARGS_COUNT_FOUR;
    static const uint8_t ARGS_INDEX_0;
    static const uint8_t ARGS_INDEX_1;
    static const uint8_t ARGS_INDEX_2;
    static const uint8_t ARGS_INDEX_3;
    static const char * const ATTR_FILLSTYLE;
    static const char * const ATTR_STROKESTYLE;
    static const char * const ATTR_LINEWIDTH;
    static const char * const ATTR_FONT;
    static const char * const ATTR_TEXTALIGN;
    static const char * const FUNC_GETCONTEXT;
    static const char * const FUNC_FILLRECT;
    static const char * const FUNC_STROKERECT;
    static const char * const FUNC_FILLTEXT;
};
} // namespace ACELite
} // namespace OHOS
#endif // FEATURE_COMPONENT_CANVAS
#endif // OHOS_ACELITE_CANVAS_COMPONENT_H
