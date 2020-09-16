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

#ifndef OHOS_ACELITE_JS_APP_CONTEXT_H
#define OHOS_ACELITE_JS_APP_CONTEXT_H

#include "stylemgr/app_style_manager.h"

namespace OHOS {
namespace ACELite {
class JSAbilityImpl;
/**
 * @brief Global App context.
 */
class JsAppContext final : public MemoryHeap {
public:
    static JsAppContext* GetInstance()
    {
        static JsAppContext instance;
        return &instance;
    }

    /**
     * @brief trigger terminate request
     */
    void TerminateAbility() const;
    /**
     * @brief eval user's JS Code and return FeatureAbility object
     *
     * @param: jsFileFullPath js file full path
     * @param: fileNameLength the given file name length
     * @param: the flag for app eval or page eval.True is eval flag.
     */
    jerry_value_t Eval(const char * const jsFileFullPath, size_t fileNameLength, bool isAppEval) const;
    /**
     * @brief call FeatureAbility's render function
     *
     * @param: page instance, viewModel to call render on
     */
    jerry_value_t Render(jerry_value_t viewModel) const;
    /**
     * @brief call FeatureAbility's show function
     *
     * @param: page instance, nativeElement to call show on
     */
    void Show() const;
    void RemoveAllView() const;
    /**
     * @brief set the ability path, bundle name and token info for current ability
     *
     * @param: ability's path, bundle name and token info
     */
    void SetCurrentAbilityInfo(const char * const abilityPath, const char * const bundleName, uint16_t token);
    /**
     * @brief return ability path
     */
    const char* GetCurrentAbilityPath() const
    {
        return currentAbilityPath_;
    }
    /**
     * @brief set the js path and uuid info for current ability
     *
     * @param: js's path
     */
    void SetCurrentJsPath(const char * const jsPath);
    /**
     * @brief return js path
     */
    const char* GetCurrentJsPath() const
    {
        return currentJsPath_;
    }
    /**
     * @brief return current bundle name
     */
    const char* GetCurrentBundleName() const
    {
        return currentBundleName_;
    }

    const JSAbilityImpl* GetTopJSAbilityImpl() const
    {
        return topJSAbilityImpl_;
    }
    /**
     * @brief return current ability implementation
     */
    void SetTopJSAbilityImpl(JSAbilityImpl* object)
    {
        topJSAbilityImpl_ = object;
    }

    const AppStyleManager* GetStyleManager()
    {
        if (styleManage_ == nullptr) {
            styleManage_ = new AppStyleManager();
        }
        return styleManage_;
    }

    void ReleaseStyles()
    {
        if (styleManage_) {
            delete styleManage_;
            styleManage_ = nullptr;
        }
    }

    /*
     * @brief: clear app env.
     */
    void ClearContext();

private:
    /**
     * @brief: release the ability info saved
     */
    void ReleaseAbilityInfo();

    void SetGlobalNamedProperty(bool isAppEval, jerry_value_t viewModel) const;
    char* currentBundleName_ = nullptr;
    char* currentAbilityPath_ = nullptr;
    char* currentJsPath_ = nullptr;
    JSAbilityImpl* topJSAbilityImpl_ = nullptr;
    AppStyleManager* styleManage_ = nullptr;
    // record current runing ability's uuid && ability path, will be release during app-cleanup
    uint16_t currentToken_ = 0;
};
} // namespace ACELite
} // namespace OHOS

#endif // OHOS_ACELITE_JS_APP_CONTEXT_H
