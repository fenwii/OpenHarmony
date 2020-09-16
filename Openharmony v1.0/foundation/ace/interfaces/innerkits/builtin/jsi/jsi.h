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

#ifndef OHOS_ACELITE_JSI_H
#define OHOS_ACELITE_JSI_H

#include <cstdlib>

#include "jsi_types.h"
#include "memory_heap.h"

/**
 * Enable JS TypedArray type support.
 */
#ifndef JS_FWK_TYPEDARRAY
#define JS_FWK_TYPEDARRAY 1
#endif

/**
 * Disable JS Symbol value support.
 */
#ifndef JS_FWK_SYMBOL
#define JS_FWK_SYMBOL 0
#endif

namespace OHOS {
namespace ACELite {
/**
 * @brief End flag used in ReleaseValueList(JSIValue value, ...).
 */
static const JSIValue ARGS_END = (JSIValue)(uintptr_t)-1;

/**
 * @brief Function pointer type used to create function callback.
 *
 * @param [in] thisVal: the this value provided for the function call
 * @param [in] args: the function arguments, array of JavaScript values
 * @param [in] argsNum: the number of arguments
 */
typedef JSIValue (*JSIFunctionHandler)(const JSIValue thisVal, const JSIValue *args, uint8_t argsNum);

/**
 * @brief Description of JerryScript heap memory status.
 */
struct JSHeapStatus : public MemoryHeap {
    size_t totalBytes;     // heap total size
    size_t allocBytes;     // currently allocated bytes
    size_t peakAllocBytes; // peak allocated bytes

    JSHeapStatus(const JSHeapStatus &) = delete;
    JSHeapStatus &operator=(const JSHeapStatus &) = delete;
    JSHeapStatus(JSHeapStatus &&) = delete;
    JSHeapStatus &operator=(JSHeapStatus &&) = delete;
    JSHeapStatus() : totalBytes(0), allocBytes(0), peakAllocBytes(0) {}
};

/**
 * @brief Struct definition for JS property descriptor
 */
struct JSPropertyDescriptor : public MemoryHeap {
    JSIFunctionHandler setter; // access function for set value
    JSIFunctionHandler getter; // access function for get value

    JSPropertyDescriptor() : setter(nullptr), getter(nullptr) {}
};

/**
 * @brief JavaScriptInterface for adapatation to javascript engines.
 */
class JSI final : public MemoryHeap {
public:
    /**
     * @brief Get the global javascript object.
     *
     * @return the global object acquired
     * value returned should be released by caller with ReleaseValue when it won't be used any more
     */
    static JSIValue GetGlobalObject();

    /**
     * @brief Create a javascript object.
     *
     * @return the object created
     * value returned should be released by caller with ReleaseValue when it won't be used any more
     */
    static JSIValue CreateObject();

    /**
     * @brief Set property to given javascript object.
     *
     * @param [in] object: host object to set
     * @param [in] key: key of the property to set
     * @param [in] value: value of the property to set
     */
    static void SetProperty(JSIValue object, JSIValue key, JSIValue value);

    /**
     * @brief Set property to javascript object with given name.
     *
     * @param [in] object: host object to set
     * @param [in] propName: name of the property to set
     * @param [in] value: value of the property to set
     */
    static void SetNamedProperty(JSIValue object, const char * const propName, JSIValue value);

    /**
     * @brief Set number property to javascript object with given name.
     *
     * @param [in] object: host object to set
     * @param [in] propName: name of the number property to set
     * @param [in] value: number value of the property to set
     */
    static void SetNumberProperty(JSIValue object, const char * const propName, double value);

    /**
     * @brief Set boolean property to javascript object with given name.
     *
     * @param [in] object: host object to set
     * @param [in] propName: name of the boolean property to set
     * @param [in] value: boolean value of the property to set
     */
    static void SetBooleanProperty(JSIValue object, const char * const propName, bool value);

    /**
     * @brief Set string property to javascript object with given name.
     *
     * @param [in] object: host object to set
     * @param [in] propName: name of the string property to set
     * @param [in] value: string value of the property to set
     */
    static void SetStringProperty(JSIValue object, const char * const propName, const char *value);

