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

#include "nativeapi_deviceinfo.h"
#include "js_async_work.h"
#include "nativeapi_common.h"
#include "nativeapi_config.h"
#include "parameter.h"
#include "screen.h"

namespace OHOS {
namespace ACELite {
namespace {
JSIValue ExecuteAsyncWork(const JSIValue thisVal, const JSIValue* args,
    uint8_t argsNum, AsyncWorkHandler ExecuteFunc, bool flag = false)
{
    JSIValue undefValue = JSI::CreateUndefined();
    if (!NativeapiCommon::IsValidJSIValue(args, argsNum)) {
        return undefValue;
    }
    FuncParams* params = new FuncParams();
    if (params == nullptr) {
        return undefValue;
    }
    params->thisVal = JSI::AcquireValue(thisVal);
    params->args = JSI::AcquireValue(args[0]);
    params->flag = flag;
    JsAsyncWork::DispatchAsyncWork(ExecuteFunc, reinterpret_cast<void *>(params));
    return undefValue;
}

void ExecuteGetInfo(void* data)
{
    FuncParams* params = reinterpret_cast<FuncParams *>(data);
    if (params == nullptr) {
        return;
    }
    JSIValue args = params->args;
    JSIValue thisVal = params->thisVal;
    char* brand =  GetBrand();
    if (brand == nullptr) {
        NativeapiCommon::FailCallBack(args, thisVal, ERROR_CODE_GENERAL);
        JSI::ReleaseValueList(args, thisVal, ARGS_END);
        delete params;
        return;
    }
    char* manufacture = GetManufacture();
    if (manufacture == nullptr) {
        free(brand);
        NativeapiCommon::FailCallBack(args, thisVal, ERROR_CODE_GENERAL);
        JSI::ReleaseValueList(args, thisVal, ARGS_END);
        delete params;
        return;
    }
    char* model = GetProductModel();
    if (model == nullptr) {
        free(brand);
        free(manufacture);
        NativeapiCommon::FailCallBack(args, thisVal, ERROR_CODE_GENERAL);
        JSI::ReleaseValueList(args, thisVal, ARGS_END);
        delete params;
        return;
    }
    JSIValue result = JSI::CreateObject();
    JSI::SetStringProperty(result, "brand", brand);
    JSI::SetStringProperty(result, "manufacturer", manufacture);
    JSI::SetStringProperty(result, "model", model);
    JSI::SetStringProperty(result, "product", model);
    Screen &screen = Screen::GetInstance();
    JSI::SetNumberProperty(result, "windowWidth", (double)screen.GetWidth());
    JSI::SetNumberProperty(result, "windowHeight", (double)screen.GetHeight());
    free(brand);
    free(manufacture);
    free(model);
    NativeapiCommon::SuccessCallBack(thisVal, args, result);
    JSI::ReleaseValueList(args, thisVal, result, ARGS_END);
    delete params;
    params = nullptr;
}
}

void InitDeviceModule(JSIValue exports)
{
    JSI::SetModuleAPI(exports, "getInfo", NativeapiDeviceInfo::GetDeviceInfo);
}

JSIValue NativeapiDeviceInfo::GetDeviceInfo(const JSIValue thisVal, const JSIValue* args, uint8_t argsNum)
{
    return ExecuteAsyncWork(thisVal, args, argsNum, ExecuteGetInfo);
}
} // ACELite
} // OHOS
