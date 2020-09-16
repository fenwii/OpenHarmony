/*
 * Copyright (c) 2020 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <errno.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "log.h"


#define HILOG_LOGBUFFER 2048
#define HILOG_MAX_FILELEN 2048
#ifdef __LINUX__
#define HILOG_PATH1 "/data/log/hilog1.txt"
#define HILOG_PATH2 "/data/log/hilog2.txt"
#else
#define HILOG_PATH1 "/storage/data/log/hilog1.txt"
#define HILOG_PATH2 "/storage/data/log/hilog2.txt"
#endif


static int FileSize(const char *filename)
{
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        return -1;
    }
    fseek(fp, 0L, SEEK_END);
    int size = ftell(fp);
    fclose(fp);

    return size;
}

static FILE *FileClear(FILE **fp, const char *filename)
{
    fclose(*fp);
    *fp = fopen(filename, "w");
    if (*fp == NULL) {
        return NULL;
    }
    printf("write file switch %s\n", filename);
    return *fp;
}

FILE *SelectWriteFile(FILE **fp1, FILE *fp2)
{
    int file1Size = FileSize(HILOG_PATH1);
    int file2Size = FileSize(HILOG_PATH2);
    if (file1Size < HILOG_MAX_FILELEN) {
        return *fp1;
    } else if (file2Size < HILOG_MAX_FILELEN) {
        return fp2;
    } else { // clear file1 write file 1
        return FileClear(fp1, HILOG_PATH1);
    }
}

FILE *SwitchWriteFile(FILE **fp1, FILE **fp2, FILE *curFp)
{
    int file1Size = FileSize(HILOG_PATH1);
    int file2Size = FileSize(HILOG_PATH2);
    // select file, if file1 is full, record file2, file2 is full, record file1
    if (file1Size < HILOG_MAX_FILELEN) {
        return *fp1;
    } else if (file2Size < HILOG_MAX_FILELEN) {
        return *fp2;
    } else if (curFp == *fp2) { // clear file1 write file 1
        return FileClear(fp1, HILOG_PATH1);
    } else {
        return FileClear(fp2, HILOG_PATH2);
    }
}

int main(int argc, const char **argv)
{
#define HILOG_PERMMISION 0700
#define HILOG_TEST_ARGC 2
    int fd;
    int ret;
    FILE *fpWrite = NULL;
    if (argc == 1) {
#ifdef OHOS_RELEASE
        return 0;
#endif
    }
    if (argc == HILOG_TEST_ARGC) {
        HILOG_ERROR(LOG_CORE, "TEST = %d,%s,%d\n", argc, "hilog test", argc);
        return 0;
    }
    fd = open(HILOG_DRIVER, O_RDONLY);
    if (fd < 0) {
        printf("hilog fd failed fd=%d\n", fd);
        return 0;
    }

    FILE *fp1 = fopen(HILOG_PATH1, "at");
    if (fp1 == NULL) {
        close(fd);
        printf("open err fp1=%p\n", fp1);
        return 0;
    }

    FILE *fp2 = fopen(HILOG_PATH2, "at");
    if (fp2 == NULL) {
        fclose(fp1);
        close(fd);
        printf("open err fp2=%p\n", fp2);
        return 0;
    }
    // First select
    fpWrite = SelectWriteFile(&fp1, fp2);
    if (fpWrite == NULL) {
        printf("SelectWriteFile open err fp1=%p\n", fp1);
        return 0;
    }
    while (1) {
        char buf[HILOG_LOGBUFFER] = {0};
        ret = read(fd, buf, HILOG_LOGBUFFER);
        if (ret < sizeof(struct HiLogEntry)) {
            continue;
        }
        struct HiLogEntry *head = (struct HiLogEntry *)buf;

        time_t rawtime;
        struct tm *info = NULL;
        unsigned int sec = head->sec;
        rawtime = (time_t)sec;
        /* Get GMT time */
        info = gmtime(&rawtime);
        if (info == NULL) {
            continue;
        }
        buf[HILOG_LOGBUFFER - 1] = '\0';
        printf("%02d-%02d %02d:%02d:%02d.%03d %d %d %s\n", info->tm_mon + 1, info->tm_mday, info->tm_hour, info->tm_min,
            info->tm_sec, head->nsec / NANOSEC_PER_MIRCOSEC, head->pid, head->taskId, head->msg);

        ret =
            fprintf(fpWrite, "%02d-%02d %02d:%02d:%02d.%03d %d %d %s\n", info->tm_mon + 1, info->tm_mday, info->tm_hour,
                info->tm_min, info->tm_sec, head->nsec / NANOSEC_PER_MIRCOSEC, head->pid, head->taskId, head->msg);
        // select file, if file1 is full, record file2, file2 is full, record file1
        fpWrite = SwitchWriteFile(&fp1, &fp2, fpWrite);
        if (fpWrite == NULL) {
            printf("[FATAL]File cant't open  fp1=%p, fp2=%p\n", fp1, fp2);
            return 0;
        }
    }
    return 0;
}
