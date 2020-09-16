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

#ifndef OHOS_BUNDLE_FILE_UTILS_H
#define OHOS_BUNDLE_FILE_UTILS_H

#include <cstdint>
#include <string>

#include "nocopyable.h"
#include "utils_list.h"

namespace OHOS {
namespace {
const char PATH_SEPARATOR = '/';
}
class BundleFileUtils : public NoCopyable {
public:
    static bool MkRecursiveDir(const char *dir, bool isReadOthers);
    static bool IsExistDir(const char *path);
    static bool IsExistFile(const char *file);
    static bool RemoveFile(const char *path);
    static bool RenameFile(const char *oldDir, const char *newDir);
    static bool ChownFile(const char *file, int32_t uid, int32_t gid);
    static bool WriteFile(const char *file, const void *buffer, uint32_t size);
    static bool IsValidPath(const std::string &rootDir, const std::string &path);
    static std::string GetPathDir(const std::string &path);
};
} // OHOS
#endif // OHOS_BUNDLE_FILE_UTILS_H
