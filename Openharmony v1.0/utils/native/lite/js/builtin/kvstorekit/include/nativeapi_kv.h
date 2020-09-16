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

#ifndef JS_NATIVE_API_KV_H
#define JS_NATIVE_API_KV_H

#include "jsi/jsi.h"

namespace OHOS {
namespace ACELite {
class NativeapiKv {
public:
    NativeapiKv() {}
    ~NativeapiKv() {}
    static JSIValue Get(const JSIValue thisVal, const JSIValue *args, uint8_t argsNum);
    static JSIValue Set(const JSIValue thisVal, const JSIValue *args, uint8_t argsNum);
    static JSIValue Delete(const JSIValue thisVal, const JSIValue *args, uint8_t argsNum);
    static JSIValue Clear(const JSIValue thisVal, const JSIValue *args, uint8_t argsNum);
};
} // ACELite
} // OHOS
#endif // JS_NATIVE_API_KV_H