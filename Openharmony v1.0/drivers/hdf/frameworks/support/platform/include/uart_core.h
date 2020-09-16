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

#ifndef UART_CORE_H
#define UART_CORE_H

#include "hdf_base.h"
#include "hdf_device_desc.h"
#include "uart_if.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

/**
 * @brief uart device operations.
 */
struct UartHost {
    struct IDeviceIoService service;
    struct HdfDeviceObject *device;
    uint32_t num;
    void *priv;
    struct UartHostMethod *method;
};

struct UartHostMethod {
    int32_t (*Init)(struct UartHost *host);
    int32_t (*Deinit)(struct UartHost *host);
    int32_t (*Read)(struct UartHost *host, uint8_t *data, uint32_t size);
    int32_t (*Write)(struct UartHost *host, uint8_t *data, uint32_t size);
    int32_t (*GetBaud)(struct UartHost *host, uint32_t *baudRate);
    int32_t (*SetBaud)(struct UartHost *host, uint32_t baudRate);
    int32_t (*GetAttribute)(struct UartHost *host, struct UartAttribute *attribute);
    int32_t (*SetAttribute)(struct UartHost *host, struct UartAttribute *attribute);
    int32_t (*SetTransMode)(struct UartHost *handle, enum UartTransMode mode);
};

struct UartHost *UartHostCreate(struct HdfDeviceObject *device);
void UartHostDestroy(struct UartHost *host);

/**
 * @brief Turn UartHost to a HdfDeviceObject.
 *
 * @param host Indicates the Uart host device.
 *
 * @return Retrns the pointer of the HdfDeviceObject on success; returns NULL otherwise.
 * @since 1.0
 */
static inline struct HdfDeviceObject *UartHostToDevice(struct UartHost *host)
{
    return (host == NULL) ? NULL : host->device;
}

/**
 * @brief Turn HdfDeviceObject to an UartHost.
 *
 * @param device Indicates a HdfDeviceObject.
 *
 * @return Retrns the pointer of the UartHost on success; returns NULL otherwise.
 * @since 1.0
 */
static inline struct UartHost *UartHostFromDevice(struct HdfDeviceObject *device)
{
    return (device == NULL) ? NULL : (struct UartHost *)device->service;
}

static inline int32_t UartHostInit(struct UartHost *host)
{
    if (host == NULL || host->method == NULL) {
        return HDF_ERR_INVALID_PARAM;
    }
    if (host->method->Init != NULL) {
        return host->method->Init(host);
    }
    return HDF_SUCCESS;
}

static inline int32_t UartHostDeinit(struct UartHost *host)
{
    if (host == NULL || host->method == NULL) {
        return HDF_ERR_INVALID_PARAM;
    }
    if (host->method->Deinit != NULL) {
        return host->method->Deinit(host);
    }
    return HDF_SUCCESS;
}

static inline int32_t UartHostRead(struct UartHost *host, uint8_t *data, uint32_t size)
{
    if (host == NULL || host->method == NULL || host->method->Read == NULL) {
        return HDF_ERR_NOT_SUPPORT;
    }
    return host->method->Read(host, data, size);
}

static inline int32_t UartHostWrite(struct UartHost *host, uint8_t *data, uint32_t size)
{
    if (host == NULL || host->method == NULL || host->method->Write == NULL) {
        return HDF_ERR_NOT_SUPPORT;
    }
    return host->method->Write(host, data, size);
}

static inline int32_t UartHostGetBaud(struct UartHost *host, uint32_t *baudRate)
{
    if (host == NULL || host->method == NULL || host->method->GetBaud == NULL) {
        return HDF_ERR_NOT_SUPPORT;
    }
    return host->method->GetBaud(host, baudRate);
}

static inline int32_t UartHostSetBaud(struct UartHost *host, uint32_t baudRate)
{
    if (host == NULL || host->method == NULL || host->method->SetBaud == NULL) {
        return HDF_ERR_NOT_SUPPORT;
    }
    return host->method->SetBaud(host, baudRate);
}

static inline int32_t UartHostGetAttribute(struct UartHost *host, struct UartAttribute *attribute)
{
    if (host == NULL || host->method == NULL || host->method->GetAttribute == NULL) {
        return HDF_ERR_NOT_SUPPORT;
    }
    return host->method->GetAttribute(host, attribute);
}

static inline int32_t UartHostSetAttribute(struct UartHost *host, struct UartAttribute *attribute)
{
    if (host == NULL || host->method == NULL || host->method->SetAttribute == NULL) {
        return HDF_ERR_NOT_SUPPORT;
    }
    return host->method->SetAttribute(host, attribute);
}

static inline int32_t UartHostSetTransMode(struct UartHost *host, enum UartTransMode mode)
{
    if (host == NULL || host->method == NULL || host->method->SetTransMode == NULL) {
        return HDF_ERR_NOT_SUPPORT;
    }
    return host->method->SetTransMode(host, mode);
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* UART_CORE_H */
