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

#ifndef OHOS_ACELITE_APP_MODULE_H
#define OHOS_ACELITE_APP_MODULE_H

#include <cJSON.h>
#include "jsi.h"
#include "non_copyable.h"

namespace OHOS {
namespace ACELite {
class AppModule final : public MemoryHeap {
public:
    ACE_DISALLOW_COPY_AND_MOVE(AppModule);
    AppModule() = default;
    ~AppModule() = default;
    static JSIValue GetInfo(const JSIValue thisVal, const JSIValue* args, uint8_t argsNum);
    static JSIValue Terminate(const JSIValue thisVal, const JSIValue* args, uint8_t argsNum);

private:
    static const char * const FILE_MANIFEST;
    static const char * const KEY_APP_NAME;
    static const char * const KEY_VERSION_NAME;
    static const char * const KEY_VERSION_CODE;

    static cJSON* ReadManifest();
};
void InitAppModule(JSIValue exports)
{
    JSI::SetModuleAPI(exports, "getInfo", AppModule::GetInfo);
    JSI::SetModuleAPI(exports, "terminate", AppModule::Terminate);
}
} // namespace ACELite
} // namespace OHOS
#endif // OHOS_ACELITE_APP_MODULE_H
