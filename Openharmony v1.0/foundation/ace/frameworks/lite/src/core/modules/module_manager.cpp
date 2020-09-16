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
#include "module_manager.h"
#include <stdlib.h>
#include <string.h>
#include "acelite_config.h"
#ifdef OHOS_ACELITE_PRODUCT_WATCH
#include "securec.h"
#endif // OHOS_ACELITE_PRODUCT_WATCH
#include "ace_log.h"
#include "fatal_handler.h"
#include "internal/jsi_internal.h"
#include "js_app_context.h"
#include "js_fwk_common.h"
#include "ohos_module_config.h"

namespace OHOS {
namespace ACELite {
// external methods for JS modules
#ifdef FEATURE_PRODUCT_MODULE
extern const Module* GetProductModules(uint16_t& moduleCount);
#endif // FEATURE_PRODUCT_MODULE
#ifdef FEATURE_PRIVATE_MODULE
extern const PrivateModule* GetPrivateModules(uint16_t& moduleCount);
#endif // FEATURE_PRIVATE_MODULE

// Initialization of static variables
JSIValue ModuleManager::requiredSystemModules = 0;
JSIValue ModuleManager::requiredHistoryModules = 0;

JSIValue ModuleManager::RequireModule(const char * const moduleName)
{
    char* category = nullptr;
    char* name = nullptr;
    if (!ParseModuleName(moduleName, &category, &name)) {
        HILOG_ERROR(HILOG_MODULE_ACE, "ModuleManager::RequireModule: parse module name failed");
        return JSI::CreateUndefined();
    }

    JSIValue moduleObj;
    if (!strcmp(category, CATEGORY_SYSTEM)) {
        uint16_t moduleCount = sizeof(OHOS_MODULES) / sizeof(Module);
        moduleObj = GetModuleObject(name, OHOS_MODULES, moduleCount, requiredSystemModules);
#ifdef FEATURE_PRODUCT_MODULE
        if (JSI::ValueIsUndefined(moduleObj)) {
            uint16_t prodModCount;
            const Module* prodModules = GetProductModules(prodModCount);
            moduleObj = GetModuleObject(name, prodModules, prodModCount, requiredSystemModules);
        }
#endif // FEATURE_PRODUCT_MODULE
#ifdef FEATURE_PRIVATE_MODULE
        if (JSI::ValueIsUndefined(moduleObj)) {
            const char * const bundleName = JsAppContext::GetInstance()->GetCurrentBundleName();
            moduleObj = GetModuleObject(name, nullptr, 0, requiredSystemModules, bundleName);
        }
#endif // FEATURE_PRIVATE_MODULE
    } else {
        moduleObj = JSI::CreateUndefined();
        HILOG_ERROR(HILOG_MODULE_ACE, "ModuleManager:RequireModule category %s does not exists!", category);
    }

    ace_free(category);
    category = nullptr;
    ace_free(name);
    name = nullptr;
    return moduleObj;
}

void ModuleManager::CleanUpModule()
{
    if (requiredSystemModules != 0) {
        JSI::ReleaseValue(requiredSystemModules);
        requiredSystemModules = 0;
    }
    InvokeCallbacks(onDestroyHead_);
}

bool ModuleManager::ParseModuleName(const char * const moduleName, char** category, char** name) const
{
    if ((moduleName == nullptr) || (category == nullptr) || (name == nullptr)) {
        return false;
    }
    // Get moduleName str
    char* str = nullptr;
    if (!CreateString(moduleName, &str)) {
        return false;
    }

    // Get category
    char* next = nullptr;
    char* tokenStr = strtok_s(str, ".", &next);
    if (!CreateString(tokenStr, category)) {
        ace_free(str);
        str = nullptr;
        return false;
    }

    // Get name
    tokenStr = strtok_s(nullptr, ".", &next);
    if (!CreateString(tokenStr, name)) {
        ace_free(str);
        str = nullptr;
        ace_free(*category);
        *category = nullptr;
        return false;
    }

    ace_free(str);
    str = nullptr;
    tokenStr = nullptr;
    next = nullptr;
    return true;
}

bool ModuleManager::CreateString(const char * const srcStr, char** resPtr) const
{
    if ((srcStr == nullptr) || (resPtr == nullptr)) {
        return false;
    }
    size_t length = strlen(srcStr);
    if (length >= UINT16_MAX) {
        return false;
    }
    (*resPtr) = static_cast<char *>(ace_malloc(length + 1));
    if ((*resPtr) == nullptr) {
        return false;
    }
    if (memcpy_s((*resPtr), length, srcStr, length) != 0) {
        ace_free(*resPtr);
        *resPtr = nullptr;
        return false;
    }

    (*resPtr)[length] = '\0';
    return true;
}

JSIValue ModuleManager::GetModuleObject(const char * const moduleName, const Module* modules, uint16_t modulesCount,
    JSIValue& categoryObj, const char * const bundleName)
{
    if (moduleName == nullptr) {
        return JSI::CreateUndefined();
    }
    if (bundleName == nullptr) {
        if (modules == nullptr) {
            return JSI::CreateUndefined();
        }
        for (uint16_t i = 0; i < modulesCount; i++) {
            const char *regName = modules[i].name;
            if ((regName != nullptr) && (strcmp(moduleName, regName) == 0)) {
                return InitModuleObject(moduleName, modules[i], categoryObj);
            }
        }
    }
#ifdef FEATURE_PRIVATE_MODULE
    else {
        uint16_t count;
        const PrivateModule* privateModules = GetPrivateModules(count);
        if (privateModules == nullptr) {
            return JSI::CreateUndefined();
        }
        for (uint16_t i = 0; i < count; i++) {
            const char *regBundleName = privateModules[i].bundleName;
            const char *regPrivateName = privateModules[i].module.name;
            if ((regBundleName != nullptr) && (regPrivateName != nullptr) &&
                (strcmp(bundleName, regBundleName) == 0) &&
                (strcmp(moduleName, regPrivateName) == 0)) {
                return InitModuleObject(moduleName, privateModules[i].module, categoryObj);
            }
        }
        HILOG_WARN(HILOG_MODULE_ACE, "ModuleManager:module %s does not exists!", moduleName);
    }
#endif
    return JSI::CreateUndefined();
}

JSIValue ModuleManager::InitModuleObject(const char * const name, Module module, JSIValue& categoryObj)
{
    if (categoryObj == 0) {
        categoryObj = JSI::CreateObject();
    }

    // Get module object from cached object
    JSIValue moduleObj = JSI::GetNamedProperty(categoryObj, name);
    if (JSI::ValueIsUndefined(moduleObj)) {
        JSIValue exports = JSI::CreateObject();
        module.initFunc(exports);

        // Get OnDestroy callback from module object
        NativeCallback destroy = GetNativeCallback(exports, nullptr);
        JsiCallback destroyHandler = GetJsiCallback(exports, ON_DESTROY_HANDLER);
        InsertCallback(onDestroyHead_, destroy, destroyHandler);

        // Insert OnTerminate callback to callback list
        InsertTerminateCallback(name, exports);

        // Set module object to cached object
        JSI::SetNamedProperty(categoryObj, name, exports);
        JSI::ReleaseValue(exports);
        moduleObj = JSI::GetNamedProperty(categoryObj, name);
    }
    return moduleObj;
}

void ModuleManager::InsertTerminateCallback(const char * const name, const JSIValue& moduleObj)
{
    if (requiredHistoryModules == 0) {
        requiredHistoryModules = JSI::CreateObject();
    }
    JSIValue object = JSI::GetNamedProperty(requiredHistoryModules, name);
    if (JSI::ValueIsUndefined(object)) {
        JSI::SetNamedProperty(requiredHistoryModules, name, moduleObj);
        // Get OnTerminate callback from module object
        NativeCallback terminate = GetNativeCallback(moduleObj, ON_TERMINATE);
        JsiCallback terminateHandler = GetJsiCallback(moduleObj, ON_TERMINATE_HANDLER);
        InsertCallback(onTerminateHead_, terminate, terminateHandler);
    }
    JSI::ReleaseValue(object);
}

void ModuleManager::OnTerminate()
{
    if (requiredHistoryModules != 0) {
        JSI::ReleaseValue(requiredHistoryModules);
        requiredHistoryModules = 0;
    }
    InvokeCallbacks(onTerminateHead_);
}

void ModuleManager::InsertCallback(CallbackNode *&head, NativeCallback callback, JsiCallback callbackHandler) const
{
    if ((callback == nullptr) && (callbackHandler == nullptr)) {
        return;
    }
    auto node = new CallbackNode();
    if (node == nullptr) {
        return;
    }
    node->callback = callback;
    node->callbackHandler = callbackHandler;
    if (head == nullptr) {
        head = node;
    } else {
        node->next = head;
        head = node;
    }
}

void ModuleManager::InvokeCallbacks(CallbackNode *&head) const
{
    CallbackNode *node = head;
    while (node != nullptr) {
        NativeCallback callback = node->callback;
        JsiCallback callbackHandler = node->callbackHandler;
        if (callback != nullptr) {
            (*callback)();
        }
        if (callbackHandler != nullptr) {
            (*callbackHandler)(JSI_ERR_OK);
        }

        head = node->next;
        delete node;
        node = head;
    }
    head = nullptr;
}

void* ModuleManager::GetObjectPointer(JSIValue object) const
{
    if (!JSI::ValueIsObject(object)) {
        return nullptr;
    }
    void *nativePtr = nullptr;
    jerry_value_t jObj = AS_JERRY_VALUE(object);
    bool exist = jerry_get_object_native_pointer(jObj, &nativePtr, nullptr);
    if (!exist || (nativePtr == nullptr)) {
        return nullptr;
    }
    jerry_delete_object_native_pointer(jObj, nullptr);
    return nativePtr;
}

void* ModuleManager::GetObjectNamedPointer(JSIValue object, const char * const name) const
{
    if (!JSI::ValueIsObject(object)) {
        return nullptr;
    }
    JSIValue funObj = JSI::GetNamedProperty(object, name);
    void *nativePtr = nullptr;
    if (JSI::ValueIsObject(funObj)) {
        nativePtr = GetObjectPointer(funObj);
        DeleteObjectProperty(object, name);
    }
    JSI::ReleaseValue(funObj);
    return nativePtr;
}

void ModuleManager::DeleteObjectProperty(JSIValue object, const char * const name) const
{
    if (name == nullptr) {
        return;
    }
    jerry_value_t jName = jerry_create_string(reinterpret_cast<const jerry_char_t *>(name));
    jerry_delete_property(AS_JERRY_VALUE(object), jName);
    jerry_release_value(jName);
}

NativeCallback ModuleManager::GetNativeCallback(JSIValue object, const char * const name) const
{
    void *callback = nullptr;
    if (name == nullptr) {
        callback = GetObjectPointer(object);
    } else {
        callback = GetObjectNamedPointer(object, name);
    }
    return reinterpret_cast<NativeCallback>(callback);
}

JsiCallback ModuleManager::GetJsiCallback(JSIValue object, const char * const name) const
{
    void *callback = GetObjectNamedPointer(object, name);
    return reinterpret_cast<JsiCallback>(callback);
}
} // namespace ACELite
} // namespace OHOS
