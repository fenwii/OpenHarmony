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

#include "sample_module.h"
#ifdef ENABLE_MODULE_REQUIRE_TEST
#if (!defined _WIN32) && (!defined _WIN64)
#include "js_async_work.h"
#endif
#include "ace_log.h"

namespace OHOS {
namespace ACELite {
JSIValue SampleModule::TestCallFunc(const JSIValue thisVal, const JSIValue *args, uint8_t argsNum)
{
    return JSI::CreateUndefined();
}

JSIValue SampleModule::TestCallback(const JSIValue thisVal, const JSIValue *args, uint8_t argsNum)
{
    JSIValue undefValue = JSI::CreateUndefined();
    if ((args == nullptr) || (argsNum == 0) || JSI::ValueIsUndefined(args[0])) {
        return undefValue;
    }

    JSIValue callback = JSI::GetNamedProperty(args[0], CB_CALLBACK);
    JSIValue result = JSI::CreateObject();
    const double defaultVal = 111;
    JSI::SetNumberProperty(result, "x", defaultVal);
    JSIValue argv[ARGC_ONE] = {result};
    JSI::CallFunction(callback, thisVal, argv, ARGC_ONE);
    JSI::ReleaseValueList(callback, result);
    return undefValue;
}

JSIValue SampleModule::TestStandardCallback(const JSIValue thisVal, const JSIValue *args, uint8_t argsNum)
{
    JSIValue undefValue = JSI::CreateUndefined();
    if ((args == nullptr) || (argsNum == 0) || JSI::ValueIsUndefined(args[0])) {
        return undefValue;
    }
    JSIValue success = JSI::GetNamedProperty(args[0], CB_SUCCESS);
    JSIValue fail = JSI::GetNamedProperty(args[0], CB_FAIL);
    JSIValue complete = JSI::GetNamedProperty(args[0], CB_COMPLETE);
    // callbacks can be invoked on demand
    JSI::CallFunction(success, thisVal, nullptr, 0);
    JSI::CallFunction(complete, thisVal, nullptr, 0);
    JSI::ReleaseValueList(success, fail, complete);
    return undefValue;
}

#if (!defined _WIN32) && (!defined _WIN64)
struct AsyncParams : public MemoryHeap {
    AsyncParams() : result(nullptr), callback(nullptr), context(nullptr) {}

