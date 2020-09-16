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

#include "perm_module.h"

#include "log.h"
#include "pms_interface.h"

namespace OHOS {
namespace ACELite {
JSIValue PermModule::CheckSelfPermission(const JSIValue thisVal, const JSIValue *args, uint8_t argsNum)
{
    JSIValue undefValue = JSI::CreateUndefined();
    if ((args == nullptr) || argsNum == 0 || JSI::ValueIsUndefined(args[0])) {
        return undefValue;
    }

    JSIValue success = JSI::GetNamedProperty(args[0], CB_SUCCESS);
    JSIValue fail = JSI::GetNamedProperty(args[0], CB_FAIL);
    JSIValue complete = JSI::GetNamedProperty(args[0], CB_COMPLETE);
    char *permission = JSI::GetStringProperty(args[0], "permission");

    int ret = CheckPermission(0, permission);
    JSIValue code = JSI::CreateNumber(ret);
    JSIValue argv[ARGC_ONE] = { code };
    if (ret != GRANTED || ret != NOT_GRANTED) {
        HILOG_ERROR(HILOG_MODULE_ACE, "Check permission failed.");
        JSI::CallFunction(fail, thisVal, argv, ARGC_ONE);
        goto RELEASE;
    }

    JSI::CallFunction(success, thisVal, argv, ARGC_ONE);

RELEASE:
    JSI::ReleaseString(permission);
    JSI::CallFunction(complete, thisVal, nullptr, 0);
    JSI::ReleaseValueList(success, fail, complete, code, ARGS_END);

    return undefValue;
}

JSIValue PermModule::RequestSelfPermission(const JSIValue thisVal, const JSIValue *args, uint8_t argsNum)
{
    JSIValue undefValue = JSI::CreateUndefined();
    if ((args == nullptr) || argsNum == 0 || JSI::ValueIsUndefined(args[0])) {
        return undefValue;
    }

    JSIValue success = JSI::GetNamedProperty(args[0], CB_SUCCESS);
    JSIValue fail = JSI::GetNamedProperty(args[0], CB_FAIL);
    JSIValue complete = JSI::GetNamedProperty(args[0], CB_COMPLETE);
    char *permission = JSI::GetStringProperty(args[0], "permission");

    int ret = RequestPermission(0, permission);
    JSIValue code = JSI::CreateNumber(ret);
    JSIValue argv[ARGC_ONE] = { code };
    if (ret != GRANTED || ret != NOT_GRANTED) {
        HILOG_ERROR(HILOG_MODULE_ACE, "Check permission failed.");
        JSI::CallFunction(fail, thisVal, argv, ARGC_ONE);
        goto RELEASE;
    }

    JSI::CallFunction(success, thisVal, argv, ARGC_ONE);

RELEASE:
    JSI::ReleaseString(permission);
    JSI::CallFunction(complete, thisVal, nullptr, 0);
    JSI::ReleaseValueList(success, fail, complete, code, ARGS_END);

    return undefValue;
}
} // namespace ACELite
} // namespace OHOS