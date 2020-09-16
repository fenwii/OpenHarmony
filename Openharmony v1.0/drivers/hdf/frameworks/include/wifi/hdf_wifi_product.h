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
 * @file hdf_wifi_product.h
 *
 * @brief Declares the data structure of the WLAN module.
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef HDFLITE_HDF_WIFI_PRODUCT_H
#define HDFLITE_HDF_WIFI_PRODUCT_H

#include "wifi_module.h"
#include "hdf_device_desc.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Defines the WLAN module.
 *
 * @since 1.0
 */
struct HdfWifiProductData {
    char product_name[MAX_WIFI_COMPONENT_NAME_LEN];  /**< WLAN module name, which contains a maximum of 10 bytes */
    char state;                                      /**< WLAN module state */
    struct WifiModule *module;                       /**< Structure of the WLAN module */
    struct HdfDeviceObject *device;                  /**< Structure of the Device Object */
};

/**
 * @brief Obtains the data structure of the WLAN module.
 *
 * @return Returns the pointer to the data structure of the WLAN module. For details, see {@link HdfWifiProductData}.
 *
 * @since 1.0
 * @version 1.0
 */
struct HdfWifiProductData *HdfWifiGetProduct(void);

#ifdef __cplusplus
}
#endif
#endif // HDFLITE_HDF_WIFI_PRODUCT_H
