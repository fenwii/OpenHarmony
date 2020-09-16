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

#include "ace_event_error_code.h"
#include "ace_log.h"
#include "fatal_handler.h"
#include "js_page_state.h"

namespace OHOS {
namespace ACELite {
void PageInitState::Handle(StateMachine &sm)
{
    int currState = sm.GetCurrentState();
    if (currState == UNDEFINED_STATE) {
        sm.SetCurrentState(INIT_STATE);
        HILOG_INFO(HILOG_MODULE_ACE, "undefined state -> init state");
        sm.BindParameters();
        // do this state's action: eval user js code and invoke life cycle callback
        sm.EvalPage();
        sm.InvokePageLifeCycleCallback(PAGE_LIFECYCLE_ON_INIT);
        sm.ChangeState(READY_STATE);
    } else {
        HILOG_ERROR(HILOG_MODULE_ACE, "current state(%d) is invalid when changing undefined state to init state.",
                    currState);
    }
}

void PageReadyState::Handle(StateMachine &sm)
{
    int currState = sm.GetCurrentState();
    if (currState == INIT_STATE) {
        HILOG_INFO(HILOG_MODULE_ACE, "init state -> ready state");
        // do this state's action:call render to setup user interface
        sm.RenderPage();
        sm.InvokePageLifeCycleCallback(PAGE_LIFECYCLE_CALLBACK_ON_READY);
        sm.SetCurrentState(READY_STATE);
    } else {
        HILOG_ERROR(HILOG_MODULE_ACE, "current state(%d) is invalid when changing init state to ready state.",
                    currState);
    }
}

void PageShowState::Handle(StateMachine &sm)
{
    int currState = sm.GetCurrentState();
    if ((currState == READY_STATE) || (currState == BACKGROUND_STATE)) {
        HILOG_INFO(HILOG_MODULE_ACE, "current state(%d) -> show state", currState);
        // do this state's action: call show to display user interface
        sm.ShowPage();
        sm.InvokePageLifeCycleCallback(PAGE_LIFECYCLE_CALLBACK_ON_SHOW);
        sm.SetCurrentState(SHOW_STATE);
    } else {
        HILOG_ERROR(HILOG_MODULE_ACE, "current state(%d) is invalid when changing ready state to show state.",
                    currState);
    }
}

void PageBackgroundState::Handle(StateMachine &sm)
{
    int currState = sm.GetCurrentState();
    if ((currState == READY_STATE) || (currState == SHOW_STATE)) {
        HILOG_INFO(HILOG_MODULE_ACE, "current state(%d) -> background state", currState);
        sm.HidePage();
        sm.InvokePageLifeCycleCallback(PAGE_LIFECYCLE_CALLBACK_ON_HIDE);
        sm.SetCurrentState(BACKGROUND_STATE);
    } else {
        HILOG_ERROR(HILOG_MODULE_ACE, "current state(%d) is invalid when changing show state to background state.",
                    currState);
    }
}

void PageDestroyState::Handle(StateMachine &sm)
{
    int currState = sm.GetCurrentState();
    // any normal state can jump to destory state
    if ((currState >= INIT_STATE) || (FatalHandler::GetInstance().IsFatalErrorHitted())) {
        HILOG_INFO(HILOG_MODULE_ACE, "current state(%d) -> destroy state", currState);
        ACE_EVENT_PRINT(MT_ACE_RELEASE_HISTORY_PAGE, 0);
        sm.InvokePageLifeCycleCallback(PAGE_LIFECYCLE_CALLBACK_ON_DESTROY);
        sm.ReleaseHistoryPageResource();
        sm.SetCurrentState(DESTROY_STATE);
    } else {
        HILOG_ERROR(HILOG_MODULE_ACE, "current state(%d) is invalid when changing show state to destroy state.",
                    currState);
    }
}
} // namespace ACELite
} // namespace OHOS
