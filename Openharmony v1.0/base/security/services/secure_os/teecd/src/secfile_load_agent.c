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

#include "secfile_load_agent.h"
#include <errno.h>
#include <sys/prctl.h>
#include "securec.h"
#include "tc_ns_client.h"
#include "teec_compat.h"

#define MAX_PATH_LEN 256
#ifdef LOG_TAG
#undef LOG_TAG
#endif
#define LOG_TAG        "secload_agent_teecd"
#define MAX_BUFFER_LEN (8 * 1024 * 1024)
int g_secLoadAgentFd = -1;

int GetSecLoadAgentFd(void)
{
    return g_secLoadAgentFd;
}

void SetSecLoadAgentFd(int secLoadAgentFd)
{
    g_secLoadAgentFd = secLoadAgentFd;
}

static int GetImgLen(FILE *fp, long *totalLen)
{
    int ret;

    ret = fseek(fp, 0, SEEK_END);
    if (ret != 0) {
        tloge("fseek error\n");
        return -1;
    }
    *totalLen = ftell(fp);
    if (*totalLen <= 0 || *totalLen > MAX_BUFFER_LEN) {
        tloge("file is not exist or size is too large, filesize = %ld\n", *totalLen);
        return -1;
    }
    ret = fseek(fp, 0, SEEK_SET);
    if (ret != 0) {
        tloge("fseek error\n");
        return -1;
    }
    return ret;
}

static int32_t SecFileLoadWork(int tzFd, const char *filePath, enum SecFileType fileType, const TEEC_UUID *uuid)
{
    char realPath[PATH_MAX + 1] = { 0 };
    FILE *fp = NULL;
    int ret;

    if (tzFd < 0) {
        tloge("fd of tzdriver is valid!\n");
        return -1;
    }
    if (realpath(filePath, realPath) == NULL) {
        tloge("realpath open file erro(%s), filePath=%s\n", strerror(errno), filePath);
        return -1;
    }
    if (strncmp(realPath, "/vendor/bin", strlen("/vendor/bin")) != 0) {
        tloge("realpath -%s- is invalid\n", realPath);
        return -1;
    }
    fp = fopen(realPath, "r");
    if (fp == NULL) {
        tloge("open file erro(%s), path=%s\n", strerror(errno), filePath);
        return -1;
    }
    ret = LoadSecFile(tzFd, fp, fileType, uuid);
    fclose(fp);
    return ret;
}

// input param uuid may be NULL, so don need to check if uuid is NULL
int32_t LoadSecFile(int tzFd, FILE *fp, enum SecFileType fileType, const TEEC_UUID *uuid)
{
    int32_t ret;
    char *fileBuffer                   = NULL;
    struct SecLoadIoctlStruct ioctlArg = { 0, { 0 }, 0, { NULL } };
    bool checkValue = (tzFd < 0 || fp == NULL);

    if (checkValue == true) {
        tloge("param erro!\n");
        return -1;
    }

    do {
        long totalLen = 0;
        ret           = GetImgLen(fp, &totalLen);
        if (ret != 0) {
            break;
        }

        if (totalLen <= 0) {
            ret = -1;
            tloge("totalLen is invalid\n");
            break;
        }
        /* alloc a less than 8M heap memory, it needn't slice. */
        fileBuffer = malloc(totalLen);
        if (fileBuffer == NULL) {
            tloge("alloc TA file buffer(size=%ld) failed\n", totalLen);
            ret = -1;
            break;
        }

        /* read total ta file to file buffer */
        long fileSize = (long)fread(fileBuffer, 1, totalLen, fp);
        if (fileSize != totalLen) {
            tloge("read ta file failed, read size/total size=%ld/%ld\n", fileSize, totalLen);
            ret = -1;
            break;
        }
        ioctlArg.fileType   = fileType;
        ioctlArg.fileSize   = totalLen;
        ioctlArg.fileBuffer = fileBuffer;
        if (uuid != NULL && memcpy_s((void *)(&ioctlArg.uuid), sizeof(ioctlArg.uuid), uuid, sizeof(*uuid)) != EOK) {
            tloge("memcpy uuid fail\n");
            ret = -1;
            break;
        }

        ret = ioctl(tzFd, (int)TC_NS_CLIENT_IOCTL_LOAD_APP_REQ, &ioctlArg);
        if (ret != 0) {
            tloge("ioctl to load sec file failed, ret = 0x%x\n", ret);
        }
    } while (false);

    if (fileBuffer != NULL) {
        free(fileBuffer);
    }
    return ret;
}

