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

#include "cipher_module.h"
#include "cipher.h"
#include "log.h"
#include "securec.h"

namespace OHOS {
namespace ACELite {
JSIValue CipherModule::Rsa(const JSIValue thisVal, const JSIValue *args, uint8_t argsNum)
{
    JSIValue undefValue = JSI::CreateUndefined();
    if ((args == nullptr) || argsNum == 0 || JSI::ValueIsUndefined(args[0])) {
        return undefValue;
    }

    JSIValue success = JSI::GetNamedProperty(args[0], CB_SUCCESS);
    JSIValue fail = JSI::GetNamedProperty(args[0], CB_FAIL);
    JSIValue complete = JSI::GetNamedProperty(args[0], CB_COMPLETE);
    char *strAction = JSI::GetStringProperty(args[0], "action");
    char *strKey = JSI::GetStringProperty(args[0], "key");
    char *strText = JSI::GetStringProperty(args[0], "text");
    char *strTransformation = JSI::GetStringProperty(args[0], "transformation");
    JSIValue code = JSI::CreateNumber(ERR_CODE);
    JSIValue data = JSI::CreateString("System error");
    JSIValue argvFail[ARGC_TWO] = { data, code };
    JSIValue result = JSI::CreateObject();
    JSIValue argvSuccess[ARGC_ONE] = { result };
    int ret = ERROR_CODE_GENERAL;
    RsaData textIn = { 0 };
    RsaData textOut = { 0 };
    RsaKeyData rsaKey = { 0 };
    if ((strKey == nullptr) || (strText == nullptr)) {
        JSI::CallFunction(fail, thisVal, argvFail, ARGC_TWO);
        goto RELEASE;
    }
    rsaKey.key = strKey;
    rsaKey.keyLen = strlen(strKey);
    rsaKey.trans = strTransformation;
    rsaKey.action = strAction;
    textIn.data = strText;
    textIn.length = strlen(strText);

    ret = RsaCrypt(&rsaKey, &textIn, &textOut);
    if ((ret != ERROR_SUCCESS) || (textOut.length == 0)) {
        HILOG_ERROR(HILOG_MODULE_ACE, "RsaCrypt failed.");
        JSI::CallFunction(fail, thisVal, argvFail, ARGC_TWO);
        goto RELEASE;
    }
    textOut.data = static_cast<char *>(ace_malloc(textOut.length));
    if (textOut.data == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "ace malloc failed.");
        JSI::CallFunction(fail, thisVal, argvFail, ARGC_TWO);
        goto RELEASE;
    }
    ret = memset_s(textOut.data, textOut.length, 0, textOut.length);
    if (ret) {
        HILOG_ERROR(HILOG_MODULE_ACE, "memset failed.");
    }
    ret = RsaCrypt(&rsaKey, &textIn, &textOut);
    if (ret != ERROR_SUCCESS) {
        HILOG_ERROR(HILOG_MODULE_ACE, "RsaCrypt failed.");
        JSI::CallFunction(fail, thisVal, argvFail, ARGC_TWO);
        goto RELEASE;
    }
    JSI::SetStringProperty(result, "text", (char*)textOut.data);
    JSI::CallFunction(success, thisVal, argvSuccess, ARGC_ONE);

RELEASE:
    JSI::ReleaseString(strAction);
    JSI::ReleaseString(strText);
    ResetStrBuf(strKey);
    JSI::ReleaseString(strKey);
    JSI::ReleaseString(strTransformation);
    JSI::CallFunction(complete, thisVal, nullptr, 0);
    JSI::ReleaseValueList(success, fail, complete, result, code, data, ARGS_END);
    if (textOut.data != nullptr) {
        ace_free(textOut.data);
    }

