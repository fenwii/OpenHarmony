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

#include "nativeapi_common.h"
#include "jsi/jsi_types.h"
#include "nativeapi_config.h"

namespace OHOS {
namespace ACELite {
void NativeapiCommon::FailCallBack(const JSIValue thisVal, const JSIValue args, int ret)
{
    if (JSI::ValueIsUndefined(args)) {
        return;
    }
    JSIValue errInfo;
    if (ret == ERROR_CODE_IO) {
        errInfo = JSI::CreateString(ERR_IO_EXCEPTION);
        ret = (-ERROR_CODE_IO);
    } else if ((ret == ERROR_CODE_PARAM) || (ret == ERROR_DIR_NOT_EMPTY)) {
        errInfo = JSI::CreateString(ERR_ILLEGAL_PARAM);
        ret = (-ERROR_CODE_PARAM);
    } else if (ret == ERROR_FR_NO_FILE) {
        errInfo = JSI::CreateString(ERR_NO_FILE);
        ret = (-ERROR_CODE_NO_FILE);
    } else if (ret == ERROR_CODE_READ_TOO_LONG) {
        errInfo = JSI::CreateString(ERR_READ_TOO_LONG);
        ret = (-ERROR_CODE_READ_TOO_LONG);
    } else {
        errInfo = JSI::CreateString(ERR_GENERAL);
        ret = (-ERROR_CODE_GENERAL);
    }
    JSIValue errCode = JSI::CreateNumber(ret);
    JSIValue fail = JSI::GetNamedProperty(args, CB_FAIL);
    JSIValue complete = JSI::GetNamedProperty(args, CB_COMPLETE);
    JSIValue argv[ARGC_TWO] = {errInfo, errCode};
    if (!JSI::ValueIsUndefined(fail)) {
        JSI::CallFunction(fail, thisVal, argv, ARGC_TWO);
    }
    if (!JSI::ValueIsUndefined(complete)) {
        JSI::CallFunction(complete, thisVal, nullptr, 0);
    }
    JSI::ReleaseValueList(fail, complete, errInfo, errCode, ARGS_END);
}

void NativeapiCommon::SuccessCallBack(const JSIValue thisVal, const JSIValue args, JSIValue jsiValue)
{
    if (JSI::ValueIsUndefined(args)) {
        return;
    }
    JSIValue success = JSI::GetNamedProperty(args, CB_SUCCESS);
    JSIValue complete = JSI::GetNamedProperty(args, CB_COMPLETE);
    if (!JSI::ValueIsUndefined(success)) {
        if (JSI::ValueIsUndefined(jsiValue)) {
            JSI::CallFunction(success, thisVal, nullptr, 0);
        } else {
            JSI::CallFunction(success, thisVal, &jsiValue, ARGC_ONE);
        }
    }
    if (!JSI::ValueIsUndefined(complete)) {
        JSI::CallFunction(complete, thisVal, nullptr, 0);
    }
    JSI::ReleaseValueList(success, complete, ARGS_END);
}

bool NativeapiCommon::IsValidJSIValue(const JSIValue* args, uint8_t argsNum)
{
    if ((args == nullptr) || (argsNum == 0) || JSI::ValueIsUndefined(args[0])) {
        return false;
    }
    return true;
}
}
}
