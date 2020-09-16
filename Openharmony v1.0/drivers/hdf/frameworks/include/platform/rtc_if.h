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
 * @addtogroup RTC
 * @{
 *
 * @brief Provides standard real-time clock (RTC) APIs.
 *
 * These APIs allow you to perform operations such as reading or writing system time, reading or writing alarm time,
 * setting alarm interrupts, registering alarm callbacks, setting the external frequency, resetting the RTC driver,
 * and customizing RTC configurations. \n
 * The RTC driver provides precise real time for the operating system (OS). If the OS is powered off, the RTC driver
 * continues to keep track of the system time using an external battery.
 *
 * @since 1.0
 */

/**
 * @file rtc_if.h
 *
 * @brief Declares the standard RTC APIs.
 *
 * @since 1.0
 */

#ifndef RTC_IF_H
#define RTC_IF_H

#include "hdf_platform.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

/**
 * @brief Enumerates alarm indexes.
 *
 * The alarm indexes will be used when you perform operations related to alarms.
 *
 * @since V1.0
 */
enum RtcAlarmIndex {
    RTC_ALARM_INDEX_A = 0, /**< Index of alarm A */
    RTC_ALARM_INDEX_B = 1, /**< Index of alarm B */
};

/**
 * @brief Defines a callback that will be invoked when an alarm is generated at the specified time.
 *
 */
typedef int32_t (*RtcAlarmCallback)(enum RtcAlarmIndex);

/**
 * @brief Defines the RTC information.
 *
 * The RTC information includes the year, month, day, day of the week, hour, minute, second, and millisecond.
 * The start time is 1970/01/01 Thursday 00:00:00 (UTC).
 */
struct RtcTime {
    uint8_t second;       /**< Second. The value ranges from 0 to 59. */
    uint8_t minute;       /**< Minute. The value ranges from 0 to 59. */
    uint8_t hour;         /**< Hour. The value ranges from 0 to 23. */
    uint8_t day;          /**< Day. The value ranges from 1 to 31. */
    uint8_t weekday;      /**< Day of the week. The value ranges from 1 to 7, representing Monday to Sunday. */
    uint8_t month;        /**< Month. The value ranges from 1 to 12. */
    uint16_t year;        /**< Year. The value is greater than or equal to 1970. */
    uint16_t millisecond; /**< Millisecond. The value ranges from 0 to 990, with a precision of 10 milliseconds. */
};

/**
 * @brief Opens the RTC device to obtain its handle.
 *
 * The OS supports only one RTC device.
 *
 * @return Returns {@link DevHandle} if the operation is successful; returns <b>NULL</b> if the operation fails.
 * @since 1.0
 */
struct DevHandle *RtcOpen(void);

/**
 * @brief Releases a specified handle of the RTC device.
 *
 * @param handle Indicates the pointer to the RTC device handle to release, which is created via {@link RtcGetHandle}.
 *
 * @since 1.0
 */
void RtcClose(struct DevHandle *handle);

/**
 * @brief Reads time from the RTC driver.
 *
 * The time information includes the year, month, day, day of the week, hour, minute, second, and millisecond.
 *
 * @param handle Indicates the pointer to the RTC device handle, which is obtained via {@link RtcGetHandle}.
 * @param time Indicates the pointer to the time information read from the RTC driver.
 * For details, see {@link RtcTime}.
 *
 * @return Returns <b>0</b> if the operation is successful; returns a negative value if the operation fails.
 * For details, see {@link HDF_STATUS}.
 * @since 1.0
 */
int32_t RtcReadTime(struct DevHandle *handle, struct RtcTime *time);

/**
 * @brief Writes format-compliant time to the RTC driver.
 *
 * Note that the RTC start time is 1970/01/01 Thursday 00:00:00 (UTC). Set the maximum value of <b>year</b> based on
 * the requirements specified in the product manual of the in-use component.
 *
 * @param handle Indicates the pointer to the RTC device handle, which is obtained via {@link RtcGetHandle}.
 * @param time Indicates the pointer to the time information to write. For details, see {@link RtcTime}.
 *
 * @return Returns <b>0</b> if the operation is successful; returns a negative value if the operation fails.
 * For details, see {@link HDF_STATUS}.
 * @since 1.0
 */
int32_t RtcWriteTime(struct DevHandle *handle, const struct RtcTime *time);

/**
 * @brief Reads the RTC alarm time that was set last time.
 *
 * @param handle Indicates the pointer to the RTC device handle, which is obtained via {@link RtcGetHandle}.
 * @param alarmIndex Indicates the RTC alarm index. For details, see {@link RtcAlarmIndex}.
 * @param time Indicates the pointer to the RTC alarm time information. For details, see {@link RtcTime}.
 *
 * @return Returns <b>0</b> if the operation is successful; returns a negative value if the operation fails.
 * For details, see {@link HDF_STATUS}.
 * @since 1.0
 */
int32_t RtcReadAlarm(struct DevHandle *handle, enum RtcAlarmIndex alarmIndex, struct RtcTime *time);

/**
 * @brief Writes the RTC alarm time based on the alarm index.
 *
 * Note that the RTC start time is 1970/01/01 Thursday 00:00:00 (UTC). Set the maximum value of <b>year</b> based on
 * the requirements specified in the product manual of the in-use component.
 *
 * @param handle Indicates the pointer to the RTC device handle, which is obtained via {@link RtcGetHandle}.
 * @param alarmIndex Indicates the RTC alarm index. For details, see {@link RtcAlarmIndex}.
 * @param tm Indicates the pointer to the RTC alarm time information. For details, see {@link RtcTime}.
 *
 * @return Returns <b>0</b> if the operation is successful; returns a negative value if the operation fails.
 * For details, see {@link HDF_STATUS}.
 * @since 1.0
 */
int32_t RtcWriteAlarm(struct DevHandle *handle, enum RtcAlarmIndex alarmIndex, const struct RtcTime *time);

/**
 * @brief Registers {@link RtcAlarmCallback} that will be invoked when an alarm is generated at the specified time.
 *
 * @param handle Indicates the pointer to the RTC device handle, which is obtained via {@link RtcGetHandle}.
 * @param alarmIndex Indicates the RTC alarm index. For details, see {@link RtcAlarmIndex}.
 * @param cb Indicates the callback to register. For details, see {@link RtcAlarmCallback}.
 *
 * @return Returns <b>0</b> if the operation is successful; returns a negative value if the operation fails.
 * For details, see {@link HDF_STATUS}.
 * @since 1.0
 */
int32_t RtcRegisterAlarmCallback(struct DevHandle *handle, enum RtcAlarmIndex alarmIndex, RtcAlarmCallback cb);

/**
 * @brief Enables or disables alarm interrupts.
 *
 * Before performing alarm operations, you need to call this function to enable alarm interrupts,
 * so that the {@link RtcRegisterAlarmCallback} will be called when the alarm is not generated upon a timeout.
 *
 * @param handle Indicates the pointer to the RTC device handle, which is obtained via {@link RtcGetHandle}.
 * @param alarmIndex Indicates the RTC alarm index. For details, see {@link RtcAlarmIndex}.
 * @param enable Specifies whether to enable RTC alarm interrupts. The value <b>1</b> means to
 * enable alarm interrupts and value <b>0</b> means to disable alarm interrupts.
 *
 * @return Returns <b>0</b> if the operation is successful; returns a negative value if the operation fails.
 * For details, see {@link HDF_STATUS}.
 * @since 1.0
 */
int32_t RtcAlarmInterruptEnable(struct DevHandle *handle, enum RtcAlarmIndex alarmIndex, uint8_t enable);

/**
 * @brief Reads the RTC external frequency.
 *
 * This function reads the frequency of the external crystal oscillator connected to the RTC driver.
 *
 * @param handle Indicates the pointer to the RTC device handle, which is obtained via {@link RtcGetHandle}.
 * @param freq Indicates the pointer to the frequency of the external crystal oscillator, in Hz.
 *
 * @return Returns <b>0</b> if the operation is successful; returns a negative value if the operation fails.
 * For details, see {@link HDF_STATUS}.
 * @since 1.0
 */
int32_t RtcGetFreq(struct DevHandle *handle, uint32_t *freq);

/**
 * @brief Sets the frequency of the external crystal oscillator connected to the RTC driver.
 *
 * Note that the frequency must be configured in accordance with the requirements specified in the product manual of
 * the in-use component.
 *
 * @param handle Indicates the pointer to the RTC device handle, which is obtained via {@link RtcGetHandle}.
 * @param freq Indicates the frequency to set for the external crystal oscillator, in Hz.
 *
 * @return Returns <b>0</b> if the operation is successful; returns a negative value if the operation fails.
 * For details, see {@link HDF_STATUS}.
 * @since 1.0
 */
int32_t RtcSetFreq(struct DevHandle *handle, uint32_t freq);

/**
 * @brief Resets the RTC driver.
 *
 * After the reset, the configuration registers are restored to the default values.
 *
 * @param handle Indicates the pointer to the RTC device handle, which is obtained via {@link RtcGetHandle}.
 *
 * @return Returns <b>0</b> if the operation is successful; returns a negative value if the operation fails.
 * For details, see {@link HDF_STATUS}.
 * @since 1.0
 */
int32_t RtcReset(struct DevHandle *handle);

/**
 * @brief Reads the configuration of a custom RTC register based on the register index.
 *
 * One index corresponds to one byte of the configuration value.
 *
 * @param handle Indicates the pointer to the RTC device handle, which is obtained via {@link RtcGetHandle}.
 * @param usrDefIndex Indicates the index of the custom register.
 * @param value Indicates the pointer to the configuration value of the specified register index.
 *
 * @return Returns <b>0</b> if the operation is successful; returns a negative value if the operation fails.
 * For details, see {@link HDF_STATUS}.
 * @since 1.0
 */
int32_t RtcReadReg(struct DevHandle *handle, uint8_t usrDefIndex, uint8_t *value);

/**
 * @brief Writes the configuration of a custom RTC register based on the register index.
 *
 * One index corresponds to one byte of the configuration value.
 *
 * @param handle Indicates the pointer to the RTC device handle, which is obtained via {@link RtcGetHandle}.
 * @param usrDefIndex Indicates the index of the custom register.
 * @param value Indicates the configuration value to write at the index of the register.
 *
 * @return Returns <b>0</b> if the operation is successful; returns a negative value if the operation fails.
 * For details, see {@link HDF_STATUS}.
 * @since 1.0
 */
int32_t RtcWriteReg(struct DevHandle *handle, uint8_t usrDefIndex, uint8_t value);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* RTC_IF_H */
/** @} */

