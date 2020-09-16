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

#ifndef OHOS_ACELITE_JSI_TYPES_H
#define OHOS_ACELITE_JSI_TYPES_H

#include <cstdint>

namespace OHOS {
namespace ACELite {
// opaque pointer for JSI abstract value
using JSIValue = struct JSIVal *;

// type used for initialization functions of built-in modules
using InitFunc = void(*)(JSIValue exports);

/**
 * type used for native callback of built-in modules
 * Note: this type is deprecated, use JsiCallback alternatively
 */
using NativeCallback = void(*)();

// type used for native callback of built-in modules
using JsiCallback = void(*)(int8_t statusCode);

// struct information for built-in modules
struct Module {
    const char* name;
    InitFunc initFunc;
};

// struct information for private modules
struct PrivateModule {
    const char* bundleName;
    Module module;
    PrivateModule(const PrivateModule &) = delete;
    PrivateModule &operator=(const PrivateModule &) = delete;
    PrivateModule(PrivateModule &&) = delete;
    PrivateModule &operator=(PrivateModule &&) = delete;
};

// constants for JSI API development
constexpr char CB_CALLBACK[] = "callback";
constexpr char CB_SUCCESS[] = "success";
constexpr char CB_FAIL[] = "fail";
constexpr char CB_COMPLETE[] = "complete";
constexpr uint8_t ARGC_ONE = 1;
constexpr uint8_t ARGC_TWO = 2;
constexpr uint8_t ARGC_THREE = 3;

// Error code used for callback processing
constexpr int8_t JSI_ERR_OK = 0;
constexpr int8_t JSI_ERR_FAIL = -1;

/**
 * @enum    TypedArrayType
 *
 * @brief   Values that represent different types of TypedArray object
 */
enum class TypedArrayType {
    JSI_INVALID_ARRAY,
    JSI_INT8_ARRAY,
    JSI_UINT8_ARRAY,
    JSI_UINT8CLAMPED_ARRAY,
    JSI_INT16_ARRAY,
    JSI_UINT16_ARRAY,
    JSI_INT32_ARRAY,
    JSI_UINT32_ARRAY,
    JSI_FLOAT32_ARRAY,
    JSI_FLOAT64_ARRAY,
    JSI_TYPE_MAX_ARRAY
};

/**
 * @enum    JsiErrorType
 *
 * @brief   Values that represent different types of error object
 */
enum class JsiErrorType {
    JSI_ERROR_INVALID,
    JSI_ERROR_COMMON,
    JSI_ERROR_EVAL,
    JSI_ERROR_RANGE,
    JSI_ERROR_REFERENCE,
    JSI_ERROR_SYNTAX,
    JSI_ERROR_TYPE,
    JSI_ERROR_URI,
    JSI_ERROR_MAX
};
} // namespace ACELite
} // namespace OHOS
#endif // OHOS_ACELITE_JSI_TYPES_H
