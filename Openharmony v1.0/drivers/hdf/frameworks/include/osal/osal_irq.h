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

/**
 * @addtogroup OSAL
 * @{
 *
 * @brief Defines the structures and interfaces for the Operating System Abstraction Layer (OSAL) module.
 *
 * The OSAL module harmonizes OS interface differences and provides unified OS interfaces externally,
 * including the memory management, thread, mutex, spinlock, semaphore, timer, file, interrupt, time,
 * atomic, firmware, and I/O operation modules.
 *
 * @since 1.0
 * @version 1.0
 */

/**
 * @file osal_irq.h
 *
 * @brief Declares interrupt request (IRQ) interfaces and common IRQ trigger modes.
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef OSAL_IRQ_H
#define OSAL_IRQ_H

#include "hdf_base.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @brief Enumerates interrupt trigger modes.
 *
 * @since 1.1
 */
typedef enum {
    OSAL_IRQF_TRIGGER_NONE = 0, /**< Edge-triggered is not set */
    OSAL_IRQF_TRIGGER_RISING = 1, /**< Rising edge triggered */
    OSAL_IRQF_TRIGGER_FALLING = 2, /**< Failing edge triggered */
    OSAL_IRQF_TRIGGER_HIGH = 4, /**< High-level triggered */
    OSAL_IRQF_TRIGGER_LOW = 8, /**< Low-level triggered */
} OSAL_IRQ_TRIGGER_MODE;

/**
 * @brief Defines an IRQ type.
 */
typedef uint32_t (*OsalIRQHandle)(uint32_t irqId, void *dev);

/**
 * @brief Registers an IRQ.
 *
 * @param irqId Indicates the IRQ ID.
 * @param config Indicates the interrupt trigger mode. For details, see {@link OSAL_IRQ_TRIGGER_MODE}.
 * @param handle Indicates the interrupt processing function.
 * @param name Indicates the pointer to the device name for registering an IRQ.
 * @param dev Indicates the pointer to the parameter passed to the interrupt processing function.
 *
 * @return Returns a value listed below: \n
 * HDF_STATUS | Description
 * ----------------------| -----------------------
 * HDF_SUCCESS | The operation is successful.
 * HDF_FAILURE | Failed to invoke the system function to register the IRQ.
 * HDF_ERR_INVALID_PARAM | Invalid parameter.
 *
 * @since 1.0
 * @version 1.0
 */
int32_t OsalRegisterIrq(uint32_t irqId, uint32_t config, OsalIRQHandle handle, const char *name, void *dev);

/**
 * @brief Unregisters an IRQ.
 *
 * @param irqId Indicates the IRQ ID.
 *
 * @return Returns a value listed below: \n
 * HDF_STATUS | Description
 * ----------------------| -----------------------
 * HDF_SUCCESS | The operation is successful.
 * HDF_FAILURE | Failed to invoke the system function to unregister the IRQ.
 * HDF_ERR_INVALID_PARAM | Invalid parameter.
 *
 * @since 1.0
 * @version 1.0
 */
int32_t OsalUnregisterIrq(uint32_t irqId);

/**
 * @brief Enables an IRQ.
 *
 * @param irqId Indicates the IRQ ID.
 *
 * @return Returns a value listed below: \n
 * HDF_STATUS | Description
 * ----------------------| -----------------------
 * HDF_SUCCESS | The operation is successful.
 * HDF_ERR_INVALID_PARAM | Invalid parameter.
 *
 * @since 1.0
 * @version 1.0
 */
int32_t OsalEnableIrq(uint32_t irqId);

/**
 * @brief Disables an IRQ.
 *
 * @param irqId Indicates the IRQ ID.
 *
 * @return Returns a value listed below: \n
 * HDF_STATUS | Description
 * ----------------------| -----------------------
 * HDF_SUCCESS | The operation is successful.
 * HDF_ERR_INVALID_PARAM | Invalid parameter.
 *
 * @since 1.0
 * @version 1.0
 */
int32_t OsalDisableIrq(uint32_t irqId);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* OSAL_IRQ_H */
/** @} */
