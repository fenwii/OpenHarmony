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

#include "input_manager_service.h"

#include "graphic_log.h"

namespace OHOS {
InputEventReader InputManagerService::reader_;
InputEventDistributer InputManagerService::distributer_;
pthread_t InputManagerService::distributerThread_ = -1;
int32_t InputManagerService::distributerThreadCreated_;
std::queue<RawEvent> InputManagerService::eventQueue_;
pthread_mutex_t InputManagerService::lock_;
pthread_cond_t InputManagerService::nonEmpty_;
pthread_cond_t InputManagerService::nonFull_;

void InputManagerService::Run()
{
    reader_.StartUpHub();
    reader_.RegisterReadCallback(ReadCallback);
    touch_ = new TouchInputEventListener();
    mouse_ = new MouseInputEventListener();
    reader_.RegisterInputEventListener(touch_);
    reader_.RegisterInputEventListener(mouse_);
    distributerThreadCreated_ = pthread_create(&distributerThread_, nullptr, Distribute, nullptr);
    if (!distributerThreadCreated_) {
        pthread_detach(distributerThread_);
    }
}

void InputManagerService::Stop()
{
    delete touch_;
    touch_ = nullptr;
    delete mouse_;
    mouse_ = nullptr;
}

InputManagerService::~InputManagerService()
{
    pthread_mutex_destroy(&lock_);
    pthread_cond_destroy(&nonEmpty_);
    pthread_cond_destroy(&nonFull_);
}

void InputManagerService::ReadCallback(RawEvent* event)
{
    pthread_mutex_lock(&lock_);
    while (eventQueue_.size() == MAX_EVENT_SIZE) {
        pthread_cond_wait(&nonFull_, &lock_);
    }
    // push events into queue
    eventQueue_.push(event[0]);
    pthread_mutex_unlock(&lock_);
    pthread_cond_signal(&nonEmpty_);
}

void* InputManagerService::Distribute(void* args)
{
    GRAPHIC_LOGI("InputManagerService::Distribute Ready to read distribute!");
    while (true) {
        pthread_mutex_lock(&lock_);
        while (eventQueue_.size() == 0) {
            pthread_cond_wait(&nonEmpty_, &lock_);
        }
        // pop events from queue
        RawEvent events[MAX_INPUT_DEVICE_NUM];
        int32_t len = (eventQueue_.size() > MAX_EVENT_SIZE) ? MAX_EVENT_SIZE : eventQueue_.size();
        for (int32_t i = 0; i < len; i++) {
            events[i] = eventQueue_.front();
            eventQueue_.pop();
        }
        distributer_.Distribute(events, len);
        pthread_mutex_unlock(&lock_);
        pthread_cond_signal(&nonFull_);
    }
    return nullptr;
}
} // namespace OHOS