    /**
     * @brief Create javascript functoin with given native function.
     *
     * @param [in] handler: native function pointer
     * @return javascript function object
     * value returned should be released by caller with ReleaseValue when it won't be used any more
     */
    static JSIValue CreateFunction(JSIFunctionHandler handler);

    /**
     * @brief Create javascript string object with character string.
     *
     * @param [in] str: string source
     * @return the string object created
     * value returned should be released by caller with ReleaseValue when it won't be used any more
     */
    static JSIValue CreateString(const char * const str);

    /**
     * @brief Create an undefined object.
     *
     * @return the undefined object created
     * value returned should be released by caller with ReleaseValue when it won't be used any more
     */
    static JSIValue CreateUndefined();

    /**
     * @brief Check if the specified value is a function object value, the value must be created by jerry interface.
     *
     * @param [in] value: value to check
     * @return true: if the given value is a function
     *         false: otherwise
     */
    static bool ValueIsFunction(JSIValue value);

    /**
     * @brief Check if the specified value is undefined.
     *
     * @param [in] value: value to check
     * @return true: if the given value is undefined
     *         false: otherwise
     */
    static bool ValueIsUndefined(JSIValue value);

    /**
     * @brief Check if the specified value is a number.
     *
     * @param [in] value: value to check
     * @return true: if the given value is a number
     *         false: otherwise
     */
    static bool ValueIsNumber(JSIValue value);

    /**
     * @brief Check if the specified value is a string value.
     *
     * @param [in] value: value to check
     * @return true: if the given value is a string value
     *         false: otherwise
     */
    static bool ValueIsString(JSIValue value);

    /**
     * @brief Check if the specified value is a boolean value.
     *
     * @param [in] value: value to check
     * @return true: if the given value is a boolean value
     *         false: otherwise
     */
    static bool ValueIsBoolean(JSIValue value);

    /**
     * @brief Check if the specified value is a null value.
     *
     * @param [in] value: value to check
     * @return true: if the given value is a null value
     *         false: otherwise
     */
    static bool ValueIsNull(JSIValue value);

    /**
     * @brief Check if the specified value is an object value.
     *
     * @param [in] value: value to check
     * @return true: if the given value is an object value
     *         false: otherwise
     */
    static bool ValueIsObject(JSIValue value);

    /**
     * @brief Check if the specified value is error value.
     *
     * @param [in] value: value to check
     * @return true: if the given value is error value
     *         false: otherwise
     */
    static bool ValueIsError(JSIValue value);

    /**
     * @brief Get the same value as json.stringify().
     *
     * @param [in] value: value which can be json stringfied
     * @return the json string created
     * value returned should be released with ReleaseString(char *&str) when it won't be used any more
     */
    static char *JsonStringify(JSIValue value);

    /**
     * @brief Get the same value as json.parse().
     *
     * @param [in] str: character string which is in json pattern
     * @return JSI value created
     * value returned should be released by caller with ReleaseValue when it won't be used any more
     */
    static JSIValue JsonParse(const char * const str);

    /**
     * @brief Get value of a property from the specified object with the given key.
     *
     * @param [in] object: object value
     * @param [in] key: property name
     * @return acquired value of the property
     * value returned should be released by caller with ReleaseValue when it won't be used any more
     */
    static JSIValue GetProperty(JSIValue object, JSIValue key);

    /**
     * @brief Get value of a property from the specified object with the given character name.
     *
     * @param [in] object: object value
     * @param [in] propName: property name in character string
     * @return acquired value of the property
     * value returned should be released by caller with ReleaseValue when it won't be used any more
     */
    static JSIValue GetNamedProperty(JSIValue object, const char * const propName);

    /**
     * @brief Get number value from the specified object with the given property name.
     *
     * @param [in] object: object value
     * @param [in] propName: the number property name
     * @return number value acquired
     * 0.0 will be returned if the argument passed is not a number object
     */
    static double GetNumberProperty(JSIValue object, const char * const propName);

