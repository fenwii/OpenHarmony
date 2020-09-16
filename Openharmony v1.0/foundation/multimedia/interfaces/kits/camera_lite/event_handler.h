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

#ifndef OHOS_EVENTHANDLER_H
#define OHOS_EVENTHANDLER_H

#include <thread>
#include <mutex>
#include <queue>
#include <condition_variable>

namespace OHOS {
namespace Media {
class EventHandler {
public:
    EventHandler();
    virtual ~EventHandler();
    /* After construct the event handler, user should check whether the thread is running before post or
     * destroy this handler */
    bool IsRunning();

    template<typename F>
    void Post(const F &f)
    {
        auto task = new PostTask<F>(f);
        std::unique_lock<std::mutex> lock(mtx_);
        msgQ_.emplace(task);
        cv_.notify_all();
    }

private:
    struct EventObj {
        EventObj() = default;
        virtual ~EventObj(){};
        virtual void Exec(){};
    };

    std::queue<EventObj *> msgQ_;
    std::thread *hdlThrd_;
    bool running_;
    std::condition_variable cv_;
    std::mutex mtx_;

    template<typename F>
    struct PostTask : public EventObj {
        PostTask(const F &f) : f_(f) {}
        const F f_;
        void Exec() override
        {
            f_();
        }
    };

    static void EventDispatch(EventHandler *hdl);
};
} // namespace Media
} // namespace OHOS

#endif // OHOS_EVENTHANDLER_H
