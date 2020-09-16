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

#ifndef OHOS_BUNDLE_DAEMON_HANDLER_H
#define OHOS_BUNDLE_DAEMON_HANDLER_H

#include <cstdint>

#include "nocopyable.h"
#include "ohos_types.h"

namespace OHOS {
class BundleDaemonHandler : public NoCopyable {
public:
    int32 ExtractHap(const char *hapPath, const char *codePath);
    int32 RenameFile(const char *oldFile, const char *newFile);
    int32 CreatePermissionDir();
    int32 CreateDataDirectory(const char *dataPath, int32_t uid, int32_t gid, bool isChown);
    int32 StoreContentToFile(const char *filePath, const void *buffer, uint32_t size);
    int32 RemoveFile(const char *file);
    int32 RemoveInstallDirectory(const char *codePath, const char *dataPath);
private:
    bool IsValideCodePath(const char *codePath);
    bool IsValideDataPath(const char *codePath);
    bool IsValideJsonPath(const char *jsonPath);
    bool IsValideSystemPath(const char *jsonPath);
};
} // OHOS
#endif // OHOS_BUNDLE_DAEMON_HANDLER_H
