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
 * @addtogroup wifiiot
 * @{
 *
 * @brief Provides dedicated device operation interfaces on the Wi-Fi module,
 * including ADC, AT, flash, GPIO, I2C, I2S, partition, PWM, SDIO, UART, and watchdog.
 *
 * @since 1.0
 * @version 1.0
 */

/**
 * @file wifiiot_adc.h
 *
 * @brief Declares the ADC interface functions for you to read data.
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef WIFIIOT_ADC_H
#define WIFIIOT_ADC_H

/**
 * @brief Enumerates ADC channel indexes.
 *
 */
typedef enum {
    /** Channel 0 */
    WIFI_IOT_ADC_CHANNEL_0,
    /** Channel 1 */
    WIFI_IOT_ADC_CHANNEL_1,
    /** Channel 2 */
    WIFI_IOT_ADC_CHANNEL_2,
    /** Channel 3 */
    WIFI_IOT_ADC_CHANNEL_3,
    /** Channel 4 */
    WIFI_IOT_ADC_CHANNEL_4,
    /** Channel 5 */
    WIFI_IOT_ADC_CHANNEL_5,
    /** Channel 6 */
    WIFI_IOT_ADC_CHANNEL_6,
    /** Channel 7 */
    WIFI_IOT_ADC_CHANNEL_7,
    /** Button value */
    WIFI_IOT_ADC_CHANNEL_BUTT,
} WifiIotAdcChannelIndex;

/**
 * @brief Enumerates analog power control modes.
 */
typedef enum {
    /** Automatic control */
    WIFI_IOT_ADC_CUR_BAIS_DEFAULT,
    /** Automatic control */
    WIFI_IOT_ADC_CUR_BAIS_AUTO,
    /** Manual control (AVDD = 1.8 V) */
    WIFI_IOT_ADC_CUR_BAIS_1P8V,
    /** Manual control (AVDD = 3.3 V) */
    WIFI_IOT_ADC_CUR_BAIS_3P3V,
    /** Button value */
    WIFI_IOT_ADC_CUR_BAIS_BUTT,
} WifiIotAdcCurBais;

/**
 * @brief Enumerates equation models.
 */
typedef enum {
    /** One-equation model */
    WIFI_IOT_ADC_EQU_MODEL_1,
    /** Two-equation model */
    WIFI_IOT_ADC_EQU_MODEL_2,
    /** Four-equation model */
    WIFI_IOT_ADC_EQU_MODEL_4,
    /** Eight-equation model */
    WIFI_IOT_ADC_EQU_MODEL_8,
    /** Button value */
    WIFI_IOT_ADC_EQU_MODEL_BUTT,
} WifiIotAdcEquModelSel;

/**
 * @brief Reads a piece of sampled data from a specified ADC channel based on the input parameters.
 *
 *
 *
 * @param channel Indicates the ADC channel index.
 * @param data Indicates the pointer to the address for storing the read data.
 * @param equModel Indicates the equation model.
 * @param curBais Indicates the analog power control mode.
 * @param rstCnt Indicates the count of the time from reset to conversion start.
 *               One count is equal to 334 ns. The value must range from 0 to 0xFF0.
 * @return Returns {@link WIFI_IOT_SUCCESS} if the operation is successful;
 *         returns an error code defined in {@link wifiiot_errno.h} otherwise.
 * @since 1.0
 * @version 1.0
 */
unsigned int AdcRead(WifiIotAdcChannelIndex channel, unsigned short *data, WifiIotAdcEquModelSel equModel,
                     WifiIotAdcCurBais curBais, unsigned short rstCnt);


#endif
/** @} */
