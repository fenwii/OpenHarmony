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

#ifndef I2C_CORE_H
#define I2C_CORE_H

#include "hdf_base.h"
#include "hdf_device_desc.h"
#include "i2c_if.h"
#include "osal_mutex.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

struct I2cCntlr;
struct I2cMethod;

struct I2cCntlr {
    struct IDeviceIoService service;
    struct HdfDeviceObject *device;
    struct OsalMutex lock;
    int16_t busId;
    void *priv;
    struct I2cMethod *ops;
};

struct I2cMethod {
    /**
     * @brief Execute one or more I2C messages.
     *
     * @param cntlr Indicates the I2C controller device.
     * @param msgs Indicates the {@link I2cMsg} message array.
     * @param count Indicates the length of the message array.
     *
     * @return Returns the number of transferred message structures if the operation is successful;
     * returns a negative value otherwise.
     * @see I2cMsg
     * @since 1.0
     */
    int32_t (*transfer)(struct I2cCntlr *cntlr, struct I2cMsg *msgs, int16_t count);
};

/**
 * @brief Bind to a HdfDeviceObject, and do some necessary check
 *
 * @param cntlr Indicates the I2C controller device.
 * @param device The HdfDeviceObject of this I2cCntlr.
 *
 * @return Returns 0 on success; returns a negative value otherwise.
 * @since 1.0
 */
int32_t I2cCntlrAdd(struct I2cCntlr *cntlr);

/**
 * @brief Create a new I2cCntlr struct, and bind it to a HdfDeviceObject.
 *
 * @param cntlr Indicates the I2C controller device.
 *
 * @since 1.0
 */
void I2cCntlrRemove(struct I2cCntlr *cntlr);

/**
 * @brief Turn I2cCntlr to a HdfDeviceObject.
 *
 * @param cntlr Indicates the I2C controller device.
 *
 * @return Retrns the pointer of the HdfDeviceObject on success; returns NULL otherwise.
 * @since 1.0
 */
static inline struct HdfDeviceObject *I2cCntlrToDevice(struct I2cCntlr *cntlr)
{
    return (cntlr == NULL) ? NULL : cntlr->device;
}

/**
 * @brief Turn HdfDeviceObject to an I2cCntlr.
 *
 * @param device Indicates a HdfDeviceObject.
 *
 * @return Retrns the pointer of the I2cCntlr on success; returns NULL otherwise.
 * @since 1.0
 */
static inline struct I2cCntlr *I2cCntlrFromDevice(struct HdfDeviceObject *device)
{
    return (device == NULL) ? NULL : (struct I2cCntlr *)device->service;
}

int32_t I2cCntlrTransfer(struct I2cCntlr *cntlr, struct I2cMsg *msgs, int16_t count);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* I2C_CORE_H */
