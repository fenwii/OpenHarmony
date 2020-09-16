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

#include "gt_bundle_extractor.h"

#include "adapter.h"
#include "appexecfwk_errors.h"
#include "bundle_util.h"
#include "gt_extractor_util.h"
#include "mc_fs.h"
#include "utils.h"

namespace OHOS {
uint8_t GtBundleExtractor::ExtractFileDataPos(int32_t fp, uint64_t &filePos)
{
    char *bundleName = nullptr;

    int32_t ret = lseek(fp, 0, SEEK_SET);
    if (ret < 0) {
        return ERR_APPEXECFWK_INSTALL_FAILED_INTERNAL_ERROR;
    }

    uint8_t errorCode = GtExtractorUtil::ExtractFileHeaderInfo(fp, &bundleName);
    if (errorCode != ERR_OK) {
        return errorCode;
    }

    filePos = MAGIC_NUMBER_LEN + INT_LENGTH + strlen(bundleName);
    AdapterFree(bundleName);
    return ERR_OK;
}

uint8_t GtBundleExtractor::ExtractHap(const char *codePath, int32_t fp, uint32_t totalFileSize)
{
    char *relativeFilePath = nullptr;
    char *fileName = nullptr;
    uint64_t fileSize = 0;
    uint64_t index = 0;

    if (codePath == nullptr) {
        return ERR_APPEXECFWK_INSTALL_FAILED_INTERNAL_ERROR;
    }

    uint8_t errorCode = ExtractFileDataPos(fp, index);
    if (errorCode != ERR_OK) {
        return errorCode;
    }

    while (index < totalFileSize) {
        ClrMailBoxStamp(MC_MAIL_ABILITY_BUNDLE_MANAGER);
        errorCode = GtExtractorUtil::ExtractFileToPath(codePath, fp, fileSize, &fileName, &relativeFilePath);
        if (errorCode != ERR_OK) {
            AdapterFree(relativeFilePath);
            AdapterFree(fileName);
            return errorCode;
        }
        index = index + INT_LENGTH + strlen(fileName) + INT_LENGTH + strlen(relativeFilePath) + LONG_LENGTH + fileSize;
        AdapterFree(relativeFilePath);
        AdapterFree(fileName);
    }
    ClrMailBoxStamp(MC_MAIL_ABILITY_BUNDLE_MANAGER);
    return errorCode;
}

char *GtBundleExtractor::ExtractHapProfile(int32_t fp, uint32_t totalFileSize)
{
    char *fileName = nullptr;
    char *relativeFilePath = nullptr;
    char *fileData = nullptr;
    uint64_t fileSize = 0;
    uint64_t index = 0;

    uint8_t errorCode = ExtractFileDataPos(fp, index);
    if (errorCode != ERR_OK) {
        return nullptr;
    }

    while (index < totalFileSize) {
        if (GtExtractorUtil::ExtractFileAttr(fp, fileSize, &fileName, &relativeFilePath) != ERR_OK) {
            AdapterFree(relativeFilePath);
            AdapterFree(fileName);
            return nullptr;
        }

        int32_t pathLen = strlen(relativeFilePath);
        int32_t fileNameLen = strlen(fileName);
        AdapterFree(relativeFilePath);

        if (strcmp(fileName, PROFILE_NAME) == 0) {
            AdapterFree(fileName);
            fileData = reinterpret_cast<char *>(AdapterMalloc(fileSize * sizeof(char)));
            if (fileData == nullptr || read(fp, fileData, fileSize) != fileSize) {
                AdapterFree(fileData);
                return nullptr;
            }
            return fileData;
        } else {
            AdapterFree(fileName);
            int32_t ret = lseek(fp, fileSize, SEEK_CUR);
            if (ret < 0) {
                return nullptr;
            }
        }

        index = index + INT_LENGTH + fileNameLen + INT_LENGTH + pathLen + LONG_LENGTH + fileSize;
    }
    return nullptr;
}

uint8_t GtBundleExtractor::ExtractBundleParam(const char *path, int32_t &fpStart, char **bundleName)
{
    if (!BundleUtil::CheckRealPath(path)) {
        return ERR_APPEXECFWK_INSTALL_FAILED_PARAM_ERROR;
    }

    int32_t fp = open(path, O_RDONLY, S_IREAD);
    if (fp < 0) {
        return ERR_APPEXECFWK_INSTALL_FAILED_FILE_NOT_EXISTS;
    }
    fpStart = fp;

    uint8_t errorCode = GtExtractorUtil::ExtractFileHeaderInfo(fp, bundleName);
    if (errorCode != ERR_OK) {
        return errorCode;
    }

    if (strlen(*bundleName) > MAX_BUNDLE_NAME_LEN) {
        return ERR_APPEXECFWK_INSTALL_FAILED_PARSE_INVALID_BUNDLENAME_LENGTH;
    }
    return ERR_OK;
}
} // namespace OHOS