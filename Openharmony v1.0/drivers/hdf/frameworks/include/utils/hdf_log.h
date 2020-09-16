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
 * @file hdf_log.h
 *
 * @brief Declares log printing functions of the driver module.
 * This module provides functions for printing logs at the verbose, debug, information, warning, and error levels.
 *
 * To use these functions, you must define <b>HDF_LOG_TAG</b>, for example, #define HDF_LOG_TAG evt.
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef HDF_LOG_H
#define HDF_LOG_H

#ifdef HDF_LOG_TAG
#undef HDF_LOG_TAG
#endif /* HDF_LOG_TAG */

/** Add quotation mark */
#define LOG_TAG_MARK_EXTEND(HDF_TAG) #HDF_TAG
#define LOG_TAG_MARK(HDF_TAG) LOG_TAG_MARK_EXTEND(HDF_TAG)

#ifndef LOG_TAG
#define LOG_TAG LOG_TAG_MARK(HDF_LOG_TAG)
#endif /* LOG_TAG */

#if defined(_LINUX_USER_)
#include "cutils/log.h"
#elif defined(__KERNEL__)
#include <linux/printk.h>
#elif defined(__LITEOS__) && defined(__USER__)
#include <stdio.h>
#elif defined(__LITEOS__)
#include "los_printf.h"
#else
#include <stdio.h>
#endif /* __KERNEL__ */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#if defined(_LINUX_USER_)
/**
 * @brief Prints logs at the verbose level.
 *
 * To use this function, you must define <b>HDF_LOG_TAG</b>, for example, #define HDF_LOG_TAG evt.
 *
 * @since 1.0
 * @version 1.0
 */
#define HDF_LOGV(...) ALOGV(__VA_ARGS__)
/**
 * @brief Prints logs at the debug level.
 *
 * To use this function, you must define <b>HDF_LOG_TAG</b>, for example, #define HDF_LOG_TAG evt.
 *
 * @since 1.0
 * @version 1.0
 */
#define HDF_LOGD(...) ALOGD(__VA_ARGS__)
/**
 * @brief Prints logs at the information level.
 *
 * To use this function, you must define <b>HDF_LOG_TAG</b>, for example, #define HDF_LOG_TAG evt.
 *
 * @since 1.0
 * @version 1.0
 */
#define HDF_LOGI(...) ALOGI(__VA_ARGS__)

/**
 * @brief Prints logs at the warning level.
 *
 * To use this function, you must define <b>HDF_LOG_TAG</b>, for example, #define HDF_LOG_TAG evt.
 *
 * @since 1.0
 * @version 1.0
 */
#define HDF_LOGW(...) ALOGW(__VA_ARGS__)

/**
 * @brief Prints logs at the error level.
 *
 * To use this function, you must define <b>HDF_LOG_TAG</b>, for example, #define HDF_LOG_TAG evt.
 *
 * @since 1.0
 * @version 1.0
 */
#define HDF_LOGE(...) ALOGE(__VA_ARGS__)

#elif defined(__KERNEL__)
#define _HDF_FMT_TAG(TAG, LEVEL) "[" #LEVEL "/" #TAG "] "
#define HDF_FMT_TAG(TAG, LEVEL) _HDF_FMT_TAG(TAG, LEVEL)

/**
 * @brief Prints logs at the verbose level.
 *
 * To use this function, you must define <b>HDF_LOG_TAG</b>, for example, #define HDF_LOG_TAG evt.
 *
 * @since 1.0
 * @version 1.0
 */
#define HDF_LOGV(fmt, args...) printk(KERN_DEBUG HDF_FMT_TAG(HDF_LOG_TAG, V) fmt, ## args)
/**
 * @brief Prints logs at the debug level.
 *
 * To use this function, you must define <b>HDF_LOG_TAG</b>, for example, #define HDF_LOG_TAG evt.
 *
 * @since 1.0
 * @version 1.0
 */
#define HDF_LOGD(fmt, args...) printk(KERN_DEBUG HDF_FMT_TAG(HDF_LOG_TAG, D) fmt, ## args)
/**
 * @brief Prints logs at the information level.
 *
 * To use this function, you must define <b>HDF_LOG_TAG</b>, for example, #define HDF_LOG_TAG evt.
 *
 * @since 1.0
 * @version 1.0
 */
#define HDF_LOGI(fmt, args...) printk(KERN_INFO HDF_FMT_TAG(HDF_LOG_TAG, I) fmt, ## args)
/**
 * @brief Prints logs at the warning level.
 *
 * To use this function, you must define <b>HDF_LOG_TAG</b>, for example, #define HDF_LOG_TAG evt.
 *
 * @since 1.0
 * @version 1.0
 */
#define HDF_LOGW(fmt, args...) printk(KERN_WARNING HDF_FMT_TAG(HDF_LOG_TAG, W) fmt, ## args)
/**
 * @brief Prints logs at the error level.
 *
 * To use this function, you must define <b>HDF_LOG_TAG</b>, for example, #define HDF_LOG_TAG evt.
 *
 * @since 1.0
 * @version 1.0
 */
#define HDF_LOGE(fmt, args...) printk(KERN_ERR HDF_FMT_TAG(HDF_LOG_TAG, E) fmt, ## args)

#elif defined(__LITEOS__) && defined(__USER__)
/**
 * @brief Prints logs at the verbose level.
 *
 * To use this function, you must define <b>HDF_LOG_TAG</b>, for example, #define HDF_LOG_TAG evt.
 *
 * @since 1.0
 * @version 1.0
 */
