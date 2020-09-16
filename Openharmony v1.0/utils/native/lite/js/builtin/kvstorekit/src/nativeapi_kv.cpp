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

#include "nativeapi_kv.h"
#include <securec.h>
#include "ability_env.h"
#include "js_async_work.h"
#include "nativeapi_common.h"
#include "nativeapi_config.h"
#include "nativeapi_kv_impl.h"

namespace OHOS {
namespace ACELite {
namespace {
char g_kvFullPath[FILE_NAME_MAX_LEN + 1] = {0};

bool IsValidKey(const char *key)
{
    if ((key == nullptr) || !strlen(key) || (strlen(key) > KEY_MAX_LEN)) {
        return false;
    }
    if (strpbrk(key, "/\\\"*+,:;<=>\?[]|\x7F")) {
        return false;
    }
    return true;
}

int GetFullPath(const char* dataPath, const char* key)
{
    if (!IsValidKey(key) || (dataPath == nullptr)) {
        return ERROR_CODE_PARAM;
    }
    if (memset_s(g_kvFullPath, sizeof(g_kvFullPath), 0x0, sizeof(g_kvFullPath)) != EOK) {
        return ERROR_CODE_GENERAL;
    }
    if (sprintf_s(g_kvFullPath, sizeof(g_kvFullPath), "%s/%s/%s", dataPath, DEFAULT_FOLDER_PATH, key) < 0) {
        return ERROR_CODE_GENERAL;
    }
    return NATIVE_SUCCESS;
}

void GetDefault(const JSIValue thisVal, const JSIValue args)
{
    char *defaultValue = JSI::GetStringProperty(args, DEFAULT);
    JSIValue result;
    if (defaultValue == nullptr) {
        result = JSI::CreateString("");
    } else {
        result = JSI::CreateString(defaultValue);
    }
    JSI::ReleaseString(defaultValue);
    NativeapiCommon::SuccessCallBack(thisVal, args, result);
    JSI::ReleaseValue(result);
}

int GetValueInner(const char* dataPath, const char* key, char* value)
{
    int ret = GetFullPath(dataPath, key);
    if (ret != NATIVE_SUCCESS) {
        return ret;
    }
    ret = GetValue(g_kvFullPath, value);
    return ret;
}

int SetValueInner(const char* dataPath, const char* key, const char* value)
{
    int ret = GetFullPath(dataPath, key);
    if (ret != NATIVE_SUCCESS) {
        return ret;
    }
    ret = SetValue(g_kvFullPath, value);
    return ret;
}

int DeleteValueInner(const char* dataPath, const char* key)
{
    int ret = GetFullPath(dataPath, key);
    if (ret != NATIVE_SUCCESS) {
        return ret;
    }
    ret = DeleteValue(g_kvFullPath);
    return ret;
}

JSIValue ExecuteAsyncWork(const JSIValue thisVal, const JSIValue* args,
    uint8_t argsNum, AsyncWorkHandler ExecuteFunc, bool flag)
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

void ExecuteGet(void* data)
{
    FuncParams* params = reinterpret_cast<FuncParams *>(data);
    if (params == nullptr) {
        return;
    }
    JSIValue args = params->args;
    JSIValue thisVal = params->thisVal;
    char* key = JSI::GetStringProperty(args, KV_KEY);
    const char* dataPath = GetDataPath();
    JSIValue result = JSI::CreateUndefined();
    int ret = ERROR_CODE_GENERAL;
    char *value = reinterpret_cast<char *>(malloc(VALUE_MAX_LEN + 1));
    if (value == nullptr) {
        NativeapiCommon::FailCallBack(thisVal, args, ret);
        goto EXIT;
    }
    ret = InitKv(dataPath);
    if (ret != NATIVE_SUCCESS) {
        NativeapiCommon::FailCallBack(thisVal, args, ret);
        goto EXIT;
    }
    ret = GetValueInner(dataPath, key, value);
    if (ret == ERROR_FR_NO_FILE) {
        GetDefault(thisVal, args);
        goto EXIT;
    }
    if (ret != NATIVE_SUCCESS) {
        NativeapiCommon::FailCallBack(thisVal, args, ret);
        goto EXIT;
    }
    result = JSI::CreateString(value);
    NativeapiCommon::SuccessCallBack(thisVal, args, result);
EXIT:
    free(value);
    JSI::ReleaseString(key);
    JSI::ReleaseValueList(args, thisVal, result, ARGS_END);
    delete params;
}

void ExecuteSet(void* data)
{
    FuncParams* params = reinterpret_cast<FuncParams *>(data);
    if (params == nullptr) {
        return;
    }
    JSIValue args = params->args;
    JSIValue thisVal = params->thisVal;
    char* key = JSI::GetStringProperty(args, KV_KEY);
    char* value = JSI::GetStringProperty(args, KV_VALUE);
    const char* dataPath = GetDataPath();
    int ret = InitKv(dataPath);
    if (ret != NATIVE_SUCCESS) {
        NativeapiCommon::FailCallBack(thisVal, args, ret);
        goto EXIT;
    }
    if ((key == nullptr) || !strlen(key)) {
        NativeapiCommon::FailCallBack(thisVal, args, ERROR_CODE_PARAM);
        goto EXIT;
    }
    if ((value == nullptr) || !strlen(value)) {
        DeleteValueInner(dataPath, key);
        NativeapiCommon::SuccessCallBack(thisVal, args, JSI::CreateUndefined());
        goto EXIT;
    }
    ret = SetValueInner(dataPath, key, value);
    if (ret != NATIVE_SUCCESS) {
        NativeapiCommon::FailCallBack(thisVal, args, ret);
        goto EXIT;
    }
    NativeapiCommon::SuccessCallBack(thisVal, args, JSI::CreateUndefined());
EXIT:
    JSI::ReleaseString(key);
    JSI::ReleaseString(value);
    JSI::ReleaseValueList(args, thisVal, ARGS_END);
    delete params;
}

void ExecuteDelete(void* data)
{
    FuncParams* params = reinterpret_cast<FuncParams *>(data);
    if (params == nullptr) {
        return;
    }
    JSIValue args = params->args;
    JSIValue thisVal = params->thisVal;
    const char* dataPath = GetDataPath();
    int ret = InitKv(dataPath);
    if (ret != NATIVE_SUCCESS) {
        NativeapiCommon::FailCallBack(thisVal, args, ret);
        JSI::ReleaseValueList(args, thisVal, ARGS_END);
        delete params;
        return;
    }
    char* key = JSI::GetStringProperty(args, KV_KEY);
    ret = DeleteValueInner(dataPath, key);
    JSI::ReleaseString(key);
    if ((ret < 0) && (ret != ERROR_FR_NO_FILE)) {
        NativeapiCommon::FailCallBack(thisVal, args, ret);
        JSI::ReleaseValueList(args, thisVal, ARGS_END);
        delete params;
        return;
    }
    NativeapiCommon::SuccessCallBack(thisVal, args, JSI::CreateUndefined());
    JSI::ReleaseValueList(args, thisVal, ARGS_END);
    delete params;
}

void ExecuteClear(void* data)
{
    FuncParams* params = reinterpret_cast<FuncParams *>(data);
    if (params == nullptr) {
        return;
    }
    JSIValue args = params->args;
    JSIValue thisVal = params->thisVal;
    const char* dataPath = GetDataPath();
    int ret = InitKv(dataPath);
    if (ret != NATIVE_SUCCESS) {
        NativeapiCommon::FailCallBack(thisVal, args, ret);
        JSI::ReleaseValueList(args, thisVal, ARGS_END);
        delete params;
        return;
    }
    ret = ClearKVStore(dataPath);
    if (ret != NATIVE_SUCCESS) {
        NativeapiCommon::FailCallBack(thisVal, args, ret);
        JSI::ReleaseValueList(args, thisVal, ARGS_END);
        delete params;
        return;
    }
    NativeapiCommon::SuccessCallBack(thisVal, args, JSI::CreateUndefined());
    JSI::ReleaseValueList(args, thisVal, ARGS_END);
    delete params;
}
}

void InitNativeApiKv(JSIValue exports)
{
    JSI::SetModuleAPI(exports, "get", NativeapiKv::Get);
    JSI::SetModuleAPI(exports, "set", NativeapiKv::Set);
    JSI::SetModuleAPI(exports, "delete", NativeapiKv::Delete);
    JSI::SetModuleAPI(exports, "clear", NativeapiKv::Clear);
}

JSIValue NativeapiKv::Get(const JSIValue thisVal, const JSIValue* args, uint8_t argsNum)
{
    return ExecuteAsyncWork(thisVal, args, argsNum, ExecuteGet, false);
}

JSIValue NativeapiKv::Set(const JSIValue thisVal, const JSIValue* args, uint8_t argsNum)
{
    return ExecuteAsyncWork(thisVal, args, argsNum, ExecuteSet, false);
}

JSIValue NativeapiKv::Delete(const JSIValue thisVal, const JSIValue* args, uint8_t argsNum)
{
    return ExecuteAsyncWork(thisVal, args, argsNum, ExecuteDelete, false);
}

JSIValue NativeapiKv::Clear(const JSIValue thisVal, const JSIValue* args, uint8_t argsNum)
{
    JSIValue undefValue = JSI::CreateUndefined();
    FuncParams* params = new FuncParams();
    if (params == nullptr) {
        return undefValue;
    }
    params->thisVal = JSI::AcquireValue(thisVal);
    if (NativeapiCommon::IsValidJSIValue(args, argsNum)) {
        params->args = JSI::AcquireValue(args[0]);
    }
    JsAsyncWork::DispatchAsyncWork(reinterpret_cast<AsyncWorkHandler>(ExecuteClear), reinterpret_cast<void *>(params));
    return undefValue;
}
} // ACELite
} // OHOS
