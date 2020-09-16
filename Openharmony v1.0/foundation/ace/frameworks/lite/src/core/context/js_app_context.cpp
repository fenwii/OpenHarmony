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

#include "js_app_context.h"
#include "ace_event_error_code.h"
#include "ace_log.h"
#if (defined(__LINUX__) || defined(__LITEOS__))
#include "ace_ability.h"
#endif
#include "component_factory.h"
#include "component_utils.h"
#include "js_app_environment.h"
#include "platform_adapter.h"
#if ENABLED(SECURE_C_FUNCTION)
#include "securec.h"
#endif // ENABLED(SECURE_C_FUNCTION)
#include "root_view.h"
#include "task_manager.h"
#include "ui_view_group.h"
#if (!defined(_WIN32) && !defined(_WIN64))
#ifdef SERVICE_MANAGER_API_SUPPORTED
// no AMS support on PC simulator
#include "ability_service_interface.h"
#include "iunknown.h"
#include "samgr_lite.h"
#endif // SERVICE_MANAGER_API_SUPPORTED
#endif // (!defined(_WIN32) && !defined(_WIN64))
#include "fatal_handler.h"
#include "js_profiler.h"

namespace OHOS {
namespace ACELite {
void JsAppContext::ClearContext()
{
    // reset current ability path and uuid
    ReleaseAbilityInfo();
}

/**
 * return value should be released by caller when it's not used
 */
jerry_value_t JsAppContext::Eval(const char * const jsFileFullPath, size_t fileNameLength, bool isAppEval) const
{
    if ((jsFileFullPath == nullptr) || (fileNameLength == 0)) {
        HILOG_ERROR(HILOG_MODULE_ACE, "Failed to eval js code cause by empty JavaScript script.");
        ACE_ERROR_CODE_PRINT(EXCE_ACE_ROUTER_REPLACE_FAILED, EXCE_ACE_PAGE_INDEX_MISSING);
        return UNDEFINED;
    }

    uint32_t contentLength = 0;
    START_TRACING(PAGE_CODE_LOAD);
    bool snapshotMode = JsAppEnvironment::GetInstance()->IsSnapshotMode();
    char *jsCode = ReadFile(jsFileFullPath, &contentLength, snapshotMode);
    STOP_TRACING();
    if (jsCode == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "empty js file, eval user code failed");
        ACE_ERROR_CODE_PRINT(EXCE_ACE_ROUTER_REPLACE_FAILED, EXCE_ACE_PAGE_FILE_READ_FAILED);
        return UNDEFINED;
    }

    START_TRACING(PAGE_CODE_EVAL);
    jerry_value_t viewModel = UNDEFINED;
    if (snapshotMode) {
        viewModel = jerry_exec_snapshot(reinterpret_cast<const uint32_t *>(jsCode), contentLength, 0, 1);
    } else {
        const jerry_char_t *jsScript = reinterpret_cast<const jerry_char_t *>(jsCode);
        jerry_value_t retValue = jerry_parse(reinterpret_cast<const jerry_char_t *>(jsFileFullPath), fileNameLength,
                                             jsScript, contentLength, JERRY_PARSE_NO_OPTS);
        if (jerry_value_is_error(retValue)) {
            ACE_ERROR_CODE_PRINT(EXCE_ACE_ROUTER_REPLACE_FAILED, EXCE_ACE_PAGE_JS_EVAL_FAILED);
            PrintErrorMessage(retValue);
            // free js code buffer
            ace_free(jsCode);
            jsCode = nullptr;
            jerry_release_value(retValue);
            STOP_TRACING();
            return UNDEFINED;
        }
        viewModel = jerry_run(retValue);
        jerry_release_value(retValue);
    }

    STOP_TRACING();
    // free js code buffer
    ace_free(jsCode);
    jsCode = nullptr;

    if (jerry_value_is_error(viewModel)) {
        ACE_ERROR_CODE_PRINT(EXCE_ACE_ROUTER_REPLACE_FAILED, EXCE_ACE_PAGE_JS_EVAL_FAILED);
        PrintErrorMessage(viewModel);
        jerry_release_value(viewModel);
        return UNDEFINED;
    }

