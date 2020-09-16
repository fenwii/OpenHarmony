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

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <dirent.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "log.h"
#include "libfs.h"
#include "KernelConstants.h"

int MakeDir(const char *dirname)
{
    if (access(dirname, F_OK) == 0) {
        LOG("dir:%s exists", dirname);
        return 1;
    } else {
        int rt = mkdir(dirname, S_IRUSR | S_IWUSR | S_IXUSR | S_IRWXG | S_IXOTH);
        if (rt) {
            LOG("create dir failed! path=%s, errno=%d:%s", dirname, errno, strerror(errno));
            return -1;
        }
    }
    return 0;
}

int RemoveDir(const char *dirname)
{
    char subDir[MAX_PATH_SIZE];
    struct stat dirStat;

    if (stat(dirname, &dirStat) < 0) {
        LOG("get directory stat error, errno=%d:%s", errno, strerror(errno));
        return -1;
    }

    if (S_ISDIR(dirStat.st_mode)) {
        DIR *pDir = opendir(dirname);
        struct dirent *entry;
        while ((entry = readdir(pDir))) {
            char *fname = entry->d_name;
            if (!strcmp(fname, ".") || !strcmp(fname, "..")) {
                continue; // skip . and ..
            }
            // MAX_PATH_SIZE is the max length of allowed path string, so it safe to use sprintf here.
            sprintf(subDir, "%s/%s", dirname, fname);
            RemoveDir(subDir);   // remove sub dir or file
        }
        closedir(pDir);
        if (rmdir(dirname) == -1) {  // delete empty dir
            LOG("delete empty directory failed, path=%s, errno=%d:%s", dirname, errno, strerror(errno));
            return -1;
        }
    } else {
        if (remove(dirname) == -1) {
            LOG("remove regular file failed, path=%s, errno=%d:%s", dirname, errno, strerror(errno));
            return -1;
        }
    }

    return 0;
}

int RemoveFile(const char *fpath)
{
    if (!remove(fpath)) {
        LOG("remove file success");
    } else {
        LOG("remove file failed! path=%s: errno=%d:%s", fpath, errno, strerror(errno));
        return -1;
    }
    return 0;
}

int CopyFile(const char *srcFile, const char *dstFile)
{
    int rt = 0;
    FILE *srcFp = fopen(srcFile, "rb");
    if (srcFp == NULL) {
        LOG("Cannot open source file %s: errno=%d,%s \n", srcFile, errno, strerror(errno));
        return -1;
    }
    FILE *dstFp = fopen(dstFile, "wb");
    if (dstFp == NULL) {
        LOG("Cannot create dest file %s: errno=%d,%s \n", dstFile, errno, strerror(errno));
        fclose(srcFp);
        return -1;
    }

    const int BUF_SIZE = 100 * 1024;
    char buffer[BUF_SIZE];
    size_t bytes;
    while ((bytes = fread(buffer, 1, sizeof(buffer), srcFp)) > 0) {
        if (fwrite(buffer, 1, bytes, dstFp) != bytes) {
            LOG("write to dest file failed: errno=%d,%s \n", errno, strerror(errno));
            rt = -1;
            break;
        }
    }
    fclose(srcFp);
    fclose(dstFp);
    return rt;
}

char* GetCurrentPath()
{
    static char path1[MAX_PATH_SIZE];
    char *path = getcwd(path1, MAX_PATH_SIZE);
    LOG("current Path = %s,path1=%s", path, path1);
    return path1;
}
