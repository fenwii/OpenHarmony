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

#ifndef OHOS_GT_BUNDLE_EXTRACTOR_UTIL_H
#define OHOS_GT_BUNDLE_EXTRACTOR_UTIL_H

#include "stdint.h"

namespace OHOS {
class GtExtractorUtil {
public:
    static uint8_t ExtractFileHeaderInfo(int32_t fp, char **bundleName);
    static uint8_t ExtractFileToPath(const char *appInstallPath, int32_t fp, uint64_t &fileSize, char **fileName,
        char **relativeFilePath);
    static uint8_t ExtractFileAttr(int32_t fp, uint64_t &fileSize, char **fileName, char **relativeFilePath);
    static bool CheckMagicNumber(int32_t fp);
private:
    static uint32_t ReadInt(int32_t fp);
    static uint64_t ReadLong(int32_t fp);
    static char *ReadString(int32_t fp, uint32_t len);
    static bool HasCopiedData(const char *filePath, int32_t fp, uint64_t size);
    static bool HasWrittenFile(const char *installPath, const char *path, const char *name, int32_t fp, uint64_t size);
};
} // namespace OHOS
#endif // OHOS_GT_BUNDLE_EXTRACTOR_UTIL_H
