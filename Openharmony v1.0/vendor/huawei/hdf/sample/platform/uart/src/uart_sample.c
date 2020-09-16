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

#include "device_resource_if.h"
#include "buf_fifo.h"
#include "hdf_device_desc.h"
#include "hdf_log.h"
#include "hisoc/uart.h"
#include "osal_io.h"
#include "osal_mem.h"
#include "uart_core.h"
#include "uart_dev_sample.h"
#include "uart_dispatch_sample.h"
#include "uart_pl011_sample.h"

#define HDF_LOG_TAG uart_sample
#define UART_RX_FIFO_SIZE 128

static uint8_t g_fifoBuffer[UART_RX_FIFO_SIZE] = {0};

/* HdfDriverEntry method definitions */
static int32_t HdfUartSampleBind(struct HdfDeviceObject *device);
static int32_t HdfUartSampleInit(struct HdfDeviceObject *device);
static void HdfUartSampleRelease(struct HdfDeviceObject *device);

/* HdfDriverEntry definitions */
struct HdfDriverEntry g_hdfUartSample = {
    .moduleVersion = 1,
    .moduleName = "UART_SAMPLE",
    .Bind = HdfUartSampleBind,
    .Init = HdfUartSampleInit,
    .Release = HdfUartSampleRelease,
};

// Initialize HdfDriverEntry
HDF_INIT(g_hdfUartSample);

/* UartHostMethod method definitions */
static int32_t SampleInit(struct UartHost *host);
static int32_t SampleDeinit(struct UartHost *host);
static int32_t SampleWrite(struct UartHost *host, uint8_t *data, uint32_t size);
static int32_t SampleSetBaud(struct UartHost *host, uint32_t baudRate);
static int32_t SampleGetBaud(struct UartHost *host, uint32_t *baudRate);

/* UartHostMethod definitions */
struct UartHostMethod g_uartSampleHostMethod = {
    .Init = SampleInit,
    .Deinit = SampleDeinit,
    .Read = NULL,
    .Write = SampleWrite,
    .SetBaud = SampleSetBaud,
    .GetBaud = SampleGetBaud,
    .SetAttribute = NULL,
    .GetAttribute = NULL,
    .SetTransMode = NULL,
};

/* UartHostMethod implementations */
static int32_t SampleInit(struct UartHost *host)
{
    HDF_LOGI("%s: Enter", __func__);
    if (host == NULL) {
        HDF_LOGE("%s: invalid parameter", __func__);
        return HDF_ERR_INVALID_PARAM;
    }
    return HDF_SUCCESS;
}

static int32_t SampleDeinit(struct UartHost *host)
{
    HDF_LOGI("%s: Enter", __func__);
    if (host == NULL) {
        HDF_LOGE("%s: invalid parameter", __func__);
        return HDF_ERR_INVALID_PARAM;
    }
    return HDF_SUCCESS;
}

static int32_t SampleWrite(struct UartHost *host, uint8_t *data, uint32_t size)
{
    HDF_LOGI("%s: Enter", __func__);
    uint32_t idx;
    struct UartRegisterMap *regMap = NULL;
    struct UartDevice *device = NULL;

    if (host == NULL || data == NULL || size == 0) {
        HDF_LOGE("%s: invalid parameter", __func__);
        return HDF_ERR_INVALID_PARAM;
    }
    device = (struct UartDevice *)host->priv;
    if (device == NULL) {
        HDF_LOGE("%s: device is NULL", __func__);
        return HDF_ERR_INVALID_PARAM;
    }
    regMap = (struct UartRegisterMap *)device->resource.physBase;
    for (idx = 0; idx < size; idx++) {
        UartPl011Write(regMap, data[idx]);
    }
    return HDF_SUCCESS;
}

