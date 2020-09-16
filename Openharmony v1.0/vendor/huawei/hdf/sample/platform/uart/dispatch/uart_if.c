/* Copyright 2020 Huawei Device Co., Ltd.
 *
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

#include "uart_if.h"
#include "securec.h"
#include "hdf_log.h"
#include "osal_mem.h"
#include "hdf_io_service_if.h"

struct DevHandle *UartOpen(uint32_t port)
{
    int32_t ret;
    struct DevHandle *handle = NULL;
    char *serviceName = NULL;

    handle = (struct DevHandle *)OsalMemCalloc(sizeof(struct DevHandle));
    if (handle == NULL) {
        HDF_LOGE("Failed to OsalMemCalloc handle");
        return NULL;
    }

    serviceName = (char *)OsalMemCalloc(sizeof(char) * (MAX_DEV_NAME_SIZE + 1));
    if (serviceName == NULL) {
        HDF_LOGE("Failed to OsalMemCalloc serviceName");
        OsalMemFree(handle);
        return NULL;
    }
    ret = snprintf_s(serviceName, MAX_DEV_NAME_SIZE + 1, MAX_DEV_NAME_SIZE, UART_DEV_SERVICE_NAME_PREFIX, port);
    if (ret < 0) {
        HDF_LOGE("Failed to snprintf_s");
        OsalMemFree(handle);
        OsalMemFree(serviceName);
        return NULL;
    }

    struct HdfIoService *service = HdfIoServiceBind(serviceName, 0);
    if (service == NULL) {
        HDF_LOGE("Failed to get service %s", serviceName);
        OsalMemFree(handle);
        OsalMemFree(serviceName);
        return NULL;
    }
    OsalMemFree(serviceName);
    handle->object = service;
    return handle;
}

int32_t UartWrite(struct DevHandle *handle, uint8_t *data, uint32_t size)
{
    int ret;
    struct HdfIoService *service = NULL;

    if (handle == NULL || handle->object == NULL) {
        HDF_LOGE("handle or handle->object is NULL");
        return HDF_FAILURE;
    }

    struct HdfSBuf *sBuf = HdfSBufObtainDefaultSize();
    if (sBuf == NULL) {
        HDF_LOGE("Failed to obtain sBuf");
        return HDF_FAILURE;
    }

    if (!HdfSbufWriteBuffer(sBuf, data, size)) {
        HDF_LOGE("Failed to write sbuf");
        HdfSBufRecycle(sBuf);
        return HDF_FAILURE;
    }

    service = (struct HdfIoService *)handle->object;
    ret = service->dispatcher->Dispatch(&service->object, UART_WRITE, sBuf, NULL);
    if (ret != HDF_SUCCESS) {
        HDF_LOGE("Failed to send service call");
    }
    HdfSBufRecycle(sBuf);
    return ret;
}

void UartClose(struct DevHandle *handle)
{
    struct HdfIoService *service = NULL;

    if (handle == NULL || handle->object == NULL) {
        HDF_LOGE("handle or handle->object is NULL");
        return;
    }
    service = (struct HdfIoService *)handle->object;
    HdfIoServiceRecycle(service);
    OsalMemFree(handle);
}