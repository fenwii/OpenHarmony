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
#include "init_read_cfg.h"
#include <errno.h>
#include <linux/capability.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include "init_jobs.h"
#include "init_perms.h"
#include "init_service_manager.h"
#include "securec.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

static const long MAX_JSON_FILE_LEN = 102400;    // max init.cfg size 100KB
#define MAX_SERVICES_CNT_IN_FILE 100
#define MAX_CAPS_CNT_FOR_ONE_SERVICE 100
#define UID_STR_IN_CFG        "uid"
#define GID_STR_IN_CFG        "gid"
#define ONCE_STR_IN_CFG       "once"
#define IMPORTANT_STR_IN_CFG  "importance"
#define BIN_SH_NOT_ALLOWED    "/bin/sh"

static char* ReadFileToBuf()
{
    char* buffer = NULL;
    FILE* fd = NULL;
    struct stat fileStat = {0};
    do {
        if (stat(INIT_CONFIGURATION_FILE, &fileStat) != 0 ||
            fileStat.st_size <= 0 || fileStat.st_size > MAX_JSON_FILE_LEN) {
            break;
        }

        fd = fopen(INIT_CONFIGURATION_FILE, "r");
        if (fd == NULL) {
            break;
        }

        buffer = (char*)malloc(fileStat.st_size + 1);
        if (buffer == NULL) {
            break;
        }

        if (fread(buffer, fileStat.st_size, 1, fd) != 1) {
            free(buffer);
            buffer = NULL;
            break;
        }
        buffer[fileStat.st_size] = '\0';
    } while (0);

    if (fd != NULL) {
        fclose(fd);
        fd = NULL;
    }
    return buffer;
}

static cJSON* GetArrItem(const cJSON* fileRoot, int* arrSize, const char* arrName)
{
    cJSON* arrItem = cJSON_GetObjectItemCaseSensitive(fileRoot, arrName);
    *arrSize = cJSON_GetArraySize(arrItem);
    if (*arrSize <= 0) {
        return NULL;
    }
    return arrItem;
}

static int IsForbidden(const char* fieldStr)
{
    size_t fieldLen = strlen(fieldStr);
    size_t forbidStrLen =  strlen(BIN_SH_NOT_ALLOWED);
    if (fieldLen == forbidStrLen) {
        if (strncmp(fieldStr, BIN_SH_NOT_ALLOWED, fieldLen) == 0) {
            return 1;
        }
        return 0;
    } else if (fieldLen > forbidStrLen) {
        // "/bin/shxxxx" is valid but "/bin/sh xxxx" is invalid
        if (strncmp(fieldStr, BIN_SH_NOT_ALLOWED, forbidStrLen) == 0) {
            if (fieldStr[forbidStrLen] == ' ') {
                return 1;
            }
        }
        return 0;
    } else {
        return 0;
    }
}

static int GetServiceString(const cJSON* curArrItem, Service* curServ, const char* targetField, size_t maxLen)
{
    char* fieldStr = cJSON_GetStringValue(cJSON_GetObjectItem(curArrItem, targetField));
    if (fieldStr == NULL) {
        return SERVICE_FAILURE;
    }

    size_t strLen = strlen(fieldStr);
    if (strLen == 0 || strLen > maxLen) {
        return SERVICE_FAILURE;
    }

    if (strncmp(targetField, "name", strlen("name")) == 0) {
        if (memcpy_s(curServ->name, maxLen, fieldStr, strLen) != EOK) {
            return SERVICE_FAILURE;
        }
        curServ->name[strLen] = '\0';
        return SERVICE_SUCCESS;
    }

    if (strncmp(targetField, "path", strlen("path")) == 0) {
        if (IsForbidden(fieldStr)) {
            printf("[Init] InitReadCfg, %s is not allowed.\n", fieldStr);
            return SERVICE_FAILURE;
        }

        if (memcpy_s(curServ->path, maxLen, fieldStr, strLen) != EOK) {
            return SERVICE_FAILURE;
        }
        curServ->path[strLen] = '\0';
        return SERVICE_SUCCESS;
    }
    return SERVICE_FAILURE;
}

static int GetServiceNumber(const cJSON* curArrItem, Service* curServ, const char* targetField)
{
    cJSON* filedJ = cJSON_GetObjectItem(curArrItem, targetField);
    if (!cJSON_IsNumber(filedJ)) {
        return SERVICE_FAILURE;
    }

    int value = (int)cJSON_GetNumberValue(filedJ);
    if (value < 0) {
        return SERVICE_FAILURE;
    }

    if (strncmp(targetField, UID_STR_IN_CFG, strlen(UID_STR_IN_CFG)) == 0) {
        curServ->servPerm.uID = value;
    } else if (strncmp(targetField, GID_STR_IN_CFG, strlen(GID_STR_IN_CFG)) == 0) {
        curServ->servPerm.gID = value;
    } else if (strncmp(targetField, ONCE_STR_IN_CFG, strlen(ONCE_STR_IN_CFG)) == 0) {
        if (value != 0) {
            curServ->attribute |= SERVICE_ATTR_ONCE;
        }
    } else if (strncmp(targetField, IMPORTANT_STR_IN_CFG, strlen(IMPORTANT_STR_IN_CFG)) == 0) {
        if (value != 0) {
            curServ->attribute |= SERVICE_ATTR_IMPORTANT;
        }
    } else {
        return SERVICE_FAILURE;
    }
    return SERVICE_SUCCESS;
}

