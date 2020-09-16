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

#ifndef OHOS_ACELITE_JS_H
#define OHOS_ACELITE_JS_H

#include "jerryscript.h"
#include "memory_heap.h"
#include <stdlib.h>

namespace OHOS {
namespace ACELite {
typedef jerry_value_t JSValue;
typedef jerry_size_t JSSize;
typedef JSValue (*JSHandler)(const JSValue func, const JSValue ctx, const JSValue args[], JSSize argsSize);

void JSRelease(JSValue value);

class JSString final : public MemoryHeap {
public:
    static JSValue Create(const char * const value);
    static bool Is(JSValue target);
    static char* Value(JSValue value);
};

class JSFunction final : public MemoryHeap {
public:
    static JSValue Create(JSHandler handler);
    static JSValue Call(JSValue func, JSValue context, JSValue args[], JSSize size);
    static bool Is(JSValue target);
};

class JSObject final : public MemoryHeap {
public:
    static JSValue Create();
    static JSValue Get(JSValue target, const char * const prop);
    static void Set(JSValue target, const char * const prop, JSValue value);
    static void Set(JSValue target, const char * const prop, JSHandler handler);
    static bool Del(JSValue target, const char * const prop);
    static JSValue Call(JSValue target, const char * const prop, JSValue args[], JSSize size);
    static JSValue Call(JSValue target, const char * const prop);
    static bool GetNativePointer(JSValue target, void** nativePointer);
    static void SetNativePointer(JSValue target, void* nativePointer);
    static bool DelNativePointer(JSValue target);
    static bool Is(JSValue target);
};

class JSGlobal final : public MemoryHeap {
public:
    static JSValue Get();
    static JSValue Get(const char * const prop);
    static void Set(const char * const prop, JSValue value);
    static JSValue Call(const char * const prop, JSValue args[], JSSize size);
    static JSValue Call(const char * const prop);
};

class JSUndefined final : public MemoryHeap {
public:
    static JSValue Create();
    static bool Is(JSValue value);
};

class JSNumber final : public MemoryHeap {
public:
    static JSValue Create(uint32_t number);
    static bool Is(JSValue target);
    static double Value(JSValue value);
};

class JSBoolean final : public MemoryHeap {
public:
    static JSValue Create(bool value);
    static bool Is(JSValue target);
    static bool Value(JSValue value);
};

class JSArray final : public MemoryHeap {
public:
    static JSValue Create(uint32_t size);
    static uint32_t Length(const JSValue array);
    static JSValue Get(JSValue array, uint32_t index);
    static JSValue Map(JSValue array, JSValue func);
    static void Push(JSValue array, JSValue element);
};
} // namespace ACELite
} // namespace OHOS
#endif // OHOS_ACELITE_JS_H
