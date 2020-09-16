/*
 * Copyright (c) 2020 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * @addtogroup Softbus
 * @{
 *
 * @brief Provides high-speed, secure communication between devices.
 *
 * This module implements unified distributed communication capability management between nearby devices,
 * and provides link-independent device discovery and transmission interfaces to support service publishing
 * and data transmission.
 *
 * @since 1.0
 * @version 1.0
 */

/**
 * @file discovery_service.h
 *
 * @brief Declares unified device service publishing interfaces.
 *
 * This file provides capabilities related to device service publishing, including publishing services,
 * unpublishing services, and setting device parameters.
 * After multiple nearby devices are discovered and networked, these interfaces can be used to perform
 * service publishing-related operations. \n
 *
 * @since 1.0
 * @version 1.0
 */
#ifndef _DISCOVERY_SERVICE_H
#define _DISCOVERY_SERVICE_H
#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Enumerates media, such as Bluetooth, Wi-Fi, and USB, used for publishing services.
 *
 * Currently, the media can only be set to coap.
 *
 */
typedef enum {
    /** Automatic medium selection */
    AUTO = 0,
    /** Bluetooth */
    BLE = 1,
    /** Wi-Fi */
    COAP = 2,
    /** USB */
    USB = 3,
} ExchanageMedium;

/**
 * @brief Enumerates frequencies for publishing services.
 * This enumeration is involved only in Bluetooth and is not supported currently.
 */
typedef enum {
    /** Low */
    LOW = 0,
   /** Medium */
    MID = 1,
   /** High */
    HIGH = 2,
   /** Super-high */
    SUPER_HIGH = 3,
} ExchangeFre;

/**
 * @brief Enumerates the modes in which services are published.
 * The publishing service supports the passive mode. Lite devices support the passive mode only.
 */
typedef enum {
    /** Passive */
    DISCOVER_MODE_PASSIVE = 0x55,
    /** Proactive */
    DISCOVER_MODE_ACTIVE  = 0xAA
} DiscoverMode;

/**
 * @brief Defines service provisioning information sent to a discovering device.
 *
 */
typedef struct PublishInfo {
  /** Service publishing ID */
    int publishId;
  /** Service publishing mode, which can be {@link DISCOVER_MODE_PASSIVE} or {@link DISCOVER_MODE_ACTIVE } */
    int mode;
  /** Service publishing medium */
    ExchanageMedium medium;
  /** Service publishing frequency */
    ExchangeFre freq;
  /** Service publishing capabilities. For details, see {@link g_capabilityMap}. */
    const char *capability;
  /** Capability data for service publishing */
    unsigned char *capabilityData;
  /** Maximum length of the capability data for service publishing (2 bytes) */
    unsigned int dataLen;
} PublishInfo;

/**
 * @brief Enumerates failure reasons for publishing services.
 *
 * The failure reason is returned to the caller through the callback function.
 *
 */
typedef enum {
   /** Unsupported medium */
    PUBLISH_FAIL_REASON_NOT_SUPPORT_MEDIUM = 1,
   /** Invalid parameter */
    PUBLISH_FAIL_REASON_PARAMETER_INVALID = 2,
   /** Unknown reason */
    PUBLISH_FAIL_REASON_UNKNOWN = 0xFF
} PublishFailReason;

/**
 * @brief Enumerates supported capabilities published by a device.
 *
 */
typedef enum {
    /** MeeTime */
    HICALL_CAPABILITY_BITMAP = 0,
    /** Video reverse connection in the smart domain */
    PROFILE_CAPABILITY_BITMAP = 1,
    /** Gallery in Vision */
    HOMEVISIONPIC_CAPABILITY_BITMAP = 2,
    /** cast+ */
    CASTPLUS_CAPABILITY_BITMAP,
    /** Input method in Vision */
    AA_CAPABILITY_BITMAP,
    /** Device virtualization tool package */
    DVKIT_CAPABILITY_BITMAP,
    /** Distributed middleware */
    DDMP_CAPABILITY_BITMAP
} DataBitMap;

/**
 * @brief Defines the mapping between supported capabilities and bitmaps.
 *
 */
typedef struct {
    /** Bitmaps. For details, see {@link DataBitMap}. */
    DataBitMap bitmap;
    /** Capability. For details, see {@link g_capabilityMap}. */
    char *capability;
} CapabilityMap;

static const CapabilityMap g_capabilityMap[] = {
    {HICALL_CAPABILITY_BITMAP, (char *)"hicall"},
    {PROFILE_CAPABILITY_BITMAP, (char *)"profile"},
    {HOMEVISIONPIC_CAPABILITY_BITMAP, (char *)"castPlus"},
    {CASTPLUS_CAPABILITY_BITMAP, (char *)"homevisionPic"},
    {AA_CAPABILITY_BITMAP, (char *)"aaCapability"},
    {DVKIT_CAPABILITY_BITMAP, (char *)"dvKit"},
    {DDMP_CAPABILITY_BITMAP, (char *)"ddmpCapability"},
};