static int GetServiceCaps(const cJSON* curArrItem, Service* curServ)
{
    curServ->servPerm.capsCnt = 0;
    curServ->servPerm.caps = NULL;

    cJSON* filedJ = cJSON_GetObjectItem(curArrItem, "caps");
    if (!cJSON_IsArray(filedJ)) {
        return SERVICE_FAILURE;
    }

    // caps array does not exist, means do not need any capability
    int capsCnt = cJSON_GetArraySize(filedJ);
    if (capsCnt <= 0) {
        return SERVICE_SUCCESS;
    }

    if (capsCnt > MAX_CAPS_CNT_FOR_ONE_SERVICE) {
        printf("[Init] GetServiceCaps, too many caps[cnt %d] for one service, should not exceed %d.\n",\
            capsCnt, MAX_CAPS_CNT_FOR_ONE_SERVICE);
        return SERVICE_FAILURE;
    }

    curServ->servPerm.caps = (unsigned int*)malloc(sizeof(unsigned int) * capsCnt);
    if (curServ->servPerm.caps == NULL) {
        return SERVICE_FAILURE;
    }

    for (int i = 0; i < capsCnt; ++i) {
        cJSON* capJ = cJSON_GetArrayItem(filedJ, i);
        if (!cJSON_IsNumber(capJ) || cJSON_GetNumberValue(capJ) < 0) {
            free(curServ->servPerm.caps);
            curServ->servPerm.caps = NULL;
            return SERVICE_FAILURE;
        }
        curServ->servPerm.caps[i] = (unsigned int)cJSON_GetNumberValue(capJ);
        if (curServ->servPerm.caps[i] > CAP_LAST_CAP && curServ->servPerm.caps[i] != FULL_CAP) {
            free(curServ->servPerm.caps);
            curServ->servPerm.caps = NULL;
            return SERVICE_FAILURE;
        }
    }
    curServ->servPerm.capsCnt = capsCnt;
    return SERVICE_SUCCESS;
}

static void ParseAllServices(const cJSON* fileRoot)
{
    int servArrSize = 0;
    cJSON* serviceArr = GetArrItem(fileRoot, &servArrSize, SERVICES_ARR_NAME_IN_JSON);
    if (serviceArr == NULL) {
        printf("[Init] InitReadCfg, get array %s failed.\n", SERVICES_ARR_NAME_IN_JSON);
        return;
    }

    if (servArrSize > MAX_SERVICES_CNT_IN_FILE) {
        printf("[Init] InitReadCfg, too many services[cnt %d] detected, should not exceed %d.\n",\
            servArrSize, MAX_SERVICES_CNT_IN_FILE);
        return;
    }

    Service* retServices = (Service*)malloc(sizeof(Service) * servArrSize);
    if (retServices == NULL) {
        printf("[Init] InitReadCfg, malloc for %s arr failed! %d.\n", SERVICES_ARR_NAME_IN_JSON, servArrSize);
        return;
    }

    if (memset_s(retServices, sizeof(Service) * servArrSize, 0, sizeof(Service) * servArrSize) != EOK) {
        free(retServices);
        retServices = NULL;
        return;
    }

    for (int i = 0; i < servArrSize; ++i) {
        cJSON* curItem = cJSON_GetArrayItem(serviceArr, i);
        if (GetServiceString(curItem, &retServices[i], "name", MAX_SERVICE_NAME) != SERVICE_SUCCESS ||
            GetServiceString(curItem, &retServices[i], "path", MAX_SERVICE_PATH) != SERVICE_SUCCESS) {
            retServices[i].attribute |= SERVICE_ATTR_INVALID;
            printf("[Init] InitReadCfg, bad string values for service %d.\n", i);
            continue;
        }

        if (GetServiceNumber(curItem, &retServices[i], UID_STR_IN_CFG) != SERVICE_SUCCESS ||
            GetServiceNumber(curItem, &retServices[i], GID_STR_IN_CFG) != SERVICE_SUCCESS ||
            GetServiceNumber(curItem, &retServices[i], ONCE_STR_IN_CFG) != SERVICE_SUCCESS ||
            GetServiceNumber(curItem, &retServices[i], IMPORTANT_STR_IN_CFG) != SERVICE_SUCCESS) {
            retServices[i].attribute |= SERVICE_ATTR_INVALID;
            printf("[Init] InitReadCfg, bad number values for service %d.\n", i);
            continue;
        }

        if (GetServiceCaps(curItem, &retServices[i]) != SERVICE_SUCCESS) {
            retServices[i].attribute |= SERVICE_ATTR_INVALID;
            printf("[Init] InitReadCfg, bad caps values for service %d.\n", i);
        }
    }
    RegisterServices(retServices, servArrSize);
}

void InitReadCfg()
{
    // read configuration file in json format
    char* fileBuf = ReadFileToBuf();
    if (fileBuf == NULL) {
        printf("[Init] InitReadCfg, read file %s failed! err %d.\n", INIT_CONFIGURATION_FILE, errno);
        return;
    }

    cJSON* fileRoot = cJSON_Parse(fileBuf);
    free(fileBuf);
    fileBuf = NULL;

    if (fileRoot == NULL) {
        printf("[Init] InitReadCfg, parse failed! please check file %s format.\n", INIT_CONFIGURATION_FILE);
        return;
    }

    // parse services
    ParseAllServices(fileRoot);

    // parse jobs
    ParseAllJobs(fileRoot);

    // release memory
    cJSON_Delete(fileRoot);

    // do jobs
    DoJob("pre-init");
    DoJob("init");
    DoJob("post-init");
    ReleaseAllJobs();
}

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */
