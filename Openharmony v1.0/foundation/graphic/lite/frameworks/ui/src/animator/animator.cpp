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

#include "animator/animator.h"

#include "common/task_manager.h"
#include "hal_tick.h"

namespace OHOS {
void Animator::Start()
{
    SetState(START);
    runTime_ = 0;
    lastRunTime_ = 0;
}

void Animator::Stop()
{
    SetState(STOP);
    if (callback_ != nullptr) {
        callback_->OnStop(*view_);
    }
}

void Animator::Pause()
{
    SetState(PAUSE);
}

void Animator::Resume()
{
    SetState(START);
    lastRunTime_ = HALTick::GetInstance().GetTime();
}

void Animator::Run()
{
    if (lastRunTime_ == 0) {
        lastRunTime_ = HALTick::GetInstance().GetTime();
    }

    uint32_t elepse = HALTick::GetInstance().GetElapseTime(lastRunTime_);

    runTime_ = (UINT32_MAX - elepse > runTime_) ? (runTime_ + elepse) : time_;
    lastRunTime_ = HALTick::GetInstance().GetTime();
    if (callback_ != nullptr) {
        callback_->Callback(view_);
    }
}

void AnimatorManager::Init()
{
    Task::Init();
}

void AnimatorManager::Add(Animator* animator)
{
    if (animator == nullptr) {
        return;
    }

    list_.PushBack(animator);
}

void AnimatorManager::Remove(const Animator* animator)
{
    if (animator == nullptr) {
        return;
    }
    ListNode<Animator*>* pos = list_.Begin();
    while (pos != list_.End()) {
        if (pos->data_ == animator) {
            list_.Remove(pos);
            return;
        }
        pos = pos->next_;
    }
}

void AnimatorManager::AnimatorTask()
{
    ListNode<Animator*>* pos = list_.Begin();
    Animator* animator = nullptr;

    while (pos != list_.End()) {
        animator = pos->data_;
        if (animator->GetState() == Animator::START) {
            if (animator->IsRepeat() || animator->GetRunTime() <= animator->GetTime()) {
                animator->Run();
            } else {
                animator->Stop();
            }
        }

        pos = pos->next_;
    }
}
}
