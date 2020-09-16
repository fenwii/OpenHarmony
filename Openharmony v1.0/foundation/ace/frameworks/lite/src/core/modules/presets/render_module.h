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
#ifndef OHOS_ACELITE_RENDER_MODULE_H
#define OHOS_ACELITE_RENDER_MODULE_H

#include "non_copyable.h"
#include "presets/preset_module.h"

namespace OHOS {
namespace ACELite {
class RenderModule final : public PresetModule {
public:
    ACE_DISALLOW_COPY_AND_MOVE(RenderModule);
    /**
     * @fn RenderModule::RenderModule()
     *
     * @brief Constructor.
     */
    RenderModule() : PresetModule(nullptr) {}

    /**
     * @fn RenderModule::~RenderModule()
     *
     * @brief Constructor.
     */
    ~RenderModule() = default;

    void Init() override;

    static void Load()
    {
        RenderModule renderModule;
        renderModule.Init();
    }

private:
    static jerry_value_t
        CreateElement(const jerry_value_t tagName, const jerry_value_t options, const jerry_value_t children);

    static jerry_value_t CreateElement(const jerry_value_t func,
                                       const jerry_value_t context,
                                       const jerry_value_t *args,
                                       const jerry_length_t argsNum);

    static jerry_value_t InitStyleSheet(const jerry_value_t func,
                                        const jerry_value_t context,
                                        const jerry_value_t *args,
                                        const jerry_length_t argsNum);

    static jerry_value_t LoopRender(const jerry_value_t func,
                                    const jerry_value_t context,
                                    const jerry_value_t *args,
                                    const jerry_length_t argsNum);

    static jerry_value_t ConditionalRender(const jerry_value_t func,
                                           const jerry_value_t context,
                                           const jerry_value_t *args,
                                           const jerry_length_t argsNum);

    static const char * const FUNC_CREATE_ELEMENT;
    static const char * const FUNC_INIT_STYLE_SHEET;
    static const char * const FUNC_LOOP_RENDER;
    static const char * const FUNC_CONDITIONAL_RENDER;
    static const int ARG_LENGTH_TAG_ONLY;
    static const int ARG_LENGTH_WITH_OPTIONS;
    static const int ARG_LENGTH_WITHOUT_OPTIONS;
    static const int ARG_LENGTH_RENDER;
};
} // namespace ACELite
} // namespace OHOS
#endif // OHOS_ACELITE_RENDER_MODULE_H
