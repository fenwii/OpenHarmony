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
 * @addtogroup Core
 * @{
 *
 * @brief Provides OpenHarmony Driver Foundation (HDF) APIs.
 *
 * The HDF implements driver framework capabilities such as driver loading, service management,
 * and driver message model. You can develop drivers based on the HDF.
 *
 * @since 1.0
 */

/**
 * @file hdf_io_service_if.h
 *
 * @brief Declares the structures defining driver service objects and event listeners, as well as the functions for
 * obtaining a driver service object, dispatching a driver service call, and registering or unregistering an
 * event listener.
 *
 * @since 1.0
 */
#ifndef HDF_IO_SERVICE_IF_H
#define HDF_IO_SERVICE_IF_H

#include <sys/stat.h>
#include "hdf_dlist.h"
#include "hdf_object.h"
#include "hdf_sbuf.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @brief Called when a driver event occurs.
 *
 * You can implement this function and bind it to the custom {@link HdfDevEventlistener} object. \n
 *
 * @param priv Indicates the pointer to the private data bound to this listener.
 * @param id Indicates the serial number of the driver event occurred.
 * @param data Indicates the pointer to the content data of the driver event.
 * @return Returns <b>0</b> if the operation is successful; returns a negative value otherwise.
 *
 * @since 1.0
 */
typedef int (*OnEventReceived)(void *priv, uint32_t id, struct HdfSBuf *data);

/**
 * @brief Defines a driver event listener object.
 *
 * @since 1.0
 */
struct HdfDevEventlistener {
     /** Callback invoked when the monitored device reports an event */
    OnEventReceived callBack;
    /** Intrusive list node used by the HDF to manage listeners. You can ignore this node. */
    struct DListHead listNode;
    /** Private data of the listener, which is passed as the first input parameter in <b>callback</b> */
    void *priv;
};

/**
 * @brief Defines a driver service call dispatcher.
 *
 * @since 1.0
 */
struct HdfIoDispatcher {
    /** Dispatches a driver service call. <b>service</b> indicates the pointer to the driver service object, <b>id</b>
    indicates the command word of the function, <b>data</b> indicates the pointer to the data you want to pass to
    the driver, and <b>reply</b> indicates the pointer to the data returned by the driver. */
    int (*Dispatch)(struct HdfObject *service, int cmdId, struct HdfSBuf *data, struct HdfSBuf *reply);
};

/**
 * @brief Defines a driver service object.
 *
 * @since 1.0
 */
struct HdfIoService {
    /** Base class object */
    struct HdfObject object;
    /** Pointer to the bound service entity, which is used for framework management. You can ignore it. */
    struct HdfObject *target;
    /** Service call dispatcher */
    struct HdfIoDispatcher *dispatcher;
};

/**
 * @brief Obtains a driver service object.
 *
 * @param serviceName Indicates the pointer to the name of the service to obtain.
 * @param permission Indicates the permission to create device nodes. The default value <b>0</b> can be used
 * when this function is called from user space.
 * @return Returns the pointer to the driver service object if the operation is successful;
 * returns <b>NULL</b> otherwise.
 *
 * @since 1.0
 */
struct HdfIoService *HdfIoServiceBind(const char *serviceName, mode_t permission);

/**
 * @brief Destroys a specified driver service object to release resources if it is no longer required.
 *
 * @param service Indicates the pointer to the driver service object to destroy.
 *
 * @since 1.0
 */
void HdfIoServiceRecycle(struct HdfIoService *service);

/**
 * @brief Registers a custom {@link HdfDevEventlistener} for listening for events reported
 * by a specified driver service object.
 *
 * @param target Indicates the pointer to the driver service object to listen, which is obtained through
 * the {@link HdfIoServiceBind} function.
 * @param listener Indicates the pointer to the listener to register.
 * @return Returns <b>0</b> if the operation is successful; returns a negative value otherwise.
 *
 * @since 1.0
 */
int HdfDeviceRegisterEventListener(struct HdfIoService *target, struct HdfDevEventlistener *listener);

/**
 * @brief Unregisters a previously registered {@link HdfDevEventlistener} to release resources
 * if it is no longer required.
 *
 * @param target Indicates the pointer to the driver service object that has been listened.
 * @param listener Indicates the listener object registered by {@link HdfDeviceRegisterEventListener}.
 * @return Returns <b>0</b> if the operation is successful; returns a negative value otherwise.
 *
 * @since 1.0
 */
int HdfDeviceUnregisterEventListener(struct HdfIoService *target, struct HdfDevEventlistener *listener);
#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif /* HDF_IO_SERVICE_IF_H */
/** @} */
