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

#ifndef OHOS_ACELITE_FATAL_HANDLER_H
#define OHOS_ACELITE_FATAL_HANDLER_H

#include "component.h"
#include "list.h"
#include "non_copyable.h"

namespace OHOS {
namespace ACELite {
class FatalHandler final : public MemoryHeap {
public:
    ACE_DISALLOW_COPY_AND_MOVE(FatalHandler);
    static FatalHandler& GetInstance();
    const char* GetErrorStr(int errorCode) const;
    void RegisterFatalHandler() const;
    void SetFatalError(int errorCode);
    void HandleFatalError(int errorCode);
    void CleanUpFatalResource();
    bool IsJSRuntimeFatal() const;
    bool IsJSHeapOverflow() const;
    bool IsFatalErrorHitted() const;
    bool IsFatalErrorHandling() const;
    bool IsFatalErrorHandleDone() const;
    void AttachComponentNode(Component* component);
    void DetachComponentNode(const Component* component);
    void SetTEHandlingFlag(bool flag);
    bool IsTEHandling() const;
    void ResetRendering();
    void SetExitingFlag(bool flag);
    bool IsAppExiting() const;
    // define all fatal error below, please note the jerry fatal defines, avoid conflicts
    static const int ERR_INVALID = 0;
    static const int ERR_NATIVE_OUT_OF_MEMORY = 200;
    static const int ERR_READ_FWK_FILE_FAILED = 201;
    static const int ERR_EVAL_FWK_FAILED = 202;
    static const int ERR_READ_JS_FILE_FAILED = 203;
    static const int ERR_EVAL_JS_FAILED = 204;

private:
    FatalHandler()
        : componentNodes_(),
          fatalErrorCode_(0),
          isRecycling_(false),
          isFatalHandled_(false),
          isTEHandling_(false),
          isExiting_(false) {}
    ~FatalHandler() {}
    bool IsErrorSupported(int errorCode) const;
    void RecycleComponents();
    List<Component *> componentNodes_;
    int fatalErrorCode_;
    bool isRecycling_;
    bool isFatalHandled_;
    bool isTEHandling_;
    bool isExiting_;
};
} // namespace ACELite
} // namespace OHOS
#endif // OHOS_ACELITE_FATAL_HANDLER_H