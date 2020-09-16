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

#include "watchdog_if.h"
#include "devsvc_manager_clnt.h"
#include "hdf_base.h"
#include "hdf_log.h"
#include "osal_mem.h"
#include "securec.h"
#include "watchdog_core.h"

#define HDF_LOG_TAG watchdog_if

#define WATCHDOG_ID_MAX   8
#define WATCHDOG_NAME_LEN 32

static struct Watchdog *WatchdogGetById(int16_t wdtId)
{
    char *serviceName = NULL;
    struct Watchdog *service = NULL;

    if (wdtId < 0 || wdtId >= WATCHDOG_ID_MAX) {
        HDF_LOGE("WatchdogGetById: invalid id:%d\n", wdtId);
        return NULL;
    }
    serviceName = OsalMemCalloc(WATCHDOG_NAME_LEN + 1);
    if (serviceName == NULL) {
        return NULL;
    }
    if (snprintf_s(serviceName, WATCHDOG_NAME_LEN + 1, WATCHDOG_NAME_LEN,
        "HDF_PLATFORM_WATCHDOG_%d", wdtId) < 0) {
        HDF_LOGE("WatchdogGetById: format service name fail!\n");
        OsalMemFree(serviceName);
        return NULL;
    }
    service = (struct Watchdog *)DevSvcManagerClntGetService(serviceName);
    if (service == NULL) {
        HDF_LOGE("WatchdogGetById: get service fail!\n");
    }
    OsalMemFree(serviceName);
    return service;
}


struct DevHandle *WatchdogOpen(int16_t wdtId)
{
    struct DevHandle *handle = NULL;
    struct Watchdog *service = NULL;

    service = WatchdogGetById(wdtId);
    if (service == NULL) {
        return NULL;
    }
    handle = OsalMemCalloc(sizeof(*handle));
    if (handle == NULL) {
        return NULL;
    }
    handle->object = service;
    return handle;
}

void WatchdogClose(struct DevHandle *handle)
{
    if (handle != NULL) {
        handle->object = NULL;
        OsalMemFree(handle);
    }
}

int32_t WatchdogGetStatus(struct DevHandle *handle, int32_t *status)
{
    if (handle == NULL) {
        return HDF_ERR_INVALID_OBJECT;
    }
    return WatchdogCntlrGetStatus((struct WatchdogCntlr *)handle->object, status);
}

int32_t WatchdogStart(struct DevHandle *handle)
{
    if (handle == NULL) {
        return HDF_ERR_INVALID_OBJECT;
    }
    return WatchdogCntlrStart((struct WatchdogCntlr *)handle->object);
}

int32_t WatchdogStop(struct DevHandle *handle)
{
    if (handle == NULL) {
        return HDF_ERR_INVALID_OBJECT;
    }
    return WatchdogCntlrStop((struct WatchdogCntlr *)handle->object);
}

int32_t WatchdogSetTimeout(struct DevHandle *handle, uint32_t seconds)
{
    if (handle == NULL) {
        return HDF_ERR_INVALID_OBJECT;
    }
    return WatchdogCntlrSetTimeout((struct WatchdogCntlr *)handle->object, seconds);
}

int32_t WatchdogGetTimeout(struct DevHandle *handle, uint32_t *seconds)
{
    if (handle == NULL) {
        return HDF_ERR_INVALID_OBJECT;
    }
    return WatchdogCntlrGetTimeout((struct WatchdogCntlr *)handle->object, seconds);
}

int32_t WatchdogFeed(struct DevHandle *handle)
{
    if (handle == NULL) {
        return HDF_ERR_INVALID_OBJECT;
    }
    return WatchdogCntlrFeed((struct WatchdogCntlr *)handle->object);
}
