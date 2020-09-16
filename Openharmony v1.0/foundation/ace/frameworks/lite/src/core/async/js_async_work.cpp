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
#include "js_async_work.h"
#include "ace_log.h"
#include "fatal_handler.h"
#include "js_fwk_common.h"
#if (defined(__LINUX__) || defined(__LITEOS__))
#include "ace_ability.h"
#endif

namespace OHOS {
namespace ACELite {
// Initialization of static variables
QueueHandler JsAsyncWork::appQueuehandler_ = nullptr;

void JsAsyncWork::SetAppQueueHandler(const QueueHandler handler)
{
    appQueuehandler_ = handler;
}

bool JsAsyncWork::DispatchToLoop(AbilityMsgId msgId, void *data)
{
    if ((appQueuehandler_ == nullptr) || (msgId >= MSG_ID_MAX) ||
        (FatalHandler::GetInstance().IsFatalErrorHitted()) ||
        (FatalHandler::GetInstance().IsAppExiting())) {
        // For the cases fatal error handling or the JS task is exiting, do not allow any async work dispatching,
        // as the messages after DESTROY will never be handled.
        return false;
    }

    AbilityInnerMsg innerMsg;
    innerMsg.msgId = msgId;
    innerMsg.data = data;
    int8_t ret = MessageQueueUtils::PutMessage(appQueuehandler_, static_cast<void *>(&innerMsg), 0);
    return (ret == MSGQ_OK);
}

bool JsAsyncWork::DispatchAsyncWork(AsyncWorkHandler workHandler, void *data)
{
    return DispatchAsyncWorkInner(workHandler, nullptr, data);
}

bool JsAsyncWork::DispatchAsyncWork(AsyncHandler handler, void *data)
{
    return DispatchAsyncWorkInner(nullptr, handler, data);
}

bool JsAsyncWork::DispatchAsyncWorkInner(AsyncWorkHandler workHandler, AsyncHandler handler, void *data)
{
    if (((workHandler == nullptr) && (handler == nullptr)) || (FatalHandler::GetInstance().IsFatalErrorHitted())) {
        HILOG_ERROR(HILOG_MODULE_ACE, "JsAsyncWork:DispatchAsyncWork parameters invalid or fatal error!");
        return false;
    }

#if (defined(__LINUX__) || defined(__LITEOS__))
    if (workHandler != nullptr) {
        auto task1 = [workHandler, data]() {
            workHandler(data);
        };
        return AceAbility::PostUITask(task1);
    }
    if (handler != nullptr) {
        auto task2 = [handler, data]() {
            handler(data, ERR_OK);
        };
        return AceAbility::PostUITask(task2);
    }
    return false;
#else
    AsyncWork* asyncWork = new AsyncWork();
    if (asyncWork == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "JsAsyncWork:DispatchAsyncWork create async work failed!");
        return false;
    }
    asyncWork->workHandler = workHandler;
    asyncWork->handler = handler;
    asyncWork->data = data;

    bool ret = DispatchToLoop(ASYNCWORK, static_cast<void *>(asyncWork));
    if (!ret) {
        HILOG_ERROR(HILOG_MODULE_ACE, "JsAsyncWork:DispatchAsyncWork failed!, handler[%p]", asyncWork->workHandler);
        delete(asyncWork);
        asyncWork = nullptr;
    }
    return ret;
#endif
}

void JsAsyncWork::ExecuteAsyncWork(AsyncWork *&asyncWork, int8_t statusCode)
{
    if (asyncWork == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "JsAsyncWork:ExecuteAsyncWork parameters invalid!");
        return;
    }
    AsyncWorkHandler workHandler = asyncWork->workHandler;
    if (workHandler != nullptr) {
        workHandler(asyncWork->data);
    }
    AsyncHandler handler = asyncWork->handler;
    if (handler != nullptr) {
        handler(asyncWork->data, statusCode);
    }
    delete asyncWork;
    asyncWork = nullptr;
}
} // namespace ACELite
} // namespace OHOS
