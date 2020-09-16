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

#include "bundle_file_utils.h"

#include <dirent.h>
#include <fcntl.h>
#include <limits.h>
#include <sys/stat.h>
#include <unistd.h>

#include "bundle_daemon_log.h"
#include "securec.h"

namespace OHOS {
bool BundleFileUtils::IsExistDir(const char *path)
{
    if (path == nullptr) {
        return false;
    }

    struct stat buf = {};
    if (stat(path, &buf) != 0) {
        return false;
    }
    return S_ISDIR(buf.st_mode);
}

bool BundleFileUtils::IsExistFile(const char *file)
{
    if (file == nullptr) {
        return false;
    }

    struct stat buf = {};
    if (stat(file, &buf) != 0) {
        return false;
    }
    return S_ISREG(buf.st_mode);
}

bool BundleFileUtils::MkRecursiveDir(const char *dir, bool isReadOthers)
{
    if (dir == nullptr) {
        return false;
    }
    if (IsExistDir(dir)) {
        return true;
    }
    size_t len = strlen(dir);
    if (len <= 0 || len > PATH_MAX) {
        return false;
    }
    // Create directories level by level
    char rootDir[PATH_MAX] = { '\0' };
    for (size_t i = 0; i < len; ++i) {
        rootDir[i] = dir[i];
        if ((rootDir[i] == PATH_SEPARATOR || i == (len - 1)) && !IsExistDir(rootDir)) {
            mode_t mode = S_IRWXU | S_IRWXG | S_IXOTH;
            mode |= (isReadOthers ? S_IROTH : 0);
            if (mkdir(rootDir, mode) < 0) {
                return false;
            }
        }
    }
    return true;
}

bool BundleFileUtils::RemoveFile(const char *path)
{
    if (IsExistFile(path)) {
        return remove(path) == 0;
    } else if (IsExistDir(path)) {
        DIR *dir = opendir(path);
        if (dir == nullptr) {
            return false;
        }
        struct dirent *dp = nullptr;
        // Remove file before delete the directory
        while ((dp = readdir(dir)) != nullptr) {
            if ((strcmp(dp->d_name, ".") == 0) || (strcmp(dp->d_name, "..")) == 0) {
                continue;
            }
            std::string dirName = std::string(path) + "/" + dp->d_name;
            if (dirName.length() >= PATH_MAX || !RemoveFile(dirName.c_str())) {
                closedir(dir);
                return false;
            }
        }
        closedir(dir);
        return remove(path) == 0;
    } else {
        return true;
    }
}

bool BundleFileUtils::RenameFile(const char *oldFile, const char *newFile)
{
    if (oldFile == nullptr || newFile == nullptr) {
        return false;
    }
    if (!RemoveFile(newFile)) {
        return false;
    }

    return rename(oldFile, newFile) == 0;
}

bool BundleFileUtils::ChownFile(const char *file, int32_t uid, int32_t gid)
{
    if (file == nullptr) {
        return false;
    }
    return chown(file, uid, gid) == 0;
}

bool BundleFileUtils::WriteFile(const char *file, const void *buffer, uint32_t size)
{
    if (file == nullptr || buffer == nullptr || size == 0) {
        return false;
    }

    int32_t fp = open(file, O_RDWR | O_CREAT | O_TRUNC, S_IREAD | S_IWUSR | S_IRGRP | S_IROTH);
    if (fp < 0) {
        return false;
    }

    if (write(fp, buffer, size) != static_cast<int32_t>(size)) {
        close(fp);
        return false;
    }

    close(fp);
    return true;
}

bool BundleFileUtils::IsValidPath(const std::string &rootDir, const std::string &path)
{
    if (rootDir.find(PATH_SEPARATOR) != 0 || rootDir.rfind(PATH_SEPARATOR) != (rootDir.size() - 1) ||
        rootDir.find("..") != std::string::npos) {
        return false;
    }
    if (path.find("..") != std::string::npos) {
        return false;
    }
    return path.compare(0, rootDir.size(), rootDir) == 0;
}

std::string BundleFileUtils::GetPathDir(const std::string &path)
{
    std::size_t pos = path.rfind(PATH_SEPARATOR);
    if (pos == std::string::npos) {
        return std::string();
    }
    return path.substr(0, pos + 1);
}
} // OHOS
