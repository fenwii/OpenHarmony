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

#include "securec.h"
#include "devsvc_manager_clnt.h"
#include "hdf_log.h"
#include "osal_mem.h"
#include "spi_core.h"
#include "spi_if.h"

#define HDF_LOG_TAG spi_if
#define HOST_NAME_LEN 32

struct SpiObject {
    struct SpiCntlr *cntlr;
    uint32_t csNum;
};

static struct SpiCntlr *SpiGetCntlrByBusNum(uint32_t num)
{
    int ret;
    char *name = NULL;
    struct SpiCntlr *cntlr = NULL;

    name = (char *)OsalMemCalloc(HOST_NAME_LEN + 1);
    if (name == NULL) {
        return NULL;
    }
    ret = snprintf_s(name, HOST_NAME_LEN + 1, HOST_NAME_LEN, "HDF_PLATFORM_SPI_%u", num);
    if (ret < 0) {
        HDF_LOGE("%s: snprintf_s failed\n", __func__);
        OsalMemFree(name);
        return NULL;
    }
    cntlr = (struct SpiCntlr *)DevSvcManagerClntGetService(name);
    OsalMemFree(name);
    return cntlr;
}

int32_t SpiTransfer(struct DevHandle *handle, struct SpiMsg *msgs, uint32_t count)
{
    struct SpiObject *obj = NULL;

    if (handle == NULL || handle->object == NULL) {
        return HDF_ERR_INVALID_PARAM;
    }
    obj = (struct SpiObject *)handle->object;
    return SpiCntlrTransfer(obj->cntlr, obj->csNum, msgs, count);
}

int32_t SpiRead(struct DevHandle *handle, uint8_t *buf, uint32_t len)
{
    struct SpiMsg msg = {0};

    msg.wbuf = NULL;
    msg.rbuf = buf;
    msg.len = len;
    return SpiTransfer(handle, &msg, 1);
}

int32_t SpiWrite(struct DevHandle *handle, uint8_t *buf, uint32_t len)
{
    struct SpiMsg msg = {0};

    msg.wbuf = buf;
    msg.rbuf = NULL;
    msg.len = len;
    return SpiTransfer(handle, &msg, 1);
}

int32_t SpiSetCfg(struct DevHandle *handle, struct SpiCfg *cfg)
{
    struct SpiObject *obj = NULL;

    if (handle == NULL || handle->object == NULL) {
        return HDF_ERR_INVALID_OBJECT;
    }
    obj = (struct SpiObject *)handle->object;
    return SpiCntlrSetCfg(obj->cntlr, obj->csNum, cfg);
}

int32_t SpiGetCfg(struct DevHandle *handle, struct SpiCfg *cfg)
{
    struct SpiObject *obj = NULL;

    if (handle == NULL || handle->object == NULL) {
        return HDF_ERR_INVALID_OBJECT;
    }
    obj = (struct SpiObject *)handle->object;
    return SpiCntlrGetCfg(obj->cntlr, obj->csNum, cfg);
}

void SpiClose(struct DevHandle *handle)
{
    if (handle == NULL) {
        HDF_LOGE("%s: handle is NULL\n", __func__);
        return;
    }
    if (handle->object != NULL) {
        OsalMemFree(handle->object);
        handle->object = NULL;
    }
    OsalMemFree(handle);
}

struct DevHandle *SpiOpen(const struct SpiDevInfo *info)
{
    struct DevHandle *handle = NULL;
    struct SpiObject *object = NULL;
    struct SpiCntlr *cntlr = NULL;

    if (info == NULL) {
        return NULL;
    }
    cntlr = SpiGetCntlrByBusNum(info->busNum);
    if (cntlr == NULL) {
        HDF_LOGE("%s: cntlr is null", __func__);
        return NULL;
    }
    handle = (struct DevHandle *)OsalMemCalloc(sizeof(*handle));
    if (handle == NULL) {
        HDF_LOGE("%s: handle malloc error\n", __func__);
        return NULL;
    }
    object = (struct SpiObject *)OsalMemCalloc(sizeof(*object));
    if (object == NULL) {
        HDF_LOGE("%s: object malloc error\n", __func__);
        OsalMemFree(handle);
        return NULL;
    }
    object->cntlr = cntlr;
    object->csNum = info->csNum;
    handle->object = object;
    return handle;
}
