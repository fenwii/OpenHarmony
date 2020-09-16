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

#include <osal_mem.h>
#include "hdf_wifi_product.h"
#include "wifi_mac80211_ops.h"
#include "ap.h"

#if __cplusplus
extern "C" {
#endif

struct WifiApFeature g_apFeature;

static int32_t ApInit(struct WifiFeature *feature)
{
    (void)feature;
    return HDF_SUCCESS;
}

static int32_t ApDeinit(struct WifiFeature *feature)
{
    (void)feature;
    return HDF_SUCCESS;
}

static int32_t SetupWireLessDev(struct NetDevice *netDev, WifiApSetting *apSettings)
{
    if (netDev->ieee80211Ptr == NULL) {
        netDev->ieee80211Ptr = (struct WirelessDev *)OsalMemCalloc(sizeof(struct WirelessDev));
        if (netDev->ieee80211Ptr == NULL) {
            return HDF_ERR_INVALID_PARAM;
        }
    }

    if (netDev->ieee80211Ptr->presetChandef.chan == NULL) {
        netDev->ieee80211Ptr->presetChandef.chan =
            (struct Ieee80211Channel *)OsalMemCalloc(sizeof(struct Ieee80211Channel));
        if (netDev->ieee80211Ptr->presetChandef.chan == NULL) {
            OsalMemFree(netDev->ieee80211Ptr);
            netDev->ieee80211Ptr = NULL;
            return HDF_ERR_INVALID_PARAM;
        }
    }

    netDev->ieee80211Ptr->presetChandef.width = (enum WifiChannelType)apSettings->freqParams.bandwidth;
    netDev->ieee80211Ptr->presetChandef.centerFreq1 = apSettings->freqParams.centerFreq1;
    netDev->ieee80211Ptr->presetChandef.chan->hwValue = (uint16_t)apSettings->freqParams.channel;
    netDev->ieee80211Ptr->presetChandef.chan->band = IEEE80211_BAND_2GHZ;
    return HDF_SUCCESS;
}

static uint32_t StartAp(struct NetDevice *netDev, WifiApSetting *apSettings)
{
    int32_t ret = SetupWireLessDev(netDev, apSettings);
    if (ret) {
        HDF_LOGE("StartAp:failed to SetupWireLessDev, error[%d]", ret);
        return ret;
    }

    struct WifiMac80211Ops *macOps = (struct WifiMac80211Ops *)g_apFeature.fe.chip->ops;
    RETURN_IF_MACOPS_NOT_REGISTERED(macOps);
    Mac80211beaconParam beaconParam = { 0 };
    RETURN_IF_MACOPS_NOT_IMPLEMENT(macOps, setChannel);
    if (macOps->setChannel(netDev)) {
        HDF_LOGE("StartAp:failed to setChannel, error[%d]", ret);
        return HDF_FAILURE;
    }

    RETURN_IF_MACOPS_NOT_IMPLEMENT(macOps, setSsid);
    if (macOps->setSsid(netDev, (const uint8_t *)apSettings->ssid, apSettings->ssidLen)) {
        HDF_LOGE("StartAp:failed to setSsid, error[%d]", ret);
        return HDF_FAILURE;
    }

    beaconParam.interval = apSettings->beaconInterval;
    beaconParam.dtimPeriod = apSettings->dtimPeriod;
    beaconParam.hiddenSsid = (apSettings->hiddenSsid == 1);
    beaconParam.beaconData = &apSettings->beaconData;
    beaconParam.operationType = MAC_BEACON_ADD;
    RETURN_IF_MACOPS_NOT_IMPLEMENT(macOps, changeBeacon);
    if (macOps->changeBeacon(netDev, &beaconParam)) {
        return HDF_FAILURE;
    }

    RETURN_IF_MACOPS_NOT_IMPLEMENT(macOps, startAp);
    ret = macOps->startAp(netDev);
    if (ret) {
        HDF_LOGE("StartAp:failed to start ap, error[%d]", ret);
        return HDF_FAILURE;
    }
    return NetIfSetStatus(netDev, NETIF_UP);
}

static uint32_t StopAp(struct NetDevice *netDev)
{
    struct WifiMac80211Ops *macOps = (struct WifiMac80211Ops *)g_apFeature.fe.chip->ops;
    RETURN_IF_MACOPS_NOT_REGISTERED(macOps);
    RETURN_IF_MACOPS_NOT_IMPLEMENT(macOps, stopAp);
    uint32_t ret = macOps->stopAp(netDev);
    if (ret) {
        HDF_LOGE("StopAp:failed, error[%d]", ret);
        return ret;
    }

    return NetIfSetStatus(netDev, NETIF_DOWN);
}

static uint32_t DelStation(struct NetDevice *netDev, struct StationDelParameters *params)
{
    struct WifiMac80211Ops *macOps = (struct WifiMac80211Ops *)g_apFeature.fe.chip->ops;
    RETURN_IF_MACOPS_NOT_REGISTERED(macOps);
    RETURN_IF_MACOPS_NOT_IMPLEMENT(macOps, delStation);
    return macOps->delStation(netDev, params->mac);
}

static uint32_t ChangeBeacon(struct NetDevice *netDev, WifiApSetting *apSettings)
{
    if (netDev == NULL || apSettings == NULL) {
        HDF_LOGI("%s: parameter null", __func__);
        return HDF_FAILURE;
    }

    Mac80211beaconParam beaconParam = { 0 };
    struct WifiMac80211Ops *macOps = g_apFeature.fe.chip->ops;
    RETURN_IF_MACOPS_NOT_REGISTERED(macOps);
    RETURN_IF_MACOPS_NOT_IMPLEMENT(macOps, changeBeacon);
    beaconParam.interval = apSettings->beaconInterval;
    beaconParam.dtimPeriod = apSettings->dtimPeriod;
    beaconParam.hiddenSsid = (apSettings->hiddenSsid == 1);
    beaconParam.beaconData = &apSettings->beaconData;
    beaconParam.operationType = MAC_BEACON_SET;

    return macOps->changeBeacon(netDev, &beaconParam);
}

struct WifiApFeature g_apFeature = {
    .fe = {
        .name = "ap",
        .init = ApInit,
        .deInit = ApDeinit,
    },
    .ops = {
        .startAp = StartAp,
        .stopAp = StopAp,
        .delStation = DelStation,
        .changeBeacon = ChangeBeacon,
    },
};

struct WifiApFeature *WifiApGetFeature(const struct WifiModule *module)
{
    return (struct WifiApFeature *)GetFeature(module, HDF_WIFI_FEATURE_AP);
}

struct WifiFeature *GetWifiApFeatureDelc(void)
{
    return (struct WifiFeature *)&g_apFeature;
}

#if __cplusplus
extern "C"
}
#endif