    /**
     * @brief Get boolean value from the specified object with the given property name.
     *
     * @param [in] object: object value
     * @param [in] propName: the boolean property name
     * @return true: if the property value is logical true
     *         false: otherwise
     */
    static bool GetBooleanProperty(JSIValue object, const char * const propName);

    /**
     * @brief Get string value from the specified object with the given property name.
     *
     * @param [in] object: object value
     * @param [in] propName: the string property name
     * @return the string value acquired
     * value returned should be released with ReleaseString(char *&str) when it won't be used any more
     */
    static char *GetStringProperty(JSIValue object, const char * const propName);

    /**
     * @brief: Release specified API value.
     *
     * @param: value JSI value to release
     */
    static void ReleaseValue(JSIValue value);

    static void ReleaseValueList() {}

    /**
     * @brief: Release API value list.
     *
     * @param: JSI value list to release
     */
    template<class T, class... Args> static void ReleaseValueList(T head, Args... rest)
    {
        ReleaseValue(head);
        ReleaseValueList(rest...);
    }

    /**
     * @brief: Release string value.
     *
     * @param: str: pointer to the buffer to be released
     */
    static void ReleaseString(char *&str);

    /**
     * @brief Call javascript function specified by a function value.
     *
     * @param [in] funcObj: the function object to call
     * @param [in] thisVal: object for 'this' binding
     * @param [in] argv:  function's call arguments
     * @param [in] argc: number of arguments
     */
    static void CallFunction(JSIValue funcObj, JSIValue thisVal, const JSIValue *argv, uint8_t argc);

    /**
     * @brief Create javascript number value.
     *
     * @param [in] value: source number
     * @return the number value created
     * value returned should be released by caller with ReleaseValue when it won't be used any more
     */
    static JSIValue CreateNumber(double value);

    /**
     * @brief Create a JSIValue representing a not-a-number value.
     *
     * @return a JSIValue representing the not-a-number value
     * value returned should be released by caller with ReleaseValue when it won't be used any more
     */
    static JSIValue CreateNumberNaN();

    /**
     * @brief Create javascript error object.
     *
     * @param [in] type: error type
     * @param [in] errorMsg: value of 'message' property of constructed error object
     * @return value of the constructed error object
     * value returned should be released by caller with ReleaseValue when it won't be used any more
     */
    static JSIValue CreateError(JsiErrorType type, const char * const errorMsg);

    /**
     * @brief Get the type of the error object.
     *
     * @param [in] errorValue: error value to get
     * @return the type of the error object
     */
    static JsiErrorType GetErrorType(JSIValue errorValue);

    /**
     * @brief Create javascript boolean value.
     *
     * @param [in] value: bool value
     * @return the boolean value created
     * value returned should be released by caller with ReleaseValue when it won't be used any more
     */
    static JSIValue CreateBoolean(bool value);

    /**
     * @brief Create javascript null object.
     *
     * @return the null object created
     * value returned should be released by caller with ReleaseValue when it won't be used any more
     */
    static JSIValue CreateNull();

#ifdef JS_FWK_SYMBOL
    /**
     * @brief Create a javascript symbol.
     *
     * @param [in] description: source value
     * @return the symbol object created
     * value returned should be released by caller with ReleaseValue when it won't be used any more
     */
    static JSIValue CreateSymbol(JSIValue description);

    /**
     * @brief Check if the specified value is a symbol value.
     *
     * @param [in] value: value to check
     * @return true: if the given value is a symbol value
     *         false: otherwise
     */
    static bool ValueIsSymbol(JSIValue value);
#endif // JS_FWK_SYMBOL

    /**
     * @brief Create a javascript array.
     *
     * @param [in] length: array length
     * @return the array object created
     * value returned should be released by caller with ReleaseValue when it won't be used any more
     */
    static JSIValue CreateArray(uint32_t length);

    /**
     * @brief Set indexed value in the specified javascript object.
     *
     * @param [in] object: object to set
     * @param [in] index: index number
     * @param [in] value: value to set
     * @return true: if the operation succeed
     *         false: otherwise
     */
    static bool SetPropertyByIndex(JSIValue object, uint32_t index, JSIValue value);

