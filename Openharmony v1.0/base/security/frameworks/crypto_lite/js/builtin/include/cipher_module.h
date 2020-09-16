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

#ifndef OHOS_ACELITE_CIPHER_MODULE_H
#define OHOS_ACELITE_CIPHER_MODULE_H

#include "jsi.h"

namespace OHOS {
namespace ACELite {
class CipherModule final : public MemoryHeap {
public:
    CipherModule() {}
    ~CipherModule() {}
    static JSIValue Rsa(const JSIValue thisVal, const JSIValue *args, uint8_t argsNum);
    static JSIValue Aes(const JSIValue thisVal, const JSIValue *args, uint8_t argsNum);
private:
    static constexpr uint8_t ERR_CODE = 200;
    static void ResetStrBuf(char *strBuf);
};

void InitCipherModule(JSIValue exports)
{
    JSI::SetModuleAPI(exports, "rsa", CipherModule::Rsa);
    JSI::SetModuleAPI(exports, "aes", CipherModule::Aes);
}
} // namespace ACELite
} // namespace OHOS
#endif // OHOS_ACELITE_CIPHER_MODULE_H
