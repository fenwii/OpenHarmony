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

#ifndef OHOS_ACELITE_JS_PAGE_STATE_MACHINE_H
#define OHOS_ACELITE_JS_PAGE_STATE_MACHINE_H

#include "js_app_context.h"
#include "non_copyable.h"
#include "scroll_layer.h"

namespace OHOS {
namespace ACELite {
enum {
    UNDEFINED_STATE = -1,
    INIT_STATE, // 0
    READY_STATE,
    SHOW_STATE,
    BACKGROUND_STATE,
    DESTROY_STATE,
    END_STATE
};
#define PAGE_STATE_SIZE END_STATE

constexpr char PAGE_LIFECYCLE_ON_INIT[] = "onInit";
constexpr char PAGE_LIFECYCLE_CALLBACK_ON_READY[] = "onReady";
constexpr char PAGE_LIFECYCLE_CALLBACK_ON_SHOW[] = "onShow";
constexpr char PAGE_LIFECYCLE_CALLBACK_ON_HIDE[] = "onHide";
constexpr char PAGE_LIFECYCLE_CALLBACK_ON_DESTROY[] = "onDestroy";

#if JS_PAGE_SPECIFIC
extern JSPageSpecific jsPageSpecific;
#endif

class State;
class StateMachine final : public MemoryHeap {
public:
    ACE_DISALLOW_COPY_AND_MOVE(StateMachine);
    StateMachine();
    ~StateMachine();
    bool Init(jerry_value_t object, jerry_value_t &msg);
    void ChangeState(int newState);
    void BindParameters();
    bool BindUri(jerry_value_t &msg);
    int8_t GetCurrentState() const
    {
        return currentState_;
    }
    void EvalPage();
    void RenderPage();
    jerry_value_t ShowPage() const;
    void HidePage() const;
    void SetCurrentState(int8_t newState);
    void InvokePageLifeCycleCallback(const char * const name) const;
    void ReleaseHistoryPageResource();
    void SetHiddenFlag(bool flag);

private:
    void RegisterUriAndParamsToPage(const char * const uri, jerry_value_t params);
    int GenerateJsPagePath(const char * const uri);
    void DeleteViewModelProperties() const;
    void ReleaseRootObject() const;

private:
    int8_t currentState_;
    State *stateMap_[PAGE_STATE_SIZE];
    char *jsPagePath_;
    char *appRootPath_;
    char *uri_;
    JsAppContext *appContext_;
    jerry_value_t viewModel_;     // the object evaled from user JS code
    jerry_value_t nativeElement_; // the object returned from render function
    jerry_value_t object_;        // object transferred from one page to another page
    bool hasParams_;              // the flag representation for whether having params of object_
    bool isEntireHidden_;            // representing if the whole app is in background
    Watcher *watchersHead_;       // head of watchers list
    ScrollLayer *scrollLayer_;
};
} // namespace ACELite
} // namespace OHOS

#endif // OHOS_ACELITE_JS_PAGE_STATE_MACHINE_H
