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

#ifndef OHOS_BUNDLE_EXTRACTOR_UTIL_H
#define OHOS_BUNDLE_EXTRACTOR_UTIL_H

#include "stdint.h"
#include "zip_file.h"

#include <string>
#include <vector>

namespace OHOS {
class ExtractorUtil {
public:
    explicit ExtractorUtil(const std::string &filePath);
    ~ExtractorUtil();
    bool Init();
    bool ExtractFileByName(const std::string &fileName, std::ostream &dest) const;
    const std::vector<std::string> &GetZipFileNames() const;
    bool ExtractFileToPath(const std::string &filePath, const std::string &fileName) const;
private:
    ZipFile zipFile_;
    bool initial_ { false };
};
} // namespace OHOS
#endif // OHOS_BUNDLE_EXTRACTOR_UTIL_H
