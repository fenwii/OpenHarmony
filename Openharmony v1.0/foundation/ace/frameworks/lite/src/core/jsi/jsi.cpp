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
#include "jsi.h"

#include <cstdarg>
#include <cstring>
#include "acelite_config.h"
#ifdef OHOS_ACELITE_PRODUCT_WATCH
#include "securec.h"
#endif // OHOS_ACELITE_PRODUCT_WATCH
#include "ace_log.h"
#include "ace_mem_base.h"
#include "acelite_config.h"
#include "internal/jsi_internal.h"
#include "js_fwk_common.h"

namespace OHOS {
namespace ACELite {
JSIValue JSI::GetGlobalObject()
{
#if defined(ENABLE_JERRY)
    return AS_JSI_VALUE(jerry_get_global_object());
#else
    HILOG_ERROR(HILOG_MODULE_ACE, "JSI:GetGlobalObject has not been implemented in this js engine!");
    return CreateUndefined();
#endif
}

JSIValue JSI::CreateObject()
{
#if defined(ENABLE_JERRY)
    return AS_JSI_VALUE(jerry_create_object());
#else
    HILOG_ERROR(HILOG_MODULE_ACE, "JSI:CreateObject has not been implemented in this js engine!");
    return CreateUndefined();
#endif
}

void JSI::SetProperty(JSIValue object, JSIValue key, JSIValue value)
{
    if (!ValueIsObject(object)) {
        HILOG_ERROR(HILOG_MODULE_ACE, "JSI:SetProperty failed!");
        return;
    }
#if defined(ENABLE_JERRY)
    jerry_value_t jObject = AS_JERRY_VALUE(object);
    jerry_value_t jKey = AS_JERRY_VALUE(key);
    jerry_value_t jVal = AS_JERRY_VALUE(value);

    jerry_release_value(jerry_set_property(jObject, jKey, jVal));
#else
    HILOG_ERROR(HILOG_MODULE_ACE, "JSI:SetProperty has not been implemented in this js engine!");
#endif
}

void JSI::SetNamedProperty(JSIValue object, const char * const propName, JSIValue value)
{
    if (!ValueIsObject(object) || (propName == nullptr)) {
        HILOG_ERROR(HILOG_MODULE_ACE, "JSI:SetNamedProperty failed!");
        return;
    }
#if defined(ENABLE_JERRY)
    jerry_value_t jKey = jerry_create_string((const jerry_char_t *)propName);
    SetProperty(object, AS_JSI_VALUE(jKey), value);
    jerry_release_value(jKey);
#else
    HILOG_ERROR(HILOG_MODULE_ACE, "JSI:SetNamedProperty has not been implemented in this js engine!");
#endif
}

void JSI::SetNumberProperty(JSIValue object, const char * const propName, double value)
{
    if (!ValueIsObject(object)) {
        HILOG_ERROR(HILOG_MODULE_ACE, "JSI:SetNumberProperty failed!");
        return;
    }
    JSIValue numValue = CreateNumber(value);
    SetNamedProperty(object, propName, numValue);
    ReleaseValue(numValue);
}

void JSI::SetBooleanProperty(JSIValue object, const char * const propName, bool value)
{
    if (!ValueIsObject(object)) {
        HILOG_ERROR(HILOG_MODULE_ACE, "JSI:SetBooleanProperty failed!");
        return;
    }
    JSIValue boolValue = CreateBoolean(value);
    SetNamedProperty(object, propName, boolValue);
    ReleaseValue(boolValue);
}

void JSI::SetStringProperty(JSIValue object, const char * const propName, const char *value)
{
    if (!ValueIsObject(object)) {
        HILOG_ERROR(HILOG_MODULE_ACE, "JSI:SetStringProperty failed!");
        return;
    }
    JSIValue strValue = CreateString(value);
    SetNamedProperty(object, propName, strValue);
    ReleaseValue(strValue);
}

#if defined(ENABLE_JERRY)
/**
 * @brief: CreateJerryFuncHelper is used to create jerry function
 *         along with JSI::CreateFunction, for internal use only.
 */
static jerry_value_t CreateJerryFuncHelper(const jerry_value_t func,
                                           const jerry_value_t thisVal,
                                           const jerry_value_t *args,
                                           const jerry_length_t argsNum)
{
    void *nativePointer = nullptr;
    bool exist = jerry_get_object_native_pointer(func, &nativePointer, nullptr);
    if (!exist || (nativePointer == nullptr) || (argsNum >= UINT8_MAX)) {
        HILOG_ERROR(HILOG_MODULE_ACE, "JSI:CreateJerryFuncHelper get function pointer failed!");
        return jerry_create_undefined();
    }

    JSIFunctionHandler handler = reinterpret_cast<JSIFunctionHandler>(nativePointer);
    JSIValue jsiThis = AS_JSI_VALUE(thisVal);
    uint8_t jsiArgsNum = (uint8_t)argsNum;
    if ((args == nullptr) || (jsiArgsNum == 0)) {
        return AS_JERRY_VALUE(handler(jsiThis, nullptr, 0));
    }
    JSIValue *jsiArgs = static_cast<JSIValue *>(ace_malloc(sizeof(JSIValue) * jsiArgsNum));
    if (jsiArgs == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "JSI:CreateJerryFuncHelper allocate memory failed!");
        return jerry_create_undefined();
    }

