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

#include "extractor_util.h"

#include <fstream>

#include "log.h"

namespace OHOS {
ExtractorUtil::ExtractorUtil(const std::string &filePath) : zipFile_(filePath) {}

ExtractorUtil::~ExtractorUtil() {}

bool ExtractorUtil::Init()
{
    if (!zipFile_.Open()) {
        HILOG_ERROR(HILOG_MODULE_APP, "zipfile open fail");
        return false;
    }
    initial_ = true;
    return true;
}

bool ExtractorUtil::ExtractFileByName(const std::string &fileName, std::ostream &dest) const
{
    if (!initial_) {
        return false;
    }
    if (!zipFile_.ExtractFile(fileName, dest)) {
        HILOG_ERROR(HILOG_MODULE_APP, "ExtractFile open fail");
        return false;
    }
    return true;
}

bool ExtractorUtil::ExtractFileToPath(const std::string &filePath, const std::string &fileName) const
{
    std::ofstream fileStream;
    fileStream.open(filePath, std::ios_base::out | std::ios_base::binary);
    if (!fileStream.is_open()) {
        HILOG_ERROR(HILOG_MODULE_APP, "ExtractFileToPath fileStream open fail");
        return false;
    }
    if ((!zipFile_.ExtractFile(fileName, fileStream)) || (!fileStream.good())) {
        fileStream.clear();
        fileStream.close();
        remove(filePath.c_str());
        return false;
    }
    fileStream.clear();
    fileStream.close();
    return true;
}

const std::vector<std::string> &ExtractorUtil::GetZipFileNames() const
{
    return zipFile_.GetFileNames();
}
} // namespace OHOS