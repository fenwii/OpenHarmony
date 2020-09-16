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

#ifndef _HDF_WIFI_FEATURE_H_
#define _HDF_WIFI_FEATURE_H_

#include "wifi_module.h"
#include "hdf_wifi_cmd.h"
#include "net_device.h"
#include "wifi_mac80211_ops.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct WiFiBaseFeatureOps {
    uint32_t (*enableEapol)(struct NetDevice *netdev, WifiEnableEapol *param);
    uint32_t (*disableEapol)(struct NetDevice *netdev);
    uint32_t (*sendEapol)(struct NetDevice *netdev, WifiTxEapol *txData);
    uint32_t (*receiveEapol)(struct NetDevice *netdev, WifiRxEapol *rxData);
    uint32_t (*changeVirtualIntf)(struct NetDevice *netdev, uint8_t iftype, uint32_t *flags,
        struct VifParams *params);
    uint32_t (*addKey)(struct NetDevice *netdev, uint8_t keyIndex, bool pairwise, const uint8_t *mac_addr,
        struct KeyParams *params);
    uint32_t (*delKey)(struct NetDevice *netdev, uint8_t keyIndex, bool pairwise, const uint8_t *macAddr);
    uint32_t (*setDefaultKey)(struct NetDevice *netdev, uint8_t keyIndex, bool unicast, bool multicast);
    uint32_t (*setDefaultMgmtKey)(struct NetDevice *netdev, uint8_t keyIndex);
} WiFiBaseFeatureOps;

struct WifiBaseFeature {
    struct WifiFeature fe;
    WiFiBaseFeatureOps ops;
};


struct WifiModule *HdfGetWifiModule(void);
struct WifiBaseFeature *WifiBaseGetFeature(const struct WifiModule *module);
struct WifiFeature *GetFeature(const struct WifiModule *module, uint16_t featureType);
int32_t DeInitFeatures(struct WifiModule *module);
int32_t InitFeatures(struct WifiModule *module);

#define RETURN_IF_MACOPS_NOT_IMPLEMENT(macOps, opsName) do { \
        if (macOps->opsName == NULL) {                   \
            HDF_LOGE("macOps" #opsName "not implement"); \
            return HDF_ERR_INVALID_OBJECT;               \
        }                                                \
    } while (0)

#define RETURN_IF_MACOPS_NOT_REGISTERED(macOps) do { \
        if (macOps == NULL) {                  \
            HDF_LOGE("macOps not registered"); \
            return HDF_ERR_INVALID_OBJECT;     \
        }                                      \
    } while (0)

#ifdef __cplusplus
}
#endif
#endif // #ifndef _HDF_WIFI_FEATURE_H_