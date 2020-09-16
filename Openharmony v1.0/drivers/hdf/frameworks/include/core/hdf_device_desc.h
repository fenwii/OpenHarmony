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
 * @file hdf_device_desc.h
 *
 * @brief Declares functions related to driver loading, service obtaining, and power management.
 *
 * @since 1.0
 */

#ifndef HDF_DEVICE_DESC_H
#define HDF_DEVICE_DESC_H

#include "hdf_device_section.h"
#include "hdf_object.h"
#include "hdf_sbuf.h"

/**
 * @brief The maximum priority for loading the host and device.
 */
#define MAX_PRIORITY_NUM 200

/**
 * @brief Enumerates policies for releasing driver services developed based on the HDF.
 *
 * If a driver is developed based on the HDF and uses the service management feature of the HDF, you need to
 * configure the policy for releasing services to external systems.
 *
 * @since 1.0
 */
typedef enum {
    /** The driver does not provide services externally. */
    SERVICE_POLICY_NONE = 0,
    /** The driver provides services for kernel-level applications. */
    SERVICE_POLICY_PUBLIC,
    /** The driver provides services for both kernel- and user-level applications. */
    SERVICE_POLICY_CAPACITY,
    /** Driver services are not released externally but can be subscribed to. */
    SERVICE_POLICY_FRIENDLY,
    /** Driver services are only internally available.
    They are not released externally and cannot be subscribed to by external users. */
    SERVICE_POLICY_PRIVATE,
    /** The service policy is incorrect. */
    SERVICE_POLICY_INVALID
} ServicePolicy;

/**
 * @brief Enumerates driver loading policies.
 *
 * If a driver developed based on the HDF needs to use the on-demand loading mechanism in the HDF, the <b>PRELOAD</b>
 * field must be correctly set in the driver configuration information to control the driver loading mode.
 *
 * @since 1.0
 */
typedef enum {
    DEVICE_PRELOAD_ENABLE = 0, /**< The driver is loaded during system startup by default. */
    DEVICE_PRELOAD_DISABLE,     /**< The driver is not loaded during system startup by default. */
    DEVICE_PRELOAD_INVALID     /**< The loading policy is incorrect. */
} DevicePreload;

/**
 * @brief Defines the device object.
 *
 * This structure is a device object defined by the HDF and is used to store private data and interface information
 * of a device.
 *
 * @since 1.0
 */
struct HdfDeviceObject {
    /** Pointer to the service interface object, which is registered with the HDF by the driver */
    struct IDeviceIoService *service;
    /** Pointer to the private data of the device, which is read by the HDF from the configuration file and
    transmitted to the driver. */
    const struct DeviceResourceNode *property;
};

/**
 * @brief Defines the client object structure of the I/O service.
 *
 * This structure describes the invoker information of the I/O servcie.
 *
 * @since 1.0
 */
struct HdfDeviceIoClient {
    /** Device object corresponding to the client object */
    struct HdfDeviceObject *device;
    /** Private data of the client object. The driver can use <b>priv</b> to bind the internal data with the client. */
    void *priv;
};

/**
 * @brief Defines the driver service.
 *
 * When a driver releases services to user-level applications, the service interface must inherit this structure
 * and implements the <b>Dispatch</b> function in the structure.
 *
 * @since 1.0
 */
struct IDeviceIoService {
    /** Driver service object ID */
    struct HdfObject object;
    /**
     * @brief Called when the driver service is enabled by a user-level application.
     *
     * @param client Indicates the pointer to the client object of the service.
     * @return Returns <b>0</b> if the operation is successful; returns a negative value otherwise.
     *
     * @since 1.0
     */
    int32_t (*Open)(struct HdfDeviceIoClient *client);
    /**
     * @brief Called when the driver service is invoked by a user-level application.
     *
     * @param client Indicates the pointer to the client object of the service.
     * @param cmdId Indicates the command word of the service interface.
     * @param data Indicates the pointer to the data passed by the invoker.
     * @param reply Indicates the pointer to the data that needs to be returned to the invoker.
     * @return Returns <b>0</b> if the operation is successful; returns a negative value otherwise.
     *
     * @since 1.0
     */
    int32_t (*Dispatch)(struct HdfDeviceIoClient *client, int cmdId, struct HdfSBuf *data, struct HdfSBuf *reply);
    /**
     * @brief Called when the driver service is released by a user-level application.
     *
     * @param client Indicates the pointer to the client object of the service.
     *
     * @since 1.0
     */
    void (*Release)(struct HdfDeviceIoClient *client);
};

/**
 * @brief Called when the driver subscribes to other driver services.
 *
 * The callback is used in the service subscription mechanism. After the driver is registered with the HDF, the HDF
 * proactively invokes the callback after the subscribed-to driver is loaded.
 *
 * @since 1.0
 */
struct SubscriberCallback {
    /** Driver object of the subscriber */
    struct HdfDeviceObject *deviceObject;
    /**
     * @brief Called by the HDF when the subscribed-to driver service is loaded.
     *
     * @param deviceObject Indicates the pointer to the variable of the {@link HdfDeviceObject} type. This variable
     * is generated by the HDF and passed to the driver.
     * @param service Indicates the pointer to the service object.
     * @return Returns <b>0</b> if the operation is successful; returns a non-zero value otherwise.
     *
     * @since 1.0
     */
    int32_t (*OnServiceConnected)(struct HdfDeviceObject *deviceObject, const struct HdfObject *service);
};

/**
 * @brief Defines the power management functions provided by the HDF for the driver.
 *
 * To use the power management mechanism provided by the HDF, implement operations of <b>IPowerEventListener</b> and
 * invoke {@linkHdfDeviceRegisterPowerListener} to register the operations with the HDF.
 *
 * @since 1.0
 */
