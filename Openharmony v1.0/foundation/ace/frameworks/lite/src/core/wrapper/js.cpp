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

#include "ace_mem_base.h"
#include "acelite_config.h"
#include "wrapper/js.h"

namespace OHOS {
namespace ACELite {
void JSRelease(JSValue value)
{
    return jerry_release_value(value);
}

JSValue JSString::Create(const char * const value)
{
    return jerry_create_string(reinterpret_cast<const jerry_char_t*>(value));
}

bool JSString::Is(JSValue target)
{
    return jerry_value_is_string(target);
}

char* JSString::Value(JSValue value)
{
    if (jerry_value_is_undefined(value)) {
        return nullptr;
    }

    jerry_value_t target;
    if (jerry_value_is_symbol(value)) {
        target = jerry_get_symbol_descriptive_string(value);
    } else {
        target = jerry_value_to_string(value);
    }

    if (jerry_value_is_error(target)) {
        jerry_release_value(target);
        return nullptr;
    }

    jerry_size_t size = jerry_get_string_size(target);
    if (size == 0) {
        jerry_release_value(target);
        // return empty char instead of nullptr, so caller can free safely
        char* emptyStr = static_cast<char *>(ace_malloc(sizeof(char)));
        if (emptyStr == nullptr) {
            return nullptr;
        }
        emptyStr[0] = '\0';
        return emptyStr;
    }
    if (size >= UINT16_MAX) {
        jerry_release_value(target);
        return nullptr;
    }
    jerry_char_t* buffer = static_cast<jerry_char_t *>(ace_malloc(sizeof(jerry_char_t) * (size + 1)));
    if (buffer == nullptr) {
        jerry_release_value(target);
        return nullptr;
    }
    jerry_size_t length = jerry_string_to_char_buffer(target, buffer, size);
    if (length == 0) {
        jerry_release_value(target);
        ace_free(buffer);
        buffer = nullptr;
        return nullptr;
    }
    // end character
    buffer[length] = '\0';
    jerry_release_value(target);
    return reinterpret_cast<char *>(buffer);
}

JSValue JSFunction::Create(JSHandler handler)
{
    return jerry_create_external_function(handler);
}

JSValue JSFunction::Call(JSValue func, JSValue context, JSValue args[], JSSize size)
{
    return jerry_call_function(func, context, args, size);
}

bool JSFunction::Is(JSValue target)
{
    return jerry_value_is_function(target);
}

JSValue JSObject::Create()
{
    return jerry_create_object();
}

JSValue JSObject::Get(JSValue target, const char * const prop)
{
    JSValue key = JSString::Create(prop);
    JSValue value = jerry_get_property(target, key);
    JSRelease(key);
    return value;
}

void JSObject::Set(JSValue target, const char * const prop, JSValue value)
{
    JSValue key = JSString::Create(prop);
    jerry_release_value(jerry_set_property(target, key, value));
    JSRelease(key);
}

void JSObject::Set(JSValue target, const char * const prop, JSHandler handler)
{
    JSValue func = JSFunction::Create(handler);
    JSObject::Set(target, prop, func);
    JSRelease(func);
}

bool JSObject::Del(JSValue target, const char * const prop)
{
    JSValue key = JSString::Create(prop);
    bool result = jerry_delete_property(target, key);
    JSRelease(key);
    return result;
}

bool JSObject::GetNativePointer(JSValue target, void** nativePointer)
{
    return jerry_get_object_native_pointer(target, nativePointer, nullptr);
}

void JSObject::SetNativePointer(JSValue target, void* nativePointer)
{
    return jerry_set_object_native_pointer(target, nativePointer, nullptr);
}

bool JSObject::DelNativePointer(JSValue target)
{
    return jerry_delete_object_native_pointer(target, nullptr);
}

JSValue JSObject::Call(JSValue target, const char * const prop, JSValue args[], JSSize size)
{
    JSValue func = Get(target, prop);
    JSValue value = JSFunction::Call(func, target, args, size);
    JSRelease(func);
    return value;
}

JSValue JSObject::Call(JSValue target, const char * const prop)
{
    return JSObject::Call(target, prop, nullptr, 0);
}

bool JSObject::Is(JSValue target)
{
    return jerry_value_is_object(target);
}

JSValue JSGlobal::Get()
{
    return jerry_get_global_object();
}

JSValue JSGlobal::Get(const char * const prop)
{
    JSValue global = JSGlobal::Get();
    JSValue result = JSObject::Get(global, prop);
    JSRelease(global);
    return result;
}

void JSGlobal::Set(const char * const prop, JSValue value)
{
    JSValue global = JSGlobal::Get();
    JSObject::Set(global, prop, value);
    JSRelease(global);
}

JSValue JSGlobal::Call(const char * const prop, JSValue args[], JSSize size)
{
    JSValue global = JSGlobal::Get();
    JSValue result = JSObject::Call(global, prop, args, size);
    JSRelease(global);
    return result;
}
JSValue JSGlobal::Call(const char * const prop)
{
    return JSGlobal::Call(prop, nullptr, 0);
}

JSValue JSUndefined::Create()
{
    return jerry_create_undefined();
}

bool JSUndefined::Is(JSValue value)
{
    return jerry_value_is_undefined(value);
}

JSValue JSNumber::Create(uint32_t number)
{
    return jerry_create_number(number);
}

bool JSNumber::Is(JSValue target)
{
    return jerry_value_is_number(target);
}

double JSNumber::Value(JSValue value)
{
    return jerry_get_number_value(value);
}

JSValue JSBoolean::Create(bool value)
{
    return jerry_create_boolean(value);
}

bool JSBoolean::Is(JSValue target)
{
    return jerry_value_is_boolean(target);
}

bool JSBoolean::Value(JSValue value)
{
    return jerry_get_boolean_value(value);
}

JSValue JSArray::Create(uint32_t size)
{
    return jerry_create_array(size);
}

uint32_t JSArray::Length(const JSValue array)
{
    return jerry_get_array_length(array);
}

JSValue JSArray::Get(JSValue array, uint32_t index)
{
    return jerry_get_property_by_index(array, index);
}

JSValue JSArray::Map(JSValue array, JSValue func)
{
    JSValue args[1] = {func};
    return JSObject::Call(array, "map", args, 1);
}

void JSArray::Push(JSValue array, JSValue element)
{
    JSValue args[1] = {element};
    JSRelease(JSObject::Call(array, "push", args, 1));
}
} // namespace ACELite
} // namespace OHOS