    for (uint8_t index = 0; index < jsiArgsNum; index++) {
        jsiArgs[index] = AS_JSI_VALUE(args[index]);
    }
    JSIValue res = handler(jsiThis, jsiArgs, jsiArgsNum);
    ace_free(jsiArgs);
    jsiArgs = nullptr;
    return AS_JERRY_VALUE(res);
}
#endif

JSIValue JSI::CreateFunction(JSIFunctionHandler handler)
{
    if (handler == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "JSI:CreateFunction failed!");
        return CreateUndefined();
    }
#if defined(ENABLE_JERRY)
    jerry_value_t jFunc = jerry_create_external_function(CreateJerryFuncHelper);
    void *nativePointer = reinterpret_cast<void *>(handler);
    jerry_set_object_native_pointer(jFunc, nativePointer, nullptr);
    return AS_JSI_VALUE(jFunc);
#else
    HILOG_ERROR(HILOG_MODULE_ACE, "JSI:CreateFunction has not been implemented in this js engine!");
    return CreateUndefined();
#endif
}

JSIValue JSI::CreateString(const char * const str)
{
    if (str == nullptr) {
        return CreateUndefined();
    }
#if defined(ENABLE_JERRY)
    return AS_JSI_VALUE(jerry_create_string(reinterpret_cast<const jerry_char_t *>(str)));
#else
    HILOG_ERROR(HILOG_MODULE_ACE, "JSI:CreateString has not been implemented in this js engine!");
    return CreateUndefined();
#endif
}

JSIValue JSI::CreateUndefined()
{
#if defined(ENABLE_JERRY)
    return AS_JSI_VALUE(jerry_create_undefined());
#else
    HILOG_ERROR(HILOG_MODULE_ACE, "JSI:CreateUndefined has not been implemented in this js engine!");
    return nullptr;
#endif
}

bool JSI::ValueIsFunction(JSIValue value)
{
#if defined(ENABLE_JERRY)
    return jerry_value_is_function(AS_JERRY_VALUE(value));
#else
    HILOG_ERROR(HILOG_MODULE_ACE, "JSI:ValueIsFunction has not been implemented in this js engine!");
    return false;
#endif
}

bool JSI::ValueIsUndefined(JSIValue value)
{
#if defined(ENABLE_JERRY)
    return jerry_value_is_undefined(AS_JERRY_VALUE(value));
#else
    HILOG_ERROR(HILOG_MODULE_ACE, "JSI:ValueIsUndefined has not been implemented in this js engine!");
    return false;
#endif
}

bool JSI::ValueIsNumber(JSIValue value)
{
#if defined(ENABLE_JERRY)
    return jerry_value_is_number(AS_JERRY_VALUE(value));
#else
    HILOG_ERROR(HILOG_MODULE_ACE, "JSI:ValueIsNumber has not been implemented in this js engine!");
    return false;
#endif
}

bool JSI::ValueIsString(JSIValue value)
{
#if defined(ENABLE_JERRY)
    return jerry_value_is_string(AS_JERRY_VALUE(value));
#else
    HILOG_ERROR(HILOG_MODULE_ACE, "JSI:ValueIsString has not been implemented in this js engine!");
    return false;
#endif
}

bool JSI::ValueIsBoolean(JSIValue value)
{
#if defined(ENABLE_JERRY)
    return jerry_value_is_boolean(AS_JERRY_VALUE(value));
#else
    HILOG_ERROR(HILOG_MODULE_ACE, "JSI:ValueIsBoolean has not been implemented in this js engine!");
    return false;
#endif
}

bool JSI::ValueIsNull(JSIValue value)
{
#if defined(ENABLE_JERRY)
    return jerry_value_is_null(AS_JERRY_VALUE(value));
#else
    HILOG_ERROR(HILOG_MODULE_ACE, "JSI:ValueIsNull has not been implemented in this js engine!");
    return false;
#endif
}

bool JSI::ValueIsObject(JSIValue value)
{
#if defined(ENABLE_JERRY)
    return jerry_value_is_object(AS_JERRY_VALUE(value));
#else
    HILOG_ERROR(HILOG_MODULE_ACE, "JSI:ValueIsObject has not been implemented in this js engine!");
    return false;
#endif
}

bool JSI::ValueIsError(JSIValue value)
{
#if defined(ENABLE_JERRY)
    return jerry_value_is_error(AS_JERRY_VALUE(value));
#else
    HILOG_ERROR(HILOG_MODULE_ACE, "JSI:ValueIsError has not been implemented in this js engine!");
    return false;
#endif
}

char *JSI::JsonStringify(JSIValue value)
{
    if (!ValueIsObject(value)) {
        HILOG_ERROR(HILOG_MODULE_ACE, "JSI:JsonStringify failed!");
        return nullptr;
    }
#if defined(ENABLE_JERRY)
    jerry_value_t stringified = jerry_json_stringify(AS_JERRY_VALUE(value));
    char *res = ValueToString(AS_JSI_VALUE(stringified));
    jerry_release_value(stringified);
    return res;
#else
    HILOG_ERROR(HILOG_MODULE_ACE, "JSI:JsonStringify has not been implemented in this js engine!");
    return nullptr;
#endif
}