static int32_t SampleSetBaud(struct UartHost *host, uint32_t baudRate)
{
    HDF_LOGI("%s: Enter", __func__);
    struct UartDevice *device = NULL;
    struct UartRegisterMap *regMap = NULL;
    UartPl011Error err;

    if (host == NULL) {
        HDF_LOGE("%s: invalid parameter", __func__);
        return HDF_ERR_INVALID_PARAM;
    }
    device = (struct UartDevice *)host->priv;
    if (device == NULL) {
        HDF_LOGE("%s: device is NULL", __func__);
        return HDF_ERR_INVALID_PARAM;
    }
    regMap = (struct UartRegisterMap *)device->resource.physBase;
    if (device->state != UART_DEVICE_INITIALIZED) {
        return UART_PL011_ERR_NOT_INIT;
    }
    if (baudRate == 0) {
        return UART_PL011_ERR_INVALID_BAUD;
    }
    err = UartPl011SetBaudrate(regMap, device->uartClk, baudRate);
    if (err == UART_PL011_ERR_NONE) {
        device->baudrate = baudRate;
    }
    return err;
}

static int32_t SampleGetBaud(struct UartHost *host, uint32_t *baudRate)
{
    HDF_LOGI("%s: Enter", __func__);
    struct UartDevice *device = NULL;

    if (host == NULL) {
        HDF_LOGE("%s: invalid parameter", __func__);
        return HDF_ERR_INVALID_PARAM;
    }
    device = (struct UartDevice *)host->priv;
    if (device == NULL) {
        HDF_LOGE("%s: device is NULL", __func__);
        return HDF_ERR_INVALID_PARAM;
    }
    *baudRate = device->baudrate;
    return HDF_SUCCESS;
}

static int UartDeviceInit(struct UartDevice *device)
{
    UartPl011Error err;
    struct UartResource *resource = &device->resource;
    struct UartRegisterMap *regMap = (struct UartRegisterMap *)resource->physBase;
    if ((resource->uartClk == 0) || (resource->baudrate == 0)) {
        return HDF_ERR_INVALID_PARAM;
    }
    /* Updating the system clock */
    device->uartClk = resource->uartClk;
    uart_clk_cfg(0, true);
    /* clear and reset registers. */
    UartPl011ResetRegisters(regMap);
    /* set baud rate as device config */
    err = UartPl011SetBaudrate(regMap, resource->uartClk, resource->baudrate);
    if (err != UART_PL011_ERR_NONE) {
        return HDF_FAILURE;
    }
    /* set the data format as device config */
    UartPl011SetDataFormat(regMap, resource->wlen, resource->parity, resource->stopBit);
    /* Enabling the FIFOs */
    UartPl011EnableFifo(regMap);
    UartPl011Enable(regMap);
    BufferFifoInit(&device->rxFifo, g_fifoBuffer, UART_RX_FIFO_SIZE);
    device->state = UART_DEVICE_INITIALIZED;
    return HDF_SUCCESS;
}

static uint32_t UartDeviceGetResource(
    struct UartDevice *device, const struct DeviceResourceNode *resourceNode)
{
    struct UartResource *resource = &device->resource;
    struct DeviceResourceIface *dri = NULL;
    dri = DeviceResourceGetIfaceInstance(HDF_CONFIG_SOURCE);
    if (dri == NULL || dri->GetUint32 == NULL) {
        HDF_LOGE("DeviceResourceIface is invalid");
        return HDF_FAILURE;
    }

    if (dri->GetUint32(resourceNode, "num", &resource->num, 0) != HDF_SUCCESS) {
        HDF_LOGE("uart config  read num fail");
        return HDF_FAILURE;
    }
    if (dri->GetUint32(resourceNode, "base", &resource->base, 0) != HDF_SUCCESS) {
        HDF_LOGE("uart config  read base fail");
        return HDF_FAILURE;
    }
    resource->physBase = (unsigned long)OsalIoRemap(resource->base, 0x48);
    if (resource->physBase == 0) {
        HDF_LOGE("uart config fail to remap physBase");
        return HDF_FAILURE;
    }
    if (dri->GetUint32(resourceNode, "irqNum", &resource->irqNum, 0) != HDF_SUCCESS) {
        HDF_LOGE("uart config read irqNum fail");
        return HDF_FAILURE;
    }
    if (dri->GetUint32(resourceNode, "baudrate", &resource->baudrate, 0) != HDF_SUCCESS) {
        HDF_LOGE("uart config  read baudrate fail");
        return HDF_FAILURE;
    }
    if (dri->GetUint32(resourceNode, "wlen", &resource->wlen, 0) != HDF_SUCCESS) {
        HDF_LOGE("uart config  read wlen fail");
        return HDF_FAILURE;
    }
    if (dri->GetUint32(resourceNode, "parity", &resource->parity, 0) != HDF_SUCCESS) {
        HDF_LOGE("uart config  read parity fail");
        return HDF_FAILURE;
    }
    if (dri->GetUint32(resourceNode, "stopBit", &resource->stopBit, 0) != HDF_SUCCESS) {
        HDF_LOGE("uart config  read stopBit fail");
        return HDF_FAILURE;
    }
    if (dri->GetUint32(resourceNode, "uartClk", &resource->uartClk, 0) != HDF_SUCCESS) {
        HDF_LOGE("uart config  read uartClk fail");
        return HDF_FAILURE;
    }
    return HDF_SUCCESS;
}