    /**
     * @brief Get the string value of the given JSIValue object.
     *
     * @param [in] value: source value
     * @return the string value created
     * value returned should be released with ReleaseString(char *&str) when it won't be used any more
     */
    static char *ValueToString(JSIValue value);

    /**
     * @brief Get the number value of the given JSIValue object.
     *
     * @param [in] value: source value
     * @return double value acquired
     * 0.0 will be returned if the argument passed is not a number object
     */
    static double ValueToNumber(JSIValue value);

    /**
     * @brief Get the boolean value of the given JSIValue object.
     *
     * @param [in] value: source value
     * @return true: if the given value is logical true
     *         false: otherwise
     */
    static bool ValueToBoolean(JSIValue value);

    /**
     * @brief Check if the specified value is an array object.
     *
     * @param [in] value: array value
     * @return array length acquired
     * 0 will be returned if the argument passed is not an array object
     */
    static uint32_t GetArrayLength(JSIValue value);

    /**
     * @brief Get indexed value from the javascript array object.
     *
     * @param [in] object: source array object
     * @param [in] index: index number
     * @return value acquired from the specified index of the array
     * value returned should be released by caller with ReleaseValue when it won't be used any more
     */
    static JSIValue GetPropertyByIndex(JSIValue object, uint32_t index);

    /**
     * @brief Get keys of the specified object value.
     *
     * @param [in] object: object value
     * @return array object of the given object keys
     * value returned should be released by caller with ReleaseValue when it won't be used any more
     */
    static JSIValue GetObjectKeys(JSIValue object);

    /**
     * @brief Get heap memory status.
     *
     * @param [out] heapStatus: struct for heap memory status acquired
     * @return true: if the operation succeed
     *         false: otherwise
     */
    static bool GetJSHeapStatus(JSHeapStatus &heapStatus);

    /**
     * @brief Check if the specified value is an array object.
     *
     * @param [in] value: value to check
     * @return true: if the given value is an array object
     *         false: otherwise
     */
    static bool ValueIsArray(JSIValue value);

    /**
     * @brief Acquire the specified JSI value to create a reference
     *
     * @param [in] value: JSI value to acquire
     * @return acquired value that may be used outside of the engine
     * value returned should be released by caller with ReleaseValue when it won't be used any more
     */
    static JSIValue AcquireValue(JSIValue value);

    /**
     * @brief Set API for given exports object
     *
     * @param [in] exports: object to set
     * @param [in] name: API name
     * @param [in] handler: pointer to the native implementation of this JS API
     */
    static void SetModuleAPI(JSIValue exports, const char * const name, JSIFunctionHandler handler);

    /**
     * @brief Set JS page destroy callback on given module object
     *
     * @param [in] object: JS module object
     * @param [in] callback: native destroy callback
     * Note: this function is deprecated, use the other one alternatively
     */
    static void SetOnDestroy(JSIValue object, NativeCallback callback);

    /**
     * @brief set JS page destroy callback on given module object
     *
     * @param [in] object: JS module object
     * @param [in] callback: native destroy callback
     */
    static void SetOnDestroy(JSIValue object, JsiCallback callback);

    /**
     * @brief set JS ability terminate callback on given module object
     *
     * @param [in] object: JS module object
     * @param [in] callback: native terminate callback
     * Note: this function is deprecated, use the other one alternatively
     */
    static void SetOnTerminate(JSIValue object, NativeCallback callback);

    /**
     * @brief set JS ability terminate callback on given module object
     *
     * @param [in] object: JS module object
     * @param [in] callback: native terminate callback
     */
    static void SetOnTerminate(JSIValue object, JsiCallback callback);

#ifdef JS_FWK_TYPEDARRAY
    /**
     * @brief Get the properties of the given javascript TypedArray object.
     *
     * @param [in] typedArray: TypedArray object
     * @param [out] type: type of the TypedArray, one of the TypedArrayType enum value
     * @param [out] length: the element number of the TypedArray
     * 0 if the typedArray parameter is not a TypedArray object
     * @param [out] arrayBuffer: the ArrayBuffer object used by the TypedArray object
     * value should be released by caller with ReleaseValue when it won't be used any more
     * @param [out] byteOffset: the start offset of the ArrayBuffer for the TypedArray
     * @return pointer to the Array Buffer's data area
     * must ensure that the output pointer is used correctly, that is there is no out of bounds reads or writes
     * the lifetime of the underlying data buffer is managed by the ArrayBuffer value, thus, do not release the
     * pointer returned
     */
    static uint8_t *GetTypedArrayInfo(JSIValue typedArray,
                                      TypedArrayType &type,
                                      size_t &length,
                                      JSIValue &arrayBuffer,
                                      size_t &byteOffset);

