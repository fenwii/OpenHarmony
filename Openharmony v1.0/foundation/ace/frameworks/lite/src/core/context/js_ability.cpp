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

#include "js_ability.h"

#include <cstring>
#include "ace_event_error_code.h"
#include "ace_log.h"
#include "acelite_config.h"
#include "fatal_handler.h"
#include "js_ability_impl.h"
#include "js_profiler.h"
#ifdef FEATURE_ACELITE_PRODUCT_MEMORY_POOL
#include "mem_pool.h"
#endif

namespace OHOS {
namespace ACELite {
/**
 * This is a helper function to cast void* to JSAbilityImpl*, for header seperating purpose.
 */
static JSAbilityImpl *CastAbilityImpl(void *abilityImpl)
{
    if (abilityImpl == nullptr) {
        return nullptr;
    }

    return static_cast<JSAbilityImpl *>(abilityImpl);
}

static void DumpNativeMemoryUsage()
{
#ifdef FEATURE_ACELITE_PRODUCT_MEMORY_POOL
    MemPool::MemInfo memInfo;
    MemPool::GetInstance()->GetMemInfo(&memInfo);
    HILOG_DEBUG(HILOG_MODULE_ACE, "avaliable free size: %d", memInfo.freeSize);
#endif // FEATURE_ACELITE_PRODUCT_MEMORY_POOL
}

void JSAbility::Launch(const char * const abilityPath, const char * const bundleName, uint16_t token)
{
    if (jsAbilityImpl_ != nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "Launch only can be triggered once");
        ACE_ERROR_CODE_PRINT(EXCE_ACE_FWK_LAUNCH_FAILED, EXCE_ACE_APP_ALREADY_LAUNCHED);
        return;
    }

    if ((abilityPath == nullptr) || (strlen(abilityPath) == 0)) {
        HILOG_ERROR(HILOG_MODULE_ACE, "invalid app path");
        ACE_ERROR_CODE_PRINT(EXCE_ACE_FWK_LAUNCH_FAILED, EXCE_ACE_INVALID_APP_PATH);
        return;
    }

    if ((bundleName == nullptr) || (strlen(bundleName) == 0)) {
        HILOG_ERROR(HILOG_MODULE_ACE, "invalid bundle name");
        ACE_ERROR_CODE_PRINT(EXCE_ACE_FWK_LAUNCH_FAILED, EXCE_ACE_INVALID_BUNDLE_NAME);
        return;
    }

    DumpNativeMemoryUsage();
    jsAbilityImpl_ = new JSAbilityImpl();
    if (jsAbilityImpl_ == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "Create JSAbilityRuntime failed");
        return;
    }
    START_TRACING(LAUNCH);
    JSAbilityImpl *jsAbilityImpl = CastAbilityImpl(jsAbilityImpl_);
    FatalHandler::GetInstance().RegisterFatalHandler();
    jsAbilityImpl->InitEnvironment(abilityPath, bundleName, token);
    jsAbilityImpl->DeliverCreate();
    STOP_TRACING();
    OUTPUT_TRACE();
}

void JSAbility::Show() const
{
    if (jsAbilityImpl_ == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "Must trigger Launch first");
        return;
    }

    JSAbilityImpl *jsAbilityImpl = CastAbilityImpl(jsAbilityImpl_);
    jsAbilityImpl->Show();
}

void JSAbility::Hide() const
{
    if (jsAbilityImpl_ == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "Must trigger Launch first");
        return;
    }

    JSAbilityImpl *jsAbilityImpl = CastAbilityImpl(jsAbilityImpl_);
    jsAbilityImpl->Hide();
}

void JSAbility::TransferToDestroy()
{
    if (jsAbilityImpl_ == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "Must trigger Launch first");
        return;
    }

    JSAbilityImpl *jsAbilityImpl = CastAbilityImpl(jsAbilityImpl_);
    jsAbilityImpl->CleanUp();
    delete reinterpret_cast<JSAbilityImpl *>(jsAbilityImpl_);
    jsAbilityImpl_ = nullptr;
    // Reset render flag or low layer task mutex in case we are during the rendering process,
    // this situation might happen if the destroy function is called outside of JS thread, such as AMS.
    FatalHandler::GetInstance().ResetRendering();
    FatalHandler::GetInstance().SetExitingFlag(false);
    DumpNativeMemoryUsage();
}

void JSAbility::BackPressed()
{
    if (jsAbilityImpl_ == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "Must trigger Launch first");
        return;
    }

    JSAbilityImpl *jsAbilityImpl = CastAbilityImpl(jsAbilityImpl_);
    jsAbilityImpl->NotifyBackPressed();
}

const char *JSAbility::GetPackageName()
{
    return JsAppContext::GetInstance()->GetCurrentBundleName();
}

void JSAbility::ForceDestroy()
{
#ifdef OHOS_ACELITE_PRODUCT_WATCH
    FatalHandler::GetInstance().HandleFatalError(FatalHandler::ERR_INVALID);
    TransferToDestroy();
    FatalHandler::GetInstance().CleanUpFatalResource();
#endif // OHOS_ACELITE_PRODUCT_WATCH
}

#ifdef OHOS_ACELITE_PRODUCT_WATCH
static RenderTickHandler g_renderTick = nullptr;
#endif // OHOS_ACELITE_PRODUCT_WATCH
void JSAbility::RegisterTEHandler(RenderTickHandler handler)
{
#ifdef OHOS_ACELITE_PRODUCT_WATCH
    if (g_renderTick != nullptr) {
        // the TE handler registering only can be performed once after whole system booting up
        return;
    }
    g_renderTick = handler;
#endif // OHOS_ACELITE_PRODUCT_WATCH
}

void JSAbility::HandleRenderTick()
{
#ifdef OHOS_ACELITE_PRODUCT_WATCH
    if ((g_renderTick != nullptr) && !(FatalHandler::GetInstance().IsAppExiting())) {
        FatalHandler::GetInstance().SetTEHandlingFlag(true);
        g_renderTick();
        FatalHandler::GetInstance().SetTEHandlingFlag(false);
    }
#endif // OHOS_ACELITE_PRODUCT_WATCH
}
} // namespace ACELite
} // namespace OHOS