static void LoadLib(struct SecAgentControlType *secAgentControl)
{
    int32_t ret;
    char fname[MAX_PATH_LEN] = { 0 };

    if (secAgentControl == NULL) {
        tloge("secAgentControl is null\n");
        return;
    }
    if (strlen(secAgentControl->LibSec.libName) > (MAX_SEC_FILE_NAME_LEN - 1)) {
        tloge("libName is too long!\n");
        secAgentControl->ret = -1;
        return;
    }
    ret =
        snprintf_s(fname, sizeof(fname), MAX_PATH_LEN - 1, "%s/%08x-%04x-%04x-%02x%02x-%02x%02x%02x%02x%02x%02x%s.sec",
                   "/vendor/bin", secAgentControl->LibSec.uuid.timeLow, secAgentControl->LibSec.uuid.timeMid,
                   secAgentControl->LibSec.uuid.timeHiAndVersion, secAgentControl->LibSec.uuid.clockSeqAndNode[0],
                   secAgentControl->LibSec.uuid.clockSeqAndNode[1], secAgentControl->LibSec.uuid.clockSeqAndNode[2],
                   secAgentControl->LibSec.uuid.clockSeqAndNode[3], secAgentControl->LibSec.uuid.clockSeqAndNode[4],
                   secAgentControl->LibSec.uuid.clockSeqAndNode[5], secAgentControl->LibSec.uuid.clockSeqAndNode[6],
                   secAgentControl->LibSec.uuid.clockSeqAndNode[7], secAgentControl->LibSec.libName);
    if (ret < 0) {
        tloge("pack fname err\n");
        secAgentControl->ret = -1;
        return;
    }
    ret = SecFileLoadWork(g_secLoadAgentFd, (const char *)fname, LOAD_LIB, NULL);
    if (ret != 0) {
        tloge("teec load app failed\n");
        secAgentControl->ret   = -1;
        secAgentControl->error = errno;
        return;
    }
    secAgentControl->ret = 0;
    return;
}

static void LoadTa(struct SecAgentControlType *secAgentControl)
{
    int32_t ret;
    char fname[MAX_PATH_LEN] = { 0 };

    if (secAgentControl == NULL) {
        tloge("secAgentControl is null\n");
        return;
    }

    ret = snprintf_s(fname, sizeof(fname), MAX_PATH_LEN - 1, "%s/%08x-%04x-%04x-%02x%02x-%02x%02x%02x%02x%02x%02x.sec",
                     "/vendor/bin", secAgentControl->TaSec.uuid.timeLow, secAgentControl->TaSec.uuid.timeMid,
                     secAgentControl->TaSec.uuid.timeHiAndVersion, secAgentControl->TaSec.uuid.clockSeqAndNode[0],
                     secAgentControl->TaSec.uuid.clockSeqAndNode[1], secAgentControl->TaSec.uuid.clockSeqAndNode[2],
                     secAgentControl->TaSec.uuid.clockSeqAndNode[3], secAgentControl->TaSec.uuid.clockSeqAndNode[4],
                     secAgentControl->TaSec.uuid.clockSeqAndNode[5], secAgentControl->TaSec.uuid.clockSeqAndNode[6],
                     secAgentControl->TaSec.uuid.clockSeqAndNode[7]);
    if (ret < 0) {
        tloge("pack fname err\n");
        secAgentControl->ret = -1;
        return;
    }
    secAgentControl->ret = 0;
    ret = SecFileLoadWork(g_secLoadAgentFd, (const char *)fname, LOAD_TA, &(secAgentControl->TaSec.uuid));
    if (ret != 0) {
        tloge("teec load TA app failed\n");
        secAgentControl->ret   = ret;
        secAgentControl->error = errno;
        return;
    }
    return;
}

static void SecLoadAgentWork(struct SecAgentControlType *secAgentControl)
{
    if (secAgentControl == NULL) {
        tloge("secAgentControl is null\n");
        return;
    }
    switch (secAgentControl->cmd) {
        case LOAD_LIB_SEC:
            LoadLib(secAgentControl);
            break;
        case LOAD_TA_SEC:
            LoadTa(secAgentControl);
            break;
        default:
            tloge("gtask agent error cmd:%d\n", secAgentControl->cmd);
            secAgentControl->ret = -1;
            break;
    }
}

void *SecfileLoadAgentThread(void *control)
{
    prctl(PR_SET_NAME, "teecd_sec_load_agent", 0, 0, 0);
    struct SecAgentControlType *secAgentControl = NULL;
    if (control == NULL) {
        tloge("control is NULL\n");
        return NULL;
    }
    secAgentControl = (struct SecAgentControlType *)control;
    if (g_secLoadAgentFd < 0) {
        tloge("m_gtask_agent_fd is -1\n");
        return NULL;
    }
    secAgentControl->magic = SECFILE_LOAD_AGENT_ID;
    while (true) {
        int ret = ioctl(g_secLoadAgentFd, (int)TC_NS_CLIENT_IOCTL_WAIT_EVENT, SECFILE_LOAD_AGENT_ID);
        if (ret) {
            tloge("gtask agent wait event failed\n");
            break;
        }
        SecLoadAgentWork(secAgentControl);
        Barriers();
        secAgentControl->magic = SECFILE_LOAD_AGENT_ID;
        Barriers();
        ret = ioctl(g_secLoadAgentFd, (int)TC_NS_CLIENT_IOCTL_SEND_EVENT_RESPONSE, SECFILE_LOAD_AGENT_ID);
        if (ret) {
            tloge("gtask agent send reponse failed\n");
            break;
        }
    }
    return NULL;
}
