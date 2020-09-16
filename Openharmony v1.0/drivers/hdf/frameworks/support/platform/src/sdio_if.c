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

#include "devsvc_manager_clnt.h"
#include "hdf_base.h"
#include "hdf_log.h"
#include "osal_mem.h"
#include "securec.h"
#include "sdio_core.h"

#define HDF_LOG_TAG sdio_if_c

#define SDIO_NAME_LEN 32
#define SDIO_BUS_MAX 2

static struct SdioCntlr *SdioGetCntlrByBusNum(int16_t busNum)
{
    struct SdioCntlr *cntlr = NULL;
    char *serviceName = NULL;

    if (busNum < 0 || busNum >= SDIO_BUS_MAX) {
        HDF_LOGE("SdioGetCntlrByBusNum: invalid bus:%d", busNum);
        return NULL;
    }
    serviceName = OsalMemCalloc(SDIO_NAME_LEN + 1);
    if (serviceName == NULL) {
        return NULL;
    }
    if (snprintf_s(serviceName, SDIO_NAME_LEN + 1, SDIO_NAME_LEN,
        "HDF_PLATFORM_SDIO_%d", busNum) < 0) {
        HDF_LOGE("SdioGetCntlrByBusNum: format service name fail!");
        OsalMemFree(serviceName);
        return NULL;
    }
    cntlr = (struct SdioCntlr*)DevSvcManagerClntGetService(serviceName);
    if (cntlr == NULL) {
        HDF_LOGE("SdioGetCntlrByBusNum: get service fail!");
    }
    OsalMemFree(serviceName);
    return cntlr;
}

struct DevHandle *SdioOpen(int16_t busNum)
{
    struct DevHandle *handle = NULL;
    struct SdioCntlr *cntlr = NULL;
    int32_t ret;

    cntlr = SdioGetCntlrByBusNum(busNum);
    if (cntlr == NULL) {
        HDF_LOGE("SdioOpen: SdioGetCntlrByBusNum fail!");
        return NULL;
    }
    if (cntlr->method == NULL) {
        HDF_LOGE("SdioOpen: method is NULL!");
        return NULL;
    }
    if (cntlr->method->findFunc == NULL) {
        HDF_LOGE("SdioOpen: findFunc is NULL!");
        return NULL;
    }

    ret = cntlr->method->findFunc(cntlr, &(cntlr->configData));
    if (ret != HDF_SUCCESS) {
        HDF_LOGE("SdioOpen: findFunc fail!");
        return NULL;
    }

    handle = OsalMemCalloc(sizeof(*handle));
    if (handle == NULL) {
        HDF_LOGE("SdioOpen: OsalMemCalloc fail!");
        return NULL;
    }
    handle->object = cntlr;
    HDF_LOGD("SdioOpen: Success!");
    return handle;
}

void SdioClose(struct DevHandle *handle)
{
    if (handle != NULL) {
        handle->object = NULL;
        OsalMemFree(handle);
    }
}

int32_t SdioReadBytes(struct DevHandle *handle, uint8_t *data, uint32_t addr,
    uint32_t size, uint32_t timeOut)
{
    struct SdioCntlr *cntlr = NULL;

    if (handle == NULL || handle->object == NULL) {
        HDF_LOGE("SdioReadBytes: handle or object is null!");
        return HDF_ERR_INVALID_OBJECT;
    }
    if (data == NULL) {
        HDF_LOGE("SdioReadBytes: data is null!");
        return HDF_ERR_INVALID_PARAM;
    }

    cntlr = (struct SdioCntlr *)handle->object;
    if (cntlr->method == NULL || cntlr->method->incrAddrReadBytes == NULL) {
        HDF_LOGE("SdioReadBytes: method or incrAddrReadBytes is null!");
        return HDF_ERR_NOT_SUPPORT;
    }
    HDF_LOGD("SdioReadBytes: Success!");
    return cntlr->method->incrAddrReadBytes(cntlr, data, addr, size, timeOut);
}

int32_t SdioWriteBytes(struct DevHandle *handle, uint8_t *data, uint32_t addr,
    uint32_t size, uint32_t timeOut)
{
    struct SdioCntlr *cntlr = NULL;

    if (handle == NULL || handle->object == NULL) {
        HDF_LOGE("SdioWriteBytes: handle or object is null!");
        return HDF_ERR_INVALID_OBJECT;
    }
    if (data == NULL) {
        HDF_LOGE("SdioWriteBytes: data is null!");
        return HDF_ERR_INVALID_PARAM;
    }

    cntlr = (struct SdioCntlr *)handle->object;
    if (cntlr->method == NULL || cntlr->method->incrAddrWriteBytes == NULL) {
        HDF_LOGE("SdioWriteBytes: method or incrAddrWriteBytes is null!");
        return HDF_ERR_NOT_SUPPORT;
    }
    HDF_LOGD("SdioWriteBytes: Success!");
    return cntlr->method->incrAddrWriteBytes(cntlr, data, addr, size, timeOut);
}

int32_t SdioReadBytesFromFixedAddr(struct DevHandle *handle, uint8_t *data,
    uint32_t addr, uint32_t size, uint32_t timeOut)
{
    struct SdioCntlr *cntlr = NULL;

    if (handle == NULL || handle->object == NULL) {
        HDF_LOGE("SdioReadBytesFromFixedAddr: handle or object is null!");
        return HDF_ERR_INVALID_OBJECT;
    }
    if (data == NULL) {
        HDF_LOGE("SdioReadBytesFromFixedAddr: data is null!");
        return HDF_ERR_INVALID_PARAM;
    }

    cntlr = (struct SdioCntlr *)handle->object;
    if (cntlr->method == NULL || cntlr->method->fixedAddrReadBytes == NULL) {
        HDF_LOGE("SdioReadBytesFromFixedAddr: method or incrAddrWriteBytes is null!");
        return HDF_ERR_NOT_SUPPORT;
    }
    HDF_LOGD("SdioReadBytesFromFixedAddr: Success!");
    return cntlr->method->fixedAddrReadBytes(cntlr, data, addr, size, timeOut);
}

int32_t SdioWriteBytesToFixedAddr(struct DevHandle *handle, uint8_t *data,
    uint32_t addr, uint32_t size, uint32_t timeOut)
{
    struct SdioCntlr *cntlr = NULL;

    if (handle == NULL || handle->object == NULL) {
        HDF_LOGE("SdioWriteBytesToFixedAddr: handle or object is null!");
        return HDF_ERR_INVALID_OBJECT;
    }
    if (data == NULL) {
        HDF_LOGE("SdioWriteBytesToFixedAddr: data is null!");
        return HDF_ERR_INVALID_PARAM;
    }

    cntlr = (struct SdioCntlr *)handle->object;
    if (cntlr->method == NULL || cntlr->method->fixedAddrWriteBytes == NULL) {
        HDF_LOGE("SdioWriteBytesToFixedAddr: method or fixedAddrWriteBytes is null!");
        return HDF_ERR_NOT_SUPPORT;
    }
    HDF_LOGD("SdioWriteBytesToFixedAddr: Success!");
    return cntlr->method->fixedAddrWriteBytes(cntlr, data, addr, size, timeOut);
}

int32_t SdioReadBytesFromFunc0(struct DevHandle *handle, uint8_t *data,
    uint32_t addr, uint32_t size, uint32_t timeOut)
{
    struct SdioCntlr *cntlr = NULL;

    if (handle == NULL || handle->object == NULL) {
        HDF_LOGE("SdioReadBytesFromFunc0: handle or object is null!");
        return HDF_ERR_INVALID_OBJECT;
    }
    if (data == NULL) {
        HDF_LOGE("SdioReadBytesFromFunc0: data is null!");
        return HDF_ERR_INVALID_PARAM;
    }

    cntlr = (struct SdioCntlr *)handle->object;
    if (cntlr->method == NULL || cntlr->method->func0ReadBytes == NULL) {
        HDF_LOGE("SdioReadBytesFromFunc0: method or func0ReadBytes is null!");
        return HDF_ERR_NOT_SUPPORT;
    }
    HDF_LOGD("SdioReadBytesFromFunc0: Success!");
    return cntlr->method->func0ReadBytes(cntlr, data, addr, size, timeOut);
}

int32_t SdioWriteBytesToFunc0(struct DevHandle *handle, uint8_t *data,
    uint32_t addr, uint32_t size, uint32_t timeOut)
{
    struct SdioCntlr *cntlr = NULL;

    if (handle == NULL || handle->object == NULL) {
        HDF_LOGE("SdioWriteBytesToFunc0: handle or object is null!");
        return HDF_ERR_INVALID_OBJECT;
    }
    if (data == NULL) {
        HDF_LOGE("SdioWriteBytesToFunc0: data is null!");
        return HDF_ERR_INVALID_PARAM;
    }

    cntlr = (struct SdioCntlr *)handle->object;
    if (cntlr->method == NULL || cntlr->method->func0WriteBytes == NULL) {
        HDF_LOGE("SdioWriteBytesToFunc0: method or func0WriteBytes is null!");
        return HDF_ERR_NOT_SUPPORT;
    }
    HDF_LOGD("SdioWriteBytesToFunc0: Success!");
    return cntlr->method->func0WriteBytes(cntlr, data, addr, size, timeOut);
}

int32_t SdioSetBlockSize(struct DevHandle *handle, uint32_t blockSize)
{
    struct SdioCntlr *cntlr = NULL;

    if (handle == NULL || handle->object == NULL) {
        HDF_LOGE("SdioSetBlockSize: handle or object is null!");
        return HDF_ERR_INVALID_OBJECT;
    }

    cntlr = (struct SdioCntlr *)handle->object;
    if (cntlr->method == NULL || cntlr->method->setBlockSize == NULL) {
        HDF_LOGE("SdioSetBlockSize: method or setBlockSize is null!");
        return HDF_ERR_NOT_SUPPORT;
    }
    HDF_LOGD("SdioSetBlockSize: Success!");
    return cntlr->method->setBlockSize(cntlr, blockSize);
}

int32_t SdioGetCommonInfo(struct DevHandle *handle, SdioCommonInfo *info, SdioCommonInfoType infoType)
{
    struct SdioCntlr *cntlr = NULL;

    if (handle == NULL || handle->object == NULL) {
        HDF_LOGE("SdioGetCommonInfo: handle or object is null!");
        return HDF_ERR_INVALID_OBJECT;
    }
    if (info == NULL) {
        HDF_LOGE("SdioGetCommonInfo: info is NULL!");
        return HDF_ERR_INVALID_PARAM;
    }

    cntlr = (struct SdioCntlr *)handle->object;
    if (cntlr->method == NULL || cntlr->method->getCommonInfo == NULL) {
        HDF_LOGE("SdioGetCommonInfo: method or getCommonInfo is null!");
        return HDF_ERR_NOT_SUPPORT;
    }
    HDF_LOGD("SdioGetCommonInfo: Success! infoType is %d.", infoType);
    return cntlr->method->getCommonInfo(cntlr, info, infoType);
}

int32_t SdioSetCommonInfo(struct DevHandle *handle, SdioCommonInfo *info, SdioCommonInfoType infoType)
{
    struct SdioCntlr *cntlr = NULL;

    if (handle == NULL || handle->object == NULL) {
        HDF_LOGE("SdioSetCommonInfo: handle or object is null!");
        return HDF_ERR_INVALID_OBJECT;
    }
    if (info == NULL) {
        HDF_LOGE("SdioSetCommonInfo: info is NULL!");
        return HDF_ERR_INVALID_PARAM;
    }

    cntlr = (struct SdioCntlr *)handle->object;
    if (cntlr->method == NULL || cntlr->method->setCommonInfo == NULL) {
        HDF_LOGE("SdioSetCommonInfo: method or setCommonInfo is null!");
        return HDF_ERR_NOT_SUPPORT;
    }
    HDF_LOGD("SdioSetCommonInfo: Success! infoType is %d.", infoType);
    return cntlr->method->setCommonInfo(cntlr, info, infoType);
}

int32_t SdioFlushData(struct DevHandle *handle)
{
    struct SdioCntlr *cntlr = NULL;

    if (handle == NULL || handle->object == NULL) {
        HDF_LOGE("SdioFlushData: handle or object is null!");
        return HDF_ERR_INVALID_OBJECT;
    }

    cntlr = (struct SdioCntlr *)handle->object;
    if (cntlr->method == NULL || cntlr->method->flushData == NULL) {
        HDF_LOGE("SdioFlushData: method or flushData is null!");
        return HDF_ERR_NOT_SUPPORT;
    }
    HDF_LOGD("SdioFlushData: Success!");
    return cntlr->method->flushData(cntlr);
}

void SdioClaimHost(struct DevHandle *handle)
{
    struct SdioCntlr *cntlr = NULL;

    if (handle == NULL || handle->object == NULL) {
        HDF_LOGE("SdioClaimHost: handle or object is null!");
        return;
    }

    cntlr = (struct SdioCntlr *)handle->object;
    if (cntlr->method == NULL || cntlr->method->claimHost == NULL) {
        HDF_LOGE("SdioClaimHost: method or claimHost is null!");
        return;
    }
    HDF_LOGD("SdioClaimHost: Success!");
    cntlr->method->claimHost(cntlr);
}

void SdioReleaseHost(struct DevHandle *handle)
{
    struct SdioCntlr *cntlr = NULL;

    if (handle == NULL || handle->object == NULL) {
        HDF_LOGE("SdioReleaseHost: handle or object is null!");
        return;
    }

    cntlr = (struct SdioCntlr *)handle->object;
    if (cntlr->method == NULL || cntlr->method->releaseHost == NULL) {
        HDF_LOGE("SdioReleaseHost: method or releaseHost is null!");
        return;
    }
    HDF_LOGD("SdioReleaseHost: Success!");
    cntlr->method->releaseHost(cntlr);
}

int32_t SdioEnableFunc(struct DevHandle *handle)
{
    struct SdioCntlr *cntlr = NULL;

    if (handle == NULL || handle->object == NULL) {
        HDF_LOGE("SdioEnableFunc: handle or object is null!");
        return HDF_ERR_INVALID_OBJECT;
    }

    cntlr = (struct SdioCntlr *)handle->object;
    if (cntlr->method == NULL || cntlr->method->enableFunc == NULL) {
        HDF_LOGE("SdioEnableFunc: method or enableFunc is null!");
        return HDF_ERR_NOT_SUPPORT;
    }
    HDF_LOGD("SdioEnableFunc: Success!");
    return cntlr->method->enableFunc(cntlr);
}

int32_t SdioDisableFunc(struct DevHandle *handle)
{
    struct SdioCntlr *cntlr = NULL;

    if (handle == NULL || handle->object == NULL) {
        HDF_LOGE("SdioDisableFunc: handle or object is null!");
        return HDF_ERR_INVALID_OBJECT;
    }

    cntlr = (struct SdioCntlr *)handle->object;
    if (cntlr->method == NULL || cntlr->method->disableFunc == NULL) {
        HDF_LOGE("SdioDisableFunc: method or disableFunc is null!");
        return HDF_ERR_NOT_SUPPORT;
    }
    HDF_LOGD("SdioDisableFunc: Success!");
    return cntlr->method->disableFunc(cntlr);
}

int32_t SdioClaimIrq(struct DevHandle *handle, SdioIrqHandler *irqHandler)
{
    struct SdioCntlr *cntlr = NULL;

    if (handle == NULL || handle->object == NULL) {
        HDF_LOGE("SdioClaimIrq: handle or object is null!");
        return HDF_ERR_INVALID_OBJECT;
    }
    if (irqHandler == NULL) {
        HDF_LOGE("SdioClaimIrq: irqHandler is null!");
        return HDF_ERR_INVALID_PARAM;
    }

    cntlr = (struct SdioCntlr *)handle->object;
    if (cntlr->method == NULL || cntlr->method->claimIrq == NULL) {
        HDF_LOGE("SdioClaimIrq: method or claimIrq is null!");
        return HDF_ERR_NOT_SUPPORT;
    }
    HDF_LOGD("SdioClaimIrq: Success!");
    return cntlr->method->claimIrq(cntlr, irqHandler);
}

int32_t SdioReleaseIrq(struct DevHandle *handle)
{
    struct SdioCntlr *cntlr = NULL;

    if (handle == NULL || handle->object == NULL) {
        HDF_LOGE("SdioReleaseIrq: handle or object is null!");
        return HDF_ERR_INVALID_OBJECT;
    }

    cntlr = (struct SdioCntlr *)handle->object;
    if (cntlr->method == NULL || cntlr->method->releaseIrq == NULL) {
        HDF_LOGE("SdioReleaseIrq: method or releaseIrq is null!");
        return HDF_ERR_NOT_SUPPORT;
    }
    HDF_LOGD("SdioReleaseIrq: Success!");
    return cntlr->method->releaseIrq(cntlr);
}
