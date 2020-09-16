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
#include "js_ability_impl.h"
#include "component.h"
#include "js_app_context.h"
#include "js_app_environment.h"
#if ENABLED(SECURE_C_FUNCTION)
#include "securec.h"
#endif // ENABLED(SECURE_C_FUNCTION)
#include "ace_event_error_code.h"
#include "ace_log.h"
#include "component_utils.h"
#include "fatal_handler.h"
#include "js_profiler.h"
#include "module_manager.h"
#include "presets/localization_module.h"
#include "presets/timer_module.h"

namespace OHOS {
namespace ACELite {
void JSAbilityImpl::InitEnvironment(const char * const abilityPath, const char * const bundleName, uint16_t token)
{
    if ((abilityPath == nullptr) || strlen(abilityPath) == 0 || (bundleName == nullptr) || strlen(bundleName) == 0) {
        HILOG_ERROR(HILOG_MODULE_ACE, "invalid input parameters");
        return;
    }

    if (isEnvInit_) {
        HILOG_ERROR(HILOG_MODULE_ACE, "already initialized, return");
        return;
    }
    // init engine && js fwk
    JsAppEnvironment *appJsEnv = JsAppEnvironment::GetInstance();
    appContext_ = JsAppContext::GetInstance();
    // check if we should use snapshot mode, do this before everything,
    // but after debugger config is set
    appJsEnv->InitRuntimeMode();
    appContext_->SetCurrentAbilityInfo(abilityPath, bundleName, token);
    appContext_->SetTopJSAbilityImpl(this);
    appJsEnv->InitJsFramework();

    // initialize js object after engine started up
    abilityModel_ = UNDEFINED;
    nativeElement_ = UNDEFINED;
    isEnvInit_ = true;

    // relocate app.js fullpath
    const char * const appJSFileName = (appJsEnv->IsSnapshotMode()) ? "app.bc" : "app.js";
    char *fileFullPath = RelocateJSSourceFilePath(abilityPath, appJSFileName);
    if (fileFullPath == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "relocate js file failed");
        ACE_ERROR_CODE_PRINT(EXCE_ACE_FWK_LAUNCH_FAILED, EXCE_ACE_APP_ENTRY_MISSING);
        return;
    }

    START_TRACING(APP_CODE_EVAL);
    abilityModel_ = appContext_->Eval(fileFullPath, strlen(fileFullPath), true); // generate global.$app js object
    STOP_TRACING();

    ace_free(fileFullPath);
    fileFullPath = nullptr;
    router_ = new Router();
    if (router_ == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "malloc router heap memory failed.");
        return;
    }
}

void JSAbilityImpl::CleanUp()
{
    START_TRACING(APP_ON_DESTROY);
    // clean up user's js
    InvokeOnDestroy();
    STOP_TRACING();

    // delete router's resources about page
    if (router_ != nullptr) {
        delete router_;
        router_ = nullptr;
    }
    TimersModule::Clear();
    LocalModule::Clear();
    if (appContext_) {
        appContext_->ClearContext();
    }
    ModuleManager::GetInstance()->OnTerminate();
    JsAppEnvironment::GetInstance()->Cleanup();
    // clean up engin
    if (isEnvInit_) {
        jerry_cleanup();
        isEnvInit_ = false;
    }
    OUTPUT_TRACE();
}

void JSAbilityImpl::DeliverCreate()
{
    START_TRACING(APP_ON_CREATE);
    // call InvokeOnCreate
    InvokeOnCreate();
    STOP_TRACING();
    // if we have done the render or not initialized yet, don't call render
    if (rendered_ || (appContext_ == nullptr)) {
        ACE_ERROR_CODE_PRINT(EXCE_ACE_FWK_LAUNCH_FAILED, EXCE_ACE_APP_RENDER_FAILED);
        return;
    }
    // call render to setup user interface
    jerry_value_t object = jerry_create_object();
    JerrySetStringProperty(object, ROUTER_PAGE_URI, PATH_DEFAULT);
    if (router_) {
        jerry_release_value(router_->Replace(object, false));
        rendered_ = true;
    }
    jerry_release_value(object);
}

void JSAbilityImpl::Show() const
{
    if (router_ == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "no router instance to perform the show request");
        return;
    }
    router_->Show();
}

void JSAbilityImpl::Hide() const
{
    if (router_ == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "no router instance to perform the hide request");
        return;
    }
    router_->Hide();
}

void JSAbilityImpl::NotifyBackPressed() const
{
    if (appContext_ == nullptr) {
        return;
    }

    InvokeOnBackPressed();

    appContext_->TerminateAbility();
}

void JSAbilityImpl::InvokeOnCreate() const
{
    if (IS_UNDEFINED(abilityModel_)) {
        HILOG_ERROR(HILOG_MODULE_ACE, "view model is undefined when call user's init");
        return;
    }
    jerry_value_t onCreateFunction = jerryx_get_property_str(abilityModel_, ABILITY_LIFECYCLE_CALLBACK_ON_CREATE);
    if (IS_UNDEFINED(onCreateFunction)) {
        // user does not set onInit method
        return;
    }
    CallJSFunctionAutoRelease(onCreateFunction, abilityModel_, nullptr, 0);
    jerry_release_value(onCreateFunction);
}

void JSAbilityImpl::InvokeOnDestroy() const
{
    InvokeMethodWithoutParameter(ABILITY_LIFECYCLE_CALLBACK_ON_DESTROY);
    // release FeatureAbility object
    jerry_release_value(abilityModel_);
}

void JSAbilityImpl::InvokeOnBackPressed() const
{
    InvokeMethodWithoutParameter(BACK_PRESSED_NAME);
}

void JSAbilityImpl::InvokeMethodWithoutParameter(const char * const name) const
{
    if (FatalHandler::GetInstance().IsJSRuntimeFatal()) {
        // can not continue to involve any JS object creating on engine in case runtime fatal
        return;
    }
    if ((name == nullptr) || strlen(name) == 0) {
        return;
    }

    jerry_value_t function = jerryx_get_property_str(abilityModel_, name);
    if (IS_UNDEFINED(function)) {
        // user does not set onBackpress method
        return;
    }
    CallJSFunctionAutoRelease(function, abilityModel_, nullptr, 0);
    jerry_release_value(function);
}
} // namespace ACELite
} // namespace OHOS
