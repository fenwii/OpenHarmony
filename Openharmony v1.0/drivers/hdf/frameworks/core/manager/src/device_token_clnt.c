/*
 * Copyright (c) 2013-2019, Huawei Technologies Co., Ltd. All rights reserved.
 * Copyright (c) 2020, Huawei Device Co., Ltd. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this list of
 *    conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice, this list
 *    of conditions and the following disclaimer in the documentation and/or other materials
 *    provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its contributors may be used
 *    to endorse or promote products derived from this software without specific prior written
 *    permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "device_token_clnt.h"
#include "hdf_device_token.h"
#include "hdf_log.h"
#include "osal_mem.h"

#define HDF_LOG_TAG device_token_clnt

static void DeviceTokenClntConstruct(struct DeviceTokenClnt *tokenClnt, struct IHdfDeviceToken *tokenIf)
{
    tokenClnt->tokenIf = tokenIf;
    tokenClnt->deviceInfo = NULL;
}

struct DeviceTokenClnt *DeviceTokenClntNewInstance(struct IHdfDeviceToken *tokenIf)
{
    struct DeviceTokenClnt *tokenClnt = NULL;
    if (tokenIf == NULL) {
        HDF_LOGE("New token client failed, tokenIf is null");
        return NULL;
    }
    tokenClnt = (struct DeviceTokenClnt *)OsalMemCalloc(sizeof(struct DeviceTokenClnt));
    if (tokenClnt != NULL) {
        DeviceTokenClntConstruct(tokenClnt, tokenIf);
    }
    return tokenClnt;
}

void DeviceTokenClntFreeInstance(struct DeviceTokenClnt *tokenClnt)
{
    if (tokenClnt != NULL) {
        OsalMemFree(tokenClnt);
    }
}

void DeviceTokenClntDelete(struct HdfSListNode *listEntry)
{
    struct DeviceTokenClnt *tokenClnt = (struct DeviceTokenClnt *)listEntry;
    if (tokenClnt != NULL) {
        DeviceTokenClntFreeInstance(tokenClnt);
    }
}
