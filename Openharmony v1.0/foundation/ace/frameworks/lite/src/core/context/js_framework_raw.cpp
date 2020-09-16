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
#include "js_framework_raw.h"

#include <cstring>

namespace OHOS {
namespace ACELite {
// The following two header files should can only be included from this source file,
// define one macro to alert any incorrect using.
#define ACELITE_FRAMEWORK_RAW_BUFFER
// The build result from `js/framework`
#include "framework_min_bc.h"
#include "framework_min_js.h"

const char *GetFrameworkRawBuffer(bool snapshotMode, size_t &bufLen)
{
    if (snapshotMode) {
        bufLen = sizeof(g_frameworkBCBuffer);
        return g_frameworkBCBuffer;
    } else {
        bufLen = strlen(g_frameworkJSBuffer);
        return g_frameworkJSBuffer;
    }
}
} // namespace ACELite
} // namespace OHOS
