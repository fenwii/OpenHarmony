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

#include "js_router.h"

#include "ace_log.h"
#include "js_async_work.h"
#include "js_page_state_machine.h"
#include "js_profiler.h"

namespace OHOS {
namespace ACELite {
static void ReplaceAsync(void *data)
{
    if (data == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "replace async failed with null input parameter");
        return;
    }
    // void* can not be dynamically_casted from
    auto router = static_cast<Router *>(data);
    router->ReplaceSync();
    OUTPUT_TRACE();
}

jerry_value_t Router::Replace(jerry_value_t object, bool async)
{
    if (newSm_ != nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "router is replacing, can not handle the new request");
        return UNDEFINED;
    }
    StateMachine *newSm = new StateMachine();
    if (newSm == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "malloc state machine memory heap failed.");
        return UNDEFINED;
    }
    // init new state machine
    jerry_value_t jsRes = jerry_create_undefined();
    bool res = newSm->Init(object, jsRes);
    if (!res) {
        delete newSm;
        return jsRes;
    }
    newSm_ = newSm;
    // dispatch the new page rendering to the async handling as the current context of
    // router.replace need to be released, which need to return out from the scope
    if (async) {
        if (!JsAsyncWork::DispatchAsyncWork(ReplaceAsync, this)) {
            // request replacing failed, no chance to do it, release the new state machine
            HILOG_ERROR(HILOG_MODULE_ACE, "dispatch replacing request failed");
            delete newSm_;
            newSm_ = nullptr;
        }
    } else {
        // for the first startup of application, no need to do the async replace
        ReplaceSync();
    }
    return jsRes;
}

void Router::ReplaceSync()
{
    if (newSm_ == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "replace sync failed, new sm should be prepared");
        return;
    }
    START_TRACING(ROUTER_REPLACE);
    // new state machine run successfully to show new page, then need to release old state machine.
    if (currentSm_ != nullptr) {
        delete currentSm_;
        currentSm_ = nullptr;
    }
    // new state machine should to be current.
    currentSm_ = newSm_;
    newSm_ = nullptr;
    currentSm_->SetHiddenFlag(hidden_);
    // run state machine and start to jump to init state.
    currentSm_->ChangeState(INIT_STATE);
    if (hidden_) {
        HILOG_DEBUG(HILOG_MODULE_ACE, "the whole application is in background, move to HIDE state directly");
        // the whole app is in background, move to HIDE state immediately
        currentSm_->ChangeState(BACKGROUND_STATE);
    } else {
        // above call will move sm into ready state, than let the page show
        currentSm_->ChangeState(SHOW_STATE);
    }
    STOP_TRACING();
}

void Router::Show()
{
    if (currentSm_ == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "no SM when performing show");
        return;
    }

    hidden_ = false;
    currentSm_->SetHiddenFlag(hidden_);
    currentSm_->ChangeState(SHOW_STATE);
}

void Router::Hide()
{
    if (currentSm_ == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "no SM when performing background");
        return;
    }

    currentSm_->ChangeState(BACKGROUND_STATE);
    hidden_ = true;
    currentSm_->SetHiddenFlag(hidden_);
}
} // namespace ACELite
} // namespace OHOS