JSIValue JSI::JsonParse(const char * const str)
{
    if (str == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "JSI:JsonParse failed!");
        return CreateUndefined();
    }
#if defined(ENABLE_JERRY)
    jerry_value_t jVal = jerry_json_parse(reinterpret_cast<const jerry_char_t *>(str), strlen(str));
    return AS_JSI_VALUE(jVal);
#else
    HILOG_ERROR(HILOG_MODULE_ACE, "JSI:JsonParse has not been implemented in this js engine!");
    return CreateUndefined();
#endif
}

JSIValue JSI::GetProperty(JSIValue object, JSIValue key)
{
    if (!ValueIsObject(object)) {
        HILOG_ERROR(HILOG_MODULE_ACE, "JSI:GetProperty failed!");
        return CreateUndefined();
    }
#if defined(ENABLE_JERRY)
    jerry_value_t jObject = AS_JERRY_VALUE(object);
    jerry_value_t jKey = AS_JERRY_VALUE(key);
    return AS_JSI_VALUE(jerry_get_property(jObject, jKey));
#else
    HILOG_ERROR(HILOG_MODULE_ACE, "JSI:GetProperty has not been implemented in this js engine!");
    return CreateUndefined();
#endif
}

JSIValue JSI::GetNamedProperty(JSIValue object, const char * const propName)
{
    if (!ValueIsObject(object) || (propName == nullptr)) {
        HILOG_ERROR(HILOG_MODULE_ACE, "JSI:GetNamedProperty failed!");
        return CreateUndefined();
    }
#if defined(ENABLE_JERRY)
    jerry_value_t jKey = jerry_create_string(reinterpret_cast<const jerry_char_t *>(propName));
    JSIValue result = GetProperty(object, AS_JSI_VALUE(jKey));
    jerry_release_value(jKey);
    return result;
#else
    HILOG_ERROR(HILOG_MODULE_ACE, "JSI:GetNamedProperty has not been implemented in this js engine!");
    return CreateUndefined();
#endif
}

double JSI::GetNumberProperty(JSIValue object, const char * const propName)
{
    if (!ValueIsObject(object)) {
        HILOG_ERROR(HILOG_MODULE_ACE, "JSI:GetNumberProperty failed!");
        return 0.0;
    }
    JSIValue propValue = GetNamedProperty(object, propName);
    double res = ValueToNumber(propValue);
    ReleaseValue(propValue);
    return res;
}

bool JSI::GetBooleanProperty(JSIValue object, const char * const propName)
{
    if (!ValueIsObject(object)) {
        HILOG_ERROR(HILOG_MODULE_ACE, "JSI:GetBooleanProperty failed!");
        return false;
    }
    JSIValue propValue = GetNamedProperty(object, propName);
    bool res = ValueToBoolean(propValue);
    ReleaseValue(propValue);
    return res;
}

char *JSI::GetStringProperty(JSIValue object, const char * const propName)
{
    if (!ValueIsObject(object)) {
        HILOG_ERROR(HILOG_MODULE_ACE, "JSI:GetStringProperty failed!");
        return nullptr;
    }
    JSIValue propValue = GetNamedProperty(object, propName);
    char *res = ValueToString(propValue);
    ReleaseValue(propValue);
    return res;
}

void JSI::ReleaseValue(JSIValue value)
{
#if defined(ENABLE_JERRY)
    if (value != ARGS_END) {
        jerry_release_value(AS_JERRY_VALUE(value));
    }
#else
    HILOG_ERROR(HILOG_MODULE_ACE, "JSI:ReleaseValue has not been implemented in this js engine!");
#endif
}

void JSI::ReleaseString(char *&str)
{
    if (str != nullptr) {
        ace_free(str);
        str = nullptr;
    }
}

void JSI::CallFunction(JSIValue funcObj, JSIValue thisVal, const JSIValue *argv, uint8_t argc)
{
    if (!ValueIsFunction(funcObj)) {
        HILOG_ERROR(HILOG_MODULE_ACE, "JSI:CallFunction failed!");
        return;
    }
#if defined(ENABLE_JERRY)
    jerry_value_t jFunc = AS_JERRY_VALUE(funcObj);
    jerry_value_t jThis = AS_JERRY_VALUE(thisVal);
    if ((argv == nullptr) || argc == 0) {
        CallJSFunctionAutoRelease(jFunc, jThis, nullptr, 0);
        return;
    }
    jerry_value_t *jArgv = new jerry_value_t[argc];
    if (jArgv == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "JSI:CallFunction allocate memory failed!");
        return;
    }

    for (uint8_t index = 0; index < argc; index++) {
        jArgv[index] = AS_JERRY_VALUE(argv[index]);
    }
    CallJSFunctionAutoRelease(jFunc, jThis, jArgv, argc);
    delete[] jArgv;
    jArgv = nullptr;
#else
    HILOG_ERROR(HILOG_MODULE_ACE, "JSI:CallFunction has not been implemented in this js engine!");
#endif
}

