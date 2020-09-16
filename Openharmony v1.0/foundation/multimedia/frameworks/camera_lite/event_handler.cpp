/*
 * Copyright(c) 2020 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http ://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "event_handler.h"

using namespace std;

namespace OHOS {
namespace Media {
EventHandler::EventHandler() : running_(false)
{
    hdlThrd_ = new thread(EventDispatch, this);
}

EventHandler::~EventHandler()
{
    while (!running_) {
        this_thread::yield(); // TODO:may not effective in muscle
    }
    running_ = false;
    cv_.notify_all();
    hdlThrd_->join();
    delete hdlThrd_;
}

bool EventHandler::IsRunning()
{
    return running_;
}

void EventHandler::EventDispatch(EventHandler *hdl)
{
    std::unique_lock<std::mutex> lock(hdl->mtx_);
    hdl->running_ = true;
    while (hdl->running_) {
        if (hdl->msgQ_.empty()) {
            hdl->cv_.wait(lock); // wait for task or exit signal
        } else {
            auto mission = hdl->msgQ_.front();
            hdl->msgQ_.pop();
            lock.unlock();
            mission->Exec();
            delete mission;
            lock.lock();
        }
    }
    /* Exec all tasks before exit */
    while (!hdl->msgQ_.empty()) {
        auto mission = hdl->msgQ_.front();
        hdl->msgQ_.pop();
        lock.unlock();
        mission->Exec();
        delete mission;
        lock.lock();
    }
}
} // namespace Media
} // namespace OHOS