    return undefValue;
}

JSIValue CipherModule::Aes(const JSIValue thisVal, const JSIValue *args, uint8_t argsNum)
{
    JSIValue undefValue = JSI::CreateUndefined();
    if ((args == nullptr) || argsNum == 0 || JSI::ValueIsUndefined(args[0])) {
        return undefValue;
    }
    JSIValue success = JSI::GetNamedProperty(args[0], CB_SUCCESS);
    JSIValue fail = JSI::GetNamedProperty(args[0], CB_FAIL);
    JSIValue complete = JSI::GetNamedProperty(args[0], CB_COMPLETE);
    char *strAction = JSI::GetStringProperty(args[0], "action");
    char *strText = JSI::GetStringProperty(args[0], "text");
    char *strKey = JSI::GetStringProperty(args[0], "key");
    char *strTransformation = JSI::GetStringProperty(args[0], "transformation");
    char *strIv = JSI::GetStringProperty(args[0], "iv");
    double ivOffset = JSI::GetNumberProperty(args[0], "ivOffset");
    JSIValue jsIvLen = JSI::GetNamedProperty(args[0], "ivLen");
    JSIValue result = JSI::CreateObject();
    JSIValue code = JSI::CreateNumber(ERR_CODE);
    JSIValue argvSuccess[ARGC_ONE] = { result };
    JSIValue data = JSI::CreateString("System error");
    JSIValue argvFail[ARGC_TWO] = { data, code };
    AesCryptContext aes = {{NULL, NULL, 0, 0, 0}, CIPHER_AES_ECB, {NULL, NULL, 0, 0}};
    AesIvMode iv = {NULL, NULL, 0, 0};
    int ret;
    double ivLen = -1;
    if (JSI::ValueIsNumber(jsIvLen)) {
        ivLen = JSI::ValueToNumber(jsIvLen);
        if (ivLen < 0) {
            HILOG_ERROR(HILOG_MODULE_ACE, "Ivlen:%lf is not natural number.", ivLen);
            JSI::CallFunction(fail, thisVal, argvFail, ARGC_TWO);
            goto RELEASE;
        }
    }
    iv.ivBuf = strIv;
    iv.ivLen = ivLen;
    iv.ivOffset = ivOffset;
    iv.transformation = strTransformation;
    ret = InitAesCryptData(strAction, strText, strKey, &iv, &aes);
    if (ret != ERROR_SUCCESS) {
        HILOG_ERROR(HILOG_MODULE_ACE, "InitAesCryptData failed.");
        JSI::CallFunction(fail, thisVal, argvFail, ARGC_TWO);
        goto RELEASE;
    }
    ret = AesCrypt(&aes);
    if (ret != ERROR_SUCCESS) {
        HILOG_ERROR(HILOG_MODULE_ACE, "AesCrypt failed.");
        JSI::CallFunction(fail, thisVal, argvFail, ARGC_TWO);
        goto RELEASE;
    }
    JSI::SetStringProperty(result, "text", (char*)aes.data.text);
    JSI::CallFunction(success, thisVal, argvSuccess, ARGC_ONE);

RELEASE:
    JSI::ReleaseString(strAction);
    JSI::ReleaseString(strText);
    ResetStrBuf(strKey);
    ResetStrBuf(strIv);
    JSI::ReleaseString(strKey);
    JSI::ReleaseString(strIv);
    JSI::ReleaseString(strTransformation);
    JSI::CallFunction(complete, thisVal, nullptr, 0);
    JSI::ReleaseValueList(success, fail, complete, result, code, data, jsIvLen, ARGS_END);
    DeinitAesCryptData(&aes);
    return undefValue;
}

void CipherModule::ResetStrBuf(char *strBuf)
{
    if (strBuf == nullptr) {
        return;
    }

    int ret = memset_s(strBuf, strlen(strBuf), 0, strlen(strBuf));
    if (ret != EOK) {
        HILOG_ERROR(HILOG_MODULE_ACE, "memset failed.");
    }
}
} // namespace ACELite
} // namespace OHOS
