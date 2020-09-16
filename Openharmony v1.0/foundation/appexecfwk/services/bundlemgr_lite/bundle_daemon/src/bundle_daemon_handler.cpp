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

#include "bundle_daemon_handler.h"

#include <limits.h>

#include "bundle_daemon_log.h"
#include "bundle_file_utils.h"
#include "extractor_util.h"
#include "hos_errno.h"

namespace OHOS {
namespace {
const char *PERMISSIONS_PATH = "/storage/app/etc/permissions/";
constexpr pid_t PMS_UID = 7;
constexpr pid_t PMS_GID = 7;
const std::string JSON_PATH = "/app/etc/";
const std::string HAP_CODE_PATH = "/app/run/";
const std::string HAP_DATA_PATH = "/app/data/";
const std::string SYSTEM_HAP_PATH = "/system/internal";
const std::string THIRD_HAP_PATH = "/system/external";
const std::string SDCARD = "/sdcard";
const std::string STORAGE = "/storage";
}

int32 BundleDaemonHandler::ExtractHap(const char *hapPath, const char *codePath)
{
    char realHapPath[PATH_MAX] = { '\0' };
    if (hapPath == nullptr || realpath(hapPath, realHapPath) == nullptr) {
        PRINTE("BundleDaemonHandler", "realPath fail!");
        return EC_INVALID;
    }
    ExtractorUtil extractorUtil(realHapPath);
    if (!extractorUtil.Init()) {
        PRINTE("BundleDaemonHandler", "init fail!");
        return EC_NOINIT;
    }

    // check and mkdir code path
    if (!IsValideCodePath(codePath)) {
        return EC_INVALID;
    }
    if (!BundleFileUtils::RemoveFile(codePath)) {
        PRINTE("BundleDaemonHandler", "remove codePath fail!");
        return EC_NODIR;
    }
    std::string codeDir = std::string(codePath);
    if (codeDir.back() != PATH_SEPARATOR) {
        codeDir += PATH_SEPARATOR;
    }

    if (!BundleFileUtils::MkRecursiveDir(codeDir.c_str(), true)) {
        PRINTE("BundleDaemonHandler", "create codePath fail!");
        return EC_NODIR;
    }

    // unzip one by one
    const std::vector<std::string> &fileNames = extractorUtil.GetZipFileNames();
    for (const auto &fileName : fileNames) {
        if (fileName.find("..") != std::string::npos) {
            PRINTE("BundleDaemonHandler", "zip file is invalid!");
            return EC_NODIR;
        }
        if (fileName.back() == PATH_SEPARATOR) {
            continue;
        }
        const std::string dir = BundleFileUtils::GetPathDir(fileName);
        if (!dir.empty()) {
            std::string fileDir = codeDir + dir;
            if (!BundleFileUtils::MkRecursiveDir(fileDir.c_str(), false)) {
                PRINTE("BundleDaemonHandler", "create other dir fail!");
                return EC_NODIR;
            }
        }
        std::string filePath = codeDir + fileName;
        if (!extractorUtil.ExtractFileToPath(filePath, fileName)) {
            PRINTE("BundleDaemonHandler", "ExtractFileToPath fail!");
            return EC_NODIR;
        }
    }
    return EC_SUCCESS;
}

int32 BundleDaemonHandler::RenameFile(const char *oldFile, const char *newFile)
{
    char realOldPath[PATH_MAX] = { '\0' };
    if (oldFile == nullptr || realpath(oldFile, realOldPath) == nullptr) {
        PRINTE("BundleDaemonHandler", "realPath fail!");
        return EC_INVALID;
    }
    if (!(IsValideCodePath(realOldPath) && IsValideCodePath(newFile)) &&
        !(IsValideJsonPath(realOldPath) && IsValideJsonPath(newFile))) {
        PRINTE("BundleDaemonHandler", "file path is invalid");
        return EC_INVALID;
    }
    if (!BundleFileUtils::RenameFile(realOldPath, newFile)) {
        PRINTE("BundleDaemonHandler", "rename dir fail");
        return EC_NODIR;
    }
    return EC_SUCCESS;
}

int32 BundleDaemonHandler::CreatePermissionDir()
{
    if (!BundleFileUtils::MkRecursiveDir(PERMISSIONS_PATH, false)) {
        PRINTE("BundleDaemonHandler", "mk dir fail");
        return EC_NODIR;
    }
    if (!BundleFileUtils::ChownFile(PERMISSIONS_PATH, PMS_UID, PMS_GID)) {
        PRINTE("BundleDaemonHandler", "chown permission path fail");
        return EC_PERMISSION;
    }
    return EC_SUCCESS;
}

int32 BundleDaemonHandler::CreateDataDirectory(const char *dataPath, int32_t uid, int32_t gid, bool isChown)
{
    if (!IsValideDataPath(dataPath)) {
        PRINTE("BundleDaemonHandler", "bundleName is nullptr");
        return EC_INVALID;
    }
    std::string dataDir = std::string(dataPath);
    if (dataDir.back() != PATH_SEPARATOR) {
        dataDir += PATH_SEPARATOR;
    }

    if (!BundleFileUtils::RemoveFile(dataDir.c_str())) {
        PRINTE("BundleDaemonHandler", "remove dataPath fail");
        return EC_NODIR;
    }

    if (!BundleFileUtils::MkRecursiveDir(dataDir.c_str(), false)) {
        PRINTE("BundleDaemonHandler", "create dataPath fail");
        return EC_NODIR;
    }
    if (isChown && !BundleFileUtils::ChownFile(dataDir.c_str(), uid, gid)) {
        PRINTE("BundleDaemonHandler", "chown file fail");
        return EC_NOFILE;
    }
    return EC_SUCCESS;
}

int32 BundleDaemonHandler::RemoveInstallDirectory(const char *codePath, const char *dataPath)
{
    bool result = IsValideCodePath(codePath) && BundleFileUtils::RemoveFile(codePath);
    result = IsValideDataPath(dataPath) && BundleFileUtils::RemoveFile(dataPath) && result;
    return result ? EC_SUCCESS : EC_NODIR;
}

int32 BundleDaemonHandler::StoreContentToFile(const char *filePath, const void *buffer, uint32_t size)
{
    if (!IsValideJsonPath(filePath)) {
        PRINTE("BundleDaemonHandler", "store content file path invalid");
        return EC_NOFILE;
    }
    // mkdir root dir
    const std::string dir = BundleFileUtils::GetPathDir(filePath);
    if (dir.empty()) {
        PRINTE("BundleDaemonHandler", "store content file dir invalid");
        return EC_NODIR;
    }
    if (!BundleFileUtils::IsExistDir(dir.c_str())) {
        if (!BundleFileUtils::MkRecursiveDir(dir.c_str(), true)) {
            PRINTE("BundleDaemonHandler", "mkdir content json path fail");
            return EC_NODIR;
        }
    }

    if (!BundleFileUtils::WriteFile(filePath, buffer, size)) {
        PRINTE("BundleDaemonHandler", "save content to file fail");
        BundleFileUtils::RemoveFile(filePath);
        return EC_NODIR;
    }
    return EC_SUCCESS;
}

int32 BundleDaemonHandler::RemoveFile(const char *filePath)
{
    char realFilePath[PATH_MAX] = { '\0' };
    if (filePath == nullptr || realpath(filePath, realFilePath) == nullptr) {
        PRINTE("BundleDaemonHandler", "realPath fail!");
        return EC_INVALID;
    }
    if (!IsValideJsonPath(realFilePath) && !IsValideSystemPath(realFilePath) &&
        !IsValideCodePath(realFilePath)) {
        PRINTE("BundleDaemonHandler", "file path is invalid");
        return EC_INVALID;
    }
    if (!BundleFileUtils::RemoveFile(realFilePath)) {
        PRINTE("BundleDaemonHandler", "clear content to file fail");
        return EC_NODIR;
    }
    return EC_SUCCESS;
}

bool BundleDaemonHandler::IsValideCodePath(const char *codePath)
{
    if (codePath == nullptr) {
        return false;
    }
    return BundleFileUtils::IsValidPath(STORAGE + HAP_CODE_PATH, codePath) ||
        BundleFileUtils::IsValidPath(SDCARD + HAP_CODE_PATH, codePath);
}

bool BundleDaemonHandler::IsValideDataPath(const char *dataPath)
{
    if (dataPath == nullptr) {
        return false;
    }
    return BundleFileUtils::IsValidPath(STORAGE + HAP_DATA_PATH, dataPath) ||
        BundleFileUtils::IsValidPath(SDCARD + HAP_DATA_PATH, dataPath);
}

bool BundleDaemonHandler::IsValideJsonPath(const char *jsonPath)
{
    if (jsonPath == nullptr) {
        return false;
    }
    return BundleFileUtils::IsValidPath(STORAGE + JSON_PATH, jsonPath);
}

bool BundleDaemonHandler::IsValideSystemPath(const char *path)
{
    if (path == nullptr) {
        return false;
    }
    return BundleFileUtils::IsValidPath(SYSTEM_HAP_PATH, path) ||
        BundleFileUtils::IsValidPath(THIRD_HAP_PATH, path);
}
} // OHOS