    /**
     * @brief Create a TypedArray object using an already existing ArrayBuffer object.
     *
     * @param [in] type: type of the TypedArray, one of the TypedArrayType enum value
     * @param [in] length: the element number of the TypedArray
     * @param [in] arrayBuffer: the ArrayBuffer object to use for the new TypedArray
     * @param [in] byteOffset: the start offset of the ArrayBuffer for the TypedArray
     * @return the TypedArray object created
     * value returned should be released by caller with ReleaseValue when it won't be used any more.
     */
    static JSIValue CreateTypedArray(TypedArrayType type, size_t length, JSIValue arrayBuffer, size_t byteOffset);

    /**
     * @brief Get the properties of the given ArrayBuffer object.
     *
     * @param [in] arrayBuffer: ArrayBuffer object
     * @param [out] byteLength size of the ArrayBuffer in bytes
     * 0 if the arrayBuffer parameter is not an ArrayBuffer object
     * @return pointer to the Array Buffer's data area
     * must ensure that the output pointer is used correctly, that is there is no out of bounds reads or writes
     * the lifetime of the underlying data buffer is managed by the ArrayBuffer value, thus, do not release the
     * pointer returned
     */
    static uint8_t *GetArrayBufferInfo(JSIValue arrayBuffer, size_t &byteLength);

    /**
     * @brief Create an ArrayBuffer object.
     *
     * @param [in] byteLength: size of the ArrayBuffer to create in bytes
     * @param [out] buffPtr: pointer to the Array Buffer's data area
     * must ensure that the output pointer is used correctly, that is there is no out of bounds reads or writes
     * the lifetime of the underlying data buffer is managed by the ArrayBuffer value, thus, do not release the pointer
     * @return the ArrayBuffer object created
     * result should be released by caller with ReleaseValue when it won't be used any more
     */
    static JSIValue CreateArrayBuffer(size_t byteLength, uint8_t *&buffPtr);

    /**
     * @brief Check if the specified value is an ArrayBuffer object.
     *
     * @param [in] value: value to check
     * @return true: if the given value is an ArrayBuffer object
     *         false: otherwise
     */
    static bool ValueIsArrayBuffer(JSIValue value);

    /**
     * @brief Check if the specified value is a TypedArray object.
     *
     * @param [in] value: value to check
     * @return true: if the given value is an TypedArray object
     *         false: otherwise
     */
    static bool ValueIsTypedArray(JSIValue value);
#endif // JS_FWK_TYPEDARRAY

    /**
     * @brief Define a property on the specified object with the given name.
     *
     * @param [in] object: object to define property on
     * @param [in] propName: property name
     * @param [in] descriptor: property descriptor
     * @return true: if success
     *         false: otherwise
     */
    static bool DefineProperty(JSIValue object, JSIValue propName, JSPropertyDescriptor descriptor);

    /**
     * @brief Define a property on the specified object with the given character name.
     *
     * @param [in] object: object to define property on
     * @param [in] propNameStr: property name in character string
     * @param [in] descriptor: property descriptor
     * @return true: if success
     *         false: otherwise
     */
    static bool DefineNamedProperty(JSIValue object, const char * const propNameStr, JSPropertyDescriptor descriptor);

private:
    // private constructor for singleton instance
    JSI() {}
    ~JSI() {}
    static void SetNamedPointer(JSIValue object, const char * const name, JsiCallback callback);
};
} // namespace ACELite
} // namespace OHOS

#endif // OHOS_ACELITE_JSI_H