static int32_t SampleAttach(struct UartHost *host, struct HdfDeviceObject *device)
{
    int32_t ret;
    struct UartDevice *uartDevice = NULL;
    if (device->property == NULL) {
        HDF_LOGE("%s: property is NULL", __func__);
        return HDF_FAILURE;
    }
    uartDevice = (struct UartDevice *)OsalMemCalloc(sizeof(struct UartDevice));
    if (uartDevice == NULL) {
        HDF_LOGE("%s: OsalMemCalloc uartDevice error", __func__);
        return HDF_ERR_MALLOC_FAIL;
    }
    SampleDispatchConstruct(uartDevice);
    device->service = &uartDevice->ioService;
    ret = UartDeviceGetResource(uartDevice, device->property);
    if (ret != HDF_SUCCESS) {
        (void)OsalMemFree(uartDevice);
        return HDF_FAILURE;
    }
    host->num = uartDevice->resource.num;
    host->priv = uartDevice;
    UartSampleAddDev(host);
    return UartDeviceInit(uartDevice);
}

static void UartDeviceDeinit(struct UartDevice *device)
{
    struct UartRegisterMap *regMap = (struct UartRegisterMap *)device->resource.physBase;
    /* wait for uart enter idle. */
    while (UartPl011IsBusy(regMap));
    UartPl011ResetRegisters(regMap);
    uart_clk_cfg(0, false);
    OsalIoUnmap((void *)device->resource.physBase);
    device->state = UART_DEVICE_UNINITIALIZED;
}

static void SampleDetach(struct UartHost *host)
{
    struct UartDevice *uartDevice = NULL;

    if (host->priv == NULL) {
        HDF_LOGE("%s: invalid parameter", __func__);
        return;
    }
    uartDevice = host->priv;
    UartDeviceDeinit(uartDevice);
    (void)OsalMemFree(uartDevice);
    host->priv = NULL;
}

/* HdfDriverEntry implementations */
static int32_t HdfUartSampleBind(struct HdfDeviceObject *device)
{
    if (device == NULL) {
        return HDF_ERR_INVALID_OBJECT;
    }
    HDF_LOGI("Enter %s:", __func__);
    return (UartHostCreate(device) == NULL) ? HDF_FAILURE : HDF_SUCCESS;
}

static int32_t HdfUartSampleInit(struct HdfDeviceObject *device)
{
    int32_t ret;
    struct UartHost *host = NULL;

    if (device == NULL) {
        HDF_LOGE("%s: device is NULL", __func__);
        return HDF_ERR_INVALID_OBJECT;
    }
    HDF_LOGI("Enter %s:", __func__);
    host = UartHostFromDevice(device);
    if (host == NULL) {
        HDF_LOGE("%s: host is NULL", __func__);
        return HDF_FAILURE;
    }
    ret = SampleAttach(host, device);
    if (ret != HDF_SUCCESS) {
        HDF_LOGE("%s: attach error", __func__);
        return HDF_FAILURE;
    }
    host->method = &g_uartSampleHostMethod;
    return ret;
}

static void HdfUartSampleRelease(struct HdfDeviceObject *device)
{
    struct UartHost *host = NULL;
    HDF_LOGI("Enter %s:", __func__);

    if (device == NULL) {
        HDF_LOGE("%s: device is NULL", __func__);
        return;
    }
    host = UartHostFromDevice(device);
    if (host == NULL) {
        HDF_LOGE("%s: host is NULL", __func__);
        return;
    }
    if (host->priv != NULL) {
        SampleDetach(host);
    }
    UartHostDestroy(host);
}
