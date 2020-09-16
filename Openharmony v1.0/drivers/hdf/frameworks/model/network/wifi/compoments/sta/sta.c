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

#include "sta.h"
#include "hdf_wifi_product.h"

#if __cplusplus
extern "C" {
#endif

struct WifiStaFeature g_staFeature;

static int32_t StaInit(struct WifiFeature *feature)
{
    (void)feature;
    return HDF_SUCCESS;
}

static int32_t StaDeinit(struct WifiFeature *feature)
{
    (void)feature;
    return HDF_SUCCESS;
}

static uint32_t Scan(struct NetDevice *netDev, struct WifiScanRequest *request)
{
    struct WifiMac80211Ops *macOps = (struct WifiMac80211Ops *)g_staFeature.fe.chip->ops;
    RETURN_IF_MACOPS_NOT_REGISTERED(macOps);
    RETURN_IF_MACOPS_NOT_IMPLEMENT(macOps, startScan);
    return macOps->startScan(netDev, request);
}

static void AbortScan(struct NetDevice *netDev)
{
    struct WifiMac80211Ops *macOps = (struct WifiMac80211Ops *)g_staFeature.fe.chip->ops;
    if (macOps == NULL) {
        HDF_LOGI("mac ops not registered");
        return;
    }

    if (macOps->abortScan != NULL) {
        macOps->abortScan(netDev);
    } else {
        HDF_LOGE("macOps abortScan not implement");
    }
}

static uint32_t Connect(struct NetDevice *netDev, struct WifiConnectParams *param)
{
    struct WifiMac80211Ops *macOps = (struct WifiMac80211Ops *)g_staFeature.fe.chip->ops;
    RETURN_IF_MACOPS_NOT_REGISTERED(macOps);
    RETURN_IF_MACOPS_NOT_IMPLEMENT(macOps, changeBeacon);
    return macOps->connect(netDev, param);
}

static uint32_t Disconnect(struct NetDevice *netDev, uint16_t reasonCode)
{
    struct WifiMac80211Ops *macOps = (struct WifiMac80211Ops *)g_staFeature.fe.chip->ops;
    RETURN_IF_MACOPS_NOT_REGISTERED(macOps);
    RETURN_IF_MACOPS_NOT_IMPLEMENT(macOps, disconnect);
    return macOps->disconnect(netDev, reasonCode);
}

struct WifiStaFeature g_staFeature = {
    .fe = {
        .name = "sta",
        .init = StaInit,
        .deInit = StaDeinit,
    },
    .ops = {
        .scan = Scan,
        .abortScan = AbortScan,
        .connect = Connect,
        .disconnect = Disconnect,
    },
};

struct WifiStaFeature *GetWifiStaFeature(const struct WifiModule *module)
{
    return (struct WifiStaFeature *)GetFeature(module, HDF_WIFI_FEATURE_STA);
}

struct WifiFeature *GetWifiStaFeatureDelc(void)
{
    return (struct WifiFeature *)&g_staFeature;
}

#ifdef __cplusplus
}
#endif