/**
 * @brief Enumerates device types.
 *
 */
typedef enum DeviceTypeEnum {
    /** Unknown */
    UNKOWN = 0x00,
    /** Smartphone */
    PHONE = 0x0E,
    /** Tablet */
    PAD = 0x11,
    /** Smart TV */
    TV = 0x9C,
    /** PC */
    PC = 0x0C,
    /** Audio device */
    AUDIO = 0x0A,
    /** Vehicle-mounted device */
    CAR = 0x83,
    /** Light device L0 */
    L0 = 0xF1,
    /** Light device L1 */
    L1 = 0xF2,
} DeviceType;

/**
 * @brief Defines the mappings between the device type enumerations and device type names.
 *
 */
typedef struct {
    /** Name of a device type. Only names defined in {@link g_devMap} are supported. */
    char *value;
    /** Enumeration of a device type. Only enumerations defined in {@link g_devMap} are supported. */
    DeviceType devType;
} DeviceMap;

static const DeviceMap g_devMap[] = {
    {(char *)"PHONE", PHONE},
    {(char *)"PAD", PAD},
    {(char *)"TV", TV},
    {(char *)"PC", PC},
    {(char *)"AUDIO", AUDIO},
    {(char *)"CAR", CAR},
    {(char *)"L0", L0},
    {(char *)"L1", L1}
};

/**
 * @brief Defines the callbacks for successful and failed service publishing.
 *
 */
typedef struct IPublishCallback {
    /** Callback for successful publishing */
    void (*onPublishSuccess)(int publishId);
    /** Callback for failed publishing */
    void (*onPublishFail)(int publishId, PublishFailReason reason);
} IPublishCallback;

/**
 * @brief Enumerates device information, such as its ID, type, and name.
 *
 */
typedef enum {
    /** Device ID. The value contains a maximum of 64 characters. */
    COMM_DEVICE_KEY_DEVID = 0,
    /** Device type. Currently, only <b>ddmpCapability</b> is supported. */
    COMM_DEVICE_KEY_DEVTYPE = 1,
    /** Device name. The value contains a maximum of 63 characters. */
    COMM_DEVICE_KEY_DEVNAME = 2,
    /** Reserved */
    COMM_DEVICE_KEY_MAX
} CommonDeviceKey;

/**
 * @brief Defines the type and content of a device to set.
 *
 */
typedef struct CommonDeviceInfo {
    /** Device information type. For details, see {@link CommonDeviceKey}. */
    CommonDeviceKey key;
    /** Content to set */
    const char *value;
} CommonDeviceInfo;

/**
 * @brief Publishes a service to the discovering device in the LAN.
 *
 * The <b>publicId</b> and <b>moduleName</b> uniquely identify a service. A maximum of three services can be published.
 *
 * @param moduleName Indicates the pointer to the module name of the upper-layer service.
 * The value contains a maximum of 63 bytes.
 * @param info Indicates the pointer to the service to publish. For details, see {@link PublishInfo}.
 * @param cb Indicates the pointer to the callback for service publishing. For details, see {@link IPublishCallback}.
 * @return Returns <b>0</b> if the operation is successful; returns <b>-1</b> otherwise.
 */
int PublishService(const char *moduleName, const struct PublishInfo* info, const struct IPublishCallback *cb);

/**
 * @brief Unpublishes a service based on the <b>publicId</b> and <b>moduleName</b>.
 *
 * @param moduleName Indicates the pointer to the module name of the upper-layer service.
 * The value contains a maximum of 63 bytes.
 * @param publishId Indicates the ID of the service to unpublish. The value must be greater than <b>0</b>.
 * @return Returns <b>0</b> if the operation is successful; returns a non-zero value otherwise.
 *
 */
int UnPublishService(const char *moduleName, int publishId);

/**
 * @brief Sets common device information, such as its ID, type, and name.
 *
 * @param devInfo Indicates the pointer to the device information array.
 * @param2 num Indicates the number of elements in the device information array.
 * If the value is inconsistent with the length of the device information array, the program breaks down.
 * @return Returns <b>0</b> if the operation is successful; returns a non-zero value otherwise.
 * @see PublishService
 */
int SetCommonDeviceInfo(const struct CommonDeviceInfo *devInfo, unsigned int num);
#ifdef __cplusplus
}
#endif
#endif /* _DISCOVERY__SERVICE_H */
