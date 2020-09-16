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

// THIS FILE IS AUTO GENERATED, PLEASE DO NOT EDIT DIRECTLY

#ifndef OHOS_ACELITE_ACE_VERSION_H
#define OHOS_ACELITE_ACE_VERSION_H

#include "js_config.h"

#if ENABLED(ACE_LITE_VERSION_JS_API)

namespace OHOS {
namespace ACELite {
class ACEVersion final {
public:
    static const char* GetStr()
    {
        return "1.0.16";
    }

    static const char* GetCommit()
    {
        return "1e53ee81c";
    }

    static const char* GetTimeStamp()
    {
        return "2020-08-13 17:25:20";
    }
}; // class ACEVersion
} // namespace ACELite
} // namespace OHOS

#endif // ENABLED(ACE_LITE_VERSION_JS_API)
#endif // OHOS_ACELITE_ACE_VERSION_H
