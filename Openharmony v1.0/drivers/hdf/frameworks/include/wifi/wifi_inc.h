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
 * @addtogroup WLAN
 * @{
 *
 * @brief Defines a WLAN module that supports cross-OS migration, component adaptation, and modular assembly and
 * compilation. Driver developers of WLAN vendors can adapt their driver code based on the unified APIs provided
 * by the WLAN module.
 *
 * @since 1.0
 * @version 1.0
 */

/**
 * @file wifi_inc.h
 *
 * @brief Describes the data structure of WLAN features and bus.
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef HDFLITE_WIFI_MODULE_INC_H
#define HDFLITE_WIFI_MODULE_INC_H

#ifdef __cplusplus
extern "C" {
#endif

struct WifiModule;
struct WifiFeature;
struct WifiFeatureList;
struct HdfWifiChipData;
struct BusDev;

/**
 * @brief Indicates the length of the name of a WLAN module or feature.
 *
 * The name of a WLAN module or feature cannot contain more than 10 characters; otherwise, the name will be truncated
 * and cannot be identified.
 *
 * @since 1.0
 */
#define MAX_WIFI_COMPONENT_NAME_LEN 10

/**
 * @brief Enumerates feature types of a WLAN module.
 *
 * You can query and register a feature or bind a feature to a WLAN module based on the feature type.
 *
 * @since 1.0
 */
enum WifiMainFeatureType {
    HDF_WIFI_FEATURE_BASE,     /**< Base feature */
    HDF_WIFI_FEATURE_AP,       /**< AP */
    HDF_WIFI_FEATURE_STA,      /**< Station */
    HDF_WIFI_FEATURE_P2P,      /**< Peer-to-peer (P2P) */
    HDF_WIFI_FEATURE_NAN,      /**< Neighbor Awareness Networking (NAN) */
    HDF_WIFI_FEATURE_RTT,      /**< Round Trip Time (RTT) */
    HDF_WIFI_FEATURE_NUM = 10  /**< Maximum number of features */
};

/**
 * @brief Enumerates bus types of a WLAN module.
 *
 * @since 1.0
 */
enum WifiBusType {
    BUS_SDIO,  /**< Secure Digital Input and Output (SDIO) */
    BUS_USB,   /**< Universal Serial Bus (USB) */
};

#ifdef __cplusplus
}
#endif

#endif // HDFLITE_WIFI_MODULE_INC_H