JSIValue JSI::CreateNumber(double value)
{
#if defined(ENABLE_JERRY)
    return AS_JSI_VALUE(jerry_create_number(value));
#else
    HILOG_ERROR(HILOG_MODULE_ACE, "JSI:CreateNumber has not been implemented in this js engine!");
    return CreateUndefined();
#endif
}

JSIValue JSI::CreateNumberNaN()
{
#if defined(ENABLE_JERRY)
    return AS_JSI_VALUE(jerry_create_number_nan());
#else
    HILOG_ERROR(HILOG_MODULE_ACE, "JSI:CreateNumberNan has not been implemented in this js engine!");
    return CreateUndefined();
#endif
}

#if defined(ENABLE_JERRY)
static jerry_error_t GetJerryErrorType(JsiErrorType jsiType)
{
    jerry_error_t jerryType;
    switch (jsiType) {
        case JsiErrorType::JSI_ERROR_COMMON:
            jerryType = JERRY_ERROR_COMMON;
            break;
        case JsiErrorType::JSI_ERROR_EVAL:
            jerryType = JERRY_ERROR_EVAL;
            break;
        case JsiErrorType::JSI_ERROR_RANGE:
            jerryType = JERRY_ERROR_RANGE;
            break;
        case JsiErrorType::JSI_ERROR_REFERENCE:
            jerryType = JERRY_ERROR_REFERENCE;
            break;
        case JsiErrorType::JSI_ERROR_SYNTAX:
            jerryType = JERRY_ERROR_SYNTAX;
            break;
        case JsiErrorType::JSI_ERROR_TYPE:
            jerryType = JERRY_ERROR_TYPE;
            break;
        case JsiErrorType::JSI_ERROR_URI:
            jerryType = JERRY_ERROR_URI;
            break;
        default:
            jerryType = JERRY_ERROR_COMMON;
            break;
    }
    return jerryType;
}

static JsiErrorType GetJsiErrorType(jerry_error_t jerryType)
{
    JsiErrorType jsiType;
    switch (jerryType) {
        case JERRY_ERROR_COMMON:
            jsiType = JsiErrorType::JSI_ERROR_COMMON;
            break;
        case JERRY_ERROR_EVAL:
            jsiType = JsiErrorType::JSI_ERROR_EVAL;
            break;
        case JERRY_ERROR_RANGE:
            jsiType = JsiErrorType::JSI_ERROR_RANGE;
            break;
        case JERRY_ERROR_REFERENCE:
            jsiType = JsiErrorType::JSI_ERROR_REFERENCE;
            break;
        case JERRY_ERROR_SYNTAX:
            jsiType = JsiErrorType::JSI_ERROR_SYNTAX;
            break;
        case JERRY_ERROR_TYPE:
            jsiType = JsiErrorType::JSI_ERROR_TYPE;
            break;
        case JERRY_ERROR_URI:
            jsiType = JsiErrorType::JSI_ERROR_URI;
            break;
        default:
            jsiType = JsiErrorType::JSI_ERROR_INVALID;
            break;
    }
    return jsiType;
}
#endif

JSIValue JSI::CreateError(JsiErrorType type, const char * const errorMsg)
{
    if ((type <= JsiErrorType::JSI_ERROR_INVALID) ||
        (type >= JsiErrorType::JSI_ERROR_MAX) || (errorMsg == nullptr)) {
        HILOG_ERROR(HILOG_MODULE_ACE, "JSI:CreateError parameters invalid!");
        return CreateUndefined();
    }
#if defined(ENABLE_JERRY)
    jerry_error_t jerryType = GetJerryErrorType(type);
    jerry_value_t jError = jerry_create_error(jerryType, reinterpret_cast<const jerry_char_t *>(errorMsg));
    return AS_JSI_VALUE(jError);
#else
    HILOG_ERROR(HILOG_MODULE_ACE, "JSI:CreateError has not been implemented in this js engine!");
    return CreateUndefined();
#endif
}

JsiErrorType JSI::GetErrorType(JSIValue errorValue)
{
    if (!ValueIsError(errorValue)) {
        return JsiErrorType::JSI_ERROR_INVALID;
    }
#if defined(ENABLE_JERRY)
    jerry_value_t jError = AS_JERRY_VALUE(errorValue);
    jerry_error_t jerryType = jerry_get_error_type(jError);
    return GetJsiErrorType(jerryType);
#else
    HILOG_ERROR(HILOG_MODULE_ACE, "JSI:GetErrorType has not been implemented in this js engine!");
    return JsiErrorType::JSI_ERROR_INVALID;
#endif
}

JSIValue JSI::CreateBoolean(bool value)
{
#if defined(ENABLE_JERRY)
    return AS_JSI_VALUE(jerry_create_boolean(value));
#else
    HILOG_ERROR(HILOG_MODULE_ACE, "JSI:CreateBoolean has not been implemented in this js engine!");
    return CreateUndefined();
#endif
}

JSIValue JSI::CreateNull()
{
#if defined(ENABLE_JERRY)
    return AS_JSI_VALUE(jerry_create_null());
#else
    HILOG_ERROR(HILOG_MODULE_ACE, "JSI:CreateNull has not been implemented in this js engine!");
    return CreateUndefined();
#endif
}

