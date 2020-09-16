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

#ifndef __SECFILE_LOAD_AGENT_H_
#define __SECFILE_LOAD_AGENT_H_

#include <sys/ioctl.h> /* for ioctl */
#include "tc_ns_client.h"
#include "tee_client_api.h"
#include "tee_log.h"

#define SECFILE_LOAD_AGENT_ID 0x4c4f4144 // SECFILE-LOAD-AGENT
#define MAX_SEC_FILE_NAME_LEN 32

typedef enum {
    LOAD_TA_SEC = 0,
    LOAD_SERVICE_SEC,
    LOAD_LIB_SEC,
} SecAgentCmd;

struct SecAgentControlType {
    SecAgentCmd cmd;
    uint32_t magic;
    int32_t ret;
    uint32_t error;
    union {
        struct {
            TEEC_UUID uuid;
        } TaSec;
        struct {
            TEEC_UUID uuid;
            char serviceName[MAX_SEC_FILE_NAME_LEN];
        } ServiceSec;
        struct {
            TEEC_UUID uuid;
            char libName[MAX_SEC_FILE_NAME_LEN];
        } LibSec;
    };
};

void *SecfileLoadAgentThread(void *control);
int32_t LoadSecFile(int tzFd, FILE *fp, enum SecFileType fileType, const TEEC_UUID *uuid);
int GetSecLoadAgentFd(void);
void SetSecLoadAgentFd(int secLoadAgentFd);

#endif
