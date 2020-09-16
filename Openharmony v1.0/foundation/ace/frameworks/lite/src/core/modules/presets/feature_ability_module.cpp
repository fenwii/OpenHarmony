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

#include "feature_ability_module.h"
#ifdef FEATURE_FEATURE_ABILITY_MODULE
#include "ace_event_error_code.h"
#include "ace_log.h"
#include "fatal_handler.h"
#include "js_app_context.h"
#include "js_async_work.h"
#include "js_fwk_common.h"
#if ENABLED(SECURE_C_FUNCTION)
#include "securec.h"
#endif // ENABLED(SECURE_C_FUNCTION)

namespace OHOS {
namespace ACELite {
constexpr char FUNC_SUBSCRIBE[] = "subscribeMsg";
constexpr char FUNC_UNSUBSCRIBE[] = "unsubscribeMsg";
constexpr char FUNC_SEND_MSG[] = "sendMsg";
constexpr char ATTR_DEVICE_ID[] = "deviceId";
constexpr char ATTR_BUNDLE_NAME[] = "bundleName";
constexpr char ATTR_ABILITY_NAME[] = "abilityName";
constexpr char ATTR_MESSAGE[] = "message";
constexpr char ERR_MESSAGE[] = "Invalid parameter";
constexpr char ERR_SEND_FAIL[] = "Send message fail";
constexpr uint8_t ARG_LENGTH_SUCCESS = 1;
constexpr uint8_t ARG_LENGTH_FAIL = 2;
constexpr uint16_t ERR_CODE_INVALID_PARAMETER = 202;
constexpr uint16_t ERR_CODE_SEND_MSG_FAILED = 2060;
jerry_value_t FeatureAbilityModule::callbackContext_;
jerry_value_t FeatureAbilityModule::successCallback_;
jerry_value_t FeatureAbilityModule::failCallback_;
bool FeatureAbilityModule::registed = false;
void FeatureAbilityModule::Init()
{
    callbackContext_ = UNDEFINED;
    successCallback_ = UNDEFINED;
    failCallback_ = UNDEFINED;
    CreateNamedFunction(FUNC_SUBSCRIBE, SubscribeMessage);
    CreateNamedFunction(FUNC_UNSUBSCRIBE, UnsubscribeMessage);
    CreateNamedFunction(FUNC_SEND_MSG, SendMsgToPeer);
}

void FeatureAbilityModule::Release()
{
    ReleaseJsValues();
    if (registed) {
        char *bundleName = const_cast<char *>(JsAppContext::GetInstance()->GetCurrentBundleName());
        AbilityKit::UnregisterReceiver(bundleName);
        registed = false;
    }
}

void FeatureAbilityModule::SyncFailCallback(jerry_value_t &failCb,
                                            const jerry_value_t &context,
                                            const char * const data,
                                            uint16_t errorCode)
{
    const char * const emptyStr = "";
    jerry_value_t args[ARG_LENGTH_FAIL];
    jerry_value_t cbContext = jerry_acquire_value(context);
    if (data == nullptr) {
        args[0] = jerry_create_string(reinterpret_cast<const jerry_char_t *>(emptyStr));
    } else {
        args[0] = jerry_create_string(reinterpret_cast<const jerry_char_t *>(data));
    }
    args[1] = jerry_create_number(errorCode);
    CallJSFunctionAutoRelease(failCb, callbackContext_, args, ARG_LENGTH_FAIL);
    ReleaseJerryValue(args[0], args[1], cbContext, VA_ARG_END_FLAG);
}
void FeatureAbilityModule::SyncSendMsgCallback(const jerry_value_t &arg,
                                               const jerry_value_t &context,
                                               const char *errMsg,
                                               const uint16_t errCode,
                                               bool success)
{
    if (success) {
        jerry_value_t successCbValue = jerryx_get_property_str(arg, ATTR_SUCCESS);
        if (jerry_value_is_function(successCbValue)) {
            CallJSFunctionAutoRelease(successCbValue, context, nullptr, 0);
        }
        jerry_release_value(successCbValue);
    } else {
        jerry_value_t failCbValue = jerryx_get_property_str(arg, ATTR_FAIL);
        if (jerry_value_is_function(failCbValue)) {
            SyncFailCallback(failCbValue, context, errMsg, errCode);
        }
        jerry_release_value(failCbValue);
    }

    jerry_value_t cmpltCbValue = jerryx_get_property_str(arg, ATTR_COMPLETE);
    if (jerry_value_is_function(cmpltCbValue)) {
        CallJSFunctionAutoRelease(cmpltCbValue, context, nullptr, 0);
    }
    jerry_release_value(cmpltCbValue);
}

jerry_value_t FeatureAbilityModule::SendMsgToPeer(const jerry_value_t func,
                                                  const jerry_value_t context,
                                                  const jerry_value_t args[],
                                                  const jerry_length_t length)
{
    if (length <= 0) {
        return UNDEFINED;
    }

    uint16_t nameLength = 0;
    jerry_value_t nameValue = jerryx_get_property_str(args[0], ATTR_BUNDLE_NAME);
    char *dstBundleName = MallocStringOf(nameValue, &nameLength);

    uint16_t msgLength = 0;
    jerry_value_t msgValue = jerryx_get_property_str(args[0], ATTR_MESSAGE);
    char *message = MallocStringOf(msgValue, &msgLength);

    uint16_t idLength = 0;
    jerry_value_t devIdValue = jerryx_get_property_str(args[0], ATTR_DEVICE_ID);
    char *deviceId = MallocStringOf(devIdValue, &idLength);
    if ((dstBundleName == nullptr) || (nameLength == 0) || (message == nullptr) || (msgLength == 0) ||
        (deviceId == nullptr)) {
        SyncSendMsgCallback(args[0], context, ERR_MESSAGE, ERR_CODE_INVALID_PARAMETER, false);
    } else {
        char *bundleName = const_cast<char *>(JsAppContext::GetInstance()->GetCurrentBundleName());
        int32_t ret = AbilityKit::SendMsgToPeerApp((idLength == 0), bundleName, dstBundleName,
                                                   (reinterpret_cast<const uint8_t *>(message)), strlen(message));
        if (ret == 0) {
            SyncSendMsgCallback(args[0], context, nullptr, 0, true);
        } else {
            SyncSendMsgCallback(args[0], context, ERR_SEND_FAIL, ERR_CODE_SEND_MSG_FAILED, false);
        }
    }
    ReleaseJerryValue(nameValue, msgValue, devIdValue, VA_ARG_END_FLAG);
    ACE_FREE(dstBundleName);
    ACE_FREE(message);
    ACE_FREE(deviceId);
    return UNDEFINED;
}

jerry_value_t FeatureAbilityModule::SubscribeMessage(const jerry_value_t func,
                                                     const jerry_value_t context,
                                                     const jerry_value_t args[],
                                                     const jerry_length_t length)
{
    if (length <= 0) {
        return UNDEFINED;
    }

    ReleaseJsValues();

    callbackContext_ = jerry_acquire_value(context);
    jerry_value_t options = args[0];
    jerry_value_t successCallback = jerryx_get_property_str(options, ATTR_SUCCESS);
    if (!IS_UNDEFINED(successCallback)) {
        if (!jerry_value_is_function(successCallback)) {
            HILOG_ERROR(HILOG_MODULE_ACE, "the success callback should be a function.");
        } else {
            successCallback_ = jerry_acquire_value(successCallback);
        }
    }
    jerry_release_value(successCallback);
    jerry_value_t failCallback = jerryx_get_property_str(options, ATTR_FAIL);
    if (!IS_UNDEFINED(failCallback)) {
        if (!jerry_value_is_function(failCallback)) {
            HILOG_ERROR(HILOG_MODULE_ACE, "the fail callback should be a function.");
        } else {
            failCallback_ = jerry_acquire_value(failCallback);
        }
    }
    jerry_release_value(failCallback);

    if (!registed) {
        char *bundleName = const_cast<char *>(JsAppContext::GetInstance()->GetCurrentBundleName());
        AbilityKit::RegisterReceiver(bundleName, MessageSuccessCallback, MessageFailCallback);
        registed = true;
    }

    return UNDEFINED;
}

jerry_value_t FeatureAbilityModule::UnsubscribeMessage(const jerry_value_t func,
                                                       const jerry_value_t context,
                                                       const jerry_value_t args[],
                                                       const jerry_length_t length)
{
    Release();
    ACE_FEATURE_EVENT_PRINT(MT_ACE_FEATUREABILITY, MT_ACE_FEATUREABILITY_UNSUBSCRIBEMSG, 0);
    return UNDEFINED;
}

int32_t FeatureAbilityModule::MessageSuccessCallback(void *data)
{
    if (FatalHandler::GetInstance().IsFatalErrorHitted()) {
        HILOG_ERROR(HILOG_MODULE_ACE, "drop message as handling fatal error");
        return -1;
    }
    if (data == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "message error");
        return -1;
    } else {
        ACE_FEATURE_EVENT_PRINT(MT_ACE_FEATUREABILITY, MT_ACE_FEATUREABILITY_SUBSCRIBEMSG, 0);
        FeatureAbilityDataInfo *origin = static_cast<FeatureAbilityDataInfo *>(data);
        FeatureAbilityDataInfo *target =
            static_cast<FeatureAbilityDataInfo *>(ace_malloc(sizeof(FeatureAbilityDataInfo)));
        if (target == nullptr) {
            HILOG_ERROR(HILOG_MODULE_ACE, "Failed to ace_malloc data");
            return -1;
        }
#if ENABLED(SECURE_C_FUNCTION)
        if (memset_s(target, sizeof(FeatureAbilityDataInfo), 0, sizeof(FeatureAbilityDataInfo)) != 0) {
            HILOG_ERROR(HILOG_MODULE_ACE, "MessageSuccessCallback memset_s failed");
            ACE_FREE(target);
            return -1;
        }
#else
        target->deviceID = nullptr;
        target->bundleName = nullptr;
        target->abilityName = nullptr;
        target->messageLength = 0;
        target->message = nullptr;
#endif
        CopySuccessMessage(origin, target);
        if (!JsAsyncWork::DispatchAsyncWork(AsyncSuccessCallback, target)) {
            ACE_FREE(target->deviceID);
            ACE_FREE(target->bundleName);
            ACE_FREE(target->abilityName);
            ACE_FREE(target->message);
            ACE_FREE(target);
        }
    }