#if defined(JS_FWK_SYMBOL)
JSIValue JSI::CreateSymbol(JSIValue description)
{
#if defined(ENABLE_JERRY)
    jerry_value_t jDsc = AS_JERRY_VALUE(description);
    return AS_JSI_VALUE(jerry_create_symbol(jDsc));
#else
    HILOG_ERROR(HILOG_MODULE_ACE, "JSI:CreateSymbol has not been implemented in this js engine!");
    return CreateUndefined();
#endif
}

bool JSI::ValueIsSymbol(JSIValue value)
{
#if defined(ENABLE_JERRY)
    return jerry_value_is_symbol(AS_JERRY_VALUE(value));
#else
    HILOG_ERROR(HILOG_MODULE_ACE, "JSI:ValueIsSymbol has not been implemented in this js engine!");
    return false;
#endif
}
#endif // JS_FWK_SYMBOL

JSIValue JSI::CreateArray(uint32_t length)
{
#if defined(ENABLE_JERRY)
    return AS_JSI_VALUE(jerry_create_array(length));
#else
    HILOG_ERROR(HILOG_MODULE_ACE, "JSI:CreateArray has not been implemented in this js engine!");
    return CreateUndefined();
#endif
}

bool JSI::SetPropertyByIndex(JSIValue object, uint32_t index, JSIValue value)
{
#if defined(ENABLE_JERRY)
    jerry_value_t jObject = AS_JERRY_VALUE(object);
    jerry_value_t jVal = AS_JERRY_VALUE(value);

    jerry_value_t res = jerry_set_property_by_index(jObject, index, jVal);
    if (jerry_value_is_error(res)) {
        jerry_release_value(res);
        return false;
    }
    jerry_release_value(res);
    return true;
#else
    HILOG_ERROR(HILOG_MODULE_ACE, "JSI:SetPropertyByIndex has not been implemented in this js engine!");
    return false;
#endif
}

char *JSI::ValueToString(JSIValue value)
{
#if defined(ENABLE_JERRY)
    char *result = nullptr;
    jerry_value_t jVal = AS_JERRY_VALUE(value);
    if (!jerry_value_is_string(jVal)) {
        HILOG_ERROR(HILOG_MODULE_ACE, "JSI:ValueToString params invalid!");
        return nullptr;
    }

    jerry_size_t size = jerry_get_string_size(jVal);
    if ((size == 0) || (size == UINT32_MAX)) {
        // Output empty char instead of nullptr, thus caller can free safely
        result = static_cast<char *>(ace_malloc(sizeof(char)));
        if (result == nullptr) {
            HILOG_ERROR(HILOG_MODULE_ACE, "JSI:ValueToString malloc memory for empty char failed!");
            return nullptr;
        }
        result[0] = '\0';
        return result;
    } else {
        jerry_char_t *buffer = static_cast<jerry_char_t *>(ace_malloc(sizeof(jerry_char_t) * (size + 1)));
        if (buffer == nullptr) {
            HILOG_ERROR(HILOG_MODULE_ACE, "JSI:ValueToString malloc memory failed!");
            return nullptr;
        }
        jerry_size_t length = jerry_string_to_char_buffer(jVal, buffer, size);
        if ((length == 0) || (length > size)) {
            HILOG_ERROR(HILOG_MODULE_ACE, "JSI:ValueToString jerry string to char buffer failed");
            ace_free(buffer);
            buffer = nullptr;
            return nullptr;
        }
        buffer[length] = '\0';
        result = reinterpret_cast<char *>(buffer);
        return result;
    }
#else
    HILOG_ERROR(HILOG_MODULE_ACE, "JSI:ValueToString has not been implemented in this js engine!");
    return nullptr;
#endif
}

double JSI::ValueToNumber(JSIValue value)
{
#if defined(ENABLE_JERRY)
    jerry_value_t jVal = AS_JERRY_VALUE(value);
    if (!jerry_value_is_number(jVal)) {
        HILOG_ERROR(HILOG_MODULE_ACE, "JSI:ValueToNumber params invalid!");
        return 0.0;
    }
    return jerry_get_number_value(jVal);
#else
    HILOG_ERROR(HILOG_MODULE_ACE, "JSI:ValueToNumber has not been implemented in this js engine!");
    return 0.0;
#endif
}

bool JSI::ValueToBoolean(JSIValue value)
{
#if defined(ENABLE_JERRY)
    jerry_value_t jVal = AS_JERRY_VALUE(value);
    if (!jerry_value_is_boolean(jVal)) {
        HILOG_ERROR(HILOG_MODULE_ACE, "JSI:ValueToBoolean params invalid!");
        return false;
    }
    return jerry_value_to_boolean(jVal);
#else
    HILOG_ERROR(HILOG_MODULE_ACE, "JSI:ValueToBoolean has not been implemented in this js engine!");
    return false;
#endif
}

uint32_t JSI::GetArrayLength(JSIValue value)
{
#if defined(ENABLE_JERRY)
    jerry_value_t jVal = AS_JERRY_VALUE(value);
    if (!jerry_value_is_array(jVal)) {
        HILOG_ERROR(HILOG_MODULE_ACE, "JSI:GetArrayLength params invalid!");
        return 0;
    }
    return jerry_get_array_length(jVal);
#else
    HILOG_ERROR(HILOG_MODULE_ACE, "JSI:GetArrayLength has not been implemented in this js engine!");
    return 0;
#endif
}

