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

#include "uart_core.h"
#include "uart_dispatch_sample.h"
#include "hdf_log.h"
#include "hdf_sbuf.h"
#include "osal_mem.h"
#include "uart_pl011_sample.h"

#define HDF_LOG_TAG "uart_dispatch_sample"

static int32_t SampleDispatchWrite(struct UartDevice *device, struct HdfSBuf *txBuf)
{
    uint32_t idx;
    uint32_t dataSize = 0;
    const uint8_t *data = NULL;
    struct UartRegisterMap *regMap = (struct UartRegisterMap *)device->resource.physBase;

    if (regMap == NULL) {
        HDF_LOGE("%s: regMap is NULL", __func__);
        return HDF_FAILURE;
    }

    if (!HdfSbufReadBuffer(txBuf, (const void **)&data, &dataSize)) {
        HDF_LOGE("%s: Failed to read sbuf", __func__);
        return HDF_FAILURE;
    }
    regMap = (struct UartRegisterMap *)device->resource.physBase;
    for (idx = 0; idx < dataSize; idx++) {
        UartPl011Write(regMap, data[idx]);
    }
    return HDF_SUCCESS;
}

static int32_t SampleDispatch(struct HdfDeviceIoClient *client, int cmdId, struct HdfSBuf *data, struct HdfSBuf *reply)
{
    int32_t result = HDF_FAILURE;
    if (client == NULL || client->device == NULL) {
        HDF_LOGE("%s: client or client->device is NULL", __func__);
        return result;
    }
    struct UartDevice *uartDevice = (struct UartDevice *)client->device->service;
    if (uartDevice == NULL) {
        HDF_LOGE("%s: uartDevice is NULL", __func__);
        return result;
    }
    switch (cmdId) {
        case UART_WRITE: {
            result = SampleDispatchWrite(uartDevice, data);
            break;
        }
        default:
            break;
    }
    return result;
}

void SampleDispatchConstruct(struct UartDevice *device)
{
    struct IDeviceIoService *ioService = &device->ioService;
    if (ioService != NULL) {
        ioService->Dispatch = &SampleDispatch;
    }
}
