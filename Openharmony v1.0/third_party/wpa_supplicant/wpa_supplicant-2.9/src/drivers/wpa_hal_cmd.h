/*
 * Driver interaction with hdf wifi
 * Copyright (c) 2020 Huawei Device Co., Ltd.
 *
 * This software may be distributed under the terms of the BSD license.
 * See README for more details.
 */

#ifndef _WPA_HAL_CMD_H_
#define _WPA_HAL_CMD_H_

#include <stdint.h>
#include "wpa_hal.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define IFNAMSIZ 16
typedef struct {
    char ifname[IFNAMSIZ + 1];
    uint32_t cmd;
    uint32_t bufLen;
    void *buf;
} IoctlMsgObj;

int32_t WifiWpaEapolPacketSend(const char *ifname, const uint8_t *srcAddr, const uint8_t *dstAddr,
    uint8_t *buf, uint32_t length);
int32_t WifiWpaEapolPacketReceive(const char *ifname, WifiRxEapol *rxEapol);
int32_t WifiWpaEapolEnable(const char *ifname);
int32_t WifiWpaEapolDisable(const char *ifname);

int32_t WifiWpaCmdSetAp(const char *ifname, WifiApSetting *apsettings);
int32_t WifiWpaCmdChangeBeacon(const char *ifname, WifiApSetting *apsettings);
int32_t WifiWpaCmdSendMlme(const char *ifname, WifiMlmeData *mlme);
int32_t WifiWpaCmdNewKey(const char *ifname, WifiKeyExt *keyExt);
int32_t WifiWpaCmdDelKey(const char *ifname, WifiKeyExt *keyExt);
int32_t WifiWpaCmdSetKey(const char *ifname, WifiKeyExt *keyExt);

int32_t WifiWpaCmdSetMode(const char *ifname, WifiSetMode *setMode);
int32_t WifiWpaCmdGetOwnMac(const char *ifname, void *buf, uint32_t len);
int32_t WifiWpaCmdGetHwFeature(const char *ifname, WifiHwFeatureData *hwFeatureData);
int32_t WifiWpaCmdScan(const char *ifname, WifiScan *scan);
int32_t WifiWpaCmdDisconnet(const char *ifname, int32_t reasonCode);
int32_t WifiWpaCmdAssoc(const char *ifname, WifiAssociateParams *assocParams);
int32_t WifiWpaCmdSetMaxStaNum(const char *ifname, void *buf, uint32_t len);
int32_t WifiWpaCmdSetNetdev(const char *ifname, WifiSetNewDev *info);
int32_t WifiWpaCmdStaRemove(const char *ifname, const uint8_t *addr, uint32_t addrLen);
int32_t WifiWpaCmdGetDrvFlags(const char *ifname, void *buf, uint32_t len);
int32_t WifiWpaCmdSendAction(const char *ifname, WifiActionData *actionData);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif /* end of wpa_hal_cmd.h */
