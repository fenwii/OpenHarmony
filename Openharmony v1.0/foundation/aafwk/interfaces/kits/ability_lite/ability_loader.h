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
 * @file ability_loader.h
 *
 * @brief Declares functions for registering the class names of {@link Ability} and {@link AbilitySlice} with the
 *        ability management framework.
 *
 * After creating your own {@link Ability} and {@link AbilitySlice} child classes, you should register their class
 * names with the ability management framework so that the application can start <b>Ability</b> instances created in
 * the background.
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef OHOS_ABILITY_LOADER_H
#define OHOS_ABILITY_LOADER_H

#include <functional>
#include <string>
#include <unordered_map>

#include "ability.h"
#ifdef ABILITY_WINDOW_SUPPORT
#include "ability_slice.h"
#endif

namespace OHOS {
using CreateAblity = std::function<Ability *(void)>;
#ifdef ABILITY_WINDOW_SUPPORT
using CreateSlice = std::function<AbilitySlice *(void)>;
#endif

/**
 * @brief Declares functions for registering the class names of {@link Ability} and {@link AbilitySlice} with the
 *        ability management framework.
 *
 * After creating your own {@link Ability} and {@link AbilitySlice} child classes, you should register their class
 * names with the ability management framework so that the application can start <b>Ability</b> instances created in
 * the background.
 *
 * @since 1.0
 * @version 1.0
 */
class AbilityLoader {
public:
    static AbilityLoader &GetInstance()
    {
        static AbilityLoader abilityLoader;
        return abilityLoader;
    }

    ~AbilityLoader() = default;

    void RegisterAbility(const std::string &abilityName, const CreateAblity &createFunc);
    Ability *GetAbilityByName(const std::string &abilityName);

#ifdef ABILITY_WINDOW_SUPPORT
    void RegisterAbilitySlice(const std::string &sliceName, const CreateSlice &createFunc);
    AbilitySlice *GetAbilitySliceByName(const std::string &sliceName);
#endif

private:
    AbilityLoader() = default;
    AbilityLoader(const AbilityLoader&) = delete;
    AbilityLoader &operator=(const AbilityLoader &) = delete;
    AbilityLoader(AbilityLoader &&) = delete;
    AbilityLoader &operator=(AbilityLoader &&) = delete;

    std::unordered_map<std::string, CreateAblity> abilities_;
#ifdef ABILITY_WINDOW_SUPPORT
    std::unordered_map<std::string, CreateSlice> slices_;
#endif
};

/**
 * @brief Registers the class name of an {@link Ability} child class.
 *
 * After implementing your own {@link Ability} class, you should call this function so that the ability management
 * framework can create <b>Ability</b> instances when loading your <b>Ability</b> class.
 *
 * @param className Indicates the {@link Ability} class name to register.
 */
#define REGISTER_AA(className)                                                                \
    __attribute__((constructor)) void RegisterAA##className() {                               \
        AbilityLoader::GetInstance().RegisterAbility(#className, []()->Ability* {             \
            return new className;                                                             \
        });                                                                                   \
    }

/**
 * @brief Registers the class name of an {@link AbilitySlice} child class.
 *
 * After implementing your own {@link AbilitySlice} class, you should call this function so that the ability
 * management framework can create <b>AbilitySlice</b> instances when loading your <b>AbilitySlice</b> class.
 *
 * @param className Indicates the {@link AbilitySlice} class name to register.
 */
#ifdef ABILITY_WINDOW_SUPPORT
#define REGISTER_AS(className)                                                                \
    __attribute__((constructor)) void RegisterAS##className() {                               \
        AbilityLoader::GetInstance().RegisterAbilitySlice(#className, []()->AbilitySlice* {   \
            return new className;                                                             \
        });                                                                                   \
    }
#endif
} // namespace OHOS
#endif // OHOS_ABILITY_LOADER_H