struct IPowerEventListener {
    /** Wakes up the driver device. The driver developer implements the operation. */
    void (*Resume)(struct HdfDeviceObject *deviceObject);
    /** Hibernates the driver device. The driver developer implements the operation. */
    void (*Suspend)(struct HdfDeviceObject *deviceObject);
};

/**
 * @brief Defines the entry structure of the driver in the HDF.
 *
 * This structure must be used as the entry for the driver to use the HDF mechanism.
 *
 * @since 1.0
 */
struct HdfDriverEntry {
    /** Driver version */
    int32_t moduleVersion;
    /** Driver module name, which is used to match the driver information in the configuration file. */
    const char *moduleName;
    /**
     * @brief Binds the external service interface of a driver to the HDF. This function is implemented by the driver
     * developer and called by the HDF.
     *
     * @param deviceObject Indicates the pointer to the variable of the {@link HdfDeviceObject} type. This variable
     * is generated by the HDF and passed to the driver. Then, the service object of the driver is bound to the
     * <b>service</b> parameter of <b>deviceObject</b>.
     * @return Returns <b>0</b> if the operation is successful; returns a non-zero value otherwise.
     *
     * @since 1.0
     */
    int32_t (*Bind)(struct HdfDeviceObject *deviceObject);
    /**
     * @brief Initializes the driver. This function is implemented by the driver developer and called by the HDF.
     *
     * @param deviceObject Indicates the pointer to the variable of the {@link HdfDeviceObject} type. It is the same
     * as the parameter of {@link Bind}.
     * @return Returns <b>0</b> if the operation is successful; returns a non-zero value otherwise.
     *
     * @since 1.0
     */
    int32_t (*Init)(struct HdfDeviceObject *deviceObject);
    /**
     * @brief Releases driver resources. This function is implemented by the driver developer. When an exception
     * occurs during driver loading or the driver is uninstalled, the HDF calls this function to release the
     * driver resources.
     *
     * @param deviceObject Indicates the pointer to the variable of the {@link HdfDeviceObject} type. It is the same
     * as the parameter of {@link Bind}.
     *
     * @since 1.0
     */
    void (*Release)(struct HdfDeviceObject *deviceObject);
};

/**
 * @brief Registers the driver with the HDF.
 *
 * For a driver developed based on the HDF, {@link HDF_INIT} must be used to register an entry with the HDF, and the
 * registered object must be of the {@link HdfDriverEntry} type.
 *
 * @param module Indicates the global variable of the {@link HdfDriverEntry} type
 *
 * @since 1.0
 */
#define HDF_INIT(module)  HDF_DRIVER_INIT(module)

/**
 * @brief Obtains the driver service object based on a driver service name.
 *
 * @param serviceName Indicates the pointer to the released driver service name.
 *
 * @return Returns the driver service object if the operation is successful; returns <b>NULL</b> otherwise.
 * @since 1.0
 */
const struct HdfObject *DevSvcManagerClntGetService(const char *svcName);

/**
 * @brief Obtains the service name of a driver.
 *
 * If a driver does not save its service name, it can use this function to obtain the service name. \n
 *
 * @param deviceObject Indicates the pointer to the driver device object.
 *
 * @return Returns the service name if the operation is successful; returns <b>NULL</b> otherwise.
 * @since 1.0
 */
const char *HdfDeviceGetServiceName(const struct HdfDeviceObject *deviceObject);

/**
 * @brief Subscribes to a driver service.
 *
 * If the driver loading time is not perceived, this function can be used to subscribe to the driver service. (The
 * driver service and the subscriber must be on the same host.) After the subscribed-to driver service is loaded by the
 * HDF, the framework proactively releases the service interface to the subscriber. \n
 *
 * @param deviceObject Indicates the pointer to the driver device object of the subscriber.
 * @param serviceName Indicates the pointer to the driver service name.
 * @param callback Indicates the callback invoked by the HDF after the subscribed-to driver service is loaded.
 *
 * @return Returns <b>0</b> if the operation is successful; returns a non-zero value otherwise.
 * @since 1.0
 */
int32_t HdfDeviceSubscribeService(
    struct HdfDeviceObject *deviceObject, const char *serviceName, struct SubscriberCallback callback);

/**
 * @brief Sends event messages.
 *
 * When the driver service invokes this function to send a message, all user-level applications that have registered
 * listeners through {@link HdfDeviceRegisterEventListener} will receive the message.
 *
 * @param deviceObject Indicates the pointer to the driver device object.
 * @param id Indicates the ID of the message sending event.
 * @param data Indicates the pointer to the message content sent by the driver.
 *
 * @return Returns <b>0</b> if the operation is successful; returns a non-zero value otherwise.
 * @since 1.0
 */
int32_t HdfDeviceSendEvent(const struct HdfDeviceObject *deviceObject, uint32_t id, const struct HdfSBuf *data);


/**
 * @brief Sends an event message to a specified client object.
 *
 * When the driver service invokes this function to send a message, the user-level applications that have registered
 * listeners through {@link HdfDeviceRegisterEventListener} and correspond to this client object will receive
 * the message.
 *
 * @param client Indicates the pointer to the client object of the driver service.
 * @param id Indicates the ID of the message sending event.
 * @param data Indicates the pointer to the message content sent by the driver.
 *
 * @return Returns <b>0</b> if the operation is successful; returns a non-zero value otherwise.
 * @since 1.0 */
int32_t HdfDeviceSendEventToClient(const struct HdfDeviceIoClient *client, uint32_t id, const struct HdfSBuf *data);

#endif /* HDF_DEVICE_DESC_H */
/** @} */