JSIValue JSI::GetPropertyByIndex(JSIValue object, uint32_t index)
{
#if defined(ENABLE_JERRY)
    jerry_value_t jVal = AS_JERRY_VALUE(object);
    return AS_JSI_VALUE(jerry_get_property_by_index(jVal, index));
#else
    HILOG_ERROR(HILOG_MODULE_ACE, "JSI:GetPropertyByIndex has not been implemented in this js engine!");
    return CreateUndefined();
#endif
}

JSIValue JSI::GetObjectKeys(JSIValue object)
{
    if (!ValueIsObject(object)) {
        HILOG_ERROR(HILOG_MODULE_ACE, "JSI:GetObjectKeys failed!");
        return CreateUndefined();
    }
#if defined(ENABLE_JERRY)
    jerry_value_t jVal = AS_JERRY_VALUE(object);
    return AS_JSI_VALUE(jerry_get_object_keys(jVal));
#else
    HILOG_ERROR(HILOG_MODULE_ACE, "JSI:GetObjectKeys has not been implemented in this js engine!");
    return CreateUndefined();
#endif
}

bool JSI::GetJSHeapStatus(JSHeapStatus &heapStatus)
{
#if defined(ENABLE_JERRY)
    jerry_heap_stats_t stats = {0};
    if (!jerry_get_memory_stats(&stats)) {
        return false;
    }
    heapStatus.totalBytes = stats.size;
    heapStatus.allocBytes = stats.allocated_bytes;
    heapStatus.peakAllocBytes = stats.peak_allocated_bytes;
    return true;
#else
    HILOG_ERROR(HILOG_MODULE_ACE, "JSI:GetJSHeapStatus has not been implemented in this js engine!");
    return false;
#endif
}

bool JSI::ValueIsArray(JSIValue value)
{
#if defined(ENABLE_JERRY)
    return jerry_value_is_array(AS_JERRY_VALUE(value));
#else
    HILOG_ERROR(HILOG_MODULE_ACE, "JSI:ValueIsArray has not been implemented in this js engine!");
    return false;
#endif
}

JSIValue JSI::AcquireValue(JSIValue value)
{
#if defined(ENABLE_JERRY)
    jerry_value_t jVal = AS_JERRY_VALUE(value);
    return AS_JSI_VALUE(jerry_acquire_value(jVal));
#else
    HILOG_ERROR(HILOG_MODULE_ACE, "JSI:AcquireValue has not been implemented in this js engine!");
    return CreateUndefined();
#endif
}

void JSI::SetModuleAPI(JSIValue exports, const char * const name, JSIFunctionHandler handler)
{
    if (!ValueIsObject(exports) || (handler == nullptr)) {
        HILOG_ERROR(HILOG_MODULE_ACE, "JSI:SetModuleAPI failed!");
        return;
    }
    JSIValue jsFunc = CreateFunction(handler);
    SetNamedProperty(exports, name, jsFunc);
    ReleaseValue(jsFunc);
}

void JSI::SetOnDestroy(JSIValue object, NativeCallback callback)
{
    if (!ValueIsObject(object) || (callback == nullptr)) {
        HILOG_ERROR(HILOG_MODULE_ACE, "JSI:SetOnDestroy failed!");
        return;
    }
#if defined(ENABLE_JERRY)
    void *nativePtr = reinterpret_cast<void *>(callback);
    jerry_set_object_native_pointer(AS_JERRY_VALUE(object), nativePtr, nullptr);
#else
    HILOG_ERROR(HILOG_MODULE_ACE, "JSI:SetOnDestroy has not been implemented in this js engine!");
#endif
}

void JSI::SetOnDestroy(JSIValue object, JsiCallback callback)
{
    SetNamedPointer(object, ON_DESTROY_HANDLER, callback);
}

void JSI::SetOnTerminate(JSIValue object, NativeCallback callback)
{
    if (!ValueIsObject(object) || (callback == nullptr)) {
        HILOG_ERROR(HILOG_MODULE_ACE, "JSI:SetOnTerminate failed!");
        return;
    }
    JSIValue funObj = JSI::CreateObject();
    JSI::SetOnDestroy(funObj, callback);
    JSI::SetNamedProperty(object, ON_TERMINATE, funObj);
    JSI::ReleaseValue(funObj);
}

void JSI::SetOnTerminate(JSIValue object, JsiCallback callback)
{
    SetNamedPointer(object, ON_TERMINATE_HANDLER, callback);
}

void JSI::SetNamedPointer(JSIValue object, const char * const name, JsiCallback callback)
{
    if (!ValueIsObject(object) || (callback == nullptr)) {
        HILOG_ERROR(HILOG_MODULE_ACE, "JSI:SetNamedPointer failed!");
        return;
    }
#if defined(ENABLE_JERRY)
    JSIValue funObj = JSI::CreateObject();
    void *nativePtr = reinterpret_cast<void *>(callback);
    jerry_set_object_native_pointer(AS_JERRY_VALUE(funObj), nativePtr, nullptr);
    SetNamedProperty(object, name, funObj);
    ReleaseValue(funObj);
#else
    HILOG_ERROR(HILOG_MODULE_ACE, "JSI:SetNamedPointer has not been implemented in this js engine!");
#endif
}