    JSIValue result;
    JSIValue callback;
    JSIValue context;
};

static void Execute(void *data)
{
    AsyncParams *params = static_cast<AsyncParams *>(data);
    if (params == nullptr) {
        return;
    }
    JSIValue callback = params->callback;
    JSIValue result = params->result;
    JSIValue context = params->context;

    JSI::CallFunction(callback, context, &result, ARGC_ONE);
    JSI::ReleaseValueList(callback, result, context);
    delete params;
    params = nullptr;
}
#endif

JSIValue SampleModule::TestCallbackWithArgs(const JSIValue thisVal, const JSIValue *args, uint8_t argsNum)
{
    JSIValue undefValue = JSI::CreateUndefined();
    if ((args == nullptr) || (argsNum == 0) || JSI::ValueIsUndefined(args[0])) {
        return undefValue;
    }
    JSIValue callback = JSI::GetNamedProperty(args[0], CB_CALLBACK);
    double num = JSI::GetNumberProperty(args[0], "param1");
    char *str = JSI::GetStringProperty(args[0], "param2");

    JSIValue result = JSI::CreateObject();
    JSI::SetNumberProperty(result, "param1", num);
    if (str != nullptr) {
        JSI::SetStringProperty(result, "param2", str);
        JSI::ReleaseString(str);
    }
#if (!defined _WIN32) && (!defined _WIN64)
    AsyncParams *params = new AsyncParams();
    if (params == nullptr) {
        return undefValue;
    }
    params->result = result;
    params->callback = callback;
    params->context = JSI::AcquireValue(thisVal);
    if (!(JsAsyncWork::DispatchAsyncWork(Execute, static_cast<void *>(params)))) {
        JSI::ReleaseValueList(result, callback, params->context);
        delete params;
        params = nullptr;
    }
    return undefValue;
#else
    JSI::CallFunction(callback, thisVal, &result, ARGC_ONE);
    JSI::ReleaseValueList(result, callback);
    return undefValue;
#endif
}

JSIValue SampleModule::TestStandardCallbackWithArgs(const JSIValue thisVal, const JSIValue *args, uint8_t argsNum)
{
    JSIValue undefValue = JSI::CreateUndefined();
    if ((args == nullptr) || (argsNum == 0) || JSI::ValueIsUndefined(args[0])) {
        return undefValue;
    }
    JSIValue success = JSI::GetNamedProperty(args[0], CB_SUCCESS);
    JSIValue fail = JSI::GetNamedProperty(args[0], CB_FAIL);
    JSIValue complete = JSI::GetNamedProperty(args[0], CB_COMPLETE);
    double num = JSI::GetNumberProperty(args[0], "param1");
    char *str = JSI::GetStringProperty(args[0], "param2");

    JSIValue result = JSI::CreateObject();
    JSI::SetNumberProperty(result, "param1", num);
    if (str != nullptr) {
        JSI::SetStringProperty(result, "param2", str);
        JSI::ReleaseString(str);
    }

    // callbacks can be invoked on demand
    JSIValue argv[ARGC_ONE] = {result};
    JSI::CallFunction(success, thisVal, argv, ARGC_ONE);
    JSI::CallFunction(fail, thisVal, argv, ARGC_ONE);
    JSI::CallFunction(complete, thisVal, argv, ARGC_ONE);
    JSI::ReleaseValueList(success, fail, complete, result);
    return undefValue;
}

JSIValue SampleModule::TestGeneralFunc(const JSIValue thisVal, const JSIValue *args, uint8_t argsNum)
{
    JSIValue result;
    if ((args == nullptr) || (argsNum < ARGC_TWO)) {
        return JSI::CreateUndefined();
    }

    char *param1 = JSI::ValueToString(args[0]);
    if (param1 == nullptr) {
        return JSI::CreateUndefined();
    }
    double param2 = JSI::ValueToNumber(args[ARGC_ONE]);
    result = JSI::CreateObject();
    JSI::SetStringProperty(result, "prop1", param1);
    JSI::SetNumberProperty(result, "prop2", param2);
    JSI::ReleaseString(param1);

    JSPropertyDescriptor desc;
    const char * const propName = "prop3";
    desc.getter = Getter;
    desc.setter = Setter;
    JSI::DefineNamedProperty(result, propName, desc);
    return result;
}

int8_t SampleModule::counter_ = 0;

JSIValue SampleModule::Setter(const JSIValue thisVal, const JSIValue *args, uint8_t argsNum)
{
    if ((args == nullptr) || (argsNum == 0) || JSI::ValueIsUndefined(args[0])) {
        return JSI::CreateUndefined();
    }
    double newValue = JSI::ValueToNumber(args[0]);
    counter_ = (int8_t)newValue;

    HILOG_DEBUG(HILOG_MODULE_ACE, "SampleModule: Setter called, setting: %d", counter_);
    return JSI::CreateUndefined();
}

JSIValue SampleModule::Getter(const JSIValue thisVal, const JSIValue *args, uint8_t argsNum)
{
    counter_++;
    HILOG_DEBUG(HILOG_MODULE_ACE, "SampleModule: Getter called, returning: %d", counter_);
    return JSI::CreateNumber(counter_);
}

void SampleModule::OnDestroy()
{
    HILOG_DEBUG(HILOG_MODULE_ACE, "SampleModule: OnDestroy called");
}

void SampleModule::OnTerminate()
{
    HILOG_DEBUG(HILOG_MODULE_ACE, "SampleModule: OnTerminate called");
}
} // namespace ACELite
} // namespace OHOS

#endif // ENABLE_MODULE_REQUIRE_TEST
