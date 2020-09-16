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

#ifndef JS_NATIVE_API_FS_H
#define JS_NATIVE_API_FS_H

#include "jsi/jsi.h"
#include "nativeapi_config.h"

namespace OHOS {
namespace ACELite {
class NativeapiFs {
public:
    NativeapiFs() {}
    ~NativeapiFs() {}

    static JSIValue MoveFile(const JSIValue thisVal, const JSIValue* args, uint8_t argsNum);
    static JSIValue CopyFile(const JSIValue thisVal, const JSIValue* args, uint8_t argsNum);
    static JSIValue DeleteFile(const JSIValue thisVal, const JSIValue* args, uint8_t argsNum);
    static JSIValue GetFileList(const JSIValue thisVal, const JSIValue* args, uint8_t argsNum);
    static JSIValue GetFileInfo(const JSIValue thisVal, const JSIValue* args, uint8_t argsNum);
    static JSIValue WriteTextFile(const JSIValue thisVal, const JSIValue* args, uint8_t argsNum);
    static JSIValue ReadTextFile(const JSIValue thisVal, const JSIValue* args, uint8_t argsNum);
    static JSIValue Access(const JSIValue thisVal, const JSIValue* args, uint8_t argsNum);
    static JSIValue CreateDir(const JSIValue thisVal, const JSIValue* args, uint8_t argsNum);
    static JSIValue RemoveDir(const JSIValue thisVal, const JSIValue* args, uint8_t argsNum);

#if (JS_FWK_TYPEDARRAY == NATIVE_FEATURE_ON)
    static JSIValue ReadArrayFile(const JSIValue thisVal, const JSIValue* args, uint8_t argsNum);
    static JSIValue WriteArrayFile(const JSIValue thisVal, const JSIValue* args, uint8_t argsNum);
#endif /* JS_FWK_TYPEDARRAY */
};
} // ACELite
} // OHOS

#endif /* JS_NATIVE_API_FS_H */
