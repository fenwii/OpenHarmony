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

#ifndef OHOS_ACELITE_JS_ABILITY_H
#define OHOS_ACELITE_JS_ABILITY_H

#include <cstdint>
#include <cstdlib>
#include <cstring>
#include "memory_heap.h"

namespace OHOS {
namespace ACELite {
/**
 * As all the UI event handling is driven by the render tick, and to make sure the the event handling is
 * in JS task, the HAL layer will transfer the TE event into the loop of JS task, when JS application go forground.
 */
typedef int32_t (*RenderTickHandler)();

class JSAbility final : public MemoryHeap {
public:
    JSAbility(const JSAbility &) = delete;
    JSAbility &operator=(const JSAbility &) = delete;
    JSAbility(JSAbility &&) = delete;
    JSAbility &operator=(JSAbility &&) = delete;

    /**
     * @fn JSAbility::JSAbility()
     *
     * @brief Default constructor.
     */
    JSAbility() : jsAbilityImpl_(nullptr) {}

    /**
     * @fn virtual JSAbility::~JSAbility()
     *
     * @brief Destructor.
     */
    virtual ~JSAbility() {}

    /**
     * @fn JSAbility::Launch()
     *
     * @brief Call this function to create the JS runtime environment, and it will init
     *        the JS framework and eval abilityPath/src/index.js as well
     * @param [in] the ability path to bundle name and token of this ability
     */
    void Launch(const char *abilityPath, const char *bundleName, uint16_t token);

    /**
     * @fn JSAbility::Show()
     *
     * @brief Call this function to active the application UI
     */
    void Show() const;

    /**
     * @fn JSAbility::Hide()
     *
     * @brief Call this function to move the current JS application to background
     */
    void Hide() const;

    /**
     * @fn JSAbility::TransferToDestroy()
     *
     * @brief Tear down JS runtime, release JS engine, and invoke user's onDestroy callback
     */
    void TransferToDestroy();

    /**
     * @fn JSAbility::BackPressed()
     *
     * @brief Called by AbilityHost to notify back key has been pressed, JS ability will tear down
     */
    void BackPressed();

    /**
     * @fn JSAbility::GetPackageName()
     *
     * @brief Return current package name
     */
    static const char *GetPackageName();

    /**
     * @fn JSAbility::ForceDestroy()
     *
     * @brief Force to clean up the whole application
     */
    void ForceDestroy();

    /**
     * @fn JSAbility::RegisterTEHandler()
     *
     * @brief Register render tick event handler
     */
    static void RegisterTEHandler(RenderTickHandler handler);

    /**
     * @fn JSAbility::HandleRenderTick()
     *
     * @brief Call the render tick if it's set
     */
    void HandleRenderTick();

private:
    // the holder of JS runtime and user' JS related environment
    void *jsAbilityImpl_;
}; // class JSAbility
} // namespace ACELite
} // namespace OHOS
#endif // OHOS_ACELITE_JS_ABILITY_H