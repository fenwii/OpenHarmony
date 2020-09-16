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

#ifndef OHOS_ACELITE_SAMPLE_MODULE_H
#define OHOS_ACELITE_SAMPLE_MODULE_H

#include "acelite_config.h"
#ifdef ENABLE_MODULE_REQUIRE_TEST

#include "jsi.h"
#include "non_copyable.h"

namespace OHOS {
namespace ACELite {
class SampleModule final : public MemoryHeap {
public:
    ACE_DISALLOW_COPY_AND_MOVE(SampleModule);
    SampleModule() {}
    ~SampleModule() {}
    static JSIValue TestCallFunc(const JSIValue thisVal, const JSIValue *args, uint8_t argsNum);
    static JSIValue TestCallback(const JSIValue thisVal, const JSIValue *args, uint8_t argsNum);
    static JSIValue TestStandardCallback(const JSIValue thisVal, const JSIValue *args, uint8_t argsNum);
    static JSIValue TestCallbackWithArgs(const JSIValue thisVal, const JSIValue *args, uint8_t argsNum);
    static JSIValue TestStandardCallbackWithArgs(const JSIValue thisVal, const JSIValue *args, uint8_t argsNum);
    static JSIValue TestGeneralFunc(const JSIValue thisVal, const JSIValue *args, uint8_t argsNum);
    static JSIValue Getter(const JSIValue thisVal, const JSIValue *args, uint8_t argsNum);
    static JSIValue Setter(const JSIValue thisVal, const JSIValue *args, uint8_t argsNum);
    static void OnDestroy();
    static void OnTerminate();
private:
    static int8_t counter_; // used for js descriptor test
};

void InitSampleModule(JSIValue exports)
{
    JSI::SetModuleAPI(exports, "testCallFunc", SampleModule::TestCallFunc);
    JSI::SetModuleAPI(exports, "testCallback", SampleModule::TestCallback);
    JSI::SetModuleAPI(exports, "testStandardCallback", SampleModule::TestStandardCallback);
    JSI::SetModuleAPI(exports, "testCallbackWithArgs", SampleModule::TestCallbackWithArgs);
    JSI::SetModuleAPI(exports, "testStandardCallbackWithArgs", SampleModule::TestStandardCallbackWithArgs);
    JSI::SetModuleAPI(exports, "testGeneralFunc", SampleModule::TestGeneralFunc);
    JSI::SetOnDestroy(exports, SampleModule::OnDestroy);
    JSI::SetOnTerminate(exports, SampleModule::OnTerminate);
}
} // namespace ACELite
} // namespace OHOS

#endif // ENABLE_MODULE_REQUIRE_TEST

#endif // OHOS_ACELITE_SAMPLE_MODULE_H