#define HDF_LOGV(fmt, arg...) printf("[HDF:V/" LOG_TAG "]" fmt "\r\n", ##arg)
/**
 * @brief Prints logs at the debug level.
 *
 * To use this function, you must define <b>HDF_LOG_TAG</b>, for example, #define HDF_LOG_TAG evt.
 *
 * @since 1.0
 * @version 1.0
 */
#define HDF_LOGD(fmt, arg...) printf("[HDF:D/" LOG_TAG "]" fmt "\r\n", ##arg)
/**
 * @brief Prints logs at the information level.
 *
 * To use this function, you must define <b>HDF_LOG_TAG</b>, for example, #define HDF_LOG_TAG evt.
 *
 * @since 1.0
 * @version 1.0
 */
#define HDF_LOGI(fmt, arg...) printf("[HDF:I/" LOG_TAG "]" fmt "\r\n", ##arg)
/**
 * @brief Prints logs at the warning level.
 *
 * To use this function, you must define <b>HDF_LOG_TAG</b>, for example, #define HDF_LOG_TAG evt.
 *
 * @since 1.0
 * @version 1.0
 */
#define HDF_LOGW(fmt, arg...) printf("[HDF:W/" LOG_TAG "]" fmt "\r\n", ##arg)
/**
 * @brief Prints logs at the error level.
 *
 * To use this function, you must define <b>HDF_LOG_TAG</b>, for example, #define HDF_LOG_TAG evt.
 *
 * @since 1.0
 * @version 1.0
 */
#define HDF_LOGE(fmt, arg...) printf("[HDF:E/" LOG_TAG "]" fmt "\r\n", ##arg)
#elif defined(__LITEOS__)
/**
 * @brief Prints logs at the verbose level.
 *
 * To use this function, you must define <b>HDF_LOG_TAG</b>, for example, #define HDF_LOG_TAG evt.
 *
 * @since 1.0
 * @version 1.0
 */
#define HDF_LOGV(fmt, arg...) PRINT_DEBUG("[HDF:V/" LOG_TAG "]" fmt "\r\n", ##arg)
/**
 * @brief Prints logs at the debug level.
 *
 * To use this function, you must define <b>HDF_LOG_TAG</b>, for example, #define HDF_LOG_TAG evt.
 *
 * @since 1.0
 * @version 1.0
 */
#define HDF_LOGD(fmt, arg...) PRINT_DEBUG("[HDF:D/" LOG_TAG "]" fmt "\r\n", ##arg)
/**
 * @brief Prints logs at the information level.
 *
 * To use this function, you must define <b>HDF_LOG_TAG</b>, for example, #define HDF_LOG_TAG evt.
 *
 * @since 1.0
 * @version 1.0
 */
#define HDF_LOGI(fmt, arg...) PRINT_INFO("[HDF:I/" LOG_TAG "]" fmt "\r\n", ##arg)
/**
 * @brief Prints logs at the warning level.
 *
 * To use this function, you must define <b>HDF_LOG_TAG</b>, for example, #define HDF_LOG_TAG evt.
 *
 * @since 1.0
 * @version 1.0
 */
#define HDF_LOGW(fmt, arg...) PRINT_WARN("[HDF:W/" LOG_TAG "]" fmt "\r\n", ##arg)
/**
 * @brief Prints logs at the error level.
 *
 * To use this function, you must define <b>HDF_LOG_TAG</b>, for example, #define HDF_LOG_TAG evt.
 *
 * @since 1.0
 * @version 1.0
 */
#define HDF_LOGE(fmt, arg...) PRINT_ERR("[HDF:E/" LOG_TAG "]" fmt "\r\n", ##arg)
#else
/**
 * @brief Prints logs at the verbose level.
 *
 * To use this function, you must define <b>HDF_LOG_TAG</b>, for example, #define HDF_LOG_TAG evt.
 *
 * @since 1.0
 * @version 1.0
 */
#define HDF_LOGV(fmt, arg...) printf("[HDF:V/" LOG_TAG "]" fmt "\r\n", ##arg)
/**
 * @brief Prints logs at the debug level.
 *
 * To use this function, you must define <b>HDF_LOG_TAG</b>, for example, #define HDF_LOG_TAG evt.
 *
 * @since 1.0
 * @version 1.0
 */
#define HDF_LOGD(fmt, arg...) printf("[HDF:D/" LOG_TAG "]" fmt "\r\n", ##arg)
/**
 * @brief Prints logs at the information level.
 *
 * To use this function, you must define <b>HDF_LOG_TAG</b>, for example, #define HDF_LOG_TAG evt.
 *
 * @since 1.0
 * @version 1.0
 */
#define HDF_LOGI(fmt, arg...) printf("[HDF:I/" LOG_TAG "]" fmt "\r\n", ##arg)
/**
 * @brief Prints logs at the warning level.
 *
 * To use this function, you must define <b>HDF_LOG_TAG</b>, for example, #define HDF_LOG_TAG evt.
 *
 * @since 1.0
 * @version 1.0
 */
#define HDF_LOGW(fmt, arg...) printf("[HDF:W/" LOG_TAG "]" fmt "\r\n", ##arg)
/**
 * @brief Prints logs at the error level.
 *
 * To use this function, you must define <b>HDF_LOG_TAG</b>, for example, #define HDF_LOG_TAG evt.
 *
 * @since 1.0
 * @version 1.0
 */
#define HDF_LOGE(fmt, arg...) printf("[HDF:E/" LOG_TAG "]" fmt "\r\n", ##arg)

#endif /* __KERNEL__ */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* HDF_LOG_H */
/** @} */
