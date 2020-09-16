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

#ifndef OHOS_ACELITE_MODULE_MANAGER_H
#define OHOS_ACELITE_MODULE_MANAGER_H

#include "jsi.h"
#include "non_copyable.h"

namespace OHOS {
namespace ACELite {
/**
 * @brief module manager for module load.
 */
class ModuleManager final : public MemoryHeap {
public:
    ACE_DISALLOW_COPY_AND_MOVE(ModuleManager);
    /**
     * @brief Get the single instance of ModuleManager
     *
     * @returns the instance.
     */
    static ModuleManager* GetInstance()
    {
        static ModuleManager instance;
        return &instance;
    }

    /**
     * @brief: require javascript module object with given module name.
     *
     * @param: moduleName name of the module required
     * @returns: javascript module object
     */
    JSIValue RequireModule(const char * const moduleName);

    /**
     * @brief: Release module object created by RequireModule.
     *         This Method should be called when current js page is
     *         going to destroy
     */
    void CleanUpModule();

    /**
     * @brief: Call OnTerminate callbacks of required modules.
     *         This Method should be called when current application is
     *         going to terminate
     */
    void OnTerminate();

private:
    struct CallbackNode : public MemoryHeap {
        ACE_DISALLOW_COPY_AND_MOVE(CallbackNode);
        CallbackNode() : callback(nullptr), callbackHandler(nullptr), next(nullptr) {}
        NativeCallback callback;
        JsiCallback callbackHandler;
        struct CallbackNode *next;
    };

    ModuleManager() : onDestroyHead_(nullptr), onTerminateHead_(nullptr) {}
    virtual ~ModuleManager() {}

    /**
     * @brief: get category and name with given moduleName.
     *
     * @param [in] moduleName module name passed from JS, e.g. system.vibrator
     * @param [out] category pointer to category which this module belongs to
     *              Content should be freed with free() when it is not used anymore
     * @param [out] name pointer to module name parsed from moduleName, e.g. vibrator
     *              Content should be freed with free() when it is not used anymore
     * @return whether operation succeed
     */
    bool ParseModuleName(const char * const moduleName, char** category, char** name) const;

    /**
     * @brief: get module object with given module name.
     *
     * @param [in] moduleName module name
     * @param [in] modules array of module infos
     * @param [in] modulesCount length of modules
     * @param [inout] categoryObj pointer to static object, e.g. requiredSystemModules
     * @param [in] bundleName bundle name of specific private module
     * @return javascript required module object
     */
    JSIValue GetModuleObject(const char * const moduleName, const Module* modules, uint16_t modulesCount,
        JSIValue& categoryObj, const char * const bundleName = nullptr);

    JSIValue InitModuleObject(const char * const name, Module module, JSIValue& categoryObj);

    // *resPtr should be freed by caller when it's not nullptr and won't be used any more
    bool CreateString(const char * const srcStr, char** resPtr) const;

    void InsertCallback(CallbackNode *&head, NativeCallback callback, JsiCallback callbackHandler) const;
    void InsertTerminateCallback(const char * const name, const JSIValue& moduleObj);
    void InvokeCallbacks(CallbackNode *&head) const;
    void* GetObjectPointer(JSIValue object) const;
    void* GetObjectNamedPointer(JSIValue object, const char * const name) const;
    void DeleteObjectProperty(JSIValue object, const char * const name) const;
    NativeCallback GetNativeCallback(JSIValue object, const char * const name) const;
    JsiCallback GetJsiCallback(JSIValue object, const char * const name) const;

    // For different native module type
    const char* CATEGORY_SYSTEM = "system";

    // JS object for caching modules
    static JSIValue requiredSystemModules;

    // JS object for required history modules before ability terminating
    static JSIValue requiredHistoryModules;

    CallbackNode *onDestroyHead_;
    CallbackNode *onTerminateHead_;
};
} // namespace ACELite
} // namespace OHOS

#endif // OHOS_ACELITE_MODULE_MANAGER_H
