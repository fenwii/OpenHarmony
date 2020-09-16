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
 * @addtogroup DriverUtils
 * @{
 *
 * @brief Defines common macros and interfaces of the driver module.
 *
 * This module provides interfaces such as log printing, doubly linked list operations, and work queues.
 *
 * @since 1.0
 * @version 1.0
 */

/**
 * @file hdf_base.h
 *
 * @brief Declares driver common types, including the enumerated values returned by the function
 * and the macro for obtaining the array size.
 *
 * @since 1.0
 * @version 1.0
 */
#ifndef HDF_BASE_TYPE_H
#define HDF_BASE_TYPE_H

#if defined(__KERNEL__)
#include <linux/types.h>
#else
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @brief Enumerates HDF return value types.
 */
typedef enum {
    HDF_SUCCESS  = 0, /**< The operation is successful. */
    HDF_FAILURE = -1, /**< Failed to invoke the OS underlying function. */
    HDF_ERR_NOT_SUPPORT = -2, /**< Not supported. */
    HDF_ERR_INVALID_PARAM = -3, /**< Invalid parameter. */
    HDF_ERR_INVALID_OBJECT = -4, /**< Invalid object. */
    HDF_ERR_MALLOC_FAIL    = -6, /**< Memory allocation fails. */
    HDF_ERR_TIMEOUT        = -7, /**< Timeout occurs. */
    HDF_ERR_THREAD_CREATE_FAIL = -10, /**< Failed to create a thread. */
    HDF_ERR_QUEUE_FULL  = -15, /**< The queue is full. */
    HDF_ERR_DEVICE_BUSY = -16, /**< The device is busy. */
    HDF_ERR_IO          = -17, /**< I/O error. */
    HDF_ERR_BAD_FD      = -18, /**< Incorrect file descriptor. */

#define HDF_BSP_ERR_START (-100) /**< Defines the start of the Board Support Package (BSP) module error codes. */
#define HDF_BSP_ERR_NUM(v) (HDF_BSP_ERR_START + (v)) /**< Defines the BSP module error codes. */
    HDF_BSP_ERR_OP = HDF_BSP_ERR_NUM(-1), /**< Failed to operate a BSP module. */
    HDF_ERR_BSP_PLT_API_ERR = HDF_BSP_ERR_NUM(-2), /**< The platform API of the BSP module is incorrect. */
    HDF_PAL_ERR_DEV_CREATE = HDF_BSP_ERR_NUM(-3), /**< Failed to create a BSP module device. */
    HDF_PAL_ERR_INNER = HDF_BSP_ERR_NUM(-4), /**< Internal error codes of the BSP module. */

#define HDF_DEV_ERR_START (-200) /**< Defines the start of the device module error codes. */
#define HDF_DEV_ERR_NUM(v) (HDF_DEV_ERR_START + (v)) /**< Defines the device module error codes. */
    HDF_DEV_ERR_NO_MEMORY               = HDF_DEV_ERR_NUM(-1), /**< Failed to allocate memory to the device module. */
    HDF_DEV_ERR_NO_DEVICE               = HDF_DEV_ERR_NUM(-2), /**< The device module has no device. */
    HDF_DEV_ERR_NO_DEVICE_SERVICE       = HDF_DEV_ERR_NUM(-3), /**< The device module has no device service. */
    HDF_DEV_ERR_DEV_INIT_FAIL           = HDF_DEV_ERR_NUM(-4), /**< Failed to initialize a device module. */
    HDF_DEV_ERR_PUBLISH_FAIL            = HDF_DEV_ERR_NUM(-5), /**< The device module failed to release a service. */
    HDF_DEV_ERR_ATTACHDEV_FAIL          = HDF_DEV_ERR_NUM(-6), /**< Failed to attach a device to a device module. */
    HDF_DEV_ERR_NODATA                  = HDF_DEV_ERR_NUM(-7), /**< Failed to read data from a device module. */
    HDF_DEV_ERR_NORANGE                 = HDF_DEV_ERR_NUM(-8), /**< The device module data is out of range. */
    HDF_DEV_ERR_OP                      = HDF_DEV_ERR_NUM(-10), /**< Failed to operate a device module. */
} HDF_STATUS;

/**
 * @brief Indicates that the function keeps waiting to obtain a semaphore or mutex.
 */
#define HDF_WAIT_FOREVER 0xFFFFFFFF

/**
 * @brief Defines the array size.
 */
#define HDF_ARRAY_SIZE(a) (sizeof(a) / sizeof((a)[0]))

/**
 * @brief Defines a time conversion unit, for example, the unit for converting from second to millisecond.
 */
#define HDF_KILO_UNIT 1000

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* HDF_BASE_TYPE_H */
/** @} */