#if defined(JS_FWK_TYPEDARRAY)
#if defined(ENABLE_JERRY)
// Helper function for JSI TypedArray type convert
TypedArrayType GetJsiArrayType(jerry_typedarray_type_t jerryType)
{
    TypedArrayType jsiType;
    switch (jerryType) {
        case JERRY_TYPEDARRAY_INT8:
            jsiType = TypedArrayType::JSI_INT8_ARRAY;
            break;
        case JERRY_TYPEDARRAY_UINT8:
            jsiType = TypedArrayType::JSI_UINT8_ARRAY;
            break;
        case JERRY_TYPEDARRAY_UINT8CLAMPED:
            jsiType = TypedArrayType::JSI_UINT8CLAMPED_ARRAY;
            break;
        case JERRY_TYPEDARRAY_INT16:
            jsiType = TypedArrayType::JSI_INT16_ARRAY;
            break;
        case JERRY_TYPEDARRAY_UINT16:
            jsiType = TypedArrayType::JSI_UINT16_ARRAY;
            break;
        case JERRY_TYPEDARRAY_INT32:
            jsiType = TypedArrayType::JSI_INT32_ARRAY;
            break;
        case JERRY_TYPEDARRAY_UINT32:
            jsiType = TypedArrayType::JSI_UINT32_ARRAY;
            break;
        case JERRY_TYPEDARRAY_FLOAT32:
            jsiType = TypedArrayType::JSI_FLOAT32_ARRAY;
            break;
        case JERRY_TYPEDARRAY_FLOAT64:
            jsiType = TypedArrayType::JSI_FLOAT64_ARRAY;
            break;
        default:
            jsiType = TypedArrayType::JSI_INVALID_ARRAY;
            break;
    }
    return jsiType;
}
#endif

uint8_t *JSI::GetTypedArrayInfo(JSIValue typedArray,
                                TypedArrayType &type,
                                size_t &length,
                                JSIValue &arrayBuffer,
                                size_t &byteOffset)
{
    if (!ValueIsTypedArray(typedArray)) {
        HILOG_ERROR(HILOG_MODULE_ACE, "JSI:GetTypedArrayInfo failed!");
        return nullptr;
    }
#if defined(ENABLE_JERRY)
    jerry_value_t jVal = AS_JERRY_VALUE(typedArray);
    jerry_typedarray_type_t jType = jerry_get_typedarray_type(jVal);
    type = GetJsiArrayType(jType);

    jerry_length_t jLength = jerry_get_typedarray_length(jVal);
    jerry_length_t jByteOffset;
    jerry_length_t jByteLength;
    jerry_value_t jArrayBuffer = jerry_get_typedarray_buffer(jVal, &jByteOffset, &jByteLength);

    length = (size_t)jLength;
    arrayBuffer = AS_JSI_VALUE(jArrayBuffer);
    byteOffset = (size_t)jByteOffset;
    return jerry_get_arraybuffer_pointer(jArrayBuffer);
#else
    HILOG_ERROR(HILOG_MODULE_ACE, "JSI:GetTypedArrayInfo has not been implemented in this js engine!");
    return nullptr;
#endif
}

#if defined(ENABLE_JERRY)
// Helper function for jerry TypedArray type convert
jerry_typedarray_type_t GetJerryArrayType(TypedArrayType jsiType)
{
    jerry_typedarray_type_t jerryType;
    switch (jsiType) {
        case TypedArrayType::JSI_INT8_ARRAY:
            jerryType = JERRY_TYPEDARRAY_INT8;
            break;
        case TypedArrayType::JSI_UINT8_ARRAY:
            jerryType = JERRY_TYPEDARRAY_UINT8;
            break;
        case TypedArrayType::JSI_UINT8CLAMPED_ARRAY:
            jerryType = JERRY_TYPEDARRAY_UINT8CLAMPED;
            break;
        case TypedArrayType::JSI_INT16_ARRAY:
            jerryType = JERRY_TYPEDARRAY_INT16;
            break;
        case TypedArrayType::JSI_UINT16_ARRAY:
            jerryType = JERRY_TYPEDARRAY_UINT16;
            break;
        case TypedArrayType::JSI_INT32_ARRAY:
            jerryType = JERRY_TYPEDARRAY_INT32;
            break;
        case TypedArrayType::JSI_UINT32_ARRAY:
            jerryType = JERRY_TYPEDARRAY_UINT32;
            break;
        case TypedArrayType::JSI_FLOAT32_ARRAY:
            jerryType = JERRY_TYPEDARRAY_FLOAT32;
            break;
        case TypedArrayType::JSI_FLOAT64_ARRAY:
            jerryType = JERRY_TYPEDARRAY_FLOAT64;
            break;
        default:
            jerryType = JERRY_TYPEDARRAY_INVALID;
            break;
    }
    return jerryType;
}
#endif

