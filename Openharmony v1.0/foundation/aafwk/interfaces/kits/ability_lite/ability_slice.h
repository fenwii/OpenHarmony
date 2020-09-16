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
 * @addtogroup AbilityKit
 * @{
 *
 * @brief Provides ability-related functions, including ability lifecycle callbacks and functions for connecting to or
 *        disconnecting from Particle Abilities.
 *
 * Abilities are classified into Feature Abilities and Particle Abilities. Feature Abilities support the Page template,
 * and Particle Abilities support the Service template. An ability using the Page template is called a Page ability for
 * short and that using the Service template is called a Service ability.
 *
 * @since 1.0
 * @version 1.0
 */

/**
 * @file ability_slice.h
 *
 * @brief Declares ability slice-related functions, including ability slice lifecycle callbacks and functions for
 *        connecting to or disconnecting from ability slices.
 *
 * <b>AbilitySlice</b> instances, which are specific to Feature Abilities (abilities using the Page template),
 * are used to present different screens on an application's user interface.
 * A Feature Ability can have multiple ability slices.
 *
 * @since 1.0
 * @version 1.0
 */
#ifndef OHOS_ABILITY_SLICE_H
#define OHOS_ABILITY_SLICE_H

#include "ability.h"

namespace OHOS {
class AbilitySliceManager;

/**
 * @brief Provides ability slice-related functions, including ability slice lifecycle callbacks and functions for
 *        connecting to or disconnecting from ability slices.
 *
 * <b>AbilitySlice</b> instances, which are specific to Feature Abilities (abilities using the Page template),
 * are used to present different screens on an application's user interface.
 * A Feature Ability can have multiple ability slices.
 *
 * @since 1.0
 * @version 1.0
 */
class AbilitySlice : public AbilityContext {
public:
    AbilitySlice() = default;
    virtual ~AbilitySlice() = default;

    /**
     * @brief Called when this ability slice is started. You must override this function if you want to perform some
     *        initialization operations during ability slice startup.
     *
     * This function can be called only once in the entire lifecycle of an ability slice.
     * You can override this function to implement your own processing logic.
     * @param want Indicates the {@link Want} structure containing startup information about the ability slice.
     */
    virtual void OnStart(const Want &want);

    /**
     * @brief Called when this ability slice enters the <b>STATE_INACTIVE</b> state.
     *
     * <b>STATE_INACTIVE</b> is an instantaneous state. The ability slice in this state may be visible but does not
     * have focus. You can override this function to implement your own processing logic.
     */
    virtual void OnInactive();

    /**
     * @brief Called when this ability slice enters the <b>STATE_ACTIVE</b> state.
     *
     * The ability slice in the <b>STATE_ACTIVE</b> state is visible and has focus.
     * You can override this function to implement your own processing logic.
     *
     * @param want Indicates the {@link Want} structure containing activation information about the ability slice.
     */
    virtual void OnActive(const Want &want);

    /**
    * @brief Called when this ability slice enters the <b>STATE_BACKGROUND</b> state.
    *
    * The ability slice in the <b>STATE_BACKGROUND</b> state is invisible.
    * You can override this function to implement your own processing logic.
    */
    virtual void OnBackground();

    /**
    * @brief Called when this ability slice enters the <b>STATE_STOP</b> state.
    *
    * The ability slice in the <b>STATE_STOP</b> state is being destroyed.
    * You can override this function to implement your own processing logic.
    */
    virtual void OnStop();

    /**
     * @brief Presents another ability slice, which can be an ability slice that is not started or an existing ability
     *        slice in the host ability.
     *
     * @attention This function can be called only when both of the following conditions are met:
     * <ul><li>The host ability is in the <b>STATE_ACTIVE</b> state.</li>
     * <li>The target ability slice is not started or destroyed.</li></ul>
     *
     * @param abilitySlice Indicates the target ability slice. This parameter cannot be null.
     * @param want Indicates the {@link Want} structure containing startup information about the target ability slice.
     */
    void Present(AbilitySlice &abilitySlice, const Want &want);

    /**
     * @brief Destroys this ability slice.
     *
     * This ability slice can call this function to destroy itself. If the ability slice to destroy is the only
     * running one in the host ability, the host ability will also be destroyed. Otherwise, the host ability will
     * not be affected.
     */
    void Terminate();

    /**
     * @brief Sets the UI layout for the host ability of this ability slice.
     *
     * You can call {@link GetWindowRootView()} to create a layout and add controls.
     *
     * @param rootView Indicates the pointer to the custom layout view you have created.
     */
    void SetUIContent(RootView *rootView);
private:
    void Init(AbilitySliceManager &abilitySliceManager);
    int GetState() const;

    AbilitySliceManager *abilitySliceManager_ { nullptr };
    RootView *curRootView_ { nullptr };
    int sliceState_ { 0 };

    friend class AbilitySliceScheduler;
};
} // namespace OHOS
#endif // OHOS_ABILITY_SLICE_H