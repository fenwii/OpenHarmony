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

#include "wifi_module.h"
#include "ap.h"
#include "eapol.h"
#include "sta.h"
#include "wifi_mac80211_ops.h"


struct WifiBaseFeature g_baseFeature;

int32_t BaseInit(struct WifiFeature *feature)
{
    (void)feature;
    return HDF_SUCCESS;
}

int32_t BaseDeinit(struct WifiFeature *feature)
{
    (void)feature;
    return HDF_SUCCESS;
}

static uint32_t EnableEapol(struct NetDevice *netdev, WifiEnableEapol *param)
{
    const struct Eapol *eapol = EapolGetInstance();
    return eapol->eapolOp->enableEapol(netdev, (struct EapolEnable *)param);
}
static uint32_t DisableEapol(struct NetDevice *netdev)
{
    const struct Eapol *eapol = EapolGetInstance();
    return eapol->eapolOp->disableEapol(netdev);
}
static uint32_t SendEapol(struct NetDevice *netdev, WifiTxEapol *txData)
{
    const struct Eapol *eapol = EapolGetInstance();
    return eapol->eapolOp->sendEapol(netdev, (struct EapolTx *)txData);
}
static uint32_t ReceiveEapol(struct NetDevice *netdev, WifiRxEapol *rxData)
{
    const struct Eapol *eapol = EapolGetInstance();
    return eapol->eapolOp->getEapol(netdev, (struct EapolRx *)rxData);
}

static uint32_t ChangeVirtualIntf(struct NetDevice *netDev, uint8_t iftype, uint32_t *flags,
    struct VifParams *params)
{
    struct WifiMac80211Ops *macOps = g_baseFeature.fe.chip->ops;
    RETURN_IF_MACOPS_NOT_REGISTERED(macOps);
    RETURN_IF_MACOPS_NOT_IMPLEMENT(macOps, changeVirtualIntf);
    return macOps->changeVirtualIntf(netDev, iftype, flags, params);
}

static uint32_t AddKey(struct NetDevice *netdev, uint8_t keyIndex, bool pairwise, const uint8_t *macAddr,
    struct KeyParams *params)
{
    struct WifiMac80211Ops *macOps = g_baseFeature.fe.chip->ops;
    RETURN_IF_MACOPS_NOT_REGISTERED(macOps);
    RETURN_IF_MACOPS_NOT_IMPLEMENT(macOps, addKey);
    return macOps->addKey(netdev, keyIndex, pairwise, macAddr, params);
}

static uint32_t DelKey(struct NetDevice *netdev, uint8_t keyIndex, bool pairwise, const uint8_t *macAddr)
{
    struct WifiMac80211Ops *macOps = g_baseFeature.fe.chip->ops;
    RETURN_IF_MACOPS_NOT_REGISTERED(macOps);
    RETURN_IF_MACOPS_NOT_IMPLEMENT(macOps, delKey);
    return macOps->delKey(netdev, keyIndex, pairwise, macAddr);
}

static uint32_t SetDefaultKey(struct NetDevice *netdev, uint8_t keyIndex, bool unicast, bool multicast)
{
    struct WifiMac80211Ops *macOps = g_baseFeature.fe.chip->ops;
    RETURN_IF_MACOPS_NOT_REGISTERED(macOps);
    RETURN_IF_MACOPS_NOT_IMPLEMENT(macOps, setDefaultKey);
    return macOps->setDefaultKey(netdev, keyIndex, unicast, multicast);
}

static uint32_t SetDefaultMgmtKey(struct NetDevice *netdev, uint8_t keyIndex)
{
    (void)netdev;
    (void)keyIndex;
    return HDF_SUCCESS;
}

struct WifiBaseFeature g_baseFeature = {
    .fe = {
        .name = "base",
        .init = BaseInit,
        .deInit = BaseDeinit,
    },
    .ops = {
        .enableEapol = EnableEapol,
        .disableEapol = DisableEapol,
        .sendEapol = SendEapol,
        .receiveEapol = ReceiveEapol,
        .changeVirtualIntf = ChangeVirtualIntf,
        .addKey = AddKey,
        .delKey = DelKey,
        .setDefaultKey = SetDefaultKey,
        .setDefaultMgmtKey = SetDefaultMgmtKey,
    }
};

struct WifiFeatureList g_featureList = { 0 };

int32_t InitFeatures(struct WifiModule *module)
{
    if (module == NULL) {
        HDF_LOGE("%s: error, no module", __func__);
        return HDF_FAILURE;
    }

    g_featureList.fe[HDF_WIFI_FEATURE_BASE] = (struct WifiFeature *)&g_baseFeature;
    g_featureList.fe[HDF_WIFI_FEATURE_AP] = GetWifiApFeatureDelc();
    g_featureList.fe[HDF_WIFI_FEATURE_STA] = GetWifiStaFeatureDelc();

    module->feList = &g_featureList;

    for (uint32_t i = 0; i < HDF_WIFI_FEATURE_NUM; i++) {
        if ((module->moduleConfig.hslConfig->featureMap & (1 << i)) && module->feList->fe[i] != NULL) {
            module->feList->fe[i]->init(module->feList->fe[i]);
        }
    }
    return HDF_SUCCESS;
}

struct WifiBaseFeature *WifiBaseGetFeature(const struct WifiModule *module)
{
    return (struct WifiBaseFeature *)GetFeature(module, HDF_WIFI_FEATURE_BASE);
}
