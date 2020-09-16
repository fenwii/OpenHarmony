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

#include "version_module.h"
#if ENABLED(ACE_LITE_VERSION_JS_API)
#include "ace_log.h"
#include "ace_version.h"
#include "platform_adapter.h"

namespace OHOS {
namespace ACELite {
void VersionModule::Init()
{
    constexpr char FUNC_GET_VERSION[] = "getAceVersion";
    constexpr char FUNC_GET_COMMIT[] = "getAceCommit";
    constexpr char FUNC_GET_STAMP[] = "getAceStamp";
    CreateNamedFunction(FUNC_GET_VERSION, GetACEVersion);
    CreateNamedFunction(FUNC_GET_COMMIT, GetACECommit);
    CreateNamedFunction(FUNC_GET_STAMP, GetACEBuildStamp);
    PrintVersionTrace();
}

jerry_value_t VersionModule::GetACEVersion(const jerry_value_t func,
                                           const jerry_value_t context,
                                           const jerry_value_t args[],
                                           const jerry_length_t argsNum)
{
    const char * const versionStr = ACEVersion::GetStr();
    return jerry_create_string(reinterpret_cast<const jerry_char_t *>(versionStr));
}

jerry_value_t VersionModule::GetACECommit(const jerry_value_t func,
                                          const jerry_value_t context,
                                          const jerry_value_t args[],
                                          const jerry_length_t argsNum)
{
    const char * const commitStr = ACEVersion::GetCommit();
    return jerry_create_string(reinterpret_cast<const jerry_char_t *>(commitStr));
}

jerry_value_t VersionModule::GetACEBuildStamp(const jerry_value_t func,
                                              const jerry_value_t context,
                                              const jerry_value_t args[],
                                              const jerry_length_t argsNum)
{
    const char * const stampStr = ACEVersion::GetTimeStamp();
    return jerry_create_string(reinterpret_cast<const jerry_char_t *>(stampStr));
}
} // namespace ACELite
} // namespace OHOS
#endif // ENABLED(ACE_LITE_VERSION_JS_API)