/*
 * Copyright (c) 2020 Huawei Device Co., Ltd.
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

 /**
 * @addtogroup Input
 * @{
 *
 * @brief Provides driver interfaces for the input service.
 *
 * These driver interfaces can be used to open and close input device files, get input events, query device information,
 * register callback functions, and control the feature status.
 *
 * @since 1.0
 * @version 1.0
 */

 /**
 * @file input_type.h
 *
 * @brief Declares types of input devices as well as the structure and enumeration types used by driver interfaces.
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef INPUT_TYPES_H
#define INPUT_TYPES_H

#include <stdint.h>
#include <stdbool.h>
#include <sys/time.h>

#ifdef __cplusplus
extern "C" {
#endif

#define MAX_INPUT_DEV_NUM 32
#define DEV_NODE_PATH 64
#define CHIP_INFO_LEN 10
#define CHIP_NAME_LEN 10
#define VENDOR_NAME_LEN 10
#define SELF_TEST_RESULT_LEN 20

/**
 * @brief Enumerates return values.
 */
enum RetStatus {
    INPUT_SUCCESS,       /**< Success */
    INPUT_EINVAL,        /**< Invalid value */
    INPUT_EFAULT,        /**< Runtime error */
    INPUT_ENOMEM,        /**< Failed to apply for memory */
    INPUT_ETIMEOUT,      /**< Execution timed out */
    INPUT_EUNSUPPORT,    /**< The feature is not supported */
    INPUT_EUNKNOWN,      /**< Unknown error */
};

/**
 * @brief Enumerates input device types.
 */
enum InputDevType {
    INDEV_TYPE_TOUCH,       /**< Touchscreen */
    INDEV_TYPE_KEY,         /**< Physical key */
    INDEV_TYPE_KEYBOARD,    /**< Keyboard */
    INDEV_TYPE_MOUSE,       /**< Mouse */
    INDEV_TYPE_BUTTON,      /**< Virtual button */
    INDEV_TYPE_CROWN,       /**< Watch crown */
    INDEV_TYPE_ENCODER,     /**< Customized type of a specific function or event */
    INDEV_TYPE_UNKNOWN,    /**< Unknown input device type */
};

/**
 * @brief Enumerates power statuses.
 */
enum PowerStatus {
    INPUT_RESUME,                  /**< Resume status */
    INPUT_SUSPEND,                 /**< Suspend status */
    INPUT_LOW_POWER,               /**< Low-power status */
    INPUT_POWER_STATUS_UNKNOWN,    /**< Unknown power status */
};

/**
 * @brief Enumerates types of capacitance tests.
 */
enum CapacitanceTest {
    BASE_TEST,             /**< Basic capacitance test */
    FULL_TEST,             /**< Full capacitance self-test */
    MMI_TEST,              /**< Man-Machine Interface (MMI) capacitance test */
    RUNNING_TEST,          /**< Running capacitance test */
    TEST_TYPE_UNKNOWN,     /**< Unknown test type */
};

/**
 * @brief Defines the extra commands.
 */
typedef struct {
    const char *cmdCode;     /**< Command code */
    const char *cmdValue;    /**< Data transmitted in the command */
} InputExtraCmd;

/**
 * @brief Describes the input event data.
 */
typedef struct {
    int32_t x;                   /**< X coordinate of a touch point */
    int32_t y;                   /**< Y coordinate of a touch point */
    int32_t pressure;            /**< Z coordinate of a touch point, such as the pressure */
    int32_t definedEvent;        /**< Specific input event, such as the pick-up or put-down event */
    uint32_t fingerID;           /**< Finger ID, used in multi-touch scenarios */
    uint32_t pointNum;           /**< Total number of fingers touching the screen */
    struct timeval timeStamp;    /**< Timestamp */
    bool moreDataFlag;           /**< Flag of continuous data read */
} InputEventData;

/**
 * @brief Describes the input event callback registered by the input service.
 */
typedef struct {
    /**
     * @brief Reports input event data by the registered callback.
     *
     * @param eventData Indicates the pointer to the input event data reported by the input driver.
     * @param count Indicates the number of input event data packets.
     * @param devIndex Indicates the index of an input device. A maximum of 32 input devices are supported.
     * The value ranges from 0 to 31, and value <b>0</b> represents the first input device.
     *
     * @since 1.0
     * @version 1.0
     */
    void (*ReportEventCallback)(const InputEventData *eventData, uint32_t count, uint32_t devIndex);
} InputReportEventCb;

/**
 * @brief Describes basic device information of the input device.
 */
typedef struct {
    uint32_t devIndex;                   /**< Device index */
    int32_t fd;                          /**< File descriptor of the device */
    uint32_t devType;                    /**< Device type */
    uint32_t powerStatus;                /**< Power status */
    char chipInfo[CHIP_INFO_LEN];        /**< Driver chip information */
    char vendorName[VENDOR_NAME_LEN];    /**< Module vendor name */
    char chipName[CHIP_NAME_LEN];        /**< Driver chip name */
    char devNodePath[DEV_NODE_PATH];     /**< Device file path */
    uint32_t solutionX;                  /**< Resolution in the X axis */
    uint32_t solutionY;                  /**< Resolution in the Y axis */
    InputReportEventCb *callback;        /**< Callback {@link InputReportEventCb} for reporting data */
} DeviceInfo;

#ifdef __cplusplus
}
#endif
#endif
/** @} */