JSIValue JSI::CreateTypedArray(TypedArrayType type, size_t length, JSIValue arrayBuffer, size_t byteOffset)
{
#if defined(ENABLE_JERRY)
    jerry_typedarray_type_t jType = GetJerryArrayType(type);
    jerry_value_t jArrayBuffer = AS_JERRY_VALUE(arrayBuffer);
    jerry_value_t jVal = jerry_create_typedarray_for_arraybuffer_sz(jType, jArrayBuffer, (jerry_length_t)byteOffset,
                                                                    (jerry_length_t)length);
    return AS_JSI_VALUE(jVal);
#else
    HILOG_ERROR(HILOG_MODULE_ACE, "JSI:CreateTypedArray has not been implemented in this js engine!");
    return CreateUndefined();
#endif
}

uint8_t *JSI::GetArrayBufferInfo(JSIValue arrayBuffer, size_t &byteLength)
{
    if (!ValueIsArrayBuffer(arrayBuffer)) {
        HILOG_ERROR(HILOG_MODULE_ACE, "JSI:GetArrayBufferInfo failed!");
        return nullptr;
    }
#if defined(ENABLE_JERRY)
    jerry_value_t jVal = AS_JERRY_VALUE(arrayBuffer);
    jerry_length_t len = jerry_get_arraybuffer_byte_length(jVal);

    byteLength = (size_t)len;
    return jerry_get_arraybuffer_pointer(jVal);
#else
    HILOG_ERROR(HILOG_MODULE_ACE, "JSI:GetArrayBufferInfo has not been implemented in this js engine!");
    return nullptr;
#endif
}

JSIValue JSI::CreateArrayBuffer(size_t byteLength, uint8_t *&buffPtr)
{
    if (byteLength == 0) {
        return CreateUndefined();
    }
#if defined(ENABLE_JERRY)
    jerry_value_t jVal = jerry_create_arraybuffer((jerry_length_t)byteLength);
    buffPtr = jerry_get_arraybuffer_pointer(jVal);
    return AS_JSI_VALUE(jVal);
#else
    HILOG_ERROR(HILOG_MODULE_ACE, "JSI:CreateArrayBuffer has not been implemented in this js engine!");
    return CreateUndefined();
#endif
}

bool JSI::ValueIsArrayBuffer(JSIValue value)
{
#if defined(ENABLE_JERRY)
    return jerry_value_is_arraybuffer(AS_JERRY_VALUE(value));
#else
    HILOG_ERROR(HILOG_MODULE_ACE, "JSI:ValueIsArrayBuffer has not been implemented in this js engine!");
    return false;
#endif
}

bool JSI::ValueIsTypedArray(JSIValue value)
{
#if defined(ENABLE_JERRY)
    return jerry_value_is_typedarray(AS_JERRY_VALUE(value));
#else
    HILOG_ERROR(HILOG_MODULE_ACE, "JSI:ValueIsTypedArray has not been implemented in this js engine!");
    return false;
#endif
}
#endif // JS_FWK_TYPEDARRAY

bool JSI::DefineProperty(JSIValue object, JSIValue propName, JSPropertyDescriptor descriptor)
{
    if (!ValueIsObject(object)) {
        HILOG_ERROR(HILOG_MODULE_ACE, "JSI:DefineProperty failed!");
        return false;
    }
#if defined(ENABLE_JERRY)
    jerry_property_descriptor_t jerryDesc;
    jerry_init_property_descriptor_fields(&jerryDesc);

    jerryDesc.is_set_defined = true;
    jerryDesc.setter =
        (descriptor.setter == nullptr) ? jerry_create_undefined() : AS_JERRY_VALUE(CreateFunction(descriptor.setter));
    jerryDesc.is_get_defined = true;
    jerryDesc.getter =
        (descriptor.getter == nullptr) ? jerry_create_undefined() : AS_JERRY_VALUE(CreateFunction(descriptor.getter));

    jerry_value_t retValue = jerry_define_own_property(AS_JERRY_VALUE(object), AS_JERRY_VALUE(propName), &jerryDesc);
    jerry_free_property_descriptor_fields(&jerryDesc);

    bool res = true;
    if (jerry_value_is_error(retValue)) {
        res = false;
    }
    jerry_release_value(retValue);
    return res;
#else
    HILOG_ERROR(HILOG_MODULE_ACE, "JSI:DefineProperty has not been implemented in this js engine!");
    return false;
#endif
}

bool JSI::DefineNamedProperty(JSIValue object, const char * const propNameStr, JSPropertyDescriptor descriptor)
{
    if (!ValueIsObject(object) || (propNameStr == nullptr)) {
        HILOG_ERROR(HILOG_MODULE_ACE, "JSI:DefineNamedProperty failed!");
        return false;
    }
#if defined(ENABLE_JERRY)
    jerry_value_t propName = jerry_create_string(reinterpret_cast<const jerry_char_t *>(propNameStr));
    bool res = DefineProperty(object, AS_JSI_VALUE(propName), descriptor);
    jerry_release_value(propName);
    return res;
#else
    HILOG_ERROR(HILOG_MODULE_ACE, "JSI:DefineNamedProperty has not been implemented in this js engine!");
    return false;
#endif
}
} // namespace ACELite
} // namespace OHOS
