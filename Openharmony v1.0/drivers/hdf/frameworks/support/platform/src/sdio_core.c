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

#include <string.h>
#include "device_resource_if.h"
#include "hdf_log.h"
#include "osal_mem.h"
#include "sdio_core.h"

#define HDF_LOG_TAG sdio_core

struct SdioCntlr *SdioCntlrCreateAndBind(struct HdfDeviceObject *device)
{
    struct SdioCntlr *cntlr = NULL;

    if (device == NULL) {
        HDF_LOGE("SdioCntlrCreateAndBind: device is NULL!");
        return NULL;
    }

    cntlr = (struct SdioCntlr *)OsalMemCalloc(sizeof(*cntlr));
    if (cntlr == NULL) {
        HDF_LOGE("SdioCntlrCreateAndBind: malloc host fail!");
        return NULL;
    }
    cntlr->device = device;
    device->service = &cntlr->service;
    return cntlr;
}

void SdioCntlrDestroy(struct SdioCntlr *cntlr)
{
    if (cntlr != NULL) {
        cntlr->device = NULL;
        cntlr->priv = NULL;
        cntlr->method = NULL;
        OsalMemFree(cntlr);
    }
}

int32_t SdioFillConfigData(struct HdfDeviceObject *device, struct SdioConfigData *configData)
{
    const struct DeviceResourceNode *node = NULL;
    struct DeviceResourceIface *drsOps = NULL;
    int32_t ret;

    if (device == NULL || configData == NULL) {
        HDF_LOGE("SdioFillConfigData: input para is NULL.");
        return HDF_FAILURE;
    }

    node = device->property;
    if (node == NULL) {
        HDF_LOGE("SdioFillConfigData: drs node is NULL.");
        return HDF_FAILURE;
    }
    drsOps = DeviceResourceGetIfaceInstance(HDF_CONFIG_SOURCE);
    if (drsOps == NULL || drsOps->GetUint32 == NULL) {
        HDF_LOGE("SdioFillConfigData: invalid drs ops fail!");
        return HDF_FAILURE;
    }

    ret = drsOps->GetUint32(node, "funcNum", &(configData->funcNum), 0);
    if (ret != HDF_SUCCESS) {
        HDF_LOGE("SdioFillConfigData: read funcNum fail!");
        return ret;
    }
    ret = drsOps->GetUint32(node, "vendorId", &(configData->vendorId), 0);
    if (ret != HDF_SUCCESS) {
        HDF_LOGE("SdioFillConfigData: read vendorId fail!");
        return ret;
    }
    ret = drsOps->GetUint32(node, "deviceId", &(configData->deviceId), 0);
    if (ret != HDF_SUCCESS) {
        HDF_LOGE("SdioFillConfigData: read deviceId fail!");
        return ret;
    }

    HDF_LOGD("SdioFillConfigData: Success! funcNum = %d, vendorId = 0x%x, deviceId = 0x%x.",
        configData->funcNum, configData->vendorId, configData->deviceId);
    return HDF_SUCCESS;
}