    SetGlobalNamedProperty(isAppEval, viewModel);
    return viewModel;
}

void JsAppContext::SetGlobalNamedProperty(bool isAppEval, jerry_value_t viewModel) const
{
    jerry_value_t globalObject = jerry_get_global_object();
    if (isAppEval) {
        JerrySetNamedProperty(globalObject, ATTR_APP, viewModel);
    } else {
        JerrySetNamedProperty(globalObject, ATTR_ROOT, viewModel);
    }
    jerry_release_value(globalObject);
}

jerry_value_t JsAppContext::Render(jerry_value_t viewModel) const
{
    if (jerry_value_is_error(viewModel)) {
        HILOG_ERROR(HILOG_MODULE_ACE, "Failed to render app cause by render error.");
        return UNDEFINED;
    }

    if (jerry_value_is_undefined(viewModel)) {
        HILOG_ERROR(HILOG_MODULE_ACE, "Nothing to render as it is undefined.");
        return UNDEFINED;
    }

    jerry_value_t renderFunction = jerryx_get_property_str(viewModel, ATTR_RENDER);
    if (jerry_value_is_undefined(renderFunction)) {
        ACE_ERROR_CODE_PRINT(EXCE_ACE_ROUTER_REPLACE_FAILED, EXCE_ACE_PAGE_NO_RENDER_FUNC);
        return UNDEFINED;
    }
    jerry_value_t nativeElement = CallJSFunction(renderFunction, viewModel, nullptr, 0);
    if (jerry_value_is_undefined(nativeElement)) {
        ACE_ERROR_CODE_PRINT(EXCE_ACE_ROUTER_REPLACE_FAILED, EXCE_ACE_PAGE_RENDER_FAILED);
    }
    jerry_release_value(renderFunction);
    return nativeElement;
}

void JsAppContext::Show() const
{
    RootView *rootView = RootView::GetInstance();
    if (rootView == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "get rootView is nullptr");
        return;
    }
    rootView->Invalidate();
}

void JsAppContext::RemoveAllView() const
{
    RootView *rootView = RootView::GetInstance();
    if (rootView == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "get rootView is nullptr");
        return;
    }
    rootView->RemoveAll();
    rootView->Invalidate();
}

void JsAppContext::TerminateAbility() const
{
    if (currentToken_ == 0) {
        // if no running js ability, drop
        return;
    }
    FatalHandler::GetInstance().SetExitingFlag(true);
    Terminate(currentToken_);
}

void JsAppContext::SetCurrentAbilityInfo(const char * const abilityPath, const char * const bundleName, uint16_t token)
{
    // release old first
    ReleaseAbilityInfo();

    if (abilityPath != nullptr) {
        size_t abilityPathLen = strlen(abilityPath);
        if ((abilityPathLen > 0) && (abilityPathLen < PATH_LENGTH_MAX)) {
            currentAbilityPath_ = static_cast<char *>(ace_malloc(abilityPathLen + 1));
            if (currentAbilityPath_ == nullptr) {
                HILOG_ERROR(HILOG_MODULE_ACE, "malloc buffer for current ability path failed");
                return;
            }
            if (memcpy_s(currentAbilityPath_, abilityPathLen, abilityPath, abilityPathLen) != 0) {
                ace_free(currentAbilityPath_);
                currentAbilityPath_ = nullptr;
                return;
            }
            currentAbilityPath_[abilityPathLen] = 0;
        }
    }

    if (bundleName != nullptr) {
        size_t bundleNameLen = strlen(bundleName);
        if ((bundleNameLen > 0) && (bundleNameLen < NAME_LENGTH_MAX)) {
            currentBundleName_ = static_cast<char *>(ace_malloc(bundleNameLen + 1));
            if (currentBundleName_ == nullptr) {
                HILOG_ERROR(HILOG_MODULE_ACE, "malloc buffer for current uuid failed");
                return;
            }
            if (memcpy_s(currentBundleName_, bundleNameLen, bundleName, bundleNameLen) != 0) {
                ace_free(currentAbilityPath_);
                currentAbilityPath_ = nullptr;
                ace_free(currentBundleName_);
                currentBundleName_ = nullptr;
                return;
            }
            currentBundleName_[bundleNameLen] = 0;
        }
    }

    currentToken_ = token;
}

void JsAppContext::SetCurrentJsPath(const char * const jsPath)
{
    // release old first
    if (currentJsPath_) {
        ace_free(currentJsPath_);
        currentJsPath_ = nullptr;
    }

    if (jsPath != nullptr) {
        size_t jsPathLen = strlen(jsPath);
        if ((jsPathLen > 0) && (jsPathLen < PATH_LENGTH_MAX)) {
            currentJsPath_ = static_cast<char *>(ace_malloc(jsPathLen + 1));
            if (currentJsPath_ == nullptr) {
                HILOG_ERROR(HILOG_MODULE_ACE, "malloc buffer for current js path failed");
                return;
            }
            if (memcpy_s(currentJsPath_, jsPathLen, jsPath, jsPathLen) != 0) {
                ace_free(currentJsPath_);
                currentJsPath_ = nullptr;
                return;
            }
            currentJsPath_[jsPathLen] = '\0';
        }
    }
}

void JsAppContext::ReleaseAbilityInfo()
{
    if (currentBundleName_) {
        ace_free(currentBundleName_);
        currentBundleName_ = nullptr;
    }

    if (currentAbilityPath_) {
        ace_free(currentAbilityPath_);
        currentAbilityPath_ = nullptr;
    }

    if (currentJsPath_) {
        ace_free(currentJsPath_);
        currentJsPath_ = nullptr;
    }
}
} // namespace ACELite
} // namespace OHOS