    return 0;
}
void FeatureAbilityModule::CopySuccessMessage(FeatureAbilityDataInfo *origin, FeatureAbilityDataInfo *&target)
{
    size_t bufSize = 0;
    if (origin->deviceID != nullptr) {
        bufSize = strlen(origin->deviceID);
        if (bufSize < DEVICE_ID_LENGTH_MAX) {
            target->deviceID = static_cast<char *>(ace_malloc(sizeof(char) * (bufSize + 1)));
            if (target->deviceID != nullptr && memcpy_s(target->deviceID, bufSize, origin->deviceID, bufSize) == 0) {
                target->deviceID[bufSize] = '\0';
            } else {
                ACE_FREE(target->deviceID);
            }
        }
    }

    if (origin->bundleName != nullptr) {
        bufSize = strlen(origin->bundleName);
        if (bufSize < NAME_LENGTH_MAX) {
            target->bundleName = static_cast<char *>(ace_malloc(sizeof(char) * (bufSize + 1)));
            if (target->bundleName != nullptr &&
                memcpy_s(target->bundleName, bufSize, origin->bundleName, bufSize) == 0) {
                target->bundleName[bufSize] = '\0';
            } else {
                ACE_FREE(target->bundleName);
            }
        }
    }

    if (origin->abilityName != nullptr) {
        bufSize = strlen(origin->abilityName);
        if (bufSize < NAME_LENGTH_MAX) {
            target->abilityName = static_cast<char *>(ace_malloc(sizeof(char) * (bufSize + 1)));
            if (target->abilityName != nullptr &&
                memcpy_s(target->abilityName, bufSize, origin->abilityName, bufSize) == 0) {
                target->abilityName[bufSize] = '\0';
            } else {
                ACE_FREE(target->abilityName);
            }
        }
    }

    if ((origin->message != nullptr) && (origin->messageLength > 0) && (origin->messageLength < UINT16_MAX)) {
        bufSize = origin->messageLength;
        char *buffer = static_cast<char *>(ace_malloc(sizeof(char) * (bufSize + 1)));
        if (buffer != nullptr && memcpy_s(buffer, bufSize, static_cast<const char *>(origin->message), bufSize) == 0) {
            buffer[bufSize] = '\0';
            target->messageLength = bufSize;
            target->message = buffer;
        } else {
            ACE_FREE(buffer);
            target->messageLength = 0;
            target->message = nullptr;
        }
    }
}
int32_t FeatureAbilityModule::MessageFailCallback(void *data, uint16_t dataLength, uint16_t errorCode)
{
    if (FatalHandler::GetInstance().IsFatalErrorHitted()) {
        HILOG_ERROR(HILOG_MODULE_ACE, "drop message as handling fatal error");
        return -1;
    }
    FailCallbackParams *params = new FailCallbackParams();
    if (params == nullptr) {
        return -1;
    }
    if ((data != nullptr) && (dataLength > 0)) {
        char *buffer = static_cast<char *>(ace_malloc(sizeof(char) * (dataLength + 1)));
        if (buffer != nullptr && memcpy_s(buffer, dataLength, static_cast<const char *>(data), dataLength) == 0) {
            buffer[dataLength] = '\0';
            params->dataLength = dataLength;
            params->data = buffer;
        } else {
            ACE_FREE(buffer);
            params->dataLength = 0;
            params->data = nullptr;
        }
    }
    params->errorCode = errorCode;

    if (!JsAsyncWork::DispatchAsyncWork(AsyncFailCallback, static_cast<void *>(params))) {
        ACE_FREE(params->data);
        delete params;
        params = nullptr;
    }
    return 0;
}

void FeatureAbilityModule::AsyncSuccessCallback(void *data)
{
    if (data == nullptr) {
        CallJSFunctionAutoRelease(successCallback_, callbackContext_, nullptr, 0);
        return;
    }

    FeatureAbilityDataInfo *nativeData = static_cast<FeatureAbilityDataInfo *>(data);
    jerry_value_t object = jerry_create_object();
    if (nativeData->deviceID != nullptr) {
        JerrySetStringProperty(object, ATTR_DEVICE_ID, nativeData->deviceID);
        ace_free(nativeData->deviceID);
        nativeData->deviceID = nullptr;
    }
    if (nativeData->bundleName != nullptr) {
        JerrySetStringProperty(object, ATTR_BUNDLE_NAME, nativeData->bundleName);
        ace_free(nativeData->bundleName);
        nativeData->bundleName = nullptr;
    }
    if (nativeData->abilityName != nullptr) {
        JerrySetStringProperty(object, ATTR_ABILITY_NAME, nativeData->abilityName);
        ace_free(nativeData->abilityName);
        nativeData->abilityName = nullptr;
    }
    if ((nativeData->message != nullptr) && (nativeData->messageLength > 0)) {
        JerrySetStringProperty(object, ATTR_MESSAGE, static_cast<const char *>(nativeData->message),
                               nativeData->messageLength);
        ace_free(nativeData->message);
        nativeData->message = nullptr;
    }

    jerry_value_t args[ARG_LENGTH_SUCCESS] = {object};
    CallJSFunctionAutoRelease(successCallback_, callbackContext_, args, ARG_LENGTH_SUCCESS);
    jerry_release_value(object);
    ace_free(nativeData);
    nativeData = nullptr;
}
void FeatureAbilityModule::AsyncFailCallback(void *data)
{
    if (data == nullptr) {
        return;
    }

    FailCallbackParams *params = static_cast<FailCallbackParams *>(data);
    jerry_value_t args[ARG_LENGTH_FAIL];
    if (params->data == nullptr || params->dataLength <= 0) {
        args[0] = jerry_create_string(reinterpret_cast<const jerry_char_t *>(""));
    } else {
        args[0] = jerry_create_string_sz_from_utf8(static_cast<const jerry_char_t *>(params->data), params->dataLength);
        ace_free(params->data);
        params->data = nullptr;
    }

    args[1] = jerry_create_number(params->errorCode);
    CallJSFunctionAutoRelease(failCallback_, callbackContext_, args, ARG_LENGTH_FAIL);
    ReleaseJerryValue(args[0], args[1], VA_ARG_END_FLAG);
    delete (params);
    params = nullptr;
}

void FeatureAbilityModule::ReleaseJsValues()
{
    ReleaseJsValue(callbackContext_);
    ReleaseJsValue(successCallback_);
    ReleaseJsValue(failCallback_);
}

void FeatureAbilityModule::ReleaseJsValue(jerry_value_t &value)
{
    if (!IS_UNDEFINED(value)) {
        jerry_release_value(value);
        value = UNDEFINED;
    }
}
} // namespace ACELite
} // namespace OHOS
#endif
