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
#include "uart_core.h"
#include "uart_if.h"

#define HDF_LOG_TAG uart_if_c
#define UART_HOST_NAME_LEN 32

static struct UartHost *UartGetHostByBusNum(uint32_t num)
{
    int ret;
    char *name = NULL;
    struct UartHost *host = NULL;

    name = (char *)OsalMemCalloc(UART_HOST_NAME_LEN + 1);
    if (name == NULL) {
        return NULL;
    }
    ret = snprintf_s(name, UART_HOST_NAME_LEN + 1, UART_HOST_NAME_LEN,
        "HDF_PLATFORM_UART_%u", num);
    if (ret < 0) {
        HDF_LOGE("%s: snprintf_s failed\n", __func__);
        OsalMemFree(name);
        return NULL;
    }
    host = (struct UartHost *)DevSvcManagerClntGetService(name);
    OsalMemFree(name);
    return host;
}

struct DevHandle *UartOpen(uint32_t port)
{
    struct DevHandle *handle = NULL;
    struct UartHost *host = NULL;

    host = UartGetHostByBusNum(port);
    if (host == NULL) {
        HDF_LOGE("%s: get host error\n", __func__);
        return NULL;
    }
    handle = (struct DevHandle *)OsalMemCalloc(sizeof(*handle));
    if (handle == NULL) {
        HDF_LOGE("%s: handle malloc error\n", __func__);
        return NULL;
    }
    if (UartHostInit(host) != HDF_SUCCESS) {
        HDF_LOGE("%s: UartHostInit error\n", __func__);
        OsalMemFree(handle);
        return NULL;
    }
    handle->object = host;
    return handle;
}

void UartClose(struct DevHandle *handle)
{
    if (handle == NULL) {
        HDF_LOGE("%s: handle is NULL\n", __func__);
        return;
    }
    if (UartHostDeinit((struct UartHost *)handle->object) != HDF_SUCCESS) {
        HDF_LOGE("%s: UartHostDeinit error\n", __func__);
    }
    OsalMemFree(handle);
}

int32_t UartRead(struct DevHandle *handle, uint8_t *data, uint32_t size)
{
    if (handle == NULL) {
        return HDF_ERR_INVALID_PARAM;
    }
    return UartHostRead((struct UartHost *)handle->object, data, size);
}

int32_t UartWrite(struct DevHandle *handle, uint8_t *data, uint32_t size)
{
    if (handle == NULL) {
        return HDF_ERR_INVALID_PARAM;
    }
    return UartHostWrite((struct UartHost *)handle->object, data, size);
}

int32_t UartGetBaud(struct DevHandle *handle, uint32_t *baudRate)
{
    if (handle == NULL) {
        return HDF_ERR_INVALID_PARAM;
    }
    return UartHostGetBaud((struct UartHost *)handle->object, baudRate);
}

int32_t UartSetBaud(struct DevHandle *handle, uint32_t baudRate)
{
    if (handle == NULL) {
        return HDF_ERR_INVALID_PARAM;
    }
    return UartHostSetBaud((struct UartHost *)handle->object, baudRate);
}

int32_t UartGetAttribute(struct DevHandle *handle, struct UartAttribute *attribute)
{
    if (handle == NULL) {
        return HDF_ERR_INVALID_PARAM;
    }
    return UartHostGetAttribute((struct UartHost *)handle->object, attribute);
}

int32_t UartSetAttribute(struct DevHandle *handle, struct UartAttribute *attribute)
{
    if (handle == NULL) {
        return HDF_ERR_INVALID_PARAM;
    }
    return UartHostSetAttribute((struct UartHost *)handle->object, attribute);
}

int32_t UartSetTransMode(struct DevHandle *handle, enum UartTransMode mode)
{
    if (handle == NULL) {
        return HDF_ERR_INVALID_PARAM;
    }
    return UartHostSetTransMode((struct UartHost *)handle->object, mode);
}
